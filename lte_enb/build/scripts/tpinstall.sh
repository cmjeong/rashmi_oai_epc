CROSS_COMPILER=$1
PROCESS=$2
#********verifying compiler input********
if [ "$1" = "arm-none-linux-gnueabi" ] || [ "$1" = "x86_64-linux-gnu" ] || [ "$1" = "gcc" ] || [ "$1" = "mipsel-unknown-linux-gnu" ] ;
then
echo "************************************************"
echo "Compiler Selected : $CROSS_COMPILER"
echo "************************************************"

#********Eondeb directory path***********
ENB_INSTALL_DIR=$PWD/../../

#********Thirdparty directory path**********
THIRDPARTY_DIR=$ENB_INSTALL_DIR/src/tenb_commonplatform/software/thirdparty/

#************** Necessary packages needed for 64 bit machine *********
if [ "$1" = "x86_64-linux-gnu" ];
then
sudo apt-get install xsltproc
sudo apt-get install dos2unix
sudo apt-get install libboost-all-dev
sudo apt-get install w3c-dtd-xhtml
sudo apt-get install autoconf
fi

if [ "$2" != "comp" ] ;
then
#********removing Thirdparty directory if already there******
rm -rf $THIRDPARTY_DIR

#********Creating Thirdparty directory******
mkdir -p $THIRDPARTY_DIR
mkdir -p $THIRDPARTY_DIR/md5
mkdir -p $THIRDPARTY_DIR/kb_getc/
mkdir -p $THIRDPARTY_DIR/origopenssl/
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/generic
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-3-5
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-4
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/generic/i686-linux
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/generic/i686-linux/bin
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/generic/i686-linux/include
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/generic/i686-linux/lib
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/generic/i686-linux/share
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/generic/i686-linux/include/libcsoap-1.1
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/generic/i686-linux/include/nanohttp-1.1
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/generic/i686-linux/include/libcsoap-1.1/libcsoap
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/generic/i686-linux/include/nanohttp-1.1/nanohttp
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/generic/i686-linux/share/aclocal
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-3-5/bfin-uclinux-2008
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-3-5/bfin-uclinux-2008-mf
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-3-5/bfin-uclinux-2008/bin
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-3-5/bfin-uclinux-2008/lib
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-3-5/bfin-uclinux-2008/include
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-3-5/bfin-uclinux-2008/share
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-3-5/bfin-uclinux-2008/include/libcsoap-1.1
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-3-5/bfin-uclinux-2008/include/nanohttp-1.1
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-3-5/bfin-uclinux-2008/include/libcsoap-1.1/libcsoap
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-3-5/bfin-uclinux-2008/include/nanohttp-1.1/nanohttp
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-3-5/bfin-uclinux-2008/share/aclocal
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-3-5/bfin-uclinux-2008-mf/bin
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-3-5/bfin-uclinux-2008-mf/lib
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-3-5/bfin-uclinux-2008-mf/include
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-3-5/bfin-uclinux-2008-mf/share
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-3-5/bfin-uclinux-2008-mf/include/libcsoap-1.1
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-3-5/bfin-uclinux-2008-mf/include/nanohttp-1.1
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-3-5/bfin-uclinux-2008-mf/include/libcsoap-1.1/libcsoap
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-3-5/bfin-uclinux-2008-mf/include/nanohttp-1.1/nanohttp
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-3-5/bfin-uclinux-2008-mf/share/aclocal
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-4/arm-none-linux-gnueabi
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-4/mipsel-unknown-linux-gnu
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-4/arm-none-linux-gnueabi/bin
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-4/arm-none-linux-gnueabi/lib
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-4/arm-none-linux-gnueabi/include
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-4/arm-none-linux-gnueabi/share
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-4/arm-none-linux-gnueabi/include/libcsoap-1.1
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-4/arm-none-linux-gnueabi/include/nanohttp-1.1
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-4/arm-none-linux-gnueabi/include/libcsoap-1.1/libcsoap
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-4/arm-none-linux-gnueabi/include/nanohttp-1.1/nanohttp
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-4/arm-none-linux-gnueabi/share/aclocal
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-4/x86_64-linux-gnu
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-4/x86_64-linux-gnu/bin
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-4/x86_64-linux-gnu/lib
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-4/x86_64-linux-gnu/include
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-4/x86_64-linux-gnu/share
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-4/x86_64-linux-gnu/include/libcsoap-1.1
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-4/x86_64-linux-gnu/include/nanohttp-1.1
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-4/x86_64-linux-gnu/include/libcsoap-1.1/libcsoap
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-4/x86_64-linux-gnu/include/nanohttp-1.1/nanohttp
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-4/x86_64-linux-gnu/share/aclocal
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-4/mipsel-unknown-linux-gnu/bin
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-4/mipsel-unknown-linux-gnu/lib
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-4/mipsel-unknown-linux-gnu/include
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-4/mipsel-unknown-linux-gnu/share
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-4/mipsel-unknown-linux-gnu/include/libcsoap-1.1
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-4/mipsel-unknown-linux-gnu/include/nanohttp-1.1
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-4/mipsel-unknown-linux-gnu/include/libcsoap-1.1/libcsoap
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-4/mipsel-unknown-linux-gnu/include/nanohttp-1.1/nanohttp
mkdir -p $THIRDPARTY_DIR/../libs/bin/csoap/hbs2-4/mipsel-unknown-linux-gnu/share/aclocal
chmod -R 0777 $THIRDPARTY_DIR/../libs/bin/csoap/*

#Set the compiler path in PATH environment variable:
source setVar.sh

#######################  DOWNLOADING AND EXTRACTION #################################

#**************** AUTOCONF ***************#
cd $THIRDPARTY_DIR
wget http://ftp.gnu.org/gnu/autoconf/autoconf-latest.tar.gz
tar --touch -zxvf autoconf-latest.tar.gz
rm -f autoconf-latest.tar.gz

cp -rf $ENB_INSTALL_DIR/src/tenb_commonplatform/scripts/compilation_scripts/configs_autoconf/configscript_autoconf $THIRDPARTY_DIR/autoconf*/

