#********************************************************************20**
#
#       Name:   Total eNodeB acceptance makefile
#
#       Type:   make file
#
#       Desc:   Compile, assemble and link Total eNodeB acceptance 
#               software for various configusztions. Further comments 
#               are embedded in the file.
#
#               This file supports a variety of environments and
#               build targets. The default build target will be the
#               portable target for the Solaris 2.xwith SUNpro C(cc)
#
#               ENVIRONMENTS:
#
#               BUILD TARGETS:
#
#               acc              acceptance tests 
#
#               depend.acc       makedepend for acceptance tests
#
#               clean            remove all object files
#               
#
#       Sid:      nl.mak@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 18:02:37 2014
#
#       Prg:    subhamay 
#
#********************************************************************21*/
#=======================================================================
#
# macros for product specific options

# commented for RTR

# for loose coupling
#PRDOPTS=-DWR_RELAY -DEU_DAT_APP -DEGTP_U -DNX -DPX -DUZ -DEU -DKW_PDCP -DKW -UPTNXLIPJU -UPTWRLIRGR -DDEBUGP -UTFU_TDD -DTFU_WRR_2 -DLCEGUIEGT -DLCWRLICTF -DLCWRLINHU -DxLCPJUIPJU -DLCWRLIRGR -ULTE_TDD -DTA_NEW -DSI_NEW -DRGR_SI_SCH -UWR_SM_LOG_TO_FILE  -UWR_DG_OAM -DVALIDATION_CHK -DWR_OAM_TEST -DWR_TEST_CODE -DWR_TEST_CLI -DENB_OVRLOAD -UMME_LDBAL -DEG -DWR -DKW -DSZ -DYS -DRG -DPJ -DCZ -DNH -DRGR_RRM_TICK -DLTE_HO_SUPPORT -DEGTP_U_REL_9 -DRGR_V1 -DLTERRC_REL9 -DNO_ERRCLS -DLCCZT -DLCEGT -DLCNHUINHU -DLCPJU

PRDOPTS=-UWR -DLCCZT -DSM -ULCLWR -ULCSMMILWR -ULCWRMILWR -DLCNHU -UNX -DLCWRLINHU -DLCNHUINHU -DLCNXLINHU -DLWLCNHUINHU -DLWLCNXLINHU -DLCNHMILNH -DLCSMNHMILNH -DLCCTF -DLCWRLICTF -DLCTFUICTF -DLCNHLICTF -URG -DLCWRLIRGR -DLCRGR -DLWLCWRLIRGR -DLCRGUIRGR -UPJ -UNH -DLCPJU  -DLCWRLIPJU -DLCPJUIPJU -USZ -DUZ -DLCUZLISZT -DLWLCUZLISZT -DLCSZUISZT -DLCSZT -DPTSZUISZT -US1AP_REL851 -DLSZV1 -DSZTV1 -UEG -DLCEGT -DLCEGUIEGT -DCCPU_OPT -DLCEULIEGT -UCZ -DRS -DLCRSLICZT -DLWLCRSLICZT -DLCCZUICZT -DLCCZT -DPTCZUICZT  -DENB  -DCMINET_BSDCOMPAT -DSS_TICKS_SEC=10 -DCMFILE_REORG_1 -DCM_INET2 -DCMFILE_REORG_2 -DSSINT2 -DCMKV2 -UHI_MULTI_THREADED  -DYS_ENB_CFG -DSS_PERF -DSS_WL_REGION=1 -DNO_ERRCLS -DNOERRCHK -DxSS_M_PROTO_REGION -DFP_RELEASE6 -DCCPU_DEBUG_TRACE -DCCPU_MEAS_CPU -DDEBUGP -ULTE_ENB_PERF -UVE_PERF_MEAS -UCM_PASN_DBG -DREL_850 -UUE_RAD_CAP -ULTE_START_UL_DL_DATA -DSS_FLOAT -DRGR_RRM_TICK -ULTE_ENB_PAL -DSLES9_PLUS -DTA_NEW -DSI_NEW -DRGR_SI_SCH -DVE_SRB2_SUPPORT -UVE_SUPPORT_RLC_UM_MODE -UNOFILESYS -ULTE_LNX_AFFINITY -DRGR_V1 -DLTEMAC_MIMO -DLTE_HO_SUPPORT -DRS -DKW_BG_DL_PROC -DKW_BG_UL_PROC -DWR_SB_SCTP -DLTERRC_REL9 -UCTF_VER3 -USSI_DEBUG_LEVEL1 -UMME_LDBAL -DSZ_ENB -DEGTP_U_REL_9 -DLEGV2 -DYS_WIRESHARK_LOG -UMAC_SCH_STATS -UPHY_ERROR_LOGING -DWR_RELAY -DEU_DAT_APP -DEGTP_U -DNX -DPX -DUZ -DEU -DKW_PDCP -UKW -UPTNXLIPJU -UPTWRLIRGR -DDEBUGP -UTFU_TDD -DTFU_WRR_2 -DLCEGUIEGT -DLCWRLICTF -DLCWRLINHU -DxLCPJUIPJU -DLCWRLIRGR -ULTE_TDD -DTA_NEW -DSI_NEW -DRGR_SI_SCH -UWR_SM_LOG_TO_FILE  -UDG -UWR_DG_OAM -DVALIDATION_CHK -UWR_OAM_TEST -UWR_TEST_CODE -UWR_TEST_CLI -DENB_OVRLOAD -DWR_ACC -DRGR_CQI_REPT -DLCRGUIRGR -DLCYSUICTF -DSZTV2 -DNOCONAVL -DSON_ENABLE -DRLOG_ENABLE_TEXT_LOGGING -DLTE_TDD


# Product options for portable build
PRDPTOPTS=$(PRDOPTS) -DCMFILE_REORG_1 -DPTSZUISZT -DCM_INET2
CCnlFLAGS= -DNL -DSS_MT_TMR -DSON_ENABLE -DNLU_LWLC -DLWLCSMNLMILNL -DTCSMSONILNL -DNLU_TC -DLWLCSMSONILNL 


# -------------- Product options for acceptance test build 
PRDACCOPTS=$(PRDOPTS) -DSM -DLCSZLISCT -DLCSZUISZT -DUZ -DDM -DCM_INET2      \
                      -DCMXTA_MASTER -DLWLCSZUISZT -DLWLCUZLISZT -DLCSULISCT \
		      -USS_MULTIPLE_PROCS -DDEBUGP -USB -UHI -UHI_MULTI_THREADED -DNL_ACC
#
# -------------- CSB OPTS for acceptance test build 
#CSBOPTS=-DSB -DLSB8 -UHI_REL_1_4 -DCM_INET2 -DLCSCT -UHI -DLCSBUISCT
#
# -------------- HI OPTS for acceptance test build 
#CHIOPTS=-DHI -DHI_REL_1_4 -UDM -DSB -DHI_MULTI_THREADED


# SECTION 2
# Options for compilation with different OS's
# Default is for Portable build
# For acceptance test build either uncomment specific OS environment
# required or specify on command line

# Gen OS Compile Options
GENOSOPTS= -DSS -DCMFILE_REORG_1 -DCMFILE_REORG_2 \
           -DxSS_SINGLE_THREADED -DLONG_MSG -USS_MULTIPLE_PROCS -DTENB_ACC -UALIGN_64BIT -UBIT_64

# Options for acceptance test build with MTSS - MOS multithread OS
MTOSOPTS=-DSS_MT -D__EXTENSIONS__ -DDEBUGNOEXIT -DSS_MT_TMR

# Options for library build with MTSS - MOS multithread OS
LIBOSOPTS="-DSS_MT -DSS  -DxSS_SINGLE_THREADED"

# Linux  specific options
LNXOSOPTS=-DSS_LINUX $(MTOSOPTS) -D_GNU_SOURCE -D__EXTENSIONS__

# Set OS options to include the OS build being used

#for Solaris MTSS
OSOPTS=$(GENOSOPTS) $(MTOSOPTS) $(LNXOSOPTS)

#=======================================================================
# SECTION 3
# macro for output file name and makefile name 
#
BASENAME=nl

MAKENAME=$(BASENAME).mak

# default acceptance test for Solaris cc environment
BINACC="$(BASENAME)_acc"

# default portable build for KlocWork
BINKW="$(BASENAME)_kw"

# Internal targets for the acceptance test build
MAKEACC=mkacc
ACCBIN=$(BASENAME)_acc

# Internal target for the kw build
MAKEKW=mkkw
KWBIN=$(BASENAME)_kw

# Internal target for makedepend
DEPEND=depend

# Build targets for testing in different environments

# Build with the Insite Memory Check progszme - Acceptance Tests only
# Acceptance Test Build
BININSITEACC=ins_acc

# Build  with the GNU compiler and linker on Linux
# Acceptance Test Build
BINLNXACC=lnx_acc
BINLNXINT=lnx_int
#purcov build
BINLNXPACC=lnx_pacc

