
#
#********************************************************************20**
#
#       Name:   LTE MAC - makefile
#
#       Type:   Makefile
#
#       Desc:   Compile, assemble and link product software for
#               various configurations. Further comments are
#               embedded in the file. The following targets are
#               defined for use:
#
#               This file supports a variety of environments and
#               build targets.
#
#               ENVIRONMENTS:
#
#               Solaris 2.x with SUNpro C
#
#               Solaris 2.x with GNU C (gcc)
#
#               Solaris 2.x with MRI C (mcc68k) cross compiled for
#               a relatively standard 68040 processor board
# 
#               Microsoft Visual C++ 4.x for Windows '95 and Windows NT
#               environments(msvc)
#
#               BUILD TARGETS:
#
#               acc              acceptance tests (with MTSS) -- default
#               pt               portable software (without MTSS) 
#               lib              library (with MTSS)
#
#               depend.acc       makedepend for acceptance tests
#               depend.pt        makedepend for portable software
#
#               clean            remove all object files
#               win_clean        remove all object files(Windows environment)
#
#       Sid:      rg.mak@@/main/3 - Sat Jul 30 02:21:19 2011
#
#       Prg:   st
#
#********************************************************************21*/
#
# Modifications required :
# For WinNT SSI :
#          BLDENV=win_acc (to be supplied on command line)
#          OBJ=$(NS_OBJ_SUFFIX)
#          make SS_DIR and MT_DIR point to path for WinNT SSI files
#          Replace MT_SRCS with NS_SRCS in PRDACC_SRCS
#          Replace MT_OBJS with NS_OBJS in PRDACC_OBJS
#          Put OSOPTS=$(WINOSOPTS) in acc/pt/lib target
#          LM_ACC_CMD_LINE shouldn't be present in PRDACCOPTS
#          use the ACC_INC_PATH in which VW_INC is not included
#
# For VxWorks SSI :
#          BLDENV=ppc_acc (to be supplied on command line)
#          OBJ=$(SOL_OBJ_SUFFIX)
#          make VW_DIR point to path for VxWorks SSI files
#          Put SS_DIR and MT_DIR as $(VW_DIR)
#          Replace MT_SRCS with VW_SRCS in PRDACC_SRCS
#          Replace MT_OBJS with VW_OBJS in PRDACC_OBJS
#          Put OSOPTS=$(VWOSOPTS) for acc rule
#          LM_ACC_CMD_LINE shouldn't be present in PRDOPTS
#          modify VW_INC appropriately to point to correct header files
#          use ACC_INC_PATH in which VW_INC is included
#
#=======================================================================


#=======================================================================
#
# macros for product specific options
#
# SECTION 1


#----------------- MAC product options --------------------------
# 
#Add the correct coupling options in PRDOPTS for FDD.
ifeq (${CMDOPT}, 1)
PRDOPTS=-DxLTE_TDD -DxTFU_TDD -DLTEMAC_MIMO -DLTEMAC_SPS -DTFU_UPGRADE -DLTE_L2_MEAS -DxLTEMAC_HDFDD -DLTEMAC_R9 -DRGR_SI_SCH -DRGR_CQI_REPT -DLTEMAC_RGU_PAD -DRGR_V1 -DLRG_V1 -DRGR_V2 -DRG -DCMFILE_REORG_1 -DCMFILE_REORG_2 -DSS_MT_TMR -DMT_TMR_CHANGES -DDEBUGP -URG_DEBUG -DCM_INET2 -DSS_FLOAT -DCMIET_LARGE_MAX_UDPRAW_SIZE -DLONG_MSG -DxRG_ULSCHED_AT_CRC -DxLTEMAC_DLUE_TMGOPTMZ -DLTEMAC_DRX -DTENB_ACC -DERRCLS_KW -DRGU_INF_OPTIMIZATION -DTENB_MULT_CELL_SUPPRT -DLTE_ADV -DRLOG_ENABLE_TEXT_LOGGING
endif

#Add the correct coupling options in PRDOPTS for TDD.
ifeq (${CMDOPT}, 2)
PRDOPTS=-DLTE_TDD -DxTFU_TDD -DLTEMAC_MIMO -DLTEMAC_SPS -DTFU_UPGRADE -DLTE_L2_MEAS -DxLTEMAC_HDFDD -DLTEMAC_R9 -DRGR_SI_SCH -DRGR_CQI_REPT -DLTEMAC_RGU_PAD -DRGR_V1 -DLRG_V1 -DLRG_V2 -DRGR_V2 -DRG -DCMFILE_REORG_1 -DCMFILE_REORG_2 -DSS_MT_TMR -DMT_TMR_CHANGES -DDEBUGP -URG_DEBUG -DCM_INET2 -DSS_FLOAT -DCMIET_LARGE_MAX_UDPRAW_SIZE -DLONG_MSG -DxRG_ULSCHED_AT_CRC -DxLTEMAC_DLUE_TMGOPTMZ -DTFU_MIMO -DxLTEMAC_UNUSED -DRG_PHASE2_SCHED -DLTEMAC_DRX -DERRCLS_KW -DDLHQ_RTT_OPT -DLOWLATENCY -DRGU_INF_OPTIMIZATION -DTENB_MULT_CELL_SUPPRT -DLTE_ADV -DTENB_MULT_CELL_SUPPRT
endif

#Add the correct coupling options in PRDOPTS for FDD with LTEMAC_HDFDD flag enabled.
ifeq (${CMDOPT}, 3)
PRDOPTS=-DxLTE_TDD -DxTFU_TDD -DLTEMAC_MIMO -DLTEMAC_SPS -DTFU_UPGRADE -DLTE_L2_MEAS -DLTEMAC_HDFDD -DLTEMAC_R9 -DRGR_SI_SCH -DRGR_CQI_REPT -DLTEMAC_RGU_PAD -DRGR_V1 -DLRG_V1 -DRGR_V2 -DRG -DCMFILE_REORG_1 -DCMFILE_REORG_2 -DSS_MT_TMR -DMT_TMR_CHANGES -DDEBUGP -URG_DEBUG -DCM_INET2 -DSS_FLOAT -DCMIET_LARGE_MAX_UDPRAW_SIZE -DLONG_MSG -DxRG_ULSCHED_AT_CRC -DxLTEMAC_DLUE_TMGOPTMZ -DLTEMAC_DRX -DERRCLS_KW -DRGU_INF_OPTIMIZATION -DTENB_MULT_CELL_SUPPRT -DLTE_ADV -DRLOG_ENABLE_TEXT_LOGGING
endif

#Add the correct coupling options in PRDOPTS for FDD with RG_ULSCHED_AT_CRC flag enabled.
ifeq (${CMDOPT}, 4)
PRDOPTS=-DxLTE_TDD -DxTFU_TDD -DLTEMAC_MIMO -DLTEMAC_SPS -DTFU_UPGRADE -DLTE_L2_MEAS -DxLTEMAC_HDFDD -DLTEMAC_R9 -DRGR_SI_SCH -DRGR_CQI_REPT -DLTEMAC_RGU_PAD -DRGR_V1 -DLRG_V1 -DRGR_V2 -DRG -DCMFILE_REORG_1 -DCMFILE_REORG_2 -DSS_MT_TMR -DMT_TMR_CHANGES -DDEBUGP -URG_DEBUG -DCM_INET2 -DSS_FLOAT -DCMIET_LARGE_MAX_UDPRAW_SIZE -DLONG_MSG -DRG_ULSCHED_AT_CRC -DxLTEMAC_DLUE_TMGOPTMZ -DLTEMAC_DRX -DERRCLS_KW -DRGU_INF_OPTIMIZATION -DTENB_MULT_CELL_SUPPRT -DLTE_ADV -DRLOG_ENABLE_TEXT_LOGGING
endif

#Add the correct coupling options in PRDOPTS for FDD with LTEMAC_DLUE_TMGOPTMZ flag enabled.
ifeq (${CMDOPT}, 5)
PRDOPTS=-DxLTE_TDD -DxTFU_TDD -DLTEMAC_MIMO -DLTEMAC_SPS -DTFU_UPGRADE -DLTE_L2_MEAS -DxLTEMAC_HDFDD -DxLTEMAC_R9 -DRGR_SI_SCH -DRGR_CQI_REPT -DLTEMAC_RGU_PAD -DRGR_V1 -DLRG_V1 -DRGR_V2 -DRG -DCMFILE_REORG_1 -DCMFILE_REORG_2 -DSS_MT_TMR -DMT_TMR_CHANGES -DDEBUGP -URG_DEBUG -DCM_INET2 -DSS_FLOAT -DCMIET_LARGE_MAX_UDPRAW_SIZE -DxLONG_MSG -DxRG_ULSCHED_AT_CRC -DLTEMAC_DLUE_TMGOPTMZ -DLTEMAC_DRX -DERRCLS_KW -DRGU_INF_OPTIMIZATION -DTENB_MULT_CELL_SUPPRT -DLTE_ADV -DRLOG_ENABLE_TEXT_LOGGING
endif

#Add the correct coupling options in PRDOPTS for FDD with LTE Avanced flags enabled.
ifeq (${CMDOPT}, 6)
PRDOPTS=-DxLTE_TDD -DxTFU_TDD -DLTEMAC_MIMO -DTFU_UPGRADE -DLTE_L2_MEAS -DxLTEMAC_HDFDD -DLTEMAC_R9 -DRGR_SI_SCH -DRGR_CQI_REPT -DLTEMAC_RGU_PAD -DRGR_V1 -DLRG_V1 -DRGR_V2 -DRG -DCMFILE_REORG_1 -DCMFILE_REORG_2 -DSS_MT_TMR -DMT_TMR_CHANGES -DDEBUGP -URG_DEBUG -DCM_INET2 -DSS_FLOAT -DCMIET_LARGE_MAX_UDPRAW_SIZE -DLONG_MSG -DxRG_ULSCHED_AT_CRC -DxLTEMAC_DLUE_TMGOPTMZ -DLTEMAC_DRX -DERRCLS_KW -DRGU_INF_OPTIMIZATION -DTENB_MULT_CELL_SUPPRT -DLTE_ADV -DRLOG_ENABLE_TEXT_LOGGING
endif

#Add the correct coupling options in PRDOPTS for PFS Simulator.
ifeq (${CMDOPT}, 7)
PRDOPTS=-DxLTE_TDD -DxTFU_TDD -DLTEMAC_MIMO -DLTEMAC_SPS -DTFU_UPGRADE -DLTE_L2_MEAS -DxLTEMAC_HDFDD -DLTEMAC_R9 -DRGR_SI_SCH -DRGR_CQI_REPT -ULTEMAC_RGU_PAD -DRGR_V1 -DLRG_V1 -DRGR_V2 -DRG -DCMFILE_REORG_1 -DCMFILE_REORG_2 -DSS_MT_TMR -DMT_TMR_CHANGES -DDEBUGP -URG_DEBUG -DCM_INET2 -DSS_FLOAT -DCMIET_LARGE_MAX_UDPRAW_SIZE -DLONG_MSG -DxRG_ULSCHED_AT_CRC -DxLTEMAC_DLUE_TMGOPTMZ -DLTEMAC_DRX -DTENB_ACC -DERRCLS_KW -DRGU_INF_OPTIMIZATION -DTENB_MULT_CELL_SUPPRT -DLTE_ADV  -DRG_PFS_STATS
endif
#-------------------System Service options----------------------
GENOSOPTS= -DCMFILE_REORG_1 -DCMFILE_REORG_2 -DSS_MT_TMR -DMT_TMR_CHANGES

# For No error class
#PRDOPTS=-DRG -DCMFILE_REORG_1 -DCM_INET2

# Product options for portable build
#Add the correct coupling option in below for portble build
PRDPTOPTS=$(PRDOPTS) -DRG $(GENOSOPTS) -DTFU_VER_2

# Product options for acceptance test build
# Remove -DRG_ACC_CMD_LINE if your system doesn't support SGetOpts (command
# line inputs)

CMD_LINE=-DRG_ACC_CMD_LINE

#For Windows Add -DSS_DRVR_SUPPORT
#Add the correct coupling options in PRDACCOPTS below.
PRDACCOPTS=$(PRDOPTS) -DRG -DKW -DNH -DNX -DRM -DTF -DSM $(CMD_LINE) -DCMXTA_MASTER -DCMXTA_RET_ERR_NONE  -ULCSCH -ULCRG -DLCTFU -DLCCRG -DLCRGU -DLCRGR -DLCLRG -DLCRGMILRG -DLCRGUIRGU -DLCRGUICRG -DLCRGUIRGR -DLCRGLITFU -DLCSMLILRG -DLCNHLICRG -DLCNXLIRGR -DLCKWLIRGU -DLCTFUITFU -DRGM_LC -DRG_PHASE2_SCHED -DLONG_MSG -DRM_INTF -ULCPRG -DRLOG_ENABLE_TEXT_LOGGING

# Product options for library build
PRDLIBOPTS=$(PRDOPTS) -DDBG4 

#=======================================================================
#
# macros for specific OS
#
# SECTION 2

# MOS Product specific option define
MSCOPTS=-DMS -DCMFILE_REORG_1 

# MTSS Product specific option define
MTCOPTS = 

# Options for compilation with different OS's
# Default is for Portable build
# For acceptance test build either uncomment specific OS environment
# required or specify on command line
# Portable build options
PTOSOPTS="-DSS_MT_TMR -DMT_TMR_CHANGES -DPORTVER"

# Options for acceptance test build with VrTx Os
VXOSOPTS="-DVX"

# Options for acceptance test build with VxWorks Os
#VWOSOPTS="-DVW"
VWOSOPTS=-DSS_VW -DSS -DCMFILE_REORG_1 -DSS_DRVR_SUPPORT -DVW_COMPILE -DCMINETFLATBUF -DCMIET_LARGE_MAX_UDPRAW_SIZE -DDEBUGNOEXIT


# Options for acceptance test build with WINNT Os kernel build
WINOSOPTS="-DWINNT"
#WINOSOPTS="-DWINNT -DNS -DSS -DCMFILE_REORG_1"

# Options for acceptance test build with MTSS - MOS Multithread OS
# To be enabled for multithreaded MAC
MTOSOPTS=-DSS_MT -DSS -DCMFILE_REORG_1 -DSS_MT_TMR -DMT_TMR_CHANGES -DSS_SINGLE_THREADED -D_REENTRANT -DDEBUGNOEXIT -DSS_DRVR_SUPPORT -DLONG_MSG -DTENB_ACC

# Options for library build with MTSS - MOS multithread OS
# To be enabled for multithreaded MAC
#LIBOSOPTS="-DSS_MT -DSS  "
LIBOSOPTS="-DSS_MT_TMR -DMT_TMR_CHANGES -DSS_MT -DSS  -DSS_SINGLE_THREADED"

# General OSOPTS. For portable build PTOSOPTS, for acceptante MTOSOPTS if using
# Trillium's MTSS solaris system services, for all others use one of the above
# or customer specific flag

#NSOSOPTS=-DNS -DSS_OLD_THREAD -DNS_ENB_MGMT -DSS_DRVR_SUPPORT

#OSOPTS=$(PTOSOPTS)
OSOPTS=$(MTOSOPTS)
#OSOPTS=$(GENOSOPTS) $(VWOSOPTS)
# For Windows
#OSOPTS=$(GENOSOPTS) $(NSOSOPTS)



#=======================================================================
# SECTION 3
# Treat each of the following as examples and modify to specific product
# requirements
#
# macro for output file name and makefile name 
#
BASENAME=rg

MAKENAME=$(BASENAME).mak

# default acceptance test for Solaris cc environment
#BINACC=$(BASENAME)_acc
BINACC=rg_acc

# default portable for Solaris cc environment
BINPT="$(BASENAME)_pt"

# default portable build for KlocWork
BINKW="$(BASENAME)_kw"

# default library for Solaris cc environment
BINLIB="$(BASENAME)_lib.lib"


# Internal targets for the acceptance test build
MAKEACC=mkacc
ACCBIN=$(BASENAME)_acc
MAKEINT=mkint
INTBIN=$(BASENAME)_int

# Internal target for the portable build
MAKEPT=mkpt
PTBIN=$(BASENAME)_pt

# Internal target for the kw build
MAKEKW=mkkw
KWBIN=$(BASENAME)_kw

# Internal target for the library build
MAKELIB=mklib
LIBBIN=$(BASENAME)_lib.lib


# Internal target for makedepend
DEPEND=depend

# Build targets for testing in different environments

# Build with the Solaris CC Compiler and linker
# Acceptance Test Build
BINSOLACC=sol_acc
BINSOLINT=sol_int
# Portable Build
BINSOLPT=sol_pt
# Library Build
BINSOLLIB=sol_lib


# Build with the GNU Compiler and linker on Solaris
# Acceptance Test Build
BINGNUACC=gnu_acc
BINGNUINT=gnu_int
# Portable Build
BINGNUPT=gnu_pt
# library Build
BINGNULIB=gnu_lib
# KlocWork Build
BINGNUKW=gnu_kw

# Build with the GNU Compiler and linker on Solaris
# Acceptance Test Build
BINGPPACC=gpp_acc
BINGPPINT=gpp_int
BINGPPPT=gpp_pt
BINGPPLIB=gpp_lib

# Build with the GNU Compiler and linker on Solaris
# Acceptance Test Build
BINCPPACC=cpp_acc
BINCPPINT=cpp_int
BINCPPPT=cpp_pt
BINCPPLIB=cpp_lib


# Build with the Insite Memory Check Programs - Acceptance Tests Only
# Acceptance Test Build
BININSITEACC=ins_acc
BININSITEINT=ins_int

# Build with the Visual C++ on Windows NT or Windows 95 (user space only)
# Acceptance Test Build
BINWINACC=win_acc
BINWININT=win_int
# Portable Build
BINWINPT=win_pt
# Library Build
BINWINLIB=win_lib

