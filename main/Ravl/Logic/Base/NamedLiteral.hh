// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLLOGIC_NAMEDLITERAL_HEADER
#define RAVLLOGIC_NAMEDLITERAL_HEADER 1
/////////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Charles Galambos"
//! lib=RavlLogic

#include "Ravl/Logic/Literal.hh"

namespace RavlLogicN {
  
  //! userlevel=Develop
  //: Named literal body.
  
  class NamedLiteralBodyC 
    : public LiteralBodyC 
  {
  public:
    NamedLiteralBodyC()
    {}
    //: Default constructor.
    
    NamedLiteralBodyC(const StringC &nname)
      : name(nname)
    {}
    //: Constructor.
    
    virtual StringC Name() const;
    //: Get the name of symbol.
    
    virtual UIntT Hash() const;
    //: Get hash value for symbol.
    
    virtual bool IsEqual(const LiteralC &oth) const;
    //: Is this equial to another LiteralC ?
    
  protected:
    StringC name;
  };
  
  //! userlevel=Develop
  //: Named literal.
  // All literals with the same name are considered equivelent. 
  // Care should be taken not to use those names used for
  // unnamed literals, i.e. L:(number) or V:(number) as unpredictable
  // behavour will result.
  
  class NamedLiteralC 
    : public LiteralC 
  {
  public:
    NamedLiteralC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    NamedLiteralC(const StringC &name)
      : LiteralC(*new NamedLiteralBodyC(name))
    {}
    //: Constructor.
    
    NamedLiteralC(const LiteralC &oth)
      : LiteralC(oth)
    {
      if(dynamic_cast<NamedLiteralBodyC *>(&Body()) == 0)
	Invalidate();
    }
    //: Base class constructor.
    // if 'oth' isn't a named literal an invalid handle
    // will be created.
    
  };

}

#endif
