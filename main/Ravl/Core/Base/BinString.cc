// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/Base/BinString.cc"

#include "Ravl/String.hh"
#include "Ravl/BinStream.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  BinOStreamC &operator << (BinOStreamC &out,const StringC &str) {
#if RAVL_CHECK
    if(!out.Stream()) {
      cerr << "BinOStreamC &operator<<(BinOStreamC &,StringC &), ERROR: Bad output stream. ";
      return out;
    }
#endif
    out << ((UIntT) str.length());
    ONDEBUG(cerr << "operator<<(BinOStreamC &,StringC &), Writting string of " << str.length() << " bytes. \n");
    out.OBuff(str.chars(),str.length());
    return out;
  }
  
  BinOStreamC &operator << (BinOStreamC &out,const SubStringC &str) {
#if RAVL_CHECK
    if(!out.Stream()) {
      cerr << "BinOStreamC &operator<<(BinOStreamC &,SubStringC &), ERROR: Bad output stream. ";
      return out;
    }
#endif
    out << ((UIntT) str.length());
    ONDEBUG(cerr << "operator<<(BinOStreamC &,StringC &), Writting string of " << str.length() << " bytes. \n");
    out.OBuff(str.chars(),str.length());
    return out;
  }
  
  BinIStreamC &operator >> (BinIStreamC &in,StringC &str) {
#if RAVL_CHECK
    if(!in.Stream()) {
      cerr << "BinIStreamC &operator>>(BinIStreamC &,StringC &), ERROR: Bad input stream. ";
      return in;
    }
#endif
    UIntT len;
    in >> len;
    ONDEBUG(cerr << "operator>>(BinIStreamC &,StringC &), Reading string of " << len << " bytes. (Hex:" << hex << len << dec <<")\n");
    if(!in.Stream()) {
      str = StringC();
      if(len > 0)
	cerr << "BinIStreamC &operator>>(BinIStreamC &,StringC &), WARNING: Stream terminated early. ";
      return in;
    }
    if(len == 0) {
      str = StringC();
      return in;
    }
    //assert(len << 1000000); // More than a megabyte ??
    str = StringC("",0,len+2);
    char *buff = str.rep->s;
    in.IBuff(buff,len);
    buff[len] =0;
    str.rep->len = len;
    return in;
  }
}
