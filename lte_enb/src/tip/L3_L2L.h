/**********************************************************************

  Name:     L3_L2L.h

  Type:     C Include File

  Desc:     Structures, variables, and typedefs required by the L3<->L2L
             interface.

  File:     L3_L2L.h

  Prg:      Radisys

**********************************************************************/

#ifndef __L3_L2L_H__
#define __L3_L2L_H__

/* Message Identities */
#define MAC_CELLCONFIG_REQ   301
#define MAC_CELLCONFIG_RSP   302
#define MAC_CELLRECONFIG_REQ 303
#define MAC_CELLRECONFIG_RSP 304
#define MAC_CELLDELETE_REQ   305
#define MAC_CELLDELETE_RSP   306
#define MAC_BROADCASTMSG_REQ 307
#define MAC_BROADCASTMSG_RSP 308
#define MAC_UECONFIG_REQ     309
#define MAC_UECONFIG_RSP     310
#define MAC_UERECONFIG_REQ   311
#define MAC_UERECONFIG_RSP   312
#define MAC_UEDELETE_REQ     313
#define MAC_UEDELETE_RSP     314
#define MAC_CELLSTART_IND    315

#define RLC_CMNCHNL_CONFIG_REQ   331
#define RLC_CMNCHNL_CONFIG_RSP   332
#define RLC_CMNCHNL_DELETE_REQ   333
#define RLC_CMNCHNL_DELETE_RSP   334
#define RLC_UECONFIG_REQ     335
#define RLC_UECONFIG_RSP     336
#define RLC_UERECONFIG_REQ   337
#define RLC_UERECONFIG_RSP   338
#define RLC_UEDELETE_REQ     339
#define RLC_UEDELETE_RSP     340
#define RRC_CCCHMSG_IND      341
#define RLC_CCCHMSG_REQ      342
#define RLC_PCCHMSG_REQ      343

#define PHY_CELLCONFIG_REQ   371
#define PHY_CELLCONFIG_RSP   372
#define PHY_CELLDELETE_REQ   373
#define PHY_CELLDELETE_RSP   374
#define L3_TTI_IND           375

#define L2_UERELEASE_IND     381

/** @brief User Equipment Identity */
typedef struct ueIdentity
{
   uint16_t ueIndex;               /*!< UE Identity Value: 0 to max UE per Cell */
   uint16_t cRnti;                 /*!< C-RNTI */
}UeIdentity;

/** @brief Radio Bearer Identity */
typedef struct rbIdentity
{
   uint8_t rbId;                  /*!< Radio Bearer Identity */
   uint8_t lcId;                  /*!< Logical Channel Identity */
   uint8_t spare[2];              /*!< Added for 4byte alignment */
}RbIdentity;

/**
 * @brief Timing Info
 */
typedef struct timingInfo
{
   uint16_t sfn;                  /*!< System Frame Number
                                    Value: 0..1023 */
   uint8_t  sf;                   /*!< Subframe Number
                                    Value: 0..9 
                                    Currently, sf level granularity
                                    is not provided */
   uint8_t  spare;                /*!< Added for 4 byte Alignment */
}TimingInfo;

/**************
 ** MAC APIs **
 *************/

/**
  @brief DL Power Control Configuration */
typedef struct dlPowerControlConfig
{
   uint16_t pcfichPowerOffset;     /*!< pcfichPowerOffset indicates
                                    * the offset to power
                                    * per antenna of the PCFICH with
                                    * respect to the reference signal power.
                                    * Range: 0, 1, 2,
                                    * 10000 (represents -6dB to 4dB in steps
                                    * 0.001dB) */
   uint16_t phichPowerOffset;      /*!< phichPowerOffset indicates
                                    * power per antenna of the
                                    * PHICH with respect to the
                                    * reference signal power
                                    * Range: 0, 1, 2,
                                    * 10000(represents -6dB to
                                    * 4dB in steps 0.001dB) */
   uint16_t pdcchPowerOffset;      /*!< pdcchPowerOffset indicates the offset
                                    * to reference signal power
                                    * for PDCCH (DCI PDUs)
                                    * Range : 0, 1, 2,
                                    * 10000 (represents -6dB to
                                    * 4dB in steps 0.001dB) */
   uint16_t pbchTransmissionPower; /*!< pbchTransmissionPower indicates
                                    * offset to the reference
                                    * signal power for PBCH
                                    * Range: 0, 1, 2
                                    * 10000 (represents -6dB to
                                    * 4dB in steps 0.001dB) */
   uint16_t pchTransmissionPower;  /*!< pchTransmissionPower indicates
                                    * the offset to the reference
                                    * signal power for PCH
                                    * Range : 0, 1, 2,
                                    * 10000 (represents -6dB to
                                    * 4dB in steps 0.001dB) */
   uint16_t spare;                 /*!< Added for 4byte alignment */
}DlPowerControlConfig;

/**
  @brief Scheduler Specific Configuration */
typedef struct schedulerSpecificConfiguration
{
   uint8_t dlSchedulingType;       /*!< Type of Scheduler
                                    * Value:
                                    * 1: Proportional Fairness Scheduler
                                    * 2: Round-Robin Scheduler
                                    * 3: QoS-Aware */
   uint8_t ulSchedulingType;       /*!< Type of Scheduler
                                    * Value:
                                    * 1: Proportional Fairness Scheduler
                                    * 2: Round-Robin Scheduler
                                    * 3: QoS-Aware */
   uint16_t spare;                  /*!< Added for 4byte alignment */
}SchedulerSpecificConfiguration;

/**
  @brief Number of Users per TTI */
typedef struct numberOfUsersPerTTI
{
   uint8_t  numberOfDlUsersPerTTI; /*!< Maximum number of UEs that
                                    * can be scheduled every subframe
                                    * Value: 1,2,4 */
   uint8_t  numberOfUlUsersPerTTI; /*!< Maximum number of UEs that
                                    * can be scheduled every subframe
                                    * Value: 1,2,4 */
   uint16_t spare;                 /*!< Added for 4byte alignment */
}NumberOfUsersPerTTI;

/**
  @brief PUSCH Configuration */
typedef struct puschConfiguration
{
   uint16_t numberOfSubBands;      /*!< Number of PUSCH Subbands
                                    * value: 1..4
                                    * Set as 1
                                    * Refer: TS 36.211 [5.3.4]*/
   uint16_t hoppingMode;           /*!< Hopping Mode
                                    * value: 0 Inter Subframe
                                    * 1: Intra Subframe
                                    * Refer: TS 36.211 [5.3.4]. */
   uint8_t  hopOffset;             /*!< Refer: TS 36.211 [5.3.4]. */
   uint8_t  spare[3];              /*!< Added for 4byte alignment */
}PuschConfiguration;

/**
 * UL Power Alpha */
typedef enum ulPowerAlpha
{
   POWER_ALPHA0 = 0,                /**< Power Alpha Value 0*/
   POWER_ALPHA4 = 4,                /**< Power Alpha Value 0.4*/
   POWER_ALPHA5 = 5,                /**< Power Alpha Value 0.5*/
   POWER_ALPHA6 = 6,                /**< Power Alpha Value 0.6*/
   POWER_ALPHA7 = 7,                /**< Power Alpha Value 0.7*/
   POWER_ALPHA8 = 8,                /**< Power Alpha Value 0.8*/
   POWER_ALPHA9 = 9,                /**< Power Alpha Value 0.9*/
   POWER_ALPHAALL = 10              /**< Power Alpha Value 1*/
}UlPowerAlpha;

/**
  @brief UL Power Control Configuration */
typedef struct ulPowerControlConfig
{
   int8_t   p0NominalPusch;           /*!< P0 Nominal PUSCH
                                       * Refer: TS 36.213, 5.1.1.1 */
   int8_t   p0NominalPucch;           /*!< P0 Nominal PUSCH */
   int8_t   deltaPreambleMessage3;    /*!< Delta Preamble Message3*/
   uint8_t  spare ;                   /*!< Added for 4 byte Alignment */
   UlPowerAlpha alpha;                /*!< Alpha
                                       * Value:0,4,5,6,7,8,9,10
                                       * Refer: TS 36.213, 5.1.1.1 */
   uint16_t format3PucchStartTpcRnti; /*!< Start RNTI for TPC */
   uint16_t format3PucchEndRnti;      /*!< Indicates contiguous
                                       * range of RNTI */
   uint16_t format3APucchStartTpcRnti;/*!< Start RNTI for TPC */
   uint16_t format3APucchEndRnti;     /*!< Indicates contiguous
                                       *range of RNTI */
   uint16_t format3PuschStartTpcRnti; /*!< Start RNTI for TPC*/
   uint16_t format3PuschEndRnti;      /*!< Indicates contiguous
                                       * range of RNTI */
   uint16_t format3APuschStartTpcRnti;/*!< Start RNTI for TPC*/
   uint16_t format3APuschEndRnti;     /*!< Indicates contiguous
                                       *  range of RNTI */
}UlPowerControlConfig;

