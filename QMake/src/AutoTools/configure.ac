#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])

AC_INIT([QMake], [1.9.0], [quickmake-support@lists.sourceforge.net], [QMake], [http://www.ee.surrey.ac.uk/CVSSP/Ravl/RavlDoc/share/doc/Ravl/Auto/Develop/Tree/Ravl.QMake.html])

# This file is part of QMake, Quick Make System
# Copyright (C) 2011-16, University of Surrey
# This code may be redistributed under the terms of the GNU General
# Public License (GPL). See the gpl.licence file for details or
# see http://www.gnu.org/copyleft/gpl.html

dnl Include standard QMake autoconf macros
m4_include([./AcMacros/QM_CHOOSE_GETCWD])
m4_include([./AcMacros/QM_CHOOSE_RPATH])
m4_include([./AcMacros/QM_CK_COMPILE_CK_LIB])
m4_include([./AcMacros/QM_CK_BESPOKE_CK_LIB])
m4_include([./AcMacros/QM_CK_PREREQ_STATE])
m4_include([./AcMacros/QM_CHECK_CC_LIB])
m4_include([./AcMacros/QM_Debug_Fn])
m4_include([./AcMacros/QM_DEFINE_ALL_EXTLIBS])
m4_include([./AcMacros/QM_DEFINE_EXTLIB_CC])
m4_include([./AcMacros/QM_DEFINE_EXTLIB_PC])
m4_include([./AcMacros/QM_DEFINE_VIRTUAL_EXTLIB])
m4_include([./AcMacros/QM_DEFINE_EXTLIB_BESPOKE])
m4_include([./AcMacros/QM_DEFINE_EXTLIB_BESPOKE_CC])
m4_include([./AcMacros/QM_RESOURCE_BASIC_SWITCHES])
m4_include([./AcMacros/QM_RESOURCE_CC_SWITCHES])
m4_include([./AcMacros/QM_FINISH_DEFINE])
m4_include([./AcMacros/QM_LOCATE_KEY_TOOLS])
m4_include([./AcMacros/QM_LOCATE_LD])
m4_include([./AcMacros/QM_LOCATE_MAKE])
m4_include([./AcMacros/QM_LOCATE_QMAKE])
m4_include([./AcMacros/QM_LOCATE_QMAKE_DEPS])
m4_include([./AcMacros/QM_PROCESS_EXTLIBS])
m4_include([./AcMacros/QM_READ_USER_ENV])
m4_include([./AcMacros/QM_SET_ARC])
m4_include([./AcMacros/QM_SET_ARCHIVER_ARFLAGS])
m4_include([./AcMacros/QM_SET_COMPILER_CFLAGS])
m4_include([./AcMacros/QM_SET_COMPILER_CCFLAGS])
m4_include([./AcMacros/QM_ID_GNU_COMPILER])
m4_include([./AcMacros/QM_SET_LINKER_LDFLAGS])
m4_include([./AcMacros/QM_SET_MAKE_MAKEFLAGS])
m4_include([./AcMacros/QM_SET_SHAREDEXT])

dnl#JFi:ToDo-Check for ver 5 of Perl as a requirement

# Main body of configure script

# First determine the current platform
AC_CANONICAL_HOST


dnl It would be good to enable the following code, however _AC_... aren't 
dnl generally available macros and may disappear/change in differing versions
dnl of autotools so its best not to rely on them. If only there was a supported
dnl means of doing this.. (you can check for the preprocessor (as we do, above)
dnl but not all of the calls that _AC_INCLUDES_DEFAULT_REQUIREMENTS expands to
dnl are individually available.
dnl
dnl#      Cause the checks for the C pre-processor and default headers to be done now
dnl#      (This can prevent multiple calls within the script's body)
dnl       _AC_INCLUDES_DEFAULT_REQUIREMENTS


dnl# We want to default to installing to /usr rather than /usr/local
dnl# This is primarily because of a number of distributions that do not
dnl# come configured to use /usr/local/lib as a default library location.
AC_PREFIX_DEFAULT([/usr])


# Locate the tools needed to run this script (shell utils, compilers etc.)
QM_LOCATE_KEY_TOOLS

dnl Allow for output of the command-line switches initialised by the
dnl QM_LOCATE_KEY_TOOLS macro. 
AC_SUBST([GET_CWD])
AC_SUBST([with_rpath])


# Now record the correct switches for the individual tools in use
QM_SET_COMPILER_CFLAGS
QM_SET_COMPILER_CCFLAGS
QM_SET_LINKER_LDFLAGS
QM_SET_ARCHIVER_ARFLAGS
QM_SET_MAKE_MAKEFLAGS




# Check for programs needed by QMake
QM_LOCATE_QMAKE_DEPS



# Define all external libs known to QMake
#
QM_DEFINE_ALL_EXTLIBS()



# Now determine which external libraries are actually available
#
LibsToProcess=$KnownLibs
QM_PROCESS_EXTLIBS()

# OpenCV is a special case, we need to post-process its include path
if test x$use_OpenCV=xpresent
then
   # Add extra include directory for OpenCV so as to prevent any confusion over
   # the inclusion of opencv/xx.h (previously, Ravl code included the OpenCV
   # headers by specifying the opencv sub-dir; this was at odds with what the
   # .pc file was set up to expect the user to do). To combat this, we add the
   # parent directory (of the opencv directory) to the include path.
   OpenCV_CFLAGS=`echo "$OpenCV_CFLAGS " | $SED '/\(-I@<:@^ @:>@*\)\/opencv /s//\1\/opencv \1 /g'`
   dnl sed command is '/\(-I[^ ]*\)\/opencv /s//\1\/opencv \1 /g'
fi


# Check for programs that are regarded as RESOURCES

AC_PATH_PROG([SWIG],[swig])
AS_IF([test "X$SWIG" != X], [ RESOURCES="$RESOURCES Swig"])
AC_SUBST([SWIG])

# We already know we have Perl as that is a pre-requisite of QMake that we
# have already checked for. So, add it to RESOURCES
RESOURCES="$RESOURCES PERL"


# Process Architecture specific issues
#
# Set the QMake ARC type...
QM_SET_ARC
AC_SUBST([ARC])
#
# Set the shared library extension. (In a perfect world this
# would be set by AC_PROG_CC as OBJEXT and EXEEXT are. Sadly
# we do not live there.)
QM_SET_SHAREDEXT
AC_SUBST([SHAREDEXT])
#
# Enable processor specific functionality...`
trace 3 Host OS is $host_os, CPU is $host_cpu
case X$host_cpu in
   Xi386* | Xi486* | Xi586* | Xi686* )
                 trace 3 Non-SSE 32-bit x86
                 # Case currently empty but we need to add some further 
                 # testing to see if SSE is actually usable (some platforms
                 # come back as i686 when in fact they are running on a P4
dnl#JFi:ToDo-Improve SSE processing + add cmd-line switches for user control
                 ;;
   Xi786* )
                 # i786 equates to Intel P4. Even Athlon XPs come back as i686
                 # from config.guess/sub

                 trace 3 Enabling SSE2 support as we are on a P4.
                 RESOURCES="$RESOURCES USE_SSE2"
                 ;;
   Xx86_64* )  
                 # 64 bit 'x86' architecture - includes both AMD & Intel but
                 # not Itanium

                 trace 3 64-bit x86 supports SSE2
                 RESOURCES="$RESOURCES USE_SSE2"
                 ;;
   * )
                 # Catch all case for tracing purposes
                 trace 3 Non-x86 chip \($host_cpu\) so no SSE support
