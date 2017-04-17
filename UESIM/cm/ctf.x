
/**********************************************************************

  Name:     LTE PHY layer
  
  Type:     C Include File 
  
  Desc:     Structures, variables, and typedefs required by the LTE PHY 
            and PHY-User Control (CTF) interface.

  File:     ctf.x 

  Sid:      ctf.x@@/main/5 - Thu Feb 16 20:00:16 2012

  Prg:      vkulkarni

**********************************************************************/

#ifndef __CTF_X__
#define __CTF_X__

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @file 
  * @brief CTF Interface File.
  */

/**
 * @brief
 * Configuration transaction identifier.
 */
/* Data Structures for CTF */

/** 
  @brief Transaction ID between CTF and User. */
typedef struct ctfCfgTransId {
   U8 trans[CTF_CFG_TRANSID_SIZE]; /*!< User transaction ID */
} CtfCfgTransId;


/* Enumerations for CTF */
/**
 * @enum ctfBandwidth
 * This element enumerates the Bandwidth values for PHY in terms of RBs. */
typedef enum {
   CTF_BW_RB_6,
   CTF_BW_RB_15,
   CTF_BW_RB_25,
   CTF_BW_RB_50,
   CTF_BW_RB_75,
   CTF_BW_RB_100   
} CtfBandwidth;

/**
 * @enum ctfDuplexMode
 * This element enumerates the duplex mode for the entire system at PHY. 
*/
typedef enum {
   CTF_DUPMODE_FDD=1,
   CTF_DUPMODE_TDD   
} CtfDuplexMode;

/**
 * @enum ctfSCSpacing
 * This element enumerates the sub-carrier spacing for configuration at PHY. 
*/
typedef enum {
   CTF_SC_SPACING_15KHZ,
   CTF_SC_SPACING_7DOT5KHZ   
} CtfSCSpacing;

/**
 * @enum ctfCPCfg
 * This element enumerates the cyclic prefix for use at PHY.
*/
typedef enum {
   CTF_CP_NORMAL,
   CTF_CP_EXTENDED   
} CtfCPCfg;

/**
 * @brief
 * This element enumerates the number of antenna ports for configuration at PHY.
*/
typedef enum {
   CTF_AP_CNT_1,
   CTF_AP_CNT_2,
   CTF_AP_CNT_4   
} CtfAntennaPortsCount;

/**
 * @enum ctfPhichDuration
 * This element enumerates the duration for PHICH configuration at PHY.
*/
typedef enum {
   CTF_PHICH_DUR_NORMAL,
   CTF_PHICH_DUR_EXTENDED   
} CtfPhichDuration;

/**
 * @enum ctfPhichResource
 * This element enumerates the resources for PHICH configuration at PHY.
*/
typedef enum {
   CTF_PHICH_RSRC_ONESIXTH,
   CTF_PHICH_RSRC_HALF,
   CTF_PHICH_RSRC_ONE,
   CTF_PHICH_RSRC_TWO   
} CtfPhichResource;

/**
 * @enum ctfPuschHoppingMode
 * This element enumerates the hopping mode for PUSCH configuration at PHY.
*/
typedef enum {
   CTF_PUSCH_HOPMODE_INTER_SUBFRM,
   CTF_PUSCH_HOPMODE_INTRAANDINTERSUBFRM   
} CtfPuschHoppingMode;

/**
 * @enum ctfPucchDeltaShift
 * This element enumerates the delta shift for PUCCH configuration at PHY.
*/
typedef enum {
   CTF_PUCCH_DELTASHIFT1,
   CTF_PUCCH_DELTASHIFT2,
   CTF_PUCCH_DELTASHIFT3   
} CtfPucchDeltaShift;

/**
 * @enum ctfPdschPaParam
 * This element enumerates the parameter PA for PDSCH configuration at PHY.
 * Each enum value maps to a PA value in dBs.
*/
typedef enum {
   CTF_PDSCH_PA_MINUS_6,
   CTF_PDSCH_PA_MINUS_4DOT77,
   CTF_PDSCH_PA_MINUS_3,
   CTF_PDSCH_PA_MINUS_1DOT77,
   CTF_PDSCH_PA_ZERO,
   CTF_PDSCH_PA_ONE,
   CTF_PDSCH_PA_TWO,
   CTF_PDSCH_PA_THREE   
} CtfPdschPaParam;

/**
 * @enum CtfCqiRptModeAperiodic
 * This element enumerates the Aperiodic CQI reporting configuration at PHY.
*/
typedef enum {
   CTF_CQI_RPT_MODE_APERIODIC_RM12, /*!< Corresponds to Mode 1-2 */
   CTF_CQI_RPT_MODE_APERIODIC_RM20, /*!< Corresponds to Mode 2-0 */
   CTF_CQI_RPT_MODE_APERIODIC_RM22, /*!< Corresponds to Mode 2-2 */
   CTF_CQI_RPT_MODE_APERIODIC_RM30, /*!< Corresponds to Mode 3-0 */
   CTF_CQI_RPT_MODE_APERIODIC_RM31  /*!< Corresponds to Mode 3-1 */
} CtfCqiRptModeAperiodic;

/**
 * @enum CtfUeTxAntSelectType 
 * This element enumerates the UE TX Antenna selection configuration at PHY.
*/
typedef enum {
   CTF_UE_TX_ANT_SELECT_CLOSEDLOOP, /*!< Closed loop selection */
   CTF_UE_TX_ANT_SELECT_OPENLOOP    /*!< Open loop selection */
} CtfUeTxAntSelectType;

/**
 * @enum CtfPucchRepFactor 
 * This element enumerates the repetition factors for PUCCH configuration.
*/
typedef enum {
   CTF_PUCCH_REP_FACTOR_N2,   /*!< Pucch repetition factor of 2 */
   CTF_PUCCH_REP_FACTOR_N4,   /*!< Pucch repetition factor of 4 */
   CTF_PUCCH_REP_FACTOR_N6    /*!< Pucch repetition factor of 6 */
} CtfPucchRepFactor;

#ifdef CTF_VER3
/* ctf_x_001.main_4:115549: */
 /**
  * @enum CtfTddAckNackFBMode
  * This element enumerates the ACK/NACK feedback mode for TDD mode of
  *  PUCCH configuration.
 */
 typedef enum {
    CTF_PUCCH_TDD_ACKNACK_FB_MODE_BUNDLING, /*!< Bundling option */
    CTF_PUCCH_TDD_ACKNACK_FB_MODE_MUXING    /*!< Multiplexing option */
 } CtfTddAckNackFBMode;
#endif /* CTF_VER3 */

/**
 * @enum CtfUeTxAntMode 
 * This element enumerates the UE Transmission mode.
*/
typedef enum {
   CTF_UE_TX_ANT_MODE_TM1, /*!< Transmission Mode 1 */
   CTF_UE_TX_ANT_MODE_TM2, /*!< Transmission Mode 2 */
   CTF_UE_TX_ANT_MODE_TM3, /*!< Transmission Mode 3 */
   CTF_UE_TX_ANT_MODE_TM4, /*!< Transmission Mode 4 */
   CTF_UE_TX_ANT_MODE_TM5, /*!< Transmission Mode 5 */
   CTF_UE_TX_ANT_MODE_TM6, /*!< Transmission Mode 6 */
   CTF_UE_TX_ANT_MODE_TM7  /*!< Transmission Mode 7 */
/* ctf_x_001.main_2: Added transmission mode 8*/
#ifdef CTF_VER1
   ,CTF_UE_TX_ANT_MODE_TM8  /*!< Transmission Mode 8 */
#endif
} CtfUeTxAntMode;
/* ctf_x_001.main_4: Removed enum for CTF reconfiguration */

