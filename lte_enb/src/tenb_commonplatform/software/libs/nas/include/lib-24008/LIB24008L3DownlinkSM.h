///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// LIB24008L3DownlinkSM.h
//
// Wrapper for the generated SM messages; we do this to hide the Encodix
// structures from the rest of the applications, so they don't need to 
// be exposed to the raw horror contained within.
//
// Copyright � 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __LIB24008L3DownlinkSM_h_
#define __LIB24008L3DownlinkSM_h_

///////////////////////////////////////////////////////////////////////////////
// Encodix Includes
///////////////////////////////////////////////////////////////////////////////

#include <Encodix24008.h>

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

#include "LIB24008Downlink.h"

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
// Class: LIB24008L3DownlinkSM
// Desc:  We don't want to have the memory management of the Dafocus structures
//        exposed to the main applications to prevent memory leaks.
///////////////////////////////////////////////////////////////////////////////

class LIB24008L3DownlinkSM : public LIB24008Downlink
{
public:
	// Constructor / destructor.
	LIB24008L3DownlinkSM ();
	virtual ~LIB24008L3DownlinkSM ();

	// Accessors for the member data.
	TXTIDDownlink_Data &GetL3PDU ();
	const TXTIDDownlink_Data &GetL3PDU () const;

private:

	// The message structure, populated manually prior to an Encode call.
	TXTIDDownlink_Data m_encodixPDU;
};

#endif