esac






#
# Create proforma Config.QMake.in
#

# Create initial, empty file
echo > ./Config.QMake.in

echo \# QMake configuration file - regenerate using configure >> ./Config.QMake.in
echo >> ./Config.QMake.in


echo \# Installation target directory tree for QMake Project files >> ./Config.QMake.in
echo QMAKE_PROJECT_DEST=@QMAKE_PROJECT_DEST@/QMake/Projects >> ./Config.QMake.in
echo \# Needed to allow a project build before QMake has been installed. >> ./Config.QMake.in
echo \# Normally, we would read/install the project files using the >> ./Config.QMake.in
echo \# QMAKE_PROJECTS variable. However, the value of this varies >> ./Config.QMake.in
echo \# between an installed copy of QMake and an interim version used >> ./Config.QMake.in
echo \# when building both the project and QMake in one step. To combat >> ./Config.QMake.in
echo \# this, we set QMAKE_PROJECT_DEST to the final, concrete, location. >> ./Config.QMake.in
echo >> ./Config.QMake.in
# Now set up QMAKE_PROJECT_DEST..
dnl#
dnl# First declate it as an output variable
AC_SUBST(QMAKE_PROJECT_DEST)
#
# Set it to the contents of datadir
QMAKE_PROJECT_DEST=$datadir
#
# Now make sure it is fully expanded (datadir will often be set to a value
# referencing $prefix; we need to make sure we know the fully expanded value)
eval Expansion="$QMAKE_PROJECT_DEST"
while ( test $Expansion != "$QMAKE_PROJECT_DEST")
do
   QMAKE_PROJECT_DEST="$Expansion"
   eval Expansion="$QMAKE_PROJECT_DEST"
