###############################################################################
#
# hbs2-factory makefile
#
# Copyright Radisys Limited
#
###############################################################################

# List of directories to run 'make'.
DIRS?= libs/common/mib-common \
       apps/fap/post-office \
       apps/fap/management/oam \
       apps/fap/management/mib-firkler \
       apps/fap/management/update \
       apps/fap/l1 \
       apps/fap/bitpeel \
       apps/fap/l2 \
       apps/fap/rrc \
       apps/fap/rrm \
       apps/fap/nas-core \
       apps/fap/nas-smsc \
       apps/fap/nas-hlr \
       apps/fap/nas-ggsn \
       apps/fap/media/cs-user-plane \
       apps/fap/tenpin \
       apps/fap/watchdogd \
       apps/utilities/the-proto-prof \
       apps/utilities/fap-flash \
       apps/utilities/cli \
       apps/fap/management/oam-rem \
       apps/fap/post-kernel-boot-actions \
       apps/test/nas-ggsn-ip-tunnel-v2

ifneq ($(HARDWARE),hbs2-4)
DIRS += apps/fap/sigverify
endif

# Define the product.  BUILD will get set accordingly by products.mk.
PRODUCT = hbs2-factory

# Path to 'software' directory.
TOP = $(shell pwd)/../../../..

include $(TOP)/makefrags/product.mk
