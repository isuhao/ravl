// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic

#include "Ravl/Logic/Literal.hh"
#include "Ravl/Logic/LiteralIter.hh"
#include "Ravl/Logic/State.hh"
#include "Ravl/Assert.hh"
#include <iostream.h>

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlLogicN {

  //: Helper function for producing debug output.
  // create a string with 'level' spaces.
  StringC Indent(int level) {
    StringC ret;
    for(;level > 0;level--)
      ret += ' ';
    return ret;
  }
  
  // Unify with another variable.
  
  bool LiteralBodyC::Unify(const LiteralC &oth,BindSetC &bs) const {
    RavlAssert(oth.IsValid());
    if(&oth.Body() == this)
      return true;
    return oth.Body().UnifyLiteral(*this,bs);
  }
  
  bool LiteralBodyC::UnifyLiteral(const LiteralBodyC &oth,BindSetC &bs) const {
    return false;
  }

  //: Dump info in human readable format to stream 'out'.
  
  void LiteralBodyC::Dump(ostream &out) {
    out << "L:" << ((void *) this);
  }
  
  //: Is this equial to another LiteralC ?
  
  bool LiteralBodyC::IsEqual(const LiteralC &oth) const 
  { return this == &oth.Body(); }

  //: Generate a unique name.
  
  StringC LiteralBodyC::Name() const
  { return StringC("L:") + StringC((UIntT) this); }
  
  //: Test if condition is true in 'state'.
  
  bool LiteralBodyC::Test(const StateC &state,BindSetC &binds) const {
    LiteralC me(const_cast<LiteralBodyC &>(*this));
    return state.Ask(me);
  }

  //: Return iterator through possibile matches to this literal in 'state', if any.
  
  LiteralIterC LiteralBodyC::Solutions(const StateC &state,BindSetC &binds) const {
    LiteralC me(const_cast<LiteralBodyC &>(*this));
    return state.ListFilter(me,binds);
  }
  
  ////////////////////////////////////////////////////////////////
  
  //: Return iterator through possibile solutions, if any.
  
  LiteralIterC LiteralC::Solutions(const StateC &state,BindSetC &binds) const
   { return Body().Solutions(state,binds); }


}