# purify
BINPURACC=pur_acc

#=======================================================================
# SECTION 4
# macro for directories and include paths
#
# Treat each of the following as examples and modify to specific product
# requirements

#Directory path
CODEPATH =../../lteson/src
CM_CODE_DIR=../../cm
CM_SS_CODE_DIR=../../mt_acc
#Windows
#CM_SS_CODE_DIR=.
NL_CODE_DIR=$(CODEPATH)
SAMPLE_CODE_DIR=$(CODEPATH)
SM_CODE_DIR=.

# common files directory
CM_CM_DIR=../../cm

CZ_DIR=../../x2ap/
HI_DIR=../../tucl/
NH_DIR=../../lterrc/
PJ_DIR=../../ltepdcp/
RG_DIR=../../ltemac/
YS_DIR=../../ltecl/
EG_DIR=../../egtpu/
RL_DIR=../../rlog/
SZ_DIR=../../s1ap/

# common files directory
CM_SS_DIR=$(CM_SS_CODE_DIR)
CM_HASH_DIR=$(CM_CODE_DIR)
CM_MEM_DIR=$(CM_CODE_DIR)
CM_TMR_DIR=$(CM_CODE_DIR)
CM_TPT_DIR=$(CM_CODE_DIR)
CM_DNS_DIR=$(CM_CODE_DIR)
CM_ASN_DIR=$(CM_CODE_DIR)
CM_LIB_DIR=$(CM_CODE_DIR)
CM_SS7_DIR=$(CM_CODE_DIR)
CM_SCT_DIR=$(CM_CODE_DIR)
CM_SHT_DIR=$(CM_CODE_DIR)
CM_HIT_DIR=$(CM_CODE_DIR)
CM_LLIST_DIR=$(CM_CODE_DIR)
CM_INET_DIR=$(CM_CODE_DIR)
CM_SM_DIR=$(SM_CODE_DIR)
#CM_PYTHON_DIR=/usr/ccpu/python/solaris/10/32bit/python-2.4.4/include/python2.4 
#CM_PYTHON_DIR=/usr/ccpu/python/solaris/10/64bit/python-2.4.4/include/python2.4 
#CM_PYTHON_DIR=/usr/ccpu/python/linux/64bit/python-2.4.4/include/python2.4  
#CM_PYTHON_DIR=/usr/ccpu/python/linux/32bit/python-2.4.4/include/python2.4 

# Total eNodeB directory
NL_DIR=$(NL_CODE_DIR)

# common layer manager interface files directory
CM_LNL_DIR=../../cm/

# Lower interface files directory

# stack manager directory
WRSM_DIR=$(SAMPLE_CODE_DIR)

# acceptance directory
NLACC_DIR=.

# OS directory
#

SS_DIR=../../mt_acc
MT_DIR=../../mt_acc

# OS Directory for Solaris MTSS
OS_DIR=../../mt_acc

# build directory
SY_DIR=.

# include path

# Acceptance test include path
#
ACC_INC_PATH="-I$(NL_DIR) -I$(CM_CM_DIR) \
   -I$(NLACC_DIR) -I$(CM_SM_DIR) -I$(WRSM_DIR) -I$(OS_DIR) -I$(HI_DIR) \
   -I$(NH_DIR) -I$(CZ_DIR) -I$(PJ_DIR) -I$(RL_DIR) -I$(EG_DIR) -I$(YS_DIR)\
   -I$(RG_DIR)"

  
#=======================================================================
# SECTION 5
# macros for environments

# GNU gcc compiler for Linux------------------------------------------
#
# These  flags define the environment required to build an image  on
# a Linux workstation with GNU C version 2.5.7 (or greater)
#
# For ANSI Compilation
#LNXENV="-DSUNOS -DANSI"
LNXENV="-DSUNOS   -DSS_LINUX -DANSI -DUSE_PURE -DNOCONAVL"
#LNXENV="-DSUNOS   -DSS_LINUX "
LNXCOPTS="-g3 -ansi -Wall -Wno-comment -pipe -Wshadow -Wcast-qual \
   -Wstrict-prototypes -Wmissing-prototypes -pedantic \
   -Wimplicit -Wunused --std=c99"

# For non-ANSI Compilation
#LNXENV="-DSUNOS"
#LNXENV="-DSUNOS -DSS_LINUX"
#LNXCOPTS="-g3 -pipe -pedantic -Wall -Wno-comment -Wshadow \
          -Wcast-align -Wcast-qual"

#LNXCC="purify gcc -m32 -DUSE_PURE -DPURE"
#LNXLD="purify gcc -m32 -DUSE_PURE -DPURE"

#LNXCC="/usr/local/insure71/bin/insure -m32"
#LNXLD="/usr/local/insure71/bin/insure -m32"
LNXCC="gcc -m32"
LNXLD="gcc -m32"
LNC_GPP_CC=g++
LNX_GPP_LD=g++
LNXLIBLD="ld"
PLNXCC="purecov gcc -m32"
PLNXLD="purecov gcc -m32"
PLNXCPP="purecov g++ -m32"
PLNXCPPLD="purecov g++ -m32"

#PURIFY 
PURCC="purify --cache-dir=/tmp gcc -m32 -DUSE_PURE -DNOCONAVL"
PURLD="purify --cache-dir=/tmp gcc -m32 -DUSE_PURE"
PURLIB="purify --cache-dir=/tmp gcc -m32"

PURCPP="purify --cache-dir=/tmp g++  -m32 -DUSE_PURE -DNOCONAVL"
PURCPPLD="purify --cache-dir=/tmp g++ -m32 -DUSE_PURE"
PURCPPLIB="purify --cache-dir=/tmp g++ -m32"

#INSURE
# For ANSI Compilation
INSENV="-DSUNOS -DSS_LINUX -DANSI -DUSE_PURE -DPURE"
INSCOPTS="-g3 -ansi -Wall -Wno-comment -pipe -Wshadow -Wcast-qual \
   -Wstrict-prototypes -Wmissing-prototypes -pedantic \
   -Wimplicit -Wunused"

# For non-ANSI Compilation
#INSENV="-DSUNOS -DSS_LINUX -DPURE"
#INSCOPTS="-g3 -pipe -pedantic -Wall -Wno-comment -Wshadow \
          -Wcast-align -Wcast-qual"

 
INSCC="/usr/local/insure71/bin/insure -m32"
INSLD="/usr/local/insure71/bin/insure -m32"
INSLOPTS="-o $(OUTNAME)"
INSLIBS="-Xlinker -export-dynamic -lpthread  -lnsl -lpython2.4 -lm -lrt -lutil -ldl"
INSLINT="lint"
INSLNTOPTS="-c -F -p -v"

LNXLOPTS="-o $(OUTNAME)"
LNXLIBOPTS="-r -o $(OUTNAME)"     
#LNXLIBOPTS="-r -o $(OUTNAME) "
LNXLIBLIBS="-export-dynamic"

LNXLOPTSCPP="-lstdc++"
LNXLIBS="-Xlinker -export-dynamic -lpthread  -lnsl -lpython2.4 -lm -lrt -lutil -ldl"
#for KSCTP
#LNXLIBS="-Xlinker -export-dynamic -lpthread  -lnsl -lpython2.4 -lm -lrt -lutil -ldl -lsctp"
LNXLINT="lint"
LNXLNTOPTS="-c -F -p -v"


# Actual Build Environment----------------------------------------------

# object file suffix----------------------------------------------------
#
# this defaults to 'o' for most UNIX based systems
# this can be set to 'obj' for DOS/Windows/NT platforms
#
SOL_OBJ_SUFFIX=o
WIN_OBJ_SUFFIX=obj
UNIX_OBJ_SUFFIX=o
MS_OBJ_SUFFIX=obj
OBJ=$(SOL_OBJ_SUFFIX)
#OBJ=$(WIN_OBJ_SUFFIX)

#=======================================================================
#
# macros for compile time options
#

# portable options 
CPTOPTS=$(MODEL) $(ENV) $(COPTS) $(INC_PATH) $(OSOPTS)

# acceptance test options - OSOPTS should be set to required environment
COSOPTS=$(MODEL) $(ENV) $(COPTS) $(INC_PATH) $(OSOPTS)
CSMOSOPTS=-DSM $(COSOPTS)

# Combined environment, OS, compiler options and include path
CENVOPTS=$(MODEL) $(ENV) $(COPTS) $(INC_PATH) $(OSOPTS)

# product options for portable build
CPRDPTOPTS="$(CENVOPTS) $(PRDPTOPTS)"

# product options for library build
CPRDLIBOPTS="$(CENVOPTS) $(PRDLIBOPTS)"

# product options for acceptance test build
CPRDACCOPTS="$(CENVOPTS) $(PRDACCOPTS)"

# Common Stack Manager File Options for portable build
CSMPTOPTS="$(CENVOPTS) $(PRDOPTS)"

# Common Stack Manager File Options for library build
CSMLIBOPTS="$(CENVOPTS) $(PRDOPTS)"

