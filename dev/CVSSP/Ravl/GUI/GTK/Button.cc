/////////////////////////////////////////////
//! rcsid="$Id$"


#include "Ravl/GUI/Button.hh"
#include "Ravl/GUI/Window.hh"
#include <iostream.h>
#include <gtk/gtk.h>

#define DODEBUG 1

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
  
  bool  ButtonBodyC::Create() {
    if(widget != 0)
      return true;
    
    if(pix.IsValid()) {
      widget = BuildWidget();
      pix.Create();
      GtkWidget *pixmapwid = pix.Widget();
      gtk_widget_show( pixmapwid );
      if(label == 0) 
	gtk_container_add( GTK_CONTAINER(widget), pixmapwid);
      else {
	GtkWidget *box = gtk_hbox_new (false, 0);
	gtk_container_set_border_width (GTK_CONTAINER (box), 1);
	GtkWidget *lw = gtk_label_new (label);
	gtk_box_pack_start (GTK_BOX (box),pixmapwid, false, false, 3);      
	gtk_box_pack_start (GTK_BOX (box), lw, false, false, 3);
	gtk_container_add( GTK_CONTAINER(widget), box);
	gtk_widget_show(lw);
	gtk_widget_show(box);
      }
    } else {
      if(label == 0)
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
