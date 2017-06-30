#********************************************************************20**
#
#       Name:   LTE UE Simulator Sample Application
#
#       Type:   make file
#
#       Desc:   Compile, assemble and link product software for
#               various configurations. Further comments are
#               embedded in the file. 
#
#               This file supports a variety of environments and
#               build targets. The default build target will be the
#               portable target for the Linu 2.4.x with GNU C(gcc)
#
#       Env:    Linux 2.4.x with GNU C (gcc)
#       Env:    Cavium  OCTEON-SDK  (mipsisa64-octeon-elf-gcc)
#
#               BUILD TARGETS:
#
#               clean            remove all object files
#   
#       File:  ue_stack.mak
#
#
#       Prg:   rbabu
#
#********************************************************************21*/
#=======================================================================

#-----------------------------------------------------------------------
# macro for output file name and makefile name
#
#OCTEON_ROOT=/usr/local/Cavium_Networks/1.9.0/OCTEON-SDK
OCTEON_ROOT=/usr/local/Cavium_Networks/OCTEON-SDK
MATCHED_MODEL=OCTEON_CN56XX
ROOT=uesim
SY_DIR=.
YS_DIR=../ltecl
MACHINE=BIT64
STOPTS=

OUTNAME=$(ROOT)

#-----------------------------------------------------------------------
# macros for td specific options
#

# MTSS defines
MTOPTS=-DSS -DSS_MT -DCONRD -UNOFILESYS
MTOPTS1=-DSS -DSS_MT -DCONRD -DNOFILESYS -DSS_DBLK_FREE_RTN

#cavium includes
OBJ_DIR=.
CVMX_CONFIG_DIR=../cavsdk/config
CVMX_INC=-I$(OCTEON_ROOT)/target/include -I$(CVMX_CONFIG_DIR)
CFLAGS_GLOBAL += $(CVMX_INC)
CFLAGS_GLOBAL += $(OCTEON_CPPFLAGS_GLOBAL_ADD)

#cavium defines
#  application config check and rules

