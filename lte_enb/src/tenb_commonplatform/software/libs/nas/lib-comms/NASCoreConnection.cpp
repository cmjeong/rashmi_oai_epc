///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// NASCoreConnection.cpp
//
// Manage a single Connection between the RRCLinkLayer and the NAS-CORE.
// Sort of the equivalent of an A-Interface connection, only much more
// lightweight.
//
// Copyright � 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////
//CODE_CLEANUP
#include <string.h>
#include <lib-system/NASTrace.h>
#include <lib-comms/NASMessage.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "lib-comms/NASCoreConnection.h"

///////////////////////////////////////////////////////////////////////////////
// Local Definitions
///////////////////////////////////////////////////////////////////////////////

// An arbitrary, 3 Way Networks value of 10 seconds.  No activity on the
// link for this period and we bail out on the connection and tear down
// any allocated resources.
static const u32 CORE_LINK_TIMEOUT = 3000;

///////////////////////////////////////////////////////////////////////////////
// Class: NASCoreConnection
// Desc : Class that handles a single Connection session between the
//        RRC Link Layer and the CORE.
///////////////////////////////////////////////////////////////////////////////
NASCoreConnection::NASCoreConnection () :
	m_sourceApp (NAS_UNKNOWN),
	m_destApp (NAS_UNKNOWN),
	m_localCOREConnectionId (ConnectionIdentifierUnused),
	m_remoteCOREConnectionId (ConnectionIdentifierUnused),
	m_dataHandler (NULL),
	m_releaseHandler (NULL),
	m_failureHandler(),
	m_releaseCompleteIn(),
	m_connectionTimer()
{
    // TODO - add replace TimedConnection timers
}

NASCoreConnection::~NASCoreConnection ()
{
}

void NASCoreConnection::HardwireCallbacks (NAS_CNXNDATA dataHandler, NAS_CNXNREL releaseHandler, NAS_CNXNFAIL failureHandler)
{
	m_dataHandler = dataHandler;
	m_releaseHandler = releaseHandler;
	m_failureHandler = failureHandler;
}

void NASCoreConnection::InitCOREConnection (NASApp sourceApp, NASApp destApp, CORE_ConnectionIdentifier localConnId, CORE_ConnectionIdentifier remoteConnId)
{
	NAS_ENTER ();
	NAS_TRACE ("Initialising NASCoreConnection LocalId", (u32) localConnId);
	NAS_TRACE ("                              RemoteId", (u32) remoteConnId);

	m_sourceApp = sourceApp;
	m_destApp = destApp;
	m_localCOREConnectionId = localConnId;
	m_remoteCOREConnectionId = remoteConnId;
	m_releaseCompleteIn = false;

	NAS_EXIT ();
}

void NASCoreConnection::TermCOREConnection (bool invokeReleaseHandler)
{
	NAS_ENTER ();
	NAS_TRACE ("Clearing NASCoreConnection LocalId", (u32) m_localCOREConnectionId);
	NAS_TRACE ("                          RemoteId", (u32) m_remoteCOREConnectionId);

    StopConnectionTimer();

	if (invokeReleaseHandler)
	{
		NAS_TRACE ("Invoking CNXNREL CallBack For Link", (u32) m_localCOREConnectionId);
		(m_releaseHandler) (
			m_localCOREConnectionId);
	}//end if

	m_sourceApp = NAS_UNKNOWN;
	m_destApp = NAS_UNKNOWN;
	m_localCOREConnectionId = ConnectionIdentifierUnused;
	m_remoteCOREConnectionId = ConnectionIdentifierUnused;

	NAS_EXIT ();
}

void NASCoreConnection::DeleteFailedCnxn ()
{
	NAS_ENTER ();
	NAS_TRACE ("Deleting Instance Data on FAILED Link", (u32) m_localCOREConnectionId);

    StopConnectionTimer();

	// Give leaf class a notification that the connection is gone.
	(m_failureHandler)
		(m_localCOREConnectionId);

	m_sourceApp = NAS_UNKNOWN;
	m_destApp = NAS_UNKNOWN;
	m_localCOREConnectionId = ConnectionIdentifierUnused;
	m_remoteCOREConnectionId = ConnectionIdentifierUnused;

	NAS_EXIT ();
}

CORE_ConnectionIdentifier NASCoreConnection::GetLocalConnectionId () const
{
	NAS_ENTER();
	NAS_RETURN(m_localCOREConnectionId);
}

