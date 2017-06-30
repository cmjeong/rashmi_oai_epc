###############################################################################
#
# hbs2-sip makefile
#
# Copyright (C) Radisys Limited
#
###############################################################################

# List of directories to run 'make'.
DIRS?= libs/common/mib-common \
       apps/fap/post-office \
       apps/fap/management/oam \
       apps/fap/management/mib-firkler \
       apps/fap/management/update \
       apps/fap/l1 \
       apps/fap/clogd \
       apps/fap/bitpeel \
       apps/fap/l2 \
       apps/fap/rrc \
       apps/fap/rrm \
       apps/fap/nas-core \
       apps/fap/nas-smsc \
       apps/fap/nas-hlr \
       apps/fap/nas-ggsn \
       apps/fap/media/cs-user-plane \
       apps/fap/watchdogd \
       apps/fap/post-kernel-boot-actions \
       apps/utilities/the-proto-prof \
       apps/utilities/logtail \
       apps/utilities/cli \
       apps/fap/management/oam-rem \
       apps/utilities/validate-ip-configuration \
       apps/test/nas-ggsn-ip-tunnel-v2

ifneq ($(HARDWARE), hbs2-4)
DIRS +=apps/utilities/fap-flash \
       apps/utilities/l1-test
endif

# Define the product.  BUILD will get set accordingly by products.mk.
PRODUCT = hbs2-sip

# Path to 'software' directory.
TOP = $(shell pwd)/../../../..

include $(TOP)/makefrags/product.mk
