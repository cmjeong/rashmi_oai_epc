///////////////////////////////////////////////////////////////////////////////
//
// KpiLogFileMgr.h
//
// Manage a file for storing and retrieving KPI.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __KpiLogFileMgr_h_
#define __KpiLogFileMgr_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/KpiGroup.h>
#include <system/FiniteSerialisableFileStore.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class KpiLogFileMgr : public FiniteSerialisableFileStore
{
public:

    /**
     * Constructor.
     *
     * \param logFileName       Path and file name to log file.
     * \param minNumAlarmEvents Minimum number of KpiGroup objects to store.
     */
    KpiLogFileMgr(const char * logFileNameStem, u32 minNumKpiGroups);

    virtual ~KpiLogFileMgr();

    /**
     * Implement SerialisableFactory.
     */
    virtual boost::shared_ptr<Serialisable> GetSerialisable(u32 serialisationId,
                                                            const u8* serialisedData,
                                                            u32 serialisedDataLen);

    /**
     * Accept a visitor.  This will iterate through all the stored objects
     * returning each to the client, oldest first.
     */
    void AcceptVisitor(KpiGroupVisitor& visitor);

    /**
     * Write object to file.  This just validates it is a KpiGroup
     * before calling FiniteSerialisableFileStore::WriteObject.
     */
    virtual void WriteObject(const Serialisable& object);

protected:

    /**
     * Read all objects, oldest first, and call HandleObjectRead().
     * Override simply to hide it from public access - use AcceptVisitor().
     */
    virtual void ReadAllObjects() { FiniteSerialisableFileStore::ReadAllObjects(); };

    /**
     * Override base class hooks.
     */
    virtual void HandleObjectRead(const shared_ptr<Serialisable> object);

private:

    /**
     * Store the visitor reference as we need to use it in HandleObjectRead
     * after calling AcceptVisitor().
     */
    KpiGroupVisitor* m_kpiGroupVisitor;
};

}

#endif
