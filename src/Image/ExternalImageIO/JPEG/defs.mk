# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2012, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#

PACKAGE=Ravl/Image

DESCRIPTION = External Image IO JPEG routines

REQUIRES=JPEG

DONOT_SUPPORT=cygwin arm

PLIB = RavlExtImgIO

SUMMARY_LIB=Ravl

LIBDEPS= RavlJPEG.def

HEADERS = ImgIOJPeg.hh ImgIOJPegB.hh JPEGFormat.hh CompressedImageJPEG.hh

SOURCES = ImgIOJPeg.cc JPEGFormat.cc CompressedImageJPEG.cc

USESLIBS = RavlImage RavlIO RavlImageIO LibJPEG
