# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
DESCRIPTION = Pattern Recognition Toolbox

PACKAGE = Ravl/PatternRec

HEADERS = Sample.hh SampleVector.hh SampleLabel.hh DataSet1.hh

SOURCES = SampleVector.cc SampleLabel.cc

MAINS = exSample.cc

PLIB = RavlPatternRec

USESLIBS=RavlCore RavlMath

