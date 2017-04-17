/*
 * ServerIPInterface.h
 *
 *  Created on: 27-Aug-2009
 *      Author: jouroussoff
 */

#ifndef SERVERIPINTERFACE_H_
#define SERVERIPINTERFACE_H_

enum eServerIPErrors
{
     SERVER_IP_ERROR_NONE,
     SERVER_IP_ERROR_SEND,
     SERVER_IP_ERROR_RECEIVE,
     SERVER_IP_ERROR_SETSOCKOPT,
     SERVER_ERROR_KOD
 };

class ServerIPInterface : public UdpRxInterface
{
public:

    static const u32 NTP_PORT = 123;

    ServerIPInterface():
        m_ntpServerIpAddress("0.0.0.0"),
        m_socketActive(false),
        m_socketAddressValid(false),
        m_socketChanged(true)
        {};
    ~ServerIPInterface(){};
    IPv4Address& GetIPAddr(void);
    void SetIpAddress(const IPv4Address& inremoteIpAddress);
    static bool SetIPSecFGWAddress(const IPv4Address& inFGWIpSecAddress)
    {
        m_fgwIPSecAddress = inFGWIpSecAddress;
        if(m_fgwIPSecAddress == "0.0.0.0")
        {
            m_IPSecEnabled = false;
        }
        else
        {
            m_IPSecEnabled = true;
        }
        return m_IPSecEnabled;
    }
    eServerIPErrors SendGetNTPPacket(NtpPacket* NTPPacket,long double* sendTime,long double* receiveTime);
    bool ReopenSocketIfChanged();
    void InitSocket();
    void HandleUdpRx(s32 fd) {};
    bool GetServerInactive(void) {return (!m_socketActive);}
    bool GetServerValid(void) {return m_socketAddressValid;}
    //shared pointer to the dynamically created UdpSocket that is opened on the NTP server for the NTP packet sending and receiving
    shared_ptr<threeway::UdpSocket> m_ntpSocket;
    //addr of the associated NTP server
    IPv4Address m_ntpServerIpAddress;
    static IPv4Address m_fgwIPSecAddress;
    bool m_socketAddressValid;
    bool m_socketActive;
    bool m_socketChanged;
    static bool m_IPSecEnabled;
};


#endif /* SERVERIPINTERFACE_H_ */
