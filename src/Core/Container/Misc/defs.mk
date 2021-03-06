# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
# $Id$
#! rcsid="$Id$"
#! file="Ravl/Core/Container/Misc/defs.mk"

PACKAGE=Ravl

HEADERS=Stack.hh StackIter.hh Tuple2.hh Tuple3.hh Tuple4.hh \
 BlkStack.hh BlkStackIter.hh \
 BinTable.hh BinIter.hh BinList.hh \
 Collection.hh CollectionIter.hh

SOURCES=Stack.cc

PLIB=RavlCore

SUMMARY_LIB=Ravl

LIBDEPS=RavlCMisc.def

USESLIBS=RavlCore

TESTEXES=testStack.cc testBlkStack.cc testBinTable.cc

EXAMPLES=exStack.cc

EHT=Ravl.API.Core.Stacks.eht Ravl.API.Core.Tuples.eht
