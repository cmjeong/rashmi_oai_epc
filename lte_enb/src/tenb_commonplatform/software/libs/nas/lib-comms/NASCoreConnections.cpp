///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// NASCoreConnections.cpp
//
// Application class that maintains a container of NASCoreConnection objects.
//
// Copyright � 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <stdlib.h>

#include <system/TimerInterface.h>

#include <lib-system/NASTrace.h>
#include <NASException.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "NASCoreConnections.h"
#include "NASCoreConnection.h"
#include "NASMessage.h"

using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Local Definitions
///////////////////////////////////////////////////////////////////////////////

u32 NASCoreConnections::sm_nextConnectionId = 0;

///////////////////////////////////////////////////////////////////////////////
// Class: NASCoreConnections
// Desc : Overall management class maintaining links between
// 3 Way applications.
///////////////////////////////////////////////////////////////////////////////
NASCoreConnections::NASCoreConnections (NASApp sourceApp, NASApp destApp, NAS_CNXNDATA dataCallback, NAS_CNXNREL releaseCallback, NAS_CNXNFAIL failureCallback, NAS_CNXNLESSDATA broadcastCallback) :
	m_sourceApp (sourceApp),
	m_destApp (destApp),
	m_broadcastHandler (broadcastCallback),
	m_activeConnectionCount (0)
{
	NAS_ENTER();

	// Wire up the callback functions immediately: no sense in waiting, or repeating
	// the job every time we get a new connection.
	for (u32 i=0;i<NUMBER_OF_NAS_LINKS;i++)
		m_coreConnections[i].HardwireCallbacks (dataCallback, releaseCallback, failureCallback);

	NAS_EXIT();
}

NASCoreConnections::~NASCoreConnections ()
{
	NAS_ENTER();
	NAS_EXIT();
}

void NASCoreConnections::TheEndIsNigh ()
{
	NAS_ENTER();
	for (u32 i=0;i<NUMBER_OF_NAS_LINKS;i++)
	{
		if (m_coreConnections[i].CnxnAllocated ())
		{
			m_coreConnections[i].SendNASRelease ();
		}//end if
	}//end for
	NAS_EXIT();
}

void NASCoreConnections::StopConnectionEngine ()
{
	NAS_ENTER();

	// Make sure all timers are stopped and deleted: doesn't actually
	// involve any other signalling (to the remote end, for example).
	// That should have been done before now.
	for (u32 i=0;i<NUMBER_OF_NAS_LINKS;i++)
		m_coreConnections[i].CloseConnection ();

	NAS_EXIT();
}

u32 NASCoreConnections::GetConnectionCount () const
{
	NAS_ENTER ();
	NAS_RETURN (m_activeConnectionCount);
}

const NASCoreConnection &NASCoreConnections::GetConnection (u32 cnxnIndex) const
{
	NAS_ENTER ();

	if (cnxnIndex < NUMBER_OF_NAS_LINKS)
	{
		NAS_RETURN (m_coreConnections[cnxnIndex]);
	}//end if

	NAS_EXIT ();
	throw NASException (__FILE__, __LINE__, "Connection Not Found In GetConnection");
}

