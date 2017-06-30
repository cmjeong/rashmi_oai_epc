///////////////////////////////////////////////////////////////////////////////
//
// DumpEnumIds.cpp
//
// Dump out enum name/value pairs for important enums in system.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <system/SerialisationIds.h>
#include <messaging/transport/MessagingEntity.h>
#include <mib-common/MibAttributeDescriptors.h>
#include <Radisys.h>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

int main (int argc, char **argv)
{
    TRACE_PRINTF("%s",__FUNCTION__);
    TRACE_PRINTF("SerialisationIds:\n");

    TRACE_PRINTF("%s \n",SerialisationIdToStringTable());

    TRACE_PRINTF("MessagingEntity:\n");

    for(u32 i = 0; i < (u32)ENTITY_NUM_ENTITIES; i++)
    {
        TRACE_PRINTF("%d  (0x%x)  %s = ",i,i,MessagingEntityToString((MessagingEntity)i));
    }

    TRACE_PRINTF("MibAttributeId:\n");

    for(u32 i = 0; i < (u32)NUM_MIB_ATTR_IDS; i++)
    {
        TRACE_PRINTF("%d  (0x %x) %s = ",i,i,getMibAttributeName((MibAttributeId)i));
    }

    return 0;
}
