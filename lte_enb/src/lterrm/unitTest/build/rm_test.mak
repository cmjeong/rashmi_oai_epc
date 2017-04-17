#********************************************************************20**
#
#       Name:   Qcom Hexagon SSI Unit Test Makefile
#
#       Type:   makefile
#
#       Desc:   For compiling Hexagon SSI unit tests
#
#       Env:    Linux
#               do make help for targets
#
#       File:  qu_test.mak
#
#       Prg:   ag
#
#********************************************************************21*/

include ../../../gt_ut/rsys_fancy.mak

GTEST_DIR = ../../../gt_ut/gtest-1.7.0/include/
GTEST_LIB_PATH=../../../gt_ut/gtest-1.7.0/lib

# Where to find user code.
BASE_DIR = ../../..
SSI_DIR = ../../../mt_acc
CM_DIR = ../../../cm
RLOG_DIR = ../../../rlog
RRM_DIR = ../../src
TEST_DIR = ../../unitTest/testFiles
STUBS_DIR = ../stubs
OBJ_DIR = ./obj

MAKENAME=rm_test.mak

#normal build
LNXCC=g++

#purcov build
BINPACC=purecov_ut
PURECOV_PATH=/usr/ccpu/rational/releases/purecov.i386_linux2.7.0.0.0-008/scripts
PACC="$(PURECOV_PATH)/../purecov g++"

# purify
BINPURACC=purify_ut
PURIFY_PATH=/usr/ccpu/rational/releases/purify.i386_linux2.7.0.0.0-008
PURIFY_OUTPUT_FILE=rm_ut.pv
PURCC="$(PURIFY_PATH)/purify -log-file=rm_purify.log -view-file=$(PURIFY_OUTPUT_FILE) -windows=no --cache-dir=/tmp g++ -m32 -DUSE_PURE -DNOCONAVL"

OUTPUT_NAME="rm_ut"

# MTSS specific defines
ALL_L2_OPTS += -DSS \
               -DCMFILE_REORG_1 \
               -fPIC \
               -DANSI \
               -DSUNOS \
               -D_REENTRANT\
               -DSS_LINUX\
               -DSS_MT\
               -DSS_FLOAT\
               -DLONG_MSG\
               -DCMFILE_REORG_2\
               -DSS_M_PROTO_REGION\
               -DDEBUGNOEXIT\
               -DSLES9_PLUS\
               -DSS_DRVR_SUPPORT\
               -DSS_DATETIME_USEC\
               -DSS_LICENSE_CHECK\
               -DDEBUGP\
               -D__EXTENSIONS__\
               -DAPI_MAIN\
               -DGTEST_DONT_DEFINE_FAIL \
					-DRRM_ARP \
					-DRMU_LWLC \
					-DNOCONAVL \
					-DSS_MT_TMR \
					-DRM_INTF \
					-DGT_SUITE \
					-DRGM_TC \
					-DRG \
					-DLTEMAC_MIMO \
				   -DRLOG_ENABLE_TEXT_LOGGING	\
					-DTENB_MAX_UE_SUPPORTED=32 \
               -DDBG_MAC_RRM_PRB_PRINT \
			   -DLTE_ADV

TO_BE_TESTED_CPP = $(OBJ_DIR)/rm_admissioncontroller.o \
             $(OBJ_DIR)/rm_acb.o \
             $(OBJ_DIR)/rm_application.o\
             $(OBJ_DIR)/rm_cellmanager.o\
             $(OBJ_DIR)/rm_mmemanager.o\
             $(OBJ_DIR)/rm_outinterface.o\
             $(OBJ_DIR)/rm_radiobearercontroller.o\
             $(OBJ_DIR)/rm_rcmdrx.o\
             $(OBJ_DIR)/rm_rcmpcqi.o\
             $(OBJ_DIR)/rm_rcmsps.o\
             $(OBJ_DIR)/rm_resourceconfigmanager.o\
             $(OBJ_DIR)/rm_prbbasedadmissioncontroller.o\
             $(OBJ_DIR)/rm_prbreportcollector.o\
             $(OBJ_DIR)/rm_qcibasedadmissioncontroller.o\
             $(OBJ_DIR)/rm_rbadmissioncontroller.o\
             $(OBJ_DIR)/rm_schedulingrequestmgr.o\
             $(OBJ_DIR)/rm_uecontext.o\
             $(OBJ_DIR)/rm_uemanager.o\
             $(OBJ_DIR)/rm_utils.o \
             $(OBJ_DIR)/rm_preEmptableERABFinder.o\
             $(OBJ_DIR)/rm_prbcongestioncontroller.o\
             $(OBJ_DIR)/rm_rcmscell.o

