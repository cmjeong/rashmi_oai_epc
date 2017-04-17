///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// NASMessage.h
//
// Class wrapper handling message content that will be sent between the
// various 3Way applications.
//
// Copyright � 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __NASMessage_h_
#define __NASMessage_h_

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////
#include <System3Way.h>

// To simplify code for the applications, I've moved the transport mechanism
// declarations into the library.  Should make life easier now, and in
// particular later if we change the transport from UDP.
class NASTransport;

// If your applications needs to communicate with 3Way_RRCLinkLayer, use
// this object.
extern NASTransport s_rrcLinkLayerTransport;

// If your applications needs to communicate with 3Way_NASCore, use
// this object.
extern NASTransport s_coreTransport;

// If your applications needs to communicate with 3Way_HLR, use
// this object.
extern NASTransport s_hlrTransport;

// If your applications needs to communicate with 3Way_DBX simulator, use
// this object.
extern NASTransport s_dbxTransport;

// If your applications needs to communicate with the 3Way SIP Portal, use
// this object.
extern NASTransport s_sipTransport;

// If your applications needs to communicate with the 3Way SMSC Portal, use
// this object.
extern NASTransport s_smscTransport;

// If your application needs to communicate with the 3Way GGSN, use
// this object.
extern NASTransport s_ggsnTransport;

// If your application needs to communicate with the 3Way Iu Interface, use
// this object.
extern NASTransport s_iuTransport;

// Note that the USER (i.e. application) code is responsible for:
//
// 1. Calling SetPorts() on the NASTransport to tell it which ports to use.
// 2. Calling SetDestAddress() on the NASTransport to tell it the destination
//    application IP address (it will default to loopback otherwise).
// 3. Calling StartThread() to initialise the NASTransport.
// 4. Calling StopThread() to terminate the NASTransport CLEANLY.

extern NASTransport s_portalTransport;

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

// Maximum payload in a message transported.
#define MAX_NAS_MESSAGE_SIZE	2500

// Use a static transport structure for ease of programming: our traffic
// will have no significant bandwidth requirement, so why bother with
// length and sync bytes?
typedef struct structNASMessageStructure
{
	// Application that is the source of the message.
	NASApp appSource;

	// Destination for the message.
	NASApp appDestination;

	// The message type, used to decode the following message
	// buffer array.
	NASAppMessage nasMessageType;

	// And the number of bytes in the message buffer above.
	u32 messageLength;

	// Raw buffer holding the message data.  We are making it
	// fixed size for speed of coding reasons: if necessary,
	// we can make it more flexible later.
	u8 nasMessage[MAX_NAS_MESSAGE_SIZE];

}NASMessageStructure;


///////////////////////////////////////////////////////////////////////////////
//
// Class: NASMessage
// Desc : Manage packing user data into a simple structure and sending it
//        to the specified application.
//
///////////////////////////////////////////////////////////////////////////////
class NASMessage
{
public:
	// Construction / destruction.
	NASMessage (NASApp msgSrc, NASApp msgDest, NASAppMessage msgType, const u8 *msgBuffer = NULL, u32 msgLength = 0);
	NASMessage (const NASMessageStructure &nasMsg);
	virtual ~NASMessage ();

	// Pack message content into the payload structure and issue.
	void SendMessage ();

	// Accessor for the message source.
	NASApp GetSource () const;

	// Accessor for the message destination.
	NASApp GetDestination () const;

	// Accessor for the message type.
	NASAppMessage GetMessageType () const;

	// Accessors for the message content.
	const u8 *GetMessage (u32 &msgLength) const;
	const NASMessageStructure &GetMessage () const;

	// This method is used to obtain the buffer that
	// user code can copy a message directly into.  Remember
	// it has to fit into the MAX_NAS_MESSAGE array.
	// Built in debug functionality.
	void FillMessage (const u8 *msgBuffer, u32 msgLength);

private:
	// Common information shared across all messages.

	// Structure containing the actual message content.
	NASMessageStructure m_nasMessage;
};

#endif

