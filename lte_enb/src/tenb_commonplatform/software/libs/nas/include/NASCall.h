///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// NASCall.h
//
// Information about a 3G NAS call currently in progress.
//
// Copyright � 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __NASCall_h_
#define __NASCall_h_


///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/TimerInterface.h>
#include <ed_c.h>


///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

// Enumeration containing the various call types currently supported.
typedef enum enumNASCallType
{
	NO_CALL,
	UE_TO_UE_CALL,
	UE_TO_SIP_CALL,
	SIP_TO_UE_CALL
}NASCallType;

// Elements valid when the call in the network is between two locally
// attached UE handsets.
typedef struct structGSMCall
{
	// The link number used to communicate with the calling 
	// UE (via the NAS_Core).
	MobileControlBlockNumber moLinkNumber;

	// The subscriber at the 'far' side of the MO leg of the call.
	c_MobileId moIdentity;
	c_TBCDArray moNumber;

	// The link number used to communicate with the called 
	// UE (via the NAS_Core).
	MobileControlBlockNumber mtLinkNumber;

	// The subscriber at the 'far' side of the MT leg of the call.
	// The TMSI of the dialled subscriber.
	c_MobileId mtIdentity;
	// And also the IMSI: we don't know which of these will be in
	// the PAGE RESPONSE, so need both.
	c_MobileId pagedImsi;
	// Finnally the MSISDN of the dialled subscriber.
	c_TBCDArray mtNumber;

}GSMCall;

// Elements valid when the call in the network is between one
// locally attached UE handset and a SIP destination.
typedef struct structSIPCall
{
	// The link number used to communicate with the calling 
	// UE (via the NAS_Core).
	MobileControlBlockNumber ueLinkNumber;

	// The subscriber at the GSM leg of the call.
	c_MobileId ueIdentity;

	// The destination telephone number dialled: will be a local UE number
	// if we have SIP -> UE call, a SIP tel: number if it's UE -> SIP.
	c_TBCDArray dialledNumber;

	// The telephone number of the dialling party: will be a local UE number
	// if we have UE -> SIP call, a SIP tel: number if it's SIP -> UE.
	c_TBCDArray diallingNumber;
	
	// Connection Number to contact the UE side of the call.
	CORE_ConnectionIdentifier rrcLinkNumber;

	// Connection Number to contact the SIP lig of the call.
	CORE_ConnectionIdentifier sipLinkNumber;

}SIPCall;

typedef struct structNASCall
{
	// This enumeration identifies the type of call this element
	// represents.  This will be used to identify which of the union
	// elements is populated and in use.
	NASCallType callType;

	// The start time of the call is NOT the time at which
	// the SETUP message is received, it's the time of CONNECT
	// indicating that the call has been answered.
	time_t callStartTime;

	// The stop time is when the first DISCONNECT message is received
	// from one of the mobiles in this call.
	time_t callStopTime;

	// Paging Timer: will expire if no PAGING_RESPONSE is received
	// from the terminating subscriber leg of the call.  Note that although
	// it is declared at the 'top' of the structure, it will NOT be used
	// when the call type is UE_TO_SIP_CALL as we have no knowledge 
	// of the PAGING mechanism used by the (3rd party) SIP controller.
	threeway::TimerHandle t3113;

	// Identifies whether the call is a Speech, Video or Data call.  Used to
	// pick out the correct RRC Radio Bearer Setup message to send.
	RadioBearerRequest callDescription;

	// Indicator as to whether the dialling number should be displayed at the
	// dialled handset.
	bool moBlockedCLI;

	union
	{
		// This will be valid if CallType is set to UE_TO_UE_CALL.
		GSMCall gsmCall;

		// This will be valid if CallType is set to UE_TO_SIP_CALL
		// or SIP_TO_UE_CALL.
		SIPCall sipCall;
	}u;
}NASCall;

///////////////////////////////////////////////////////////////////////////////
// Class: GSMCall
// Desc : Information about a call present in our network.
///////////////////////////////////////////////////////////////////////////////

#endif
