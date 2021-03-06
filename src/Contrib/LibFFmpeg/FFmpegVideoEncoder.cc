// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, Omniperception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: FFmpegVideoEncoder.cc 7052 2008-12-04 14:43:12Z ees1wc $"
//! lib=RavlLibFFmpeg

#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS 1
#include <stdint.h>
#endif

#include "Ravl/Image/FFmpegVideoEncoder.hh"
#include "Ravl/Exception.hh"
#include "Ravl/DP/AttributeValueTypes.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Image/Deinterlace.hh"
#include "Ravl/String.hh"
#include "Ravl/PointerManager.hh"
#include "Ravl/StrStream.hh"
#include "Ravl/BinStream.hh"


#if LIBAVFORMAT_VERSION_INT >= ((51<<16)+(12<<8)+1)
// Point at which swscale was introduced
#define LIBAVFORMAT_USE_SWSCALER
#endif

#ifdef LIBAVFORMAT_USE_SWSCALER
extern "C" {
  #if FFMPEG_OLD_HDR
    #include <swscale.h>
  #else
    #include <libswscale/swscale.h>
    #if  LIBAVFORMAT_VERSION_MAJOR > 52 && ( LIBAVFORMAT_VERSION_MAJOR > 53 || defined(LIBAVFORMAT_VERSION_MINOR) && LIBAVFORMAT_VERSION_MINOR >= 2)
      // Libav fork removemd mathematics.h from avutil.h between 53-2-0 and
      // 53-3-0 necessitating explicit inclusion.
      #ifndef AVUTIL_MATHEMATICS_H
        #include <libavutil/mathematics.h>
      #endif
    #endif
  #endif
}
#endif

#define DODEBUG 0

