// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLLOGICLIST_HEADER
#define RAVLLOGICLIST_HEADER 1
/////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Logic"
//! lib=RavlLogic

#include "Ravl/Logic/Literal.hh"
#include "Ravl/DList.hh"

namespace RavlLogicN {
  
  //! userlevel=Develop
  //: Logical List.
  
  class LListBodyC
    : public LiteralBodyC
  {
  public:
    LListBodyC()
    {}
    //: Default constructor.
    
    DListC<LiteralC> &List()
    { return lst; }
    //: Access list.
    
    virtual bool Unify(const LiteralC &oth,BindSetC &bs) const;
    //: Unify with another variable.
    
  protected:
    virtual bool UnifyLiteral(const LiteralBodyC &oth,BindSetC &bs) const;
    //: Unify with simple symb.
    
    DListC<LiteralC> lst;
  };
  
  //! userlevel=Normal
  //: Logical List.
  
  class LListC
    : public LiteralC 
  {
  public:
    LListC()
    {}
    //: Default constructor.
    // Creates invalid handle.
    
    LListC(bool)
      : LiteralC(*new LListBodyC())
    {}
    //: Constructor.
    
  protected:
    LListBodyC &Body()
    { return static_cast<LListBodyC &>(LiteralC::Body()); }
    //: Body access.
    
    const LListBodyC &Body() const
    { return static_cast<const LListBodyC &>(LiteralC::Body()); }
    //: Body access.

  public:
    DListC<LiteralC> &List()
    { return Body().List(); }
    //: Access list.
  };
}


#endif