TO_BE_TESTED_C = $(OBJ_DIR)/rm_ex_ms.o \
					  $(OBJ_DIR)/rm_lmm.o \
					  $(OBJ_DIR)/rm_ptli.o \
					  $(OBJ_DIR)/rm_ptmi.o \
					  $(OBJ_DIR)/rm_ptui.o 

TEST_FILES = $(OBJ_DIR)/test_rm_admissioncontroller.o \
             $(OBJ_DIR)/test_rm_prbreportcollector.o  \
             $(OBJ_DIR)/test_rm_prbbasedadmissioncontroller.o \
             $(OBJ_DIR)/test_rm_qcibasedadmissioncontroller.o \
             $(OBJ_DIR)/test_rm_rbadmissioncontroller.o\
             $(OBJ_DIR)/test_rm_cellmanager.o\
             $(OBJ_DIR)/test_rm_utils.o \
             $(OBJ_DIR)/test_rm_preemptableErabFinder.o \
             $(OBJ_DIR)/test_rm_application.o \
             $(OBJ_DIR)/test_rm_congestioncontroller.o \
             $(OBJ_DIR)/test_rm_uemanager.o


STUB_FILES = $(OBJ_DIR)/rmu_interface_hdl.o 

CM_FILES = $(OBJ_DIR)/rmu_pk.o \
           $(OBJ_DIR)/cm_bdy5.o \
           $(OBJ_DIR)/cm_mem.o \
           $(OBJ_DIR)/cm_gen.o \
           $(OBJ_DIR)/cm_lib.o \
			  $(OBJ_DIR)/cm_mblk.o\
           $(OBJ_DIR)/rmu_unpk.o \
           $(OBJ_DIR)/rgm.o 

RLOG_FILES = $(OBJ_DIR)/rl_rlog.o \
			    $(OBJ_DIR)/rl_common.o 


SSI_FILES = $(OBJ_DIR)/ss_pack.o \
				$(OBJ_DIR)/ss_gen.o \
				$(OBJ_DIR)/ss_mem.o \
				$(OBJ_DIR)/ss_task.o \
				$(OBJ_DIR)/ss_strm.o \
				$(OBJ_DIR)/mt_ss.o \
				$(OBJ_DIR)/ss_queue.o \
				$(OBJ_DIR)/ss_timer.o \
				$(OBJ_DIR)/ss_msg.o

TO_BE_TESTED_SRCS=$(patsubst %,-file=%,$(patsubst %.o,%.cpp, $(subst $(OUT_DIR_NAME)/,,$(TO_BE_TESTED_CPP))))
TO_BE_TESTED_SRCS +=$(patsubst %,-file=%,$(patsubst %.o,%.c, $(subst $(OUT_DIR_NAME)/,,$(TO_BE_TESTED_C))))


OBJ_FILES = $(TO_BE_TESTED_CPP) $(TEST_FILES) $(CM_FILES) $(STUB_FILES) $(SSI_FILES) $(TO_BE_TESTED_C) $(UTILS_FILES) $(RLOG_FILES)

