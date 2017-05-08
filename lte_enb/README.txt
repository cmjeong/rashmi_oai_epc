This version of TeNB software supports be below flavours;

* Monolithic eNodeB (without OAM)
* Monolithic eNodeB (with OAM)
* Sliced eNodeB - TIP architecture (without OAM)
* Sliced eNodeB - TIP architecture (with OAM)

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

Compilation and execution of monolithic eNodeB (with OAM)
=========================================================
1) Untar the release package.
2) Go to folder lte_enb/build/pal/
3) Run following compilation command:
   b) make tenb OAM_ENABLE=YES TEXT_LOG=YES
4) On successful compilation, an executable package will be created at path: lte_enb/build/pal/rsys/
5) Go to rsys/config/ folder;
6) Update wr_cfg.txt file; [Key parameters to be updated are mentioned in the configuration section]
7) Update ys_cfg.txt file;
8) Update below parameters in 'configFile';
   a) OAM_ETHERNET_INTERFACE -> set to the interface of eNodeB L3 IP.
   b) OAM_NUM_CELL_ENTRIES -> set to 1
   c) LTE_X_RADISYS_NUM_OF_CELLS -> all entries set to 1
8) Execute the follwing command to run the binary:
   a) . ./install.sh
   b) . ./start_TeNB.sh
9) Administrative state is set to lock by default. Do the following to unlock;
   a) Open a new terminal;
   b) Go to rsys/bin;
   c) execute cli as below;
      ./cli
   d) Configure PLMN ID;
      tr69.addobject Device.Services.FAPService.1.CellConfig.LTE.EPC.PLMNList.
      tr69.set Device.Services.FAPService.1.CellConfig.LTE.EPC.PLMNList.1.PLMNID 311481
      tr69.set Device.Services.FAPService.1.CellConfig.LTE.EPC.PLMNList.1.IsPrimary 1
	  tr69.set Device.Services.FAPService.1.CellConfig.LTE.EPC.PLMNList.1.CellReservedForOperatorUse 1
	  tr69.set Device.Services.FAPService.1.CellConfig.LTE.EPC.PLMNList.1.Enable 1
   e) Set administrative state as below;
	   tr69.set Device.Services.FAPService.1.FAPControl.LTE.AdminState 1
10) To stop the binaries;
   . ./stop_TeNB.sh

Compilation and execution of sliced eNodeB - TIP architecture (with OAM)
========================================================================
1) Untar the release package.
2) Go to folder lte_enb/build/pal/
3) Run following compilation command:
   b) make tenb TIP=YES OAM_ENABLE=YES TEXT_LOG=YES
4) On successful compilation, an executable package will be created at path: lte_enb/build/pal/rsys/
5) Go to rsys/config/ folder;
6) Update wr_cfg.txt file; [Key parameters to be updated are mentioned in the configuration section]
7) Update ys_cfg.txt file;
8) Update below parameters in 'configFile';
   a) OAM_ETHERNET_INTERFACE -> set to the interface of eNodeB L3 IP.
   b) OAM_NUM_CELL_ENTRIES -> set to 1
   c) LTE_X_RADISYS_NUM_OF_CELLS -> all entries set to 1
   b) LTE_SIGLINK_SERVER_LIST -> MME IP address
8) Execute the follwing command to run the binary:
   a) . ./install_tip.sh
   b) . ./start_TeNB_tip.sh
9) Administrative state is set to lock by default. Do the following to unlock;
   a) Open a new terminal;
   b) Go to rsys/bin;
   c) execute cli as below;
      ./cli
   d) Configure PLMN ID;
      tr69.addobject Device.Services.FAPService.1.CellConfig.LTE.EPC.PLMNList.
      tr69.set Device.Services.FAPService.1.CellConfig.LTE.EPC.PLMNList.1.PLMNID 311481
      tr69.set Device.Services.FAPService.1.CellConfig.LTE.EPC.PLMNList.1.IsPrimary 1
	  tr69.set Device.Services.FAPService.1.CellConfig.LTE.EPC.PLMNList.1.CellReservedForOperatorUse 1
	  tr69.set Device.Services.FAPService.1.CellConfig.LTE.EPC.PLMNList.1.Enable 1
   e) Set administrative state as below;
	   tr69.set Device.Services.FAPService.1.FAPControl.LTE.AdminState 1
10) To stop the binaries;
   . ./stop_TeNB.sh

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

Compilation and execution of sliced eNodeB with SRS PHY (without OAM)
============================================================
1) Untar the release package.
2) Go to folder lte_enb/build/pal/
3) Run following compilation command:
   b) make tenb TEXT_LOG=YES SRS_PHY=YES
4) On successful compilation, an executable package will be created at path: lte_enb/build/pal/rsys_withoutoam/
5) Go to rsys_withoutoam/bin;
6) Update wr_cfg.txt file; [Key parameters to be updated are mentioned in the configuration section]
7) Update ys_cfg.txt file;
8) Execute the follwing command to run the binary:
   a) L3: ./start_eNB.sh

