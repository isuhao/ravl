# This file is part of QMake, Quick Make System 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU General 
# Public License (GPL). See the gpl.licence file for details or
# see http://www.gnu.org/copyleft/gpl.html
# file-header-ends-here
#######################################
# Setup make flags.
# $Id$
#! rcsid="$Id$"
#! file="Ravl/QMake/QMake.mk"

ifndef MAKEHOME
  MAKEHOME=.
endif

ifndef ARC
  ARC=$(shell $(MAKEHOME)/config.arc)#
endif
export ARC

SYSCONF:=$(MAKEHOME)/../../$(ARC)/bin/SysConf
MAKEDEFS:=perl -f $(MAKEHOME)/mkdefs.pl

ifndef PROCS
  PROCS=$(shell $(SYSCONF) -a )
endif
export PROCS

# Set default uses lib to auto?

ifdef USERBUILD
  export USERBUILD
endif
export ARC
export LOCALBIN := $(MAKEHOME)/../../$(ARC)/bin
export DPATH:=$(shell basename $(shell 'pwd'))
export TARGET

ifndef PROJECT_OUT
  PROJECT_OUT := $(shell 'pwd')
else
ifeq ($(PROJECT_OUT),"")
  PROJECT_OUT := $(shell 'pwd')
endif
endif

export PROJECT_OUT

# Setup default build target.

TARGET=fullbuild

include $(MAKEHOME)/config.$(ARC)
NOVAR=1
include $(MAKEHOME)/Dirs.mk

# The following is for loging only.
-include $(QCWD)/defs.mk

USELOGOUT = $(MAKEHOME)/logs/usage

VPATH=$(QCWD)

ifdef QMAKE_INFO
  export QMAKE_INFO
endif

.PHONY : all depend opt qopt qdb debug develop qd check distclean \
 clean pack unpack org help isdep srcp srcd org orgopt orgdebug chead \
 lib_info defs mdoc notes qc qcheck src mirror srcinst doconly log \
 fulldoc fullcheck fullsrc fulltest fullbuild shared

##################################
# Do makes.

MAKEFLAGS += --no-print-directory -r $(PAR_MAKE)

# Where commands are prefixed by 'q' frozen dependancies are used.
# NB. Frozen dependancies can only be used where  normal make has 
#  successfully built ALL the depenacies for that directories, this
#  can be done using the target depend.

# Make with dependancies

ifdef MIRROR
all: mirror
else
 ifdef CIMSG
all: ci
 else
  ifdef VAR
all: novar
  else
all: check
  endif
 endif
endif
allns: all

############################
# Compilation targets.

src:
	$(SMAKEMO) src_all NOINCDEFS=1 TARGET=src_all 

novar: log
	$(SMAKEMD) fullbuild TARGET=fullbuild  

opt: log 
	$(SMAKEMD) fullbuild VAR=opt TARGET=fullbuild  

shared: log 
	$(SMAKEMD) fullbuild VAR=shared TARGET=fullbuild  

debug: log
	$(SMAKEMD) fullbuild VAR=debug TARGET=fullbuild  

debugall: log
	$(SMAKEMD) fullbuild VAR=debug BASE_VAR=debug TARGET=fullbuild  

check: log
	$(SMAKEMD) fullbuild VAR=check TARGET=fullbuild  

purify: log
	$(SMAKEMD) purifybuild VAR=debug PROCS=1 TARGET=purifybuild  

prof: log
	$(SMAKEMD) fullbuild VAR=prof TARGET=fullbuild  

gprof: log
	$(SMAKEMD) fullbuild VAR=gprof TARGET=fullbuild  

chead:
	$(SMAKEMD) cheadbuild FULLCHECKING=1 TARGET=cheadbuild  


