# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001-14, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
######################################################

PACKAGE=Ravl/GUI

LICENSE=LGPL

REQUIRES = libGL libGTK2

#ifeq ($(ARC),sol2)
ifneq ($(filter $(ARC), sol2_7 sol2_9),)
# The solaris x11 header files a broken, so we need
# to turn off ansi flag and make the compiler more forgiving.
#ANSIFLAG=-fpermissive
endif
ifeq ($(ARC),alpha)
# The solaris x11 header files a broken, so we need
# to turn off ansi flag and make the compiler more forgiving.
ANSIFLAG=-fpermissive
endif

# Some of the mac opengl header files are broken, at least non-ansi c,
# so we have to swtich off the ansi flag.
ANSIFLAG=

DESCRIPTION = Interface to open GL.

#MAINS = #v3d.cc

HEADERS = \
 DObject3D.hh DLight3D.hh Util.hh Canvas3D.hh DViewPoint3D.hh \
 DCube3D.hh DTriMesh3D.hh DPointSet3d.hh DPinholeCamera03D.hh \
 DTexTriMesh3D.hh View3D.hh DSurfacePointVertexArray.hh \
 DSurfacePointVertexByteRGBArray.hh GLContext.hh 

SOURCES = DObject3D.cc  DLight3D.cc \
 Util.cc Canvas3D.cc DViewPoint3D.cc DCube3D.cc DTriMesh3D.cc \
 DPointSet3d.cc DPinholeCamera03D.cc DTexTriMesh3D.cc View3D.cc \
 DSurfacePointVertexArray.cc DSurfacePointVertexByteRGBArray.cc \
 GLContext.cc

PLIB = RavlGUI3D

SUMMARY_LIB=Ravl

EXAMPLES = exCanvas3D.cc exView3D.cc exDTexTriMesh3d.cc

USESLIBS = RavlCore RavlMath RavlGUI OpenGL Ravl3D x11 GTK RavlImage

ifeq ($(strip $(filter-out $(RESOURCES),GTKGLExt)),)
EXTERNALLIBS= GtkGLExt.def
USERCPPFLAGS += -DRAVL_USE_GTKGLEXT=1
USESLIBS += GtkGLExt
else
HEADERS += gdkgl.h gtkglarea.h
SOURCES += gdkgl.c gtkglarea.c
endif

EHT = Ravl.API.GUI.3D.html

PROGLIBS = Ravl3DIO RavlOS RavlImageIO RavlExtImgIO RavlDPDisplay.opt
