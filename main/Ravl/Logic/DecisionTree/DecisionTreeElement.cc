// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic

#include "Ravl/Logic/DecisionTreeElement.hh"

namespace RavlLogicN {
  
  //: Constructor.
  
  DecisionTreeElementBodyC::DecisionTreeElementBodyC()
    : examples(true)
  {}
  
  //: Constructor.
  
  DecisionTreeElementBodyC::DecisionTreeElementBodyC(const DecisionExamplesC &nexamples) 
    : examples(nexamples)
  {}
  
  //: Find next level in the decision tree for given 'state'.
  
  DecisionTreeElementC DecisionTreeElementBodyC::Find(const StateC &state) {
    RavlAssertMsg(0,"DecisionTreeElementBodyC::Find(), Abstract method called. ");
    return DecisionTreeElementC();
  }

  //: Pad line to given level.
  // Used in dump.
  
  ostream &DecisionTreeElementBodyC::Pad(ostream &out,int level) {
    for(int i = 0;i < level;i++)
      out << "  ";
    return out;
  }

  //: Go through the tree building a rule set.
  
  void DecisionTreeElementBodyC::BuildRuleSet(const LiteralC &preCond,StateC &ruleSet) const {    
    RavlAssertMsg(0,"DecisionTreeElementBodyC::BuildRuleSet(), Abstract method called. ");
  }
  
  //: Dump node in human readable form,
  
  void DecisionTreeElementBodyC::Dump(ostream &out,IntT level) const {
    cerr << "DecisionTreeElementBodyC::Dump(), Abstract method called \n";
  }
  

}
