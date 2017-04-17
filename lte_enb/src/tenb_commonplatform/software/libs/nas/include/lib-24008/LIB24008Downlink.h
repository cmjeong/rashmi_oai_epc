///////////////////////////////////////////////////////////////////////////////
//
// LIB24008Downlink.h
//
// Base class wrapper for generated messages.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __LIB24008Downlink_h_
#define __LIB24008Downlink_h_

///////////////////////////////////////////////////////////////////////////////
// Class: LIB24008Downlink
// Desc:  We don't want to have the memory management of the Dafocus structures
//        exposed to the main applications to prevent memory leaks.
///////////////////////////////////////////////////////////////////////////////

class LIB24008Downlink
{
public:
	// Constructor / destructor.
	LIB24008Downlink ();
	virtual ~LIB24008Downlink ();

	// Not const as we use this to obtain the buffer when populating
	// the buffer in the Encode logic.
    u8 *GetEncodeBuffer ();
    char *GetEncodeBufferAsCharPtr ();

	// And a const version used when using the object as read-only (e.g.
	// for message sending).
	const u8 *GetEncodeBuffer () const;

	u32 GetEncodeBufferLength () const;
	void SetEncodeBufferLength (u32 encodedBufferLength);

	// Debug output to screen.
	void DumpPDU ();

private:
	// The result of the encode.
	u8 m_encodixEncode[1024];

	// And the length (in BYTES) of the data in the buffer above.
	u32 m_encodeLength;
};

#endif
