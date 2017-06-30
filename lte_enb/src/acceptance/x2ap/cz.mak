#
#********************************************************************20**
#
#       Name:   X2 Application Protocol (X2AP) (CZ) - makefile
#
#       Type:   make file
#
#       Desc:   Compile, assemble and link product software for
#               various configurations. Further comments are
#               embedded in the file.
#
#               This file supports a variety of environments and
#               build targets. The default build target will be the
#               portable target for the Solaris 2.x with SUNpro C(cc)
#
#               ENVIRONMENTS:
#
#               Solaris 2.x with SUNpro C(cc)
#
#               Solaris 2.x with GNU C(gcc)
#
#               Solaris 2.x with MRI C (mcc68k) cross compiled for
#               a relatively standard 68040 processor board
#
#               Microsoft Visual C++ 4.x for Windows '95 and Windows NT
#               environments(meuc)
#
#               BUILD TARGETS:
#
#               pt               portable software (without MOS) -- default
#               acc              acceptance tests with DUMMY SCTP
#               acc1             acceptance tests with Trillium SCTP 
#               acc2             acceptance tests with KSCTP
#               acc3             acceptance test with Dummy and Trillium SCTP
#               acc4             Building the slave.
#
#               depend.acc       makedepend for acceptance tests
#               depend.pt        makedepend for portable software
#
#               clean            remove all object files
#               win_clean        remove all object files(Windows environment)
#
#       Sid:      cz.mak@@/main/2 - Tue Aug 30 18:36:02 2011
#
#       Prg:    rp
#
#********************************************************************21*/
# NOTE: Search for TODO - To get the options what to change for other 
#       platforms/rules .
#       For DUMMY TUCL related rules, search for DUMMY
#       For STUB releated rules, search for STUB
#       For Slave Releater rules, search for SLAVE


# NOTE: for compilation on different platforms, the BLDENV specification 
#       is not sufficient. The OS_DIR needs to be set to the correct 
#       directory  and the OBJ needs to be set to the correct
#       object file extension
#

#=======================================================================
# SECTION 1
# Defines to specify appropriate directories
# Set the defines below to respective product directories

# CZ files directory
CZ_DIR=../../x2ap

# HI files directory
HI_DIR=../../tucl
HI_ACC_DIR=../tucl
# SB files directory
SB_DIR=../../sctp
SB_ACC_DIR=../sctp

# Common files directory
CM_DIR=../../cm

# common stack manager files directory
SM_DIR=../../cm

# CZ stack manager files directory
CZSM_DIR=.

# HI stack manager files directory
HISM_DIR=.

# acceptance directory
CZACC_DIR=.


# TODO  - Default is for linux 32bit. User has to change the PY_DIR
#         TO corresponding paths for both 32 and 64-bit compilations.
#         For Vx-Works there is no need for the PY_DIR path.

# acceptance directory(added for CC compilation on solaris)

#PY_DIR=/usr/local/include/python2.4
#PY_DIR=/usr/ccpu/python/solaris/10/32bit/python-2.4.4/include/python2.4/
#PY_DIR=/usr/ccpu/python/linux/64bit/python-2.4.4
#PY_DIR="C:/Python24/include"

# acceptance directory
CZNEWACC_DIR=.

# acceptance directory
CZTCACC_DIR=.

# TODO  - Default is for linux 32bit. User has to change the SS_DIR
#         to the SS files path.

# system services directories
# common SS
#SS_DIR=/u/prd/rtr/mt
SS_DIR=../../mt_acc
#SS_DIR=../mt_3.1
#SS_DIR=C:\Diameter\Codebase\vw

#  TODO  - Default is for linux/solaris - MT files
#        - For Windows comment the MT_DIR and uncomment NS_DIR and update path
#        - For Vx-Works comment the MT_DIR and uncomment VW_DIR and update path

# for MTSS
#MT_DIR=../mt_3.1
MT_DIR=../../mt_acc
#MT_DIR=.

# for NT
#NS_DIR=/u/prd/rtr/ns/
NS_DIR=.

#for VxWorks
#VW_DIR=/u/prd/rtr/vw/
VW_DIR=C:\Diameter\Codebase\vw

#  TODO  - Default is for linux/solaris - OS_DIR=MT_DIR
#        - For Windows OS_DIR=$(NS_DIR)
#        - For Vx-Works OS_DIR=$(VW_DIR)

OS_DIR=$(MT_DIR)
#OS_DIR=$(NS_DIR)
#OS_DIR=$(VW_DIR)

#Provide correct SSL library include path for TLS.
#SSL_DIR=
SSL_DIR=/usr/local/ssl
SSL_INC_PATH=$(SSL_DIR)/include
SSL_LIB_PATH=$(SSL_DIR)/lib
# build directory
SY_DIR=.

# include path
# portable include path
# new acceptance test include path
PT_INC_PATH="-I$(CM_DIR) -I$(CZ_DIR) -I$(HI_DIR) -I$(SB_DIR)"

# library include path
# new acceptance test include path
LIB_INC_PATH="-I$(CM_DIR) -I$(SS_DIR) -I$(OS_DIR) -I$(CZ_DIR) -I$(HI_DIR) -I$(SB_DIR)"

# TODO - VxWorks include paths

# Please modify them according to Tornado setup
#VW_INC=.
#VW_INC1=C:\Tornado2.2\target\h
#VW_INC2=C:\Tornado2.2\target\h\wrn
#VW_INC3=C:\Tornado2.2\target\h\wrn\coreip
#VW_INC4=C:\Tornado2.2\target\h\wrn\coreip\netinet
#VW_INC5=C:\Tornado2.2\host\x86-win32\i386-pc-mingw32\sys-include

# For the WorkBench windRiver
VW_INC=C:/WindRiver/vxworks-6.3/target/h
VW_INC1=C:/WindRiver/vxworks-6.3/target/h/wrn
VW_INC2=C:/WindRiver/vxworks-6.3/target/h/wrn/coreip
VW_INC3=C:/WindRiver/vxworks-6.3/target/h/wrn/coreip/netinet
VW_INC4=C:/WindRiver/vxworks-6.3/sys-include


# TODO  ---- For acceptance Test Build
ACC_INC_PATH="-I$(CM_DIR) -I$(CZ_DIR) -I$(HI_DIR) -I$(CZNEWACC_DIR) \
         -I$(SM_DIR) -I$(CZSM_DIR) -I$(HISM_DIR) -I$(SS_DIR) -I$(OS_DIR) \
         -I$(PY_DIR) -I$(SB_DIR) -I$(SB_ACC_DIR) -I$(HI_ACC_DIR)"

# For the VX-WORKS SLAVE Testing
#ACC_INC_PATH="-I$(CM_DIR) -I$(CZ_DIR) -I$(HI_DIR) -I$(CZNEWACC_DIR) \
#         -I$(SM_DIR) -I$(CZSM_DIR) -I$(HISM_DIR) -I$(SS_DIR) -I$(OS_DIR) \
#         -I$(VW_INC) -I$(VW_INC1) -I$(VW_INC2) -I$(VW_INC3) -I$(VW_INC4)"


# SS - include path
SSINC_PATH=-I$(SS_DIR) -I$(OS_DIR) -I$(CM_DIR)

# library path - used for integrated products and simulation env.
LIB_PATH=./

#=======================================================================
# SECTION 2
# Product specific options
#
## TCP/UDP convergence layer (HI) 
# HI_REL_1_3 : enable to be compatable to rel 1.3
# HI_REL_1_2 : enable to be compatable to rel 1.2
# HI_LPBK    : enable to run TUCL in loopback mode
# DEBUGP     : enable to turn ON debug support
# NO_ERRCLS : enable to compile out error class checking
#
## Common options
# CM_INET2      : enable to be compatable to the cm_inet rel 2
# CMINETDBG     : enable socket debugging supprt
# DEBUGP        : enable to turn ON debug support

## X2AP layer (CZ)
# LCZ_FILE_LOG   : enable to turn on File log
# CZ_GROUPED_CHK : enable for the validatin of grouped IE's
# CZ_PRNT_DATA   : To print the ie data portion on console
# NO_ERRCLS : enable to compile out error class checking
# DEBUGP     : enable runtime debugging

## X2AP extensions flags

# Interface wrapper flag

# Interface coupling flags
# All interfaces are loose coupled by default, comment the
# corresponding flag to tight couple an interface.
# Enable this flag if compiling with multi-threaded TUCL
# Enable this flag if compiling with multi-threaded TUCL
#LHI (TUCL - LM)
LHILCFLG=-DLCHIMILHI -DLCSMHIMILHI -DLCLHI 

#HIT (TUCL - user)
HITLCFLG=-DLCHIUIHIT -DLCSBLIHIT -DLCHIUISCT

#LSB (SCTP - LM)
LSBLCFLG=-DLCSBMILSB -DLCSMSBMILSB -DLCLSB

#SCT (SCTP user)
SCTLCFLG=-DLCSCT -DLCSBUISCT -DLCDMUISCT  -DLCCZLISCT -DLCSULISCT

#CZT (X2AP - user (RS))
#CZTLCFLG=-DLCCZUICZT -DLCRSLICZT -DPTRSLICZT -DLWLCCZUICZT  -DLCCZT -DPTCZUICZT
CZTLCFLG=-DCZ -DRS -DLCRSLICZT -DLWLCRSLICZT -DLCCZUICZT -DLCCZT -DX2AP_REL11 -DCZTV1

# light weight loose coupling at the CZT interface
#CZTLWLCFLG=-DLWLCCZUICZT -DLWLCRSLICZT -DLWLCCZT

#LCZ (X2AP - LM)
#LCZLCFLG=-DLCCZMILCZ -DLCSMCZMILCZ  -DLWLCCZMILCZ -DLCLCZ 
LCZLCFLG=-DLCLCZ -DSM -DCZ -DLCSMCZMILCZ  -DLCCZMILCZ

# All SM flags
SMLCFLG=-DLCSMHIMILHI -DLCSMCZMILCZ -DLCSMSBMILSB 

# TCP/UDP convergence layer options

#TUCL Release 1.2 flags
#HIREL12FLG=-DHI_REL_1_2

#TUCL Release 1.3 flags
HIREL13FLG=-DHI_REL_1_3 -DCM_INET2

#TUCL Release 1.4 flags
HIREL14FLG=-DHI_REL_1_4 -DHI_REL_1_3 -DCM_INET2

#TUCL flags added to make X2AP compilable with 1.4 and 1.5
HIREL15FLG=-DHI_REL_1_4 -DHI_REL_1_3 -DCM_INET2 -DHI_REL_1_2 -DHI006_12

#TUCL Fast Find flags. Enable this to improve performance 
HIFASTFINDFLG=-DHI_FAST_FIND -DCM_INET_FDSET_PEEK

# SCTP flags
CSBOPTS=-DSB -DLSB8 -DHI_REL_1_4 -DCM_INET2  -DLCSCT -DHI -DLCSBUISCT -UDM -USB_DEBUGP
CSBPERFOPTS=-DSB -DLSB8 -DLSB5 -DHI_REL_1_4 -DCM_INET2  -DLCSCT -DHI -DLCSBUISCT


#TUCL Debug flags
HIDBGFLG=-DCMINETDBG 

CHIOPTS=-DHI -DHI_REL_1_4  -DHI_MULTI_THREADED -DPTHIUISCT -UDM

# for KSCTP 
KCHIOPTS= -DHI -DHI_REL_1_4  -DHI_MULTI_THREADED 
#CHIOPTS=-DHI -DHI_REL_1_4 -UDM -USB -DHI_MULTI_THREADED -DLCHIUISCT 

#Enable this for TUCL loopback compiling
#HIOPTS=-DHI $(HITLCFLG) $(LHILCFLG) $(HIREL13FLG) -DHI_LPBK \

#Enable this for TUCL multi-threading. Also enable HITLCFLG
#HIOPTS=-DHI $(HITLCFLG) $(LHILCFLG) $(HIREL13FLG) $(HIFASTFINDFLG) \
#       $(HIDBGFLG) -DHI_MULTI_TREADED

# X2AP layer options
#CZOPTS = -DCZ -DCM_PASN_ESC_SUPPORT -DDEBUGP -DCM_PASN_CLASS_IDTYPE  -UCM_PASN_DBG
CZOPTS=-DCZ -DRS -DLCRSLICZT -DLWLCRSLICZT -DLCCZUICZT -DLCCZT -DLTE_HO_SUPPORT -DLCSCT -DDEBUGP

CZOPTS1 = -DCZ -DCM_PASN_ESC_SUPPORT -DDEBUGP -DCM_PASN_CLASS_IDTYPE  \
          -UCM_PASN_DBG

CZOPTS2 = -DCZ -DRS -DCM_PASN_ESC_SUPPORT -DDEBUGP \
        -DCM_PASN_CLASS_IDTYPE  -DHI_LKSCTP -DCZAC_LKSCTP -DCM_LKSCTP -UCM_PASN_DBG

# Placeholder for SFT. Dont modify this line. 

# For Portable Build
CZPTOPTS=$(CZOPTS) -DCM_INET2 -DDONT_USE_SYS_LIB

#Performance Options
#CZPERFOPTS=$(CZOPTS) -DCZAC_SCTP -DRS  -DSM -DDM -DLCSMMILCZ -DLWLCSMMILCZ  $(CZTLCFLG) $(CZTLWLCFLG) $(LCZLCFLG) $(SMLCFLG)  

CZPERFOPTS=$(CZOPTS) -DSS_MULTICORE_SUPPORT -DRS -DSM -DLCSMMILCZ -DLWLCSMMILCZ  $(CHIOPTS) $(CSBPERFOPTS) $(HITLCFLG) $(LHILCFLG) $(CZTLCFLG) $(CZTLWLCFLG) $(LCZLCFLG) $(SMLCFLG) $(LSBLCFLG) -DLCCZLISCT -USS_HISTOGRAM_SUPPORT
 

# Product options for Acceptance Test Build with dummy SCTP
CZACCOPTS=$(CZOPTS) -UCZAC_SCTP -DRS -DCMXTA_MASTER -DSM -DDM -DLCSMMILCZ -DLWLCSMMILCZ  $(CZTLCFLG) $(CZTLWLCFLG) $(LCZLCFLG) $(SMLCFLG)  
 
# Product options for Acceptance Test Build with Trillium SCTP
CZACCOPTS1=$(CZOPTS1) -DCZAC_SCTP -DRS -DCMXTA_MASTER  -DSM -DDM $(CHIOPTS) $(CSBOPTS) $(HITLCFLG) $(LHILCFLG) $(CZTLCFLG) $(CZTLWLCFLG) $(LCZLCFLG)$(SMLCFLG) 

# Product options for Acceptance Test Build - with KSCTP
CZACCOPTS2=$(CZOPTS2) $(HITLCFLG) $(LHILCFLG)-DCMXTA_MASTER  -DSM $(KCHIOPTS) $(CZTLCFLG) $(CZTLWLCFLG) $(LCZLCFLG) $(SCTLCFLG) 

# Product options for building dummy + SCTP
CZACCOPTS3=-DCZAC_SCTP -DRS -DCMXTA_MASTER -DSM -DLCSMMILCZ -DLWLCSMMILCZ  $(CZTLCFLG) $(CZTLWLCFLG) $(LCZLCFLG) $(SMLCFLG) $(CZOPTS1) $(CHIOPTS) $(CSBOPTS) $(HITLCFLG) $(LHILCFLG) $(SCTLCFLG) -DDM  -DNO_ERRCLS -DLTE_HO_SUPPORT

# Product options for SLAVE Compilation.
CZACCOPTS4=$(CZOPTS) $(CHIOPTS) $(CSBOPTS) $(CZTLCFLG) $(CZTLWLCFLG) $(LCZLCFLG) $(SCTLCFLG) -DSS_DRVR_SUPPORT -UDM $(HITLCFLG) $(LSBLCFLG) $(LHILCFLG)

#======================================================================
# Options for compilation with different OS's
# SECTION 3

# System Services product specific options
# options for a Portable Build
GENPTOSOPTS=-DCMFILE_REORG_2 -DCMFILE_REORG_1

# options for a Library Build
GENLIBOSOPTS=-DCMFILE_REORG_2 -DCMFILE_REORG_1

LNXLIBOSOPTS="-DSS_MT -D_REENTRANT -D__EXTENSIONS__  -DDEBUGNOEXIT -D_GNU_SOURCE -DSS_LINUX"
SOLLIBOSOPTS="-DSS_MT -D_REENTRANT -D__EXTENSIONS__  -DDEBUGNOEXIT"

# Enable for a Multithreaded Acceptance Test Build
GENACCOSOPTS=-DSS -DCMFILE_REORG_1 -DCMFILE_REORG_2 -DSS_MULTIPLE_PROCS -DLONG_MSG -DCM_INET2 -DSS_DRVR_SUPPORT -DTENB_ACC

# Enable for building with KSCTP
# TODO - Enable the corresponding acc opts based on the Rules:

# This Rule is for the acceptance test build with SCTP
GENACCOSOPTS1=-DSS -DCMFILE_REORG_1 -DCMFILE_REORG_2 -DSS_MULTIPLE_PROCS -DCM_INET2 -DSS_DRVR_SUPPORT -DLONG_MSG #-DUSE_PURE

# Enable for building with KSCTP
GENACCOSOPTS2=-DSS -DCMFILE_REORG_1 -DCMFILE_REORG_2 -DLONG_MSG -DSS_MULTIPLE_PROCS -DCM_INET2  -DSS_DRVR_SUPPORT 

# Enable for building All
GENACCOSOPTS3=-DSS -DCMFILE_REORG_1 -DCMFILE_REORG_2 -DSS_MULTIPLE_PROCS -DLONG_MSG -DCM_INET2 -DSS_DRVR_SUPPORT

# Enable for a SLAVE Testing Mode - ONLY MULTIPLE_PROC Mode
GENACCOSOPTS4=-DSS -DCMFILE_REORG_1 -DCMFILE_REORG_2  -DSS_TICKS_SEC=SS_100MS  -DSS_DRVR_SUPPORT -DCMINETFLATBUF -DCMINET_SINLEN -DDEBUGNOEXIT -DSS_MULTIPLE_PROCS -DCM_INET2 -DLONG_MSG

# Portable build options
PTOSOPTS=-DPORTVER

# Options for acceptance test build with PEGS Os
PEGCZPTS=-DSS_PS

# Options for acceptance test build with VrTx Os
VXOSOPTS=-DSS_VX

# Options for acceptance test build with VxWorks Os
VWOSOPTS=-DSS_VW -DVW_COMPILE -DSS_VW6X -DSS_DRVR_SUPPORT

# Options for acceptance test build with WINNT Os kernel build
WINOSOPTS=-DWINNT

# Options for acceptance test build with MTSS-Solaris
MTOSOPTS=-DSS_MT -D_REENTRANT -D__EXTENSIONS__ -DDEBUGNOEXIT -DSLES9_PLUS -USS_MULTICORE_SUPPORT -USS_M_PROTO_REGION -USS_HISTOGRAM_SUPPORT

# Options for acceptance test build with Linux
# CZACC_PRETTY_PRINT is an addition for colour debug prints during acceptance 
# testing
LNXOSOPTS=-D_xGNU_SOURCE -DSS_LINUX $(MTOSOPTS)

PERFOSOPTS=-D_xGNU_SOURCE -DSS_LINUX $(MTOSOPTS) -DSS_PERF

# Options for MTSS-Windows NT
NSOSOPTS="-DNS -DSS_OLD_THREAD -DNS_ENB_MGMT"

#=======================================================================
# Macros for output file name and makefile name 
# SECTION 4

BASENAME=cz

MAKENAME=$(BASENAME).mak

# default acceptance test for Solaris cc environment
BINACC="$(BASENAME)_acc"
BINACC1="$(BASENAME)_acc1"
BINACC2="$(BASENAME)_acc2"
BINACC3="$(BASENAME)_acc3"
BINACC4="$(BASENAME)_acc4"
BINTC="$(BASENAME)_tc"
#OUTNAME=$(BINACC)
#Perfromance Binary
PERFACC ="$(BASENAME)_perf"

# default portable for Solaris cc environment
BINPT="$(BASENAME)_pt"
BINPT1="$(BASENAME)_pt1"
BINPT2="$(BASENAME)_pt2"
BINPT3="$(BASENAME)_pt3"
BINPT4="$(BASENAME)_pt4"
#OUTNAME=$(BINPT)
# default portable for Solaris cc environment
BINLIB="$(BASENAME)_lib"
BINLIB1="$(BASENAME)_lib1"
BINLIB2="$(BASENAME)_lib2"
BINLIB3="$(BASENAME)_lib3"
BINLIB4="$(BASENAME)_lib4"

# Internal targets for the acceptance test build
MAKEACC=mkacc
MAKEACC1=mkacc1
MAKEACC2=mkacc2
MAKEACC3=mkacc3
MAKEACC4=mkacc4

ACCBIN=$(BASENAME)_acc
ACCBIN1=$(BASENAME)_acc1
ACCBIN2=$(BASENAME)_acc2
ACCBIN3=$(BASENAME)_acc3
ACCBIN4=$(BASENAME)_acc4
TCBIN=$(BASENAME)_tc
PERFBIN=$(BASENAME)_perf


# Performance build
MAKEPERF=mkperf
# Internal target for the portable build
MAKEPT=mkpt
MAKEPT1=mkpt1
MAKEPT2=mkpt2
MAKEPT3=mkpt3
MAKEPT4=mkpt4

PTBIN=$(BASENAME)_pt
PTBIN1=$(BASENAME)_pt1
PTBIN2=$(BASENAME)_pt2
PTBIN3=$(BASENAME)_pt3
PTBIN4=$(BASENAME)_pt4

# Internal target for the library build
MAKELIB=mklib
MAKELIB1=mklib1
MAKELIB2=mklib2
MAKELIB3=mklib3
MAKELIB4=mklib4

LIBBIN=$(BASENAME)_lib
LIBBIN1=$(BASENAME)_lib1
LIBBIN2=$(BASENAME)_lib2
LIBBIN3=$(BASENAME)_lib3
LIBBIN4=$(BASENAME)_lib4


# Internal target for makedepend
DEPEND=depend

# Build targets for testing in different environments

# Build with the Solaris CC compiler and linker
# Acceptance Test Build
BINSOLACC=sol_acc
BINSOLACC1=sol_acc1
BINSOLACC2=sol_acc2
BINSOLACC3=sol_acc3
BINSOLACC4=sol_acc4
# Portable Build
BINSOLPT=sol_pt
BINSOLPT1=sol_pt1
BINSOLPT2=sol_pt2
BINSOLPT3=sol_pt3
BINSOLPT4=sol_pt4

#Build with the cc386 compiler and liner on 
BINVWACC=vw_acc
BINVWACC1=vw_acc1
BINVWACC2=vw_acc2
BINVWACC3=vw_acc3
BINVWACC4=vw_acc4

# Build with the GNU compiler and linker on Solaris
# Acceptance Test Build
BINGNUACC=gnu_acc
BINGNUACC1=gnu_acc1
BINGNUACC2=gnu_acc2
BINGNUACC3=gnu_acc3
BINGNUACC4=gnu_acc4
# Portable Build
BINGNUPT=gnu_pt
BINGNUPT1=gnu_pt1
BINGNUPT2=gnu_pt2
BINGNUPT3=gnu_pt3
BINGNUPT4=gnu_pt4

# Build with the GNU compiler and linker on Linux
# Acceptance Test Build
BINLNXACC=lnx_acc
BINLNXACC1=lnx_acc1
BINLNXACC2=lnx_acc2
BINLNXACC3=lnx_acc3
BINLNXACC4=lnx_acc4

