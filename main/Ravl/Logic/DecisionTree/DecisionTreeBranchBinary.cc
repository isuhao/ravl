// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic

#include "Ravl/Logic/DecisionTreeBranchBinary.hh"
#include "Ravl/Logic/State.hh"

namespace RavlLogicN {

  DecisionTreeBranchBinaryBodyC::DecisionTreeBranchBinaryBodyC()
  {}

  //: Dump node in human readable form,
  
  void DecisionTreeBranchBinaryBodyC::Dump(ostream &out,IntT level) const {
    Pad(out,level) << test << "\n";
    Pad(out,level) << "true:\n";
    children[0].Dump(out,level+1);
    Pad(out,level) << "false:\n";
    children[1].Dump(out,level+1);
  }
  
  //: Find next level in the decision tree for given 'state'.
  
  DecisionTreeElementC DecisionTreeBranchBinaryBodyC::Find(const StateC &state) {
    return children[state.Ask(test)];
  }
  
}
