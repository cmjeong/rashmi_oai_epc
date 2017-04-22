///////////////////////////////////////////////////////////////////////////////
//
// ManagedObject.h
//
// Base class for a managed object.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ManagedObject_h_
#define __ManagedObject_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>

#include <boost/shared_ptr.hpp>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace boost;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ManagedObject
{
public:
    
    enum AdminState
    {
        ADMIN_STATE_LOCKED = 0,
        ADMIN_STATE_UNLOCKED,
        ADMIN_STATE_SHUTTING_DOWN
    };
    
    enum OpState
    {
        OP_STATE_DISABLED = 0,
        OP_STATE_ENABLED
    };

    enum SONConfigPresence
    {
       SON_EARFCNDL_LIST_CONFIGURED = 1,
       SON_EARFCNUL_LIST_CONFIGURED = 2,
       SON_ROOT_SEQUENCE_INDEX_LIST_CONFIGURED = 4,
       SON_CONFIG_INDEX_LIST_CONFIGURED = 8,
       SON_ZERO_CORRELATIONZONE_CONFIG_LIST_CONFIGURED = 16,
       SON_FREQ_OFFSET_LIST_CONFIGURED = 32,
       SON_SELECTED_PCI_CONFIGURED = 64,
       SON_LTE_PHY_CELLID_LIST_CONFIGURED = 128,
       SON_SELECTED_EARFCNUL_CONFIGURED = 256,
       SON_SELECTED_EARFCNDL_CONFIGURED = 512,
       SON_LTE_PDSCH_CONFIG_COMMON_CONFIGURED= 1024,
       SON_LTE_POWER_OFFSET_CONFIGURED =2048,
       SON_LTE_PDSCH_CONFIG_DEDICATED_CONFIGURED=4096

    };
    
    static const char * AdminStateToString(AdminState adminState);
    static const char * OpStateToString(OpState opState);

    ManagedObject();
    virtual ~ManagedObject();
    
    /**
     * Accessors
     */
    virtual void SetAdminState(AdminState adminState);
    AdminState GetAdminState() const;
    const char * GetAdminStateString() const;
    void SetParentMO(shared_ptr<ManagedObject> parent);
    shared_ptr<ManagedObject> GetParentMO() const;
    
    /**
     * Op state will be dependent on the specific functionality of
     * the object so will normally be overridden.
     * Default is to return 'disabled' if locked, 'enabled' if unlocked.
     */
    virtual OpState GetOpState() const;
    virtual string GetOpStateString() const;
    
    /**
     * Present as string for debug.
     */
    string ToString() const;
    
protected:
    
private:
    // Administrative state.
    AdminState m_adminState;

    // Parent object
    shared_ptr<ManagedObject> m_parent;
};

}

#endif