test: src log
	@if [ ! -d $(INST_TESTBIN) ] ; then \
	  $(MKDIR) $(INST_TESTBIN); \
	fi 
	@if [ ! -d $(INST_TESTLOG) ] ; then \
	  $(MKDIR) $(INST_TESTLOG); \
	fi 
	$(SHOWIT)touch $(INST_TESTDB); \
	if $(MAKEMD) VAR=check testbuild FULLCHECKING=1 NOEXEBUILD=1 TARGET=testbuild ; then true ; \
	else \
	  echo "test: Failed to do inital build for test. "; \
	  exit 1 ; \
	fi ; \
	if $(MAKEMD) VAR=check testbuild FULLCHECKING=1 TARGET=testbuild ; then true ; \
	else \
	  echo "test: Failed to do executable build. " ; \
	  exit 1 ; \
	fi ; \
	sort -u -o$(INST_TESTDB) $(INST_TESTDB); \
	$(LOCALBIN)/Validate -v $(INST_TEST)

retest:
	$(SHOWIT)sort -u -o$(INST_TESTDB) $(INST_TESTDB) ; \
	$(LOCALBIN)/Validate -v $(INST_TEST)	



###########################################################
# Utilities for eevsspsoft


# PROJECT_OUT=/vol/vssp/local/develop/amma

FULLBUILDSRC := BASE_VAR=none FULLCHECKING=1

# The last INST_LIBDEF is because the calling PROJECT_OUT may not
# be the one we using.

FULLBUILDFLAGS = NOCHECKOUT=1  $(FULLBUILDSRC)

# Check out latest version.

fullsrc:	
	$(SMAKEMO) NOINCDEFS=1 src_all $(FULLBUILDSRC)

fullhdr:	
	$(SMAKEMO) NOINCDEFS=1 src_all $(FULLBUILDFLAGS)

# Build check of latest version.

fullcheck:	
	$(SMAKEMD) fullbuild VAR=check $(FULLBUILDFLAGS) TARGET=fullbuild

fulldebug:	
	$(SMAKEMD) fullbuild VAR=debug $(FULLBUILDFLAGS) TARGET=fullbuild

fullopt:	
	$(SMAKEMD) fullbuild VAR=opt $(FULLBUILDFLAGS) TARGET=fullbuild

fullinfo:	
	$(SMAKEMO) info VAR=check $(FULLBUILDFLAGS)

fullclean:
	$(SMAKECL) clean VAR=check $(FULLBUILDFLAGS) TARGET=clean

libbuild: 
	$(SMAKEMD) libbuild  $(FULLBUILDFLAGS) TARGET=libbuild

# Build amma.
# Proceeds as follows:
#  1-Src the latest version of the source.
#  2-Compile all libraries.
#  3-Build executables.
#  4-Build documentation

fullbuild:
	$(SHOWIT)if [ ! -d $(PROJECT_OUT)/log ] ; then \
	  $(MKDIR) $(PROJECT_OUT)/log; \
	fi ; \
	if $(MAKEMO) $(FULLBUILDFLAGS) src_all NOINCDEFS=1 ; then true; \
        else \
	  echo "QMAKE: Installation of header files failed. " ; \
	  exit 1; \
        fi ; \
	if $(MAKEMD) $(FULLBUILDFLAGS) libbuild VAR=check TARGET=libbuild NOEXEBUILD=1 ; then true; \
        else \
	  echo "QMAKE: Check library build failed. " ; \
	  exit 1; \
        fi ; \
	echo "Check build complete. " ; \
	if $(MAKEMD) $(FULLBUILDFLAGS) libbuild VAR=debug TARGET=libbuild NOEXEBUILD=1 ; then true; \
        else \
	  echo "QMAKE: Debug library build failed. " ; \
	  exit 1; \
        fi ; \
	if $(MAKEMD) $(FULLBUILDFLAGS) libbuild VAR=opt TARGET=libbuild NOEXEBUILD=1 ; then true; \
        else \
	  echo "QMAKE: opt library build failed. " ; \
	  exit 1; \
        fi ; \
	if $(MAKEMD) $(FULLBUILDFLAGS) fullbuild VAR=opt TARGET=fullbuild  ; then true; \
        else \
	  echo "QMAKE: executable build failed. " ; \
	  exit 1; \
        fi ; \
	echo "Building documentation. " ; \
	$(MAKEDC) $(FULLBUILDFLAGS) doc 