done
#
# QMAKE_PROJECT_DEST should now be the fully expanded location of datadir



# Define location of compilers and helper programs for build system
echo >> ./Config.QMake.in
echo \# List of programs required for the build process >> ./Config.QMake.in
echo >> ./Config.QMake.in
echo AR=@AR@ >> ./Config.QMake.in
echo AWK=@AWK@ >> ./Config.QMake.in
echo CC=@CC@ >> ./Config.QMake.in
echo CCACHE=@CCACHE@ >> ./Config.QMake.in
echo CP=@CP@ >> ./Config.QMake.in
echo CPP=@CPP@ >> ./Config.QMake.in
echo CHGRP=@CHGRP@ >> ./Config.QMake.in
echo CHMOD=@CHMOD@ >> ./Config.QMake.in
echo CHOWN=@CHOWN@ >> ./Config.QMake.in
echo CXX=@CXX@ >> ./Config.QMake.in
echo CXXCPP=@CXXCPP@ >> ./Config.QMake.in
echo EXPR=@EXPR@ >> ./Config.QMake.in
echo GET_CWD=@GET_CWD@ >> ./Config.QMake.in
echo GREP=@GREP@ >> ./Config.QMake.in
# A null INSTALL means QMake will sort one out for itself so if we do not know
# of an installer, we should not set INSTALL in the config file.
if ( test "x$INSTALL" != x )
then
  echo INSTALL=$INSTALL >> ./Config.QMake.in
  # Not using @-enclosed substitution variable as the configure substitution
  # logic is hard-coded to use ac_INSTALL not INSTALL and we may have altered
  # the value held in INSTALL
fi
echo INSTALL_DATA=@INSTALL_DATA@ >> ./Config.QMake.in
echo INSTALL_PROGRAM=@INSTALL_PROGRAM@ >> ./Config.QMake.in
echo LD=@LD@ >> ./Config.QMake.in
echo LEX=@LEX@ >> ./Config.QMake.in
echo LEXLIB=@LEXLIB@ >> ./Config.QMake.in
echo LN_S=@LN_S@ >> ./Config.QMake.in
echo MAKE=@MAKE@ >> ./Config.QMake.in
echo MKDIR_P=$MKDIR_P >> ./Config.QMake.in
# Not using @-enclosed substitution variable as the configure substitution
# logic is hard-coded to use ac_MKDIR_P not MKDIR_P and we may have altered
# the value held in MKDIR_P
echo NVCC=@NVCC@ >> ./Config.QMake.in
echo PERL=@PERL@ >> ./Config.QMake.in
echo PKG_CONFIG=@PKG_CONFIG@ >> ./Config.QMake.in
echo QMAKE_PAGER=@PAGER@ >> ./Config.QMake.in
echo RANLIB=@RANLIB@ >> ./Config.QMake.in
echo RM=@RM@ >> ./Config.QMake.in
echo SED=@SED@ >> ./Config.QMake.in
echo SORT=@SORT@ >> ./Config.QMake.in
echo SYNC=@SYNC@ >> ./Config.QMake.in
echo TOUCH=@TOUCH@ >> ./Config.QMake.in
echo TR=@TR@ >> ./Config.QMake.in
echo XARGS=@XARGS@ >> ./Config.QMake.in
echo YACC=@YACC@ >> ./Config.QMake.in
echo >> ./Config.QMake.in


