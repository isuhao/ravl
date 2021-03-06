# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2002-14, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here

DONOT_SUPPORT=arm

EXAMPLES=mosaic.cc 
MAINS=mosaic.cc xmosaic.cc

PROGLIBS=RavlImageProc RavlVideoIO RavlGUI2D RavlImgIOV4L.opt \
  RavlDPDisplay.opt RavlDV.opt RavlExtImgIO.opt RavlImageIO \
  RavlMPEG2.opt CSPDriver.opt RavlURLIO.opt RavlLibFFmpeg.opt GTK

#EHT = Ravl.Applications.Mosaic.mosaic.html \
# Ravl.Applications.Mosaic.xmosaic.html Ravl.Applications.tracker.html

REQUIRES = libGTK2

