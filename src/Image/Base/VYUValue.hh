// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_VYUVALUE_HEADER
#define RAVL_VYUVALUE_HEADER 1
////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Image/Base/VYUValue.hh"
//! lib=RavlImage
//! userlevel=Normal
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.API.Images.Pixel Types.YUV"

#include "Ravl/TFVector.hh"
#include "Ravl/Traits.hh"

namespace RavlImageN {
  using namespace RavlN;
#if RAVL_VISUALCPP_NAMESPACE_BUG
  using RavlN::BinIStreamC;
  using RavlN::BinOStreamC;
  using RavlN::TFVectorC;
#endif
  
  //! userlevel=Normal
  //: VYU Pixel base class.
  
  template<class CompT>
  class VYUValueC 
    : public TFVectorC<CompT,3>
  {
  public:
    VYUValueC()
    {}
    //: Default constructor.
    // Creates an undefined value.

    VYUValueC(const CompT &v,const CompT &y,const CompT &u) {
      this->data[0] = v;
      this->data[1] = y;
      this->data[2] = u;
    }
    //: Construct from component values.
    
    VYUValueC(const TFVectorC<CompT,3> &v)
      : TFVectorC<CompT,3>(v)
    {}
    //: Constructor from base class.
    
    template<class OCompT>
    VYUValueC(VYUValueC<OCompT> &oth) {
      this->data[0] = oth.V();
      this->data[1] = oth.Y();
      this->data[2] = oth.U();
    }
    //: Construct from another component type.

    void Set(const CompT &v,const CompT &y,const CompT &u) {
      this->data[0] =v;
      this->data[1] =y;
      this->data[2] =u;
    }
    //: Set the values.
    
    inline const CompT & V() const
    { return this->data[0]; }
    //: Returns the level of the V component.
    
    inline const CompT & Y() const
    { return this->data[1]; }
    //: Returns the level of the Y component.
    
    inline const CompT & U() const
    { return this->data[2]; }
    //: Returns the level of the U component.
    
    inline CompT & V()
    { return this->data[0]; }
    //: Returns the level of the V component.
    
    inline CompT & Y() 
    { return this->data[1]; }
    //: Returns the level of the Y component.
    
    inline CompT & U()
    { return this->data[2]; }
    //: Returns the level of the U component.
    
  };

  template<class CompT>
  inline
  std::istream &operator>>(std::istream &strm,VYUValueC<CompT> &val) 
  { return strm >> ((TFVectorC<CompT,3> &)(val)); }
  //: Stream input.
  
  template<class CompT>
  inline
  std::ostream &operator<<(std::ostream &strm,const VYUValueC<CompT> &val) 
  { return strm << ((const TFVectorC<CompT,3> &)(val)); }
  //: Stream output.
  
  template<class CompT>
  inline
  BinIStreamC &operator>>(BinIStreamC &strm,VYUValueC<CompT> &val) 
  { return strm >> ((TFVectorC<CompT,3> &)(val)); }
  //: Binary stream input.
  
  template<class CompT>
  inline
  BinOStreamC &operator<<(BinOStreamC &strm,const VYUValueC<CompT> &val) 
  { return strm << ((const TFVectorC<CompT,3> &)(val)); }
  //: Binary stream output

}

namespace RavlN {
  
  //! userlevel=Advanced
  //: Traits for type
  
  template<typename PixelT>
  struct NumericalTraitsC<RavlImageN::VYUValueC<PixelT> > {
    typedef RavlImageN::VYUValueC<typename NumericalTraitsC<PixelT>::AccumT > AccumT;    //: Type to use for accumulator, guarantee's at least 2x no bits for interger types.
    typedef RavlImageN::VYUValueC<typename NumericalTraitsC<PixelT>::RealAccumT > RealAccumT; //: Type to use for a floating point accumulator.
    typedef RavlImageN::VYUValueC<typename NumericalTraitsC<PixelT>::LongAccumT > LongAccumT; //: Type to use for accumulators that can take large sums.(10000's of elements at least.)
  };
}


#endif
