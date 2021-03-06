# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003-14, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here

PACKAGE=Ravl/Image

REQUIRES=libdc1394

DONOT_SUPPORT=VCPP

MAINS= twocam.cc

HEADERS= ImgIO1394dc.hh Lib1394dcFormat.hh

SOURCES= ImgIO1394dc.cc Lib1394dcFormat.cc

PLIB= RavlImgIO1394dc

EXTERNALLIBS= Lib1394dc.def

MUSTLINK=InitLib1394dc.cc

USESLIBS=RavlCore RavlIO RavlImage Lib1394dc 

PROGLIBS=  RavlOSIO RavlDPDisplay.opt

EHT=Ravl.Contrib.Video_IO.IIDC.html

EXAMPLES=test1394dc.cc 