fullshared:
	if $(MAKEMD) $(FULLBUILDFLAGS) fullbuild VAR=shared TARGET=fullbuild NOEXEBUILD=1 ; then true; \
        else \
	  echo "QMAKE: Shared library build failed. " ; \
	  exit 1; \
        fi ; \

fulldoc:
	$(SMAKEDC) doc    $(FULLBUILDFLAGS)

# Make a defs.mk file automaticly.

mkdef:
	$(MAKEDEFS) -i .

##########################################################
# Util

mirror:
	$(SMAKEUT) mirror

srcinst:
	$(SMAKEUT) srcinst

listoff:
	$(SMAKEUT) listoff

listco:
	$(SMAKEUT) listco

listfix:
	$(SMAKEUT) listfix

listlocked:
	$(SMAKEUT) listlocked

################################
# Admin

clean:
	$(SMAKECL) clean TARGET=clean

cleanlib:
	$(SMAKECL) cleanlib TARGET=cleanlib

cleandep:
	$(SMAKECL) cleandep TARGET=cleandep

optclean:
	$(SMAKECL) clean VAR=opt TARGET=clean

dbclean:
	$(SMAKECL) clean VAR=debug TARGET=clean

chkclean:
	$(SMAKECL) clean VAR=check TARGET=clean

lib_info:
	$(SMAKEMO) lib_info

info:
	$(SMAKEMO) info

udchangelog:
	$(SMAKEUT) udchangelog

co:
	$(SMAKEUT) co

ci:
	$(SMAKEUT) ci

pack:
	$(SMAKEMO) NOINCDEFS=1 pack

unpack:
	$(SMAKEMO) NOINCDEFS=1 unpack

################################
# Documentation.

# Install files, build documentation
doc: src
	$(SMAKEDC) doc

# Just install files.
docinit: src
	$(SMAKEDC) docinit

# Just build documentation
redoc:
	$(SMAKEDC) doc


###################################
# Clean up.

distclean: chkclean dbclean optclean
	$(SHOWIT)echo "--- Deleting " $(BUILDDIR); \
	if [ -d $(BUILDDIR) ] ; then \
	  $(RM) -rf $(BUILDDIR) ; \
	fi ; \
	echo "--- Deleting " $(INST_INCLUDE) ; \
	if [ -d $(INST_INCLUDE) ] ; then \
	  $(RM) -rf $(INST_INCLUDE) ; \
	fi ; \
	echo "--- Deleting " $(INST_LIBDEF) ; \
	if [ -d $(INST_LIBDEF)  ] ; then \
	  $(RM) -rf $(INST_LIBDEF) ; \
	fi ; \
	echo "--- Deleting " $(INST_DOC) ; \
	if [ -d $(INST_DOC)  ] ; then \
	  $(RM) -rf $(INST_DOC) ; \
	fi ; \
	echo "--- Deleting " $(INST_DEPEND) ; \
	if [ -d $(INST_DEPEND) ] ; then \
	  $(RM) -rf $(INST_DEPEND) ; \
	fi ;

###############################################
# Logging

log: 
	@if [ -w $(USELOGOUT) ] ; then \
	  echo "$(USER):" `date`":$(USESLIBS) $(PROGLIBS):$(NESTED)" >> $(USELOGOUT) ;\
	fi ;

###############################################
# Misc

$(MAKEHOME)/config.$(ARC) :
	@true

$(MAKEHOME)/Dirs.mk :
	@true

$(MAKEHOME)/GlobalMake :
	@true

$(MAKEHOME)/MainDep.mk :
	@true

###############################################
# Help

notes:
	@$(PAGER) $(MAKEHOME)/Notes.txt

defs:
	@$(PAGER) $(MAKEHOME)/Defs.txt

#$(QCWD)/defs.mk:
#	@echo "Checking out defs.mk "; \
#	co -q -u $(QCWD)/defs.mk 

include $(MAKEHOME)/rcs.mk

.DEFAULT help:
	@$(PAGER) $(MAKEHOME)/Help.txt