# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2002-11, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! file="Ravl/Applications/SkinBlobFind/defs.mk"
DONOT_SUPPORT=arm

MAINS=SkinBlobFind.cc
USESLIBS=RavlImage RavlImageIO RavlExtImgIO.opt RavlOSIO RavlImageProc
PROGLIBS = DynLink

#EHT=exeSkinBlobFind.eht