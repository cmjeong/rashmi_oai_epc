#
#********************************************************************20**
#
#       Name:   LTE RRC - makefile
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
#       Sid:      nh.mak@@/main/3 - Fri Jul  1 01:13:11 2011
#
#       Prg:    vk
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
# For Solaris :
#          use the Python Paths defined for solaris
#          use the LIB_INC_PATH defined for solaris
#          use the ACC_INC_PATH defined for solaris
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


#----------------- RRC product options --------------------------
# 
#PRDOPTS=-DNH -DCMFILE_REORG_1 -DCMFILE_REORG_2 -DDEBUGP -DCM_PASN_DBG -DCM_INET2 -DCCPU_OPT -DRRC_PHY_CFG_SUPP -UNH_ASN_COND_VALIDATE -DTENB_MULT_CELL_SUPPRT -DLTERRC_REL9 -DNHU_VER2 -DCTF_VER2
PRDOPTS=-DNH -DDEBUGP -DSM -DLCLNH -DLCSMMILNH -DLCSMNHMILNH -DLCNHMILNH -DLCNHU -DWR -DNX -DLCWRLINHU -DLCNHUINHU -DLCNXLINHU\
   -DLCNHLICRG -DLCCRG -DLCRGUICRG -DLCNHLICKW -DLCCKW -DLCKWUICKW -DLCCPJ -DNH -UKW -DLCNHLICPJ -DLCPJUICPJ \
	-UKW -DNH -DLCKWUIKWU -DLCKWU -DLCNHLIKWU -DCCPU_OPT -UPJ  -DLCPJU  -DLCNHLIPJU -DLCPJUIPJU -DRX -DRNC_INTEG_CCPU \
	-DCM_INET2 -DTENB_ACC -DRLOG_ENABLE_TEXT_LOGGING -DLTERRC_REL9 -DNHU_VER2 -DCTF_VER2 -DRRC_REL11 -UCM_PASN_DBG \
	-DTENB_MULT_CELL_SUPPRT -DLTE_ADV

# Product options for portable build
PRDPTOPTS=$(PRDOPTS) -DNH_PT_BUILD 

# Product options for acceptance test build
#For Windows Add -DSS_DRVR_SUPPORT
PRDACCOPTS=$(PRDOPTS) -DNX -DSM -DDM -DCMXTA_MASTER -UNO_ERRCLS 

# Product options for library build
PRDLIBOPTS=$(PRDACCOPTS) -DDBG4

#=======================================================================
#
# macros for specific OS
#
# SECTION 2

#MOS Product specific option define
MSOPTS=-DMS

# System Services (e.g. MOS, MTSS etc.) Product specific option define
#
MSCOPTS=-DCMFILE_REORG_1 -D__EXTENSIONS__ -DCMFILE_REORG_2

# Options for compilation with different OS's
# Default is for Portable build
# For acceptance test build either uncomment specific OS environment
# required or specify on command line

# General OS Compile Options
GENOSOPTS=-DSS -DCMFILE_REORG_1 -DCMFILE_REORG_2
          
# General OS Compile Options
GENOSPTOPTS=-DCMFILE_REORG_1 -DCMFILE_REORG_2 

# General OS Compile Options for 64 bit compilation
#GENOSOPTS=-DSS -DCMFILE_REORG_1 -DCMFILE_REORG_2 -DALIGN_64BIT -DBIT_64

# Portable build options
PTOSOPTS=-DPORTVER 

# Options for acceptance test build with VrTx OS
VXOSOPTS=-DVX

# Options for acceptance test build with VxWorks OS
VWOSOPTS=-DSS_VW -DSS_DRVR_SUPPORT -DVW_COMPILE -DCMIET_LARGE_MAX_UDPRAW_SIZE -DDEBUGNOEXIT -DSS_VW6X

# Options for acceptance test build with WINNT OS kernel build
WINOSOPTS=-DWINNT -DNS

# Options for acceptance test build with MTSS - MOS Multithread OS
MTOSOPTS=-DSS_MT -DCMFILE_REORG_1 -DSS_SINGLE_THREADED -D_REENTRANT -DDEBUGNOEXIT -DSS_DRVR_SUPPORT -DTENB_ACC

# Options for acceptance test build with MTSS - WINNT
NSOSOPTS=-DNS -DSS_OLD_THREAD -DNS_ENB_MGMT -DSS_DRVR_SUPPORT

# Linux specific options
LNXOSOPTS=-DSS_LINUX $(MTOSOPTS)

# Options for library build with MTSS 
LIBOSOPTS="-DSS_MT -DSS  -DSS_SINGLE_THREADED"

# General OSOPTS. For portable build PTOSOPTS, for acceptante MTOSOPTS if using
# Trillium's MTSS solaris system services, for all others use one of the above
# or customer specific flag

# For Pt build
#OSOPTS=$(GENOSPTOPTS) $(PTOSOPTS)

# For MTSS - Linux
OSOPTS=$(GENOSOPTS) $(MTOSOPTS)

# For vxWorks
#OSOPTS=$(GENOSOPTS) $(VWOSOPTS)

# For Windows
#OSOPTS=$(GENOSOPTS) $(NSOSOPTS)

# OS options for build with Linux C compiler
#OSOPTS=$(GENOSOPTS) $(LNXOSOPTS)


#=======================================================================
# SECTION 3
# Treat each of the following as examples and modify to specific product
# requirements
#
# macro for output file name and makefile name 
#
BASENAME=nh

MAKENAME=$(BASENAME).mak

# default acceptance test for Solaris cc environment
BINACC=$(BASENAME)_acc

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

#Library Build
BINLNXLIB=lnx_lib

#purify
BINPURACC=pur_acc


#=======================================================================
#
# macro for directories and include paths
#
# SECTION 4
# Treat each of the following as examples and modify to specific product
# requirements



# Common files directory 
CM_DIR=../../cm

# RRC directory
NH_DIR=../../lterrc

# RL directory
RL_DIR=../../rlog

# Parent RRC directory
NI_DIR=.

# Sample RRC User Layer directory
NHU_DIR=.

# Sample RRC provider directory
NH_SAMPLE_DIR=.

# common stack manager files directory 
SM_DIR=../../cm

# RRC stack manager directory
SM_DIR=../../cm

# Solaris MTSS specific dir.
MT_DIR=../../mt_acc

# VxWorks include directory
#VW_DIR=/u/prd/rtr/vw

# WIN Include directory
#NS_DIR=/u/prd/rtr/ns

# mos directory
OS_DIR=../../mt_acc
#OS_DIR=$(VW_DIR)

# Common SSI directory
SS_DIR=../../mt_acc
#SS_DIR=$(VW_DIR)
#MT_DIR=$(VW_DIR)



# acceptance directory
NHACC_DIR=./

#build directory
SY_DIR=.

#include path for VxWorks
# include path VxWorks environment
#VW_INC=/tools/vxworks/ppc/target/h
#VW_INC=C:/WindRiver/vxworks-6.3/target/h
#VW_INC1=C:/WindRiver/vxworks-6.3/target/h/wrn
#VW_INC2=C:/WindRiver/vxworks-6.3/target/h/wrn/coreip
#VW_INC3=C:/WindRiver/vxworks-6.3/target/h/wrn/coreip/netinet
#VW_INC4=C:/WindRiver/vxworks-6.3/sys-include

#VW_INC=C:\WindRiver\vxworks-6.7\target\h
#VW_INC1=C:\WindRiver\vxworks-6.7\target\h\wrn
#VW_INC2=C:\WindRiver\vxworks-6.7\target\h\wrn\coreip
#VW_INC3=C:\WindRiver\vxworks-6.7\target\h\wrn\coreip\netinet
#VW_INC4=C:\WindRiver\vxworks-6.7\target\usr\h
#VW_INC5=C:\WindRiver\vxworks-6.7\sys-include
#VW_INC6=C:/WindRiver/gnu/4.1.2-vxworks-6.7/lib/gcc/powerpc-wrs-vxworks/4.1.2/include

#VW_INC6=C:\WindRiver\components\ip_net2-6.7\ipcom\config
#VW_INC7=C:\WindRiver\components\ip_net2-6.7\ipcom\port\vxworks\config
#VW_INC8=C:\WindRiver\components\ip_net2-6.7\ipcom\include
#VW_INC9=C:\WindRiver\components\ip_net2-6.7\ipcom
#VW_INC10=C:\WindRiver\components\ip_net2-6.7\ipxinc\include
#VW_INC11=C:\WindRiver\components\ip_net2-6.7\ipcom\port\vxworks\include


# portable include path
PT_INC_PATH="-I$(CM_DIR) -I$(NH_DIR)"

# RL
RL_INC_PATH="-I$(RL_DIR)-I$(CM_DIR) -I$(NH_DIR)"
# for m68k 
#PT_INC_PATH="-I$(CM_DIR) -I$(LM_DIR) -I/usr/include"

#For windows Add suitable Python Path
#PYTHON_PATH_WIN = c:\Python24\include

#Python Paths for solaris 32 bit
#PYTHON_PATH_SOL32=/usr/ccpu/python/solaris/10/32bit/python-2.4.4/include/python2.4
#PY_LIB_DIR=/usr/ccpu/python/solaris/10/32bit/python-2.4.4/lib
#Python Paths for solaris 64 bit
#PYTHON_PATH_SOL32=/usr/ccpu/python/solaris/10/64bit/python-2.4.4/include/python2.4
#PY_LIB_DIR=/usr/ccpu/python/solaris/10/64bit/python-2.4.4/lib


# library include path for linux
LIB_INC_PATH="-I$(NH_DIR) -I$(SY_DIR) -I$(CM_DIR) -I$(SS_DIR) -I$(MT_DIR)"
# library include path for solaris
#LIB_INC_PATH="-I$(NH_DIR) -I$(SY_DIR) -I$(CM_DIR) -I$(SS_DIR) -I$(MT_DIR) -I$(PY_LIB_DIR)"


# acceptance test include path for linux 
ACC_INC_PATH="-I$(NH_DIR) -I$(CM_DIR) -I$(NHACC_DIR) -I$(SM_DIR) \
	      -I$(SM_DIR)  -I$(OS_DIR) -I$(NHU_DIR) -I$(NH_SAMPLE_DIR)\
              -I$(MT_DIR) -I$(SS_DIR) -I$(RL_DIR)"

# acceptance test include path for solaris
#ACC_INC_PATH="-I$(NH_DIR) -I$(CM_DIR) -I$(NHACC_DIR) -I$(SM_DIR) \
#	      -I$(SM_DIR)  -I$(OS_DIR) -I$(NHU_DIR) -I$(NH_SAMPLE_DIR)\
#              -I$(MT_DIR) -I$(SS_DIR) -I$(PYTHON_PATH_SOL32)"

