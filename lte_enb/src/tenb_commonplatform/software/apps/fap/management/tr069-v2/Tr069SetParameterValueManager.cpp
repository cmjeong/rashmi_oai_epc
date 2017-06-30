///////////////////////////////////////////////////////////////////////////////
//
// TR069SetParameterValueManager.cpp
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
#include <messaging/messages/common/OamActionReq.h>
#include <mib-common/messages/MibValidateAttributesReq.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069Application.h"
#include "Tr069SetParameterValueManager.h"
#include "Tr069DataModelManager.h"
#include "Tr069TransactionSession.h"

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

   Tr069SetParameterValueManager::Tr069SetParameterValueManager(
         MibAccessInterface& mib,
         SendMessageInterface &messenger,
         Tr069TransactionSession & transactionSessionFsm ) :
      m_mib(mib),
      m_messenger(messenger),
      m_transactionSessionFsm(transactionSessionFsm),
      m_parameterKey(""),
      m_fsm(*this, true)
   {
   }

   Tr069SetParameterValueManager::~Tr069SetParameterValueManager()
   {
   }

   void Tr069SetParameterValueManager::HandleEvent( shared_ptr<Queueable> event)
   {
      RSYS_ASSERT(event);

      switch(event->GetDomain())
      {
         case Queueable::MESSAGE_SERIALISED_DATA:
            {
               shared_ptr<MessageSerialisedData> message = dynamic_pointer_cast<MessageSerialisedData>(event);
               if (message)
               {
                  switch (message->GetSerialisationId())
                  {
                     case SERIALISATION_ID_MIB_VALIDATE_ATTRIBUTES_CNF:
                        {
                           shared_ptr<MibValidateAttributesCnf> mibValidateAttributesCnf = Serialisable::DeSerialise<MibValidateAttributesCnf>(message);
                           RSYS_ASSERT(mibValidateAttributesCnf);
                           m_fsm.InjectMibVerifyConfirm( mibValidateAttributesCnf );
                        }
                        break;

                     default: break;
                  }
               }
            }
            break;

         case Queueable::OTHER:
            {
               shared_ptr<Tr069QueueableEvent> tr069Event = dynamic_pointer_cast<Tr069QueueableEvent>(event);

               if (tr069Event)
               {
                  if(Tr069QueueableEvent::SPV_FSM == tr069Event->GetDst())
                  {
                     switch( tr069Event->GetId() )
                     {
                        case Tr069QueueableEvent::RPC_SET_PARAMETER_VALUE:
                           {
                              shared_ptr<RpcSetParameterValue> rpcSetParameterValue = dynamic_pointer_cast<RpcSetParameterValue>(tr069Event);
                              m_parameterKey = rpcSetParameterValue->GetParameterKey();
                              m_fsm.InjectSetParameterValueRequest(rpcSetParameterValue);
                           }
                           break;

                        case Tr069QueueableEvent::DATA_MODEL_VERIFY_CNF:
                           {
                              shared_ptr<DataModelVerifyCnf> dataModelVerifyCnf = dynamic_pointer_cast<DataModelVerifyCnf>(tr069Event);
                              m_fsm.InjectDataModelVerifyConfirm(dataModelVerifyCnf);
                           }
                           break;


                        default:
                           RSYS_ASSERT_PRINTF(false,"Unhandled SPV_FSM event %s.", tr069Event->ToString());
                           break;
                     }
                  }
               }
            }
            break;

         default:
            break;
      }
   }

   bool Tr069SetParameterValueManager::HandleTimerExpiry(threeway::TimerHandle expiredTimer)
   {
      bool timerHandled = false;

      return timerHandled;
   }

   // Actions
   void Tr069SetParameterValueManager::StoreSetRequest(shared_ptr<RpcSetParameterValue> rpcSetParameterValue)
   {
      m_rpcSetParameterValue = rpcSetParameterValue;

   }

   void Tr069SetParameterValueManager::SendSetParametersReject()
   {
      std::string cwmpId = m_rpcSetParameterValue->GetCwmpId();
      std::string timeout = Tr069Application::GetInstance().GetSoapTimeout();
      std::ostringstream txFault;
      txFault << "<soap-env:Envelope" << tr069::tr069XmlNsHeaderPreamble << ">"
         "<soap-env:Header>"
         "<cwmp:ID soap-env:mustUnderstand=\"1\">"<<cwmpId<<"</cwmp:ID>";
      if(timeout.compare("") != 0)
      {
         txFault << 
            "<cwmp:SessionTimeout soap-env:mustUnderstand=\"0\">" <<timeout<<"</cwmp:SessionTimeout>";
      }
      txFault <<
         "</soap-env:Header>"
         "<soap-env:Body>"
         "<soap-env:Fault>"
         "<faultcode>Client</faultcode>"
         "<faultstring>CWMP fault</faultstring>"
         "<detail>"
         "<cwmp:Fault>";;
#if 0
         "<FaultCode>9007</FaultCode>"
         "<FaultString>Not Valid Value</FaultString>";
#endif
      for(int i =0 ;i< no_of_fault; i++)
      {
         u32 faultCode=getFaultCode(m_faults[i]);
         txFault <<
            "<SetParameterValuesFault>"
            "<ParameterName>"<< name[i] << "</ParameterName>"
            "<FaultCode>"<<faultCode <<"</FaultCode>"
            "<FaultString>" << m_faults[i] << "</FaultString>"
            "</SetParameterValuesFault>";
            m_faults[i]="";
      }
      txFault <<
         "</cwmp:Fault>"
         "</detail>"
         "</soap-env:Fault>"
         "</soap-env:Body>"
         "</soap-env:Envelope>";

      shared_ptr<HttpPostRequest> faultResponse(new HttpPostRequest( txFault.str().c_str()) );
      m_transactionSessionFsm.HandleEvent(faultResponse);
   }

   void Tr069SetParameterValueManager::SendSetParametersConfirm()
   {
      u32 status = 0;
      DataModelManager & paramMgr = DataModelManager::GetInstance();

      if(Immediate != paramMgr.changeApplies)
      {
         status = 1;
      }

      std::string cwmpId = m_rpcSetParameterValue->GetCwmpId();
      std::string timeout = Tr069Application::GetInstance().GetSoapTimeout();
      std::ostringstream txSetParameterValuesResponse;
      txSetParameterValuesResponse << "<soap-env:Envelope" << tr069::tr069XmlNsHeaderPreamble << ">"
         "<soap-env:Header>"
         "<cwmp:ID soap-env:mustUnderstand=\"1\">"<<cwmpId<<"</cwmp:ID>";
      if(timeout.compare("") != 0)
      {
         txSetParameterValuesResponse << 
            "<cwmp:SessionTimeout soap-env:mustUnderstand=\"0\">" <<timeout<<"</cwmp:SessionTimeout>";
      }
      txSetParameterValuesResponse  <<
         "</soap-env:Header>"
         "<soap-env:Body>"
         "<cwmp:SetParameterValuesResponse>"
         "<Status>" << status << "</Status>"
         "</cwmp:SetParameterValuesResponse>"
         "</soap-env:Body>"
         "</soap-env:Envelope>";

      shared_ptr<HttpPostRequest> setParameterValuesResponse(new HttpPostRequest( txSetParameterValuesResponse.str().c_str()) );
      m_transactionSessionFsm.HandleEvent(setParameterValuesResponse);

      MibAttributeValues attrs;
      attrs.AddAttribute( PARAM_ID_TR069_HMS_PARAMETER_KEY, m_parameterKey);
      m_mib.SetMibAttributes( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), attrs, ENTITY_TR069);

      u32 opState = false;
      Tr069Application::GetInstance().GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP),PARAM_ID_LTE_RFTX_OP_STATE, opState);

      if((OnReboot == paramMgr.changeApplies) && (true == opState))
      {
         OamActionReq oamActionReq(OAM_ACTION_REBOOT);
         Tr069Application::GetInstance().SendMessage(oamActionReq, ENTITY_OAM, ENTITY_TR069);
      }
   }


   void Tr069SetParameterValueManager::SendSetMibAttributes(shared_ptr<MibValidateAttributesCnf>)
   {
      u32 inst = 0;
      // TODO: Modify SetMibAttributes to accept multiple DNs
      for( MibAttributeValuesByDn::iterator i = m_mibAttributeValuesByDn->begin();
            i != m_mibAttributeValuesByDn->end();
            ++i)
      {
         MibDN dn = i->first;
         MibAttributeValues mibAttributeValues = i->second;

         TRACE_PRINTF("%s SetMibAttributesByDn is called",__FUNCTION__);
         //Tr069Application::GetInstance().GetMibCache().SetMibAttributes( dn, mibAttributeValues, ENTITY_TR069);

         if( (dn.ToString().find("LTE_RAN_MOB_IDLE_MODE_INTER_FREQ_CARRIER")) != string::npos)
         {
            std::vector<u32> interFreqCarrSrcLst;
            MibAttributeValues attrs;
            char * instance = StringUtils::GetMibObjectInstanceNum(dn.ToString());
            if(instance == NULL)
            {
               //We should not reach here
               return;
            }
            inst = atoi(instance);
            string faplte ="FAP_LTE.";
            Tr069Application::GetInstance().GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(dn.ToString().substr(0,dn.ToString().find(faplte)+faplte.size()+1)),PARAM_ID_LTE_X_RADISYS_NEIGH_FREQ_SRC, interFreqCarrSrcLst);

            if(inst < interFreqCarrSrcLst.size())
            {
               interFreqCarrSrcLst[inst] = 1; /*Src is SPV */
            }
            attrs.AddAttribute( PARAM_ID_LTE_X_RADISYS_NEIGH_FREQ_SRC, interFreqCarrSrcLst);
            
            Tr069Application::GetInstance().GetMibCache().SetMibAttributes(MibDN::GenerateMibDN(dn.ToString().substr(0,dn.ToString().find(faplte)+faplte.size()+1)),attrs, ENTITY_TR069);
         }  

         m_parameterKey = GetParameterKey();
         Tr069Application::GetInstance().GetMibCache().SetMibAttributesByDn( dn, mibAttributeValues, ENTITY_TR069);
      }
   }

   // Entry/Exit
   void Tr069SetParameterValueManager::SettingEntry()
   {
      RSYS_ASSERT(m_rpcSetParameterValue);
      m_mibAttributeValuesByDn.reset();

      MibAttributeValues attrs;
      attrs.AddAttribute(PARAM_ID_TR069_SPV_IN_PROGRESS, 1);
      Tr069Application::GetInstance().GetMibCache().SetMibAttributes(attrs, ENTITY_TR069);

   }

   void Tr069SetParameterValueManager::SettingExit()
   {

   }

   void Tr069SetParameterValueManager::AwaitDataModelVerifyCnfEntry()
   {
      DataModelManager::GetInstance().ValidateSetParamterValue( m_rpcSetParameterValue->GetMap() );
   }

   void Tr069SetParameterValueManager::AwaitDataModelVerifyCnfExit()
   {

   }

   void Tr069SetParameterValueManager::AwaitMibVerifyCnfEntry()
   {
      MibValidateAttributesReq mibValidateAttributesReq;

      for( MibAttributeValuesByDn::iterator i = m_mibAttributeValuesByDn->begin();
            i != m_mibAttributeValuesByDn->end();
            ++i)
      {
         MibDN dn = i->first;
         MibAttributeValues mibAttributeValues = i->second;

         mibValidateAttributesReq.AddAttributes(dn,mibAttributeValues);
      }

      Tr069Application::GetInstance().SendMessage(mibValidateAttributesReq, ENTITY_MIB);
   }

   void Tr069SetParameterValueManager::AwaitMibVerifyCnfExit()
   {

   }

   // Guard Conditions
   bool Tr069SetParameterValueManager::QueryEmptySet()
   {
      return m_rpcSetParameterValue->GetMap().empty();
   }

   bool Tr069SetParameterValueManager::QueryVerified(shared_ptr<MibValidateAttributesCnf> mibValidateAttributesCnf)
   {
      bool queryAllOk = mibValidateAttributesCnf->AllAttributesValidateOk();

      if(!queryAllOk)
      {
         const MibValidateAttributesCnf::MibAttrValidationFailuresByDn&  failures = mibValidateAttributesCnf->GetFailures();
         MibValidateAttributesCnf::MibAttrValidationFailuresByDn::const_iterator i;

         ParameterValueMap setParaMap;
         setParaMap = m_rpcSetParameterValue->GetMap();
         ParameterValueMap::const_iterator param = setParaMap.begin();
         DataModelManager & paramMgr = DataModelManager::GetInstance();
         DmNameMap::const_iterator dm;
         u16 k=0,fno;
         MibAttributeId Attrid,faultAttrid;
         for(param = setParaMap.begin(); param != setParaMap.end() ; param++)
         {
            dm = paramMgr.m_nameMap.find(param->first);
            if(dm != paramMgr.m_nameMap.end())
            {
               Attrid = (dm->second).mibAttrId ;

               for(i = failures.begin(); i != failures.end(); i++)
               { 
                  for(fno = 0; fno < (i->second).size(); fno++)
                  {
                     faultAttrid = (i->second).at(fno).GetMibAttributeId();
                     if(Attrid == faultAttrid)
                     {
                        m_faults[k] = m_faults[k] + (*i).second.at(fno).ToString();
                     }
                  }
                  name[k++]= param->first;
                  fno++;
               }
            }
         }
         no_of_fault = k;
      }

      return queryAllOk;
   }

   bool Tr069SetParameterValueManager::QueryVerified(shared_ptr<DataModelVerifyCnf> dataModelVerifyCnf)
   {
      m_mibAttributeValuesByDn = dataModelVerifyCnf->GetMibAttributeValuesByDn();

      no_of_fault = dataModelVerifyCnf->GetNoOfFaults();
      for(int i = 0 ;i< no_of_fault ;i++)
      {
         m_faults[i] =  dataModelVerifyCnf->GetFault(i);
         name[i] = dataModelVerifyCnf->GetFaultParameter(i);
      }
      return dataModelVerifyCnf->VerifiedOk();
   }

u32 Tr069SetParameterValueManager::getFaultCode(string faultString)
{
   FaultCodeMap faultCodeMap[]={

      {"ObjectDoesNotExist",9005},
      {"NotAllowedOnObject",9005},
      {"AttributeIdNotFound",9005},
      {"BelowMinimum",9007},
      {"AboveMaximum",9007},
      {"NotValidValue",9007},
      {"TooShort",9007},
      {"TooLong",9007},
      {"TooManyInstances",9006},
      {"ReadOnly",9008},
      {"InvalidDataType",9006}
   };
   u32 faultCode=9007;

   for(u32 i=0;i<sizeof(faultCodeMap)/sizeof(faultCodeMap[0]);i++)

   {
      if (strstr(faultString.c_str(),faultCodeMap[i].faultString))
      {
         faultCode=faultCodeMap[i].faultCode;
         break;
      }
   }
   return faultCode;
}


}

