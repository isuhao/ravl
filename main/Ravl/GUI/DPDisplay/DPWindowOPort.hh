// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUI_DPWINDOWOPORT_HEADER
#define RAVLGUI_DPWINDOWOPORT_HEADER 1
/////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUIDisplay

#include "Ravl/GUI/DPWindow.hh"

namespace RavlGUIN {

  //! userlevel=Develop
  //: Window OPort body.
  
  class DPWindowOPortBodyC
    : public DPOPortBodyC<DPDisplayObjC>
  {
  public:
    DPWindowOPortBodyC(DPWindowC &win,bool accum = false);
    //: Constructor.
    
    virtual bool Put(const DPDisplayObjC &newObj);
    //: Process in coming display objects.
    
  protected:
    bool accumulate;
    DPWindowC win;
  };

  //! userlevel=Normal
  //: Window OPort.
  
  class DPWindowOPortC
    : public DPOPortC<DPDisplayObjC>
  {
  public:
    DPWindowOPortC(DPWindowC &win,bool accum = false)
      : DPEntityC(*new DPWindowOPortBodyC(win,accum))
    {}
    //: Constructor.
    
    DPWindowOPortC()
      : DPEntityC(true)
    {}
    //: Default constructor.
    // creates an invalid handle.
  };
  
  
}

#endif