# acceptance test include path for VXWORKS
#ACC_INC_PATH="-I$(NH_DIR) -I$(CM_DIR) -I$(NHACC_DIR) -I$(SM_DIR) \
#	       -I$(SM_DIR)  -I$(OS_DIR) -I$(NHU_DIR) -I$(NH_SAMPLE_DIR)\
#          -I$(VW_DIR) -I$(VW_INC) -I$(VW_INC1) -I$(VW_INC2) -I$(VW_INC3) -I$(VW_INC4)\
#			 -I$(VW_INC5) -I$(VW_INC6)"

# MTSS - files include path
#MTINC_PATH="-I$(CM_DIR) -I$(SS_DIR) -I$(MT_DIR)"

# library path - used for intgrated products and simulation env.
LIB_PATH=/tools/mri/lib
  
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
SOLCOPTS="-Xa -g "

# For non-ANSI Compilation 
#SOLENV="-DSUNOS -D__EXTENSIONS__"
#SOLCOPTS="-g "

#For 64 Bit Compilation
#SOLCOPTS="-g -mt -xarch=v9 -DALIGN_64BIT -DBIT_64"
#SOLLOPTS="-mt -xarch=v9 -o $(OUTNAME) -lpthread -lrt -lpython2.4 -lsocket -lnsl"
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
INSENV="-DSUNOS -DANSI -DUSE_PURE -DSS_LINUX"
INSCOPTS="-g3 -ansi -Wall -Wno-comment -pipe -Wshadow -Wcast-qual \
   -Wstrict-prototypes -Wmissing-prototypes -pedantic \
   -Wimplicit -Wunused"

#INSCOPTS=""
 
# For non-ANSI Compilation
#INSENV=-DSUNOS 
#INSCOPTS="-g"
#INSCOPTS="-g "

INSCC="/usr/local/insure71/bin/insure -m32"
INSLD="/usr/local/insure71/bin/insure -m32"
INSLOPTS="-o $(OUTNAME)"
INSLIBS="-Xlinker -export-dynamic -lpthread  -lnsl -lpython2.4 -lm -lrt -lutil -ldl"
INSLINT="lint"
INSLNTOPTS="-c -F -p -v"


#----------------------------------------- GNU gcc for SPARC 
#
# These flags define the environment required to build an image on
# a Sun/SPARC workstation with GNU C version 2.5.7 (or greater) running
# Solaris 2.4
#
# For ANSI Compilation
GNUENV="-DSUNOS -DANSI -D__EXTENSIONS__"

# For non-ANSI Compilation
#GNUENV="-DSUNOS -D__EXTENSIONS__"

# For ANSI portable Compilation
GNUPTENV = $(GNUENV)

# For non-ANSI portable Compilation
#GNUPTENV="-DSUNOS -D__EXTENSIONS__ -DDONT_USE_SYS_LIB"

#/* for m68k compiler */
#GNUENV="-DSUNOS -DANSI -DELVIS_68040 -DNOERRCHK -DNO_ERRCLS -DNOCONAVL"
#GNUCC="m68k-coff-gcc"
#GNULD="m68k-coff-ld"
#GNULIBLD="ld"
#GNUCOPTS="-m68040 -Wall -fno-strict-aliasing -Wno-comment -pipe -Wshadow \
#-Wcast-qual  -Wstrict-prototypes -Wmissing-prototypes"
#GNULOPTS="-A -o $(OUTNAME) -Tlinker.ld -Map=lm_pt.map" 

#GNUCC=gcc
#GNULD=gcc

GNUCC=g++
GNULD=g++

GNULIBLD="/usr/ccs/bin/ld"

GNUCOPTS=" -O1 -g3 -Wimplicit -Wunused -Wcomment -Wchar-subscripts \
-Wuninitialized -Wparentheses -Wformat -Winline -Wreturn-type -fPIC \
-Wmissing-prototypes -pedantic"


#For 64 Bit compilation
#GNUCOPTS="-g -m64 -DALIGN_64BIT -DBIT_64"
#GNULOPTS="-m64 -64 -DALIGN_64BIT -DBIT_64 -o $(OUTNAME) -lsocket -lnsl -lpython2.4 -lm -ldl -lposix4"
#GNUPTLOPTS="-m64 -64 -DALIGN_64BIT -DBIT_64 -o $(OUTNAME) -lsocket -lnsl -lm -ldl -lposix4"

#g++ options
#-Wstrict-prototypes -Wmissing-prototypes"
#GNUCOPTS="-g3 -Wall -Wno-comment -pipe -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes"

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
CPPCOPTS="-g"
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
GPPENV="-DSUNOS -DANSI -DSS_LINUX"
GPPCC=g++
GPPLD=g++
GPPLIBLD=/usr/ccpu/suntools/bin/ld
GPPCOPTS="-g -Wall -fno-strict-aliasing -Wno-comment -pipe -Wcast-qual  \
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
LNXENV="-DSUNOS -DANSI -DSS_LINUX -DNOCONAVL -DUSE_PURE"

# For non-ANSI Compilation
#LNXENV="-DSUNOS -DSS_LINUX"

# For ANSI portable Compilation
LNXPTENV = $(LNXENV)

# For non-ANSI portable Compilation
#LNXPTENV="-DSUNOS -DDONT_USE_SYS_LIB"

# For Purify accpetance build
ifeq ($(CCPU_PURIFY),y)
LNXCC="purify gcc -m32"
LNXLD="purify gcc -m32"
else
#LNXCC="gcc -m32"
#LNXLD="gcc -m32"
LNXCC="g++ -m32"
LNXLD="g++ -m32"

endif

LNXLIBLD="ld"
PLNXCC="purecov g++ -m32"
PLNXLD="purecov g++ -m32"
#LNXCC="/usr/local/Rational/releases/PurifyPlus.2003a.06.13/i386_linux2/bin/purify gcc -g"
#LNXLD="/usr/local/Rational/releases/PurifyPlus.2003a.06.13/i386_linux2/bin/purify gcc -g"
#LNXCOPTS="-Os -g3 -ansi -Wall -fno-strict-aliasing -Wno-comment -pipe -Wshadow -Wcast-qual \
	-Wstrict-prototypes -Wmissing-prototypes -pedantic \
	-Wimplicit -Wunused --std=c99"
LNXCOPTS="-g3 -ansi -Wall -fno-strict-aliasing -Wno-comment -pipe -Wshadow -Wno-cast-qual \
	-pedantic -Wimplicit -Wunused -Wno-variadic-macros"
LNXLOPTS="-o $(OUTNAME) -lpthread -lnsl -lrt -Xlinker -zmuldefs -export-dynamic -lpython2.4 -lm -ldl -lutil"
LNXPTLOPTS="-o $(OUTNAME)"
LNXLIBOPTS="-r -o $(OUTNAME)"

#For 64 Bit compilation
#LNXCC="gcc -m64 -DALIGN_64BIT -DBIT_64"
#LNXLD="gcc -m64"
#LNXCOPTS="-Os -g3 -ansi -Wall -fno-strict-aliasing -Wno-comment -pipe -Wshadow -Wcast-qual \
#        -Wstrict-prototypes -Wmissing-prototypes -pedantic \
#        -Wimplicit -Wunused"
#LNXLOPTS="-o $(OUTNAME) -lpthread -lrt -Xlinker -zmuldefs -export-dynamic -lpython2.4 -lm -ldl -lutil"

LNXLIBS=""
LNXLDLIBS=""
LNXLINT="lint"
LNXLNTOPTS="-c -F -p -v"
LNXLIBOSOPTS="-DSS_MT -D_REENTRANT -D__EXTENSIONS__  -DDEBUGNOEXIT -D_GNU_SOURCE -DSS_LINUX"

#PURIFY
PURCC="purify --cache-dir=/tmp g++ -m32 -DUSE_PURE"
PURLD="purify --cache-dir=/tmp g++ -m32 -DUSE_PURE"
PURLIB="purify --cache-dir=/tmp g++ -m32"

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
WINENV="-DWIN32 -DANSI -DWIN2K -DWIN32_LEAN_AND_MEAN -DSS_DRVR_SUPPORT"
 
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
WINLIBOPTS="lib /OUT:$(OUTNAME)"

# cc386 for VxWorks - Pentium Target
# These flags define the environment required to build an image on Vxworks
# with cc386 on Pentium Target
#
# For ANSI Compilation
VWINTENV="-DANSI -DCPU=PENTIUM -DCPU_VARIANT=PENTIUMPRO "
VWINTCOPTS="-g -mpentium -msoft-float -fvolatile -fno-builtin -Wall \
	     -Wno-comment -ansi -pedantic -nostdinc -Wshadow \
             -Wcast-qual -fsigned-char"
VWINTLIBS="-lsocket"

# For non-ANSI Compilation
#VWINTENV="-DCPU=PENTIUM -DCPU_VARIANT=PENTIUMPRO "
#VWINTCOPTS="-g -mpentium -msoft-float -fvolatile -fno-builtin -Wall \
#	      -Wno-comment -pipe -nostdinc -Wshadow -Wredundant-decls \
#             -Wcast-qual -fsigned-char"

VWINTCC="cc386 -mcpu=pentium"
VWINTLD="ld386"
VWINTLOPTS="-o $(OUTNAME) -r"
#VWINTLIBS=""
 
# ccppc cross compiler on Solaris for Vx Works on PPC--------------------
# These flags define the environment required to build an image on a Sun/SPARC
# workstation with ccppc v. 2.7.2 running Solaris 2.5.1
#
# For ANSI Compilation
#For VXWORKS
PPCENV=-DCPU=SIMNT -DANSI -DPQUICCADS -DVW_COMPILE -DCMINETFLATBUF
PPCCOPTS=-g -mcpu=i486 -fvolatile -fno-builtin -Wall \
	     -Wno-comment -ansi -pedantic -pipe -nostdinc -Wshadow \
	     -Wcast-qual -fsigned-char

#PPCENV="-DCPU=PPC860 -DCCPPC -DANSI -DPQUICCADS"
#PPCENV="-DCPU=SIMNT -DANSI -DPQUICCADS"
#PPCENV=-DPCORE -DCPU=PPC604 -DANSI -DCCPPC
#PPCCOPTS="-g -mcpu=i486 -msoft-float -fvolatile -fno-builtin -Wall \
#	      -Wno-comment -ansi -pedantic -pipe -nostdinc -Wshadow \
#	      -Wcast-qual -fsigned-char"
#PPCCOPTS="-mcpu=860 -msoft-float -fvolatile -fno-builtin -Wall -fno-strict-aliasing \
#           -Wno-comment -ansi -pedantic -pipe -nostdinc -Wshadow \
#           -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes"

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
 


