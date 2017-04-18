///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// NASMessage.cpp
//
// Class wrapper handling message content that will be sent between the
// various 3Way applications.
//
// Copyright � 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <stdio.h>
#include <lib-system/NASTrace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "NASMessage.h"
#include "NASTransport.h"

///////////////////////////////////////////////////////////////////////////////
// Local Definitions
///////////////////////////////////////////////////////////////////////////////

static const s8 NAS_BUFFER_EMPTY[] = { "BUFFER-EMPTY" };

NASTransport s_rrcLinkLayerTransport;
NASTransport s_coreTransport;
NASTransport s_hlrTransport;
NASTransport s_dbxTransport;
NASTransport s_sipTransport;
NASTransport s_smscTransport;
NASTransport s_ggsnTransport;
NASTransport s_iuTransport;
NASTransport s_portalTransport;

///////////////////////////////////////////////////////////////////////////////
//
// Class: NASMessage
// Desc : Manage packing user data into a simple structure and sending it
//        to the specified application.
//
///////////////////////////////////////////////////////////////////////////////
NASMessage::NASMessage (NASApp msgSrc, NASApp msgDest, NASAppMessage msgType, const u8 *msgBuffer, u32 msgLength) :
    m_nasMessage()
{
	NAS_ENTER()

	// Can't put these into argument list as it's a structure.
	m_nasMessage.appSource = msgSrc;
	m_nasMessage.appDestination = msgDest;
	m_nasMessage.messageLength = msgLength;
	m_nasMessage.nasMessageType = msgType;

	// Really just for debugging help, so we can easily tell if
	// the user of this mechanism has forgotten to populate
	// the message payload.
	if (msgLength == 0)
	{
		memcpy (&m_nasMessage.nasMessage[0], NAS_BUFFER_EMPTY, sizeof (NAS_BUFFER_EMPTY));
	}
	else if (msgLength <= sizeof(m_nasMessage.nasMessage))
	{
		memcpy (&m_nasMessage.nasMessage[0], msgBuffer, msgLength);
	}
	else
	{
	    TRACE_LEV(TRACE_WARNING, "NASMessage: msgLength too big in constructor", msgLength)
	}//end if

	NAS_EXIT()
}

NASMessage::NASMessage (const NASMessageStructure &nasMsg)
{
	NAS_ENTER();
	memcpy (&m_nasMessage, &nasMsg, sizeof (NASMessageStructure));
	NAS_EXIT();
}

NASMessage::~NASMessage ()
{
	NAS_ENTER();
	NAS_EXIT();
}

void NASMessage::SendMessage ()
{
	NAS_ENTER();

	switch (m_nasMessage.appDestination)
	{
	case NAS_CORE:
		{
			NAS_MSG ("Sending To NAS Core");
			s_coreTransport.SendMessage (*this);
		}
		break;

	case NAS_HLR:
		{
			NAS_MSG ("Sending To NAS HLR");
			s_hlrTransport.SendMessage (*this);
		}
		break;

	case NAS_RRCLINKLAYER:
		{
			NAS_MSG ("Sending To NAS RRC Link Layer");
			s_rrcLinkLayerTransport.SendMessage (*this);
		}
		break;

	case NAS_SMSC:
		{
			NAS_MSG ("Sending To NAS SMSC");
			s_smscTransport.SendMessage (*this);
		}
		break;

	case NAS_GGSN:
		{
			NAS_MSG ("Sending To NAS GGSN");
			s_ggsnTransport.SendMessage (*this);
		}
		break;

    case NAS_IU:
        {
            NAS_MSG ("Sending To NAS Iu Interface");
            s_iuTransport.SendMessage (*this);
        }
        break;

	case NAS_BROADCAST:
		{
			NAS_MSG ("Sending To ALL_APPS");
			s_dbxTransport.SendMessage (*this);
			s_coreTransport.SendMessage (*this);
			s_hlrTransport.SendMessage (*this);
			s_rrcLinkLayerTransport.SendMessage (*this);
		}
		break;

	case NAS_UNKNOWN:
	default:
		{
			NAS_MSG ("Unknown DESTINATION for NASMessage: Not Sent");
		}
	}//end switch

	NAS_EXIT();
}

NASApp NASMessage::GetSource () const
{
	NAS_ENTER()
	NAS_RETURN (m_nasMessage.appSource);
}

NASApp NASMessage::GetDestination () const
{
	NAS_ENTER()
	NAS_RETURN (m_nasMessage.appDestination);
}

NASAppMessage NASMessage::GetMessageType () const
{
	NAS_ENTER();
	NAS_RETURN (m_nasMessage.nasMessageType);
}

const u8 *NASMessage::GetMessage (u32 &msgLength) const
{
	NAS_ENTER()
	msgLength = m_nasMessage.messageLength;
	NAS_RETURN (&m_nasMessage.nasMessage[0]);
}

const NASMessageStructure &NASMessage::GetMessage () const
{
	NAS_ENTER()
	NAS_RETURN (m_nasMessage);
}

void NASMessage::FillMessage (const u8 *msgBuffer, u32 msgLength)
{
	NAS_ENTER();

	// Preconditions.
	RSYS_ASSERT(msgLength <= sizeof(m_nasMessage.nasMessage));

	if ((msgLength > 0) && (msgBuffer != NULL))
	{
		memcpy (m_nasMessage.nasMessage, msgBuffer, msgLength);
		m_nasMessage.messageLength = msgLength;
	}//end if

	NAS_EXIT();
}
