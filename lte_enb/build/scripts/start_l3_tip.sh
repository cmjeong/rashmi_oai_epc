#!/bin/sh

echo "                                                             "
echo "                                                             "
echo "                                                             "
echo "                           ((       ))                       "
echo "                            ((     ))                        "
echo "                             ((   ))                         "
echo "   / ::::  /::::::         ||   *   :::::: ::    :: ::::::   "
echo "  : /      ||   ||     ....||  | |  ||      ::  ::  ||       "
echo "  | |      ||   ||    ||   ||  | |  ::::::    ||    ::::::   "
echo "  | |      ||   ::    ||   ||  | |      ||    ||        ||   "
echo "  | |      ::::::,,,  ||:::::  | |  ::::::    ||    ::::::   "

echo "                                                             "
echo "                                                             "
echo "                                                             "
echo "   TotaleNodeB L3 Solution for TIP                           "
echo "                                                             "
echo "                                                             "
echo "                                                             "

sleep 3
ulimit -c unlimited
SSI_CONFIG_FILE="../config/ssi_mem_net"
echo "RADISYS:Launching enodeb_l3 with $SSI_CONFIG_FILE"
./enodeb_l3 -f $SSI_CONFIG_FILE
