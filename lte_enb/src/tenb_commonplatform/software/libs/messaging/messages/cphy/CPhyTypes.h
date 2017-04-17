///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyTypes.h 28271 2010-07-16 10:11:20Z mmcternan $
//
// CPHY message types.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

/** \file
 * Types commonly used in the CPhy interface.
 * This file contains a number of types and defines that are used consistently
 * in the \ref CPhy "CPhy" interface.  A small set of helper functions are also defined
 * to pretty print values and types for logging and debug.
 *
 * \ingroup CPhy
 */

#ifndef __CPhyTypes_h_
#define __CPhyTypes_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

#include <mobnet/MobnetTypes.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Message Constants
///////////////////////////////////////////////////////////////////////////////

/** Size of a BCH transport block in bytes.
 * A BCH TrCH is 246 bits, which rounds up to 31 bytes.
 */
#define BCH_TRCH_BLOCK_SIZE_BYTES 31

/*Pradeep start*/
#define MAX_NUM_BCH_TRANSPORT_BLOCKS 32
/*Pradeep stop*/

/** Size of a PCH transport block in bytes.
 * A PCH TrCH is 240 bits, which rounds is exactly 30 bytes.
 */
#define PCH_TRCH_BLOCK_SIZE_BYTES 30

/** Size of a GSM BCCH block in bytes.
 * A GSM BCCH block is 184 bits, which is exactly 23 bytes.
 */
#define BCCH_GSM_BLOCK_SIZE_BYTES 23

/*Pradeep start*/
/** Maximum number of GSM BCCH blocks.
 */
#define MAX_BCCH_GSM_BLOCKS 8
/*Pradeep end*/

/** Invalid value for a bsic_t.
 */
#define INVALID_BSIC 0xff

/** Maximum number of ARFCNs which can be processed by a single RSSI scan.
 */
#define MAX_REM_GSM_RSSI_SCAN_FREQS  374

/** Maximum number of concurrent compressed mode transmission gap pattern sequences.
 * Defines the maximum number of concurrent compressed mode transmission gap
 * pattern sequences supported by L1 compressed mode gap pattern generator.
 */
#define NUM_MAX_CM_TGP_SEQUENCES  6

/** Maximum number of Transport Formats in a TFS.
 */
#define MAX_L1_TF   8

/** Maximum number of Transport Channels in a Cctrch.
 */
// Based on this, "MAX_L1_TRCH_DEFINED_IN_RRC" is defined as 6 in RRCConnection.h.
#define MAX_L1_TRCH  6 // If value is changed here, change in  RRCConnection.h also

/** Maximum number of Transport Format Combination Identifiers for a Cctrch.
 */
#define MAX_L1_TFCI  64


/** Maximum number of Paging Indicators per frame.
 */
#define MAX_PI_PER_FRAME  144

/** Maximum number of Hybrid-ARQ processes available for HSDPA.
 * This defines the maximum number of Hybrid-ARQ processes available for HSDPA.
 */
#define NUM_MAX_HSDPA_HARQ_PROCS 8

/** Maximum number of GSM ARFCN.
 * This is used by Rem-app to send ARFCNs to Cphy for doing COSC.
 */
#define MAX_GSM_FREQS_FOR_NLM_COSC 3
/** Maximum number of MCC digits.
 */
#define MAX_MCC_DIGITS  3

/** Maximum number of MCC digits.
 */
#define MAX_MNC_DIGITS  3
///////////////////////////////////////////////////////////////////////////////
// Message Structures
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

/** Generic Layer 1 status codes.
 * These maybe returned by functions or in messages to give different error
 * causes.  The intended purpose of differentiating errors to to aid debug,
 * rather than change program behaviour based on failure modes.
 */
typedef enum
{
    L1_SOK = 0,             /**< The action completed successfully. */

    L1_SFAILED,             /**< Something failed. */
    L1_SNOT_IMPLEMENTED,    /**< The functionality is not yet supported. */
    L1_SNOT_SUPPORTED,      /**< The functionality is not supported. */
    L1_SNOT_READY,          /**< Unspecified error. */
    L1_SBUSY,               /**< Busy processing a prior request. */
    L1_SBAD_BUFFER,         /**< A passed buffer is invalid or unacceptable. */
    L1_SBAD_PARAM,          /**< A passed parameter is invalid or unacceptable. */
    L1_SBAD_STATE,          /**< The current state does not support the requested operation. */
    L1_SNO_MEM,             /**< Out of memory error. */
    L1_SNOT_FOUND,          /**< Some required lookup failed. */

    NUM_L1STATUS
}
l1status_t;


