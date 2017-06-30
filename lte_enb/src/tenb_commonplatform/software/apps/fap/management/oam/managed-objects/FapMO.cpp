///////////////////////////////////////////////////////////////////////////////
//
// FapMO.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
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

#include "FapMO.h"
#include "oam_env.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Static Data
///////////////////////////////////////////////////////////////////////////////

FapMO* FapMO::s_instance = NULL;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

FapMO::FapMO() :
    m_opState(OP_STATE_DISABLED),
    m_iuhEnabled(false),
    m_iuCsEnabled(false),
    m_iuPsEnabled(false),
    m_inNodeBState(false),
    m_networkEnabled(false),
    m_tr069Enabled(false),
    m_freqSyncEnabled(false),
    m_freqSyncIsRequired(true),
    m_serviceApiDisableRadio(false),
    m_overTemperature(false),
    m_hwConfiguredOk(false),
    m_sctpEnabled(false),
    m_hnbapRuaEnabled(false),
    m_smEnabled(false)
{
    ENTER();

    UpdateOpState("Init");

    // TODO - set op state in MIB

    EXIT();
}

FapMO::~FapMO()
{
    ENTER();
    EXIT();
}

FapMO& FapMO::GetInstance()
{
    if(s_instance == NULL)
    {
        s_instance = new FapMO();
    }

    return *s_instance;
}

void FapMO::SetAdminState(AdminState adminState)
{
    ENTER();

    ManagedObject::SetAdminState(adminState);
    UpdateOpState("AdminState");

    EXIT();
}

void FapMO::UpdateOpState(const char * modificationInfo)
{
    ENTER();

    ManagedObject::OpState previousOpState = m_opState;

	bool iuOperational = m_iuCsEnabled || m_iuPsEnabled;
	bool syncFlag = m_freqSyncEnabled || !m_freqSyncIsRequired;
	bool hbs2IuOperational = m_tr069Enabled && m_sctpEnabled && iuOperational && m_inNodeBState && m_networkEnabled && syncFlag;

	if(m_iuhEnabled)
	{
	    hbs2IuOperational &= m_hnbapRuaEnabled;
	}

        /*
	bool operational = (!oamEnv_isProductHbs2Iu() || hbs2IuOperational )
                       && !m_overTemperature && !m_serviceApiDisableRadio && m_hwConfiguredOk;
        */

        bool dependentOpStates = m_tr069Enabled && m_networkEnabled;
        bool operational =  (!oamEnv_isProductHbs2Iu() || dependentOpStates ) && m_smEnabled;

	bool unlocked = (GetAdminState() == ManagedObject::ADMIN_STATE_UNLOCKED);

    // OperState enabled if...
    if( unlocked && operational )
    {
        m_opState = ManagedObject::OP_STATE_ENABLED;
    }
    else
    {
        m_opState = ManagedObject::OP_STATE_DISABLED;
    }

    if(m_opState != previousOpState)
    {
        TRACE_PRINTF("FapMO OpState Change (%s changed): %s", modificationInfo, ToString().c_str());
        // TODO - set op state in MIB
    }
}

void FapMO::SetSmEnabled(bool smEnabled)
{
    m_smEnabled = smEnabled;
    UpdateOpState("StackManager");
}

void FapMO::SetIuhEnabled(bool iuhEnabled)
{
    m_iuhEnabled = iuhEnabled;
    UpdateOpState("IuhMode");
}

void FapMO::SetIuCsEnabled(bool iuCsEnabled)
{
    m_iuCsEnabled = iuCsEnabled;
    UpdateOpState("IuCs");
}

void FapMO::SetIuPsEnabled(bool iuPsEnabled)
{
    m_iuPsEnabled = iuPsEnabled;
    UpdateOpState("IuPs");
}

void FapMO::SetL1L2InNodeBState(bool inNodeBState)
{
    m_inNodeBState = inNodeBState;
    UpdateOpState("L1L2");
}

void FapMO::SetNetworkEnabled(bool networkEnabled)
{
    m_networkEnabled = networkEnabled;
    UpdateOpState("Network");
}

void FapMO::SetTr069Enabled(bool tr069Enabled)
{
    m_tr069Enabled = tr069Enabled;
    UpdateOpState("TR069");
}

void FapMO::SetFreqSyncEnabled(bool freqSyncEnabled)
{
    m_freqSyncEnabled = freqSyncEnabled;
    UpdateOpState("FreqSync");
}

void FapMO::SetFreqSyncIsRequired(bool freqSyncIsRequired)
{
    m_freqSyncIsRequired = freqSyncIsRequired;
    UpdateOpState("FreqSyncRequired");
}

void FapMO::SetServiceApiDisableRadio(bool disableRadio)
{
    m_serviceApiDisableRadio = disableRadio;
    UpdateOpState("ServiceAPI");
}

void FapMO::SetFapIsOverTemperature(bool overTemperature)
{
    m_overTemperature = overTemperature;
    UpdateOpState("Temperature");
}

void FapMO::SetHwConfiguredOk(bool hwConfiguredOk)
{
    m_hwConfiguredOk = hwConfiguredOk;
    UpdateOpState("HwConfiguredOk");
}

void FapMO::SetSctpEnabled(bool sctpEnabled)
{
    m_sctpEnabled = sctpEnabled;
    UpdateOpState("Sctp");
}

void FapMO::SetHnbapRuaEnabled(bool hnbapRuaEnabled)
{
    m_hnbapRuaEnabled = hnbapRuaEnabled;
    UpdateOpState("HnbapRua");
}

string FapMO::ToString() const
{
    ostringstream stream;

    stream << ManagedObject::ToString();
    /*
    stream << ": IuMode=" << (m_iuhEnabled ? "Iuh" : "Iu")
           << ", IuCS=" << (m_iuCsEnabled ? "Enabled" : "*Disabled*")
           << ", IuPS=" << (m_iuPsEnabled ? "Enabled" : "*Disabled*")
           << ", L1L2=" << (m_inNodeBState ? "NodeB" : "*NotNodeB*")
           << ", Network=" << (m_networkEnabled ? "Enabled" : "*Disabled*")
           << ", TR069=" << (m_tr069Enabled ? "Enabled" : "*Disabled*")
           << ", FreqSync=" << (m_freqSyncEnabled ? "InSync" : (m_freqSyncIsRequired ? "*NotInSync*" : "NotInSyncButNotRequired"))
           << ", ServiceAPI=" << (m_serviceApiDisableRadio ? "*DisableRadio*" : "TryToEnableRadio")
           << ", Temperature=" << (m_overTemperature ? "*OverTemp*" : "TempOK")
           << ", Hardware=" << (m_hwConfiguredOk ? "Configured" : "*NotConfigured*")
           << ", Sctp=" << (m_sctpEnabled ? "Enabled" : "*Disabled*");
    */ 

    stream << ", TR069=" << (m_tr069Enabled ? "Enabled" : "*Disabled*");
    if(m_iuhEnabled)
    {
        stream << ", HnbapRua=" << (m_hnbapRuaEnabled ? "Enabled" : "*Disabled*");
    }

    return stream.str();
}
