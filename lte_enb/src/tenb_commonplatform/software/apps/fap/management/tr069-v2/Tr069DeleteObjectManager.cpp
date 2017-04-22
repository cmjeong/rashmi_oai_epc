///////////////////////////////////////////////////////////////////////////////
//
// Tr069MultiInstanceObject.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069Application.h"
#include "Tr069MultiInstanceMibObjectManager.h"
#include "Tr069DeleteObjectManager.h"
//#include "Tr069DeleteObject_fsm_interface.h"
#include "Tr069DeleteObject_fsm.h"
#include "SoapEnvelope.h"
#include "Tr069DeleteObjectResponse.h"

using namespace std;
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
DeleteObjectManager::DeleteObjectManager(
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

DeleteObjectManager::~DeleteObjectManager()
{
}

void DeleteObjectManager::DeleteObject( const string & pathname )
{

}

void DeleteObjectManager::AddParameterToParameterList( const string & name, ParameterList & parameterList )
{

}


void DeleteObjectManager::HandleEvent( shared_ptr<Queueable> event)
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
                    case SERIALISATION_ID_MIB_DELETE_OBJECT_CNF:
{
                        shared_ptr<MibDeleteObjectCnf> mibDeleteObjectCnf = Serialisable::DeSerialise<MibDeleteObjectCnf>(message);
                        RSYS_ASSERT(mibDeleteObjectCnf);
                        m_fsm.InjectMibDeleteObjectCnf( mibDeleteObjectCnf );
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

            if(Tr069QueueableEvent::DELETE_OBJECT_FSM == tr069Event->GetDst())
            {
                switch( tr069Event->GetId() )
                {
                    case Tr069QueueableEvent::RPC_DELETE_OBJECT:
                    {
                        shared_ptr<RpcDeleteObject> rpcDeleteObject = dynamic_pointer_cast<RpcDeleteObject>(tr069Event);
                        m_fsm.InjectDeleteObject(rpcDeleteObject);
                    }
                    break;

                    default:
                        RSYS_ASSERT_PRINTF(false,"Unhandled DELETE_OBJECT_FSM event %s.", tr069Event->ToString());
                        break;
                }
            }
 }
 break;

        default:
            break;
    }
}

void DeleteObjectManager::IdleEntry()
{
    m_parameterKey = "";
}


/*void DeleteObjectManager::DeleteObject( const string & object )
{

}*/



DeleteObjectFsmActionSendDeleteMibObjectReq::Outcome DeleteObjectManager::SendDeleteMibObjectReq( shared_ptr<RpcDeleteObject> rpcDeleteObject)
{
   m_rpcDeleteObject = rpcDeleteObject;
   shared_ptr<Tr069MultiInstanceObject> mio = MultiInstanceMibObjectManager::GetInstance().GetMio(rpcDeleteObject->GetObjectName());

   if(mio)
   {
      if((!(mio->check_if_instance_exist(rpcDeleteObject->GetInstance()- 1))) &&
         (strstr(rpcDeleteObject->GetObjectName().c_str(),
                  "CellConfig.LTE.RAN.NeighborList.LTECell.")==NULL))
      {
         SoapFault soapFault;
         stringstream faultString;
         faultString << "The instance  " << rpcDeleteObject->GetInstance()<< " of Delete Object "<< rpcDeleteObject->GetObjectName()<<"does not exist ";
         soapFault.m_cmwpFault.m_faultString = faultString.str();
         soapFault.m_cmwpFault.m_faultCode   = 9005;
         SendFault(soapFault,rpcDeleteObject->GetCwmpId());
         return DeleteObjectFsmActionSendDeleteMibObjectReq::FSM_ACTION_DELETE_OBJECT_NOT_SUPPORTED;
      }

      u32 instance = rpcDeleteObject->GetInstance();
      if(instance > 0)
      {
         if(mio->Delete(instance -1 ))
         {
            m_parameterKey = rpcDeleteObject->GetParameterKey();
            return DeleteObjectFsmActionSendDeleteMibObjectReq::FSM_ACTION_SUCCESS;
          }
          else
          {
              SoapFault soapFault;
              stringstream faultString;
              faultString << "Unable to Delete Frequency Object "<< rpcDeleteObject->GetObjectName()<<". Cell already exists for this frequency.";
              soapFault.m_cmwpFault.m_faultString = faultString.str();
              soapFault.m_cmwpFault.m_faultCode   = 9005;
              SendFault(soapFault,rpcDeleteObject->GetCwmpId());
              return DeleteObjectFsmActionSendDeleteMibObjectReq::FSM_ACTION_DELETE_OBJECT_NOT_SUPPORTED;
          }
      }
   }
   else
   {
      SoapFault soapFault;
      stringstream faultString;
      faultString << "DeleteObject of object name " << rpcDeleteObject->GetObjectName() << " invalid.";
      soapFault.m_cmwpFault.m_faultCode   = 9005;
      soapFault.m_cmwpFault.m_faultString = faultString.str();
      SendFault(soapFault,rpcDeleteObject->GetCwmpId());
      return DeleteObjectFsmActionSendDeleteMibObjectReq::FSM_ACTION_DELETE_OBJECT_NOT_SUPPORTED;
   }
   return DeleteObjectFsmActionSendDeleteMibObjectReq::FSM_ACTION_DELETE_OBJECT_NOT_SUPPORTED;
}

void DeleteObjectManager::SendFault(SoapFault &soapFault,string CwmpId)
{
         SoapEnvelope envelope(soapFault);
         std::string timeout = Tr069Application::GetInstance().GetSoapTimeout();
         envelope.soapheader.SetCwmpId(CwmpId);
         envelope.soapheader.SetSoapTimeout(timeout);
         shared_ptr<HttpPostRequest> httpPostRequest(new HttpPostRequest( envelope ) );
         m_transactionSessionFsm.HandleEvent(httpPostRequest);

}

void DeleteObjectManager::SendDeleteObjectResponse(shared_ptr<MibDeleteObjectCnf> mibDeleteObjectCnf)
{
    DeleteObjectResponse deleteObjectResponse(mibDeleteObjectCnf->GetDn().back().GetMibObjectInstance() + 1);
    SoapEnvelope envelope(deleteObjectResponse);
	envelope.soapheader.SetCwmpId(m_rpcDeleteObject->GetCwmpId());
	std::string timeout = Tr069Application::GetInstance().GetSoapTimeout();
	envelope.soapheader.SetSoapTimeout(timeout);
	
	shared_ptr<HttpPostRequest> httpPostRequest(new HttpPostRequest( envelope ) );
    m_transactionSessionFsm.HandleEvent(httpPostRequest);

    MibAttributeValues attrs;
    attrs.AddAttribute( PARAM_ID_TR069_HMS_PARAMETER_KEY, m_parameterKey);
    m_mib.SetMibAttributes( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), attrs, ENTITY_TR069);
}


}

