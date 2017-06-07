#!/bin/bash

if [ ! -z ${VERBOSE} ]; then
   set -x
fi


C_DIR=`pwd`
mkdir -p .build

MARCH=`getconf LONG_BIT`
MACHINE=BIT$MARCH
ARCH=$MARCH

#build MME and create a softlink in SETUP
echo "[INFO]Build MME"
cd mme
make -f vb.mak BLDENV=lnx_acc COMPILER=GCC MACHINE=$MACHINE  acc -j 5 > ../.build/mme.build.log 2>&1

if [ ! -f $C_DIR/mme/vb_acc ]
then
   echo "[ERROR] MME build failed"
   exit 1
fi
echo "[INFO]MME build complete"
#------------------------------------------------------------

#build SGW and create a softlink in SETUP
echo "[INFO]Build SGW"
cd ../sgw
make -f qo.mak BLDENV=lnx_acc MACHINE=$MACHINE  acc -j 5 > ../.build/sgw.build.log 2>&1
if [ ! -f $C_DIR/sgw/qo_acc ]
then
   echo "[ERROR] SGW build failed"
   exit 1
fi
echo "[INFO]SGW build complete"
#------------------------------------------------------------

#build PGW and create a softlink in SETUP
echo "[INFO]Build PGW"
cd ../pgw
make -f av.mak BLDENV=lnx_acc MACHINE=$MACHINE  acc -j 5 > ../.build/pgw.build.log 2>&1
if [ ! -f $C_DIR/pgw/av_acc ]
then
   echo "[ERROR] PGW build failed"
   exit 1
fi
echo "[INFO]PGW build complete"
#------------------------------------------------------------

exit 0