#=======================================================================
#
# macros for compile time options
#
 
# portable options
CPTOPTS=$(MODEL) $(ENV) $(COPTS) $(INC_PATH) $(OSOPTS) -DNH_PT_BUILD
 
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
SMOPTS=-DCMFILE_REORG_1 -DCMFILE_REORG_2 -DDEBUGP 
 
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

#RLOG includes
RL_INC=$(RL_DIR)/rl_common.h $(RL_DIR)/rl_rlog.h $(RL_DIR)/rl_interface.h 
# all system includes 
SYS_INC=$(ENV_INC) $(GEN_INC) $(SSI_INC) $(RL_INC)

# Product layer management - lnh includes
LNH_INC=$(CM_DIR)/lnh.h $(CM_DIR)/lnh.x

# Product Upper Interface - nhu includes 
NHU_INC=$(CM_DIR)/nhu.h $(CM_DIR)/nhu.x

# Product Lower Interface - CKW, CRG, KWU, CPJ, PJU includes
NHL_INC=$(CM_DIR)/ckw.h $(CM_DIR)/ckw.x $(CM_DIR)/crg.h $(CM_DIR)/crg.x $(CM_DIR)/kwu.h $(CM_DIR)/kwu.x $(CM_DIR)/cpj.h $(CM_DIR)/cpj.x $(CM_DIR)/pju.h $(CM_DIR)/pju.x $(CM_DIR)/ctf.h $(CM_DIR)/ctf.x

# common function library includes
CM_INC=$(CM_DIR)/cm5.x    $(CM_DIR)/cm5.h    \
	$(CM_DIR)/cm_lib.x $(CM_DIR)/cm_err.h  \
	$(CM_DIR)/cm_tkns.x   $(CM_DIR)/cm_tkns.h \
	$(CM_DIR)/cm_inet.x  $(CM_DIR)/cm_inet.h

# RRC layer includes
NH_INC=$(NH_DIR)/nh.h $(NH_DIR)/nh.x

# RRC acceptance test includes 
LMACC_INC= $(NH_DIR)/nh_acc.x $(NH_DIR)/nh_acc.h

# Product includes 
NHP_INC=$(LNH_INC) $(NHU_INC) $(NH_INC)

# ALL Product includes 
NHALL_INC=$(LNH_INC) $(NHU_INC) $(NH_INC) \
          $(NHL_INC) 

# Product - sample acceptance test includes
NHACC_INC=$(NHACC_DIR)/nhac_acc.h $(NHACC_DIR)/nhac_acc.x

# sample acceptance tests all includes
NHACCALL_INC=$(LNH_INC) $(NHU_INC) $(NHL_INC) $(NHACC_INC)

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

# Common includes for the product
CMP_INC=$(SS_INC) $(CM_INC)


# include path VxWorks environment
#VW_INC=/tools/vxworks/ppc/target/h

#=======================================================================
#
# macros for source and object files
# SECTION 7
#


#----------------------------------------- acceptance test source
NHAC_SRCS = \
	$(NHACC_DIR)/cm_xta_txn.c \
	$(NHACC_DIR)/cm_xta_intutl.c \
	$(NHACC_DIR)/cm_xta_tmr.c \
	$(NHACC_DIR)/cm_xta_inthdl.c \
	$(NHACC_DIR)/cm_xta_intreg.c \
	$(NHACC_DIR)/cm_xta_res.c \
	$(NHACC_DIR)/cm_xta_queue.c \
	$(NHACC_DIR)/cm_xta_log.c \
	$(NHACC_DIR)/cm_xta_master.c \
	$(NHACC_DIR)/cm_xta_reg.c \
	$(NHACC_DIR)/cm_xta_tst.c \
	$(NHACC_DIR)/cm_xta_ipc.c \
	$(NHACC_DIR)/cm_xta_flag.c \
	$(NHACC_DIR)/cm_xta_py.c \
	$(NHACC_DIR)/cm_xta_tcfsm.c \
	$(NHACC_DIR)/cm_xta_ldfsm.c \
	$(NHACC_DIR)/cm_xta_xml.c \
	$(NHACC_DIR)/cm_xta_ex_ms.c \
	$(NHACC_DIR)/cm_xta_tgfsm.c \
	$(NHACC_DIR)/cm_xta_tafsm.c \
	$(NHACC_DIR)/cm_xta_slave.c \
	$(NHACC_DIR)/nhac_kwureg.c \
	$(NHACC_DIR)/nhac_kwucb.c \
	$(NHACC_DIR)/nhac_kwuhdl.c \
	$(NHACC_DIR)/nhac_kwuutl_r9.c \
   $(NHACC_DIR)/nhac_kwuutl_r11.c \
	$(NHACC_DIR)/nhac_ckwreg.c \
	$(NHACC_DIR)/nhac_ckwcb.c \
	$(NHACC_DIR)/nhac_ckwhdl.c \
	$(NHACC_DIR)/nhac_ckwutl.c \
	$(NHACC_DIR)/nhac_crgreg.c \
	$(NHACC_DIR)/nhac_crgcb.c \
	$(NHACC_DIR)/nhac_crghdl.c \
	$(NHACC_DIR)/nhac_crgutl.c \
	$(NHACC_DIR)/nhac_ctfreg.c \
	$(NHACC_DIR)/nhac_ctfcb.c \
	$(NHACC_DIR)/nhac_ctfhdl.c \
	$(NHACC_DIR)/nhac_ctfutl.c \
	$(NHACC_DIR)/nhac_cpjreg.c \
	$(NHACC_DIR)/nhac_cpjcb.c \
	$(NHACC_DIR)/nhac_cpjhdl.c \
	$(NHACC_DIR)/nhac_cpjutl.c \
	$(NHACC_DIR)/nhac_pjureg.c \
	$(NHACC_DIR)/nhac_pjucb.c \
	$(NHACC_DIR)/nhac_pjuhdl.c \
	$(NHACC_DIR)/nhac_pjuutl_r11.c \
	$(NHACC_DIR)/nhac_pjuutl_r9.c \
	$(NHACC_DIR)/nhac_lnhreg.c \
	$(NHACC_DIR)/nhac_lnhcb.c \
	$(NHACC_DIR)/nhac_lnhhdl.c \
	$(NHACC_DIR)/nhac_lnhutl.c \
	$(NHACC_DIR)/nhac_nhureg.c \
	$(NHACC_DIR)/nhac_nhucb.c \
	$(NHACC_DIR)/nhac_nhuhdl.c \
	$(NHACC_DIR)/nhac_nhuutl.c \
	$(NHACC_DIR)/nhac_db.c \
	$(NHACC_DIR)/nhac_rg_ex_ms.c \
	$(NHACC_DIR)/nhac_kw_ex_ms.c \
	$(NHACC_DIR)/nhac_nx_ex_ms.c \
	$(NHACC_DIR)/nhac_lr_ex_ms.c \
	$(NHACC_DIR)/nhac_pj_ex_ms.c \
	$(NHACC_DIR)/nhac_tf_ex_ms.c \
	$(NHACC_DIR)/nhac_prof.c \
	$(NHACC_DIR)/nhac_ex_ms.c \
	$(NHACC_DIR)/nhac_tst.c \
	$(NHACC_DIR)/nhac_flag.c \
	$(NHACC_DIR)/nhac_asn_pk.c \
	$(NHACC_DIR)/nhac_asn_unpk.c \
	$(NH_SAMPLE_DIR)/pj_ptui.c \
	$(NH_SAMPLE_DIR)/rg_ptui.c \
	$(NH_SAMPLE_DIR)/kw_ptui.c \
	$(NH_SAMPLE_DIR)/tf_ptui.c \
	$(NH_SAMPLE_DIR)/nx_ptli.c 

   #$(NH_SAMPLE_DIR)/nx_ex_ms.c \
#----------------------------------------- acceptance test objects
NHAC_OBJS = \
	$(SY_DIR)/cm_xta_tmr.$(OBJ) \
	$(SY_DIR)/cm_xta_txn.$(OBJ) \
	$(SY_DIR)/cm_xta_res.$(OBJ) \
	$(SY_DIR)/cm_xta_queue.$(OBJ) \
	$(SY_DIR)/cm_xta_master.$(OBJ) \
	$(SY_DIR)/cm_xta_reg.$(OBJ) \
	$(SY_DIR)/cm_xta_tst.$(OBJ) \
	$(SY_DIR)/cm_xta_log.$(OBJ) \
	$(SY_DIR)/cm_xta_ipc.$(OBJ) \
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
	$(SY_DIR)/cm_xta_tafsm.$(OBJ) \
	$(SY_DIR)/cm_xta_slave.$(OBJ) \
	$(SY_DIR)/nhac_kwureg.$(OBJ)\
	$(SY_DIR)/nhac_kwucb.$(OBJ)\
	$(SY_DIR)/nhac_kwuhdl.$(OBJ)\
	$(SY_DIR)/nhac_kwuutl_r9.$(OBJ)\
	$(SY_DIR)/nhac_kwuutl_r11.$(OBJ)\
	$(SY_DIR)/nhac_kw_ex_ms.$(OBJ)\
	$(SY_DIR)/nhac_nx_ex_ms.$(OBJ)\
	$(SY_DIR)/nhac_lr_ex_ms.$(OBJ)\
	$(SY_DIR)/nhac_ckwreg.$(OBJ)\
	$(SY_DIR)/nhac_ckwcb.$(OBJ)\
	$(SY_DIR)/nhac_ckwhdl.$(OBJ)\
	$(SY_DIR)/nhac_ckwutl.$(OBJ)\
	$(SY_DIR)/nhac_crgreg.$(OBJ)\
	$(SY_DIR)/nhac_crgcb.$(OBJ)\
	$(SY_DIR)/nhac_crghdl.$(OBJ)\
	$(SY_DIR)/nhac_crgutl.$(OBJ)\
	$(SY_DIR)/nhac_ctfreg.$(OBJ)\
	$(SY_DIR)/nhac_ctfcb.$(OBJ) \
	$(SY_DIR)/nhac_ctfhdl.$(OBJ) \
	$(SY_DIR)/nhac_ctfutl.$(OBJ) \
	$(SY_DIR)/nhac_tf_ex_ms.$(OBJ) \
	$(SY_DIR)/nhac_rg_ex_ms.$(OBJ)\
	$(SY_DIR)/nhac_lnhreg.$(OBJ)\
	$(SY_DIR)/nhac_lnhcb.$(OBJ)\
	$(SY_DIR)/nhac_lnhhdl.$(OBJ)\
	$(SY_DIR)/nhac_lnhutl.$(OBJ)\
	$(SY_DIR)/nhac_nhureg.$(OBJ)\
	$(SY_DIR)/nhac_nhucb.$(OBJ)\
	$(SY_DIR)/nhac_nhuhdl.$(OBJ)\
	$(SY_DIR)/nhac_nhuutl.$(OBJ)\
	$(SY_DIR)/nhac_db.$(OBJ)\
	$(SY_DIR)/nhac_cpjreg.$(OBJ)\
	$(SY_DIR)/nhac_cpjcb.$(OBJ)\
	$(SY_DIR)/nhac_cpjhdl.$(OBJ)\
	$(SY_DIR)/nhac_cpjutl.$(OBJ)\
	$(SY_DIR)/nhac_pjureg.$(OBJ)\
	$(SY_DIR)/nhac_pjucb.$(OBJ)\
	$(SY_DIR)/nhac_pjuhdl.$(OBJ)\
	$(SY_DIR)/nhac_pjuutl_r9.$(OBJ)\
	$(SY_DIR)/nhac_pjuutl_r11.$(OBJ)\
	$(SY_DIR)/nhac_pj_ex_ms.$(OBJ)\
	$(SY_DIR)/nhac_prof.$(OBJ) \
	$(SY_DIR)/nhac_ex_ms.$(OBJ) \
	$(SY_DIR)/nhac_tst.$(OBJ) \
	$(SY_DIR)/nhac_flag.$(OBJ) \
	$(SY_DIR)/nhac_asn_pk.$(OBJ) \
	$(SY_DIR)/nhac_asn_unpk.$(OBJ) \
	$(SY_DIR)/pj_ptui.$(OBJ) \
	$(SY_DIR)/kw_ptui.$(OBJ) \
	$(SY_DIR)/rg_ptui.$(OBJ) \
	$(SY_DIR)/tf_ptui.$(OBJ) \
	$(SY_DIR)/nx_ptli.$(OBJ) 