SMOPTS=-DSM
# Common Stack Manager File Options for acceptance test build
CSMACCOPTS="$(CENVOPTS) $(PRDOPTS) $(SMOPTS)" 

# MOS options - for use with the MOS/MTSS files in test environment
#CMSOPTS=$(CENVOPTS) $(MSINC_PATH) $(MSCOPTS)

#=======================================================================
#
# macros for depend and lint options
#

# depend acceptance test
DEPOPTS_ACC="$(PRDACCOPTS)"

# depend portable test
DEPOPTS_PT="$(PRDPTOPTS)"

#=======================================================================
#
# macros for hardcoded dependencies 
#

# 
# The following are enabled by default since we assume makedepend
# is not available. If makedepend is available in your environemnt
# uncomment out this section.
# 
# DIAB cross compiler under Sun Solaris for PSOS----------------
#
# These flags define the environment required to build an image for
# a DIAB cross compiler on Sun Solaris
#
#
# For ANSI Compilation
# DIABENV=<compiler-specific options>

# For non-ANSI Compilation
# DIABENV=<compiler-specific options>
# DIABCC=<compiler tool>
# DIABLD=<linker tool>
# DIABCOPTS=<compiler options>
# DIABLOPTS=<linker options>
# DIABLIBS=<library files if required>
# DIABLINT=<lint tool>
# DIABLNTOPTS=<lint tool options>

# SECTION 6
# Use the following as examples and modify it to the specific
# product requirements 

# environment
ENV_INC=$(CM_CM_DIR)/envdep.h $(CM_CM_DIR)/envind.h $(CM_CM_DIR)/envopt.h

# system service interface
SSI_INC=$(CM_CM_DIR)/ssi.h $(CM_CM_DIR)/ssi.x
#SSI_INC=

# geneszl
GEN_INC=$(CM_CM_DIR)/gen.h $(CM_CM_DIR)/gen.x 
#$(CM_CM_DIR)/cm_gen.h $(CM_CM_DIR)/cm_gen.x
#GEN_INC=

# all system includes
SYS_INC=$(ENV_INC) $(GEN_INC) $(SSI_INC) 

#RLOG includes
#RL_INC=$(RL_DIR)/rl_common.h $(RL_DIR)/rl_rlog.h $(RL_DIR)/rl_interface.h
RL_INC=$(RL_DIR)/rl_common.h $(RL_DIR)/rl_rlog.h $(RL_DIR)/rl_interface.h 

# Product layer management - LSZ includes
LNL_INC=$(CM_LNL_DIR)/lnl.h $(CM_LNL_DIR)/lnl.x 
#LSI_INC=
CM_NLT_DIR=../../cm
WR_DIR=../../enbapp
# Product Upper Interface - SZT includes
NLU_INC=$(CM_NLT_DIR)/nlu.h $(CM_NLT_DIR)/nlu.x 

# Product lower Interface - SCT includes
#RGM_INC= $(CM_RMT_DIR)/rgm.h $(CM_RMT_DIR)/rgm.x

# common function library includes 
CM_INC=\
	$(CM_CM_DIR)/envdep.h         $(CM_CM_DIR)/envind.h         \
	$(CM_CM_DIR)/envopt.h                                    \
	$(CM_CM_DIR)/gen.h            $(CM_CM_DIR)/gen.x            \
	$(CM_CM_DIR)/cm_hash.x        $(CM_CM_DIR)/cm_hash.h        \
	$(CM_CM_DIR)/cm_lte.x        $(CM_CM_DIR)/cm_lte.h        \
	$(CM_CM_DIR)/cm5.h            $(CM_CM_DIR)/cm5.x            \
	$(CM_CM_DIR)/cm_umts.h        $(CM_CM_DIR)/cm_umts.x        \
	$(CM_CM_DIR)/cm_err.h         $(CM_CM_DIR)/cm_lib.x         \
	$(CM_CM_DIR)/cm_mblk.h        $(CM_CM_DIR)/cm_mblk.x        \
	$(CM_CM_DIR)/cm_tkns.h        $(CM_CM_DIR)/cm_tkns.x        \
	$(CM_CM_DIR)/cm_llist.h       $(CM_CM_DIR)/cm_llist.x       \
	$(CM_CM_DIR)/cm_os.h          $(CM_CM_DIR)/cm_os.x          \
	$(CM_CM_DIR)/cm_hash.h        $(CM_CM_DIR)/cm_hash.x        \
	$(CM_CM_DIR)/cm_inet.h        $(CM_CM_DIR)/cm_inet.x        \
	$(CM_CM_DIR)/cm_gen.h         $(CM_CM_DIR)/cm_gen.x         \
	$(CM_CM_DIR)/cm_tpt.h         $(CM_CM_DIR)/cm_tpt.x         \
	$(CM_CM_DIR)/cm_dns.h         $(CM_CM_DIR)/cm_dns.x         \
	$(CM_CM_DIR)/ssi.h            $(CM_CM_DIR)/ssi.x            \
	$(CM_CM_DIR)/nhu.h            $(CM_CM_DIR)/nhu.x            \
        $(CM_CM_DIR)/lnl.h            $(CM_CM_DIR)/lnl.x            \
        $(CM_CM_DIR)/nlu.h            $(CM_CM_DIR)/nlu.x            \
        $(CM_CM_DIR)/cm_pint.h        $(CM_CM_DIR)/cm_pint.x        \
	$(CM_CM_DIR)/cm_perr.h                                      \
        $(CM_CM_DIR)/nhu_pk.x         $(CM_CM_DIR)/nhu_unpk.x       \
        $(CM_CM_DIR)/nhu_asn.h         $(CM_CM_DIR)/nhu_asn.x       \
	$(CM_CM_DIR)/cm_pasn.h        $(CM_CM_DIR)/cm_pasn.x        \
	$(CM_CM_DIR)/cm_mem.h         $(CM_CM_DIR)/cm_mem.x         
# message functions
MF_INC = \
   $(CM_ASN_DIR)/cm_pasn.h        \
   $(CM_ASN_DIR)/cm_pasn.x


# Product - includes
#WR_INC=
#WR_INC=$(NL_DIR)/wr.h $(NL_DIR)/wr_lwr.h
#RM_INC=$(NL_DIR)/rm.h $(NL_DIR)/rm_wr.h $(NL_DIR)/rm_rbc.h $(NL_DIR)/rm_rcm.h $(NL_DIR)/rm_cac.h $(NL_DIR)/rm_tmr.h

#NL_INC=
NL_INC=$(NL_DIR)/nl.h $(NL_DIR)/nl.x 

# ALL product includes
NLALL_INC=$(NLU_INC) $(LNL_INC) $(NL_INC) $(SYS_INC) $(RL_INC) 

# Product - sample acceptance test includes
NLACC_INC=$(NLACC_DIR)/nlac_acc.h $(NLACC_DIR)/nlac_acc.x 

# sample acceptance tests all includes
NLACCALL_INC=$(NLALL_INC) $(NLACC_INC)

# OS specific includes - SS includes
#SS_INC=
SS_INC=$(SS_DIR)/ss_dep.h $(SS_DIR)/ss_dep.x $(SS_DIR)/ss_err.h \
	$(SS_DIR)/ss_drvr.x $(SS_DIR)/ss_gen.h $(SS_DIR)/ss_gen.x    \
	$(SS_DIR)/ss_mem.h $(SS_DIR)/ss_mem.x $(SS_DIR)/ss_msg.h     \
	$(SS_DIR)/ss_msg.x $(SS_DIR)/ss_queue.h $(SS_DIR)/ss_queue.x \
	$(SS_DIR)/ss_strm.h $(SS_DIR)/ss_strm.x $(SS_DIR)/ss_task.h  \
	$(SS_DIR)/ss_task.x $(SS_DIR)/ss_timer.x \

#MT_INC=
MT_INC=$(MT_DIR)/mt_ss.h $(MT_DIR)/mt_ss.x $(MT_DIR)/mt_err.h


#=======================================================================
# SECTION 7
# macros for source and object files

# Product sources-------------------------------------------------------

# Product objects-------------------------------------------------------


# acceptance test source------------------------------------------------
NL_ACC_SRCS= \
	$(NLACC_DIR)/nlac_lnlcb.c \
	$(NLACC_DIR)/nlac_lnlreg.c \
	$(NLACC_DIR)/nlac_nlucb.c \
	$(NLACC_DIR)/nlac_nluhdl.c \
	$(NLACC_DIR)/nlac_nlureg.c \
	$(NLACC_DIR)/nlac_dm_ex_ms.c \
	$(NLACC_DIR)/nlac_nlld.c \
	$(NLACC_DIR)/nlac_tst.c \
	$(NLACC_DIR)/nlac_prof.c \
	$(NLACC_DIR)/nlac_flag.c \
	$(NLACC_DIR)/nlac_lnlhdl.c \

