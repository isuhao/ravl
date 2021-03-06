# This file is part of RAVL, Recognition And Vision Library
# Copyright (C) 2008, OmniPerception Ltd.
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# Python is used under the terms of the Python License
# Copyright (C) 2001, 2002, 2003, 2004 Python Software Foundation; All Rights Reserved
# file-header-ends-here

REQUIRES =  NumPy

PACKAGE = Ravl

HEADERS = 

SOURCES = NumPy.cc

PLIB = RavlNumPy

MUSTLINK = linkNumPy.cc

USESLIBS =  Python NumPy

PROGLIBS = 

TESTEXES =

EXAMPLES = 

EXTERNALLIBS = NumPy.def
