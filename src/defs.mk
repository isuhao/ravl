# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001-12, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
#
# file-header-ends-here

PACKAGE=

DESCRIPTION=RAVL, Recognition and Vision Library

NESTED=Core.r OS.r CCMath.r Math.r Plot.r PatternRec.r Audio.r \
Image.r 3D.r Logic.r SourceTools.r GUI.r CompVision.r Contrib.r \
Applications.r AutoTools.r Single

EXTRA_DIST_DIRS=Single
# Include the dir Single in the dist file. This is needed as we do not build in there
# recursivly hence it is not listed for automatic parsing (not listed with the .r
# suffix in NESTED).

LOCAL_FILES=

EHT=Ravl.eht Ravl.API.html