/**
  @brief RACH configuration */
typedef struct rachConfiguration
{
   uint8_t raWindowSize;             /*!< RA window Size
                                      * Value: 2..8,10
                                      * Refer: TS 36.321 */
   uint8_t maxMsg3HarqTransmissions; /*!< Maximum Number of
                                      * Msg3 HARQ Transmissions
                                      * value: Minimum - 1, Maximum - 8
                                      * Refer: TS 36.321 */
   uint8_t numberOfRAPreambles;      /*!< Number of RA Preambles
                                      * Value: 4,8,12,16,20,24,28,32,
                                      * 36,40,44,48,52,56,60 64
                                      * Refer: TS 36.321 */
   uint8_t sizeOfRAPreambleinGroupA; /*!< Size of RA Preamble in Group A
                                      * Value: 4,8,12,16,20,24,28,32,
                                      * 36,40,44,48,52,56,60
                                      * Refer: TS 36.321 */
   uint16_t messageSizeGroupA;       /*!< Message Size Group A
                                      * Value: 56,144,208,256
                                      * Refer: TS 36.321 */
   uint8_t prachConfigurationIndex;  /*!< PRACH Configuration Index
                                      * Value: 0..63
                                      * Refer: TS 36.211 */
   uint8_t prachFrequencyOffset;     /*!< PRACH Frequency Offset
                                      * Value: 0..94
                                      * Refer: TS 36.211 */
   uint8_t contentionResolutionTimer; /*!< Contention Resolution Timer
                                       * Value: 8,16,24,32,40,48,56,64 */
   uint8_t spare[3];                 /*!< Added for 4byte Alginment */
}RachConfiguration;

/**
 * SRS BandwidthCondiguration */
typedef enum srsBwConfiguration
{
   SRS_BANDWIDTH_0, /**< Sounding Reference Signal BW CFG 0 */
   SRS_BANDWIDTH_1, /**< Sounding Reference Signal BW CFG 1 */
   SRS_BANDWIDTH_2, /**< Sounding Reference Signal BW CFG 2 */
   SRS_BANDWIDTH_3, /**< Sounding Reference Signal BW CFG 3 */
   SRS_BANDWIDTH_4, /**< Sounding Reference Signal BW CFG 4 */
   SRS_BANDWIDTH_5, /**< Sounding Reference Signal BW CFG 5 */
   SRS_BANDWIDTH_6, /**< Sounding Reference Signal BW CFG 6 */
   SRS_BANDWIDTH_7  /**< Sounding Reference Signal BW CFG 7 */
}SrsBwConfiguration;

/**
  @brief SRS Configuration */
typedef struct srsConfiguration
{
   Bool    cellSpecificSrsEnable;      /*!< Cell-specific SRS enable flag
                                        * Value-0-Disable/1-Enable */
   uint8_t srsSubframeConfiguration;   /*!< SRS Subframe Configuration
                                        * Values: 0..15
                                        * Refer: TS 36.211,
                                        * [21,table 5.5.3.3-1 and 5.5.3.3-2*/
   Bool    simultaneousAckNackAndSrs;  /*!< Indicates if Simultaneous
                                        * AckNack and SRS is enabled
                                        * Value 1- Present, 0- Absent
                                        * Refer: TS 36.213 [8.2] */
   uint8_t spare;                      /*!< Added spare byte for
                                        * 4byte alignment */
   SrsBwConfiguration srsBwConfigInfo; /*!< SRS Bandwidth
                                        * Configuration
                                        * Values: 0..7
                                        * Refer: TS 36.211,
                                        * [21, table 5.5.3.2-1,
                                        * 5.5.3.2-2, 5.5.3.2-3
                                        * and 5.5.3.2-4].*/
}SrsConfiguration;

/**
  @brief PUCCH Configuration */
typedef struct pucchConfiguration
{
   uint8_t   resourceSize;    /*!< PUCCH resource-size or
                               * N^(2)_RB (in RBs).
                               * Same as nRB-CQI
                               * Refer: TS 36.211 [5.4] */
   uint8_t   deltaShift;      /*!< Delta Shift for PUCCH
                               * Value: 1, 2, 3
                               * Refer: TS 36.211, 5.4.1 */
   uint16_t  n1PucchAckNack;  /*!< N^(1)_PUCCH
                               * Refer: TS 36.213, [10.1] */
   uint8_t   cyclicShift;     /*!< Cyclic Shift for PUCCH (N^(1) _CS
                               * Value: [0-7]
                               * Refer: TS 36.211
                               * [Table 5.5.2.1.1-2] */
   uint8_t   spare[3];        /*!< Added spare byte for
                               * 4byte alignment */
}PucchConfiguration;

/**
 * PHICH For more details refer to 36.211 Sec 6.9 */
typedef enum phichDuration
{
   PHICH_DUR_NORMAL,
   PHICH_DUR_EXTENDED
}PhichDuration;

/**
 * PHICH For more details refer to 36.211 Sec 6.9 */
typedef enum phichRE
{
   PHICH_R_ONE_SIXTH, /**< PHICH Values 1/6 */
   PHICH_R_HALF,      /**< PHICH Values 1/2 */
   PHICH_R_ONE,       /**< PHICH Values 1   */
   PHICH_R_TWO        /**< PHICH Values 2   */
}PhichRE;

/**
  @brief PHICH Configuration */
typedef struct phichConfiguration
{
   PhichRE phichResource; /*!< The number of resources element
                            groups used for PHICH.
                            Value:
                            0: PHICH_R_ONE_SIXTH,
                            1: PHICH_R_HALF,
                            2: PHICH_R_ONE,
                            3: PHICH_R_TWO
                            Refer: TS 36.211 [6.9] */
   PhichDuration phichDuration; /*!< PHICH Duration: Value: 1-extended/0-normal
                                  Refer: TS 36.211 [Table 6.9.3-1] */
}PhichConfiguration;

/**
 *  Duplexing mode */
typedef enum duplexMode
{
   TDD,          /**< TDD Mode configuration */
   FDD,          /**< FDD Mode configuration */
   HD_FDD        /**< HD-FDD Mode configuration */
}DuplexMode;

/**
 * Bandwidth */
typedef enum bandwidth
{
   BW_RB_6 = 6,
   BW_RB_15 = 15,
   BW_RB_25 = 25,
   BW_RB_50 = 50,
   BW_RB_75 = 75,
   BW_RB_100 = 100
}Bandwidth;

/**
  @brief Bandwidth Configuration */
typedef struct bandwidthConfiguration
{
   Bandwidth  dlBandwidth;   /*!< Value: 6, 15, 25, 50, 75, 100*/
   Bandwidth  ulBandwidth;   /*!< Value: 6, 15, 25, 50, 75, 100*/
   DuplexMode duplexingMode; /*!< Value: 0-TDD, 1- FDD, 2- HD-FDD */
}BandwidthConfiguration;

/**
  @brief RNTI Configuration */
typedef struct rntiConfiguration
{
   uint16_t startRnti;     /*!< Range 0x0001 - 0x003C */
   uint16_t endRnti;       /*!< Range 0x0001 - 0x003C */
}RntiConfiguration;

/**
  @brief HARQ Configuration */
typedef struct harqConfiguration
{
   uint8_t  maxDlHarqTransmissions;   /*!< Range 1 to 8 */
   uint8_t  maxMsg4HarqTransmissions; /*!< Range 1 to 4 */
   uint16_t spare;                    /*!< Added spare byte
                                       * for 4byte alignment */
}HarqConfiguration;

/**
  @brief MAC Cell Config Req */