CM_XTA_SRCS= \
	$(NLACC_DIR)/cm_xta_txn.c \
	$(NLACC_DIR)/cm_xta_intutl.c \
	$(NLACC_DIR)/cm_xta_tmr.c \
    	$(NLACC_DIR)/cm_xta_inthdl.c \
	$(NLACC_DIR)/cm_xta_intreg.c \
	$(NLACC_DIR)/cm_xta_res.c \
   	$(NLACC_DIR)/cm_xta_queue.c \
   	$(NLACC_DIR)/cm_xta_log.c \
	$(NLACC_DIR)/cm_xta_slave.c \
	$(NLACC_DIR)/cm_xta_master.c \
	$(NLACC_DIR)/cm_xta_reg.c \
	$(NLACC_DIR)/cm_xta_tst.c \
	$(NLACC_DIR)/cm_xta_flag.c \
	$(NLACC_DIR)/cm_xta_py.c \
	$(NLACC_DIR)/cm_xta_tcfsm.c \
	$(NLACC_DIR)/cm_xta_ldfsm.c \
	$(NLACC_DIR)/cm_xta_xml.c \
	$(NLACC_DIR)/cm_xta_ex_ms.c \
	$(NLACC_DIR)/cm_xta_tgfsm.c \
	$(NLACC_DIR)/cm_xta_tafsm.c 

# acceptance test object------------------------------------------------

NL_ACC_OBJS= \
        $(SY_DIR)/nlac_lnlcb.$(OBJ) \
	$(SY_DIR)/nlac_lnlreg.$(OBJ) \
	$(SY_DIR)/nlac_nlucb.$(OBJ) \
	$(SY_DIR)/nlac_nluhdl.$(OBJ) \
	$(SY_DIR)/nlac_nlureg.$(OBJ) \
	$(SY_DIR)/nlac_dm_ex_ms.$(OBJ) \
	$(SY_DIR)/nlac_nlld.$(OBJ) \
	$(SY_DIR)/nlac_tst.$(OBJ) \
	$(SY_DIR)/nlac_prof.$(OBJ) \
	$(SY_DIR)/nlac_flag.$(OBJ) \
	$(SY_DIR)/nlac_lnlhdl.$(OBJ) \
	
CM_XTA_OBJS= \
	$(SY_DIR)/cm_xta_tmr.$(OBJ) \
	$(SY_DIR)/cm_xta_txn.$(OBJ) \
	$(SY_DIR)/cm_xta_res.$(OBJ) \
	$(SY_DIR)/cm_xta_queue.$(OBJ) \
	$(SY_DIR)/cm_xta_slave.$(OBJ) \
	$(SY_DIR)/cm_xta_master.$(OBJ) \
	$(SY_DIR)/cm_xta_reg.$(OBJ) \
	$(SY_DIR)/cm_xta_tst.$(OBJ) \
	$(SY_DIR)/cm_xta_log.$(OBJ) \
	$(SY_DIR)/cm_xta_flag.$(OBJ) \
	$(SY_DIR)/cm_xta_intreg.$(OBJ) \
	$(SY_DIR)/cm_xta_inthdl.$(OBJ) \
	$(SY_DIR)/cm_xta_intutl.$(OBJ) \
	$(SY_DIR)/cm_xta_py.$(OBJ) \
	$(SY_DIR)/cm_xta_tcfsm.$(OBJ) \
	$(SY_DIR)/cm_xta_ldfsm.$(OBJ) \
	$(SY_DIR)/cm_xta_xml.$(OBJ) \
	$(SY_DIR)/cm_xta_ex_ms.$(OBJ) \
	$(SY_DIR)/cm_xta_tgfsm.$(OBJ) \
	$(SY_DIR)/cm_xta_tafsm.$(OBJ) 

# Total eNodeB SON source------------------------------------------------
NL_SRCS= \
	$(NL_DIR)/nl_lmm.c \
	$(NL_DIR)/nl_init.c \
	$(NL_DIR)/nl_ptmi.c \
	$(NL_DIR)/nl_ptui.c \
	$(NL_DIR)/nl_pci_sel.c \
	$(NL_DIR)/nl_earfcn_sel.c \
	$(NL_DIR)/nl_events.c \
	$(NL_DIR)/nl_alarm.c \
	$(NL_DIR)/nl_prach_sel.c \
	$(NL_DIR)/nl_tmr.c \
	$(NL_DIR)/nl_pt_son.c \
	$(NL_DIR)/nl_txpower_sel.c \
 #       $(NL_DIR)/example_client.c\
	

# Total eNodeB SON objects-------------------------------------------------------
NL_OBJS= \
	$(SY_DIR)/nl_lmm.$(OBJ) \
	$(SY_DIR)/nl_init.$(OBJ) \
	$(SY_DIR)/nl_ptmi.$(OBJ) \
	$(SY_DIR)/nl_ptui.$(OBJ) \
	$(SY_DIR)/nl_pci_sel.$(OBJ) \
	$(SY_DIR)/nl_earfcn_sel.$(OBJ) \
	$(SY_DIR)/nl_events.$(OBJ) \
	$(SY_DIR)/nl_alarm.$(OBJ) \
	$(SY_DIR)/nl_prach_sel.$(OBJ) \
	$(SY_DIR)/nl_tmr.$(OBJ) \
	$(SY_DIR)/nl_pt_son.$(OBJ) \
	$(SY_DIR)/nl_txpower_sel.$(OBJ) \
  #      $(SY_DIR)/example_client.$(OBJ)\

# Total eNodeB Application source---------------------------------------------------
#WR_SRCS = \
         $(WR_DIR)/wr_smm_init.c \
         $(WR_DIR)/wr_smm_tmr.c

# Total eNodeB Application objects--------------------------------------------------
#WR_OBJS= \
        $(WR_DIR)/wr_smm_init.$(OBJ) \
        $(SY_DIR)/wr_smm_tmr.$(OBJ)

#---------------RL parent source........
RL_SRCS=$(RL_DIR)/rl_rlog.c $(RL_DIR)/rl_common.c
#RL_SRCS=$(RL_DIR)/rl_common.c

#...............RL OBJECTS......
RL_OBJS=$(SY_DIR)/rl_rlog.$(OBJ) $(SY_DIR)/rl_common.$(OBJ)
#RL_OBJS= $(SY_DIR)/rl_common.$(OBJ)

# common source(C header files)-----------------------------------------
#WRCMH_SRCS= \
	cm_hash.h \
	cm_hash.x \
	cm_lib.x  \
	cm5.h     \
	cm5.x     \
	cm_err.h  \
	envdep.h  \
	envind.h  \
	gen.h     \
	gen.x     \
	hit.x     \
	hit.h     \
	ssi.h     \
	ssi.x

# common source(C source files)-----------------------------------------
WRCM_SRCS= \
	$(CM_CM_DIR)/cm_gen.c      \
	$(CM_CM_DIR)/cm_lib.c     \
	$(CM_CM_DIR)/cm_hash.c   \
	$(CM_CM_DIR)/cm_llist.c \
	$(CM_CM_DIR)/cm_os.c \
	$(CM_CM_DIR)/cm_tkns.c     \
	$(CM_CM_DIR)/cm_dns.c     \
	$(CM_CM_DIR)/cm_inet.c   \
	$(CM_CM_DIR)/cm_pasn1.c   \
	$(CM_CM_DIR)/cm_pasn2.c   \
	$(CM_CM_DIR)/cm_pasn3.c   \
	$(CM_CM_DIR)/cm_pasn4.c   \
	$(CM_CM_DIR)/cm_lte.c   \
	$(CM_CM_DIR)/cm_bdy5.c    \
	$(CM_CM_DIR)/cm_tpt.c     \
        $(CM_CM_DIR)/nlu_pk.c    \
        $(CM_CM_DIR)/nlu_unpk.c  \
        $(CM_CM_DIR)/lnl.c       \
        


# common objects--------------------------------------------------------
WRCM_OBJS= \
	$(SY_DIR)/cm_gen.$(OBJ)    \
	$(SY_DIR)/cm_tkns.$(OBJ)   \
	$(SY_DIR)/cm_lib.$(OBJ)    \
	$(SY_DIR)/cm_hash.$(OBJ)   \
	$(SY_DIR)/cm_llist.$(OBJ)  \
	$(SY_DIR)/cm_os.$(OBJ)  \
	$(SY_DIR)/cm_dns.$(OBJ)    \
	$(SY_DIR)/cm_inet.$(OBJ)   \
	$(SY_DIR)/cm_pasn1.$(OBJ)  \
	$(SY_DIR)/cm_pasn2.$(OBJ)  \
	$(SY_DIR)/cm_pasn3.$(OBJ)  \
	$(SY_DIR)/cm_pasn4.$(OBJ)  \
	$(SY_DIR)/cm_lte.$(OBJ)  \
	$(SY_DIR)/cm_mblk.$(OBJ)   \
	$(SY_DIR)/cm_bdy5.$(OBJ)   \
	$(SY_DIR)/cm_tpt.$(OBJ)    \
	$(SY_DIR)/lnl.$(OBJ)    \
	$(SY_DIR)/nlu_pk.$(OBJ)    \
	$(SY_DIR)/nlu_unpk.$(OBJ)    \

