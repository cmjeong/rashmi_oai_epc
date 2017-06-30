Extraction, compilation and execution:
======================================
1) Untar EPC.tar.gz
2) Go to EPC folder
3) Run one of the following command to compile EPC:
   a) For a 32 bit machine: ./build.sh -m 32
   b) For a 64 bit machine (default): ./build.sh -m 64
4) Change the configuration parameters for mme, sgw and pgw (refer the below configuration section)
5) Run the following command to execute EPC: make sure that the configured IPs are valid
   a) ./runCne
   
Configuration:
==============
1) Open mme/vbsm_cfg.txt
   a) set VBSM_ENB_ADDR_1 to eNodeB L3 IP address
   b) set VBSM_MME_IPADDR to MME IP address
   c) set VBSM_SGW_IPADDR to SGW IP address
   d) set VBSM_PGW_IPADDR to PGW IP address
   e) set VBSM_MCC_DIG1 to first digit to MCC value
   f) set VBSM_MCC_DIG2 to second digit to MCC value
   g) set VBSM_MCC_DIG3 to third digit to MCC value
   h) set VBSM_MNC_DIG1 to first digit to MNC value
   i) set VBSM_MNC_DIG2 to second digit to MNC value
   j) set VBSM_MNC_DIG3 to third digit to MNC value (if only 2 digits, then set to -1)
2) Open sgw/qosm_cfg.txt
   a) set QOSM_SGW_IPADDR to SGW IP address
3) Open pgw/avsm_cfg.txt
   a) set AVSM_PGW_DFLT_ADDR to PGW IP address
   b) set AVSM_PGW_DFLT_EXGW_ADDR to default gateway IP address
   c) set AVSM_SGW_IPADDR to SGW IP address

Compiler version:
=================
This version of the EPC software was verifed on GCC version: 4.4.7
