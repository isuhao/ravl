// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_DILATE_HEADER
#define RAVLIMAGE_DILATE_HEADER 1
//! rcsid="$Id$"
//! lib=RavlImage
//! author="Joel Mitchelson"
//! userlevel=Normal
//! docentry="Ravl.Images.Morphology"
//! file="Ravl/Image/Processing/Morphology/Dilate.hh"

#include "Ravl/Image/Image.hh"
#include "Ravl/Image/Rectangle2dIter.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Array2dIter.hh"

namespace RavlImageN
{
  template<class DataT> 
  void BinaryDilate(const ImageC<DataT>& image, const ImageC<DataT>& kernel,ImageC<DataT>& result,DataT inRegion = 1)
  {
    ImageRectangleC resRect(image.Rectangle());
    resRect.TRow() -= kernel.Rectangle().TRow();
    resRect.BRow() -= kernel.Rectangle().BRow();
    resRect.LCol() -= kernel.Rectangle().LCol();
    resRect.RCol() -= kernel.Rectangle().RCol();
    RavlAssertMsg(resRect.Area() > 0,"Dilate, ERROR: Rectangle too small.");
    if(!result.Rectangle().Contains(resRect)) // Check the result rectangle is large enough.
      result = ImageC<DataT>(resRect); // If its not make another.
    
    Array2dIterC<DataT> res(result,resRect);
    for(Rectangle2dIterC rit(image.Frame(),kernel.Frame());rit;rit++,res++) {
      *res = 0;
      for(Array2dIter2C<DataT,DataT> it(kernel,Array2dC<DataT>(image,rit.Window()));it;it++) {
	if(it.Data1() && it.Data2()) {
	  *res = inRegion;
	  break;
	}
      }
    }
  }
  //: Binary dilation
  // This code does not deal with boundry conditions. It will write the output into the appropriate
  // place in 'results', if results is doesn't contain the appropriate range of pixels it will be
  // reallocated.
  
}

#endif
