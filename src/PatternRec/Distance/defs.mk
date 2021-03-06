# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/PatternRec/Distance/defs.mk"

DESCRIPTION = Pattern Recognition Toolbox

PACKAGE = Ravl/PatternRec

HEADERS=Distance.hh DistanceEuclidean.hh DistanceMax.hh DistanceCityBlock.hh \
 DistanceMahalanobis.hh DistanceSqrEuclidean.hh DistanceRobust.hh DistanceChi2.hh \
 DistanceCorrelation.hh

SOURCES=Distance.cc DistanceEuclidean.cc DistanceMax.cc DistanceCityBlock.cc \
 DistanceMahalanobis.cc DistanceSqrEuclidean.cc DistanceRobust.cc DistanceChi2.cc \
 DistanceCorrelation.cc

#LIBDEPS=RavlPatternRecDistance.def

PLIB=RavlPatternRec

SUMMARY_LIB=Ravl

TESTEXES=testMeasure.cc testDistanceXMLFactory.cc

USESLIBS=RavlCore RavlMath RavlOSIO RavlIO fann RavlXMLFactory RavlMathIO RavlDataSet Optimisation

EHT=Ravl.API.Pattern_Recognition.Distance.html

MUSTLINK=linkDistance.cc

# MAINS=testDistanceXMLFactory.cc
