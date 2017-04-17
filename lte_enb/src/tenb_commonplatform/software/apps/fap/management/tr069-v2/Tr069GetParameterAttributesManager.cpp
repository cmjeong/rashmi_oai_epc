///////////////////////////////////////////////////////////////////////////////
//
// GetParameterAttributesManager.cpp
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
#include "Tr069GetParameterAttributesManager.h"
#include "Tr069DataModelManager.h"
#include "Tr069TransactionSession.h"
#include "SoapEnvelope.h"
#include "SoapFault.h"

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
GetParameterAttributesManager::GetParameterAttributesManager()
{
}

GetParameterAttributesManager::~GetParameterAttributesManager()
{
}

void GetParameterAttributesManager::HandleGetParameterAttributes( Tr069FsmInterface & transactionSessionFsm, const RpcGetParameterAttributes & rpcGetParameterAttributes )
{
    DataModelManager & paramMgr = DataModelManager::GetInstance();
    AttributeList parameterList;

    const ParameterNames & parameterNames = rpcGetParameterAttributes.GetParameters();
	const std::string cwmpId = rpcGetParameterAttributes.GetCwmpId();
	
    ParameterNames faultParameterNames;

    for(ParameterNames::const_iterator it = parameterNames.begin(); it != parameterNames.end(); ++it)
    {
        string parameterName = *it;

        AttributeList additionalAttributeList;

        paramMgr.AddParameterToAttributeList(parameterName, additionalAttributeList);

        if(additionalAttributeList.QueryValid())
        {
            parameterList.AppendParameters(additionalAttributeList);
        }
        else
        {
            faultParameterNames.push_back(parameterName);
        }
    }

    if(parameterList.QueryValid() && faultParameterNames.empty() )
    {
        SendGetParameterAttributesConfirm(transactionSessionFsm, parameterList, cwmpId);
    }
    else
    {
        SendGetParameterAttributesReject(transactionSessionFsm,faultParameterNames, cwmpId );
    }
}


void GetParameterAttributesManager::SendGetParameterAttributesReject(Tr069FsmInterface & transactionSessionFsm, const ParameterNames & faultParameterNames, std::string cwmpId )
{
    SoapFault soapFault;
	std::string timeout = Tr069Application::GetInstance().GetSoapTimeout();

    if(faultParameterNames.empty())
    {
        soapFault.m_cmwpFault.m_faultCode   = 9003;
        soapFault.m_cmwpFault.m_faultString = "Invalid Arguments";
    }
    else
    {
        stringstream ss;
        ss << "Invalid Parameter Names [" << faultParameterNames.size() << "], including: " << faultParameterNames.at(0);

        soapFault.m_cmwpFault.m_faultCode   = 9005;
        soapFault.m_cmwpFault.m_faultString = ss.str();
    }

    SoapEnvelope envelope(soapFault);
	envelope.soapheader.SetCwmpId(cwmpId);
	envelope.soapheader.SetSoapTimeout(timeout);

    shared_ptr<HttpPostRequest> httpPostRequest(new HttpPostRequest( envelope ) );
    transactionSessionFsm.HandleEvent(httpPostRequest);
}

void GetParameterAttributesManager::SendGetParameterAttributesConfirm( Tr069FsmInterface & transactionSessionFsm, const AttributeList & parameterList, std::string cwmpId)
{
    std::ostringstream txGetParameterAttributesResponse;
    std::string timeout = Tr069Application::GetInstance().GetSoapTimeout();
    txGetParameterAttributesResponse << "<soap-env:Envelope"
            << tr069::tr069XmlNsHeaderPreamble << ">"
	"<soap-env:Header>"
	"<cwmp:ID soap-env:mustUnderstand=\"1\">"<< cwmpId <<"</cwmp:ID>";
	if(timeout.compare("")!=0)
	{
        txGetParameterAttributesResponse <<
        "<cwmp:SessionTimeout soap-env:mustUnderstand=\"0\">"<< timeout <<"</cwmp:SessionTimeout>";
	}
	txGetParameterAttributesResponse <<
	"</soap-env:Header>"
        "<soap-env:Body>"
        "<cwmp:GetParameterAttributesResponse>" <<
        parameterList.Xmlise() <<
        "</cwmp:GetParameterAttributesResponse>"
        "</soap-env:Body>"
        "</soap-env:Envelope>";

    shared_ptr<HttpPostRequest> setParameterAttributesResponse(new HttpPostRequest( txGetParameterAttributesResponse.str().c_str()) );
    transactionSessionFsm.HandleEvent(setParameterAttributesResponse);
}

}



