##############################################################################
#
# Makefile fragment for building a unittest shared library under Linux.
#
# Makefiles using this fragment in general only have to set:
#
#   TARGET_NAME
#
# There are a number of optional variables that can be set in the makefile
# including this fragment, including:
#
#   TOP           - Points to the top level 'software' directory.
#                   Defaults to ../../..
#   LIBS          - Additional libraries to link against.
#   INCLUDE_PATHS - Additional include paths.
#   CPPFLAGS      - Additional C PreProcessor flags.
#   CXXFLAGS      - Additional C++ flags.
#   CFLAGS        - Additional C flags.
#   LDFLAGS       - Additional linker flags.
#
##############################################################################

# Normally we build unit tests for i686-linux.
BUILD ?= i686-linux
HARDWARE ?= generic

include $(TOP)/makefrags/products.mk

ifneq ($(BUILD),i686-linux)
ifneq ($(BUILD),i686-pc-cygwin)
  $(error Unittest libraries can only be built for i686-linux or i686-pc-cygwin)
endif
endif

# All unittest libraries get put in the same place so we can dynamically load them.
INSTALL_DIR = $(TOP)/test/unittest/unittest-libs/$(HARDWARE)/$(BUILD)

newall: build
	cd $(TOP)/test/unittest/unittest-runner && $(MAKE)
	@mkdir -p $(INSTALL_DIR)
	cp $(TARGET_DIR)/*.so $(INSTALL_DIR)

run: newall
	cd $(TOP)/test/unittest/unittest-runner && $(UTWRAPPER) obj/$(HARDWARE)/$(BUILD)/unittest-runner ../unittest-libs/$(HARDWARE)/$(BUILD)/ $(TARGET_NAME)

INCLUDE_PATHS := \
  $(TOP)/libs/common/include \
  $(TOP)/libs/common \
  $(TOP)/libs \
  $(TOP)/libs/common/mib-common/obj/$(PRODUCT)/generic/generic \
  $(TOP)/libs/nas/include \
  $(TOP)/libs/nas/include/lib-system \
  $(TOP)/libs/nas/include/lib-comms \
  $(TOP)/libs/nas/include/lib-24008 \
  $(TOP)/libs/nas/lib-24008/codegen \
  $(TOP)/libs/nas/include/lib-25331 \
  $(TOP)/libs/nas/lib-25331/generated/i686-linux \
  $(TOP)/thirdparty/encodix/Common \
  $(TOP)/thirdparty/oss/include/i686-linux/ \
  $(INCLUDE_PATHS)

LIB_DEPS_PREBUILT = cppunit pthread dl

include $(TOP)/makefrags/sharedlibrary.mk

