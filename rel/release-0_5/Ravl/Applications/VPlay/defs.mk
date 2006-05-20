# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
###############################################
# $Id$
#! rcsid="$Id$"
#! file="Ravl/Applications/VPlay/defs.mk"

DESCRIPTION = VPlay - Video Player.

NESTED = Bitmaps.r

HEADERS = PlayControl.hh

SOURCES = PlayControl.cc

PACKAGE = Ravl/VPlay

MAINS= VPlay.cc 
#VCopy.cc

USESLIBS = RavlCore RavlOS RavlImage RavlOSIO RavlGUI RavlDPMT RavlGUI2D \
 RavlImageIO RavlVideoIO

PROGLIBS =

EHT = exeVPlay.eht