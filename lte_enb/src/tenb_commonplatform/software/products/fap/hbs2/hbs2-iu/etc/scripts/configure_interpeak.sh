#!/bin/sh

FLASH_DIR=/mnt
FLASH_DIR_ACTIVE_BANK=$FLASH_DIR/bank-active
FLASH_DIR_APPS=$FLASH_DIR_ACTIVE_BANK/dbx
FLASH_DIR_LOCAL_CFG=$FLASH_DIR_ACTIVE_BANK/config

##############################################################################

echo Configuring Interpeak based solution

IKE_SEND_INTERMEDIATE_CERTS=`$FLASH_DIR_APPS/mib-firkler -q IKE_SEND_INTERMEDIATE_CERTS`
IPSEC_NAT_T_PORT=`$FLASH_DIR_APPS/mib-firkler -q IPSEC_NAT_T_PORT`
PATH_MTU_DISCOVERY=`$FLASH_DIR_APPS/mib-firkler -q IP_PATH_MTU_DISC`

echo Configuring IKE/IPsec

sed -i -e '/^ipike.send_intermediate_certs=.*$/d' ${FLASH_DIR_LOCAL_CFG}/ike.sysvar
sed -i -e '/^ipike.port_nat=.*$/d' ${FLASH_DIR_LOCAL_CFG}/ike.sysvar

echo "ipike.send_intermediate_certs=${IKE_SEND_INTERMEDIATE_CERTS}" >> ${FLASH_DIR_LOCAL_CFG}/ike.sysvar
if [ 0 -ne "${IPSEC_NAT_T_PORT}" ];
then
    echo "ipike.port_nat=${IPSEC_NAT_T_PORT}" >> ${FLASH_DIR_LOCAL_CFG}/ike.sysvar
fi

echo Configuring Path MTU Discovery "${PATH_MTU_DISCOVERY}"
echo "$PATH_MTU_DISCOVERY" > /proc/sys/net/ipnet/path_mtu_discovery

