// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_RANDOMVARIABLECONTINUOUS_HEADER
#define RAVLPROB_RANDOMVARIABLECONTINUOUS_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"

#include "Omni/Prob/RandomVariable.hh"
#include "Ravl/RealRange1d.hh"

namespace RavlProbN {
  using namespace RavlN;

  //! userlevel=Develop
  //: Implementation of a continuous random variable
  class RandomVariableContinuousBodyC
    : public RandomVariableBodyC {
  public:
    RandomVariableContinuousBodyC(const StringC& name, const RealRangeC& interval);
    //: Constructor
    //!param: name - convention is that it starts with a Capital letter, eg Face
    //!param: interval - the interval of value values for the variable

    RandomVariableContinuousBodyC(istream &in);
    //: Construct from stream
    //!param: in - standard input stream

    RandomVariableContinuousBodyC(BinIStreamC &in);
    //: Construct from binary stream
    //!param: in - binary input stream
    
    virtual bool Save (ostream &out) const;
    //: Writes object to stream, can be loaded using stream constructor
    //!param: out - standard output stream
    //!return: true if the object was successfully saved

    virtual bool Save (BinOStreamC &out) const;
    //: Writes object to stream, can be loaded using binary stream constructor
    //!param: out - binary output stream
    //!return: true if the object was successfully saved
    
    virtual ~RandomVariableContinuousBodyC();
    //: Destructor
    
    virtual StringC ToString() const;
    //: Get a string representation of the values that the variable can take

    const RealRangeC& Interval() const;
    //: Get access to the interval of legal values

  private:
    void SetInterval(const RealRangeC& interval);
    //: Interval of values that this variable can take

  private:
    RealRangeC m_interval;
    //: Interval of values that this variable can take
  };

  //! userlevel=Normal
  //: Implementation of a continuous random variable
  //!cwiz:author
  
  class RandomVariableContinuousC
    : public RandomVariableC
  {
  public:
    RandomVariableContinuousC()
    {}
    //: Default constructor makes invalid handle

    RandomVariableContinuousC(const StringC& name, const RealRangeC& interval)
      : RandomVariableC(new RandomVariableContinuousBodyC(name, interval))
    {}
    //: Constructor
    //!param: name - convention is that it starts with a Capital letter, eg Face
    //!param: interval - the interval of value values for the variable

    RandomVariableContinuousC(istream &in);
    //: Construct from stream
    //!param: in - standard input stream
    
    RandomVariableContinuousC(BinIStreamC &in);
    //: Construct from binary stream
    //!param: in - binary input stream
    
    RandomVariableContinuousC(const RandomVariableC& variable)
      : RandomVariableC(dynamic_cast<const RandomVariableContinuousBodyC *>(BodyPtr(variable)))
    {}
    //: Upcast constructor
    // Creates an invalid handle if types don't match
    
    const RealRangeC& Interval() const
    { return Body().Interval(); }
    //: Get access to the interval of legal values

  protected:
    RandomVariableContinuousC(RandomVariableContinuousBodyC &bod)
     : RandomVariableC(bod)
    {}
    //: Body constructor. 
    
    RandomVariableContinuousC(const RandomVariableContinuousBodyC *bod)
     : RandomVariableC(bod)
    {}
    //: Body constructor. 
    
    RandomVariableContinuousBodyC& Body()
    { return static_cast<RandomVariableContinuousBodyC &>(RandomVariableC::Body()); }
    //: Body Access. 
    
    const RandomVariableContinuousBodyC& Body() const
    { return static_cast<const RandomVariableContinuousBodyC &>(RandomVariableC::Body()); }
    //: Body Access. 
    
  };

}

#endif