# Purify Acceptance Test Build
BINPURACC=pur_acc
BINPURACC1=pur_acc1
BINPURACC2=pur_acc2
BINPURACC3=pur_acc3
BINPURACC4=pur_acc4
# Purcove Acceptance Test Build
BINCOVACC=purccov_acc
BINCOVACC1=purccov_acc1
BINCOVACC2=purccov_acc2
BINCOVACC3=purccov_acc3
BINCOVACC4=purccov_acc4
# Quantify  Test Build
BINQUANACC=purquantify_acc
BINQUANACC1=purquantify_acc1
BINQUANACC2=purquantify_acc2
BINQUANACC3=purquantify_acc3
BINQUANACC4=purquantify_acc4

# Portable Build
BINLNXPT=lnx_pt
BINLNXPT1=lnx_pt1
BINLNXPT2=lnx_pt2
BINLNXPT3=lnx_pt3
BINLNXPT4=lnx_pt4

# Build with the Insite Memory Check programe - Acceptance Tests only
# Acceptance Test Build
BININSITEACC=ins_acc
BININSITEACC1=ins_acc1
BININSITEACC2=ins_acc2
BININSITEACC3=ins_acc3
BININSITEACC4=ins_acc4

# Build with the Visual C++ on Windows NT or Windows 95(user space only)
# Acceptance Test Build
BINWINACC=win_acc
BINWINACC1=win_acc1
BINWINACC2=win_acc2
BINWINACC3=win_acc3
BINWINACC4=win_acc4
# Portable Build
BINWINPT=win_pt
BINWINPT1=win_pt1
BINWINPT2=win_pt2
BINWINPT3=win_pt3
BINWINPT4=win_pt4

# Build with the Microtek MRI C compiler on Solaris - portable only
# Portable Build
BINMRIPT=mri_pt
BINMRIPT1=mri_pt1
BINMRIPT2=mri_pt2
BINMRIPT3=mri_pt3
BINMRIPT4=mri_pt4

# Build with the MRI compiler for vxWorks - 68040 target
# Acceptance Tests only
BINPPCACC=ppc_acc
BINPPCACC1=ppc_acc1
BINPPCACC2=ppc_acc2
BINPPCACC3=ppc_acc3
BINPPCACC4=ppc_acc4

# Portable build
BINPPCPT=ppc_pt
BINPPCPT1=ppc_pt1
BINPPCPT2=ppc_pt2
BINPPCPT3=ppc_pt3
BINPPCPT4=ppc_pt4

# g++ Acceptance Test Build
BINGPPACC=gpp_acc
BINGPPACC1=gpp_acc1
BINGPPACC2=gpp_acc2
BINGPPACC3=gpp_acc3
BINGPPACC4=gpp_acc4

# c++ Acceptance Test Build
BINCPPACC=cpp_acc
BINCPPACC1=cpp_acc1
BINCPPACC2=cpp_acc2
BINCPPACC3=cpp_acc3
BINCPPACC4=cpp_acc4

# g++ portable Build
BINGPPPT=gpp_pt
BINGPPPT1=gpp_pt1
BINGPPPT2=gpp_pt2
BINGPPPT3=gpp_pt3
BINGPPPT4=gpp_pt4

# c++ portable Build
BINCPPPT=cpp_pt
BINCPPPT1=cpp_pt1
BINCPPPT2=cpp_pt2
BINCPPPT3=cpp_pt3
BINCPPPT4=cpp_pt4

# Library Build
BINSOLLIB=sol_lib
BINSOLLIB1=sol_lib1
BINSOLLIB2=sol_lib2
BINSOLLIB3=sol_lib3
BINSOLLIB4=sol_lib4

BINGNULIB=gnu_lib
BINGNULIB1=gnu_lib1
BINGNULIB2=gnu_lib2
BINGNULIB3=gnu_lib3
BINGNULIB4=gnu_lib4

BINLNXLIB=lnx_lib
BINLNXLIB1=lnx_lib1
BINLNXLIB2=lnx_lib2
BINLNXLIB3=lnx_lib3
BINLNXLIB4=lnx_lib4

BINGPPLIB=gpp_lib
BINGPPLIB1=gpp_lib1
BINGPPLIB2=gpp_lib2
BINGPPLIB3=gpp_lib3
BINGPPLIB4=gpp_lib4

BINCPPLIB=cpp_lib
BINCPPLIB1=cpp_lib1
BINCPPLIB2=cpp_lib2
BINCPPLIB3=cpp_lib3
BINCPPLIB4=cpp_lib4

#Perfrmance Build
BINLNXPERF=lnx_perf

#=======================================================================
# macros for environments
# SECTION 5 

# SUN SPARC Compiler for Solaris----------------------------------------
#
# These flags define the environment required to build an image on
# a Sun/SPARC workstation with Sun Spro C version 4.0 running
# Solaris 2.4
#
# For ANSI Compilation
SOLENV="-DSUNOS -DANSI"
SOLCOPTS="-Xa -g -mt"

# For non-ANSI Compilation
#SOLENV="-DSUNOS"
#SOLCOPTS="-g -o$@"
 
# For 64 Bit Compilation
 #SOLCOPTS="-g -mt -xarch=v9 -DALIGN_64BIT -DBIT_64"

SOLCC="/opt/SUNWspro/bin/cc"
SOLLD="/opt/SUNWspro/bin/cc"
#TODO - For 64-bit enable the below CC/LD.
#SOLCC="/opt/SUNWspro/bin/cc -xarch=v9 -DALIGN_64BIT -DBIT_64"
#SOLLD="/opt/SUNWspro/bin/cc -xarch=v9"
SOLPYPATH=/usr/ccpu/python/solaris/10/32bit/python-2.4.4/lib/python2.4/config
SOLLOPTS="-o $(OUTNAME)"
SOLLOPTS1="-o $(OUTNAME) -L$(SSL_LIB_PATH) -lrt -lssl -lcrypto -ldl"
SOLLIBS="-lnsl -lsocket -lpthread -lposix4 -L$(SOLPYPATH) -lpython2.4 -lm -ldl "

#For KSCTP
#SOLLOPTS="-o $(OUTNAME) -lpthread -lposix4 -lnsl -lpython2.4 -lsctp"

SOLLINT="lint"
SOLLIBLD="/usr/ccs/bin/ld"
SOLLNTOPTS="-c -F -p -v"
SOLLIBLOPTS="-r -o $(OUTNAME)"
SOLLLIBS=""

# cc386 for VxWorks - Pentium Target
# These flags define the environment required to build an image on Vxworks
# with cc386 on Pentium Target
#
# For ANSI Compilation
VWINTENV="-DANSI -DCPU=PENTIUM -DCPU_VARIANT=PENTIUMPRO -DPQUICCADS"
VWINTCOPTS="-g -mpentium -msoft-float -fvolatile -fno-builtin -Wall \
         -Wno-comment -ansi -pedantic -nostdinc -Wshadow \
         -Wcast-qual -fsigned-char"

# For non-ANSI Compilation
#VWINTENV="-DCPU=PENTIUM -DCPU_VARIANT=PENTIUMPRO -DPQUICCADS"
#VWINTCOPTS="-g -mpentium -msoft-float -fvolatile -fno-builtin -Wall \
#          -Wno-comment -pipe -nostdinc -Wshadow -Wredundant-decls \
#         -Wcast-qual -fsigned-char"

VWINTCC="cc386 -mcpu=pentium"
VWINTLD="ld386"
VWINTLOPTS="-o $(OUTNAME) -r"
VWINTLIBS=""

# SUN SPARC Compiler With Insight-----------------------------------------------
#
# These flags define the environment required to build an image on
# a Sun/SPARC workstation with SUN Spro C version 4.0 C compiler running 
# Solaris 2.4 , with the INSURE(Insight) run time memory check tool.
#
# For ANSI Compilation
INSENV="-DSUNOS -DSS_LINUX -DANSI -DPURE -DUSE_PURE"
INSCOPTS="-Xa -g -DCZ_INSURE -DNO_ERRCLS"

# For non-ANSI Compilation
#INSENV=-DSUNOS -DPURE
#INSCOPTS="-g -DCZ_INSURE -DNO_ERRCLS"

INSCC="insure"
INSLD="insure"
INSLOPTS="-o $(OUTNAME)"
INSLOPTS1="-o $(OUTNAME) -lrt -lssl -lcrypto -ldl"
INSLIBS="-Xlinker -export-dynamic -lnsl -lpthread -lpython2.4 -lm -ldl -lutil"
INSLINT="lint"
INSLNTOPTS="-c -F -p -v"

PPCENV=-DCPU=SIMNT -DANSI -DPQUICCADS
#PPCENV=-DANSI -DPCORE -DCPU=PPC604
PPCCC=ccpentium
PPCLD=ldpentium


PPCCOPTS=-g -mtune=i486 -fvolatile -fno-builtin -Wall \
         -Wno-comment -ansi -pedantic -pipe -nostdinc -Wshadow \
         -Wcast-qual -fsigned-char

PPCLOPTS=-r -e vwMain -Map $(OUTNAME).map -o $(OUTNAME)
PPCLIBS=
PPCLINT=
PPCLNTOPTS=

# GNU gcc compiler for SPARC--------------------------------------------
#
# These flags define the environment required to build an image on
# a Sun/SPARC workstation with GNU C version 2.5.7 (or greater) running
# Solaris 2.4
#
# For ANSI Compilation
GNUENV="-DSUNOS -DANSI -D__EXTENSIONS__"

# For non-ANSI Compilation
#GNUENV="-DSUNOS"

GNUCOPTS="-g3 -Wall -Wno-comment -pipe -Wshadow \
          -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes "
#GNUCOPTS=" -O1 -g3 -Wimplicit -Wunused -Wcomment -Wchar-subscripts \
#-Wuninitialized -Wparentheses -Wformat -Winline -Wreturn-type -fPIC \
#-Wmissing-prototypes -pedantic"

#For 64 Bit compilation
#GNUCOPTS="-g -m64 -DALIGN_64BIT -DBIT_64"
#GNULOPTS="-m64 -64 -DALIGN_64BIT -DBIT_64 -o $(OUTNAME) -lsocket -lnsl -lpython2.4 -lm -ldl -lposix4


GNUCC="g++"
GNULD="g++"
GNULOPTS="-o $(OUTNAME)"
GNULOPTS1="-o $(OUTNAME) -L$(SSL_LIB_PATH) -lrt -lssl -lcrypto -ldl"
# lib nptl is as this taken care in 2.6 version kernel. please enable below
# rule if you are using 2.4 version kernel.
#GNULIBS="-lpython2.4 -lm -ldl -lnsl -lsocket -L/usr/lib/nptl -lpthread -lposix4"
GNULIBS="-lpython2.4 -lm -ldl -lnsl -lsocket -lpthread -lposix4"
GNULINT="lint"
GNULNTOPTS="-c -F -p -v"

GNULIBLD="ld"
GNULIBLOPTS="-r -o $(OUTNAME)"
GNULLIBS=""

# GNU gcc compiler for Linux------------------------------------------
#
# These flags define the environment required to build an image on
# a Linux workstation with GNU C version 2.5.7 (or greater)
#
# For ANSI Compilation
#LNXENV="-DSUNOS -DSS_LINUX -DANSI -DUSE_PURE -DPURE"
LNXENV="-DSUNOS -DSS_LINUX -DANSI -DNOCONAVL -UUSE_PURE -D_GNU_SOURCE"
#LNXCOPTS="-g3 -m32 -ansi -pipe -pedantic -Wall -Wno-comment -Wshadow \
     -Wcast-align -Wcast-qual -fno-strict-aliasing -Wimplicit -Wunused\
     -Wstrict-prototypes -Wmissing-prototypes --std=c99"
LNXCOPTS="-g3 -m32 -ansi -pipe -pedantic -Wall -Wno-comment -Wshadow \
     -Wcast-align -Wno-cast-qual -fno-strict-aliasing -Wimplicit -Wunused"

#LNXCOPTS="-g -m64 -DALIGN_64BIT -DBIT_64"
     
# For non-ANSI Compilation
#LNXENV="-DSUNOS -DSS_LINUX"
#LNXCOPTS="-g3 -pipe -pedantic -Wall -Wno-comment -Wshadow \
#     -Wcast-align -Wcast-qual"

# For Purify accpetance build
ifeq ($(CCPU_PURIFY),y)
LNXCC="purify g++ -m32"
LNXLD="purify g++ -m32"
else
LNXCC="g++ -m32"
LNXLD="g++ -m32"
endif

LNXLOPTS="-m32 -Xlinker -export-dynamic "

#64 bit compilation
#LNXCC="gcc -m64 -DALIGN_64BIT -DBIT_64"
#LNXLD="gcc -m64 -DALIGN_64BIT -DBIT_64"
#LNXLOPTS=" -m64 -DALIGN_64BIT -DBIT_64 -o $(OUTNAME) -Xlinker -export-dynamic -lpthread"

# lib nptl is as this taken care in 2.6 version kernel. please enable below
# rule if you are using 2.4 version kernel.
#LNXLOPTS1="-o $(OUTNAME) -Xlinker -export-dynamic -L/usr/lib/nptl -lpthread  -lnsl -lrt -lssl -lcrypto -ldl"
LNXLOPTS1="-o $(OUTNAME) -Xlinker -export-dynamic -lpthread  -lnsl -lrt -lssl -lcrypto -ldl"
LNXLIBS="-L/usr/lib/nptl -lpthread -lpython2.4 -lm -ldl -lutil -o $(OUTNAME) "
#For KSCTP
# lib nptl is as this taken care in 2.6 version kernel. please enable below
# if you are using 2.4 version kernel.
#LNXLIBS2="-lpthread -lpython2.4 -lm -ldl -lutil -lsctp -lssi -o $(OUTNAME) "
LNXLIBS2="-L/usr/lib/nptl -lpthread -lpython2.4 -lm -ldl -lutil -lsctp -lssi -o $(OUTNAME) "
LNXLIBS4="-lm -ldl -lutil"
LNXLINT="lint"
LNXLIBLD="ld"
LNXLNTOPTS="-c -F -p -v"
LNXLIBLOPTS="-r -o $(OUTNAME)"
LNXLLIBS=""
LNXCCCC="cc"



#Performance Environment
PERFENV="-DSUNOS -DSS_LINUX -DANSI "
PERFCOPTS="-O3 -m32 -ansi -pipe -pedantic -Wall -Wno-comment -Wshadow \
     -Wcast-align -Wcast-qual -fno-strict-aliasing -Wimplicit -Wunused\
     -Wstrict-prototypes -Wmissing-prototypes"
PERFCC="g++"
PERFLD="g++"
PERFLOPTS="-m32 -Xlinker -export-dynamic "

#64 bit compilation
#LNXCC="g++ -m64 -DALIGN_64BIT -DBIT_64"
#LNXLD="g++ -m64 -DALIGN_64BIT -DBIT_64"
#LNXLOPTS=" -m64 -DALIGN_64BIT -DBIT_64 -o $(OUTNAME) -Xlinker -export-dynamic -L/usr/lib/nptl -lpthread"

#PERFLOPTS1="-o $(OUTNAME) -Xlinker -export-dynamic -lpthread  -lnsl -lrt -lssl -lcrypto -ldl"
PERFLOPTS1="-o $(OUTNAME) -L/usr/lib/nptl -Xlinker -export-dynamic  -lnsl -lrt -lssl -lcrypto -ldl"

PERFLIBS="-lpthread -lm -ldl -lutil -o $(OUTNAME) "
#For KSCTP
PERFLIBS2="-lpthread -lpython2.4 -lm -ldl -lutil -lsctp -lssi -o $(OUTNAME) "
PERFLIBS4="-lm -ldl -lutil"
LINT="lint"
PERFLIBLD="ld"
PERFLNTOPTS="-c -F -p -v"
PERFLIBLOPTS="-r -o $(OUTNAME)"
PERFLLIBS=""
PERFCCCC="cc"

# Purify gcc compiler for Linux------------------------------------------
#
# These flags define the environment required to build an image on
# a Linux workstation with GNU C version 2.5.7 (or greater)
#
# For ANSI Compilation
PURENV="-DSUNOS -DSS_LINUX -DANSI -DPURE -DUSE_PURE -DNOCONAVL"
PURCOPTS="-g3 -ansi -pipe -pedantic -Wall -Wno-comment -Wshadow \
     -Wcast-align -Wcast-qual \
     -Wstrict-prototypes -Wmissing-prototypes"

# For non-ANSI Compilation
#PURENV="-DSUNOS -DSS_LINUX -DPURE -DUSE_PURE"
#PURCOPTS="-g3 -pipe -pedantic -Wall -Wno-comment -Wshadow \
#     -Wcast-align -Wcast-qual"

PURCC="purify -cache-dir=\tmp -windows=yes g++ -m32"
PURLD="purify -cache-dir=\tmp -windows=yes g++ -m32"
PURLOPTS="-o $(OUTNAME) -Xlinker -export-dynamic -L/usr/lib/nptl -lpthread"
PURLOPTS1="-o $(OUTNAME) -Xlinker -export-dynamic -L/usr/lib/nptl -lpthread  -lrt -lssl -lcrypto -ldl"
PURLIBS="-lpython2.4 -lm -ldl -lutil"
PURLINT="lint"
PURLNTOPTS="-c -F -p -v"

# Quantify gcc compiler for Linux--------------------------------------
QUANTIFYCC="quantify g++"
QUANTIFYLD="quantify g++"

# Purecov gcc compiler for Linux--------------------------------------
PURCOVCC="purecov -cache-dir=\tmp -windows=yes g++ -m32"
PURCOVLD="purecov -cache-dir=\tmp -windows=yes g++ -m32"

#  g++ compiler for Linux--------------------------------------
GPPCC="g++"
GPPLD="g++"
GPPLIBLD="ld"
GPPCOPTS="-g3 -Wall -Wno-comment -pipe -Wshadow -Wcast-qual"

#  c++ compiler for Linux--------------------------------------
CPPCC="c++"
CPPLD="c++"
CPPCOPTS="-g"
CPPLIBLD="ld"



#  g++ compiler for Solaris--------------------------------------
#GPPCC="g++"
#GPPLD="g++"
#GPPLIBLD="ld"
#GPPCOPTS="-g3 -Wall -Wno-comment -pipe -Wshadow -Wcast-qual -fno-exceptions"

#  c++ compiler for Solaris--------------------------------------
#CPPCC="c++"
#CPPLD="c++"
#CPPCOPTS="-g -fno-exceptions"
#CPPLIBLD="ld"


# MRI mcc68k compiler for 68040-----------------------------------------
#
# These flags define the environment required to build an image for
# a Motorola MVME162 Board (68040) with Microtec Research C version 4.4
# for a portable environment.
#
# For ANSI Compilation
MRIENV="-DELVIS -DPROC_68XXX -DPROC_68040 -DRY_ENBRAW \
   -DSOLMRI43 -DMAXBRDS=4 -DANSI -DNOERRCHK -DNO_ERRCLS -DNOCONAVL "

# For non-ANSI Compilation
#MRIENV="-DELVIS -DPROC_68XXX -DPROC_68040 -DENB_RELAY -DRY_ENBRAW \
#         -DSOLMRI43 -DMAXBRDS=4 -DNOERRCHK -DNO_ERRCLS -DNOCONAVL"

MRICC="mcc68k"
MRILD="mcc68k"
MRICOPTS="-p68040 -H -A -v -Fsm -O -Ob -Oe -Ot -nKc -nKm  -Mcp -Mdp -Ml -Gf"
MRILOPTS="-e$(OUTNAME).lnk -Wl,\"-m > $(OUTNAME).map -o $(OUTNAME).vcs -F s\""
MRILIBS="$(LIB_PATH)/lib040.lib"
MRILINT=""
MRILNTOPTS=""

# Microsoft Visual C++ for Win 95/NT------------------------------------
#
# These flags define the environment required to build an image for
# a Windows '95 or Windows NT environment
#
#
# For ANSI Compilation
WINENV="-DWIN32 -DANSI -D_CRT_SECURE_NO_DEPRECATE"

# For non-ANSI Compilation
#WINENV="-DWIN32"

WINCC="cl"
WINLD="cl"
WINCOPTS="-Od -W3 -Zi -Yd"
WINLOPTS="-o $(OUTNAME) -F250000 -Zd"
#WINLIBS="ws2_32.lib ssleay32MT.lib libeay32MT.lib -link -debug:full -debugtype:cv"
WINLIBS="ws2_32.lib C:\Python24\libs\python24.lib -link -debug:full -debugtype:cv"

WINLINT=""
WINLNTOPTS=""


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


#Actual Build Environment---------------------------------
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
# TODO - For windows Change the suffix to obj & for other platforms .o

# this defaults to 'o' for most UNIX based systems
# this can be set to 'obj' for DOS/Windows/NT platforms
#
UNIX_OBJ_SUFFIX=o
WIN_OBJ_SUFFIX=obj
OBJ=$(UNIX_OBJ_SUFFIX)
#OBJ=$(WIN_OBJ_SUFFIX)

#=======================================================================
#
# macros for compile time options
#
# combined environment, compiler options and include path
CENVOPTS=$(MODEL) $(ENV) $(COPTS) $(INC_PATH)

# portable options 
CPTOPTS=$(CENVOPTS) $(GENPTOSOPTS) $(OSOPTS)

# library options 
CLIBOPTS=$(CENVOPTS) $(GENLIBOSOPTS) $(OSOPTS)

# acceptance test options
CACCOPTS=$(CENVOPTS) $(GENACCOSOPTS) $(OSOPTS)
CACCOPTS1=$(CENVOPTS) $(GENACCOSOPTS1) $(OSOPTS)
CACCOPTS2=$(CENVOPTS) $(GENACCOSOPTS2) $(OSOPTS)
CACCOPTS3=$(CENVOPTS) $(GENACCOSOPTS3) $(OSOPTS)
CACCOPTS4=$(CENVOPTS) $(GENACCOSOPTS4) $(OSOPTS)

# product options for portable build
CPRDPTOPTS="$(CPTOPTS) $(CZPTOPTS)"
CPRDPTOPTS1="$(CPTOPTS) $(CZPTOPTS1)"
CPRDPTOPTS2="$(CPTOPTS) $(CZPTOPTS2)"
CPRDPTOPTS3="$(CPTOPTS) $(CZPTOPTS3)"
CPRDPTOPTS4="$(CPTOPTS) $(CZPTOPTS4)"

# product options for acceptance test build
CPRDACCOPTS="$(CACCOPTS) $(CZACCOPTS)"
CPRDACCOPTS1="$(CACCOPTS1) $(CZACCOPTS1)"
CPRDACCOPTS2="$(CACCOPTS2) $(CZACCOPTS2)"
CPRDACCOPTS3="$(CACCOPTS3) $(CZACCOPTS3)"
CPRDACCOPTS4="$(CACCOPTS4) $(CZACCOPTS4)"

# product options for library build
CPRDLIBOPTS="$(CLIBOPTS) $(CZOPTS)"
CPRDLIBOPTS1="$(CLIBOPTS) $(CZOPTS1)"
CPRDLIBOPTS2="$(CLIBOPTS) $(CZOPTS2)"
CPRDLIBOPTS3="$(CLIBOPTS) $(CZOPTS3)"
CPRDLIBOPTS4="$(CLIBOPTS) $(CZOPTS4)"

# common stack manager file options for portable build
CSMPTOPTS="$(CPTOPTS) $(CZPTOPTS)"
CSMPTOPTS1="$(CPTOPTS) $(CZPTOPTS1)"
CSMPTOPTS2="$(CPTOPTS) $(CZPTOPTS2)"
CSMPTOPTS3="$(CPTOPTS) $(CZPTOPTS3)"
CSMPTOPTS4="$(CPTOPTS) $(CZPTOPTS4)"

# common stack manager file options for acceptance test build
CSMACCOPTS="$(CACCOPTS) $(CZOPTS) $(SMLCFLG) -DSM"
CSMACCOPTS1="$(CACCOPTS) $(CZOPTS1)"
CSMACCOPTS2="$(CACCOPTS) $(CZOPTS2)"
CSMACCOPTS3="$(CACCOPTS) $(CZOPTS3)"
CSMACCOPTS4="$(CACCOPTS) $(CZOPTS4)"

