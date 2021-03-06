# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001-11, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! file="Ravl/OS/IO/defs.mk"

PACKAGE=Ravl/DP

HEADERS=FileSequence.hh SequenceIO.hh FileListIO.hh CompositeStream.hh \
 FileFormatComposite.hh  PlayList.hh  SubSequenceSpec.hh EditSpec.hh  \
 FileFormatDynamic.hh DynamicLink.hh ProcessPlayList.hh DPNetwork.hh \
 DynamicIO.hh

SOURCES=FileSequence.cc SequenceIO.cc FileListIO.cc CompositeStream.cc  \
 FileFormatComposite.cc  PlayList.cc  SubSequenceSpec.cc EditSpec.cc \
 FileFormatDynamic.cc DynamicLink.cc ProcessPlayList.cc DPNetwork.cc \
 DPStreamOpSetup.cc

MUSTLINK=RavlOSIOMustLink.cc

PLIB=RavlOSIO

SUMMARY_LIB=Ravl

USESLIBS=RavlOS RavlIO DynLink RavlXMLFactory

TESTEXES= testSequenceIO.cc

EXAMPLES=  exCompositeStream.cc exDynamicLink.cc exDynamicFormat.cc 

EHT=Ravl.API.OS.Sequence.html Ravl.API.OS.Sequence.Numbered_Files.html
