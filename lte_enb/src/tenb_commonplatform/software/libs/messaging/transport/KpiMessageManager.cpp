///////////////////////////////////////////////////////////////////////////////
//
// KpiMessageManager.cpp
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
#include <messaging/messages/common/KpiReadReq.h>
#include <messaging/messages/common/KpiReadCnf.h>
#include <set>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "KpiMessageManager.h"


using namespace boost;
using namespace std;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////
KpiMessageManager::KpiMessageManager( MessagingEntity entity, SendMessageInterface & sendMessageInterface) :
        m_thisEntity(entity),
        m_sendMessageInterface(sendMessageInterface)
{
}

KpiMessageManager::~KpiMessageManager()
{
}

void KpiMessageManager::RegisterKpiCollector(MessagingEntity entity, shared_ptr<KpiCollector> kpiCollector)
{
    ENTER();

    KpiCollectors::const_iterator iter = m_kpiCollectors.find(entity);

    RSYS_ASSERT_PRINTF(iter == m_kpiCollectors.end(), "Entity %s already registered", MessagingEntityToString(entity));

    TRACE("Adding KPI collector for entity", MessagingEntityToString(entity));
    m_kpiCollectors[entity] = kpiCollector;

    EXIT();
}

bool KpiMessageManager::MessageHandler(shared_ptr<MessageSerialisedData> & message)
{
    ENTER();

    bool handled = false;
    u32 messageId = message->GetSerialisationId();

    if( (messageId == SERIALISATION_ID_KPI_READ_REQ))
    {
        HandleKpiReadReqMessage(message);

        // We're done and are going to swallow these messages.
        // Derived classes don't need to know about them.
        handled = true;
    }

    RETURN(handled);
}

void KpiMessageManager::HandleKpiReadReqMessage(shared_ptr<MessageSerialisedData> message)
{
    ENTER();

    TRACE("Received KPI message", message->ToString().c_str());

    MessagingEntity kpiEntity = message->GetToEntity();
    KpiCollectors::const_iterator iter = m_kpiCollectors.find(kpiEntity);
    if(iter != m_kpiCollectors.end())
    {
        if(iter->second != NULL)
        {
            // We have a KPI collector!

            // Grab the KPI values and send confirm.
            shared_ptr<KpiReadReq> kpiReadReq = Serialisable::DeSerialise<KpiReadReq>(message);
            if(kpiReadReq)
            {
                std::set<KpiGroupId> kpiGroupIdList = kpiReadReq->GetKpiGroupIdList();
                if(kpiGroupIdList.size() == 0)
                {
                    return;
                }
                std::set<KpiGroupId>::iterator kpiGroupIdListIter = kpiGroupIdList.begin();
                while(true)
                {
                   // The group may not be found in the collector so make sure we
                   // have a valid group, with the correct ID to pass back in KpiReadCnf
                   // even if not found in collector.
                   KpiGroup kpiGroup(*kpiGroupIdListIter);
                   iter->second->GetKpiGroup(*kpiGroupIdListIter,
                                             kpiReadReq->GetKpiMeasurementSet(),
                                             kpiReadReq->GetKpiReadMode() == KpiReadReq::READ_AND_RESET_KPIS,
                                             kpiGroup);
                   TRACE_PRINTF("Sending KPI values for entity %s: %s",
                                 MessagingEntityToString(kpiEntity),
                                 kpiGroup.ToString().c_str());

                   if( kpiReadReq->isCollectionreqPending() )
                   {
                       kpiGroup.TouchAndAlignTimeStampToUploadInterval(kpiReadReq->getPeriodicUploadIntervalInSecs());
                   }

                   KpiReadCnf kpiReadCnf(kpiReadReq->GetKpiMeasurementSet(), kpiGroup);

                   

                   m_sendMessageInterface.SendMessage(kpiReadCnf, message->GetFromEntity(), kpiEntity);
                   kpiGroupIdListIter++;
                   if(kpiGroupIdListIter == kpiGroupIdList.end())
                   {
                       //Send the last Read Cnf message to OAM to inform the completion of read request processing.
                       m_sendMessageInterface.SendMessage(kpiReadCnf, ENTITY_OAM, kpiEntity);
                       break;
                   }
                }
            }
        }
    }

    EXIT();
}


}