typedef struct macCellConfigReq
{
   uint8_t           cyclicPrefix;     /*!< DL/UL Cyclic Prefix
                                        * Value: 0 Normal, 1 Extended
                                        * Refer: TS 36.211 [ 5.2.1] */
   Bool              enable64Qam;      /*!< Value: 0 16QAM, 1 64QAM */
   uint8_t           cfiValue;         /*!< Range 1 to 4 */
   Bool              dynamicCfiEnable; /*!< 0 - Not enabled, 1 - Enabled */
   HarqConfiguration harqConfigInfo;   /*!< Contains the details of DL
                                         And Msg4 retransmission */
   RntiConfiguration rntiConfigInfo;   /*!< Contains the details of rnti */
   Bool              dlfsEnable;       /*!< 0 - Not enabled, 1 - Enabled */
   Bool              ulfsEnable;       /*!< 0 - Not enabled, 1 - Enabled */
   int8_t            pMax;             /*!< Cell Uplink Transmission Power */
   uint8_t	     spare;
   uint16_t          defaultPagingCycle; /*!< Default paging cycle,
                                          * used to derive 'T' in TS 36.304.
                                          * Range : 32, 64, 128, 256
                                          * Refer: 36.304 , section 7
                                          * 36.331, sec 6.3.2 */
   uint16_t	     spare1;
   BandwidthConfiguration bwInfo;          /*!< Contains DL , UL and
                                            * Duplex mode information */
   PhichConfiguration     phichConfigInfo; /*!< Contains the resource and
                                            * duration */
   PucchConfiguration     pucchConfigInfo;
   SrsConfiguration       srsConfigInfo;
   RachConfiguration      rachConfigInfo;
   UlPowerControlConfig   ulPowerControlConfigInfo;
   PuschConfiguration     puschConfigInfo;
   NumberOfUsersPerTTI    numOfUsersPerTTI;
   SchedulerSpecificConfiguration schedulerSpecificConfigInfo;
   DlPowerControlConfig   dlPowerControlConfigInfo;
   uint8_t                numOfTxAntennas; /*!< numOfTxAntennas indicates
                                            * the number of
                                            * Transmission Antennas
                                            * Value: 1,2
                                            * Refer : 36.211, sec: 5.3.3 */
   uint8_t nB;            /*!< The value of nB is used in the calculation
                           * of Ns as below Ns = max (1, nB/T)
                           * The subframe patterns for paging is derived
                           * from Ns as per the 36.304,
                           * section 7 specification.
                           * T is the default paging cycle
                           * 0 - 4T
                           * 1 - 2T
                           * 2 - T
                           * 3 - T/2
                           * 4 - T/4
                           * 5 - T/8
                           * 6 - T/16
                           * 7 - T/32 */
   uint16_t l3SfPeriodicity; /*!< Interval of sf indication to L3.
                               Should be in the order of 10 milliseconds. */
}MacCellConfigReq;


/**
  @brief MAC Cell Config Rsp */
typedef struct macCellConfigRsp
{
   uint16_t status;                 /*!< Status of the configuration request
                                     * sent from higher layer.
                                     * Value: 0: success, 1: failure */
   uint16_t spare;                  /*!< Added spare byte for 4byte alignment */
}MacCellConfigRsp;

/**
  @brief Mac Cell Delete Rsp */
typedef struct macCellDeleteRsp
{
   uint16_t status;                /*!< Status of the configuration
                                    * request sent from higher layer.
                                    * Value: 0: success, 1: failure */
   uint16_t spare;                 /*!< Added spare byte for 4byte alignment */
}MacCellDeleteRsp;

/**
  @brief Transmission Mode Configuration */
typedef struct transmissionModeConfig
{
   Bool    transmissionModePresent; /*!< Indicates presence of
                                     * Transmission Mode for UE
                                     * Value: 1- Present, 0- Absent */
   uint8_t transmissionMode;        /*!< Transmission Mode configured
                                     * to the UE
                                     * Value: 1..9
                                     * Refer: TS 36.213 [7.1] */
   uint16_t spare;                  /*!< Added spare byte for
                                     * 4byte alignment */
}TransmissionModeConfig;

/**
 * Aperiodic Cqi Transmission mode */
typedef enum aperiodicCqiTransMode
{
   APERIODIC_CQI_MOD12,  /**< Aperiodic CQI Mode 1-2 */
   APERIODIC_CQI_MOD20,  /**< Aperiodic CQI Mode 2-0 */
   APERIODIC_CQI_MOD22,  /**< Aperiodic CQI Mode 2-2 */
   APERIODIC_CQI_MOD30,  /**< Aperiodic CQI Mode 3-0 */
   APERIODIC_CQI_MOD31   /**< Aperiodic CQI Mode 3-1 */
}AperiodicCqiTransMode;

/**
  @brief Aperiodic CQI Config */
typedef struct aperiodicCqiConfig
{
   Bool                  present;          /*!< Indicates presence of
                                            * Aperiodic CQI configuration for UE
                                            * Value: 1- Present, 0- Absent */
   uint8_t               spare[3];         /*!< Added spare byte for 4byte alignment */
   AperiodicCqiTransMode aperiodicCqiMode; /*!< Mode of Aperiodic CQI
                                            * Value:
                                            * 0- Aperiodic CQI mode 1-2
                                            * 1- Aperiodic CQI mode 2-0
                                            * 2- Aperiodic CQI mode 2-2
                                            * 3- Aperiodic CQI mode 3-0
                                            * 4- Aperiodic CQI mode 3-1
                                            * Refer: TS 36.213 [7.2.1]. */
}AperiodicCqiConfig;

/**
 * Periodic Cqi Transmission Mode */
typedef enum periodicCqiTransMode
{
   PERIODIC_CQI_MOD10,   /**< Periodic CQI Mode 1-0 */
   PERIODIC_CQI_MOD11,   /**< Periodic CQI Mode 1-1 */
   PERIODIC_CQI_MOD20,   /**< Periodic CQI Mode 2-0 */
   PERIODIC_CQI_MOD21    /**< Periodic CQI Mode 2-1 */
}PeriodicCqiTransMode;

/**
  @brief Periodic CQI Config */
typedef struct periodicCqiConfig
{
   Bool    present;                  /*!< Indicates presence of Periodic
                                      * CQI configuration for UE
                                      * Value: 1- Present, 0- Absent */
   uint8_t cqiPucchResourceIndex;    /*!< CQI-PUCCH-Resource
                                      * Index same as N2PUCCH
                                      * Value: 0..1185
                                      * Refer: TS 36.213 [7.2]. */
   uint8_t cqiPmiConfigurationIndex; /*!< CQI-PMI Configuration
                                      * Index for periodicity
                                      * Value: 0..1023
                                      * Refer: TS 36.213
                                      * [tables 7.2.2-1A and 7.2.2-1C] */
   uint8_t k;                        /*!< Subband size
                                      * Value: 1..4
                                      * Refer: TS 36.213 [7.2.2]. */
   PeriodicCqiTransMode periodicCqiMode;  /*!< Mode of Periodic CQI
                                           * Value:
                                           * 0-Periodic CQI mode 1-0
                                           * 1-Periodic CQI mode 1-1
                                           * 2-Periodic CQI mode 2-0
                                           * 3-Periodic CQI mode 2-1
                                           * Refer: TS 36.213
                                           * [table 7.2.2-1]. */
   uint8_t  simultaneousAckNackAndCqi; /*!< Indicates Support of
                                        * Simultaneous-ACKNACK-and-CQI
                                        * Value: 1- Allowed 0- Not Allowed */
   Bool     riEnableFlag;              /*!< Indicates presence/processing
                                        * of Rank Indication
                                        * Value: 1- Present 0- Absent */
   uint16_t riConfigIndex;             /*!< RI Config Index IRI
                                        * Value: 0..1023
                                        * Refer: TS 36.213 [7.2.2-1B]. */
}PeriodicCqiConfig;

/**
  @brief DL CQI Config */
typedef struct dlCqiConfig
{
   AperiodicCqiConfig aperiodicCqiConfigInfo;
   PeriodicCqiConfig  periodicCqiConfigInfo;
}DlCqiConfig;

/**
  @brief UL HARQ configuration */
typedef struct ulHarqConfiguration
{
   uint8_t  maxUlHarqTransmissions;
   uint8_t  spare[3];      /*!< Added spare byte for 4byte alignment */
}UlHarqConfiguration;

/**
  @brief UE UL Power Control Configuration */
typedef struct uePuschGroupPowerControlConfig
{
   Bool     present;  /*!< Indicates presence of UL PUSCH
                       * Power control configuration for UE
                       * Value: 1- Present, 0- Absent */
   uint8_t  index;    /*!< Index of TPC used depending on configured DCI format
                       * Value:
                       * 1..15 for DCI Format 3
                       * 1..31 for DCI Format 3A */
   uint16_t tpcRnti;  /*!< TPC RNTI */
}UePuschGroupPowerControlConfig;

/**
  @brief UE PUCCH Group Power Control Configuration */
typedef struct uePucchGroupPowerControlConfig
{
   Bool     present;        /*!< Indicates presence of
                             * UL PUCCH Power control
                             * configuration for UE
                             * Value: 1- Present, 0- Absent */
   uint8_t  index;          /*!< Index of TPC used depending
                             * on configured DCI format
                             * Value:
                             * 1..15 for DCI Format 3
                             * 1..31 for DCI Format 3A */
   uint16_t tpcRnti;        /*!< TPC RNTI */
   uint8_t  accumulatedFlag;/*!< Flag to denote Accumulated Mode
                             * Value:
                             * 1: Accumulative Power Control
                             * 0: Absolute Power Control
                             * Refer: TS 36.213 [5.1.1.1]. */
   uint8_t  deltaMcsFlag;   /*!< Flag to denote Delta-MCS in UL PC
                             * Value: 1- Present 0- Absent
                             * Refer: TS 36.213 [5.1.1.1]. */
   int8_t   p0UePusch;      /*!< P0 Nominal PUSCH
                             * Value: -8 ..7
                             * Refer: TS 36.213 [5.1.1.1]. */
   int8_t   p0UePucch;      /*!< P0 Nominal PUCCH
                             * Value: in dBm
                             * Refer: TS 36.213 [5.1.1.1]. */
}UePucchGroupPowerControlConfig;

