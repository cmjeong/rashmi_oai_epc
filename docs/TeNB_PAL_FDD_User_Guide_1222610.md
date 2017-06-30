  ----------------------------------------------------------------------------------
  ![](media/image1.png){width="6.424528652668417in" height="0.5715069991251094in"}

  **LTE TOTALeNodeB Solution**
  
  **(on Physical Abstraction Layer)**
  
  **User Guide (for GA 4.0)**
  
  **1222610 4.0**

  ----------------------------------------------------------------------------------

© 2015 by RadiSys Corporation. All rights reserved.

Radisys, Network Service-Ready Platform, Quick!Start, TAPA, Trillium,
Trillium+plus, Trillium Digital Systems, Trillium On Board, TAPA, and
the Trillium logo are trademarks or registered trademarks of RadiSys
Corporation. All other trademarks, registered trademarks, service marks,
and trade names are the property of their respective owners.

[]{#_Toc114674536 .anchor}

**Contents**

[1. Preface 6](#preface)

[1.1 Objective 6](#objective)

[1.2 Audience 6](#audience)

[1.3 Document Organization 6](#document-organization)

[1.4 Release History 7](#release-history)

[2. Introduction 8](#introduction)

[2.1 Product Description 8](#product-description)

[2.2 Definitions and Acronyms 11](#definitions-and-acronyms)

[3. Setup (End-to-End Solution) 17](#setup-end-to-end-solution)

[3.1 End-to-End Demo with Uu Stacks on Single Linux Machine
17](#end-to-end-demo-with-uu-stacks-on-single-linux-machine)

[3.2 End-to-End Demo with Uu Stacks on Multiple Linux Machines
18](#end-to-end-demo-with-uu-stacks-on-multiple-linux-machines)

[3.3 Hardware 19](#hardware)

[3.4 Software 19](#software)

[4. TeNB Directory Structure 20](#tenb-directory-structure)

[5. Building Integrated Stacks 22](#building-integrated-stacks)

[5.1 Build Core Network Emulators (Radisys CNE)
22](#build-core-network-emulators-radisys-cne)

[5.1.1. MME 22](#mme)

[5.1.1.1. Product Feature Flags 22](#product-feature-flags)

[5.1.1.2. Build MME 23](#build-mme)

[5.1.2. SGW 23](#sgw)

[5.1.2.1. Product Feature Flags 23](#product-feature-flags-1)

[5.1.2.2. Build SGW 24](#build-sgw)

[5.1.3 PGW 24](#pgw)

[5.1.3.1. Product Feature Flags 24](#product-feature-flags-2)

[5.1.3.2. Build PGW 25](#build-pgw)

[5.2 Build TeNB 25](#build-tenb)

[5.2.1 Product Feature Flags 25](#product-feature-flags-3)

[5.2.2 Building TeNB Integrated Stack for Linux
27](#building-tenb-integrated-stack-for-linux)

[6. Configuring Radisys CNE and TeNB
28](#configuring-radisys-cne-and-tenb)

[6.1 Configuration Settings for Core Network Emulators
28](#configuration-settings-for-core-network-emulators)

[6.1.1 Configuration Settings for MME
28](#configuration-settings-for-mme)

[6.1.2 Configuration Settings for SGW
30](#configuration-settings-for-sgw)

[6.1.3 Configuration Settings for PGW
31](#configuration-settings-for-pgw)

[6.2 Configuration Settings for eNodeB
32](#configuration-settings-for-enodeb)

[6.3 Configuration Setting of Video Client
53](#configuration-setting-of-video-client)

[6.4 Configuration Settings in CNE for Multi-UE Scenario
53](#configuration-settings-in-cne-for-multi-ue-scenario)

[7. Execution of the Nodes 55](#execution-of-the-nodes)

[7.1 Radisys CNE 55](#radisys-cne)

[7.2 TeNB 55](#tenb)

[7.2.1 TeNB without OAM 55](#tenb-without-oam)

[7.2.2 TeNB with OAM 56](#tenb-with-oam)

[8. End-to-End Call Flow (Message Sequence Chart)
58](#end-to-end-call-flow-message-sequence-chart)

[9. Traffic Generators 64](#traffic-generators)

[9.1 UDP Performance Testing 64](#udp-performance-testing)

[9.1.1 Uplink Data 64](#uplink-data)

[9.1.2 Downlink Data 64](#downlink-data)

[9.2 TCP Performance Testing 64](#tcp-performance-testing)

[9.2.1 Uplink Data 64](#uplink-data-1)

[9.2.2 Downlink Data 64](#downlink-data-1)

[10. Performance Management 65](#performance-management)

[10.1 L2 Layer Measurement Counters 65](#l2-layer-measurement-counters)

[11. Troubleshooting 67](#troubleshooting)

[12. References 68](#references)

**Figures**

[Figure-1: End-to-End Demo with Uu Stacks on Single Linux Machine
17](#_Toc418590643)

[Figure-2: End-to-End Demo with Uu Stacks on Multiple Linux Machines
18](#_Toc418590644)

[Figure-3: TeNB Directory Structure 20](#_Toc418590645)

[Figure-4: LTE Control and Data Call Flow 58](#_Toc418590646)

[Figure-5: Message Sequence Flow between UE and CNE through eNodeB
59](#_Toc418590647)

[Figure-6: LTE Control and Data Call Flow using Dedicated Bearer
60](#_Toc418590648)

[Figure-7: Mobile Terminating Call Sequence - Flow 1 61](#_Toc418590649)

[Figure-8: Mobile Terminating Call Sequence - Flow 2 62](#_Toc418590650)

[Figure-9: Mobile Terminating Call Sequence - Flow 3 63](#_Toc418590651)

[Figure-10: L2 Layer Measurement Counters 65](#_Toc418590652)

**Tables **

[Table-1: Document Organization 6](#_Toc418590653)

[Table-2: Release History 7](#_Toc418590654)

[Table-3: Definitions and Acronyms 11](#_Toc418590655)

[Table-4: MME Product Feature Flags 22](#_Toc418590656)

[Table-5: SGW Product Feature Flags 23](#_Toc418590657)

[Table-6: PGW Product Feature Flags 24](#_Toc418590658)

[Table-7: TeNB Product Feature Flags 25](#_Toc418590659)

[Table-8: vbsm\_cfg.txt Configuration File 28](#_Toc418590660)

[Table-9: qosm\_cfg.txt Configuration File 30](#_Toc418590661)

[Table-10: avsm\_cfg.txt Configuration File 31](#_Toc418590662)

[Table-11: wr\_cfg.txt Configuration File 33](#_Toc418590663)

[Table-12: ys\_cfg.txt Configuration File 53](#_Toc418590664)

[Table 13: configFile Configuration File 56](#_Toc418590665)

1.  Preface
    =======

    1.  Objective
        ---------

This document provides the usage of LTE TOTALeNodeB FDD Solution on PAL
platform designed by Radisys. This document describes the procedure to
setup, configure, signaling and data calls.

Audience
--------

Radisys assumes that the readers of this document are:

-   Product Development team,

-   Product Line Management team,

-   Sales team,

-   Test/Validation team,

-   Program Management team, and

-   Existing and potential customers.

The readers must have an understanding of TeNB and its architecture.

Document Organization
---------------------

This document contains the following sections:

[[]{#_Toc418590653 .anchor}]{#_Toc383776996 .anchor}Table-1: Document
Organization

  **Ch. No.**   **Section**                                         **Description **
  ------------- --------------------------------------------------- --------------------------------------------------------------------------------------
  1.            **Preface**                                         Provides the objective and release details.
  1.            **Introduction**                                    Provides an overview of the product, including the product description and features.
  1.            **Setup (End-to-End Solution)**                     Describes the end-to-end setup information for this software.
  1.            **TeNB Directory Structure**                        Illustrates the directory structure of the TeNB code base for PAL.
  1.            **Building Integrated Stacks**                      Describes the procedure to build the integrated stack.
  1.            **Configuring Radisys CNE and TeNB **               Describes the procedure to configure TeNB and CNE.
  1.            **Execution of the Nodes**                          Describes the execution process of this software.
  1.            **End-to-End Call Flow (Message Sequence Chart)**   Provides the call flow diagrams of the solution.
  1.            **Traffic Generators**                              Describes the different performance testing options.
  1.            **Performance Management**                          Describes the performance data recording environment.
  1.            **Troubleshooting**                                 Lists the troubleshooting information for this software.
  1.            **References**                                      Lists the reference documents.

Release History
---------------

The following table lists the history of changes in successive revisions
to this document.

[[]{#_Toc418590654 .anchor}]{#_Toc383776997 .anchor}Table-2: Release
History

  **Version**   **Date**        **Description**
  ------------- --------------- ---------------------------------------------------------------
  4.0           May 08, 2015    LTE TeNB Solution GA 4.0 release on PAL.
  2.0           July 14, 2014   LTE TeNB Solution GA 3.0 release on PAL.
  1.0           May 30, 2014    LTE TeNB Solution Early Availability (EA) 3.0 release on PAL.

1.  Introduction
    ============

    1.  Product Description
        -------------------

Radisys TOTALeNodeB (TeNB) is a LTE eNodeB FDD Solution designed and
productized for small cell deployments. Radisys TeNB is a comprehensive
small solution available on leading SoC platforms optimized for
performance. TeNB includes control and data plane protocol suites for L2
and L3 that are integrated with the L1 on the SoC, along with an
application supporting a FSM and other key application components.

The key features of the TeNB solution are as follows:

-   Attach and Detach

-   Random Access procedure

-   RRC Connection and Reconfiguration procedure

-   E-RAB

    -   E-RAB Setup

    -   E-RAB Release

    -   E-RAB Release initiated by eNB

    -   E-RAB Modify

-   S1AP

    -   Reset (MME initiated)

    -   Reset (eNB initiated)

    -   S1 Setup (Successful Operation)

    -   S1 Setup (Unsuccessful Operation)

    -   MME Configuration Update (Successful Operation)

    -   MME Configuration Update (Unsuccessful Operation)

    -   eNB Configuration Update (Successful Operation)

    -   eNB Configuration Update (Unsuccessful Operation)

-   eNB Configuration Update (Retransmission)X2AP

    -   X2AP Reset

    -   X2AP: Reset (Retransmission)

    -   X2AP: X2 Setup (Successful Operation)

    -   X2AP: X2 Setup (Unsuccessful Operation)

    -   X2AP: X2 Setup (Retransmission)

    -   X2AP: eNB Configuration Update (Successful Operation)

    -   X2AP: eNB Configuration Update (Unsuccessful Operation)

    -   X2AP: eNB Configuration Update (Retransmission)

-   Handover

    -   Intra-frequency and Inter-frequency S1 Handover

    -   Intra-frequency and Inter-frequency X2 Handover

    -   Uplink & Downlink Data Forwarding

    -   Inter-RAT Handover to WCDMA cell

-   EPS Mobility Management

    -   EMM Connection Management procedure

        -   Paging

        -   Service Request by UE

    -   EMM specific procedures (UE initiated)

        -   Tracking Area Update procedure for ECM Idle mode

        -   Tracking Area Update procedure for ECM Connected mode

-   Broadcast of MIBs and SIBs (SIB1, SIB2, SIB3, SIB4, SIB5, SIB6,
    > SIB7, SIB8, SIB9, SIB10, SIB11, and SIB12)

-   UL& DL HARQ

-   2x2 MIMO

-   UE Context Release procedure initiated by eNB

-   MME Selection and Load Balance

-   eNodeB Overload Control

-   Network Elements (MME, eNB) monitoring by using heartbeat messages

-   Access Class Barring

-   Emergency Calls

    -   TeNB supports emergency calls for open mode of access by
        > releasing existing calls when running at full capacity

-   Periodic CQI Support

-   Cell Broadcast Service / Public Warning System

    -   Earthquake and Tsunami Warning System (ETWS)

    -   Commercial Mobile Alert System (CMAS)

-   Support for 5, 10 , 15 and 20 MHz Bandwidth

-   2 UE / TTI Scheduling

-   4 UE / TTI Scheduling

-   SNOW3G Integrity and Ciphering Algorithms for AS Security

-   UE Redirection feature when MAX\_ACTIVE\_USERS are reached

-   Tested and integrated with Radisys OAM

-   Automatic Neighbor Relation (ANR): Event (A3, A5) and Periodic based

-   Improved Link Adaptation based on BLER (DL and UL)

-   Binary and Text logging for RRC and eNB Application

-   Watchdog

    -   Software Watchdog to monitor registered applications

    -   Hardware Watchdog to monitor Software Watchdog

-   Radio Environment Monitoring (REM) / Networking Monitoring Module
    > (NMM)

-   Scheduling Algorithms

    -   Proportional Fair Scheduler (PFS) for MAC scheduling

    -   Semi Persistent Scheduling (SPS) for VoLTE

    -   Round Robin (RR)

-   Long and Short DRX

-   Circuit Switched Fallback (CSFB)

    -   UTRA FDD with or without UE measurements (with and without
        > System Information)

    -   CSFB to CDMA2000 1xRTT network with or without UE measurements

    -   eCSFB to CDMA2000 1xRTT network with or without UE measurements

    -   CSFB to GERAN without UE measurements (with or without System
        > Information)

    -   CSFB to GERAN with or without UE measurements (with or without
        > NACC)

    -   CSFB to TD-SCDMA with or without UE measurements (with or
        > without System Information)

-   Redirection to IRAT

    -   Redirection to TD-SCDMA with SI based on B2 event

-   Dynamic IP

-   OAM statistical counters

    -   Layer 3 Counters (RRC and S1AP)

    -   Layer 2 Measurement Counters (RLC Downlink Throughput, RLC
        > Uplink Throughput, PDCP SDU Discard Rate, MAC RACH Counters)

-   Cell Access Mode

    -   Open Access Mode

    -   Closed Access Mode

-   DSCP Marking support at eNodeB

-   Release 11 ASN.1 Compliance for RRC, S1AP and X2AP

-   Disabling DRX for QCI 1, 2, 3, 4

-   SCTP Multi-homing

-   S1-U Error Events

-   Release-10 Compliance for S1AP and X2AP

-   Dynamic Configuration Update through HeMS (only for LTE neighbor
    > Frequency and neighbor Cell)

-   Dynamic Control Format Indicator (DCFI)

-   Downlink Frequency Selective Scheduling (DLFSS)

-   UE History Information (UHI) and Handover Restriction List (HRL)

-   RIM for UTRAN and GERAN SI.

-   SON module supports the following features:

    -   PRACH configuration parameter selection during cell bring up

    -   DL-EARFCN selection during cell bring up

    -   PCI selection during cell bring up

    -   PCI collision prevention

    -   PCI confusion detection and correction

-   NTP

    -   Static configuration of NTP server during TeNB boot up

    -   Dynamic configuration of NTP server

    -   Enable or disable NTP feature statically and dynamically

    -   Reporting current time to OAM or HeMS after synchronizing with
        > NTP server

    -   Reporting NTP time status to OAM or HeMS

-   TLS for secure TR-069 connection

The following end point applications are supported in end-to-end
solution including UeSim, eNodeB, and CNE:

1.  PING application

2.  Data transfer through iperf utility

Definitions and Acronyms
------------------------

The definitions, acronyms, and abbreviations used in this document are:

[[]{#_Toc418590655 .anchor}]{#_Toc383776998 .anchor}Table-3: Definitions
and Acronyms

  **Acronym**             > **Description**
  ----------------------- -----------------------------------------------------
  > 1xRTT                 > 1x (single-carrier) Radio Transmission Technology
  ABS                     > Almost Blank Subframes
  ANR                     > Automatic Neighbor Relations
  App                     > Sample Application Layer
  ARFCN                   > Absolute Radio Frequency Channel Number
  BPSK                    > Binary Phase Shift Keying
  BSP                     > Bicriterion Shortest Path
  CLI                     > Command Line Interface
  CMAS                    > Commercial Mobile Alert System
  CN                      > Core Network
  CNE                     > Core Network Emulators
  CPRI                    > Common Public Radio Interface
  CPU                     > Central Processing Unit
  CQI                     > Channel Quality Indicator
  CRE                     > Cell Range Expansion
  C-RNTI                  > Cell Radio Network Temporary Identifier
  > CNM                   > Continuous Network Monitoring
  > CSFB                  > Circuit Switched FallBack
  > CDMA                  > Code Division Multiple Access
  > DCFI                  > Dynamic Control Format Indicator
  > DL                    > Downlink
  > DLFSS                 > Downlink Frequency Selective Scheduling
  > DLPC                  > Downlink Power Control
  DRB                     > Data Radio Bearer
  DRX                     > Discontinuous Reception
  DTCH                    > Dedicated Traffic CHannel
  EAID                    > Emergency Area ID
  ECGI                    > E-UTRAN Cell Global Identifier
  e-GTP                   > Evolved GTP
  EARFCN                  > E-UTRA Absolute Radio Frequency Channel Number
  eNB or eNodeB           > E-UTRAN Node B
  EPC                     > Evolved Packet Core
  EPS                     > Evolved Packet System
  E-RAB or ERAB           E-UTRAN Radio Access Bearer
  ETWS                    Earthquake and Tsunami Warning System
  E-UTRAN                 Evolved UTRAN
  EVM                     Error Vector Magnitude
  EDGE                    Enhanced Data rates for Global Evolution
  FDD                     Frequency Division Duplex
  FDX                     Full Duplex
  FGI                     Feature Group Indicator
  GBR                     Guaranteed Bit Rate
  GTP                     GPRS Tunneling Protocol
  GERAN                   GSM EDGE Radio Access Network
  GPRS                    General Packet Radio Service
  HARQ                    Hybrid ARQ
  HeMS                    Home eNodeB Management System
  HRL                     Handover Restriction List
  HSS                     Home Subscriber Server
  IE                      Information Element
  IKEv2                   Internet Key Exchange v2
  IMSI                    International Mobile Subscriber Identity
  IP                      Internet Protocol
  IPsec                   IP Security
  LA                      Link Adaptation
  L-ARM or LARM           Lower ARM
  LCG                     Logical Channel Group
  LTE                     Long Term Evolution
  MAC                     Medium Access Control Protocol
  MCC                     Mobile Country Code
  MIB                     Master Information Block
  MIMO                    Multiple Input Multiple Output
  MME                     Mobile Management Entity
  MNC                     Mobile Network Code
  MTU                     Maximum Transmission Unit
  NACC                    Network-Assisted Cell Change
  NAS                     Non-Access Stratum
  NMM                     Network Monitor Mode
  NR                      Neighbor Relation
  NRT                     Neighbor Relation Table
  NTP                     Network Time Protocol
  OAM                     Operation And Maintenance
  ODMA                    Opportunity-Driven Multiple Access
  OPC                     Operations Controller
  PAL                     Physical Abstraction Layer
  PCCH                    Paging Control Channel
  PCI                     Physical Cell Identifier
  PDCCH                   Physical Downlink Control CHannel
  PDCP                    Packet Data Convergence Protocol
  PDN                     Packet Data Network
  PDSCH                   Physical Downlink Shared CHannel
  PDU                     Protocol Data Unit
  PFS                     Proportional Fair Scheduler
  PRB                     Physical Resource Block
  PUSCH                   Physical Uplink Shared CHannel
  P-GW, PDN-GW or PGW     PDN Gateway
  PLMN                    Public Land Mobile Network
  PWS                     Public Warning System
  QAM                     Quadrature Amplitude Modulation
  QPSK                    Quadrature Phase Shift Keying
  QXDM                    Qualcomm Extensible Diagnostic Monitor
  RAB                     Radio Access Bearer
  RAC                     Radio Admission Control
  RAN                     Radio Access Network
  RB                      Radio Bearer
  REM                     Radio Environment Monitoring
  RF                      Radio Frequency
  RLC                     Radio Link Control Protocol
  RIM                     RAN Information Management
  RNC                     Radio Network Controller
  RNTI                    Radio Network Temporary Identifier
  RRC                     Radio Resource Control Protocol
  RRM                     Radio Resource Management
  RV                      Redundancy Version
  Rx or RX                Receiver
  S1AP                    S1 Application Protocol
  SCTP                    Stream Control Transmission Protocol
  SCTP RTO                SCTP Retransmission Time-Out
  S-GW or SGW             Serving Gateway
  SDU                     Service Data Unit
  SIB                     System Information Block
  SINR                    Signal to Noise Ratio
  SISO                    Single Input Single Output
  SI                      System Information
  SM                      Stack Manager
  SoC                     System-on-a-Chip
  SON                     Self Organizing Network
  SPS                     Semi Persistent Scheduling
  TCP                     Transmission Control Protocol
  TDD                     Time Division Duplex
  TeNB or TOTALeNB        TOTALeNodeB
  TFTP                    Trivial File Transfer Protocol
  TLS                     Transport Layer Security
  TTI                     Transmission Timing Interval
  TUCL                    TCP/UDP Convergence Layer
  Tx or TX                Transmitter
  U-ARM or UARM           Upper ARM
  U-Boot                  Universal Boot Loader
  UDP                     User Datagram Protocol
  UE                      User Equipment
  UeSim, UESim or ueSim   Radisys UE Simulator
  UHI                     UE History Information
  UL                      Uplink
  ULPC                    Uplink Power Control
  USB                     Universal Serial Bus
  UTRAN                   Universal Terrestrial Radio Access Network
  VC                      Video Client
  VS                      Video Server
  X2AP                    X2 Application Protocol

For a list of commonly used terms, refer to the engineering glossary at
[www.radisys.com/resources/wireless-glossary/](http://www.radisys.com/resources/wireless-glossary/)

Setup (End-to-End Solution) 
============================

This section describes the hardware and software components and setup
required to execute the CNEs (binaries) in end-to-end environment to
demonstrate the functions and interactions of CNEs with rest of nodes
like UeSim, eNodeB, external client and server. eNodeB and UeSim (Uu
stack) is executed on Linux platform.

> **Note:** MME, SGW, PGW together form core-network emulators (CNE).
> UeSim and CNE sample applications **must** be treated as reference
> applications with limited set of functionality**.**

End-to-End Demo with Uu Stacks on Single Linux Machine
------------------------------------------------------

Figure-1 shows the setup of end-to-end demo executing LTE eNodeB with Uu
stacks on single Linux machine.

[[]{#_Toc418590643 .anchor}]{#_Ref387839869 .anchor}**Figure-1:
End-to-End Demo with Uu Stacks on Single Linux Machine**

![](media/image2.png){width="6.647222222222222in"
height="3.623611111111111in"}

For single PC setup, a system with two interfaces is required to
configure with five different IPs as follows:

> ifconfig eth0 172.27.2.42 up
>
> ifconfig eth0:1 172.27.2.43 up
>
> ifconfig eth0:2 172.27.2.44 up
>
> ifconfig eth0:3 172.27.2.45 up
>
> ifconfig eth1 172.27.3.92 up

There must be a route established between UE and Video Client (VC) using
the following route command to ensure that VC is reachable only from UE.

> **route add –host &lt;ue\_client\_ip\_addr&gt; gw
> &lt;ue\_sim\_ip\_addr\_connected\_to\_ue\_client&gt; dev
> &lt;device\_connected\_to\_ue\_client&gt; **
>
> For example: route add -host 172.27.3.91 gw 172.27.3.92 dev eth1,
> where 172.27.3.91 is used in the test setup for VC.

End-to-End Demo with Uu Stacks on Multiple Linux Machines
---------------------------------------------------------

Figure-2 shows the setup of end-to-end demo executing LTE eNodeB, CNEs,
and UeSim with Uu Stacks on multiple Linux machines.

[[]{#_Toc418590644 .anchor}]{#_Ref387841862 .anchor}Figure-: End-to-End
Demo with Uu Stacks on Multiple Linux Machines

![](media/image4.png){width="6.473333333333334in"
height="3.5566666666666666in"}

Hardware
--------

The hardware requirements are as follows:

-   One Linux machine (desktop/server) with an Ethernet card to run CNE.

> With virtual IP configured on the same Linux machine (desktop/server)
> having an Ethernet card is used to execute MME, SGW, and PGW. However,
> based on hardware availability, the nodes are executed on different
> Linux machines.

-   One Linux machine (desktop/server) with an Ethernet card to execute
    eNodeB.

-   One Linux machine (desktop/server) with two Ethernet cards to
    execute UeSim.

-   One machine (laptop/desktop) to execute the video client. This can
    be windows or Linux machine.

> Connected directly to one of the interfaces of UE simulator and must
> not have any other connectivity other than the direct connection to UE
> simulator.

-   One machine (laptop/desktop) to execute the video server. This can
    be windows or Linux machine.

-   One 8 ports gig L2 switch and 5 to 6 Ethernet cables.

    1.  Software 
        ---------

The software requirements are as follows:

-   libpcap and libpcap-devel packages v0.9.1 or later required for PGW
    and UE simulator.

-   Linux operating system with kernel version 2.6 to execute CNEs,
    eNodeB and UE simulator.

[]{#_Toc264544033 .anchor}

TeNB Directory Structure
========================

This section describes the directory structure for the TeNB code based
on PAL.

[[]{#_Toc418590645 .anchor}]{#_Toc383776989 .anchor}Figure-3: TeNB
Directory Structure

**Package information**:

In **PAL\_RSYS** directory, there are several folders.

a.  **docs** folder contains documents released with the package.

b.  **bin** folder contains:

    I.  **rsys** folder containing precompiled OAM binaries, libraries,
        TeNB binaries and configuration files (**ys\_cfg.txt**,
        **wr\_cfg.txt**, **configFile**, and **start\_TeNB**).

c.  **src** folder contains TeNB source code:

<!-- -->

I.  **tenb\_commonplatform** folder contains OAM source code and third
    party tools,

II. The other folders contain source code for LTE protocol stack layer
    corresponding to the name of the folder,

III. The **enbapp** folder contains **src** and **build** folders.

IV. The **lteremapp** folder contains files for REM Application and REM
    convergence layer. REM convergence layer file is under the
    **lteremapp/remcl** folder.

<!-- -->

a.  **libs** folder contains RRM library, if RRM as a source code is not
    delivered.

Building Integrated Stacks
==========================

The entities/nodes are bundled as an executable in a unique directory.

Build Core Network Emulators (Radisys CNE)
------------------------------------------

The Radisys (RSYS) CNE binaries for MME, SGW, and PGW simulation can be
built on any Linux machine.

1.  ### MME

    1.  #### Product Feature Flags

LTE MME Reference Application supports features that are conditionally
compiled.

The compile-time flags that are enabled to invoke the corresponding
features are as follows.

[[]{#_Toc418590656 .anchor}]{#_Toc383776999 .anchor}Table-4: MME Product
Feature Flags

  --------------------------------------------------------------------------------------------------------------------------------------------------------------
  **Flag**                        **Description**
  ------------------------------- ------------------------------------------------------------------------------------------------------------------------------
  **VB**                          MME main flag.

  **VB\_DEBUG**                   Debug flag to compile the code for debug printing in LTE MME Reference Application.

  **LCLVB**                       Loose coupling layer management flag.

  **LCLVBMILVB**                  Loose coupling from protocol stack towards stack manager.

  **LCSMMILVB**                   Loose coupling from stack manager towards protocol stack.

  **VB\_USTA**                    Alarm flag to compile the code for generating unsolicited status in LTE MME Reference Application.

  **VB\_MME**                     MME flag to compile MME support.

  **LCSMVBMILVB**                 Loose coupling from stack manager towards protocol stack.

  **VB\_PERF\_MEAS**              Performance measurement flag to compile the code to measure performance in LTE MME Reference Application.

  **VB\_MME\_AUTH**               Authentication flag to compile authentication support in LTE MME Reference Application.

  **VB\_MME\_NW\_INIT\_DETACH**   Network initiated detach procedure.

  **EG\_REL\_930**                Release-9 upgrade for eGTP.

  **EG\_PHASE2**                  Release-9 (phase 2) upgrade for eGTP.

  **VB\_SB\_SCTP**                Trillium SCTP support. Enable this flag under product options for acceptance test build (**PRDACCOPTS**) in **ve.mak** file.

  **HI\_LKSCTP**                  Kernel SCTP support.
                                  
  **CM\_LKSCTP**                  **Note**: TUCL supports Kernel SCTP version 1.0.7 only and Linux Kernel version must be between 2.6.18 and 2.6.22.

  **VB\_IMSI\_REATTACH **         To attach with the same IMSI, for which MME already has an UE context.
  --------------------------------------------------------------------------------------------------------------------------------------------------------------

[[[]{#_Toc381032841 .anchor}]{#_Toc381032744 .anchor}]{#_Toc381032648
.anchor}

#### Build MME

The makefile for building MME is **vb.mak**. Execute the following
command to build the binary:

-   **make –f vb.mak BLDENV=lnx\_acc acc**

> The build command creates the sample stack manager and sample
> application of MME, and links with the required integrated stack
> libraries (TUCL, SCTP, S1AP, and eGTP). Creates the **vb\_acc**
> executable in the **/build** directory.

1.  ### SGW

    1.  #### Product Feature Flags

LTE SGW Reference Application supports features that are conditionally
compiled.

The list of compile-time flags that are enabled to invoke the
corresponding features are as follows.

[[]{#_Toc418590657 .anchor}]{#_Toc383777000 .anchor}**Table-5: SGW
Product Feature Flags**

  **Flag**           **Description**
  ------------------ ----------------------------------------------------------------------------------------------------
  **QO**             SGW main flag.
  **QO\_DEBUG**      Debug flag to compile the code for debug printing in LTE SGW Reference Application.
  **LCLQO**          Loose coupling layer management flag.
  **LCQOMILQO**      Loose coupling from protocol stack towards stack manager.
  **LCSMMILQO**      Loose coupling from stack manager towards protocol stack.
  **QO\_USTA**       Alarm flag to compile the code for generating unsolicited status in LTE SGW Reference Application.
  **QO\_SGW**        SGW flag to compile SGW support.
  **LCSMQOMILQO**    Loose coupling from stack manager towards protocol stack.
  **EG\_REL\_930**   Release-9 upgrade for eGTP.
  **EG\_PHASE2**     Release-9 (Phase-2) upgrade for eGTP.

#### Build SGW

The makefile for building SGW is **qo.mak**. Execute the following
command to build the binary:

-   **make –f qo.mak BLDENV=lnx\_acc acc**

> The build command creates the sample stack manager and sample
> application of SGW, and links with the required integrated stack
> libraries (TUCL and eGTP). Creates the **qo\_acc** executable in the
> **/build** directory.

3.  ### PGW

    1.  #### Product Feature Flags

LTE PGW Reference Application supports features that are conditionally
compiled.

The list of compile-time flags that are enabled to invoke the
corresponding features are as follows.

[[]{#_Toc418590658 .anchor}]{#_Toc383777001 .anchor}**Table-6: PGW
Product Feature Flags**

  **Flag**           **Description**
  ------------------ -----------------------------------------------------------------------------------------------------------
  **AV**             PGW main flag.
  **LCLAV**          Loose coupling layer management flag.
  **LCAVMILAV**      Loose coupling from protocol stack towards stack manager.
  **LCSMAVMILAV**    Loose coupling from stack manager towards protocol stack.
  **AV\_USTA**       Alarm flag to compile the code for generating unsolicited status in LTE PGW Reference Application.
  **AV\_PERF**       Performance measurement flag to compile the code to measure performance in LTE PGW Reference Application.
  **EG\_REL\_930**   Release-9 upgrade for eGTP.
  **EG\_PHASE2**     Release-9 (Phase-2) upgrade for eGTP.

#### Build PGW

The makefile for building PGW is **av.mak**. PGW makes use of the
Libpcap APIs, for which the library (**libpcap.a**) must be present in
the build directory. The relevant/associated header files of this
library of PCAP must be present in the **/usr/include/** directory.
Execute the following command to build the binary:

-   **make –f av.mak BLDENV=lnx\_acc acc**

> The build command creates the sample stack manager and sample
> application of PGW, and links with the required integrated stack
> libraries (TUCL and eGTP). Creates the **av\_acc** executable in the
> **/build** directory.

2.  Build TeNB
    ----------

    1.  ### Product Feature Flags

The list of mandatory flags enabled in TeNB integrated solution
validations are as follows.

End-to-end validation of TeNB is performed only when all these flags are
enabled. Validation of integrated solution when keeping a sub-set of
these flags disabled is un-deterministic.

[]{#_Toc418590659 .anchor}Table-: TeNB Product Feature Flags

  ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  **Flag**                   **Description**
  -------------------------- ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  **SI\_NEW**                SIBs for cell selection or reselection.

  **RGR\_SI\_SCH**           Enabled along with SI\_NEW for SIBs cell selection or reselection. When the flags are enabled, the SIB3, SIB4, and SIB5 used for cell selection or reselection by the UE are sent.

  **WR\_RELAY**              Relay of RRC to S1AP and S1AP to RRC. This flag needs to be enabled always.

  **EU\_DAT\_APP**           Relay of PDCP to eGTP-u and eGTP-u to PDCP. This flag needs to be enabled always.

  **EGTP\_U**                eGTP-u functionality.

  **KW\_PDCP**               Conditionally compiles code to allow stack to support the LTE PDCP protocol.

  **KW**                     Conditionally compiles code to allow stack to support the LTE RLC protocol.

  **LCEGUIEGT**              EGT interface.

  **LCWRLICTF**              CTF interface.

  **LCWRLINHU**              MAC interface.

  **LCPJUIPJU**              PDCP interface.

  **HI\_MULTI\_THREADED**    TUCL in multi-threaded mode. The S\_SINGLE\_THREADED flag must not be defined.

  **SS\_M\_PROTO\_REGION**   Multi-region support from SSI.

  **RGR\_RRM\_TICK**         TTI ticks to RRM (that is, TeNB application) by LTE MAC layer.

  **LTE\_LNX\_AFFINITY**     Affinity \[CPU/processor\] set for different system threads on Linux.

  **LTEMAC\_MIMO**           Multiple Input Multiple Output.

  **LSZV1**                  Release-9 upgrade for S1AP.

  **SS\_TICKS\_SEC**         Tick resolution for timers.
                             
                             If SS\_TICKS\_SEC=10 it means resolution is 100 milli seconds (ms).
                             
                             If SS\_TICKS\_SEC=100 it means resolution is 10 ms (default configuration).
                             
                             If SS\_TICKS\_SEC=1000 it means resolution is 1 ms.
                             
                             (1/SS\_TICKS\_SEC) ~\*~ 1000 gives the resolution unit in terms of ms.

  **LTE\_HO\_SUPPORT**       S1 handover and X2 handover support.

  **WR\_SB\_SCTP**           Trillium SCTP support.
                             
                             To avail this feature, need to enable this flag under product options for acceptance test build (PRDACCOPTS) in ve.mak file.

  **LTEMAC\_DRX**            DRX functionality. UEs which support the long DRX are configured with the values set in the wr\_cfg.txt configuration file. The values are common for all the UEs.

  **WR\_RSYS\_OAM**          OAM functionality.

  **WR\_RSYS\_KPI**          KPI functionality.

  **SS\_DIAG**               Logging support.

  **RM\_INTF**               RRM functionality and must be enabled always.

  **SS\_RBUF**               Ring Buffer optimization.
  ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

The list of optional flags enabled in TeNB integrated solution
validations are as follows.

  **Flag**                 **Description**
  ------------------------ ---------------------------------------------------------
  **DEBUGP**               Debug prints on the screen.
  **LTE\_ENB\_PAL**        Physical Abstraction Layer (that is, IP communication).
  **TENB\_AS\_SECURITY**   Access Stratum Security.

### Building TeNB Integrated Stack for Linux

The eNodeB integrated stack binary for Linux is built on any Linux
machine.

***Build TeNB without OAM***

-   Execute the following command to go to **eNodeB** compilation
    > directory.

<!-- -->

-   **cd src/enbapp/build**

<!-- -->

-   Execute the following command to build without OAM.

<!-- -->

-   **make tenb**

> The build command internally invokes **enodeb\_pal\_lnx.mak** makefile
> with\
> ‘**acc BLDENV=lnx\_split**’ build environment and creates the
> **enodeb** binary in **src/enbapp/build/obj** directory.

-   Execute the following command to clean up the binary and object
    > files of TeNB.

<!-- -->

-   **make clean**

***Build TeNB with OAM***

-   Execute the following command to go to **eNodeB** compilation
    > directory.

<!-- -->

-   **cd src/enbapp/build**

<!-- -->

-   Execute the following command to build with OAM.

<!-- -->

-   **make tenb\_oam**

> The build command compiles and copies **enodeb** binary with OAM to
> the **/rsys** directory.

-   Execute the following command to clean up the OAM libraries and OAM
    > object files along with all other object files.

<!-- -->

-   **make clean**

Configuring Radisys CNE and TeNB
================================

The following sections explain the various configuration files and
details to be considered before executing various binaries at different
nodes.

1.  Configuration Settings for Core Network Emulators
    -------------------------------------------------

    1.  ### Configuration Settings for MME

<!-- -->

1.  Go to the executable directory of MME where the **vb\_acc** binary
    > is present.

2.  The **vbsm\_cfg.txt** and **vb\_hss\_ue.db** files must be present
    > in the **/mme** directory of MME.

3.  Edit the **vbsm\_cfg.txt** file and update the following IP
    > addresses for demonstration purpose:

<!-- -->

i.  **VBSM\_ENB\_ADDR**: Provide IP address of server with eNodeB
    executable.

ii. **VBSM\_MME\_IPADDR**: Provide IP address of server with MME
    executable.

iii. **VBSM\_SGW\_IP\_ADDR**: Provide IP address of server with SGW
    executable.

iv. **VBSM\_PGW\_IP\_ADDR**: Provide IP address of server with PGW
    executable.

[]{#_Toc418590660 .anchor}**Table-8: vbsm\_cfg.txt Configuration File**

  ---------------------------------------------------------------------------------------------------------------------------------------
  **Parameters **                      > **Value **      > **Description **
  ------------------------------------ ----------------- --------------------------------------------------------------------------------
  > VBSM\_EG\_DFLT\_PORT               > 2123            > eGTP default port

  > VBSM\_EG\_NONDFLT\_PORT            > 2124            > eGTP non default port

  > VBSM\_EG\_DFLT\_HOST\_NAME         > egtp.rsys.com   > eGTP host name

  > VBSM\_ENB\_ADDR                    > 172.26.2.4      > IP address of eNodeB

  > VBSM\_ENB\_PORT                    > 36412           > eNodeB port

  > VBSM\_MME\_IPADDR                  > 172.26.2.1      > MME IP address

  > VBSM\_MME\_SCTP\_PORT              > 36412           > MME SCTP port

  > VBSM\_SGW\_IPADDR                  > 172.26.2.2      > SGW IP address

  > VBSM\_SGW\_PORT                    > 2123            > SGW port

  > VBSM\_PGW\_IPADDR                  > 172.26.2.3      > PGW IP address

  > VBSM\_PGW\_PORT                    > 2125            > PGW port

  > VBSM\_UE\_NUM                      > 35              > Number of UEs

  > VBSM\_SCTP\_UDP\_SERV\_TYPE        > 0               > SCTP service type

  > VBSM\_VC\_IP                       > 172.27.2.26     > VC IP address

  > VBSM\_MME\_DBG\_MASK               > 1111            > Debug mask to be set in the form:
                                                         >
                                                         > |LVB\_DBGMASK\_INFO|LVB\_DBGMA SK\_ERROR|LVB\_DBGMASK\_TRC|LVB\_DBGMASK\_MEM

  > VBSM\_DBG\_MASK                    > 0000            > Debug mask to be set in the form:
                                                         >
                                                         > |LVB\_DBGMASK\_INFO|LVB\_DBGMA SK\_ERROR|LVB\_DBGMASK\_TRC|LVB\_DBGMASK\_MEM

  > VBSM\_NW\_INIATED\_DETACH\_TIMER   > 1000            > Timer configuration value for network initiated detach procedure.

  > VBSM\_MCC\_DIG0                    > 0               > Change MCC and MNC values according to the requirement.
  >                                    >                 
  > VBSM\_MCC\_DIG1                    > 2               
  >                                    >                 
  > VBSM\_MCC\_DIG2                    > 1               
  >                                    >                 
  > VBSM\_MNC\_DIG0                    > 2               
  >                                    >                 
  > VBSM\_MNC\_DIG1                    > 1               
  >                                    >                 
  > VBSM\_MNC\_DIG2                    > f               

  > VBSM\_MME\_GRP\_ID                 > 11              > MME group ID
  >                                    >                 >
  > VBSM\_MME\_REL\_CAP                > 3               > MME relative capability value
  >                                    >                 >
  > VBSM\_MME\_CODE                    > A               > MME code (provide value in HEX).
  ---------------------------------------------------------------------------------------------------------------------------------------

**Note**: Do NOT change the order of the parameters.

> User must enter the UE details in **vb\_hss\_ue.db** file. Match with
> the required UE or UeSim under test for this setup, especially IMSI
> parameter.

### Configuration Settings for SGW 

1.  Go to the executable directory of SGW where the **qo\_acc** binary
    > is present.

2.  The **qosm\_cfg.txt** file must be present in the **/sgw** directory
    > of SGW.

3.  Edit the **qosm\_cfg.txt** file and update the following IP address
    > for demonstration purpose:

<!-- -->

i.  **QOSM\_SGW\_IP\_ADDR**: Provide IP address of server with SGW
    executable.

[]{#_Toc418590661 .anchor}**Table-9: qosm\_cfg.txt Configuration File**

  --------------------------------------------------------------------------------------------------------------------------------
  **Parameters **                > **Value **       > **Description **
  ------------------------------ ------------------ ------------------------------------------------------------------------------
  > QOSM\_EG\_C\_DFLT\_PORT      > 2123             > eGTP port

  > QOSM\_EG\_C\_S11\_PORT       > 2124             > eGTP port

  > QOSM\_EG\_C\_S5S8\_PORT      > 2125             > eGTP port

  > QOSM\_EG\_U\_DFLT\_PORT      > 2152             > SGW port

  > QOSM\_EG\_DFLT\_HOST\_NAME   > egtp1.rsys.com   > eGTP host name

  > QOSM\_SGW\_IPADDR            > 172.25.0.19      > SGW IP address

  > QOSM\_UE\_NUM                > 35               > Number of UEs

  > QOSM\_SGW\_DBG\_MASK         > 1111             > Debug mask to be set in the form:
                                                    
                                                    |LQO\_DBGMASK\_INFO|LQO\_DBGMA SK\_ERROR|LQO\_DBGMASK\_TRC|LQO\_DBGMASK\_MEM

  > QOSM\_SM\_DBG\_MASK          > 0000             > Debug mask to be set in the form:
                                                    
                                                    |LQO\_DBGMASK\_INFO|LQO\_DBGMA SK\_ERROR|LQO\_DBGMASK\_TRC|LQO\_DBGMASK\_MEM
  --------------------------------------------------------------------------------------------------------------------------------

**Note**: Do NOT change the order of the parameters.

### Configuration Settings for PGW 

1.  Go to the executable directory of PGW where the **av\_acc** binary
    > is present.

2.  The **avsm\_cfg.txt** file must be present in **/pgw** directory of
    > PGW.

3.  Edit the **avsm\_cfg.txt** file and update the following IP
    > addresses for demonstration purpose:

<!-- -->

i.  **AVSM\_PGW\_DFLT\_ADDR**: Provide IP address of Server with PGW
    executable.

ii. **AVSM\_PGW\_DFLT\_EXGW\_ADDR**: Provide IP address of external
    server \[for example, Video Server (VS)\] which intends to
    communicate with PGW.

iii. **AVSM\_PGW\_UE\_START\_ADDR**: Provide IP address of server where
    UE client \[for example: Video Client (VC)\] is present. This is the
    IP address assigned by PGW for the first UE. PGW uses this IP
    address as a reference for new assignment to a new UE.

iv. **AVSM\_PGW\_IP\_NUM**: Number of IP addresses configured for UE
    clients.

> Ensure the source port number of Video server is configured with a
> port less than **AV\_PGW\_MAX\_WELL\_KNOWN\_IP\_PORT** specified in
> the **av.h** file.

[]{#_Toc418590662 .anchor}**Table-10: avsm\_cfg.txt Configuration File**

  -----------------------------------------------------------------------------------------------------------------------------------
  **Parameters **                 > **Value **       > **Description **
  ------------------------------- ------------------ --------------------------------------------------------------------------------
  > AVSM\_EG\_C\_DFLT\_PORT       > 2123             > eGTP port

  > AVSM\_EG\_C\_NONDFLT\_PORT    > 2124             > eGTP port

  > AVSM\_EG\_U\_DFLT\_PORT       > 2152             > eGTP port

  > AVSM\_EG\_DFLT\_HOST\_NAME    > egtp2.rsys.com   > eGTP host name

  > AVSM\_PGW\_DFLT\_ADDR         > 172.27.2.94      > PGW IP address

  > AVSM\_PGW\_DFLT\_EXGW\_ADDR   > 172.27.2.50      > External gateway address

  > AVSM\_PGW\_UE\_START\_ADDR    > 172.27.2.96      > Starting address of UE

  > AVSM\_PGW\_UE\_NUM            > 35               > Number of UEs supported

  > AVSM\_PGW\_IP\_NUM            > 35               > Number of PGW IP addresses

  > AVSM\_SGW\_IPADDR             > 172.27.2.93      > SGW IP address

  > AVSM\_SGW\_PORT               > 2152             > SGW port

  > AVSM\_PGW\_DBG\_MASK          > 0000             > Debug mask to be in the form:
                                                     >
                                                     > |LAV\_DBGMASK\_INFO|LAV\_DBGMASK\_ ERROR|LAV\_DBGMASK\_TRC|LAV\_DBGMASK\_MEM

  > AVSM\_DBG\_MASK               > 0000             > Debug mask to be in the form:
                                                     >
                                                     > |LAV\_DBGMASK\_INFO|LAV\_DBGMASK\_ERROR|LAV\_DBGMASK\_TRC|LAV\_DBGMASK\_MEM

  > AVSM\_INACTIVE\_TMR\_VAL      > 10000            > Inactive timer value

  > AVSM\_EXPIRY\_CNT             > 500              > Expiry count

  > AVSM\_PGW\_DNS\_ADDR          > 172.27.2.26      > DNS IP address.
  -----------------------------------------------------------------------------------------------------------------------------------

**Note**: Do NOT change the order of the parameters.

Configuration Settings for eNodeB
---------------------------------

1.  Edit the **wr\_cfg.txt** configuration file with the following
    > entries:

<!-- -->

a.  Update the following IP addresses for demonstration purpose:

<!-- -->

i.  **WR\_TAG\_ENB\_IP\_ADDR**: Provide IP address of the server
    intended to run eNodeB.

ii. **WR\_TAG\_MME\_INFO**: Provide IP address of the server intended to
    run MME.

iii. **WR\_TAG\_SCTP\_IP\_ADDR**: Provide IP address of the server
    intended to run eNodeB.

<!-- -->

a.  **WR\_TAG\_INACTIVITY\_TIMER\_VAL**: Specifies the time in
    > milliseconds (ms) after which the inactivity timer in the eNodeB
    > expires.

b.  **WR\_TAG\_MAX\_EXPIRY**: Specifies the number of expiries after
    > which the inactivity of the UE is detected.

c.  **WR\_TAG\_SCTP\_SRVC\_TYPE**: Specifies **0** for SCTP over RAW IP
    > and **1** for SCTP over UDP.

d.  Long DRX Configuration parameters: The below values are common for
    > all UEs

<!-- -->

i.  **WR\_TAG\_DRX\_ON\_DURATION\_TMR**: Enumerator used to configure
    the DRX On-Duration timer. Recommended value is 8.

ii. **WR\_TAG\_DRX\_INACTIVITY\_TMR**: Enumerator used to configure the
    DRX Inactivity timer. Recommended value is 4.

iii. **WR\_TAG\_DRX\_RETX\_TMR**: Enumerator used to configure the DRX
    Retransmission timer. Recommended value is 1.

iv. **WR\_TAG\_DRX\_LONG\_CYCLE**: Enumerator used to configure the DRX
    Long Cycle value. Recommended value is 3 (40 ms).

> It is also recommended that the DRX Long Cycle is in multiples of 10
> ms, in alignment with the CQI reporting periodicity 10, 20, 40, 80,
> and so on. The values 32, 64, 128, and so on, are not recommended. The
> maximum recommended value for DRX Long Cycle is 3 (40 ms).
>
> For example: if long duration is 20 ms, the number of unique DRX,
> CQI/RI offsets possible is 20/2 = 10. Implies that only 10 UEs get
> unique offsets. For the eleventh UE, the offset must be reused
> resulting in CQI/RI decoding failure.
>
> Recommended not to use the DRX Long Cycle values 10, 20 in this
> release.

[[]{#_Toc418590663 .anchor}]{#_Toc383777007 .anchor}**Table-11:
wr\_cfg.txt Configuration File**

+-----------------------+-----------------------+-----------------------+
| Parameters            | Value                 | Description           |
+=======================+=======================+=======================+
| WR\_TAG\_CELL\_ID     | 1                     | Cell ID               |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_OP\_MODE     | 4                     | Not applicable to PAL |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_PERIOD       | 2                     | Not applicable to PAL |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_MOD\_TYPE    | 0                     | Modulation type: BPSK |
|                       |                       | / QPSK /16QAM / 64QAM |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_TDD\_ULDL\_C | 2                     | TDD Uplink Downlink   |
| FG\_MODE              |                       | Configuration Mode    |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_TDD\_SPCL\_S | 7                     | SF configuration      |
| F\_CONFIG             |                       |                       |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_DUP\_MODE    | 1                     | Duplexing mode:       |
|                       |                       | TDD/FDD               |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_MAX\_UE\_SUP | 20                    | Maximum number of UEs |
| PORT                  |                       | that can be supported |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_MCC\_0       | 3                     | MCC0                  |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_MCC\_1       | 1                     | MCC1                  |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_MCC\_2       | 1                     | MCC2                  |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_MNC\_0       | 4                     | MNC0                  |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_MNC\_1       | 8                     | MNC1                  |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_MNC\_2       | 1                     | MNC2                  |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_TA\_CODE     | 1                     | Tracking Area Code    |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_FREQ\_BAND\_ | 7                     | Frequency Band        |
| IND                   |                       | Indicator             |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_DL\_EARFCN   | 3100                  | DL EARFCN value for   |
|                       |                       | Band-7                |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_UL\_EARFCN   | 0                     | UL EARFCN value for   |
|                       |                       | Band-7                |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_ENB\_IP\_ADD | 172.26.10.22          | Provide IP address of |
| R                     |                       | server intended to    |
|                       |                       | run eNodeB.           |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_PCI\_SELECT\ | 1                     | Enable or disable PCI |
| _TYPE                 |                       | selection type from   |
|                       |                       | SON.                  |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_PRACH\_SELEC | 1                     | Enable or disable     |
| T\_TYPE               |                       | PRACH selection type  |
|                       |                       | from SON.             |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_EARFCN\_SELE | 1                     | Enable or disable     |
| CT\_TYPE              |                       | EARFCN selection type |
|                       |                       | from SON.             |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_PCI\_LIST    | {{1,2,3,4}}           | List of PCIs from     |
|                       |                       | which SON select the  |
|                       |                       | serving PCI.          |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_DL\_EARFCN\_ | {{3100}}              | DL-EARFCN list from   |
| LIST                  |                       | which SON selects the |
|                       |                       | serving DL-EARFCN.    |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_UL\_EARFCN\_ | {{21100}}             | UL-EARFCN list from   |
| LIST                  |                       | which SON selects the |
|                       |                       | serving UL-EARFCN.    |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_ROOTSEQ\_IDX | {{823,10,18}}         | Root Sequence Index   |
| \_LIST                |                       | list from which SON   |
|                       |                       | selects the           |
|                       |                       | RootSeqIndex value.   |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_PRACHCFG\_ID | {{1,2,48}}            | PRACH Configuration   |
| X\_LIST               |                       | Index list from which |
|                       |                       | SON selects the       |
|                       |                       | PrachCfgIndex value.  |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_ZERO\_CORR\_ | {{8,10,14}}           | Zero Correlation Zone |
| ZONE\_CFG\_LIST       |                       | Configuration list    |
|                       |                       | from which SON        |
|                       |                       | selects the           |
|                       |                       | ZeroCorrZoneCfg       |
|                       |                       | value.                |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_PRACH\_FREQ\ | {{1,5}}               | PRACH Frequency       |
| _OFFSET\_LIST         |                       | Offset list from      |
|                       |                       | which SON selects the |
|                       |                       | PrachFreqOffset       |
|                       |                       | value.                |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_ROOTSEQ\_IDX | 823                   | Configured            |
|                       |                       | RootSeqIndex value.   |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_PRACHCFG\_ID | 1                     | Configured            |
| X                     |                       | PrachCfgIndex value.  |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_ZERO\_CORR\_ | 10                    | Configured            |
| ZONE\_CFG             |                       | ZeroCorrZoneCfg       |
|                       |                       | value.                |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_PRACH\_FREQ\ | 1                     | Configured            |
| _OFFSET               |                       | PrachFreqOffset       |
|                       |                       | value.                |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_NO\_OF\_MME\ | 1                     | Number of MMEs        |
| _INFO                 |                       |                       |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_MME\_INFO    | {{1,1,                | Provide IP address of |
|                       | 172.26.10.154}}       | server intended to    |
|                       |                       | run MME.              |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_SCTP\_IP\_AD | 172.26.10.22          | Provide IP address of |
| DR                    |                       | server intended to    |
|                       |                       | run eNodeB.           |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_HI\_DBG      | 0                     | TUCL debug prints.    |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_SB\_DBG      | 0                     | SCTP debug prints.    |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_SZ\_DBG      | 0                     | S1AP debug prints.    |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_EG\_DBG      | 0                     | eGTP debug prints.    |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_WR\_DBG      | 1                     | eNBApp debug prints.  |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_NH\_DBG      | 0                     | RRC debug prints.     |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_KW\_DBG      | 0                     | PDCP debug prints.    |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_RG\_DBG      | 0                     | MAC debug prints.     |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_CZ\_DBG      | 0                     | X2AP debug prints.    |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_YS\_DBG      | 0                     | Convergence Layer     |
|                       |                       | debug prints.         |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_SM\_DBG      | 1                     | Layer Manger debug    |
|                       |                       | prints.               |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_INACTIVITY\_ | 20000                 | Specifies the time in |
| TIMER\_VAL            |                       | milliseconds after    |
|                       |                       | which inactivity      |
|                       |                       | timer in the eNodeB   |
|                       |                       | expires.              |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_END\_MARKER\ | 10                    | Specifies the time in |
| _TIMER\_VAL           |                       | milliseconds for end  |
|                       |                       | marker packet value.  |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_MAX\_EXPIRY  | 30                    | Specifies the number  |
|                       |                       | of expiries after     |
|                       |                       | which the inactivity  |
|                       |                       | of the UE is          |
|                       |                       | detected.             |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_X2\_PREP\_TM | 1000000               | The time to wait for  |
| R                     |                       | reception of the      |
|                       |                       | HandoverCommand       |
|                       |                       | message after sending |
|                       |                       | the HandoverRequired  |
|                       |                       | from the eNB to the   |
|                       |                       | MME.                  |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_X2\_OVRALL\_ | 1000000               | The time to wait for  |
| TMR                   |                       | the UEContextRelease  |
|                       |                       | message from the      |
|                       |                       | Target eNB after      |
|                       |                       | receiving the         |
|                       |                       | HandoverRequestAcknow |
|                       |                       | ledge                 |
|                       |                       | message from the      |
|                       |                       | Target eNB and        |
|                       |                       | handover is complete. |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_NO\_OF\_BRDC | 1                     | Number of broadcast   |
| ST\_PLMN              |                       | PLMN IDs.             |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_PLMN\_ID\_LS | {311481}              | List of PLMN IDs.     |
| T                     |                       |                       |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_CELL\_FDD\_C | {0, 1, 2, 3}          | FDD-specific cell     |
| FG                    |                       | configuration.        |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_CELL\_TDD\_C | {0, 1, 2, 3, 4, 5}    | TDD-specific cell     |
| FG                    |                       | configuration.        |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_NO\_OF\_NGH\ | INVLD                 | Number of neighbors’  |
| _INFO                 |                       | information.          |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_NGH\_INFO\_C | INVLD                 | Configuration of      |
| FG                    |                       | neighbor information. |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_NO\_OF\_GU\_ | 1                     | Number of MME groups. |
| GRP                   |                       |                       |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_GU\_GRP\_ID\ | {{0, 1}}              | List of MME group IDs |
| _CFG                  |                       | to be connected to    |
|                       |                       | the eNB.              |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_S1\_PREP\_TM | 100000                | The time to wait for  |
| R                     |                       | reception of the      |
|                       |                       | HandoverCommand       |
|                       |                       | message after sending |
|                       |                       | the HandoverRequired  |
|                       |                       | from the eNB to the   |
|                       |                       | MME.                  |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_S1\_OVRALL\_ | 100000                | The time to wait for  |
| TMR                   |                       | the                   |
|                       |                       | UEContextReleaseComma |
|                       |                       | nd                    |
|                       |                       | message from the MME  |
|                       |                       | after the             |
|                       |                       | HandoverCommand       |
|                       |                       | message from the eNB  |
|                       |                       | is received by the    |
|                       |                       | MME and handover is   |
|                       |                       | complete.             |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_MEAS\_CFG\_E | 1                     | Measurement           |
| NB                    |                       | configuration.        |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_RRM\_RNTI\_S | 205                   | Start RNTI for RRM.   |
| TRT                   |                       |                       |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_MAX\_RRM\_RN | 20                    | Maximum RNTIs managed |
| TIS                   |                       | by RRM.               |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_MAC\_RNTI\_S | 61                    | Start RNTI for MAC.   |
| TRT                   |                       |                       |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_MAX\_MAC\_RN | 35                    | Maximum RNTIs managed |
| TIS                   |                       | by MAC.               |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_RRM\_NO\_OF\ | 10                    | Dedicated preambles   |
| _DED\_PREMBL          |                       | for RRM.              |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_RRM\_DED\_PR | 41                    | Initial random access |
| EMBL\_STRT            |                       | preamble ID for RRM.  |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_MAC\_NO\_OF\ | 6                     | Number of             |
| _PREMBL               |                       | non-dedicated         |
|                       |                       | preambles.            |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_A1\_RSRP\_TH | 90                    | Threshold value for   |
| RSHLD\_VAL            |                       | the event A1.         |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_A2\_RSRP\_TH | 6                     | Threshold value for   |
| RSHLD\_VAL            |                       | the event A2.         |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_INTRA\_A5\_R | 65                    | Threshold-1 value for |
| SRP\_THRSHLD1\_VAL    |                       | event A5              |
|                       |                       | (Intra-frequency).    |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_INTRA\_A5\_R | 70                    | Threshold-2 value for |
| SRP\_THRSHLD2\_VAL    |                       | event A5              |
|                       |                       | (Intra-frequency).    |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_INTER\_A5\_R | 65                    | Threshold-1 value for |
| SRP\_THRSHLD1\_VAL    |                       | the event A5          |
|                       |                       | (Inter-frequency).    |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_INTER\_A5\_R | 70                    | Threshold-2 value for |
| SRP\_THRSHLD2\_VAL    |                       | the event A5          |
|                       |                       | (Inter-frequency).    |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_INTRA\_HO\_A | 10                    | Event A3 offset for   |
| 3\_OFFSET             |                       | HO. Offset value is   |
|                       |                       | 10.                   |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_INTRA\_ANR\_ | 5                     | Event A3 offset for   |
| A3\_OFFSET            |                       | ANR. Offset value is  |
|                       |                       | 5.                    |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_INTER\_ANR\_ | 75                    | Threshold-1 value for |
| A5\_RSRP\_THRSD1\_VAL |                       | ANR event A5          |
|                       |                       | (Inter-frequency).    |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_INTER\_ANR\_ | 50                    | Threshold-2 value for |
| A5\_RSRP\_THRSD2\_VAL |                       | ANR event A5          |
|                       |                       | (Inter-frequency).    |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_ANR\_REPORT\ | 3                     | ANR report            |
| _CFG\_VAL             |                       | configuration.        |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 0 = No ANR,           |
|                       |                       |                       |
|                       |                       | 1 = Intra-frequency   |
|                       |                       | ANR event,            |
|                       |                       |                       |
|                       |                       | 3 = Periodical ANR    |
|                       |                       | (default),            |
|                       |                       |                       |
|                       |                       | 4 = Intra- and        |
|                       |                       | Inter-frequency ANR   |
|                       |                       | event.                |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_HO\_REPORT\_ | 1                     | Handover report       |
| CFG\_VAL              |                       | configuration.        |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 1 = Event A3,         |
|                       |                       |                       |
|                       |                       | 2 = Event A5.         |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_ANR\_EPOC\_T | 1000                  | EPOCH timer values.   |
| MR\_VAL\_IN\_SECS     |                       |                       |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_ANR\_TRICE\_ | 10                    | TRICE timer value =   |
| INTV\_COUNT           |                       | EPOCH timer value /   |
|                       |                       | TRICE interval count. |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_S\_MEASURE\_ | 0                     | S-Measure value for   |
| VAL                   |                       | measurement           |
|                       |                       | configuration.        |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_INTRA\_TTT\_ | 7                     | Time to trigger value |
| VAL                   |                       | for event measurement |
|                       |                       | configuration.        |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_INTRA\_HYTER | 1                     | Hysteresis value for  |
| ISIS                  |                       | event measurement     |
|                       |                       | configuration.        |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_NO\_OF\_NGH\ | INVLD                 | Number of neighbor    |
| _ENB\_CFG             |                       | eNodeBs configured.   |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_NGH\_ENB\_CF | INVLD                 | Neighbor eNodeB       |
| G                     |                       | configuration.        |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_PCI\_VAL     | 1                     | Physical Cell ID.     |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_DL\_NUM\_UE\ | 1                     | Configuring number of |
| _PER\_TTI             |                       | UEs per TTI for DL.   |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 1 = Minimum value     |
|                       |                       | (default),            |
|                       |                       |                       |
|                       |                       | 4 = Maximum value.    |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_UL\_NUM\_UE\ | 1                     | Configuring number of |
| _PER\_TTI             |                       | UEs per TTI for UL.   |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 1 = Minimum value     |
|                       |                       | (default),            |
|                       |                       |                       |
|                       |                       | 4 = Maximum value.    |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_MAX\_DL\_NUM | 1                     | Configuring maximum   |
| \_UE\_PER\_TTI        |                       | number of UEs per TTI |
|                       |                       | for DL.               |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 1 = Minimum value     |
|                       |                       | (default),            |
|                       |                       |                       |
|                       |                       | 4 = Maximum value.    |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_MAX\_UL\_NUM | 1                     | Configuring maximum   |
| \_UE\_PER\_TTI        |                       | number of UEs per TTI |
|                       |                       | for UL.               |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 1 = Minimum value     |
|                       |                       | (default),            |
|                       |                       |                       |
|                       |                       | 4 = Maximum value.    |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_DL\_SCHD\_TY | 2                     | Configuring DL        |
| PE                    |                       | Scheduler type:       |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 1 = PFS,              |
|                       |                       |                       |
|                       |                       | 2 = RR (default).     |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_UL\_SCHD\_TY | 2                     | Configuring UL        |
| PE                    |                       | Scheduler type.       |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 1 = PFS,              |
|                       |                       |                       |
|                       |                       | 2 = RR (default).     |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_DLFS\_SCHD\_ | 1                     | Enable/disable DLFSS  |
| TYPE                  |                       | feature.              |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 0 = Disable DLFSS,    |
|                       |                       |                       |
|                       |                       | 1 = Enable DLFSS.     |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_MAX\_X2\_PEE | 5                     | Maximum number of     |
| RS                    |                       | X2AP peers.           |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_X2\_TIME\_TO | 200000                | The Time-to-Wait      |
| \_WAIT                |                       | value included in the |
|                       |                       | X2SetupFailure        |
|                       |                       | message sent by the   |
|                       |                       | eNB that receives an  |
|                       |                       | X2SetupRequest        |
|                       |                       | message.              |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_SCTP\_SRVC\_ | 0                     | SCTP service type.    |
| TYPE                  |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 0 = SCTP over RAW IP, |
|                       |                       |                       |
|                       |                       | 1 = SCTP over UDP.    |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_DIAG\_TUCL   | {{0, 10}}             | Enable/disable and    |
|                       |                       | log level             |
|                       |                       | configuration for     |
|                       |                       | TUCL.                 |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 0 = Disable the log,  |
|                       |                       |                       |
|                       |                       | 1 = Enable the log,   |
|                       |                       |                       |
|                       |                       | 10 = Number of levels |
|                       |                       | that must be enabled. |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_DIAG\_S1AP   | {{0, 10}}             | Enable/disable and    |
|                       |                       | log level             |
|                       |                       | configuration for     |
|                       |                       | S1AP.                 |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 0 = Disable the log,  |
|                       |                       |                       |
|                       |                       | 1 = Enable the log,   |
|                       |                       |                       |
|                       |                       | 10 = Number of levels |
|                       |                       | that must be enabled. |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_DIAG\_EGTP   | {{0, 10}}             | Enable/disable and    |
|                       |                       | log level             |
|                       |                       | configuration for     |
|                       |                       | eGTP-c.               |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 0 = Disable the log,  |
|                       |                       |                       |
|                       |                       | 1 = Enable the log,   |
|                       |                       |                       |
|                       |                       | 10 = Number of levels |
|                       |                       | that must be enabled. |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_DIAG\_LTERLC | {{0, 10}}             | Enable/disable and    |
|                       |                       | log level             |
|                       |                       | configuration for LTE |
|                       |                       | RLC.                  |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 0 = Disable the log,  |
|                       |                       |                       |
|                       |                       | 1 = Enable the log,   |
|                       |                       |                       |
|                       |                       | 10 = Number of levels |
|                       |                       | that must be enabled. |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_DIAG\_LTEPDC | {{0, 10}}             | Enable/disable and    |
| P                     |                       | log level             |
|                       |                       | configuration for LTE |
|                       |                       | PDCP.                 |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 0 = Disable the log,  |
|                       |                       |                       |
|                       |                       | 1 = Enable the log,   |
|                       |                       |                       |
|                       |                       | 10 = Number of levels |
|                       |                       | that must be enabled. |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_DIAG\_LTECL  | {{0, 10}}             | Enable/disable and    |
|                       |                       | log level             |
|                       |                       | configuration for LTE |
|                       |                       | CL.                   |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 0 = Disable the log,  |
|                       |                       |                       |
|                       |                       | 1 = Enable the log,   |
|                       |                       |                       |
|                       |                       | 10 = Number of levels |
|                       |                       | that must be enabled. |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_DIAG\_LTEMAC | {{0, 10}}             | Enable/disable and    |
|                       |                       | log level             |
|                       |                       | configuration for LTE |
|                       |                       | MAC.                  |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 0 = Disable the log,  |
|                       |                       |                       |
|                       |                       | 1 = Enable the log,   |
|                       |                       |                       |
|                       |                       | 10 = Number of levels |
|                       |                       | that must be enabled. |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_DIAG\_LTEX2A | {{0, 10}}             | Enable/disable and    |
| P                     |                       | log level             |
|                       |                       | configuration for LTE |
|                       |                       | X2AP.                 |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 0 = Disable the log,  |
|                       |                       |                       |
|                       |                       | 1 = Enable the log,   |
|                       |                       |                       |
|                       |                       | 10 = Number of levels |
|                       |                       | that must be enabled. |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_DIAG\_SCTP   | {{0, 10}}             | Enable/disable and    |
|                       |                       | log level             |
|                       |                       | configuration for     |
|                       |                       | SCTP.                 |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 0 = Disable the log,  |
|                       |                       |                       |
|                       |                       | 1 = Enable the log,   |
|                       |                       |                       |
|                       |                       | 10 = Number of levels |
|                       |                       | that must be enabled. |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_SCTP\_RTO\_M | 100                   | SCTP RTO minimum      |
| IN                    |                       | value (100).          |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_SCTP\_RTO\_M | 1000                  | SCTP RTO maximum      |
| AX                    |                       | value (1000).         |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_SCTP\_RTO\_I | 200                   | SCTP RTO initial      |
| NITIAL                |                       | value (200).          |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_SCTP\_HRTBEA | 5000                  | SCTP heartbeat        |
| T\_INTERVAL           |                       | interval value        |
|                       |                       | (5000).               |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_UL\_ENABLE\_ | 1                     | PHY logging interval  |
| TIME                  |                       | in seconds. This      |
|                       |                       | parameter is used to  |
|                       |                       | enable logging period |
|                       |                       | for PHY.              |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_NUM\_EUTRA\_ | 3                     | Number of E-UTRA      |
| FREQ                  |                       | frequencies.          |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_EUTRA\_FREQ\ | {{5230, 23230},       | List of E-UTRA        |
| _CFG                  | {2600, 20600}, {3100, | frequency             |
|                       | 21100}}               | configurations.       |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_NUM\_UTRA\_F | 2                     | Number of UTRA        |
| REQ                   |                       | frequencies.          |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_UTRA\_FREQ\_ | {{10713, 23230},      | List of UTRA          |
| CFG                   | {10714, 23231}}       | frequency             |
|                       |                       | configurations.       |
|                       |                       |                       |
|                       |                       | Parameter contains    |
|                       |                       | list of DL ARFCN, UL  |
|                       |                       | ARFCN values. For     |
|                       |                       | example:              |
|                       |                       |                       |
|                       |                       | 10713 = DL ARFCN,     |
|                       |                       |                       |
|                       |                       | 23230 = UL ARFCN.     |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_NO\_OF\_NGH\ | 2                     | Number of target base |
| _CFG                  |                       | stations for          |
|                       |                       | multi-target          |
|                       |                       | preparation during    |
|                       |                       | handover. Maximum of  |
|                       |                       | four eNBs can be      |
|                       |                       | prepared. If the      |
|                       |                       | value entered is 1,   |
|                       |                       | the multi-target      |
|                       |                       | preparation is not    |
|                       |                       | executed.             |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_NGH\_CELL\_C | {{1, 172.27.3.95,     | List of neighbor cell |
| FG                    | 141, 1, 1, 8, 3100,   | configurations.       |
|                       | 21100, 0, 1, 0}, {0,  |                       |
|                       | 172.27.2.101, 142, 1, | The parameter values  |
|                       | 67, 45006, 2600,      | are:                  |
|                       | 20600, 0, 1, 0}}      |                       |
|                       |                       | 1 = Home eNB (eNodeB  |
|                       |                       | type) or 0 = Macro,   |
|                       |                       |                       |
|                       |                       | 172.27.3.95 = IP      |
|                       |                       | address,              |
|                       |                       |                       |
|                       |                       | 141 = Physical Cell   |
|                       |                       | Identity,             |
|                       |                       |                       |
|                       |                       | 1 = TAC,              |
|                       |                       |                       |
|                       |                       | 1 = Cell ID,          |
|                       |                       |                       |
|                       |                       | 21901 = PLMN ID,      |
|                       |                       |                       |
|                       |                       | 3100 = DL ARFCN,      |
|                       |                       |                       |
|                       |                       | 1100 = UL ARFCN,      |
|                       |                       |                       |
|                       |                       | 0 = Disabled (is X2   |
|                       |                       | required) or 1 =      |
|                       |                       | Enabled,              |
|                       |                       |                       |
|                       |                       | 0 = Start RB,         |
|                       |                       |                       |
|                       |                       | 24 = End RB.          |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_NO\_OF\_UTRA | 2                     | Number of UTRA        |
| \_NGH\_CFG            |                       | neighbor              |
|                       |                       | configurations.       |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_NGH\_UTRA\_C | {{10,70,10713,23230,6 | List of UTRA cell     |
| ELL\_CFG              | ,1,21901,145,45},{20, | configurations.       |
|                       | 71,10714,23231,10,1,2 |                       |
|                       | 1901,150,50.0}}       | The parameter values  |
|                       |                       | are:                  |
|                       |                       |                       |
|                       |                       | 10 = RNC ID,          |
|                       |                       |                       |
|                       |                       | 70 = Cell ID,         |
|                       |                       |                       |
|                       |                       | 172.27.2.100 = eNB IP |
|                       |                       | address,              |
|                       |                       |                       |
|                       |                       | 10713 = DL ARFCN,     |
|                       |                       |                       |
|                       |                       | 23230 = UL ARFCN.     |
|                       |                       |                       |
|                       |                       | 0 = RIM support flag, |
|                       |                       | disabled by default,  |
|                       |                       | change it to 1 to     |
|                       |                       | enable it.            |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_NUM\_CDMA\_1 | 1                     | Number of CDMA 1xRTT  |
| XRTT\_BAND\_CLS       |                       | band classes.         |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_CDMA\_1XRTT\ | {{1,1,1,1}}           | CDMA 1xRTT band       |
| _BAND\_CLS            |                       | class.                |
|                       |                       |                       |
|                       |                       | The parameter values  |
|                       |                       | are:\                 |
|                       |                       | Parameter 1 = Band    |
|                       |                       | class,                |
|                       |                       |                       |
|                       |                       | Parameter 2 = Cell    |
|                       |                       | reselector,           |
|                       |                       |                       |
|                       |                       | Parameter 3 = Maximum |
|                       |                       | threshold value,      |
|                       |                       |                       |
|                       |                       | Parameter 4 = Minimum |
|                       |                       | threshold value.      |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_NUM\_CDMA\_1 | 1                     | Number of neighbor    |
| XRTT\_NEIGH\_FREQ     |                       | CDMA 1xRTT frequency  |
|                       |                       | configurations.       |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_CDMA\_1XRTT\ | {{1,1000,1}}          | Neighbor CDMA 1xRTT   |
| _NEIGH\_FREQ          |                       | frequency             |
|                       |                       | configuration.        |
|                       |                       |                       |
|                       |                       | The parameter values  |
|                       |                       | are:\                 |
|                       |                       | Parameter 1 = Band    |
|                       |                       | class,                |
|                       |                       |                       |
|                       |                       | Parameter 2 = ARFCN,  |
|                       |                       |                       |
|                       |                       | Parameter 3 =         |
|                       |                       | Frequency priority.   |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_NUM\_CDMA\_1 | 1                     | Number of CDMA 1xRTT  |
| XRTT\_NEIGH\_CELL     |                       | neighbor cells.       |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_CDMA\_1XRTT\ | {{1,1000,1,1,1}}      | Neighbor CDMA 1xRTT   |
| _NEIGH\_CELL          |                       | cell configuration.   |
|                       |                       |                       |
|                       |                       | The parameter values  |
|                       |                       | are:\                 |
|                       |                       | Parameter 1 = Band    |
|                       |                       | class,                |
|                       |                       |                       |
|                       |                       | Parameter 2 = ARFCN,  |
|                       |                       |                       |
|                       |                       | Parameter 3 = PN      |
|                       |                       | offset,               |
|                       |                       |                       |
|                       |                       | Parameter 4 = Current |
|                       |                       | rank,                 |
|                       |                       |                       |
|                       |                       | Parameter 5 =         |
|                       |                       | Neighbor cell flag.   |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_CSFB\_UTRA\_ | 0                     | CSFB to UTRA          |
| CFG\_VAL              |                       | configuration.        |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 0 = CSFB to UTRA      |
|                       |                       | without Measurement,  |
|                       |                       |                       |
|                       |                       | 1 = CSFB to UTRA with |
|                       |                       | Measurement.          |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_CSFB\_CDMA\_ | 0                     | CSFB to CDMA          |
| CFG\_VAL              |                       | configuration.        |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 0 = CSFB to 1xRTT     |
|                       |                       | without Measurement,  |
|                       |                       |                       |
|                       |                       | 1 = CSFB to 1xRTT     |
|                       |                       | with Measurement.     |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_ECSFB\_CFG\_ | 0                     | eCSFB configuration.  |
| VAL                   |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 0 = eCSFB not         |
|                       |                       | supported,            |
|                       |                       |                       |
|                       |                       | 1 = eCSFB without     |
|                       |                       | Measurement,          |
|                       |                       |                       |
|                       |                       | 2 = eCSFB with        |
|                       |                       | Measurement.          |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_DUAL\_RX\_SU | 1                     | Enable/disable Dual   |
| PPORTED               |                       | Rx.                   |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_AS\_PRI\_INT | {1}                   | Enable/disable        |
| G\_ALGO\_LST          |                       | Integrity protection  |
|                       |                       | on AS Security.       |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 0 = EIA0,             |
|                       |                       |                       |
|                       |                       | 1 = 128-EIA1          |
|                       |                       | (SNOW3G),             |
|                       |                       |                       |
|                       |                       | 2 = 128-EIA2 (AES).   |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_AS\_PRI\_CIP | {0}                   | Enable/disable        |
| H\_ALGO\_LST          |                       | Ciphering on AS       |
|                       |                       | Security.             |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 0 = EEA0,             |
|                       |                       |                       |
|                       |                       | 1 = 128-EEA1          |
|                       |                       | (SNOW3G),             |
|                       |                       |                       |
|                       |                       | 2 = 128-EEA2 (AES).   |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_A3\_OFFSET   | -6                    | Event A3 offset for   |
|                       |                       | eNB.                  |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | -30 = Minimum value,  |
|                       |                       |                       |
|                       |                       | 30 = Maximum value.   |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_PICO\_OFFSET | 20                    | Cell-specific offset  |
|                       |                       | for neighbor eNB\     |
|                       |                       | (Q-Offset Range).     |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | -24db = Minimum       |
|                       |                       | value,                |
|                       |                       |                       |
|                       |                       | 24db = Maximum value. |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_ABS\_PATTERN | 2                     | ABS subframes pattern |
| \_TYPE                |                       | type to transmit or   |
|                       |                       | mute.                 |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | RGR\_ABS\_TRANSMIT    |
|                       |                       | for a pico eNB,       |
|                       |                       |                       |
|                       |                       | RGR\_ABS\_MUTE for a  |
|                       |                       | macro eNB.            |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_ABS\_PATTERN | 010101010101010101010 | ABS pattern type to   |
|                       | 1010101010101010101   | mute or transmit over |
|                       |                       | 4 subframes.          |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_ABS\_LOAD\_P | 0                     | Periodicity of ABS    |
| ERIODICITY            |                       | pattern negotiation   |
|                       |                       | with peer eNodeBs.    |
|                       |                       | Value “0” is for OAM  |
|                       |                       | mode ABS pattern      |
|                       |                       | configuration.        |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_SFR\_START\_ | 25                    | Starting PRB of Cell  |
| RB                    |                       | edge bandwidth.       |
|                       |                       |                       |
|                       |                       | Range: 0 to 99,       |
|                       |                       | default is 25.        |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_SFR\_END\_RB | 49                    | Ending PRB of Cell    |
|                       |                       | edge bandwidth.       |
|                       |                       |                       |
|                       |                       | Range: 0 to 99,       |
|                       |                       | default is 49.        |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_SFR\_POWER\_ | 4                     | Power level for cell  |
| LOW                   |                       | center UE.            |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 0 = dB-6,             |
|                       |                       |                       |
|                       |                       | 1 = dB-4dot77,        |
|                       |                       |                       |
|                       |                       | 2 = dB-3,             |
|                       |                       |                       |
|                       |                       | 3 = dB-1dot77,        |
|                       |                       |                       |
|                       |                       | 4 = dB0 (default),    |
|                       |                       |                       |
|                       |                       | 5 = dB1,              |
|                       |                       |                       |
|                       |                       | 6 = dB2,              |
|                       |                       |                       |
|                       |                       | 7 = dB3.              |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_SFR\_POWER\_ | 5                     | Power level for cell  |
| HIGH                  |                       | edge UE.              |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 0 = dB-6,             |
|                       |                       |                       |
|                       |                       | 1 = dB-4dot77,        |
|                       |                       |                       |
|                       |                       | 2 = dB-3,             |
|                       |                       |                       |
|                       |                       | 3 = dB-1dot77,        |
|                       |                       |                       |
|                       |                       | 4 = dB0,              |
|                       |                       |                       |
|                       |                       | 5 = dB1 (default),    |
|                       |                       |                       |
|                       |                       | 6 = dB2,              |
|                       |                       |                       |
|                       |                       | 7 = dB3.              |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_DRX\_ENABLED | 1                     | Enable/disable DRX    |
|                       |                       | feature.              |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 0 = Disable DRX       |
|                       |                       | feature (default),    |
|                       |                       |                       |
|                       |                       | 1 = Enable DRX        |
|                       |                       | feature.              |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_DRX\_ON\_DUR | 0 – 15                | DRX on duration timer |
| ATION\_TMR            |                       | value. psf value is   |
|                       |                       | in number of PDCCH    |
|                       |                       | sub-frames. Value of  |
|                       |                       | psf1 corresponds to 1 |
|                       |                       | PDCCH subframe.       |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 0 = psf1,             |
|                       |                       |                       |
|                       |                       | 1 = psf2,             |
|                       |                       |                       |
|                       |                       | 2 = psf3,             |
|                       |                       |                       |
|                       |                       | 3 = psf4,             |
|                       |                       |                       |
|                       |                       | 4 = psf5,             |
|                       |                       |                       |
|                       |                       | 5 = psf6,             |
|                       |                       |                       |
|                       |                       | 6 = psf8,             |
|                       |                       |                       |
|                       |                       | 7 = psf10 (default),  |
|                       |                       |                       |
|                       |                       | 8 = psf20,            |
|                       |                       |                       |
|                       |                       | 9 = psf30,            |
|                       |                       |                       |
|                       |                       | 10 = psf40,           |
|                       |                       |                       |
|                       |                       | 11 = psf50,           |
|                       |                       |                       |
|                       |                       | 12 = psf60,           |
|                       |                       |                       |
|                       |                       | 13 = psf80,           |
|                       |                       |                       |
|                       |                       | 14 = psf100,          |
|                       |                       |                       |
|                       |                       | 15 = psf200.          |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_DRX\_INACTIV | 0 – 21                | DRX inactivity timer  |
| ITY\_TMR              |                       | value. psf value is   |
|                       |                       | in number of PDCCH    |
|                       |                       | sub-frames. Value of  |
|                       |                       | psf1 corresponds to 1 |
|                       |                       | PDCCH subframe.       |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 0 = psf1,             |
|                       |                       |                       |
|                       |                       | 1 = psf2,             |
|                       |                       |                       |
|                       |                       | 2 = psf3,             |
|                       |                       |                       |
|                       |                       | 3 = psf4,             |
|                       |                       |                       |
|                       |                       | 4 = psf5,             |
|                       |                       |                       |
|                       |                       | 5 = psf6,             |
|                       |                       |                       |
|                       |                       | 6 = psf8,             |
|                       |                       |                       |
|                       |                       | 7 = psf10,            |
|                       |                       |                       |
|                       |                       | 8 = psf20(default),   |
|                       |                       |                       |
|                       |                       | 9 = psf30,            |
|                       |                       |                       |
|                       |                       | 10 = psf40,           |
|                       |                       |                       |
|                       |                       | 11 = psf50,           |
|                       |                       |                       |
|                       |                       | 12 = psf60,           |
|                       |                       |                       |
|                       |                       | 13 = psf80,           |
|                       |                       |                       |
|                       |                       | 14 = psf100,          |
|                       |                       |                       |
|                       |                       | 15 = psf200,          |
|                       |                       |                       |
|                       |                       | 16 = psf300,          |
|                       |                       |                       |
|                       |                       | 17 = psf500,          |
|                       |                       |                       |
|                       |                       | 18 = psf750,          |
|                       |                       |                       |
|                       |                       | 19 = psf1280,         |
|                       |                       |                       |
|                       |                       | 20 = psf1920,         |
|                       |                       |                       |
|                       |                       | 21 = psf2560.         |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_DRX\_RETX\_T | 0 – 7                 | DRX retransmission    |
| MR                    |                       | timer value. psf      |
|                       |                       | value is in number of |
|                       |                       | PDCCH sub-frames.     |
|                       |                       | Value of psf1         |
|                       |                       | corresponds to 1      |
|                       |                       | PDCCH subframe.       |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 0 = psf1,             |
|                       |                       |                       |
|                       |                       | 1 = psf2 (default),   |
|                       |                       |                       |
|                       |                       | 2 = psf4,             |
|                       |                       |                       |
|                       |                       | 3 = psf6,             |
|                       |                       |                       |
|                       |                       | 4 = psf8,             |
|                       |                       |                       |
|                       |                       | 5 = psf16,            |
|                       |                       |                       |
|                       |                       | 6 = psf24,            |
|                       |                       |                       |
|                       |                       | 7 = psf33.            |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_DRX\_LONG\_C | 5                     | DRX long cycle to be  |
| YCLE\_GBR             |                       | configured for an UE  |
|                       |                       | with GBR bearers.     |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_DRX\_LONG\_C | 1                     | DRX long cycle to be  |
| YCLE\_NON\_GBR        |                       | configured for an UE  |
|                       |                       | with non-GBR bearers. |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_DRX\_LONG\_C | 0 – 15                | DRX long cycle value. |
| YCLE                  |                       | sf value is in number |
|                       |                       | of subframes. Value   |
|                       |                       | of sf10 corresponds   |
|                       |                       | to 10 subframes.      |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 0 = sf10,             |
|                       |                       |                       |
|                       |                       | 1 = sf20,             |
|                       |                       |                       |
|                       |                       | 2 = sf32,             |
|                       |                       |                       |
|                       |                       | 3 = sf40 (default),   |
|                       |                       |                       |
|                       |                       | 4 = sf64,             |
|                       |                       |                       |
|                       |                       | 5 = sf80,             |
|                       |                       |                       |
|                       |                       | 6 = sf128,            |
|                       |                       |                       |
|                       |                       | 7 = sf160,            |
|                       |                       |                       |
|                       |                       | 8 = sf256,            |
|                       |                       |                       |
|                       |                       | 9 = sf320,            |
|                       |                       |                       |
|                       |                       | 10 = sf512            |
|                       |                       |                       |
|                       |                       | 11 = s1f640,          |
|                       |                       |                       |
|                       |                       | 12 = sf1024,          |
|                       |                       |                       |
|                       |                       | 13 = sf1280,          |
|                       |                       |                       |
|                       |                       | 14 = sf2048,          |
|                       |                       |                       |
|                       |                       | 15 = sf2560.          |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_ANR\_DRX\_LO | 0 – 15                | ANR specific DRX long |
| NG\_CYCLE             |                       | cycle value (default  |
|                       |                       | value is 11, which    |
|                       |                       | corresponds to        |
|                       |                       | sf640).               |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 0 = sf10,             |
|                       |                       |                       |
|                       |                       | 1 = sf20,             |
|                       |                       |                       |
|                       |                       | 2 = sf32,             |
|                       |                       |                       |
|                       |                       | 3 = sf40,             |
|                       |                       |                       |
|                       |                       | 4 = sf64,             |
|                       |                       |                       |
|                       |                       | 5 = sf80,             |
|                       |                       |                       |
|                       |                       | 6 = sf128,            |
|                       |                       |                       |
|                       |                       | 7 = sf160,            |
|                       |                       |                       |
|                       |                       | 8 = sf256,            |
|                       |                       |                       |
|                       |                       | 9 = sf320,            |
|                       |                       |                       |
|                       |                       | 10 = sf512,           |
|                       |                       |                       |
|                       |                       | 11 = sf640 (default), |
|                       |                       |                       |
|                       |                       | 12 = sf1024,          |
|                       |                       |                       |
|                       |                       | 13 = sf1280,          |
|                       |                       |                       |
|                       |                       | 14 = sf2048,          |
|                       |                       |                       |
|                       |                       | 15 = sf2560.          |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_DEFAULT\_PAG | 0                     | Default paging cycle  |
| ING\_CYCLE            |                       | value with range from |
|                       |                       | 0 to 3.               |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_DEFAULT\_PCC | 7                     | Default NB value for  |
| H\_CFG\_NB            |                       | paging configuration  |
|                       |                       | (PCCH\_CFG\_NB) with  |
|                       |                       | range from 0 to 7.    |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_BANDWIDTH    | 10                    | LTE bandwidth of 5    |
|                       |                       | MHz, 10 MHz or 20 MHz |
|                       |                       | respectively.         |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_BOOT\_MODE   | 0                     | Boot mode value set   |
|                       |                       | to zero for E-UTRAN   |
|                       |                       | Test Module (ETM)     |
|                       |                       | testing.              |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_PRIMETWS\_NO | 5                     | Primary ETWS          |
| \_BROADCAST           |                       | broadcasted value in  |
|                       |                       | hours.                |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_PRIMETWS\_RE | 10                    | Primary ETWS          |
| PETITION\_PERIOD      |                       | repetition period.    |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_WATCHDOG\_SO | 5                     | Time period in        |
| FT\_LIMIT             |                       | seconds for the       |
|                       |                       | watchdog task to      |
|                       |                       | report a problem, if  |
|                       |                       | the context is not    |
|                       |                       | responding at least   |
|                       |                       | this often.           |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_WATCHDOG\_HA | 15                    | Time period in        |
| RD\_LIMIT             |                       | seconds for the       |
|                       |                       | watchdog task to stop |
|                       |                       | responding to the     |
|                       |                       | hardware watchdog, if |
|                       |                       | the context is not    |
|                       |                       | responding at least   |
|                       |                       | this often eventually |
|                       |                       | causing the system to |
|                       |                       | reset.                |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_LOG\_PATH    | /var/log              | Path of the log files |
|                       |                       | to be stored.         |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_LOG\_FILE    | dbglog / stdout       | Log file name. If     |
|                       |                       | file name is given as |
|                       |                       | “stdout”, log         |
|                       |                       | framework prints the  |
|                       |                       | logs on console.      |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_LOG\_MAX\_FI | 5 (Maximum)           | Maximum number of log |
| LES                   |                       | files that can be     |
|                       |                       | created for storing.  |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_LOG\_FILESIZ | 3                     | Maximum file size     |
| E\_LIMIT              |                       | limit in multiples of |
|                       |                       | MB for each log file. |
|                       |                       | When log file size    |
|                       |                       | exceeds the limit,    |
|                       |                       | new log file is       |
|                       |                       | created.              |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_LOG\_LEVEL   | 2                     | There are 6 log       |
|                       |                       | levels. If log level  |
|                       |                       | is defined as 3, all  |
|                       |                       | logs with log level   |
|                       |                       | 1, 2 and 3 are logged |
|                       |                       | in the log file. If   |
|                       |                       | log level is 1, the   |
|                       |                       | log with level 1 only |
|                       |                       | is logged in the log  |
|                       |                       | file.                 |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_LOG\_MASK    | \[0\]                 | Logging for           |
|                       |                       | particular module can |
|                       | or                    | be enabled by         |
|                       |                       | specifying its module |
|                       | \[4,32,16\]           | name in module mask.  |
|                       |                       | Logging for multiple  |
|                       |                       | modules can be        |
|                       |                       | enabled by giving     |
|                       |                       | comma separated       |
|                       |                       | module numbers.       |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_LOG\_PORT    | 9999                  | Remote application    |
|                       |                       | (post processor) port |
|                       |                       | to connect to the     |
|                       |                       | eNB, collect live     |
|                       |                       | binary logs and       |
|                       |                       | display on console or |
|                       |                       | re-direct to any      |
|                       |                       | file.                 |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_LOG\_REMOTE\ | 0,1                   | Enable/disable remote |
| _LOGGING              |                       | logging.              |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 0 = Disable remote    |
|                       |                       | logging,              |
|                       |                       |                       |
|                       |                       | 1 = Enable remote     |
|                       |                       | logging.              |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_LOG\_CIRBUF\ | 1024                  | Maximum size of       |
| _SIZE                 |                       | circular buffer in    |
|                       |                       | multiples of 1 Kb or  |
|                       |                       | 1024 bytes.           |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_LOG\_COREDUM | 0,1                   | Generate core file or |
| P\_FLAG               |                       | not.                  |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 0 = Generate core     |
|                       |                       | file,                 |
|                       |                       |                       |
|                       |                       | 1 = Do not generate   |
|                       |                       | core file.            |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_INT\_FREQ\_M | 1                     | Inter-frequency       |
| EAS\_GAP              |                       | measurement gap       |
|                       |                       | value.                |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_ANR\_MEAS\_G | 1                     | ANR measurement gap   |
| AP\_CONFIG            |                       | value.                |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_NO\_OF\_EAID | 1                     | Number of EAIDs.      |
| \_INFO                |                       |                       |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_EAID\_LIST\_ | {1}                   | List of EAIDs to be   |
| INFO                  |                       | transmitted.          |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_RRM\_SR\_PRD | 3                     | Index to the SR       |
| CTY                   |                       | periodicity to be     |
|                       |                       | configured for the    |
|                       |                       | SR. Range is 0 to 6.  |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_RRM\_CQI\_PR | 4                     | Index to the CQI      |
| DCTY                  |                       | periodicity to be     |
|                       |                       | configured for the    |
|                       |                       | CQI. Range is 0 to 9. |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_RRM\_NUM\_SR | 2                     | Number of SR          |
| \_PER\_TTI            |                       | resources that can be |
|                       |                       | scheduled per TTI.    |
|                       |                       | Range is 0 to 2047.   |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_RRM\_NUM\_CQ | 2                     | Number of CQI         |
| I\_PER\_TTI           |                       | resources that can be |
|                       |                       | scheduled per TTI.    |
|                       |                       | Range is 0 to 1176.   |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_RRM\_N1\_PUC | 6                     | Number of resources   |
| CH                    |                       | reserved for N1       |
|                       |                       | PUCCH. Range is 1 to  |
|                       |                       | 8.                    |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_DRX\_QCI\_SU | 0                     | Enable/Disable        |
| PPORT\_ENABLED        |                       | Configure DRX QCI.    |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 0 = Disable DRX QCI   |
|                       |                       | (default),            |
|                       |                       |                       |
|                       |                       | 1 = Enable DRX QCI.   |
|                       |                       |                       |
|                       |                       | If this feature is    |
|                       |                       | disabled, DRX is      |
|                       |                       | enabled for QCI       |
|                       |                       | 1,2,3,4 and vice      |
|                       |                       | versa.                |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_PWS\_ETWS\_C | 0,1,2                 | PWS control for CMAS  |
| MAS\_CNTRL            |                       | and ETWS.             |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 0 = Disable PWS,      |
|                       |                       |                       |
|                       |                       | 1 = Enable PWS with   |
|                       |                       | ETWS,                 |
|                       |                       |                       |
|                       |                       | 2 = Enabled PWS with  |
|                       |                       | CMAS.                 |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_SPS\_ENABLE\ | 0,1                   | Enable/Disable SPS    |
| _FLAG                 |                       | feature.              |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 0 = Disable SPS       |
|                       |                       | (default),            |
|                       |                       |                       |
|                       |                       | 1 = Enable SPS.       |
|                       |                       |                       |
|                       |                       | **Note**: For value   |
|                       |                       | other than 1, the SPS |
|                       |                       | feature is disabled.  |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_DL\_NUM\_SPS | 1,                    | Maximum number of     |
| \_UE\_PER\_TTI        | WR\_TAG\_DL\_NUM\_UE\ | downlink SPS UE       |
|                       | _PER\_TTI             | scheduling (for       |
|                       |                       | transmission or       |
|                       |                       | retransmission) per   |
|                       |                       | TTI.                  |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | Minimum value = 1     |
|                       |                       | (default),            |
|                       |                       |                       |
|                       |                       | Maximum value =       |
|                       |                       | WR\_TAG\_DL\_NUM\_UE\ |
|                       |                       | _PER\_TTI.            |
|                       |                       |                       |
|                       |                       | **Note**: This        |
|                       |                       | parameter is          |
|                       |                       | considered only if    |
|                       |                       | SPS feature is        |
|                       |                       | enabled. For invalid  |
|                       |                       | value, the value “1”  |
|                       |                       | is configured.        |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_UL\_NUM\_SPS | 1,                    | Maximum number of     |
| \_UE\_PER\_TTI        | WR\_TAG\_UL\_NUM\_UE\ | uplink SPS UE         |
|                       | _PER\_TTI             | scheduling (for       |
|                       |                       | transmission or       |
|                       |                       | retransmission) per   |
|                       |                       | TTI.                  |
|                       |                       |                       |
|                       |                       | Minimum value = 1     |
|                       |                       | (default),            |
|                       |                       |                       |
|                       |                       | Maximum value =       |
|                       |                       | WR\_TAG\_UL\_NUM\_UE\ |
|                       |                       | _PER\_TTI.            |
|                       |                       |                       |
|                       |                       | **Note**: This        |
|                       |                       | parameter is          |
|                       |                       | considered only if    |
|                       |                       | SPS feature is        |
|                       |                       | enabled. For invalid  |
|                       |                       | value, the value “1”  |
|                       |                       | is configured.        |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_MAX\_SPS\_RB | 1 to 100              | Maximum resource      |
|                       |                       | blocks allocated for  |
|                       |                       | SPS.                  |
|                       |                       |                       |
|                       |                       | Default value = 10    |
|                       |                       |                       |
|                       |                       | **Note**: If invalid  |
|                       |                       | value is provided,    |
|                       |                       | the value is          |
|                       |                       | configured as 50% of  |
|                       |                       | the cell resource     |
|                       |                       | blocks derived from   |
|                       |                       | the cell bandwidth    |
|                       |                       | (WR\_TAG\_BANDWIDTH). |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_DSCP\_ENABLE | 0,1                   | Enable or disable     |
|                       |                       | DSCP feature.         |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 0 = Disable DSCP      |
|                       |                       | (default),            |
|                       |                       |                       |
|                       |                       | 1 = Enable DSCP.      |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_QCI\_DSCP\_M | {152,120,104,72,180,4 | QCI and DSCP values   |
| AP                    | 4,12,4,4}             | are mapped as         |
|                       |                       | follows:              |
|                       |                       |                       |
|                       |                       | (QCI,DSCP) =          |
|                       |                       | {(1,152),(2,120),(3,1 |
|                       |                       | 04),(4,72),(5,180),(6 |
|                       |                       | ,44),(7,12),(8,4),(9, |
|                       |                       | 4)}                   |
|                       |                       |                       |
|                       |                       | where:                |
|                       |                       |                       |
|                       |                       | QCI value ranges from |
|                       |                       | 1 to 9 as per 3GPP TS |
|                       |                       | 23.203.               |
|                       |                       |                       |
|                       |                       | For DSCP, the default |
|                       |                       | values are arrived    |
|                       |                       | for using the purpose |
|                       |                       | of each QCI.          |
|                       |                       |                       |
|                       |                       | **Note**: Each DSCP   |
|                       |                       | value is a            |
|                       |                       | combination of 8 bits |
|                       |                       | as follows:           |
|                       |                       |                       |
|                       |                       | Bits 7 to 5 = IP      |
|                       |                       | precedence            |
|                       |                       |                       |
|                       |                       | Bit 4 = Delay         |
|                       |                       |                       |
|                       |                       | Bit 3 = High / low    |
|                       |                       | throughput            |
|                       |                       |                       |
|                       |                       | Bit 2 = High / normal |
|                       |                       | reliability           |
|                       |                       |                       |
|                       |                       | Bit 1,0 = Unused      |
|                       |                       |                       |
|                       |                       | Refer to              |
|                       |                       | specifications: IETF  |
|                       |                       | RFC 2460, 2474, 2475  |
|                       |                       | and 3GPP TS 23.203.   |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_CSG\_CSG\_ID | 1234567               | CSG ID of the cell.   |
|                       |                       | The CSG ID of a cell  |
|                       |                       | can be 27 bits        |
|                       |                       | starting from value   |
|                       |                       | 0.                    |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_CSG\_ACCESS\ | 1,2,3                 | Operational mode for  |
| _MODE                 |                       | the cell.             |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 1 = Open access mode  |
|                       |                       | (default),            |
|                       |                       |                       |
|                       |                       | 2 = Closed access     |
|                       |                       | mode,                 |
|                       |                       |                       |
|                       |                       | 3 = Hybrid access     |
|                       |                       | mode (not supported). |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_CSG\_CSG\_PC | 1                     | Start of closed       |
| I\_START              |                       | access mode PCI       |
|                       |                       | range. The values can |
|                       |                       | be 0 to 503. The      |
|                       |                       | configured serving    |
|                       |                       | cell PCI must be      |
|                       |                       | within this range for |
|                       |                       | closed access mode.   |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_CSG\_CSG\_PC | 5                     | Number of consecutive |
| I\_RANGE              |                       | physical cell         |
|                       |                       | identities (including |
|                       |                       | Start PCI) is an      |
|                       |                       | enumeration starting  |
|                       |                       | from value 0 to 13.   |
|                       |                       |                       |
|                       |                       | As per 3GPP TS        |
|                       |                       | 36.331,\              |
|                       |                       | PhysCellIdRange =     |
|                       |                       | ENUMERATED {n4, n8,   |
|                       |                       | n12, n16, n24, n32,   |
|                       |                       | n48, n64, n84, n96,   |
|                       |                       | n128, n168, n252,     |
|                       |                       | n504, spare2,         |
|                       |                       | spare1}.              |
|                       |                       |                       |
|                       |                       | For example: The PCI  |
|                       |                       | range 5 translates to |
|                       |                       | n32 which indicates   |
|                       |                       | the number of         |
|                       |                       | physical cell         |
|                       |                       | identities (32 in     |
|                       |                       | this case) in the     |
|                       |                       | range (including      |
|                       |                       | Start PCI).           |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_CSG\_SMCELL\ | 1                     | Start PCI value of    |
| _PCI\_START           |                       | small cell PCI range. |
|                       |                       | Small cell start PCI  |
|                       |                       | value must be         |
|                       |                       | configured based on   |
|                       |                       | the configured        |
|                       |                       | serving cell PCI and  |
|                       |                       | CSG PCI start.        |
|                       |                       |                       |
|                       |                       | **Note**: The CSG PCI |
|                       |                       | range can be a        |
|                       |                       | completely distinct   |
|                       |                       | set from small cell   |
|                       |                       | PCI range or a        |
|                       |                       | sub-set of small cell |
|                       |                       | PCI range. But small  |
|                       |                       | cell PCI range cannot |
|                       |                       | and must not be       |
|                       |                       | configured as a       |
|                       |                       | subset of CSG PCI     |
|                       |                       | range.                |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_CSG\_SMCELL\ | 5                     | Range of the          |
| _PCI\_RANGE           |                       | consecutive PCI       |
|                       |                       | values starting from  |
|                       |                       | WR\_TAG\_CSG\_SMCELL\ |
|                       |                       | _PCI\_START.          |
|                       |                       | Values can range      |
|                       |                       | between from 0 to     |
|                       |                       | 503.                  |
|                       |                       |                       |
|                       |                       | **Note**: Default     |
|                       |                       | value of the          |
|                       |                       | parameter is 5 and    |
|                       |                       | small cell PCI range  |
|                       |                       | is from 1 to 6.       |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_CSG\_HENB\_N | “RADISYS”             | Indicates the HeNB    |
| AME                   |                       | name.                 |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_CNM\_ENABLE  | 0                     | Enable or disable     |
|                       |                       | Continuous Network    |
|                       |                       | Mode **Note**: For    |
|                       |                       | PAL, CNM must always  |
|                       |                       | be disabled.          |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_DCFI\_ENABLE | 0                     | Enable or disable the |
|                       |                       | Dynamic CFI feature.  |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_CFI          | 1                     | Default CFI value     |
|                       |                       | configured.           |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_RIM\_CFG     | {86400000, 5000,      | RIM configuration     |
|                       | 5000, 5000, 2}        | feature.              |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 86400000 = RIM        |
|                       |                       | overall timer value,  |
|                       |                       |                       |
|                       |                       | 5000 = RIR            |
|                       |                       | retransmission timer  |
|                       |                       | value,                |
|                       |                       |                       |
|                       |                       | 5000 = RI             |
|                       |                       | retransmission timer  |
|                       |                       | Value,                |
|                       |                       |                       |
|                       |                       | 5000 = RIAE           |
|                       |                       | retransmission timer  |
|                       |                       | value,                |
|                       |                       |                       |
|                       |                       | 2 = Maximum           |
|                       |                       | retransmission count. |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_NUM\_GERAN\_ | 4                     | Number of GERAN       |
| NEIGH\_FREQ           |                       | frequencies.          |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_GERAN\_NEIGH | {{1,92,2,255},        | Idle mode GERAN       |
| \_FREQ                | {2,512,6,255},        | neighbor cell         |
|                       | {2,800,7,255},        | information in the    |
|                       | {0,130,3,255}}        | order of:             |
|                       |                       |                       |
|                       |                       | 1, 2, 2, 0 =          |
|                       |                       | BandIndicator,        |
|                       |                       |                       |
|                       |                       | 92, 512, 800, 130 =   |
|                       |                       | BCCHARFCN,            |
|                       |                       |                       |
|                       |                       | 2, 6, 7, 3 =          |
|                       |                       | CellReselectionPriori |
|                       |                       | ty,                   |
|                       |                       |                       |
|                       |                       | 255, 255, 255, 255 =  |
|                       |                       | ncc-Permitted.        |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_GERAN\_NEIGH | {{32020,3,4,63,972,1, | Connected mode        |
| \_CELL                | 92,255,0,0},          | neighbor cell         |
|                       | {32020,3,2,62,971,2,5 | information in the    |
|                       | 12,255,0,0},          | order of:             |
|                       | {32020,3,3,61,973,2,8 |                       |
|                       | 00,255,0,0},          | 32020, 32020, 32020,  |
|                       | {32020,3,5,60,974,0,1 | 32020 = PLMNID,       |
|                       | 30,255,0,0}}          |                       |
|                       |                       | 3, 3, 3, 3 = LAC,     |
|                       |                       |                       |
|                       |                       | 4, 2, 3, 5 = RAC,     |
|                       |                       |                       |
|                       |                       | 63, 62, 61, 60 =      |
|                       |                       | BSIC,                 |
|                       |                       |                       |
|                       |                       | 972, 971, 973, 974 =  |
|                       |                       | CI,                   |
|                       |                       |                       |
|                       |                       | 1, 2, 2, 0 =          |
|                       |                       | BandIndicator,        |
|                       |                       |                       |
|                       |                       | 92, 512, 800, 130 =   |
|                       |                       | BCCHARFCN,            |
|                       |                       |                       |
|                       |                       | 255, 255, 255, 255 =  |
|                       |                       | ncc-PermittedMeas,    |
|                       |                       |                       |
|                       |                       | 0, 0, 0, 0 =          |
|                       |                       | isDTMCapbility,       |
|                       |                       |                       |
|                       |                       | 0, 0, 0, 0 =          |
|                       |                       | isRIMSupported.       |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_GERAN\_MEAS\ | {2,1,1,1000,          | GERAN measurement     |
| _CFG                  | 2500,480}             | related parameters.   |
|                       |                       |                       |
|                       |                       | Valid values are:     |
|                       |                       |                       |
|                       |                       | 2 = ReportInterval,   |
|                       |                       |                       |
|                       |                       | 1 =                   |
|                       |                       | isGERANMeasAllowedFor |
|                       |                       | CCO,                  |
|                       |                       |                       |
|                       |                       | 1 = isCCOAllowed,     |
|                       |                       |                       |
|                       |                       | 1000 =                |
|                       |                       | GERANMeasWaitTmr,     |
|                       |                       |                       |
|                       |                       | 2500 =                |
|                       |                       | T304expWaitTmrVal,    |
|                       |                       |                       |
|                       |                       | 480 =                 |
|                       |                       | rrcDatCfmWaitTmr.     |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_CELL\_SIZE\_ | 0                     | Default value of      |
| TYPE                  |                       | CellSizeType          |
|                       |                       | corresponding to very |
|                       |                       | small for UE History  |
|                       |                       | Information.          |
+-----------------------+-----------------------+-----------------------+
| WR\_TAG\_ARP\_EMER\_S | 1                     | Default value of ARP  |
| ERV                   |                       | Emergency Bearer      |
|                       |                       | configured for HRL.   |
+-----------------------+-----------------------+-----------------------+
| CFGEND                | 1                     | End of the            |
|                       |                       | configuration file.   |
+-----------------------+-----------------------+-----------------------+

[[]{#_Toc264544058 .anchor}]{#_Toc383776965 .anchor}

1.  For PAL, edit the **ys\_cfg.txt** file in the **/build** directory.

<!-- -->

a.  Update only the following IP addresses for demonstration purpose:

    i.  **YS\_IP\_ADDR\_ENB**: Provide IP address of the server intended
        > to run the eNodeB.

    ii. **YS\_IP\_ADDR\_UE**: Provide IP address of the machine intended
        > to run the UeSim.

    iii. **YS\_TTI\_TMR\_VAL\_CFG**: Configure the TTI value.

[]{#_Toc418590664 .anchor}Table-: ys\_cfg.txt Configuration File

+-----------------------+-----------------------+-----------------------+
| **Parameters**        | > **Value**           | **Descriptions**      |
+=======================+=======================+=======================+
| YS\_PORT\_ENB         | > 6789                | > eNodeB port         |
+-----------------------+-----------------------+-----------------------+
| YS\_PORT\_UE          | > 9876                | > UE port             |
+-----------------------+-----------------------+-----------------------+
| YS\_IP\_ADDR\_ENB     | > 127.0.0.1           | > eNodeB IP address   |
+-----------------------+-----------------------+-----------------------+
| YS\_IP\_ADDR\_UE      | > 127.0.0.1           | > UeSim IP address    |
|                       |                       | > towards eNodeB      |
+-----------------------+-----------------------+-----------------------+
| YS\_TTI\_TMR\_VAL\_CF | > 1000000             | > TTI value:\         |
| G                     |                       | > 1000000 --&gt; 1 ms |
|                       |                       | > TTI,\               |
|                       |                       | > 10000000 --&gt; 10  |
|                       |                       | > ms TTI              |
+-----------------------+-----------------------+-----------------------+
| WIRESHARK\_SRVR\_IP\_ | > 172.27.2.30         | > IP address of the   |
| ADDR                  |                       | > machine where       |
|                       |                       | > Wireshark is        |
|                       |                       | > intended to run     |
+-----------------------+-----------------------+-----------------------+
| YS\_CELL\_ID          | > 1                   | > eNodeB Cell ID      |
+-----------------------+-----------------------+-----------------------+

Configuration Setting of Video Client
-------------------------------------

The laptop running video client is assigned a static IP address and have
the IP address of UE simulator as its default gateway. Check route
information and verify route is created. Use the following command, for
example:

-   **route add –host &lt;IP address of VC client machine&gt; gw &lt;IP
    > address of UeSim machine&gt; dev eth0 **

    1.  Configuration Settings in CNE for Multi-UE Scenario
        ---------------------------------------------------

The configuration settings in CNE required for multi-UE scenario are as
follows:

-   **AVSM\_PGW\_UE\_NUM** and **AVSM\_PGW\_IP\_NUM** in
    **avsm\_cfg.txt** file

> Change the values to the number of UEs to be supported.

-   **VB\_HSS\_MAX\_PDN\_SUB\_CTXT** in **vb\_hss.h** file

> Change the value to the number of UEs to be supported.

-   **HSS DB UE Entries** in **vb\_hss\_ue.db** file

> Add of HSS DB entry for all the UEs with unique IMSI value.

-   **VBSM\_UE\_NUM** in **vbsm\_cfg.txt** file

> Change the value to number of UEs to be supported.

-   **UE\_NUM\_PER\_CELL** in **lteue/ue.h** file

> Set value of UE\_NUM\_PER\_CELL same as WR\_MAX\_MAC\_RNTI of
> **wr\_cfg.txt** file

-   **WR\_TAG\_MAX\_UE\_SUPPORT** in **wr\_cfg.txt** file

> Set the WR\_TAG\_MAX\_UE\_SUPPORT value more than WR\_MAX\_UE value.

-   **QOSM\_MAX\_UE** in **sgw/qosm\_cfg.txt** file

> Change the value to maximum number of UEs.

Execution of the Nodes
======================

This section describes the execution of nodes.[]{#_Ref302386398 .anchor}

Radisys CNE
-----------

Start the RSYS CNE as follows and run the corresponding binary:

a.  MME Emulator (Refer Section 6.1.1 to configure RSYS MME) and run
    > **vb\_acc** binary.

b.  SGW Emulator (Refer Section 6.1.2 to configure RSYS SGW) and run
    > **qo\_acc** binary.

c.  PGW Emulator (Refer Section 6.1.3 to configure RSYS PGW) and run
    > **av\_acc** binary.

    1.  TeNB
        ----

This section describes the execution of the Radisys TeNB software on PAL
along with RSYS CNE simulators.

TeNB without OAM
----------------

Execute the following steps to start the demonstration:

1.  **On Linux Machine 1, start the Core Network Emulators**:

<!-- -->

1.  MME Emulator (Refer Section 6.1.1 to configure RSYS MME) and run
    **vb\_acc** binary.

2.  SGW Emulator (Refer Section 6.1.2 to configure RSYS SGW) and run
    **qo\_acc** binary.

3.  PGW Emulator (Refer Section 6.1.3 to configure RSYS PGW) and run
    **av\_acc** binary.

> **Note**: For third party CNEs, start the CNE as per respective
> command.

1.  **TeNB on PAL:**

> Copy the packages (**enodeb**, **wr\_cfg.txt** and **ys\_cfg.txt**) to
> the **/root/** directory in the Linux machine.

a.  Execute the following command in **/root/** directory and convert
    > the binaries to executable mode:

    -   **chmod +x enodeb**

b.  Execute the following command to boot the eNodeB:

    -   **./enodeb **

> eNodeB console prints **TTI indication** on successful **enodeb**
> binary execution.
>
> **Note**: The order to follow is: start the CNEs, run eNodeB, and
> attach UE to bring up the setup.

### TeNB with OAM

Execute the following steps to start the demonstration:

A.  **On Linux Machine 1, start the Core Network Emulators**:

<!-- -->

1.  MME Emulator (Refer Section 6.1.1 to configure RSYS MME) and run
    > **vb\_acc** binary.

2.  SGW Emulator (Refer Section 6.1.2 to configure RSYS SGW) and run
    > **qo\_acc** binary.

3.  PGW Emulator (Refer Section 6.1.3 to configure RSYS PGW) and run
    > **av\_acc** binary.

> **Note**: For third party CNEs, start the CNE as per respective
> command.

A.  **TeNB on Linux machine:**

> The startup script (**start\_TeNB)** executes OAM components and
> eNodeB. Before starting the script, appropriate configuration must be
> provided in the **configFile** (refer Table 13) placed at the
> following path.

-   **&lt;path&gt;/rsys/configFile **

> Go to the following path and execute the **start\_TeNB** script:

-   **cd &lt;path&gt;/rsys/**

-   **. ./start\_TeNB**

[[[]{#_Toc418590665 .anchor}]{#_Ref417983897 .anchor}]{#_Ref417983901
.anchor}Table : configFile Configuration File

+-----------------------+-----------------------+-----------------------+
| **Parameters**        | > **Value**           | **Descriptions**      |
+=======================+=======================+=======================+
| OAM\_CONFIG\_FILES\_D | > ../setup            | > Path of TeNB setup  |
| IR                    |                       |                       |
+-----------------------+-----------------------+-----------------------+
| OAM\_LOGGING\_DIR     | > /root/OAM/setup/tra | > Path of logging     |
|                       | ce                    | > directory           |
+-----------------------+-----------------------+-----------------------+
| OAM\_ETHERNET\_INTERF | > eth0                | > OAM interface       |
| ACE                   |                       |                       |
+-----------------------+-----------------------+-----------------------+
| STRONGSWAN\_INSTALL\_ | > /tmp/strongswan     | > Path for Strongswan |
| DIR                   |                       | > installed directory |
|                       |                       | > and related         |
|                       |                       | > libraries           |
+-----------------------+-----------------------+-----------------------+
| STRONGSWAN\_LEFTCERT\ | > carolcert.pem       | Strongswan            |
| _FILENAME             |                       | Certificate file name |
+-----------------------+-----------------------+-----------------------+
| STRONGSWAN\_LEFT\_ID  | > radisys.smallcell-f | > Strongswan leftid   |
|                       | orum.org              | > configuration       |
+-----------------------+-----------------------+-----------------------+
| MANAGEMENT\_PASSWORD  | > Cpe                 | > HeMS User Password  |
+-----------------------+-----------------------+-----------------------+
| MANAGEMENT\_SERVER    | > <http://172.27.4.24 | > HeMS URL            |
|                       | 4:80/cpe.php>         |                       |
+-----------------------+-----------------------+-----------------------+
| MANAGEMENT\_USERNAME  | > Cpe                 | > HeMS User Name      |
+-----------------------+-----------------------+-----------------------+
| LTE\_SIGLINK\_SERVER\ | > "172.27.2.52"       | > IP address of       |
| _LIST                 |                       | > server intended to  |
|                       |                       | > run MME             |
+-----------------------+-----------------------+-----------------------+
| LTE\_DUPLEX\_MODE     | > TDDMode             | > Duplex mode:        |
|                       |                       | > TDDMode or FDDMode  |
+-----------------------+-----------------------+-----------------------+
| LTE\_BANDS\_SUPPORTED | > 40                  | > Supported bands     |
+-----------------------+-----------------------+-----------------------+
| LTE\_FREQ\_BAND\_INDI | > 40                  | > Serving band        |
| CATOR                 |                       | > indicator           |
+-----------------------+-----------------------+-----------------------+
| LTE\_DL\_EARFCN       | > 39150               | > DL-EARFCN value     |
+-----------------------+-----------------------+-----------------------+
| LTE\_UL\_EARFCN       | > 39150               | > UL-EARFCN value     |
+-----------------------+-----------------------+-----------------------+
| LTE\_RRM\_SR\_PRDCTY  | > 4                   | > Index to the SR     |
|                       |                       | > periodicity to be   |
|                       |                       | > configured for the  |
|                       |                       | > SR.\                |
|                       |                       | > Range is 0 to 6.    |
+-----------------------+-----------------------+-----------------------+
| LTE\_RRM\_CQI\_PRDCTY | > 5                   | > Index to the CQI    |
|                       |                       | > periodicity to be   |
|                       |                       | > configured for the  |
|                       |                       | > CQI.\               |
|                       |                       | > Range is 0 to 9.    |
+-----------------------+-----------------------+-----------------------+
| LTE\_RRM\_NUM\_SR\_PE | > 8                   | > Number of SR        |
| R\_TTI                |                       | > resources that can  |
|                       |                       | > be scheduled per    |
|                       |                       | > TTI.\               |
|                       |                       | > Range is 0 to 2047  |
+-----------------------+-----------------------+-----------------------+
| LTE\_RRM\_NUM\_CQI\_P | > 8                   | > Number of CQI       |
| ER\_TTI               |                       | > resources that can  |
|                       |                       | > be scheduled per    |
|                       |                       | > TTI.\               |
|                       |                       | > Range is 0 to 1176. |
+-----------------------+-----------------------+-----------------------+
| tr69.addobject        | > Device.Services.FAP | > Command to add      |
|                       | Service.1.CellConfig. | > object from OAM CLI |
|                       | LTE.EPC.PLMNList      |                       |
+-----------------------+-----------------------+-----------------------+
| LTE\_EPC\_PLMN\_ENABL | > 1                   | > PLMN configured for |
| E                     | > FAP.0.LTE\_CELL\_PL | > this index 0        |
|                       | MN\_LIST.0            |                       |
+-----------------------+-----------------------+-----------------------+
| LTE\_OAM\_PRIMARY\_PL | > 1                   | > PLMN Primary on     |
| MN                    | > FAP.0.LTE\_CELL\_PL | > this index 0        |
|                       | MN\_LIST.0            |                       |
+-----------------------+-----------------------+-----------------------+
| LTE\_OAM\_PLMNID      | > 22020               | > Serving PLMN set as |
|                       | > FAP.0.LTE\_CELL\_PL | > “22020”.            |
|                       | MN\_LIST.0            |                       |
+-----------------------+-----------------------+-----------------------+
| LTE\_SON\_EARFCNUL\_L | > 39150               | > List of EARFCNs     |
| IST                   |                       | > from which SON      |
|                       |                       | > selects the serving |
|                       |                       | > UL-EARFCN. To set   |
|                       |                       | > multiple EARFCN,    |
|                       |                       | > assign values as    |
|                       |                       | > “39150”,”38000”,”39 |
|                       |                       | 250”                  |
+-----------------------+-----------------------+-----------------------+
| LTE\_SON\_EARFCNDL\_L | > 39150               | List of EARFCNs from  |
| IST                   |                       | which SON selects the |
|                       |                       | serving DL-EARFCN. To |
|                       |                       | set multiple EARFCNs, |
|                       |                       | assign values as      |
|                       |                       | “39150”,”38000”,”3925 |
|                       |                       | 0”                    |
+-----------------------+-----------------------+-----------------------+
| LTE\_FAP\_ADMIN\_STAT | > 0                   | > Admin State         |
| E                     |                       |                       |
+-----------------------+-----------------------+-----------------------+

End-to-End Call Flow (Message Sequence Chart)
=============================================

**The call flow for S1 setup and valid UE Attach with default bearer
establishment is illustrated in Figure-4.**

[[[]{#_Toc418590646 .anchor}]{#_Toc383776990 .anchor}]{#_Ref388618901
.anchor}**Figure-4: LTE Control and Data Call Flow**

![](media/image5.png){width="6.0625in" height="5.145833333333333in"}

[[]{#_Toc418590647 .anchor}]{#_Toc383776991 .anchor}**Figure-5: Message
Sequence Flow between UE and CNE through eNodeB**

![](media/image6.emf){width="6.239583333333333in"
height="3.4791666666666665in"}

[[]{#_Toc418590648 .anchor}]{#_Toc383776992 .anchor}Figure-6: LTE
Control and Data Call Flow using Dedicated Bearer

**S1 Setup and Valid UE Attach with Default and Dedicated Bearer
Establishment**

[[]{#_Toc418590649 .anchor}]{#_Toc383776993 .anchor}Figure-7: Mobile
Terminating Call Sequence - Flow 1

![](media/image7.png){width="6.5in" height="7.96875in"}

[[]{#_Toc418590650 .anchor}]{#_Toc383776994 .anchor}**Figure-8: Mobile
Terminating Call Sequence - Flow 2**

[[]{#_Toc418590651 .anchor}]{#_Toc383776995 .anchor}**Figure-9: Mobile
Terminating Call Sequence - Flow 3**

Traffic Generators
==================

The performance testing for different scenarios is done using special
commands as follows.

UDP Performance Testing
-----------------------

Execute the following commands to collect the UDP performance data.

### Uplink Data

External Server side:

**iperf -s -u -i 1 -p 5000 –B &lt;External Server IP address&gt;**

For example: iperf -s -u -i 1 -p 5000 –B 172.26.10.211

UE Client side:

**iperf -c &lt;External Server IP address&gt; -B &lt;UE Client IP
address&gt; -u -i 1 -t 1000 -p 5000 -b 19m**

For example: iperf -c 172.26.10.211 -B 172.26.10.xxx -u -i 1 -t 1000 -p
5000 -b 19m

### Downlink Data

UE Client side:

**iperf -s -u -i 1 -p 9999 -B &lt;UE Client IP address&gt;**

For example: iperf -s -u -i 1 -p 9999 -B 172.26.10.xxx

External Server side:

**iperf -c &lt;UE Client IP address&gt; -B &lt;External Server IP
address&gt; -u -i 1 -t 1000 -p 9999 -b 23m**

For example: iperf -c 172.26.10.xxx -B 172.26.10.211 -u -i 1 -t 1000 -p
9999 -b 23m

TCP Performance Testing
-----------------------

To collect the TCP performance data, execute the following commands.

### 9.2.1 Uplink Data {#uplink-data-1 .ListParagraph}

External Server side:

**iperf -s –w 128K -i 1 -p 5000 –B &lt;External Server IP address&gt;**

For example: iperf -s –w 128K -i 1 -p 5000 –B 172.26.10.211

UE Client side:

**iperf -c &lt;External Server IP address&gt; -B &lt;UE Client IP
address&gt; -i 1 -t 1000 -p 5000 –w 128K**

For example: iperf -c 172.26.10.211 -B 172.26.10.xxx -i 1 -t 1000 -p
5000 –w 128K

### Downlink Data 

UE Client side:

**iperf -s –w 512K -i 1 -p 9999 -B &lt;UE Client IP address&gt;**

For example: iperf -s –w 512K -i 1 -p 9999 -B 172.26.10.xxx

External Server side:

**iperf -c &lt;UE Client IP address&gt; -B &lt;External Server IP
address&gt; -i 1 -t 1000 -p 9999 –w 512K**

For example: iperf -c 172.26.10.xxx -B 172.26.10.211 -i 1 -t 1000 -p
9999 –w 512K

Performance Management
======================

Any evaluation of HeNB system behavior requires performance data
collected and recorded for inspection. TeNB collects and records
performance data according to a schedule established by the HeMS. This
aspect of the management environment is termed as Performance Management
(PM).

L2 Layer Measurement Counters
-----------------------------

The L2 counters are defined in the 3GPP TS 36314-910 and TS 32425-990.
Currently, four measurement counters are implemented.

-   RLC Downlink Throughput

-   RLC Uplink Throughput

-   PDCP SDU Discard Rate

-   MAC RACH Counters

The DL throughput and UL throughput is reported per UE per QCI while the
Discard rate is reported per QCI by the L2 layers. Each L2 layer
(currently RLC and MAC) has its own interface APIs to Start, Report
(Get) and Stop L2 Measurement.

[[]{#_Toc418590652 .anchor}]{#_Toc387350691 .anchor}**Figure-10: L2
Layer Measurement Counters**

![C:\\Users\\rsinha\\Desktop\\L2 Counters
CMRs\\L2\_meas.png](media/image8.png){width="5.21875in"
height="3.8645833333333335in"}

1.  The OAM sends the Start L2 Measurement to the eNBApp+SM, which
    > contains the counters that are required from the L2 layers.

2.  The SM configures the related layers with the measurements, namely,
    > DL/UL throughput; discard rate is configured at RLC, and MACH RACH
    > counters are configured at MAC.

3.  These measurements are periodically fetched from the respective
    > layers by sending Get/Send L2 measurement.

4.  In response, each layer sends the measurement confirm with the
    > calculated measurements. After sending the measurements, each
    > layer resets all the measurement related counters and starts them
    > again.

5.  A L2 counters collection notification is sent to OAM.

Troubleshooting
===============

This section describes the solution for the common problems that are
seen while executing the demo:

1.  Messages exchange between CNE or eNodeB fails:

    a.  MME and eNodeB must run from root mode, since SCTP uses RAW
        > sockets. If root access is not available then run SCTP over
        > UDP sockets. For information on how to configure UDP sockets,
        > contact <trillium-support@radisys.com>

    b.  PGW must run with root privilege, since it uses PCAP library to
        > communicate with external network \[Video Server\].

    c.  Verify that the right IP addresses are provided in
        > **wr\_cfg.txt** and **vbsm\_cfg.txt** files.

    d.  Verify correct IP address is provided in **configFile** if used
        > with OAM.

    e.  Verify platform and server running CNEs are reachable on
        > Ethernet interface. Try PING command from both the sides to
        > receive reply.

2.  Failed to bring up binaries:

    a.  Verify **vbsm\_cfg.txt** configuration file and
        > **vb\_hss\_ue.db** database file is present with MME binary.

    b.  Verify **qosm\_cfg.txt** configuration file is present with SGW
        > binary.

    c.  Verify **avsm\_cfg.txt** configuration file is present with PGW
        > binary.

    d.  Verify **wr\_cfg.txt** and **ys\_cfg.txt** configuration are
        > files present with eNodeB binary.

    e.  Verify **configFile** configurations if used with OAM.

3.  Check-points for End-to-End PAL setup:

    a.  Verify that **ys\_cfg.txt** file of both UeSim and eNodeB have
        > loopback address on a single PC setup as shown in Section
        > 6.3.1.

    b.  When UeSim and eNodeB are running on different machines, verify
        > that UeSim IP address mentioned in **ys\_cfg.txt** is of the
        > interface which is connected to switch and not the one which
        > is communicating with the VC.

    c.  Verify VC is reachable from UeSim, if not add route for the same
        > as mentioned in Section 6.3.

    d.  SCTP UDP service type must be same at eNodeB and MME
        > configuration file. The parameters to verify are:
        > VBSM\_SCTP\_UDP\_SERV\_TYPE (for eNodeB) and
        > WR\_TAG\_SCTP\_SRVC\_TYPE (for MME).

    e.  SB\_CHECKSUM and SB\_CHECKSUM\_CRC flags must be defined or
        > undefined, both at eNodeB and MME side.

    f.  All the nodes must be in the same network.

References 
===========

Refer to the following documents for additional information.

1.  TeNB\_PAL\_FDD\_Release\_Notes\_1225610.pdf

2.  TeNB\_Solution\_Functional\_Specification\_1091606.pdf

3.  TeNB\_Logging\_Framework\_User\_Guide\_1222469.pdf.

4.  TeNB\_OAM\_User\_Guide\_1222464.pdf

5.  TeNB\_OAM\_Integration\_Guide\_1555464.pdf

![](media/image9.png){width="1.8333333333333333in"
height="0.5895833333333333in"}

[www.radisys.com](http://www.radisys.com)
