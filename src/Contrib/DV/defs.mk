# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001-14, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here

PACKAGE = Ravl/Image

DESCRIPTION = Digital Video Classes

SUPPORT_ONLY = linux  linux64

REQUIRES = libDV

MAINS=doDvDisplay.cc 

HEADERS=ImgIODv.hh DvDecode.hh DvIFormat.hh 

SOURCES=ImgIODv.cc DvDecode.cc DvIFormat.cc DvFrameConvert.cc

PLIB=RavlDV

SUMMARY_LIB=Ravl

EXTERNALLIBS= LibDV.def

USESLIBS=RavlCore RavlImage RavlIO RavlOS RavlOSIO LibDV  RavlVideoIO RavlAV

PROGLIBS= RavlDPDisplay.opt RavlDevAudio

MUSTLINK = RAVLVidIDV.cc

EHT = DV.html