# common stack manager file options for library build
CSMLIBOPTS="$(CLIBOPTS) $(CZLIBOPTS)"
CSMLIBOPTS1="$(CLIBOPTS) $(CZLIBOPTS1)"
CSMLIBOPTS2="$(CLIBOPTS) $(CZLIBOPTS2)"
CSMLIBOPTS3="$(CLIBOPTS) $(CZLIBOPTS3)"
CSMLIBOPTS4="$(CLIBOPTS) $(CZLIBOPTS4)"
#Performance Options
CPRDPERFOPTS1="$(CACCOPTS1) $(CZPERFOPTS)"



# OS options
# Check if Flag CONVAL should be enbale from here
COSOPTS=$(CENVOPTS) $(GENACCOSOPTS) $(OSOPTS) -DSS_DRVR_SUPPORT

#=======================================================================
#
# macros for depend and lint options
#

# depend acceptance test
DEPOPTS_ACC="$(CZACCOPTS)"
DEPOPTS_ACC1="$(CZACCOPTS1)"
DEPOPTS_ACC2="$(CZACCOPTS2)"
DEPOPTS_ACC3="$(CZACCOPTS3)"
DEPOPTS_ACC4="$(CZACCOPTS4)"

# depend portable test
DEPOPTS_PT="$(CZPTOPTS)"

#=======================================================================
# Macros for hardcoded dependencies 
# SECTION 6
# 
# The following are enabled by default since we assume makedepend
# is not available. If makedepend is available in your environemnt
# uncomment out this section.
#
#
# environment
ENV_INC=$(CM_DIR)/envdep.h $(CM_DIR)/envopt.h

# system service interface
SSI_INC=$(CM_DIR)/ssi.h $(CM_DIR)/ssi.x

# general
GEN_INC=$(CM_DIR)/gen.h $(CM_DIR)/gen.x

# all system includes
SYS_INC=$(ENV_INC) $(GEN_INC) $(SSI_INC)

# product layer management - LCZ includes
LCZ_INC=$(CM_DIR)/lcz.h $(CM_DIR)/lcz.x

# TUCL Layer Management - LHI includes
LHI_INC=$(HI_DIR)/lhi.h $(HI_DIR)/lhi.x

# SCTP 
LSB_INC=$(CM_DIR)/lsb.h $(CM_DIR)/lsb.x

# X2AP Upper Interface - CZT includes
CZT_INC = $(CM_DIR)/czt.h $(CM_DIR)/czt.x

# product lower interface - HIT includes
HIT_INC=$(CM_DIR)/hit.h $(CM_DIR)/hit.x

# product lower interface - SCT includes
SCT_INC=$(CM_DIR)/sct.h $(CM_DIR)/sct.x

# common function library includes
CM_INC= $(CM_DIR)/cm_err.h   $(CM_DIR)/cm_lib.x   \
   $(CM_DIR)/cm_hash.h  $(CM_DIR)/cm_hash.x  \
   $(CM_DIR)/cm_llist.h $(CM_DIR)/cm_llist.x \
   $(CM_DIR)/cm_gen.h    \
   $(CM_DIR)/cm_tpt.h   $(CM_DIR)/cm_tpt.x   \
   $(CM_DIR)/cm_inet.h  $(CM_DIR)/cm_inet.x  \
   $(CM_DIR)/cm_tkns.h  $(CM_DIR)/cm_tkns.x  \
   $(CM_DIR)/cm_mblk.h  $(CM_DIR)/cm_mblk.x  \
   $(CM_DIR)/cm_dns.x   \
   $(CM_DIR)/cm_pasn.x  $(CM_DIR)/cm_pasn.x   \
   $(CM_DIR)/cm_mem.h   $(CM_DIR)/cm_mem.x

# TUCL includes
HI_INC=$(HI_DIR)/hi.h $(HI_DIR)/hi.x $(HI_DIR)/hi_err.h

# SB includes
SB_INC=$(SB_DIR)/sb.h $(SB_DIR)/sb.x $(SB_DIR)/sb_mtu.h $(SB_DIR)/sb_mtu.x

# X2AP includes
CZ_INC = $(CZ_DIR)/cz.h $(CZ_DIR)/cz.x $(CZ_DIR)/cz_err.h

# all product includes
CZALL_INC=$(LCZ_INC) $(CZ_INC) $(CZT_INC) $(SB_DIR) $(SB_ACC_DIR) $(HI_DIR) $(HI_ACC_DIR)

CZALLDEP_INC=$(LCZ_INC) $(LHI_INC) $(CZ_INC) $(HI_INC) $(SB_INC) $(LSB_INC)

# sample acceptance tests all includes
CZACCALL_INC=$(CZALL_INC) $(CZACC_INC)

# OS specific includes - SS includes
SS_INC=$(SS_DIR)/ss_dep.h $(SS_DIR)/ss_dep.x $(SS_DIR)/ss_err.h \
       $(SS_DIR)/ss_drvr.x $(SS_DIR)/ss_gen.h $(SS_DIR)/ss_gen.x \
       $(SS_DIR)/ss_mem.h $(SS_DIR)/ss_mem.x \
       $(SS_DIR)/ss_msg.h $(SS_DIR)/ss_msg.x \
       $(SS_DIR)/ss_queue.h $(SS_DIR)/ss_queue.x \
       $(SS_DIR)/ss_strm.h $(SS_DIR)/ss_strm.x \
       $(SS_DIR)/ss_task.h $(SS_DIR)/ss_task.x $(SS_DIR)/ss_timer.x

# OS specific includes - MTSS includes
MT_INC = $(MT_DIR)/mt_ss.h \
    $(MT_DIR)/mt_ss.x \
    $(MT_DIR)/mt_err.h

#=======================================================================
# Macros for source and object files
# SECTION 7 

# acceptance test controller source ----------------------------------

# acceptance test controller object ----------------------------------
TC_OBJS= $(SY_DIR)/cm_xta_ipc.$(OBJ) $(SY_DIR)/cm_xta_slave.$(OBJ) $(SY_DIR)/cm_xta_reg.$(OBJ) $(SY_DIR)/czac_prof.$(OBJ) $(SY_DIR)/czac_slave.$(OBJ)


# common source(C source files) for TC--------------------------------
TC_CM_SRCS = $(CM_DIR)/cm_gen.c  \
     $(CM_DIR)/cm_lib.c  \
     $(CM_DIR)/cm_hash.c \
     $(CM_DIR)/cm_bdy5.c \
     $(CM_DIR)/cm_inet.c \
     $(CM_DIR)/cm_tpt.c

# common objects for TC ----------------------------------------------
TC_CM_OBJS = $(SY_DIR)/cm_gen.$(OBJ)  \
     $(SY_DIR)/cm_lib.$(OBJ)  \
     $(SY_DIR)/cm_hash.$(OBJ) \
     $(SY_DIR)/cm_bdy5.$(OBJ) \
     $(SY_DIR)/cm_inet.$(OBJ) \
     $(SY_DIR)/cm_tpt.$(OBJ)

CZ_ACC_SRCS= \
	$(CZACC_DIR)/czac_cztcb.c \
	$(CZACC_DIR)/czac_czthdl.c \
	$(CZACC_DIR)/czac_db.c \
	$(CZACC_DIR)/czac_asn_pk.c \
	$(CZACC_DIR)/czac_asn_unpk.c \
	$(CZACC_DIR)/czac_asn_pk.c \
	$(CZACC_DIR)/czac_asn_unpk.c \
	$(CZACC_DIR)/czac_cztreg.c \
	$(CZACC_DIR)/czac_cztutl_r9.c \
	$(CZACC_DIR)/czac_cztutl_r11.c \
	$(CZACC_DIR)/czac_lczcb.c  \
	$(CZACC_DIR)/czac_lczhdl.c \
	$(CZACC_DIR)/czac_lczreg.c \
	$(CZACC_DIR)/czac_scthdl.c \
	$(CZACC_DIR)/czac_sctreg.c \
	$(CZACC_DIR)/czac_sctutl_r9.c \
	$(CZACC_DIR)/czac_sctutl_r11.c \
	$(CZACC_DIR)/czac_sctcb.c  \
	$(CZACC_DIR)/czac_sb_ex_ms.c  \
	$(CZACC_DIR)/rs_ex_ms.c  \
	$(CZACC_DIR)/rs_ptli.c  \
	$(CZACC_DIR)/czac_tst.c  \
	$(CZACC_DIR)/czac_prof.c  \
	$(CZACC_DIR)/czac_flag.c \
	$(CZACC_DIR)/czac_lczutl.c \
	$(CZACC_DIR)/czac_czld.c \
	$(CZACC_DIR)/czac_sctptui.c  
         
CZ_ACC2_SRCS= \
	$(CZACC_DIR)/czac_cztcb.c \
	$(CZACC_DIR)/czac_czthdl.c \
	$(CZACC_DIR)/czac_db.c \
	$(CZACC_DIR)/czac_asn_pk.c \
	$(CZACC_DIR)/czac_asn_unpk.c \
	$(CZACC_DIR)/czac_cztreg.c \
	$(CZACC_DIR)/czac_cztutl_r9.c \
	$(CZACC_DIR)/czac_cztutl_r11.c \
	$(CZACC_DIR)/czac_lhicb.c  \
	$(CZACC_DIR)/czac_lhihdl.c \
	$(CZACC_DIR)/czac_lhiutl.c \
	$(CZACC_DIR)/czac_lhireg.c \
	$(CZACC_DIR)/czac_lczcb.c  \
	$(CZACC_DIR)/czac_lczhdl.c \
	$(CZACC_DIR)/czac_lczreg.c \
	$(CZACC_DIR)/czac_scthdl.c \
	$(CZACC_DIR)/czac_sctreg.c \
	$(CZACC_DIR)/czac_sctutl_r9.c \
	$(CZACC_DIR)/czac_sctutl_r11.c \
	$(CZACC_DIR)/czac_sctcb.c  \
	$(CZACC_DIR)/czac_sb_ex_ms.c  \
	$(CZACC_DIR)/rs_ex_ms.c  \
	$(CZACC_DIR)/rs_ptli.c  \
	$(CZACC_DIR)/czac_tst.c  \
	$(CZACC_DIR)/czac_prof.c  \
	$(CZACC_DIR)/czac_flag.c \
	$(CZACC_DIR)/czac_lczutl.c \
	$(CZACC_DIR)/czac_czld.c \
	$(CZACC_DIR)/czac_sctptui.c  
 
# acceptance test object------------------------------------------------
CZ_ACC2_OBJS= \
	$(SY_DIR)/czac_cztcb.$(OBJ)     \
	$(SY_DIR)/czac_czthdl.$(OBJ)    \
	$(SY_DIR)/czac_db.$(OBJ)    \
	$(SY_DIR)/czac_asn_pk.$(OBJ)    \
	$(SY_DIR)/czac_asn_unpk.$(OBJ)    \
	$(SY_DIR)/czac_cztreg.$(OBJ)    \
	$(SY_DIR)/czac_cztutl_r9.$(OBJ)    \
	$(SY_DIR)/czac_cztutl_r11.$(OBJ)    \
	$(SY_DIR)/czac_lhireg.$(OBJ)    \
	$(SY_DIR)/czac_lhiutl.$(OBJ)    \
	$(SY_DIR)/czac_lhihdl.$(OBJ)    \
	$(SY_DIR)/czac_lhicb.$(OBJ)     \
	$(SY_DIR)/czac_lczcb.$(OBJ)     \
	$(SY_DIR)/czac_lczhdl.$(OBJ)    \
	$(SY_DIR)/czac_lczreg.$(OBJ)    \
	$(SY_DIR)/czac_scthdl.$(OBJ)    \
	$(SY_DIR)/czac_sctreg.$(OBJ)    \
	$(SY_DIR)/czac_sctutl_r9.$(OBJ)    \
	$(SY_DIR)/czac_sctutl_r11.$(OBJ)    \
	$(SY_DIR)/czac_sctcb.$(OBJ)     \
	$(SY_DIR)/czac_sb_ex_ms.$(OBJ)  \
	$(SY_DIR)/czac_tst.$(OBJ)    	  \
	$(SY_DIR)/czac_prof.$(OBJ)   	  \
	$(SY_DIR)/czac_flag.$(OBJ)   	  \
	$(SY_DIR)/czac_lczutl.$(OBJ)    \
	$(SY_DIR)/czac_czld.$(OBJ) \
	$(SY_DIR)/czac_sctptui.$(OBJ)


# acceptance test object------------------------------------------------
CZ_ACC_OBJS= \
	$(SY_DIR)/czac_cztcb.$(OBJ)     \
	$(SY_DIR)/czac_czthdl.$(OBJ)    \
	$(SY_DIR)/czac_db.$(OBJ)    \
	$(SY_DIR)/czac_asn_pk.$(OBJ)    \
	$(SY_DIR)/czac_asn_unpk.$(OBJ)    \
	$(SY_DIR)/czac_cztreg.$(OBJ)    \
	$(SY_DIR)/czac_cztutl_r9.$(OBJ)    \
	$(SY_DIR)/czac_cztutl_r11.$(OBJ)    \
	$(SY_DIR)/czac_lczcb.$(OBJ)     \
	$(SY_DIR)/czac_lczhdl.$(OBJ)    \
	$(SY_DIR)/czac_lczreg.$(OBJ)    \
	$(SY_DIR)/czac_scthdl.$(OBJ)    \
	$(SY_DIR)/czac_sctreg.$(OBJ)    \
	$(SY_DIR)/czac_sctutl_r9.$(OBJ)    \
	$(SY_DIR)/czac_sctutl_r11.$(OBJ)    \
	$(SY_DIR)/czac_sctcb.$(OBJ)     \
	$(SY_DIR)/czac_sb_ex_ms.$(OBJ)  \
	$(SY_DIR)/czac_tst.$(OBJ)    	  \
	$(SY_DIR)/czac_prof.$(OBJ)   	  \
	$(SY_DIR)/czac_flag.$(OBJ)   	  \
	$(SY_DIR)/czac_lczutl.$(OBJ)    \
	$(SY_DIR)/czac_czld.$(OBJ) \
	$(SY_DIR)/czac_sctptui.$(OBJ)

CZ_ACC1_SRCS= \
	$(CZACC_DIR)/czac_cztcb.c \
	$(CZACC_DIR)/czac_czthdl.c \
	$(CZACC_DIR)/czac_db.c \
	$(CZACC_DIR)/czac_asn_pk.c \
	$(CZACC_DIR)/czac_asn_unpk.c \
	$(CZACC_DIR)/czac_cztreg.c \
	$(CZACC_DIR)/czac_cztutl_r9.c \
	$(CZACC_DIR)/czac_cztutl_r11.c \
	$(CZACC_DIR)/czac_lczcb.c  \
	$(CZACC_DIR)/czac_lczhdl.c \
	$(CZACC_DIR)/czac_lczreg.c \
	$(CZACC_DIR)/czac_lhicb.c  \
	$(CZACC_DIR)/czac_lhihdl.c \
	$(CZACC_DIR)/czac_lhiutl.c \
	$(CZACC_DIR)/czac_lhireg.c \
	$(CZACC_DIR)/czac_lsbcb.c  \
	$(CZACC_DIR)/czac_lsbhdl.c \
	$(CZACC_DIR)/czac_lsbutl.c \
	$(CZACC_DIR)/czac_lsbreg.c \
	$(CZACC_DIR)/czac_scthdl.c \
	$(CZACC_DIR)/czac_sctreg.c \
	$(CZACC_DIR)/czac_sctutl_r9.c \
	$(CZACC_DIR)/czac_sctutl_r11.c \
	$(CZACC_DIR)/czac_sctcb.c  \
	$(CZACC_DIR)/czac_sb_ex_ms.c  \
	$(CZACC_DIR)/rs_ex_ms.c  \
	$(CZACC_DIR)/rs_ptli.c  \
	$(CZACC_DIR)/czac_tst.c  \
	$(CZACC_DIR)/czac_prof.c  \
	$(CZACC_DIR)/czac_flag.c \
	$(CZACC_DIR)/czac_lczutl.c \
	$(CZACC_DIR)/czac_czld.c \
	$(CZACC_DIR)/czac_sctptui.c  
         

# Performance acceptance test object------------------------------------------------
CZ_PERF_OBJS= \
	$(RS_PERF_OBJS)	\
        $(CZ_OBJS)    \
        $(SS_OBJS)    \
        $(OS_OBJS)    \
        $(SB_OBJS)    \
        $(HI_OBJS)    \
        $(CZT_OBJS)   \
        $(CZCM_OBJS)  \
        $(HICM_OBJS)  \
        $(SBCM_OBJS)  \
        $(CZSM_PERF_OBJS)  \
        $(SBSM_OBJS)  \
        $(HISM_OBJS)  \
        $(SM_OBJS)    \
        $(SY_DIR)/cz_ex_ms.$(OBJ)   

RS_PERF_OBJS= \
	$(SY_DIR)/rs_app.$(OBJ)     \
	$(SY_DIR)/rs_perf_tst.$(OBJ) \
	$(SY_DIR)/rssm.$(OBJ)    \
	$(SY_DIR)/rssm_hihdl.$(OBJ)  \
	$(SY_DIR)/rssm_sbhdl.$(OBJ)  \
	$(SY_DIR)/rssm_czhdl.$(OBJ)  \
	$(SY_DIR)/rssm_utl.$(OBJ)    \
	$(SY_DIR)/rs_tmr.$(OBJ)    \
        $(SY_DIR)/rs_perf_ex_ms.$(OBJ) \
        $(SY_DIR)/rs_perf_ptli.$(OBJ) 

RS_PERF_SRCS= \
	$(CZACC_DIR)/rs_app.c \
	$(CZACC_DIR)/rs_perf_tst.c \
	$(CZACC_DIR)/rssm.c \
	$(CZACC_DIR)/rssm_hihdl.c \
	$(CZACC_DIR)/rssm_sbhdl.c \
	$(CZACC_DIR)/rssm_czhdl.c  \
	$(CZACC_DIR)/rssm_utl.c \
	$(CZACC_DIR)/rs_tmr.c \
	$(CZACC_DIR)/rs_perf_ex_ms.c \
	$(CZACC_DIR)/rs_perf_ptli.c 

CZSM_PERF_OBJS = \
       $(SY_DIR)/smczexms_perf.$(OBJ) \
       $(SY_DIR)/smczptmi_perf.$(OBJ) 

# acceptance test object------------------------------------------------
CZ_ACC1_OBJS= \
	$(SY_DIR)/czac_cztcb.$(OBJ)     \
	$(SY_DIR)/czac_czthdl.$(OBJ)    \
	$(SY_DIR)/czac_db.$(OBJ)    \
	$(SY_DIR)/czac_asn_pk.$(OBJ)    \
	$(SY_DIR)/czac_asn_unpk.$(OBJ)    \
	$(SY_DIR)/czac_cztreg.$(OBJ)    \
	$(SY_DIR)/czac_cztutl_r9.$(OBJ)    \
	$(SY_DIR)/czac_cztutl_r11.$(OBJ)    \
	$(SY_DIR)/czac_lczcb.$(OBJ)     \
	$(SY_DIR)/czac_lczhdl.$(OBJ)    \
	$(SY_DIR)/czac_lczreg.$(OBJ)    \
	$(SY_DIR)/czac_lhireg.$(OBJ)    \
	$(SY_DIR)/czac_lhiutl.$(OBJ)    \
	$(SY_DIR)/czac_lhihdl.$(OBJ)    \
	$(SY_DIR)/czac_lhicb.$(OBJ)     \
	$(SY_DIR)/czac_lsbreg.$(OBJ)    \
	$(SY_DIR)/czac_lsbutl.$(OBJ)    \
	$(SY_DIR)/czac_lsbhdl.$(OBJ)    \
	$(SY_DIR)/czac_lsbcb.$(OBJ)     \
	$(SY_DIR)/czac_scthdl.$(OBJ)    \
	$(SY_DIR)/czac_sctreg.$(OBJ)    \
	$(SY_DIR)/czac_sctutl_r9.$(OBJ)    \
	$(SY_DIR)/czac_sctutl_r11.$(OBJ)    \
	$(SY_DIR)/czac_sctcb.$(OBJ)     \
	$(SY_DIR)/czac_sb_ex_ms.$(OBJ)  \
	$(SY_DIR)/czac_tst.$(OBJ)    	  \
	$(SY_DIR)/czac_prof.$(OBJ)   	  \
	$(SY_DIR)/czac_flag.$(OBJ)   	  \
	$(SY_DIR)/czac_lczutl.$(OBJ)    \
	$(SY_DIR)/czac_czld.$(OBJ) \
	$(SY_DIR)/czac_sctptui.$(OBJ)

# All acceptance sources for dummy + SCTP
CZ_ACC3_SRCS= \
	$(CZACC_DIR)/czac_cztcb.c \
	$(CZACC_DIR)/czac_czthdl.c \
	$(CZACC_DIR)/czac_db.c \
	$(CZACC_DIR)/czac_asn_pk.c \
	$(CZACC_DIR)/czac_asn_unpk.c \
	$(CZACC_DIR)/czac_cztreg.c \
	$(CZACC_DIR)/czac_cztutl_r9.c \
	$(CZACC_DIR)/czac_cztutl_r11.c \
	$(CZACC_DIR)/czac_lczcb.c  \
	$(CZACC_DIR)/czac_lczhdl.c \
	$(CZACC_DIR)/czac_lczreg.c \
	$(CZACC_DIR)/czac_lhicb.c  \
	$(CZACC_DIR)/czac_lhihdl.c \
	$(CZACC_DIR)/czac_lhiutl.c \
	$(CZACC_DIR)/czac_lhireg.c \
	$(CZACC_DIR)/czac_lsbcb.c  \
	$(CZACC_DIR)/czac_lsbhdl.c \
	$(CZACC_DIR)/czac_lsbutl.c \
	$(CZACC_DIR)/czac_lsbreg.c \
	$(CZACC_DIR)/czac_scthdl.c \
	$(CZACC_DIR)/czac_sctreg.c \
	$(CZACC_DIR)/czac_sctutl_r9.c \
	$(CZACC_DIR)/czac_sctutl_r11.c \
	$(CZACC_DIR)/czac_sctcb.c  \
	$(CZACC_DIR)/czac_sb_ex_ms.c  \
	$(CZACC_DIR)/rs_ex_ms.c  \
	$(CZACC_DIR)/rs_ptli.c  \
	$(CZACC_DIR)/czac_tst.c  \
	$(CZACC_DIR)/czac_prof.c  \
	$(CZACC_DIR)/czac_flag.c \
	$(CZACC_DIR)/czac_lczutl.c \
	$(CZACC_DIR)/czac_czld.c \
	$(CZACC_DIR)/czac_sctptui.c \
	$(CZACC_DIR)/czac_cztcb.c \
	$(CZACC_DIR)/czac_czthdl.c \
	$(CZACC_DIR)/czac_db.c \
	$(CZACC_DIR)/czac_asn_pk.c \
	$(CZACC_DIR)/czac_asn_unpk.c \
	$(CZACC_DIR)/czac_cztreg.c \
	$(CZACC_DIR)/czac_cztutl_r9.c \
	$(CZACC_DIR)/czac_cztutl_r11.c \
	$(CZACC_DIR)/czac_lczcb.c  \
	$(CZACC_DIR)/czac_lczhdl.c \
	$(CZACC_DIR)/czac_lczreg.c \
	$(CZACC_DIR)/czac_scthdl.c \
	$(CZACC_DIR)/czac_sctreg.c \
	$(CZACC_DIR)/czac_sctutl_r9.c \
	$(CZACC_DIR)/czac_sctutl_r11.c \
	$(CZACC_DIR)/czac_sctcb.c  \
	$(CZACC_DIR)/czac_sb_ex_ms.c  \
	$(CZACC_DIR)/rs_ex_ms.c  \
	$(CZACC_DIR)/rs_ptli.c  \
	$(CZACC_DIR)/czac_tst.c  \
	$(CZACC_DIR)/czac_prof.c  \
	$(CZACC_DIR)/czac_flag.c \
	$(CZACC_DIR)/czac_lczutl.c \
	$(CZACC_DIR)/czac_czld.c \
	$(CZACC_DIR)/czac_sctptui.c  
         
         
