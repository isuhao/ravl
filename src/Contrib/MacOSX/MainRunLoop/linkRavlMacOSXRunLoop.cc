// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2005, Charles Galambos.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! lib=RavlMacOSXRunLoop

namespace RavlN {

  extern bool DoLinkMacOSXMainRunLoop();

  void LinkRavlMacOSXRunLoop() {
    DoLinkMacOSXMainRunLoop();
  }
}
