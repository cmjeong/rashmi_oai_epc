###############################################################################
#
# hbs2-solo-split (i686-bits) makefile
#
# Copyright Radisys Limited
#
###############################################################################

# The apps need to as per hbs2-sip product.
override PRODUCT = hbs2-sip
override HARDWARE = generic
override BUILD = i686-linux

# List of directories to run 'make'.
DIRS?= libs/common/mib-common \
       apps/fap/nas-core \
       apps/fap/nas-smsc \
       apps/fap/nas-hlr \
       apps/fap/rrc \
       apps/utilities/the-proto-prof \
       apps/utilities/cli

# Path to 'software' directory.
TOP = $(shell pwd)/../../../../..

include $(TOP)/makefrags/product.mk
