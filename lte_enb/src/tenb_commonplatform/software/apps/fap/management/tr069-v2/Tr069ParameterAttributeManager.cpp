///////////////////////////////////////////////////////////////////////////////
//
// ParameterAttributeManager.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <system/Trace.h>
#include <system/SetParameterAttribute.h>
#include <messaging/messages/common/OamActionReq.h>
#include <mib-common/messages/MibValidateAttributesReq.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069Application.h"
#include "Tr069ParameterAttributeManager.h"
#include "Tr069DataModelManager.h"
#include "Tr069TransactionSession.h"
#include "SoapEnvelope.h"
#include "SoapFault.h"
#include "Tr069ParameterValueChangeNotificationManager.h"

using namespace std;
using namespace threeway;
using namespace tr069;

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////
namespace tr069
{

/**
 * Implement SerialisableFactory.  Used when we read
 * objects from the alarm log file(s).
 */
ParameterAttributeManager::ParameterAttributeManager( const char * fileName ) :
        m_setParameterAttributesHistory(fileName, *this, true)
{
}

ParameterAttributeManager::~ParameterAttributeManager()
{
}

shared_ptr<Serialisable> ParameterAttributeManager::GetSerialisable(
        u32 serialisationId,
        const u8* serialisedData,
        u32 serialisedDataLen)
{
    shared_ptr<Serialisable> setParameterAttribute;

    if(serialisationId == SERIALISATION_ID_SET_PARAMETER_ATTRIBUTE)
    {
        setParameterAttribute.reset(new SetParameterAttribute);

        setParameterAttribute->DeSerialise(serialisedData, serialisedDataLen);
    }

    RETURN(setParameterAttribute);
}

void ParameterAttributeManager::HandleSetParamAttributes( Tr069FsmInterface & transactionSessionFsm, const RpcSetParameterAttribute & rpcSetParameterAttribute )
{
    bool setAttrOk = true;
	std::string cwmpid;

    SetParameterAttributeNotifications span;
    SetParameterAttributeNotification *notif;

    DataModelManager::GetInstance().SetParamterAttribute(rpcSetParameterAttribute, span);
	cwmpid = rpcSetParameterAttribute.GetCwmpId();

    if (!span.empty())
    {
       setAttrOk = true;
    }
    else
    {
       setAttrOk = false;
    }
    TRACE_PRINTF("SetParameterAttributes: %s", span.ToString().c_str() );

    for ( u32 idx = 0; idx < span.GetSizeOfSetParameterAttributeNotifications(); idx++ )
    {
       notif = span.GetParamterAttribute(idx);
       Tr069ParameterValueChangeNotificationManager::GetInstance().SetParamterAttributes(notif->GetName().c_str(), (ExtDMAttrNotificationType)notif->GetNotification());
    }

    if(setAttrOk)
    {
        SendSetParametersConfirm(transactionSessionFsm, cwmpid);
    }
    else
    {
        SendSetParametersAttributeReject(transactionSessionFsm, cwmpid);
    }
}


void ParameterAttributeManager::SendSetParametersAttributeReject(Tr069FsmInterface & transactionSessionFsm, std::string cwmpId)
{
	std::string timeout = Tr069Application::GetInstance().GetSoapTimeout();
    SoapFault soapFault;

    soapFault.m_cmwpFault.m_faultCode   = 9009;
    soapFault.m_cmwpFault.m_faultString = "Notification request rejected";

    SoapEnvelope envelope(soapFault);
	envelope.soapheader.SetCwmpId(cwmpId);
	envelope.soapheader.SetSoapTimeout(timeout);

    shared_ptr<HttpPostRequest> httpPostRequest(new HttpPostRequest( envelope ) );
    transactionSessionFsm.HandleEvent(httpPostRequest);
}

void ParameterAttributeManager::SendSetParametersConfirm( Tr069FsmInterface & transactionSessionFsm, std::string cwmpId )
{
   std::string timeout = Tr069Application::GetInstance().GetSoapTimeout();
   std::ostringstream txSetParameterAttributesResponse;
   txSetParameterAttributesResponse << "<soap-env:Envelope" << tr069::tr069XmlNsHeaderPreamble << ">"
      "<soap-env:Header>"
      "<cwmp:ID soap-env:mustUnderstand=\"1\">"<< cwmpId <<"</cwmp:ID>";
   if(timeout.compare("") != 0)
   {
      txSetParameterAttributesResponse << 
         "<cwmp:SessionTimeout soap-env:mustUnderstand=\"0\">" <<timeout<<"</cwmp:SessionTimeout>";
   }
   txSetParameterAttributesResponse <<
      "</soap-env:Header>"
      "<soap-env:Body>"
      "<cwmp:SetParameterAttributesResponse/>"
      "</soap-env:Body>"
      "</soap-env:Envelope>";

   shared_ptr<HttpPostRequest> setParameterAttributesResponse(new HttpPostRequest( txSetParameterAttributesResponse.str().c_str()) );
   transactionSessionFsm.HandleEvent(setParameterAttributesResponse);
}

}

