include ../common/rsys_fancy.mak
include ../common/env.mak

OAM_ROOT=$(ROOT_DIR)/src/tenb_commonplatform/software
WATCHDOG_DIR=$(OAM_ROOT)/apps/fap/watchdogd
ifeq ($(PLTFRM),PAL)
PRODUCT_OPTION=generic
HARDWARE_OPTION=generic
else
PRODUCT_OPTION=hbs2-iu
HARDWARE_OPTION=hbs2-4
endif

ifeq ($(OAM_ENABLE), YES)
ifneq ($(wildcard $(OAM_ROOT)), )
# OAM is available in software
SMLLIB_PATH=$(OAM_ROOT)/apps/fap/management/oam-sm/obj/$(HARDWARE_OPTION)/$(BUILD)
MIBCOMMSLIB_PATH=$(OAM_ROOT)/libs/common/mib-common/obj/$(PRODUCT_OPTION)/$(HARDWARE_OPTION)/$(BUILD)
THREEWAY_COMMSLIB_PATH=$(OAM_ROOT)/libs/common/comms/obj/$(HARDWARE_OPTION)/$(BUILD)
THREEWAY_MSGLIB_PATH=$(OAM_ROOT)/libs/messaging/obj/$(PRODUCT_OPTION)/$(HARDWARE_OPTION)/$(BUILD)
THREEWAY_MOBNETLIB_PATH=$(OAM_ROOT)/libs/common/mobnet/obj/$(HARDWARE_OPTION)/$(BUILD)
THREEWAY_SYSTEMLIB_PATH=$(OAM_ROOT)/libs/common/system/obj/$(HARDWARE_OPTION)/$(BUILD)
THREEWAY_LIBS=$(OAM_ROOT)/libs/bin/threeway/$(PRODUCT_OPTION)/$(HARDWARE_OPTION)/$(BUILD)
OAM_LIB_MAKE_PATH=$(OAM_ROOT)/products/fap/hbs2/hbs2-iu/
BLD_LNX_OAM_LIB=lnx_sm_oam_lib
LNXMSLOPTS+= -ldl -L$(SMLLIB_PATH) -lsm  -L$(MIBCOMMSLIB_PATH) -lRadisys-mib-common \
    -L$(THREEWAY_COMMSLIB_PATH) -lthreeway-comms -L$(THREEWAY_MSGLIB_PATH) \
    -lthreeway-messaging -L$(THREEWAY_MOBNETLIB_PATH) -lthreeway-mobnet -L$(THREEWAY_LIBS)\
    -L$(THREEWAY_SYSTEMLIB_PATH) -lthreeway-system -lstdc++

