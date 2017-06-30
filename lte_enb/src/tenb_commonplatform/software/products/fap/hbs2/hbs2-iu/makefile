###############################################################################
#
# Copyright Radisys Limited
#
###############################################################################

# List of directories to run 'make'.
#DIRS?= libs/common/mib-common \
       apps/fap/post-office \
       apps/fap/tenpin \
       apps/fap/ike-tunnel-ind \
       apps/fap/ntp-client/Ver2 \
       apps/fap/management/tr069-v2 \
       apps/fap/management/oam \
       apps/fap/management/mib-firkler \
       apps/fap/management/oam-sm \
       apps/utilities/cli

DIRS?= libs/common/mib-common \
       libs/mib-core \
       libs/messaging \
       apps/fap/post-office \
       apps/fap/tenpin \
       apps/fap/ike-tunnel-ind \
       apps/fap/management/tr069-v2 \
       apps/fap/management/oam \
       apps/fap/management/oam-sm \
       apps/fap/management/mib-firkler \
       apps/utilities/cli \
       apps/fap/management/update

# Define the product.  BUILD will get set accordingly by products.mk.
#PRODUCT = hbs2-iu
#PRODUCT = generic
PRODUCT = $(PRODUCT)


# Path to 'software' directory.
TOP = ../../../..

include $(TOP)/makefrags/product.mk