/**
 *  @brief
 *  UE ID information
 */
typedef struct ctfUeInfo {
   CmLteCellId    cellId;     /*!< Cell ID */
   CmLteRnti      ueId;       /*!< UE ID */
}CtfUeInfo;

/* Data Structures for CTF */
/**
 * @brief   Bandwidth Configuration.
 * @details This structure contains the uplink and downlink bandwidth 
 *          information for configuration at PHY.
*/
typedef struct ctfBwCfgInfo {
   CtfBandwidth   dlBw;       /*!< Downlink Bandwidth in RBs */
   CtfBandwidth   ulBw;       /*!< Uplink Bandwidth in RBs */
   U8             eUtraBand;  /*!< EUTRA Operating Band - 36.104 (5.5)
                                   FDD:(1..14), TDD:(33..40) */
} CtfBwCfgInfo;

/**
 * @brief   Transmission Scheme Configuration.
 * @details This structure contains the transmission scheme related information.
*/
typedef struct ctfTxSchemeCfg {
   CtfDuplexMode  duplexMode; /*!< Duplexing Mode: TDD/FDD */
   CtfSCSpacing   scSpacing;  /*!< Sub-carrier spacing */
   CtfCPCfg       cycPfx;     /*!< Cyclic prefix */
} CtfTxSchemeCfg;

/**
 * @brief   Antenna Ports configuration.
 * @details This structure contains the antenna configuration information for 
 *          configuration at PHY.
*/
typedef struct ctfAntennaCfgInfo {
   CtfAntennaPortsCount   antPortsCnt; /*!< Count of antenna ports */
} CtfAntennaCfgInfo;

/**
 * @brief   PRACH configuration.
 * @details This structure contains the configuration information for PRACH at PHY.
 *          -# PRACH preamble sequences are generated by PHY using Zadoff-Chu 
 *             sequences.[Ref: 36.211, 5.7.2]
 *          -# PRACH preamble format is derived from PRACH Configuration Index.
 *             [Ref: 36.211, Table 5.7.1-2]
 *          -# PrachFreqOffset is the first physical resource block allocated to 
 *             the PRACH opportunity considered for preamble format 0, 1, 2 and 3.
 *             [Ref: 36.211, 5.7.1]
*/
typedef struct ctfPrachCfgInfo {
   Bool  pres;                   /*!< Indicates the presence of this info */
   U16   rootSequenceIndex;      /*!< Range (0..837) */
   U8    prachCfgIndex;          /*!< Prach Config Index (0..63) */
   U8    zeroCorrelationZoneCfg; /*!< Used for preamble sequence generation
                                      (36.211, 5.7.2); FDD:0..15, TDD:0..6 */
   Bool  highSpeedFlag;          /*!< TRUE: Restricted set, 
                                      FALSE: Unrestricted Set */
   U8    prachFreqOffset;        /*!< Range(0..94) */
} CtfPrachCfgInfo;

/**
 * @brief   PDSCH configuration.
 * @details This structure contains the PDSCH configuration information for 
 *          configuration at PHY.
*/
typedef struct ctfPdschCfgInfo {
   Bool           pres;       /*!< Indicates the presence of this info */
   S8             refSigPwr;  /*!< Provides downlink reference signal EPRE, 
                                   in (-60..50)dBm */
   U8             p_b;        /*!< Range(0..3) [36.213, 5.2] */ 
} CtfPdschCfgInfo;

/**
 * @brief   Basic PUSCH configuration.
 * @details This structure contains the basic PUSCH configuration information for 
 *          configuration at PHY.
*/
typedef struct ctfPuschCfgBasic {
   U8                   noOfsubBands;  /*!< Number of sub-bands, (1..4) */
   CtfPuschHoppingMode  hoppingMode;   /*!< Hopping Mode */
   U8                   hoppingOffset; /*!< Hopping Offset(0..98) */
   Bool                 enable64QAM;   /*!< 64 QAM,TRUE: enabled, 
                                                   FALSE: disabled */
} CtfPuschCfgBasic;

/**
 * @brief   PUSCH Uplink Reference Signals configuration.
 * @details This structure contains the PUSCH configuration information for 
 *          uplink reference signals configuration at PHY.
*/
typedef struct ctfPuschUlRS {
   Bool  grpHopEnabled; /*!< Group hopping, TRUE: enabled, FALSE: disabled */
   Bool  seqHopEnabled; /*!< Sequence hopping, TRUE: enabled, FALSE: disabled */
   U8    grpNum;        /*!< Group number (0..29) */
   U8    cycShift;      /*!< Cyclic shift(0..7) */
} CtfPuschUlRS;

/**
 * @brief   PUSCH configuration.
 * @details This structure contains the information for PUSCH 
 *          configuration at PHY.
*/
typedef struct ctfPuschCfgInfo {
   Bool              pres;          /*!< Indicates the presence of PUSCH configuration info */
   CtfPuschCfgBasic  puschBasicCfg; /*!< PUSCH basic configuration */
   CtfPuschUlRS      puschUlRS;     /*!< PUSCH uplink RS */
} CtfPuschCfgInfo;

/**
 * @brief   PHICH configuration.
 * @details This structure contains the duration and resource information for
 *          PHICH configuration at PHY.
*/
typedef struct ctfPhichCfgInfo {
   Bool              pres;       /*!< Indicates the presence of PHICH 
                                      configuration info */
   CtfPhichDuration  duration;   /*!< PHICH duration, normal/extended, 
                                      [36.211, 6.9.3-1] */
   CtfPhichResource  resource;   /*!< PHICH Resource, Ng [36.211, 6.9] */
} CtfPhichCfgInfo;

/**
 * @brief   PUCCH configuration.
 * @details This structure contains the information for PUCCH
 *          configuration at PHY.
*/
typedef struct ctfPucchCfgInfo {
   Bool  pres; /*!< Indicates the presence of PUCCH configuration info */
   U8    nRB;  /*!< Number of RBs that are available for use by 
                    PUCCH formats (0..98) */
   U8    nCS;  /*!< Number of cyclic shifts used for PUCCH formats (0..7) */
   U16   n1PUCCH; /*!< PUCCH resource for transmission of ACK/NACK (0..2047) */
   CtfPucchDeltaShift   deltaShift; /*!< PUCCH delta shift */
} CtfPucchCfgInfo;

/**
 * @brief   SRS uplink configuration.
 * @details This structure contains the information for setting-up/release
 *          of uplink SRS configuration at PHY.
*/
typedef struct ctfSrsUlCfgInfo {
   Bool              pres;       /*!< Indicates the presence of UL SRS info */
   U8                srsCfgType; /*!< Setup/Release: The setup structure
                                      is valid ,only if srcCfgType is setup. */
   struct srsSetupS
   {
      U8                srsBw;   /*!< SRS bandwidth config (0..7) */
      U8                sfCfg;   /*!< SRS sub-frame config (0..15) */
      Bool              srsANSimultTx; /*!< Simultaneous transmisson 
                                            of SRS and ACK/NACK */
      Bool              srsMaxUpPts;   /*!< SRS MaxUpPTS: TRUE/FALSE, 
                                            This field is valid only for TDD */
   } srsSetup;
} CtfSrsUlCfgInfo;