#oam:watchdogd
oam:
#	@echo "************* OAM Build    ************** product = $(PRODUCT_OPTION)"
#@echo "Hardware= $(HARDWARE_OPTION build=$(BUILD_OPTION)")
	$(Q) ../common/autogenCompile.sh
	$(Q) mkdir -p ./oamlibs
	echo " distro PRODUCT=$(PRODUCT_OPTION) HARDWARE=$(HARDWARE_OPTION) BUILD=$(BUILD)"
	$(Q)cd $(OAM_LIB_MAKE_PATH);$(MAKE) distro PRODUCT=$(PRODUCT_OPTION) HARDWARE=$(HARDWARE_OPTION) BUILD=$(BUILD)
	$(Q)cp -rf $(OAM_ROOT)/libs/common/mib-common/obj/$(PRODUCT_OPTION)/$(HARDWARE_OPTION)/$(BUILD)/libRadisys-mib-common.so  ./oamlibs
	$(Q)cp -rf $(OAM_ROOT)/libs/common/mobnet/obj/$(HARDWARE_OPTION)/$(BUILD)/libthreeway-mobnet.so ./oamlibs
	$(Q)cp -rf $(OAM_ROOT)/libs/common/comms/obj/$(HARDWARE_OPTION)/$(BUILD)/libthreeway-comms.so  ./oamlibs
	$(Q)cp -rf $(OAM_ROOT)/libs/common/system/obj/$(HARDWARE_OPTION)/$(BUILD)/libthreeway-system.so ./oamlibs
	$(Q)cp -rf $(OAM_ROOT)/libs/messaging/obj/$(PRODUCT_OPTION)/$(HARDWARE_OPTION)/$(BUILD)/libthreeway-messaging.so ./oamlibs
	$(Q)cp -rf $(OAM_ROOT)/libs/mib-core/obj/$(PRODUCT_OPTION)/$(HARDWARE_OPTION)/$(BUILD)/libRadisys-mib-core.so ./oamlibs
	$(Q)cp -rf $(OAM_ROOT)/apps/fap/management/oam-sm/obj/$(HARDWARE_OPTION)/$(BUILD)/libsm.so ./oamlibs
	$(Q)cp -rf $(OAM_ROOT)/thirdparty/md5/obj/$(HARDWARE_OPTION)/$(BUILD)/libmd5.so ./oamlibs
	$(Q)cp -rf $(OAM_ROOT)/apps/fap/ike-tunnel-ind/obj/$(PRODUCT_OPTION)/$(HARDWARE_OPTION)/$(BUILD)/ike-tunnel-ind ./oamlibs
	$(Q)cp -rf $(OAM_ROOT)/apps/fap/post-office/obj/$(PRODUCT_OPTION)/$(HARDWARE_OPTION)/$(BUILD)/post-office ./oamlibs
	$(Q)cp -rf $(OAM_ROOT)/apps/fap/management/oam/obj/$(PRODUCT_OPTION)/$(HARDWARE_OPTION)/$(BUILD)/oam ./oamlibs
	$(Q)cp -rf $(OAM_ROOT)/apps/utilities/cli/obj/$(PRODUCT_OPTION)/$(HARDWARE_OPTION)/$(BUILD)/cli ./oamlibs
	$(Q)cp -rf $(OAM_ROOT)/apps/fap/tenpin/obj/$(PRODUCT_OPTION)/$(HARDWARE_OPTION)/$(BUILD)/tenpin ./oamlibs
	$(Q)cp -rf $(OAM_ROOT)/apps/fap/management/tr069-v2/obj/$(PRODUCT_OPTION)/$(HARDWARE_OPTION)/$(BUILD)/tr069-v2 ./oamlibs
	$(Q)cp -rf $(OAM_ROOT)/thirdparty/kb_getc/obj/$(HARDWARE_OPTION)/$(BUILD)/libkb_getc.so ./oamlibs

watchdogd:
	$(Q)echo "Building WATCHDOG ... "
	$(Q)cd $(WATCHDOG_DIR);$(MAKE) $(S) PRODUCT=generic HARDWARE=generic BUILD=$(BUILD) WATCHBSPPATH=$(BSPPATH);	 

clean:
	@echo -e "$(COLOR_RED)Cleaning OAM  $(REVERT_COLOR)"
	$(Q)cd $(OAM_LIB_MAKE_PATH); $(MAKE) clean PRODUCT=$(PRODUCT_OPTION) HARDWARE=$(HARDWARE_OPTION) BUILD=$(BUILD);

else
# OAM is not available in sources so there is nothing to be built.
# We will use the libraries packaged with the software
oam:
	echo -e "$(COLOR_RED)OAM is not available as source. Nothing to build.$(REVERT_COLOR)"

clean:
	echo -e "$(COLOR_RED)OAM is not available as source. Nothing to clean.$(REVERT_COLOR)"

endif
else
oam:
	echo -e "$(COLOR_RED)OAM is disabled. Nothing to make$(REVERT_COLOR)"

clean:
	echo -e "$(COLOR_RED)OAM is disabled. Nothing to clean$(REVERT_COLOR)"
endif

