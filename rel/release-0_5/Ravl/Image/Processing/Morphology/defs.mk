# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Image/Processing/Morphology/defs.mk"

PACKAGE=Ravl/Image

HEADERS=Erode.hh Dilate.hh DilateSubSample2X.hh

PLIB=RavlImage

LIBDEPS=RavlImageMorphology.def

USESLIBS=RavlImage 

EHT=Ravl.Images.Morphology.html

TESTEXES=testMorphology.cc