/**
 * @brief   Subframe Configuration for TDD mode.
 * @details This structure contains the information for setting-up
 *          the subframe for TDD mode at PHY.
*/
typedef struct ctfTddSfCfgInfo {
   Bool  pres;             /*!< Indicates if this info is valid */
   U8    sfAssignment;     /*!< UL-DL subframe assignment : (0..6)
                                36.211 Table 4.2-2 */
   U8    spclSfPatterns;   /*!< Special subframe configuration : (0..8)
                                36.211 Table 4.2-1 */
} CtfTddSfCfgInfo;

/* ctf_x_001.main_4: Added support for vendor specific parameters */
#ifdef CTF_VER3
/**
 * @brief   Vendor Specific Parameter
 * @details This structure contains the Parameters which is spaciftc to 
 *     Vendor.
 */

typedef struct ctfVendorSpecific{
  U16  buffLen ;  /*!<  Length of parameters in bytes */
  U8  *paramBuffer ; /*!< parameter Buffer */
} CtfVendorSpecific;
#endif
/* Cell specific configuration parameters */

/**
 * @brief   Cell Configuration Information.
 * @details This structure contains the information for setting-up
 *          of a cell and its associated resources at PHY.
*/

typedef struct ctfCellCfgInfo {
   CmLteCellId       cellId;     /*!< Cell ID */
   U8                cellIdGrpId;/*!< Cell Identity Group ID (0..167) */
   U8                physCellId; /*!< Cell ID (0..2) */
   CtfBwCfgInfo      bwCfg;      /*!< Bandwidth configuration */
   CtfTxSchemeCfg    txCfg;      /*!< Basic transmission scheme 
                                      configuration [36.300, 5.1.1] */
   CtfAntennaCfgInfo antennaCfg; /*!< Antenna configuration */
   CtfPrachCfgInfo   prachCfg;   /*!< PRACH configuration */
   CtfPdschCfgInfo   pdschCfg;   /*!< PDSCH configuration */
   CtfPuschCfgInfo   puschCfg;   /*!< PUSCH configuration */
   CtfPhichCfgInfo   phichCfg;   /*!< PHICH configuration */
   CtfPucchCfgInfo   pucchCfg;   /*!< PUCCH configuration */
   CtfSrsUlCfgInfo   srsUlCfg;   /*!< SRS UL configuration, setup case */
   CtfTddSfCfgInfo   tddSfCfg;   /*!< SubFrame configuration for TDD only */
} CtfCellCfgInfo;

/**
 * @brief   Cell Re-configuration Information.
 * @details This structure contains the information for reconfiguration
 *          of a cell and its associated resources at PHY.
*/
typedef struct ctfCellRecfgInfo {
   CmLteCellId       cellId;     /*!< Cell ID */
   CmLteTimingInfo   actvnTime;  /*!< Activation time, only SFN is valid */
   CtfPrachCfgInfo   prachCfg;   /*!< PRACH configuration */
   CtfPdschCfgInfo   pdschCfg;   /*!< PDSCH configuration */
   CtfPuschCfgInfo   puschCfg;   /*!< PUSCH configuration */
   CtfPhichCfgInfo   phichCfg;   /*!< PHICH configuration */
   CtfPucchCfgInfo   pucchCfg;   /*!< PUCCH configuration */
   CtfSrsUlCfgInfo   srsUlCfg;   /*!< SRS UL configuration, setup case */
   CtfTddSfCfgInfo   tddSfCfg;   /*!< SubFrame configuration for TDD only */
} CtfCellRecfgInfo;

/* UE-specific/Dedicated config parameters */

/**
 * @brief   Dedicated PDSCH Configuration.
 * @details This structure contains the information for PDSCH configuration
 *          specific to an UE.
*/
typedef struct ctfDedPdschCfgInfo {
   Bool              pres; /*!< Indicates the presence of PDSCH configuration info */
   CtfPdschPaParam   pA;   /*!< Pa (in dB) */
} CtfDedPdschCfgInfo;

/**
 * @brief   Dedicated PUCCH Configuration.
 * @details This structure contains the information for setting-up/release 
 *          PUCCH configuration specific to an UE.
*/
typedef struct ctfDedPucchCfgInfo {
   Bool              pres;             /*!< Indicates the presence of PUCCH info */
   U8                dedPucchCfgType;  /*!< Setup/Release */
   struct pucchSetupS
   {
#ifdef CTF_VER3
      /* ctf_x_001.main_4:115549: */
      Bool              repFactPres;   /*!< Indicates if repetition factor
                                             is configured or not */
#endif /* CTF_VER3 */
      CtfPucchRepFactor repFact;       /*!< ACK/NACK repetition factor */
      U16               n1PUCCHRep;    /*!< PUCCH resource to repeat the 
                                            transmission of the corresponding 
                                            ACK/NACK responce [36.213, 10.1] */
   } pucchSetup;
#ifdef CTF_VER3
   /* ctf_x_001.main_4:115549: */
    Bool                 tddAckNackCfgPres; /*! Present flag for TDD 
                                                ACK/NACK config */
    CtfTddAckNackFBMode  tddAckNackFBMode; /*!< TDD ACK/NACK Feedback Mode 
                                                 (bundling, multiplexing) */
#endif /* CTF_VER3 */
} CtfDedPucchCfgInfo;

/**
 * @brief   Dedicated PUSCH Configuration.
 * @details This structure contains the information for PUCCH 
 *          configuration specific to an UE.
*/
typedef struct ctfDedPuschCfgInfo {
   Bool     pres;             /*!< Indicates the presence of PUSCH info */
   U8       betaOffsetAckIdx; /*!< Beta offset ACK index, (0..15)
                                   [36.213, Table 8.6.3.-1] */
   U8       betaOffsetRiIdx;  /*!< Beta offset RI index, (0..15)
                                   [36.213, Table 8.6.3.-2] */
   U8       betaOffsetCqiIdx; /*!< Beta offset CQI index, (0..15)
                                   [36.213, Table 8.6.3.-3] */
} CtfDedPuschCfgInfo;


/* ctf_x_001.main_2: Added pmiRiRpt and cqiMask*/
#ifdef CTF_VER1
/**
 * @enum ctfPmiRiRptSetup
 * This element enumerates the CQI PMI Report setup configuration at PHY.
*/
typedef enum ctfPmiRiRptSetup
{
   CTF_CQI_PMI_RPT_SETUP  /*!< PMI Report setup */
} CtfPmiRiRptSetup;

/**
 * @struct ctfPmiRiRpt
 * This struct contains the  CQI PMI Report setup configuration at PHY.
*/
typedef struct ctfPmiRiRpt
{
   Bool              pres;           /*!< Indicates presence of Pmi Ri Rpt */
   CtfPmiRiRptSetup  pmiRiRptSetup;  /*!< PMI Report setup */
} CtfPmiRiRpt;

/**
 * @enum ctfCqiMaskSetup
 * This element enumerates the CQI reporting setup configuration at PHY.
*/
typedef enum ctfCqiMaskSetup
{
   CTF_CQI_RPT_SETUP  /*!< Cqi report setup */
} CtfCqiMaskSetup;

/**
 * @struct ctfCqiMask
 * This struct contains the CQI reporting setup configuration at PHY.
*/
typedef struct ctfCqiMask
{
   Bool             pres;     /*!< Presence field */
   CtfCqiMaskSetup  cqiMaskSetup;  /*!< Cqi Report Setup */
} CtfCqiMask;
#endif /* CTF_VER1 */

