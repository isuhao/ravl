# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001-14, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here

DESCRIPTION = Basic parts of the Pattern Recognition library.

PACKAGE = Ravl/PatternRec

HEADERS =  Sample.hh SampleIter.hh SampleVector.hh SampleLabel.hh \
 SampleDiscrete.hh DataSetBase.hh DataSet1.hh DataSet1Iter.hh DataSet2.hh \
 DataSet2Iter.hh DataSet3.hh DataSet3Iter.hh DataSet4.hh DataSet4Iter.hh \
 SampleIO.hh Function.hh Function1.hh Designer.hh \
 DesignFunctionUnsupervised.hh DesignFunctionSupervised.hh VectorLabelIO.hh \
 DataSetVectorLabel.hh DataSetVectorLabelWeight.hh SampleStream.hh \
 SampleStreamVector.hh SampleVectorFloat.hh SampleStreamVectorFloat.hh \
 SampleReal.hh SampleStreamFromSample.hh ProcessVectorFunction.hh \
 ProcessVectorLabelFunction.hh FunctionSlice.hh FunctionConcatenate.hh \
 FunctionCascade.hh SampleStreamVectorLabel.hh DataSetIO.hh FieldInfo.hh \
 TestFunctions.hh FunctionExpand.hh DPProcessFunction.hh

SOURCES =  SampleVector.cc SampleLabel.cc DataSetBase.cc Function.cc \
 Function1.cc Designer.cc DesignFunctionUnsupervised.cc \
 DesignFunctionSupervised.cc VectorLabelIO.cc DataSetVectorLabel.cc \
 SampleStreamVector.cc DataSetVectorLabelWeight.cc SampleVectorFloat.cc \
 SampleStreamVectorFloat.cc SampleReal.cc FunctionSlice.cc \
 FunctionConcatenate.cc FunctionCascade.cc SampleStreamVectorLabel.cc \
 SampleIO.cc DataSetIO.cc FieldInfo.cc TestFunctions.cc \
 FunctionExpand.cc  DPProcessFunction.cc

MAINS = doDataSet.cc exPlotTestFunctions.cc

PLIB = RavlDataSet

SUMMARY_LIB=Ravl

EXAMPLES = exSample.cc exSampleStream.cc 

TESTEXES=testDataSet.cc testDataSetXMLFactory.cc

USESLIBS=RavlCore RavlMath RavlOSIO RavlIO fann RavlXMLFactory RavlMathIO 

PROGLIBS=RavlOS RavlPatternRecIO RavlGnuPlot.opt

EHT=Ravl.API.Pattern_Recognition.Data_Set.html

MUSTLINK=linkDataSet.cc