/** Layer 1 operating modes.
 * This gives the various operating modes that can be controlled via the
 * #CphyModeChangeReq message.  This does not include the pre-initialised mode
 * which cannot be explicitly entered and can only be left via the
 * #CphyHwConfigReq.
 */
typedef enum
{
    L1_MODE_NULL,       /**< NULL mode, from which other modes can be entered. */
    L1_MODE_NODEB,      /**< Node B operational mode. */
    L1_MODE_REM_WCDMA,  /**< REM WCDMA operational mode. */
    L1_MODE_REM_GSM,    /**< REM GSM operational mode. */

    NUM_L1_MODE
}
l1mode_t;

/** Layer 1 operating modes.
 */
typedef enum
{
    GSM_MAP_PLMN_SEL,            /**< GSM MAP PLMN. */
    GSM_MAP_ANSI_41_PLMN_SEL,    /**< GSM MAP and ANSI 41 PLMN. */
    NUM_PLMN_TYPE
}
plmnType_t;


/** Type for a UMTS UARFCN.
 */
typedef uint16_t uarfcn_t;

/** Enumerated type for UMTS radio bands.
 */
typedef UmtsBandId uband_t;

/** Type for a GSM ARFCN.
 */
typedef uint16_t arfcn_t;

/** Enumerated type for GSM radio bands.
 * \note The values of these enums are used by the radio calibration station.
 *       Therefore, any changes to these value must also be reflected in the
 *       radio calibration station and related documents.
 */
typedef enum
{
    BAND_INVALID = 0,
    BAND_GSM450,
    BAND_GSM480,
    BAND_GSM850,
    BAND_GSM900,        /**< GSM 900 + E-GSM900. */
    BAND_DCS1800,
    BAND_PCS1900,
    BAND_RGSM900,

    BAND_FIRST = BAND_GSM450,
    BAND_LAST  = BAND_RGSM900,
    NUM_BAND   = BAND_LAST+1 - BAND_FIRST,
}
band_t;

/** Type for a GSM Base Station Identity Code.
 */
typedef uint8_t   bsic_t;

/** Type for a Primary Scrambling Code.
 */
typedef uint32_t  upsc_t;

/** Type for a Primary Scrambling Code Count.
 */
typedef uint32_t  upsccnt_t;

/** Activation time representation.
 */
typedef struct
{
    bool     now;       /**< If TRUE, immediate, otherwise at SFN. */
    uint16_t sfn;       /**< System Frame Number at which to start. */
}
l1_activation_time_t;

/** PLMN ID 
 */
typedef struct
{
    uint8_t  mcc[MAX_MCC_DIGITS];       /**< If TRUE, immediate, otherwise at SFN. */
    uint8_t  numMncDigits;              /**< If TRUE, immediate, otherwise at SFN. */
    uint8_t  mnc[MAX_MCC_DIGITS];       /**< If TRUE, immediate, otherwise at SFN. */
}
plmnId_t;

/** Enumeration of possible Ue states; PhyNodeBCctrchRemoveReq may
 *  result in a change to CELL PCH as well as CELL IDLE.
 */
typedef enum
{
    ue_state_cell_idle,
    ue_state_cell_pch
}
ue_state_t;

/** Enumeration of possible WCDMA coding schemes.
 */
typedef enum
{
    CS_NONE, /**< Not a legal option. */
    CS_C2,   /**< 1/2 rate convolutional. */
    CS_C3,   /**< 1/3 rate convolutional. */
    CS_T3,   /**< 1/3 rate turbo. */
}
coding_scheme_t;


/** Enumeration of possible WCDMA CRC lengths.
 */
typedef enum
{
    CRC_0,    /**< Zero length CRC. */
    CRC_8,    /**< 8-bit CRC. */
    CRC_12,   /**< 12-bit CRC. */
    CRC_16,   /**< 16-bit CRC. */
    CRC_24    /**< 24-bit CRC. */
}
crc_length_t;


/** Enumeration of supported WCDMA spreading factors.
 */
typedef enum
{
    SF_256,                     /**< Spread by 256. */
    SF_128,                     /**< Spread by 128. */
    SF_64,                      /**< Spread by 64. */
    SF_32,                      /**< Spread by 32. */
    SF_16,                      /**< Spread by 16. */
    SF_8,                       /**< Spread by 8. */
    SF_4,                       /**< Spread by 4. */
    NUM_SUPPORTED_SF,           /**< Number of non-HSUPA spreading factors supported. */
    SF_4x2 = NUM_SUPPORTED_SF,  /**< HSUPA 4x2. */
    SF_2x2,                     /**< HSUPA 2x2. */
    SF_2x2_4x2,                 /**< HSUPA 2x2 4x2. */
    NUM_SUPPORTED_HSUPA_SF      /**< Total number of supported spreading factors. */
}
spreading_factor_t;


