// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////
//! userlevel=Normal
//! rcsid="$Id$"
//! lib=RavlVideoIO
//! author="Charles Galambos"
//! date="24/03/2002"
//! file="Ravl/Image/VideoIO/ImgIOjs.cc"

#include "Ravl/Image/ImgIOjs.hh"
#include "Ravl/OS/Filename.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/BinStream.hh"
#include "Ravl/DP/ByteFileIO.hh"
#include "Ravl/DP/SPortAttach.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlImageN {

  //: Constructor.
  // This constructs with the basic yuv format.
  
  DPImageJSBaseBodyC::DPImageJSBaseBodyC()
    : frameSize(0),
      framePadding(0),
      frameNo(0),
      seqSize((UIntT) -1),
      blockSize(16384),
      offset(0)
  { }

  //: Constructor.
  
  DPImageJSBaseBodyC::DPImageJSBaseBodyC(const StringC &filename,bool read)
    : frameSize(0),
      framePadding(0),
      frameNo(0),
      seqSize((UIntT) -1),
      blockSize(16384),
      offset(0)
  {
    if (read)
    {
      DPIByteFileC byteFile(filename);
      m_inputStream = DPISPortAttachC<ByteT>(byteFile, byteFile);
    }
    else
    {
      m_outputStream = DPOByteFileC(filename);
    }
  }



  DPImageJSBaseBodyC::DPImageJSBaseBodyC(DPISPortC<ByteT> inputPort)
    : frameSize(0),
      framePadding(0),
      frameNo(0),
      seqSize((UIntT) -1),
      blockSize(16384),
      offset(0)
  {
    m_inputStream = inputPort;
  }



  DPImageJSBaseBodyC::DPImageJSBaseBodyC(DPOPortC<ByteT> outputPort)
    : frameSize(0),
      framePadding(0),
      frameNo(0),
      seqSize((UIntT) -1),
      blockSize(16384),
      offset(0)
  {
    m_outputStream = outputPort;
  }

  //: Read header from stream.
  
  bool DPImageJSBaseBodyC::ReadHeader() {
    if(!m_inputStream.IsValid() || !m_inputStream.IsGetReady()) {
      cerr << "DPImageJSBaseBodyC::ReadHeader(), Bad stream. \n";
      return false;
    }
    ByteT magic[4];
    SArray1dC<ByteT> magicArray(magic, 4, false);
    if(m_inputStream.GetArray(magicArray) < 0) {
      cerr << "DPImageJSBaseBodyC::ReadHeader(), Failed to read magic bytes. \n";
      return false;
    }
#if DODEBUG
    for(int i = 0;i < 4;i++)
      cerr << hex << (int) magic[i] << ' ';
    cerr << "\n";
#endif
    if((((int) magic[0]) != 0) || (((int) magic[1]) != 0x6) || 
       (((int) magic[2]) != 0x9) || (((int) magic[3]) != ((int) 0xce))) {
      cerr << "DPImageJSBaseBodyC::ReadHeader(), Bad magic number. \n";
      return false;
    }
    
    UIntT header[11];
    
    int i;
    for(i = 0;i < 9;i++) {
      UIntT x = 0;
      SArray1dC<ByteT> xArray(reinterpret_cast<ByteT*>(&x), 4, false);
      if(!m_inputStream.GetArray(xArray))
	return false;
#if RAVL_ENDIAN_LITTLE
      x = bswap_32(x);
#endif
      header[i] = x;
    }
    
#if DODEBUG
    cerr << "Header :\n";
    for(i = 0;i < 9;i++) {
      cerr << " " << i << "=" << header[i];
    }
    cerr << "\n" << hex;
    for(i = 0;i < 9;i++) {
      cerr << " " << i << "=" << header[i];
    }
    cerr << dec << "\n";
#endif
    
    // 0 Typical 3
    // 1 Typical 3007 2989 ...
    // 2 16384, block size.
    // 3 Typical 1
    // 4 width
    // 5 height
    // 6 Typical 1008
    // 7 Typical 14656
    // 8 Typical 0xe0000000
    
    blockSize = header[2];
    int width = header[4];
    int height = header[5];
    
    
    rect = ImageRectangleC(height,width);
    SetupIO();
    ONDEBUG(cerr << " BlockSize=" << blockSize << " Width=" << width << " Height=" << height << " \n");
    
    StreamSizeT imageData = m_inputStream.Size() - offset;
    seqSize = (StreamSizeT) (imageData / (StreamSizeT) frameSize);
    
    // There maybe unwritten padding for the last block.
    UIntT imgSize = (rect.Area() * 2);
    if((imageData % frameSize) >= imgSize)
      seqSize++; 
    
    ONDEBUG(cerr << "DPIImageJSBodyC::ReadHeader(), Sequence size=" << seqSize << " Filesize=" << m_inputStream.Size() << "\n");
    
    return true;
  }

  //: Setup paramiters needed for io.
  
  void DPImageJSBaseBodyC::SetupIO() {
    UIntT imgSize = (rect.Area() * 2);
    
    // Fixme: The image size may be slightly larger, as it might contain out of frame info.
    
    framePadding = blockSize - (imgSize % blockSize);
    frameSize = imgSize + framePadding;
    
    offset = frameSize;
    ONDEBUG(cerr << "blockSize=" << blockSize << " imageSize=" << imgSize << " frameSize=" << frameSize << " framePadding=" << framePadding << " offset=" << offset << endl);
  }
  
  
  /////////////////////////////////////////////////////////
  

  ///////////////////////////
  //: Constructor from stream 

  DPIImageJSBodyC::DPIImageJSBodyC(const IStreamC &nStrm)
  { 
    RavlAssertMsg(0,"Not supported. ");
    //ReadHeader();
  }
  
  //: Constructor from a file.
  
  DPIImageJSBodyC::DPIImageJSBodyC(const StringC &fileName) 
  : DPImageJSBaseBodyC(fileName,true)
  { ReadHeader(); }



  DPIImageJSBodyC::DPIImageJSBodyC(DPISPortC<ByteT> inputPort)
  : DPImageJSBaseBodyC(inputPort)
  { ReadHeader(); }

  ///////////////////////////
  //: Seek to location in stream.
  // Returns false, if seek failed. (Maybe because its
  // not implemented.)
  // if an error occurered (Seek returned False) then stream
  // position will not be changed.
  
  bool DPIImageJSBodyC::Seek(UIntT off) {
    if(off == ((UIntT) -1))
      return false; // File to big.
    frameNo = off;// Wait to after seek in case of exception.
    return true;
  }
  
  //: Delta Seek, goto location relative to the current one.
  
  bool DPIImageJSBodyC::DSeek(IntT off) {
    if(off < 0) {
      if((-off) > (IntT) frameNo)
	return false; // Seek off begining of data.
    }
    frameNo = frameNo + off; // Wait till after seek in case of exception.
    return true;
  }
  
  //: Find current location in stream.
  UIntT DPIImageJSBodyC::Tell() const { 
    return frameNo; 
  }
  
  //: Find the total size of the stream.
  UIntT DPIImageJSBodyC::Size() const { 
    return SeqSize(); 
  }

  /////////////////////////
  //: Get next image.
  
  ImageC<ByteYUV422ValueC> DPIImageJSBodyC::Get() {
    ImageC<ByteYUV422ValueC> head;
    if(!Get(head))
      throw DataNotReadyC("Failed to get image. ");
    return head;
  }
  
  //////////////////////////
  //: Get next image.
  
  bool DPIImageJSBodyC::Get(ImageC<ByteYUV422ValueC> &head) {
    if (!m_inputStream.IsValid())
      return false;

    m_inputStream.Seek(CalcOffset(frameNo));
    
    // Check input image.
    
    if(head.Rectangle() != rect) {
      head = ImageC<ByteYUV422ValueC>(rect);
      SArray1dC<ByteT> imageArray(reinterpret_cast<ByteT*>(&(head[rect.Origin()])), rect.Area() * sizeof(ByteYUV422ValueC), false);
      if(m_inputStream.GetArray(imageArray) <= 0) // Zero indicates end of file.
        return false;
    } else {
      IntT width = head.Cols() * sizeof(ByteYUV422ValueC);
      IndexC atrow = head.TRow();
      IndexC offset = head.LCol();
      IndexC brow = head.BRow();
      for(;atrow <= brow;atrow++) {
        SArray1dC<ByteT> rowArray(reinterpret_cast<ByteT*>(&(head[atrow][offset])), width, false);
	      if(m_inputStream.GetArray(rowArray) <= 0) // Zero indicates end of file.
	        return false;
      }
    }
    //ONDEBUG(cerr << "Reading image... \n");
    frameNo++;
    return true; 
  }
  
  //////////////////////////////////////////////////////////////////////////////////////
  
  //: Constructor from stream.  
  
  DPOImageJSBodyC::DPOImageJSBodyC(const OStreamC &nStrm)
    :  doneHeader(false)
  {
    RavlAssertMsg(0,"Not supported. ");
    //if(!strm.Good())
    //cerr << "DPOImageJSBodyC::DPOImageJSBodyC(OStreamC), Passed bad stream. \n";
  }
  
  //: Constructor from stream 
  
  DPOImageJSBodyC::DPOImageJSBodyC(const StringC &fileName) 
    : DPImageJSBaseBodyC(fileName,false),
      doneHeader(false)
  {}



  DPOImageJSBodyC::DPOImageJSBodyC(DPOPortC<ByteT> outputPort)
  : DPImageJSBaseBodyC(outputPort),
    doneHeader(false)
  {}

  //: Write js header.
  
  bool DPOImageJSBodyC::WriteHeader(const ImageRectangleC &wrect) {
    RavlAssert(m_outputStream.IsValid());
    if(doneHeader)
      return true;
    rect = wrect;
    
    ByteT magic[4];
    magic[0] = 0;
    magic[1] = 0x6;
    magic[2] = 0x9;
    magic[3] = 0xce;
    SArray1dC<ByteT> magicArray(magic, 4, false);
    if(m_outputStream.PutArray(magicArray) != static_cast<IntT>(magicArray.Size()))
      return false;
    
    int datatype = 3,width = wrect.Cols(),height = wrect.Rows();
    
    UIntT header[11];
    
    header[0]= datatype;      // Typical 3.
    header[1]= ((int) 3007);  // Typical 3007 2989 ...
    header[2]= blockSize;     // 16384, offset of first frame.
    header[3]= ((int) 1);     // Typical 1
    header[4]= width;         // width.
    header[5]= height;        // height.
    header[6]= ((int) 1008);  // Typical 1008
    header[7]= ((int) 14656); // Typical 14656
    header[8]= ((UIntT) 0xe0000000); // Typical.
    
#if RAVL_ENDIAN_LITTLE
    for(int i = 0;i < 9;i++)
      header[i] = bswap_32(header[i]);
#endif
    SArray1dC<ByteT> headerArray(reinterpret_cast<ByteT*>(header), 9 * sizeof(UIntT), false);
    if(m_outputStream.PutArray(headerArray) != static_cast<IntT>(headerArray.Size()))
      return false;

    SetupIO();

    SArray1dC<ByteT> paddingArray(offset - 40);
    if(m_outputStream.PutArray(paddingArray) <= 0)
      return false;
    
    doneHeader = true;
    return true;
  }
  
  //: Seek to location in stream.
  // Returns false, if seek failed. (Maybe because its
  // not implemented.)
  // if an error occurered (Seek returned False) then stream
  // position will not be changed.
  
  bool DPOImageJSBodyC::Seek(UIntT off) {
    if(off == ((UIntT)-1))
      return false; 
    frameNo = off;// Wait to after seek in case of exception.
    return true;
  }
  
  //: Delta Seek, goto location relative to the current one.
  
  bool DPOImageJSBodyC::DSeek(IntT off) {
    if(off < 0) {
      if((-off) > ((IntT) frameNo))
	return false; // Seek off begining of data.
    }
    UIntT nfrmno = frameNo + off;
    frameNo = nfrmno; // Wait to after seek in case of exception.
    if(frameNo > seqSize)
      seqSize = frameNo;
    return true;
  }
  
  //: Find current location in stream.
  
  UIntT DPOImageJSBodyC::Tell() const { 
    return frameNo; 
  }

  //: Find the total size of the stream.
  
  UIntT DPOImageJSBodyC::Size() const { 
    return SeqSize(); 
  }

  /////////////////////////////////
  // Put next frame into stream.
  // Returns false if can't.
  
  bool DPOImageJSBodyC::Put(const ImageC<ByteYUV422ValueC> &img) {
    if (!m_outputStream.IsValid())
      return false;
    
    if(!doneHeader) {
      if(!WriteHeader(img.Rectangle())) {
        cerr << "DPOImageJSBodyC::Put(), ERROR: Failed to write file header. \n";
        return false;
      }
    }
    RavlAssert(img.Rectangle() == rect); // Expected image size ?
    if(&(img[rect.TRow()][rect.RCol()]) == (&(img[rect.TRow()+1][rect.LCol()]))+1) {
      const ByteT* imagePtr = reinterpret_cast<const ByteT*>(&(img[rect.Origin()]));
      SArray1dC<ByteT> imageArray(const_cast<ByteT*>(imagePtr), rect.Area() * sizeof(ByteYUV422ValueC), false);
      if(m_outputStream.PutArray(imageArray) <= 0)
        return false;
    } else {
      IntT width = img.Cols() * sizeof(ByteYUV422ValueC);
      IndexC atrow = img.TRow();
      IndexC offset = img.LCol();
      IndexC brow = img.BRow();
      for(;atrow <= brow;atrow++)
      {
        const ByteT* rowPtr = reinterpret_cast<const ByteT*>(&(img[atrow][offset]));
        SArray1dC<ByteT> rowArray(const_cast<ByteT*>(rowPtr), width, false);
      	if(m_outputStream.PutArray(rowArray) <= 0)
          return false;
      }
    }
    
    frameNo++;
    if(frameNo > seqSize)
      seqSize = frameNo;

    if (framePadding != 0)
    {
      SArray1dC<ByteT> paddingArray(framePadding);
      if(m_outputStream.PutArray(paddingArray) <= 0)
        return false;
    }

    return true;
  }
  
  
  
  //////////////////////////////////////////////////////
  
  //: Constructor from filename.  
  
  DPIImageJSC::DPIImageJSC(const StringC &fn)
    : DPEntityC(*new DPIImageJSBodyC(fn))
  {}

  //: Constructor from filename.  
  
  DPOImageJSC::DPOImageJSC(const StringC &fn)
    : DPEntityC(*new DPOImageJSBodyC(fn))
  {}
}
