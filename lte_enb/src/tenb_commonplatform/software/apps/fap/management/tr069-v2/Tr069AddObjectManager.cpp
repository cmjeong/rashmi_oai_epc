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
#include "Tr069AddObjectManager.h"
#include "Tr069AddObject_fsm.h"
#include "SoapEnvelope.h"
#include "Tr069AddObjectResponse.h"
#include "SoapFault.h"
#include <mib-common/MIOAutoManage.h>

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

AddObjectManager::AddObjectManager(
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

AddObjectManager::~AddObjectManager()
{
}

void AddObjectManager::AddObject( const string & pathname )
{

}

void AddObjectManager::AddParameterToParameterList( const string & name, ParameterList & parameterList )
{

}


void AddObjectManager::HandleEvent( shared_ptr<Queueable> event)
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
                    case SERIALISATION_ID_MIB_CREATE_OBJECT_CNF:
                    {
                        shared_ptr<MibCreateObjectCnf> mibCreateObjectCnf = Serialisable::DeSerialise<MibCreateObjectCnf>(message);
                        RSYS_ASSERT(mibCreateObjectCnf);
                        m_fsm.InjectMibCreateObjectCnf( mibCreateObjectCnf );
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

            if(Tr069QueueableEvent::ADD_OBJECT_FSM == tr069Event->GetDst())
            {
                switch( tr069Event->GetId() )
                {
                    case Tr069QueueableEvent::RPC_ADD_OBJECT:
                    {
                        shared_ptr<RpcAddObject> rpcAddObject = dynamic_pointer_cast<RpcAddObject>(tr069Event);
                        m_fsm.InjectAddObject(rpcAddObject);
                    }
                    break;

                    default:
                        RSYS_ASSERT_PRINTF(false,"Unhandled ADD_OBJECT_FSM event %s.", tr069Event->ToString());
                        break;
                }
            }
        }
        break;

        default:
            break;
    }
}

void AddObjectManager::IdleEntry()
{
    m_parameterKey = "";
}


void AddObjectManager::DeleteObject( const string & object )
{

}



AddObjectFsmActionSendCreateMibObjectReq::Outcome AddObjectManager::SendCreateMibObjectReq( shared_ptr<RpcAddObject> rpcAddObject)
{
   TRACE_PRINTF("%s",__func__);

   std::string timeout = Tr069Application::GetInstance().GetSoapTimeout();

   shared_ptr<Tr069MultiInstanceObject> mio = MultiInstanceMibObjectManager::GetInstance().GetMio(rpcAddObject->GetObjectName());
   if(mio)
   {
      MibObjectClass MOC = mio->GetChildClass();
      m_rpcAddObject = rpcAddObject;
      if(MIOAutoManage::GetInstance().isReadOnly(MOC))
      {
         TRACE_PRINTF("is READ ONLY");
         SoapFault soapFault;

         stringstream faultString;
         faultString << "Object :" << rpcAddObject->GetObjectName() << " is ReadOnly";

         soapFault.m_cmwpFault.m_faultCode   = 9008;
         soapFault.m_cmwpFault.m_faultString = faultString.str();

         SoapEnvelope envelope(soapFault);
         envelope.soapheader.SetCwmpId(rpcAddObject->GetCwmpId());
         envelope.soapheader.SetSoapTimeout(timeout);

         shared_ptr<HttpPostRequest> httpPostRequest(new HttpPostRequest( envelope ) );
         m_transactionSessionFsm.HandleEvent(httpPostRequest);

         return AddObjectFsmActionSendCreateMibObjectReq::FSM_ACTION_ADD_OBJECT_NOT_SUPPORTED;
      }

      MibAttributeValues attr;

      shared_ptr<MibCreateObjectReq> mibCreateObjectReq = mio->New( attr );

      if(mibCreateObjectReq)
      {
         m_messenger.SendMessage( *mibCreateObjectReq, ENTITY_MIB, ENTITY_TR069 );
         m_parameterKey = rpcAddObject->GetParameterKey();

         return AddObjectFsmActionSendCreateMibObjectReq::FSM_ACTION_SUCCESS;
      }
      else
      {
         SoapFault soapFault;

         soapFault.m_cmwpFault.m_faultCode   = 9004;
         soapFault.m_cmwpFault.m_faultString = "AddObject request would exceed maximum number permitted";

         SoapEnvelope envelope(soapFault);
         envelope.soapheader.SetCwmpId(rpcAddObject->GetCwmpId());
         envelope.soapheader.SetSoapTimeout(timeout);

         shared_ptr<HttpPostRequest> httpPostRequest(new HttpPostRequest( envelope ) );
         m_transactionSessionFsm.HandleEvent(httpPostRequest);

         return AddObjectFsmActionSendCreateMibObjectReq::FSM_ACTION_MAX_ENTRIES_EXCEEDED;
      }
   }
   else
   {
      SoapFault soapFault;

      stringstream faultString;
      faultString << "AddObject of object name " << rpcAddObject->GetObjectName() << " invalid.";

      soapFault.m_cmwpFault.m_faultCode   = 9005;
      soapFault.m_cmwpFault.m_faultString = faultString.str();

      SoapEnvelope envelope(soapFault);
      envelope.soapheader.SetCwmpId(rpcAddObject->GetCwmpId());
      envelope.soapheader.SetSoapTimeout(timeout);

      shared_ptr<HttpPostRequest> httpPostRequest(new HttpPostRequest( envelope ) );
      m_transactionSessionFsm.HandleEvent(httpPostRequest);

      return AddObjectFsmActionSendCreateMibObjectReq::FSM_ACTION_ADD_OBJECT_NOT_SUPPORTED;
   }
}

void AddObjectManager::SendAddObjectResponse(shared_ptr<MibCreateObjectCnf> mibCreateObjectCnf)
{
    AddObjectResponse addObjectResponse(mibCreateObjectCnf->GetDn().back().GetMibObjectInstance() + 1);
    SoapEnvelope envelope(addObjectResponse);
	envelope.soapheader.SetCwmpId(m_rpcAddObject->GetCwmpId());
	std::string timeout = Tr069Application::GetInstance().GetSoapTimeout();
	envelope.soapheader.SetSoapTimeout(timeout);

    shared_ptr<HttpPostRequest> httpPostRequest(new HttpPostRequest( envelope ) );
    m_transactionSessionFsm.HandleEvent(httpPostRequest);

    MibAttributeValues attrs;
    attrs.AddAttribute( PARAM_ID_TR069_HMS_PARAMETER_KEY, m_parameterKey);
    m_mib.SetMibAttributes( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), attrs, ENTITY_TR069);
}


}

