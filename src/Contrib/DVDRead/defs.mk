# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003-14, OmniPerception Ltd.
# This code may be redistributed under the terms of the GNU
# General Public License (GPL). See the gpl.licence file for details
# file-header-ends-here

REQUIRES = dvdread libmpeg2

CCPPFLAGS += -D__STDC_LIMIT_MACROS 

DONOT_SUPPORT=VCPP

PACKAGE = Ravl

HEADERS = DVDRead.hh DVDFormat.hh ImgIOMPEG2DVD.hh

SOURCES = DVDRead.cc DVDFormat.cc ImgIOMPEG2DVD.cc

PLIB = RavlDVDRead

EXAMPLES = exDVDRead.cc

USESLIBS = RavlLibMPEG2 DVDRead RavlIO RavlCore

PROGLIBS = RavlDPDisplay.opt RavlImage  

MUSTLINK = InitDVDFormat.cc

EXTERNALLIBS = DVDRead.def
