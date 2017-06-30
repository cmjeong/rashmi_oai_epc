#********************************************************************20**
#
#       Name:   RSYS FANCY MAKE OUTOUT
#
#       Type:   Makefile
#
#       Desc:   To control fancy features in the build process
#
#
#       File:   rsys_fancy.mak
#
#       Sid:      rsys_fancy.mak@@/main/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:51:46 2016
#
#       Prg:    ag
#
#  
#********************************************************************21*/

#-----------------------------------------------------------------------
# FANCY STUFF... you can play around with this if you want to
COLOR_RED=\e[31m\e[1m
COLOR_GREEN=\e[32m\e[1m
COLOR_YELLOW=\e[33m\e[1m
COLOR_BLUE=\e[34m\e[1m
COLOR_MAG=\e[35m\e[1m
COLOR_CYAN=\e[36m\e[1m
REVERT_COLOR=\e[m

#-----------------------------------------------------------------------
# DO NOT EDIT THIS SECTION
ifeq ($(VERBOSE),YES)
export QUIET=
MK_QUIET=
else
export QUIET=@ 
MK_QUIET=-s # Make works in quite mode
endif

