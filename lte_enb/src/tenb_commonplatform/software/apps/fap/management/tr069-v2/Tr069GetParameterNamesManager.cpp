///////////////////////////////////////////////////////////////////////////////
//
// GetParameterNamesManager.cpp
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
#include "Tr069GetParameterNamesManager.h"
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
GetParameterNamesManager::GetParameterNamesManager()
{
}

GetParameterNamesManager::~GetParameterNamesManager()
{
}

void GetParameterNamesManager::HandleGetParameterNames( Tr069FsmInterface & transactionSessionFsm, const RpcGetParameterNames & rpcGetParameterNames )
{
   TRACE_PRINTF("%s",__FUNCTION__);

   DataModelManager & paramMgr = DataModelManager::GetInstance();
   ParameterInfoList parameterInfoList;

   const ParameterNames & parameterNames = rpcGetParameterNames.GetParameters();
   const std::string cwmpId = rpcGetParameterNames.GetCwmpId();

   ParameterNames faultParameterNames;

   for(ParameterNames::const_iterator it = parameterNames.begin(); it != parameterNames.end(); ++it)
   {
      string parameterName = *it;

      ParameterInfoList additionalParameterList;

      paramMgr.AddParameterInfoToParameterList(parameterName, additionalParameterList);

      if(additionalParameterList.QueryValid())
      {
         parameterInfoList.AppendParameters(additionalParameterList);
      }
      else
      {
         faultParameterNames.push_back(parameterName);
      }
   }

   if(parameterInfoList.QueryValid() && faultParameterNames.empty() )
   {
      SendGetParameterNamesConfirm(transactionSessionFsm, parameterInfoList, cwmpId);
   }
   else
   {
      SendGetParameterNamesReject(transactionSessionFsm, faultParameterNames, cwmpId );
   }
}


void GetParameterNamesManager::SendGetParameterNamesReject(Tr069FsmInterface & transactionSessionFsm, const ParameterNames & faultParameterNames, std::string cwmpId )
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

void GetParameterNamesManager::SendGetParameterNamesConfirm( Tr069FsmInterface & transactionSessionFsm, const ParameterInfoList & parameterList, std::string cwmpId)
{
   std::ostringstream txGetParameterNamesResponse;
   std::string timeout = Tr069Application::GetInstance().GetSoapTimeout();
   txGetParameterNamesResponse << "<soap-env:Envelope"
      << tr069::tr069XmlNsHeaderPreamble << ">"
      "<soap-env:Header>"
      "<cwmp:ID soap-env:mustUnderstand=\"1\">"<< cwmpId <<"</cwmp:ID>";
   if(timeout.compare("") != 0)
   {
      txGetParameterNamesResponse <<
         "<cwmp:SessionTimeout soap-env:mustUnderstand=\"0\">"<< timeout <<"</cwmp:SessionTimeout>";
   }
   txGetParameterNamesResponse <<
      "</soap-env:Header>"
      "<soap-env:Body>"
      "<cwmp:GetParameterNamesResponse>" <<
      parameterList.Xmlise() <<
      "</cwmp:GetParameterNamesResponse>"
      "</soap-env:Body>"
      "</soap-env:Envelope>";

   shared_ptr<HttpPostRequest> setParameterAttributesResponse(new HttpPostRequest( txGetParameterNamesResponse.str().c_str()) );
   transactionSessionFsm.HandleEvent(setParameterAttributesResponse);
}

}

