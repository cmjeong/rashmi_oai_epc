///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// LIB24008Interface.h
//
// Exports from the LIB_24.008 library: these C functions are wrappers for
// the (hidden) implementation in the Encodix generated source.
//
// Copyright � 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __LIB24008Interface_h_
#define __LIB24008Interface_h_

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

class LIB24008Uplink;
class LIB24008L3Uplink;
class LIB24008L3UplinkSM;
class LIB24008L3Downlink;
class LIB24008L3DownlinkSM;

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////
#include <Layer3Constants.h>

// GSM Layer 3 message builder functions.  Any problems building and these
// will throw a LIB24008Exception, so be sure to wrap any code calling 
// these in try...catch logic.

// These use the Encodix generated code: and notice how shit the Encode
// interface is.  We have to identify the message type, since there are
// separate Encode functions for every message type!

LIB24008Uplink *LIB_24008_Decode (const u8 *pduData, u16 pduLength);

void LIB_24008_EncodeMM (GSM0408MmMessageType mmType, LIB24008L3Downlink &l3Message);
void LIB_24008_EncodeCC (GSM0408CcMessageType ccType, bool tiFlag, u8 tiValue, LIB24008L3Downlink &l3Message);
void LIB_24008_EncodeSM (GSM0408SmMessageType smType, bool tiFlag, u8 tiValue, LIB24008L3DownlinkSM &l3Message);
//void LIB_24008_EncodeSM (GSM0408SmMessageType smType, bool tiFlag, u8 tiValue, LIB24008L3UplinkSM &l3Message);
void LIB_24008_EncodeGMM (GSM0408GmmMessageType gmmType, LIB24008L3Downlink &l3Message);

#endif