# Compiler, etc. switches
echo >> ./Config.QMake.in
echo \# Relevant QMake build process flags >> ./Config.QMake.in
echo >> ./Config.QMake.in
echo \# Declare platform architecture >> ./Config.QMake.in
echo ARC=@ARC@ >> ./Config.QMake.in
echo >> ./Config.QMake.in
echo \# File extension for shared libraries >> ./Config.QMake.in
echo SHAREDEXT=@SHAREDEXT@ >> ./Config.QMake.in
echo >> ./Config.QMake.in
echo >> ./Config.QMake.in
echo \# Flags for the C compiler >> ./Config.QMake.in
echo >> ./Config.QMake.in
echo \# User specified at configure time >> ./Config.QMake.in
echo QMAKE_CFLAGS=@CONFIGURE_CFLAGS@ >> ./Config.QMake.in
echo >> ./Config.QMake.in
echo \# QMake compiler settings >> ./Config.QMake.in
echo COMPILER_ANSI_CFLAGS=@COMPILER_ANSI_CFLAGS@ >> ./Config.QMake.in
# Only output the standards flags if the variable has explicitly been set (this
# allows QMake to distinguish between the standard needing no compiler flag (the
# variable is set but null) and not being available (variable is not set at
# all).
if ( test "X${COMPILER_C90_CFLAGS-Unset}" != XUnset )
then
   echo COMPILER_C90_CFLAGS=@COMPILER_C90_CFLAGS@ >> ./Config.QMake.in
fi
if ( test "X${COMPILER_C95_CFLAGS-Unset}" != XUnset )
then
   echo COMPILER_C95_CFLAGS=@COMPILER_C95_CFLAGS@ >> ./Config.QMake.in
fi
if ( test "X${COMPILER_C99_CFLAGS-Unset}" != XUnset )
then
   echo COMPILER_C99_CFLAGS=@COMPILER_C99_CFLAGS@ >> ./Config.QMake.in
fi
if ( test "X${COMPILER_C11_CFLAGS-Unset}" != XUnset )
then
   echo COMPILER_C11_CFLAGS=@COMPILER_C11_CFLAGS@ >> ./Config.QMake.in
fi
echo COMPILER_DEBUG_CFLAGS=@COMPILER_DEBUG_CFLAGS@ >> ./Config.QMake.in
echo COMPILER_GPROF_CFLAGS=@COMPILER_GPROF_CFLAGS@ >> ./Config.QMake.in
echo COMPILER_NON_OPT_CFLAGS=@COMPILER_NON_OPT_CFLAGS@ >> ./Config.QMake.in
echo COMPILER_OPT_CFLAGS=@COMPILER_OPT_CFLAGS@ >> ./Config.QMake.in
echo COMPILER_PROF_CFLAGS=@COMPILER_PROF_CFLAGS@ >> ./Config.QMake.in
echo COMPILER_SHARED_CFLAGS=@COMPILER_SHARED_CFLAGS@ >> ./Config.QMake.in
echo COMPILER_SPECIFIC_CFLAGS=@COMPILER_SPECIFIC_CFLAGS@ >> ./Config.QMake.in
echo >> ./Config.QMake.in
echo \# Flags for the C++ compiler >> ./Config.QMake.in
echo >> ./Config.QMake.in
echo \# User specified at configure time >> ./Config.QMake.in
echo QMAKE_CCFLAGS=@CONFIGURE_CCFLAGS@ >> ./Config.QMake.in
echo >> ./Config.QMake.in
echo \# QMake compiler settings >> ./Config.QMake.in
echo COMPILER_ANSI_CCFLAGS=@COMPILER_ANSI_CCFLAGS@ >> ./Config.QMake.in
# Only output the standards flags if the variable has explicitly been set (this
# allows QMake to distinguish between the standard needing no compiler flag (the
# variable is set but null) and not being available (variable is not set at
# all).
if ( test "X${COMPILER_CC98_CCFLAGS-Unset}" != XUnset )
then
   echo COMPILER_CC98_CCFLAGS=@COMPILER_CC98_CCFLAGS@ >> ./Config.QMake.in
fi
if ( test "X${COMPILER_CC03_CCFLAGS-Unset}" != XUnset )
then
   echo COMPILER_CC03_CCFLAGS=@COMPILER_CC03_CCFLAGS@ >> ./Config.QMake.in
