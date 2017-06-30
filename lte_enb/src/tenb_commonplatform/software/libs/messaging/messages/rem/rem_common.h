/**************************************************************************************************

     Name:     REM-APP

     Type:     C++ Header file

     Desc:     All datastructures are added in this header file

     File:     rem_common.h

     Sid:      rem_common.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/Br_Tenb_Mspd_T2K_Intg_MS8.0_RC/1 - Tue Jul 23 16:17:41 2013

     Prg:      Ambika S

**************************************************************************************************/

#ifndef REM_COMMON_H_
#define REM_COMMON_H_

#ifdef USE_RADISYS_OAM
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
//	  System Includes
///////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <stdio.h>
#include <time.h>

#include "rem_interface.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
//	  Message Constants
///////////////////////////////////////////////////////////////////////////////////////////////////
#define REM_MAX_PLMN_LIST       64
#define REM_MAX_PCI_LIST        32
#define REM_MAX_CARRIER_LIST	64
#define REM_MAX_BAND_LIST		64
#define REM_MAX_RSSI_LIST		16
#define REM_MAX_RSRP_LIST		16
#define REM_MAX_CELL_LIST		64
#define REM_MAX_ERRORS			256
#define REM_MAX_VENDOR_LIST 	6
#define REM_MAX_CELL_FOUND_LIST	16
#define TEST 00

#define RSSI_THRESHOLD_TO_IGNORE	-105
#define RSRP_THRESHOLD_TO_IGNORE	-105
#define RSCP_THRESHOLD_TO_IGNORE	-105
#define MIN_RSSI	-128
#define MIN_RSRP	-128
#define MIN_RSCP	-140

#define SI_WINDOW  40

#define MIB_FAILED 	1
#define MIB_OK		0

#define RSSI_TIMEOUT_PER_EARFCN	15

#define NMM_SUCCESS			0
#define NMM_ERR_MIB_FAILED	200

///////////////////////////////////////////////////////////////////////////////
// Debugging Flags
///////////////////////////////////////////////////////////////////////////////

#define AIRV_ASSERT assert

///////////////////////////////////////////////////////////////////////////////////////////////////
// Trace Constants & Trace levels bit masks.
///////////////////////////////////////////////////////////////////////////////////////////////////

static const U32 REM_TRACE_VERBOSE          = 0x00000001;
static const U32 REM_TRACE_INFO             = 0x00000002;
static const U32 REM_TRACE_WARNING          = 0x00000004;
static const U32 REM_TRACE_CRITICAL         = 0x00000008;
static const U32 REM_TRACE_FATAL            = 0x00000010;
static const U32 REM_TRACE_CALL_STACK       = 0x00000020;
static const U32 REM_TRACE_EXCEPTIONS       = 0x00000040;
static const U32 REM_TRACE_CAT_NONE=0; // Null category used when no category is required/relevant

// MAP < band, list(ARFCN) >
typedef std::map<U8, std::list<U16> > BANDLIST;
typedef std::list<U16> ARFCNLIST;
typedef std::list<std::string> PLMNLIST;
typedef std::list<std::string> UARFCNLIST;

#ifdef USE_RADISYS_OAM
inline void remLog(U32 level,const char* strLog)
{
    TRACE_MSG_LEV(level,strLog);
}
#else
void remLog(U32 level,const char* strLog);
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
//   @enum __enSupportedRAT
///////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	RAT_LTE = 0,
	RAT_WCDMA,
	RAT_GERAN,
	RAT_CDMA,
	MAX_SUPPORTED_RATS
} __enSupportedRAT;

#if 0
///////////////////////////////////////////////////////////////////////////////////////////////////
//   @enum __enRemScanStatus
///////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	REM_INDETERMINATE = 0,
	REM_IN_PROGRES,
	REM_SUCCESS,
	REM_ERROR,
	REM_ERROR_TIMEOUT
} __enRemScanStatus;
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
//   @struct __stRemFromOamStartScan
//   Message from OAM to RemApp
///////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
	__enSupportedRAT   enScanType;	// Scantype : LTE/WCDMA/GERAN/CDMA
} __stRemFromOamStartScan;

#if 0
///////////////////////////////////////////////////////////////////////////////////////////////////
//   @struct __stRemMsgScanStatus
//   Message from RemApp to SON/OAM
///////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	__enSupportedRAT		enScanType;        // Scantype
	__enRemScanStatus  		enRemScanStatus;   // Scan status
	std::string				strErrorDetails; // Reason when scan status
											 // is error or timeout
} __stRemMsgScanStatus;
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
//   @enum __enRemCsgSpiltNumOfPsc
//
///////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	REM_NUM_OF_PSC_5 = 5,
	REM_NUM_OF_PSC_10 = 10,
	REM_NUM_OF_PSC_15 = 15,
	REM_NUM_OF_PSC_20 = 20,
	REM_NUM_OF_PSC_30 = 30,
	REM_NUM_OF_PSC_40 = 40,
	REM_NUM_OF_PSC_50 = 50,
	REM_NUM_OF_PSC_64 = 64,
	REM_NUM_OF_PSC_80 = 80,
	REM_NUM_OF_PSC_120 = 120,
	REM_NUM_OF_PSC_160 = 160,
	REM_NUM_OF_PSC_256 = 256
} __enRemCsgSpiltNumOfPsc;

///////////////////////////////////////////////////////////////////////////////////////////////////
//   @struct __stRemMsgSonStartCarrierExpScan
//   Message from SON to RemApp
///////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	U8			    		bScanTimeOut; 	// Maximum duration of time during
										 	// which Express scan shall be active
	U8						bNumOfEarfcn; 	// Number of carriers which should be
										 	// Measured
	U16						usnEarfcnList[REM_MAX_CARRIER_LIST];
										 	// The list of carriers to be measured
} __stRemMsgSonStartCarrierExpScan;