# Build with the Microtek MRI C Compiler on Solaris - portable only
BINMRIPT=mri_pt

# Build with the Solaris cross compiler for VxWorks Power PC
# Acceptance Test Build
BINPPCACC=ppc_acc
BINPPCINT=ppc_int

#Build with the cc386 compiler and liner on 
BINVWACC=vw_acc

# Build with the GNU compiler and linker on Linux
# Acceptance Test Build
BINLNXACC=lnx_acc
BINLNXINT=lnx_int
# Portable Build
BINLNXPT=lnx_pt
#purcov build
BINLNXPACC=lnx_pacc
BINPURACC=pur_acc
#Library Build
BINLNXLIB=lnx_lib


#=======================================================================
#
# macro for directories and include paths
#
# SECTION 4
# Treat each of the following as examples and modify to specific product
# requirements



# Common files directory 
CM_DIR=../../cm/

# MAC directory
RG_DIR=../../ltemac

# Parent MAC directory
GK_DIR=../../ltemac

# Sample MAC User/provider directory
RG_SAMPLE_DIR=.

# common stack manager files directory 
SM_DIR=../../cm

# MAC stack manager directory
SM_DIR=../../cm

# WIN Include directory
NS_DIR=/u/prd/rtr/ns

# mos directory
# OS_DIR=
# OS_DIR=$(NS_DIR)
OS_DIR=../../mt_acc

# Common SSI directory
SS_DIR=../../mt_acc
#SS_DIR=/u/prd/rtr/vw
#SS_DIR=$(NS_DIR)

# Solaris MTSS specific dir.
MT_DIR=../../mt_acc
#MT_DIR=$(NS_DIR)

# VxWorks include directory
VW_DIR=/u/prd/rtr/vw

# acceptance directory
RGACC_DIR=.

#build directory
SY_DIR=.

#Python directory
#PY_DIR=/usr/local/include/python2.4
#PY_DIR=/usr/ccpu/python/linux/64bit/python-2.4.4
#PY_DIR=/usr/ccpu/python/solaris/10/32bit/python-2.4.4/include/python2.4
PY_DIR1=/usr/ccpu/python/linux/32bit/python-2.4.4/include/python2.4
PY_DIR=/usr/ccpu/python/linux/32bit/python-2.4.4/lib/python2.4 -I$(PY_DIR1)
#RLOG directory
RL_DIR=../../rlog/

#include path for VxWorks
# include path VxWorks environment
VW_INC=/tools/vxworks/ppc/target/h
#VW_INC=C:/WindRiver/vxworks-6.3/target/h
#VW_INC1=C:/WindRiver/vxworks-6.3/target/h/wrn
#VW_INC2=C:/WindRiver/vxworks-6.3/target/h/wrn/coreip
#VW_INC3=C:/WindRiver/vxworks-6.3/target/h/wrn/coreip/netinet
#VW_INC4=C:/WindRiver/vxworks-6.3/sys-include


# portable include path
PT_INC_PATH="-I$(CM_DIR) -I$(RG_DIR)"
# for m68k 
#PT_INC_PATH="-I$(CM_DIR) -I$(LM_DIR) -I/usr/include"

# library include path
LIB_INC_PATH="-I$(RG_DIR) -I$(SY_DIR) -I$(CM_DIR) -I$(SS_DIR) -I$(MT_DIR)"

# acceptance test include path
ACC_INC_PATH="-I$(SY_DIR) -I$(RG_DIR) -I$(CM_DIR) -I$(RGACC_DIR) -I$(SM_DIR) \
	          -I$(SM_DIR)  -I$(OS_DIR) -I$(RG_SAMPLE_DIR)\
              -I$(MT_DIR) -I$(SS_DIR) -I$(PY_DIR) -I$(RL_DIR)"

# acceptance test include path for VXWORKS
#ACC_INC_PATH="-I$(RG_DIR) -I$(CM_DIR) -I$(RGACC_DIR) -I$(SM_DIR) \
#	          -I$(SM_DIR)  -I$(OS_DIR) -I$(RG_SAMPLE_DIR)\
#              -I$(VW_DIR) -I$(VW_INC) -I$(VW_INC1) -I$(VW_INC2) -I$(VW_INC3)\
#	       -I$(VW_INC4)"

# MTSS - files include path
MTINC_PATH=-I$(CM_DIR) -I$(SS_DIR) -I$(MT_DIR)

#=======================================================================
#
# macros for environments
#
# SECTION 5

  
#----------------------------------------- Sun C for SPARC
#
# These flags define the environment required to build an image on
# a Sun/SPARC workstation with Sun Spro C version 4.0 running
# Solaris 2.4
#
# For ANSI Compilation 
SOLENV="-DSUNOS -DANSI -D__EXTENSIONS__"
SOLPTENV="-DSUNOS -DANSI -D__EXTENSIONS__"
SOLCOPTS="-Xa -g "

# For non-ANSI Compilation 
#SOLENV="-DSUNOS -D__EXTENSIONS__"
#SOLPTENV="-DSUNOS -D__EXTENSIONS__"
#SOLCOPTS="-g "

#For 64 Bit Compilation
#SOLCOPTS="-g -mt -xarch=v9 -DALIGN_64BIT -DBIT_64"
#SOLLOPTS="-mt -xarch=v9 -o $(OUTNAME) -lpthread -lrt -lpython2.4 -lsocket -lnsl -lm"
#SOLPTLOPTS="-mt -xarch=v9 -o $(OUTNAME) -lpthread -lrt -lsocket -lnsl"

SOLCC="cc"
SOLLD="cc"
SOLLIBLD="/usr/ccs/bin/ld"
SOLLOPTS="-o $(OUTNAME) -lpthread -lrt -lsocket -lnsl -lpython2.4 -lm -ldl"
SOLPTLOPTS="-o $(OUTNAME) -lpthread -lrt -lsocket -lnsl -lm -ldl"

SOLLIBS=""
SOLLINT="lint"
SOLLNTOPTS="-c -F -p -v"

# for library compilation
SOLLIBOPTS="-r -o $(OUTNAME)"


# SUN SPARC Compiler With Insight---------------------------------------------
#
# These flags define the environment required to build an image on
# a Sun/SPARC workstation with SUN Spro C version 4.0 C compiler running
# Solaris 2.4 , with the INSURE(insight) run time memory check tool.
#
# For ANSI Compilation
INSENV="-DSUNOS -DANSI -DPURE -DUSE_PURE -DSS_LINUX"
INSCOPTS="-Xa -g -insure++ -uninit_min_size=1"
#INSCOPTS=""
 
# For non-ANSI Compilation
#INSENV=-DSUNOS -DPURE
#INSCOPTS="-g"
INSCOPTS="-g -DSO_INSURE "

 
INSCC="insure -m32"
INSLD="insure -m32"
#INSCC="/usr/local/bin.linux2/insure"
#INSLD="/usr/local/bin.linux2/insure"
INSLOPTS="-o $(OUTNAME)"
INSLIBS="-Xlinker -export-dynamic -lnsl -lpthread -lpython2.4 -lm -ldl -lutil -lrt"
INSLINT="lint"
INSLNTOPTS="-c -F -p -v"


#----------------------------------------- GNU gcc for SPARC 
#
# These flags define the environment required to build an image on
# a Sun/SPARC workstation with GNU C version 2.5.7 (or greater) running
# Solaris 2.4
#
# For ANSI Compilation
GNUENV="-DSUNOS -DANSI -DSOLARIS -DSPARC -DPROC_SPARC -DUNIX -D__EXTENSIONS__"
GNUPTENV="-DSUNOS -DANSI -DSOLARIS -DSPARC -DPROC_SPARC -DUNIX -D__EXTENSIONS__ -DDONT_USE_SYS_LIB"

# For non-ANSI Compilation
#GNUENV="-DSUNOS D__EXTENSIONS__"

#/* for m68k compiler */
#GNUENV="-DSUNOS -DANSI -DELVIS_68040 -DNOERRCHK -DNO_ERRCLS -DNOCONAVL"
#GNUCC="m68k-coff-gcc"
#GNULD="m68k-coff-ld"
#GNULIBLD="ld"
#GNUCOPTS="-m68040 -Wall -fno-strict-aliasing -Wno-comment -pipe -Wshadow \
#-Wcast-qual  -Wstrict-prototypes -Wmissing-prototypes"
#GNULOPTS="-A -o $(OUTNAME) -Tlinker.ld -Map=lm_pt.map" 

GNUCC=gcc
GNULD=gcc


GNULIBLD="/usr/ccs/bin/ld"

GNUCOPTS=" -g3 -Wimplicit -Wunused -Wcomment -Wchar-subscripts \
-Wparentheses -Wformat -Winline -Wreturn-type -fPIC \
-Wstrict-prototypes -Wmissing-prototypes -pedantic -Wshadow -Wcast-qual"
#non-ANSI compilation 
#GNUCOPTS=" -g3 -Wimplicit -Wunused -Wcomment -Wchar-subscripts \
#-Wparentheses -Wformat -Winline -Wreturn-type -fPIC \
#-pedantic -Wshadow -Wcast-qual"


#For 64 Bit compilation
#GNUCOPTS="-g -m64 -DALIGN_64BIT -DBIT_64"
#GNULOPTS="-m64 -64 -DALIGN_64BIT -DBIT_64 -o $(OUTNAME) -lsocket -lnsl -lpython2.4 -lm -ldl -lposix4"
#GNUPTLOPTS="-m64 -64 -DALIGN_64BIT -DBIT_64 -o $(OUTNAME) -lsocket -lnsl -lm -ldl -lposix4"

#g++ options
#GNUCOPTS="-g3 -Wall -fno-strict-aliasing -Wno-comment -pipe -Wcast-qual \
#          -Wstrict-prototypes -Wmissing-prototypes"

GNULOPTS="-o $(OUTNAME) -lsocket -lnsl -lpython2.4 -lm -ldl -lposix4"
GNUPTLOPTS="-o $(OUTNAME) -lsocket -lnsl -lm -ldl -lposix4"
#GNULOPTS="-o $(OUTNAME) -lpthread" 
GNULIBS=""
GNULINT="lint"
GNULNTOPTS="-c -F -p -v"

# for library compilation
GNULIBOPTS="-r -o $(OUTNAME)"

#----------------------------------------- c++ compiler
#
# These flags define the environment required to build an image on
# a Sun/SPARC workstation with GNU C version 2.5.7 (or greater) running
# Solaris 2.4
#
CPPENV="-DSUNOS -DANSI -D__EXTENSIONS__"
CPPCC=CC
CPPLD=CC
#change for LIB complaion. verify the path od ld.
CPPLIBLD=/usr/ccpu/suntools/bin/ld
CPPCOPTS="-g "
CPPLOPTS="-o $(OUTNAME) -lpthread -lposix4 -lsocket -lnsl -lpython2.4 -lm -ldl"
CPPPTLOPTS="-o $(OUTNAME) -lpthread -lposix4 -lsocket -lnsl -lm -ldl"
CPPLIBOPTS="-r -o $(OUTNAME)"
CPPLIBS=""
CPPLINT="lint"
CPPLNTOPTS="-c -F -p -v"

#----------------------------------------- g++ compiler
#
# These flags define the environment required to build an image on
# a Sun/SPARC workstation with GNU C version 2.5.7 (or greater) running
# Solaris 2.4
#
GPPENV="-DSUNOS -DANSI "
GPPCC=g++
GPPLD=g++
GPPLIBLD=/usr/ccpu/suntools/bin/ld
GPPCOPTS="-g -Wall -fno-strict-aliasing -Wno-comment -pipe \
	     -Wredundant-decls"
GPPLOPTS="-o $(OUTNAME) -lpthread -lposix4 -lpython2.4 -lsocket -lnsl -lm -ldl"
GPPPTLOPTS="-o $(OUTNAME) -lpthread -lposix4 -lsocket -lnsl -lm -ldl"
GPPLIBOPTS="-r -o $(OUTNAME)"
GPPLIBS=""
GPPLINT="lint"
GPPLNTOPTS="-c -F -p -v"

# GNU gcc compiler for Linux------------------------------------------
#
# These flags define the environment required to build an image on
# a Linux workstation with GNU C version 2.5.7 (or greater)
#
# For ANSI Compilation
LNXENV="-DSUNOS -DANSI -DSS_LINUX -DSSI_DEBUG_LEVEL1 -UNO_ERRCLS -DNOCONAVL -UUSE_PURE -D_GNU_SOURCE"
LNXCOPTS="-g3 -Wall  -fno-strict-aliasing -Wno-comment -pipe -Wshadow -Wcast-qual \
	-Wstrict-prototypes -Wmissing-prototypes -pedantic \
	-Wimplicit -Wunused -fsigned-char -Wcast-align --std=c99"
LNXPTENV="-DSUNOS -DANSI -DSS_LINUX"

# For non-ANSI Compilation
#LNXENV="-DSUNOS -DSS_LINUX"
#LNXCOPTS="-g3 -pipe -pedantic -Wall -Wno-comment -Wshadow \
#          -Wcast-align -Wcast-qual"
#LNXPTENV="-DSUNOS -DSS_LINUX -DDONT_USE_SYS_LIB"

# For Purify accpetance build
ifeq ($(CCPU_PURIFY),y)
LNXCC="purify gcc -m32"
LNXLD="purify gcc -m32"
else
LNXCC="gcc -m32"
LNXLD="gcc -m32"
endif

PURENV="-DSUNOS -DSS_LINUX -DANSI -DPURE -DUSE_PURE -DNOCONAVL"
PURCC="purify gcc"
PURLD="purify gcc"
PURLOPTS="-o $(OUTNAME) -lpthread -lnsl -lrt -Xlinker -zmuldefs -export-dynamic -lpython2.4 -lm -ldl -lutil"
PURCOPTS="-g3 -ansi -Wall -fno-strict-aliasing -Wno-comment -pipe -Wshadow -Wcast-qual \
	-Wstrict-prototypes -Wmissing-prototypes -pedantic \
	-Wimplicit -Wunused -fsigned-char -Wcast-align --std=c99"
PURLIBS=""
LNXLIBLD="ld"
PLNXCC="purecov gcc -m32"
PLNXLD="purecov gcc -m32"
#LNXCC="/usr/local/Rational/releases/PurifyPlus.2003a.06.13/i386_linux2/bin/purify gcc -g"
#LNXLD="/usr/local/Rational/releases/PurifyPlus.2003a.06.13/i386_linux2/bin/purify gcc -g"
LNXLOPTS="-o $(OUTNAME) -lpthread -lnsl -lrt -Xlinker -zmuldefs -export-dynamic -lpython2.4 -lm -ldl -lutil"
LNXPTLOPTS="-o $(OUTNAME) -lpthread -lnsl -lrt -Xlinker -zmuldefs -export-dynamic -lm -ldl -lutil"
LNXLIBOPTS="-r -o $(OUTNAME)"

#For 64 Bit compilation
#LNXCC="gcc -m64 -DALIGN_64BIT -DBIT_64"
#LNXLD="gcc -m64"
#LNXCOPTS="-g3 -ansi -Wall -fno-strict-aliasing -Wno-comment -pipe -Wshadow -Wcast-qual \
#        -Wstrict-prototypes -Wmissing-prototypes -pedantic \
#        -Wimplicit -Wunused"
#LNXLOPTS="-o $(OUTNAME) -lpthread -lrt -Xlinker -zmuldefs -export-dynamic -lpython2.4 -lm -ldl -lutil"
#LNXPTLOPTS="-o $(OUTNAME) -lpthread -lrt -Xlinker -zmuldefs -export-dynamic -lm -ldl -lutil"

LNXLIBS=""
LNXLINT="lint"
LNXLNTOPTS="-c -F -p -v"
LNXLIBOSOPTS="-DSS_MT -D_REENTRANT -D__EXTENSIONS__  -DDEBUGNOEXIT -D_GNU_SOURCE -DSS_LINUX"


# MRI mcc68k compiler for 68040-----------------------------------------
#
# These flags define the environment required to build an image for
# a Motorola MVME162 Board (68040) with Microtec Research C version 4.4
# for a portable environment.
#
# For ANSI Compilation
MRIENV="-DELVIS_68040 -DANSI -DNOERRCHK -DNO_ERRCLS -DNOCONAVL -DSTDIO_INCLD"
#MRIENV="-DELVIS_68040 -DANSI  -DNOCONAVL -DSTDIO_INCLD"
 
# For non-ANSI Compilation
#MRIENV="-DELVIS_68040 -DNOERRCHK -DNO_ERRCLS -DNOCONAVL"
 
MRICC="mcc68k"
MRILD="mcc68k"
MRICOPTS="-p68040 -H -A -v -Fsm -O -Ob -Oe -Ot -nKc -nKm  -Mcp -Mdp -Ml -Gf"
MRILOPTS="-e$(OUTNAME).lnk -Wl,\"-m > $(OUTNAME).map -o $(OUTNAME).vcs -F s\""
MRILOPTS="-Wl,\"-m > $(OUTNAME).map -o $(OUTNAME).vcs -F s\""
MRILIBS="$(LIB_PATH)/mcc68kpc040.lib"
MRILINT=""
MRILNTOPTS=""
 
 
# Microsoft Visual C++ for Win 95/NT------------------------------------
#
# These flags define the environment required to build an image for
# a Windows '95 or Windows NT environment
#
#
# For ANSI Compilation
#WINENV="-DWIN32 -DANSI -DWIN2K -DWIN32_LEAN_AND_MEAN"
WINENV="-DWIN32 -DANSI -DWIN2K -DWIN32_LEAN_AND_MEAN -D_CRT_SECURE_NO_DEPRECATE -DSS_DRVR_SUPPORT"
 
# For non-ANSI Compilation
#WINENV="-DWIN32"
 