fi
if ( test "X${COMPILER_CC11_CCFLAGS-Unset}" != XUnset )
then
   echo COMPILER_CC11_CCFLAGS=@COMPILER_CC11_CCFLAGS@ >> ./Config.QMake.in
fi
if ( test "X${COMPILER_CC14_CCFLAGS-Unset}" != XUnset )
then
   echo COMPILER_CC14_CCFLAGS=@COMPILER_CC14_CCFLAGS@ >> ./Config.QMake.in
fi
echo COMPILER_DEBUG_CCFLAGS=@COMPILER_DEBUG_CCFLAGS@ >> ./Config.QMake.in
echo COMPILER_GPROF_CCFLAGS=@COMPILER_GPROF_CCFLAGS@ >> ./Config.QMake.in
echo COMPILER_NON_OPT_CCFLAGS=@COMPILER_NON_OPT_CCFLAGS@ >> ./Config.QMake.in
echo COMPILER_OPT_CCFLAGS=@COMPILER_OPT_CCFLAGS@ >> ./Config.QMake.in
echo COMPILER_PROF_CCFLAGS=@COMPILER_PROF_CCFLAGS@ >> ./Config.QMake.in
echo COMPILER_SHARED_CCFLAGS=@COMPILER_SHARED_CCFLAGS@ >> ./Config.QMake.in
echo COMPILER_SPECIFIC_CCFLAGS=@COMPILER_SPECIFIC_CCFLAGS@ >> ./Config.QMake.in
echo >> ./Config.QMake.in
echo >> ./Config.QMake.in
echo \# Flags for the linker >> ./Config.QMake.in
echo >> ./Config.QMake.in
echo \# User specified at configure time >> ./Config.QMake.in
echo QMAKE_LDFLAGS=@LDFLAGS@ >> ./Config.QMake.in
echo >> ./Config.QMake.in
echo \# Take any user specified LDFLAGS as applying to libraries as well >> ./Config.QMake.in
echo QMAKE_LDLIBFLAGS=@LDFLAGS@ >> ./Config.QMake.in
echo >> ./Config.QMake.in
echo \# General QMake linker settings >> ./Config.QMake.in
echo LINKER_SPECIFIC_LDFLAGS=@LINKER_SPECIFIC_LDFLAGS@ >> ./Config.QMake.in
echo LINKER_SHARED_LDFLAGS=@LINKER_SHARED_LDFLAGS@ >> ./Config.QMake.in
echo >> ./Config.QMake.in
echo \# Linker settings for QMake libraries >> ./Config.QMake.in
echo LINKER_SPECIFIC_LDLIBFLAGS=@LINKER_SPECIFIC_LDLIBFLAGS@ >> ./Config.QMake.in
echo LINKER_SHARED_LDLIBFLAGS=@LINKER_SHARED_LDLIBFLAGS@ >> ./Config.QMake.in
echo >> ./Config.QMake.in
echo \# Specific linker functionality >> ./Config.QMake.in
echo >> ./Config.QMake.in
echo LINKER_LIBPATHSWITCH=@LINKER_LIBPATHSWITCH@ >> ./Config.QMake.in
echo USE_LIBPATHSWITCH=@with_rpath@ >> ./Config.QMake.in
echo LINKER_SET_SONAME=@LINKER_SET_SONAME@ >> ./Config.QMake.in
echo LINKER_UNDEFSYMB=@LINKER_UNDEFSYMB@ >> ./Config.QMake.in
echo >> ./Config.QMake.in
echo >> ./Config.QMake.in
# Only write out NVCC flags if we have found the compiler driver
if ( test x$use_NVCC = xpresent )
then
   echo \# CUDA compiler settings >> ./Config.QMake.in
   echo >> ./Config.QMake.in
   echo \# User specified at configure time >> ./Config.QMake.in
   echo QMAKE_NVCCFLAGS=@CONFIGURE_NVCCFLAGS@ >> ./Config.QMake.in
   echo >> ./Config.QMake.in
   echo \# Settings determined for current combination of C++ and CUDA compilers >> ./Config.QMake.in
   echo QMAKE_NVCC_TARGS=@DEFAULT_NVCC_TARGS@ >> ./Config.QMake.in
   echo NVCC_ANSI_NVCCFLAGS=@NVCC_ANSI_NVCCFLAGS@ >> ./Config.QMake.in
   echo NVCC_CC98_NVCCFLAGS=@NVCC_CC98_NVCCFLAGS@ >> ./Config.QMake.in
   echo NVCC_CC03_NVCCFLAGS=@NVCC_CC03_NVCCFLAGS@ >> ./Config.QMake.in
   echo NVCC_CC11_NVCCFLAGS=@NVCC_CC11_NVCCFLAGS@ >> ./Config.QMake.in
   echo NVCC_CC14_NVCCFLAGS=@NVCC_CC14_NVCCFLAGS@ >> ./Config.QMake.in
   echo NVCC_DEBUG_NVCCFLAGS=@NVCC_DEBUG_NVCCFLAGS@ >> ./Config.QMake.in
   echo NVCC_GPROF_NVCCFLAGS=@NVCC_GPROF_NVCCFLAGS@ >> ./Config.QMake.in
   echo NVCC_NON_OPT_NVCCFLAGS=@NVCC_NON_OPT_NVCCFLAGS@ >> ./Config.QMake.in
   echo NVCC_OPT_NVCCFLAGS=@NVCC_OPT_NVCCFLAGS@ >> ./Config.QMake.in
   echo NVCC_PROF_NVCCFLAGS=@NVCC_PROF_NVCCFLAGS@ >> ./Config.QMake.in
   echo NVCC_SHARED_NVCCFLAGS=@NVCC_SHARED_NVCCFLAGS@ >> ./Config.QMake.in
   echo NVCC_SPECIFIC_NVCCFLAGS=@NVCC_SPECIFIC_NVCCFLAGS@ >> ./Config.QMake.in
   echo >> ./Config.QMake.in
   echo >> ./Config.QMake.in
   dnl Declare variables for output that have not already been declared
   AC_SUBST([CONFIGURE_NVCCFLAGS])
   AC_SUBST([DEFAULT_NVCC_TARGS])