/* ctf_x_001.main_2: Moved aPeriodic enum to seperate structure*/
#ifdef CTF_VER2
/* Moved aPeriodic enum to seperate structure */
/**
 * @brief   APeriodic CQI Report Configuration.
 * @details This structure contains the information for Aperiodic CQI report
 *          related configuration specific to an UE.
*/
typedef struct ctfCqiReportModeAPeriodic {
    Bool pres;
    CtfCqiRptModeAperiodic aPeriodicRptMode; /*!<Aperiodic CQI report*/
}CtfCqiRptModeAprd;
#endif /* CTF_VER2 */

/**
 * @brief   Periodic CQI Report Configuration.
 * @details This structure contains the information for periodic CQI report
 *          related configuration specific to an UE.
*/
typedef struct ctfCqiRptModePeriodic {
#ifdef CTF_VER2
   Bool  pres;
#endif /* CTF_VER2 */
   U8    cqiPeriodicCfgType;     /*!< Configuration type: Setup/Release  */
   struct cqiSetupS
   {
      U16   cqiPUCCHRsrcIndx;    /*!< Range (0..1185) */
      U16   cqiPmiCfgIndx;       /*!< Range (0..1023) */
      U8    formatIndicator;     /*!< Type: Wideband/Subband */
      struct subbandCqiS
      {
         U8    k;                /*!< Range (1..4) */
      } subbandCqi;              /*!< Valid only if formatIndicator is Subband */

      Bool  riCfgPres;           /*!< RI Configuration index is present or absent */
      U16   riCfgIndx;           /*!< Range (0..1023) */
      Bool  simultaneousAckNack; /*!< Simultaneous ACK/NACK with CQI support
                                      TRUE: YES, FALSE: NO */
/* ctf_x_001.main_2: Added cqiMask*/
#ifdef CTF_VER1
   CtfCqiMask   cqiMask;         /*!< cqi mask */
#endif /* CTF_VER1 */
   } cqiSetup;                   /*!< Valid only if cqiPeriodicCfgType is Setup */
} CtfCqiRptModePeriodic;

/**
 * @brief   CQI Report Configuration.
 * @details This structure contains the information for CQI report
 *          related configuration specific to an UE.
*/
typedef struct ctfCqiReportCfgInfo {
   Bool  pres;                /*!< Indicates the presence of this info  */
/* ctf_x_001.main_2: period and aperiodic rpt both can be configured simultaneously*/
#ifdef CTF_VER2
   struct
   {
      CtfCqiRptModeAprd       aPeriodicRpt;
      CtfCqiRptModePeriodic   periodicRpt;
   } reportMode;
#else /* CTF_VER2 */
   U8    reportingMode;       /*!< Reporting mode: Periodic/Aperiodic */
   union
   {
      CtfCqiRptModeAperiodic  aPeriodicRpt;
      CtfCqiRptModePeriodic   periodicRpt;
   } reportMode;
#endif /* CTF_VER2 */
/* ctf_x_001.main_2: Added PmiRiRpt*/
#ifdef CTF_VER1
   CtfPmiRiRpt  pmiRiRpt;        /*!< Pmi Ri Report */
#endif /* CTF_VER1 */
} CtfCqiReportCfgInfo;

/**
 * @brief   Dedicated Uplink SRS Configuration.
 * @details This structure contains the information for setting-up/release
 *          UL SRS configuration specific to an UE.
*/
typedef struct ctfDedSrsUlCfgInfo {
   Bool     pres;             /*!< Indicates the presence of SRS UL info */
   U8       dedSrsUlCfgType;  /*!< Setup/Release */
   struct dedSrsSetupS
   {
      U8       srsBw;         /*!< SRS bandwidth(0,1,2,3) */
      U8       srsHopngBw;    /*!< SRS hopping bandwidth (0,1,2,3) */
      U8       freqDmnPos;    /*!< Frequency domain position (0..23) */
      Bool     duration;      /*!< Duration, FALSE: single, 
                                             TRUE: indefinite */
      U16      srsCfgIdx;     /*!< SRS config index (0..1023) */
      U8       txComb;        /*!< transmission comb (0..1) */
      U8       cyclicShift;   /*!< Cyclic shift (0..7) */
   } dedSrsSetup;
} CtfDedSrsUlCfgInfo;

/**
 * @brief   Dedicated SR Configuration
 * @details This structure contains the information for setting-up/release
 *          SR configuration specific to an UE at PHY.
*/
typedef struct ctfDedSRCfgInfo {
   Bool     pres;          /*!< Indicates the presence of SR info */
   U8       dedSRCfgType;  /*!< Setup/Release */
   struct dedSrSetupS
   {
      U16      srPUCCHRi;  /*!< SR PUCCH Resource Index, n(1)PUCCH,SRI 
                                (0..2047) */
      U8       srCfgIdx;   /*!< SR config index, Isr (0..155) */
   } dedSrSetup;           /*!< Valid only if dedSRCfgType is setup */
} CtfDedSRCfgInfo;

#ifdef CTF_VER2
/* ctf_x_001.main_2 : Added enum for Code Book Subset Restriction */
/**
 * @enum CtfCdBkSubsetRestnType
 * This element enumerates the Code Book Subset Restriction 
 * configuration at PHY for a UE.
*/
typedef enum ctfCdBkSubsetRestnType
{
   N2TX_ANT_TM3,     /*!< 2 Antenna Ports for transmissiom mode 3*/
   N4TX_ANT_TM3,     /*!< 4 Antenna Ports for transmissiom mode 3*/
   N2TX_ANT_TM4,     /*!< 2 Antenna Ports for transmissiom mode 4*/
   N4TX_ANT_TM4,     /*!< 4 Antenna Ports for transmissiom mode 4*/
   N2TX_ANT_TM5,     /*!< 2 Antenna Ports for transmissiom mode 5*/
   N4TX_ANT_TM5,     /*!< 4 Antenna Ports for transmissiom mode 5*/
   N2TX_ANT_TM6,     /*!< 2 Antenna Ports for transmissiom mode 6*/
   N4TX_ANT_TM6      /*!< 4 Antenna Ports for transmissiom mode 6*/
}CtfCdBkSubsetRestnType;

/* nh005.201_LPR2 : Added new structure for Code Book Subset Restriction */
/**
 * @struct  CtfDedAntCodeBkSubsetRes
 * @brief Code Book Subset Restriction Configuration.
 * @details This structure contains the information for 
 *          codeBookSubsetRestriction  configuration specific to 
 *          transmission mode of a UE Phy.
*/
typedef struct ctfDedAntCodeBookSubsetRestn
{
  CtfCdBkSubsetRestnType ctfCdBkRestType;
  union
  {
      U8   n2TxAntTm3;     /*!< 2 Antenna Ports for transmissiom mode 3*/
      U8   n4TxAntTm3;     /*!< 4 Antenna Ports for transmissiom mode 3*/
      U8   n2TxAntTm4;     /*!< 2 Antenna Ports for transmissiom mode 4*/
      U8   n4TxAntTm4[8];  /*!< 4 Antenna Ports for transmissiom mode 4*/
      U8   n2TxAntTm5;     /*!< 2 Antenna Ports for transmissiom mode 5*/
      U16  n4TxAntTm5;     /*!< 4 Antenna Ports for transmissiom mode 5*/
      U8   n2TxAntTm6;     /*!< 2 Antenna Ports for transmissiom mode 6*/
      U16  n4TxAntTm6;     /*!< 4 Antenna Ports for transmissiom mode 6*/
  }codeBookSubsetRestn;
}CtfDedAntCodeBkSubsetRes;
#endif /* CTF_VER2 */