#NHAC source for VX wroks compilation
NHACCM_SRCS=\
    	$(CM_DIR)/cm_xta_slave.c \
	$(CM_DIR)/cm_xta_reg.c \
	$(CM_DIR)/cm_xta_ipc.c \
#	$(NHACC_DIR)/nhac_prof.c \
#	$(NHACC_DIR)/nhac_tst.c

NHACCM_OBJS=\
    	$(SY_DIR)/cm_xta_slave.$(OBJ) \
	$(SY_DIR)/cm_xta_reg.$(OBJ) \
	$(SY_DIR)/cm_xta_ipc.$(OBJ) \
#	$(SY_DIR)/nhac_prof.$(OBJ) \
#	$(SY_DIR)/nhac_tst.$(OBJ)

#---------------RL parent source
RL_SRCS=$(RL_DIR)/rl_rlog.c $(RL_DIR)/rl_common.c

#---------------RL OBJECTS
RL_OBJS=$(SY_DIR)/rl_rlog.$(OBJ) $(SY_DIR)/rl_common.$(OBJ)

#----------------------------------------- rrc parent source
NI_SRCS= \
	$(NI_DIR)/ni_brm.c         \
	$(NI_DIR)/ni_dbm.c         \
	$(NI_DIR)/ni_ccm.c         \
	$(NI_DIR)/ni_cgm.c         \
	$(NI_DIR)/ni_cpm.c          \
	$(NI_DIR)/ni_db.c         \
	$(NI_DIR)/ni_edm.c         \
	$(NI_DIR)/ni_lim.c         \
	$(NI_DIR)/ni_lmm.c         \
	$(NI_DIR)/ni_pim.c         \
	$(NI_DIR)/ni_rhm.c         \
	$(NI_DIR)/ni_rtm.c         \
	$(NI_DIR)/ni_uim.c         \
	$(NI_DIR)/ni_utl.c         \
	$(NI_DIR)/ni_id.c          \
	$(NI_DIR)/ni_init.c          \
	$(NI_DIR)/ni_ptli.c        \
	$(NI_DIR)/ni_ptmi.c        \
	$(NI_DIR)/ni_ptui.c        

NI_SRCS1= \
	$(NI_DIR)/ni_ex_ms.c




#----------------------------------------- rrc objects
NI_OBJS= \
	$(NI_DIR)/ni_brm.$(OBJ)         \
	$(NI_DIR)/ni_dbm.$(OBJ)         \
	$(NI_DIR)/ni_ccm.$(OBJ)         \
	$(NI_DIR)/ni_cgm.$(OBJ)         \
	$(NI_DIR)/ni_cpm.$(OBJ)          \
	$(NI_DIR)/ni_db.$(OBJ)         \
	$(NI_DIR)/ni_edm.$(OBJ)         \
	$(NI_DIR)/ni_lmm.$(OBJ)         \
	$(NI_DIR)/ni_rhm.$(OBJ)         \
	$(NI_DIR)/ni_rtm.$(OBJ)         \
	$(NI_DIR)/ni_uim.$(OBJ)         \
	$(NI_DIR)/ni_utl.$(OBJ)         \
	$(NI_DIR)/ni_id.$(OBJ)         \
	$(NI_DIR)/ni_init.$(OBJ)         \
	$(NI_DIR)/ni_ptli.$(OBJ)          \
	$(NI_DIR)/ni_ptmi.$(OBJ)          \
	$(NI_DIR)/ni_ptui.$(OBJ)        \
	$(NI_DIR)/ni_lim.$(OBJ)        \
	$(NI_DIR)/ni_pim.$(OBJ)


NI_OBJS1= \
	$(SY_DIR)/ni_ex_ms.$(OBJ) 

#----------------------------------------- rrc  source
NH_SRCS= \
	$(NH_DIR)/nh_brm.c         \
	$(NH_DIR)/nh_dbm.c         \
	$(NH_DIR)/nh_ccm.c         \
	$(NH_DIR)/nh_cgm.c         \
	$(NH_DIR)/nh_cpm.c         \
	$(NH_DIR)/nh_db.c          \
	$(NH_DIR)/nh_3gdb.c        \
	$(NH_DIR)/nh_edm.c         \
	$(NH_DIR)/nh_lim.c         \
	$(NH_DIR)/nh_lmm.c         \
	$(NH_DIR)/nh_pim.c         \
	$(NH_DIR)/nh_rhm.c         \
	$(NH_DIR)/nh_rtm.c         \
	$(NH_DIR)/nh_uim.c         \
	$(NH_DIR)/nh_utl.c         \
	$(NH_DIR)/nh_id.c          \
	$(NH_DIR)/nh_init.c         \
	$(NH_DIR)/nh_ptli.c        \
	$(NH_DIR)/nh_ptmi.c        \
	$(NH_DIR)/nh_ptui.c        

NH_SRCS1= \
	$(NH_DIR)/nh_ex_ms.c




#----------------------------------------- rrc objects
NH_OBJS= \
	$(SY_DIR)/nh_brm.$(OBJ)         \
	$(SY_DIR)/nh_dbm.$(OBJ)         \
	$(SY_DIR)/nh_ccm.$(OBJ)         \
	$(SY_DIR)/nh_cgm.$(OBJ)         \
	$(SY_DIR)/nh_cpm.$(OBJ)         \
	$(SY_DIR)/nh_db.$(OBJ)          \
	$(SY_DIR)/nh_3gdb.$(OBJ)        \
	$(SY_DIR)/nh_edm.$(OBJ)         \
	$(SY_DIR)/nh_lmm.$(OBJ)         \
	$(SY_DIR)/nh_rhm.$(OBJ)         \
	$(SY_DIR)/nh_rtm.$(OBJ)         \
	$(SY_DIR)/nh_uim.$(OBJ)         \
	$(SY_DIR)/nh_utl.$(OBJ)         \
	$(SY_DIR)/nh_id.$(OBJ)          \
	$(SY_DIR)/nh_init.$(OBJ)         \
	$(SY_DIR)/nh_ptli.$(OBJ)        \
	$(SY_DIR)/nh_ptmi.$(OBJ)        \
	$(SY_DIR)/nh_ptui.$(OBJ)        \
	$(SY_DIR)/nh_lim.$(OBJ)        \
	$(SY_DIR)/nh_pim.$(OBJ)         

NH_OBJS1= \
	$(SY_DIR)/nh_ex_ms.$(OBJ) 

#----------------------------------------- common source
NHCM_SRCS= \
	$(CM_DIR)/nhu.c     \
	$(CM_DIR)/lnh.c     \
	$(CM_DIR)/cm_bdy5.c \
	$(CM_DIR)/cm_gen.c  \
	$(CM_DIR)/cm_tkns.c     \
	$(CM_DIR)/cm_lib.c  \
	$(CM_DIR)/cm_hash.c \
	$(CM_DIR)/cm_mblk.c \
	$(CM_DIR)/cm_inet.c \
	$(CM_DIR)/cm_llist.c  \
	$(CM_DIR)/cm_pasn1.c  \
	$(CM_DIR)/cm_pasn2.c  \
	$(CM_DIR)/cm_pasn3.c  \
	$(CM_DIR)/cm_pasn4.c  \
	$(CM_DIR)/ckw.c \
	$(CM_DIR)/crg.c \
	$(CM_DIR)/cpj.c \
	$(CM_DIR)/pju.c \
	$(CM_DIR)/nhu_pk.c \
	$(CM_DIR)/nhu_3gpk.c \
	$(CM_DIR)/nhu_unpk.c \
	$(CM_DIR)/nhu_3gunpk.c \
	$(CM_DIR)/cm_lte.c \
	$(CM_DIR)/kwu.c \
	$(CM_DIR)/ctf.c

#----------------------------------------- common headers
NHCMH_SRCS= \
	$(CM_DIR)/cm5.h     \
	$(CM_DIR)/cm5.x     \
	$(CM_DIR)/cm_err.h  \
	$(CM_DIR)/cm_lib.x  \
	$(CM_DIR)/envopt.h  \
	$(CM_DIR)/envdep.h  \
	$(CM_DIR)/envind.h  \
	$(CM_DIR)/gen.h     \
	$(CM_DIR)/gen.x     \
	$(CM_DIR)/cm_lte.x  \
	$(CM_DIR)/cm_lte.h  \
	$(CM_DIR)/lnh.h     \
	$(CM_DIR)/lnh.x     \
	$(CM_DIR)/kwu.h     \
	$(CM_DIR)/kwu.x     \
	$(CM_DIR)/ckw.h     \
	$(CM_DIR)/ckw.x     \
	$(CM_DIR)/crg.h     \
	$(CM_DIR)/crg.x     \
	$(CM_DIR)/cpj.h     \
	$(CM_DIR)/cpj.x     \
	$(CM_DIR)/pju.h     \
	$(CM_DIR)/pju.x     \
	$(CM_DIR)/ctf.h     \
	$(CM_DIR)/ctf.x     \
	$(CM_DIR)/ssi.h     \
	$(CM_DIR)/ssi.x

