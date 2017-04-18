###############################################################################
#
# Makefile Options:
#
#  make [clean] PRODUCT=<product> [BUILD=<build>]
#
# Copyright radisys Limited
#
###############################################################################

TOP = $(shell pwd)/../../..
include $(TOP)/makefrags/products.mk

TARGET_NAME = tenpin

ifeq ($(HARDWARE),hbs2-4)
    TPM = null_tpm
    STACK = strongswan
    X509 = openssl
endif
ifeq ($(HARDWARE),generic)
    TPM = null_tpm
    STACK = strongswan
    X509 = openssl
endif

SRC_DIRS = stack/$(STACK) hardware/tpm/$(TPM) x509/$(X509)

LIB_DEPS = \
  $(TOP)/libs/messaging/obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)/libthreeway-messaging \
  $(TOP)/libs/common/mib-common/obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)/libRadisys-mib-common \
  $(TOP)/libs/common/mobnet/obj/$(HARDWARE)/$(BUILD)/libthreeway-mobnet \
  $(TOP)/libs/common/comms/obj/$(HARDWARE)/$(BUILD)/libthreeway-comms \
  $(TOP)/libs/common/system/obj/$(HARDWARE)/$(BUILD)/libthreeway-system
  #$(TOP)/libs/common/clog/obj/$(HARDWARE)/$(BUILD)/libRadisys-clog \

SYSTEM_LIBS = pthread

ifeq ($(X509),openssl)
	ifeq ($(HARDWARE),hbs2-4)
	ifeq ($(BUILD),arm-none-linux-gnueabi)
	LIB_DEPS_PREBUILT = \
							  $(TOP)/thirdparty/openssl-0.9.8/openssl-0.9.8r/lib/libcrypto
	endif
	ifeq ($(BUILD),mipsel-unknown-linux-gnu)
	LIB_DEPS_PREBUILT = \
							  $(TOP)/thirdparty/openssl-0.9.8/openssl-0.9.8rm/lib/libcrypto
	endif
endif
ifeq ($(HARDWARE),generic)
	LIB_DEPS_PREBUILT = \
							  $(TOP)/thirdparty/openssl-0.9.8/openssl-0.9.8rl/lib/libcrypto
	endif
endif

INCLUDE_PATHS = \
  $(TOP)/apps \
  $(TOP)/apps/fap/tenpin \
  $(TOP)/apps/fap/tenpin/stack/$(STACK) \
  $(TOP)/apps/fap/tenpin/hardware/tpm/$(TPM) \
  $(TOP)/apps/fap/tenpin/x509/$(X509) \
  $(TOP)/libs/messaging/transport

ifeq ($(X509),openssl)
ifeq ($(HARDWARE),hbs2-4)
ifeq ($(BUILD),arm-none-linux-gnueabi)
INCLUDE_PATHS += \
  $(TOP)/thirdparty/openssl-0.9.8/openssl-0.9.8r/include
endif
ifeq ($(BUILD),mipsel-unknown-linux-gnu)
INCLUDE_PATHS += \
  $(TOP)/thirdparty/openssl-0.9.8/openssl-0.9.8rm/include
endif
endif
endif

ifeq ($(X509),openssl)
ifeq ($(HARDWARE),generic)
INCLUDE_PATHS += \
  $(TOP)/thirdparty/openssl-0.9.8/openssl-0.9.8r/include
endif
endif

CPPFLAGS += -DRADISYS_UMTS_FAP -DIPNETAPP -DPICASSO_RADISYS_PORT
CPPFLAGS += -DIP_PORT_LAS -DIPNET -DIPIKE -DIPEAP -DIPCRYPTO -DIPFIREWALL -Werror
#ifeq ($(BUILD),bfin-uclinux-2008)
#CPPFLAGS += -DIP_TARGET_BLACKFIN -DIP_LITTLE_ENDIAN
#else
CPPFLAGS += -DIP_TARGET_I386 -DIP_LITTLE_ENDIAN
#endif

#BFIN_UCLINUX_APP_STACK_SIZE = 0x80000

include $(TOP)/makefrags/application.mk
