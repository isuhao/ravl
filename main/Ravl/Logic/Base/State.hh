// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLLOGICSTATE_HEADER
#define RAVLLOGICSTATE_HEADER 1
////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic

#include "Ravl/Logic/Literal.hh"
#include "Ravl/Logic/MinTerm.hh"
#include "Ravl/Logic/LiteralIter.hh"

namespace RavlLogicN {
  
  class BindSetC;
  
  //! userlevel=Develop
  //: Abstract state description.
  
  class StateBodyC
    : public RCBodyVC
  {
  public:
    StateBodyC()
    {}
    //: Default constructor.
    
    virtual RCBodyVC &Copy() const;
    //: Make a copy of this state.
    
    virtual bool Ask(const LiteralC &lit) const;
    //: Ask if a literal is set.

    virtual bool Ask(const LiteralC &lit,BindSetC &binds) const;
    //: Ask if a literal is set.
    
    virtual bool Tell(const LiteralC &lit);
    //: Set a literal.
    
    virtual LiteralIterC List() const;
    //: List contents of state.
    
    virtual LiteralIterC ListFilter(const LiteralC &it,BindSetC &bnds) const;
    //: Search state for matching literals.
    
    virtual MinTermC Difference(const StateC &oth) const;
    //: List the differences between this and another state.
    // Positive terms are ones in this state, but not in 'oth'. <p>
    // Negative terms are those in the 'oth' state but not in this one.
    
    virtual UIntT Size() const;
    //: Return the number of literals in the state.
  };
  
  //! userlevel=Normal
  //: Abstract state description.
  
  class StateC 
    : public RCHandleC<StateBodyC>
  {
  public:
    StateC()
      {}
    //: Default constructor
    // creates an invalid handle.
    
  protected:
    StateC(StateBodyC &bod)
      : RCHandleC<StateBodyC>(bod)
    {}
    //: Body constructor.
    
    StateBodyC &Body()
    { return RCHandleC<StateBodyC>::Body(); }
    //: Access body.
    
    const StateBodyC &Body() const
    { return RCHandleC<StateBodyC>::Body(); }
    //: Access body.

  public:
    
    StateC Copy() const
      { return StateC(static_cast<StateBodyC &>(Body().Copy())); }
    //: Make a copy of this state.
    
    bool Ask(const LiteralC &lit) const
    { return Body().Ask(lit); }
    //: Ask if a literal is set.
    
    bool Ask(const LiteralC &lit,BindSetC &binds) const
    { return Body().Ask(lit,binds); }
    //: Ask if a literal is set.
    
    bool Tell(const LiteralC &lit)
    { return Body().Tell(lit); }
    //: Set a literal.
    
    LiteralIterC List() const
    { return Body().List(); }
    //: List contents of state.
    
    LiteralIterC ListFilter(const LiteralC &it,BindSetC &bnds) const
      { return Body().ListFilter(it,bnds); }
    //: Search state for matching literals.
    
    MinTermC Difference(const StateC &oth) const
    { return Body().Difference(oth); }
    //: List the differences between this and another state.
    // Positive terms are ones in this state, but not in 'oth'. <p>
    // Negative terms are those in the 'oth' state but not in this one.

    UIntT Size() const
      { return Body().Size(); }
    //: Return the number of literals in the state.
    
  };


  ostream &operator<<(ostream &out,const StateC &state);
  //: Write out to stream.
  
  istream &operator>>(istream &out,StateC &stae);
  //: Read in from stream.
}

#endif