#----------------------------------------- common object
NHCM_OBJS=\
	$(SY_DIR)/lnh.$(OBJ)     \
	$(SY_DIR)/cm_tkns.$(OBJ)   \
	$(SY_DIR)/cm_bdy5.$(OBJ) \
	$(SY_DIR)/cm_gen.$(OBJ) \
	$(SY_DIR)/cm_lib.$(OBJ) \
	$(SY_DIR)/cm_hash.$(OBJ) \
	$(SY_DIR)/cm_mblk.$(OBJ) \
	$(SY_DIR)/cm_inet.$(OBJ) \
	$(SY_DIR)/cm_llist.$(OBJ) \
	$(SY_DIR)/cm_pasn1.$(OBJ)  \
	$(SY_DIR)/cm_pasn2.$(OBJ)  \
	$(SY_DIR)/cm_pasn3.$(OBJ)  \
	$(SY_DIR)/cm_pasn4.$(OBJ)  \
	$(SY_DIR)/cpj.$(OBJ) \
	$(SY_DIR)/pju.$(OBJ) \
	$(SY_DIR)/nhu_pk.$(OBJ) \
	$(SY_DIR)/nhu_3gpk.$(OBJ) \
	$(SY_DIR)/nhu.$(OBJ) \
	$(SY_DIR)/nhu_unpk.$(OBJ) \
	$(SY_DIR)/nhu_3gunpk.$(OBJ) \
	$(SY_DIR)/cm_lte.$(OBJ) \
	$(SY_DIR)/ckw.$(OBJ) \
   $(SY_DIR)/kwu.$(OBJ) \
	$(SY_DIR)/crg.$(OBJ) \
	$(SY_DIR)/ctf.$(OBJ)

#----------------------------------------- common stack manager source
SM_SRCS=\
	$(SM_DIR)/sm_bdy1.c \
	$(SM_DIR)/sm_ex_ms.c 

#----------------------------------------- common stack manager objects
SM_OBJS= \
	$(SY_DIR)/sm_bdy1.$(OBJ) \
	$(SY_DIR)/sm_ex_ms.$(OBJ) 

#----------------------------------------- product stack manager source
NHSM_SRCS= \
	$(NH_SAMPLE_DIR)/smnhptmi.c 

#----------------------------------------- product stack manager objects
NHSM_OBJS= \
	$(SY_DIR)/smnhptmi.$(OBJ) 

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
MT_SRCS= \
        $(MT_DIR)/mt_ss.c \
        $(MT_DIR)/mt_id.c \
        $(CM_DIR)/cm_mem.c

# OS - mtss objects-------------------------------------------------------
MT_OBJS= \
        $(SY_DIR)/mt_ss.$(OBJ) \
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
	$(NH_DIR)/nh_tst.c   \
	$(NH_DIR)/nh_ex_pt.c   \
	$(CM_DIR)/ss_ptsp.c

#----------------------------------------- portable build objects
PT_OBJS= \
	$(SY_DIR)/nh_tst.$(OBJ)   \
	$(SY_DIR)/nh_ex_pt.$(OBJ)   \
	$(SY_DIR)/ss_ptsp.$(OBJ)


#----------------------------------------- all acceptance test source
#replace MT_SRCS with VW_SRCS if using vx works or NT_SRCS if using windows NT
#replace  NHAC_SRCS  with NHACCM_SRCS if using vx works 
PRDACC_SRCS= \
	$(NH_SRCS)    \
	$(NH_SRCS1)    \
	$(NHAC_SRCS) \
	$(NHCM_SRCS)  \
	$(SM_SRCS)    \
	$(NHSM_SRCS)  \
	$(RL_SRCS)    \
	$(SS_SRCS)   \
	$(MT_SRCS)
#	$(NT_SRCS)
#	$(VW_SRCS)


#----------------------------------------- all acceptance test objects
#replace MT_OBJS with VW_OBJS if using vx works or NT_OBJS if using windows NT
#replace  NHAC_OBJS  with NHACCM_OBJS if using vx works 
PRDACC_OBJS= \
	$(NH_OBJS)    \
	$(NHAC_OBJS) \
	$(NHCM_OBJS)  \
	$(SM_OBJS)  \
	$(NHSM_OBJS)  \
	$(NH_OBJS1)    \
	$(SS_OBJS) \
	$(RL_OBJS)    \
	$(MT_OBJS)  
#	$(VW_OBJS)
#	$(NS_OBJS)
#	$(NHACCM_OBJS)
# 
#----------------------------------------- all acceptance test source
#replace MT_SRCS with VW_SRCS if using vx works or NT_SRCS if using windows NT
#replace  NHAC_SRCS  with NHACCM_SRCS if using vx works 
PRDINT_SRCS= \
	$(NI_SRCS)    \
	$(NI_SRCS1)    \
	$(NHAC_SRCS) \
	$(NHCM_SRCS)  \
	$(SM_SRCS)    \
	$(NHSM_SRCS)  \
	$(SS_SRCS)   \
	$(MT_SRCS)
#	$(NHACCM_SRCS)
#	$(MT_SRCS)
#	$(NT_SRCS)
#	$(VW_SRCS)


#----------------------------------------- all acceptance test objects
#replace MT_OBJS with VW_OBJS if using vx works or NT_OBJS if using windows NT
#replace NHAC_OBJS  with NHACCM_OBJS if using vx works 
PRDINT_OBJS= \
	$(NI_OBJS)    \
	$(NHAC_OBJS) \
	$(SM_OBJS)  \
	$(NHSM_OBJS)  \
	$(NI_OBJS1)    \
	$(NHCM_OBJS)  \
	$(SS_OBJS) \
	$(MT_OBJS)  \
#	$(VW_OBJS)
#	$(NS_OBJS)
#	$(NHACCM_OBJS)

#----------------------------------------- all portable source
PRDPT_SRCS= \
	$(NH_SRCS) \
	$(PT_SRCS) \
	$(NHCM_SRCS)

#----------------------------------------- all portable objects
PRDPT_OBJS= \
	$(NH_OBJS) \
	$(PT_OBJS) \
	$(NHCM_OBJS)

#----------------------------------------- Klocwork analysis objects
PRDKW_OBJS= \
	$(NH_OBJS) \
	$(PT_OBJS) 

# all library sources--------------------------------------------------
PRDLIB_SRCS=  $(NH_DIR)/nh_ex_ms.c $(NH_SRCS) 

# all library objects--------------------------------------------------
PRDLIB_OBJS= $(SY_DIR)/nh_ex_ms.$(OBJ)  $(NH_OBJS)


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
	@$(MAKE) -f $(MAKENAME) $(MAKEPT) -e ENV=$(SOLENV) CC=$(SOLCC)  \
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
	LD=$(LNXLD) COPTS=$(LNXCOPTS)  LIBS=$(LNXLDLIBS) \
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
	@$(MAKE) -f $(MAKENAME) $(MAKEACC) -e ENV=$(LNXENV) CC=$(PURCC) \
	LD=$(PURLD) COPTS=$(LNXCOPTS) LOPTS=$(LNXLOPTS) LIBS=$(LNXLIBS) \
	OBJ=$(SOL_OBJ_SUFFIX) 

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
	OBJ=$(MS_OBJ_SUFFIX)
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
	OBJ=$(SOL_OBJ_SUFFIX) OS_DIR=$(VW_DIR)
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
# SECTION 9


#---------------------------- RRC objects ---------------------------


$(SY_DIR)/nh_brm.$(OBJ): $(NH_DIR)/nh_brm.c $(CMP_INC) $(NHP_INC)  
	$(CC) -c $(CPRDOPTS)  $(NH_DIR)/nh_brm.c

$(SY_DIR)/nh_ccm.$(OBJ): $(NH_DIR)/nh_ccm.c $(CMP_INC) $(NHP_INC)  
	$(CC) -c $(CPRDOPTS)  $(NH_DIR)/nh_ccm.c

$(SY_DIR)/nh_cgm.$(OBJ): $(NH_DIR)/nh_cgm.c $(CMP_INC) $(NHP_INC) 
	$(CC) -c $(CPRDOPTS)  $(NH_DIR)/nh_cgm.c

$(SY_DIR)/nh_cpm.$(OBJ): $(NH_DIR)/nh_cpm.c $(CMP_INC) $(NHP_INC)  
	$(CC) -c $(CPRDOPTS)  $(NH_DIR)/nh_cpm.c

$(SY_DIR)/nh_db.$(OBJ): $(NH_DIR)/nh_db.c $(CMP_INC) $(NHP_INC) 
	$(CC) -c $(CPRDOPTS)  $(NH_DIR)/nh_db.c

$(SY_DIR)/nh_dbm.$(OBJ): $(NH_DIR)/nh_dbm.c $(CMP_INC) $(NHP_INC)
	$(CC) -c $(CPRDOPTS)  $(NH_DIR)/nh_dbm.c

$(SY_DIR)/nh_3gdb.$(OBJ): $(NH_DIR)/nh_3gdb.c $(CMP_INC) $(NHP_INC) 
	$(CC) -c $(CPRDOPTS)  $(NH_DIR)/nh_3gdb.c

$(SY_DIR)/nh_edm.$(OBJ): $(NH_DIR)/nh_edm.c $(CMP_INC) $(NHP_INC) 
	$(CC) -c $(CPRDOPTS)  $(NH_DIR)/nh_edm.c

$(SY_DIR)/nh_lim.$(OBJ): $(NH_DIR)/nh_lim.c $(CMP_INC) $(NHALL_INC) 
	$(CC) -c $(CPRDOPTS)  $(NH_DIR)/nh_lim.c

$(SY_DIR)/nh_lmm.$(OBJ): $(NH_DIR)/nh_lmm.c $(CMP_INC) $(NHP_INC) 
	$(CC) -c $(CPRDOPTS)  $(NH_DIR)/nh_lmm.c

$(SY_DIR)/nh_pim.$(OBJ): $(NH_DIR)/nh_pim.c $(CMP_INC) $(NHALL_INC) 
	$(CC) -c $(CPRDOPTS)  $(NH_DIR)/nh_pim.c

$(SY_DIR)/nh_rhm.$(OBJ): $(NH_DIR)/nh_rhm.c $(CMP_INC) $(NHP_INC) 
	$(CC) -c $(CPRDOPTS)  $(NH_DIR)/nh_rhm.c

