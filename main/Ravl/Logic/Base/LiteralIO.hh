// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLLOGIC_LITERALIO_HEADER
#define RAVLLOGIC_LITERALIO_HEADER 1
//! rcsid="$Id$"
//! lib=RavlLogic
//! docentry="Ravl.Logic"

#include "Ravl/Logic/Literal.hh"
#include "Ravl/Exception.hh"

namespace RavlLogicN {
  
  bool LoadState(IStreamC &is,StateC &state);
  //: Load data into stream.
  
  bool LoadState(const StringC &filename,StateC &state);
  //: Load data from a file into a state.
  
  bool SaveState(OStreamC &os,StateC &state);
  //: Save data into stream.
  
  bool SaveState(const StringC &filename,StateC &state);
  //: Save data to file from state.

}

#endif
