include ../common/rsys_fancy.mak
include ../common/env.mak

CLR1=$(COLOR_RED)
CLR2=$(REVERT_COLOR)

REM_DIR=$(ROOT_DIR)/src/lteremapp/
OAM_DIR=$(ROOT_DIR)/src/tenb_commonplatform
REM_LIB=$(LIB_ROOT)/

ifneq ($(wildcard $(REM_DIR)), )
rem_lib:
	cd $(REM_DIR)/src; $(MAKE) clean;$(MAKE) PRODUCT=hbs2-iu HARDWARE=hbs2-4 BUILD=$(BUILD)
endif

ifeq ($(OAM_ENABLE),YES)
ifneq ($(wildcard $(OAM_DIR)), )
ifneq ($(wildcard $(REM_DIR)), )
rem:
	$(Q)echo -e " Root dir =  $(ROOT_DIR),Rem dir =  $(REM_DIR)"
	$(Q)echo -e "$(CLR1)Building REM ... $(CLR2)"
	$(Q)cd $(REM_DIR);$(MAKE) PRODUCT=hbs2-iu HARDWARE=hbs2-4 BUILD=$(BUILD)

clean:
	@echo "************* CLEANING REM **************"
	$(Q)cd $(REM_DIR);$(MAKE) clean PRODUCT=hbs2-iu HARDWARE=hbs2-4 BUILD=$(BUILD)
else
# Dummy target to satisfy make
rem:
# Dummy target to satisfy make
clean:
endif
else
# Dummy target to satisfy make
rem:
# Dummy target to satisfy make
clean:
endif
else
# Dummy target to satisfy make
rem:
# Dummy target to satisfy make
clean:
endif