WINCC="cl"
WINLD="cl"
WINCOPTS="-Od -W3 -Zi -Yd"
WINLOPTS="-o $(OUTNAME) -F25000"
WINLIBS="ws2_32.lib -link -debug:full -debugtype:cv"
WINLINT=""
WINLNTOPTS=""

# for library compilation
WINLIBOPTS="-r -o $(OUTNAME)"

# cc386 for VxWorks - Pentium Target
# These flags define the environment required to build an image on Vxworks
# with cc386 on Pentium Target
#
# For ANSI Compilation
VWINTENV="-DANSI -DCPU=PENTIUM -DCPU_VARIANT=PENTIUMPRO -DPQUICCADS"
VWINTCOPTS="-g -mpentium -msoft-float -fvolatile -fno-builtin -Wall \
	      -Wno-comment -ansi -pedantic -nostdinc -Wshadow \
         -Wcast-qual -fsigned-char"
VWINTLIBS="-lsocket"

# For non-ANSI Compilation
#VWINTENV="-DCPU=PENTIUM -DCPU_VARIANT=PENTIUMPRO -DPQUICCADS"
#VWINTCOPTS="-g -mpentium -msoft-float -fvolatile -fno-builtin -Wall \
#	       -Wno-comment -pipe -nostdinc -Wshadow -Wredundant-decls \
#         -Wcast-qual -fsigned-char"

VWINTCC="cc386 -mcpu=pentium"
VWINTLD="ld386"
VWINTLOPTS="-o $(OUTNAME) -r"
VWINTLIBS=""
 
# ccppc cross compiler on Solaris for Vx Works on PPC--------------------
# These flags define the environment required to build an image on a Sun/SPARC
# workstation with ccppc v. 2.7.2 running Solaris 2.5.1
#
# For ANSI Compilation
#For VXWORKS
PPCENV=-DCPU=SIMNT -DANSI -DPQUICCADS -DVW_COMPILE -DCMINETFLATBUF
PPCCOPTS=-g -mtune=i486 -fno-builtin -Wall \
	      -Wno-comment -ansi -pedantic -pipe -nostdinc -Wshadow \
	      -Wcast-qual -fsigned-char

#PPCENV="-DCPU=PPC860 -DCCPPC -DANSI -DPQUICCADS"
#PPCENV=-DPCORE -DCPU=PPC604 -DANSI -DCCPPC
#PPCCOPTS="-mcpu=860 -msoft-float -fvolatile -fno-builtin -Wall -fno-strict-aliasing \
#              -Wno-comment -ansi -pedantic -pipe -nostdinc -Wshadow \
#              -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes"

PPCCC=ccpentium
PPCLD=ldpentium
#PPCCC="/tools/wind/host/sun4-solaris2/bin/ccppc"
#PPCLD="/tools/wind/host/sun4-solaris2/bin/ldppc"
#PPCLOPTS=-r -Map $(OUTNAME).map -o $(OUTNAME)
PPCLOPTS=-r -e vwMain -Map $(OUTNAME).map -o $(OUTNAME)
PPCLIBS=
PPCLINT=
PPCLNTOPTS=

# Microsoft Visual C++ for DOS------------------------------------------
#
# These flags define the environment required to build an image for
# a DOS environment
#
# This environment is TBD
#
# For ANSI Compilation
DOSENV="-DMSC60 -DDOS -DANSI"
 
# For non-ANSI Compilation
#DOSENV="-DMSC60 -DDOS"
 
DOSCC="cl"
DOSLD="cl"
DOSCOPTS="-Od -W3 -Zi -Yd -Gx- -Gd -Gy"
DOSLOPTS="@$(OUTNAME).lnk /ST:25000 /CO /NOI /NOE"
DOSLIBS=""
DOSLINT=""
DOSLNTOPTS=""
# legacy flag for x86 machines
#
# define if required (only for DOS!).
 
#
# -AH -- huge model
# -AL -- large model
# -AS -- small model
#
MODEL=
 
 
# Actual Build Environment----------------------------------------------
#
# This is the actual environment used, set it appropriately
# (default Solaris)
# Uncomment this for default compilation under the Solaris
# environment for portable build and the acceptance test build
#ENV=$(SOLENV)
#CC=$(SOLCC)
#LD=$(SOLLD)
#COPTS=$(SOLCOPTS)
#LOPTS=$(SOLLOPTS)
#LIBS=$(SOLLIBS)
#LINT=$(SOLLINT)
#LNTOPTS=$(SOLLNTOPTS)
 
# object file suffix----------------------------------------------------
#
# this defaults to 'o' for most UNIX based systems
# this can be set to 'obj' for DOS/Windows/NT platforms
#
SOL_OBJ_SUFFIX=o
NS_OBJ_SUFFIX=obj
OBJ=$(SOL_OBJ_SUFFIX)
#OBJ=$(NS_OBJ_SUFFIX)
 


#=======================================================================
#
# macros for compile time options
#
 
# portable options
CPTOPTS=$(MODEL) $(ENV) $(COPTS) $(INC_PATH) $(OSOPTS) -DRG_PT_BUILD
 
# acceptance test options - OSOPTS should be set to required environment
COSOPTS=$(MODEL) $(ENV) $(COPTS) $(INC_PATH) $(OSOPTS)
 
# Combined environment, OS, compiler options and include path
CENVOPTS=$(MODEL) $(ENV) $(COPTS) $(INC_PATH) $(OSOPTS)
 
# product options for portable build
CPRDPTOPTS="$(CENVOPTS) $(PRDPTOPTS)"
 
# product options for library build
CPRDLIBOPTS="$(CENVOPTS) $(PRDLIBOPTS)"

# product options for acceptance test build
CPRDACCOPTS="$(COSOPTS) $(PRDACCOPTS)"

# product options for acceptance test build
CPRDINTOPTS="$(COSOPTS) $(PRDACCOPTS)"
 
# Common Stack Manager File Options for library build
CSMLIBOPTS="$(CENVOPTS) $(PRDOPTS)"

# Stack Manager file option for acceptance test build
SMOPTS=-DCMFILE_REORG_1 -DCMFILE_REORG_2 -UDEBUGP -DRG_DEBUG 
 
# Common Stack Manager File Options for acceptance test build
#CSMACCOPTS="$(CENVOPTS) $(PRDOPTS) $(SMOPTS)"
CSMACCOPTS="$(CENVOPTS) $(SMOPTS)"
 
# Common Stack Manager File Options for portable build
#CSMPTOPTS="$(CENVOPTS) $(PRDOPTS)"
CSMPTOPTS="$(CENVOPTS) $(PRDOPTS)"
 
# MTSS options - for use with the MOS files in test environment
CMTOPTS=$(CENVOPTS) $(OSOPTS)
 

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
# SECTION 6

#RLOG includes
RL_INC=$(RL_DIR)/rl_common.h $(RL_DIR)/rl_rlog.h $(RL_DIR)/rl_interface.h 

# 
# The following are enabled  by default since we assume makedepend
# is not available. If makedepend is  available in your environemnt
# uncomment out this section.
# 

# environment 
ENV_INC=$(CM_DIR)/envdep.h $(CM_DIR)/envind.h $(CM_DIR)/envopt.h

# system service 
SSI_INC=$(CM_DIR)/ssi.h $(CM_DIR)/ssi.x

# general 
GEN_INC=$(CM_DIR)/gen.h $(CM_DIR)/gen.x

# all system includes 
SYS_INC=$(ENV_INC) $(GEN_INC) $(SSI_INC)

# Product layer management - LRG includes
LRG_INC=$(CM_DIR)/lrg.h $(CM_DIR)/lrg.x

# Product Upper Interface - CRG, RGR, RGM and RGU includes 
RG_U_INC=$(CM_DIR)/crg.h $(CM_DIR)/crg.x $(CM_DIR)/rgr.h $(CM_DIR)/rgr.x $(CM_DIR)/rgu.h $(CM_DIR)/rgu.x $(CM_DIR)/rgm.h $(CM_DIR)/rgm.x

# Product Lower Interface - PHY includes
RG_P_INC=$(CM_DIR)/tfu.h $(CM_DIR)/tfu.x

# common function library includes
CM_INC=$(CM_DIR)/cm5.x    $(CM_DIR)/cm5.h    \
	$(CM_DIR)/cm_lib.x $(CM_DIR)/cm_err.h $(CM_DIR)/cm_tkns.x    \
   $(CM_DIR)/cm_tkns.h $(CM_DIR)/cm_mblk.x $(CM_DIR)/cm_mblk.h  \
   $(CM_DIR)/cm_inet.x  $(CM_DIR)/cm_inet.h

# MAC layer includes
RG_INC=$(RG_DIR)/rg.h $(RG_DIR)/rg.x $(RG_DIR)/rg_err.h 

# MAC acceptance test includes 
LMACC_INC= $(RG_DIR)/rg_acc.x $(RG_DIR)/rg_acc.h

# ALL Product includes 
RGALL_INC=$(LRG_INC) $(RG_U_INC) $(RG_INC) \
          $(RG_P_INC) $(RL_INC) 
# Product - sample acceptance test includes
RGACC_INC=$(RGACC_DIR)/rgac_acc.h $(RGACC_DIR)/rgac_acc.x

# sample acceptance tests all includes
RGACCALL_INC=$(RGALL_INC) $(RGACC_INC)

# OS specific includes - MOS includes
#MS_INC=$(OS_DIR)/ms.h $(OS_DIR)/ms.x $(OS_DIR)/ms_err.h
#MS_INC

# System Services common
SS_INC=$(SS_DIR)/ss_dep.h $(SS_DIR)/ss_dep.x $(SS_DIR)/ss_drvr.x \
       $(SS_DIR)/ss_err.h $(SS_DIR)/ss_gen.h $(SS_DIR)/ss_gen.x \
       $(SS_DIR)/ss_mem.h $(SS_DIR)/ss_mem.x $(SS_DIR)/ss_msg.h \
       $(SS_DIR)/ss_msg.x $(SS_DIR)/ss_queue.h $(SS_DIR)/ss_queue.x \
       $(SS_DIR)/ss_strm.h $(SS_DIR)/ss_strm.x $(SS_DIR)/ss_task.h \
       $(SS_DIR)/ss_task.x $(SS_DIR)/ss_timer.x $(SS_DIR)/ss_gen.x \
       $(SS_DIR)/ss_queue.x



# include path VxWorks environment
#VW_INC=/tools/vxworks/ppc/target/h

#=======================================================================
#
# macros for source and object files
# SECTION 7
#

#----------------------------------------- acceptance test source
RGAC_SRCS = \
	$(RGACC_DIR)/cm_xta_tmr.c         \
	$(RGACC_DIR)/cm_xta_txn.c         \
	$(RGACC_DIR)/cm_xta_res.c         \
	$(RGACC_DIR)/cm_xta_queue.c       \
	$(RGACC_DIR)/cm_xta_master.c      \
	$(RGACC_DIR)/cm_xta_reg.c         \
	$(RGACC_DIR)/cm_xta_tst.c         \
	$(RGACC_DIR)/cm_xta_log.c         \
	$(RGACC_DIR)/cm_xta_ipc.c         \
	$(RGACC_DIR)/cm_xta_flag.c        \
	$(RGACC_DIR)/cm_xta_intreg.c      \
	$(RGACC_DIR)/cm_xta_inthdl.c      \
	$(RGACC_DIR)/cm_xta_intutl.c      \
	$(RGACC_DIR)/cm_xta_py.c          \
	$(RGACC_DIR)/cm_xta_tcfsm.c       \
	$(RGACC_DIR)/cm_xta_ldfsm.c       \
	$(RGACC_DIR)/cm_xta_xml.c         \
	$(RGACC_DIR)/cm_xta_ex_ms.c       \
	$(RGACC_DIR)/cm_xta_tgfsm.c       \
	$(RGACC_DIR)/cm_xta_tafsm.c       \
	$(RGACC_DIR)/cm_xta_slave.c       \
	$(RGACC_DIR)/rgac_pfssimreg.c  \
   $(RGACC_DIR)/tf_ptui.c         \
	$(RGACC_DIR)/nx_ptli.c         \
	$(RGACC_DIR)/nh_ptli.c         \
	$(RGACC_DIR)/kw_ptli.c         \
	$(RGACC_DIR)/rm_ptli.c         \
	$(RGACC_DIR)/rgac_prof.c       \
	$(RGACC_DIR)/rgac_tst.c        \
	$(RGACC_DIR)/rgac_crgreg.c     \
	$(RGACC_DIR)/rgac_crgcb.c      \
	$(RGACC_DIR)/rgac_crghdl.c     \
	$(RGACC_DIR)/rgac_crgutl.c     \
	$(RGACC_DIR)/nh_ex_ms.c   \
	$(RGACC_DIR)/rgac_rgrreg.c     \
	$(RGACC_DIR)/rgac_dcfireg.c     \
	$(RGACC_DIR)/rgac_rgrcb.c      \
	$(RGACC_DIR)/rgac_rgrhdl.c     \
	$(RGACC_DIR)/rgac_dcfihdl.c     \
	$(RGACC_DIR)/rgac_rgrutl.c     \
	$(RGACC_DIR)/rgac_rgmreg.c     \
	$(RGACC_DIR)/rgac_rgmcb.c      \
	$(RGACC_DIR)/rgac_rgmhdl.c     \
	$(RGACC_DIR)/nx_ex_ms.c   \
	$(RGACC_DIR)/rm_ex_ms.c   \
	$(RGACC_DIR)/rgac_rgureg.c     \
	$(RGACC_DIR)/rgac_rgucb.c      \
	$(RGACC_DIR)/rgac_rguhdl.c     \
	$(RGACC_DIR)/rgac_rguutl.c     \
	$(RGACC_DIR)/kw_ex_ms.c   \
	$(RGACC_DIR)/rgac_tfureg.c     \
	$(RGACC_DIR)/rgac_tfucb.c      \
	$(RGACC_DIR)/rgac_tfuhdl.c     \
	$(RGACC_DIR)/rgac_tfuutl.c     \
	$(RGACC_DIR)/rgac_flag.c     \
	$(RGACC_DIR)/rgac_edutl.c     \
	$(RGACC_DIR)/tf_ex_ms.c   \
	$(RGACC_DIR)/rgac_lrgreg.c     \
	$(RGACC_DIR)/rgac_lrgcb.c      \
	$(RGACC_DIR)/rgac_lrghdl.c     \
	$(RGACC_DIR)/rgac_lrgutl.c     \
	$(RGACC_DIR)/lm_ex_ms.c      

#----------------------------------------- acceptance test objects
RGAC_OBJS = \
	$(SY_DIR)/cm_xta_tmr.$(OBJ)      \
	$(SY_DIR)/cm_xta_txn.$(OBJ)      \
	$(SY_DIR)/cm_xta_res.$(OBJ)      \
	$(SY_DIR)/cm_xta_queue.$(OBJ)    \
	$(SY_DIR)/cm_xta_master.$(OBJ)   \
	$(SY_DIR)/cm_xta_reg.$(OBJ)      \
	$(SY_DIR)/cm_xta_tst.$(OBJ)      \
	$(SY_DIR)/cm_xta_log.$(OBJ)      \
	$(SY_DIR)/cm_xta_ipc.$(OBJ)      \
	$(SY_DIR)/cm_xta_flag.$(OBJ)     \
	$(SY_DIR)/cm_xta_intreg.$(OBJ)   \
	$(SY_DIR)/cm_xta_inthdl.$(OBJ)   \
	$(SY_DIR)/cm_xta_intutl.$(OBJ)   \
	$(SY_DIR)/cm_xta_py.$(OBJ)       \
	$(SY_DIR)/cm_xta_tcfsm.$(OBJ)    \
	$(SY_DIR)/cm_xta_ldfsm.$(OBJ)    \
	$(SY_DIR)/cm_xta_xml.$(OBJ)      \
	$(SY_DIR)/cm_xta_ex_ms.$(OBJ)    \
	$(SY_DIR)/cm_xta_tgfsm.$(OBJ)    \
	$(SY_DIR)/cm_xta_tafsm.$(OBJ)    \
	$(SY_DIR)/cm_xta_slave.$(OBJ)    \
	$(SY_DIR)/rgac_pfssimreg.$(OBJ)  \
   $(SY_DIR)/tf_ptui.$(OBJ)         \
	$(SY_DIR)/nx_ptli.$(OBJ)         \
	$(SY_DIR)/nh_ptli.$(OBJ)         \
	$(SY_DIR)/kw_ptli.$(OBJ)         \
	$(SY_DIR)/rm_ptli.$(OBJ)         \
	$(SY_DIR)/rgac_prof.$(OBJ)       \
	$(SY_DIR)/rgac_tst.$(OBJ)        \
	$(SY_DIR)/rgac_crgreg.$(OBJ)     \
	$(SY_DIR)/rgac_crgcb.$(OBJ)      \
	$(SY_DIR)/rgac_crghdl.$(OBJ)     \
	$(SY_DIR)/rgac_crgutl.$(OBJ)     \
	$(SY_DIR)/nh_ex_ms.$(OBJ)   \
	$(SY_DIR)/rgac_rgrreg.$(OBJ)     \
	$(SY_DIR)/rgac_dcfireg.$(OBJ)     \
	$(SY_DIR)/rgac_rgrcb.$(OBJ)      \
	$(SY_DIR)/rgac_rgrhdl.$(OBJ)     \
	$(SY_DIR)/rgac_dcfihdl.$(OBJ)     \
	$(SY_DIR)/rgac_rgrutl.$(OBJ)     \
	$(SY_DIR)/rgac_rgmreg.$(OBJ)     \
	$(SY_DIR)/rgac_rgmcb.$(OBJ)      \
	$(SY_DIR)/rgac_rgmhdl.$(OBJ)     \
	$(SY_DIR)/nx_ex_ms.$(OBJ)   \
	$(SY_DIR)/rm_ex_ms.$(OBJ)   \
	$(SY_DIR)/rgac_rgureg.$(OBJ)     \
	$(SY_DIR)/rgac_rgucb.$(OBJ)      \
	$(SY_DIR)/rgac_rguhdl.$(OBJ)     \
	$(SY_DIR)/rgac_rguutl.$(OBJ)     \
	$(SY_DIR)/kw_ex_ms.$(OBJ)   \
	$(SY_DIR)/rgac_tfureg.$(OBJ)     \
	$(SY_DIR)/rgac_tfucb.$(OBJ)      \
	$(SY_DIR)/rgac_tfuhdl.$(OBJ)     \
	$(SY_DIR)/rgac_tfuutl.$(OBJ)     \
	$(SY_DIR)/rgac_flag.$(OBJ)     \
	$(SY_DIR)/rgac_edutl.$(OBJ)      \
	$(SY_DIR)/tf_ex_ms.$(OBJ)   \
	$(SY_DIR)/rgac_lrgreg.$(OBJ)     \
	$(SY_DIR)/rgac_lrgcb.$(OBJ)      \
	$(SY_DIR)/rgac_lrghdl.$(OBJ)     \
	$(SY_DIR)/rgac_lrgutl.$(OBJ)     \
	$(SY_DIR)/lm_ex_ms.$(OBJ)      


