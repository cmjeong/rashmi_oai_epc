///////////////////////////////////////////////////////////////////////////////
//
// RegisterEntityReq
//
// See header file for documentation.
//
// Copyright radisys Limited
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

#include "RegisterEntityReq.h"

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

s32 RegisterEntityReq::Serialise(u8* data, u32 dataMaxBytes) const
{
    u8 * start = data;

    u32 count = m_entities.size();

    if ((sizeof(MessagingEntity) * count) <= dataMaxBytes)
    {
        for ( MessagingEntities::const_iterator it = m_entities.begin();
              it != m_entities.end();
              it++
            )
        {
            SerialiseIt(*it, data);
        }
    }

    return (data - start);
}

bool RegisterEntityReq::DeSerialise(const u8* data, u32 dataLen)
{
    bool decode = (0 == (dataLen % sizeof(MessagingEntity)));

    if (decode)
    {
        u32 count = dataLen / sizeof(MessagingEntity);

        for (u32 i = 0; i < count; i++)
        {
            MessagingEntity entity;

            DeSerialiseIt(entity, data);

            m_entities.push_back(entity);
        }
    }

    return decode;
}

string RegisterEntityReq::ToString() const
{
    ostringstream stream;

    stream << "RegisterEntityReq: ";

    for ( MessagingEntities::const_iterator it = m_entities.begin();
          it != m_entities.end();
          it++
        )
    {
        stream << MessagingEntityToString(*it) << ",";
    }

    return stream.str();
}
