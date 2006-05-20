// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUICWIDGET_HEADER
#define RAVLGUICWIDGET_HEADER 1
////////////////////////////////////////////////////
//! file="Ravl/GUI/GTK/CWidget.hh"
//! lib=RavlGUI
//! author="Charles Galambos"
//! date="23/03/99"
//! rcsid="$Id$"
//! docentry="Ravl.GUI.Internal"

#include "Ravl/GUI/Widget.hh"
#include "Ravl/DList.hh"
#include "Ravl/Threads/Mutex.hh"

namespace RavlGUIN {
  
  //! userlevel=Develop
  //: Container Widget Body
  
  class ContainerWidgetBodyC 
    : public WidgetBodyC
  {
  public:
    ContainerWidgetBodyC()
      {}
    //: Default constructor.
    
    ContainerWidgetBodyC(const DListC<WidgetC> &widges)
      : children(widges)
      {}
    //: Constructor.
    
    virtual bool Create();
    //: Create the widget.
    
    virtual bool Add(const WidgetC &widge);
    //: Add a child widget.
    
    bool Add(const DListC<WidgetC> &widges);
    //: Add children.
    
    bool GUIAdd(WidgetC &widge);
    //: Add widget.
    // GUI thread only.
    
    virtual bool Remove(WidgetC &widge);
    //: Remove a child widget.
    
  protected:
    virtual void Destroy();
    //: Undo all refrences.
    // Used to avoid problems with circluar refrences.
    // This should undo all refrences to RAVL and GUI
    // objects which are not in the destroy tree. 
    // The function is called by the root window in its
    // destructor.
    
    MutexC access;   // Access control to widget list.
    DListC<WidgetC> children; // Child widgets.
    
    friend class ContainerWidgetC;
  };
  
  //! userlevel=Normal
  //: Container Widget
  
  class ContainerWidgetC 
    : public WidgetC
  {
  public:
    ContainerWidgetC()
      {}
    //: Default constructor.
    
  protected:
    ContainerWidgetC(ContainerWidgetBodyC &body)
      : WidgetC(body)
      {}
    //: Body constructor.

    ContainerWidgetC(WidgetC &body)
      : WidgetC(body)
      {
	if(dynamic_cast<ContainerWidgetBodyC *>(&WidgetC::Body()) == 0)
	  Invalidate();
      }
    //: Base constructor.
    
    ContainerWidgetBodyC &Body() 
      { return static_cast<ContainerWidgetBodyC &>(WidgetC::Body()); }
    //: Access body.
    
    const ContainerWidgetBodyC &Body() const
      { return static_cast<const ContainerWidgetBodyC &>(WidgetC::Body()); }
    //: Access body.
    
    bool GUIAdd(WidgetC &widge)
      { return Body().GUIAdd(widge); }
    //: Add widget.
    // GUI thread only.
    
  public:  
    bool Add(const WidgetC &widge)
      { return Body().Add(widge); }
    //: Add child widget.

    bool Remove(WidgetC &widge)
      { return Body().Remove(widge); }
    //: Remove child widget.
    
    bool Add(const DListC<WidgetC> &widges)
      { return Body().Add(widges); }
    //: Add child widget.
    
    bool operator+=(const WidgetC &widge)
      { return Body().Add(widge); }
    //: Add child widget.
    
    friend class ContainerWidgetBodyC;
  };
}

#endif