/**
  @brief UE QoS Configuration */
typedef struct ueQosConfiguration
{
   Bool     ambrPresent;    /*!< AMBR support present flag
                             * Value:1- Present 0- Absent */
   uint8_t  spare[3];       /*!< Added spare byte for 4byte alignment */
   uint32_t dlAmbrValue;    /*!< DL AMBR value for UE (bytes/sec) */
   uint32_t ulByteRate;     /*!< UL Byte Rate value for UE (bytes/sec) */
}UeQosConfiguration;

/**
  @brief UE UL Power Control Configuration */
typedef struct ueUlPowerControlConfig
{
   UePuschGroupPowerControlConfig uePuschGroupPowerControlConfigInfo;
   UePucchGroupPowerControlConfig uePucchGroupPowerControlConfigInfo;
}UeUlPowerControlConfig;

/**
  @brief UE DRX Configuration */
typedef struct ueDrxConfiguration
{
   Bool     drxEnabledFlag;          /*!< DRX present flag
                                      * Value:1- Present, 0- Absent
                                      * Refer: TS 36.321 */
   uint8_t  cqiMask;                 /*!< CQI Mask Refer: TS 36.321 */
   uint16_t drxInactivitytimer;      /*!< DRX Inactivity Timer value in
                                      * PDCCH subframes Refer: TS 36.321 */
   uint8_t  drxOnDurationTimer;      /*!< DRX On-duration Timer value in
                                      * PDCCH subframes Refer: TS 36.321 */
   uint8_t  drxRetransmissionTimer;  /*!< DRX On-duration Timer value in
                                      * PDCCH subframes Refer: TS 36.321 */
   uint16_t longDrxCycle;            /*!< DRX Long Cycle value in subframes
                                      * Refer: TS 36.321 */
   uint16_t longDrxCycleStartOffset; /*!< DRX Long Cycle offset in subframes
                                      * Refer: TS 36.321 */
   uint8_t   spare[2];                 /*!< Added spare byte for alignment */
   Bool     shortDrxPresent;         /*!< short DRX present flag
                                      * Value: 1- Present 0- Absent */
   uint8_t   spare1[3];                 /*!< Added spare byte for alignment */
   uint16_t shortDrxCycle;           /*!< Short Long Cycle
                                      * Value in subframes */
   uint16_t shortDrxCycleTimer;      /*!< Value in multiples of
                                      * Short DRX Cycles
                                      * Value: 1..16
                                      * Refer: TS 36.321 */
}UeDrxConfiguration;

/**
  @brief Codebook Subset Restriction Configuration */
typedef struct cbSubsetRestrictionConfig
{
   Bool      cbSubsetRestrictionflag; /*!< Codebook Subset
                                       * Restriction present flag
                                       * Value: 1- Present 0- Absent */
   uint8_t   spare[3];                /*!< Added spare byte for
                                       * 4byte alignment */
   uint32_t  cbBitmap[2];            /*!< Bitmap supporting upto
                                       * 64 codebook options*/
}CbSubsetRestrictionConfig;

/**
  @brief SRS Ue Configuration */
typedef struct srsUeConfiguration
{
   Bool    srsConfigFlag;            /*!< Indicates if UL SRS
                                      * flag is enabled
                                      * Value: 1- Present 0- Absent */
   uint8_t srsConfigIndex;           /*!< SRS COnfig Index
                                      * Value: 0..1023
                                      * Refer: TS 36.213 [table8.2-1]. */
   uint8_t srsBandwidth;             /*!< SRS Bandwidth
                                      * Value: 0,1,2,3
                                      * Refer: TS 36.211, [table 5.5.3.2-1,
                                      * 5.5.3.2-2,
                                      * 5.5.3.2-3 and 5.5.3.2-4].  */
   uint8_t srsHoppingBandwidth;      /*!< SRS Hopping Bandwidth
                                      * Value: 0,1,2,3
                                      * Refer: TS 36.211 [5.5.3.2] */
   uint8_t srsCyclicShift;           /*!< SRS Cyclic Shift
                                      * Value: 0,1,2,3,4,5,6,7
                                      * Refer: TS 36.211 [ 5.5.3.1] */
   uint8_t duration;                 /*!< Duration
                                      * Value: 0 -Single, 1- Infinite
                                      * Refer: TS 36.213 [8.2] */
   uint8_t transmissionComb;         /*!< Transmission Comb
                                      * Value: 0,1
                                      * Refer: TS 36.211 [5.5.3.2] */
   uint8_t frequencyDomainPosition;  /*!< Frequency Domain Position
                                      * Value: 0..23
                                      * Refer: TS 36.211 [5.5.3.2] */
}SrsUeConfiguration;

/**
  @brief SR Configuration */
typedef struct srConfiguration
{
   Bool    srConfigFlag;      /*!< Indicates if SR flag is enabled
                               * Value: 1- Present 0- Absent */
   uint8_t srConfigIndex;     /*!< SR Config Index
                               * Value: 0..155
                               * Refer: TS 36.213 [10.1]. */
   uint16_t srResourceIndex;  /*!< SR Resource Index
                               * Value: 0..2047
                               * Refer: TS 36.213 [10.1]. */
}SrConfiguration;

/**
  @brief UE PUSCH Configuration */
typedef struct uePuschConfiguration
{
   Bool    uePuschConfigSupport;   /*!< Indicates if UE PUSCH
                                    * Configuration is supported
                                    * Value: 1- Present 0- Absent */
   uint8_t harqBetaOffset;         /*!< HARQ Beta Offset
                                    * Refer: TS 36.213 [Table 8.6.3-1]. */
   uint8_t riBetaOffset;           /*!< RI Beta Offset
                                    * Refer: TS 36.213 [Table 8.6.3-3]. */
   uint8_t cqiBetaOffset;          /*!< CQI Beta Offset
                                    * Refer: TS 36.213 [Table 8.6.3-2]. */
}UePuschConfiguration;

/**
  @brief UE Measurement GapConfig */
typedef struct ueMeasurementGapConfig
{
   Bool ueMeasurementGapFlag;  /*!< Measurement Gap feature present flag
                                * Value: 1- Present 0- Absent
                                * Refer: TS 36.213 [10.1]. */
   uint8_t gapPeriod;          /*!< Gap Period
                                * Value:40,80 */
   uint8_t gapOffset;
   uint8_t spare;              /*!< Added spare byte for 4byte alignment */
}UeMeasurementGapConfig;

/**
  @brief UE PDSCH CONFIGURATION */
typedef struct uePdschConfiguration
{
   Bool     uePdschPAConfigFlag;    /*!< Indicates if PDSCH P_A
                                     * config is supported
                                     * Value: 1- Present 0- Absent */
   uint8_t  pA;                     /*!< PA Value: 0..7
                                     * Refer: TS 36.213 [5.2]. */
   uint16_t spare;                  /*!< Added spare byte for
                                     * 4byte alignment */
}UePdschConfiguration;

/**
  @brief CQI PMI Config Index Info */
typedef struct cqiPmiConfigIndexInfo
{
   uint16_t cqiPmiConfigIndex;          /*!< cqiPMIConfigIndex specifies
                                         * the CQI/PMI
                                         * periodicity and configuration index
                                         * Refer: 36.213 Section 7.2
                                         * 36.331 Section 6.3.2 */
   uint16_t cqiPucchResourceIndex;      /*!< cqiPucchResourceIndex specifies
                                         * the pucch resources for periodic
                                         * CQI on uplink
                                         * 36.213 Section 7.2
                                         * 36.331 Section 6.3.2 */
   uint8_t simultaneousAckNackAndCqi;   /*!< simultaneousAc kNackAndCQI
                                         * specifies whether simultaneous
                                         * transmission of CQI and
                                         * ACK/NACK is allowed or not
                                         * Refer : 36.213 Section 7.2
                                         * 36.331 Section 6.3.2 */
   uint8_t cqiFormatIndicatorPeriodic;  /*!< Range : PERIODIC_WIDE
                                         * BAND = 0,
                                         * PERIODIC_SUBBAND = 1
                                         * Refer : 36.213 Section 7.2
                                         * 36.331 Section 6.3.2 */
   uint16_t riConfigIndex;              /*!< riConfigIndex
                                         * Refer : 36.213 Section 7.2
                                         * 36.331 Section 6.3.2  */
   uint8_t subbandCqik;                 /*!< Value K
                                         * (subbandCQI_k) of subbandCQI
                                         *  Parameter: K)
                                         * Refer : 36.213 Section 7.2
                                         * 36.331 Section 6.3.2 */
   uint8_t spare[3];                    /*!< Added spare byte for
                                         * 4byte alignment */
}CqiPmiConfigIndexInfo;

