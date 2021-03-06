# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003-14, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here

REQUIRES=libGTK2

PACKAGE=Ravl/GUI

HEADERS=AttributeEditor.hh AttributeEditorWindow.hh ThumbNailTimeLine.hh EventTimeLine.hh

SOURCES=AttributeEditor.cc AttributeEditorWindow.cc ThumbNailTimeLine.cc EventTimeLine.cc

PLIB=RavlGUIUtil

SUMMARY_LIB=Ravl

USESLIBS=RavlGUI RavlCore RavlIO RavlGUI2D GTK

EXAMPLES= exAttributeEditor.cc
