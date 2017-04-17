###############################################################################
#
# pc-iu makefile
#
# make [clean|distro]
#
# Copyright Radisys Limited
#
###############################################################################

# List of directories to run 'make'.
DIRS ?= libs/common/mib-common \
        apps/fap/bitpeel \
        apps/fap/post-office \
        apps/fap/sigverify \
        apps/fap/tenpin \
        apps/fap/ike-tunnel-ind \
        apps/fap/management/oam-rem \
        apps/fap/management/service-api \
        apps/fap/management/mib-firkler \
        apps/fap/rrc \
        apps/fap/iu \
        apps/fap/media/cs-user-plane \
        apps/fap/media/ps-user-plane \
        apps/fap/ntp-client/Ver2 \
        apps/fap/watchdogd \
        apps/fap/lockcon \
        apps/fap/serialport \
        apps/fap/gps \
        apps/utilities/the-proto-prof \
        apps/utilities/cli \
        apps/utilities/validate-ip-configuration

# didn't build out the box
#        apps/fap/management/oam
#        apps/fap/management/tr069
#        apps/fap/management/tr069-v2
#        apps/fap/management/update
#        apps/fap/l1
#        apps/fap/l2
#        apps/fap/rrm
#        apps/fap/post-kernel-boot-actions
#        apps/utilities/fap-flash

# Define the product.  BUILD will get set accordingly by products.mk.
PRODUCT = pc-iu

# Path to 'software' directory.
TOP = ../..

include $(TOP)/makefrags/product.mk