#RGAC source for VX wroks compilation
RGACCM_SRCS=\
    	$(RGACC_DIR)/cm_xta_slave.c \
	$(RGACC_DIR)/cm_xta_reg.c \
	$(RGACC_DIR)/cm_xta_ipc.c \
	$(RGACC_DIR)/rgac_prof.c \
	$(RGACC_DIR)/rgac_slave.c \
	$(RGACC_DIR)/rgac_tst.c

RGACCM_OBJS=\
    	$(RGACC_DIR)/cm_xta_slave.$(OBJ) \
	$(RGACC_DIR)/cm_xta_reg.$(OBJ) \
	$(RGACC_DIR)/cm_xta_ipc.$(OBJ) \
	$(RGACC_DIR)/rgac_prof.$(OBJ) \
	$(RGACC_DIR)/rgac_slave.$(OBJ) \
	$(RGACC_DIR)/rgac_tst.$(OBJ)


#----------------------------------------- mac parent source
GK_SRCS= \
	$(GK_DIR)/gk_cfg.c   \
	$(GK_DIR)/gk_com.c   \
	$(GK_DIR)/gk_dbm.c   \
	$(GK_DIR)/gk_dhm.c   \
	$(GK_DIR)/gk_sch.c   \
	$(GK_DIR)/gk_sch_dlfs.c   \
	$(GK_DIR)/gk_sch_sc1.c   \
	$(GK_DIR)/gk_sch_utl_clist.c   \
	$(GK_DIR)/gk_sch_rr.c   \
	$(GK_DIR)/gk_sch_pfs.c   \
	$(GK_DIR)/gk_sch_maxci.c   \
	$(GK_DIR)/gk_sch_sps.c   \
	$(GK_DIR)/gk_sch_pwr.c   \
	$(GK_DIR)/gk_dux.c   \
	$(GK_DIR)/gk_gom.c   \
	$(GK_DIR)/gk_id.c   \
	$(GK_DIR)/gk_lim.c   \
	$(GK_DIR)/gk_lmm.c   \
	$(GK_DIR)/gk_mux.c   \
	$(GK_DIR)/gk_ptui.c  \
	$(GK_DIR)/gk_ptmi.c  \
	$(GK_DIR)/gk_ptli.c  \
	$(GK_DIR)/gk_sch_pt.c  \
	$(GK_DIR)/gk_ram.c   \
	$(GK_DIR)/gk_rom.c   \
	$(GK_DIR)/gk_tom.c   \
	$(GK_DIR)/gk_tmr.c   \
	$(GK_DIR)/gk_uhm.c   \
	$(GK_DIR)/gk_uim.c   \
	$(GK_DIR)/gk_utl.c

GK_SRCS1= \
	$(GK_DIR)/gk_ex_ms.c




#----------------------------------------- mac objects
GK_OBJS= \
	$(SY_DIR)/gk_cfg.$(OBJ)      \
	$(SY_DIR)/gk_com.$(OBJ)      \
	$(SY_DIR)/gk_dbm.$(OBJ)      \
	$(SY_DIR)/gk_dhm.$(OBJ)      \
	$(SY_DIR)/gk_sch.$(OBJ)      \
	$(SY_DIR)/gk_sch_dlfs.$(OBJ)      \
	$(SY_DIR)/gk_sch_sc1.$(OBJ)      \
	$(SY_DIR)/gk_sch_utl_clist.$(OBJ)      \
	$(SY_DIR)/gk_sch_rr.$(OBJ)      \
	$(SY_DIR)/gk_sch_pfs.$(OBJ)      \
	$(SY_DIR)/gk_sch_maxci.$(OBJ)      \
	$(SY_DIR)/gk_sch_sps.$(OBJ)      \
	$(SY_DIR)/gk_sch_pwr.$(OBJ)      \
	$(SY_DIR)/gk_dux.$(OBJ)      \
	$(SY_DIR)/gk_gom.$(OBJ)      \
	$(SY_DIR)/gk_id.$(OBJ)      \
	$(SY_DIR)/gk_lim.$(OBJ)      \
	$(SY_DIR)/gk_lmm.$(OBJ)      \
	$(SY_DIR)/gk_mux.$(OBJ)      \
	$(SY_DIR)/gk_ptui.$(OBJ)     \
	$(SY_DIR)/gk_ptmi.$(OBJ)     \
	$(SY_DIR)/gk_ptli.$(OBJ)     \
	$(SY_DIR)/gk_sch_pt.$(OBJ)     \
	$(SY_DIR)/gk_ram.$(OBJ)      \
	$(SY_DIR)/gk_rom.$(OBJ)      \
	$(SY_DIR)/gk_tom.$(OBJ)      \
	$(SY_DIR)/gk_tmr.$(OBJ)      \
	$(SY_DIR)/gk_uhm.$(OBJ)      \
	$(SY_DIR)/gk_uim.$(OBJ)      \
	$(SY_DIR)/gk_utl.$(OBJ)

GK_OBJS1= \
	$(SY_DIR)/gk_ex_ms.$(OBJ) 

#----------------------------------------- mac  source

RG_SRCS= \
	$(RG_DIR)/rg_sch_sc1.c   \
	$(RG_DIR)/rg_sch_utl_clist.c   \
	$(RG_DIR)/rg_sch_rr.c   \
	$(RG_DIR)/rg_sch_pfs.c   \
	$(RG_DIR)/rg_sch_maxci.c   \
	$(RG_DIR)/rg_sch_sps.c   \
	$(RG_DIR)/rg_sch.c   \
	$(RG_DIR)/rg_sch_cfg.c   \
	$(RG_DIR)/rg_sch_pwr.c   \
	$(RG_DIR)/rg_sch_dbm.c   \
	$(RG_DIR)/rg_sch_dhm.c   \
	$(RG_DIR)/rg_sch_ex_ms.c   \
	$(RG_DIR)/rg_sch_gom.c   \
	$(RG_DIR)/rg_sch_lmm.c   \
	$(RG_DIR)/rg_sch_ram.c   \
	$(RG_DIR)/rg_sch_tmr.c   \
	$(RG_DIR)/rg_sch_tom.c   \
	$(RG_DIR)/rg_sch_mga.c   \
	$(RG_DIR)/rg_sch_uhm.c   \
	$(RG_DIR)/rg_sch_utl.c   \
	$(RG_DIR)/rg_sch_cmn.c   \
	$(RG_DIR)/rg_sch_dlfs.c   \
	$(RG_DIR)/rg_cfg.c   \
	$(RG_DIR)/rg_com.c   \
	$(RG_DIR)/rg_dbm.c   \
	$(RG_DIR)/rg_dhm.c   \
	$(RG_DIR)/rg_dux.c   \
	$(RG_DIR)/rg_id.c   \
	$(RG_DIR)/rg_lim.c   \
	$(RG_DIR)/rg_lmm.c   \
	$(RG_DIR)/rg_mux.c   \
	$(RG_DIR)/rg_ptui.c  \
	$(RG_DIR)/rg_ptmi.c  \
	$(RG_DIR)/rg_ptli.c  \
	$(RG_DIR)/rg_ram.c   \
	$(RG_DIR)/rg_rom.c   \
	$(RG_DIR)/rg_tom.c   \
	$(RG_DIR)/rg_uhm.c   \
	$(RG_DIR)/rg_uim.c   \
	$(RG_DIR)/rg_sch_inf.c   \
	$(RG_DIR)/rg_sch_pt.c   \
	$(RG_DIR)/rg_utl.c \
	$(RG_DIR)/rg_sch_scell.c \
	$(RG_DIR)/rg_prg.c   \
	$(RG_DIR)/rg_laa.c   \
	$(RG_DIR)/rg_prg_pt.c \
	$(RG_DIR)/rg_sch_laa.c \
	$(RG_DIR)/rg_pom_scell.c

RG_SRCS1= \
	$(RG_DIR)/rg_ex_ms.c

#---------------RL parent source
RL_SRCS=$(RL_DIR)/rl_rlog.c \
		  $(RL_DIR)/rl_common.c

#---------------RL OBJECTS
RL_OBJS=$(SY_DIR)/rl_rlog.$(OBJ) \
		  $(SY_DIR)/rl_common.$(OBJ)





#----------------------------------------- mac objects
RG_OBJS= \
	$(SY_DIR)/rg_sch_sps.$(OBJ)   \
	$(SY_DIR)/rg_sch_hdfdd.$(OBJ)   \
	$(SY_DIR)/rg_sch_l2m.$(OBJ)   \
	$(SY_DIR)/rg_l2m.$(OBJ)   \
	$(SY_DIR)/rg_sch_uhm.$(OBJ)   \
	$(SY_DIR)/rg_sch_ex_ms.$(OBJ)   \
	$(SY_DIR)/rg_sch_ram.$(OBJ)   \
	$(SY_DIR)/rg_sch_utl.$(OBJ)   \
	$(SY_DIR)/rg_sch_cmn.$(OBJ)   \
	$(SY_DIR)/rg_sch_dlfs.$(OBJ)   \
	$(SY_DIR)/rg_sch_drx.$(OBJ)   \
	$(SY_DIR)/rg_sch_dbm.$(OBJ)   \
	$(SY_DIR)/rg_sch_dhm.$(OBJ)   \
	$(SY_DIR)/rg_sch_gom.$(OBJ)   \
	$(SY_DIR)/rg_sch_tmr.$(OBJ)   \
	$(SY_DIR)/rg_sch_lmm.$(OBJ)      \
	$(SY_DIR)/rg_sch_tom.$(OBJ)      \
	$(SY_DIR)/rg_sch_mga.$(OBJ)      \
	$(SY_DIR)/rg_sch_cfg.$(OBJ)   \
	$(SY_DIR)/rg_cfg.$(OBJ)      \
	$(SY_DIR)/rg_com.$(OBJ)      \
	$(SY_DIR)/rg_dbm.$(OBJ)      \
	$(SY_DIR)/rg_dhm.$(OBJ)      \
	$(SY_DIR)/rg_sch.$(OBJ)      \
	$(SY_DIR)/rg_sch_sc1.$(OBJ)      \
	$(SY_DIR)/rg_sch_utl_clist.$(OBJ)      \
	$(SY_DIR)/rg_sch_rr.$(OBJ)      \
	$(SY_DIR)/rg_sch_pfs.$(OBJ)      \
	$(SY_DIR)/rg_sch_maxci.$(OBJ)      \
	$(SY_DIR)/rg_sch_pwr.$(OBJ)      \
	$(SY_DIR)/rg_dux.$(OBJ)      \
	$(SY_DIR)/rg_id.$(OBJ)      \
	$(SY_DIR)/rg_lim.$(OBJ)      \
	$(SY_DIR)/rg_lmm.$(OBJ)      \
	$(SY_DIR)/rg_mux.$(OBJ)      \
	$(SY_DIR)/rg_ptui.$(OBJ)     \
	$(SY_DIR)/rg_ptmi.$(OBJ)     \
	$(SY_DIR)/rg_ptli.$(OBJ)     \
	$(SY_DIR)/rg_ram.$(OBJ)      \
	$(SY_DIR)/rg_rom.$(OBJ)      \
	$(SY_DIR)/rg_tom.$(OBJ)      \
	$(SY_DIR)/rg_uhm.$(OBJ)      \
	$(SY_DIR)/rg_uim.$(OBJ)      \
	$(SY_DIR)/rg_sch_inf.$(OBJ)      \
	$(SY_DIR)/rg_sch_pt.$(OBJ)      \
	$(SY_DIR)/rg_utl.$(OBJ)   \
	$(SY_DIR)/rg_sch_scell.$(OBJ) \
	$(SY_DIR)/rg_prg.$(OBJ)      \
	$(SY_DIR)/rg_laa.$(OBJ)      \
	$(SY_DIR)/rg_prg_pt.$(OBJ) \
	$(SY_DIR)/rg_sch_laa.$(OBJ) \
	$(SY_DIR)/rg_pom_scell.$(OBJ)

RG_OBJS1= \
	$(SY_DIR)/rg_ex_ms.$(OBJ) 

#----------------------------------------- common source
RGCM_SRCS= \
	$(CM_DIR)/rgr.c      \
	$(CM_DIR)/rgm.c      \
	$(CM_DIR)/crg.c      \
	$(CM_DIR)/lrg.c      \
	$(CM_DIR)/rgu.c      \
	$(CM_DIR)/tfu.c      \
	$(CM_DIR)/cm_bdy5.c  \
	$(CM_DIR)/cm_gen.c   \
	$(CM_DIR)/cm_tkns.c  \
	$(CM_DIR)/cm_lib.c   \
	$(CM_DIR)/cm_hash.c  \
	$(CM_DIR)/cm_mblk.c  \
	$(CM_DIR)/cm_llist.c \
	$(CM_DIR)/cm_lte.c      \
	$(CM_DIR)/cm_math.c      \
	$(CM_DIR)/cm_inet.c  


#----------------------------------------- common headers
RGCMH_SRCS= \
	$(CM_DIR)/cm5.h     \
	$(CM_DIR)/cm5.x     \
	$(CM_DIR)/cm_lib.x  \
	$(CM_DIR)/envopt.h  \
	$(CM_DIR)/envdep.h  \
	$(CM_DIR)/envind.h  \
	$(CM_DIR)/gen.h     \
	$(CM_DIR)/gen.x     \
	$(CM_DIR)/lrg.h     \
	$(CM_DIR)/lrg.x     \
	$(CM_DIR)/rgr.h     \
	$(CM_DIR)/rgr.x     \
	$(CM_DIR)/rgm.h     \
	$(CM_DIR)/rgm.x     \
	$(CM_DIR)/crg.h     \
	$(CM_DIR)/crg.x     \
	$(CM_DIR)/rgu.h     \
	$(CM_DIR)/rgu.x     \
	$(CM_DIR)/tfu.h     \
	$(CM_DIR)/tfu.x     \
	$(CM_DIR)/ssi.h     \
	$(CM_DIR)/ssi.x

#----------------------------------------- common object
RGCM_OBJS=\
	$(SY_DIR)/rgr.$(OBJ)       \
	$(SY_DIR)/rgm.$(OBJ)       \
	$(SY_DIR)/crg.$(OBJ)       \
	$(SY_DIR)/lrg.$(OBJ)       \
	$(SY_DIR)/rgu.$(OBJ)       \
	$(SY_DIR)/tfu.$(OBJ)       \
	$(SY_DIR)/cm_bdy5.$(OBJ)   \
	$(SY_DIR)/cm_gen.$(OBJ)    \
	$(SY_DIR)/cm_tkns.$(OBJ)   \
	$(SY_DIR)/cm_lib.$(OBJ)    \
	$(SY_DIR)/cm_hash.$(OBJ)   \
	$(SY_DIR)/cm_mblk.$(OBJ)   \
	$(SY_DIR)/cm_llist.$(OBJ)  \
	$(SY_DIR)/cm_lte.$(OBJ)       \
	$(SY_DIR)/cm_math.$(OBJ)       \
	$(SY_DIR)/cm_inet.$(OBJ)  

#----------------------------------------- common stack manager source
SM_SRCS=\
	$(SM_DIR)/sm_bdy1.c \
	$(SM_DIR)/sm_ex_ms.c 

#----------------------------------------- common stack manager objects
SM_OBJS= \
	$(SY_DIR)/sm_bdy1.$(OBJ) \
	$(SY_DIR)/sm_ex_ms.$(OBJ) 

#----------------------------------------- product stack manager source
RGSM_SRCS= \
	$(RG_SAMPLE_DIR)/smrgptmi.c 

#----------------------------------------- product stack manager objects
RGSM_OBJS= \
	$(SY_DIR)/smrgptmi.$(OBJ) 

#----------------------------------------- os - mos source
MS_SRCS= \
	$(OS_DIR)/ms_id.c    \
	$(OS_DIR)/ms_bdy1.c  \
	$(OS_DIR)/ms_bdy2.c  \
	$(CM_DIR)/cm_ss.c    \
	$(OS_DIR)/ms_ex_ms.c \
	$(OS_DIR)/ms_ptmi.c

#----------------------------------------- mos objects
MS_OBJS= \
	$(SY_DIR)/ms_id.$(OBJ)    \
	$(SY_DIR)/ms_bdy1.$(OBJ)  \
	$(SY_DIR)/ms_bdy2.$(OBJ)  \
	$(SY_DIR)/cm_ss.$(OBJ)    \
	$(SY_DIR)/ms_ex_ms.$(OBJ) \
	$(SY_DIR)/ms_ptmi.$(OBJ)