/**
 * @brief   Dedicated Antenna Configuration.
 * @details This structure contains the information for antenna related
 *          configuration specific to an UE at PHY.
*/
typedef struct ctfDedAntCfgInfo {
   Bool              pres;   /*!< Indicates the presence of antenna configuration info */
   CtfUeTxAntMode    txMode; /*!< Transmission Mode: 36.213, 7.1 */
   struct ueTxAntSelectionS
   {
      U8                      cfgType;       /*!< Setup/Release */
      CtfUeTxAntSelectType    txAntSelect;   /*!< Closed/Open, valid only if
                                                  cfgType is setup:36.213, 8.7 */
   } ueTxAntSelection;
#ifdef CTF_VER2
   /*ctf_x_001.main_2 : Added CodeBookSubsetRestriction Parameter */
   CtfDedAntCodeBkSubsetRes codeBookSubsetRes;
#endif /* CTF_VER2 */
} CtfDedAntCfgInfo;

/**
 * @brief   UE Category Configuration.
 * @details This structure contains the information for configuring
 *          the UE category at PHY.
*/
typedef struct ctfUeCatCfgInfo {
   Bool                 pres;       /*!< TRUE - indicates UE category is present */
   CmLteUeCategory      ueCategory; /*!< UE category */
} CtfUeCatCfgInfo;

/**
 * @brief   Dedicated Configuration Information.
 * @details This structure contains the information for configuration 
 *          of UE-specific physical channel resources at PHY.
*/
typedef struct ctfDedCfgInfo {
   CmLteCellId          cellId;     /*!< Cell ID */
   CmLteRnti            ueId;       /*!< UE ID */
   CtfUeCatCfgInfo      ueCatCfg;   /*!< UE Cateogry configuration */
   CtfDedPdschCfgInfo   pdschCfg;   /*!< PDSCH configuration */
   CtfDedPucchCfgInfo   pucchCfg;   /*!< PUCCH configuration */
   CtfDedPuschCfgInfo   puschCfg;   /*!< PUSCH configuration */
   CtfCqiReportCfgInfo  cqiRptCfg;  /*!< CQI report configuration */
   CtfDedSrsUlCfgInfo   srsUlCfg;   /*!< SRS UL configuration */
   CtfDedSRCfgInfo      dedSRCfg;   /*!< SR configuration */
   CtfDedAntCfgInfo     antInfo;    /*!< Antenna configuration */
} CtfDedCfgInfo;

/**
 * @brief   Dedicated Re-configuration Information.
 * @details This structure contains the information for re-configuration 
 *          of UE-specific physical channel resources at PHY.
*/
typedef struct ctfDedRecfgInfo {
   CmLteCellId          cellId;     /*!< Cell ID */
   CmLteRnti            ueId;       /*!< Old UE ID */
   /* ctf_x_001.main_4: ReEst Fix */
#ifdef CTF_VER3
   CmLteRnti            newUeId;       /*!< If ueId is not getting reconfigured,
                                            both ueId and newUeId shell hold same
                                            value. If ueId is getting reconfigured 
                                            then these two value should be different
                                            from each other */
#endif
   CtfUeCatCfgInfo      ueCatCfg;   /*!< UE Cateogry configuration */
   CtfDedPdschCfgInfo   pdschCfg;   /*!< PDSCH configuration */
   CtfDedPucchCfgInfo   pucchCfg;   /*!< PUCCH configuration */
   CtfDedPuschCfgInfo   puschCfg;   /*!< PUSCH configuration */
   CtfDedSrsUlCfgInfo   srsUlCfg;   /*!< SRS UL configuration */
   CtfDedSRCfgInfo      dedSRCfg;   /*!< SR configuration */
/*ctf_x_001.main_1*/ 
   CtfCqiReportCfgInfo  cqiRptCfg;  /*!< CQI report configuration */
   CtfDedAntCfgInfo     antInfo;    /*!< Antenna configuration */
} CtfDedRecfgInfo;

/**
 * @brief   Cell Release Information.
 * @details This structure contains the information for release/removal 
 *          of a cell and its assocated resources at PHY.
*/
typedef struct ctfCellReleaseInfo {
   CmLteCellId cellId; /*!< Cell ID */
} CtfCellReleaseInfo;

/**
 * @brief   Dedicated Release Information
 * @details This structure contains the information for release/removal 
 *          of dedicated/UE-specific configuration at PHY.
*/
typedef struct ctfDedReleaseInfo {
   CmLteCellId cellId;  /*!< Cell ID */
   CmLteRnti   ueId;    /*!< UE ID (rnti) */
} CtfDedReleaseInfo;

/**
 * @brief   Configuration Information.
 * @details This structure contains the information for setting-up 
 *          cell or UE-specific configuration at PHY.
*/
typedef struct ctfCfgInfo {
   U8 cfgElem; /*!< Configuration element : Cell/UE */
   union
   {
      CtfCellCfgInfo cellCfg; /*!< Cell configuration */
      CtfDedCfgInfo  dedCfg;  /*!< UE configuration */
   } u;
} CtfCfgInfo;

/**
 * @brief   Re-configuration Information.
 * @details This structure contains the information for re-configuring 
 *          cell or UE-specific configuration at PHY.
*/
typedef struct ctfReCfgInfo {
   U8 cfgElem; /*!< Configuration element: Cell/UE */
   union
   {
      CtfCellRecfgInfo  cellRecfg;  /*!< Cell reconfiguration */
      CtfDedRecfgInfo   dedRecfg;   /*!< UE reconfiguration */
   } u;
} CtfReCfgInfo;

/**
 * @brief   Release Configuration Information.
 * @details This structure contains the information for releasing 
 *          cell or UE-specific configuration at PHY.
*/
typedef struct ctfReleaseInfo {
   U8 cfgElem; /*!< Configuration element : Cell/UE */
   union
   {
      CtfCellReleaseInfo  cellRel;  /*!< Cell release */
      CtfDedReleaseInfo   dedRel;   /*!< UE release */
   } u;
} CtfReleaseInfo;



/**
 * @brief   Configuration Request Information.
 * @details This is the main structure in the configuration request primitive.
 *    -# This structure contains the configuration information as given by 
 *       the User to configure PHY layer for common/dedicated resources.
 *    -# It can contain Config/Reconfig/Release.
 *    -# The result of configuration is indicated in TfUiCtfCfgCfm. 
*/
typedef struct ctfCfgReqInfo {
   U8    cfgType; /*!< Configuration type: Config/Reconfig/Release */
   union
   {
      CtfCfgInfo     cfg;     /*!< Cell/UE Configuration information */
      CtfReCfgInfo   reCfg;   /*!< Cell/UE Reconfiguration information */
      CtfReleaseInfo release; /*!< Cell/UE Release information */
   } u;
/* ctf_x_001.main_4: Added support for vendor specific parameters */
#ifdef CTF_VER3
   CtfVendorSpecific  vendorParams ; /*!< Vendor Specific Parameter */ 
#endif   
} CtfCfgReqInfo;


/* 
 * Function Prototypes 
*/
/* Request from User to PHY to bind the CTF interface SAP. */
typedef S16 (*CtfBndReq) ARGS((
   Pst*                 pst,
   SuId                 suId,
   SpId                 spId));

/* Confirmation from PHY to User for the bind request of the CTF interface SAP.
*/
typedef S16 (*CtfBndCfm) ARGS((
   Pst*                 pst,
   SuId                 suId,
   U8                   status));

/* Request from User to PHY to Unbind the CTF interface SAP. */
typedef S16 (*CtfUbndReq) ARGS((
   Pst*                 pst,
   SpId                 spId,
   Reason               reason));