WRSBCM_SRCS= \
	$(CM_SCT_DIR)/lsb.c

WRSBCM_OBJS= \
	$(SY_DIR)/lsb.$(OBJ)

# common objects--------------------------------------------------------
WRHICM_SRCS= \
	$(CM_HIT_DIR)/hit.c        \
	$(CM_HIT_DIR)/lhi.c

WRHICM_OBJS= \
	$(SY_DIR)/hit.$(OBJ)      \
	$(SY_DIR)/lhi.$(OBJ)


# common stack manager source-------------------------------------------
SM_SRCS= \
	$(CM_SM_DIR)/sm_bdy1.c 	\
	$(CM_SM_DIR)/sm_ex_ms.c 

# common stack manager objects------------------------------------------
SM_OBJS= \
	$(SY_DIR)/sm_bdy1.$(OBJ) \
	$(SY_DIR)/sm_ex_ms.$(OBJ) 

#  stack manager source------------------------------------------
WRSM_SRCS= \
#	$(WRSM_DIR)/smwrexms.c \
#	$(WRSM_DIR)/smwrptmi.c


# stack manager objects-----------------------------------------
WRSM_OBJS= \
#	$(SY_DIR)/smwrexms.$(OBJ) \
#	$(SY_DIR)/smwrptmi.$(OBJ)

#----------------------------------------- SS Sources 
SS_SRCS= \
   $(SS_DIR)/ss_gen.c              \
   $(SS_DIR)/ss_task.c             \
   $(SS_DIR)/ss_drvr.c             \
   $(SS_DIR)/ss_timer.c            \
   $(SS_DIR)/ss_mem.c              \
   $(SS_DIR)/ss_strm.c             \
   $(SS_DIR)/ss_msg.c              \
   $(SS_DIR)/ss_queue.c            \
   $(SS_DIR)/ss_pack.c             \
   $(SS_DIR)/ss_rtr.c

#----------------------------------------- SS Objects
SS_OBJS= \
   $(SY_DIR)/ss_gen.$(OBJ)         \
   $(SY_DIR)/ss_task.$(OBJ)        \
   $(SY_DIR)/ss_drvr.$(OBJ)        \
   $(SY_DIR)/ss_timer.$(OBJ)       \
   $(SY_DIR)/ss_mem.$(OBJ)         \
   $(SY_DIR)/ss_strm.$(OBJ)        \
   $(SY_DIR)/ss_msg.$(OBJ)         \
   $(SY_DIR)/ss_queue.$(OBJ)       \
   $(SY_DIR)/ss_pack.$(OBJ)        \
   $(SY_DIR)/ss_rtr.$(OBJ)

#------------------------------------------ MT sources
MT_SRCS= \
   $(OS_DIR)/mt_ss.c               \
   $(OS_DIR)/mt_id.c               \
   $(CM_MEM_DIR)/cm_mem.c

#------------------------------------------- MT objects
MT_OBJS= \
   $(SY_DIR)/mt_ss.$(OBJ)          \
   $(SY_DIR)/mt_id.$(OBJ)          \
   $(SY_DIR)/cm_mem.$(OBJ)

# select which OS build-------------------------------------------------

#for Solaris MTSS
OS_SRCS=$(SS_SRCS) $(MT_SRCS)
OS_OBJS=$(SS_OBJS) $(MT_OBJS)

# all acceptance test source--------------------------------------------
PRDACC_SRCS= \
	$(NL_ACC_SRCS) \
	$(CM_XTA_SRCS)\
	$(WRCM_SRCS) \
	$(WRHICM_SRCS) \
	$(SM_SRCS)    \
	$(WRCM_SRCS)  \
        $(WR_SRCS)    \
	$(OS_SRCS)    \
        $(RL_SRCS)    \
        $(NL_SRCS)    \
        $(NL_DIR)/nl_ex_ms.c  \

# all acceptance test objects-------------------------------------------
PRDACC_OBJS= \
	$(NL_ACC_OBJS)  \
	$(CM_XTA_OBJS) \
	$(WRCM_OBJS)  \
	$(WRHICM_OBJS)  \
	$(SM_OBJS)     \
	$(WRSM_OBJS)   \
        $(WR_OBJS)     \
	$(OS_OBJS)    \
        $(RL_OBJS)    \
        $(NL_OBJS)    \
        $(SY_DIR)/nl_ex_ms.$(OBJ)   \

#----------------------------------------- Klocwork analysis objects
PRDKW_OBJS= \
	$(NL_ACC_OBJS)  \
	$(CM_XTA_OBJS) \
	$(WRCM_OBJS)  \
	$(SM_OBJS)     \
	$(WRSM_OBJS)   \
        $(WR_OBJS)     \
	$(OS_OBJS)    \
        $(NL_OBJS)    \
        $(SY_DIR)/nl_ex_ms.$(OBJ)   \


#=======================================================================
#
# special progszms required for Internal Development by makefile
#
# adjust as required
#
# System Binary Dir - replace with appropriate directory and progszme
# for system
BIN=/bin
MAKEDEPEND=makedepend
REMOVE=$(BIN)/rm -f
DELETE=del

#=======================================================================
#
# build targets
# 

