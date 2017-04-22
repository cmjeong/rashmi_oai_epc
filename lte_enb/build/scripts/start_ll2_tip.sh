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
echo "   TotaleNodeB LL2 Solution for TIP                          "
echo "                                                             "
echo "                                                             "
echo "                                                             "

sleep 3
ulimit -c unlimited
SSI_CONFIG_FILE="../config/ssi_mem_radio"
echo "RADISYS:Launching enodeb_ll2 with $SSI_CONFIG_FILE"
./enodeb_ll2 -f $SSI_CONFIG_FILE
