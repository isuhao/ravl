// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlMPEG
//! file="Ravl/Image/ExternalImageIO/MpegFormat.cc"

#include "Ravl/Image/MPEGIFormat.hh"
#include "Ravl/Image/ImgIMPEG.hh"
#include <ctype.h>

#define USE_MPEGWRITE 0

#define DPDEBUG 0
#if DPDEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlImageN {
  
  void InitMPEGIFormat()
  {}
  
  // MPEG ////////////////////////////////////////////////////////////////
  
  //: Constructor.
  
  FileFormatMPEGBodyC::FileFormatMPEGBodyC(const StringC &id,const StringC &desc)
    : FileFormatBodyC(id,desc)
  {}
  
  //: Try and choose best format for IO.
  
  const std::type_info &FileFormatMPEGBodyC::ChooseFormat(const std::type_info &obj_type) const  {
    return typeid(ImageC<ByteRGBAValueC>);   
  }
  
  //: Is stream in std stream format ?
  
  const std::type_info &
  FileFormatMPEGBodyC::ProbeLoad(IStreamC &in,const std::type_info &obj_type) const {
    ONDEBUG(std::cerr << "FileFormatMPEGBodyC::ProbeLoad(IStreamC &,...), called. \n");
    if(!in.good())
      return typeid(void);
    ByteT buff[9];
    in.read((char*)buff,4);
    in.Unget((char *)buff,4);
    ONDEBUG(std::cerr << "FileFormatMPEGBodyC::ProbeLoad(), 0= " << hex << ((UIntT) buff[0])  << " " << ((UIntT) buff[1]) << " " << ((UIntT) buff[2])  << " " << ((UIntT) buff[3]) << dec << " \n");
    
    if((((UIntT) buff[0]) == 0) && (((UIntT) buff[1]) == 0)) {
      if(((UIntT) buff[2]) == 0x01 && ((UIntT) buff[3]) == 0xb3 )
	return typeid(ImageC<ByteRGBAValueC>);
    }
    
    ONDEBUG(std::cerr << "FileFormatMPEGBodyC::ProbeLoad(), Not a MPEG. \n");
    return typeid(void); 
  }
  
  const std::type_info &
  FileFormatMPEGBodyC::ProbeLoad(const StringC &nfilename,IStreamC &in,const std::type_info &obj_type) const {
    const std::type_info &pref = ProbeLoad(in,obj_type);
    ONDEBUG(std::cerr << "FileFormatMPEGBodyC::ProbeLoad(), Req:" <<obj_type.name() << "  Ret:" << pref.name() << " \n");
    return  pref;
  }
  
  const std::type_info &
  FileFormatMPEGBodyC::ProbeSave(const StringC &filename,const std::type_info &obj_type,bool forceFormat ) const {
#if USE_MPEGWRITE
    if(!forceFormat) {
      if(Extension(filename) != "mpg" && filename != "-")
	return typeid(void);
    }
    const std::type_info &pref = ChooseFormat(obj_type);
    ONDEBUG(std::cerr << "FileFormatMPEGBodyC::ProbeSave(), Req:" << obj_type.name() << "  Ret:" << pref.name() << " \n");
    return pref;
#else
    return typeid(void);   
#endif
  }
  
  //: Create a input port for loading from file 'filename'.
  // Will create an Invalid port if not supported. <p>
  DPIPortBaseC FileFormatMPEGBodyC::CreateInput(const StringC &fn,const std::type_info &obj_type) const {
    return DPIImageMPEGByteRGBC(fn);
  }
  
  //: Create a output port for saving to file 'filename'..
  // Will create an Invalid port if not supported. <p>
  
  DPOPortBaseC FileFormatMPEGBodyC::CreateOutput(const StringC &fn,const std::type_info &obj_type) const {
#if USE_MPEGWRITE
    return DPOImageMPEGByteRGBC(fn);
#else
    return DPOPortBaseC();  
#endif
  }
  
  //: Create a input port for loading.
  // Will create an Invalid port if not supported.
  
  DPIPortBaseC FileFormatMPEGBodyC::CreateInput(IStreamC &in,const std::type_info &obj_type) const { 
    return DPIImageMPEGByteRGBC(in); 
  }
  
  //: Create a output port for saving.
  // Will create an Invalid port if not supported.
  
  DPOPortBaseC FileFormatMPEGBodyC::CreateOutput(OStreamC &out,const std::type_info &obj_type) const  {
#if USE_MPEGWRITE
    return DPOImageMPEGByteRGBC(out);
#else
    return DPOPortBaseC();  
#endif
  }
  
  //: Get prefered IO type.
  
  const std::type_info &FileFormatMPEGBodyC::DefaultType() const  { 
    return typeid(ImageC<ByteRGBAValueC>); 
  }

#if USE_MPEGWRITE
  FileFormatMPEGC RegisterFileFormatMPEG("mpeg","Mpeg file input. ");
#else
  FileFormatMPEGC RegisterFileFormatMPEG("mpeg","Mpeg file IO. (only reading supported)");
#endif
  
}
