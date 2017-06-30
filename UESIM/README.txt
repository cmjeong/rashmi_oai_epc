Compilation:
============
1) for linux gcc 32 bit
 make -f ue_stack.mak clean BLDENV=lnx_e2e_acc MACHINE=BIT32 acc

2) for linux gcc 32 bit (default)
 make -f ue_stack.mak clean BLDENV=lnx_e2e_acc MACHINE=BIT64 acc

Execution:
==========
1) change the configuration for UE SIM in uesim_cfg.txt
   a) set UE_APP_SELF_ETH_INF_ADDR to UESIM IP address
2) change the configuration for UE and eNodeB comminication in ys_cfg.txt
   a) set YS_IP_ADDR_UE to UESIM IP address
   b) set YS_IP_ADDR_ENB1 to eNodeB LL2 IP address (same as WR_TAG_LL2_IP)
3) Run the following command to execute UE SIM:
   a) ./uesim

Compiler version:
=================
This version of the UESIM software was verifed on GCC version: 4.4.7
