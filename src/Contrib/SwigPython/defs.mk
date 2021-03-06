# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2006-14, OmniPerception Ltd.
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here

REQUIRES=LibPython Swig SwigPython

PACKAGE=Ravl/Swig

HEADERS=

SOURCES=Ravl.i

PLIB=RavlPythonSwig

SINGLESO=_RavlPython

USESLIBS=RavlDPDisplay.opt RavlGUI2D.opt RavlGUI.opt RavlMath ccmath \
RavlImageIO RavlImage Python RavlNet RavlService RavlXMLFactory RavlThreads \
RavlOSIO RavlOS RavlIO RavlCore

SWIGOPTS=-python

AUXDIR=/share/Python

AUXFILES=Ravl.py
