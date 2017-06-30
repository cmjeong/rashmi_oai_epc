###############################################################################
#
# hbs2-rrc makefile
#
# Copyright Radisys Limited
#
###############################################################################

# List of directories to run 'make'.
DIRS?= libs/common/mib-common \
       apps/fap/bitpeel \
       apps/fap/post-office \
       apps/fap/management/mib-firkler \
       apps/fap/management/oam \
       apps/fap/management/oam-snmp \
       apps/fap/management/oam-rem \
       apps/fap/management/update \
       apps/fap/l1 \
       apps/fap/l2 \
       apps/fap/rrc \
       apps/fap/rrm \
       apps/fap/watchdogd \
       apps/fap/post-kernel-boot-actions \
       apps/fap/clogd \
       apps/utilities/the-proto-prof \
       apps/utilities/fap-flash \
       apps/utilities/validate-ip-configuration \
       apps/utilities/logtail \
       apps/utilities/cli

# Define the product.  BUILD will get set accordingly by products.mk.
PRODUCT = hbs2-rrc

# Path to 'software' directory.
TOP = $(shell pwd)/../../../..

include $(TOP)/makefrags/product.mk
