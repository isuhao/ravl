// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, Omniperception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_ENCODEFFMPEG_AVFORMAT_HEADER 
#define RAVL_ENCODEFFMPEG_AVFORMAT_HEADER 
//! rcsid="$Id: FFmpegDPOPacketStream.hh 7052 2008-12-04 14:43:12Z ees1wc $"
//! lib=RavlLibFFmpeg
//! docentry = "Ravl.API.Images.Video.Video IO.LibFFmpeg"

#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS 1
#include <stdint.h>
#endif

#include "Ravl/DP/SPort.hh"
#include "Ravl/Image/FFmpegPacket.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"

extern "C" {
//#if defined(LIBAVFORMAT_VERSION_MAJOR) && LIBAVFORMAT_VERSION_MAJOR >= 52
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
//#else 
//#include <avformat.h>
//#endif
}

namespace RavlN {
    using namespace RavlImageN;
  
  //: FFmpeg packet stream.
  
  class FFmpegEncodePacketStreamBodyC 
    : public DPOSPortBodyC<FFmpegPacketC>
  {
  public:
    FFmpegEncodePacketStreamBodyC(const StringC &filename);
    //: Constructor
    
    FFmpegEncodePacketStreamBodyC();
    //: Default constructor.
    
    ~FFmpegEncodePacketStreamBodyC();
    //: Destructor.
    
    bool Open(const StringC &filename);
    //: Open file.

    bool Open();
    //: Open file.
    
    bool CheckForOutPut();
    //: Check for a output video stream.
    
    AVFormatContext *FormatCtx()
    { return pFormatCtx; }
    //: Access format context.
    
    bool FirstVideoStream(IntT &videoStreamId,IntT &codecId);
    //: Find info about first video stream.
    
    //virtual FFmpegPacketC Put();
    bool Put();
    //: Get a packet from the stream.
    
    bool Put(const FFmpegPacketC &packet);
    //: Put a packet from the stream.

    virtual bool IsPutReady() const;
    //: Is get ready ?
    
    virtual bool GetAttr(const StringC &attrName,StringC &attrValue);
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool GetAttr(const StringC &attrName,IntT &attrValue);
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool GetAttr(const StringC &attrName,RealT &attrValue);
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.

    virtual bool SetAttr(const StringC &attrName,RealT &attrValue);
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
    virtual bool GetAttr(const StringC &attrName,bool &attrValue);
    //: Get a attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    
  protected:
    void Init();
    //: Initalise attributes.
    
    StringC out_filename;
    AVFormatContext *pFormatCtx;
    AVOutputFormat *fmt;
    AVStream *audio_st, *video_st;
    double audio_pts, video_pts;
    AVCodec *video_codec,*audio_codec;
    AVCodecContext *video_codec_context,*audio_codec_context;
    IntT video_outbuffer_sz,audio_outbuffer_sz,audio_input_frame_size;
    Int16T *samples;
    UInt8T *video_outbuf,*audio_outbuf,*picture_buf;
    AVFrame *picture, *tmp_picture;
    FloatT t,tincr,tincr2;

    IntT positionRefStream,width,height,done_header,write_nbr; // Stream to use as a position reference.
    Int64T currentTimeStamp;
    Int64T frameRate;
    Int64T frameRateBase;
    Int64T compression;
    
    Int64T startFrame; // Frame number of start of sequence.
    bool haveSeek,header_done; // Do we have seeking ?
    
    Int64T Frame2Time(Int64T frame) const;
    //: Convert a frame no into a time
    
    Int64T Time2Frame(Int64T time) const;
    //: Convert a  time into a frame no
    
  };

  
  //! userlevel=Normal
  //: FFmpeg packet stream. 
  //!cwiz:author
  
  class FFmpegEncodePacketStreamC
    : public DPOSPortC<FFmpegPacketC>
  {
  public:
    FFmpegEncodePacketStreamC(const StringC & filename) 
      : DPEntityC(*new FFmpegEncodePacketStreamBodyC(filename))
    {}
    //: Constructor 
    //!cwiz:author
    
    FFmpegEncodePacketStreamC(bool)
      : DPEntityC(*new FFmpegEncodePacketStreamBodyC())
    {}
    //: Constructor.
    
    FFmpegEncodePacketStreamC()
      : DPEntityC(true)
    {}
    //: Default constructor.
    
    FFmpegEncodePacketStreamC(const DPOSPortC<FFmpegPacketC> &other)
      : DPEntityC(dynamic_cast<const FFmpegEncodePacketStreamBodyC *>(other.BodyPtr(other)))
    {
     }
    //: Upcast constructor.
    
    bool Open(const StringC & filename) 
    { return Body().Open(filename); }
    //: Open file. 
    //!cwiz:author

    bool Open() 
    { return Body().Open(); }
    //: Open file.
    
    bool CheckForVideo() 
    { return Body().CheckForOutPut(); }
    //: Check for a readable video stream. 
    //!cwiz:author

    AVFormatContext *FormatCtx()
    { return Body().FormatCtx(); }
    //: Access format context.
    
    bool FirstVideoStream(IntT &videoStreamId,IntT &codecId)
    { return Body().FirstVideoStream(videoStreamId,codecId); }
    //: Find info about first video stream.
    
    bool Put(const FFmpegPacketC & packet) 
    {  
       return Body().Put(packet); 
     }
    //: Get a packet from the stream. 
    //!cwiz:author


    bool Put() 
    {  
       return Body().Put(); 
     }

    bool IsPutReady() const
    { return Body().IsPutReady(); }
    //: Is get ready ? 
    //!cwiz:author
    
    bool GetAttr(const StringC & attrName,StringC & attrValue) 
    { return Body().GetAttr(attrName,attrValue); }
    //: Get a attribute. 
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    //!cwiz:author
    
    bool GetAttr(const StringC & attrName,IntT & attrValue) 
    { return Body().GetAttr(attrName,attrValue); }
    //: Get a attribute. 
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    //!cwiz:author
    
    bool GetAttr(const StringC & attrName,RealT & attrValue) 
    { return Body().GetAttr(attrName,attrValue); }
    //: Get a attribute. 
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    //!cwiz:author
    
    bool GetAttr(const StringC & attrName,bool & attrValue) 
    { return Body().GetAttr(attrName,attrValue); }
    //: Get a attribute. 
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    //!cwiz:author

    bool SetAttr(const StringC & attrName,RealT & attrValue) 
    {  
        return Body().SetAttr(attrName,attrValue); }
    //: Get a attribute. 
    // Returns false if the attribute name is unknown.
    // This is for handling attributes such as frame rate, and compression ratios.
    //!cwiz:author
    
  protected:
    FFmpegEncodePacketStreamC(FFmpegEncodePacketStreamBodyC &bod)
      : DPEntityC(bod)
    {}
    //: Body constructor. 
    
    FFmpegEncodePacketStreamBodyC& Body()
    { return dynamic_cast<FFmpegEncodePacketStreamBodyC &>(DPEntityC::Body()); }
    //: Body Access. 
    
    const FFmpegEncodePacketStreamBodyC& Body() const
    { return dynamic_cast<const FFmpegEncodePacketStreamBodyC &>(DPEntityC::Body()); }
    //: Body Access. 
    
  };
}


#endif

