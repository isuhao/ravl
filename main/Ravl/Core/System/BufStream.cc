// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/System/BufStream.cc"

#include "Ravl/BufStream.hh"

#if RAVL_HAVE_ANSICPPHEADERS
#if USE_GCC30
#include <sstream>
#else
#include <strstream>
#endif
#else
#ifndef VISUAL_CPP
#include <strstream.h>
#else
#include <strstrea.h>
#endif
#endif

namespace RavlN {

#if USE_GCC3

  class BufferStringBodyC 
    : public BufferBodyC<char>
  {
  public:
    BufferStringBodyC(string &nstr,UIntT size)
      : BufferBodyC<char>(size,(char *) nstr.data()),
	str(nstr)
    {}
    //: Constructor.
    
  protected:
    string str;
  };

  class BufferStringC 
    : public BufferC<char> 
  {
  public:
    BufferStringC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    BufferStringC(string &str,UIntT size)
      : BufferC<char>(*new BufferStringBodyC(str,size))
    {}
    //: Constructor.
  };
    
#endif
  ///////////////////
  //: Default constructor.
  
  BufOStreamC::BufOStreamC()
    : 
#if !USE_GCC3
    OStreamC(*(oss = new ostrstream()),true)
#else
    OStreamC(*(oss = new ostringstream()),true)
#endif
  {}
  
  ///////////////////
  //: Get text written to stream so far.
  // NB. This does NOT clean the buffer.
  
  SArray1dC<char> &BufOStreamC::Data() {
#if USE_GCC3
#if 0
    data = SArray1dC<char>((char *) oss->str().data(),oss->str().size());
#else
    string astr(oss->str());
    SizeT size = oss->str().size();
    BufferStringC buf(astr,size);
    data = SArray1dC<char>(buf,size);
#endif
#else
    data = SArray1dC<char>((char *) oss->str(),oss->pcount());
#endif
    return data;
  }
  
  ////////////////////////////////////////////////////
  
  //: Default constructor.
  
  BufIStreamC::BufIStreamC(const SArray1dC<char> &dat) 
    :
#ifdef VISUAL_CPP
    IStreamC(*(iss = new istrstream(const_cast<char *>(dat.ReferenceElm()),dat.Size())),true),
#else
#if !USE_GCC3
    IStreamC(*(iss = new istrstream(dat.ReferenceElm(),dat.Size())),true),
#else
    IStreamC(*(iss = new istringstream(string(dat.ReferenceElm(),dat.Size()))),true),
#endif
#endif
      data(dat)
  {}
}