/** Enumeration of TTI lengths.
 */
typedef enum
{
    TTI_10,  /**< 10ms TTI. */
    TTI_20,  /**< 20ms TTI. */
    TTI_40,  /**< 40ms TTI. */
    TTI_2,   /**<  2ms TTI. */

    NUM_TTI_LENGTHS
}
tti_length_t;


/** Enumeration of H-ARQ buffer memory partitioning modes.
 */
typedef enum
{
    HM_PART_MODE_IMPLICIT,
    HM_PART_MODE_EXPLICIT,

    NUM_HM_PART_MODES
}
hsdpa_hm_part_mode_t;


/** Parameters giving a Transport Format(TF).
 */
typedef struct
{
    /* Dynamic parameters */
    uint8_t                 blockCount;     /**< Count of blocks. */
    uint16_t                blockSize;      /**< Block size in bits. */
}
l1_tf_param_t;


/** Parameters for a Transport Channel.
 * This gives an Id, each Transport Format and each Transport Format Set
 * defined for the TrCh.
 */
typedef struct
{
    /** Count of defined Transport Formats. */
    uint8_t                 nTf;

    /* Semi-static parameters. */
    uint8_t                 tti;            /**< TTI in blocks, 1, 2, 4. */
    coding_scheme_t         coding;         /**< Coding method. */
    crc_length_t            crc;            /**< CRC length. */
    uint8_t                 rmAttr;         /**< Rate matching attribute - 1. (1-256). */

    /** Parameters for each defined Transport Format. */
    l1_tf_param_t           tfs[MAX_L1_TF];

    /* Other parameters */
    uint8_t                 macHeaderBit;   /**< First bit in data blocks. */
}
l1_trch_param_t;


/** Parameters for a Coded Composite Transport Channel.
 * This gives the Transport Channels and TFCS that define a CCTRCH.
 */
typedef struct
{
    /** Count of TrChs. */
    uint8_t                 nTrch;

    /** Parameters for each TrCh. */
    l1_trch_param_t         trch[MAX_L1_TRCH];

    /** Count of TFCIs. */
    uint8_t                 nTfci;

    /** The Transport Format Combination Set.
     * Given a TFCI and TrCh, this gives the transport format index for that
     * TrCh which should be used.
     */
    uint8_t                 tfIdx[MAX_L1_TRCH][MAX_L1_TFCI];
}
l1_cctrch_param_t;


/** Outer loop power control parameters.
 */
typedef struct
{
    bool                    enable;                          /**< If TRUE, enable outer loop power control. */
    bool                    perTrchBler;                     /**< If TRUE, use individual BLER targets for each TrCH, otherwise use a single combined target. */
    uint16_t                blerToAchieve;                   /**< BLER target in 1/10ths of a percent. */
    uint16_t                trchBlerToAchieve[MAX_L1_TRCH];  /**< BLER target in 1/10ths of a percent for each transport channel */
    uint16_t                hsupaBler;                       /**< BLER target in 1/10ths of a percent for HSUPA */
}
l1_olpc_param_t;


/** Physical channel parameters related to HSDPA.
 */
typedef struct
{
    bool                    active;                               /**< If TRUE, HSDPA is active. */
    uint8_t                 ueCat;                                /**< HSDPA UE category. */
    uint8_t                 nHarqProcs;                           /**< Number of H-ARQ processes. */
    hsdpa_hm_part_mode_t    hmPartMode;                           /**< H-ARQ buffer memory partitioning mode. */
    uint32_t                harqBufLen[NUM_MAX_HSDPA_HARQ_PROCS]; /**< H-ARQ soft-buffer size for each H-ARQ processes if using #HM_PART_MODE_EXPLICIT. */
}
l1_hsdpa_param_t;

/** Physical channel parameters for the uplink related to HSUPA.
 */
typedef struct
{
    uint8_t                 ueCat;                /**< HSUPA UE category. */
    uint8_t                 trnsBlockTabId;       /**< Transport block table id. */
    uint8_t                 plNonMax;             /**< Puncturing limit to use if the number of code channels is less max allowed (PLnon-max) in 25ths. */
    spreading_factor_t      minSf;                /**< Minimum spreading factor for the E-DPDCHs. */
    bool                    rvFlag;               /**< Flag to indicate the use of redundancy version 0 only. */
}
l1_hsupa_ul_param_t;

/** Physical channel parameters for the downlink related to HSUPA.
 */
typedef struct
{
    uint8_t                 ehichSig;             /**< Signature Sequence to use for the E-HICH. */
    uint8_t                 ehichSpreadingCode;   /**< Spreading Code for the E-HICH. */
    uint16_t                ernti;                /**< Configured E-RNTI. */
}
l1_hsupa_dl_param_t;

