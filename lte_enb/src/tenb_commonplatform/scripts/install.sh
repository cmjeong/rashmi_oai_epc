##########################################################################################################
# 
#  Note:- This script should be run in <curbank>/rsys/scripts folder in the target machine
#         board
#
#  Usage:  . ./setup_TeNB
#  Example: . ./setup_TeNB 
#
##########################################################################################################

#DO NOT delete the .
logger "RADISYS:Inside install.sh"
FILENAME="install.sh"
CONFIG_PATH="/mnt"
OAM_CONFIG_FILES_DIR=../setup
OAM_NV_DIR_PATH=../config

chmod 0755 ../scripts/*
mkdir -p $OAM_CONFIG_FILES_DIR
mkdir -p $OAM_CONFIG_FILES_DIR/trace/ 
mkdir -p $OAM_CONFIG_FILES_DIR/dbx 
mkdir -p $OAM_CONFIG_FILES_DIR/config
mkdir -p $OAM_CONFIG_FILES_DIR/bank-active/config/
mkdir -p $OAM_CONFIG_FILES_DIR/tmp
mkdir -p $CONFIG_PATH
mkdir -p $CONFIG_PATH/tmp
mkdir -p $CONFIG_PATH/log
mkdir -p $CONFIG_PATH/bank-active
mkdir -p $CONFIG_PATH/bank-active/config

chmod 0777 $CONFIG_PATH
chmod 0777 $CONFIG_PATH/log
chmod 0777 $CONFIG_PATH/bank-active
chmod 0777 $CONFIG_PATH/bank-active/config

cd ../config
chmod 0777 $OAM_NV_DIR_PATH/*

cp -f ./nas-system-configuration $CONFIG_PATH/bank-active/config/.
cp -f ../scripts/reboot-fap $OAM_CONFIG_FILES_DIR/config/.
dos2unix $OAM_CONFIG_FILES_DIR/config/reboot-fap

if [ -e $OAM_CONFIG_FILES_DIR/config/mib-home-fap.nv ]
 then
     logger "RADISYS:$FILENAME:mib-home-fap.nv already Exists hence Skip copying default"
 else
     cp -f $OAM_NV_DIR_PATH/mib-home-fap.nv $OAM_CONFIG_FILES_DIR/config
fi

if [ -e $OAM_CONFIG_FILES_DIR/config/param-attribute.nv ]
 then
     logger "RADISYS:$FILENAME:param-attribute.nv already Exists hence Skip copying default"
 else
     cp -f ./param-attribute.nv $OAM_CONFIG_FILES_DIR/config
fi

cp -f ./developer $OAM_CONFIG_FILES_DIR/config

cp -f ./configFile          $CONFIG_PATH/tmp/
cp -f ../scripts/ftpput.sh  $CONFIG_PATH/tmp
cp -f ../scripts/ftpputLog.sh  $CONFIG_PATH/tmp
cp -f ../scripts/ftpget.sh  $CONFIG_PATH/tmp
cp -f ../scripts/upgrade.sh $CONFIG_PATH/tmp/
cp -f ../config/software-release $CONFIG_PATH/bank-active/config/

cd ../bin
chmod -R 0777 ../config/wr_cfg.txt
chmod -R 0777 ../config/ys_cfg.txt

ln -sf  ../config/wr_cfg.txt  wr_cfg.txt
ln -sf  ../config/ys_cfg.txt  ys_cfg.txt

if [ -f ../lib/libc.so.6 ]
then
rm  ../lib/libc.so.6
fi
chmod 0755 ../bin/*
chmod 0755 $OAM_NV_DIR_PATH/*
chmod 0755 ../config/*
chmod 0755 ../lib/*
chmod 0755 $CONFIG_PATH/tmp/ftpput.sh
chmod 0755 $CONFIG_PATH/tmp/ftpputLog.sh
chmod 0755 $CONFIG_PATH/tmp/ftpget.sh
chmod 0755 $CONFIG_PATH/tmp/upgrade.sh
chmod 0755 $CONFIG_PATH/bank-active/config/software-release

chmod 0777 $OAM_CONFIG_FILES_DIR/dbx 
chmod 0777 $OAM_CONFIG_FILES_DIR/config
chmod 0777 $OAM_CONFIG_FILES_DIR/bank-active/config
chmod 0777 $OAM_CONFIG_FILES_DIR/tmp

cd ../lib/
ln -sf libc-2.8.so libc.so.6

cd ../scripts
sed -i "/CONFIGPATH=/c CONFIGPATH=$CONFIG_PATH/tmp "  start_TeNB.sh
logger "RADISYS:$FILENAME:TARGET SETUP COMPLETED"