cd $THIRDPARTY_DIR/autoconf*

dos2unix configscript_autoconf
rm -f d2u*

#**************** MD5 ***************#

cd  $THIRDPARTY_DIR/md5/

wget --no-check-certificate http://www.opensource.apple.com/source/xnu/xnu-1456.1.26/libkern/crypto/md5.c?txt
mv  md5.c?txt md5.c
wget --no-check-certificate http://www.opensource.apple.com/source/xnu/xnu-1456.1.26/libkern/libkern/crypto/md5.h?txt
mv md5.h?txt md5.h

cp $ENB_INSTALL_DIR/src/tenb_commonplatform/scripts/compilation_scripts/md5/makefile $THIRDPARTY_DIR/md5/.

find -exec dos2unix {} \;
rm -f d2u* ; rm -f `find . -name d2u*`

cd $THIRDPARTY_DIR/md5
patch -p1 -i $ENB_INSTALL_DIR/src/tenb_commonplatform/scripts/oam_patch/md5.patch
#sed -i '/\#define MD5_H/a\#include<stdint.h>' md5.h
#sed -i 's/u_char/uint8_t/g' md5.h

#**************** kb_getc ***************#

cd $THIRDPARTY_DIR/kb_getc/

wget --no-check-certificate https://gerardvw.home.xs4all.nl/HOME/src/kbhit.c 
sleep 5
mv kbhit.c kb_getc.c

wget --no-check-certificate https://raw.githubusercontent.com/gt-ros-pkg/hrl-lib/master/hrl_lib/include/hrl_lib/kbhit.h 
sleep 5
mv kbhit.h kb_getc.h

#wget http://scimp.googlecode.com/svn/trunk/src/kb_getc.c
#sleep 5
#wget http://scimp.googlecode.com/svn/trunk/include/kb_getc.h 

dos2unix kb_getc*
rm -f d2u* ;

patch -p1 -i $ENB_INSTALL_DIR/src/tenb_commonplatform/scripts/oam_patch/kb_getc.patch

cp -rf $ENB_INSTALL_DIR/src/tenb_commonplatform/scripts/compilation_scripts/kb_getc/makefile $THIRDPARTY_DIR/kb_getc/


#**************** libxml ***************#

cd $THIRDPARTY_DIR

wget   http://xmlsoft.org/sources/libxml2-2.7.2.tar.gz
tar --touch -zxvf libxml2-2.7.2.tar.gz
rm -f libxml2-2.7.2.tar.gz
cp -rf $ENB_INSTALL_DIR/src/tenb_commonplatform/scripts/compilation_scripts/configs_libxml2/configscript_libxml2 $THIRDPARTY_DIR/libxml2-2.7.2/

cd  $THIRDPARTY_DIR/libxml2-2.7.2/

find -exec dos2unix {} \;
rm -f d2u* ; rm -f `find . -name d2u*`

wget http://www.openssl.org/source/openssl-1.0.1l.tar.gz

cp -rf openssl-1.0.1l.tar.gz  $THIRDPARTY_DIR/origopenssl/


#**************** openssl ***************#
cd  $THIRDPARTY_DIR

