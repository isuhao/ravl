#ifndef RAVLGUIONECHILD_HEADER 
#define RAVLGUIONECHILD_HEADER 1
/////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=GUI
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
	if(dynamic_cast<WidgetBodyC *>(&Body()) == 0)
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
