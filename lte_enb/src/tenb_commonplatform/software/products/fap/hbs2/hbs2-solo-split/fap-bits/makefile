###############################################################################
#
# hbs2-solo-split (fap-bits) makefile
#
# Copyright Radisys Limited
#
###############################################################################

# The apps need to as per hbs2-sip product.
override PRODUCT = hbs2-sip
override HARDWARE = hbs2-3-5
override BUILD = bfin-uclinux-2008

# List of directories to run 'make'.
DIRS?= libs/common/mib-common \
       apps/fap/post-office \
       apps/fap/l1 \
       apps/fap/bitpeel \
       apps/fap/l2 \
       apps/fap/rrc \
       apps/fap/nas-ggsn \
       apps/fap/media/cs-user-plane \
       apps/fap/management/oam \
       apps/fap/management/oam-rem \
       apps/fap/management/update \
       apps/utilities/the-proto-prof \
       apps/utilities/fap-flash \
       apps/utilities/cli

# Path to 'software' directory.
TOP = $(shell pwd)/../../../../..

include $(TOP)/makefrags/product.mk
