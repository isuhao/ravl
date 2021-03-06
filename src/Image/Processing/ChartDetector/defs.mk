# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2004-14, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
#
# file-header-ends-here

PACKAGE=Ravl/Image

MAINS=chartdet.cc

HEADERS= ChartDetector.hh ChartDetectorRegion.hh ChartLocalise.hh \
 CostAffineImageCorrelation.hh

SOURCES= ChartDetector.cc ChartDetectorRegion.cc ChartLocalise.cc \
 CostAffineImageCorrelation.cc

PLIB=RavlChartDetector

SUMMARY_LIB=Ravl

USESLIBS=RavlImage RavlImageProc RavlImageIO  Optimisation

PROGLIBS=RavlDPDisplay.opt RavlExtImgIO RavlOS RavlPatternRec

AUXFILES=CalibrationChart.ps CalibrationChart.png CalibrationChart.coords

AUXDIR=share/RAVL/pixmaps
