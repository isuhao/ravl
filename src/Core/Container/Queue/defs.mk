# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
# $Id$
#! rcsid="$Id$"
#! file="Ravl/Core/Container/Queue/defs.mk"

DESCRIPTION=Queues.

PACKAGE=Ravl

MAINS = 

PLIB = RavlCore

SUMMARY_LIB=Ravl

LIBDEPS = RavlQueue.def

HEADERS = PriQueue.hh PriQueueL.hh HeapNode.hh BlkQueue.hh FixedQueue.hh

EXAMPLES = testPriQH.cc testPriQ.cc

USESLIBS = RavlCore

TESTEXES = testPriQH.cc testPriQ.cc testPriQueue.cc testFixedQueue.cc testQueue.cc 

EHT=Ravl.API.Core.Queues.eht
