#!/bin/sh

echo Configuring StrongSWAN-based solution

echo Copying trusted certificates
cp /mnt/certificates/trusted/* /etc/ipsec.d/cacerts/

echo Disabling Path MTU
echo "1" > /proc/sys/net/ipv4/ip_no_pmtu_disc
