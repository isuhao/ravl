// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_FUNCTION_HEADER
#define RAVL_FUNCTION_HEADER 1
///////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! author="Charles Galambos, based on code by Robert Crida"
//! docentry="Ravl.Pattern Recognition.Functions"

#include "Ravl/Vector.hh"
#include "Ravl/Matrix.hh"
#include "Ravl/RCHandleV.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Map an input vector to an output vector.
  
  class FunctionBodyC
    : public RCBodyVC
  {
  public:
    FunctionBodyC()
    {}
    //: Default constructor.
    
    FunctionBodyC(istream &strm);
    //: Load from stream.
    
    FunctionBodyC(BinIStreamC &strm);
    //: Load from binary stream.
    
    virtual VectorC Apply(const VectorC &data) const;
    //: Apply function to 'data'
    
    virtual MatrixC Jacobian (const VectorC &X) const;
    //: Calculate Jacobian matrix at X
    // Performs numerical estimation of the Jacobian using differences. This
    // function has and should be overloaded for all cases where the Jacobian
    // can be calculated analytically.
    
    inline UIntT InputSize() const
    { return inputSize; }
    //: Size of input vectors
    
    inline UIntT OutputSize() const
    { return outputSize; }
    //: Size of output vectors
    
    virtual bool Save (ostream &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual bool Save (BinOStreamC &out) const;
    //: Writes object to stream, can be loaded using constructor
    
  protected:
    inline void InputSize(UIntT inSize)
    { inputSize = inSize; }
    //: Set the input size.
    
    inline void OutputSize(UIntT outSize)
    { outputSize = outSize; }
    //: Set the output size.
    
    UIntT inputSize;  // (X in amma speak.)
    UIntT outputSize; // (Y in amma speak.)
  };
  
  //! userlevel=Develop
  //: Map an input vector to an output vector.
  
  class FunctionC
    : public RCHandleVC<FunctionBodyC>
  {
  public:
    FunctionC()
    {}
    //: Default constructor.
    // Creates an invalid handle.

  protected:
    FunctionC(FunctionBodyC &bod)
      : RCHandleVC<FunctionBodyC>(bod)
    {}
    //: Body constructor.
    
    FunctionBodyC &Body()
    { return RCHandleC<FunctionBodyC>::Body(); }
    //: Access body.
    
    const FunctionBodyC &Body() const
    { return RCHandleC<FunctionBodyC>::Body(); }
    //: Access body.
    
  public:
    VectorC Apply(const VectorC &data) const
    { return Body().Apply(data); }
    //: Apply function to 'data'
    
    VectorC operator() (const VectorC &X) const 
    { return Body().Apply(X); }
    //: Evaluate Y=f(X)
    
    MatrixC Jacobian(const VectorC &X) const
    { return Body().Jacobian(X); }    
    //: Calculate Jacobian matrix at X
    // Performs numerical estimation of the Jacobian using differences. This
    // function has and should be overloaded for all cases where the Jacobian
    // can be calculated analytically.
    
    inline UIntT InputSize() const
    { return Body().InputSize(); }
    //: Size of input vector
    
    inline UIntT OutputSize() const
    { return Body().OutputSize(); }
    //: Size of output vector
    
  };
}

#endif
