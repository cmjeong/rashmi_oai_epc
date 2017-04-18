///////////////////////////////////////////////////////////////////////////////
//
// FapMO.h
//
// FAP managed object class.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __FapMO_h_
#define __FapMO_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/ManagedObject.h>
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class FapMO : public threeway::ManagedObject
{
protected:
    /**
     * Singleton so protected constructor.
     */
    FapMO();

public:
    /**
     * Construction / destruction.
     */
    static FapMO& GetInstance();
    virtual ~FapMO();

    /**
     * Override setting FAP admin state.
     */
    virtual void SetAdminState(AdminState adminState);

    /**
     * Implement FAP op state.  This will be based on e.g. state of the iu link.
     */
    virtual threeway::ManagedObject::OpState GetOpState() const { return m_opState; };

    /**
     * Iu (Sigtran) or Iuh (HNBAP/RUA)?
     */
    void SetIuhEnabled(bool iuhEnabled);
    
    /**
     * Set the state of the Iu link based on domain (CS / PS).
     */
    void SetIuCsEnabled(bool iuCsEnabled);
    void SetIuPsEnabled(bool iuPsEnabled);
    
    void SetL1L2InNodeBState(bool inNodeBState);
    void SetNetworkEnabled(bool networkEnabled);
    void SetTr069Enabled (bool tr069Enabled);
    void SetFreqSyncEnabled (bool freqSyncEnabled);
    void SetFreqSyncIsRequired (bool freqSyncIsRequired);
    void SetServiceApiDisableRadio(bool disableRadio);
    void SetFapIsOverTemperature(bool overTemperature);
    void SetHwConfiguredOk(bool hwConfiguredOk);
    void SetSctpEnabled(bool sctpEnabled);
    void SetHnbapRuaEnabled(bool hnbapRuaEnabled);
    void SetSmEnabled(bool smEnabled);

    /**
     * Present as string for debug.
     */
    string ToString() const;

protected:

private:
    /**
     * Update our op state value and dump out trace on change.
     */
    void UpdateOpState(const char * modificationInfo);

    // Singleton instance.
    static FapMO* s_instance;

    ManagedObject::OpState m_opState;
    bool m_iuhEnabled;
    bool m_iuCsEnabled;
    bool m_iuPsEnabled;
    bool m_inNodeBState;
    bool m_networkEnabled;
    bool m_tr069Enabled;
    bool m_freqSyncEnabled;
    bool m_freqSyncIsRequired;
    bool m_serviceApiDisableRadio;
    bool m_overTemperature;
    bool m_hwConfiguredOk;
    bool m_sctpEnabled;
    bool m_hnbapRuaEnabled;
    bool m_smEnabled;
};

#endif
