// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGTKTYPES_HEADER
#define RAVLGTKTYPES_HEADER 1
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/GUI/GTK/GTKTypes.hh"
//! lib=RavlGUI
//! userlevel=Develop
//! author="Charles Galambos"
//! docentry="Ravl.GUI.Internal"
//! date="23/03/99"

extern "C" {
  struct _GdkWindow;
  
  typedef struct _GtkWidget GtkWidget;
  typedef struct _GtkObject GtkObject;

#ifndef VISUAL_CPP  
  typedef struct _GdkWindow GdkWindow;
  typedef struct _GdkWindow GdkPixmap;
  typedef struct _GdkWindow GdkDrawable;
  typedef struct _GdkWindow GdkBitmap;
#else
  typedef struct _GdkDrawable GdkDrawable;
  typedef struct _GdkDrawable GdkBitmap;
  typedef struct _GdkDrawable GdkPixmap;
  typedef struct _GdkDrawable GdkWindow;
#endif
  
  typedef struct _GdkCursor GdkCursor;
  typedef union  _GdkEvent  GdkEvent;
  typedef struct _GdkEventExpose GdkEventExpose;
  typedef struct _GdkEventButton GdkEventButton;
  typedef struct _GdkEventMotion GdkEventMotion;
  typedef struct _GdkGC	  GdkGC;
}
#endif
