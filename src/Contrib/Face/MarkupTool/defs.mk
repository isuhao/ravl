# Copyright (C) 2003, OmniPerception Ltd.
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here

REQUIRES=RLog

PACKAGE= Ravl/Face

MAINS =  markupTool.cc

LOCALHEADERS = ViewPage.hh ControlWin.hh

SOURCES = ViewPage.cc ControlWin.cc

PLIB = MarkupTool

USESLIBS = RavlGUI RavlFace RavlGUI2D

PROGLIBS = RavlExtImgIO RavlImgIOJasper.opt RLog GTK