# acceptance test object------------------------------------------------
CZ_ACC3_OBJS= \
	$(SY_DIR)/czac_cztcb.$(OBJ)     \
	$(SY_DIR)/czac_czthdl.$(OBJ)    \
	$(SY_DIR)/czac_db.$(OBJ)    \
	$(SY_DIR)/czac_asn_pk.$(OBJ)    \
	$(SY_DIR)/czac_asn_unpk.$(OBJ)    \
	$(SY_DIR)/czac_cztreg.$(OBJ)    \
	$(SY_DIR)/czac_cztutl_r9.$(OBJ)    \
	$(SY_DIR)/czac_cztutl_r11.$(OBJ)    \
	$(SY_DIR)/czac_lczcb.$(OBJ)     \
	$(SY_DIR)/czac_lczhdl.$(OBJ)    \
	$(SY_DIR)/czac_lczreg.$(OBJ)    \
	$(SY_DIR)/czac_lhireg.$(OBJ)    \
	$(SY_DIR)/czac_lhiutl.$(OBJ)    \
	$(SY_DIR)/czac_lhihdl.$(OBJ)    \
	$(SY_DIR)/czac_lhicb.$(OBJ)     \
	$(SY_DIR)/czac_lsbreg.$(OBJ)    \
	$(SY_DIR)/czac_lsbutl.$(OBJ)    \
	$(SY_DIR)/czac_lsbhdl.$(OBJ)    \
	$(SY_DIR)/czac_lsbcb.$(OBJ)     \
	$(SY_DIR)/czac_scthdl.$(OBJ)    \
	$(SY_DIR)/czac_sctreg.$(OBJ)    \
	$(SY_DIR)/czac_sctutl_r9.$(OBJ)    \
	$(SY_DIR)/czac_sctutl_r11.$(OBJ)    \
	$(SY_DIR)/czac_sctcb.$(OBJ)     \
	$(SY_DIR)/czac_sb_ex_ms.$(OBJ)  \
	$(SY_DIR)/czac_tst.$(OBJ)    	  \
	$(SY_DIR)/czac_prof.$(OBJ)   	  \
	$(SY_DIR)/czac_flag.$(OBJ)   	  \
	$(SY_DIR)/czac_lczutl.$(OBJ)    \
	$(SY_DIR)/czac_czld.$(OBJ) \
	$(SY_DIR)/czac_sctptui.$(OBJ) 


CM_XTA_SRCS= \
	$(CZACC_DIR)/cm_xta_txn.c \
	$(CZACC_DIR)/cm_xta_ipc.c \
	$(CZACC_DIR)/cm_xta_intutl.c \
	$(CZACC_DIR)/cm_xta_tmr.c \
   $(CZACC_DIR)/cm_xta_inthdl.c \
	$(CZACC_DIR)/cm_xta_intreg.c \
	$(CZACC_DIR)/cm_xta_res.c \
   $(CZACC_DIR)/cm_xta_queue.c \
   $(CZACC_DIR)/cm_xta_log.c \
	$(CZACC_DIR)/cm_xta_slave.c \
	$(CZACC_DIR)/cm_xta_master.c \
	$(CZACC_DIR)/cm_xta_reg.c \
	$(CZACC_DIR)/cm_xta_tst.c \
	$(CZACC_DIR)/cm_xta_flag.c \
	$(CZACC_DIR)/cm_xta_py.c \
	$(CZACC_DIR)/cm_xta_ldfsm.c \
	$(CZACC_DIR)/cm_xta_xml.c \
	$(CZACC_DIR)/cm_xta_ex_ms.c \
	$(CZACC_DIR)/cm_xta_tgfsm.c \
	$(CZACC_DIR)/cm_xta_tafsm.c \
	$(CZACC_DIR)/cm_xta_tcfsm.c 

CM_XTA_OBJS= \
	$(SY_DIR)/cm_xta_tmr.$(OBJ) \
	$(SY_DIR)/cm_xta_ipc.$(OBJ) \
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
	$(SY_DIR)/cm_xta_ldfsm.$(OBJ) \
	$(SY_DIR)/cm_xta_xml.$(OBJ) \
	$(SY_DIR)/cm_xta_py.$(OBJ) \
	$(SY_DIR)/cm_xta_ex_ms.$(OBJ) \
	$(SY_DIR)/cm_xta_tgfsm.$(OBJ) \
	$(SY_DIR)/cm_xta_tafsm.$(OBJ) \
	$(SY_DIR)/cm_xta_tcfsm.$(OBJ) 




# new acceptance test object--------------------------------------------
CZNEWTC_OBJS = $(SY_DIR)/cm_xta_slave.$(OBJ)

# sample upper layer source---------------------------------------------
RS_SRCS = $(CZACC_DIR)/rs_ex_ms.c \
       $(CZACC_DIR)/rs_ptli.c

# sample upper layer objects--------------------------------------------
RS_OBJS = $(SY_DIR)/rs_ex_ms.$(OBJ) \
       $(SY_DIR)/rs_ptli.$(OBJ)


# Product source------------------------------------------------
CZ_SRCS = \
	$(CZ_DIR)/cz_id.c     \
	$(CZ_DIR)/cz_ptui.c   \
	$(CZ_DIR)/cz_ptmi.c   \
	$(CZ_DIR)/cz_lim.c   \
	$(CZ_DIR)/cz_lmm.c   \
	$(CZ_DIR)/cz_ex_ms.c   \
	$(CZ_DIR)/cz_uim.c   \
	$(CZ_DIR)/cz_nmm.c   \
	$(CZ_DIR)/cz_bmp.c   \
	$(CZ_DIR)/cz_gpm.c   \
	$(CZ_DIR)/cz_ldm.c   \
	$(CZ_DIR)/cz_tpm.c   \
	$(CZ_DIR)/cz_tmr.c   \
   $(CZ_DIR)/cz_utl.c      \
   $(CZ_DIR)/cz_db.c      \
   $(CZ_DIR)/cz_edm.c      \
	$(CZ_DIR)/cz_ptli.c


# Product objects-------------------------------------------------------
CZ_OBJS = \
	$(SY_DIR)/cz_id.$(OBJ)     \
	$(SY_DIR)/cz_ptmi.$(OBJ)   \
	$(SY_DIR)/cz_ptui.$(OBJ)   \
	$(SY_DIR)/cz_uim.$(OBJ)   \
	$(SY_DIR)/cz_lim.$(OBJ)   \
	$(SY_DIR)/cz_lmm.$(OBJ)   \
	$(SY_DIR)/cz_nmm.$(OBJ)   \
	$(SY_DIR)/cz_bmp.$(OBJ)   \
	$(SY_DIR)/cz_gpm.$(OBJ)   \
	$(SY_DIR)/cz_ldm.$(OBJ)   \
	$(SY_DIR)/cz_tpm.$(OBJ)   \
	$(SY_DIR)/cz_tmr.$(OBJ)   \
   $(SY_DIR)/cz_utl.$(OBJ)   \
   $(SY_DIR)/cz_db.$(OBJ)   \
   $(SY_DIR)/cz_edm.$(OBJ)   \
	$(SY_DIR)/cz_ptli.$(OBJ)


# Product source------------------------------------------------
CZ_SRCS1 = $(CZ_DIR)/cz_edm.c \
           $(CZ_DIR)/cz_dbs11.c \
           $(CZ_DIR)/cz_dbutl.c \
           $(CZ_DIR)/cz_util.c \

# Product objects-------------------------------------------------------
CZ_OBJS1 = \
      $(SY_DIR)/cz_edm.$(OBJ) \
      $(SY_DIR)/cz_dbs11.$(OBJ) \
      $(SY_DIR)/cz_dbs5.$(OBJ) \
      $(SY_DIR)/cz_dbutl.$(OBJ) \
      $(SY_DIR)/cz_util.$(OBJ)  


# TUCL source-------------------------------------------------
HI_SRCS = $(HI_DIR)/hi_bdy1.c  \
      $(HI_DIR)/hi_bdy2.c  \
      $(HI_DIR)/hi_bdy3.c  \
      $(HI_DIR)/hi_ex_ms.c \
      $(HI_DIR)/hi_ptui.c  \
      $(HI_DIR)/hi_ptmi.c  \
      $(HI_DIR)/hi_id.c

# TUCL objects------------------------------------------------
HI_OBJS = $(SY_DIR)/hi_bdy1.$(OBJ)  \
      $(SY_DIR)/hi_bdy2.$(OBJ)  \
      $(SY_DIR)/hi_bdy3.$(OBJ)  \
      $(SY_DIR)/hi_ex_ms.$(OBJ) \
      $(SY_DIR)/hi_ptui.$(OBJ)  \
      $(SY_DIR)/hi_ptmi.$(OBJ)  \
      $(SY_DIR)/hi_id.$(OBJ)

# SCTP source-------------------------------------------------
SB_SRCS = $(SB_DIR)/sb_bdy1.c \
      $(SB_DIR)/sb_bdy2.c  \
      $(SB_DIR)/sb_bdy3.c  \
      $(SB_DIR)/sb_bdy4.c  \
      $(SB_DIR)/sb_ex_ms.c \
      $(SB_DIR)/sb_mtu.c   \
      $(SB_DIR)/sb_port.c  \
      $(SB_DIR)/sb_ptui.c  \
      $(SB_DIR)/sb_ptmi.c  \
      $(SB_DIR)/sb_ptli.c  \
      $(SB_DIR)/sb_id.c

# SCTP objects------------------------------------------------
SB_OBJS = $(SY_DIR)/sb_bdy1.$(OBJ)  \
      $(SY_DIR)/sb_bdy2.$(OBJ)  \
      $(SY_DIR)/sb_bdy3.$(OBJ)  \
      $(SY_DIR)/sb_bdy4.$(OBJ)  \
      $(SY_DIR)/sb_ex_ms.$(OBJ) \
      $(SY_DIR)/sb_mtu.$(OBJ) \
      $(SY_DIR)/sb_port.$(OBJ) \
      $(SY_DIR)/sb_ptui.$(OBJ)  \
      $(SY_DIR)/sb_ptmi.$(OBJ)  \
      $(SY_DIR)/sb_ptli.$(OBJ)  \
      $(SY_DIR)/sb_id.$(OBJ)


# common source(C source files)-----------------------------------------
CZCM_SRCS = $(CM_DIR)/cm_gen.c \
    $(CM_DIR)/cm_lib.c \
    $(CM_DIR)/cm_hash.c \
    $(CM_DIR)/cm_llist.c \
    $(CM_DIR)/cm_bdy5.c \
    $(CM_DIR)/cm_inet.c \
    $(CM_DIR)/cm_tpt.c \
    $(CM_DIR)/cm_tkns.c \
    $(CM_DIR)/cm_mblk.c \
    $(CM_DIR)/czt_pk.c \
    $(CM_DIR)/czt_unpk.c \
    $(CM_DIR)/cm_pasn1.c \
    $(CM_DIR)/cm_pasn2.c \
    $(CM_DIR)/cm_pasn3.c \
    $(CM_DIR)/cm_pasn4.c \
    $(CM_DIR)/cm_dns.c \
    $(CM_DIR)/czt.c \
    $(CM_DIR)/lcz.c \
    $(CM_DIR)/sct.c 


# common objects--------------------------------------------------------
CZCM_OBJS = $(SY_DIR)/cm_gen.$(OBJ) \
   $(SY_DIR)/cm_lib.$(OBJ) \
   $(SY_DIR)/cm_hash.$(OBJ) \
   $(SY_DIR)/cm_llist.$(OBJ) \
   $(SY_DIR)/cm_bdy5.$(OBJ) \
   $(SY_DIR)/cm_inet.$(OBJ) \
   $(SY_DIR)/cm_tpt.$(OBJ) \
   $(SY_DIR)/cm_tkns.$(OBJ) \
   $(SY_DIR)/cm_mblk.$(OBJ) \
   $(SY_DIR)/czt_unpk.$(OBJ) \
   $(SY_DIR)/czt_pk.$(OBJ) \
   $(SY_DIR)/cm_pasn1.$(OBJ) \
   $(SY_DIR)/cm_pasn2.$(OBJ) \
   $(SY_DIR)/cm_pasn3.$(OBJ) \
   $(SY_DIR)/cm_pasn4.$(OBJ) \
   $(SY_DIR)/cm_dns.$(OBJ) \
   $(SY_DIR)/lcz.$(OBJ) \
   $(SY_DIR)/czt.$(OBJ) \
   $(SY_DIR)/sct.$(OBJ) 

# common sources related to HI
HICM_SRCS = $(CM_DIR)/lhi.c \
            $(CM_DIR)/hit.c

# common objects related to HI
HICM_OBJS = $(SY_DIR)/lhi.$(OBJ)  \
	         $(SY_DIR)/hit.$(OBJ)

# common srcs related to SB
SBCM_SRCS = $(CM_DIR)/lsb.c 

# common objects related to SB
SBCM_OBJS = $(SY_DIR)/lsb.$(OBJ)  

# common stack manager source-------------------------------------------
SM_SRCS = $(SM_DIR)/sm_bdy1.c \
     $(SM_DIR)/sm_ex_ms.c

# common stack manager objects------------------------------------------
SM_OBJS = $(SY_DIR)/sm_bdy1.$(OBJ) \
     $(SY_DIR)/sm_ex_ms.$(OBJ)

# Product stack manager source------------------------------------------
CZSM_SRCS = \
       $(CZSM_DIR)/smczexms.c \
       $(CZSM_DIR)/smczptmi.c \
#       $(CZSM_DIR)/smczbdy1.c 

# Product stack manager objects-----------------------------------------
CZSM_OBJS = \
       $(SY_DIR)/smczexms.$(OBJ) \
       $(SY_DIR)/smczptmi.$(OBJ) \
#       $(SY_DIR)/smczbdy1.$(OBJ) 

# TUCL stack manager source------------------------------------------
HISM_SRCS = $(HI_ACC_DIR)/smhiexms.c \
       $(HI_ACC_DIR)/smhiptmi.c \
       #$(HISM_DIR)/smhibdy1.c 

# TUCL stack manager objects-----------------------------------------
HISM_OBJS = $(SY_DIR)/smhiexms.$(OBJ) \
       $(SY_DIR)/smhiptmi.$(OBJ) \
       #$(SY_DIR)/smhibdy1.$(OBJ) 

# SCTP stack manager source------------------------------------------
SBSM_SRCS = $(SB_ACC_DIR)/smsbexms.c \
       $(SB_ACC_DIR)/smsbptmi.c \
# $(SBSM_DIR)/smsbbdy1.c 
		  
# SCTP stack manager objects-----------------------------------------
SBSM_OBJS = $(SY_DIR)/smsbexms.$(OBJ) \
       $(SY_DIR)/smsbptmi.$(OBJ) \
# $(SY_DIR)/smsbbdy1.$(OBJ) 
		  
# OS - common sources---------------------------------------------------
SS_SRCS = $(SS_DIR)/ss_gen.c              \
     $(SS_DIR)/ss_task.c             \
     $(SS_DIR)/ss_drvr.c             \
     $(SS_DIR)/ss_timer.c            \
     $(SS_DIR)/ss_mem.c              \
     $(SS_DIR)/ss_strm.c             \
     $(SS_DIR)/ss_msg.c              \
     $(SS_DIR)/ss_queue.c            \
     $(SS_DIR)/ss_pack.c             \
     $(SS_DIR)/ss_rtr.c              \
     $(CM_DIR)/cm_mem.c

# OS - common objects---------------------------------------------------
SS_OBJS = $(SY_DIR)/ss_gen.$(OBJ)         \
     $(SY_DIR)/ss_task.$(OBJ)        \
     $(SY_DIR)/ss_drvr.$(OBJ)        \
     $(SY_DIR)/ss_timer.$(OBJ)       \
     $(SY_DIR)/ss_mem.$(OBJ)         \
     $(SY_DIR)/ss_strm.$(OBJ)        \
     $(SY_DIR)/ss_msg.$(OBJ)         \
     $(SY_DIR)/ss_queue.$(OBJ)       \
     $(SY_DIR)/ss_pack.$(OBJ)        \
     $(SY_DIR)/ss_rtr.$(OBJ)         \
     $(SY_DIR)/cm_mem.$(OBJ)

# OS - MT sources-------------------------------------------------------
MT_SRCS= \
   $(OS_DIR)/mt_ss.c               \
   $(OS_DIR)/mt_id.c

# OS - MT objects-------------------------------------------------------
MT_OBJS= \
   $(SY_DIR)/mt_ss.$(OBJ)          \
   $(SY_DIR)/mt_id.$(OBJ)

# OS - NT sources-------------------------------------------------------
NS_SRCS= \
   $(OS_DIR)/ns_gen.c              \
   $(OS_DIR)/smnsexms.c            \
   $(OS_DIR)/smnsbdy1.c            \
   $(OS_DIR)/smnsptmi.c            \
   $(OS_DIR)/lns.c                 \
   $(OS_DIR)/ns_ex_ms.c            \
   $(OS_DIR)/ns_id.c               \
   $(OS_DIR)/ns_ptmi.c             \
   $(OS_DIR)/ns_space.c            \
   $(OS_DIR)/ns_task.c             \
   $(OS_DIR)/ns_timer.c

# OS - NT objects-------------------------------------------------------
NS_OBJS= \
   $(SY_DIR)/ns_gen.$(OBJ)         \
   $(SY_DIR)/smnsexms.$(OBJ)       \
   $(SY_DIR)/smnsbdy1.$(OBJ)       \
   $(SY_DIR)/smnsptmi.$(OBJ)       \
   $(SY_DIR)/lns.$(OBJ)            \
   $(SY_DIR)/ns_ex_ms.$(OBJ)       \
   $(SY_DIR)/ns_id.$(OBJ)          \
   $(SY_DIR)/ns_ptmi.$(OBJ)        \
   $(SY_DIR)/ns_space.$(OBJ)       \
   $(SY_DIR)/ns_task.$(OBJ)        \
   $(SY_DIR)/ns_timer.$(OBJ)

# VxWorks sources---------------------------------------------------
VW_SRCS = $(OS_DIR)/vw_ss.c               \
     $(OS_DIR)/vw_id.c

# VxWorks objects---------------------------------------------------
VW_OBJS = $(SY_DIR)/vw_ss.$(OBJ)          \
     $(SY_DIR)/vw_id.$(OBJ)

# portable build sources------------------------------------------------
PT_SRCS= $(CZ_DIR)/cz_tst.c              \
    $(CZ_DIR)/cz_ex_pt.c                 \
    $(CM_DIR)/ss_ptsp.c

# portable build objects------------------------------------------------
PT_OBJS= $(SY_DIR)/cz_tst.$(OBJ)         \
    $(SY_DIR)/cz_ex_pt.$(OBJ)            \
    $(SY_DIR)/ss_ptsp.$(OBJ)

# Dummy  acceptance test sources ------------------------------
PRDACC_SRCS= \
    $(CZ_SRCS) \
    $(CZ_ACC_SRCS)   \
    $(CM_XTA_SRCS)   \
    $(CZSM_SRCS) \
    $(CZCM_SRCS) \
    $(SS_SRCS)   \
    $(OS_SRCS)   \
    $(SM_SRCS)   \
    $(CZT_SRCS)   \

# Dummy  acceptance test objects ------------------------------
PRDACC_OBJS= \
    $(CZ_OBJS)       \
    $(SY_DIR)/cz_ex_ms.$(OBJ)   \
    $(CZ_ACC_OBJS)  \
    $(CM_XTA_OBJS)   \
    $(CZSM_OBJS)     \
    $(CZCM_OBJS)     \
    $(SM_OBJS)       \
    $(RS_OBJS)       \
    $(SS_OBJS)       \
    $(OS_OBJS)       

# Sources with trillium SCTP--------------------------------------------
PRDACC_SRCS1= \
    $(CZ_SRCS) \
    $(CZ_ACC1_SRCS)   \
    $(CM_XTA_SRCS)   \
    $(CZSM_SRCS) \
    $(SBSM_SRCS)\
    $(HISM_SRCS)\
    $(HICM_SRCS) \
    $(SBCM_SRCS) \
    $(CZCM_SRCS) \
    $(SS_SRCS)   \
    $(OS_SRCS)   \
    $(SB_SRCS)       \
    $(HI_SRCS)   \
    $(RS_SRCS)   \
    $(SM_SRCS)   \
    $(CZT_SRCS)   


# Objects with trillium SCTP--------------------------------------------
PRDACC_OBJS1= \
   $(CZ_OBJS)       \
   $(CZ_ACC1_OBJS)  \
   $(CM_XTA_OBJS)   \
   $(CZSM_OBJS)     \
   $(SBSM_OBJS)\
   $(HISM_OBJS) \
   $(HICM_OBJS) \
   $(SBCM_OBJS) \
   $(CZCM_OBJS)     \
   $(SS_OBJS)       \
   $(OS_OBJS)       \
   $(SB_OBJS)       \
   $(HI_OBJS)   \
   $(RS_OBJS)       \
   $(SM_OBJS)   \
   $(CZT_OBJS)   \
   $(SY_DIR)/cz_ex_ms.$(OBJ)   

# acceptance test source with KSCTP ----------------------------------------
PRDACC_SRCS2= \
    $(CZ_SRCS) \
    $(CZ_ACC2_SRCS)   \
    $(CZSM_SRCS) \
    $(RS_SRCS)  \
    $(CZCM_SRCS) \
    $(HICM_SRCS) \
    $(SS_SRCS)   \
    $(OS_SRCS)   \
    $(SM_SRCS)   \
    $(HI_SRCS)   \
    $(HISM_SRCS)

# acceptance test objects with KSCTP
PRDACC_OBJS2= \
	$(CZ_ACC2_OBJS)  \
	$(CZ_OBJS)     \
	$(CM_XTA_OBJS) \
	$(CZCM_OBJS)  \
	$(HI_OBJS)     \
        $(RS_OBJS)  \
	$(SM_OBJS)     \
        $(HICM_OBJS) \
	$(CZSM_OBJS)   \
        $(HISM_OBJS)\
	$(SY_DIR)/cz_ex_ms.$(OBJ)  \
	#$(OS_OBJS)    \

# acceptance test source for slave ----------------------------------------
PRDACC_SRCS3= \
    $(CZ_SRCS) \
    $(CZAC_SRCS)   \
    $(CZSM_SRCS) \
    $(CZCM_SRCS) \
    $(SS_SRCS)   \
    $(OS_SRCS)   \
    $(SM_SRCS)   \
    $(HI_SRCS)   \

# acceptance test objects for Dummy + SCTP
PRDACC_OBJS3= \
   $(CZ_OBJS)       \
   $(CZ_ACC3_OBJS)  \
   $(CM_XTA_OBJS)   \
   $(CZSM_OBJS)     \
   $(SBSM_OBJS)\
   $(HISM_OBJS) \
   $(HICM_OBJS) \
   $(SBCM_OBJS) \
   $(CZCM_OBJS)     \
   $(SS_OBJS)       \
   $(OS_OBJS)       \
   $(SB_OBJS)       \
   $(HI_OBJS)   \
   $(RS_OBJS)       \
   $(SM_OBJS)   \
   $(CZT_OBJS)   \
   $(SY_DIR)/cz_ex_ms.$(OBJ)   


# New acceptance test objects  for SLAVE
PRDACC_OBJS4= \
    $(TC_OBJS)  \
    $(CZ_OBJS)       \
	$(SY_DIR)/cz_ex_ms.$(OBJ)   \
    $(CZCM_OBJS)     \
    $(HICM_OBJS)     \
    $(SBCM_OBJS)     \
    $(SS_OBJS) \
    $(OS_OBJS) \
    $(SB_OBJS)       \
    $(HI_OBJS)      \
#    $(CZSM_OBJS)     \
    $(SBSM_OBJS)     \
    $(HISM_OBJS)     \
    $(SM_OBJS)       \

