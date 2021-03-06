# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003-14, OmniPerception Ltd.
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here

REQUIRES=libGuppi libGTK2
# Requirement for libGTK2 stems from using RavlGUI rather than being
# a direrct dependency.

ORGANISATION=OmniPerception Ltd.

DONOT_SUPPORT=VCPP

PACKAGE=Ravl/Plot

HEADERS=GuppiTypes.hh GuppiHeaders.hh GuppiElement.hh GuppiGroup.hh GuppiCanvas.hh \
 GuppiScalarSequence.hh GuppiLineGraph.hh GuppiGraph.hh

SOURCES=GuppiElement.cc GuppiGroup.cc GuppiCanvas.cc GuppiScalarSequence.cc \
 GuppiLineGraph.cc GuppiGraph.cc GuppiInit.cc

PLIB=RavlGuppi

USESLIBS=RavlPlot RavlGUI Guppi

EXAMPLES=exGuppi.cc

EXTERNALLIBS=Guppi.def