/**
  @brief CQI Periodic configuration */
typedef struct cqiPeriodicConfiguration
{
   uint8_t requestType;         /*!< Range : 0 - RELEASE,
                                 * 1 - SETUP */
   uint8_t spare[3];            /*!< Added spare byte for
                                 * 4byte alignment */
   CqiPmiConfigIndexInfo cqiPeriodicInfo;
}CqiPeriodicConfiguration;

/**
  @brief UE TA Timer Configuration */
typedef struct ueTaTimerConfiguration
{
   Bool       present;    /*!< TA support present flag
                           * Value: 1- Present 0- Absent */
   uint8_t    spare;      /*!< Added spare byte for 4byte alignment */
   uint16_t   taTimer;    /*!< Timer configuration
                           * (in subframes) */
}UeTaTimerConfiguration;

/**
  @brief GBR Qos Info */
typedef struct gbrQosInfo
{
   uint32_t erabMaxBitRateDl;
   uint32_t erabMaxBitRateUl;
   uint32_t erabGuaranteedBitRateDl;
   uint32_t erabGuaranteedBitRateUl;
}GbrQosInfo;

/**
  @brief QOS Info */
typedef struct qosInfo
{
   uint8_t qci;
   uint8_t spare[3];      /*!< Added spare byte for 4byte alignment */
   GbrQosInfo gbrQosConfigInfo;
}QosInfo;

/**
  @brief Dl LC Create Req */
typedef struct dlLcCreateReq
{
   uint8_t lchPriority;
   uint8_t spare[3];      /*!< Added spare byte for 4byte alignment */
}DlLcConfig;

/**
  @brief UL LC Create Req */
typedef struct ulLcCreateReq
{
   uint8_t lcgId;
   uint8_t spare[3];      /*!< Added spare byte for 4byte alignment */
}UlLcConfig;

/**
 * Entity Direction */
typedef enum entityDirection
{
   UPLINK   = 1,
   DOWNLINK = 2,
   BOTH     = 3
}EntityDirection;

/**
  @brief CREATE LC REQ */
typedef struct createLcReq
{
   uint8_t lcConfigType;      /*!< LC config type for UE Reconfig only;
                                   Use 0 for MAC_UEConfig.
                                   0-Reserve, 1-Create, 2-Modify, 3-Delete */
   uint8_t lchId;
   uint8_t spare[2];          /*!< Added spare byte for 4byte alignment */
   EntityDirection dirInfo;   /*!< Conveys the direction of LC ID */
   UlLcConfig ulLcInfo;
   DlLcConfig dlLcInfo;
   QosInfo qosConfigInfo;
}LcConfigInfo;

typedef enum ueAsRelInfo
{
   UE_REL_8,
   UE_REL_9,
   UE_REL_10
} UEAsRelInfo;

/**
  @brief Mac UE Config Req */
typedef struct macUeConfigReq
{
   UeIdentity ueInfo;            /*!< Contains UE Identity */
   Bool       ueConfigPresent;   /*!< Indicates presence
                                  * of UE Configuration
                                  * Value: 1- Present 0- Absent */
   uint8_t    ueCategory;        /*!< UE Category
                                  * Value: 1 to 8
                                  * 1 implies UE Category-1
                                  * Refer: TS 36.306 */
   Bool      ttiBundlingEnable; /*!< TTI bundling
                                                     * present flag
                                                     * Value: 1- Present
                                                     * 0- Absent */
   uint8_t    spare;		 /*!< Added spare byte for 4byte alignment */
   TransmissionModeConfig        transmissionModeConfigInfo;
   DlCqiConfig                   dlCqiConfigInfo;
   UlHarqConfiguration           ulHarqConfigInfo;
   UeUlPowerControlConfig        ueUlPowerControlConfigInfo;
   UeQosConfiguration            ueQosConfigInfo;
   UeTaTimerConfiguration        ueTaTimerConfigInfo;
   UeDrxConfiguration            ueDrxConfigInfo;
   UeMeasurementGapConfig        ueMeasurementGapConfigInfo;
   CbSubsetRestrictionConfig     cbSubsetRestrictionConfigInfo;
   SrsUeConfiguration            srsUeConfigInfo;
   SrConfiguration               srConfigInfo;
   UePuschConfiguration          uePuschConfigInfo;
   UePdschConfiguration          uePdschConfigInfo;
   UEAsRelInfo   		 ueRel;  /*!< Access Stratum UE release info */
   uint8_t                       numberOfLcs; /*!< Number of LC
                                               * configuration present */
   uint8_t    			 spare1[3]; /*!< Added spare byte for 4byte alignment */
   LcConfigInfo  		 lcInfo[1]; /*!<DL and UL LC Config parameters */

}MacUeConfigReq;

#define MAC_MAX_LC_ID 10
#define MAC_MAX_LCG_ID 4

typedef struct failedLcList
{
   uint8_t lcConfigType;      /*!< LC config type for UE Reconfig only;
                                   Use 0 for MAC_UEConfig.
                                   0-Reserve, 1-Create, 2-Modify, 3-Delete */
   uint8_t lchId;
   uint8_t spare[2];              /*!< Added for 4byte alignment */
}FailedLcList;

/**
  @brief MAC UE CONFIG RSP */
typedef struct macUeConfigRsp
{
   UeIdentity ueInfo;   /* Contains UE Identity */
   uint16_t status;     /*!< Status of the configuration request
                         * sent from higher layer.
                         * Value: 0: success, 1: failure */
   uint8_t  spare[2];     /*!< Added spare byte for 4byte alignment */
   uint8_t  numberOfFailedLcs; /*!< number of entities */
   uint8_t  spare1[3];      /*!< Added spare byte for 4byte alignment */
   FailedLcList  lc[1];  /*!< List of LC identities */
}MacUeConfigRsp;

#define MAC_TRANSMISSION_MODE_RECONFIGURATION    0x00000001
#define MAC_APERIODIC_DL_CQI_RECONFIGURATION     0x00000002
#define MAC_UL_HARQ_RECONFIGURATION              0x00000004
#define MAC_QoS_RECONFIGURATION                  0x00000008
#define MAC_TA_TIMER_RECONFIGURATION             0x00000010
#define MAC_UL_POWER_RECONFIGURATION             0x00000020
#define MAC_ACK_NACK_REPETITION_RECONFIGURATION  0x00000040
#define MAC_MEASUREMENT_GAP_RECONFIGURATION      0x00000080
#define MAC_CODEBOOK_SUBSET_RECONFIGURATION      0x00000100
#define MAC_UE_CATEGORY_RECONFIGURATION          0x00000200
#define MAC_PERIODIC_CQI_RECONFIGURATION         0x00000400
#define MAC_SRS_RECONFIGURATION                  0x00000800
#define MAC_SR_RECONFIGURATION                   0x00001000
#define MAC_UE_DRX_RECONFIGURATION               0x00002000
#define MAC_PDSCH_RECONFIGURATION                0x00004000
#define MAC_PUSCH_RECONFIGURATION                0x00008000
#define MAC_UEIDCHANGE_RECONFIGURATION           0x00010000

/**
  @brief MAC UE RECONFIG REQ */
typedef struct macUeReconfigReq
{
   uint16_t ueIndex;           /*!< UE Index Value: 0 to max UE per Cell */
   uint16_t oldCRnti;          /*!< old CRNTI */
   uint8_t  ueCategory;        /*!< UE Category
                                * Value: 1 to 8
                                * 1 implies UE Category-1
                                * Refer: TS 36.306 */
   uint8_t  spare;             /*!< Added spare byte for 4byte alignment */
   uint16_t newCRnti;          /*!< new CRNTI */
   uint32_t bitMask;           /*!< Indicates the reconfiguration elements
                                 present in this message */
   TransmissionModeConfig        transmissionModeConfigInfo;
   DlCqiConfig                   dlCqiConfigInfo;
   UlHarqConfiguration           ulHarqConfigInfo;
   UeUlPowerControlConfig        ueUlPowerControlConfigInfo;
   UeQosConfiguration            ueQosConfigInfo;
   UeTaTimerConfiguration        ueTaTimerConfigInfo;
   UeDrxConfiguration            ueDrxConfigInfo;
   UeMeasurementGapConfig        ueMeasurementGapConfigInfo;
   CbSubsetRestrictionConfig     cbSubsetRestrictionConfigInfo;
   SrsUeConfiguration            srsUeConfigInfo;
   SrConfiguration               srConfigInfo;
   UePuschConfiguration          uePuschConfigInfo;
   UePdschConfiguration          uePdschConfigInfo;
   Bool                          ttiBundlingEnable;  /*!< TTI bundling
                                                      * present flag
                                                      * Value: 1- Present
                                                      * 0- Absent */
   uint8_t       numberOfLcs;   /*!< Added spare byte for 4byte alignment */
   uint8_t       spare1[2];     /*!< Added spare byte for 4byte alignment */
   LcConfigInfo  LcInfo[1];        /*!< DL and UL LC Config parameters */
}MacUeReconfigReq;