///////////////////////////////////////////////////////////////////////////////////////////////////
//   @struct __stRemMsgSonStartPciExpScan
//   Message from SON to RemApp
///////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	U8						bScanTimeOut; // Maximum duration of time during
								   		  // which Express scan shall be active
	U8						bNumOfPcis;   // Number of PCIs in the array
	U16						usPci[REM_MAX_PCI_LIST];
									      // Physical Cell Id of the detected
										  // EUTRA cell
} __stRemMsgSonStartPciExpScan;

///////////////////////////////////////////////////////////////////////////////////////////////////
//   @struct __stRemMsgSonCarrierScanRes
//   Message from RemApp to SON
///////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	__enRemScanStatus  		enScanStatus;  	// Scan status
	std::string			   	strErrorDeatails;
											// Reason when scan status is error
										 	// or timeout
	U8				   		bNumRssi;	 	// Number of RSSI's in array
	S16				   		sNRssi[REM_MAX_RSSI_LIST];
											//Received Signal Strength Indicator
} __stRemMsgSonCarrierScanRes;

///////////////////////////////////////////////////////////////////////////////////////////////////
//   @struct __stRemMsgSonPciScanRes
//   Message from RemApp to SON
///////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	__enRemScanStatus  		enScanStatus;// Scan status
	std::string			   	strErrorDeatils;
							       		 // Reason when scan status
										 // is error or timeout
	U8				   		bNumRsrp;	 // Numer of RSRP's in the array
	S16				   		sNRsrp[REM_MAX_RSSI_LIST];
										 // Received RSRP level of detected
										 // EUTRA cell, specified in dBm.
} __stRemMsgSonPciScanRes;



#if 0
///////////////////////////////////////////////////////////////////////////////////////////////////
//   @struct __stRemWcdmaCellBcchCsgSplit
//
///////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	U8					bStartPscRangeCoeff; // Value of this IE multiplied
										     // by 8 specifies the start PSC
											 // value
	__enRemCsgSpiltNumOfPsc	enNumOfPscs;	 // Number of PSCs reserved for
											 // CSG cells in each PSC range
	U8					bPscRange2Offset;	 // If present, UE shall calculate
											 // the second PSC range
} __stRemWcdmaCellBcchCsgSplit;

///////////////////////////////////////////////////////////////////////////////////////////////////
//   @struct __stRemWcdmaCellBcchRefPos
//
///////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	S8					bLatitude;	       // Latitude of device's position
										   // in degrees,multpilied by 1
										   // million
	U16					usLongitude;	   // Longitude of device's position
										   // in degrees,multiplied by 1
										   // million
	U8					bUncertSemiMajor;  // Uncertainty r is derived from
										   // this parameter 'k' by
										   // r = 10 * (1.1 <power> (k-1))
	U8					bUncertSemiMinor;  // Uncertainty r is derived from
	   	   	   	   	   	   	   	   	   	   // this parameter 'k' by
	   	   	   	   	   	   	   	   	   	   // r = 10 * (1.1 <power> (k-1))
	U8					bOrientMajorAxis;  // This is(N) derived by the
										   // formula: 2N <= a < 2(N+1)
	U8					bConfidence;	   	   // The degree of confidence in the
										   // ellipsoid's points expressed in
										   // percent
} __stRemWcdmaCellBcchRefPos;

///////////////////////////////////////////////////////////////////////////////////////////////////
//   @struct __stRemWcdmaCellBcch
//
///////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	std::string			strPlmnType;	   // Type of PLMN ,Enumeration of
										   // GSM-MAP & ANSI-41
	std::string	  		strPlmnId[REM_MAX_PLMN_IDS];
										   //PLMN Id consisting of MCC & MNC
	U16					usLac;			   // Location Area Code as defined
	U8					bRac;			   // Routing Area Code as defined
										   // in SIB1
	U32					uiCellId;		   // Cell Identity as specified in
										   // SIB3
	S16					sPcpichTxPwr;	   // Primary Common Pilot Channel
										   // (CPICH) power level on SIB 5/6
	U8					bCsgInd;		  	   // Indicates whether CSG is
	  	  	  	  	  	  	  	  	  	   // used in this cell or not
	U32					uiCsgIdentity;	   // Defines CSG ID
	std::string			strUarfcnDlList;   // Comma seperated list of UTRA
										   // ARFCNs.This list is broadcast
										   // in SIB-11 bits
	__stRemWcdmaCellBcchCsgSplit 	stWcdmaCsgPscSplitInfo;
	__stRemWcdmaCellBcchRefPos		stWcdmaBcchRefPosition;
} __stRemWcdmaCellBcch;

///////////////////////////////////////////////////////////////////////////////////////////////////
//   @struct __stRemWcdmaCellRf
//
///////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	U16					usNuarfcndl;	// UTRA ARFCN in the DL direction
										// of an FDD mode cell
	S32					icPichRscp; 	// Received signal level in dBm
										// of the CPICH channel
	S32		 			icPichEcNo;		// Measured EcNo in dB received
										// in the downlink pilot channel
	S32					iRssi;			// This RSSI measurement is for
										// Inter-frequency handover evalu
										// -ation
	U16					usPsc;			// Primary Scrambling Code
	 __stRemWcdmaCellBcch	stRemWcdmaCellBcch[REM_MAX_CELL_LIST];
} __stWcdmaRemResult;
#endif

#endif /* REM_COMMON_H_ */
