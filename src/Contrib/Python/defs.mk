# This file is part of RAVL, Recognition And Vision Library
# Copyright (C) 2008-14, OmniPerception Ltd.
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# Python is used under the terms of the Python License
# Copyright (C) 2001, 2002, 2003, 2004 Python Software Foundation; All Rights Reserved
# file-header-ends-here

REQUIRES = LibPython

PACKAGE = Ravl

HEADERS = Python.hh PythonObject.hh PythonException.hh PythonLock.hh PythonMainState.hh

SOURCES = Python.cc PythonObject.cc PythonException.cc PythonLock.cc PythonMainState.cc

PLIB = RavlPython

USESLIBS = RavlOS RavlCore RavlThreads Python 

EXAMPLES = exPython.cc exPythonThreaded.cc exPythonMultipleInterpreters.cc

ifeq (libGTK2,$(filter libGTK2,$(RESOURCES)))
  # This example requires RavlGUI which depends on libGTK2
  # hence we only build it if we have the GTK libraries
  PROGLIBS = RavlGUI
  EXAMPLES += exPyGTK.cc
endif

TESTEXES =

EXTERNALLIBS = Python.def
