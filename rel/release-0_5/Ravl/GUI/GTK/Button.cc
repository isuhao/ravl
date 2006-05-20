// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI
//! file="Ravl/GUI/GTK/Button.cc"


#include "Ravl/GUI/Button.hh"
#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/Manager.hh"
#include <iostream.h>
#include <gtk/gtk.h>

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x) 
#endif

namespace RavlGUIN {
  
  // Default constructor.
  
  ButtonBodyC::ButtonBodyC(const char *nlabel,const char *ntooltip)
    : state(false),
      label(nlabel)
    
  { SetToolTip(ntooltip); }
  
  //: Constructor.
  
  ButtonBodyC::ButtonBodyC(const char *nlabel,const PixmapC &pixm)
    : state(false),
      pix(pixm),
      label(nlabel)
  {}

  GtkWidget *ButtonBodyC::BuildWidget(const char *aLab) {
    if(aLab == 0)
      return gtk_button_new ();
    return gtk_button_new_with_label (aLab);
  }

  //: Set toggle label.
  // GUI thread only.
  
  bool ButtonBodyC::GUISetLabel(StringC &text) {
    label = text;
    GtkWidget *tb;
    GtkWidget *child = GTK_BIN(widget)->child;
    if(child != 0) {
      if(GTK_IS_LABEL(child)) { // Is a label widget already ?
	gtk_label_set(GTK_LABEL(child),text.chars());
	return true;
      }
      gtk_container_remove(GTK_CONTAINER(widget),child);
    }
    tb = gtk_label_new(text.chars());
    gtk_widget_show (tb);
    gtk_container_add(GTK_CONTAINER(widget),tb);
    return true;
  }
  
  //: Set toggle label.
  
  void ButtonBodyC::SetLabel(StringC &text) {
    Manager.Queue(Trigger(ButtonC(*this),&ButtonC::GUISetLabel,text));
  }

  
  bool  ButtonBodyC::Create() {
    if(widget != 0)
      return true;
    if(pix.IsValid()) {
      widget = BuildWidget();
      pix.Create();
      GtkWidget *pixmapwid = pix.Widget();
      gtk_widget_show( pixmapwid );
      if(label.Size() == 0) 
	gtk_container_add( GTK_CONTAINER(widget), pixmapwid);
      else {
	GtkWidget *box = gtk_hbox_new (false, 0);
	gtk_container_set_border_width (GTK_CONTAINER (box), 1);
	GtkWidget *lw = gtk_label_new (label.chars());
	gtk_box_pack_start (GTK_BOX (box),pixmapwid, false, false, 3);      
	gtk_box_pack_start (GTK_BOX (box), lw, false, false, 3);
	gtk_container_add( GTK_CONTAINER(widget), box);
	gtk_widget_show(lw);
	gtk_widget_show(box);
      }
    } else {
      ONDEBUG(cerr << "ButtonBodyC::Create() Label:'" << label << "'\n");
      if(label.Size() == 0)
	widget = BuildWidget("?");
      else
	widget = BuildWidget(label);
    }
    ConnectSignals();
    return true;
  }
  
  ////////////////////////////////
  //: Create a button.
  
  
  ButtonC::ButtonC(const char *nlabel,const char *ntooltip)
    : WidgetC(*new ButtonBodyC(nlabel,ntooltip))
  {}
  
}