CVMX_CONFIG = ../cavsdk/config/cvmx-config.h
CVMX_OTHER_CONFIGS := ../cavsdk/config/*-config.h
CVMX_OTHER_CONFIGS := $(shell echo $(CVMX_OTHER_CONFIGS) | sed 's/config\/cvmx-config.h//')

$(CVMX_CONFIG): $(CVMX_OTHER_CONFIGS)
	cvmx-config $(CVMX_OTHER_CONFIGS)

#  special rule to re-compile if important environment variables change
MATCH=${findstring DUSE_RUNTIME_MODEL_CHECKS=1, ${OCTEON_CPPFLAGS_GLOBAL_ADD}}
ifeq (${MATCH}, DUSE_RUNTIME_MODEL_CHECKS=1)
#  We are using runtime model detection, so use "runtime" as model to avoid
#    a re-compile if only OCTEON_MODEL used for simulation changes
MADE_WITH_OCTEON_MODEL = "runtime"
else
MADE_WITH_OCTEON_MODEL = $(OCTEON_MODEL)
endif
#  set special filename for target and change any spaces in it to commas
MADE_WITH = $(shell echo "$(OBJ_DIR)/made_with-OCTEON_MODEL=$(MADE_WITH_OCTEON_MODEL)=-OCTEON_CPPFLAGS_GLOBAL_ADD=$(OCTEON_CPPFLAGS_GLOBAL_ADD)=." | sed 's/\ /,/g')

# Add profile-feedback flags.
ifdef FDO_PASS
ifeq ($(FDO_PASS), 1)
CFLAGS_GLOBAL += -fprofile-generate
LDFLAGS_GLOBAL += -fprofile-generate
else # 1
ifeq ($(FDO_PASS), 2)
CFLAGS_GLOBAL += -fprofile-use
LDFLAGS_GLOBAL += -fprofile-use
else # 2
$(error FDO_PASS should either be 1 or 2)
endif # 2
endif # 1
endif # FDO_PASS

ifdef OCTEON_DISABLE_BACKTRACE
CFLAGS_GLOBAL += -fno-asynchronous-unwind-tables -DOCTEON_DISABLE_BACKTRACE
endif

ifndef OCTEON_TARGET
  OCTEON_TARGET=cvmx_64
endif

ifeq (${BLDENV},cav_e2e_acc_n32)
  OCTEON_TARGET=cvmx_n32
endif


SUPPORTED_TARGETS=linux_64 linux_n32 linux_uclibc linux_o32 cvmx_n32 cvmx_64
ifeq ($(findstring $(OCTEON_TARGET), $(SUPPORTED_TARGETS)),)
    ${error Invalid value for OCTEON_TARGET. Supported values: ${SUPPORTED_TARGETS}}
endif

ifeq (${OCTEON_TARGET},linux_64)
    PREFIX=-linux_64
    CFLAGS_GLOBAL += -DOCTEON_TARGET=${OCTEON_TARGET} -mabi=64 -march=octeon -msoft-float -Dmain=appmain
    ASFLAGS_GLOBAL += -DOCTEON_TARGET=${OCTEON_TARGET} -mabi=64 -march=octeon -msoft-float -Dmain=appmain
    LDFLAGS_GLOBAL += -mabi=64 -static -lrt -Xlinker -T -Xlinker $(OCTEON_ROOT)/target/lib/cvmx-shared-linux.ld
else # linux_64
ifeq (${OCTEON_TARGET},linux_n32)
    PREFIX=-linux_n32
    CFLAGS_GLOBAL += -DOCTEON_TARGET=${OCTEON_TARGET} -mabi=n32 -march=octeon -msoft-float -Dmain=appmain
    ASFLAGS_GLOBAL += -DOCTEON_TARGET=${OCTEON_TARGET} -mabi=n32 -march=octeon -msoft-float -Dmain=appmain
    LDFLAGS_GLOBAL += -mabi=n32 -static -lrt -Xlinker -T -Xlinker $(OCTEON_ROOT)/target/lib/cvmx-shared-linux-n32.ld
else # linux_n32
ifeq (${OCTEON_TARGET},linux_uclibc)
    PREFIX=-linux_uclibc
    CFLAGS_GLOBAL += -DOCTEON_TARGET=${OCTEON_TARGET} -muclibc -march=octeon -msoft-float -Dmain=appmain
    ASFLAGS_GLOBAL += -DOCTEON_TARGET=${OCTEON_TARGET} -muclibc -march=octeon -msoft-float -Dmain=appmain
    LDFLAGS_GLOBAL += -muclibc -static -lrt -Xlinker -T -Xlinker $(OCTEON_ROOT)/target/lib/cvmx-shared-linux-n32.ld
else # linux_uclibc
ifeq (${OCTEON_TARGET},linux_o32)
    PREFIX=-linux_o32
    CFLAGS_GLOBAL += -DOCTEON_TARGET=${OCTEON_TARGET} -mabi=32 -march=octeon -msoft-float -Dmain=appmain
    ASFLAGS_GLOBAL += -DOCTEON_TARGET=${OCTEON_TARGET} -mabi=32 -march=octeon -msoft-float -Dmain=appmain
    LDFLAGS_GLOBAL += -mabi=32 -static -lrt -Xlinker -T -Xlinker $(OCTEON_ROOT)/target/lib/cvmx-shared-linux-o32.ld
else # linux_o32
ifeq (${OCTEON_TARGET},cvmx_n32)
    CFLAGS_GLOBAL += -DOCTEON_TARGET=cvmx_n32 -mabi=n32
    ASFLAGS_GLOBAL += -DOCTEON_TARGET=cvmx_n32 -mabi=n32
    LDFLAGS_GLOBAL += -mabi=n32
    PREFIX=-cvmx_n32
else # cvmx_n32
ifeq (${OCTEON_TARGET},cvmx_64)
    CFLAGS_GLOBAL += -DOCTEON_TARGET=cvmx_64
    ASFLAGS_GLOBAL += -DOCTEON_TARGET=cvmx_64
else # cvmx_64
    ${error Invalid value for OCTEON_TARGET. Supported values: ${SUPPORTED_TARGETS}}
endif # cvmx_64
endif # cvmx_n32
endif # linux_o32
endif # linux_uclibc
endif # linux_n32
endif # linux_64

CFLAGS_GLOBAL += -DOCTEON_MODEL=$(MATCHED_MODEL)

ifeq (${MATCHED_MODEL},OCTEON_CN56XX)
CFLAGS_GLOBAL += -DBOARD_OCTEON56XX
endif

CVMXOPTS += $(CFLAGS_GLOBAL)

## UE stack compilation options details:
# ENB_PERF_MEAS     : enable for Uu Perf and Uu Perf with Pcap Setup.
# UESIM_ENABLE_PCAP : Enable for Pcap in Both Uu performance setup without core
#                     network contact and with pcaplib and e2e Setup with pcaplib.
# ENB_PERF_UL_DATA  : Enable only for Uu Perf .
#                     For Uu Perf with Pcap we need to enable UESIM_ENABLE_PCAP, 
#                     ENB_PERF_MEAS flags and disable ENB_PERF_UL_DATA flag.   
# LTE_LNX_AFFINITY: Enable to assign a dedicated cpu core for a system thread. 

CMENBPERFOPTS= -DRG -DSS_TICKS_SEC=100 -DCMFILE_REORG_1 -DCMFILE_REORG_2 \
          -DSS_PERF -UNO_ERRCLS -DDEBUGP -UNOERRCHK -URG_DEBUG -DTFU_UPGRADE -UTFU_TDD -DLTE_ADV_TFU\
          -USTOP_UL -DTFU_VER_2 -DLCTFU -DLTE_ENB_PERF -UCM_PASN_DBG -DSS_DATETIME_USEC\
          -ULTE_START_UL_DL_DATA -DENB_PERF_MEAS -ULTE_LNX_AFFINITY -DYS_PAL_PERF_MEAS\
          -DUESIM_ENABLE_PCAP -DENB_PERF_UL_DATA -DLTEMAC_SPS
           
CMENBE2EOPTS= -DRG -DSS_TICKS_SEC=100 -DCMFILE_REORG_1 -DCMFILE_REORG_2 -DMULTI_UE_ATTACH\
          -DSS_PERF -UNO_ERRCLS -DDEBUGP -UNOERRCHK -URG_DEBUG -DTFU_UPGRADE -UTFU_TDD -DLTE_ADV_TFU\
          -USTOP_UL -DTFU_VER_2 -DLCTFU -DLTE_ENB_PERF -UCM_PASN_DBG \
          -ULTE_START_UL_DL_DATA -UENB_PERF_MEAS -UUESIM_TRIGGER_DRB_EST -DUE_RAD_CAP \
          -UUESIM_ENABLE_PCAP -UENB_PERF_UL_DATA -DCNE_UESIM_COMMON_SUBNET -UTA_NEW -DSI_NEW -ULTE_HO_SUPPORT \
			 -UTRACKING_AREA_UPDATE -DTOTAL_ENB -DLTERRC_REL9 -DLTEMAC_MIMO -DLTEMAC_SPS

CMENBE2EPERFOPTS= -DRG -DSS_TICKS_SEC=100 -DCMFILE_REORG_1 -DCMFILE_REORG_2 \
          -DSS_PERF -UNO_ERRCLS -DDEBUGP -UNOERRCHK -URG_DEBUG -DTFU_UPGRADE -UTFU_TDD -DLTE_ADV_TFU\
          -DTFU_VER_2 -DLCTFU -UCM_PASN_DBG \
          -DLTE_E2E_PERF_MEAS -UUE_SUPPORT_RLC_UM_MODE -DLTEMAC_SPS

# The options below are used to pass on to the actual product compilations
# Just this one variable is passed for individual compilations and hence
# all the needed options are added from various other defined option macros

#ALL PAL layer options
TFUOPTS=-DTFU_VER_2 -UTFU_TDD -DLCTFU -DTFU_UPGRADE -DLTE_ADV_TFU
TFOPTS=-DTF $(TFUOPTS) -DDL_STS -UTTI_PROC -URLC_STATUS_GEN -UUL_PROC

#-----------------------------------------------------------------------
# macros for sw and include directories
#

CODEPATH=.
MT_DIR=../mt
MT_SE_DIR=../mtse
CM_DIR=../cm
TF_DIR=../ltecl
UE_DIR=../lteue

MTLIB_DIR=.
CMLIB_DIR=.
UELIB_DIR=.
TFLIB_DIR=.

F8API_DIR=$(IO_DIR)/F8API
CRYPT_DIR=$(IO_DIR)/CRYPTAPI
#set the path for Pico compilation
CROSSDIR=$(IO_DIR)/picolib-1.6.4
#export PICO_CROSS_LIBROOT=$(PWD)/$(CROSSDIR)


BLD_LNX_CM_OBJS=$(SY_DIR)/liblnxcm.a
BLD_LNX_SS_OBJS=$(SY_DIR)/liblnxmt.a
BLD_LNX_UE_PERF_OBJS=$(SY_DIR)/liblnxperfue.a
BLD_LNX_UE_E2EPERF_OBJS=$(SY_DIR)/liblnxe2eperfue.a
BLD_LNX_UE_E2E_OBJS=$(SY_DIR)/liblnxe2eue.a
BLD_LNX_TF_OBJS=$(SY_DIR)/liblnxtf.a

BLD_CAV_CM_OBJS=$(SY_DIR)/libcavcm.a
BLD_CAV_SS_OBJS=$(SY_DIR)/libcavmt.a
BLD_CAV_UE_PERF_OBJS=$(SY_DIR)/libcavperfue.a
BLD_CAV_UE_E2E_OBJS=$(SY_DIR)/libcave2eue.a
BLD_CAV_TF_OBJS=$(SY_DIR)/libcavtf.a

# make the list for .x and .h dependent

# common include files(no makedepend)
CM_INC=\
	$(CM_DIR)/envdep.h         $(CM_DIR)/envind.h       \
	$(CM_DIR)/envopt.h         $(CM_DIR)/ssi.h          \
	$(CM_DIR)/ssi.x            $(CM_DIR)/gen.h          \
	$(CM_DIR)/gen.x            $(CM_DIR)/cm5.x          \
	$(CM_DIR)/cm5.h            $(CM_DIR)/cm_lib.x       \
	$(CM_DIR)/cm_err.h         $(CM_DIR)/cm_tkns.x      \
	$(CM_DIR)/cm_tkns.h        $(CM_DIR)/cm_mblk.x      \
	$(CM_DIR)/cm_mblk.h        $(CM_DIR)/cm_pasn.h      \
	$(CM_DIR)/cm_perr.h        $(CM_DIR)/cm_pasn.x      \
        $(CM_DIR)/nhu_asn.x        $(CM_DIR)/nhu_asn.h      \
        $(CM_DIR)/cm_emm.h         $(CM_DIR)/cm_emm.x       \
        $(CM_DIR)/cm_esm.h         $(CM_DIR)/cm_esm.x       \
        $(CM_DIR)/nhu.h            $(CM_DIR)/nhu.x
CMLIB_INC=\
        $(CMLIB_DIR)/envdep.h         $(CMLIB_DIR)/envind.h       \
        $(CMLIB_DIR)/envopt.h         $(CMLIB_DIR)/ssi.h          \
        $(CMLIB_DIR)/ssi.x            $(CMLIB_DIR)/gen.h          \
        $(CMLIB_DIR)/gen.x            $(CMLIB_DIR)/cm5.x          \
        $(CMLIB_DIR)/cm5.h            $(CMLIB_DIR)/cm_lib.x       \
        $(CMLIB_DIR)/cm_err.h         $(CMLIB_DIR)/cm_tkns.x      \
        $(CMLIB_DIR)/cm_tkns.h        $(CMLIB_DIR)/cm_mblk.x      \
        $(CMLIB_DIR)/cm_mblk.h        $(CMLIB_DIR)/cm_pasn.h      \
        $(CMLIB_DIR)/cm_perr.h        $(CMLIB_DIR)/cm_pasn.x      \
        $(CMLIB_DIR)/nhu_asn.x        $(CMLIB_DIR)/nhu_asn.h      \
        $(CMLIB_DIR)/cm_emm.h         $(CMLIB_DIR)/cm_emm.x       \
        $(CMLIB_DIR)/cm_esm.h         $(CMLIB_DIR)/cm_esm.x       \
        $(CMLIB_DIR)/nhu.h            $(CMLIB_DIR)/nhu.x

#-----------------------------------------------------------------------
# macros for compile and link options
LNXENV=-DSUNOS -DSS -DSS_MT -DANSI -D_GNU_SOURCE -DSS_LINUX -D_REENTRANT -D__EXTENSIONS__ \
    -DDEBUGNOEXIT -UUSE_PURE -DSLES9_PLUS

CAVENV=-DSUNOS -DSS -DSS_CAVIUM -DSS_MT -DANSI -D_GNU_SOURCE -DSS_LINUX -D_REENTRANT \
       -D__EXTENSIONS__ -DSS_CAVIUM_MULT_BIN \
       -DDEBUGNOEXIT -DALIGN_64BIT -DBIT_64  $(CVMXOPTS) 

ifeq (linux,$(findstring linux,$(OCTEON_TARGET)))
    LNXCC = mips64-octeon-linux-gnu-gcc
    AR = mips64-octeon-linux-gnu-ar
    LNXLD = mips64-octeon-linux-gnu-ld
    STRIP = mips64-octeon-linux-gnu-strip
    OBJDUMP = mips64-octeon-linux-gnu-objdump
    NM = mips64-octeon-linux-gnu-nm
else
    LNXCC = mipsisa64-octeon-elf-gcc
    AR = mipsisa64-octeon-elf-ar
    LNXLD = mipsisa64-octeon-elf-ld
    STRIP = mipsisa64-octeon-elf-strip
    OBJDUMP = mipsisa64-octeon-elf-objdump
    NM = mipsisa64-octeon-elf-nm
endif

ifeq (${BLDENV}, cav_e2e_acc_n32)
COMPILE = $(CC) $(CFLAGS_GLOBAL) $(CFLAGS_LOCAL) -MD -c -o $@ $<

ASSEMBLE = $(CC) $(ASFLAGS_GLOBAL) $(ASFLAGS_LOCAL) -MD -c -o $@ $<

CAVENV=-DSUNOS -DSS -DSS_CAVIUM -DSS_MT -DANSI -D_GNU_SOURCE -DSS_LINUX -D_REENTRANT \
       -D__EXTENSIONS__ -DSS_CAVIUM_MULT_BIN \
       -DDEBUGNOEXIT -UALIGN_64BIT -UBIT_64  $(CVMXOPTS) 


dir := $(OCTEON_ROOT)/executive
include $(dir)/cvmx.mk
endif


ifeq ($(MACHINE), BIT32)
LNX_CC="gcc"
LNX_LD="gcc"
else
# Enable to support 64bit compilation
LNX_CC="gcc -m64 -DALIGN_64BIT -DBIT_64"
LNX_LD="gcc -m64"
endif

#PURIFY 
#LNX_CC="purify --cache-dir=/tmp gcc -m32"
#LNX_LD="purify --cache-dir=/tmp gcc -m32"
ifeq ($(MACHINE), BIT32)
PURLIB="purify --cache-dir=/tmp gcc -m32"
else
PURLIB="purify --cache-dir=/tmp gcc -m64"
endif

CAVCOPTS=" -g3 -pipe -Wall -Wno-comment -Wshadow -Wcast-qual \
      -Wstrict-prototypes -Wmissing-prototypes -fno-strict-aliasing"

LNXCOPTS="  -g3 -pipe -pedantic -Wall -Wno-comment -Wshadow -Wcast-qual \
-Wstrict-prototypes -Wmissing-prototypes -Wno-strict-aliasing --std=c99"


LNXARMCC="arm-none-linux-gnueabi-gcc"
LNXARMLD="arm-none-linux-gnueabi-gcc"
LNXARMCOPTS=" -O3 -pipe -pedantic -Wall -Wno-comment -Wshadow -Wcast-qual \
      -Wstrict-prototypes -Wmissing-prototypes -fno-strict-aliasing"

# object files:
# o     UNIX
OBJ=o                                    # object files, sunos

#######################################################################
# library path
LNXLIBPATH=-Llib/
CAVLIBPATH=-L$(OCTEON_ROOT)/target/lib -L$(OBJ_DIR)
#######################################################################

# linker options:
#LNXLOPTS=libpcap.a -lpthread -lnsl -lrt 
ifeq ($(MACHINE), BIT32)
LNXLOPTS=libpcap.a -lpthread -lnsl -lrt -Xlinker \
         -export-dynamic -lm -ldl -lutil -L/usr/lib/nptl
else
LNXLOPTS=libpcap-64bit.a -lpthread -lnsl -lrt -Xlinker \
         -export-dynamic -lm -ldl -lutil -L/usr/lib/nptl
endif
ifeq (${BLDENV}, lnx_perf_msstub_acc)
	LNXLOPTS += -losal
	CMENBPERFOPTS += -DYS_MSPD_OSAL
else
ifeq (${BLDENV}, lnx_e2e_msstub_acc)
	LNXLOPTS += -losal
	CMENBE2EOPTS += -DYS_MSPD_OSAL
endif
endif

LNXLOPTS1=-lpthread -lnsl -lrt -Xlinker \
         -export-dynamic -lm -ldl -lutil -L/usr/lib/nptl

CAVLOPTS= $(LDFLAGS_GLOBAL) -Xlinker $(OBJ_DIR)/libcvmx.a  

PHY_DIR=../ltephy/mindspeed
# include options:
LNXIOPTS  =  -I$(MT_DIR) -I$(CM_DIR) -I$(TF_DIR) -I$(UE_DIR) -I/u/prd/rtr/mt -I$(PHY_DIR)
LNXLIBIOPTS =  -I$(MTLIB_DIR) -I$(CMLIB_DIR) -I$(TFLIB_DIR) -I$(UELIB_DIR) -I/u/prd/rtr/mt
CAVIOPTS  =  -I$(MT_SE_DIR) -I$(CM_DIR) $(CVMX_INC) -I$(TF_DIR) -I$(UE_DIR)
CAVLIBIOPTS =  -I$(MTLIB_DIR) -I$(CMLIB_DIR)  $(CVMX_INC) -I$(TFLIB_DIR) -I$(UELIB_DIR) -I/u/prd/rtr/mt

# compiler options:

# MTSS defines
CCLNXMTOPTS=$(DEBUGPOPTS) $(LNXENV) $(MTOPTS) $(CMOPTS) $(STOPTS) 
CCCAVMTOPTS=$(DEBUGPOPTS) $(CAVENV) $(MTOPTS1) $(CMOPTS) $(STOPTS) -DAPI_MAIN

#TF defines 
CCLNXTFOPTS= $(LNXENV) $(TFOPTS)  $(STOPTS) $(CMOPTS)
CCCAVTFOPTS= $(CAVENV) $(TFOPTS)  $(STOPTS) $(CMOPTS) -DNOFILESYS

CCLNXCMOPTS= $(LNXENV) $(CMOPTS) \
         $(MKUOPTS) $(CMKOPTS)  \
         $(CRLOPTS) $(RLUOPTS)  $(STOPTS) \
         $(TCUOPTS) $(LRXOPTS) 

CCCAVCMOPTS= $(CAVENV) $(CMOPTS) \
         $(MKUOPTS) $(CMKOPTS)  \
         $(CRLOPTS) $(RLUOPTS)  $(STOPTS) \
         $(CTCOPTS) $(TCUOPTS) $(LRXOPTS) 

#Default Compilation
# Change the value of BLDENV as per the BLDENV rules specified down
ifndef BLDENV

BLDENV=arm_acc
TARGETS:
	@$(MAKE) -f $(MAKENAME) $(BLDENV)  L1_INC_SA_DIR=$(PWD)
endif

#  standard compile line
ifeq (${BLDENV}, cav_perf_acc)
COMPILE = $(CC) $(CFLAGS_GLOBAL) $(CFLAGS_LOCAL) -MD -c -o $@ $<

ASSEMBLE = $(CC) $(ASFLAGS_GLOBAL) $(ASFLAGS_LOCAL) -MD -c -o $@ $<

dir := $(OCTEON_ROOT)/executive
include $(dir)/cvmx.mk
endif

ifeq (${BLDENV}, cav_e2e_acc)
COMPILE = $(CC) $(CFLAGS_GLOBAL) $(CFLAGS_LOCAL) -MD -c -o $@ $<

ASSEMBLE = $(CC) $(ASFLAGS_GLOBAL) $(ASFLAGS_LOCAL) -MD -c -o $@ $<

#dir := $(OCTEON_ROOT)/executive
dir := ../cavsdk/executive
include $(dir)/cvmx.mk
endif

LNXPRDENBPERF_OBJS: \
    $(BLD_LNX_TF_OBJS) \
    $(BLD_LNX_CM_OBJS) \
    $(BLD_LNX_SS_OBJS) \
    $(BLD_LNX_UE_PERF_OBJS)

LNXPRDENBE2EPERF_OBJS: \
    $(BLD_LNX_TF_OBJS) \
    $(BLD_LNX_CM_OBJS) \
    $(BLD_LNX_SS_OBJS) \
    $(BLD_LNX_UE_E2EPERF_OBJS)

LNXPRDENBE2E_OBJS: \
    $(BLD_LNX_TF_OBJS) \
    $(BLD_LNX_CM_OBJS) \
    $(BLD_LNX_SS_OBJS) \
    $(BLD_LNX_UE_E2E_OBJS)

CAVPRDENBPERF_OBJS: \
    $(CVMX_CONFIG) \
    $(BLD_CAV_TF_OBJS) \
    $(BLD_CAV_CM_OBJS) \
    $(BLD_CAV_SS_OBJS) \
    $(BLD_CAV_UE_PERF_OBJS) \
    $(LIBS_LIST)
 
CAVPRDENBE2E_OBJS: \
    $(CVMX_CONFIG) \
    $(BLD_CAV_TF_OBJS) \
    $(BLD_CAV_CM_OBJS) \
    $(BLD_CAV_SS_OBJS) \
    $(BLD_CAV_UE_E2E_OBJS) \
    $(LIBS_LIST)

ENBBIN=uesim
LNXENBPERFBIN=se_lnx_perf
LNXENBE2EPERFBIN=se_lnx_e2eperf
CAVENBPERFBIN=se_cav_perf
LNXENBE2EBIN=se_lnx_e2e
CAVENBE2EBIN=se_cav_e2e
CAVENBE2EBINN32=se_cav_e2e_n32
LNXLIBBIN=lnxlib
CAVLIBBIN=cavlib

BASENAME=ue_stack
MAKENAME=$(BASENAME).mak

ifeq ($(BLDENV),lnx_perf_msstub_acc)
BINLNXPERFACC=lnx_perf_msstub_acc
else
ifeq ($(BLDENV),lnx_e2e_msstub_acc)
BINLNXE2EACC=lnx_e2e_msstub_acc
else
ifeq ($(BLDENV),lnx_e2e_acc)
BINLNXE2EACC=lnx_e2e_acc
else
ifeq ($(BLDENV),lnx_e2eperf_acc)
BINLNXE2EPERFACC=lnx_e2eperf_acc
else
BINLNXPERFACC=lnx_perf_acc
endif # lnx_e2e_acc
endif # lnx_e2eperf_acc
endif # lnx_e2e_msstub_acc
endif # lnx_perf_msstub_acc

BINCAVPERFACC=cav_perf_acc
BINCAVE2EACC=cav_e2e_acc
BINCAVE2EACCN32=cav_e2e_acc_n32

BINLNXLIB=lnx_lib
BINCAVLIB=cav_lib

#
#
# Linux Default GNU acceptance test build 
#
acc:
	@$(MAKE) -f $(MAKENAME) $(BLDENV) L1_INC_SA_DIR=$(PWD) 

lib:
	@$(MAKE) -f $(MAKENAME) $(BLDENV) L1_INC_SA_DIR=$(PWD) 

$(BINLNXPERFACC):
	@$(MAKE) -f $(MAKENAME) $(LNXENBPERFBIN) CC=$(LNX_CC) \
	LL=$(LNX_LD) COPTS=$(LNXCOPTS) CMOPTS='$(CMENBPERFOPTS)' \
	PICO_CROSS_LIBROOT='$(PWD)/$(CROSSDIR)'

  
$(LNXENBPERFBIN):LNXPRDENBPERF_OBJS 
	$(CC)  $(SY_DIR)/*.o $(LNXLIBPATH) $(LNXLOPTS) -o ./$(SY_DIR)/$(OUTNAME)

$(BINLNXE2EPERFACC):
	@$(MAKE) -f $(MAKENAME) $(LNXENBE2EPERFBIN) CC=$(LNX_CC) \
	LL=$(LNX_LD) COPTS=$(LNXCOPTS) CMOPTS='$(CMENBE2EPERFOPTS)' \
	PICO_CROSS_LIBROOT='$(PWD)/$(CROSSDIR)'

$(LNXENBE2EPERFBIN):LNXPRDENBE2EPERF_OBJS 
	$(CC)  $(SY_DIR)/*.o $(LNXLIBPATH) $(LNXLOPTS1) -o ./$(SY_DIR)/$(OUTNAME)

$(BINCAVPERFACC):
	@$(MAKE) -f $(MAKENAME) $(CAVENBPERFBIN) CC=$(LNXCC) \
        LL=$(LNXLD) COPTS='$(CAVCOPTS)' CMOPTS='$(CMENBPERFOPTS)' \
        PICO_CROSS_LIBROOT='$(PWD)/$(CROSSDIR)'

$(CAVENBPERFBIN):CAVPRDENBPERF_OBJS
	$(CC)  $(SY_DIR)/*.o $(CAVLIBPATH) $(CAVLOPTS) -o ./$(SY_DIR)/$(OUTNAME)

####################################E2E###############################################

$(BINLNXE2EACC):
	@$(MAKE) -f $(MAKENAME) $(LNXENBE2EBIN) CC=$(LNX_CC) \
        LL=$(LNX_LD) COPTS=$(LNXCOPTS) CMOPTS='$(CMENBE2EOPTS)' \
        PICO_CROSS_LIBROOT='$(PWD)/$(CROSSDIR)'

$(LNXENBE2EBIN):LNXPRDENBE2E_OBJS
	$(CC)  $(SY_DIR)/*.o $(LNXLIBPATH) $(LNXLOPTS) -o ./$(SY_DIR)/$(OUTNAME)

$(BINCAVE2EACC):
	@$(MAKE) -f $(MAKENAME) $(CAVENBE2EBIN) CC=$(LNXCC) \
        LL=$(LNXLD) COPTS='$(CAVCOPTS)' CMOPTS='$(CMENBE2EOPTS)' \
        PICO_CROSS_LIBROOT='$(PWD)/$(CROSSDIR)'

$(BINCAVE2EACCN32):
	@$(MAKE) -f $(MAKENAME) $(CAVENBE2EBINN32) CC=$(LNXCC) \
        LL=$(LNXLD) COPTS='$(CAVCOPTS)' CMOPTS='$(CMENBE2EOPTS)' \
        PICO_CROSS_LIBROOT='$(PWD)/$(CROSSDIR)'



$(CAVENBE2EBIN):CAVPRDENBE2E_OBJS
	$(CC)  $(SY_DIR)/*.o $(CAVLIBPATH) $(CAVLOPTS) -o ./$(SY_DIR)/$(OUTNAME)

$(CAVENBE2EBINN32):CAVPRDENBE2E_OBJS
	$(CC)  $(SY_DIR)/*.o $(CAVLIBPATH) $(CAVLOPTS) -o ./$(SY_DIR)/$(OUTNAME)

$(BINLNXLIB):
	@$(MAKE) -f $(MAKENAME) $(LNXLIBBIN) CC=$(LNX_CC) \
        LL=$(LNX_LD) COPTS=$(LNXCOPTS) CMOPTS='$(CMENBE2EOPTS)' \
        PICO_CROSS_LIBROOT='$(PWD)/$(CROSSDIR)'

$(BINCAVLIB):
	@$(MAKE) -f $(MAKENAME) $(CAVLIBBIN) CC=$(LNXCC) \
        LL=$(LNXLD) COPTS=$(CAVCOPTS) CMOPTS='$(CMENBE2EOPTS)' \
        PICO_CROSS_LIBROOT='$(PWD)/$(CROSSDIR)'

# Portable compilation -> Point to acc directly
# Default compilation with Iu 
# Portability is not supported
pt:acc

$(BINLNXPT):
	@$(MAKE) -f $(MAKENAME) $(ENBBIN)  CC=$(LNXCC) \
	LL=$(LNXLD) COPTS=$(LNXCOPTS) CMOPTS='$(CMENBOPTS)'



#-----------------------------------------------------------------------
# UNIX link - absolute object file depends on relocatable object
# (.o) files

#
# Making Common Libraries
#
$(BLD_LNX_CM_OBJS):
	@$(MAKE) -f cm.mak $(SY_DIR)/libcm.a COPTS=$(LNXCOPTS) \
	LOPTS='$(LNXLOPTS)' POPTS='$(CCLNXCMOPTS)' IOPTS='$(LNXIOPTS)' IN_DIR='$(CM_DIR)' \
	OUT_DIR='$(SY_DIR)' OBJ='$(OBJ)' CC='$(CC)' LL='$(LL)'  CM_INC='$(CM_INC)'

$(BLD_CAV_CM_OBJS):
	@$(MAKE) -f cmse.mak $(SY_DIR)/libcm.a COPTS=$(CAVCOPTS) \
	LOPTS='$(CAVLOPTS)' POPTS='$(CCCAVCMOPTS)' IOPTS='$(CAVIOPTS)' IN_DIR='$(CM_DIR)' \
	OUT_DIR='$(SY_DIR)' OBJ='$(OBJ)' CC='$(CC)' LL='$(LL)'  CM_INC='$(CM_INC)'


#
#Making MAC Layer
#
$(BLD_LNX_UE_PERF_OBJS):
	@$(MAKE) -f ue.mak $(SY_DIR)/libperfue.a COPTS=$(LNXCOPTS) \
	LOPTS='$(LNXLOPTS)' POPTS='$(CCLNXTFOPTS)' IOPTS='$(LNXIOPTS)' IN_DIR='$(UE_DIR)' \
	OUT_DIR='$(SY_DIR)' OBJ='$(OBJ)' CC='$(CC)' LL='$(LL)' CM_INC='$(CM_INC)'

$(BLD_LNX_UE_E2EPERF_OBJS):
	@$(MAKE) -f ue.mak $(SY_DIR)/libe2eperfue.a COPTS=$(LNXCOPTS) \
	LOPTS='$(LNXLOPTS1)' POPTS='$(CCLNXTFOPTS)' IOPTS='$(LNXIOPTS)' IN_DIR='$(UE_DIR)' \
	OUT_DIR='$(SY_DIR)' OBJ='$(OBJ)' CC='$(CC)' LL='$(LL)' CM_INC='$(CM_INC)'
	
$(BLD_LNX_UE_E2E_OBJS):
	@$(MAKE) -f ue.mak $(SY_DIR)/libe2eue.a COPTS=$(LNXCOPTS) \
	LOPTS='$(LNXLOPTS)' POPTS='$(CCLNXTFOPTS)' IOPTS='$(LNXIOPTS)' IN_DIR='$(UE_DIR)' \
	OUT_DIR='$(SY_DIR)' OBJ='$(OBJ)' CC='$(CC)' LL='$(LL)' CM_INC='$(CM_INC)'

$(LNXLIBBIN):
	@$(MAKE) -f ue.mak $(SY_DIR)/libe2eue.a COPTS=$(LNXCOPTS) \
        LOPTS='$(LNXLOPTS)' POPTS='$(CCLNXTFOPTS)' IOPTS='$(LNXLIBIOPTS)' IN_DIR='$(UELIB_DIR)' \
        OUT_DIR='$(SY_DIR)' OBJ='$(OBJ)' CC='$(CC)' LL='$(LL)' CM_INC='$(CMLIB_INC)'
$(CAVLIBBIN):
	@$(MAKE) -f ue_cav.mak $(SY_DIR)/libe2eue.a COPTS=$(CAVCOPTS) \
        LOPTS='$(CAVLOPTS)' POPTS='$(CCCAVTFOPTS)' IOPTS='$(CAVLIBIOPTS)' IN_DIR='$(UELIB_DIR)' \
        OUT_DIR='$(SY_DIR)' OBJ='$(OBJ)' CC='$(CC)' LL='$(LL)' CM_INC='$(CMLIB_INC)'

$(BLD_CAV_UE_PERF_OBJS):
	@$(MAKE) -f ue_cav.mak $(SY_DIR)/libperfue.a COPTS=$(CAVCOPTS) \
	LOPTS='$(CAVLOPTS)' POPTS='$(CCCAVTFOPTS)' IOPTS='$(CAVIOPTS)' IN_DIR='$(UE_DIR)' \
	OUT_DIR='$(SY_DIR)' OBJ='$(OBJ)' CC='$(CC)' LL='$(LL)' CM_INC='$(CM_INC)'

$(BLD_CAV_UE_E2E_OBJS):
	@$(MAKE) -f ue_cav.mak $(SY_DIR)/libe2eue.a COPTS=$(CAVCOPTS) \
	LOPTS='$(CAVLOPTS)' POPTS='$(CCCAVTFOPTS)' IOPTS='$(CAVIOPTS)' IN_DIR='$(UE_DIR)' \
	OUT_DIR='$(SY_DIR)' OBJ='$(OBJ)' CC='$(CC)' LL='$(LL)' CM_INC='$(CM_INC)'
#
#Making CL Layer
#
$(BLD_CAV_TF_OBJS):
	@$(MAKE) -f ys.mak $(SY_DIR)/libcavys.a COPTS=$(CAVCOPTS) \
	LOPTS='$(CAVLOPTS)' POPTS='$(CCCAVTFOPTS)' IOPTS='$(CAVIOPTS)' IN_DIR='$(YS_DIR)' \
	OUT_DIR='$(SY_DIR)' OBJ='$(OBJ)' CC='$(CC)' LL='$(LL)' CM_INC='$(CM_INC)'


ifeq ($(BLDENV),lnx_e2e_msstub_acc)
$(BLD_LNX_TF_OBJS):
	@$(MAKE) -f ys_ms.mak $(SY_DIR)/liblnxys.a COPTS=$(LNXCOPTS) \
	LOPTS='$(LNXLOPTS)' POPTS='$(CCLNXTFOPTS)' IOPTS='$(LNXIOPTS)' IN_DIR='$(TF_DIR)' \
	OUT_DIR='$(SY_DIR)' OBJ='$(OBJ)' CC='$(CC)' LL='$(LL)' CM_INC='$(CM_INC)'
else
ifeq ($(BLDENV),lnx_perf_msstub_acc)
$(BLD_LNX_TF_OBJS):
	@$(MAKE) -f ys_ms.mak $(SY_DIR)/liblnxys.a COPTS=$(LNXCOPTS) \
	LOPTS='$(LNXLOPTS)' POPTS='$(CCLNXTFOPTS)' IOPTS='$(LNXIOPTS)' IN_DIR='$(TF_DIR)' \
	OUT_DIR='$(SY_DIR)' OBJ='$(OBJ)' CC='$(CC)' LL='$(LL)' CM_INC='$(CM_INC)'
else
ifeq ($(BLDENV),lnx_perf_acc)
$(BLD_LNX_TF_OBJS):
	@$(MAKE) -f ys.mak $(SY_DIR)/liblnxys.a COPTS=$(LNXCOPTS) \
	LOPTS='$(LNXLOPTS1)' POPTS='$(CCLNXTFOPTS)' IOPTS='$(LNXIOPTS)' IN_DIR='$(TF_DIR)' \
	OUT_DIR='$(SY_DIR)' OBJ='$(OBJ)' CC='$(CC)' LL='$(LL)' CM_INC='$(CM_INC)'
else
ifeq ($(BLDENV),lnx_e2eperf_acc)
$(BLD_LNX_TF_OBJS):
	@$(MAKE) -f ys.mak $(SY_DIR)/liblnxys.a COPTS=$(LNXCOPTS) \
	LOPTS='$(LNXLOPTS1)' POPTS='$(CCLNXTFOPTS)' IOPTS='$(LNXIOPTS)' IN_DIR='$(TF_DIR)' \
	OUT_DIR='$(SY_DIR)' OBJ='$(OBJ)' CC='$(CC)' LL='$(LL)' CM_INC='$(CM_INC)'
else
$(BLD_LNX_TF_OBJS):
	@$(MAKE) -f ys.mak $(SY_DIR)/liblnxys.a COPTS=$(LNXCOPTS) \
	LOPTS='$(LNXLOPTS)' POPTS='$(CCLNXTFOPTS)' IOPTS='$(LNXIOPTS)' IN_DIR='$(TF_DIR)' \
	OUT_DIR='$(SY_DIR)' OBJ='$(OBJ)' CC='$(CC)' LL='$(LL)' CM_INC='$(CM_INC)'
endif
endif
endif
endif	
#$(BLD_CAV_TF_OBJS):
#	@$(MAKE) -f ys.mak $(SY_DIR)/libcavys.a COPTS=$(CAVCOPTS) \
#	LOPTS='$(CAVLOPTS)' POPTS='$(CCCAVTFOPTS)' IOPTS='$(CAVIOPTS)' IN_DIR='$(TF_DIR)' \
#	OUT_DIR='$(SY_DIR)' OBJ='$(OBJ)' CC='$(CC)' LL='$(LL)' CM_INC='$(CM_INC)'

#$(BLD_LNX_TF_OBJS):
#	@$(MAKE) -f ys.mak BLDENV=lnx_lib palue 

# making Multi Threaded SSI
#
$(BLD_LNX_SS_OBJS):
	@$(MAKE) -f mt.mak $(SY_DIR)/libmt.a COPTS=$(LNXCOPTS) \
	LOPTS='$(LNXLOPTS)' POPTS='$(CCLNXMTOPTS)' IOPTS='$(LNXIOPTS)' IN_DIR='$(MT_DIR)' \
   OUT_DIR='$(SY_DIR)' OBJ='$(OBJ)' CC='$(CC)' LL='$(LL)'  \
   CM_INC='$(CM_INC)'

$(BLD_CAV_SS_OBJS):
	@$(MAKE) -f mtse.mak $(SY_DIR)/libmt.a COPTS=$(CAVCOPTS) \
	LOPTS='$(CAVLOPTS)' POPTS='$(CCCAVMTOPTS)' IOPTS='$(CAVIOPTS)' IN_DIR='$(MT_SE_DIR)' \
   OUT_DIR='$(SY_DIR)' OBJ='$(OBJ)' CC='$(CC)' LL='$(LL)'  \
   CM_INC='$(CM_INC)'
#
# Linking to get the product

$(PICOLIB):
	@$(MAKE) -C $(PIC_DIR)

$(L1API):
	@$(MAKE) -C $(L1API_DIR)

$(L1INT):
	@$(MAKE) -C $(L1_INT_DIR) SA_DIR=$(L1_INC_SA_DIR)

$(F8API):
	@$(MAKE) -C $(F8API_DIR)

$(CRYPT):
	@$(MAKE) -C $(CRYPT_DIR)


cleanpico:
	@$(MAKE) -C $(PIC_DIR) clean

cleanl1api:
	@$(MAKE) -C $(L1API_DIR) clean

cleanl1Int:
	@$(MAKE) -C $(L1_INT_DIR) clean

cleanF8api:
	@$(MAKE) -C $(F8API_DIR) clean

cleanCrypt:
	@$(MAKE) -C $(CRYPT_DIR) clean

clean:
	\rm -f $(SY_DIR)/$(OUTNAME) $(SY_DIR)/*.o $(SY_DIR)/core $(SY_DIR)/*~ \
	$(SY_DIR)/*.bak $(SY_DIR)/*.err $(SY_DIR)/libcm.a  $(SY_DIR)/libmt.a \
	$(SY_DIR)/libtf.a  $(SY_DIR)/libue.a ./*.d

cleanl1: cleanpico cleanl1api cleanl1Int cleanF8api cleanCrypt

cleanall: clean cleanl1


# DO NOT DELETE THIS LINE -- make depend depends on it.