CORE_ConnectionIdentifier NASCoreConnection::GetRemoteConnectionId () const
{
	NAS_ENTER();
	NAS_RETURN(m_remoteCOREConnectionId);
}

const threeway::TimeWrap &NASCoreConnection::GetTimeOfLastActivity () const
{
	NAS_ENTER ();
	NAS_RETURN (m_lastActivity);
}

bool NASCoreConnection::CnxnAllocated () const
{
	NAS_ENTER();
	NAS_RETURN(m_localCOREConnectionId != ConnectionIdentifierUnused);
}

bool NASCoreConnection::CnxnAvailable () const
{
	NAS_ENTER();
	NAS_RETURN(m_localCOREConnectionId == ConnectionIdentifierUnused);
}

void NASCoreConnection::ReceiveCNXNRequest (const COREMessageStructure &nasCoreMsg)
{
	NAS_ENTER();
	NAS_TRACE("Received CNXN-REQ: RemoteID Number", (u32) m_remoteCOREConnectionId);
	NAS_TRACE("                   LocalID Number", (u32) m_localCOREConnectionId);

	// Means the create time will be the time at which the original
	// connection request was received.
	UpdateCreateTime ();

	// First of all, acknowledge that we have accepted the connection: the RRC
	// Link Layer is waiting for this notification.
	COREMessageStructure msgStruct;
	msgStruct.sourceConnectionId = m_localCOREConnectionId;
	msgStruct.destConnectionId = m_remoteCOREConnectionId;
	msgStruct.thePayload.messageType = NAS_PAYLOAD_EMPTY;
	NASMessage nasMessage (
		m_sourceApp,
		m_destApp,
		NAS_CORE_CNXN_CONF,
		(u8 *) &msgStruct,
		sizeof (COREMessageStructure));

	NAS_MSG (" Sending CNXN-CNF");
	NAS_TRACE (" From LocalConnID", (u32) m_localCOREConnectionId);
	NAS_TRACE (" To RemoteConnId", (u32) m_remoteCOREConnectionId);

	nasMessage.SendMessage ();

	// Now, do we have an associated L3 Message payload to handle?
	if (nasCoreMsg.thePayload.messageType != NAS_PAYLOAD_EMPTY)
	{
		// Yes, deal with it then.  Delegated to the leaf class that must
		// provide a data handling function.
		ReceiveCNXNData (nasCoreMsg);
	}//end if

	NAS_EXIT();
}

void NASCoreConnection::ReceiveCNXNConfirm (const COREMessageStructure &nasCoreMsg)
{
	NAS_ENTER ();

	// We will have started the connection timer when the CNXN_REQ was
	// sent to the CORE.
	StopConnectionTimer ();

	// Pull out ID that will be destination for all following
	// messages on this link and we are done.
	m_remoteCOREConnectionId = nasCoreMsg.sourceConnectionId;

	NAS_TRACE ("Received CNXN-CNF: RemoteID Number", (u32) m_remoteCOREConnectionId);
	NAS_TRACE ("                   LocalID Number", (u32) m_localCOREConnectionId);

	// Self explanatory?
	m_lastActivity.Touch ();

	NAS_EXIT ();
}

void NASCoreConnection::ReceiveCNXNRefuse (const COREMessageStructure &nasCoreMsg)
{
	NAS_ENTER ();
	NAS_TRACE (" Received CNXN-REF At LocalId", (u32) m_localCOREConnectionId);
	NAS_TRACE ("                   From RemoteId", (u32) m_remoteCOREConnectionId);

	// We will have started the connection timer when the CNXN_REQ was
	// sent to the CORE.
	StopConnectionTimer ();

	// Self explanatory?
	m_lastActivity.Touch ();

	// Nothing else to do: CORE_LinkManager will tidy up this object.

	NAS_EXIT ();
}

void NASCoreConnection::ReceiveCNXNData (const COREMessageStructure &nasCoreMsg)
{
	NAS_ENTER ();
	NAS_TRACE ("Received CNXN-DATA: RemoteID Number", (u32) m_remoteCOREConnectionId);
	NAS_TRACE ("                    LocalID Number ", (u32) m_localCOREConnectionId);

	// Self explanatory?
	m_lastActivity.Touch ();

	(m_dataHandler) (
		m_localCOREConnectionId,
		nasCoreMsg.thePayload);

	NAS_EXIT ();
}

