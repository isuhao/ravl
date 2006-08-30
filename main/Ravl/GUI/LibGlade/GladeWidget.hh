// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUI_GLADEWIDGET_HEADER
#define RAVLGUI_GLADEWIDGET_HEADER 1
//! docentry="Ravl.API.GUI.LibGlade"
//! rcsid="$Id$"
//! lib=RavlLibGlade
//! file="Ravl/GUI/LibGlade/GladeWidget.hh"

#include "Ravl/GUI/Widget.hh"
#include "Ravl/GUI/GladeXML.hh"

namespace RavlGUIN {

  //! userlevel=Develop
  //: Glade widget
  
  class GladeWidgetBodyC
    : public WidgetBodyC
  {
  public:
    GladeWidgetBodyC(const GladeXMLC &gladeXml,const StringC &widgetName,bool customWidget = true);
    //: Constructor
    
    GladeWidgetBodyC(const StringC &widgetName,bool customWidget = true);
    //: Constructor
    // NOTE: If using this constructor a Glade XML object must be set with SetXML()
    
    virtual ~GladeWidgetBodyC() { }
    //: Virtual destructor

    bool SetXML(const GladeXMLC &gladeXml);
    //: Set a Glade XML object to use
    // NOTE: Will be ignored if one has already been set
    
    virtual bool Create()
    { return CommonCreate(); }
    //: Create the widget.
    
    virtual bool Create(GtkWidget *_widget)
    { return CommonCreate(_widget); }
    //: Create with a widget supplied from elsewhere.
    
    bool AddObject(const StringC &name,const WidgetC &widget, bool optional = false);
    //: Add named widget.
    //!param: name - Name of the widget to search for in the Glade file
    //!param: widget - Widget object to connect to the named object
    //!param: optional - If false, warn if the widget is not found
    
  protected:
    bool InterceptDeleteEvent();
    //: Intercept the "delete-event", and just hide the widget.
    // Useful on windows where you just want to make them dissapear.
    // Note: Must be called after widget has been initialised
    
    virtual void WidgetDestroy();
    //: Called when gtk widget is destroyed.
    
    bool CommonCreate(GtkWidget *_widget = NULL);
    //: Common object creation
    
    GladeXMLC xml;
    StringC name;
    HashC<StringC, Tuple2C<WidgetC, bool> > children;
    bool customWidget;
  };
  
  //! userlevel=Normal
  //: Glade widget
  
  class GladeWidgetC
    : public WidgetC
  {
  public:
    GladeWidgetC()
    {}
    //: Default constructor
    // Creates an invalid handle.
    
    GladeWidgetC(const GladeXMLC &gladeXml,const StringC &widgetName,bool customWidget = true)
      : WidgetC(*new GladeWidgetBodyC(gladeXml,widgetName,customWidget))
    {}
    //: Constructor
    
    GladeWidgetC(const StringC &widgetName,bool customWidget = true)
      : WidgetC(*new GladeWidgetBodyC(widgetName,customWidget))
    {}
    //: Constructor
    // NOTE: If using this constructor a Glade XML object must be set with SetXML()
    
  protected:
    GladeWidgetC(GladeWidgetBodyC &body)
      : WidgetC(body)
    {}
    //: Body constructor
    
    GladeWidgetBodyC &Body()
    { return static_cast<GladeWidgetBodyC &>(WidgetC::Body()); }
    //: Access widget body.
    
    const GladeWidgetBodyC &Body() const
    { return static_cast<const GladeWidgetBodyC &>(WidgetC::Body()); }
    //: Access widget body.
    
  public:
    bool AddObject(const StringC &name,const WidgetC &widget, bool optional = false)
    { return Body().AddObject(name,widget,optional); }
    //: Add named widget.
    //!param: name - Name of the widget to search for in the Glade file
    //!param: widget - Widget object to connect to the named object
    //!param: optional - If false, warn if the widget is not found
    
  };

}


#endif
