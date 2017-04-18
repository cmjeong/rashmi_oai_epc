#!/bin/bash


if [ ! -z ${VERBOSE} ]; then
   set -x
fi

helpUsage()
{
   echo -e  >&2 \
   "usage: $0 [-m <32|64>]"
}

MACHINE=BIT32
ARCH=32

while [ $# -gt 0 ]
do
   case "$1" in
      -m) 
      if [ -z $2 ]
      then
         helpUsage
         exit 1
      fi
      if [ $2 == 32 -o $2 == 64 ]
      then
         MACHINE=BIT$2 
         ARCH=$2
      else
         helpUsage
         exit 1
      fi
      shift;;
      -*) helpUsage
      exit 1;;
      *) break;;
   esac
   shift
done

C_DIR=`pwd`
mkdir -p .build

MARCH=`getconf LONG_BIT`

if [ $? -eq 0 ] 
then

   if [ $MARCH != $ARCH ]
   then
      echo "-------------------------------------------------------------------------"
      echo "[WARNING] build machine is $MARCH bit architecture. Build chosen is $ARCH"
      echo "[WARNING] !!!!! Build can fail. !!!!!"
      echo "[WARNING] contact radisys"
      echo "-------------------------------------------------------------------------"
   fi  

fi

cd mme
make -f vb.mak BLDENV=lnx_acc  clean MACHINE=$MACHINE
cd ../sgw
make -f qo.mak BLDENV=lnx_acc  clean MACHINE=$MACHINE
cd ../pgw
make -f av.mak BLDENV=lnx_acc  clean MACHINE=$MACHINE
cd ..

