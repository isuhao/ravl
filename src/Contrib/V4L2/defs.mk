# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001-14, OmniPerception Ltd.
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here

REQUIRES = devVideo4Linux2

SUPPORT_ONLY = linux linux64

PACKAGE = Ravl/Image

HEADERS = V4L2Format.hh ImgIOV4L2.hh V4L2Buffer.hh

SOURCES = V4L2Format.cc ImgIOV4L2.cc

PLIB = RavlImgIOV4L2

SUMMARY_LIB=Ravl

MUSTLINK = MustLinkV4L2.cc

USESLIBS = RavlImage RavlIO RavlThreads

PROGLIBS = RavlOSIO RavlDPDisplay.opt

ANSIFLAG =

