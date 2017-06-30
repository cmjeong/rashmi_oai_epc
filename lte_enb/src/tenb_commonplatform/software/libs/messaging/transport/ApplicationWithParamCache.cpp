///////////////////////////////////////////////////////////////////////////////
//
// ApplicationWithParamCache.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ApplicationWithParamCache.h"

using namespace std;
using namespace boost;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

ApplicationWithParamCache::ApplicationWithParamCache(const char * appName) :
    ApplicationWithMessaging(appName)
{
    ENTER();

    EXIT();
}

ApplicationWithParamCache::~ApplicationWithParamCache()
{
    ENTER();

    EXIT();
}

void ApplicationWithParamCache::StartAttributeCache()
{
    ENTER();

    RSYS_ASSERT(m_messenger != NULL);

    m_attribCache.reset(new AppMibAttributeCache(m_messenger, *this, *this));

    EXIT();
}

bool ApplicationWithParamCache::MessageHandler(shared_ptr<threeway::MessageSerialisedData> & message)
{
    ENTER();

    TRACE_PRINTF_LEV( TRACE_VERBOSE, "ApplicationWithParamCache::MessageHandler");

    RSYS_ASSERT(m_attribCache != NULL);

    // First, pass to parent
    bool handled = ApplicationWithMessaging::MessageHandler(message);

    if( !handled )
    {
        //Deliberately not setting handled here as the subscription may also get handled elsewhere

        // Is this one of our Param handling messages?
        switch(message->GetSerialisationId())
        {
            case SERIALISATION_ID_MIB_SUBSCRIBE_ATTRIBUTES_IND:
                m_attribCache->HandleMibSubscribeAttributesInd(message);
                break;

            case SERIALISATION_ID_MIB_SUBSCRIBE_ATTRIBUTES_DELETE_IND:
                m_attribCache->HandleMibSubscribeAttributesDeleteInd(message);
                break;

            default:
                break;
        }
    }

    RETURN(handled);
}

}
