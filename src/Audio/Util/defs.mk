# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! file="Ravl/Audio/Util/defs.mk"

PACKAGE=Ravl/Audio

HEADERS=AudioIO.hh  Types.hh WindowSignal.hh Segment.hh Transcription.hh \
 AudioFrame.hh

SOURCES=AudioIO.cc WindowSignal.cc  Segment.cc Transcription.cc \
 AudioFrame.cc

PLIB=RavlAudioUtil

SUMMARY_LIB=Ravl

MUSTLINK= linkRavlAudioUtil.cc

USESLIBS=RavlIO RavlOSIO RavlXMLFactory

EHT= Ravl.API.Audio.IO.html

TESTEXES= testAudioUtil.cc



