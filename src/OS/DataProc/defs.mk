# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001-11, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! file="Ravl/OS/DataProc/defs.mk"

PACKAGE=Ravl/DP

HEADERS= MTIOConnect.hh PlayControl.hh ThreadPipe.hh Buffer.hh FixedBuffer.hh \
 Governor.hh Hold.hh SerialisePort.hh Blackboard.hh SPortShare.hh SplitI.hh \
 TailIStream.hh OpenPortInventory.hh

SOURCES= MTIOConnect.cc PlayControl.cc Governor.cc Blackboard.cc \
 TailIStream.cc OpenPortInventory.cc

EXAMPLES= exMTDataProc.cc exDPSplit.cc
# exFailOver.cc  exDPMultiplex.cc 

TESTEXES = testOSDataProc.cc

PLIB=RavlDPMT

SUMMARY_LIB=Ravl

USESLIBS=RavlOS RavlIO RavlThreads 
