///////////////////////////////////////////////////////////////////////////////
//
// IMEI.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <cstring>
#include <sstream>

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "IMEI.h"

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

IMEI::IMEI() :
    m_isSet(false)
{
    memset(m_imei, 0, sizeof(m_imei));
}

IMEI::IMEI(const u8 * imei) :
    m_isSet(true)
{
    RSYS_ASSERT(imei != NULL);

    TRACE_PRINTF("Constructing threeway::IMEI, d0=%"PRIu8", d1=%"PRIu8", ...", imei[0], imei[1]);
    memcpy(m_imei, imei, sizeof(m_imei));
}

IMEI::IMEI(const string& imei) :
    m_isSet(true)
{
    RSYS_ASSERT_PRINTF(imei.size() == IMEI_NUM_DIGITS, "%s", imei.c_str());

    for(u8 i = 0; i < IMEI_NUM_DIGITS; i++)
    {
        RSYS_ASSERT_PRINTF((imei.at(i) >= '0') && (imei.at(i) <= '9'), "%s", imei.c_str());
        m_imei[i] = (u8)(imei.at(i) - '0');
    }
}

IMEI::~IMEI()
{
}

void IMEI::SetDigits(const u8* imeiDigits)
{
    RSYS_ASSERT(imeiDigits != NULL);

    memcpy(m_imei, imeiDigits, sizeof(m_imei));
    m_isSet = true;
}

bool IMEI::operator==(const IMEI& rhs) const
{
    if(m_isSet != rhs.m_isSet)
    {
        RETURN(false);
    }

    return (memcmp(m_imei, rhs.m_imei, sizeof(m_imei)) == 0);
}

bool IMEI::operator!=(const IMEI& rhs) const
{
    return (!(*this == rhs));
}

void IMEI::SetImeiPacked(const u8 *imeiValue)
{
    RSYS_ASSERT(imeiValue != NULL);

    u8 imeiDigit = 0;

    // We don't need the check nibble, hence the -1 on length.
    for(u8 packedIndex = 0; ((packedIndex < IMEI_PACKED_NUM_BYTES - 1) && (imeiDigit < IMEI_NUM_DIGITS - 1)); packedIndex++)
    {
       m_imei[imeiDigit++] = ((imeiValue[packedIndex] >> 4) & 0x0f);
       m_imei[imeiDigit++] = (imeiValue[packedIndex] & 0x0f);
    }

    m_isSet = true;
}

void IMEI::GetImeiPacked(u8 *imeiValue, u32 imeiValueSize) const
{
    RSYS_ASSERT(m_isSet);
    RSYS_ASSERT(imeiValue != NULL);
    RSYS_ASSERT(imeiValueSize >= IMEI_PACKED_NUM_BYTES);  // Room for 60 bits, 7.5 bytes

    // Copy the actual IMEI value in packed form.
    u8 imeiDigit = 0;
    for(u8 packedIndex = 0; packedIndex < IMEI_NUM_DIGITS; packedIndex += 2)
    {
        imeiValue[imeiDigit++] = ((m_imei[packedIndex] & 0x0f) << 4) + (m_imei[packedIndex+1] & 0x0f);
    }

    // Last byte contains 1 nibble of dummy check digit.
    imeiValue[imeiDigit] = 0;
}

string IMEI::ToString() const
{
    ostringstream stream;

    if(m_isSet)
    {
        for(u8 i = 0; i < IMEI_NUM_DIGITS; i++)
        {
            stream << (char)(m_imei[i] + '0');
        }
    }
    else
    {
        stream << "notset";
    }

    return stream.str();
}
