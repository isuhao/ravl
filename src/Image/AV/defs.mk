# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Image/AV/defs.mk"

PACKAGE=Ravl

HEADERS= AVFrame.hh AVMixer.hh

SOURCES= AVFrame.cc AVMixer.cc

PLIB=RavlAV

SUMMARY_LIB=Ravl

USESLIBS=RavlAudioUtil RavlImageIO
