# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003-11, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
#
# file-header-ends-here

REQUIRES=avifile

DONOT_SUPPORT=VCPP

PACKAGE=Ravl/Image

HEADERS= AVIFileIO.hh AVIFileFormat.hh

SOURCES= AVIFileIO.cc AVIFileFormat.cc

PLIB=RavlAVIFile

MUSTLINK= MustLinkAVIFile.cc

USESLIBS= RavlImage RavlIO AVIFile

PROGLIBS= RavlVideoIO

EXAMPLES=testAVIFile.cc

EXTERNALLIBS=AVIFile.def
