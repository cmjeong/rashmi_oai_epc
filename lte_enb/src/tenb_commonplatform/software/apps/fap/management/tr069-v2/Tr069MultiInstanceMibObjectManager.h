///////////////////////////////////////////////////////////////////////////////
//
// MultiInstanceMibObjectManager.h
//
// Class for managing TR069 Add Object RPC
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069MultiInstanceMibObjectManager_h_
#define __Tr069MultiInstanceMibObjectManager_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <mib-common/MibDN.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069MultiInstanceMibObject.h"

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace threeway;

namespace tr069
{

class MultiInstanceMibObjectManager
{
private:
    // Is singleton so private constructor.
    MultiInstanceMibObjectManager(MibAccessInterface& mib, SendMessageInterface &messanger );

public:
    /**
     * Construction / destruction.
     */
    ~MultiInstanceMibObjectManager ();
    static MultiInstanceMibObjectManager& GetInstance();

    void PerformMibSubscriptions( u32 subscriptionId );
    void HandleMibSubscribeAttributesInd( u32 subscriptionId );
    void Str_replace(std::string &str,char *subStr, string newValue);
    void AddParameterToParameterList( const string & name, ParameterList & parameterList );

    shared_ptr<Tr069MultiInstanceObject> GetMio( const string & path );

private:

    MibAccessInterface& m_mib;
    SendMessageInterface & m_messenger;

    static MultiInstanceMibObjectManager* s_instance;

    set< shared_ptr<Tr069MultiInstanceObject> > m_multiInstanceObjects;
    map< u32, shared_ptr<Tr069MultiInstanceObject> > m_mioMibSubscription;
    map< string, shared_ptr<Tr069MultiInstanceObject> > m_mioByPath;
    map< string, shared_ptr<Tr069MultiInstanceObject> > m_mioMaxEntries;
    map< string, shared_ptr<Tr069MultiInstanceObject> > m_mioCurrentEntries;
    u32 numCells;
};



}
#endif