$(SY_DIR)/nh_rtm.$(OBJ): $(NH_DIR)/nh_rtm.c $(CMP_INC) $(NHP_INC) 
	$(CC) -c $(CPRDOPTS)  $(NH_DIR)/nh_rtm.c

$(SY_DIR)/nh_uim.$(OBJ): $(NH_DIR)/nh_uim.c $(CMP_INC) $(NHP_INC)  
	$(CC) -c $(CPRDOPTS)  $(NH_DIR)/nh_uim.c

$(SY_DIR)/nh_utl.$(OBJ): $(NH_DIR)/nh_utl.c $(CMP_INC) $(NHALL_INC) 
	$(CC) -c $(CPRDOPTS)  $(NH_DIR)/nh_utl.c

$(SY_DIR)/nh_ptmi.$(OBJ): $(NH_DIR)/nh_ptmi.c $(CMP_INC) $(NHP_INC)  
	$(CC) -c $(CPRDOPTS)  $(NH_DIR)/nh_ptmi.c

$(SY_DIR)/nh_ptui.$(OBJ): $(NH_DIR)/nh_ptui.c $(CMP_INC) $(NHP_INC) 
	$(CC) -c $(CPRDOPTS)  $(NH_DIR)/nh_ptui.c

$(SY_DIR)/nh_ptli.$(OBJ): $(NH_DIR)/nh_ptli.c $(CMP_INC) $(NHALL_INC) 
	$(CC) -c $(CPRDOPTS) $(NH_DIR)/nh_ptli.c

$(SY_DIR)/nh_id.$(OBJ): $(NH_DIR)/nh_id.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS) $(NH_DIR)/nh_id.c

$(SY_DIR)/nh_init.$(OBJ): $(NH_DIR)/nh_init.c $(CMP_INC) $(NHP_INC)  
	$(CC) -c $(CPRDOPTS)  $(NH_DIR)/nh_init.c

$(SY_DIR)/nh_ex_ms.$(OBJ): $(NH_DIR)/nh_ex_ms.c $(CMP_INC) $(NHALL_INC)  
	$(CC) -c $(CPRDOPTS) $(NH_DIR)/nh_ex_ms.c
#---------------------------- RRC Parent objects ---------------------------


$(SY_DIR)/ni_brm.$(OBJ): $(NI_DIR)/ni_brm.c $(CMP_INC) $(NHP_INC)  
	$(CC) -c $(CPRDOPTS)  $(NI_DIR)/ni_brm.c

$(SY_DIR)/ni_ccm.$(OBJ): $(NI_DIR)/ni_ccm.c $(CMP_INC) $(NHP_INC)  
	$(CC) -c $(CPRDOPTS)  $(NI_DIR)/ni_ccm.c

$(SY_DIR)/ni_cgm.$(OBJ): $(NI_DIR)/ni_cgm.c $(CMP_INC) $(NHP_INC)  
	$(CC) -c $(CPRDOPTS)  $(NI_DIR)/ni_cgm.c

$(SY_DIR)/ni_cpm.$(OBJ): $(NI_DIR)/ni_cpm.c $(CMP_INC) $(NHP_INC) 
	$(CC) -c $(CPRDOPTS)  $(NI_DIR)/ni_cpm.c

$(SY_DIR)/ni_db.$(OBJ): $(NI_DIR)/ni_db.c $(CMP_INC) $(NHP_INC)  
	$(CC) -c $(CPRDOPTS)  $(NI_DIR)/ni_db.c

$(SY_DIR)/ni_dbm.$(OBJ): $(NI_DIR)/ni_dbm.c $(CMP_INC) $(NHP_INC)  
	$(CC) -c $(CPRDOPTS)  $(NI_DIR)/ni_dbm.c

$(SY_DIR)/ni_edm.$(OBJ): $(NI_DIR)/ni_edm.c $(CMP_INC) $(NHP_INC)  
	$(CC) -c $(CPRDOPTS)  $(NI_DIR)/ni_edm.c

$(SY_DIR)/ni_lim.$(OBJ): $(NI_DIR)/ni_lim.c $(CMP_INC) $(NHALL_INC)  
	$(CC) -c $(CPRDOPTS)  $(NI_DIR)/ni_lim.c

$(SY_DIR)/ni_lmm.$(OBJ): $(NI_DIR)/ni_lmm.c $(CMP_INC) $(NHP_INC) 
	$(CC) -c $(CPRDOPTS)  $(NI_DIR)/ni_lmm.c

$(SY_DIR)/ni_pim.$(OBJ): $(NI_DIR)/ni_pim.c $(CMP_INC) $(NHALL_INC)  
	$(CC) -c $(CPRDOPTS)  $(NI_DIR)/ni_pim.c

$(SY_DIR)/ni_rhm.$(OBJ): $(NI_DIR)/ni_rhm.c $(CMP_INC) $(NHP_INC)  
	$(CC) -c $(CPRDOPTS)  $(NI_DIR)/ni_rhm.c

$(SY_DIR)/ni_rtm.$(OBJ): $(NI_DIR)/ni_rtm.c $(CMP_INC) $(NHP_INC)  
	$(CC) -c $(CPRDOPTS)  $(NI_DIR)/ni_rtm.c

$(SY_DIR)/ni_uim.$(OBJ): $(NI_DIR)/ni_uim.c $(CMP_INC) $(NHP_INC) 
	$(CC) -c $(CPRDOPTS)  $(NI_DIR)/ni_uim.c

$(SY_DIR)/ni_utl.$(OBJ): $(NI_DIR)/ni_utl.c $(CMP_INC) $(NHALL_INC) 
	$(CC) -c $(CPRDOPTS)  $(NI_DIR)/ni_utl.c

$(SY_DIR)/ni_id.$(OBJ): $(NI_DIR)/ni_id.c $(SYS_INC) $(CM_INC)  
	$(CC) -c $(CPRDOPTS)  $(NI_DIR)/ni_id.c

$(SY_DIR)/ni_init.$(OBJ): $(NI_DIR)/ni_init.c $(CMP_INC) $(NHP_INC)  
	$(CC) -c $(CPRDOPTS)  $(NI_DIR)/ni_init.c

$(SY_DIR)/ni_ptmi.$(OBJ): $(NI_DIR)/ni_ptmi.c $(CMP_INC) $(NHP_INC)  
	$(CC) -c $(CPRDOPTS)  $(NI_DIR)/ni_ptmi.c

$(SY_DIR)/ni_ptui.$(OBJ): $(NI_DIR)/ni_ptui.c $(CMP_INC) $(NHP_INC) 
	$(CC) -c $(CPRDOPTS)  $(NI_DIR)/ni_ptui.c

$(SY_DIR)/ni_ptli.$(OBJ): $(NI_DIR)/ni_ptli.c $(CMP_INC) $(NHALL_INC)  
	$(CC) -c $(CPRDOPTS) $(NI_DIR)/ni_ptli.c

$(SY_DIR)/ni_ex_ms.$(OBJ): $(NI_DIR)/ni_ex_ms.c $(CMP_INC) $(NHALL_INC)  
	$(CC) -c $(CPRDOPTS) $(NI_DIR)/ni_ex_ms.c
#----------------------------------------- acceptance test objects

$(SY_DIR)/cm_xta_ex_ms.$(OBJ): $(NHACC_DIR)/cm_xta_ex_ms.c $(SYS_INC) 
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/cm_xta_ex_ms.c -o $(SY_DIR)/cm_xta_ex_ms.$(OBJ)

$(SY_DIR)/cm_xta_xml.$(OBJ): $(NHACC_DIR)/cm_xta_xml.c $(SYS_INC) 
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/cm_xta_xml.c -o $(SY_DIR)/cm_xta_xml.$(OBJ)

$(SY_DIR)/cm_xta_ldfsm.$(OBJ): $(NHACC_DIR)/cm_xta_ldfsm.c $(SYS_INC) 
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/cm_xta_ldfsm.c -o $(SY_DIR)/cm_xta_ldfsm.$(OBJ)

$(SY_DIR)/cm_xta_tcfsm.$(OBJ): $(NHACC_DIR)/cm_xta_tcfsm.c $(SYS_INC) 
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/cm_xta_tcfsm.c -o $(SY_DIR)/cm_xta_tcfsm.$(OBJ)

$(SY_DIR)/cm_xta_tgfsm.$(OBJ): $(NHACC_DIR)/cm_xta_tgfsm.c $(SYS_INC) 
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/cm_xta_tgfsm.c -o $(SY_DIR)/cm_xta_tgfsm.$(OBJ)

$(SY_DIR)/cm_xta_tafsm.$(OBJ): $(NHACC_DIR)/cm_xta_tafsm.c $(SYS_INC) 
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/cm_xta_tafsm.c -o $(SY_DIR)/cm_xta_tafsm.$(OBJ)

$(SY_DIR)/cm_xta_py.$(OBJ): $(NHACC_DIR)/cm_xta_py.c $(SYS_INC) 
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/cm_xta_py.c -o $(SY_DIR)/cm_xta_py.$(OBJ)

$(SY_DIR)/cm_xta_inthdl.$(OBJ): $(NHACC_DIR)/cm_xta_inthdl.c $(SYS_INC) 
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/cm_xta_inthdl.c -o $(SY_DIR)/cm_xta_inthdl.$(OBJ)

