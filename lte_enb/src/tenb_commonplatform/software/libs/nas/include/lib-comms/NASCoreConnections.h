///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// NASCoreConnections.h
//
// Application class that maintains a container of NASCoreConnection objects.
//
// Copyright � 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __NASCoreConnections_h_
#define __NASCoreConnections_h_

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <system/TimerInterface.h>
#include <NASObject.h>
#include <System3Way.h>
#include "NASCoreConnection.h"

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

// Callback function to handle receipt of CNXNLESS-DATA
typedef void (*NAS_CNXNLESSDATA) (const NASAppPayload &thePayload);

///////////////////////////////////////////////////////////////////////////////
// Class: NASCoreConnections
// Desc : Overall management class maintaining links between
// 3 Way applications.
///////////////////////////////////////////////////////////////////////////////
class NASCoreConnections : public NASObject
{
public:
	// Construction / destruction.
	NASCoreConnections (NASApp sourceApp, NASApp destApp, NAS_CNXNDATA dataCallback, NAS_CNXNREL releaseCallback, NAS_CNXNFAIL failureCallback, NAS_CNXNLESSDATA broadcastCallback);
	virtual ~NASCoreConnections ();

	// Call this when the system is shutting down, to cleanly terminate and
	// links to a remote application.  All we do is send CNXN_REL and don't
	// bother waiting for CNXN_RELCOMP (why bother when we know the application
	// is closing down).
	void TheEndIsNigh ();

	// And when final shutdown beckons, this empties all allocated resources
	// prior to (presumbably) application termination.
	void StopConnectionEngine ();

	// Message handlers, that send + receive PDU's from the remote application.
	void NAS_Rx (NASAppMessage msgType, const COREMessageStructure &nasCoreMsg);
	void NAS_Tx (CORE_ConnectionIdentifier localConnId, const NASAppPayload &thePayload);

	// When a NASCoreConnection timer expires, it will be routed (and handled)
	// in this method.
	bool NotifyTimerExpiry (threeway::TimerHandle expiredTimer);

	// Static, equivalent of a UNIT-DATA: not sent to a specific connection
	// handler, more of a broadcast message between the specified applications.
	static void SendNASMessageNoTarget (NASApp appSource, NASApp appDest, const NASAppPayload &thePayload);

	// Get current count on the number of connections.
	u32 GetConnectionCount () const;

	// For any purpose other than debug?  Retrieve a given connection object.
	const NASCoreConnection &GetConnection (u32 cnxnIndex) const;

	// This is called when a new NASCoreConnection is required, either as a result
	// of a received NAS_CNXN_REQ, or when a local app is about to send NAS_CNXN_REQ.
	NASCoreConnection *RequestConnection ();

	// Called to send RELEASE on a given connection, shortly followed by a
	// REL-COMP or timer expiry, both of which cause the NASCoreConnection
	// object to be deleted.
	void ReleaseConnection (CORE_ConnectionIdentifier coreConnId);

	// Brute force: no messaging involved, just reset all memory
	// associated with the link number provided.
	void ForceConnectionDrop (CORE_ConnectionIdentifier localConnId);

	// Check the connections we currently know about to see if any have
	// been idle for a very long time and should be erased.  The aging
	// units are minutes.
	void AgeConnections (u32 agePeriod) const;

protected:

	// Try to find the specified connection instance.  Will return NULL
	// if it cannot be found.
	NASCoreConnection *FindConnection (CORE_ConnectionIdentifier localId);

	// Mark a currently used connection as finished, so we can now
	// re-use it for a subsequent connection.
	void FreeCoreConnection (CORE_ConnectionIdentifier localConnId);

private:

	// Since we fix all of the identifiers at compile time, we know
	// the maximum number of objects we will need at run time.  Use this
	// knowledge to create all of our objects on the stack to help
	// prevent thos pesky memory leaks.
	NASCoreConnection m_coreConnections [NUMBER_OF_NAS_LINKS];

	// An ever incrementing number used to give unique connection ID
	// to each new connection
	static u32 sm_nextConnectionId;

	// Just a tracked to make some operations a bit easier: how many links
	// currently allocated for use?
	u32 m_activeConnectionCount;

	// Need the knowledge of which 3 Way Application is the SOURCE (i.e.
	// ORIGINATOR of a connection), and which is the DEST.
	NASApp m_sourceApp;
	NASApp m_destApp;

	// Callback data handler for connectionless, broadcast messages.
	// Callback function to handle receipt of CNXN-DATA
	NAS_CNXNLESSDATA m_broadcastHandler;
};

#endif
