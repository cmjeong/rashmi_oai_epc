#
#       Name:   LTE eNodeB Sample Application
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
#
#               BUILD TARGETS:
#
#               clean            remove all object files
#   
#       File:  stack.mak
#
#
#       Prg:   an
#
#********************************************************************21*/
#=======================================================================

STOPTS=-DENB 

Q=
S=
# Check for verbose build
ifneq ($(V),1)
    Q:=@
    S:=-s
endif
export Q
export S

# With the assumption that the make command is run from the directory
# where the makefile is located, PWD fetches the build directory and
# all other directories are generated using the build directory.
BUILD_DIR=$(PWD)
ROOT_DIR_BRCM =$(patsubst %/build/brcm,%,$(BUILD_DIR))
ROOT_DIR_INTEL =$(patsubst %/build/intel,%,$(BUILD_DIR))
ROOT_DIR_PAL =$(patsubst %/build/pal,%,$(BUILD_DIR))
COM_BUILD_DIR=$(BUILD_DIR)/common
export BUILD_DIR
export ROOT_DIR_BRCM
export ROOT_DIR_INTEL
export COM_BUILD_DIR

# Path where the .o files or the directories with .o files are located
OBJ_ROOT =$(BUILD_DIR)/obj
export OBJ_ROOT
# Path where the binary logging related files are generated
LOG_ROOT  =$(BUILD_DIR)/logdb
export LOG_ROOT
# Path where the libraries are created
LIB_ROOT =$(BUILD_DIR)/lib
export LIB_ROOT
# Path for the common files that are used across multiple layers
CM_DIR   =$(ROOT_DIR)/src/cm
export CM_DIR
# Path where the final binaries are created
BIN_DIR  =$(BUILD_DIR)/build/obj
export BIN_DIR
# Path where the libraries are packaged and these are used when not built from source
EXT_LIB_DIR  =$(ROOT_DIR)/lib
export EXT_LIB_DIR
ifeq (${TEXT_LOG}, YES)
BIN_LOG = NO
CMENBE2EOPTS += $(RLOG_OPTS_TEXT)
else
BIN_LOG = YES
CMENBE2EOPTS += $(RLOG_OPTS_BIN)
endif
export BIN_LOG

WATCHDOG_DIR = $(ROOT_DIR)/src/watchdog
export WATCHDOG_DIR

ifneq ($(wildcard $(ROOT_DIR)/src/tenb_commonplatform/software), )
OAM_SRC=NO
endif

L_OPTS = -lrt -lm -lpthread -lstdc++ -L $(LIB_ROOT)

L_OAM += -L./oamlibs/ -lsm  -lRadisys-mib-common -lthreeway-comms \
   -lthreeway-messaging -ldl -lthreeway-mobnet -lthreeway-system
