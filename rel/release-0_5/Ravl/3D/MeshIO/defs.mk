# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/3D/MeshIO/defs.mk"

PACKAGE=Ravl/3D

HEADERS= MeshIO.hh \
         TriFileIO.hh FormatTriFile.hh \
         MeshIOObj.hh FormatMeshObj.hh

SOURCES= TriFileIO.cc FormatTriFile.cc TriMeshIO.cc \
         MeshIOObj.cc FormatMeshObj.cc

MUSTLINK= RavlMeshIO.cc

PLIB=Ravl3DIO

USESLIBS=Ravl3D RavlIO

EHT= Ravl.3D.IO.html