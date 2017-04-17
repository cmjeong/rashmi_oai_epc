///////////////////////////////////////////////////////////////////////////////
//
// ApplicationWithParamCache.h
//
// Extends ApplicationWithMessaging class to add parameter retrieval/caching.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ApplicationWithParamCache_h_
#define __ApplicationWithParamCache_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <map>
#include <string>

#include <boost/shared_ptr.hpp>

#include <messaging/transport/ApplicationWithMessaging.h>
#include <system/Serialisable.h>
#include <mib-common/MibAttributeValues.h>
#include <mib-common/MibAttributeValuesByDn.h>
#include <mib-common/MibAttributeIdsByDn.h>
#include <MibAttributeId.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "AppMibAttributeCache.h"

using namespace boost;
using namespace std;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class ApplicationWithParamCache :
    public ApplicationWithMessaging,
    public MibAttributeUpdatedInformInterface
{
protected:
    /**
     * Construct ApplicationWithParamCache
     *
     * \param appName      Give the application a name -
     * passed to ApplicationWithMessaging
     */
    ApplicationWithParamCache(const char * appName);

public:
    virtual ~ApplicationWithParamCache();

    /**
     * Call this once messaging started.
     */
    void StartAttributeCache();

    /**
     * Get interface for accessing the MIB.
     */
    MibAccessInterface& GetMibCache() const { RSYS_ASSERT(m_attribCache != NULL); return *m_attribCache; };

    /**
     * default versions do nothing. Override them if necessary.
     * note that these functions should be implemented defensively as they could be called before
     * the application has received the start message.
     */
    virtual void MibAttributeUpdated(const MibDN& dn, MibAttributeId mibAttributeId) {}
    virtual void MibAttributesUpdated(u32 subscriptionId, const MibAttributeValuesByDn &oldValues, const MibAttributeValuesByDn &newValues) {}
    virtual void MibAttributesUpdated(u32 subscriptionId, const MibAttributeIdsByDn& mibAttributeValuesByDn) {}

protected:
    // MessageHandler interface
    virtual bool MessageHandler(shared_ptr<threeway::MessageSerialisedData> & message);

private:

    /**
     * Instance of class for managing MIB attribute cache for this app.
     */
    boost::shared_ptr<AppMibAttributeCache> m_attribCache;
};

}

#endif