/* Configuration Request from User to PHY for cell or dedicated configuration. 
*/
typedef S16 (*CtfCfgReq) ARGS((
   Pst*                 pst,
   SpId                 spId,
   CtfCfgTransId        transId,
   CtfCfgReqInfo*       cfgReqInfo));

/* Configuration Confirm from PHY to User. */
typedef S16 (*CtfCfgCfm) ARGS((
   Pst*                 pst,
   SuId                 suId,
   CtfCfgTransId        transId,
   U8                   status));

/* UE ID Change Request from User to PHY. */
typedef S16 (*CtfUeIdChgReq) ARGS((
   Pst*                 pst,
   SpId                 spId,
   CtfCfgTransId        transId,
   CtfUeInfo *          ueInfo,
   CtfUeInfo *          newUeInfo));

/* UE ID Change Confirm from PHY to User. */
typedef S16 (*CtfUeIdChgCfm) ARGS((
   Pst*                 pst,
   SuId                 suId,
   CtfCfgTransId        transId,
   CtfUeInfo *          ueInfo,
   CmStatus             status));

/** 
 * @brief Bind Request from PHY User to bind the CTF interface SAP.
 *
 * @details This primitiveis used to bind a user to the CTF interface.
 *          -# PHY layer registers this user, allocates a Service Access Point
 *          for this bind and records the identity of the service user.
 *          -# PHY issues a @ref TfUiCtfBndCfm to the service user after
 *          completing a successful bind.
 *
 * @param[in] pst  Pointer to the post structure. SSI uses pst for loosely 
 *                 coupled intertask communication.
 * @param[in] suId The service user SAP ID. The service user uses this
 *                 reference number to identify a SAP. The service user provides
 *                 this ID and the service provider retains it. The service 
 *                 provider provides this reference number in any further 
 *                 primitives that the service provider sends to the service 
 *                 user.
 * @param[in] spId The service provider SAP ID. The service provider uses this
 *                 reference number to identify its SAP. The service user 
 *                 provides this reference number in any further primitives 
 *                 that the service user sends to the service provider.
 *
 * @return S16
 *  -# ROK on success
 *  -# RFAILED on failure
 *
*/
EXTERN S16 TfUiCtfBndReq ARGS((
   Pst*                 pst,
   SuId                 suId,
   SpId                 spId
));

/** 
 * @brief Bind Confirm from PHY to User.
 *
 * @details This primitive is used to report the status of processing a bind 
 *          request. If the service user does not receive a bind confirm 
 *          primitive, it must stop trying to bind after a limited number of 
 *          retries. The service provider must send a bind confirm upon 
 *          receiving a bind request primitive from the service user. These 
 *          status values are requested:
 *          - CM_BND_OK: This status is reported when the bind request is 
 *                       successful.
 *          - CM_BND_NOK: This status is reported when the bind request is unsuccessful.
 *
 * @param[in] pst  Pointer to the post structure. SSI uses pst for loosely 
 *                 coupled intertask communication.
 * @param[in] suId The service user SAP ID. The service user uses this 
 *                 reference number to identify its lower control block.
 * @param[in] status The allowed values of status are:
 *                   CM_BND_OK   1
 *                   CM_BND_NOK  2
 *
 * @return S16
 * -# ROK 
 * -# RFAILED 
 *
*/
EXTERN S16 TfUiCtfBndCfm ARGS((
   Pst*                 pst,
   SuId                 suId,
   U8                   status
));

/** 
 * @brief Unbind Request from PHY user.
 *
 * @details This primitive is used to unbind the user SAP. The SAP is not
 *          deallocated and hence a new bind request can be issued on this SAP
 *          (without reconfiguring the SAP in PHY).
 *
 * @param[in] pst Pointer to the post structure. SSI uses pst for loosely 
 *                coupled inter-task communication.
 * @param[in] spId The service provider SAP ID. The service provider uses this
 *                 this reference number to idenitfy the SAP.
 * @param[in] reason Defines the reason for the unbind.
 *
 * @return S16
 * -# ROK
 * -# RFAILED
 *
*/
EXTERN S16 TfUiCtfUbndReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   Reason               reason
));

/** 
 * @brief Configuration Request from User.
 *
 * @details This primitive is used by User for the following at PHY:
 *          - Configure cell-related parameters.
 *          - Reconfigure cell-related parameters.
 *          - Release a cell context.
 *          - Configure UE-specific information.
 *          - Reconfigure UE-specific information.
 *          - Release UE-specific configuration.
 * The cell-specific configuration is identified using a cell identifier.
 * The UE-specific configuration is identified using a cell identifier and 
 * an UE identifier.
 * The configuration request primitive is assocated with a transaction 
 * identifier to correlate the configuration confirm returned by PHY.
 *
 * @param[in] pst Pointer to the service user task configuration structure.
 * @param[in] spId The service provider SAP ID.
 * @param[in] transId The transaction identifier.
 * @param[in] cfgReqInfo Pointer to the PHY(Cell/UE) configuration information.
 *
 * @return S16
 *  -# ROK
 *  -# RFAILED
 *
*/
EXTERN S16 TfUiCtfCfgReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   CtfCfgTransId        transId,
   CtfCfgReqInfo*       cfgReqInfo
));

/** 
 * @brief Configuration Confirm from PHY to user.
 *
 * @details This primitive is used to indicate to the service user the status of
 *          configuration done at PHY as a response to configuration request.
 *          The status field in this primitive carries the status of processing
 *          this primitive at PHY. A configuration is treated as success, only 
 *          if it is successful at PHY. The primitive is associated with a 
 *          transaction identifier that is received in the request.
 *
 * @param[in] pst Pointer to the post structure. SSI uses pst for loosely coupled
 *                inter-task communication.
 * @param[in] suId    The service user SAP ID.
 * @param[in] transId The transaction identifier associated with the 
 *                    configuration request.
 * @param[in] status The status of the configuration request processing at PHY.
 *                   -# CTF_CFG_CFM_OK 1
 *                   -# CTF_CFG_CFM_NOK 2
 *
 * @return S16
 *    -# ROK
 *    -# RFAILED
 *
*/
EXTERN S16 TfUiCtfCfgCfm ARGS((
   Pst*                 pst,
   SuId                 suId,
   CtfCfgTransId        transId,
   U8                   status
));

/** 
 * @brief UE ID Change Request from User to PHY.
 *
 * @details This primitive is used by User for reconfiguring the C-RNTI
 *          at PHY of an UE.
 *
 * @param[in] pst Pointer to the service user task configuration structure.
 * @param[in] spId The service provider SAP ID.
 * @param[in] transId The transaction identifier.
 * @param[in] ueInfo UE ID (C-RNTI) of the UE.
 * @param[in] newUeInfo New UE ID (C-RNTI) for the UE denoted by ueInfo.
 *
 * @return S16
 *  -# ROK
 *  -# RFAILED
 *
*/
EXTERN S16 TfUiCtfUeIdChgReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   CtfCfgTransId        transId,
   CtfUeInfo *          ueInfo,
   CtfUeInfo *          newUeInfo
));