# all portable sources--------------------------------------------------
PRDPT_SRCS=  \
   $(PT_SRCS)                      \
   $(CZ_SRCS)                      \
   $(CZCM_SRCS)

# all portable objects--------------------------------------------------
PRDPT_OBJS= \
   $(PT_OBJS)                      \
   $(CZ_OBJS)                      \
   $(CZCM_OBJS)

# all library objects--------------------------------------------------
PRDLIB_OBJS= \
   $(LIB_OBJS)\
   $(CZ_OBJS)\
   $(CZCM_OBJS)

# special programs required for Internal Development by makefile
# adjust as required
#
# System Binary Dir - replace with appropriate directory and programe
# for system

BIN=/bin
MAKEDEPEND=makedepend
REMOVE=$(BIN)/rm -f
CAT=cat
DELETE=del
OPENSSL=openssl
#
# build targets
# 

# clean-----------------------------------------------------------------
#
# cleans up everything...
#
clean:
	$(REMOVE) $(SY_DIR)/*.$(OBJ) $(SY_DIR)/$(BINACC) $(SY_DIR)/$(BINTC) \
	$(SY_DIR)/$(BINPT) $(SY_DIR)/*.ln $(SY_DIR)/*.s *.$(OBJ) $(SY_DIR)/*.lib \
	$(BINACC) $(BINPT) *.ln *.s

win_clean:
	$(DELETE) *.$(OBJ)
	$(DELETE) $(BINACC).exe
	$(DELETE) $(BINTC).exe
	$(DELETE) $(BINPT).exe
	$(DELETE) *.ln
	$(DELETE) *.s


# external target for acceptance test including SCTP and KSCTP
acc:
	@$(MAKE) -f $(MAKENAME) $(BLDENV) INC_PATH=$(ACC_INC_PATH) \
	OUTNAME=$(BINACC) F_OBJS="$(PRDACC_OBJS)"

# External target for new acceptance test build without SCTP
acc1:
	@$(MAKE) -f $(MAKENAME) $(BLDENV) INC_PATH=$(ACC_INC_PATH) \
	OUTNAME=$(BINACC) F_OBJS="$(PRDACC_OBJS1)"

# External target for new acceptance test build with KSCTP
acc2:
	@$(MAKE) -f $(MAKENAME) $(BLDENV) INC_PATH=$(ACC_INC_PATH) \
	OUTNAME=$(BINACC) F_OBJS="$(PRDACC_OBJS2)"

# External target for new acceptance test build with KSCTP
acc3:
	@$(MAKE) -f $(MAKENAME) $(BLDENV) INC_PATH=$(ACC_INC_PATH) \
	OUTNAME=$(BINACC) F_OBJS="$(PRDACC_OBJS3)"

# External target for new acceptance test build for slave
acc4:
	@$(MAKE) -f $(MAKENAME) $(BLDENV) INC_PATH=$(ACC_INC_PATH) \
	OUTNAME=$(BINACC) F_OBJS="$(PRDACC_OBJS4)"

# Performance test build
perf:
	@$(MAKE) -f $(MAKENAME) $(BLDENV) INC_PATH=$(ACC_INC_PATH) \
	OUTNAME=$(PERFACC) F_OBJS="$(CZ_PERF_OBJS)"

# External target for portable build
pt:
	@$(MAKE) -f $(MAKENAME) $(BLDENV) OUTNAME=$(BINPT)
	INC_PATH=$(PT_INC_PATH)

pt1:
	@$(MAKE) -f $(MAKENAME) $(BLDENV) OUTNAME=$(BINPT1)
	INC_PATH=$(PT_INC_PATH)

pt2:
	@$(MAKE) -f $(MAKENAME) $(BLDENV) OUTNAME=$(BINPT2)
	INC_PATH=$(PT_INC_PATH)

pt3:
	@$(MAKE) -f $(MAKENAME) $(BLDENV) OUTNAME=$(BINPT3)
	INC_PATH=$(PT_INC_PATH)

pt4:
	@$(MAKE) -f $(MAKENAME) $(BLDENV) OUTNAME=$(BINPT4)
	INC_PATH=$(PT_INC_PATH)


# External target for Library build

lib:
	@$(MAKE) -f $(MAKENAME) $(BLDENV) OUTNAME=$(BINLIB)
	INC_PATH=$(LIB_INC_PATH)

lib1:
	@$(MAKE) -f $(MAKENAME) $(BLDENV) OUTNAME=$(BINLIB1)
	INC_PATH=$(LIB_INC_PATH)

lib2:
	@$(MAKE) -f $(MAKENAME) $(BLDENV) OUTNAME=$(BINLIB2)
	INC_PATH=$(LIB_INC_PATH)

lib3:
	@$(MAKE) -f $(MAKENAME) $(BLDENV) OUTNAME=$(BINLIB3)
	INC_PATH=$(LIB_INC_PATH)

lib4:
	@$(MAKE) -f $(MAKENAME) $(BLDENV) OUTNAME=$(BINLIB4)
	INC_PATH=$(LIB_INC_PATH)

#=======================================================================
# SECTION 8 and 9
# Portable Target builds for Solaris CC, Solaris GNU, MRI mcc68k on
# Solaris, Linux GNU and Microczft Visual C++ for WINNT/WIN95
#
# Solaris CC portable build---------------------------------------------
#
$(BINSOLPT):
	@$(MAKE) -f $(MAKENAME) $(MAKEPT) -e ENV=$(SOLENV) CC=$(SOLCC)  \
	LD=$(SOLLD) COPTS=$(SOLCOPTS) LOPTS=$(SOLLOPTS) LIBS=$(SOLLIBS) \
	OBJ=$(UNIX_OBJ_SUFFIX) INC_PATH=$(PT_INC_PATH) OSOPTS=$(PTOSOPTS)

#
# Solaris GNU portable build--------------------------------------------
#
$(BINGNUPT):
	@$(MAKE) -f $(MAKENAME) $(MAKEPT) -e ENV=$(GNUENV) CC=$(GNUCC) \
	LD=$(GNULD) COPTS=$(GNUCOPTS) LOPTS=$(GNULOPTS) LIBS=$(GNULIBS) \
	OBJ=$(UNIX_OBJ_SUFFIX) INC_PATH=$(PT_INC_PATH) OSOPTS=$(PTOSOPTS)

#
# Linux GNU portable build--------------------------------------------
#
$(BINLNXPT):
	@$(MAKE) -f $(MAKENAME) $(MAKEPT) -e ENV=$(LNXENV) CC=$(LNXCC) \
	LD=$(LNXLD) COPTS=$(LNXCOPTS) LOPTS=$(LNXLOPTS) LIBS=$(LNXLIBS) \
	OBJ=$(UNIX_OBJ_SUFFIX) INC_PATH=$(PT_INC_PATH) OSOPTS=$(PTOSOPTS)

#
# Microczft Visual C++ for WINNT/WIN95 portable build-------------------
#
$(BINWINPT):
	@$(MAKE) -f $(MAKENAME) $(MAKEPT) -e ENV=$(WINENV) CC=$(WINCC) \
	LD=$(WINLD) COPTS=$(WINCOPTS) LOPTS=$(WINLOPTS) LIBS=$(WINLIBS) \
	OBJ=$(WIN_OBJ_SUFFIX) INC_PATH=$(PT_INC_PATH) OSOPTS=$(PTOSOPTS)

#
# MicroTec Research Compiler in Solaris Environment---------------------
$(BINMRIPT):
	@$(MAKE) -f $(MAKENAME) $(MAKEPT) -e ENV=$(MRIENV) CC=$(MRICC) \
	LD=$(MRILD) COPTS=$(MRICOPTS) LOPTS=$(MRILOPTS) LIBS=$(MRILIBS) \
	OBJ=$(UNIX_OBJ_SUFFIX) INC_PATH=$(PT_INC_PATH) OSOPTS=$(PTOSOPTS)

#
# Linux g++ portable build--------------------------------------------
#
$(BINGPPPT):
	@$(MAKE) -f $(MAKENAME) $(MAKEPT) -e ENV=$(LNXENV) CC=$(GPPCC) \
	LD=$(GPPLD) COPTS=$(GPPCOPTS) LOPTS=$(LNXLOPTS) LIBS=$(LNXLIBS) \
	OBJ=$(UNIX_OBJ_SUFFIX) INC_PATH=$(PT_INC_PATH) OSOPTS=$(PTOSOPTS)

# Linux c++ portable build--------------------------------------------
#
$(BINCPPPT):
	@$(MAKE) -f $(MAKENAME) $(MAKEPT) -e ENV=$(LNXENV) CC=$(CPPCC) \
	LD=$(CPPLD) COPTS=$(CPPCOPTS) LOPTS=$(LNXLOPTS) LIBS=$(LNXLIBS) \
	OBJ=$(UNIX_OBJ_SUFFIX) INC_PATH=$(PT_INC_PATH) OSOPTS=$(PTOSOPTS)

#
# VxWorks portable build--------------------------------------------
#
$(BINPPCPT):
	@$(MAKE) -f $(MAKENAME) $(MAKEPT) -e ENV=$(PPCENV) CC=$(PPCCC) \
	LD=$(PPCLD) COPTS=$(PPCCOPTS) LOPTS=$(PPCLOPTS) LIBS=$(PPCLIBS) \
	OBJ=$(UNIX_OBJ_SUFFIX) INC_PATH=$(PT_INC_PATH) OSOPTS=$(PTOSOPTS)


#
# Acceptance test target builds for Solaris CC, Solaris GNU, Linux GNU,
# Insite Memory Check tool and Microczft Visual C++ for WINNT/WIN95
#
# Linux CC acceptance test build--------------------------------------
#
$(BINSOLACC):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC) -e ENV=$(SOLENV) CC=$(SOLCC) \
	LD=$(SOLLD) COPTS=$(SOLCOPTS) LOPTS=$(SOLLOPTS) LIBS=$(SOLLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(MTOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

$(BINSOLACC1):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC1) -e ENV=$(SOLENV) CC=$(SOLCC) \
	LD=$(SOLLD) COPTS=$(SOLCOPTS) LOPTS=$(SOLLOPTS) LIBS=$(SOLLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(MTOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

$(BINSOLACC2):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC2) -e ENV=$(SOLENV) CC=$(SOLCC) \
	LD=$(SOLLD) COPTS=$(SOLCOPTS) LOPTS=$(SOLLOPTS) LIBS=$(SOLLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(MTOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

$(BINSOLACC3):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC3) -e ENV=$(SOLENV) CC=$(SOLCC) \
	LD=$(SOLLD) COPTS=$(SOLCOPTS) LOPTS=$(SOLLOPTS) LIBS=$(SOLLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(MTOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

$(BINSOLACC4):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC4) -e ENV=$(SOLENV) CC=$(SOLCC) \
	LD=$(SOLLD) COPTS=$(SOLCOPTS) LOPTS=$(SOLLOPTS1) LIBS=$(SOLLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(MTOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

#
# Solaris GNU acceptance test build-------------------------------------
#
$(BINGNUACC):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC) -e ENV=$(GNUENV) CC=$(GNUCC) \
	LD=$(GNULD) COPTS=$(GNUCOPTS) LOPTS=$(GNULOPTS) LIBS=$(GNULIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(MTOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

$(BINGNUACC1):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC1) -e ENV=$(GNUENV) CC=$(GNUCC) \
	LD=$(GNULD) COPTS=$(GNUCOPTS) LOPTS=$(GNULOPTS) LIBS=$(GNULIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(MTOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

$(BINGNUACC2):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC2) -e ENV=$(GNUENV) CC=$(GNUCC) \
	LD=$(GNULD) COPTS=$(GNUCOPTS) LOPTS=$(GNULOPTS) LIBS=$(GNULIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(MTOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

$(BINGNUACC3):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC3) -e ENV=$(GNUENV) CC=$(GNUCC) \
	LD=$(GNULD) COPTS=$(GNUCOPTS) LOPTS=$(GNULOPTS) LIBS=$(GNULIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(MTOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

$(BINGNUACC4):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC4) -e ENV=$(GNUENV) CC=$(GNUCC) \
	LD=$(GNULD) COPTS=$(GNUCOPTS) LOPTS=$(GNULOPTS) LIBS=$(GNULIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(MTOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

#
# Linux GNU Purify acceptance test build--------------------------------
#
$(BINPURACC):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC) -e ENV=$(PURENV) CC=$(PURCC) \
	LD=$(PURLD) COPTS=$(PURCOPTS) LOPTS=$(PURLOPTS) LIBS=$(PURLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(LNXOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

$(BINPURACC1):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC1) -e ENV=$(PURENV) CC=$(PURCC) \
	LD=$(PURLD) COPTS=$(PURCOPTS) LOPTS=$(PURLOPTS1) LIBS=$(PURLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(LNXOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

$(BINPURACC2):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC2) -e ENV=$(PURENV) CC=$(PURCC) \
	LD=$(PURLD) COPTS=$(PURCOPTS) LOPTS=$(PURLOPTS) LIBS=$(PURLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(LNXOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

$(BINPURACC3):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC3) -e ENV=$(PURENV) CC=$(PURCC) \
	LD=$(PURLD) COPTS=$(PURCOPTS) LOPTS=$(PURLOPTS) LIBS=$(PURLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(LNXOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

$(BINPURACC4):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC4) -e ENV=$(PURENV) CC=$(PURCC) \
	LD=$(PURLD) COPTS=$(PURCOPTS) LOPTS=$(PURLOPTS1) LIBS=$(PURLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(LNXOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

#
# Linux GNU Quantify acceptance test build------------------------------
#
$(BINQUANACC):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC) -e ENV=$(PURENV) CC=$(QUANTIFYCC) \
	LD=$(QUANTIFYLD) COPTS=$(PURCOPTS) LOPTS=$(PURLOPTS1) LIBS=$(PURLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(LNXOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

$(BINQUANACC1):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC1) -e ENV=$(PURENV) CC=$(QUANTIFYCC) \
	LD=$(QUANTIFYLD) COPTS=$(PURCOPTS) LOPTS=$(PURLOPTS1) LIBS=$(PURLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(LNXOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

$(BINQUANACC2):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC2) -e ENV=$(PURENV) CC=$(QUANTIFYCC) \
	LD=$(QUANTIFYLD) COPTS=$(PURCOPTS) LOPTS=$(PURLOPTS) LIBS=$(PURLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(LNXOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

$(BINQUANACC3):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC3) -e ENV=$(PURENV) CC=$(QUANTIFYCC) \
	LD=$(QUANTIFYLD) COPTS=$(PURCOPTS) LOPTS=$(PURLOPTS) LIBS=$(PURLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(LNXOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

$(BINQUANACC4):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC4) -e ENV=$(PURENV) CC=$(QUANTIFYCC) \
	LD=$(QUANTIFYLD) COPTS=$(PURCOPTS) LOPTS=$(PURLOPTS) LIBS=$(PURLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(LNXOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

#
# Linux GNU Purify coverage acceptance test build-----------------------
#
$(BINCOVACC):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC) -e ENV=$(PURENV) CC=$(PURCOVCC) \
	LD=$(PURCOVLD) COPTS=$(PURCOPTS) LOPTS=$(PURLOPTS) LIBS=$(PURLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(LNXOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

$(BINCOVACC1):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC1) -e ENV=$(PURENV) CC=$(PURCOVCC) \
	LD=$(PURCOVLD) COPTS=$(PURCOPTS) LOPTS=$(PURLOPTS1) LIBS=$(PURLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(LNXOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

$(BINCOVACC2):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC2) -e ENV=$(PURENV) CC=$(PURCOVCC) \
	LD=$(PURCOVLD) COPTS=$(PURCOPTS) LOPTS=$(PURLOPTS) LIBS=$(PURLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(LNXOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

$(BINCOVACC3):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC3) -e ENV=$(PURENV) CC=$(PURCOVCC) \
	LD=$(PURCOVLD) COPTS=$(PURCOPTS) LOPTS=$(PURLOPTS) LIBS=$(PURLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(LNXOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

$(BINCOVACC4):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC4) -e ENV=$(PURENV) CC=$(PURCOVCC) \
	LD=$(PURCOVLD) COPTS=$(PURCOPTS) LOPTS=$(PURLOPTS1) LIBS=$(PURLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(LNXOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)


#
#
# Linux GNU acceptance test build-------------------------------------
#
$(BINLNXACC):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC) -e ENV=$(LNXENV) CC=$(LNXCC) \
	LD=$(LNXLD) COPTS=$(LNXCOPTS) LOPTS=$(LNXLOPTS) LIBS=$(LNXLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(LNXOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

$(BINLNXACC1):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC1) -e ENV=$(LNXENV) CC=$(LNXCC) \
	LD=$(LNXLD) COPTS=$(LNXCOPTS) LOPTS=$(LNXLOPTS1) LIBS=$(LNXLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(LNXOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

$(BINLNXACC2):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC2) -e ENV=$(LNXENV) CC=$(LNXCC) \
	LD=$(LNXLD) COPTS=$(LNXCOPTS) LOPTS=$(LNXLOPTS) LIBS=$(LNXLIBS2) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(LNXOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

$(BINLNXACC3):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC3) -e ENV=$(LNXENV) CC=$(LNXCC) \
	LD=$(LNXLD) COPTS=$(LNXCOPTS) LOPTS=$(LNXLOPTS) LIBS=$(LNXLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(LNXOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

$(BINLNXACC4):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC4) -e ENV=$(LNXENV) CC=$(LNXCC) \
	LD=$(LNXLD) COPTS=$(LNXCOPTS) LOPTS=$(LNXLOPTS1) LIBS=$(LNXLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(LNXOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

#
#
# Solaris g++ acceptance test build-------------------------------------
#
$(BINGPPACC):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC) -e ENV=$(LNXENV) CC=$(GPPCC) \
	LD=$(GPPLD) COPTS=$(GPPCOPTS) LOPTS=$(LNXLOPTS) LIBS=$(LNXLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(MTOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

$(BINGPPACC1):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC1) -e ENV=$(LNXENV) CC=$(GPPCC) \
	LD=$(GPPLD) COPTS=$(GPPCOPTS) LOPTS=$(LNXLOPTS1) LIBS=$(LNXLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(MTOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

$(BINGPPACC2):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC2) -e ENV=$(LNXENV) CC=$(GPPCC) \
	LD=$(GPPLD) COPTS=$(GPPCOPTS) LOPTS=$(LNXLOPTS) LIBS=$(LNXLIBS2) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(MTOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

$(BINGPPACC3):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC3) -e ENV=$(LNXENV) CC=$(GPPCC) \
	LD=$(GPPLD) COPTS=$(GPPCOPTS) LOPTS=$(LNXLOPTS) LIBS=$(LNXLIBS2) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(MTOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

$(BINGPPACC4):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC4) -e ENV=$(LNXENV) CC=$(GPPCC) \
	LD=$(GPPLD) COPTS=$(GPPCOPTS) LOPTS=$(LNXLOPTS1) LIBS=$(LNXLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(MTOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

#
#
# Solaris c++ acceptance test build-------------------------------------
#
$(BINCPPACC):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC) -e ENV=$(LNXENV) CC=$(CPPCC) \
	LD=$(CPPLD) COPTS=$(CPPCOPTS) LOPTS=$(LNXLOPTS) LIBS=$(LNXLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(MTOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

$(BINCPPACC1):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC1) -e ENV=$(LNXENV) CC=$(CPPCC) \
	LD=$(CPPLD) COPTS=$(CPPCOPTS) LOPTS=$(LNXLOPTS1) LIBS=$(LNXLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(MTOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

$(BINCPPACC2):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC2) -e ENV=$(LNXENV) CC=$(CPPCC) \
	LD=$(CPPLD) COPTS=$(CPPCOPTS) LOPTS=$(LNXLOPTS) LIBS=$(LNXLIBS2) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(MTOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

$(BINCPPACC3):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC3) -e ENV=$(LNXENV) CC=$(CPPCC) \
	LD=$(CPPLD) COPTS=$(CPPCOPTS) LOPTS=$(LNXLOPTS) LIBS=$(LNXLIBS2) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(MTOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

$(BINCPPACC4):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC4) -e ENV=$(LNXENV) CC=$(CPPCC) \
	LD=$(CPPLD) COPTS=$(CPPCOPTS) LOPTS=$(LNXLOPTS1) LIBS=$(LNXLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(MTOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

#
# Microczft Visual C++ for WINNT/WIN95 acceptance test build------------
#
$(BINWINACC):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC) -e ENV=$(WINENV) CC=$(WINCC) \
	LD=$(WINLD) COPTS=$(WINCOPTS) LOPTS=$(WINLOPTS) LIBS=$(WINLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS=$(NSOSOPTS) OS_SRCS=$(NS_SRCS) \
	OBJ=$(WIN_OBJ_SUFFIX) OS_OBJS="$(NS_OBJS)" OS_DIR=$(NS_DIR)

$(BINWINACC1):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC1) -e ENV=$(WINENV) CC=$(WINCC) \
	LD=$(WINLD) COPTS=$(WINCOPTS) LOPTS=$(WINLOPTS) LIBS=$(WINLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS=$(NSOSOPTS) OS_SRCS=$(NS_SRCS) \
	OBJ=$(WIN_OBJ_SUFFIX) OS_OBJS="$(NS_OBJS)" OS_DIR=$(NS_DIR)

$(BINWINACC2):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC2) -e ENV=$(WINENV) CC=$(WINCC) \
	LD=$(WINLD) COPTS=$(WINCOPTS) LOPTS=$(WINLOPTS) LIBS=$(WINLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS=$(NSOSOPTS) OS_SRCS=$(NS_SRCS) \
	OBJ=$(WIN_OBJ_SUFFIX) OS_OBJS="$(NS_OBJS)" OS_DIR=$(NS_DIR)

$(BINWINACC3):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC3) -e ENV=$(WINENV) CC=$(WINCC) \
	LD=$(WINLD) COPTS=$(WINCOPTS) LOPTS=$(WINLOPTS) LIBS=$(WINLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS=$(NSOSOPTS) OS_SRCS=$(NS_SRCS) \
	OBJ=$(WIN_OBJ_SUFFIX) OS_OBJS="$(NS_OBJS)" OS_DIR=$(NS_DIR)

$(BINWINACC4):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC4) -e ENV=$(WINENV) CC=$(WINCC) \
	LD=$(WINLD) COPTS=$(WINCOPTS) LOPTS=$(WINLOPTS) LIBS=$(WINLIBS) \
	INC_PATH=$(ACC_INC_PATH3) OSOPTS=$(NSOSOPTS) OS_SRCS=$(NS_SRCS) \
	OBJ=$(WIN_OBJ_SUFFIX) OS_OBJS="$(NS_OBJS)" OS_DIR=$(NS_DIR)

#
# Vxworks cc386 acceptance test build on Pentium Target----------------
#
$(BINVWACC1):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC1) -e ENV=$(VWINTENV) CC=$(VWINTCC) \
	LD=$(VWINTLD) COPTS=$(VWINTCOPTS) LOPTS=$(VWINTLOPTS) LIBS=$(VWINTLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS=$(VWOSOPTS) OS_SRCS=$(VW_SRCS) \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS=$(VW_OBJS) OS_DIR=$(VW_DIR)

$(BINVWACC2):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC2) -e ENV=$(VWINTENV) CC=$(VWINTCC) \
	LD=$(VWINTLD) COPTS=$(VWINTCOPTS) LOPTS=$(VWINTLOPTS) LIBS=$(VWINTLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(VWOSOPTS)" OS_SRCS=$(VW_SRCS) \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS=$(VW_OBJS) OS_DIR=$(VW_DIR)

$(BINVWACC3):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC3) -e ENV=$(VWINTENV) CC=$(VWINTCC) \
	LD=$(VWINTLD) COPTS=$(VWINTCOPTS) LOPTS=$(VWINTLOPTS) LIBS=$(VWINTLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(VWOSOPTS)" OS_SRCS=$(VW_SRCS) \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS=$(VW_OBJS) OS_DIR=$(VW_DIR)

$(BINVWACC4):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC4) -e ENV=$(VWINTENV) CC=$(VWINTCC) \
	LD=$(VWINTLD) COPTS=$(VWINTCOPTS) LOPTS=$(VWINTLOPTS) LIBS=$(VWINTLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(VWOSOPTS)" OS_SRCS=$(VW_SRCS) \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS=$(VW_OBJS) OS_DIR=$(VW_DIR)

#
# MicroTec Research Compiler in Solaris Environment acceptance test build-
#
$(BINPPCACC):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC) "ENV=$(PPCENV)" CC=$(PPCCC) \
	LD=$(PPCLD) "COPTS=$(PPCCOPTS)" "LOPTS=$(PPCLOPTS)" LIBS=$(PPCLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(VWOSOPTS)" "OS_SRCS=$(VW_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) "OS_OBJS=$(VW_OBJS)" OS_DIR=$(VW_DIR)

$(BINPPCACC1):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC1) "ENV=$(PPCENV)" CC=$(PPCCC) \
	LD=$(PPCLD) "COPTS=$(PPCCOPTS)" "LOPTS=$(PPCLOPTS)" LIBS=$(PPCLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(VWOSOPTS)" OS_SRCS="$(VW_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(VW_OBJS)" OS_DIR=$(VW_DIR)

$(BINPPCACC2):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC2) "ENV=$(PPCENV)" CC=$(PPCCC) \
	LD=$(PPCLD) "COPTS=$(PPCCOPTS)" "LOPTS=$(PPCLOPTS)" LIBS=$(PPCLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(VWOSOPTS)" OS_SRCS="$(VW_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(VW_OBJS)" OS_DIR=$(VW_DIR)

$(BINPPCACC3):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC3) "ENV=$(PPCENV)" CC=$(PPCCC) \
	LD=$(PPCLD) "COPTS=$(PPCCOPTS)" "LOPTS=$(PPCLOPTS)" LIBS=$(PPCLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(VWOSOPTS)" OS_SRCS="$(VW_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(VW_OBJS)" OS_DIR=$(VW_DIR)

$(BINPPCACC4):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC4) "ENV=$(PPCENV)" CC=$(PPCCC) \
	LD=$(PPCLD) "COPTS=$(PPCCOPTS)" "LOPTS=$(PPCLOPTS)" LIBS=$(PPCLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(VWOSOPTS)" OS_SRCS="$(VW_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(VW_OBJS)" 

#
# Inisite Memory Check Tool in Solaris acceptance test build-------------
#
$(BININSITEACC):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC) -e ENV=$(INSENV) CC=$(INSCC) \
	LD=$(INSLD) COPTS=$(INSCOPTS) LOPTS=$(INSLOPTS) LIBS=$(INSLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(MTOSOPTS)" OS_SRCS=$(MT_SRCS) \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS=$(MT_OBJS) OS_DIR=$(MT_DIR)

$(BININSITEACC1):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC1) -e ENV=$(INSENV) CC=$(INSCC) \
	LD=$(INSLD) COPTS=$(INSCOPTS) LOPTS=$(INSLOPTS1) LIBS=$(INSLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(MTOSOPTS)" OS_SRCS=$(MT_SRCS) \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS=$(MT_OBJS) OS_DIR=$(MT_DIR)

$(BININSITEACC2):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC2) -e ENV=$(INSENV) CC=$(INSCC) \
	LD=$(INSLD) COPTS=$(INSCOPTS) LOPTS=$(INSLOPTS) LIBS=$(INSLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(MTOSOPTS)" OS_SRCS=$(MT_SRCS) \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS=$(MT_OBJS) OS_DIR=$(MT_DIR)

$(BININSITEACC3):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC3) -e ENV=$(INSENV) CC=$(INSCC) \
	LD=$(INSLD) COPTS=$(INSCOPTS) LOPTS=$(INSLOPTS) LIBS=$(INSLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(MTOSOPTS)" OS_SRCS=$(MT_SRCS) \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS=$(MT_OBJS) OS_DIR=$(MT_DIR)

$(BININSITEACC4):
	@$(MAKE) -f $(MAKENAME) $(MAKEACC4) -e ENV=$(INSENV) CC=$(INSCC) \
	LD=$(INSLD) COPTS=$(INSCOPTS) LOPTS=$(INSLOPTS1) LIBS=$(INSLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(MTOSOPTS)" OS_SRCS=$(MT_SRCS) \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS=$(MT_OBJS) OS_DIR=$(MT_DIR)


# Library--------------------------------------------------------------
#
# cc Library build for Solaris----------------------------------------
$(BINSOLLIB):
	@$(MAKE) -f $(MAKENAME) $(MAKELIB) -e ENV=$(SOLENV) CC=$(SOLCC)  \
	LD=$(SOLLIBLD) COPTS=$(SOLCOPTS) LOPTS=$(SOLLIBLOPTS) LIBS=$(SOLLLIBS) \
	OBJ=$(UNIX_OBJ_SUFFIX) INC_PATH=$(LIB_INC_PATH) OSOPTS=$(SOLLIBOSOPTS)

$(BINSOLLIB1):
	@$(MAKE) -f $(MAKENAME) $(MAKELIB1) -e ENV=$(SOLENV) CC=$(SOLCC)  \
	LD=$(SOLLIBLD) COPTS=$(SOLCOPTS) LOPTS=$(SOLLIBLOPTS) LIBS=$(SOLLLIBS) \
	OBJ=$(UNIX_OBJ_SUFFIX) INC_PATH=$(LIB_INC_PATH1) OSOPTS=$(SOLLIBOSOPTS)

$(BINSOLLIB2):
	@$(MAKE) -f $(MAKENAME) $(MAKELIB2) -e ENV=$(SOLENV) CC=$(SOLCC)  \
	LD=$(SOLLIBLD) COPTS=$(SOLCOPTS) LOPTS=$(SOLLIBLOPTS) LIBS=$(SOLLLIBS) \
	OBJ=$(UNIX_OBJ_SUFFIX) INC_PATH=$(LIB_INC_PATH2) OSOPTS=$(SOLLIBOSOPTS)

$(BINSOLLIB3):
	@$(MAKE) -f $(MAKENAME) $(MAKELIB3) -e ENV=$(SOLENV) CC=$(SOLCC)  \
	LD=$(SOLLIBLD) COPTS=$(SOLCOPTS) LOPTS=$(SOLLIBLOPTS) LIBS=$(SOLLLIBS) \
	OBJ=$(UNIX_OBJ_SUFFIX) INC_PATH=$(LIB_INC_PATH2) OSOPTS=$(SOLLIBOSOPTS)

$(BINSOLLIB4):
	@$(MAKE) -f $(MAKENAME) $(MAKELIB4) -e ENV=$(SOLENV) CC=$(SOLCC)  \
	LD=$(SOLLIBLD) COPTS=$(SOLCOPTS) LOPTS=$(SOLLIBLOPTS) LIBS=$(SOLLLIBS) \
	OBJ=$(UNIX_OBJ_SUFFIX) INC_PATH=$(LIB_INC_PATH3) OSOPTS=$(SOLLIBOSOPTS)

# gcc Library build for Solaris----------------------------------------
$(BINGNULIB):
	@$(MAKE) -f $(MAKENAME) $(MAKELIB) -e ENV=$(GNUENV) CC=$(GNUCC) \
	LD=$(GNULIBLD) COPTS=$(GNUCOPTS) LOPTS=$(GNULIBLOPTS) LIBS=$(GNULLIBS) \
	OBJ=$(UNIX_OBJ_SUFFIX) INC_PATH=$(LIB_INC_PATH) OSOPTS=$(SOLLIBOSOPTS)

$(BINGNULIB1):
	@$(MAKE) -f $(MAKENAME) $(MAKELIB1) -e ENV=$(GNUENV) CC=$(GNUCC) \
	LD=$(GNULIBLD) COPTS=$(GNUCOPTS) LOPTS=$(GNULIBLOPTS) LIBS=$(GNULLIBS) \
	OBJ=$(UNIX_OBJ_SUFFIX) INC_PATH=$(LIB_INC_PATH1) OSOPTS=$(SOLLIBOSOPTS)

$(BINGNULIB2):
	@$(MAKE) -f $(MAKENAME) $(MAKELIB2) -e ENV=$(GNUENV) CC=$(GNUCC) \
	LD=$(GNULIBLD) COPTS=$(GNUCOPTS) LOPTS=$(GNULIBLOPTS) LIBS=$(GNULLIBS) \
	OBJ=$(UNIX_OBJ_SUFFIX) INC_PATH=$(LIB_INC_PATH2) OSOPTS=$(SOLLIBOSOPTS)

$(BINGNULIB3):
	@$(MAKE) -f $(MAKENAME) $(MAKELIB3) -e ENV=$(GNUENV) CC=$(GNUCC) \
	LD=$(GNULIBLD) COPTS=$(GNUCOPTS) LOPTS=$(GNULIBLOPTS) LIBS=$(GNULLIBS) \
	OBJ=$(UNIX_OBJ_SUFFIX) INC_PATH=$(LIB_INC_PATH2) OSOPTS=$(SOLLIBOSOPTS)

$(BINGNULIB4):
	@$(MAKE) -f $(MAKENAME) $(MAKELIB4) -e ENV=$(GNUENV) CC=$(GNUCC) \
	LD=$(GNULIBLD) COPTS=$(GNUCOPTS) LOPTS=$(GNULIBLOPTS) LIBS=$(GNULLIBS) \
	OBJ=$(UNIX_OBJ_SUFFIX) INC_PATH=$(LIB_INC_PATH3) OSOPTS=$(SOLLIBOSOPTS)


# gcc Library build for Linux----------------------------------------
$(BINLNXLIB):
	@$(MAKE) -f $(MAKENAME) $(MAKELIB) -e ENV=$(LNXENV) CC=$(LNXCC) \
	LD=$(LNXLIBLD) COPTS=$(LNXCOPTS) LOPTS=$(LNXLIBLOPTS) LIBS=$(LNXLLIBS) \
	OBJ=$(UNIX_OBJ_SUFFIX) INC_PATH=$(LIB_INC_PATH) OSOPTS=$(LNXLIBOSOPTS)

$(BINLNXLIB1):
	@$(MAKE) -f $(MAKENAME) $(MAKELIB1) -e ENV=$(LNXENV) CC=$(LNXCC) \
	LD=$(LNXLIBLD) COPTS=$(LNXCOPTS) LOPTS=$(LNXLIBLOPTS) LIBS=$(LNXLLIBS) \
	OBJ=$(UNIX_OBJ_SUFFIX) INC_PATH=$(LIB_INC_PATH1) OSOPTS=$(LNXLIBOSOPTS)

$(BINLNXLIB2):
	@$(MAKE) -f $(MAKENAME) $(MAKELIB2) -e ENV=$(LNXENV) CC=$(LNXCC) \
	LD=$(LNXLIBLD) COPTS=$(LNXCOPTS) LOPTS=$(LNXLIBLOPTS) LIBS=$(LNXLLIBS) \
	OBJ=$(UNIX_OBJ_SUFFIX) INC_PATH=$(LIB_INC_PATH2) OSOPTS=$(LNXLIBOSOPTS)

$(BINLNXLIB3):
	@$(MAKE) -f $(MAKENAME) $(MAKELIB3) -e ENV=$(LNXENV) CC=$(LNXCC) \
	LD=$(LNXLIBLD) COPTS=$(LNXCOPTS) LOPTS=$(LNXLIBLOPTS) LIBS=$(LNXLLIBS) \
	OBJ=$(UNIX_OBJ_SUFFIX) INC_PATH=$(LIB_INC_PATH2) OSOPTS=$(LNXLIBOSOPTS)

$(BINLNXLIB4):
	@$(MAKE) -f $(MAKENAME) $(MAKELIB4) -e ENV=$(LNXENV) CC=$(LNXCC) \
	LD=$(LNXLIBLD) COPTS=$(LNXCOPTS) LOPTS=$(LNXLIBLOPTS) LIBS=$(LNXLLIBS) \
	OBJ=$(UNIX_OBJ_SUFFIX) INC_PATH=$(LIB_INC_PATH3) OSOPTS=$(LNXLIBOSOPTS)

# g++ Library build for Linux----------------------------------------
$(BINGPPLIB):
	@$(MAKE) -f $(MAKENAME) $(MAKELIB) -e ENV=$(LNXENV) CC=$(GPPCC) \
	LD=$(GPPLIBLD) COPTS=$(GPPCOPTS) LOPTS=$(LNXLIBLOPTS) LIBS=$(LNXLLIBS) \
	OBJ=$(UNIX_OBJ_SUFFIX) INC_PATH=$(LIB_INC_PATH) OSOPTS=$(LNXLIBOSOPTS)

$(BINGPPLIB1):
	@$(MAKE) -f $(MAKENAME) $(MAKELIB1) -e ENV=$(LNXENV) CC=$(GPPCC) \
	LD=$(GPPLIBLD) COPTS=$(GPPCOPTS) LOPTS=$(LNXLIBLOPTS) LIBS=$(LNXLLIBS) \
	OBJ=$(UNIX_OBJ_SUFFIX) INC_PATH=$(LIB_INC_PATH1) OSOPTS=$(LNXLIBOSOPTS)

$(BINGPPLIB2):
	@$(MAKE) -f $(MAKENAME) $(MAKELIB2) -e ENV=$(LNXENV) CC=$(GPPCC) \
	LD=$(GPPLIBLD) COPTS=$(GPPCOPTS) LOPTS=$(LNXLIBLOPTS) LIBS=$(LNXLLIBS) \
	OBJ=$(UNIX_OBJ_SUFFIX) INC_PATH=$(LIB_INC_PATH2) OSOPTS=$(LNXLIBOSOPTS)

$(BINGPPLIB3):
	@$(MAKE) -f $(MAKENAME) $(MAKELIB3) -e ENV=$(LNXENV) CC=$(GPPCC) \
	LD=$(GPPLIBLD) COPTS=$(GPPCOPTS) LOPTS=$(LNXLIBLOPTS) LIBS=$(LNXLLIBS) \
	OBJ=$(UNIX_OBJ_SUFFIX) INC_PATH=$(LIB_INC_PATH2) OSOPTS=$(LNXLIBOSOPTS)

$(BINGPPLIB4):
	@$(MAKE) -f $(MAKENAME) $(MAKELIB4) -e ENV=$(LNXENV) CC=$(GPPCC) \
	LD=$(GPPLIBLD) COPTS=$(GPPCOPTS) LOPTS=$(LNXLIBLOPTS) LIBS=$(LNXLLIBS) \
	OBJ=$(UNIX_OBJ_SUFFIX) INC_PATH=$(LIB_INC_PATH3) OSOPTS=$(LNXLIBOSOPTS)

# c++ Library build for Linux----------------------------------------
$(BINCPPLIB):
	@$(MAKE) -f $(MAKENAME) $(MAKELIB) -e ENV=$(LNXENV) CC=$(CPPCC) \
	LD=$(CPPLIBLD) COPTS=$(CPPCOPTS) LOPTS=$(LNXLIBLOPTS) \
	OBJ=$(UNIX_OBJ_SUFFIX) INC_PATH=$(LIB_INC_PATH) OSOPTS=$(LNXLIBOSOPTS)

$(BINCPPLIB1):
	@$(MAKE) -f $(MAKENAME) $(MAKELIB1) -e ENV=$(LNXENV) CC=$(CPPCC) \
	LD=$(CPPLIBLD) COPTS=$(CPPCOPTS) LOPTS=$(LNXLIBLOPTS) \
	OBJ=$(UNIX_OBJ_SUFFIX) INC_PATH=$(LIB_INC_PATH1) OSOPTS=$(LNXLIBOSOPTS)

$(BINCPPLIB2):
	@$(MAKE) -f $(MAKENAME) $(MAKELIB2) -e ENV=$(LNXENV) CC=$(CPPCC) \
	LD=$(CPPLIBLD) COPTS=$(CPPCOPTS) LOPTS=$(LNXLIBLOPTS) \
	OBJ=$(UNIX_OBJ_SUFFIX) INC_PATH=$(LIB_INC_PATH2) OSOPTS=$(LNXLIBOSOPTS)

$(BINCPPLIB3):
	@$(MAKE) -f $(MAKENAME) $(MAKELIB3) -e ENV=$(LNXENV) CC=$(CPPCC) \
	LD=$(CPPLIBLD) COPTS=$(CPPCOPTS) LOPTS=$(LNXLIBLOPTS) \
	OBJ=$(UNIX_OBJ_SUFFIX) INC_PATH=$(LIB_INC_PATH2) OSOPTS=$(LNXLIBOSOPTS)

$(BINCPPLIB4):
	@$(MAKE) -f $(MAKENAME) $(MAKELIB4) -e ENV=$(LNXENV) CC=$(CPPCC) \
	LD=$(CPPLIBLD) COPTS=$(CPPCOPTS) LOPTS=$(LNXLIBLOPTS) \
	OBJ=$(UNIX_OBJ_SUFFIX) INC_PATH=$(LIB_INC_PATH3) OSOPTS=$(LNXLIBOSOPTS)


# Performance compilation--------------------------------------------------
$(BINLNXPERF):
	@$(MAKE) -f $(MAKENAME) $(MAKEPERF) -e ENV=$(PERFENV) CC=$(PERFCC) \
	LD=$(PERFLD) COPTS=$(PERFCOPTS) LOPTS=$(PERFLOPTS1) LIBS=$(PERFLIBS) \
	INC_PATH=$(ACC_INC_PATH) OSOPTS="$(PERFOSOPTS)" OS_SRCS="$(MT_SRCS)" \
	OBJ=$(UNIX_OBJ_SUFFIX) OS_OBJS="$(MT_OBJS)" OS_DIR=$(MT_DIR)

# Library compilation--------------------------------------------------
$(MAKELIB):
	@$(MAKE) -f $(MAKENAME) $(LIBBIN) CPRDOPTS=$(CPRDLIBOPTS) \
	CSMOPTS=$(CSMLIBOPTS)

$(MAKELIB1):
	@$(MAKE) -f $(MAKENAME) $(LIBBIN1) CPRDOPTS=$(CPRDLIBOPTS1) \
	CSMOPTS=$(CSMLIBOPTS1)

$(MAKELIB2):
	@$(MAKE) -f $(MAKENAME) $(LIBBIN2) CPRDOPTS=$(CPRDLIBOPTS2) \
	CSMOPTS=$(CSMLIBOPTS2)

$(MAKELIB3):
	@$(MAKE) -f $(MAKENAME) $(LIBBIN3) CPRDOPTS=$(CPRDLIBOPTS3) \
	CSMOPTS=$(CSMLIBOPTS3)

$(MAKELIB4):
	@$(MAKE) -f $(MAKENAME) $(LIBBIN4) CPRDOPTS=$(CPRDLIBOPTS4) \
	CSMOPTS=$(CSMLIBOPTS4)

$(LIBBIN): $(PRDLIB_OBJS)
	$(LD) $(LOPTS) $(PRDLIB_OBJS) $(LIBS)

$(LIBBIN1): $(PRDLIB_OBJS1)
	$(LD) $(LOPTS) $(PRDLIB_OBJS1) $(LIBS)

$(LIBBIN2): $(PRDLIB_OBJS2)
	$(LD) $(LOPTS) $(PRDLIB_OBJS2) $(LIBS)

$(LIBBIN3): $(PRDLIB_OBJS3)
	$(LD) $(LOPTS) $(PRDLIB_OBJS3) $(LIBS)

$(LIBBIN4): $(PRDLIB_OBJS4)
	$(LD) $(LOPTS) $(PRDLIB_OBJS4) $(LIBS)

#
# The following assumes that the compile and linker options are
# set in the make-file before the definition of this target
#

$(MAKEPT):
	@$(MAKE) -f $(MAKENAME) $(PTBIN) CPRDOPTS=$(CPRDPTOPTS) \
	CSMOPTS=$(CSMPTOPTS)

$(MAKEPT1):
	@$(MAKE) -f $(MAKENAME) $(PTBIN) CPRDOPTS=$(CPRDPTOPTS1) \
	CSMOPTS=$(CSMPTOPTS1)

$(MAKEPT2):
	@$(MAKE) -f $(MAKENAME) $(PTBIN) CPRDOPTS=$(CPRDPTOPTS2) \
	CSMOPTS=$(CSMPTOPTS2)

$(MAKEPT3):
	@$(MAKE) -f $(MAKENAME) $(PTBIN) CPRDOPTS=$(CPRDPTOPTS3) \
	CSMOPTS=$(CSMPTOPTS3)

$(MAKEPT4):
	@$(MAKE) -f $(MAKENAME) $(PTBIN) CPRDOPTS=$(CPRDPTOPTS4) \
	CSMOPTS=$(CSMPTOPTS4)

$(PTBIN): $(PRDPT_OBJS)
	$(LD) $(LOPTS) $(PRDPT_OBJS) $(LIBS)


# acceptance test-------------------------------------------------------
#
# The following assumes that the compile and linker options are
# set in the make-file before the definition of this target
# 
$(MAKEACC):
	@$(MAKE) -f $(MAKENAME) $(OUTNAME) CPRDOPTS=$(CPRDACCOPTS) \
	CSMOPTS=$(CSMACCOPTS)

$(MAKEACC1):
	@$(MAKE) -f $(MAKENAME) $(OUTNAME) CPRDOPTS=$(CPRDACCOPTS1) \
	CSMOPTS=$(CSMACCOPTS1)

$(MAKEACC2):
	@$(MAKE) -f $(MAKENAME) $(OUTNAME) CPRDOPTS=$(CPRDACCOPTS2) \
	CSMOPTS=$(CSMACCOPTS2)

$(MAKEACC3):
	@$(MAKE) -f $(MAKENAME) $(OUTNAME) CPRDOPTS=$(CPRDACCOPTS3) \
	CSMOPTS=$(CSMACCOPTS3)

$(MAKEACC4):
	@$(MAKE) -f $(MAKENAME) $(OUTNAME) CPRDOPTS=$(CPRDACCOPTS4) \
	CSMOPTS=$(CSMACCOPTS4)
#Performance makeacc
$(MAKEPERF):
	@$(MAKE) -f $(MAKENAME) $(OUTNAME) CPRDOPTS=$(CPRDPERFOPTS1) \
	CSMOPTS=$(CSMACCOPTS)

$(ACCBIN): $(F_OBJS) $(OS_OBJS)
	$(LD) $(LOPTS) $(F_OBJS) $(OS_OBJS) $(LIBS)

$(TCBIN): $(CZTC_OBJS)
	$(LD) $(LOPTS) $(CZTC_OBJS) $(LIBS)

$(PERFBIN): $(F_OBJS) $(OS_OBJS)
	$(LD) $(LOPTS) $(F_OBJS) $(OS_OBJS) $(LIBS)

#
# Make Depend
# depend portable test--------------------------------------------------
# dependency for portable source 
depend_pt: $(PRDPT_SRCS)
	@$(MAKE) -f $(MAKENAME) $(DEPEND) -e \
	DEPOPTS=$(DEPOPTS_PT) INC_PATH=$(PT_INC_PATH) \
	OSOPTS=$(PTOSOPTS) DEP_SRCS="$(PRDPT_SRCS)" 

# depend acceptance test------------------------------------------------
# dependency for acceptance test 
depend_acc: $(PRDACC_SRCS)
	$(MAKE) -f $(MAKENAME) $(DEPEND) -e \
	DEPOPTS=$(DEPOPTS_ACC) INC_PATH=$(ACC_INC_PATH) \
	OSOPTS=$(MTOSOPTS) OS_SRCS=$(SSMT_SRCS) OS_OBJS=$(SSMT_OBJS) \
	OS_DIR=$(MT_DIR) DEP_SRCS="$(PRDACC_SRCS)"

# Build the dependency
$(DEPEND):
	$(MAKEDEPEND) -f $(MAKENAME) $(COSOPTS) $(DEPOPTS) $(INC_PATH) $(DEP_SRCS)

#=======================================================================
#
# Source code build directives
# SECTION 10
# Modify this section to list out the build directives for the specific 
# product

# Portable build ------------------------------------------------
$(SY_DIR)/ss_ptsp.$(OBJ): $(CM_DIR)/ss_ptsp.c
	$(CC) -c $(CPTOPTS) $(CZOPTS) $(CM_DIR)/ss_ptsp.c -o $(SY_DIR)/ss_ptsp.$(OBJ)

$(SY_DIR)/cz_tst.$(OBJ): $(CZ_DIR)/cz_tst.c
	$(CC) -c $(CPTOPTS) $(CZ_DIR)/cz_tst.c -o $(SY_DIR)/cz_tst.$(OBJ)

$(SY_DIR)/cz_ex_pt.$(OBJ): $(CZ_DIR)/cz_ex_pt.c
	$(CC) -c $(CPTOPTS) $(CZ_DIR)/cz_ex_pt.c -o $(SY_DIR)/cz_ex_pt.$(OBJ)


# acceptance test-------------------------------------------------------
$(SY_DIR)/czac_db.$(OBJ): $(CZACC_DIR)/czac_db.c $(SYS_INC) $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/czac_db.c -o $(SY_DIR)/czac_db.$(OBJ)

$(SY_DIR)/czac_asn_pk.$(OBJ): $(CZACC_DIR)/czac_asn_pk.c $(SYS_INC) $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/czac_asn_pk.c -o $(SY_DIR)/czac_asn_pk.$(OBJ)

$(SY_DIR)/czac_asn_unpk.$(OBJ): $(CZACC_DIR)/czac_asn_unpk.c $(SYS_INC) $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/czac_asn_unpk.c -o $(SY_DIR)/czac_asn_unpk.$(OBJ)

$(SY_DIR)/czac_czthdl.$(OBJ): $(CZACC_DIR)/czac_czthdl.c $(SYS_INC) $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/czac_czthdl.c -o $(SY_DIR)/czac_czthdl.$(OBJ)

$(SY_DIR)/czac_cztreg.$(OBJ): $(CZACC_DIR)/czac_cztreg.c $(SYS_INC) $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/czac_cztreg.c -o $(SY_DIR)/czac_cztreg.$(OBJ)

$(SY_DIR)/czac_cztcb.$(OBJ): $(CZACC_DIR)/czac_cztcb.c $(SYS_INC) $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/czac_cztcb.c -o $(SY_DIR)/czac_cztcb.$(OBJ)

$(SY_DIR)/czac_cztutl_r9.$(OBJ): $(CZACC_DIR)/czac_cztutl_r9.c $(SYS_INC) $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/czac_cztutl_r9.c -o $(SY_DIR)/czac_cztutl_r9.$(OBJ)

$(SY_DIR)/czac_cztutl_r11.$(OBJ): $(CZACC_DIR)/czac_cztutl_r11.c $(SYS_INC) $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/czac_cztutl_r11.c -o $(SY_DIR)/czac_cztutl_r11.$(OBJ)

$(SY_DIR)/czac_scthdl.$(OBJ): $(CZACC_DIR)/czac_scthdl.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/czac_scthdl.c -o $(SY_DIR)/czac_scthdl.$(OBJ)

$(SY_DIR)/czac_sctreg.$(OBJ): $(CZACC_DIR)/czac_sctreg.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/czac_sctreg.c -o $(SY_DIR)/czac_sctreg.$(OBJ)

$(SY_DIR)/czac_sctcb.$(OBJ): $(CZACC_DIR)/czac_sctcb.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/czac_sctcb.c -o $(SY_DIR)/czac_sctcb.$(OBJ)

$(SY_DIR)/czac_sb_ex_ms.$(OBJ): $(CZACC_DIR)/czac_sb_ex_ms.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/czac_sb_ex_ms.c -o $(SY_DIR)/czac_sb_ex_ms.$(OBJ)

$(SY_DIR)/rs_ex_ms.$(OBJ): $(CZACC_DIR)/rs_ex_ms.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/rs_ex_ms.c -o $(SY_DIR)/rs_ex_ms.$(OBJ)

$(SY_DIR)/rs_ptli.$(OBJ): $(CZACC_DIR)/rs_ptli.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/rs_ptli.c -o $(SY_DIR)/rs_ptli.$(OBJ)

$(SY_DIR)/czac_sctutl_r9.$(OBJ): $(CZACC_DIR)/czac_sctutl_r9.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/czac_sctutl_r9.c -o $(SY_DIR)/czac_sctutl_r9.$(OBJ)

$(SY_DIR)/czac_sctutl_r11.$(OBJ): $(CZACC_DIR)/czac_sctutl_r11.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/czac_sctutl_r11.c -o $(SY_DIR)/czac_sctutl_r11.$(OBJ)

$(SY_DIR)/czac_lsbhdl.$(OBJ): $(CZACC_DIR)/czac_lsbhdl.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CSBOPTS) $(CZACC_DIR)/czac_lsbhdl.c -o $(SY_DIR)/czac_lsbhdl.$(OBJ)

$(SY_DIR)/czac_lsbreg.$(OBJ): $(CZACC_DIR)/czac_lsbreg.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CSBOPTS) $(CZACC_DIR)/czac_lsbreg.c -o $(SY_DIR)/czac_lsbreg.$(OBJ)

$(SY_DIR)/czac_lsbcb.$(OBJ): $(CZACC_DIR)/czac_lsbcb.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CSBOPTS) $(CZACC_DIR)/czac_lsbcb.c -o $(SY_DIR)/czac_lsbcb.$(OBJ)

$(SY_DIR)/czac_lsbutl.$(OBJ): $(CZACC_DIR)/czac_lsbutl.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CSBOPTS) $(CZACC_DIR)/czac_lsbutl.c -o $(SY_DIR)/czac_lsbutl.$(OBJ)

$(SY_DIR)/czac_lhihdl.$(OBJ): $(CZACC_DIR)/czac_lhihdl.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CHIOPTS) $(CZACC_DIR)/czac_lhihdl.c -o $(SY_DIR)/czac_lhihdl.$(OBJ)

$(SY_DIR)/czac_lhireg.$(OBJ): $(CZACC_DIR)/czac_lhireg.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CHIOPTS) $(CZACC_DIR)/czac_lhireg.c -o $(SY_DIR)/czac_lhireg.$(OBJ)

$(SY_DIR)/czac_lhicb.$(OBJ): $(CZACC_DIR)/czac_lhicb.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CHIOPTS) $(CZACC_DIR)/czac_lhicb.c -o $(SY_DIR)/czac_lhicb.$(OBJ)

$(SY_DIR)/czac_lhiutl.$(OBJ): $(CZACC_DIR)/czac_lhiutl.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CHIOPTS) $(CZACC_DIR)/czac_lhiutl.c -o $(SY_DIR)/czac_lhiutl.$(OBJ)

$(SY_DIR)/czac_lczhdl.$(OBJ): $(CZACC_DIR)/czac_lczhdl.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/czac_lczhdl.c -o $(SY_DIR)/czac_lczhdl.$(OBJ)

$(SY_DIR)/czac_lczreg.$(OBJ): $(CZACC_DIR)/czac_lczreg.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/czac_lczreg.c -o $(SY_DIR)/czac_lczreg.$(OBJ)

$(SY_DIR)/czac_lczcb.$(OBJ): $(CZACC_DIR)/czac_lczcb.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/czac_lczcb.c -o $(SY_DIR)/czac_lczcb.$(OBJ)

$(SY_DIR)/czac_lczutl.$(OBJ): $(CZACC_DIR)/czac_lczutl.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/czac_lczutl.c -o $(SY_DIR)/czac_lczutl.$(OBJ)

$(SY_DIR)/czac_tst.$(OBJ): $(CZACC_DIR)/czac_tst.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/czac_tst.c -o $(SY_DIR)/czac_tst.$(OBJ)

$(SY_DIR)/czac_prof.$(OBJ): $(CZACC_DIR)/czac_prof.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/czac_prof.c -o $(SY_DIR)/czac_prof.$(OBJ)

$(SY_DIR)/czac_flag.$(OBJ): $(CZACC_DIR)/czac_flag.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/czac_flag.c -o $(SY_DIR)/czac_flag.$(OBJ)

$(SY_DIR)/czac_czld.$(OBJ): $(CZACC_DIR)/czac_czld.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/czac_czld.c -o $(SY_DIR)/czac_czld.$(OBJ)

$(SY_DIR)/czac_sctptui.$(OBJ): $(CZACC_DIR)/czac_sctptui.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/czac_sctptui.c -o $(SY_DIR)/czac_sctptui.$(OBJ)

# ---------------------------  CM_XTA files

$(SY_DIR)/cm_xta_ex_ms.$(OBJ): $(CZACC_DIR)/cm_xta_ex_ms.c
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/cm_xta_ex_ms.c -o $(SY_DIR)/cm_xta_ex_ms.$(OBJ)

$(SY_DIR)/cm_xta_xml.$(OBJ): $(CZACC_DIR)/cm_xta_xml.c
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/cm_xta_xml.c -o $(SY_DIR)/cm_xta_xml.$(OBJ)

$(SY_DIR)/cm_xta_ldfsm.$(OBJ): $(CZACC_DIR)/cm_xta_ldfsm.c
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/cm_xta_ldfsm.c -o $(SY_DIR)/cm_xta_ldfsm.$(OBJ)

$(SY_DIR)/cm_xta_tcfsm.$(OBJ): $(CZACC_DIR)/cm_xta_tcfsm.c
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/cm_xta_tcfsm.c -o $(SY_DIR)/cm_xta_tcfsm.$(OBJ)

$(SY_DIR)/cm_xta_tgfsm.$(OBJ): $(CZACC_DIR)/cm_xta_tgfsm.c
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/cm_xta_tgfsm.c -o $(SY_DIR)/cm_xta_tgfsm.$(OBJ)

$(SY_DIR)/cm_xta_tafsm.$(OBJ): $(CZACC_DIR)/cm_xta_tafsm.c
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/cm_xta_tafsm.c -o $(SY_DIR)/cm_xta_tafsm.$(OBJ)

$(SY_DIR)/cm_xta_py.$(OBJ): $(CZACC_DIR)/cm_xta_py.c
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/cm_xta_py.c -o $(SY_DIR)/cm_xta_py.$(OBJ)

$(SY_DIR)/cm_xta_inthdl.$(OBJ): $(CZACC_DIR)/cm_xta_inthdl.c
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/cm_xta_inthdl.c -o $(SY_DIR)/cm_xta_inthdl.$(OBJ)

$(SY_DIR)/cm_xta_intreg.$(OBJ): $(CZACC_DIR)/cm_xta_intreg.c
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/cm_xta_intreg.c -o $(SY_DIR)/cm_xta_intreg.$(OBJ)

$(SY_DIR)/cm_xta_res.$(OBJ): $(CZACC_DIR)/cm_xta_res.c
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/cm_xta_res.c -o $(SY_DIR)/cm_xta_res.$(OBJ)

$(SY_DIR)/cm_xta_queue.$(OBJ): $(CZACC_DIR)/cm_xta_queue.c
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/cm_xta_queue.c -o $(SY_DIR)/cm_xta_queue.$(OBJ)

$(SY_DIR)/cm_xta_flag.$(OBJ): $(CZACC_DIR)/cm_xta_flag.c
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/cm_xta_flag.c -o $(SY_DIR)/cm_xta_flag.$(OBJ)

$(SY_DIR)/cm_xta_log.$(OBJ): $(CZACC_DIR)/cm_xta_log.c
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/cm_xta_log.c -o $(SY_DIR)/cm_xta_log.$(OBJ)

$(SY_DIR)/cm_xta_slave.$(OBJ): $(CZACC_DIR)/cm_xta_slave.c
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/cm_xta_slave.c -o $(SY_DIR)/cm_xta_slave.$(OBJ)

$(SY_DIR)/cm_xta_master.$(OBJ): $(CZACC_DIR)/cm_xta_master.c
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/cm_xta_master.c -o $(SY_DIR)/cm_xta_master.$(OBJ)

$(SY_DIR)/cm_xta_reg.$(OBJ): $(CZACC_DIR)/cm_xta_reg.c
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/cm_xta_reg.c -o $(SY_DIR)/cm_xta_reg.$(OBJ)

$(SY_DIR)/cm_xta_tst.$(OBJ): $(CZACC_DIR)/cm_xta_tst.c
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/cm_xta_tst.c -o $(SY_DIR)/cm_xta_tst.$(OBJ)

$(SY_DIR)/cm_xta_ipc.$(OBJ): $(CZACC_DIR)/cm_xta_ipc.c
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/cm_xta_ipc.c -o $(SY_DIR)/cm_xta_ipc.$(OBJ)

$(SY_DIR)/cm_xta_txn.$(OBJ): $(CZACC_DIR)/cm_xta_txn.c
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/cm_xta_txn.c -o $(SY_DIR)/cm_xta_txn.$(OBJ)

$(SY_DIR)/cm_xta_intutl.$(OBJ): $(CZACC_DIR)/cm_xta_intutl.c
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/cm_xta_intutl.c -o $(SY_DIR)/cm_xta_intutl.$(OBJ)

$(SY_DIR)/cm_xta_tmr.$(OBJ): $(CZACC_DIR)/cm_xta_tmr.c
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/cm_xta_tmr.c -o $(SY_DIR)/cm_xta_tmr.$(OBJ)

$(SY_DIR)/czac_slave.$(OBJ): $(CZACC_DIR)/czac_slave.c $(SYS_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/czac_slave.c -o $(SY_DIR)/czac_slave.$(OBJ)

# X2AP user files build----------------------------------------------

$(SY_DIR)/czuiptli.$(OBJ): $(CZACC_DIR)/czuiptli.c $(SYS_INC) $(CM_INC) $(CZALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/czuiptli.c -o $(SY_DIR)/czuiptli.$(OBJ)

$(SY_DIR)/czulayer.$(OBJ): $(CZACC_DIR)/czulayer.c $(SYS_INC) $(CM_INC) $(CZALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/czulayer.c -o $(SY_DIR)/czulayer.$(OBJ)

$(SY_DIR)/czuiexms.$(OBJ): $(CZACC_DIR)/czuiexms.c $(SYS_INC) $(CM_INC) $(CZALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/czuiexms.c -o $(SY_DIR)/czuiexms.$(OBJ)


# X2AP lower interface build----------------------------------------------

$(SY_DIR)/czliexms.$(OBJ): $(CZACC_DIR)/czliexms.c $(SYS_INC) $(CM_INC) $(CZALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/czliexms.c -o $(SY_DIR)/czliexms.$(OBJ)

$(SY_DIR)/czliptui.$(OBJ): $(CZACC_DIR)/czliptui.c $(SYS_INC) $(CM_INC) $(CZALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/czliptui.c -o $(SY_DIR)/czliptui.$(OBJ)

$(SY_DIR)/czllayer.$(OBJ): $(CZACC_DIR)/czllayer.c $(SYS_INC) $(CM_INC) $(CZALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/czllayer.c -o $(SY_DIR)/czllayer.$(OBJ)

# product Id  file---------------------------------------------------

$(SY_DIR)/cz_id.$(OBJ): $(CZ_DIR)/cz_id.c $(SYS_INC) $(CM_INC) $(CZALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZ_DIR)/cz_id.c -o $(SY_DIR)/cz_id.$(OBJ)


# X2AP product files
$(SY_DIR)/cz_uim.$(OBJ): $(CZ_DIR)/cz_uim.c $(SYS_INC) $(CM_INC) $(CZALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZ_DIR)/cz_uim.c -o $(SY_DIR)/cz_uim.$(OBJ)
	
$(SY_DIR)/cz_lmm.$(OBJ): $(CZ_DIR)/cz_lmm.c $(SYS_INC) $(CM_INC) $(CZALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZ_DIR)/cz_lmm.c -o $(SY_DIR)/cz_lmm.$(OBJ)
	
$(SY_DIR)/cz_lim.$(OBJ): $(CZ_DIR)/cz_lim.c $(SYS_INC) $(CM_INC) $(CZALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZ_DIR)/cz_lim.c -o $(SY_DIR)/cz_lim.$(OBJ)
	
$(SY_DIR)/cz_tmr.$(OBJ): $(CZ_DIR)/cz_tmr.c $(SYS_INC) $(CM_INC) $(CZALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZ_DIR)/cz_tmr.c -o $(SY_DIR)/cz_tmr.$(OBJ)
	
$(SY_DIR)/cz_nmm.$(OBJ): $(CZ_DIR)/cz_nmm.c $(SYS_INC) $(CM_INC) $(CZALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZ_DIR)/cz_nmm.c -o $(SY_DIR)/cz_nmm.$(OBJ)
	
$(SY_DIR)/cz_bmp.$(OBJ): $(CZ_DIR)/cz_bmp.c $(SYS_INC) $(CM_INC) $(CZALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZ_DIR)/cz_bmp.c -o $(SY_DIR)/cz_bmp.$(OBJ)
	
$(SY_DIR)/cz_gpm.$(OBJ): $(CZ_DIR)/cz_gpm.c $(SYS_INC) $(CM_INC) $(CZALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZ_DIR)/cz_gpm.c -o $(SY_DIR)/cz_gpm.$(OBJ)
	
$(SY_DIR)/cz_db.$(OBJ): $(CZ_DIR)/cz_db.c $(SYS_INC) $(CM_INC) $(CZALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZ_DIR)/cz_db.c -o $(SY_DIR)/cz_db.$(OBJ)
	
$(SY_DIR)/cz_edm.$(OBJ): $(CZ_DIR)/cz_edm.c $(SYS_INC) $(CM_INC) $(CZALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZ_DIR)/cz_edm.c -o $(SY_DIR)/cz_edm.$(OBJ)

$(SY_DIR)/cz_ldm.$(OBJ): $(CZ_DIR)/cz_ldm.c $(SYS_INC) $(CM_INC) $(CZALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZ_DIR)/cz_ldm.c -o $(SY_DIR)/cz_ldm.$(OBJ)

$(SY_DIR)/cz_tpm.$(OBJ): $(CZ_DIR)/cz_tpm.c $(SYS_INC) $(CM_INC) $(CZALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZ_DIR)/cz_tpm.c -o $(SY_DIR)/cz_tpm.$(OBJ)

$(SY_DIR)/cz_utl.$(OBJ): $(CZ_DIR)/cz_utl.c $(SYS_INC) $(CM_INC) $(CZALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZ_DIR)/cz_utl.c -o $(SY_DIR)/cz_utl.$(OBJ)

# All layers to CZ interface file
$(SY_DIR)/cz_ex_ms.$(OBJ): $(CZ_DIR)/cz_ex_ms.c $(SYS_INC) $(CM_INC) $(CZALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZ_DIR)/cz_ex_ms.c -o $(SY_DIR)/cz_ex_ms.$(OBJ)
	
# X2AP to X2AP user file
$(SY_DIR)/cz_ptui.$(OBJ): $(CZ_DIR)/cz_ptui.c $(SYS_INC) $(CM_INC) $(CZALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZ_DIR)/cz_ptui.c -o $(SY_DIR)/cz_ptui.$(OBJ)
	
# X2AP to layer3 file
$(SY_DIR)/cz_ptli.$(OBJ): $(CZ_DIR)/cz_ptli.c $(SYS_INC) $(CM_INC) $(CZALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZ_DIR)/cz_ptli.c -o $(SY_DIR)/cz_ptli.$(OBJ)
	
# X2AP to layer management file
$(SY_DIR)/cz_ptmi.$(OBJ): $(CZ_DIR)/cz_ptmi.c $(SYS_INC) $(CM_INC) $(CZALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZ_DIR)/cz_ptmi.c -o $(SY_DIR)/cz_ptmi.$(OBJ)
	
# SCTP files build---------------------------------------------------

$(SY_DIR)/sb_bdy1.$(OBJ): $(SB_DIR)/sb_bdy1.c $(SYS_INC) $(CM_INC) $(SBALL_INC)
	$(CC) -c $(CPRDOPTS) $(CSBOPTS) $(SB_DIR)/sb_bdy1.c -o $(SY_DIR)/sb_bdy1.$(OBJ)

$(SY_DIR)/sb_bdy2.$(OBJ): $(SB_DIR)/sb_bdy2.c $(SYS_INC) $(CM_INC) $(SBALL_INC)
	$(CC) -c $(CPRDOPTS) $(CSBOPTS) $(SB_DIR)/sb_bdy2.c -o $(SY_DIR)/sb_bdy2.$(OBJ)

$(SY_DIR)/sb_bdy3.$(OBJ): $(SB_DIR)/sb_bdy3.c $(SYS_INC) $(CM_INC) $(SBALL_INC)
	$(CC) -c $(CPRDOPTS) $(CSBOPTS) $(SB_DIR)/sb_bdy3.c -o $(SY_DIR)/sb_bdy3.$(OBJ)

$(SY_DIR)/sb_bdy4.$(OBJ): $(SB_DIR)/sb_bdy4.c $(SYS_INC) $(CM_INC) $(SBALL_INC)
	$(CC) -c $(CPRDOPTS) $(CSBOPTS) $(SB_DIR)/sb_bdy4.c -o $(SY_DIR)/sb_bdy4.$(OBJ)

$(SY_DIR)/sb_id.$(OBJ): $(SB_DIR)/sb_id.c $(SYS_INC) $(CM_INC) $(SBALL_INC)
	$(CC) -c $(CPRDOPTS) $(CSBOPTS) $(SB_DIR)/sb_id.c -o $(SY_DIR)/sb_id.$(OBJ)

$(SY_DIR)/sb_ptmi.$(OBJ): $(SB_DIR)/sb_ptmi.c $(SYS_INC) $(CM_INC) $(SBALL_INC)
	$(CC) -c $(CPRDOPTS) $(CSBOPTS) $(CSMOPTS) $(SB_DIR)/sb_ptmi.c -o $(SY_DIR)/sb_ptmi.$(OBJ)

$(SY_DIR)/sb_ptui.$(OBJ): $(SB_DIR)/sb_ptui.c $(SYS_INC) $(CM_INC) $(SBALL_INC)
	$(CC) -c $(CPRDOPTS) $(CSBOPTS) $(SB_DIR)/sb_ptui.c -o $(SY_DIR)/sb_ptui.$(OBJ)

$(SY_DIR)/sb_ptli.$(OBJ): $(SB_DIR)/sb_ptli.c $(SYS_INC) $(CM_INC) $(SBALL_INC)
	$(CC) -c $(CPRDOPTS) $(CSBOPTS) $(SB_DIR)/sb_ptli.c -o $(SY_DIR)/sb_ptli.$(OBJ)

$(SY_DIR)/sb_ex_ms.$(OBJ): $(SB_DIR)/sb_ex_ms.c $(SYS_INC) $(CM_INC) $(SBALL_INC)
	$(CC) -c $(CPRDOPTS) $(CSBOPTS) $(SB_DIR)/sb_ex_ms.c -o $(SY_DIR)/sb_ex_ms.$(OBJ)

$(SY_DIR)/sb_port.$(OBJ): $(SB_DIR)/sb_port.c $(SYS_INC) $(CM_INC) $(SBALL_INC)
	$(CC) -c $(CPRDOPTS) $(CSBOPTS) $(SB_DIR)/sb_port.c -o $(SY_DIR)/sb_port.$(OBJ)

$(SY_DIR)/sb_mtu.$(OBJ): $(SB_DIR)/sb_mtu.c $(SYS_INC) $(CM_INC) $(SBALL_INC)
	$(CC) -c $(CPRDOPTS) $(CSBOPTS) $(SB_DIR)/sb_mtu.c -o $(SY_DIR)/sb_mtu.$(OBJ)


# TUCL layer build-------------------------------------------------

$(SY_DIR)/hi_bdy1.$(OBJ): $(HI_DIR)/hi_bdy1.c $(SYS_INC) $(CM_INC) $(CZALL_INC)
	$(CC) -c $(CPRDOPTS) $(CHIOPTS) $(HI_DIR)/hi_bdy1.c -o $(SY_DIR)/hi_bdy1.$(OBJ)

$(SY_DIR)/hi_bdy2.$(OBJ): $(HI_DIR)/hi_bdy2.c $(SYS_INC) $(CM_INC) $(CZALL_INC)
	$(CC) -c $(CPRDOPTS) $(CHIOPTS) $(HI_DIR)/hi_bdy2.c -o $(SY_DIR)/hi_bdy2.$(OBJ)

$(SY_DIR)/hi_bdy3.$(OBJ): $(HI_DIR)/hi_bdy3.c $(SYS_INC) $(CM_INC) $(CZALL_INC)
	$(CC) -c $(CPRDOPTS) $(CHIOPTS) $(HI_DIR)/hi_bdy3.c -o $(SY_DIR)/hi_bdy3.$(OBJ)

$(SY_DIR)/hi_ex_ms.$(OBJ): $(HI_DIR)/hi_ex_ms.c $(SYS_INC) $(CM_INC) $(CZALL_INC)
	$(CC) -c $(CPRDOPTS) $(CHIOPTS) $(HI_DIR)/hi_ex_ms.c -o $(SY_DIR)/hi_ex_ms.$(OBJ)

$(SY_DIR)/hi_ptui.$(OBJ): $(HI_DIR)/hi_ptui.c $(SYS_INC) $(CM_INC) $(CZALL_INC)
	$(CC) -c $(CPRDOPTS) $(CHIOPTS) $(HI_DIR)/hi_ptui.c -o $(SY_DIR)/hi_ptui.$(OBJ)

$(SY_DIR)/hi_ptmi.$(OBJ): $(HI_DIR)/hi_ptmi.c $(SYS_INC) $(CM_INC) $(CZALL_INC)
	$(CC) -c $(CPRDOPTS) $(CHIOPTS) $(HI_DIR)/hi_ptmi.c -o $(SY_DIR)/hi_ptmi.$(OBJ)

$(SY_DIR)/hi_id.$(OBJ): $(HI_DIR)/hi_id.c $(SYS_INC) $(CM_INC) $(CZALL_INC)
	$(CC) -c $(CPRDOPTS) $(CHIOPTS) $(HI_DIR)/hi_id.c -o $(SY_DIR)/hi_id.$(OBJ)

$(SY_DIR)/hi_ex_pt.$(OBJ): $(HI_DIR)/hi_ex_pt.c $(SYS_INC) $(CM_INC) $(CZALL_INC)
	$(CC) -c $(CPRDOPTS) $(CHIOPTS) $(HI_DIR)/hi_ex_pt.c -o $(SY_DIR)/hi_ex_pt.$(OBJ)

$(SY_DIR)/hi_tst.$(OBJ): $(HI_DIR)/hi_tst.c $(SYS_INC) $(CM_INC) $(CZALL_INC)
	$(CC) -c $(CPRDOPTS) $(CHIOPTS) $(HI_DIR)/hi_tst.c -o $(SY_DIR)/hi_tst.$(OBJ)

# stack manager build-------------------------------------------
$(SY_DIR)/sm_bdy1.$(OBJ): $(CM_DIR)/sm_bdy1.c $(SYS_INC) $(LCZ_INC)
	$(CC) -c  $(CSMOPTS) $(CM_DIR)/sm_bdy1.c -o $(SY_DIR)/sm_bdy1.$(OBJ)

$(SY_DIR)/sm_ex_ms.$(OBJ): $(CM_DIR)/sm_ex_ms.c $(SYS_INC) $(LCZ_INC)
	$(CC) -c $(CPRDOPTS) $(CSMOPTS) $(CM_DIR)/sm_ex_ms.c -o $(SY_DIR)/sm_ex_ms.$(OBJ)

$(SY_DIR)/smhibdy1.$(OBJ): $(CM_DIR)/smhibdy1.c $(SYS_INC) $(LCZ_INC)
	$(CC) -c $(CPRDOPTS) $(CHIOPTS) $(CSMOPTS) $(CM_DIR)/smhibdy1.c -o $(SY_DIR)/smhibdy1.$(OBJ)

$(SY_DIR)/smhiexms.$(OBJ): $(HI_ACC_DIR)/smhiexms.c $(SYS_INC) $(LCZ_INC)
	$(CC) -c $(CPRDOPTS) $(CHIOPTS) $(CSMOPTS) $(HI_ACC_DIR)/smhiexms.c -o $(SY_DIR)/smhiexms.$(OBJ)

$(SY_DIR)/smhiptmi.$(OBJ): $(HI_ACC_DIR)/smhiptmi.c $(SYS_INC) $(LCZ_INC)
	$(CC) -c $(CPRDOPTS) $(CHIOPTS) $(CSMOPTS) $(HI_ACC_DIR)/smhiptmi.c -o $(SY_DIR)/smhiptmi.$(OBJ)

$(SY_DIR)/smsbbdy1.$(OBJ): $(CM_DIR)/smsbbdy1.c $(SYS_INC) $(LCZ_INC)
	$(CC) -c $(CPRDOPTS) $(CSBOPTS) $(CSMOPTS) $(CM_DIR)/smsbbdy1.c -o $(SY_DIR)/smsbbdy1.$(OBJ)

$(SY_DIR)/smsbexms.$(OBJ): $(SB_ACC_DIR)/smsbexms.c $(SYS_INC) $(LCZ_INC)
	$(CC) -c $(CPRDOPTS) $(CSBOPTS) $(CSMOPTS) $(SB_ACC_DIR)/smsbexms.c -o $(SY_DIR)/smsbexms.$(OBJ)

$(SY_DIR)/smsbptmi.$(OBJ): $(SB_ACC_DIR)/smsbptmi.c $(SYS_INC) $(LCZ_INC)
	$(CC) -c $(CPRDOPTS)  $(CSMOPTS) $(SB_ACC_DIR)/smsbptmi.c -o $(SY_DIR)/smsbptmi.$(OBJ)

$(SY_DIR)/smczbdy1.$(OBJ): $(CZSM_DIR)/smczbdy1.c $(SYS_INC) $(LCZ_INC)
	$(CC) -c $(CPRDOPTS) $(CSMOPTS) $(CZSM_DIR)/smczbdy1.c -o $(SY_DIR)/smczbdy1.$(OBJ)

$(SY_DIR)/smczexms.$(OBJ): $(CZSM_DIR)/smczexms.c $(SYS_INC) $(LCZ_INC)
	$(CC) -c $(CPRDOPTS) $(CSMOPTS) $(CZSM_DIR)/smczexms.c -o $(SY_DIR)/smczexms.$(OBJ)

$(SY_DIR)/smczptmi.$(OBJ): $(CZSM_DIR)/smczptmi.c $(SYS_INC) $(LCZ_INC)
	$(CC) -c $(CPRDOPTS) $(CSMOPTS) $(CZSM_DIR)/smczptmi.c -o $(SY_DIR)/smczptmi.$(OBJ)



# common build---------------------------------------------------------

$(SY_DIR)/cm_gen.$(OBJ): $(CM_DIR)/cm_gen.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_gen.c -o $(SY_DIR)/cm_gen.$(OBJ)

$(SY_DIR)/cm_hash.$(OBJ): $(CM_DIR)/cm_hash.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_hash.c -o $(SY_DIR)/cm_hash.$(OBJ)

$(SY_DIR)/cm_llist.$(OBJ): $(CM_DIR)/cm_llist.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_llist.c -o $(SY_DIR)/cm_llist.$(OBJ)

$(SY_DIR)/cm_lib.$(OBJ): $(CM_DIR)/cm_lib.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_lib.c -o $(SY_DIR)/cm_lib.$(OBJ)

$(SY_DIR)/cm_bdy5.$(OBJ): $(CM_DIR)/cm_bdy5.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_bdy5.c -o $(SY_DIR)/cm_bdy5.$(OBJ)

$(SY_DIR)/cm_inet.$(OBJ): $(CM_DIR)/cm_inet.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_inet.c -o $(SY_DIR)/cm_inet.$(OBJ)

$(SY_DIR)/cm_tpt.$(OBJ): $(CM_DIR)/cm_tpt.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CSBOPTS) $(CPRDOPTS) $(CM_DIR)/cm_tpt.c -o $(SY_DIR)/cm_tpt.$(OBJ)

$(SY_DIR)/cm_tkns.$(OBJ): $(CM_DIR)/cm_tkns.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_tkns.c -o $(SY_DIR)/cm_tkns.$(OBJ)

$(SY_DIR)/cm_mblk.$(OBJ): $(CM_DIR)/cm_mblk.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_mblk.c -o $(SY_DIR)/cm_mblk.$(OBJ)

$(SY_DIR)/cm_dns.$(OBJ): $(CM_DIR)/cm_dns.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_dns.c -o $(SY_DIR)/cm_dns.$(OBJ)

$(SY_DIR)/cm_xtree.$(OBJ): $(CM_DIR)/cm_xtree.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_xtree.c -o $(SY_DIR)/cm_xtree.$(OBJ)

$(SY_DIR)/cm_sdp.$(OBJ): $(CM_DIR)/cm_sdp.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_sdp.c -o $(SY_DIR)/cm_sdp.$(OBJ)

$(SY_DIR)/cm_abnf.$(OBJ): $(CM_DIR)/cm_abnf.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_abnf.c -o $(SY_DIR)/cm_abnf.$(OBJ)

$(SY_DIR)/cmabnfrx.$(OBJ): $(CM_DIR)/cmabnfrx.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cmabnfrx.c -o $(SY_DIR)/cmabnfrx.$(OBJ)

$(SY_DIR)/hit.$(OBJ): $(CM_DIR)/hit.c $(SYS_INC) $(HIT_INC)
	$(CC) -c $(CHIOPTS) $(CPRDOPTS) $(CM_DIR)/hit.c -o $(SY_DIR)/hit.$(OBJ)

$(SY_DIR)/sct.$(OBJ): $(CM_DIR)/sct.c $(SYS_INC) $(SCT_INC)
	$(CC) -c $(CSBOPTS) $(CPRDOPTS) $(CM_DIR)/sct.c -o $(SY_DIR)/sct.$(OBJ)

$(SY_DIR)/czt.$(OBJ): $(CM_DIR)/czt.c $(SYS_INC) $(CZT_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/czt.c -o $(SY_DIR)/czt.$(OBJ)

$(SY_DIR)/lcz.$(OBJ): $(CM_DIR)/lcz.c $(SYS_INC) $(CZT_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/lcz.c -o $(SY_DIR)/lcz.$(OBJ)

$(SY_DIR)/lhi.$(OBJ): $(CM_DIR)/lhi.c $(SYS_INC) $(CZALL_INC)
	$(CC) -c $(CHIOPTS) $(CPRDOPTS) $(CM_DIR)/lhi.c -o $(SY_DIR)/lhi.$(OBJ)

$(SY_DIR)/lsb.$(OBJ): $(CM_DIR)/lsb.c $(SYS_INC) $(CZALL_INC)
	$(CC) -c $(CSBOPTS) $(CPRDOPTS) $(CM_DIR)/lsb.c -o $(SY_DIR)/lsb.$(OBJ)


$(SY_DIR)/czt_pk.$(OBJ): $(CM_DIR)/czt_pk.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/czt_pk.c -o $(SY_DIR)/czt_pk.$(OBJ)

$(SY_DIR)/czt_unpk.$(OBJ): $(CM_DIR)/czt_unpk.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/czt_unpk.c -o $(SY_DIR)/czt_unpk.$(OBJ)

$(SY_DIR)/cm_pasn1.$(OBJ): $(CM_DIR)/cm_pasn1.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_pasn1.c -o $(SY_DIR)/cm_pasn1.$(OBJ)

$(SY_DIR)/cm_pasn2.$(OBJ): $(CM_DIR)/cm_pasn2.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_pasn2.c -o $(SY_DIR)/cm_pasn2.$(OBJ)

$(SY_DIR)/cm_pasn3.$(OBJ): $(CM_DIR)/cm_pasn3.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_pasn3.c -o $(SY_DIR)/cm_pasn3.$(OBJ)

$(SY_DIR)/cm_pasn4.$(OBJ): $(CM_DIR)/cm_pasn4.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_pasn4.c -o $(SY_DIR)/cm_pasn4.$(OBJ)





# System Services-------------------------------------------------------

$(SY_DIR)/ss_gen.$(OBJ): $(SS_DIR)/ss_gen.c $(SYS_INC) $(SS_INC) $(OS_INC)
	$(CC) -c $(COSOPTS) $(SS_DIR)/ss_gen.c -o $(SY_DIR)/ss_gen.$(OBJ)

$(SY_DIR)/ss_mem.$(OBJ): $(SS_DIR)/ss_mem.c $(SYS_INC) $(SS_INC) $(OS_INC)
	$(PURE) $(CC) -c $(COSOPTS) $(SS_DIR)/ss_mem.c -o $(SY_DIR)/ss_mem.$(OBJ)

$(SY_DIR)/ss_queue.$(OBJ): $(SS_DIR)/ss_queue.c $(SYS_INC) $(SS_INC) $(OS_INC)
	$(PURE) $(CC) -c $(COSOPTS) $(SS_DIR)/ss_queue.c -o $(SY_DIR)/ss_queue.$(OBJ)

$(SY_DIR)/ss_timer.$(OBJ): $(SS_DIR)/ss_timer.c $(SYS_INC) $(SS_INC) $(OS_INC)
	$(PURE) $(CC) -c $(COSOPTS) $(SS_DIR)/ss_timer.c -o $(SY_DIR)/ss_timer.$(OBJ)

$(SY_DIR)/ss_msg.$(OBJ): $(SS_DIR)/ss_msg.c $(SYS_INC) $(SS_INC) $(OS_INC)
	$(PURE) $(CC) -c $(COSOPTS) $(SS_DIR)/ss_msg.c -o $(SY_DIR)/ss_msg.$(OBJ)

$(SY_DIR)/ss_rtr.$(OBJ): $(SS_DIR)/ss_rtr.c $(SYS_INC) $(SS_INC) $(OS_INC)
	$(PURE) $(CC) -c $(COSOPTS) $(SS_DIR)/ss_rtr.c -o $(SY_DIR)/ss_rtr.$(OBJ)

$(SY_DIR)/ss_drvr.$(OBJ): $(SS_DIR)/ss_drvr.c $(SYS_INC) $(SS_INC) $(OS_INC)
	$(PURE) $(CC) -c $(COSOPTS) $(SS_DIR)/ss_drvr.c -o $(SY_DIR)/ss_drvr.$(OBJ)

$(SY_DIR)/ss_pack.$(OBJ): $(SS_DIR)/ss_pack.c $(SYS_INC) $(SS_INC) $(OS_INC)
	$(PURE) $(CC) -c $(COSOPTS) $(SS_DIR)/ss_pack.c -o $(SY_DIR)/ss_pack.$(OBJ)

$(SY_DIR)/ss_strm.$(OBJ): $(SS_DIR)/ss_strm.c $(SYS_INC) $(SS_INC) $(OS_INC)
	$(PURE) $(CC) -c $(COSOPTS) $(SS_DIR)/ss_strm.c -o $(SY_DIR)/ss_strm.$(OBJ)

$(SY_DIR)/ss_task.$(OBJ): $(SS_DIR)/ss_task.c $(SYS_INC) $(SS_INC) $(OS_INC)
	$(PURE) $(CC) -c $(COSOPTS) $(SS_DIR)/ss_task.c -o $(SY_DIR)/ss_task.$(OBJ)

$(SY_DIR)/ss_id.$(OBJ): $(SS_DIR)/ss_id.c $(SYS_INC) $(SS_INC) $(OS_INC)
	$(PURE) $(CC) -c $(COSOPTS) $(SS_DIR)/ss_id.c -o $(SY_DIR)/ss_id.$(OBJ)

$(SY_DIR)/cm_mem.$(OBJ): $(CM_DIR)/cm_mem.c $(SYS_INC) $(SS_INC) $(OS_INC)
	$(CC) -c $(COSOPTS) $(CM_DIR)/cm_mem.c -o $(SY_DIR)/cm_mem.$(OBJ)

# OS - MTSS build-------------------------------------------------------
$(SY_DIR)/mt_ss.$(OBJ): $(MT_DIR)/mt_ss.c $(SYS_INC) $(SS_INC) $(MT_INC)
	$(CC) -c $(COSOPTS) $(MT_DIR)/mt_ss.c -o $(SY_DIR)/mt_ss.$(OBJ)

$(SY_DIR)/mt_id.$(OBJ): $(MT_DIR)/mt_id.c $(SYS_INC) $(SS_INC) $(MT_INC)
	$(PURE) $(CC) -c $(COSOPTS) $(MT_DIR)/mt_id.c -o $(SY_DIR)/mt_id.$(OBJ)

$(SY_DIR)/mt_tst.$(OBJ): $(MT_DIR)/mt_sts.c $(SYS_INC) $(SS_INC) $(MT_INC)
	$(PURE) $(CC) -c $(COSOPTS) $(MT_DIR)/mt_sts.c -o $(SY_DIR)/mt_sts.$(OBJ)

# MTSS-Windows NT-------------------------------------------------------
$(SY_DIR)/ns_gen.$(OBJ): $(OS_DIR)/ns_gen.c $(SYS_INC) $(SS_INC)
	$(CC) -c $(COSOPTS) $(OS_DIR)/ns_gen.c

$(SY_DIR)/smnsexms.$(OBJ): $(OS_DIR)/smnsexms.c $(SYS_INC) $(SS_INC)
	$(CC) -c $(CSMOPTS) $(COSOPTS) $(OS_DIR)/smnsexms.c

$(SY_DIR)/smnsbdy1.$(OBJ): $(OS_DIR)/smnsbdy1.c $(SYS_INC) $(SS_INC)
	$(CC) -c $(CSMOPTS) $(COSOPTS) $(OS_DIR)/smnsbdy1.c

$(SY_DIR)/lns.$(OBJ): $(OS_DIR)/lns.c $(SYS_INC) $(SS_INC)
	$(CC) -c $(COSOPTS) $(OS_DIR)/lns.c

$(SY_DIR)/ns_ex_ms.$(OBJ): $(OS_DIR)/ns_ex_ms.c $(SYS_INC) $(SS_INC)
	$(CC) -c $(COSOPTS) $(OS_DIR)/ns_ex_ms.c

$(SY_DIR)/ns_id.$(OBJ): $(OS_DIR)/ns_id.c $(SYS_INC) $(SS_INC)
	$(CC) -c $(COSOPTS) $(OS_DIR)/ns_id.c

$(SY_DIR)/ns_ptmi.$(OBJ): $(OS_DIR)/ns_ptmi.c $(SYS_INC) $(SS_INC)
	$(CC) -c $(COSOPTS) $(OS_DIR)/ns_ptmi.c

$(SY_DIR)/ns_space.$(OBJ): $(OS_DIR)/ns_space.c $(SYS_INC) $(SS_INC)
	$(CC) -c $(COSOPTS) $(OS_DIR)/ns_space.c

$(SY_DIR)/ns_task.$(OBJ): $(OS_DIR)/ns_task.c $(SYS_INC) $(SS_INC)
	$(CC) -c $(COSOPTS) $(OS_DIR)/ns_task.c

$(SY_DIR)/ns_timer.$(OBJ): $(OS_DIR)/ns_timer.c $(SYS_INC) $(SS_INC)
	$(CC) -c $(COSOPTS) $(OS_DIR)/ns_timer.c

$(SY_DIR)/np_gen.$(OBJ): $(OS_DIR)/np_gen.c $(SYS_INC) $(SS_INC)
	$(CC) -c $(COSOPTS) $(OS_DIR)/np_gen.c

$(SY_DIR)/np_task.$(OBJ): $(OS_DIR)/np_task.c $(SYS_INC) $(SS_INC)
	$(CC) -c $(COSOPTS) $(OS_DIR)/np_task.c

$(SY_DIR)/np_timer.$(OBJ): $(OS_DIR)/np_timer.c $(SYS_INC) $(SS_INC)
	$(CC) -c $(COSOPTS) $(OS_DIR)/np_timer.c

$(SY_DIR)/smnsptmi.$(OBJ): $(OS_DIR)/smnsptmi.c $(SYS_INC) $(SS_INC)
	$(CC) -c $(COSOPTS) $(OS_DIR)/smnsptmi.c

# VxWorks----------------------------------------------------------
$(SY_DIR)/vw_ss.$(OBJ): $(OS_DIR)/vw_ss.c $(SYS_INC) $(SS_INC)
	$(CC) -c $(COSOPTS) $(OS_DIR)/vw_ss.c

$(SY_DIR)/vw_id.$(OBJ): $(OS_DIR)/vw_id.c $(SYS_INC) $(SS_INC)
	$(CC) -c $(COSOPTS) $(OS_DIR)/vw_id.c

$(SY_DIR)/vw_acc.$(OBJ): $(OS_DIR)/vw_acc.c $(SYS_INC) $(SS_INC)
	$(CC) -c $(COSOPTS) $(OS_DIR)/vw_acc.c

#Performance Files
$(SY_DIR)/rs_app.$(OBJ): $(CZACC_DIR)/rs_app.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/rs_app.c -o $(SY_DIR)/rs_app.$(OBJ)

$(SY_DIR)/rs_perf_tst.$(OBJ): $(CZACC_DIR)/rs_perf_tst.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/rs_perf_tst.c -o $(SY_DIR)/rs_perf_tst.$(OBJ)

$(SY_DIR)/rssm.$(OBJ): $(CZACC_DIR)/rssm.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/rssm.c -o $(SY_DIR)/rssm.$(OBJ)

$(SY_DIR)/rssm_sbhdl.$(OBJ): $(CZACC_DIR)/rssm_sbhdl.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/rssm_sbhdl.c -o $(SY_DIR)/rssm_sbhdl.$(OBJ)

$(SY_DIR)/rssm_czhdl.$(OBJ): $(CZACC_DIR)/rssm_czhdl.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/rssm_czhdl.c -o $(SY_DIR)/rssm_czhdl.$(OBJ)

$(SY_DIR)/rssm_utl.$(OBJ): $(CZACC_DIR)/rssm_utl.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/rssm_utl.c -o $(SY_DIR)/rssm_utl.$(OBJ)

$(SY_DIR)/rs_tmr.$(OBJ): $(CZACC_DIR)/rs_tmr.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/rs_tmr.c -o $(SY_DIR)/rs_tmr.$(OBJ)

$(SY_DIR)/rssm_hihdl.$(OBJ): $(CZACC_DIR)/rssm_hihdl.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/rssm_hihdl.c -o $(SY_DIR)/rssm_hihdl.$(OBJ)

$(SY_DIR)/rs_perf_ex_ms.$(OBJ): $(CZACC_DIR)/rs_perf_ex_ms.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/rs_perf_ex_ms.c -o $(SY_DIR)/rs_perf_ex_ms.$(OBJ)

$(SY_DIR)/rs_perf_ptli.$(OBJ): $(CZACC_DIR)/rs_perf_ptli.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/rs_perf_ptli.c -o $(SY_DIR)/rs_perf_ptli.$(OBJ)

$(SY_DIR)/smczexms_perf.$(OBJ): $(CZACC_DIR)/smczexms_perf.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/smczexms_perf.c -o $(SY_DIR)/smczexms_perf.$(OBJ)

$(SY_DIR)/smczptmi_perf.$(OBJ): $(CZACC_DIR)/smczptmi_perf.c $(CZACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(CZACC_DIR)/smczptmi_perf.c -o $(SY_DIR)/smczptmi_perf.$(OBJ)

#********************************************************************30**
#
#        End of file:     cz.mak@@/main/2 - Tue Aug 30 18:36:02 2011
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
#----------- -------- ---- -----------------------------------------------
#/main/1      ---      rp                1. Created for Initial Release 1.1
# /main/2     ---      pt                1. LTE-X2AP 3.1 release.
#********************************************************************91*/

# DO NOT DELETE THIS LINE -- make depend depends on it.