/** Physical channel parameters related to HSUPA.
 */
typedef struct
{
    bool                    active;               /**< If TRUE, HSUPA is active. */
    tti_length_t            ttiLen;               /**< TTI length (#TTI_2 or #TTI_10). */
    l1_hsupa_ul_param_t     ul;                   /**< Uplink Parameters. */
    l1_hsupa_dl_param_t     dl;                   /**< Downlink Parameters. */
}
l1_hsupa_param_t;

/** Uplink Physical channel parameters.
 */
typedef struct
{
    upsc_t                  psc;                  /**< Uplink primary scrambling code. */
    spreading_factor_t      minSf;                /**< Minimum spreading factor. */
    uint8_t                 punctureLimit100;     /**< Puncturing limit * 100. */
    uint16_t                maxDpdchBitsPerFrame; /**< Max DPDCH bits per frame. */
}
l1_ulphy_param_t;


/** Downlink Physical channel parameters.
 */
typedef struct
{
    bool                    dtxPositionFixed;     /**< Whether DTX bits are fixed or flexible. */
    spreading_factor_t      sf;                   /**< Spreading factor. */
    uint8_t                 ovsf;                 /**< OVSF code number. */
    uint8_t                 slotFormat;           /**< Slot format. */

    /* DPCCH Parameters */
    uint16_t                tfciBitsPerSlot;
    uint16_t                tpcBitsPerSlot;
    uint16_t                pilotBitsPerSlot;

    /* DPDCH Parameters */
    uint16_t                dataBitsPerSlot;
    uint16_t                dataBitsPerFrame;
}
l1_dlphy_param_t;


/** Synchronisation procedures.
 */
typedef enum
{
    L1_SYNC_NONE,       /**< Disable sync procedure. */
    L1_SYNC_A,          /**< Sync A procedure. */
    L1_SYNC_B,          /**< Sync B procedure. */

    L1_SYNC_CONTINUE,   /**< Continue previous sync procedure,
                              used on Radio Bearer Reconfigurations. */

    NUM_L1_SYNC
}
l1_sync_procedure_t;


/** Type for an array of Paging Indicators.
 * This gives an array where each bit represents a single paging indicator
 * transmission within a frame.  There are enough bits to represent up to
 * 144 bits in a frame, although the PICH maybe configured to transmit fewer.
 *
 * \see CphyNodeBSccpchConfigReq
 */
typedef uint32_t pi_t[(MAX_PI_PER_FRAME+31) / 32];

/** Type for defining how communicate if to estimate the osc dac
 *  when running rem-gsm
 */
typedef enum
{
    L1_OSC_LOCK_DISABLE = 0,   /**< Don't measure the frequency error. */
    L1_OSC_LOCK_MEASURE_ONLY,  /**< Measure and report the frequency error. */
    L1_OSC_LOCK_UPDATE         /**< Measure and report the frequency error AND update the osc dac value. */
}
updateOscMode_t;


///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

/** Return a l1status_t value as a string for pretty printing.
 * \param[in] status  The l1status enumerated type.
 * \retval Pointer to a constant string giving the human readable status.
 */
const char *CphyL1StatusToString(l1status_t status);

/** Return a l1mode_t value as a string for pretty printing.
 * \param[in] mode  The l1mode enumerated type.
 * \retval Pointer to a constant string giving the human readable mode.
 */
const char *CphyL1ModeToString(l1mode_t mode);

/** Return a band_t value as a string for pretty printing.
 * \param[in] band  The band enumerated type.
 * \retval Pointer to a constant string giving the human readable band.
 */
const char *CphyBandToString(band_t band);

/** Return a spreading_factor_t as a string for pretty printing.
 * \param[in] sf   The spreading factor enumerated type.
 * \retval Pointer to a constant string giving the human readable spreading factor.
 */
const char *CphySpreadingFactorToString(spreading_factor_t sf);

/** Pretty print an array of uint16_t values.
 *
 * \param[in] out   The stream to which the array should be printed.
 * \param[in] name  The name of the array.
 * \param[in] array Array of values to print.
 * \param[in] n     Count of elements in the array to print.
 */
void CphyPrintArrayU16(FILE *out, const char *name, const uint16_t *array, uint8_t n);


/** Pretty print an array of int16_t values.
 *
 * \param[in] out   The stream to which the array should be printed.
 * \param[in] name  The name of the array.
 * \param[in] array Array of values to print.
 * \param[in] n     Count of elements in the array to print.
 */
void CphyPrintArrayS16(FILE *out, const char *name, const int16_t *array, uint8_t n);


#ifdef __cplusplus
}
#endif


///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////


#endif /* __CPhyTypes_h_ */
