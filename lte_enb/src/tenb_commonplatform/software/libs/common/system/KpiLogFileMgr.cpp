///////////////////////////////////////////////////////////////////////////////
//
// KpiLogFileMgr.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "KpiLogFileMgr.h"

using namespace std;
using namespace threeway;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

KpiLogFileMgr::KpiLogFileMgr(const char * logFileNameStem, u32 minNumKpiGroups) :
    FiniteSerialisableFileStore(logFileNameStem, minNumKpiGroups),
    m_kpiGroupVisitor(NULL)
{
    ENTER();

    EXIT();
}

KpiLogFileMgr::~KpiLogFileMgr()
{
    ENTER();

    EXIT();
}

shared_ptr<Serialisable> KpiLogFileMgr::GetSerialisable(u32 serialisationId,
                                                        const u8* serialisedData,
                                                        u32 serialisedDataLen)
{
    ENTER();

    shared_ptr<KpiGroup> object;

    if(serialisationId == SERIALISATION_ID_KPI_GROUP)
    {
        object.reset(new KpiGroup);
        if(object->DeSerialise(serialisedData, serialisedDataLen) == false)
        {
            // Reading may fail if the KPI group is unknown by this build.
            // In that case, reset the object as it is of no use to us.
            object.reset();
        }
    }

    RETURN(object);
}

void KpiLogFileMgr::AcceptVisitor(KpiGroupVisitor& visitor)
{
    ENTER();

    m_kpiGroupVisitor = &visitor;

    // Let HandleObjectRead() callback to client.
    ReadAllObjects();

    m_kpiGroupVisitor = NULL;

    EXIT();
}

void KpiLogFileMgr::WriteObject(const Serialisable& object)
{
    RSYS_ASSERT(object.GetSerialisationId() == SERIALISATION_ID_KPI_GROUP);
    FiniteSerialisableFileStore::WriteObject(object);
}

void KpiLogFileMgr::HandleObjectRead(const shared_ptr<Serialisable> object)
{
    ENTER();

    RSYS_ASSERT(m_kpiGroupVisitor != NULL);

    const shared_ptr<KpiGroup> kpiGroup = dynamic_pointer_cast<KpiGroup>(object);

    if(kpiGroup != NULL)
    {
        m_kpiGroupVisitor->VisitKpiGroup(*kpiGroup);
    }

    EXIT();
}

}
