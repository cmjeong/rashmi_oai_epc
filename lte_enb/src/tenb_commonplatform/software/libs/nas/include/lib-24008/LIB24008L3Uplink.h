///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// LIB24008L3Uplink.h
//
// Wrapper for the generated messages; we do this to hide the Encodix
// structures from the rest of the applications, so they don't need to 
// be exposed to the raw horror contained within.
//
// Copyright © 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __LIB24008L3Uplink_h_
#define __LIB24008L3Uplink_h_

///////////////////////////////////////////////////////////////////////////////
// Encodix Includes
///////////////////////////////////////////////////////////////////////////////

#include <Encodix24008.h>

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

#include "LIB24008Uplink.h"

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
// Class: LIB24008L3Uplink
// Desc:  We don't want to have the memory management of the structures
//        exposed to the main applications to prevent memory leaks.
///////////////////////////////////////////////////////////////////////////////

class LIB24008L3Uplink : public LIB24008Uplink
{
public:
	// Constructor / destructor.
	LIB24008L3Uplink ();
	LIB24008L3Uplink (const u8 pageResponse [], u16 pageRespLength);
	virtual ~LIB24008L3Uplink ();

	// Accessors for the generated message.
	TL3Uplink_Data &GetL3PDU ();
	const TL3Uplink_Data &GetL3PDU () const;
	const c_PAGE_RESPONSE_UP GetPagingResponse () const;

	// Retrieve Layer 3 protocol discriminator.
	virtual GSM0408ProtocolDiscrim GetPD () const;

private:

	// The message structure, populated by the Encodix Decode_L3Upink
	// call.
	TL3Uplink_Data m_encodixPDU;

	// And since Encodix don't support this message, we do it manually
	// and spoof any calling application code.
	_c_PAGE_RESPONSE_UP m_pageResponse;
};

#endif
