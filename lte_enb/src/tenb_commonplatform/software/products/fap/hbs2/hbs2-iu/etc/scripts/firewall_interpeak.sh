#!/bin/sh

case ${1} in
    "initialise" | "init")
        echo initialising firewall rules
        # ipsec nat-t esp
        /bin/ipf pass in  quick proto udp from any port = 4500 to me  port = 4500
        /bin/ipf pass out quick proto udp from me  port = 4500 to any port = 4500
        # ipsec esp
        /bin/ipf pass in  quick proto esp from any to me
        /bin/ipf pass out quick proto esp from me  to any
        # ike
        /bin/ipf pass in  quick proto udp from any port = 500 to me  port = 500
        /bin/ipf pass out quick proto udp from me  port = 500 to any port = 500
        # dhcp
        /bin/ipf pass in  quick proto udp from any to any port = 68
        /bin/ipf pass out quick proto udp from any to any port = 67
        # dns
        /bin/ipf pass in  quick proto udp from any port = 53 to me
        /bin/ipf pass out quick proto udp from me            to any port = 53
        # udp logging
        /bin/ipf pass out quick proto udp from me to any port 9001 \<\> 9050
        # icmp
        /bin/ipf pass in  quick proto icmp from any to me
        /bin/ipf pass out quick proto icmp from me  to any
    ;;
    "flush")
        echo flushing firewall rules
        /bin/ipf -Fa
    ;;
    "enable" | "on")
        echo enabling firewall
        /bin/ipf -E
    ;;
    "disable" | "off")
        echo disabling firewall
        /bin/ipf -D
    ;;
    "print" | "list" | "")
        /bin/ipf -Pr
    ;;
    *)
        echo unhandled case ${1}
    ;;
esac
