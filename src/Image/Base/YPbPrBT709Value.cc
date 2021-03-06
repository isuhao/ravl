// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2008-12, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! lib=RavlImage

#include "Ravl/Image/YPbPrBT709Value.hh"
#include "Ravl/Image/RGBValue.hh"

namespace RavlImageN {
  
  // Convert a pixel type from RGB to YPbPrBT709
  
  void RGBFloat2YPbPrBT709Float(const RGBValueC<float> &value,YPbPrBT709ValueC<float> &outValue) {
    outValue.Set( + 0.21259    * value.Red() + 0.71521    * value.Green() + 0.07220    * value.Blue(),
                  - 0.11719 * value.Red() - 0.39423 * value.Green() + 0.51141      * value.Blue(),
                  + 0.51141      * value.Red() - 0.46454 * value.Green() - 0.04688 * value.Blue());
  }
  
  // Convert a pixel type from YPbPrBT709 to RGB
  
  void YPbPrBT709Float2RGBFloat(const YPbPrBT709ValueC<float> &value,RGBValueC<float> &outValue) {
    outValue.Set(value.Y() + 0.00000 * value.Pb() + 1.53967    * value.Pr(),
                 value.Y() - 0.18317    * value.Pb() - 0.45764    * value.Pr(),
                 value.Y() + 1.81421     * value.Pb() + 0.00000 * value.Pr());
  }
  
     
}
