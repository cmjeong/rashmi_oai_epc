###############################################################################
#
# Unit tests makefile
#
# Copyright Radisys Limited
#
###############################################################################

# List of directories to run 'make'.
# These are directories with unittest subdirectories.
DIRS = libs/common/mib-common \
       libs/messaging \
       libs/common/comms \
       libs/common/system \
       libs/mib-core \
       apps/fap/management/tr069-v2 \

# Define the product.  BUILD will get set accordingly by products.mk.
PRODUCT = test
HARDWARE = generic

# Path to 'software' directory.
TOP = $(shell pwd)/../..

include $(TOP)/makefrags/product.mk
