///////////////////////////////////////////////////////////////////////////////
//
// UpdateInUseUtraCellList.cpp
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
#include <system/SerialisationUtils.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "UpdateInUseUtraCellList.h"

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

UpdateInUseUtraCellList::UpdateInUseUtraCellList() :
    m_MsgType(0),
    m_UtraCellCfg(NULL)
{
    ENTER();
    EXIT();
}

UpdateInUseUtraCellList::UpdateInUseUtraCellList(u32 msgType, void *data) :
    m_MsgType(msgType),
    m_UtraCellCfg(data)
{
    ENTER();
    EXIT();
}

s32 UpdateInUseUtraCellList::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    RSYS_ASSERT(dataMaxBytes >= 8);

    // Serialise all the members.
    u8* serialisedData = data;

    SerialiseIt(m_MsgType, serialisedData);
    SerialiseIt(m_UtraCellCfg, serialisedData);

    RETURN(serialisedData - data);
}

bool UpdateInUseUtraCellList::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    RSYS_ASSERT(dataLen == 8);

    DeSerialiseIt(m_MsgType, data);
    DeSerialiseIt(m_UtraCellCfg, data);
    RETURN(true);
}

std::string UpdateInUseUtraCellList::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "msgTyep=" << m_MsgType<< ", Data=" << m_UtraCellCfg;

    RETURN(stream.str());
}
void *UpdateInUseUtraCellList::GetUtaCellCfg()
{
    ENTER();
    if(m_UtraCellCfg == NULL)
    {
      TRACE_PRINTF("UpdateInUseUtraCellList: m_UtraCellCfg not intialised NULL Pointer\n");
    }
    RETURN(m_UtraCellCfg);
}

