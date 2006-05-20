# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Math/Statistics/MeanCovariance/defs.mk"

PACKAGE=Ravl

HEADERS= MeanVariance.hh MeanNd.hh MeanCovarianceNd.hh Statistics.hh \
 Mean.hh

SOURCES= MeanVariance.cc MeanNd.cc MeanCovarianceNd.cc Statistics.cc \
 Mean.cc

TESTEXES=testMeanCovar.cc

PLIB=RavlMath

LIBDEPS=RavlMathMeanCov.def

USESLIBS=RavlMath