#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlImageN {
  
  //: Constructor.
  
  FFmpegVideoEncoderBaseC::FFmpegVideoEncoderBaseC(DPOPortC<FFmpegPacketC> &_packetStream,IntT _videoStreamId,IntT _codecId) 
    : videoStreamId(-1),
      pcodecctx(0),
      pFrame(0),
      bytesRemaining(0),
      rawData(0),
      streamInfo(0),
      pSWSCtx(0),
      m_haveFullSeek(true),
      open_done(false)
  {
    if(!Open(_packetStream,_videoStreamId,_codecId)) {
      throw ExceptionOperationFailedC("Failed to open video stream. ");
    }
  }
  
  //: Default constructor.
  
  FFmpegVideoEncoderBaseC::FFmpegVideoEncoderBaseC() 
    : videoStreamId(-1),
      pcodecctx(0),
      pFrame(0),
      bytesRemaining(0),
      rawData(0),
      streamInfo(0),
      pSWSCtx(0),
      m_haveFullSeek(true),
      open_done(false)
  {}
  
  //: Destructor.
  
  FFmpegVideoEncoderBaseC::~FFmpegVideoEncoderBaseC() {
    // Clean up codec
    if(pcodecctx != 0)
      avcodec_close(pcodecctx);
    if(tmp_picture != 0)
      av_free(tmp_picture);
#ifdef LIBAVFORMAT_USE_SWSCALER
    if(pSWSCtx != 0)
      sws_freeContext(pSWSCtx); 
#endif
  }





  //: Open a stream.
  
  bool FFmpegVideoEncoderBaseC::Open(DPOPortC<FFmpegPacketC> &packetStream,IntT _videoStreamId,IntT codecId) {
    output = packetStream;
    ONDEBUG(cerr << "FFmpegVideoEncoderBaseC::Open(DPOPortC<FFmpegPacketC> &packetStream,IntT _videoStreamId,IntT codecId), Called " << _videoStreamId << "\n");

   psc = FFmpegEncodePacketStreamC(packetStream);
    ONDEBUG(cerr << "FFmpegVideoEncoderBaseC::Open(DPOPortC<FFmpegPacketC> &packetStream,IntT _videoStreamId,IntT codecId), psc allocated \n");    
   //Alloctae the output media context.

    out_filename = filename;
    ONDEBUG(cerr << "FFmpegVideoEncoderBaseC::Open(DPOPortC<FFmpegPacketC> &packetStream,IntT _videoStreamId,IntT codecId), streamInfo allocated \n");

    videoStreamId = _videoStreamId;

    tmp_picture=avcodec_alloc_frame();
    if (!tmp_picture) {
        return NULL;
    }

        ONDEBUG(cerr << "FFmpegVideoEncoderDPOBaseC::Open codecID is " << codecId << " \n");
#if LIBAVCODEC_VERSION_MAJOR > 53
    codec_id = (AVCodecID)codecId;
#else
    codec_id = (CodecID)codecId;
#endif
    return true;


  }

  bool FFmpegVideoEncoderBaseC::finishOpen() {

   pFormatCtx = psc.FormatCtx();   //av_alloc_format_context();  //avformat_alloc_context();
   if(!pFormatCtx) {
      ONDEBUG(cerr << "FFmpegPacketStreamBodyC::Open(" << filename << "), Failed allocate output media context. \n");
      return false;
    }
    videoStreamId = psc.getVideoStreamId();
    streamInfo = pFormatCtx->streams[videoStreamId];

    vCodecCtx = psc.VideoCodecCtx();
    if(!vCodecCtx) {
      ONDEBUG(cerr << "FFmpegPacketStreamBodyC::Open(" << filename << "), Failed allocate output media context. \n");
      return false;
    }
    size = avpicture_get_size(PIX_FMT_RGB24, width, height);
    picture_buf = (uint8_t *)av_malloc(size);
    if (!picture_buf) {
        av_free(picture);
        ONDEBUG(cerr << "FFmpegVideoEncoderDPOBaseC::finishOpen() picture_buf error" << " \n");
        return NULL;
    }
    avpicture_fill((AVPicture *)tmp_picture, picture_buf,
                   PIX_FMT_RGB24, width, height);
    open_done = true;
    return true;
  }

  //: Encode the next frame.
  
  bool FFmpegVideoEncoderBaseC::EncodeFrame() {
    int             bytesEncoded;
        video_outbuf = new uint8_t[numBytes];
        bytesEncoded=avcodec_encode_video(pcodecctx, video_outbuf, numBytes, tmp_picture);  //pFrame);  //,
          //                                &frameFinished, rawData, bytesRemaining);        

        // Was there an error?
        if(bytesEncoded < 0) {
          return false;
        }
        packet = FFmpegPacketC(true);
                AVPacket pkt;
        av_init_packet(&pkt);

#if LIBAVUTIL_VERSION_MAJOR >= 51
        pkt.flags |= AV_PKT_FLAG_KEY;
#else
        pkt.flags |= PKT_FLAG_KEY;
#endif
        pkt.stream_index= streamInfo->index;
        pkt.data= (uint8_t *)video_outbuf;  //(uint8_t *)tmp_picture->data;   //(uint8_t *)video_outbuf;   //tmp_picture->data;  //(uint8_t *)video_outbuf;
        pkt.size= bytesEncoded;   //video_outbuf_size;  //sizeof(AVPicture);
        packet.setPacket(pkt);
        delete video_outbuf;
        return true;
  }
  
  bool FFmpegVideoEncoderBaseC::Put() {
    ONDEBUG(cerr << "FFmpegVideoDecoderDPOBaseC::Put " << " \n");
    return false;
  }

  //: Get a frame of video from stream.
  
  bool FFmpegVideoEncoderBaseC::PutFrame( const ImageC<ByteRGBValueC> &img) {
    if(!open_done) {
       width = img.Cols();
       height = img.Rows();
       psc.finishOpen(width,height);
       finishOpen();
    }
    //Need to re write the header as the image size was unknown to the ProbeLoad/ProbeSave methods due to architecture reasons.
    AVStream *st = streamInfo;
    IntT out_size, ret;
    AVCodecContext *c;
    static struct SwsContext *img_convert_ctx;

    c = vCodecCtx;   //streamInfo->codec;

    if (0) {
        /* no more frame to compress. The codec has a latency of a few
           frames if using B frames, so we get the last frames by
           passing the same picture again */
    } else {
        if (img_convert_ctx == NULL) {
            #ifdef LIBAVFORMAT_USE_SWSCALER
            img_convert_ctx = sws_getContext(img.Cols(), img.Rows(),
                                             PIX_FMT_RGB24,
                                             img.Cols(), img.Rows(),
                                             PIX_FMT_YUV420P,
                                             SWS_BICUBIC, NULL, NULL, NULL);
            //#else
            //    img_convert((AVPicture *)pFrameRGB, PIX_FMT_RGB24, (AVPicture*)pFrame, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height);
            //#endif
            if (img_convert_ctx == NULL) {
                ONDEBUG(cerr << "FFmpegVideoEncoderDPOBaseC::PutFrame Cannot initialize the conversion context" << " \n");
                fprintf(stderr, "Cannot initialize the conversion context\n");
                exit(1);
            }
            #endif
        }
        
    //AVFrame *picture;
    int size;

    out_picture = avcodec_alloc_frame();
    if (!out_picture) {
        ONDEBUG(cerr << "FFmpegVideoEncoderDPOBaseC::PutFrame out_picture = NULL" << " \n");
        return NULL;
    }
    size = avpicture_get_size(PIX_FMT_YUV420P,img.Cols(),img.Rows());   //pix_fmt, width, height);
    picture_buf2 = (uint8_t *)av_malloc(size);   //new uint8_t[size];   // (uint8_t *)av_malloc(size);
    if (!picture_buf2) {
        ONDEBUG(cerr << "FFmpegVideoEncoderDPOBaseC::PutFrame picture_buf2 = NULL" << " \n");
        av_free(picture);
        return NULL;
    }
    avpicture_fill((AVPicture *)out_picture, picture_buf2,
                   PIX_FMT_YUV420P, img.Cols(), img.Rows());
    if (!out_picture) {
        ONDEBUG(cerr << "FFmpegVideoEncoderDPOBaseC::PutFrame out_picture = NULL" << " \n");
        return NULL;
    }
    out_size = avpicture_get_size(c->pix_fmt, img.Cols(), img.Rows());

        uint8_t *r;
        r = tmp_picture->data[ 0 ];
        //const ByteRGBValueC *all_v = img.Row(0);
        Array2dIterC<ByteRGBValueC> img_it(img);
        for(;img_it;img_it++) {
           *r = img_it.Data().Red();
           r++;
           *r = img_it.Data().Green();
           r++;
           *r = img_it.Data().Blue();
           r++;
        }
        #ifdef LIBAVFORMAT_USE_SWSCALER
        sws_scale(img_convert_ctx, tmp_picture->data, tmp_picture->linesize,
                  0, c->height, out_picture->data, out_picture->linesize);
        #else
        img_convert((AVPicture *)tmp_picture, PIX_FMT_RGB24, (AVPicture*)out_picture, PIX_FMT_YUV420P, img.Cols(), img.Rows());
        #endif
    }
   if (pFormatCtx->oformat->flags & AVFMT_RAWPICTURE) {
        AVPacket pkt;
        av_init_packet(&pkt);

#if LIBAVUTIL_VERSION_MAJOR >= 51
        pkt.flags |= AV_PKT_FLAG_KEY;
#else
        pkt.flags |= PKT_FLAG_KEY;
#endif
        pkt.stream_index= st->index;
        pkt.data= (uint8_t *)tmp_picture;
        pkt.size= sizeof(AVPicture);

            packet = FFmpegPacketC(true);
            packet.setPacket(pkt);
            packet.setWH(img.Cols(),img.Rows());
            ret = output.Put(packet);
    } else {  
        /* encode the image */
        video_outbuf = (uint8_t *)av_malloc(out_size);   //new uint8_t[out_size];
        int encode_size = avcodec_encode_video(c, video_outbuf, out_size, out_picture);

        /* if zero size, it means the image was buffered */
        if (encode_size > 0) {
            AVPacket pkt;
            av_init_packet(&pkt);

            int64_t comp = 0x8000000000000000LL;

            if (c->coded_frame->pts != comp ) {
                pkt.pts= av_rescale_q(c->coded_frame->pts, c->time_base, st->time_base);
            }
            if(c->coded_frame->key_frame) {
#if LIBAVUTIL_VERSION_MAJOR >= 51
              pkt.flags |= AV_PKT_FLAG_KEY;
#else
                pkt.flags |= PKT_FLAG_KEY;
#endif
            }
            pkt.stream_index= pFormatCtx->streams[videoStreamId]->index;   //st->index;
            pkt.data= video_outbuf;   //(uint8_t *)out_picture->data;   //video_outbuf;
            pkt.size= encode_size;

            /* write the compressed frame in the media file */
            packet = FFmpegPacketC(true);
            packet.setPacket(pkt);
            packet.setWH(img.Cols(),img.Rows());
            ret = output.Put(packet);
            if(!ret) {
          // There can't be any more frames in the stream.
               return false; // Failed to find next packet.
            }
        } else {
            ret = 0;
        }
    }
    if (ret == 0) {
        fprintf(stderr, "Error while writing video frame\n");
        exit(1);
    }
    frame_count++;
    delete video_outbuf;
    #ifdef LIBAVFORMAT_USE_SWSCALER
    sws_freeContext(pSWSCtx);
    #endif
    av_free(picture_buf2);
    return true;
  }

  //: Get a attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling attributes such as frame rate, and compression ratios.
  
  bool FFmpegVideoEncoderBaseC::GetHandleAttr(const StringC &attrName,StringC &attrValue) {
    if(attrName == "filename" || attrName == "title" || attrName == "author" || 
       attrName == "copyright"|| attrName == "comment"|| attrName == "album") {
      if(!output.IsValid() || !output.GetAttr(attrName,attrValue))
        attrValue = StringC("");
      return true;
    }
    if(attrName == "aspectratio") {
      if(vCodecCtx == 0)
        attrValue = "?";
      else
        attrValue = StringC(vCodecCtx->sample_aspect_ratio.num) + ":" + StringC(vCodecCtx->sample_aspect_ratio.den);
      return true;
    }
    return false;
  }
    
  //: Get a attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling attributes such as frame rate, and compression ratios.
  
  bool FFmpegVideoEncoderBaseC::GetHandleAttr(const StringC &attrName,IntT &attrValue) {
    return false;
  }
  
  //: Get a attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling attributes such as frame rate, and compression ratios.
  
  bool FFmpegVideoEncoderBaseC::GetHandleAttr(const StringC &attrName,RealT &attrValue) {
    if(attrName == "framerate") {
      if(!output.IsValid() || !output.GetAttr(attrName,attrValue))
        attrValue = 0.0;
      return true;
    }
    if(attrName == "compression") {
      if(!output.IsValid() || !output.GetAttr(attrName,attrValue)) {
        attrValue = 0.0;
      }
      return true;
    }
    return false;
  }
 
 //: Set a attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling attributes such as frame rate, and compression ratios.
  
  bool FFmpegVideoEncoderBaseC::SetHandleAttr(const StringC &attrName,const RealT &attrValue) {
    if(attrName == "compression") {
      if(!output.IsValid() || !output.SetAttr(attrName,attrValue)) {
        //attrValue = 0.0;
      }
      return true;
    }
    return false;
  }
 
 //: Get a attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling attributes such as frame rate, and compression ratios.
  
  bool FFmpegVideoEncoderBaseC::SetHandleAttr(const StringC &attrName,const IntT &attrValue) {
    if(attrName == "compression") {
      if(!output.IsValid() || !output.SetAttr(attrName,attrValue)) {
        //attrValue = 0.0;
      }
      return true;
    }
    return false;
  }

 //: Get a attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling attributes such as frame rate, and compression ratios.
  
  bool FFmpegVideoEncoderBaseC::SetHandleAttr(const StringC &attrName,const StringC &attrValue) {
    if(attrName == "compression") {
      if(!output.IsValid() || !output.SetAttr(attrName,attrValue)) {
        //attrValue = 0.0;
      }
      return true;
    }
    return false;
  }

  //: Get a attribute.
  // Returns false if the attribute name is unknown.
  // This is for handling attributes such as frame rate, and compression ratios.
  
  bool FFmpegVideoEncoderBaseC::GetHandleAttr(const StringC &attrName,bool &attrValue) {
    return false;
  }
  
  //: Initalise attributes.
  
  void FFmpegVideoEncoderBaseC::InitAttr(AttributeCtrlBodyC &attrCtrl) {
    ONDEBUG(cerr << "FFmpegVideoEncoderBaseC::InitAttr " << " \n");
    attrCtrl.RegisterAttribute(AttributeTypeNumC<RealT>("framerate","Frame rate of video",true,true,0.0,1000.0,0.01,25));
    attrCtrl.RegisterAttribute(AttributeTypeStringC("aspectratio","Aspect ratio",true,false,"4:3"));
    
    attrCtrl.RegisterAttribute(AttributeTypeStringC("filename","Original filename of stream",true,false,""));
    attrCtrl.RegisterAttribute(AttributeTypeStringC("title","Title of stream",true,false,""));
    attrCtrl.RegisterAttribute(AttributeTypeStringC("author","Author",true,false,""));
    attrCtrl.RegisterAttribute(AttributeTypeStringC("copyright","Copyright for material",true,false,""));
    attrCtrl.RegisterAttribute(AttributeTypeStringC("comment","Comment",true,false,""));
    attrCtrl.RegisterAttribute(AttributeTypeStringC("album","album",true,false,""));
    attrCtrl.RegisterAttribute(AttributeTypeNumC<RealT>("compression","compression ratio",true,true,1,31,1,31));
  }

  
}
