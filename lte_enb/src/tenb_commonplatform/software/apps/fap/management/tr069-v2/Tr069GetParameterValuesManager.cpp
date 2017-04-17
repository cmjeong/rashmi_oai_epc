///////////////////////////////////////////////////////////////////////////////
//
// GetParameterValuesManager.cpp
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
#include "Tr069GetParameterValuesManager.h"
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
GetParameterValuesManager::GetParameterValuesManager()
{
}

GetParameterValuesManager::~GetParameterValuesManager()
{
}

void GetParameterValuesManager::HandleGetParameterValues( Tr069FsmInterface & transactionSessionFsm, const RpcGetParameterValues & rpcGetParameterValues )
{
    DataModelManager & paramMgr = DataModelManager::GetInstance();
    ParameterList parameterList;

    const ParameterNames & parameterNames = rpcGetParameterValues.GetParameters();
	const std::string cwmpId = rpcGetParameterValues.GetCwmpId();
	
    ParameterNames faultParameterNames;

    for(ParameterNames::const_iterator it = parameterNames.begin(); it != parameterNames.end(); ++it)
    {
        string parameterName = *it;

        ParameterList additionalParameterList;

        paramMgr.AddParameterToParameterList(parameterName, additionalParameterList);

        if(additionalParameterList.QueryValid())
        {
            parameterList.AppendParameters(additionalParameterList);
        }
        else
        {
            faultParameterNames.push_back(parameterName);
        }
    }

    if(parameterList.QueryValid() && faultParameterNames.empty() )
    {
        SendGetParameterValuesConfirm(transactionSessionFsm, parameterList, cwmpId);
    }
    else
    {
        SendGetParameterValuesReject(transactionSessionFsm,faultParameterNames, cwmpId );
    }
}


void GetParameterValuesManager::SendGetParameterValuesReject(Tr069FsmInterface & transactionSessionFsm, const ParameterNames & faultParameterNames, std::string cwmpId )
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

void GetParameterValuesManager::SendGetParameterValuesConfirm( Tr069FsmInterface & transactionSessionFsm, const ParameterList & parameterList, std::string cwmpId)
{
   std::ostringstream txGetParameterValuesResponse;
   std::string timeout = Tr069Application::GetInstance().GetSoapTimeout();
   txGetParameterValuesResponse << "<soap-env:Envelope"
      << tr069::tr069XmlNsHeaderPreamble << ">"
      "<soap-env:Header>"
      "<cwmp:ID soap-env:mustUnderstand=\"1\">"<< cwmpId <<"</cwmp:ID>";
   if(timeout.compare("")!=0)
   {
      txGetParameterValuesResponse <<
         "<cwmp:SessionTimeout soap-env:mustUnderstand=\"0\">"<< timeout <<"</cwmp:SessionTimeout>";
   }
   txGetParameterValuesResponse <<
      "</soap-env:Header>"
      "<soap-env:Body>"
      "<cwmp:GetParameterValuesResponse>" <<
      parameterList.Xmlise() <<
      "</cwmp:GetParameterValuesResponse>"
      "</soap-env:Body>"
      "</soap-env:Envelope>";

   shared_ptr<HttpPostRequest> setParameterAttributesResponse(new HttpPostRequest( txGetParameterValuesResponse.str().c_str()) );
   transactionSessionFsm.HandleEvent(setParameterAttributesResponse);
}

}