void NASCoreConnections::NAS_Rx (NASAppMessage msgType, const COREMessageStructure &nasCoreMsg)
{
	NAS_ENTER();

	switch (msgType)
	{
	case NAS_CORE_CNXN_REQ:
		{
			// New connection estabishment request from the remote app: first
			// try to obtain a local ID number for this connection (we have
			// imposed a software limit on the maximum number - no need to
			// be silly about these things!).
			NASCoreConnection *newCnxn = NULL;
			for (u32 i=0;i<NUMBER_OF_NAS_LINKS;i++)
			{
				NASCoreConnection &nextCnxn = m_coreConnections[i];
				if (nextCnxn.CnxnAvailable ())
				{
					// Found an item available for use: mark it and initialise
					// with our instance data.
					nextCnxn.InitCOREConnection (
						m_sourceApp,
						m_destApp,
						sm_nextConnectionId++,
						nasCoreMsg.sourceConnectionId);

					// Keep our internal tracker up to date.
					m_activeConnectionCount++;
					newCnxn = &nextCnxn;
					break;
				}//end if
			}//end for

			if (newCnxn != NULL)
			{
				newCnxn->ReceiveCNXNRequest (nasCoreMsg);
			}
			else
			{
				NAS_MSG("NASCoreConnections: Rejecting NASLink Request (Congestion)");

				COREMessageStructure coreMsg;
				coreMsg.destConnectionId = nasCoreMsg.sourceConnectionId;
				coreMsg.sourceConnectionId = ConnectionIdentifierUnused;
				coreMsg.thePayload.messageType = NAS_PAYLOAD_EMPTY;

				NASMessage nasLinkReject (
					m_sourceApp,
					m_destApp,
					NAS_CORE_CNXN_REF,
					(u8 *) &coreMsg,
					sizeof (COREMessageStructure));
				nasLinkReject.SendMessage ();
			}//end if
		}
		break;

	case NAS_CORE_CNXN_CONF:
		{
			// Confirmation of establishment of a CNXN_REQ from the MSC.
			NASCoreConnection *localCnxn = FindConnection (
				nasCoreMsg.destConnectionId);
			if (localCnxn != NULL)
			{
				localCnxn->ReceiveCNXNConfirm (nasCoreMsg);
			}
			else
			{
				NAS_TRACE (
					"NASCoreConnections ERROR: Unknown CORE Connection Id",
					nasCoreMsg.destConnectionId);
			}//end if
		}
		break;

	case NAS_CORE_CNXN_REF:
		{
			// MSC is (probably) congested: it has refused our request.
			NAS_TRACE ("Received CNXN-REF For ConnId", (u32) nasCoreMsg.destConnectionId);
			NASCoreConnection *localCnxn = FindConnection (
				nasCoreMsg.destConnectionId);
			if (localCnxn != NULL)
				localCnxn->ReceiveCNXNRefuse (nasCoreMsg);

			FreeCoreConnection (nasCoreMsg.destConnectionId);
		}
		break;

	case NAS_CORE_CNXN_DATA:
		{
			// Simple message pass-through on an existing link.  Leaf class has
			// the implementation of the ReceiveCNXNData member.
			NASCoreConnection *theCnxn = FindConnection (
				nasCoreMsg.destConnectionId);
			if (theCnxn != NULL)
				theCnxn->ReceiveCNXNData (nasCoreMsg);
		}
		break;

	case NAS_CORE_CNXN_REL:
		{
			// NAS has dropped a connection: free local resources.
			// Final connection clearing at the local side: drop local
			// resources here, then notify remote side.
			NAS_MSG("NASCoreConnections: Release NASLink Request");

			// Give leaf class a shot at handling the message, if necessary.
			NASCoreConnection *theCnxn = FindConnection (
				nasCoreMsg.destConnectionId);
			if (theCnxn != NULL)
			{
				// Delete all resources.
				theCnxn->ReceiveCNXNRelease (nasCoreMsg);
				FreeCoreConnection (nasCoreMsg.destConnectionId);
			}
			else
			{
				// Hmm, didn't find it.  Just send an immediate RELEASE COMPLETE
				// to satisfy the CORE that all is well (although it might not be!).
				NAS_MSG ("**********************************************");
				NAS_MSG ("* ERROR: Received CNXNREL For Vaporised Link *");
				NAS_MSG ("**********************************************");

				COREMessageStructure relComp;
				relComp.sourceConnectionId = nasCoreMsg.destConnectionId;
				relComp.destConnectionId = nasCoreMsg.sourceConnectionId;
				relComp.thePayload.messageType = NAS_PAYLOAD_EMPTY;

				NASMessage nasMessage (
					m_sourceApp,
					m_destApp,
					NAS_CORE_CNXN_RELCOMP,
					(u8 *) &relComp,
					sizeof (COREMessageStructure));
				nasMessage.SendMessage ();
			}//end if
		}
		break;

	case NAS_CORE_CNXN_RELCOMP:
		{
			// Connection clearing complete at the remote side: drop local
			// resources here.
			NASCoreConnection *theCnxn = FindConnection (
				nasCoreMsg.destConnectionId);
			if (theCnxn != NULL)
				theCnxn->ReceiveCNXNReleaseComplete (nasCoreMsg);

			FreeCoreConnection (nasCoreMsg.destConnectionId);
		}
		break;

	case NAS_CORE_CNXNLESS_MSG:
		{
			// Slightly different case here: this is sent when there is no
			// connection established.  An example of this would be when a PAGE
			// request is required.  Since there is no NASCoreConnection, the
			// callback handler is here.
			NAS_MSG ("Invoking CNXNLESS_DATA Callback");
			(m_broadcastHandler)
				(nasCoreMsg.thePayload);
		}
		break;

	default:
		{
			// Error case: a non-CORE message Type has been received.
			NAS_TRACE(
				"NASCoreConnections ERROR: Unknown Message Type Received",
				(u32) msgType);
		}
	}//end switch

	NAS_EXIT();
}