SS_SRCS= \
	$(SS_DIR)/ss_gen.c \
	$(SS_DIR)/ss_task.c \
	$(SS_DIR)/ss_drvr.c \
	$(SS_DIR)/ss_timer.c \
	$(SS_DIR)/ss_mem.c \
	$(SS_DIR)/ss_strm.c \
	$(SS_DIR)/ss_msg.c \
	$(SS_DIR)/ss_queue.c \
	$(SS_DIR)/ss_pack.c \
	$(SS_DIR)/ss_rtr.c 

SS_OBJS=  \
	$(SY_DIR)/ss_gen.$(OBJ) \
	$(SY_DIR)/ss_task.$(OBJ) \
	$(SY_DIR)/ss_drvr.$(OBJ) \
	$(SY_DIR)/ss_timer.$(OBJ) \
	$(SY_DIR)/ss_mem.$(OBJ) \
	$(SY_DIR)/ss_strm.$(OBJ) \
	$(SY_DIR)/ss_msg.$(OBJ) \
	$(SY_DIR)/ss_queue.$(OBJ) \
	$(SY_DIR)/ss_pack.$(OBJ) \
	$(SY_DIR)/ss_rtr.$(OBJ) 

# OS - mtss source-------------------------------------------------------
MT_SRCS=$(MT_DIR)/mt_ss.c \
        $(MT_DIR)/mt_id.c \
    $(CM_DIR)/cm_mem.c

# OS - mtss objects-------------------------------------------------------
MT_OBJS=$(SY_DIR)/mt_ss.$(OBJ) \
        $(SY_DIR)/mt_id.$(OBJ) \
    $(SY_DIR)/cm_mem.$(OBJ)

# OS - VxWorks source---------------------------------------------------
VW_SRCS= \
    $(VW_DIR)/vw_ss.c \
    $(VW_DIR)/cm_mem.c \
    $(VW_DIR)/vw_id.c

# OS - VxWorks objects--------------------------------------------------
VW_OBJS= \
    $(SY_DIR)/vw_ss.$(OBJ) \
    $(SY_DIR)/cm_mem.$(OBJ) \
    $(SY_DIR)/vw_id.$(OBJ)

# OS - WinNT source-----------------------------------------------------
NS_SRCS= \
    $(SS_DIR)/ns_gen.c \
    $(SS_DIR)/smnsexms.c \
    $(SS_DIR)/smnsbdy1.c \
    $(SS_DIR)/ns_ex_ms.c \
    $(SS_DIR)/ns_id.c \
    $(SS_DIR)/ns_ptmi.c \
    $(SS_DIR)/ns_space.c \
    $(SS_DIR)/ns_task.c \
    $(SS_DIR)/ns_timer.c \
        $(SS_DIR)/cm_mem.c

# OS - WinNT objects-----------------------------------------------------
NS_OBJS= \
    $(SY_DIR)/ns_gen.$(OBJ) \
    $(SY_DIR)/smnsexms.$(OBJ) \
    $(SY_DIR)/smnsbdy1.$(OBJ) \
    $(SY_DIR)/ns_ex_ms.$(OBJ) \
    $(SY_DIR)/ns_id.$(OBJ) \
    $(SY_DIR)/ns_ptmi.$(OBJ) \
    $(SY_DIR)/ns_space.$(OBJ) \
    $(SY_DIR)/ns_task.$(OBJ) \
    $(SY_DIR)/ns_timer.$(OBJ) \
        $(SY_DIR)/cm_mem.$(OBJ)


#----------------------------------------- portable build source
PT_SRCS= \
	$(RG_DIR)/rg_tst.c   \
	$(RG_DIR)/rg_ex_pt.c   \
	$(CM_DIR)/ss_ptsp.c

#----------------------------------------- portable build objects
PT_OBJS= \
	$(SY_DIR)/rg_tst.$(OBJ)   \
	$(SY_DIR)/rg_ex_pt.$(OBJ)   \
	$(SY_DIR)/ss_ptsp.$(OBJ)


#----------------------------------------- all acceptance test source
#replace MT_SRCS with VW_SRCS if using vx works or NT_SRCS if using windows NT
#replace  RGAC_SRCS  with RGACCM_SRCS if using vx works 
PRDACC_SRCS= \
	$(RG_SRCS)    \
	$(RG_SRCS1)    \
	$(RL_SRCS)    \
	$(RGAC_SRCS) \
	$(RGCM_SRCS)  \
	$(SM_SRCS)    \
	$(RGSM_SRCS)  \
	$(SS_SRCS)   \
	$(MT_SRCS)

#  $(RGACCM_SRCS)
#    $(MT_SRCS)
#   $(NT_SRCS)
#   $(VW_SRCS)


#----------------------------------------- all acceptance test objects
#replace MT_OBJS with VW_OBJS if using vx works or NT_OBJS if using windows NT
#replace  RGAC_OBJS  with RGACCM_OBJS if using vx works 
PRDACC_OBJS= \
	$(RG_OBJS)    \
	$(RL_OBJS)    \
	$(SM_OBJS)  \
	$(RGSM_OBJS)  \
	$(RG_OBJS1)    \
	$(RGCM_OBJS)  \
	$(RGAC_OBJS) \
	$(SS_OBJS) \
	$(MT_OBJS)  \

#	$(VW_OBJS)
#	$(NS_OBJS)
#	$(MT_OBJS)
#	$(RGACCM_OBJS)
# 
#----------------------------------------- all acceptance test source
#replace MT_SRCS with VW_SRCS if using vx works or NT_SRCS if using windows NT
#replace  RGAC_SRCS  with RGACCM_SRCS if using vx works 
PRDINT_SRCS= \
	$(GK_SRCS)    \
	$(GK_SRCS1)    \
	$(SM_SRCS)    \
	$(RGSM_SRCS)  \
	$(RGCM_SRCS)  \
	$(RGAC_SRCS) \
	$(SS_SRCS)   \
	$(MT_SRCS)


#----------------------------------------- all acceptance test objects
#replace MT_OBJS with VW_OBJS if using vx works or NT_OBJS if using windows NT
#replace  RGAC_OBJS  with RGACCM_OBJS if using vx works 
PRDINT_OBJS= \
	$(GK_OBJS)    \
	$(GK_OBJS1)    \
	$(SM_OBJS)  \
	$(RGSM_OBJS)  \
	$(RGCM_OBJS)  \
	$(RGAC_OBJS) \
	$(SS_OBJS) \
	$(MT_OBJS)  


#----------------------------------------- all portable source
PRDPT_SRCS= \
	$(RG_SRCS) \
	$(PT_SRCS) \
	$(RGCM_SRCS)

#----------------------------------------- all portable objects
PRDPT_OBJS= \
	$(RG_OBJS) \
	$(PT_OBJS) \
	$(RGCM_OBJS)

#----------------------------------------- Klocwork analysis objects
PRDKW_OBJS= \
	$(RG_OBJS) \
	$(PT_OBJS) 

# all library sources--------------------------------------------------
PRDLIB_SRCS=  $(RG_DIR)/rg_ex_ms.c $(RG_SRCS) 

# all library objects--------------------------------------------------
PRDLIB_OBJS= $(SY_DIR)/rg_ex_ms.$(OBJ)  $(RG_OBJS)


#=======================================================================
#
# special programs required for Internal Development by makefile
#
# adjust as required
#
# System Binary Dir - replace with appropriate directory and programe
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
	$(REMOVE) *.$(OBJ) $(BINACC) $(BINPT) *.ln *.s *.i
 
win_clean:
	$(DELETE) *.$(OBJ)
	$(DELETE) $(BINACC).exe
	$(DELETE) $(BINPT).exe
	$(DELETE) *.ln
	$(DELETE) *.s

# External target for acceptance test build
# replace MTOSOPTS with appropriate OSOPTS
acc:
	cp -f $(RG_DIR)/rg_env_acc.h $(RG_DIR)/rg_env.h
	@$(MAKE) -f $(MAKENAME) $(BLDENV) INC_PATH=$(ACC_INC_PATH) \
	 OUTNAME=$(BINACC)
 
int:
	@$(MAKE) -f $(MAKENAME) $(BLDENV) INC_PATH=$(ACC_INC_PATH) \
	OUTNAME=$(BINACC)

# External target for portable build
pt:
	@$(MAKE) -f $(MAKENAME) $(BLDENV) OUTNAME=$(BINPT) OSOPTS=$(PTOSOPTS) \
	INC_PATH=$(PT_INC_PATH)

# External target for portable build
lib:
	@$(MAKE) -f $(MAKENAME) $(BLDENV) OUTNAME=$(BINLIB)  \
    OSOPTS=$(LIBOSOPTS) INC_PATH=$(LIB_INC_PATH)

# External target for portable build
kw:
	@$(MAKE) -f $(MAKENAME) $(BLDENV) OUTNAME=$(BINKW) OSOPTS=$(PTOSOPTS) \
   INC_PATH=$(PT_INC_PATH)

#==================================================================
# SECTION 8
# Portable Target builds for Solaris CC, Solaris GNU, MRI mcc68k on
# Solaris and Microsoft Visual C++ for WINNT/WIN95
#
# Solaris CC portable build---------------------------------------------
#
$(BINSOLPT):
	@$(MAKE) -f $(MAKENAME) $(MAKEPT) -e ENV=$(SOLPTENV) CC=$(SOLCC)  \
	LD=$(SOLLD) COPTS=$(SOLCOPTS) LOPTS=$(SOLPTLOPTS) LIBS=$(SOLLIBS) \
	OBJ=$(SOL_OBJ_SUFFIX)
#
# Solaris GNU portable build--------------------------------------------
#
$(BINGNUPT):
	@$(MAKE) -f $(MAKENAME) $(MAKEPT) -e ENV=$(GNUPTENV) CC=$(GNUCC)  \
	LD=$(GNULD) COPTS=$(GNUCOPTS) LOPTS=$(GNUPTLOPTS) LIBS=$(GNULIBS) \
	OBJ=$(SOL_OBJ_SUFFIX)
#
# Linux GNU portable build--------------------------------------------
$(BINLNXPT):
	@$(MAKE) -f $(MAKENAME) $(MAKEPT) -e ENV=$(LNXPTENV) CC=$(LNXCC) \
	LD=$(LNXLD) COPTS=$(LNXCOPTS)  LIBS=$(LNXLIBS) \
	OBJ=$(SOL_OBJ_SUFFIX) LOPTS=$(LNXPTLOPTS) 
#
# Microsoft Visual C++ for WINNT/WIN95 portable build-------------------
$(BINWINPT):
	@$(MAKE) -f $(MAKENAME) $(MAKEPT) -e ENV=$(WINENV) CC=$(WINCC)  \
	LD=$(WINLD) COPTS=$(WINCOPTS) LOPTS=$(WINLOPTS) LIBS=$(WINLIBS) \
	OBJ=$(NS_OBJ_SUFFIX)
#
# MicroTec Research Compiler in Solaris Environment---------------------
$(BINMRIPT):
	@$(MAKE) -f $(MAKENAME) $(MAKEPT) -e ENV=$(MRIENV) CC=$(MRICC) \
	LD=$(MRILD) COPTS=$(MRICOPTS) LOPTS=$(MRILOPTS) LIBS=$(MRILIBS) \
	OBJ=$(SOL_OBJ_SUFFIX)
#
# Acceptance test target builds for Solaris CC, Solaris GNU,
# Inisite Memory Check tool and Microsoft Visual C++ for WINNT/WIN95
#
# Solaris CC acceptance test build--------------------------------------
#
$(BINSOLACC):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC) -e ENV=$(SOLENV) CC=$(SOLCC) \
	LD=$(SOLLD) COPTS=$(SOLCOPTS) LOPTS=$(SOLLOPTS) LIBS=$(SOLLIBS) \
	OBJ=$(SOL_OBJ_SUFFIX)
$(BINSOLINT):
	@$(MAKE) -f $(MAKENAME) $(MAKEINT) -e ENV=$(SOLENV) CC=$(SOLCC) \
	LD=$(SOLLD) COPTS=$(SOLCOPTS) LOPTS=$(SOLLOPTS) LIBS=$(SOLLIBS) \
	OBJ=$(SOL_OBJ_SUFFIX)
#
# Solaris GNU acceptance test build-------------------------------------
#
$(BINGNUACC):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC) -e ENV=$(GNUENV) CC=$(GNUCC) \
	LD=$(GNULD) COPTS=$(GNUCOPTS) LOPTS=$(GNULOPTS) LIBS=$(GNULIBS) \
	OBJ=$(SOL_OBJ_SUFFIX)
$(BINGNUINT):
	@$(MAKE) -f $(MAKENAME) $(MAKEINT) -e ENV=$(GNUENV) CC=$(GNUCC) \
	LD=$(GNULD) COPTS=$(GNUCOPTS) LOPTS=$(GNULOPTS) LIBS=$(GNULIBS) \
	OBJ=$(SOL_OBJ_SUFFIX)

# Solaris GPP(g++) acceptance test build-------------------------------------
#
$(BINGPPACC):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC) -e ENV=$(GPPENV) CC=$(GPPCC) \
	LD=$(GPPLD) COPTS=$(GPPCOPTS) LOPTS=$(GPPLOPTS) LIBS=$(GPPLIBS) \
	OBJ=$(SOL_OBJ_SUFFIX)
$(BINGPPINT):
	@$(MAKE) -f $(MAKENAME) $(MAKEINT) -e ENV=$(GPPENV) CC=$(GPPCC) \
	LD=$(GPPLD) COPTS=$(GPPCOPTS) LOPTS=$(GPPLOPTS) LIBS=$(GPPLIBS) \
	OBJ=$(SOL_OBJ_SUFFIX)
$(BINGPPPT):
	@$(MAKE) -f $(MAKENAME) $(MAKEPT) -e ENV=$(GPPENV) CC=$(GPPCC) \
	LD=$(GPPLD) COPTS=$(GPPCOPTS) LOPTS=$(GPPPTLOPTS) LIBS=$(GPPLIBS) \
	OBJ=$(SOL_OBJ_SUFFIX)
$(BINGPPLIB):
	@$(MAKE) -f $(MAKENAME) $(MAKELIB) -e ENV=$(GPPENV) CC=$(GPPCC) \
	LD=$(GPPLIBLD) COPTS=$(GPPCOPTS) LOPTS=$(GPPLIBOPTS) LIBS=$(GPPLIBS) \
	OBJ=$(SOL_OBJ_SUFFIX)

# Solaris GNU acceptance test build-------------------------------------
#
$(BINCPPACC):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC) -e ENV=$(CPPENV) CC=$(CPPCC) \
	LD=$(CPPLD) COPTS=$(CPPCOPTS) LOPTS=$(CPPLOPTS) LIBS=$(CPPLIBS) \
	OBJ=$(SOL_OBJ_SUFFIX)
$(BINCPPINT):
	@$(MAKE) -f $(MAKENAME) $(MAKEINT) -e ENV=$(CPPENV) CC=$(CPPCC) \
	LD=$(CPPLD) COPTS=$(CPPCOPTS) LOPTS=$(CPPLOPTS) LIBS=$(CPPLIBS) \
	OBJ=$(SOL_OBJ_SUFFIX)
$(BINCPPPT):
	@$(MAKE) -f $(MAKENAME) $(MAKEPT) -e ENV=$(CPPENV) CC=$(CPPCC) \
	LD=$(CPPLD) COPTS=$(CPPCOPTS) LOPTS=$(CPPPTLOPTS) LIBS=$(CPPLIBS) \
	OBJ=$(SOL_OBJ_SUFFIX)
$(BINCPPLIB):
	@$(MAKE) -f $(MAKENAME) $(MAKELIB) -e ENV=$(CPPENV) CC=$(CPPCC) \
	LD=$(CPPLIBLD) COPTS=$(CPPCOPTS) LOPTS=$(CPPLIBOPTS) LIBS=$(CPPLIBS) \
	OBJ=$(SOL_OBJ_SUFFIX)

#
# Linux GNU acceptance test build-------------------------------------
$(BINLNXACC):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC) -e ENV=$(LNXENV) CC=$(LNXCC) \
	LD=$(LNXLD)   LIBS=$(LNXLIBS) \
	OBJ=$(SOL_OBJ_SUFFIX) LOPTS=$(LNXLOPTS) COPTS=$(LNXCOPTS)
$(BINLNXINT):
	@$(MAKE) -f $(MAKENAME) $(MAKEINT) -e ENV=$(LNXENV) CC=$(LNXCC) \
	LD=$(LNXLD)   LIBS=$(LNXLIBS) \
	OBJ=$(SOL_OBJ_SUFFIX) LOPTS=$(LNXLOPTS) COPTS=$(LNXCOPTS)

# Linux purecov acceptance test build-------------------------------------
$(BINLNXPACC):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC) -e ENV=$(LNXENV) CC=$(PLNXCC) \
	LD=$(PLNXLD)   LIBS=$(LNXLIBS) \
	OBJ=$(SOL_OBJ_SUFFIX) LOPTS=$(LNXLOPTS) COPTS=$(LNXCOPTS)

# Linux purify acceptance test build-------------------------------------
$(BINPURACC):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC) -e ENV=$(PURENV) CC=$(PURCC) \
	LD=$(PURLD)   LIBS=$(PURLIBS) \
	OBJ=$(SOL_OBJ_SUFFIX) LOPTS=$(PURLOPTS) COPTS=$(PURCOPTS)

#Linux GNU lib build---------------------------------------------------
$(BINLNXLIB):
	@$(MAKE) -f $(MAKENAME) $(MAKELIB) -e ENV=$(LNXENV) CC=$(LNXCC) \
	LD=$(LNXLIBLD)   LIBS=$(LNXLIBS) OSOPTS=$(LNXLIBOSOPTS) \
	OBJ=$(SOL_OBJ_SUFFIX) LOPTS=$(LNXLIBOPTS) COPTS=$(LNXCOPTS) \
	INC_PATH=$(LIB_INC_PATH)


