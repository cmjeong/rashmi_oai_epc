///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNlmErrInd.cpp 28519 2010-07-21 14:39:46Z mmcternan $
//
// See header file for documentation.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CPhyNlmErrInd.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyNlmErrInd::CPhyNlmErrInd(const CphyNlmErrInd *msg)
{
    m_Struct = *msg;
}

s32 CPhyNlmErrInd::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyNlmErrInd_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyNlmErrInd::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyNlmErrInd_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyNlmErrInd::GetStruct(CphyMessageData *const msg)
{
    msg->nlmErrInd = &m_Struct;

    return GetSerialisationId();
}

string CPhyNlmErrInd::ToString() const
{
    ostringstream stream;
    string errCodeString;

    switch(m_Struct.errCode)
    {
       case NLM_COSC_LOST :
          errCodeString = "COSC Lost";
          break;

       case NLM_COSC_NO_SERVICE :
          errCodeString = "COSC No Service available";
          break;
    }
 
    stream << "CPhyNlmErrInd " << endl;
    stream << "{ error code =" <<     errCodeString << endl;
    stream << "}" << endl;

    return(stream.str());
}

extern "C"
{


s32 CphyNlmErrInd_Serialise(const CphyNlmErrInd *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNlmErrInd))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyNlmErrInd));
    return sizeof(CphyNlmErrInd);
}


s32 CphyNlmErrInd_Deserialise(const u8 *buffer, u32 maxLen, CphyNlmErrInd *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNlmErrInd))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyNlmErrInd));
    return sizeof(CphyNlmErrInd);
}

}

// END OF FILE
