///////////////////////////////////////////////////////////////////////////////
//
// MfManager.h
//
// Manager for the "Managed Fings" i.e. modules, apps, whatever that adhere
// to the MF interface.  Allows MFs to be registered, their status queried
// and their admin state changed.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MfManager_h_
#define __MfManager_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/ManagedObject.h>
#include <messaging/transport/Messenger.h>
#include <platform/ManagedFing.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class MfManager
{
public:
    /**
     * Default constructor.
     */
    MfManager(threeway::SendMessageInterface& sendMessageInterface) :
        m_sendMessageInterface(sendMessageInterface) {};

    /**
     * Destructor.
     */
    ~MfManager() {};

    /**
     * Register an MF including its messaging entity.
     */
    void RegisterMf(ManagedFing mf, MessagingEntity mfEntity);

    /**
     * Record the operational state of an MF.
     * MF must already be registered.
     */
    void UpdateMfOpState(ManagedFing mf,
                         threeway::ManagedObject::OpState opState,
                         threeway::ManagedObject::AdminState adminState,
                         const std::string& additionalInfo);
    void UpdateMfOpState(ManagedFing mf,
                         threeway::ManagedObject::OpState opState,
                         const std::string& additionalInfo);

    /**
     * Set admin state of an MF.  If the MF is registered then this will send
     * a message to it to change its admin state.
     *
     * \return true on success, false otherwise
     */
    bool SetMfAdminState(ManagedFing mf, threeway::ManagedObject::AdminState adminState) const;

    /**
     * Get as string for debug/trace.
     * Will list out registered MFs.
     */
    std::string ToString() const;

private:

    // We need to be able to send messages to change MF admin state.
    threeway::SendMessageInterface& m_sendMessageInterface;

    // Information about a registered MF.
    typedef struct
    {
        MessagingEntity m_messagingEntity;
        threeway::ManagedObject::OpState m_opState;
        threeway::ManagedObject::AdminState m_adminState;
        bool m_adminStateValid;
        std::string m_additionalInfo;
    } ManagedFingDescriptor;

    // The list of MFs that we've got registered - as detected by setting their op state.
    typedef std::map< ManagedFing, ManagedFingDescriptor > RegisteredManagedFings;
    RegisteredManagedFings m_mfs;

};

#endif
