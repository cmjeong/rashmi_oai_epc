#!/bin/bash


if [ ! -z ${VERBOSE} ]; then
   set -x
fi


C_DIR=`pwd`
mkdir -p .build

MARCH=`getconf LONG_BIT`
MACHINE=BIT$MARCH
ARCH=$MARCH

cd mme
make -f vb.mak BLDENV=lnx_acc  clean MACHINE=$MACHINE
cd ../sgw
make -f qo.mak BLDENV=lnx_acc  clean MACHINE=$MACHINE
cd ../pgw
make -f av.mak BLDENV=lnx_acc  clean MACHINE=$MACHINE
cd ..

