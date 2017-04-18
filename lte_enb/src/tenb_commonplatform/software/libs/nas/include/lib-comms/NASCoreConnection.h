///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// NASCoreConnection.h
//
// Manage a single Connection between the RRCLinkLayer and the NAS-CORE.
// Sort of the equivalent of an A-Interface connection, only much more
// lightweight.
//
// Copyright � 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __NASCoreConnection_h_
#define __NASCoreConnection_h_

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

#include <System3Way.h>
#include <NASString.h>
#include <NASAppPayload.h>
#include <system/TimeWrap.h>
#include <system/TimerInterface.h>

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

// Callback function to handle receipt of CNXN-DATA
typedef void (*NAS_CNXNDATA) (CORE_ConnectionIdentifier coreConn, const NASAppPayload &thePayload);

// Callback function to handle receipt of CNXN-REF, CNXN-REL, CNXN-RELCOMP
typedef void (*NAS_CNXNREL) (CORE_ConnectionIdentifier coreConn);

// Callback function to handle receipt of Connection Failure (Timer Expiry)
typedef void (*NAS_CNXNFAIL) (CORE_ConnectionIdentifier coreConn);

///////////////////////////////////////////////////////////////////////////////
// Class: NASCoreConnection
// Desc : Class that handles a single Connection session between the
//        RRC Link Layer and the CORE.  
///////////////////////////////////////////////////////////////////////////////
class NASCoreConnection
{
public:
	// Construction / destruction.
	NASCoreConnection ();
	virtual ~NASCoreConnection ();

	// Separate init+term methods as these objects are on the stack and
	// re-used, to prevent memory leakage.
	void HardwireCallbacks (NAS_CNXNDATA dataHandler, NAS_CNXNREL releaseHandler, NAS_CNXNFAIL failureHandler);
	void InitCOREConnection (NASApp sourceApp, NASApp destApp, CORE_ConnectionIdentifier localConnId, CORE_ConnectionIdentifier remoteConnId);
	void TermCOREConnection (bool invokeReleaseHandler);

	// Simple ways to check object usage.
	bool CnxnAllocated () const;
	bool CnxnAvailable () const;

	// Check to see if this connection has been idle for longer than the
	// provided age period.  If it has, it will be deleted.  The age
	// period units are minutes.
	void AgeConnection (u32 agePeriod);

	// Note this is NOT the same as TermCOREConnection: the difference being that
	// TermCOREConnection is part of 'normal' link release, and invokes the CNXNREL
	// callback, whereas this function does not.
	void DeleteFailedCnxn ();

	// Retrieve the connection number used to identify this CORE Link
	// within the RRC Link Layer.
	CORE_ConnectionIdentifier GetLocalConnectionId () const;
	CORE_ConnectionIdentifier GetRemoteConnectionId () const;

	// When was the last activity on this link?  Housekeeper thread
	// could use this to age (delete) them if necessary to make sure
	// things don't get stuck.
	const threeway::TimeWrap &GetTimeOfLastActivity () const;

	// Receive a Layer3 message PDU from the CORE (MSC).  They are virtual
	// in case the leaf class wants to add to the core functionality, but
	// MAKE SURE YOU CALL THE BASE IMPLEMENTATION, as it controls things
	// like the messaging timers.
	virtual void ReceiveCNXNRequest (const COREMessageStructure &nasCoreMsg);
	virtual void ReceiveCNXNConfirm (const COREMessageStructure &nasCoreMsg);
	virtual void ReceiveCNXNRefuse (const COREMessageStructure &nasCoreMsg);
	virtual void ReceiveCNXNData (const COREMessageStructure &nasCoreMsg);
	virtual void ReceiveCNXNRelease (const COREMessageStructure &nasCoreMsg);
	virtual void ReceiveCNXNReleaseComplete (const COREMessageStructure &nasCoreMsg);

	// Transmit logic: sends (optional) PDU payload to the remote application.
	// Arguments are defaulted so we can establish a link without providing
	// any message payload.
	void SendNASMessage (const NASAppPayload &appPayload);

	// When a connection is no longer used, issue a CON_RELEASE message to
	// the far side: receipt of REL_COMP (or timer expiry) clears down the
	// local connection instance.  For simplicity, I am not allowing any
	// message payload in this message.
	void SendNASRelease ();

    void OpenConnection();
    void CloseConnection();
    threeway::TimerHandle GetTimerHandle () const;

protected:

	// Interface methods that force leaf class behaviour.

	// Leaf class must provide some debug tracing if it's a NASObject.
	virtual void GetObjectDescription (char *debugText) const;

	// Force debug menu to drive debug options.
	virtual void GetMenu (NASString& debugMenu) const;

	// Tell leaf class which option has been selected from the menu.
	virtual bool HandleMenuOption (char menuOption, NASString& resultText) const;

	void StartConnectionTimer ();
    void StopConnectionTimer ();
    void UpdateCreateTime();

private:

	// We set up a 'pseudo' connection between the two CORE_Connection 
	// instances running in spearate applications.
	CORE_ConnectionIdentifier m_localCOREConnectionId;
	CORE_ConnectionIdentifier m_remoteCOREConnectionId;

	// Need the knowledge of which 3 Way Application is the SOURCE (i.e.
	// ORIGINATOR of a connection), and which is the DEST.
	NASApp m_sourceApp;
	NASApp m_destApp;

	// These functions will be called whenever we receive a PDU with payload
	// data or a refuse, release, releasecomplete or timer expiry
	// from the remote side of a given NASCoreConnection.  User code must
	// suppliy this in the constructor arguments.  I don't dare you to set
	// either of these to NULL...
	NAS_CNXNDATA m_dataHandler;
	NAS_CNXNREL m_releaseHandler;
	NAS_CNXNFAIL m_failureHandler;

	// The m_releaseCompleteIn flag is here as we have seen the following behaviour...
	// <-- CNXN-RELEASE
	// --> CNXN-RELCOMP
	//     So the ReleaseComplete Handler runs, deleting instance information...
	// < StartConnectionTimer >
	//
	// Instead of 
	// <-- CNXN-RELEASE
	// < StartConnectionTimer >
	// --> CNXN-RELCOMP
	//     ReleaseComplete Handler runs correctly, stopping timer...
	bool m_releaseCompleteIn;

	// Bit of extra debug, so we can detect idle connections: we may put an
	// administrative thread into the app code, deleting long-term idle
	// connections.
    threeway::TimeWrap m_creationTime;
    threeway::TimeWrap m_lastActivity;
    threeway::TimerHandle m_connectionTimer;
};

#endif
