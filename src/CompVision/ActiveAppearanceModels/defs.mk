# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2005-11, OmniPerception Ltd.
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
#
# file-header-ends-here

DESCRIPTION = Active appearance models

PACKAGE = Ravl/Image

DONOT_SUPPORT = arm

MAINS = aamBuildShapeModel.cc aamBuildAppearanceModel.cc \
 aamBuildActiveAppearanceModel.cc  aamCombineActiveAppearanceModel.cc \
 aamLocaliseFace.cc aamBuildPoseEstimator.cc aamSynthesizeFrontal.cc aamTrackFace.cc

EXAMPLES = aamBuildShapeModel.cc aamBuildAppearanceModel.cc \
 aamBuildActiveAppearanceModel.cc aamCombineActiveAppearanceModel.cc aamLocaliseFace.cc \
 aamBuildPoseEstimator.cc aamSynthesizeFrontal.cc

HEADERS = AAMAppearance.hh AAMShapeModel.hh AAMAffineShapeModel.hh AAMScaleRotationShapeModel.hh \
 AAMAppearanceModel.hh AAMAppearanceUtil.hh AAMActiveAppearanceModel.hh AAMSampleStream.hh \
 AAMMultiResActiveAppearanceModel.hh AAMFaceLocalisation.hh AAMPoseEstimateCostFunction.hh \
 AAMPoseEstimate.hh AAMFaceCorrection.hh AAMSampleStreamFileList.hh 

SOURCES = AAMAppearance.cc AAMShapeModel.cc AAMAffineShapeModel.cc AAMScaleRotationShapeModel.cc \
 AAMAppearanceModel.cc AAMAppearanceUtil.cc AAMActiveAppearanceModel.cc AAMSampleStream.cc \
 AAMMultiResActiveAppearanceModel.cc AAMFaceLocalisation.cc AAMPoseEstimateCostFunction.cc \
 AAMPoseEstimate.cc AAMFaceCorrection.cc AAMActiveAppearanceModelsIO.cc AAMSampleStreamFileList.cc 

MUSTLINK = AAMActiveAppearanceModelMustLink.cc

PLIB = RavlAAM

SUMMARY_LIB=Ravl

USESLIBS = RavlCore RavlImage RavlImageProc RavlMath RavlOS RavlPatternRec RavlOptimise \
 RavlIO Optimisation

PROGLIBS = RavlImageIO RavlExtImgIO.opt RavlMathIO RavlDPDisplay.opt RavlImgIOV4L2.opt

EHT = AAM.html

AUXDIR=share/doc/Ravl/Images/AAM

AUXFILES= 000_1_2_090.png 000_1_2_090.xml
