# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2004, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"

REQUIRES=libmkl

PACKAGE=Ravl

HEADERS=IntelFFT2d.hh

SOURCES=IntelFFT2d.cc

TESTEXE= testIntelFFT2d.cc

PLIB=RavlIntelMKL

USESLIBS=IntelMKL RavlMath

AUXFILES=IntelMKL.def

AUXDIR=lib/RAVL/libdep