$(SY_DIR)/cm_xta_intreg.$(OBJ): $(NHACC_DIR)/cm_xta_intreg.c $(SYS_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/cm_xta_intreg.c -o $(SY_DIR)/cm_xta_intreg.$(OBJ)

$(SY_DIR)/cm_xta_res.$(OBJ): $(NHACC_DIR)/cm_xta_res.c $(SYS_INC) 
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/cm_xta_res.c -o $(SY_DIR)/cm_xta_res.$(OBJ)

$(SY_DIR)/cm_xta_queue.$(OBJ): $(NHACC_DIR)/cm_xta_queue.c $(SYS_INC) 
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/cm_xta_queue.c -o $(SY_DIR)/cm_xta_queue.$(OBJ)

$(SY_DIR)/cm_xta_flag.$(OBJ): $(NHACC_DIR)/cm_xta_flag.c $(SYS_INC) 
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/cm_xta_flag.c -o $(SY_DIR)/cm_xta_flag.$(OBJ)

$(SY_DIR)/cm_xta_log.$(OBJ): $(NHACC_DIR)/cm_xta_log.c $(SYS_INC) 
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/cm_xta_log.c -o $(SY_DIR)/cm_xta_log.$(OBJ)

$(SY_DIR)/cm_xta_slave.$(OBJ): $(NHACC_DIR)/cm_xta_slave.c $(SYS_INC) 
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/cm_xta_slave.c -o $(SY_DIR)/cm_xta_slave.$(OBJ)

$(SY_DIR)/cm_xta_master.$(OBJ): $(NHACC_DIR)/cm_xta_master.c $(SYS_INC) 
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/cm_xta_master.c -o $(SY_DIR)/cm_xta_master.$(OBJ)

$(SY_DIR)/cm_xta_reg.$(OBJ): $(NHACC_DIR)/cm_xta_reg.c $(SYS_INC) 
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/cm_xta_reg.c -o $(SY_DIR)/cm_xta_reg.$(OBJ)

$(SY_DIR)/cm_xta_tst.$(OBJ): $(NHACC_DIR)/cm_xta_tst.c $(SYS_INC) 
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/cm_xta_tst.c -o $(SY_DIR)/cm_xta_tst.$(OBJ)

$(SY_DIR)/cm_xta_ipc.$(OBJ): $(NHACC_DIR)/cm_xta_ipc.c $(SYS_INC) 
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/cm_xta_ipc.c -o $(SY_DIR)/cm_xta_ipc.$(OBJ)

$(SY_DIR)/cm_xta_txn.$(OBJ): $(NHACC_DIR)/cm_xta_txn.c $(SYS_INC) 
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/cm_xta_txn.c -o $(SY_DIR)/cm_xta_txn.$(OBJ)

$(SY_DIR)/cm_xta_intutl.$(OBJ): $(NHACC_DIR)/cm_xta_intutl.c $(SYS_INC) 
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/cm_xta_intutl.c -o $(SY_DIR)/cm_xta_intutl.$(OBJ)

$(SY_DIR)/cm_xta_tmr.$(OBJ): $(NHACC_DIR)/cm_xta_tmr.c $(SYS_INC) 
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/cm_xta_tmr.c -o $(SY_DIR)/cm_xta_tmr.$(OBJ)

$(SY_DIR)/nhu_pk.$(OBJ): $(CM_DIR)/nhu_pk.c $(SYS_INC) 
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/nhu_pk.c -I./cmxta/  -I./header/ -o $(SY_DIR)/nhu_pk.$(OBJ)

$(SY_DIR)/nhac_asn_pk.$(OBJ): $(NHACC_DIR)/nhac_asn_pk.c $(SYS_INC) 
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_asn_pk.c -I./cmxta/  -I./header/ -o $(SY_DIR)/nhac_asn_pk.$(OBJ)

$(SY_DIR)/nhu_3gpk.$(OBJ): $(CM_DIR)/nhu_3gpk.c $(SYS_INC) 
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/nhu_3gpk.c -I./cmxta/  -I./header/ -o $(SY_DIR)/nhu_3gpk.$(OBJ)

$(SY_DIR)/nhu_unpk.$(OBJ): $(CM_DIR)/nhu_unpk.c $(SYS_INC) 
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/nhu_unpk.c -I./cmxta/  -I./header/ -o $(SY_DIR)/nhu_unpk.$(OBJ)

$(SY_DIR)/nhu_3gunpk.$(OBJ): $(CM_DIR)/nhu_3gunpk.c $(SYS_INC) 
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/nhu_3gunpk.c -I./cmxta/  -I./header/ -o $(SY_DIR)/nhu_3gunpk.$(OBJ)

$(SY_DIR)/nhac_asn_unpk.$(OBJ): $(NHACC_DIR)/nhac_asn_unpk.c $(SYS_INC) 
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_asn_unpk.c -I./cmxta/  -I./header/ -o $(SY_DIR)/nhac_asn_unpk.$(OBJ)

$(SY_DIR)/cm_lte.$(OBJ): $(CM_DIR)/cm_lte.c $(SYS_INC) 
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_lte.c -I./cmxta/  -I./header/ -o $(SY_DIR)/cm_lte.$(OBJ)

$(SY_DIR)/kw_ptui.$(OBJ): $(NH_SAMPLE_DIR)/kw_ptui.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NH_SAMPLE_DIR)/kw_ptui.c -I./cmxta/  -I./header/ -o $(SY_DIR)/kw_ptui.$(OBJ)

$(SY_DIR)/rg_ptui.$(OBJ): $(NH_SAMPLE_DIR)/rg_ptui.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NH_SAMPLE_DIR)/rg_ptui.c -I./cmxta/  -I./header/ -o $(SY_DIR)/rg_ptui.$(OBJ)

$(SY_DIR)/tf_ptui.$(OBJ): $(NH_SAMPLE_DIR)/tf_ptui.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NH_SAMPLE_DIR)/tf_ptui.c -I./cmxta/  -I./header/ -o $(SY_DIR)/tf_ptui.$(OBJ)

$(SY_DIR)/nx_ptli.$(OBJ): $(NH_SAMPLE_DIR)/nx_ptli.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NH_SAMPLE_DIR)/nx_ptli.c -I./cmxta/  -I./header/ -o $(SY_DIR)/nx_ptli.$(OBJ)


#Starting with kwu interface
$(SY_DIR)/nhac_kwuhdl.$(OBJ): $(NHACC_DIR)/nhac_kwuhdl.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_kwuhdl.c -I./cmxta/  -I./header/ -o $(SY_DIR)/nhac_kwuhdl.$(OBJ)

$(SY_DIR)/nhac_kwureg.$(OBJ): $(NHACC_DIR)/nhac_kwureg.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_kwureg.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_kwureg.$(OBJ)

$(SY_DIR)/nhac_kwucb.$(OBJ): $(NHACC_DIR)/nhac_kwucb.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_kwucb.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_kwucb.$(OBJ)

$(SY_DIR)/nhac_kwuutl_r9.$(OBJ): $(NHACC_DIR)/nhac_kwuutl_r9.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_kwuutl_r9.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_kwuutl_r9.$(OBJ)

$(SY_DIR)/nhac_kwuutl_r11.$(OBJ): $(NHACC_DIR)/nhac_kwuutl_r11.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_kwuutl_r11.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_kwuutl_r11.$(OBJ)

#ckw Interface Rules

$(SY_DIR)/nhac_ckwreg.$(OBJ): $(NHACC_DIR)/nhac_ckwreg.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_ckwreg.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_ckwreg.$(OBJ)

$(SY_DIR)/nhac_ckwcb.$(OBJ): $(NHACC_DIR)/nhac_ckwcb.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_ckwcb.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_ckwcb.$(OBJ)

$(SY_DIR)/nhac_ckwhdl.$(OBJ): $(NHACC_DIR)/nhac_ckwhdl.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_ckwhdl.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_ckwhdl.$(OBJ)

$(SY_DIR)/nhac_ckwutl.$(OBJ): $(NHACC_DIR)/nhac_ckwutl.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_ckwutl.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_ckwutl.$(OBJ)

$(SY_DIR)/nhac_kw_ex_ms.$(OBJ): $(NHACC_DIR)/nhac_kw_ex_ms.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_kw_ex_ms.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_kw_ex_ms.$(OBJ)


#crg Interface
$(SY_DIR)/nhac_crgreg.$(OBJ): $(NHACC_DIR)/nhac_crgreg.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_crgreg.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_crgreg.$(OBJ)

$(SY_DIR)/nhac_crgcb.$(OBJ): $(NHACC_DIR)/nhac_crgcb.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_crgcb.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_crgcb.$(OBJ)

$(SY_DIR)/nhac_crghdl.$(OBJ): $(NHACC_DIR)/nhac_crghdl.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_crghdl.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_crghdl.$(OBJ)

$(SY_DIR)/nhac_crgutl.$(OBJ): $(NHACC_DIR)/nhac_crgutl.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_crgutl.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_crgutl.$(OBJ)

$(SY_DIR)/nhac_rg_ex_ms.$(OBJ): $(NHACC_DIR)/nhac_rg_ex_ms.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_rg_ex_ms.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_rg_ex_ms.$(OBJ)

#ctf Interface
$(SY_DIR)/nhac_ctfreg.$(OBJ): $(NHACC_DIR)/nhac_ctfreg.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_ctfreg.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_ctfreg.$(OBJ)

$(SY_DIR)/nhac_ctfcb.$(OBJ): $(NHACC_DIR)/nhac_ctfcb.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_ctfcb.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_ctfcb.$(OBJ)

$(SY_DIR)/nhac_ctfhdl.$(OBJ): $(NHACC_DIR)/nhac_ctfhdl.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_ctfhdl.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_ctfhdl.$(OBJ)

$(SY_DIR)/nhac_ctfutl.$(OBJ): $(NHACC_DIR)/nhac_ctfutl.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_ctfutl.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_ctfutl.$(OBJ)

$(SY_DIR)/nhac_tf_ex_ms.$(OBJ): $(NHACC_DIR)/nhac_tf_ex_ms.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_tf_ex_ms.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_tf_ex_ms.$(OBJ)

#pju Interface
$(SY_DIR)/nhac_pjureg.$(OBJ): $(NHACC_DIR)/nhac_pjureg.c $(SYS_INC) $(NHACCALL_INC) 
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_pjureg.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_pjureg.$(OBJ)

$(SY_DIR)/nhac_pjucb.$(OBJ): $(NHACC_DIR)/nhac_pjucb.c $(SYS_INC) $(NHACCALL_INC) 
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_pjucb.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_pjucb.$(OBJ)

$(SY_DIR)/nhac_pjuhdl.$(OBJ): $(NHACC_DIR)/nhac_pjuhdl.c $(SYS_INC) $(NHACCALL_INC) 
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_pjuhdl.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_pjuhdl.$(OBJ)

$(SY_DIR)/nhac_pjuutl_r9.$(OBJ): $(NHACC_DIR)/nhac_pjuutl_r9.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_pjuutl_r9.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_pjuutl_r9.$(OBJ)

$(SY_DIR)/nhac_pjuutl_r11.$(OBJ): $(NHACC_DIR)/nhac_pjuutl_r11.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_pjuutl_r11.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_pjuutl_r11.$(OBJ)
#cpj Interface
$(SY_DIR)/nhac_cpjreg.$(OBJ): $(NHACC_DIR)/nhac_cpjreg.c $(SYS_INC) $(NHACCALL_INC) 
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_cpjreg.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_cpjreg.$(OBJ)

$(SY_DIR)/nhac_cpjcb.$(OBJ): $(NHACC_DIR)/nhac_cpjcb.c $(SYS_INC) $(NHACCALL_INC) 
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_cpjcb.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_cpjcb.$(OBJ)

$(SY_DIR)/nhac_cpjhdl.$(OBJ): $(NHACC_DIR)/nhac_cpjhdl.c $(SYS_INC) $(NHACCALL_INC) 
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_cpjhdl.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_cpjhdl.$(OBJ)