wget --no-check-certificate  http://www.openssl.org/source/openssl-1.0.1l.tar.gz

cp -rf openssl-1.0.1l.tar.gz  $THIRDPARTY_DIR/origopenssl/

cd  $THIRDPARTY_DIR/origopenssl/

tar --touch -zxvf openssl-1.0.1l.tar.gz

mv openssl-1.0.1l/* .

cp -rf  $ENB_INSTALL_DIR/src/tenb_commonplatform/scripts/compilation_scripts/configs_openssl/configscript_openssl  $THIRDPARTY_DIR/origopenssl/

#Execute the following command to go to /origopenssl directory:
cd  $THIRDPARTY_DIR/origopenssl/

find -exec dos2unix {} \;
rm -f d2u* ; rm -f `find . -name d2u*`

#**************** csoap ***************#

cd $THIRDPARTY_DIR

wget --no-check-certificate http://prdownloads.sourceforge.net/csoap/libsoap-1.1.0.tar.gz
tar --touch -zxvf libsoap-1.1.0.tar.gz

mv libsoap-1.1.0 $THIRDPARTY_DIR/csoap/

cp -rf $ENB_INSTALL_DIR/src/tenb_commonplatform/scripts/compilation_scripts/configs_csoap/*  $THIRDPARTY_DIR/csoap/

cd  $THIRDPARTY_DIR/csoap/
find -exec dos2unix {} \;
rm -f d2u* ; rm -f `find . -name d2u*`

#Applying csoap patch
patch -p1 -i $ENB_INSTALL_DIR/src/tenb_commonplatform/scripts/oam_patch/csoap.patch


if [ "$1" != "x86_64-linux-gnu" ];
then
#**************** boost ***************#

cd $THIRDPARTY_DIR
wget --no-check-certificate  http://sourceforge.net/projects/boost/files/boost/1.52.0/boost_1_52_0.tar.gz

tar --touch -zxvf boost_1_52_0.tar.gz

mkdir -p  $ENB_INSTALL_DIR/src/tenb_commonplatform//software/libs/common/include/boost

cp -rf boost_1_52_0/boost/*  $ENB_INSTALL_DIR/src/tenb_commonplatform/software/libs/common/include/boost/

cd $ENB_INSTALL_DIR/src/tenb_commonplatform/software/libs/common/include/boost/

find -exec dos2unix {} \;
rm -f d2u* ; rm -f `find . -name d2u*`

fi

##########################  COMPILATION #################################
else
echo "**********************************************************************"
echo "only compilation so no extraction"
echo "**********************************************************************"
fi
if [ "$2" != "ext" ] ;
then
echo "**********************************************************************"
echo "Compilation"
echo "**********************************************************************"
#**************** Autoconf ***************#

cd $THIRDPARTY_DIR/autoconf*

./configscript_autoconf $CROSS_COMPILER

#**************** libxml ***************#

cd  $THIRDPARTY_DIR/libxml2-2.7.2/

./configscript_libxml2 $CROSS_COMPILER

#**************** openssl ***************#

cd  $THIRDPARTY_DIR/origopenssl/

./configscript_openssl $CROSS_COMPILER

#**************** csoap ***************#

cd  $THIRDPARTY_DIR/csoap

./configscript_csoap_1 $CROSS_COMPILER

sed -i '39,39s/HAVE_MALLOC.*0/HAVE_MALLOC 1/' $THIRDPARTY_DIR/csoap/config.h
sed -i 's/^\(.*malloc.*rpl_malloc.*$\)/\/\*\1\/\//g' $THIRDPARTY_DIR/csoap/config.h

./configscript_csoap_build

./configscript_csoap_2 $CROSS_COMPILER

sed -i '39,39s/HAVE_MALLOC.*0/HAVE_MALLOC 1/' $THIRDPARTY_DIR/csoap/config.h
sed -i 's/^\(.*malloc.*rpl_malloc.*$\)/\/\*\1\/\//g' $THIRDPARTY_DIR/csoap/config.h

./configscript_csoap_build

#**************** openssl ***************#

cd  $THIRDPARTY_DIR/origopenssl/

./configscript_openssl $CROSS_COMPILER

###########################################################################
else
echo "**********************************************************************"
echo "only extraction selected so no compilation"
echo "**********************************************************************"
fi
else
echo "**********************************************************************"
echo "Invalid compiler option Plese select valid compiler options from below"
echo "arm-none-linux-gnueabi"
echo "mipsel-unknown-linux-gnu"
echo "x86_64-linux-gnu"
echo "gcc"
echo "**********************************************************************"
fi
