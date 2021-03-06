# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/3D/Carve3D/defs.mk"
PACKAGE=Ravl/3D
HEADERS=SurfacePoint3dArray.hh #VoxelSet.hh PointSet.hh VoxelCameraLookup.hh VoxelCarve.hh 
SOURCES= SurfacePoint3dArray.cc #VoxelCameraLookup.cc #VoxelCarve.cc
PLIB=Ravl3D
SUMMARY_LIB=Ravl
LIBDEPS=RavlCarve3D.def
USESLIBS=RavlCore RavlMath RavlImage # RavlCameraCal

#Unlinked EHT as it no longer seems to be relevant
#EHT=Ravl.API.3D.Carve3D.html