fi
echo \# Flags for the archiver >> ./Config.QMake.in
echo \# >> ./Config.QMake.in
echo \# No user supplied ARFLAGS are accepted owing to the nature of how ar works >> ./Config.QMake.in
echo >> ./Config.QMake.in
echo AR_SPECIFIC_ARFLAGS=@AR_SPECIFIC_ARFLAGS@ >> ./Config.QMake.in
echo >> ./Config.QMake.in
echo >> ./Config.QMake.in
echo \# Flags for make >> ./Config.QMake.in
echo >> ./Config.QMake.in
echo \# User specified at configure time >> ./Config.QMake.in
echo QMAKE_MAKEFLAGS=@MAKEFLAGS@ >> ./Config.QMake.in
echo >> ./Config.QMake.in
echo \# General QMake make settings >> ./Config.QMake.in
echo MAKE_SPECIFIC_MAKEFLAGS=@MAKE_SPECIFIC_MAKEFLAGS@ >> ./Config.QMake.in
echo >> ./Config.QMake.in
echo MAKE_SPECIFIC_PARALLEL=@MAKE_SPECIFIC_PARALLEL@ >> ./Config.QMake.in
echo >> ./Config.QMake.in
echo >> ./Config.QMake.in
echo >> ./Config.QMake.in


# Known external libraries and resource programs
echo \# External resources >> ./Config.QMake.in
echo >> ./Config.QMake.in
echo RESOURCES=@RESOURCES@ >> ./Config.QMake.in
AC_SUBST([RESOURCES])
echo >> ./Config.QMake.in

# Now output the location of the individual external libs. Calculate RESOURCES
# as we go (based on the libraries we can use)
#
echo \# Location details for external libraries >> ./Config.QMake.in
echo >> ./Config.QMake.in
trace 2 Calculating RESOURCES settings from library availability
trace 3 \(Initial value of RESOURCES "@<:@$RESOURCES@:>@"\)
for lib in $KnownLibs
do
   eval lib_enablement=\$use_${lib}
   case $lib_enablement in
    'blocked' | 'missing' )
                   TRACE_INDENT="     "
                   trace 3 ${lib} $lib_enablement
                   ;;
    'no' )
                   TRACE_INDENT="     "
                   trace 3 ${lib} discarded
                   ;;
    'check' | 'yes' )
                   trace 1 Assertion: --with-${lib} should not equal ${lib_enablement} here!
                   ;;
    'present' )
                   if ( test "$with_rpath" = 'Y' )
                   then
                      eval setting=\$${lib}_LIBS
                      setting=`echo $setting | $SED 's/-L *\(@<:@^ @:>@@<:@^ @:>@*\)/\$(LINKER_LIBPATHSWITCH)\1 -L\1/g'`
