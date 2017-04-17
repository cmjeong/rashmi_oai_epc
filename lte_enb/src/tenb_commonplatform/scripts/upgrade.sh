#!/bin/bash
logger "RADISYS:Inside Upgrade.sh"
FILENAME="upgrade.sh"
CURBANK=$2/../..
BANK1="/root/bank1"
BANK2="/root/bank2"

if [ "$CURBANK" == "$BANK1/rsys/bin/../.." ]
then
TARGETBANK=$BANK2
else
TARGETBANK=$BANK1
fi
mkdir -p $TARGETBANK
NEWSOFTNAME=$4
FAULTCODE=9010

logger "RADISYS:$FILENAME:CURBANK ::: $CURBANK"
logger "RADISYS:$FILENAME:TARGET PATH ::: $TARGETBANK"
logger "RADISYS:$FILENAME:NEW SOFTWARE NAME ::: $NEWSOFTNAME"

resetTargetBank()
{
   if [ "$CURBANK" == "$BANK1/rsys/bin/../.." ]
   then
      TARGETBANK=$BANK1
   else
      TARGETBANK=$BANK2
         mkdir -p $TARGETBANK
   fi
}

handleError()
{
   if [ $? != 0 ]
   then
      logger "RADISYS:$FILENAME:ERROR: Setting OLD Software Version Again"
      resetTargetBank
      cd $TARGETBANK
      if [ -f oldSw.tar.gz ]
      then
         tar -xvzf oldSw.tar.gz
      fi

      sed -i "/LTE_SOFTWARE_UPGRADE_COMPLETE/c LTE_SOFTWARE_UPGRADE_COMPLETE/0 = $FAULTCODE" $TARGETBANK/rsys/config/mib-home-fap.nv
      sed -i '/LTE_SOFTWARE_IMAGE_DOWNLOAD_COMPLETE/c LTE_SOFTWARE_IMAGE_DOWNLOAD_COMPLETE/0 = 1' $TARGETBANK/rsys/config/mib-home-fap.nv

      logger "RADISYS:$FILENAME:UPDATING /etc/init.d/S98auto"
      chmod 0755 /etc/init.d/S98auto
      echo "cd "$TARGETBANK"/rsys/scripts/" >/etc/init.d/S98auto
      echo ". ./start_TeNB.sh" >>/etc/init.d/S98auto

      reboot
   fi
}

logger "RADISYS:$FILENAME:Sending SIGTERM enodeb Application"
killall -15 enb_cpuh
logger "RADISYS:$FILENAME:Sending SIGTERM to OAM processes"
killall -15 post-office
killall -15 oam
killall -15 tenpin
killall -15 tr069-v2

cd /root
rm -rf app.tgz

logger "RADISYS:$FILENAME:Compressing OLD Software"
cd $CURBANK
tar -cvzf oldSw.tar.gz  rsys >/dev/null
handleError
CURBANK="`pwd`"
logger "RADISYS:$FILENAME:Removeing Old Software"
rm -rf rsys >/dev/null
handleError

logger "RADISYS:$FILENAME:Untaring New Software"
cd $TARGETBANK
tar -xvzf /mnt/tmp/$NEWSOFTNAME >/dev/null
handleError
rm -rf /mnt/tmp/$NEWSOFTNAME >/dev/null

logger "RADISYS:$FILENAME:Doing Basic Verification Of New Software"
cd $TARGETBANK/rsys/scripts/
./basicVerification.sh ../bin
handleError

sed -i '/LTE_SOFTWARE_UPGRADE_COMPLETE/c LTE_SOFTWARE_UPGRADE_COMPLETE/0 = 1' $TARGETBANK/rsys/config/mib-home-fap.nv
sed -i '/LTE_SOFTWARE_IMAGE_DOWNLOAD_COMPLETE/c LTE_SOFTWARE_IMAGE_DOWNLOAD_COMPLETE/0 = 1' $TARGETBANK/rsys/config/mib-home-fap.nv

sed -i '/SW_UPDATE_PACKAGE_NAME_A/c SW_UPDATE_PACKAGE_NAME_A/0 = $NEWSOFTNAME' $TARGETBANK/rsys/config/mib-home-fap.nv

cd $TARGETBANK/rsys/scripts/
source ./install.sh

logger "RADISYS:$FILENAME:UPDATING /etc/init.d/S98auto"
chmod 0755 /etc/init.d/S98auto
echo "cd "$TARGETBANK"/rsys/scripts/" >/etc/init.d/S98auto
echo ". ./start_TeNB.sh" >>/etc/init.d/S98auto

logger "RADISYS:$FILENAME:SUCCESSFULL UPGRADE removing old tarball"
cd $CURBANK
rm -f oldSw.tar.gz >/dev/null
logger "RADISYS: Going For Reboot After 10 Sec"
sleep 10
reboot
