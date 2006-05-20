// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUIONECHILD_HEADER 
#define RAVLGUIONECHILD_HEADER 1
/////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI
//! docentry="Ravl.GUI.Internal"
//! author="Charles Galambos"
//! file="Ravl/GUI/GTK/OneChild.hh"
//! date="08/04/99"

#include "Ravl/GUI/Widget.hh"

namespace RavlGUIN {

  //! userlevel=Develop
  //: Base class for all widgets with exactly one child.
  // This is an abstract class.
  
  class OneChildBodyC 
    : public WidgetBodyC
  {
  public:
    OneChildBodyC(const WidgetC &widge);
    //: Constructor.
    
    OneChildBodyC()
      {}
    //: Constructor.
    
    virtual bool Create();
    //: Create the widget.
    
    const WidgetC &Child() const { return child; }
    //: Access window contents;
    
    WidgetC &Child() { return child; }
    //: Access window contents;
    
    bool Add(const WidgetC &nchild);
    //: Add widget.
    
  protected:
    virtual void Destroy();
    //: Undo all refrences.
    // Used to avoid problems with circluar refrences.
    // This should undo all refrences to RAVL and GUI
    // objects which are not in the destroy tree. 
    // The function is called by the root window in its
    // destructor.
    
    WidgetC child;
  };
  
  //! userlevel=Normal
  //: Base class for all widgets with exactly one child.
  // This is an abstract class.
  
  class OneChildC
    : public WidgetC
  {
  public:
    OneChildC()
      {}
    //: Default constructor.
    // Creates an invalid handle.

  protected:
    OneChildC(OneChildBodyC &bod)
      : WidgetC(bod)
      {}
    //: Body constructor

    OneChildC(WidgetC &bod)
      : WidgetC(bod)
      {
	if(dynamic_cast<WidgetBodyC *>(&WidgetC::Body()) == 0)
	  Invalidate();
      }
    //: Base class constructor
    // If object is of wrong type an invalid handle will be
    // created.
    
    OneChildBodyC &Body() 
      { return static_cast<OneChildBodyC &>(WidgetC::Body()); }
    //: Access body.
    
    const OneChildBodyC  &Body() const
      { return static_cast<const OneChildBodyC &>(WidgetC::Body()); }
    //: Access body.
    
  public:
    
    bool Add(const WidgetC &widge) 
      { return Body().Add(widge); }
    //: Add widget.
    // Only has effect before create is called.
    
    const WidgetC &Child() const 
      { return Body().Child(); }
    //: Access window contents;
  };

}

#endif