dnl                   # The sed command is actually:
dnl                   #    's/-L *\([^ ][^ ]*\)/\$(LINKER_LIBPATHSWITCH)\1 -L\1/g'
dnl                   # the square brackets having been substituted to prevent
dnl                   # m4 removing them. 
                      # The sed command looks for:
                      #
                      #        -L<optional spaces><something><space> 
                      # 
                      # if this pattern is found, each and every occurrence is
                      # replaced by the following:
                      #
                      #       $(LINKER_LIBPATHSWITCH)<something> -L<something>
                      #
                      # <something> being the substring found in the original
                      # fragment.
                      eval ${lib}_LIBS=\$setting
                   fi
                   TRACE_INDENT="     "
                   trace 3 RESOURCES+=${lib}
                   RESOURCES="$RESOURCES $lib"
                   # Put the placeholders into Config.QMake.in so we record the
                   # flags associated with the libraries that we can use
                   dnl If we ever extend the configure program to support
                   dnl Fortran, this section of code will need to output the
                   dnl requisite Fortran variables.

                   eval check=\$with_${lib}_check
                   if ( test x$check = xvirtual )
                   then
                      # For virtual packages, we need to output the settings
                      # associated with the pre-requisites. If we have a virtual
                      # package that the user has configured via pkg-config,
                      # this script will have already changed the check type so
                      # we do not need to consider that here.
                      #
                      # Start with empty definitions
                      cflags=""
                      ccflags=""
                      libs=""
                      eval prereqs=\$with_${lib}_prq
                      # For each pre-requisite of the package
                      for p in $prereqs
                      do
                         # If any C flags exist for the pre-requisite package
                         # include those
                         eval prereqcflags=\$${p}_CFLAGS
                         if ( test "X$prereqcflags" != X )
                         then
                            cflags="$cflags @${p}_CFLAGS@"
                         fi
                         # Include any C++ flags from the pre-requisite
                         eval prereqccflags=\$${p}_CCFLAGS
                         if ( test "X$prereqccflags" != X )
                         then
                            ccflags="$ccflags @${p}_CCFLAGS@"
                         fi
                         # Include any library flags from the pre-requisite
                         eval prereqlibs=\$${p}_LIBS
                         if ( test "X$prereqlibs" != X )
                         then
                            libs="$libs @${p}_LIBS@"
                         fi
                      done
                   else
                      # Always output a CFLAGS setting even if it is null
                      # <lib>_CFLAGS will already be declared as a substitution
                      # variable
                      cflags="@${lib}_CFLAGS@"
                      # If any C++ flags exist for the package, ensure that
                      # they output too.
                      eval ccflags=\$${lib}_CCFLAGS
                      if ( test "X$ccflags" != X )
                      then
                         ccflags="@${lib}_CCFLAGS@"
                      fi
                      # Always output a LIBS setting
                      # <lib>_LIBS will already be declared as a substitution
                      # variable
                      libs="@${lib}_LIBS@"
                   fi
                   # Now actually output the flags
                   #
                   # Always output a CFLAGS setting
                   echo ${lib}_CFLAGS=$cflags >> Config.QMake.in
                   # If any C++ flags exist for the package, ensure that
                   # they output too.
                   if ( test "X$ccflags" != X )
                   then
                      echo ${lib}_CCFLAGS=$ccflags >> Config.QMake.in
                   fi
                   # Always output a LIBS setting
                   echo ${lib}_LIBS=$libs >> Config.QMake.in
                   echo >> ./Config.QMake.in
                   ;;
   esac
done





dnl Create Makefiles and Config.QMake
AC_CONFIG_FILES([Config.QMake])
AC_CONFIG_FILES([Makefile:src/AutoTools/Makefile.in])
AC_CONFIG_FILES([Targets.QMake:src/AutoTools/Targets.QMake.in])
AC_OUTPUT