# clean-----------------------------------------------------------------
#
# cleans up everything...
#
clean:
	$(REMOVE) *.$(OBJ) $(BINACC) $(BINPT) *.ln *.s $(SY_DIR)/*.$(OBJ) \
      $(SY_DIR)/$(BINACC) $(SY_DIR)/*.ln $(SY_DIR)/*.s 

win_clean:
	$(DELETE) *.$(OBJ)
	$(DELETE) $(BINACC).exe
	$(DELETE) $(BINPT).exe
	$(DELETE) *.ln
	$(DELETE) *.s

# External target for acceptance test build
acc:
	@$(MAKE) -f $(MAKENAME) $(BLDENV) INC_PATH=$(ACC_INC_PATH) \
	OUTNAME=$(BINACC)

# External target for klocworks build
kw:
	@$(MAKE) -f $(MAKENAME) $(BLDENV) INC_PATH=$(ACC_INC_PATH) \
	OUTNAME=$(BINKW)

#
# Linux  GNU acceptance test build-------------------------------------
$(BINLNXACC):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC) -e ENV=$(LNXENV) CC=$(LNXCC) \
	LD=$(LNXLD) COPTS=$(LNXCOPTS) LOPTS=$(LNXLOPTS) LIBS=$(LNXLIBS) \
	OBJ=$(SOL_OBJ_SUFFIX) CPP=$(LNC_GPP_CC) LDCPP=$(LNX_GPP_LD) LOPTSCPP=$(LNXLOPTSCPP)
#
# Linux  purecov acceptance test build-------------------------------------
$(BINLNXPACC):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC) -e ENV=$(LNXENV) CC=$(PLNXCC) \
	LD=$(PLNXLD) COPTS=$(LNXCOPTS) LOPTS=$(LNXLOPTS) LIBS=$(LNXLIBS) \
	OBJ=$(SOL_OBJ_SUFFIX) CPP=$(PLNXCPP) LDCPP=$(PLNXCPPLD) LOPTSCPP=$(LNXLOPTSCPP)
#
# Linux purify acceptance test build-------------------------------------
$(BINPURACC):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC) -e ENV=$(LNXENV) CC=$(PURCC) \
	LD=$(PURLD) COPTS=$(LNXCOPTS) LOPTS=$(LNXLOPTS) LIBS=$(LNXLIBS) \
	OBJ=$(SOL_OBJ_SUFFIX) CPP=$(PURCPP) LDCPP=$(PURCPPLD) LOPTSCPP=$(LNXLOPTSCPP)

# SECTION 8 
# Portable Target builds for Solaris CC, Solaris GNU, MRI mcc68k on
# Solaris and Microsoft Visual C++ for WINNT/WIN95


# acceptance test-------------------------------------------------------
# SECTION 9
# The following assumes that the compile and linker options are
# set in the make-file before the definition of this target
# 
$(MAKEACC):
	@$(MAKE) -f $(MAKENAME) $(ACCBIN) CPRDOPTS=$(CPRDACCOPTS) \
	CSMOPTS=$(CSMACCOPTS)
 
$(ACCBIN): $(PRDACC_OBJS)
	$(LD) $(LOPTSCPP) $(PRDACC_OBJS) $(LIBS) $(LOPTS)  

#
# Make Depend
# depend acceptance test------------------------------------------------
# dependency for acceptance test 
depend_acc: $(PRDACC_SRCS)
	@$(MAKE) -f $(MAKENAME) $(DEPEND) -e \
	DEPOPTS=$(DEPOPTS_ACC) INC_PATH=$(ACC_INC_PATH) DEP_SRCS="$(PRDACC_SRCS)"

# Build the dependency
$(DEPEND):
	$(MAKEDEPEND) -f $(MAKENAME) $(OSOPTS) $(DEPOPTS) $(INC_PATH) $(DEP_SRCS)
#=======================================================================
# SECTION 10
# Source code build directives
# Modify this section to list out the build directives for the specific 
# product

# --------------------------  acceptance test files build

$(SY_DIR)/nlac_lnlhdl.$(OBJ): $(NLACC_DIR)/nlac_lnlhdl.c $(NLACCALL_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CCnlFLAGS) $(NLACC_DIR)/nlac_lnlhdl.c -o $(SY_DIR)/nlac_lnlhdl.$(OBJ)

$(SY_DIR)/nlac_lnlreg.$(OBJ): $(NLACC_DIR)/nlac_lnlreg.c $(NLACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NLACC_DIR)/nlac_lnlreg.c -o $(SY_DIR)/nlac_lnlreg.$(OBJ)

$(SY_DIR)/nlac_lnlcb.$(OBJ): $(NLACC_DIR)/nlac_lnlcb.c $(NLACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NLACC_DIR)/nlac_lnlcb.c -o $(SY_DIR)/nlac_lnlcb.$(OBJ)

$(SY_DIR)/nlac_nluhdl.$(OBJ): $(NLACC_DIR)/nlac_nluhdl.c $(NLACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CCnlFLAGS) $(NLACC_DIR)/nlac_nluhdl.c -o $(SY_DIR)/nlac_nluhdl.$(OBJ)

$(SY_DIR)/nlac_nlureg.$(OBJ): $(NLACC_DIR)/nlac_nlureg.c $(NLACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NLACC_DIR)/nlac_nlureg.c -o $(SY_DIR)/nlac_nlureg.$(OBJ)

$(SY_DIR)/nlac_nlucb.$(OBJ): $(NLACC_DIR)/nlac_nlucb.c $(NLACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NLACC_DIR)/nlac_nlucb.c -o $(SY_DIR)/nlac_nlucb.$(OBJ)
	
$(SY_DIR)/nlac_dm_ex_ms.$(OBJ): $(NLACC_DIR)/nlac_dm_ex_ms.c $(NLACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NLACC_DIR)/nlac_dm_ex_ms.c -o $(SY_DIR)/nlac_dm_ex_ms.$(OBJ)

$(SY_DIR)/nlac_prof.$(OBJ): $(NLACC_DIR)/nlac_prof.c $(NLACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NLACC_DIR)/nlac_prof.c -o $(SY_DIR)/nlac_prof.$(OBJ)

$(SY_DIR)/nlac_nlld.$(OBJ): $(NLACC_DIR)/nlac_nlld.c $(NLACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NLACC_DIR)/nlac_nlld.c -o $(SY_DIR)/nlac_nlld.$(OBJ)

$(SY_DIR)/nlac_tst.$(OBJ): $(NLACC_DIR)/nlac_tst.c $(NLACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NLACC_DIR)/nlac_tst.c -o $(SY_DIR)/nlac_tst.$(OBJ)

$(SY_DIR)/nlac_flag.$(OBJ): $(NLACC_DIR)/nlac_flag.c $(NLACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NLACC_DIR)/nlac_flag.c -o $(SY_DIR)/nlac_flag.$(OBJ)


# ---------------------------  CM_XTA files

$(SY_DIR)/cm_xta_ex_ms.$(OBJ): $(NLACC_DIR)/cm_xta_ex_ms.c
	$(CC) -c $(CPRDOPTS) $(NLACC_DIR)/cm_xta_ex_ms.c -o $(SY_DIR)/cm_xta_ex_ms.$(OBJ)

$(SY_DIR)/cm_xta_xml.$(OBJ): $(NLACC_DIR)/cm_xta_xml.c
	$(CC) -c $(CPRDOPTS) $(NLACC_DIR)/cm_xta_xml.c -o $(SY_DIR)/cm_xta_xml.$(OBJ)

$(SY_DIR)/cm_xta_ldfsm.$(OBJ): $(NLACC_DIR)/cm_xta_ldfsm.c
	$(CC) -c $(CPRDOPTS) $(NLACC_DIR)/cm_xta_ldfsm.c -o $(SY_DIR)/cm_xta_ldfsm.$(OBJ)

$(SY_DIR)/cm_xta_tcfsm.$(OBJ): $(NLACC_DIR)/cm_xta_tcfsm.c
	$(CC) -c $(CPRDOPTS) $(NLACC_DIR)/cm_xta_tcfsm.c -o $(SY_DIR)/cm_xta_tcfsm.$(OBJ)

$(SY_DIR)/cm_xta_tgfsm.$(OBJ): $(NLACC_DIR)/cm_xta_tgfsm.c
	$(CC) -c $(CPRDOPTS) $(NLACC_DIR)/cm_xta_tgfsm.c -o $(SY_DIR)/cm_xta_tgfsm.$(OBJ)

$(SY_DIR)/cm_xta_tafsm.$(OBJ): $(NLACC_DIR)/cm_xta_tafsm.c
	$(CC) -c $(CPRDOPTS) $(NLACC_DIR)/cm_xta_tafsm.c -o $(SY_DIR)/cm_xta_tafsm.$(OBJ)

$(SY_DIR)/cm_xta_py.$(OBJ): $(NLACC_DIR)/cm_xta_py.c
	$(CC) -c $(CPRDOPTS) $(NLACC_DIR)/cm_xta_py.c -o $(SY_DIR)/cm_xta_py.$(OBJ)

$(SY_DIR)/cm_xta_inthdl.$(OBJ): $(NLACC_DIR)/cm_xta_inthdl.c
	$(CC) -c $(CPRDOPTS) $(NLACC_DIR)/cm_xta_inthdl.c -o $(SY_DIR)/cm_xta_inthdl.$(OBJ)

$(SY_DIR)/cm_xta_intreg.$(OBJ): $(NLACC_DIR)/cm_xta_intreg.c
	$(CC) -c $(CPRDOPTS) $(NLACC_DIR)/cm_xta_intreg.c -o $(SY_DIR)/cm_xta_intreg.$(OBJ)

$(SY_DIR)/cm_xta_res.$(OBJ): $(NLACC_DIR)/cm_xta_res.c
	$(CC) -c $(CPRDOPTS) $(NLACC_DIR)/cm_xta_res.c -o $(SY_DIR)/cm_xta_res.$(OBJ)

$(SY_DIR)/cm_xta_queue.$(OBJ): $(NLACC_DIR)/cm_xta_queue.c
	$(CC) -c $(CPRDOPTS) $(NLACC_DIR)/cm_xta_queue.c -o $(SY_DIR)/cm_xta_queue.$(OBJ)

$(SY_DIR)/cm_xta_flag.$(OBJ): $(NLACC_DIR)/cm_xta_flag.c
	$(CC) -c $(CPRDOPTS) $(NLACC_DIR)/cm_xta_flag.c -o $(SY_DIR)/cm_xta_flag.$(OBJ)

$(SY_DIR)/cm_xta_log.$(OBJ): $(NLACC_DIR)/cm_xta_log.c
	$(CC) -c $(CPRDOPTS) $(NLACC_DIR)/cm_xta_log.c -o $(SY_DIR)/cm_xta_log.$(OBJ)

$(SY_DIR)/cm_xta_slave.$(OBJ): $(NLACC_DIR)/cm_xta_slave.c
	$(CC) -c $(CPRDOPTS) $(NLACC_DIR)/cm_xta_slave.c -o $(SY_DIR)/cm_xta_slave.$(OBJ)

$(SY_DIR)/cm_xta_master.$(OBJ): $(NLACC_DIR)/cm_xta_master.c
	$(CC) -c $(CPRDOPTS) $(NLACC_DIR)/cm_xta_master.c -o $(SY_DIR)/cm_xta_master.$(OBJ)

$(SY_DIR)/cm_xta_reg.$(OBJ): $(NLACC_DIR)/cm_xta_reg.c
	$(CC) -c $(CPRDOPTS) $(NLACC_DIR)/cm_xta_reg.c -o $(SY_DIR)/cm_xta_reg.$(OBJ)

$(SY_DIR)/cm_xta_tst.$(OBJ): $(NLACC_DIR)/cm_xta_tst.c
	$(CC) -c $(CPRDOPTS) $(NLACC_DIR)/cm_xta_tst.c -o $(SY_DIR)/cm_xta_tst.$(OBJ)

$(SY_DIR)/cm_xta_ipc.$(OBJ): $(NLACC_DIR)/cm_xta_ipc.c
	$(CC) -c $(CPRDOPTS) $(NLACC_DIR)/cm_xta_ipc.c -o $(SY_DIR)/cm_xta_ipc.$(OBJ)

$(SY_DIR)/cm_xta_txn.$(OBJ): $(NLACC_DIR)/cm_xta_txn.c
	$(CC) -c $(CPRDOPTS) $(NLACC_DIR)/cm_xta_txn.c -o $(SY_DIR)/cm_xta_txn.$(OBJ)

$(SY_DIR)/cm_xta_intutl.$(OBJ): $(NLACC_DIR)/cm_xta_intutl.c
	$(CC) -c $(CPRDOPTS) $(NLACC_DIR)/cm_xta_intutl.c -o $(SY_DIR)/cm_xta_intutl.$(OBJ)

$(SY_DIR)/cm_xta_tmr.$(OBJ): $(NLACC_DIR)/cm_xta_tmr.c
	$(CC) -c $(CPRDOPTS) $(NLACC_DIR)/cm_xta_tmr.c -o $(SY_DIR)/cm_xta_tmr.$(OBJ)

$(SY_DIR)/cm_xta_dum.$(OBJ): $(NLACC_DIR)/cm_xta_dum.c
	$(CC) -c $(CPRDOPTS) $(NLACC_DIR)/cm_xta_dum.c -o $(SY_DIR)/cm_xta_dum.$(OBJ)


# Total eNodeB files build------------------------------------------------

$(SY_DIR)/nl_ex_ms.$(OBJ): $(NL_CODE_DIR)/nl_ex_ms.c $(NLALL_INC)
	$(CC) -c $(CPRDOPTS) $(CCnlFLAGS) $(NL_CODE_DIR)/nl_ex_ms.c -o $(SY_DIR)/nl_ex_ms.$(OBJ)

$(SY_DIR)/nl_init.$(OBJ): $(NL_CODE_DIR)/nl_init.c $(NLALL_INC)
	$(CC) -c $(CPRDOPTS) $(CCnlFLAGS) $(NL_CODE_DIR)/nl_init.c -o $(SY_DIR)/nl_init.$(OBJ)

$(SY_DIR)/nl_lmm.$(OBJ): $(NL_CODE_DIR)/nl_lmm.c $(NLALL_INC)
	$(CC) -c $(CPRDOPTS) $(CCnlFLAGS) $(NL_CODE_DIR)/nl_lmm.c -o $(SY_DIR)/nl_lmm.$(OBJ)

$(SY_DIR)/nl_ptmi.$(OBJ): $(NL_CODE_DIR)/nl_ptmi.c $(NLALL_INC)
	$(CC) -c $(CPRDOPTS) $(CCnlFLAGS) $(NL_CODE_DIR)/nl_ptmi.c -o $(SY_DIR)/nl_ptmi.$(OBJ)

$(SY_DIR)/nl_ptui.$(OBJ): $(NL_CODE_DIR)/nl_ptui.c $(NLALL_INC)
	$(CC) -c $(CPRDOPTS) $(CCnlFLAGS) $(NL_CODE_DIR)/nl_ptui.c -o $(SY_DIR)/nl_ptui.$(OBJ)

$(SY_DIR)/nl_pci_sel.$(OBJ): $(NL_CODE_DIR)/nl_pci_sel.c $(NLALL_INC)
	$(CC) -c $(CPRDOPTS) $(CCnlFLAGS) $(NL_CODE_DIR)/nl_pci_sel.c -o $(SY_DIR)/nl_pci_sel.$(OBJ)

$(SY_DIR)/nl_events.$(OBJ): $(NL_CODE_DIR)/nl_events.c $(NLALL_INC)
	$(CC) -c $(CPRDOPTS) $(CCnlFLAGS) $(NL_CODE_DIR)/nl_events.c -o $(SY_DIR)/nl_events.$(OBJ)

$(SY_DIR)/nl_alarm.$(OBJ): $(NL_CODE_DIR)/nl_alarm.c $(NLALL_INC)
	$(CC) -c $(CPRDOPTS) $(CCnlFLAGS) $(NL_CODE_DIR)/nl_alarm.c -o $(SY_DIR)/nl_alarm.$(OBJ)

$(SY_DIR)/nl_prach_sel.$(OBJ): $(NL_CODE_DIR)/nl_prach_sel.c $(NLALL_INC)
	$(CC) -c $(CPRDOPTS) $(CCnlFLAGS) $(NL_CODE_DIR)/nl_prach_sel.c -o $(SY_DIR)/nl_prach_sel.$(OBJ)

$(SY_DIR)/nl_earfcn_sel.$(OBJ): $(NL_CODE_DIR)/nl_earfcn_sel.c $(NLALL_INC)
	$(CC) -c $(CPRDOPTS) $(CCnlFLAGS) $(NL_CODE_DIR)/nl_earfcn_sel.c -o $(SY_DIR)/nl_earfcn_sel.$(OBJ)

$(SY_DIR)/nl_tmr.$(OBJ): $(NL_CODE_DIR)/nl_tmr.c $(NLALL_INC)
	$(CC) -c $(CPRDOPTS) $(CCnlFLAGS) $(NL_CODE_DIR)/nl_tmr.c -o $(SY_DIR)/nl_tmr.$(OBJ)

$(SY_DIR)/nl_pt_son.$(OBJ): $(NL_CODE_DIR)/nl_pt_son.c $(NLALL_INC)
	$(CC) -c $(CPRDOPTS) $(CCnlFLAGS) $(NL_CODE_DIR)/nl_pt_son.c -o $(SY_DIR)/nl_pt_son.$(OBJ)

$(SY_DIR)/nl_txpower_sel.$(OBJ): $(NL_CODE_DIR)/nl_txpower_sel.c $(NLALL_INC)
	$(CC) -c $(CPRDOPTS) $(CCnlFLAGS) $(NL_CODE_DIR)/nl_txpower_sel.c -o $(SY_DIR)/nl_txpower_sel.$(OBJ)

#$(SY_DIR)/example_client.$(OBJ): $(NL_CODE_DIR)/example_client.c $(NLALL_INC)
#	$(CC) -c $(CPRDOPTS) $(CCnlFLAGS) $(NL_CODE_DIR)/example_client.c -o $(SY_DIR)/example_client.$(OBJ)

# stack manager files build---------------------------------------------

$(SY_DIR)/sm_bdy1.$(OBJ): $(CM_SM_DIR)/sm_bdy1.c $(SYS_INC) $(LWR_INC)
	$(CC) -c $(CSMOPTS) $(CM_SM_DIR)/sm_bdy1.c -o $(SY_DIR)/sm_bdy1.$(OBJ)

$(SY_DIR)/sm_ex_ms.$(OBJ): $(CM_SM_DIR)/sm_ex_ms.c $(SYS_INC) $(LWR_INC)
	$(CC) -c $(CPRDOPTS) $(CSMOPTS) $(CM_SM_DIR)/sm_ex_ms.c -o $(SY_DIR)/sm_ex_ms.$(OBJ)

#$(SY_DIR)/smwrbdy1.$(OBJ): $(WRSM_DIR)/smwrbdy1.c $(SYS_INC) $(LWR_INC)
#	$(CC) -c $(CPRDOPTS) $(CSMOPTS) $(WRSM_DIR)/smwrbdy1.c -o $(SY_DIR)/smwrbdy1.$(OBJ)

#  interface specific files

$(SY_DIR)/lnl.$(OBJ): $(CM_CM_DIR)/lnl.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CCnlFLAGS) $(CM_CM_DIR)/lnl.c  -o $(SY_DIR)/lnl.$(OBJ)

$(SY_DIR)/nlu_pk.$(OBJ): $(CM_CM_DIR)/nlu_pk.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS) $(CCnlFLAGS) $(CM_CM_DIR)/nlu_pk.c -o $(SY_DIR)/nlu_pk.$(OBJ)

$(SY_DIR)/nlu_unpk.$(OBJ): $(CM_CM_DIR)/nlu_unpk.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS) $(CCnlFLAGS) $(CM_CM_DIR)/nlu_unpk.c -o $(SY_DIR)/nlu_unpk.$(OBJ)

# common library files
$(SY_DIR)/cm_hash.$(OBJ): $(CM_HASH_DIR)/cm_hash.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_HASH_DIR)/cm_hash.c -o $(SY_DIR)/cm_hash.$(OBJ)
	
$(SY_DIR)/cm_llist.$(OBJ): $(CM_LLIST_DIR)/cm_llist.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_LLIST_DIR)/cm_llist.c -o $(SY_DIR)/cm_llist.$(OBJ)
	
$(SY_DIR)/cm_os.$(OBJ): $(CM_LLIST_DIR)/cm_os.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_LLIST_DIR)/cm_os.c -o $(SY_DIR)/cm_os.$(OBJ)
	
$(SY_DIR)/cm_lib.$(OBJ): $(CM_LIB_DIR)/cm_lib.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_LIB_DIR)/cm_lib.c -o $(SY_DIR)/cm_lib.$(OBJ)
	
$(SY_DIR)/cm_bdy5.$(OBJ): $(CM_TMR_DIR)/cm_bdy5.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_TMR_DIR)/cm_bdy5.c -o $(SY_DIR)/cm_bdy5.$(OBJ)
	
$(SY_DIR)/cm_tpt.$(OBJ): $(CM_TMR_DIR)/cm_tpt.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_TMR_DIR)/cm_tpt.c -o $(SY_DIR)/cm_tpt.$(OBJ)
	
$(SY_DIR)/hit.$(OBJ): $(CM_TMR_DIR)/hit.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_TMR_DIR)/hit.c -o $(SY_DIR)/hit.$(OBJ)
	
$(SY_DIR)/lhi.$(OBJ): $(CM_TMR_DIR)/lhi.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_TMR_DIR)/lhi.c -o $(SY_DIR)/lhi.$(OBJ)

$(SY_DIR)/lsb.$(OBJ): $(CM_TMR_DIR)/lsb.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CSBOPTS) $(CM_TMR_DIR)/lsb.c -o $(SY_DIR)/lsb.$(OBJ)
	
$(SY_DIR)/cm_gen.$(OBJ): $(CM_CM_DIR)/cm_gen.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_CM_DIR)/cm_gen.c -o $(SY_DIR)/cm_gen.$(OBJ)

$(SY_DIR)/cm_ss7.$(OBJ): $(CM_SS7_DIR)/cm_ss7.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_SS7_DIR)/cm_ss7.c -o $(SY_DIR)/cm_ss7.$(OBJ)

$(SY_DIR)/cm_tkns.$(OBJ): $(CM_CM_DIR)/cm_tkns.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_CM_DIR)/cm_tkns.c -o $(SY_DIR)/cm_tkns.$(OBJ)

$(SY_DIR)/cm_dns.$(OBJ): $(CM_DNS_DIR)/cm_dns.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DNS_DIR)/cm_dns.c -o $(SY_DIR)/cm_dns.$(OBJ)

$(SY_DIR)/cm_inet.$(OBJ): $(CM_INET_DIR)/cm_inet.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_INET_DIR)/cm_inet.c -o $(SY_DIR)/cm_inet.$(OBJ)

$(SY_DIR)/cm_pasn1.$(OBJ): $(CM_ASN_DIR)/cm_pasn1.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_ASN_DIR)/cm_pasn1.c -o $(SY_DIR)/cm_pasn1.$(OBJ)

$(SY_DIR)/cm_pasn2.$(OBJ): $(CM_ASN_DIR)/cm_pasn2.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_ASN_DIR)/cm_pasn2.c -o $(SY_DIR)/cm_pasn2.$(OBJ)

$(SY_DIR)/cm_pasn3.$(OBJ): $(CM_ASN_DIR)/cm_pasn3.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_ASN_DIR)/cm_pasn3.c -o $(SY_DIR)/cm_pasn3.$(OBJ)

$(SY_DIR)/cm_pasn4.$(OBJ): $(CM_ASN_DIR)/cm_pasn4.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_ASN_DIR)/cm_pasn4.c -o $(SY_DIR)/cm_pasn4.$(OBJ)

$(SY_DIR)/cm_lte.$(OBJ): $(CM_ASN_DIR)/cm_lte.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_ASN_DIR)/cm_lte.c -o $(SY_DIR)/cm_lte.$(OBJ)

$(SY_DIR)/cm_mblk.$(OBJ): $(CM_MEM_DIR)/cm_mblk.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_MEM_DIR)/cm_mblk.c -o $(SY_DIR)/cm_mblk.$(OBJ)

$(SY_DIR)/cm_ss.$(OBJ): $(CM_CM_DIR)/cm_ss.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CMSOPTS) $(CM_CM_DIR)/cm_ss.c -o $(SY_DIR)/cm_ss.$(OBJ)

# System services--------------------------------------------------

$(SY_DIR)/ss_gen.$(OBJ): $(SS_DIR)/ss_gen.c $(SYS_INC) $(SS_INC)
	$(CC) -c $(COSOPTS) $(SS_DIR)/ss_gen.c -o $(SY_DIR)/ss_gen.$(OBJ)
 
$(SY_DIR)/ss_task.$(OBJ): $(SS_DIR)/ss_task.c $(SYS_INC) $(SS_INC)
	$(CC) -c $(COSOPTS) $(SS_DIR)/ss_task.c -o $(SY_DIR)/ss_task.$(OBJ)
 
$(SY_DIR)/ss_drvr.$(OBJ): $(SS_DIR)/ss_drvr.c $(SYS_INC) $(SS_INC)
	$(CC) -c $(COSOPTS) $(SS_DIR)/ss_drvr.c -o $(SY_DIR)/ss_drvr.$(OBJ)
 
$(SY_DIR)/ss_timer.$(OBJ): $(SS_DIR)/ss_timer.c $(SYS_INC) $(SS_INC)
	$(CC) -c $(COSOPTS) $(SS_DIR)/ss_timer.c -o $(SY_DIR)/ss_timer.$(OBJ)
 
$(SY_DIR)/ss_mem.$(OBJ): $(SS_DIR)/ss_mem.c $(SYS_INC) $(SS_INC)
	$(CC) -c $(COSOPTS) $(SS_DIR)/ss_mem.c -o $(SY_DIR)/ss_mem.$(OBJ)
 
$(SY_DIR)/ss_strm.$(OBJ): $(SS_DIR)/ss_strm.c $(SYS_INC) $(SS_INC)
	$(CC) -c $(COSOPTS) $(SS_DIR)/ss_strm.c -o $(SY_DIR)/ss_strm.$(OBJ)
 
$(SY_DIR)/ss_msg.$(OBJ): $(SS_DIR)/ss_msg.c $(SYS_INC) $(SS_INC)
	$(CC) -c $(COSOPTS) $(SS_DIR)/ss_msg.c -o $(SY_DIR)/ss_msg.$(OBJ)
 
$(SY_DIR)/ss_queue.$(OBJ): $(SS_DIR)/ss_queue.c $(SYS_INC) $(SS_INC)
	$(CC) -c $(COSOPTS) $(SS_DIR)/ss_queue.c -o $(SY_DIR)/ss_queue.$(OBJ)
 
$(SY_DIR)/ss_pack.$(OBJ): $(SS_DIR)/ss_pack.c $(SYS_INC) $(SS_INC)
	$(CC) -c $(COSOPTS) $(SS_DIR)/ss_pack.c -o $(SY_DIR)/ss_pack.$(OBJ)
 
$(SY_DIR)/ss_rtr.$(OBJ): $(SS_DIR)/ss_rtr.c $(SYS_INC) $(SS_INC)
	$(CC) -c $(COSOPTS) $(SS_DIR)/ss_rtr.c -o $(SY_DIR)/ss_rtr.$(OBJ)
 
# mtss Solaris -------------------------------------------------------
 
$(SY_DIR)/cm_mem.$(OBJ): $(CM_MEM_DIR)/cm_mem.c $(SYS_INC) $(SS_INC) $(MT_INC)
	$(CC) -c $(COSOPTS) $(CM_MEM_DIR)/cm_mem.c -o $(SY_DIR)/cm_mem.$(OBJ)
 
$(SY_DIR)/mt_ss.$(OBJ): $(OS_DIR)/mt_ss.c $(SYS_INC) $(SS_INC) $(MT_INC)
	$(CC) -c $(COSOPTS) $(OS_DIR)/mt_ss.c -o $(SY_DIR)/mt_ss.$(OBJ)
 
$(SY_DIR)/mt_id.$(OBJ): $(OS_DIR)/mt_id.c $(SYS_INC) $(SS_INC) $(MT_INC)
	$(CC) -c $(COSOPTS) $(OS_DIR)/mt_id.c -o $(SY_DIR)/mt_id.$(OBJ)

# portable files build--------------------------------------------------

$(SY_DIR)/rl_common.$(OBJ): $(RL_DIR)/rl_common.c $(SYS_INC) $(CM_INC) $(NLALL_INC)  
	$(CC) -c $(CPRDOPTS) $(RL_DIR)/rl_common.c -o $(SY_DIR)/rl_common.$(OBJ)

$(SY_DIR)/rl_rlog.$(OBJ): $(RL_DIR)/rl_rlog.c $(SYS_INC) $(CM_INC) $(NLALL_INC)  
	$(CC) -c $(CPRDOPTS) $(RL_DIR)/rl_rlog.c -o $(SY_DIR)/rl_rlog.$(OBJ)


#********************************************************************30**
#  
#        End of file:     nl.mak@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 18:02:37 2014
#    
#********************************************************************31*/
#
#********************************************************************40**
#  
#        Notes:
#  
#********************************************************************41*/
#
#********************************************************************50**
#
#********************************************************************51*/
#
#********************************************************************60**
#  
#       Revision history:
#  
#********************************************************************61*/
# 
#********************************************************************90**
#
#    ver       pat    init                  description
#----------- -------- ---- -----------------------------------------------
#/main/4      ---      ve  1. Initial release TeNB acc 1.1
#********************************************************************91*/

#DO NOT DELETE THIS LINE -- make depend depends on it.
