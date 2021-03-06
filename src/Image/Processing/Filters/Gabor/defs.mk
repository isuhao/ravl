# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001-14, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here

PACKAGE = Ravl/Image

SOURCES = GaborComplex.cc GaborFilter2d.cc 

HEADERS = GaborComplex.hh GaborFilter2d.hh

LIBDEPS = RavlImageGabor.def

PLIB = RavlImageProc

SUMMARY_LIB=Ravl

USESLIBS=  RavlImageProc

PROGLIBS = RavlDPDisplay.opt RavlExtImgIO

EXAMPLES = exGaborFilter.cc exGaborComplex.cc

HTML = Gabor.pdf


