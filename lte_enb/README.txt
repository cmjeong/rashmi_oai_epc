This version of TeNB software supports be below flavours;

* Monolithic eNodeB (without OAM)
* Sliced eNodeB - TIP architecture (without OAM)

The below sections describes the different 

Compilation and execution of monolithic eNodeB (without OAM)
============================================================
1) Untar the release package.
2) Go to folder lte_enb/build/pal/
3) Run following compilation command:
   b) make tenb TEXT_LOG=YES
4) On successful compilation, an executable package will be created at path: lte_enb/build/pal/rsys_withoutoam/
5) Go to rsys_withoutoam/bin;
6) Update wr_cfg.txt file; [Key parameters to be updated are mentioned in the configuration section]
7) Update ys_cfg.txt file;
8) Execute the follwing command to run the binary:
   a) L3: ./start_eNB.sh

Compilation and execution of sliced eNodeB - TIP architecture (without OAM)
===========================================================================
1) Untar the release package.
2) Go to folder lte_enb/build/pal/
3) Run following compilation command:
   b) make tenb TIP=YES TEXT_LOG=YES
4) On successful compilation, an executable package will be created at path: lte_enb/build/pal/rsys_withoutoam/
5) Go to rsys_withoutoam/bin;
6) Update wr_cfg.txt file; [Key parameters to be updated are mentioned in the configuration section]
7) Update ys_cfg.txt file;
8) Execute the follwing commands in different consoles to run the binaries:
   a) ./l3.sh
   b) ./ul2.sh
   c) ./ll2.sh


Common configuration parameters in wr_cfg.txt: (only for without OAM case)
==========================================================================
WR_TAG_ENB_IP_ADDR = <S1 MME ethernet IP. 172.16.3.132>
WR_TAG_SCTP_IP_ADDR = <S1 MME ethernet IP. 172.16.3.132>
WR_TAG_CELL_ID = <Default set to 22. Change for different RAU.>
WR_TAG_PCI_LIST = <Default set to 30. Change for different RAU. Set same as WR_TAG_PCI_VAL>
WR_TAG_PCI_VAL = <Default set to 30. Change for different RAU.>
WR_TAG_MCC_0 = <first digit of MCC. Default 0>
WR_TAG_MCC_1 = <second digit of MCC. Default 0>
WR_TAG_MCC_2 = <third digit of MCC. Default 1>
WR_TAG_MNC_0 = <first digit of MNC. Default 0>
WR_TAG_MNC_1 = <second digit of MNC. Default 1>
WR_TAG_MNC_2 = <third digit of MNC. Default -1>
WR_TAG_TA_CODE = <tracking area code - 12594 for Aricent>
WR_TAG_FREQ_BAND_IND = <Default set to 7. Set to 2 for band 2>
WR_TAG_DL_EARFCN = <Default set to 3100 for Band7. Change to 900 for Band2>
WR_TAG_UL_EARFCN = <Default set to 21100 for Band7. Change to 18900 for Band2>
WR_TAG_MME_INFO = <Default set to 172.16.3.133>
WR_TAG_PLMN_ID_LST = <Default set to 00101. Change to 22222 if connecting to TM500>
   
Configuration parameters in wr_cfg.txt for TIP architecture (mandatory when TIP=YES)
====================================================================================
WR_TAG_L3_IP = <TIP interface L3 IP. 172.16.2.5>
WR_TAG_UL2_IP = <TIP interface UL2-3 Subnet IP. As per OpenStack Cloud Env.>
WR_TAG_LL2_IP = <TIP interface RAU IP. As per OpenStack Cloud Env.>
WR_TAG_DUL2_IP = <S1 Subnet UL2 IP. As per OpenStack Cloud Env.>
WR_TAG_L3_PORT = <Default set to 38000. Only change if needed to run on same VM where another L3 binary is running>

Common configuration parameters in ys_cfg.txt (mandatory for both flavours)
===========================================================================
YS_IP_ADDR_ENB        192.168.10.4  - eNodeB address
YS_IP_ADDR_UE         192.168.10.5  - UE IP address
