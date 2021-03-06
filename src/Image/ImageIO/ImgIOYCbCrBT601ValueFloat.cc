// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////
//! author="Charles Galambos"
//! rcsid="$Id: ImgIOByteYUV.cc 3700 2003-11-19 17:44:12Z craftit $"
//! lib=RavlImageIO
//! file="Ravl/Image/ImageIO/ImgIOByteYUV.cc"

#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"
#include "Ravl/DP/Converter.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/YCbCrBT601Value.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/TypeName.hh"

namespace RavlImageN {
  
  void InitImgIOYCbCrBT601ValueFloat() {
  }
  
  static TypeNameC type3(typeid(ImageC<YCbCrBT601ValueC<float> >),"RavlImageN::ImageC<YCbCrBT601ValueC<float>>");
  
  static FileFormatStreamC<ImageC<YCbCrBT601ValueC<float> > > FileFormatStream_ImageC_YCbCrBT601ValueC_float;
  static FileFormatBinStreamC<ImageC<YCbCrBT601ValueC<float> > > FileFormatBinStream_ImageC_YCbCrBT601ValueC_float;
  
}

