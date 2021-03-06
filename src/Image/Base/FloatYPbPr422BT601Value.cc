// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2008, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: ByteYUV422Value.cc 3700 2003-11-19 17:44:12Z craftit $"
//! lib=RavlImage
//! file="Ravl/Image/Base/ByteYPbPr422Value.cc"

#include "Ravl/BinStream.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/FloatYPbPr422BT601Value.hh"
#include "Ravl/TypeName.hh"

namespace RavlImageN {
  
  BinOStreamC &operator << (BinOStreamC &out,const ImageC<FloatYPbPr422BT601ValueC> &img)
  { 
    out << img.Rectangle();
    
    IntT width = img.Cols() * 2;
    IndexC atrow = img.TRow();
    IndexC offset = img.LCol();
    IndexC brow = img.BRow();
    for(;atrow <= brow;atrow++)
      out.OBuff((const char *) &(img[atrow][offset]),width);  
    return out;
  }
  
  BinIStreamC &operator >> (BinIStreamC &in,ImageC<FloatYPbPr422BT601ValueC> &img)
  { 
    ImageRectangleC rect;
    in >> rect;
    img = ImageC<FloatYPbPr422BT601ValueC>(rect);
    
    IntT width = img.Cols() * 2;
    IndexC atrow = img.TRow();
    IndexC offset = img.LCol();
    
    IndexC brow = img.BRow();
    for(;atrow <= brow;atrow++)
      in.IBuff((char *) &(img[atrow][offset]),width);
    return in;
  }
}