/** 
 * @brief UE ID Change Confirm from PHY to user.
 *
 * @details This primitive is used to indicate to the service user the status of
 *          configuration done at PHY as a response to configuration request.
 *          The status field in this primitive carries the status of processing
 *          this primitive at PHY. A configuration is treated as success, only 
 *          if it is successful at PHY. The primitive is associated with a 
 *          transaction identifier that is received in the request.
 *
 * @param[in] pst Pointer to the post structure. SSI uses pst for loosely coupled
 *                inter-task communication.
 * @param[in] suId    The service user SAP ID.
 * @param[in] transId The transaction identifier associated with the configuration
 *                    request.
 * @param[in] status The status of the configuration request processging at PHY.
 *                   -# CTF_CFG_CFM_OK 1
 *                   -# CTF_CFG_CFM_NOK 2
 *
 * @return S16
 *    -# ROK
 *    -# RFAILED
 *
*/
/** UE ID Change Confirm from PHY to User. */
EXTERN S16 TfUiCtfUeIdChgCfm ARGS((
   Pst*                 pst,
   SuId                 suId,
   CtfCfgTransId        transId,
   CtfUeInfo *          ueInfo,
   CmStatus             status
));


#ifdef NH
/* Request from User to PHY to Bind the CTF interface SAPs. */
EXTERN S16 NhLiCtfBndReq ARGS((
   Pst*                 pst,
   SuId                 suId,
   SpId                 spId
));
/* Confirmation from PHY to User for the Bind/Unbind 
 * Request for the CTF interface SAP. */
EXTERN S16 NhLiCtfBndCfm ARGS((
   Pst*                 pst,
   SuId                 suId,
   U8                   status
));
/* Request from User to PHY to Unbind the CTF interface SAP. */
EXTERN S16 NhLiCtfUbndReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   Reason               reason
));
/* Configuration Request from User to PHY for 
 * cell or dedicated configuration. */
EXTERN S16 NhLiCtfCfgReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   CtfCfgTransId        transId,
   CtfCfgReqInfo*       cfgReqInfo
));
/* Configuration Confirm from PHY to User. */
EXTERN S16 NhLiCtfCfgCfm ARGS((
   Pst*                 pst,
   SuId                 suId,
   CtfCfgTransId        transId,
   U8                   status 
));
/** UE ID Change Request from User to PHY. */
EXTERN S16 NhLiCtfUeIdChgReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   CtfCfgTransId        transId,
   CtfUeInfo *          ueInfo,
   CtfUeInfo *          newUeInfo
));
/** UE ID Change Confirm from PHY to user. */
EXTERN S16 NhLiCtfUeIdChgCfm ARGS((
   Pst*                 pst,
   SuId                 suId,
   CtfCfgTransId        transId,
   CtfUeInfo *          ueInfo,
   CmStatus             status
));
#endif /* NH */

#ifdef LCCTF
/* Request from User to PHY to Bind the CTF interface SAP. */
EXTERN S16 cmPkCtfBndReq ARGS((
   Pst*                 pst,
   SuId                 suId,
   SpId                 spId
));
/* Request from User to PHY to Bind the CTF interface SAP. */
EXTERN S16 cmUnpkCtfBndReq ARGS((
   CtfBndReq            func,
   Pst*                 pst,
   Buffer               *mBuf
));
/* Confirmation from PHY to user for the Bind/Unbind 
 * Request for the CTF interface SAP.
*/
EXTERN S16 cmPkCtfBndCfm ARGS((
   Pst*                 pst,
   SuId                 suId,
   U8                   status
));
/* Confirmation from PHY to User for the Bind/Unbind 
 * Request for the CTF interface SAP.
*/
EXTERN S16 cmUnpkCtfBndCfm ARGS((
   CtfBndCfm            func,
   Pst*                 pst,
   Buffer               *mBuf
));
/* Request from User to PHY to Unbind the CTF interface SAP. */
EXTERN S16 cmPkCtfUbndReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   Reason               reason
));
/* Request from User to PHY to Unbind the interface SAPs. */
EXTERN S16 cmUnpkCtfUbndReq ARGS((
   CtfUbndReq           func,
   Pst*                 pst,
   Buffer               *mBuf
));
/* Configuration Request from User to PHY for 
 * cell or dedicated configuration. 
*/
EXTERN S16 cmPkCtfCfgReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   CtfCfgTransId        transId,
   CtfCfgReqInfo  *     cfgReqInfo
));
/* Configuration Request from User to PHY for 
 * cell or dedicated configuration.
*/
EXTERN S16 cmUnpkCtfCfgReq ARGS((
   CtfCfgReq            func,
   Pst*                 pst,
   Buffer               *mBuf
));
/* Configuration Confirm from PHY to User. */
EXTERN S16 cmPkCtfCfgCfm ARGS((
   Pst*                 pst,
   SuId                 suId,
   CtfCfgTransId        transId,
   U8                   status
));
/* Configuration Confirm from PHY to User. */
EXTERN S16 cmUnpkCtfCfgCfm ARGS((
   CtfCfgCfm            func,
   Pst*                 pst,
   Buffer               *mBuf
));
/** UE ID Change Request from User to PHY. */
EXTERN S16 cmPkCtfUeIdChgReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   CtfCfgTransId        transId,
   CtfUeInfo *          ueInfo,
   CtfUeInfo *          newUeInfo
));
/** UE ID Change Request from User to PHY. */
EXTERN S16 cmUnpkCtfUeIdChgReq ARGS((
   CtfUeIdChgReq        func,
   Pst*                 pst,
   Buffer               *mBuf
));
/** UE ID Change Confirm from PHY to User. */
EXTERN S16 cmPkCtfUeIdChgCfm ARGS((
   Pst*                 pst,
   SuId                 suId,
   CtfCfgTransId        transId,
   CtfUeInfo *          ueInfo,
   CmStatus             status
));
/** UE ID Change Confirm from PHY to User. */
EXTERN S16 cmUnpkCtfUeIdChgCfm ARGS((
   CtfUeIdChgCfm        func,
   Pst*                 pst,
   Buffer               *mBuf
));
#endif /* LCCTF */

#ifdef DM
/* Request from User to PHY to Bind the CTF interface SAP. */
EXTERN S16 DmUiCtfBndReq ARGS((
   Pst*                 pst,
   SuId                 suId,
   SpId                 spId
));
/* Confirmation from PHY to User for the Bind/Unbind 
 * Request for the CTF interface SAP.
*/
EXTERN S16 DmUiCtfBndCfm ARGS((
   Pst*                 pst,
   SuId                 suId,
   U8                   status
));
/* Request from User to PHY to Unbind the CTF interface SAP. */
EXTERN S16 DmUiCtfUbndReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   Reason               reason
));
/* Configuration Request from User to PHY for 
 * cell or dedicated configuration.
*/
EXTERN S16 DmUiCtfCfgReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   CtfCfgTransId        transId,
   CtfCfgReqInfo*       cfgReqInfo
));
/* Configuration Confirm from PHY to User. */
EXTERN S16 DmUiCtfCfgCfm ARGS((
   Pst*                 pst,
   SuId                 suId,
   CtfCfgTransId        transId,
   U8                   status
));
/** UE ID Change Request from User to PHY. */
EXTERN S16 DmUiCtfUeIdChgReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   CtfCfgTransId        transId,
   CtfUeInfo *          ueInfo,
   CtfUeInfo *          newUeInfo
));
/** UE ID Change Confirm from PHY to user. */
EXTERN S16 DmUiCtfUeIdChgCfm ARGS((
   Pst*                 pst,
   SuId                 suId,
   CtfCfgTransId        transId,
   CtfUeInfo *          ueInfo,
   U8                   status
));
#endif /* DM */

/*****************************************************************************
 *                      PACK/UNPACK FUNCTIONS
 ****************************************************************************/