#
# Microsoft Visual C++ for WINNT/WIN95 acceptance test build------------
$(BINWINACC):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC) -e ENV=$(WINENV) CC=$(WINCC) \
	LD=$(WINLD) COPTS=$(WINCOPTS) LOPTS=$(WINLOPTS) LIBS=$(WINLIBS) \
	OBJ=$(NS_OBJ_SUFFIX)
$(BINWININT):
	@$(MAKE) -f $(MAKENAME) $(MAKEINT) -e ENV=$(WINENV) CC=$(WINCC) \
	LD=$(WINLD) COPTS=$(WINCOPTS) LOPTS=$(WINLOPTS) LIBS=$(WINLIBS) \
	OBJ=$(NS_OBJ_SUFFIX)
#
# Inisite Memory Check Toolin Solaris acceptance test build-------------
$(BININSITEACC):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC) -e ENV=$(INSENV) CC=$(INSCC) \
	LD=$(INSLD) COPTS=$(INSCOPTS) LOPTS=$(INSLOPTS) LIBS=$(INSLIBS) \
	OBJ=$(SOL_OBJ_SUFFIX)
$(BININSITEINT):
	@$(MAKE) -f $(MAKENAME) $(MAKEINT) -e ENV=$(INSENV) CC=$(INSCC) \
	LD=$(INSLD) COPTS=$(INSCOPTS) LOPTS=$(INSLOPTS) LIBS=$(INSLIBS) \
	OBJ=$(SOL_OBJ_SUFFIX)

#
# Solaris GNU acceptance test build-------------------------------------
#
$(BINPPCACC):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC) -e "ENV=$(PPCENV)" CC=$(PPCCC) \
	LD=$(PPCLD) "COPTS=$(PPCCOPTS)" "LOPTS=$(PPCLOPTS)" LIBS=$(PPCLIBS)\
	OBJ=$(SOL_OBJ_SUFFIX)
$(BINPPCINT):
	@$(MAKE) -f $(MAKENAME) $(MAKEINT) -e ENV=$(PPCENV) CC=$(PPCCC) \
	LD=$(PPCLD) COPTS=$(PPCCOPTS) LOPTS=$(PPCLOPTS) LIBS=$(PPCLIBS)

#
# Vxworks cc386 acceptance test build on Pentium Target----------------
#
$(BINVWACC):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC) -e ENV=$(VWINTENV) CC=$(VWINTCC) \
	LD=$(VWINTLD) COPTS=$(VWINTCOPTS) LOPTS=$(VWINTLOPTS) LIBS=$(VWINTLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(VWOSOPTS)" OS_SRCS=$(VW_SRCS) \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS=$(VW_OBJS) OS_DIR=$(VW_DIR)

 
# portable--------------------------------------------------------------
#
# The following assumes that the compile and linker options are
# set in the make-file before the definition of this target
#
$(MAKEPT):
	@$(MAKE) -f $(MAKENAME) $(PTBIN) CPRDOPTS=$(CPRDPTOPTS) \
	CSMOPTS=$(CSMPTOPTS)
 
$(MAKEKW):
	@$(MAKE) -f $(MAKENAME) $(KWBIN) CPRDOPTS=$(CPRDPTOPTS) \
	CSMOPTS=$(CSMPTOPTS)
 
$(PTBIN): $(PRDPT_OBJS)
	$(LD) $(LOPTS) $(PRDPT_OBJS) $(LIBS)
 
$(KWBIN): $(PRDKW_OBJS)
	$(LD) $(LOPTS) $(PRDKW_OBJS) $(LIBS)
 
$(LIBBIN): $(PRDLIB_OBJS)
	$(LD) $(LOPTS) $(PRDLIB_OBJS) $(LIBS)

#
# Library target builds for Solaris CC &  Solaris GNU
#
# Solaris CC library build--------------------------------------
#
$(BINSOLLIB):
	@$(MAKE) -f $(MAKENAME) $(MAKELIB) -e ENV=$(SOLENV) CC=$(SOLCC) \
    LD=$(SOLLIBLD) COPTS=$(SOLCOPTS) LOPTS=$(SOLLIBOPTS) LIBS=$(SOLLIBS) \
    OBJ=$(SOL_OBJ_SUFFIX)
#
# Solaris GNU library build-------------------------------------
#
$(BINGNULIB):
	@$(MAKE) -f $(MAKENAME) $(MAKELIB) -e ENV=$(GNUENV) CC=$(GNUCC) \
    LD=$(GNULIBLD) COPTS=$(GNUCOPTS) LOPTS=$(GNULIBOPTS) LIBS=$(GNULIBS) \
    OBJ=$(SOL_OBJ_SUFFIX)

#
# Window NT library build-------------------------------------
#
$(BINWINLIB):
	@$(MAKE) -f $(MAKENAME) $(MAKELIB) -e ENV=$(WINENV) CC=$(WINCC) \
    LD=$(WINLIBLD) COPTS=$(WINCOPTS) LOPTS=$(WINLIBOPTS) LIBS=$(WINLIBS) \
    OBJ=$(WIN_OBJ_SUFFIX)

#
# Solaris  KW build--------------------------------------------
#
$(BINGNUKW):
	@$(MAKE) -f $(MAKENAME) $(MAKEKW) -e ENV=$(GNUENV) CC=$(GNUCC) \
    LD=$(GNULD) COPTS=$(GNUCOPTS) LOPTS=$(GNULOPTS) LIBS=$(GNULIBS) \
    OBJ=$(SOL_OBJ_SUFFIX)

# acceptance test-------------------------------------------------------
#
# The following assumes that the compile and linker options are
# set in the make-file before the definition of this target
#
#For VXWORKS
#$(MAKEACC):
#	@$(MAKE) -f $(MAKENAME) $(ACCBIN) CPRDOPTS=$(CPRDACCOPTS) \
#	CSMOPTS=$(CSMACCOPTS) VWCSMOPTS=$(VWINTACCOPTS)

$(MAKEACC):
	@$(MAKE) -f $(MAKENAME) $(ACCBIN) CPRDOPTS=$(CPRDACCOPTS) \
	CSMOPTS=$(CSMACCOPTS)
 
$(MAKEINT):
	@$(MAKE) -f $(MAKENAME) $(INTBIN) CPRDOPTS=$(CPRDINTOPTS) \
	CSMOPTS=$(CSMACCOPTS)

$(ACCBIN): $(PRDACC_OBJS)
	$(LD)  $(PRDACC_OBJS) $(LOPTS) $(LIBS)

$(INTBIN): $(PRDINT_OBJS)
	$(LD)  $(PRDINT_OBJS) $(LOPTS) $(LIBS)

$(MAKELIB):
	@$(MAKE) -f $(MAKENAME) $(LIBBIN) CPRDOPTS=$(CPRDLIBOPTS) \
    CSMOPTS=$(CSMLIBOPTS)

 
#
# Make Depend
# depend portable test--------------------------------------------------
# dependency for portable source
depend_pt: $(PRDPT_SRCS)
	@$(MAKE) -f $(MAKENAME) $(DEPEND) -e OSOPTS=$(PTOSOPTS) \
	DEPOPTS=$(DEPOPTS_PT) INC_PATH=$(PT_INC_PATH) DEP_SRCS="$(PRDPT_SRCS)"
 
# depend acceptance test------------------------------------------------
# dependency for acceptance test
depend_acc: $(PRDACC_SRCS)
	@$(MAKE) -f $(MAKENAME) $(DEPEND) -e OSOPTS=$(MTOSOPTS) \
	DEPOPTS=$(DEPOPTS_ACC) INC_PATH=$(ACC_INC_PATH) DEP_SRCS="$(PRDACC_SRCS)"
 
depend_int: $(PRDINT_SRCS)
	@$(MAKE) -f $(MAKENAME) $(DEPEND) -e OSOPTS=$(MTOSOPTS) \
	DEPOPTS=$(DEPOPTS_INT) INC_PATH=$(ACC_INC_PATH) DEP_SRCS="$(PRDINT_SRCS)"

# Build the dependency
$(DEPEND):
	$(MAKEDEPEND) -f $(MAKENAME) $(OSOPTS) $(DEPOPTS) $(INC_PATH) $(DEP_SRCS)


#=======================================================================
#
# Source code build directives
# SECTION 10


#---------------------------- MAC objects ---------------------------

$(SY_DIR)/rg_cfg.$(OBJ): $(RG_DIR)/rg_cfg.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_cfg.c -o $(SY_DIR)/rg_cfg.$(OBJ)

$(SY_DIR)/rg_com.$(OBJ): $(RG_DIR)/rg_com.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_com.c -o $(SY_DIR)/rg_com.$(OBJ)

$(SY_DIR)/rg_dbm.$(OBJ): $(RG_DIR)/rg_dbm.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_dbm.c -o $(SY_DIR)/rg_dbm.$(OBJ)

$(SY_DIR)/rg_dhm.$(OBJ): $(RG_DIR)/rg_dhm.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_dhm.c -o $(SY_DIR)/rg_dhm.$(OBJ)

$(SY_DIR)/rg_sch.$(OBJ): $(RG_DIR)/rg_sch.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_sch.c -o $(SY_DIR)/rg_sch.$(OBJ)

$(SY_DIR)/rg_sch_sc1.$(OBJ): $(RG_DIR)/rg_sch_sc1.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_sch_sc1.c -o $(SY_DIR)/rg_sch_sc1.$(OBJ)

$(SY_DIR)/rg_sch_utl_clist.$(OBJ): $(RG_DIR)/rg_sch_utl_clist.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_sch_utl_clist.c -o $(SY_DIR)/rg_sch_utl_clist.$(OBJ)

$(SY_DIR)/rg_sch_rr.$(OBJ): $(RG_DIR)/rg_sch_rr.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_sch_rr.c -o $(SY_DIR)/rg_sch_rr.$(OBJ)

$(SY_DIR)/rg_sch_maxci.$(OBJ): $(RG_DIR)/rg_sch_maxci.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_sch_maxci.c -o $(SY_DIR)/rg_sch_maxci.$(OBJ)

$(SY_DIR)/rg_sch_pfs.$(OBJ): $(RG_DIR)/rg_sch_pfs.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_sch_pfs.c -o $(SY_DIR)/rg_sch_pfs.$(OBJ)

$(SY_DIR)/rg_sch_sps.$(OBJ): $(RG_DIR)/rg_sch_sps.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_sch_sps.c -o $(SY_DIR)/rg_sch_sps.$(OBJ)

$(SY_DIR)/rg_sch_hdfdd.$(OBJ): $(RG_DIR)/rg_sch_hdfdd.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_sch_hdfdd.c -o $(SY_DIR)/rg_sch_hdfdd.$(OBJ)

$(SY_DIR)/rg_sch_l2m.$(OBJ): $(RG_DIR)/rg_sch_l2m.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_sch_l2m.c -o $(SY_DIR)/rg_sch_l2m.$(OBJ)

$(SY_DIR)/rg_l2m.$(OBJ): $(RG_DIR)/rg_l2m.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_l2m.c -o $(SY_DIR)/rg_l2m.$(OBJ)

$(SY_DIR)/rg_sch_pwr.$(OBJ): $(RG_DIR)/rg_sch_pwr.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_sch_pwr.c -o $(SY_DIR)/rg_sch_pwr.$(OBJ)

$(SY_DIR)/rg_dux.$(OBJ): $(RG_DIR)/rg_dux.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_dux.c -o $(SY_DIR)/rg_dux.$(OBJ)

$(SY_DIR)/rg_id.$(OBJ): $(RG_DIR)/rg_id.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_id.c -o $(SY_DIR)/rg_id.$(OBJ)

$(SY_DIR)/rg_ex_ms.$(OBJ): $(RG_DIR)/rg_ex_ms.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_ex_ms.c -o $(SY_DIR)/rg_ex_ms.$(OBJ)

$(SY_DIR)/rg_lim.$(OBJ): $(RG_DIR)/rg_lim.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_lim.c -o $(SY_DIR)/rg_lim.$(OBJ)

$(SY_DIR)/rg_lmm.$(OBJ): $(RG_DIR)/rg_lmm.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_lmm.c -o $(SY_DIR)/rg_lmm.$(OBJ)

$(SY_DIR)/rg_mux.$(OBJ): $(RG_DIR)/rg_mux.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_mux.c -o $(SY_DIR)/rg_mux.$(OBJ)

$(SY_DIR)/rg_ptui.$(OBJ): $(RG_DIR)/rg_ptui.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)   $(RG_DIR)/rg_ptui.c -o $(SY_DIR)/rg_ptui.$(OBJ)

$(SY_DIR)/rg_ptmi.$(OBJ): $(RG_DIR)/rg_ptmi.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)   $(RG_DIR)/rg_ptmi.c -o $(SY_DIR)/rg_ptmi.$(OBJ)

$(SY_DIR)/rg_ptli.$(OBJ): $(RG_DIR)/rg_ptli.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)   $(RG_DIR)/rg_ptli.c -o $(SY_DIR)/rg_ptli.$(OBJ)

$(SY_DIR)/rg_ram.$(OBJ): $(RG_DIR)/rg_ram.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_ram.c -o $(SY_DIR)/rg_ram.$(OBJ)

$(SY_DIR)/rg_rom.$(OBJ): $(RG_DIR)/rg_rom.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_rom.c -o $(SY_DIR)/rg_rom.$(OBJ)

$(SY_DIR)/rg_tom.$(OBJ): $(RG_DIR)/rg_tom.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_tom.c -o $(SY_DIR)/rg_tom.$(OBJ)

$(SY_DIR)/rg_uhm.$(OBJ): $(RG_DIR)/rg_uhm.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_uhm.c -o $(SY_DIR)/rg_uhm.$(OBJ)

$(SY_DIR)/rg_uim.$(OBJ): $(RG_DIR)/rg_uim.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_uim.c -o $(SY_DIR)/rg_uim.$(OBJ)

$(SY_DIR)/rg_sch_inf.$(OBJ): $(RG_DIR)/rg_sch_inf.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_sch_inf.c -o $(SY_DIR)/rg_sch_inf.$(OBJ)

$(SY_DIR)/rg_sch_pt.$(OBJ): $(RG_DIR)/rg_sch_pt.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_sch_pt.c -o $(SY_DIR)/rg_sch_pt.$(OBJ)

$(SY_DIR)/rg_utl.$(OBJ): $(RG_DIR)/rg_utl.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_utl.c -o $(SY_DIR)/rg_utl.$(OBJ)
$(SY_DIR)/rg_sch_scell.$(OBJ): $(RG_DIR)/rg_sch_scell.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_sch_scell.c -o $(SY_DIR)/rg_sch_scell.$(OBJ)

$(SY_DIR)/rg_prg.$(OBJ): $(RG_DIR)/rg_prg.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_prg.c -o $(SY_DIR)/rg_prg.$(OBJ)

$(SY_DIR)/rg_laa.$(OBJ): $(RG_DIR)/rg_laa.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_laa.c -o $(SY_DIR)/rg_laa.$(OBJ)

$(SY_DIR)/rg_prg_pt.$(OBJ): $(RG_DIR)/rg_prg_pt.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_prg_pt.c -o $(SY_DIR)/rg_prg_pt.$(OBJ)
$(SY_DIR)/rg_pom_scell.$(OBJ): $(RG_DIR)/rg_pom_scell.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RG_DIR)/rg_pom_scell.c -o $(SY_DIR)/rg_pom_scell.$(OBJ)


#---------------------------- MAC Parent objects ---------------------------
$(SY_DIR)/rg_sch_lmm.$(OBJ): $(GK_DIR)/rg_sch_lmm.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/rg_sch_lmm.c -o $(SY_DIR)/rg_sch_lmm.$(OBJ)
$(SY_DIR)/rg_sch_uhm.$(OBJ): $(GK_DIR)/rg_sch_uhm.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/rg_sch_uhm.c -o $(SY_DIR)/rg_sch_uhm.$(OBJ)
$(SY_DIR)/rg_sch_dbm.$(OBJ): $(GK_DIR)/rg_sch_dbm.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/rg_sch_dbm.c -o $(SY_DIR)/rg_sch_dbm.$(OBJ)
$(SY_DIR)/rg_sch_gom.$(OBJ): $(GK_DIR)/rg_sch_gom.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/rg_sch_gom.c -o $(SY_DIR)/rg_sch_gom.$(OBJ)
$(SY_DIR)/rg_sch_tmr.$(OBJ): $(GK_DIR)/rg_sch_tmr.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/rg_sch_tmr.c -o $(SY_DIR)/rg_sch_tmr.$(OBJ)
$(SY_DIR)/rg_sch_dhm.$(OBJ): $(GK_DIR)/rg_sch_dhm.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/rg_sch_dhm.c -o $(SY_DIR)/rg_sch_dhm.$(OBJ)
$(SY_DIR)/rg_sch_ex_ms.$(OBJ): $(GK_DIR)/rg_sch_ex_ms.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/rg_sch_ex_ms.c -o $(SY_DIR)/rg_sch_ex_ms.$(OBJ)
$(SY_DIR)/rg_sch_tom.$(OBJ): $(GK_DIR)/rg_sch_tom.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/rg_sch_tom.c -o $(SY_DIR)/rg_sch_tom.$(OBJ)
$(SY_DIR)/rg_sch_mga.$(OBJ): $(GK_DIR)/rg_sch_mga.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/rg_sch_mga.c -o $(SY_DIR)/rg_sch_mga.$(OBJ)
$(SY_DIR)/rg_sch_ram.$(OBJ): $(GK_DIR)/rg_sch_ram.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/rg_sch_ram.c -o $(SY_DIR)/rg_sch_ram.$(OBJ)
$(SY_DIR)/rg_sch_utl.$(OBJ): $(GK_DIR)/rg_sch_utl.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/rg_sch_utl.c -o $(SY_DIR)/rg_sch_utl.$(OBJ)
$(SY_DIR)/rg_sch_cmn.$(OBJ): $(GK_DIR)/rg_sch_cmn.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/rg_sch_cmn.c -o $(SY_DIR)/rg_sch_cmn.$(OBJ)
$(SY_DIR)/rg_sch_laa.$(OBJ): $(GK_DIR)/rg_sch_laa.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/rg_sch_laa.c -o $(SY_DIR)/rg_sch_laa.$(OBJ)
$(SY_DIR)/rg_sch_dlfs.$(OBJ): $(GK_DIR)/rg_sch_dlfs.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/rg_sch_dlfs.c -o $(SY_DIR)/rg_sch_dlfs.$(OBJ)
$(SY_DIR)/rg_sch_drx.$(OBJ): $(GK_DIR)/rg_sch_drx.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/rg_sch_drx.c -o $(SY_DIR)/rg_sch_drx.$(OBJ)
$(SY_DIR)/rg_sch_cfg.$(OBJ): $(GK_DIR)/rg_sch_cfg.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/rg_sch_cfg.c -o $(SY_DIR)/rg_sch_cfg.$(OBJ)
$(SY_DIR)/gk_cfg.$(OBJ): $(GK_DIR)/gk_cfg.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/gk_cfg.c -o $(SY_DIR)/gk_cfg.$(OBJ)

