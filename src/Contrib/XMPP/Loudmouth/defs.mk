# This file is part of RAVL, Recognition And Vision Library
# Copyright (C) 2010-14, OmniPerception Ltd.
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here

REQUIRES=Loudmouth RLog
# Requirement for RLog is from needing RavlXMPP not a direct requirement


PACKAGE=Ravl/XMPP

HEADERS=LMConnection.hh

SOURCES=LMConnection.cc

MAINS= exLoudmouth.cc

PLIB=RavlXMPPLoudmouth

USESLIBS=RavlXMPP RavlCore Loudmouth RavlOS RavlThreads RavlXMLFactory

PROGLIBS=

MUSTLINK=LinkRavlXMPP.cc

EXTERNALLIBS=Loudmouth.def