/**
  @brief MAC UE RECONFIG RSP */
typedef struct macUeReconfigRsp
{
   UeIdentity ueInfo;/* Contains UE Identity */
   uint16_t status;  /*!< Status of the configuration request
                      * sent from higher layer.
                      * Value: 0: success, 1: failure */
   uint8_t spare[2];      /*!< Added spare byte for 4byte alignment */
   uint8_t  numberOfFailedLcs; /*!< number of entities */
   uint8_t spare1[3];      /*!< Added spare byte for 4byte alignment */
   FailedLcList  lc[MAC_MAX_LC_ID];  /*!< List of LC identities */
}MacUeReconfigRsp;

/**
  @brief MAC UE DELETE REQ */
typedef struct macUeDeleteReq
{
   UeIdentity ueInfo;                      /* Contains UE Identity */
}MacUeDeleteReq;

/**
  @brief MAC UE DELETE RSP */
typedef struct macUeDeleteRsp
{
   UeIdentity ueInfo;     /* Contains UE Identity */
   uint16_t   status;     /*!< Status of the Delete request
                           * sent from higher layer.
                           * Value: 0: success, 1: failure */
   uint16_t   spare;      /*!< Added spare byte for
                           * 4byte alignment */
}MacUeDeleteRsp;

/**
 * SiModificationPeriod */
typedef enum siModificationPeriod
{
   SI_MODIFICATION_PERD_64   = 64,    /**< modification period 64 RF */
   SI_MODIFICATION_PERD_128  = 128,   /**< modification period 128 RF */
   SI_MODIFICATION_PERD_256  = 256,   /**< modification period 256 RF */
   SI_MODIFICATION_PERD_512  = 512,   /**< modification period 512 RF */
   SI_MODIFICATION_PERD_1024 = 1024  /**< modification period 1024 RF */
}SiModificationPeriod;

/**
 * SiBroadCastChangeTime
 */
typedef enum siBroadCastChangeTime
{
   SI_CHANGE_NORMAL = 1, /* Broadcast SI in next mod period */
   SI_CHANGE_IMMEDIATE,  /* Broadcast SI in next repetition period */
} SiBroadCastChangeTime;

/**
 * @brief SI Window Length
 */
typedef enum siWindowLength
{
   SI_WINDOW_LENGTH_1 = 1,
   SI_WINDOW_LENGTH_2 = 2,
   SI_WINDOW_LENGTH_5 = 5,
   SI_WINDOW_LENGTH_10 = 10,
   SI_WINDOW_LENGTH_15 = 15,
   SI_WINDOW_LENGTH_20 = 20,
   SI_WINDOW_LENGTH_40 = 40
}SiWindowLength;

/**
 * SI Periodicity */
typedef enum siPeriodicity
{
   SI_PERD_8   = 8,    /**< SI Periodicity 8 RF */
   SI_PERD_16  = 16,   /**< SI Periodicity 16 RF */
   SI_PERD_32  = 32,   /**< SI Periodicity 32 RF */
   SI_PERD_64  = 64,   /**< SI Periodicity 64 RF */
   SI_PERD_128 = 128,  /**< SI Periodicity 128 RF */
   SI_PERD_256 = 256,  /**< SI Periodicity 256 RF */
   SI_PERD_512 = 512   /**< SI Periodicity 512 RF */
}SiPeriodicity;

/**
  @brief SI Pdu Info */
typedef struct siPduInfo
{
   uint16_t pduLength;     /*!< Length of the SI PDU */
   uint16_t  	  spare;         /*!< Added for 4-byte alignment */
   uint8_t  spare1[3];               /*!< To carry SI PDU */
   uint8_t  siPdu[1];      /*!< To carry SI PDU */
}SiPduInfo;

/**
  @brief SI Configuration */
typedef struct siConfiguration
{
   uint16_t       siId;          /*!< System Information identity number */
   uint16_t  	  spare;         /*!< Added for 4-byte alignment */
   
   uint8_t        numSegments;   /*!< Number of segments in the SI */
   uint8_t        spare1[3];        /*!< Added for 4 byte Alignment */
   SiPeriodicity  siPeriodicity; /*!< SI Periodicity */
   SiPduInfo      siPduList[1];     /*!< List of segments for the SI */
}SiConfiguration;

#define MAC_MIB_PDU   0x01
#define MAC_SIB1_PDU  0x02
#define MAC_SI_PDU    0x04
#define MAC_SI_PWS    0x08
/**
  @brief MAC Broadcast Msg Req */
typedef struct macBroadcastMsgReq
{
   SiWindowLength  siWindowLen;      /*!< SI window length */
   SiModificationPeriod modfnPeriod; /*!< Modification Periodicity */
   SiBroadCastChangeTime siBrdcstChngTim; /*!< To indicate whether SI change
                                            should happen immediately or
                                            after modification period */
   uint16_t  siCfgBitMask;           /*!< Bit mask to indicate
                                       the presence of
                                       specific broadcast PDUs.
                                       Bit number 1: MIB PDU
                                       Bit number 2: SIB1 PDU
                                       Bit number 3: SI PDU
                                       Bit number 4: PWS SI PDU */
   uint16_t  mibPduLen;             /*!< Length of the MIB PDU */
   uint16_t  sib1PduLen;            /*!< Length of the SIB1 PDU */
   uint16_t  spare;		    /*!< Added for 4-byte alignment */
   uint8_t   siRetxCnt;             /*!< SI Retransmission Count */
   uint8_t   numSiPdus;             /*!< Number of SI PDUs being
                                      configured. Value: 0..11 */
   uint8_t   mibPdu[1];                /*!< MIB broadcast PDU */
   uint8_t   sib1Pdu[1];               /*!< SIB1 broadcast PDU */
   SiConfiguration siConfigInfo[1];
}MacBroadcastMsgReq;

/**
  @brief MAC Broadcast Msg Rsp */
typedef struct macBroadcastMsgRsp
{
   uint16_t status; /*!< Configuration status.
                     * Value: 0 - Success, 1 - Failure */
   uint16_t spare;  /*!< Added spare byte for 4byte alignment */
}MacBroadcastMsgRsp;

/**************
 ** PHY APIs **
 *************/

/**
  @brief PHY Bandwidth Configuration */
typedef struct phyBandwidthConfig
{
   Bandwidth dlBandwidth;  /*!< Downlink channel bandwidth in resource blocks.
                           * Value: 6,15, 25, 50, 75, 100 */
   Bandwidth ulBandwidth;  /*!< Uplink channel bandwidth in resource blocks.
                           * Value: 6,15, 25, 50, 75, 100 */
   uint16_t frequencyBand; /*!< Bandwidth in which the cell is operating.
                           * Value: FDD: 0..7; TDD: 33 .. 40 */
   uint16_t dlEarfcn;      /*!< Downlink EARFCN */
   uint16_t ulEarfcn;      /*!< Uplink EARFCN */
   uint16_t spare;         /*!< Added spare byte for 4byte alignment */
}PhyBandwidthConfig;

/**
  @brief Transmission Scheme Configuration */
typedef struct transmissionSchemeConfig
{
   DuplexMode duplexMode;        /*!< Type of duplexing mode.
                                  * Value : 1 : FDD, 2 : TDD */
   uint16_t subCarrierSpacing;   /*!< Subcarrier spacing used
                                  * Value: 0:15KHZ, 1: 7DOT5KHZ */
   uint16_t cyclicPrefix;        /*!< Cyclic prefix type used
                                  * for DL and UL.
                                  * Value: 0 : CP_NORMAL,
                                  * 1 : CP_EXTENDED */
}TransmissionSchemeConfig;

/**
  @brief Antenna Configuration */
typedef struct antennaConfiguration
{
   uint16_t txAntennaPorts;      /*!< Number of antenna
                                  * ports present for DL.
                                  * Value: 1, 2, 4 */
   uint16_t spare1;              /*!< Added spare byte for
                                  * 4byte alignment */
}AntennaConfiguration;

/**
  @brief Contains Prach configuration */
typedef struct prachConfiguration
{
   uint16_t rootSeqIndex;    /*!< PRACH Root sequence index. Value: 0..837 */
   uint16_t configIndex;     /*!< Provides information about the location and
                               format of the PRACH. Value: 0..63 */
   uint16_t zeroCorrZoneConfig;   /*!< Equivalent to Ncs, see [8] section 5.7.2.
                                    Values: TDD: 0..6, FDD: 0..15 */
   uint16_t highSpeedFlag;        /*!< Indicates if unrestricted, or restricted,
                                    set of preambles is used.
                                    Value: 0 : HS_UNRESTRICTED_SET,
                                    1 : HS_RESTRICTED_SET */
   uint16_t freqencyOffset;       /*!< The first physical resource
                                   * block available for PRACH.
                                   * Value: 0..(UL_channel_bandwidth - 6) */
   uint16_t spare;                /*!< Added spare byte for 4byte
                                   * alignment */
}PrachConfiguration;