void NASCoreConnections::NAS_Tx (CORE_ConnectionIdentifier localConnId, const NASAppPayload &thePayload)
{
	NAS_ENTER();
	NAS_TRACE("Trying to SEND To", (u32) localConnId);

	NASCoreConnection *theCnxn = FindConnection (localConnId);
	if (theCnxn != NULL)
	{
		theCnxn->SendNASMessage (thePayload);
	}
	else
	{
		// Hmm, this is not good.  Some bad user code is leaking their
		// CORE_ConnectionIdentifier numbers.  It's a programming error, so should
		// never occur in the real world.  If it does, we trust to the message
		// timer mechanism at the user code to handle the lack of response to
		// this unsent message.
		TRACE_LEV(TRACE_WARNING, "No LocalConnection With CONN_ID ==", (u32) localConnId);

		// If it looks like this is occurring, we might need to throw an exception
		// here to notify the calling code instead...
	}//end if

	NAS_EXIT();
}

bool NASCoreConnections::NotifyTimerExpiry (TimerHandle expiredTimer)
{
	NAS_ENTER();

	// Well, let's find it and close it down.
	bool timerHandled = false;
	for (u32 i=0;i<NUMBER_OF_NAS_LINKS;i++)
	{
		if (m_coreConnections[i].GetTimerHandle () == expiredTimer)
		{
			NAS_TRACE(
				"NASCoreConnections ERROR: CORE Timer Expired",
				(u32) expiredTimer);

			// Clear all instance data associated with this connection.
			m_coreConnections[i].DeleteFailedCnxn ();

			// And we are done.
			timerHandled = true;
			break;
		}//end if
	}//end for

	NAS_RETURN (timerHandled);
}

NASCoreConnection *NASCoreConnections::FindConnection (CORE_ConnectionIdentifier connId)
{
	NAS_ENTER ();
	NAS_TRACE ("Trying To Find Connection Number", (u32) connId);

	for (u32 i=0;i<NUMBER_OF_NAS_LINKS;i++)
	{
		CORE_ConnectionIdentifier localConnId = m_coreConnections[i].GetLocalConnectionId ();

		// Although we statically allocate the 1024 links for use, this
		// check makes sure we don't bother with 'idle' links when searching
		// for a connection to use.  IT's a very small performance improvement,
		// and also prevents erroneous code from trying to send messages to
		// the invalid ConnectionIdentifierUnused number.
		if (localConnId == ConnectionIdentifierUnused)
			continue;

		NAS_TRACE ("Checking Active Connection Number", (u32) localConnId);
		if (localConnId == connId)
		{
			NAS_MSG ("And I'm Returning This One");
			NAS_RETURN (&m_coreConnections[i]);
		}//end if
	}//end for

	NAS_RETURN (NULL);
}

void NASCoreConnections::SendNASMessageNoTarget (NASApp appSource, NASApp appDest, const NASAppPayload &thePayload)
{
	NAS_ENTER ();

	COREMessageStructure msgStruct;
	msgStruct.sourceConnectionId = 0xffffffff;
	msgStruct.destConnectionId = 0xffffffff;
	memcpy (&msgStruct.thePayload, &thePayload, sizeof (NASAppPayload));

	NASMessage nasUnitData (
		appSource,
		appDest,
		NAS_CORE_CNXNLESS_MSG,
		(u8 *) &msgStruct,
		sizeof (COREMessageStructure));
	nasUnitData.SendMessage ();

	NAS_EXIT ();
}