$(SY_DIR)/nhac_cpjutl.$(OBJ): $(NHACC_DIR)/nhac_cpjutl.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_cpjutl.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_cpjutl.$(OBJ)

$(SY_DIR)/pj_ptui.$(OBJ): $(NH_SAMPLE_DIR)/pj_ptui.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NH_SAMPLE_DIR)/pj_ptui.c -I./cmxta/ -I./header/ -o $(SY_DIR)/pj_ptui.$(OBJ)

$(SY_DIR)/nhac_pj_ex_ms.$(OBJ): $(NHACC_DIR)/nhac_pj_ex_ms.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_pj_ex_ms.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_pj_ex_ms.$(OBJ)



#lnh Interface
$(SY_DIR)/nhac_lnhreg.$(OBJ): $(NHACC_DIR)/nhac_lnhreg.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_lnhreg.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_lnhreg.$(OBJ)

$(SY_DIR)/nhac_lnhcb.$(OBJ): $(NHACC_DIR)/nhac_lnhcb.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_lnhcb.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_lnhcb.$(OBJ)

$(SY_DIR)/nhac_lnhhdl.$(OBJ): $(NHACC_DIR)/nhac_lnhhdl.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_lnhhdl.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_lnhhdl.$(OBJ)

$(SY_DIR)/nhac_lnhutl.$(OBJ): $(NHACC_DIR)/nhac_lnhutl.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_lnhutl.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_lnhutl.$(OBJ)

$(SY_DIR)/nhac_lr_ex_ms.$(OBJ): $(NHACC_DIR)/nhac_lr_ex_ms.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_lr_ex_ms.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_lr_ex_ms.$(OBJ)


#nhu Interface
$(SY_DIR)/nhac_nhureg.$(OBJ): $(NHACC_DIR)/nhac_nhureg.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_nhureg.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_nhureg.$(OBJ)

$(SY_DIR)/nhac_nhucb.$(OBJ): $(NHACC_DIR)/nhac_nhucb.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_nhucb.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_nhucb.$(OBJ)

$(SY_DIR)/nhac_nhuhdl.$(OBJ): $(NHACC_DIR)/nhac_nhuhdl.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_nhuhdl.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_nhuhdl.$(OBJ)

$(SY_DIR)/nhac_nhuutl.$(OBJ): $(NHACC_DIR)/nhac_nhuutl.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_nhuutl.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_nhuutl.$(OBJ)

$(SY_DIR)/nhac_db.$(OBJ): $(NHACC_DIR)/nhac_db.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_db.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_db.$(OBJ)

$(SY_DIR)/nhac_nx_ex_ms.$(OBJ): $(NHACC_DIR)/nhac_nx_ex_ms.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_nx_ex_ms.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_nx_ex_ms.$(OBJ)

$(SY_DIR)/nhac_nh_ex_ms.$(OBJ): $(NHACC_DIR)/nhac_nh_ex_ms.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_nh_ex_ms.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_nh_ex_ms.$(OBJ)


#Some utility functions
$(SY_DIR)/nhac_prof.$(OBJ): $(NHACC_DIR)/nhac_prof.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_prof.c -o $(SY_DIR)/nhac_prof.$(OBJ)

$(SY_DIR)/nhac_ex_ms.$(OBJ): $(NHACC_DIR)/nhac_ex_ms.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_ex_ms.c -o $(SY_DIR)/nhac_ex_ms.$(OBJ)

#RRCAC Tst function
$(SY_DIR)/nhac_tst.$(OBJ): $(NHACC_DIR)/nhac_tst.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_tst.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_tst.$(OBJ)
	
#finally FLAG function
$(SY_DIR)/nhac_flag.$(OBJ): $(NHACC_DIR)/nhac_flag.c $(SYS_INC) $(NHACCALL_INC)
	$(CC) -c $(CPRDOPTS) $(NHACC_DIR)/nhac_flag.c -I./cmxta/ -I./header/ -o $(SY_DIR)/nhac_flag.$(OBJ)

#----------------------------------------- RRC Lower layer objects
#Include files for all the lower layers
$(SY_DIR)/ll_ptui.$(OBJ): $(NH_SAMPLE_DIR)/ll_ptui.c $(SYS_INC) $(CM_INC) $(NHACCALL_INC) 
	$(CC) -c $(CPRDOPTS)  $(NH_SAMPLE_DIR)/ll_ptui.c

$(SY_DIR)/layer2.$(OBJ):  $(NH_SAMPLE_DIR)/layer2.c $(SYS_INC) $(CM_INC) $(NHACCALL_INC) 
	$(CC) -c $(CPRDOPTS)  $(NH_SAMPLE_DIR)/layer2.c

$(SY_DIR)/l2_ex_ms.$(OBJ): $(NH_SAMPLE_DIR)/l2_ex_ms.c $(SYS_INC) $(CM_INC) $(NHACCALL_INC) 
	$(CC) -c $(CPRDOPTS)   $(NH_SAMPLE_DIR)/l2_ex_ms.c

#----------------------------------------- RRC User  objects

$(SY_DIR)/l4_ptli.$(OBJ): $(NHU_DIR)/l4_ptli.c $(SYS_INC) $(CM_INC) $(NHACCALL_INC) 
	$(CC) -c $(CPRDOPTS)  $(NHU_DIR)/l4_ptli.c

$(SY_DIR)/layer4.$(OBJ):  $(NHU_DIR)/layer4.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(NHU_DIR)/layer4.c

$(SY_DIR)/l4_ex_ms.$(OBJ): $(NHU_DIR)/l4_ex_ms.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)   $(NHU_DIR)/l4_ex_ms.c

#----------------------------------------- common objects

$(SY_DIR)/kwu.$(OBJ): $(CM_DIR)/kwu.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/kwu.c

$(SY_DIR)/ckw.$(OBJ): $(CM_DIR)/ckw.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/ckw.c

$(SY_DIR)/crg.$(OBJ): $(CM_DIR)/crg.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/crg.c

$(SY_DIR)/cpj.$(OBJ): $(CM_DIR)/cpj.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cpj.c

$(SY_DIR)/ctf.$(OBJ): $(CM_DIR)/ctf.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/ctf.c

$(SY_DIR)/pju.$(OBJ): $(CM_DIR)/pju.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/pju.c

$(SY_DIR)/nhu.$(OBJ): $(CM_DIR)/nhu.c  $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/nhu.c

$(SY_DIR)/lnh.$(OBJ): $(CM_DIR)/lnh.c  $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/lnh.c

$(SY_DIR)/cm_gen.$(OBJ): $(CM_DIR)/cm_gen.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_gen.c

$(SY_DIR)/cm_tkns.$(OBJ): $(CM_DIR)/cm_tkns.c $(SYS_INC) $(LNH_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_tkns.c -o $(SY_DIR)/cm_tkns.$(OBJ)

$(SY_DIR)/cm_ss.$(OBJ): $(CM_DIR)/cm_ss.c  $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_ss.c

$(SY_DIR)/cm_lib.$(OBJ): $(CM_DIR)/cm_lib.c  $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_lib.c

$(SY_DIR)/cm_inet.$(OBJ): $(CM_DIR)/cm_inet.c $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_inet.c -o $(SY_DIR)/cm_inet.$(OBJ)

$(SY_DIR)/cm_hash.$(OBJ): $(CM_DIR)/cm_hash.c  $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_hash.c

$(SY_DIR)/cm_mblk.$(OBJ): $(CM_DIR)/cm_mblk.c  $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_mblk.c

$(SY_DIR)/cm_llist.$(OBJ): $(CM_DIR)/cm_llist.c  $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_llist.c

$(SY_DIR)/cm_pasn1.$(OBJ): $(CM_DIR)/cm_pasn1.c  $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_pasn1.c

$(SY_DIR)/cm_pasn2.$(OBJ): $(CM_DIR)/cm_pasn2.c  $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_pasn2.c

$(SY_DIR)/cm_pasn3.$(OBJ): $(CM_DIR)/cm_pasn3.c  $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_pasn3.c

$(SY_DIR)/cm_pasn4.$(OBJ): $(CM_DIR)/cm_pasn4.c  $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_pasn4.c

$(SY_DIR)/cm_bdy5.$(OBJ): $(CM_DIR)/cm_bdy5.c  $(SYS_INC) $(CM_INC)
	$(CC) -c $(CPRDOPTS) $(CM_DIR)/cm_bdy5.c

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

$(SY_DIR)/sm_bdy1.$(OBJ): $(SM_DIR)/sm_bdy1.c $(SYS_INC) $(LNH_INC)
	$(CC) -c $(CSMOPTS) -DSM $(SM_DIR)/sm_bdy1.c

$(SY_DIR)/sm_ex_ms.$(OBJ): $(SM_DIR)/sm_ex_ms.c $(SYS_INC) $(LNH_INC)
	$(CC) -c $(CSMOPTS) -DSM $(SM_DIR)/sm_ex_ms.c

$(SY_DIR)/smnhptmi.$(OBJ): $(NH_SAMPLE_DIR)/smnhptmi.c $(SYS_INC) $(LNH_INC)
	$(CC) -c $(CPRDOPTS) -DSM $(NH_SAMPLE_DIR)/smnhptmi.c

#----------------------------------------- portable objects

$(SY_DIR)/nh_ex_pt.$(OBJ): $(NH_DIR)/nh_ex_pt.c 
	$(CC) -c $(CPTOPTS) $(NH_DIR)/nh_ex_pt.c

$(SY_DIR)/nh_tst.$(OBJ): $(NH_DIR)/nh_tst.c 
	$(CC) -c $(CPTOPTS) $(NH_DIR)/nh_tst.c

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

#---------------------------- RL objects ---------------------------

$(SY_DIR)/rl_rlog.$(OBJ): $(RL_DIR)/rl_rlog.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS) $(RL_DIR)/rl_rlog.c

$(SY_DIR)/rl_common.$(OBJ): $(RL_DIR)/rl_common.c $(SYS_INC) $(CM_INC) 
	$(CC) -c $(CPRDOPTS)  $(RL_DIR)/rl_common.c


#
#********************************************************************30**
#  
#        End of file:     nh.mak@@/main/3 - Fri Jul  1 01:13:11 2011
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
#  /main/1    ---     vk   1. LTE RRC Initial Release.
#  /main/2    ---   vkulkarni   1. LTE RRC Release 2.1
#  /main/3    ---   hsingh   1. LTE RRC Release 3.1
#********************************************************************91*/

# DO NOT DELETE THIS LINE -- make depend depends on it.

