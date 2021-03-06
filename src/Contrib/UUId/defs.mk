# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001-12, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! file="Contrib/UUId/defs.mk"

REQUIRES = UUIdTheo

LICENSE=LGPL

ORGANISATION=OmniPerception Ltd.

DESCRIPTION=

PACKAGE= Ravl

HEADERS= GenerateUUId.hh

SOURCES= GenerateUUId.cc

MAINS=

PLIB=RavlUUId

SUMMARY_LIB=Ravl

USESLIBS=uuidTheo RavlThreads 

PROGLIBS=

EXAMPLES=

EXTERNALLIBS = uuidTheo.def
