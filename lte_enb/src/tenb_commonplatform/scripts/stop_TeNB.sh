###############################################################################
# 
#  Note:- This script should be run in the target machine board
#
###############################################################################
                  
echo "Stopping Apps"
pkill -9 post-office 
pkill -9 oam 
pkill -9 tenpin
pkill -9 tr069-v2
pkill -9 fileTransMgr
pkill -9 enodeb_l3
pkill -9 enodeb
#pkill -9 cli
rm -rf ../setup /mnt/bank-active /mnt/log /mnt/tmp
#cp ../config/mib-factory.nv temp.nv
line=$(tail -1 ../config/mib-factory.nv)
if [[ "$line" =~ "LTE_X_TIP_NUM_OF_CELLS" ]]; then
head -n -2 ../config/mib-factory.nv > temp.nv
mv -f temp.nv ../config/mib-factory.nv
fi

#killall -9 post-office oam tenpin tr069-v2 ftp-func ./obj/enodeb
#ipsec stop
