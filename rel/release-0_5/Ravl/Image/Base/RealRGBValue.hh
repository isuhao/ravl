// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_REALRGBVALUE_HEADER
#define RAVL_REALRGBVALUE_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Image/Base/RealRGBValue.hh"
//! lib=RavlImage
//! userlevel=Normal
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Images.Pixel Types"

#include "Ravl/Image/RGBValue.hh"

namespace RavlImageN {
  
  class RealYUVValueC;
  
  //: Real RGB value class.
  
  class RealRGBValueC
    : public RGBValueC<RealT>
  {
  public:
    RealRGBValueC()
      {}
    //: Default constructor.
    // creates an undefined RGB pixel.

    inline RealRGBValueC(const RealYUVValueC &);
    //: Convert from a YUV pixel.
    // Implementation in Ravl/Image/RGBcYUV.hh include
    // this header when needed.
    
    RealRGBValueC(RealT r,RealT g, RealT b)
      : RGBValueC<RealT>(r,g,b)
      {}
    //: Construct from components.
    
    RealRGBValueC(const RGBValueC<RealT> &oth)
      : RGBValueC<RealT>(oth)
      {}
    //: Default constructor.
    // creates an undefined RGB pixel.
    
  };

}

#endif