void NASCoreConnection::ReceiveCNXNRelease (const COREMessageStructure &nasCoreMsg)
{
	NAS_ENTER ();
	NAS_TRACE (" Received CNXN-REL At LocalId", (u32) m_localCOREConnectionId);
	NAS_TRACE ("                   From RemoteId", (u32) m_remoteCOREConnectionId);

	// Self explanatory?
	m_lastActivity.Touch ();

	// Higher level management class is handling the maps and memory allocation,
	// so all we need to do here is notify the RRC Link Layer that it can safely
	// release its own resources (i.e. the connection is released successfully).
	COREMessageStructure msgStruct;
	msgStruct.sourceConnectionId = m_localCOREConnectionId;
	msgStruct.destConnectionId = m_remoteCOREConnectionId;
	msgStruct.thePayload.messageType = NAS_PAYLOAD_EMPTY;
	NASMessage nasMessage (
		m_sourceApp,
		m_destApp,
		NAS_CORE_CNXN_RELCOMP,
		(u8 *) &msgStruct,
		sizeof (COREMessageStructure));

	NAS_MSG (" Sending CNXN-RELCOMP");
	nasMessage.SendMessage ();
	NAS_EXIT ();
}

void NASCoreConnection::ReceiveCNXNReleaseComplete (const COREMessageStructure &nasCoreMsg)
{
	NAS_ENTER ();
	NAS_MSG (" Received CNXN-RELCOMP");

	NAS_MSG ("Setting RELCOMP Received Flag");
	m_releaseCompleteIn = true;

	// In response to our CNXN_RELEASE that was sent to the NAS CORE.
	StopConnectionTimer ();

	// Self explanatory?
	m_lastActivity.Touch ();

	// Nothing else to do: LinkManager class responsible for
	// all memory tidying.

	NAS_EXIT ();
}

void NASCoreConnection::SendNASMessage (const NASAppPayload &thePayload)
{
	NAS_ENTER ();

	COREMessageStructure msgStruct;
	msgStruct.sourceConnectionId = m_localCOREConnectionId;
	msgStruct.destConnectionId = m_remoteCOREConnectionId;
	memcpy (&msgStruct.thePayload, &thePayload, sizeof (NASAppPayload));

	NAS_TRACE("Sending From LocalCOREId", m_localCOREConnectionId);
	NAS_TRACE(" To RemoteCOREId", m_remoteCOREConnectionId);
	if (m_remoteCOREConnectionId == ConnectionIdentifierUnused)
	{
		NAS_MSG("  CNXN-REQ");
		NASMessage pduForCORE (
			m_sourceApp,
			m_destApp,
			NAS_CORE_CNXN_REQ,
			(u8 *) &msgStruct,
			sizeof (COREMessageStructure));
		pduForCORE.SendMessage ();

		// Check this out: I've seen this behaviour...
		//
		// CNXN REQUEST --->
		//                  <--- CNXN CONFIRM
		//                       * StopConnectionTimer *
		//                       This thread sending REQUEST is interrupted by the received
		//                       CONFIRM and handles it.  So, we have already run the logic
		//                       to StopConnectionTimer.  Basically it's a race, so check
		//                       if the CONFIRM is already in before starting the timer.
		// * StartConnectionTimer *
		// Without a subsequent CONFIRM
		// message this timer will expire
		// at some arbitrary point in the
		// procedure and blow away the link.

		if (m_remoteCOREConnectionId == ConnectionIdentifierUnused)
		{
			NAS_MSG ("No CONFIRM In Yet: Starting Timer");
			StartConnectionTimer ();
		}
		else
		{
			NAS_MSG ("CONFIRM Already Received");
		}//end if

		// Means the create time will be the time at which the original
		// connection request was received.
		UpdateCreateTime ();
	}
	else
	{
		NAS_MSG("  CNXN-DATA");
		NASMessage pduForCORE (
			m_sourceApp,
			m_destApp,
			NAS_CORE_CNXN_DATA,
			(u8 *) &msgStruct,
			sizeof (COREMessageStructure));
		pduForCORE.SendMessage ();

		// No message timer in this case: once the 'link' is up, message
		// transport is best effort.  The normal GSM / 3G timers will recover
		// the situation now if the link fails.
	}//end if

	// Self explanatory?
	m_lastActivity.Touch ();

	NAS_EXIT ();
}