INC_FILES = $(RRM_DIR)/*.h \
				$(SSI_DIR)/*.h \
				$(SSI_DIR)/*.x \
				$(CM_DIR)/*.h \
				$(CM_DIR)/*.x \
				$(RLOG_DIR)/*.h 


# TODO include other .h dependencies $(SSI_DIR)/*.h 
OUT_DIR_NAME=$(subst /,,$(subst .,,$(OBJ_DIR)))

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_DIR) $(ALL_L2_OPTS) -I$(RRM_DIR) -I$(SSI_DIR) -I$(TEST_DIR) \
				-I../stubs \
				-I$(RLOG_DIR) \
				-I$(CM_DIR)

# Flags passed to the C++ compiler.
CXXFLAGS += -g3 -Wall -Wextra -Wno-unused-parameter -pthread $(ALL_L2_OPTS) 

# Linux  unit test build-------------------------------------
ut:  $(OBJ_FILES) $(GTEST_LIB_PATH)/gtest_main.a
	$(QUIET) $(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $(OUTPUT_NAME)

# Linux purecov build-------------------------------------
$(BINPACC):
	@$(MAKE) $(MK_QUIET) -f $(MAKENAME) CXX=$(PACC)
	@./$(OUTPUT_NAME) --gtest_output=xml:./report_$(OUTPUT_NAME).xml
	@echo -e "$(COLOR_BLUE)"
	@$(PURECOV_PATH)/pc_summary $(TO_BE_TESTED_SRCS) ./$(OUTPUT_NAME).pcv
	@echo -e "$(REVERT_COLOR)"

# Linux purify acceptance test build-------------------------------------
$(BINPURACC):
	@$(MAKE) $(MK_QUIET) -f $(MAKENAME) CXX=$(PURCC)

help:
	@echo "Usage : make -f $(MAKENAME) <target>"
	@echo "<target> can be one of the below:"
	@echo "    help       - To display this help"
	@echo "    ut         - To build unit tests ($(OUTPUT_NAME))"
	@echo "    purecov_ut - To run purecov over the unit tests"
	@echo "    purify_ut  - To build unit tests binary ($(OUTPUT_NAME)) with purify"
	@echo "    clean      - To remove all object files and binaries created"

clean :
	rm -f $(OUTPUT_NAME) $(OBJ_DIR)/*.o 

$(TO_BE_TESTED_CPP): $(OBJ_DIR)/%.o: $(INC_FILES) $(RRM_DIR)/%.cpp
	@echo -e "Compiling $(COLOR_GREEN) $(RSYS_QCOM_DIR)/src/$(patsubst %.o,%.cpp, $(subst $(OUT_DIR_NAME),,$@)) $(REVERT_COLOR)..."
	$(QUIET) $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(RRM_DIR)/$(patsubst %.o,%.cpp, $(subst $(OUT_DIR_NAME),,$@)) -o $@

$(TEST_FILES): $(OBJ_DIR)/%.o: $(INC_FILES) $(TEST_DIR)/%.cpp
	@echo -e "Compiling $(COLOR_GREEN) $(TEST_DIR)/$(patsubst %.o,%.cpp, $(subst $(OUT_DIR_NAME),,$@)) $(REVERT_COLOR)..."
	$(QUIET) $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(TEST_DIR)/$(patsubst %.o,%.cpp, $(subst $(OUT_DIR_NAME),,$@)) -o $@

$(STUB_FILES): $(OBJ_DIR)/%.o: $(INC_FILES) $(STUBS_DIR)/%.cpp
	@echo -e "Compiling $(COLOR_GREEN) $(STUBS_DIR)/$(patsubst %.o,%.cpp, $(subst $(OUT_DIR_NAME),,$@)) $(REVERT_COLOR)..."
	$(QUIET) $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(STUBS_DIR)/$(patsubst %.o,%.cpp, $(subst $(OUT_DIR_NAME),,$@)) -o $@

$(TO_BE_TESTED_C): $(OBJ_DIR)/%.o: $(INC_FILES) $(RRM_DIR)/%.c
	@echo -e "Compiling $(COLOR_GREEN) $(RRM_DIR)/$(patsubst %.o,%.c, $(subst $(OUT_DIR_NAME),,$@)) $(REVERT_COLOR)..."
	$(QUIET) $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(RRM_DIR)/$(patsubst %.o,%.c, $(subst $(OUT_DIR_NAME),,$@)) -o $@

$(CM_FILES): $(OBJ_DIR)/%.o: $(INC_FILES) $(CM_DIR)/%.c
	@echo -e "Compiling $(COLOR_GREEN) $(CM_DIR)/$(patsubst %.o,%.c, $(subst $(OUT_DIR_NAME),,$@)) $(REVERT_COLOR)..."
	$(QUIET) $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(CM_DIR)/$(patsubst %.o,%.c, $(subst $(OUT_DIR_NAME),,$@)) -o $@

$(SSI_FILES): $(OBJ_DIR)/%.o: $(INC_FILES) $(SSI_DIR)/%.c
	@echo -e "Compiling $(COLOR_GREEN) $(SSI_DIR)/$(patsubst %.o,%.c, $(subst $(OUT_DIR_NAME),,$@)) $(REVERT_COLOR)..."
	$(QUIET) $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(SSI_DIR)/$(patsubst %.o,%.c, $(subst $(OUT_DIR_NAME),,$@)) -o $@

$(RLOG_FILES): $(OBJ_DIR)/%.o: $(INC_FILES) $(RLOG_DIR)/%.c
	@echo -e "Compiling $(COLOR_GREEN) $(RLOG_DIR)/$(patsubst %.o,%.c, $(subst $(OUT_DIR_NAME),,$@)) $(REVERT_COLOR)..."
	$(QUIET) $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(RLOG_DIR)/$(patsubst %.o,%.c, $(subst $(OUT_DIR_NAME),,$@)) -o $@