#ifdef LCCTF
EXTERN S16 cmPkCtfCfgTransId ARGS((
   CtfCfgTransId        *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCtfCfgTransId ARGS((
   CtfCfgTransId        *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCtfUeInfo ARGS((
   CtfUeInfo            *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCtfUeInfo ARGS((
   CtfUeInfo            *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCtfBwCfgInfo ARGS((
   CtfBwCfgInfo         *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCtfBwCfgInfo ARGS((
   CtfBwCfgInfo         *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCtfTxSchemeCfg ARGS((
   CtfTxSchemeCfg       *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCtfTxSchemeCfg ARGS((
   CtfTxSchemeCfg       *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCtfAntennaCfgInfo ARGS((
   CtfAntennaCfgInfo    *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCtfAntennaCfgInfo ARGS((
   CtfAntennaCfgInfo    *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCtfPrachCfgInfo ARGS((
   CtfPrachCfgInfo      *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCtfPrachCfgInfo ARGS((
   CtfPrachCfgInfo      *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCtfPdschCfgInfo ARGS((
   CtfPdschCfgInfo      *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCtfPdschCfgInfo ARGS((
   CtfPdschCfgInfo      *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCtfPuschCfgBasic ARGS((
   CtfPuschCfgBasic     *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCtfPuschCfgBasic ARGS((
   CtfPuschCfgBasic     *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCtfPuschUlRS ARGS((
   CtfPuschUlRS         *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCtfPuschUlRS ARGS((
   CtfPuschUlRS         *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCtfPuschCfgInfo ARGS((
   CtfPuschCfgInfo      *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCtfPuschCfgInfo ARGS((
   CtfPuschCfgInfo      *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCtfPhichCfgInfo ARGS((
   CtfPhichCfgInfo      *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCtfPhichCfgInfo ARGS((
   CtfPhichCfgInfo      *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCtfPucchCfgInfo ARGS((
   CtfPucchCfgInfo      *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCtfPucchCfgInfo ARGS((
   CtfPucchCfgInfo      *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCtfSrsUlCfgInfo ARGS((
   CtfSrsUlCfgInfo      *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCtfSrsUlCfgInfo ARGS((
   CtfSrsUlCfgInfo      *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCtfTddSfCfgInfo ARGS((
   CtfTddSfCfgInfo      *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCtfTddSfCfgInfo ARGS((
   CtfTddSfCfgInfo      *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCtfCellCfgInfo ARGS((
   CtfCellCfgInfo       *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCtfCellCfgInfo ARGS((
   CtfCellCfgInfo       *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCtfCellRecfgInfo ARGS((
   CtfCellRecfgInfo     *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCtfCellRecfgInfo ARGS((
   CtfCellRecfgInfo     *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCtfDedPdschCfgInfo ARGS((
   CtfDedPdschCfgInfo   *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCtfDedPdschCfgInfo ARGS((
   CtfDedPdschCfgInfo   *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCtfDedPucchCfgInfo ARGS((
   CtfDedPucchCfgInfo   *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCtfDedPucchCfgInfo ARGS((
   CtfDedPucchCfgInfo   *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCtfDedPuschCfgInfo ARGS((
   CtfDedPuschCfgInfo   *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCtfDedPuschCfgInfo ARGS((
   CtfDedPuschCfgInfo   *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCtfCqiRptModePeriodic ARGS((
   CtfCqiRptModePeriodic *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCtfCqiRptModePeriodic ARGS((
   CtfCqiRptModePeriodic *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCtfCqiReportCfgInfo ARGS((
   CtfCqiReportCfgInfo  *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCtfCqiReportCfgInfo ARGS((
   CtfCqiReportCfgInfo  *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCtfDedSrsUlCfgInfo ARGS((
   CtfDedSrsUlCfgInfo   *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCtfDedSrsUlCfgInfo ARGS((
   CtfDedSrsUlCfgInfo   *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCtfDedSRCfgInfo ARGS((
   CtfDedSRCfgInfo      *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCtfDedSRCfgInfo ARGS((
   CtfDedSRCfgInfo      *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCtfDedAntCfgInfo ARGS((
   CtfDedAntCfgInfo     *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCtfDedAntCfgInfo ARGS((
   CtfDedAntCfgInfo     *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCtfUeCatCfgInfo ARGS((
   CtfUeCatCfgInfo      *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCtfUeCatCfgInfo ARGS((
   CtfUeCatCfgInfo      *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCtfDedCfgInfo ARGS((
   CtfDedCfgInfo        *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCtfDedCfgInfo ARGS((
   CtfDedCfgInfo        *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCtfDedRecfgInfo ARGS((
   CtfDedRecfgInfo      *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCtfDedRecfgInfo ARGS((
   CtfDedRecfgInfo      *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCtfCellReleaseInfo ARGS((
   CtfCellReleaseInfo   *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCtfCellReleaseInfo ARGS((
   CtfCellReleaseInfo   *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCtfDedReleaseInfo ARGS((
   CtfDedReleaseInfo    *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCtfDedReleaseInfo ARGS((
   CtfDedReleaseInfo    *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCtfCfgInfo ARGS((
   CtfCfgInfo           *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCtfCfgInfo ARGS((
   CtfCfgInfo           *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCtfReCfgInfo ARGS((
   CtfReCfgInfo         *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCtfReCfgInfo ARGS((
   CtfReCfgInfo         *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCtfReleaseInfo ARGS((
   CtfReleaseInfo       *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCtfReleaseInfo ARGS((
   CtfReleaseInfo       *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCtfCfgReqInfo ARGS((
   CtfCfgReqInfo        *param,
   Buffer               *mBuf
));
/* ctf_x_001.main_4: Added support for vendor specific parameters */
EXTERN S16 cmUnpkCtfCfgReqInfo ARGS((
   Pst                  *pst,
   CtfCfgReqInfo        *param,
   Buffer               *mBuf
)) ;

#ifdef CTF_VER3
EXTERN S16 cmPkCtfVendorSpecParams ARGS((
   CtfVendorSpecific *param,
   Buffer *mBuf
));

EXTERN S16 cmUnpkCtfVendorSpecParams ARGS((
    Pst*                 pst,
    CtfVendorSpecific *param,
    Buffer *mBuf
));
#endif /* CTF_VER3*/
#endif /* LCCTF */


#ifdef __cplusplus
}
#endif
#endif /* __CTF_X__ */

/**********************************************************************
  
         End of file:     ctf.x@@/main/5 - Thu Feb 16 20:00:16 2012
  
**********************************************************************/

/**********************************************************************
  
        Notes:
  
**********************************************************************/

/**********************************************************************
Put notes here
**********************************************************************/


/**********************************************************************
  
        Revision history:
  
**********************************************************************/
  
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---    vkulkarni        1. Initial release.
/main/2      ---    chebli           1. (ctf_x_001.main_1)Added dedicated CQI and Antenna re-configuration
                                        support.
/main/3      ---      ctf_x_001.main_2 mpatel 1. Updated for Release of 3.1. 
                                        Added cqiMask, pmiRiRpt
/main/4  ctf_x_001.main_3 mnawas      1. Added missing fields inside the CFG and RECFG structure
/main/5      ---      ctf_x_001.main_4 ragrawal    1. Added enum CtfTddAckNackFBMode
                                      2. Added repFactorPres,tddAckNackCfgPres and tddAckNackFBMode
                                         in CtfDedPucchCfgInfo structure 
                                      3. Added support for vendor specific parameters.
                                      4. ReEst Fix.
*********************************************************************91*/
