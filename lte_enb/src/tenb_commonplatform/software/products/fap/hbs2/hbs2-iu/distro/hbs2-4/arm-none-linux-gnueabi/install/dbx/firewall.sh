#!/bin/sh

ALL_TABLES='filter nat'
FILTER_TABLE_CHAINS='INPUT FORWARD OUTPUT'

case ${1} in
    "initialise" | "init")
        echo initialising firewall rules
        ${0} flush
        echo setting default policies
        for chain in ${FILTER_TABLE_CHAINS}; do
            iptables --policy ${chain} DROP
        done

        echo loading kernel modules
        modprobe nf_conntrack
        modprobe nf_conntrack_ipv4
        modprobe nf_conntrack_ftp
        modprobe nf_defrag_ipv4
        modprobe iptable_nat
        modprobe nf_nat
        modprobe nf_nat_ftp
        modprobe xt_state

        echo permitting all local traffic
        iptables --append INPUT    --in-interface lo --jump ACCEPT
        iptables --append FORWARD  --in-interface lo --jump ACCEPT
        iptables --append FORWARD --out-interface lo --jump ACCEPT
        iptables --append OUTPUT  --out-interface lo --jump ACCEPT

        echo installing firewall filter rules
        # state tracking rules
        for chain in ${FILTER_TABLE_CHAINS}; do
            iptables --append ${chain} --match state --state INVALID             --jump DROP
            iptables --append ${chain} --match state --state ESTABLISHED,RELATED --jump ACCEPT
        done

        # ipsec nat-t esp
        iptables --append OUTPUT --protocol udp --sport 4500 --dport 4500 --match state --state NEW --jump ACCEPT

        # ipsec esp
        iptables --append OUTPUT --protocol esp --match state --state NEW --jump ACCEPT

        # ike
        iptables --append OUTPUT --protocol udp --sport 500 --dport 500 --match state --state NEW --jump ACCEPT

        # dhcp
        iptables --append OUTPUT --protocol udp --dport 67 --match state --state NEW --jump ACCEPT

        # dns
        iptables --append OUTPUT --protocol udp --dport 53 --match state --state NEW --jump ACCEPT

        # udp logging
        iptables --append OUTPUT --protocol udp --dport 9001:9050 --jump ACCEPT

        # icmp
        iptables --append INPUT  --protocol icmp --jump ACCEPT
        iptables --append OUTPUT --protocol icmp --jump ACCEPT
    ;;
    "flush")
        echo flushing firewall rules
        for table in ${ALL_TABLES}; do
            iptables -t ${table} --flush
            iptables -t ${table} --delete-chain
        done
    ;;
    "enable" | "on")
        echo enabling firewall
        # no explicit enable for iptables, so reinitialise
        ${0} initialise
    ;;
    "disable" | "off")
        echo disabling firewall
        # no explicit disable for iptables, so just set permissive policies
        for chain in ${FILTER_TABLE_CHAINS}; do
            iptables --policy ${chain} ACCEPT
        done
    ;;
    "print" | "list" | "")
        iptables --list
    ;;
    *)
        echo unhandled case ${1}
    ;;
esac

