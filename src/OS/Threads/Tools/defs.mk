# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001-16, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
##########################################################
#! rcsid="$Id$"
#! file="Ravl/OS/Threads/Tools/defs.mk"

CXX_STD=CXX11

DESCRIPTION=Threading tools

PACKAGE=Ravl/Threads

HEADERS=MessageQueue.hh LaunchThread.hh TickerTrigger.hh \
 Signal.hh Signal1.hh Signal2.hh Signal3.hh MTPriQueueL.hh \
 SignalConnectionSet.hh TimedTriggerQueue.hh \
 ThreadState.hh ThreadLimitCounter.hh

SOURCES=MessageQueue.cc LaunchThread.cc TickerTrigger.cc \
 Signal.cc \
 SignalConnectionSet.cc TimedTriggerQueue.cc \
 ThreadState.cc ThreadLimitCounter.cc

EHT=Ravl.API.OS.Signals.html

PLIB=RavlThreads

SUMMARY_LIB=Ravl

LIBDEPS=RavlThreadTools.def

USESLIBS = RavlThreads RavlOS

EXAMPLES= exSignal.cc exSignal1.cc exSignal2.cc exLaunchThread.cc testAtomicSpeed.cc

TESTEXES = testLaunchThread.cc testTickerTrigger.cc testTimedTriggerQueue.cc testSignal.cc testAtomic.cc testThreads.cc