/**
  @brief PDSCH Configuration */
typedef struct phyPdschConfiguration
{
   uint16_t pB;    /*!< Refers to downlink power allocation.
                              Value: 0..3 */
   uint16_t spare; /*!< Added spare byte for 4byte alignment */
}PhyPdschConfiguration;

/**
  @brief UL Reference Signal Configuration */
typedef struct ulReferenceSignalConfiguration
{
   Bool     groupHoppingEnable;   /*!< To enable group hopping.
                                   * Value: 0 : DISABLE, 1 : ENABLE */
   Bool     sequnceHoppingEnable; /*!< To enable sequence hopping.
                                   * Value: 0 : DISABLE, 1 : ENABLE */
   uint16_t groupAssignment;      /*!< The sequence shift pattern used
                                   * if group hopping is enabled.
                                   * Values: 0..29 */
   uint16_t cyclicShift;          /*!< Specifies the cyclic shift for
                                   * the reference signal used
                                   * in the cell.
                                   * Value: 0..7 */
   uint16_t spare;                /*!< Added for 4 byte alignment */
}UlReferenceSignalConfiguration;

/**
  @brief PUSCH Configuration */
typedef struct phyPuschConfiguration
{
   uint16_t hoppingMode;        /*!< If hopping is enabled indicates
                                 * the type of hopping used.
                                 * Value: 0: HM_INTER_SF,
                                 * 1: HM_INTRA_INTER_SF */
   uint16_t hoppingOffset;      /*!< The offset used if hopping
                                 * is enabled.
                                 * Value: 0..98 */
   uint16_t numberOfSubbands;   /*!< The number of sub-bands
                                 * used fohopping.
                                 * Value: 1..4 */
   Bool     enable64Qam;        /*!< To enable 64QAM in UL.
                                 * Value: 0 : DISABLE, 1 : ENABLE */
   uint8_t  spare;              /*!< Added for 4 byte alignment */
   UlReferenceSignalConfiguration ulRefSigCfgInfo;
}PhyPuschConfiguration;

/**
  @brief PHY PHICH Configuration */
typedef struct phyPhichConfiguration
{
   PhichDuration phichDuration; /*!< The PHICH duration for MBSFN
                                  and non-MBSFN sub-frames.
                                  Value: 0: PHICH_D_NORMAL,
                                  1: PHICH_D_EXTENDED */
   uint16_t phichPowerOffset;   /*!< The power per antenna of the PHICH
                                 * with respect to the reference signal.
                                 * Value: 0..10000 [Represents
                                 * -6dB to 4dB in steps 0.001dB] */
   uint16_t  spare;              /*!< Added for 4 byte alignment */								 
   PhichRE  phichResource;      /*!< The number of resource element
                                 * groups used for PHICH.
                                 * Value: 0: PHICH_R_ONE_SIXTH,
                                 * 1: PHICH_R_HALF,
                                 * 2: PHICH_R_ONE,
                                 * 3: PHICH_R_TWO */
}PhyPhichConfiguration;

typedef enum pucchCyclicShift {
   PUCCH_DELTASHIFT1 = 1,
   PUCCH_DELTASHIFT2,
   PUCCH_DELTASHIFT3
} PucchDeltaShift;

/**
  @brief PHY PUCCH Configuration */
typedef struct phyPucchConfiguration
{
   uint16_t nRB;                  /*!< Number of RBs available for use by
                                    PUCCH formats. Value: 0..98 */
   uint16_t nCS;                  /*!< The number of cyclic shifts
                                    used for PUCCH formats.  Value: 0..7 */
   uint16_t n1PucchAn;            /*!< PUCCH resource for transmission
                                    of ACK/NACK. Value: 0..2047 */
   uint16_t spare;
   PucchDeltaShift deltaPucchShift; /*!< The cyclic shift difference.
                                      Value: 1..3 */
}PhyPucchConfiguration;

/**
  @brief PHY SRS Configuration */
typedef struct phySrsConfiguration
{
   uint16_t bwConfig; /*!< The available SRS bandwidth of the cell.
                        Value: 0..7 */
   uint16_t sfConfig; /*!< The sub-frame configuration.
                        Needed if semi-static configuration is held in PHY.
                        Value: 0 - 15 */
   uint16_t anSimultTx; /*!< Indicates if SRS and ACK/NACK can be received
                          in the same subframe.  Needed if semi-static
                          configuration is held in PHY.
                          Value:
                          0: no simultaneous transmission,
                          1: simultaneous transmission */
   uint16_t spare;
}PhySrsConfiguration;

/**
  @brief PHY Sig Configuration */
typedef struct phySigConfiguration
{
   uint16_t priSyncSignal; /*!< The power of primary synchronization signal
                             with respect to the reference signal.
                             Value: 0..9999 represents
                             -6dB to 4dB in step 0.001dB */
   uint16_t secSyncSignal; /*!< The power of secondary synchronization signal
                             with respect to the reference signal.
                             Value: 0..9999 represents
                             -6dB to 4dB in step 0.001dB */
   uint16_t refSignalPower; /*!< Reference Signal Power level */
   uint16_t spare;
}PhySigConfiguration;

/**
  @brief PHY CELL CONFIG REQ */
typedef struct phyCellConfigReq
{
   uint16_t pci;               /*!< Physical Cell Identity */
   uint16_t pcfichPowerOffset; /*!< The power per antenna of
                                * the PCFICH with
                                * respect to the reference signal.
                                * Value: 0..10000,
                                * represents -6dB to 4dB
                                * in steps 0.001dB */
   PhyBandwidthConfig bwConfigInfo;
   TransmissionSchemeConfig txSchemeConfigInfo;
   AntennaConfiguration antennaConfigInfo;
   PrachConfiguration prachConfigInfo;
   PhyPdschConfiguration pdschConfigInfo;
   PhyPuschConfiguration puschConfigInfo;
   PhyPhichConfiguration phichConfigInfo;
   PhyPucchConfiguration pucchConfigInfo;
   PhySrsConfiguration srsConfigInfo;
   PhySigConfiguration sigConfigInfo;
   uint16_t spare;                /*!< Added spare byte for
                                   * 4byte alignment */
}PhyCellConfigReq;


/**
  @brief PHY_CELL_CONFIG_RSP */
typedef struct phyCellConfigRsp
{
   uint16_t status; /*!< Status of the configuration
                     * request sent from higher layer.
                     * Value: 0: success, 1: failure */
   uint16_t spare;  /*!< Added spare byte for 4byte alignment */
}PhyCellConfigRsp;

/**
  @brief PHY Cell Delete Req */
typedef struct phyCellDeleteReq
{
   uint16_t   spare[2];                       /*!< Added spare byte for
                                            * 4byte alignment */
}PhyCellDeleteReq;

/**
  @brief PHY Cell Delete Rsp */
typedef struct phyCellDeleteRsp
{
   uint16_t status;                /*!< Status of the configuration
                                    * request sent from higher layer.
                                    * Value: 0: success, 1: failure */
   uint16_t spare;                 /*!< Added spare byte for 4byte alignment */
}PhyCellDeleteRsp;

/**
  @brief L3 TTI Indication*/
typedef struct l3TtiInd
{
   TimingInfo timingInfo;        /*!< Needed only for PCCH */
}L3TtiInd;

/**************
 ** RLC APIs **
 *************/

typedef enum rlcCommonEntityType
{
   RLC_ENTITY_DL_BCCH = 1,
   RLC_ENTITY_DL_CCCH,
   RLC_ENTITY_UL_CCCH,
   RLC_ENTITY_DL_PCCH
}RlcCommonEntityType;

typedef struct rlcCommonChannelConfigReq
{
   uint8_t    numberOfEntities;     /*!< Number of entities to be configured
                                      during a new cell configuration. */
   uint8_t    spare[3];
   RlcCommonEntityType entityType[1]; /*!< List of entity configurations. */
} RlcCmnChnlConfigReq;

/**
 * @brief Common Channel Entity Confirmation
 */
typedef struct rlcCommonChannelFailedEntity
{
   RlcCommonEntityType entityType; /*!< Common channel entity type */
} RlcComnChnlFailedEntity;

typedef struct rlcCommonChannelConfigRsp
{
   uint8_t    configStatus;      /*!< Configuration status */
   uint8_t    numberOfEntities;  /*!< Number of entities for which status is
                                   being shared */
   uint8_t    spare[2];
   RlcComnChnlFailedEntity cfgStatus[1]; /*!< List of failed entities */
} RlcCmnChnlConfigRsp;

