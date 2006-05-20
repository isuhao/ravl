# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Image/Processing/Filters/defs.mk"

PACKAGE=Ravl/Image

HEADERS= Convolve2d.hh ConvolveSeparable2d.hh ConvolveHorz2d.hh \
 ConvolveVert2d.hh BilinearInterpolation.hh

SOURCES= Convolve2d.cc

TESTEXES= testConvolve.cc

LIBDEPS=RavlImageFilter.def

PLIB=RavlImage

USESLIBS=RavlImage

EHT= Ravl.Images.Filtering.html Ravl.Images.Warping.html