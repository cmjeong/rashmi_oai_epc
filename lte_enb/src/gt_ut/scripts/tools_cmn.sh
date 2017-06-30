#!/bin/sh

# location of the build directory
#MOD_PREFIX=jf
FIN_LOG_FILE=./${MOD_PREFIX}_gt_report.log
BUILD_PATH=..
MAKEFILE=./${MOD_PREFIX}_test.mak
CLEAN=clean
GT_REPORT_FILE=report_${MOD_PREFIX}_ut.xml

# for purecov
MAKE_PURECOV=purecov_ut
PURECOV_PCV=${MOD_PREFIX}_ut.pcv

#for purify
MAKE_PURIFY=purify_ut
PURIFY_LOG=${MOD_PREFIX}_purify.log
PURIFY_PV=${MOD_PREFIX}_ut.pv
EXE=${MOD_PREFIX}_ut

# log file where the summary of the tools run will be captured

PURECOV_PATH=/usr/ccpu/rational/releases/purecov.i386_linux2.7.0.0.0-008/scripts

exe_and_log ()
{
   $@ 2>&1 | tee -a $FIN_LOG_FILE
}
