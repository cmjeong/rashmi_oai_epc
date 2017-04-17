###############################################################################
# 
#  Note:- This script should be run in the target machine board
#         please run install.sh before running start_TeNB.sh
#  Usage : source ./start_TeNB.sh
#                 (OR)
#          . ./start_TeNB.sh
#
###############################################################################
logger "RADISYS:Inside start_TeNB.sh"
FILENAME="start_TeNB.sh"
BANKPATH=$PWD/../..
PST_OFC='post-office'

CONFIGPATH=/mnt/tmp 
MOD_CONFIG_PATH=`echo "$CONFIGPATH" | sed s/\\\//\\\\\\\\\\\\//g`

#cd ../bin/
#./l1.sh &
#sleep 15
#cd -

logger "RADISYS:$FILENAME:OAM Processes are coming up..."

date -s "2015-01-01 11:11:11"

cd $BANKPATH/rsys/bin

logger "RADISYS:$FILENAME:Running post-office"
./post-office $CONFIGPATH &

if ps ax | grep -v grep | grep $PST_OFC > /dev/null
then
    logger "RADISYS:$FILENAME:$PST_OFC is running"
else
    logger "RADISYS:$FILENAME:$PST_OFC is not running"
    return
fi
sleep 2
#./watchdogd 5 15 &

logger "RADISYS:$FILENAME:Running oam"
./oam  $CONFIGPATH&

sleep 5
cp -f $CONFIGPATH/configFile configFile.sh
chmod 0777 configFile.sh

cp -f $CONFIGPATH/tipAddObjFile addObj.sh
chmod 0777 addObj.sh

logger "RADISYS:$FILENAME:Running tr069-v2"
./tr069-v2 $CONFIGPATH &

sed -i '/OAM_CONFIG_FILES_DIR/d' configFile.sh
sed -i '/OAM_LOGGING_DIR/d' configFile.sh
sed -i '/OAM_NV_DIR_PATH/d' configFile.sh
sed -i '/LD_LIBRARY_PATH/d' configFile.sh
sed -i '/STRONGSWAN/d' configFile.sh
sed -i '/OAM_TAG_LOG_FILE_NAME/d' configFile.sh
sed -i '/OAM_ETHERNET_INTERFACE/d' configFile.sh
sed -i '/MANAGEMENT/d' configFile.sh
sed -i 's/\"/\\\"/g' configFile.sh
sed -i 's/^/printf \"\%s\\nq\" \"oam.set /' configFile.sh
sed -i 's/$/\" \| tee \/dev\/tty \| \.\/cli CONFIG_PATH \-c/' configFile.sh
sed -i 's/oam.set tr69.add/tr69.add/g' configFile.sh
sed -i "s/CONFIG_PATH/$MOD_CONFIG_PATH/g" configFile.sh
./configFile.sh
rm -f configFile.sh

sleep 5
sed -i 's/^/printf \"\%s\\nq\" \"/' addObj.sh 
sed -i 's/$/\" \| tee \/dev\/tty \| \.\/cli CONFIG_PATH \-c/' addObj.sh
./addObj.sh
rm -rf addObj.sh


logger "RADISYS:$FILENAME:Running ftp-func"
./fileTransMgr $CONFIGPATH &
logger "RADISYS:$FILENAME:All configFile configuration applied successfully."

logger "RADISYS:$FILENAME:Running tenpin"
./tenpin $CONFIGPATH &

./enodeb_l3 -c $CONFIGPATH/configFile
#cd $BANKPATH/rsys/scripts
#logger "RADISYS:$FILENAME:enodeb will be up after configuration complete and if ADMIN state is unlocked.."
#./start_eNB.sh $CONFIGPATH/configFile  $BANKPATH
#sleep 5
#logger "RADISYS:$FILENAME:Running rem"
#./start_rem.sh