$(SY_DIR)/gk_com.$(OBJ): $(GK_DIR)/gk_com.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/gk_com.c -o $(SY_DIR)/gk_com.$(OBJ)

$(SY_DIR)/gk_dbm.$(OBJ): $(GK_DIR)/gk_dbm.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/gk_dbm.c -o $(SY_DIR)/gk_dbm.$(OBJ)

$(SY_DIR)/gk_dhm.$(OBJ): $(GK_DIR)/gk_dhm.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/gk_dhm.c -o $(SY_DIR)/gk_dhm.$(OBJ)

$(SY_DIR)/gk_sch.$(OBJ): $(GK_DIR)/gk_sch.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/gk_sch.c -o $(SY_DIR)/gk_sch.$(OBJ)

$(SY_DIR)/gk_sch_dlfs.$(OBJ): $(GK_DIR)/gk_sch_dlfs.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/gk_sch_dlfs.c -o $(SY_DIR)/gk_sch_dlfs.$(OBJ)

$(SY_DIR)/gk_sch_utl_clist.$(OBJ): $(GK_DIR)/gk_sch_utl_clist.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/gk_sch_utl_clist.c -o $(SY_DIR)/gk_sch_utl_clist.$(OBJ)

$(SY_DIR)/gk_sch_rr.$(OBJ): $(GK_DIR)/gk_sch_rr.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/gk_sch_rr.c -o $(SY_DIR)/gk_sch_rr.$(OBJ)

$(SY_DIR)/gk_dux.$(OBJ): $(GK_DIR)/gk_dux.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/gk_dux.c -o $(SY_DIR)/gk_dux.$(OBJ)

$(SY_DIR)/gk_gom.$(OBJ): $(GK_DIR)/gk_gom.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/gk_gom.c -o $(SY_DIR)/gk_gom.$(OBJ)

$(SY_DIR)/gk_id.$(OBJ): $(GK_DIR)/gk_id.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/gk_id.c -o $(SY_DIR)/gk_id.$(OBJ)

$(SY_DIR)/gk_ex_ms.$(OBJ): $(GK_DIR)/gk_ex_ms.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/gk_ex_ms.c -o $(SY_DIR)/gk_ex_ms.$(OBJ)

$(SY_DIR)/gk_lim.$(OBJ): $(GK_DIR)/gk_lim.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/gk_lim.c -o $(SY_DIR)/gk_lim.$(OBJ)

$(SY_DIR)/gk_lmm.$(OBJ): $(GK_DIR)/gk_lmm.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/gk_lmm.c -o $(SY_DIR)/gk_lmm.$(OBJ)

$(SY_DIR)/gk_mux.$(OBJ): $(GK_DIR)/gk_mux.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/gk_mux.c -o $(SY_DIR)/gk_mux.$(OBJ)

$(SY_DIR)/gk_ptui.$(OBJ): $(GK_DIR)/gk_ptui.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)   $(GK_DIR)/gk_ptui.c -o $(SY_DIR)/gk_ptui.$(OBJ)

$(SY_DIR)/gk_ptmi.$(OBJ): $(GK_DIR)/gk_ptmi.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)   $(GK_DIR)/gk_ptmi.c -o $(SY_DIR)/gk_ptmi.$(OBJ)

$(SY_DIR)/gk_ptli.$(OBJ): $(GK_DIR)/gk_ptli.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)   $(GK_DIR)/gk_ptli.c -o $(SY_DIR)/gk_ptli.$(OBJ)
	
$(SY_DIR)/gk_sch_pt.$(OBJ): $(GK_DIR)/gk_sch_pt.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)   $(GK_DIR)/gk_sch_pt.c -o $(SY_DIR)/gk_sch_pt.$(OBJ)

$(SY_DIR)/gk_ram.$(OBJ): $(GK_DIR)/gk_ram.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/gk_ram.c -o $(SY_DIR)/gk_ram.$(OBJ)

$(SY_DIR)/gk_rom.$(OBJ): $(GK_DIR)/gk_rom.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/gk_rom.c -o $(SY_DIR)/gk_rom.$(OBJ)

$(SY_DIR)/gk_tmr.$(OBJ): $(GK_DIR)/gk_tmr.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/gk_tmr.c -o $(SY_DIR)/gk_tmr.$(OBJ)

$(SY_DIR)/gk_tom.$(OBJ): $(GK_DIR)/gk_tom.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/gk_tom.c -o $(SY_DIR)/gk_tom.$(OBJ)

$(SY_DIR)/gk_uhm.$(OBJ): $(GK_DIR)/gk_uhm.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/gk_uhm.c -o $(SY_DIR)/gk_uhm.$(OBJ)

$(SY_DIR)/gk_uim.$(OBJ): $(GK_DIR)/gk_uim.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/gk_uim.c -o $(SY_DIR)/gk_uim.$(OBJ)

$(SY_DIR)/gk_utl.$(OBJ): $(GK_DIR)/gk_utl.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(GK_DIR)/gk_utl.c -o $(SY_DIR)/gk_utl.$(OBJ)

# rlog files------------------------------------------------
$(SY_DIR)/rl_rlog.$(OBJ): $(RL_DIR)/rl_rlog.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS) $(RL_DIR)/rl_rlog.c -o $(SY_DIR)/rl_rlog.$(OBJ)

$(SY_DIR)/rl_common.$(OBJ): $(RL_DIR)/rl_common.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS) $(RL_DIR)/rl_common.c -o $(SY_DIR)/rl_common.$(OBJ)


#----------------------------------------- acceptance test objects

$(SY_DIR)/cm_xta_ex_ms.$(OBJ): $(RGACC_DIR)/cm_xta_ex_ms.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/cm_xta_ex_ms.c -o $(SY_DIR)/cm_xta_ex_ms.$(OBJ)

$(SY_DIR)/cm_xta_xml.$(OBJ): $(RGACC_DIR)/cm_xta_xml.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/cm_xta_xml.c -o $(SY_DIR)/cm_xta_xml.$(OBJ)

$(SY_DIR)/cm_xta_ldfsm.$(OBJ): $(RGACC_DIR)/cm_xta_ldfsm.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/cm_xta_ldfsm.c -o $(SY_DIR)/cm_xta_ldfsm.$(OBJ)

$(SY_DIR)/cm_xta_tcfsm.$(OBJ): $(RGACC_DIR)/cm_xta_tcfsm.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/cm_xta_tcfsm.c -o $(SY_DIR)/cm_xta_tcfsm.$(OBJ)

$(SY_DIR)/cm_xta_tgfsm.$(OBJ): $(RGACC_DIR)/cm_xta_tgfsm.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/cm_xta_tgfsm.c -o $(SY_DIR)/cm_xta_tgfsm.$(OBJ)

$(SY_DIR)/cm_xta_tafsm.$(OBJ): $(RGACC_DIR)/cm_xta_tafsm.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/cm_xta_tafsm.c -o $(SY_DIR)/cm_xta_tafsm.$(OBJ)

$(SY_DIR)/cm_xta_py.$(OBJ): $(RGACC_DIR)/cm_xta_py.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/cm_xta_py.c -o $(SY_DIR)/cm_xta_py.$(OBJ)

$(SY_DIR)/cm_xta_inthdl.$(OBJ): $(RGACC_DIR)/cm_xta_inthdl.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/cm_xta_inthdl.c -o $(SY_DIR)/cm_xta_inthdl.$(OBJ)

$(SY_DIR)/cm_xta_intreg.$(OBJ): $(RGACC_DIR)/cm_xta_intreg.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/cm_xta_intreg.c -o $(SY_DIR)/cm_xta_intreg.$(OBJ)

$(SY_DIR)/cm_xta_res.$(OBJ): $(RGACC_DIR)/cm_xta_res.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/cm_xta_res.c -o $(SY_DIR)/cm_xta_res.$(OBJ)

$(SY_DIR)/cm_xta_queue.$(OBJ): $(RGACC_DIR)/cm_xta_queue.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/cm_xta_queue.c -o $(SY_DIR)/cm_xta_queue.$(OBJ)

$(SY_DIR)/cm_xta_flag.$(OBJ): $(RGACC_DIR)/cm_xta_flag.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/cm_xta_flag.c -o $(SY_DIR)/cm_xta_flag.$(OBJ)

$(SY_DIR)/cm_xta_log.$(OBJ): $(RGACC_DIR)/cm_xta_log.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/cm_xta_log.c -o $(SY_DIR)/cm_xta_log.$(OBJ)

$(SY_DIR)/cm_xta_slave.$(OBJ): $(RGACC_DIR)/cm_xta_slave.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/cm_xta_slave.c -o $(SY_DIR)/cm_xta_slave.$(OBJ)

$(SY_DIR)/cm_xta_master.$(OBJ): $(RGACC_DIR)/cm_xta_master.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/cm_xta_master.c -o $(SY_DIR)/cm_xta_master.$(OBJ)

$(SY_DIR)/cm_xta_reg.$(OBJ): $(RGACC_DIR)/cm_xta_reg.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/cm_xta_reg.c -o $(SY_DIR)/cm_xta_reg.$(OBJ)

$(SY_DIR)/cm_xta_tst.$(OBJ): $(RGACC_DIR)/cm_xta_tst.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/cm_xta_tst.c -o $(SY_DIR)/cm_xta_tst.$(OBJ)

$(SY_DIR)/cm_xta_ipc.$(OBJ): $(RGACC_DIR)/cm_xta_ipc.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/cm_xta_ipc.c -o $(SY_DIR)/cm_xta_ipc.$(OBJ)

$(SY_DIR)/cm_xta_txn.$(OBJ): $(RGACC_DIR)/cm_xta_txn.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/cm_xta_txn.c -o $(SY_DIR)/cm_xta_txn.$(OBJ)

$(SY_DIR)/cm_xta_intutl.$(OBJ): $(RGACC_DIR)/cm_xta_intutl.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/cm_xta_intutl.c -o $(SY_DIR)/cm_xta_intutl.$(OBJ)

$(SY_DIR)/cm_xta_tmr.$(OBJ): $(RGACC_DIR)/cm_xta_tmr.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/cm_xta_tmr.c -o $(SY_DIR)/cm_xta_tmr.$(OBJ)

$(SY_DIR)/cm_xta_dum.$(OBJ): $(RGACC_DIR)/cm_xta_dum.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/cm_xta_dum.c -o $(SY_DIR)/cm_xta_dum.$(OBJ)

$(SY_DIR)/tf_ptui.$(OBJ): $(RGACC_DIR)/tf_ptui.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/tf_ptui.c -I./cmxta/  -I./header/ -o $(SY_DIR)/tf_ptui.$(OBJ)

$(SY_DIR)/nh_ptli.$(OBJ): $(RGACC_DIR)/nh_ptli.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/nh_ptli.c -I./cmxta/  -I./header/ -URL -o $(SY_DIR)/nh_ptli.$(OBJ)

$(SY_DIR)/nx_ptli.$(OBJ): $(RGACC_DIR)/nx_ptli.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RG_SAMPLE_DIR)/nx_ptli.c -I./cmxta/  -I./header/ -o $(SY_DIR)/nx_ptli.$(OBJ)

$(SY_DIR)/kw_ptli.$(OBJ): $(RGACC_DIR)/kw_ptli.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RG_SAMPLE_DIR)/kw_ptli.c -I./cmxta/  -I./header/ -o $(SY_DIR)/kw_ptli.$(OBJ)

$(SY_DIR)/rm_ptli.$(OBJ): $(RGACC_DIR)/rm_ptli.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RG_SAMPLE_DIR)/rm_ptli.c -I./cmxta/  -I./header/ -o $(SY_DIR)/rm_ptli.$(OBJ)


#Starting with RGR interface
$(SY_DIR)/rgac_rgrhdl.$(OBJ): $(RGACC_DIR)/rgac_rgrhdl.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rgac_rgrhdl.c -I./cmxta/  -I./header/ -o $(SY_DIR)/rgac_rgrhdl.$(OBJ)

$(SY_DIR)/rgac_dcfihdl.$(OBJ): $(RGACC_DIR)/rgac_dcfihdl.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rgac_dcfihdl.c -I./cmxta/  -I./header/ -o $(SY_DIR)/rgac_dcfihdl.$(OBJ)

$(SY_DIR)/rgac_rgrreg.$(OBJ): $(RGACC_DIR)/rgac_rgrreg.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rgac_rgrreg.c -I./cmxta/ -I./header/ -o $(SY_DIR)/rgac_rgrreg.$(OBJ)

$(SY_DIR)/rgac_dcfireg.$(OBJ): $(RGACC_DIR)/rgac_dcfireg.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rgac_dcfireg.c -I./cmxta/ -I./header/ -o $(SY_DIR)/rgac_dcfireg.$(OBJ)

$(SY_DIR)/rgac_rgrcb.$(OBJ): $(RGACC_DIR)/rgac_rgrcb.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rgac_rgrcb.c -I./cmxta/ -I./header/ -o $(SY_DIR)/rgac_rgrcb.$(OBJ)

$(SY_DIR)/rgac_rgrutl.$(OBJ): $(RGACC_DIR)/rgac_rgrutl.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rgac_rgrutl.c -I./cmxta/ -I./header/ -o $(SY_DIR)/rgac_rgrutl.$(OBJ)

$(SY_DIR)/nx_ex_ms.$(OBJ): $(RGACC_DIR)/nx_ex_ms.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/nx_ex_ms.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nx_ex_ms.$(OBJ)

$(SY_DIR)/rgac_rgmhdl.$(OBJ): $(RGACC_DIR)/rgac_rgmhdl.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rgac_rgmhdl.c -I./cmxta/  -I./header/ -o $(SY_DIR)/rgac_rgmhdl.$(OBJ)

$(SY_DIR)/rgac_rgmreg.$(OBJ): $(RGACC_DIR)/rgac_rgmreg.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rgac_rgmreg.c -I./cmxta/ -I./header/ -o $(SY_DIR)/rgac_rgmreg.$(OBJ)

$(SY_DIR)/rgac_rgmcb.$(OBJ): $(RGACC_DIR)/rgac_rgmcb.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rgac_rgmcb.c -I./cmxta/ -I./header/ -o $(SY_DIR)/rgac_rgmcb.$(OBJ)

$(SY_DIR)/rm_ex_ms.$(OBJ): $(RGACC_DIR)/rm_ex_ms.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rm_ex_ms.c -I./cmxta/ -I./header/ -o $(SY_DIR)/rm_ex_ms.$(OBJ)


#CRG Interface Rules

$(SY_DIR)/rgac_crgreg.$(OBJ): $(RGACC_DIR)/rgac_crgreg.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rgac_crgreg.c -I./cmxta/ -I./header/ -o $(SY_DIR)/rgac_crgreg.$(OBJ)

$(SY_DIR)/rgac_crgcb.$(OBJ): $(RGACC_DIR)/rgac_crgcb.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rgac_crgcb.c -I./cmxta/ -I./header/ -o $(SY_DIR)/rgac_crgcb.$(OBJ)

$(SY_DIR)/rgac_crghdl.$(OBJ): $(RGACC_DIR)/rgac_crghdl.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rgac_crghdl.c -I./cmxta/ -I./header/ -o $(SY_DIR)/rgac_crghdl.$(OBJ)

$(SY_DIR)/rgac_crgutl.$(OBJ): $(RGACC_DIR)/rgac_crgutl.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rgac_crgutl.c -I./cmxta/ -I./header/ -o $(SY_DIR)/rgac_crgutl.$(OBJ)

$(SY_DIR)/nh_ex_ms.$(OBJ): $(RGACC_DIR)/nh_ex_ms.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/nh_ex_ms.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nh_ex_ms.$(OBJ)

#RGU Interface
$(SY_DIR)/rgac_rgureg.$(OBJ): $(RGACC_DIR)/rgac_rgureg.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rgac_rgureg.c -I./cmxta/ -I./header/ -o $(SY_DIR)/rgac_rgureg.$(OBJ)

$(SY_DIR)/rgac_rgucb.$(OBJ): $(RGACC_DIR)/rgac_rgucb.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rgac_rgucb.c -I./cmxta/ -I./header/ -o $(SY_DIR)/rgac_rgucb.$(OBJ)

$(SY_DIR)/rgac_rguhdl.$(OBJ): $(RGACC_DIR)/rgac_rguhdl.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rgac_rguhdl.c -I./cmxta/ -I./header/ -o $(SY_DIR)/rgac_rguhdl.$(OBJ)

