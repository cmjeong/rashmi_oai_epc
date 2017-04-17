///////////////////////////////////////////////////////////////////////////////
//
// IkeTunnelCreateCnf
//
// See header file for documentation.
//
// Copyright radisys
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Trace.h>
#include <system/SerialisationUtils.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "IkeTunnelCreateCnf.h"

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace threeway;

s32 IkeTunnelCreateCnf::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    u8 * start = data;

    if (4 <= dataMaxBytes)
    {
        SerialiseIt(m_id, data);
    }

    RETURN(data - start);
}

bool IkeTunnelCreateCnf::DeSerialise(
    const u8 *  data,
    u32         dataLen
)
{
    ENTER();

    bool decode = (4 <= dataLen);

    if (decode)
    {
        DeSerialiseIt(m_id, data);
    }

    RETURN(decode);
}

string IkeTunnelCreateCnf::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "IkeTunnelCreateCnf: " << " id=" << m_id;

    RETURN(stream.str());
}
