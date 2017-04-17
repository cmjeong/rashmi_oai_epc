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
echo "   TotaleNodeB UL2 Solution for TIP                          "
echo "                                                             "
echo "                                                             "
echo "                                                             "

sleep 3
ulimit -c unlimited
SSI_CONFIG_FILE="../config/ssi_mem"
echo "RADISYS:Launching enodeb_ul2 with $SSI_CONFIG_FILE"
./enodeb_ul2 -f $SSI_CONFIG_FILE
