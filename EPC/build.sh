#!/bin/bash

if [ ! -z ${VERBOSE} ]; then
   set -x
fi

helpUsage()
{
   echo -e  >&2 \
   "usage: $0 [-m <32|64>]"
}

MACHINE=BIT64
ARCH=64

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

#build MME and create a softlink in SETUP
echo "[INFO]Build MME"
cd mme
make -f vb.mak BLDENV=lnx_acc COMPILER=GPP MACHINE=$MACHINE  acc -j 5 > ../.build/mme.build.log 2>&1

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

