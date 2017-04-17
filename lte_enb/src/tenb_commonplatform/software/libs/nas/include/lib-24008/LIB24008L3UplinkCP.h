///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// LIB24008L3UplinkCP.h
//
// A CP message: either CPDATA, CPACK or CPERROR.
//
// Copyright ? 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __LIB24008L3UplinkCP_h_
#define __LIB24008L3UplinkCP_h_

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

#include "LIB24008Uplink.h"

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

typedef enum enumLIB24008L3UplinkCPType
{
	CPDATA = 0x01,
	CPACK = 0x04,
	CPERROR = 0x10
}LIB24008L3UplinkCPType;

typedef enum enumCPErrorCause
{
	NETWORK_FAILURE = 0x11,
	CONGESTION = 0x16,
	INVALID_TID = 0x51,
	SEMANTICALLY_INCORRECT_MESSAGE = 0x5F,
	INVALID_MANDATORY_INF = 0x60,
	MESSAGE_TYPE_NON_EXISTENT = 0x61,
	MESSAGE_NOT_COMPATIBLE_WITH_STATE = 0x62,
	INFORMATION_ELEMENT_NON_EXISTENT = 0x63,
	PROTOCOL_ERROR = 0x6F
}CPErrorCause;

typedef struct structRPUserData
{
	u8 rpLength;
	u8 rpMessage[232];
}RPUserData;

class RPMessage;

///////////////////////////////////////////////////////////////////////////////
// Class: LIB24008L3UplinkCP
// Desc : Layer 3 CP decode / encode class.
///////////////////////////////////////////////////////////////////////////////
class LIB24008L3UplinkCP : public LIB24008Uplink
{
public:
	// Construction / destruction.
	LIB24008L3UplinkCP (const u8 *cpMessage, u16 messageLength);
	virtual ~LIB24008L3UplinkCP ();

	// Retrieve the type of the CP message.
	LIB24008L3UplinkCPType GetType () const;

	// Combined Transaction Id / Protocol Discriminator byte.
	u8 GetTId () const;

	// For a CPERROR, retrieve the cause.
	CPErrorCause GetErrorCause () const;

	// For a CPDATA, retrieve the RP payload.
	const RPUserData &GetRPMessage () const;

	// Retrieve Layer 3 protocol discriminator.
	virtual GSM0408ProtocolDiscrim GetPD () const;

private:

	// Transaction identification number.
	u8 m_tId;

	// Which if the CP messages do we have.
	LIB24008L3UplinkCPType m_cpType;

	// If we have a CPERROR, this will contain the cause.
	CPErrorCause m_cpErrorCause;

	// If we have an RP payload to a CPDATA, it will be decoded here.
	RPUserData m_rpMessage;
};

#endif

