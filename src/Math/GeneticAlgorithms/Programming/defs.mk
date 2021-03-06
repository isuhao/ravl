# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2011-4, Charles Galambos
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! author=Charles Galambos
#! docentry=Ravl.API.Math.Genetic.Programming

PACKAGE=Ravl/Genetic

ORGANISATION=Charles Galambos

HEADERS= GPInstruction.hh \
 GPVariable.hh GPInstSendSignal.hh GPInstIf.hh GPInstRoutine.hh \
 GPInstLoadConst.hh GPInstAdd.hh GPInstSubtract.hh GPInstAssign.hh \
 GPInstPutArray.hh GPInstGetArray.hh GPInstIncrement.hh \
 GPInstDecrement.hh GPInstLoop.hh GPInstMultiply.hh GPInstDivide.hh

SOURCES=GPInstruction.cc \
 GPVariable.cc GPInstSendSignal.cc GPInstIf.cc GPInstRoutine.cc \
 GPInstLoadConst.cc GPInstAdd.cc GPInstSubtract.cc GPInstAssign.cc \
 GPInstPutArray.cc GPInstGetArray.cc GPInstIncrement.cc \
 GPInstDecrement.cc GPInstLoop.cc GPInstMultiply.cc GPInstDivide.cc

MAINS=

MUSTLINK=LinkGeneticProgram.cc

PLIB=RavlGeneticProgram

SUMMARY_LIB=Ravl

USESLIBS=RavlOS RavlGeneticOptimisation

#TESTEXES=testGeneticProgram.cc
 
