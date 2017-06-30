///////////////////////////////////////////////////////////////////////////////
//
// UpdateInUseEutraCellList.cpp
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

#include "UpdateInUseEutraCellList.h"

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

UpdateInUseEutraCellList::UpdateInUseEutraCellList() :
    m_MsgType(0),
    m_EutrCellCfg(NULL)
{
    ENTER();
    EXIT();
}

UpdateInUseEutraCellList::UpdateInUseEutraCellList(u32 msgType, void *data) :
    m_MsgType(msgType),
    m_EutrCellCfg(data)
{
    ENTER();
    EXIT();
}

s32 UpdateInUseEutraCellList::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    RSYS_ASSERT(dataMaxBytes >= 8);

    // Serialise all the members.
    u8* serialisedData = data;

    SerialiseIt(m_MsgType, serialisedData);
    SerialiseIt(m_EutrCellCfg, serialisedData);

    RETURN(serialisedData - data);
}

bool UpdateInUseEutraCellList::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    RSYS_ASSERT(dataLen == 8);

    DeSerialiseIt(m_MsgType, data);
    DeSerialiseIt(m_EutrCellCfg, data);
    RETURN(true);
}

std::string UpdateInUseEutraCellList::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "UpdateInUseEutraCellList: msgTyep=" << m_MsgType<< ", Data=" << m_EutrCellCfg;

    RETURN(stream.str());
}

void *UpdateInUseEutraCellList::GetEutaCellCfg()
{
    ENTER();
    if(m_EutrCellCfg == NULL)
    {
      TRACE_PRINTF("UpdateInUseEutraCellList: m_UtraCellCfg not intialised NULL Pointer\n");
    }
    RETURN(m_EutrCellCfg);
}
