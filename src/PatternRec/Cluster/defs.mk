# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! file="Ravl/PatternRec/Cluster/defs.mk"

DESCRIPTION = Pattern Recognition Classifiers

PACKAGE=Ravl/PatternRec

HEADERS=Classifier.hh DesignClassifierUnsupervised.hh ClassifierNearestNeighbour.hh \
 DesignKMeans.hh DesignMeanShiftCluster.hh DesignCluster.hh DesignKohonenNet.hh \
 ClassifierFuzzyCMeans.hh DesignFuzzyCMeansCluster.hh

SOURCES=Classifier.cc DesignClassifierUnsupervised.cc ClassifierNearestNeighbour.cc \
 DesignKMeans.cc DesignMeanShiftCluster.cc DesignCluster.cc DesignKohonenNet.cc \
 ClassifierFuzzyCMeans.cc DesignFuzzyCMeansCluster.cc 

PLIB=RavlPatternRec

SUMMARY_LIB=Ravl

LIBDEPS=RavlPatternRecCluster.def

USESLIBS=RavlPatternRec

PROGLIBS= RavlPatternRecIO  RavlGnuPlot.opt

MAINS= doCluster.cc

EXAMPLES=exKMeansCluster.cc exFuzzyCMeansCluster.cc exDesignMeanShiftCluster.cc

TESTEXES= testPatternRecCluster.cc
