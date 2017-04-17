///////////////////////////////////////////////////////////////////////////////
//
// MfOpStateInformInd.h
//
// Message for informing OAM of a change in operational state of a managed
// "fing".
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MfOpStateInformInd_h_
#define __MfOpStateInformInd_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include <system/ManagedObject.h>
#include <system/SerialisationUtils.h>
#include <platform/ManagedFing.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class MfOpStateInformInd : public threeway::Serialisable
{
public:
    /**
     * Construction / destruction.
     */
    MfOpStateInformInd();
    MfOpStateInformInd(ManagedFing managedFing,
                       threeway::ManagedObject::OpState opState,
                       u32 additionalInfoValue,
                       const char * additionalInfoString);
    MfOpStateInformInd(ManagedFing managedFing,
                       threeway::ManagedObject::OpState opState,
                       threeway::ManagedObject::AdminState adminState,
                       u32 additionalInfoValue,
                       const char * additionalInfoString);
    virtual ~MfOpStateInformInd();

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_MF_OP_STATE_INFORM_IND; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Accessors.
     */
    ManagedFing                         GetManagedFing() const          { return m_managedFing; }
    threeway::ManagedObject::OpState    GetOpState() const              { return m_opState; }
    bool                                IsAdminStatePresent() const     { return m_adminStatePresent; }
    threeway::ManagedObject::AdminState GetAdminState() const;
    string                              GetAdditionalInfoString() const { return m_additionalInfoString; }
    u32                                 GetAdditionalInfoValue() const  { return m_additionalInfoValue; }
    
    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;
    
private:
    static const u32 ADDITIONAL_INFO_MAX_LEN = 500;
    
    /**
     * Optionally set the additional info string and validate length.
     */
    void SetAdditionalInfoString(const char * additionalInfoString);

    // The MF reporting its state.
    ManagedFing m_managedFing;

    // Operational state of the MF.
    threeway::ManagedObject::OpState m_opState;

    // Admin state of the MF - useful if MF doesn't immediately transition to requested state due to async events.
    // NOTE: An MF if LOCKED should immediately, or in a short and guaranteed period (< few secs), transition to LOCKED state.
    //             if SHUTDOWN may take an indeterminate amount of time to transition to LOCKED as it waits for ongoing service to complete.
    threeway::ManagedObject::AdminState m_adminState;
    bool m_adminStatePresent;

    // Additional info.
    u32 m_additionalInfoValue;
    string m_additionalInfoString;
};

#endif