$(SY_DIR)/rgac_rguutl.$(OBJ): $(RGACC_DIR)/rgac_rguutl.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rgac_rguutl.c -I./cmxta/ -I./header/ -o $(SY_DIR)/rgac_rguutl.$(OBJ)

$(SY_DIR)/kw_ex_ms.$(OBJ): $(RGACC_DIR)/kw_ex_ms.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/kw_ex_ms.c -I./cmxta/ -I./header/ -o $(SY_DIR)/kw_ex_ms.$(OBJ)

#TFU Interface

$(SY_DIR)/rgac_tfureg.$(OBJ): $(RGACC_DIR)/rgac_tfureg.c $(SYS_INC) $(RGACCALL_INC) 
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rgac_tfureg.c -I./cmxta/ -I./header/ -o $(SY_DIR)/rgac_tfureg.$(OBJ)

$(SY_DIR)/rgac_tfucb.$(OBJ): $(RGACC_DIR)/rgac_tfucb.c $(SYS_INC) $(RGACCALL_INC) 
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rgac_tfucb.c -I./cmxta/ -I./header/ -o $(SY_DIR)/rgac_tfucb.$(OBJ)

$(SY_DIR)/rgac_tfuhdl.$(OBJ): $(RGACC_DIR)/rgac_tfuhdl.c $(SYS_INC) $(RGACCALL_INC) 
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rgac_tfuhdl.c -I./cmxta/ -I./header/ -o $(SY_DIR)/rgac_tfuhdl.$(OBJ)

$(SY_DIR)/rgac_edutl.$(OBJ): $(RGACC_DIR)/rgac_edutl.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rgac_edutl.c -I./cmxta/ -I./header/ -o $(SY_DIR)/rgac_edutl.$(OBJ)

$(SY_DIR)/rgac_tfuutl.$(OBJ): $(RGACC_DIR)/rgac_tfuutl.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rgac_tfuutl.c -I./cmxta/ -I./header/ -o $(SY_DIR)/rgac_tfuutl.$(OBJ)

$(SY_DIR)/rgac_flag.$(OBJ): $(RGACC_DIR)/rgac_flag.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rgac_flag.c -I./cmxta/ -I./header/ -o $(SY_DIR)/rgac_flag.$(OBJ)

$(SY_DIR)/tf_ex_ms.$(OBJ): $(RGACC_DIR)/tf_ex_ms.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/tf_ex_ms.c -I./cmxta/ -I./header/ -o $(SY_DIR)/tf_ex_ms.$(OBJ)

$(SY_DIR)/tc_ptui.$(OBJ): $(RGACC_DIR)/tc_ptui.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/tc_ptui.c -I./cmxta/ -I./header/ -o $(SY_DIR)/tc_ptui.$(OBJ)

$(SY_DIR)/rgac_tc_ex_ms.$(OBJ): $(RGACC_DIR)/rgac_tc_ex_ms.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rgac_tc_ex_ms.c -I./cmxta/ -I./header/ -o $(SY_DIR)/rgac_tc_ex_ms.$(OBJ)



#LRG Interface
$(SY_DIR)/rgac_lrgreg.$(OBJ): $(RGACC_DIR)/rgac_lrgreg.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rgac_lrgreg.c -I./cmxta/ -I./header/ -o $(SY_DIR)/rgac_lrgreg.$(OBJ)

$(SY_DIR)/lm_ex_ms.$(OBJ): $(RGACC_DIR)/lm_ex_ms.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/lm_ex_ms.c -I./cmxta/ -I./header/ -o $(SY_DIR)/lm_ex_ms.$(OBJ)

$(SY_DIR)/rgac_lrgcb.$(OBJ): $(RGACC_DIR)/rgac_lrgcb.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rgac_lrgcb.c -I./cmxta/ -I./header/ -o $(SY_DIR)/rgac_lrgcb.$(OBJ)

$(SY_DIR)/rgac_lrghdl.$(OBJ): $(RGACC_DIR)/rgac_lrghdl.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rgac_lrghdl.c -I./cmxta/ -I./header/ -o $(SY_DIR)/rgac_lrghdl.$(OBJ)

$(SY_DIR)/rgac_lrgutl.$(OBJ): $(RGACC_DIR)/rgac_lrgutl.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rgac_lrgutl.c -I./cmxta/ -I./header/ -o $(SY_DIR)/rgac_lrgutl.$(OBJ)

$(SY_DIR)/rgac_pfssimreg.$(OBJ): $(RGACC_DIR)/rgac_pfssimreg.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rgac_pfssimreg.c -I./cmxta/ -I./header/ -o $(SY_DIR)/rgac_pfssimreg.$(OBJ)

$(SY_DIR)/rgac_lr_ex_ms.$(OBJ): $(RGACC_DIR)/rgac_lr_ex_ms.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rgac_lr_ex_ms.c -I./cmxta/ -I./header/ -o $(SY_DIR)/rgac_lr_ex_ms.$(OBJ)


#Some utility functions
$(SY_DIR)/rgac_prof.$(OBJ): $(RGACC_DIR)/rgac_prof.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rgac_prof.c -o $(SY_DIR)/rgac_prof.$(OBJ)

$(SY_DIR)/rgac_slave.$(OBJ): $(RGACC_DIR)/rgac_slave.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rgac_slave.c -o $(SY_DIR)/rgac_slave.$(OBJ)

#finally MACAC Tst function
$(SY_DIR)/rgac_tst.$(OBJ): $(RGACC_DIR)/rgac_tst.c $(SYS_INC) $(RGACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(RGACC_DIR)/rgac_tst.c -I./cmxta/ -I./header/ -o $(SY_DIR)/rgac_tst.$(OBJ)
	


#----------------------------------------- common objects---------------------

$(SY_DIR)/cm_lte.$(OBJ): $(CM_DIR)/cm_lte.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_lte.c -o $(SY_DIR)/cm_lte.$(OBJ)
	
$(SY_DIR)/cm_math.$(OBJ): $(CM_DIR)/cm_math.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_math.c -o $(SY_DIR)/cm_math.$(OBJ)

$(SY_DIR)/rgr.$(OBJ): $(CM_DIR)/rgr.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/rgr.c -o $(SY_DIR)/rgr.$(OBJ)

$(SY_DIR)/rgm.$(OBJ): $(CM_DIR)/rgm.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/rgm.c -o $(SY_DIR)/rgm.$(OBJ)

$(SY_DIR)/crg.$(OBJ): $(CM_DIR)/crg.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/crg.c -o $(SY_DIR)/crg.$(OBJ)

$(SY_DIR)/rgu.$(OBJ): $(CM_DIR)/rgu.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/rgu.c -o $(SY_DIR)/rgu.$(OBJ)

$(SY_DIR)/tfu.$(OBJ): $(CM_DIR)/tfu.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/tfu.c -o $(SY_DIR)/tfu.$(OBJ)

$(SY_DIR)/lrg.$(OBJ): $(CM_DIR)/lrg.c  $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/lrg.c -o $(SY_DIR)/lrg.$(OBJ)

$(SY_DIR)/cm_gen.$(OBJ): $(CM_DIR)/cm_gen.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_gen.c -o $(SY_DIR)/cm_gen.$(OBJ)

$(SY_DIR)/cm_tkns.$(OBJ): $(CM_DIR)/cm_tkns.c $(SYS_INC) $(LRG_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_tkns.c -o $(SY_DIR)/cm_tkns.$(OBJ)

$(SY_DIR)/cm_ss.$(OBJ): $(CM_DIR)/cm_ss.c  $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_ss.c -o $(SY_DIR)/cm_ss.$(OBJ)

$(SY_DIR)/cm_lib.$(OBJ): $(CM_DIR)/cm_lib.c  $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_lib.c -o $(SY_DIR)/cm_lib.$(OBJ)

$(SY_DIR)/cm_inet.$(OBJ): $(CM_DIR)/cm_inet.c  $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_inet.c

$(SY_DIR)/cm_hash.$(OBJ): $(CM_DIR)/cm_hash.c  $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_hash.c -o $(SY_DIR)/cm_hash.$(OBJ)

$(SY_DIR)/cm_mblk.$(OBJ): $(CM_DIR)/cm_mblk.c  $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_mblk.c -o $(SY_DIR)/cm_mblk.$(OBJ)

$(SY_DIR)/cm_llist.$(OBJ): $(CM_DIR)/cm_llist.c  $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_llist.c -o $(SY_DIR)/cm_llist.$(OBJ)

$(SY_DIR)/cm_bdy5.$(OBJ): $(CM_DIR)/cm_bdy5.c  $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_bdy5.c -o $(SY_DIR)/cm_bdy5.$(OBJ)

#----------------------------------------- mos objects

$(SY_DIR)/ms_bdy1.$(OBJ): $(OS_DIR)/ms_bdy1.c $(SYS_INC) $(MS_INC)
	$(PCC) $(CC) -c $(CMTOPTS) $(MSOPTS) $(OS_DIR)/ms_bdy1.c

$(SY_DIR)/ms_bdy2.$(OBJ): $(OS_DIR)/ms_bdy2.c $(SYS_INC) $(MS_INC)
	$(PCC) $(CC) -c $(CMTOPTS) $(MSOPTS) $(OS_DIR)/ms_bdy2.c

$(SY_DIR)/ms_ptmi.$(OBJ): $(OS_DIR)/ms_ptmi.c $(SYS_INC) $(MS_INC)
	$(PCC) $(CC) -c $(CMTOPTS) $(MSOPTS) $(OS_DIR)/ms_ptmi.c

$(SY_DIR)/ms_id.$(OBJ): $(OS_DIR)/ms_id.c $(SYS_INC) $(MS_INC)
	$(PCC) $(CC) -c $(CMTOPTS) $(MSOPTS) $(OS_DIR)/ms_id.c

$(SY_DIR)/ms_ex_ms.$(OBJ): $(OS_DIR)/ms_ex_ms.c $(SYS_INC) $(MS_INC)
	$(PCC) $(CC) -c $(CMTOPTS) $(MSOPTS) $(OS_DIR)/ms_ex_ms.c

#----------------------------------------- stack manager objects

$(SY_DIR)/sm_bdy1.$(OBJ): $(SM_DIR)/sm_bdy1.c $(SYS_INC) $(LRG_INC)
	$(CC) -c $(CSMOPTS) -DSM -DRG $(SM_DIR)/sm_bdy1.c -o $(SY_DIR)/sm_bdy1.$(OBJ)

$(SY_DIR)/sm_ex_ms.$(OBJ): $(SM_DIR)/sm_ex_ms.c $(SYS_INC) $(LRG_INC)
	$(CC) -c $(CSMOPTS) -DSM -DRG $(SM_DIR)/sm_ex_ms.c -o $(SY_DIR)/sm_ex_ms.$(OBJ)

$(SY_DIR)/smrgptmi.$(OBJ): $(RG_SAMPLE_DIR)/smrgptmi.c $(SYS_INC) $(LRG_INC)
	$(CC) -c $(CPRDOPTS) -DSM -DRG $(RG_SAMPLE_DIR)/smrgptmi.c -o $(SY_DIR)/smrgptmi.$(OBJ)

#----------------------------------------- portable objects

$(SY_DIR)/rg_ex_pt.$(OBJ): $(RG_DIR)/rg_ex_pt.c 
	$(CC) -c $(CPTOPTS) $(RG_DIR)/rg_ex_pt.c

$(SY_DIR)/rg_tst.$(OBJ): $(RG_DIR)/rg_tst.c 
	$(CC) -c $(CPTOPTS) $(RG_DIR)/rg_tst.c

$(SY_DIR)/ss_ptsp.$(OBJ): $(CM_DIR)/ss_ptsp.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPTOPTS) $(CM_DIR)/ss_ptsp.c

#------------------------------------------ MTSS objects
$(SY_DIR)/ss_gen.$(OBJ): $(SS_DIR)/ss_gen.c $(SS_INC)
	$(PURE) $(CC) -c $(CMTOPTS) $(SS_DIR)/ss_gen.c

$(SY_DIR)/ss_task.$(OBJ): $(SS_DIR)/ss_task.c $(SS_INC)
	$(PURE) $(CC) -c $(CMTOPTS) $(SS_DIR)/ss_task.c

$(SY_DIR)/ss_drvr.$(OBJ): $(SS_DIR)/ss_drvr.c $(SS_INC)
	$(PURE) $(CC) -c $(CMTOPTS) $(SS_DIR)/ss_drvr.c

$(SY_DIR)/ss_timer.$(OBJ): $(SS_DIR)/ss_timer.c $(SS_INC)
	$(PURE) $(CC) -c $(CMTOPTS) $(SS_DIR)/ss_timer.c

$(SY_DIR)/ss_mem.$(OBJ): $(SS_DIR)/ss_mem.c $(SS_INC)
	$(PURE) $(CC) -c $(CMTOPTS) $(SS_DIR)/ss_mem.c

$(SY_DIR)/ss_strm.$(OBJ): $(SS_DIR)/ss_strm.c $(SS_INC)
	$(PURE) $(CC) -c $(CMTOPTS) $(SS_DIR)/ss_strm.c

$(SY_DIR)/ss_msg.$(OBJ): $(SS_DIR)/ss_msg.c $(SS_INC)
	$(PURE) $(CC) -c $(CMTOPTS) $(SS_DIR)/ss_msg.c

$(SY_DIR)/ss_queue.$(OBJ): $(SS_DIR)/ss_queue.c $(SS_INC)
	$(PURE) $(CC) -c $(CMTOPTS) $(SS_DIR)/ss_queue.c

$(SY_DIR)/ss_pack.$(OBJ): $(SS_DIR)/ss_pack.c $(SS_INC)
	$(PURE) $(CC) -c $(CMTOPTS) $(SS_DIR)/ss_pack.c

$(SY_DIR)/ss_rtr.$(OBJ): $(SS_DIR)/ss_rtr.c $(SS_INC)
	$(PURE) $(CC) -c $(CMTOPTS) $(SS_DIR)/ss_rtr.c

#-----------------------------------------  mt files build
$(SY_DIR)/cm_mem.$(OBJ): $(CM_DIR)/cm_mem.c $(SYS_INC) $(CM_INC) 
	$(PURE) $(CC) -c $(CMTOPTS) $(CM_DIR)/cm_mem.c

$(SY_DIR)/mt_ss.$(OBJ): $(MT_DIR)/mt_ss.c 
	$(PURE) $(CC) -c $(CMTOPTS) $(MT_DIR)/mt_ss.c

$(SY_DIR)/mt_id.$(OBJ): $(MT_DIR)/mt_id.c 
	$(PURE) $(CC) -c $(CMTOPTS) $(MT_DIR)/mt_id.c

#-----------------------VXWORKS
$(SY_DIR)/vw_ss.$(OBJ): $(VW_DIR)/vw_ss.c $(SYS_INC) $(SS_INC) $(VW_INC)
	$(CC) -c $(CMTOPTS) $(VW_DIR)/vw_ss.c

$(SY_DIR)/vw_id.$(OBJ): $(VW_DIR)/vw_id.c $(SYS_INC) $(SS_INC) $(VW_INC)
	$(CC) -c $(CMTOPTS) $(VW_DIR)/vw_id.c

$(SY_DIR)/vw_acc.$(OBJ): $(VW_DIR)/vw_acc.c $(SYS_INC) $(SS_INC) $(VW_INC)
	$(CC) -c $(CMTOPTS) $(VW_DIR)/vw_acc.c

# WinNT Files Build -----------------------------------------
$(SY_DIR)/ns_gen.$(OBJ): $(SS_DIR)/ns_gen.c
	$(CC) -c $(CMTOPTS) $(SS_DIR)/ns_gen.c

$(SY_DIR)/smnsexms.$(OBJ): $(SS_DIR)/smnsexms.c
	$(CC) -c $(CPRDOPTS) $(SS_DIR)/smnsexms.c

$(SY_DIR)/smnsbdy1.$(OBJ): $(SS_DIR)/smnsbdy1.c
	$(CC) -c $(CPRDOPTS) $(SS_DIR)/smnsbdy1.c

$(SY_DIR)/ns_ex_ms.$(OBJ): $(SS_DIR)/ns_ex_ms.c
	$(CC) -c $(CMTOPTS) $(SS_DIR)/ns_ex_ms.c

$(SY_DIR)/ns_id.$(OBJ): $(SS_DIR)/ns_id.c
	$(CC) -c $(CMTOPTS) $(SS_DIR)/ns_id.c

$(SY_DIR)/ns_ptmi.$(OBJ): $(SS_DIR)/ns_ptmi.c
	$(CC) -c $(CMTOPTS) $(SS_DIR)/ns_ptmi.c

$(SY_DIR)/ns_space.$(OBJ): $(SS_DIR)/ns_space.c
	$(CC) -c $(CMTOPTS) $(SS_DIR)/ns_space.c

$(SY_DIR)/ns_task.$(OBJ): $(SS_DIR)/ns_task.c
	$(CC) -c $(CMTOPTS) $(SS_DIR)/ns_task.c

$(SY_DIR)/ns_timer.$(OBJ): $(SS_DIR)/ns_timer.c
	$(CC) -c $(CMTOPTS) $(SS_DIR)/ns_timer.c


#
#********************************************************************30**
#  
#        End of file:     rg.mak.04@@/main/2 - Sat Jul 30 02:21:22 2011
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
#   ver       pat    init                  description
#---------- -------- ---- -----------------------------------------------
#/main/1      ---     st   1. Initial Release.
#/main/2      ---     nu   1. Updated for LTEMAC release 3.1.
#$SID$         ---     rt   1. Updated the default PRDOPTS for release 4.1                                 
#********************************************************************91*/

# DO NOT DELETE THIS LINE -- make depend depends on it.

