/*
 * NTPPacket.h
 *
 *  Created on: 26-Aug-2009
 *      Author: jouroussoff
 */

#ifndef NTPPACKET_H_
#define NTPPACKET_H_
///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <netinet/ip.h>
#include <unistd.h>

#include <3waytypes.h>
#include "FNTPTime.h"

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
using namespace boost;
using namespace threeway;

struct NtpData
{
    unsigned char mode :3;
    unsigned char vn :3;
    unsigned char li :2;
    unsigned char stratum;
    char poll;
    char precision;
    unsigned long root_delay;
    unsigned long root_dispersion;
    unsigned long reference_identifier;
    unsigned long reference_timestamp_secs;
    unsigned long reference_timestamp_frac;
    unsigned long originate_timestamp_secs;
    unsigned long originate_timestamp_frac;
    unsigned long receive_timestamp_secs;
    unsigned long receive_timestamp_frac;
    unsigned long transmit_timestamp_secs;
    unsigned long transmit_timestamp_frac;
};
///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////
//NTP packet structure. This is the actual packet that is sent to and received from the NTP server
class NtpPacket
{
    static const u32 KOD_MSG_SIZE = 4;
    static const u32 MAX_STRATUM = 1;

public:

    NtpPacket() {bzero(&m_data,sizeof(NtpData));}
    ~NtpPacket() {};

    NtpData* GetNTPData() {return &m_data;}

    void InitNow()
    {
        m_data.vn = 4;
        m_data.mode = 3;
        m_data.originate_timestamp_secs = htonl(time(0) + NTP_EPOCH);
        m_data.poll = 10;
        m_data.stratum = 1;
    }

    void OutputPacketToDebug()
    {
        TRACE_PRINTF("mode = %d\n vn = %d\n li = %d\n stratum = %d\n poll = %d\n prec = %d\n root delay = %d\n root dispersion = %d\n reference identifier = %d\n", ntohl(m_data.mode),ntohl(m_data.vn),ntohl(m_data.li),ntohl(m_data.stratum),ntohl(m_data.poll),ntohl(m_data.precision),ntohl(m_data.root_delay),ntohl(m_data.root_dispersion),ntohl(m_data.reference_identifier));
        TRACE_PRINTF("%u.%u  %u.%u  %u.%u  %u.%u", ntohl(m_data.reference_timestamp_secs), ntohl(m_data.reference_timestamp_frac), ntohl(m_data.originate_timestamp_secs), ntohl(m_data.originate_timestamp_frac), ntohl(m_data.receive_timestamp_secs), ntohl(m_data.receive_timestamp_frac), ntohl(m_data.transmit_timestamp_secs), ntohl(m_data.transmit_timestamp_frac));
    }

    bool IsItAKODPacket()
    {
        if ((m_data.stratum == 0) && (m_data.li == 3))
        {
            char kodMsg[KOD_MSG_SIZE + 1];
            memcpy(kodMsg, (char*) (&(m_data.reference_identifier)), KOD_MSG_SIZE);
            kodMsg[KOD_MSG_SIZE] = '\0';
            TRACE_PRINTF("Kiss of Death message = %s",kodMsg);
            OutputPacketToDebug();
            return true;
        }
        return false;
    }

    bool CheckStratumCorrect(void)
    {
        bool StratumCorrectValue = false;
        if((m_data.stratum > MAX_STRATUM))
        {
            TRACE_PRINTF("Statum = %d, max stratum = %d",m_data.stratum,MAX_STRATUM);
            StratumCorrectValue = false;
        }
        else
        {
            StratumCorrectValue =  true;
        }
        return StratumCorrectValue;
    }

    u8* GetPktBuff()
    {
        //return ((u8*)this);
        return ((u8*)&m_data);
    }

    long double Gett2(void)
    {
        return(NTPtoLongDouble(m_data.receive_timestamp_secs,m_data.receive_timestamp_frac));
    }

    long double Gett3(void)
    {
        return(NTPtoLongDouble(m_data.transmit_timestamp_secs,m_data.transmit_timestamp_frac));
    }

    NtpData m_data;
};

#endif /* NTPPACKET_H_ */
