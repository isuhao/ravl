# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/OS/Misc/defs.mk"

PACKAGE=Ravl/OS

DESCRIPTION=Interfaces for common computer hardware.

HEADERS=UnixStreamIO.hh WinStreamIO.hh DMABuffer.hh SysLog.hh CharIO.hh

SOURCES=UnixStreamIO.cc WinStreamIO.cc CharIO.cc

PLIB=RavlOS

SUMMARY_LIB=Ravl

EHT= Ravl.API.OS.Hardware.html

USESLIBS=RavlCore RavlIO

LIBDEPS=RavlOSMisc.def

TESTEXES=testOSMisc.cc

EXAMPLES=exReadWithoutReturn.cc