typedef RlcCmnChnlConfigReq RlcCmnChnlDeleteReq;
typedef RlcCmnChnlConfigRsp RlcCmnChnlDeleteRsp;

/**
  @brief Acknowledged Configuration */
typedef struct ackModeConfiguration
{
   uint16_t pollRetransmitTimer;
   int16_t  pollPdu;  /*!< Value: 4, 8, 16, 32, 64, 128, 256, -1 */
   uint8_t  maxRetransmissions;
   uint8_t  spare1;              /*!< Added for 4byte alignment */
   int16_t  pollByte; /*!< Value: 25, 50, 75, 100, 125, 250, 375,
                       * 500, 750, 1000, 1250, 1500, 2000, 3000, -1 */
   uint8_t  reorderingTimer;     /*!< Value: 0, 5, 10, 15, 20, 25, 30,
                                  * 35, 40, 45, 50, 55, 60, 65, 70, 75,
                                  * 80, 85, 90, 95, 100, 110, 120, 130,
                                  * 140, 150, 160, 170, 180, 190, 200 */
   uint8_t  spare2;              /*!< Added for 4byte alignment */
   uint16_t statusProhibitTimer;
}AckModeConfiguration;

/**
  @brief UnAcknowledged Configuration */
typedef struct unAckModeConfiguration
{
   uint8_t dlSN;            /*!< Downlink sequence number. */
   uint8_t ulSN;            /*!< Uplink sequence number. */
   uint8_t reorderingTimer; /*!< Timer value for reordering packets.*/
   uint8_t spare;           /*!< Added for 4 byte alignment */
}UnAckModeConfiguration;

typedef enum rlcEntityCfgType
{
   RLC_RB_ADD = 1,
   RLC_RB_MODIFY,
   RLC_RB_DELETE,
   RLC_RB_RESET
}RlcEntityCfgType;

/**
  @brief Entity Configuration */
typedef struct rlcEntityConfiguration
{
   RlcEntityCfgType       configType;
   RbIdentity             rbInfo;     /*!< Radio Bearer identity */
   uint8_t                qci;        /*!< Qos Class Identifier
                                       * Value: 0..255 */
   uint8_t                entityMode; /*!< RLC Entity mode of operation
                                       * Value: 1 - TM, 2 - UM, 3 - AM */
   uint8_t                spare[2];   /*Added for 4 byte alignment */
   EntityDirection        direction;  /*!< 1- UL, 2- DL, 3- Both */
   UnAckModeConfiguration unackModeConfigInfo;
   AckModeConfiguration   ackModeConfigInfo;
}RlcEntityConfiguration;

/**
  @brief RLC Config Req */
typedef struct rlcUeConfigReq
{
   UeIdentity ueInfo;               /*!< Contains UE Identity */
   uint8_t    numberOfEntites;      /*!< Number of entities to be configured
                                     * during a new cell configuration. */
   uint8_t    spare[3];             /*!< Added for 4byte alignment */
   RlcEntityConfiguration entityInfo[1]; /*!< List of entity configurations.
                                        * The size can vary from 1 to
                                        * Number of entities'. */
}RlcUeConfigReq;

/**
  @brief Entity Confirmation */
typedef struct rlcEntityConfirmation
{
   RbIdentity       rbInfo;     /*!< Radio Bearer identity */
   RlcEntityCfgType configType; /*!< Configuration Type */
}RlcEntityConfirmation;

/**
  @brief RLC Config Rsp */
typedef struct rlcUeConfigRsp
{
   UeIdentity ueInfo;              /*!< Contains UE Identity */
   uint8_t    status;              /*!< Overall status of configuration */
   uint8_t    numberOfEntities;    /*!< number of entities */
   uint8_t    spare[2];            /*!< Added for 4byte alignment */
   RlcEntityConfirmation entityInfo[1]; /*!< List of confirmations.
                                        The size can vary from 1 to
                                        number of entities'. */
}RlcUeConfigRsp;

/* RLC UE reconfiguration type definition */
#define RLC_UERECONFIG_RB    0x0001
#define RLC_UERECONFIG_UEID  0x0002

/**
  @brief RLC UE Reconfiguration Request */
typedef struct rlcUeReconfigReq
{
   UeIdentity ueInfo;               /*!< Contains UE Identity */
   uint16_t   recfgBitMask;         /*!< Bit mask to identify the
                                      reconfiguration elements */
   uint16_t   newCrnti;             /*!< New CRNTI */
   uint8_t    numberOfEntites;      /*!< Number of entities to be configured
                                     * during a new cell configuration. */
   uint8_t    spare[3];             /*!< Added for 4byte alignment */
   RlcEntityConfiguration entityInfo[1]; /*!< List of entity configurations.
                                        * The size can vary from 1 to
                                        * ‘Number of entities'. */
}RlcUeReconfigReq;

typedef RlcUeConfigRsp RlcUeReconfigRsp;

/**
  @brief RLC UE Delete Request */
typedef struct rlcUeDeleteReq
{
   UeIdentity ueInfo;               /*!< Contains UE Identity */
}RlcUeDeleteReq;

/**
  @brief RLC UE Delete Response */
typedef struct rlcUeDeleteRsp
{
   UeIdentity ueInfo;              /*!< Contains UE Identity */
   uint8_t    status;              /*!< Status of UE delete request */
}RlcUeDeleteRsp;

/**
 * @brief To send UL CCCH message to RRC
 */
typedef struct rrcCcchMsgInd
{
   UeIdentity   ueInfo;      /*!< UE Identity */
   uint16_t     msgLen;      /*!< Message length */
   uint8_t      spare[1];
   uint8_t      ccchMsg[1];     /*!< CCCH message */
} RrcCcchMsgInd;

/**
 * @brief To send DL CCCH message
 */
typedef struct rlcCcchMsgReq
{
   UeIdentity   ueInfo;      /*!< UE Identity */
   uint16_t     msgLen;      /*!< Message length */
   uint8_t      spare[1];
   uint8_t      ccchMsg[1];     /*!< CCCH message */
} RlcCcchMsgReq;

/**
 * @brief To send DL CCCH Reject message
 */
typedef struct rlcCcchUeRejReq
{
   UeIdentity   ueInfo;      /*!< UE Identity */
   uint16_t     msgLen;      /*!< Message length */
   uint8_t      spare[1];
   uint8_t      ccchMsg[1];     /*!< CCCH message */
} RlcCcchUeRejReq;

/**
 * @brief To send DL PCCH message
 */
typedef struct rlcPcchMsgReq
{
   TimingInfo   timingInfo;  /*!< Time at which paging should be broadcasted */
   uint16_t     msgLen;      /*!< Message length */
   uint16_t     numberOfSfn; /*!< Duration for which Paging message
                              * has to be broadcasted. During SI
                              * modification/broadcast of
                              * warning messages,
                              * this IE shall have value
                              * greater than 1
                              * Range: 1 to 8191 */
   uint8_t      ovrWrtMsg;   /*!< Indication to overwrite the Paging
                               message at specific PF,PO */
   uint8_t      spare[3];    /*!< Added for 4byte alignment */
   uint8_t      pcchMsg[1];  /*!< PCCH message */
} RlcPcchMsgReq;

typedef enum l2UeRelCause
{
   L2_UEREL_CAUSE_MAXRETX = 1,
   L2_UEREL_CAUSE_ULSYNC_LOSS,
   L2_UEREL_CAUSE_UEINACTIVITY
} L2UeRelCause;

/**
 * @brief To send UE release indication to L3
 */
typedef struct l2UeRelInd
{
   UeIdentity   ueInfo;      /*!< UE Identity */
   L2UeRelCause cause;       /*!< Cause for UE Release */
} L2UeRelInd;

#endif /* __L3_L2L_H__ */

/**********************************************************************

         End of file:

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
------------ -------- -------  ----------------------------------------
     1.0        ---   radisys  1. initial release.
     1.1              radisys  1. Added L3_Tti.REQ, Phy_CellDelete.REQ
     1.2              radisys  1. Edited RLC Config related Messages
     1.3              radisys  1. Edited MAC_CellConfig among others
     1.4              radisys  1. Edited UE Release Info, MAC_CellStart
     1.5              radisys  1. Edited MAC_UEReconfig for LC changes among others
     1.6              radisys  1. Added UE Connection Reject   
     1.7              radisys  1. Spare Bit Alignment
     1.8              radisys  1. Data type of DefaultPagingCycle, Spare bits 
     1.9              radisys  1. RefSigPower as Int16
     1.10             radisys  1. Comment on sf level granularity, cosmetic changes
     1.11             radisys  1. RLC PCCH Message updation.
                               2. MAC and RLC UE Reconfiguration for Reestablishment case.
     1.12             radisys  1. UE release indication API definition to indicate RLF.
     1.13             radisys  1. MAC UE RECONIG - spare bit reduced.
**********************************************************************/