NASCoreConnection *NASCoreConnections::RequestConnection ()
{
	NAS_ENTER();

	// First things first, do we have a connection available?  We use a
	// numeric counter to make this easy.
	NASCoreConnection *allocatedCnxn = NULL;
	if (m_activeConnectionCount == NUMBER_OF_NAS_LINKS)
	{
		// Uh oh, congestion has just been reached.  We have no
		// more links to the core available.
		NAS_MSG (" *** WARNING ***");
		NAS_MSG (" NASCoreConnections Just Breached High-Tide");

		// Nothing further we can do: returning NULL let's the
		// user code know we cannot help at this time...
	}
	else
	{
		// Find the next unused object and reserve it...
		for (u32 i=0;i<NUMBER_OF_NAS_LINKS;i++)
		{
			NASCoreConnection &nextCnxn = m_coreConnections[i];
			if (nextCnxn.CnxnAvailable ())
			{
				// Perfect, mark it as used and set member data.  Note we don't
				// know the remote side ConnId until we receive CNXN-CONF.  This is
				// normal behaviour (remote side allocates remote ids).
				nextCnxn.InitCOREConnection (
					m_sourceApp,
					m_destApp,
					sm_nextConnectionId++,
					ConnectionIdentifierUnused);

				// Keep our internal tracker up to date.
				m_activeConnectionCount++;

				// And return the allocated connection object.
				allocatedCnxn = &nextCnxn;
				break;
			}//end if
		} //end for
	}//end if

	NAS_RETURN (allocatedCnxn);
}

void NASCoreConnections::ReleaseConnection (CORE_ConnectionIdentifier localConnId)
{
	NAS_ENTER();

	// We send Release so the remote end gets notified of the drop from
	// 'this' side: no response the timer goes off OR response of
	// release-complete trigger object deletion and final link release.
	NASCoreConnection *coreCnxn = FindConnection (localConnId);
	if (coreCnxn != NULL)
		coreCnxn->SendNASRelease ();

	NAS_EXIT();
}

void NASCoreConnections::ForceConnectionDrop (CORE_ConnectionIdentifier localConnId)
{
	NAS_ENTER ();
	NAS_TRACE ("FORCING Release Of Local ConnectionId", (u32) localConnId);

	u32 i = 0;
	while (i < NUMBER_OF_NAS_LINKS)
	{
		if (m_coreConnections[i].GetLocalConnectionId () == localConnId)
		{
			m_coreConnections[i].TermCOREConnection (false);
			m_activeConnectionCount--;

			break;
		}//end if

		i++;
	}//end while

	if (i == NUMBER_OF_NAS_LINKS)
	{
		NAS_MSG ("Unable To FreeCoreConnection: It Wasn't Found");
	}//end if

	NAS_EXIT ();
}

void NASCoreConnections::FreeCoreConnection (CORE_ConnectionIdentifier localConnId)
{
	NAS_ENTER ();
	NAS_TRACE ("Releasing Local ConnectionId", (u32) localConnId);

	u32 i = 0;
	while (i < NUMBER_OF_NAS_LINKS)
	{
		if (m_coreConnections[i].GetLocalConnectionId () == localConnId)
		{
			m_coreConnections[i].TermCOREConnection (true);
			m_activeConnectionCount--;

			break;
		}//end if

		i++;
	}//end while

	if (i == NUMBER_OF_NAS_LINKS)
	{
		NAS_MSG ("Unable To FreeCoreConnection: It Wasn't Found");
	}//end if

	NAS_EXIT ();
}

void NASCoreConnections::AgeConnections (u32 agePeriod) const
{
	NAS_ENTER ();
	NAS_TRACE ("Checking Age Of Connections, Period Is", agePeriod);

	for (u32 i=0;i<NUMBER_OF_NAS_LINKS;i++)
	{
		if (m_coreConnections[i].CnxnAllocated ())
		{
			NAS_TRACE ("Checking Allocated Connection At Index", i);

			// Spot the hack: we need to remove the const temporarily,
			// as the AgeConnection on the NASCoreConnection is not
			// a const (it can't be is it needs to reset member data).  In
			// my defence, you could say that it's logically const >:-)
			((NASCoreConnections *) this)->m_coreConnections[i].AgeConnection (agePeriod);
		}//end if
	}//end for

	NAS_EXIT ();
}