void NASCoreConnection::SendNASRelease ()
{
	NAS_ENTER ();

	COREMessageStructure msgStruct;
	msgStruct.sourceConnectionId = m_localCOREConnectionId;
	msgStruct.destConnectionId = m_remoteCOREConnectionId;
	msgStruct.thePayload.messageType = NAS_PAYLOAD_EMPTY;

	NASMessage nasCORERelease (
		m_sourceApp,
		m_destApp,
		NAS_CORE_CNXN_REL,
		(u8 *) &msgStruct,
		sizeof (COREMessageStructure));

	// Off the release request goes to the NAS Core.
	NAS_TRACE ("CNXN-REL Sent From", (u32) m_localCOREConnectionId);
	NAS_TRACE ("         Sent To", (u32) m_remoteCOREConnectionId);

	// mja Check flag here as we have seen the following behaviour...
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
	//
	// So as the RELCOMP has already come in, the timer is started erroneously...
	nasCORERelease.SendMessage ();
	m_lastActivity.Touch ();

	// TODO Should this be a semaphore?  I think the flag solution will be fine.
	if (m_releaseCompleteIn == false)
	{
		// And start the timer to make sure we still close the link down
		// if the message does not receive a response.
		StartConnectionTimer ();
	}
	else
	{
		NAS_MSG ("No Release Time Started: RELCOMP Already Received");
	}//end if

	NAS_EXIT ();
}

void NASCoreConnection::AgeConnection (u32 agePeriod)
{
	NAS_ENTER ();

	threeway::TimeWrap timeNow;
	u32 minutesElapsed = m_lastActivity.GetSecondsElapsed() / 60;

	NAS_TRACE ("Current Time Is", timeNow);
	NAS_TRACE ("Last Activity Was At", m_lastActivity);
	NAS_TRACE (
		"So The Number Of Minutes Where Nothing Happened Is",
		minutesElapsed);

	if (minutesElapsed >= agePeriod)
	{
		// Very long time since any activity on this link: we
		// will manually erase all knowledge of it.
		DeleteFailedCnxn ();
	}//end if

	NAS_EXIT ();
}

void NASCoreConnection::GetObjectDescription (char *debugText) const
{
	char createTime[64] = { '\0', }, lastTouch[64] = { '\0', };
	m_creationTime.GetDateStr (createTime, sizeof(createTime));
	m_lastActivity.GetDateStr (lastTouch, sizeof(lastTouch));

	// Add private information to the basics.
	char debugInf[1024] = { '\0', };

	snprintf (
		debugInf,
        sizeof(debugInf),
		"\nNASCoreConnection Object:\n Created %s\n Touched %s\n  LocalCORE-ConnId %" PRIu32 "\n  RemoteCORE-ConnId %" PRIu32 "\n",
		createTime,
		lastTouch,
		m_localCOREConnectionId,
		m_remoteCOREConnectionId);

	strcat (debugText, debugInf);
}

void NASCoreConnection::GetMenu (NASString& debugMenu) const
{
	snprintf (
		(char*)debugMenu, debugMenu.GetSize(),
		"NASCoreConnection Link Menu\n \
		=============================\n \
		\n \
		1: Show Link Status\n \
		2: Drop Link\n");
}

bool NASCoreConnection::HandleMenuOption (char inChar, NASString& resultText) const
{
	bool optionHandled;
	switch (inChar)
	{
	case '1':
		{
			snprintf (
				(char*)resultText, resultText.GetSize(),
				"Source App              : %u\n\
				Dest App                 : %u\n\
				Local Connection Number  : %" PRIu32 "\n\
				Remote Connection Number : %" PRIu32 "\n",
				m_sourceApp,
				m_destApp,
				m_localCOREConnectionId,
				m_remoteCOREConnectionId);

			optionHandled = true;
		}
		break;

	case '2':
		{
			snprintf (
	            (char*)resultText, resultText.GetSize(),
				"Drop Request Issued For CORE Link Number %" PRIu32 "\n",
				m_localCOREConnectionId);

			optionHandled = true;

			// Temporary removal of const for this debug call.
			((NASCoreConnection *) this)->SendNASRelease ();
		}
		break;

	default:
		{
			optionHandled = false;

		}
	}//end switch

	return optionHandled;
}

void NASCoreConnection::StartConnectionTimer ()
{

}

void NASCoreConnection::StopConnectionTimer ()
{

}

void NASCoreConnection::UpdateCreateTime ()
{

}

void NASCoreConnection::OpenConnection ()
{
    NAS_ENTER();
    NAS_EXIT();
}

void NASCoreConnection::CloseConnection ()
{
    NAS_ENTER();

    // stop & delete connection timer

    NAS_EXIT();
}

threeway::TimerHandle NASCoreConnection::GetTimerHandle () const
{
    NAS_ENTER();
    NAS_RETURN(m_connectionTimer);
}
