///////////////////////////////////////////////////////////////////////////////
//
// TcpClientLayerTest.h
//
// Unit tests for TcpClientLayer class.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __TcpClientLayerTest_h_
#define __TcpClientLayerTest_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <unistd.h>
#include <string.h>

#include <cppunit/TestCase.h>
#include <iostream>
#include <string>

#include <3waytypes.h>
#include <system/Trace.h>
#include <comms/TcpClientLayer.h>
#include <comms/TcpSocket.h>

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////
class TcpServerSocketListener : public TcpServerRxInterface
{
public:
    s32 m_sendFd;
    void HandleNewTcpSock(s32 fd) { m_sendFd = fd; }
    s32 HandleTcpRx(s32 fd)
    {
        u8 packet[2048];
        int packetLen = recv(fd, packet, sizeof(packet), 0);
        cout << "Client received TCP packet on FD=" << fd << ", packet length=" << packetLen << ": ";
        if(packetLen > 0)
        {
            s32 i = 0;
            while(i < packetLen)
            {
                if(isprint(packet[i]))
                {
                    cout << (char)packet[i];
                }
                else
                {
                    cout << '.';
                }
                i++;
            }
        }
        cout << endl;
        return (packetLen > 0 ? 0 : -1);
    }

    void HandleTcpDisconnect(s32 fd)
    {
        cout << "TCP disconnect on FD=" << fd << endl;
    }
};

class TcpClientLayerTest;

class TestUpperLayer : public ProtocolLayer
{
public:
    TestUpperLayer(TcpClientLayerTest& tcpClientLayerTest);

    virtual void ReceiveFromHigherLayer(shared_ptr<PDU> pdu);
    virtual void ReceiveFromLowerLayer(shared_ptr<PDU> pdu);

private:
    TcpClientLayerTest& m_tcpClientLayerTest;

};

class TcpClientLayerTest : public CppUnit::TestCase
{
public:
    void ReceiveFromLowerLayer(shared_ptr<PDU> pdu)
    {
        cout << "PDU received from TCP client layer: " << pdu->ToString() << endl;

        shared_ptr<TcpMgmtPDU> mgmtPDU = dynamic_pointer_cast<TcpMgmtPDU>(pdu);
        shared_ptr<SimplePDU> tcpPacketPDU = dynamic_pointer_cast<SimplePDU>(pdu);

        switch(m_messageCount++)
        {
            case 0:
                // First message should be CONNECT-CNF.
                cout << "Validate first message is CONNECT-CNF with correct parameters." << endl;
                if(mgmtPDU != NULL)
                {
                    CPPUNIT_ASSERT_MESSAGE("Check first PDU is CONNECT-CNF",
                            mgmtPDU->GetMessageType() == TcpMgmtPDU::CONNECT_CNF);
                    CPPUNIT_ASSERT_MESSAGE("Check CONNECT-CNF contains correct IP address",
                            mgmtPDU->GetRemoteIpAddress() == m_remoteIpAddress);
                    CPPUNIT_ASSERT_MESSAGE("Check CONNECT-CNF contains correct port",
                            mgmtPDU->GetRemotePort() == m_remotePort);
                    m_connectionId1 = mgmtPDU->GetConnectionId();
                }
                else
                {
                    CPPUNIT_FAIL("First PDU is not TcpMgmtPDU");
                }
                break;
            case 1:
                // Second message should be a data packet containing SSH server response string.
                cout << "Validate second message is SSH response data packet." << endl;
                // TODO - if we get failures here the test runner app Aborts rather than
                // printing the error message.  I believe this is a threading issue.
                if(tcpPacketPDU != NULL)
                {
                    CPPUNIT_ASSERT_MESSAGE("Check connection ID matches",
                            m_connectionId1 == tcpPacketPDU->GetConnectionId());

                    const u8 * packetData =  tcpPacketPDU->GetPacket();
                    for (u32 index = 0; index < sizeof(m_data); index++)
                    {
                        CPPUNIT_ASSERT_MESSAGE("Validate data packet contains the string 'SSH'",
                                packetData[index] == m_data[index]);
                    }
                }
                else
                {
                    CPPUNIT_FAIL("Second PDU is not data packet");
                }
                break;
            case 2:
                // Should be CONNECT-CNF.
                if(mgmtPDU != NULL)
                {
                    m_connectionId2 = mgmtPDU->GetConnectionId();
                }
                else
                {
                    CPPUNIT_FAIL("Third PDU is not TcpMgmtPDU");
                }
                break;
            default:
                break;
        }
    }

    void runTest()
    {
        cout << endl << endl
             << "********************" << endl
             << "TcpClientLayer tests" << endl
             << "********************" << endl << endl;

        //Start server
        m_remotePort = 1977;

        cout << "Create server socket on " << m_remotePort << endl;
        shared_ptr<TcpServerSocketListener> localListener(new TcpServerSocketListener);
        TcpSocket tcpServerSocket(m_remotePort, localListener.get());
        tcpServerSocket.StartReceiving();
        sleep(1);

        // Start the client side which we are testing here
        m_messageCount = 0;
        shared_ptr<TestUpperLayer> testUpperLayer(new TestUpperLayer(*this));

        cout << "Constructing TcpClientLayer" << endl;
        shared_ptr<TcpClientLayer> tcpClientLayer(new TcpClientLayer);

        testUpperLayer->SetLowerLayer(tcpClientLayer);
        tcpClientLayer->SetHigherLayer(testUpperLayer);


        m_remoteIpAddress = "127.0.0.1";
        shared_ptr<TcpMgmtPDU> connectReq1( new TcpMgmtPDU(m_remoteIpAddress, m_remotePort) );

        tcpClientLayer->ReceiveFromHigherLayer(connectReq1);
        sleep(2); // This gives the receiving socket a chance to start up
        // TODO : By inserting a delay here it is giving the server socket more of a chance to start up. Ideally we should not be using
        // the server socket at the moment and hence not need the sleep.

        // Send some data
        s32 sendResult;
        sendResult = tcpServerSocket.TcpSend(m_data, 3, localListener->m_sendFd);
        TRACE_PRINTF("sendResult: %"PRId32" %s", sendResult, sendResult < 0 ? strerror(errno) : "OK" );
        CPPUNIT_ASSERT_MESSAGE("Check packet sent OK", sendResult > 0);

        sleep(1);

        // Make another connection but disconnect it ourselves instead of waiting
        // for the destructor.
        shared_ptr<TcpMgmtPDU> connectReq2( new TcpMgmtPDU(m_remoteIpAddress, m_remotePort) );
        tcpClientLayer->ReceiveFromHigherLayer(connectReq2);
        cout << "TCP Client Layer:" << endl << tcpClientLayer->ToString() << endl;

        sleep(1);

        // Disconnect it.
        shared_ptr<TcpMgmtPDU> disconnectReq( new TcpMgmtPDU(TcpMgmtPDU::DISCONNECT_REQ, m_connectionId2) );
        tcpClientLayer->ReceiveFromHigherLayer(disconnectReq);
        cout << "TCP Client Layer:" << endl << tcpClientLayer->ToString() << endl;

        sleep(1);

        cout << "Deleting TcpClientLayer" << endl;
        tcpServerSocket.StopReceiving();

#if 0
        // TODO for some reason this causes UdpMessenger unit tests to fail with
        // seg fault when calling CPPUNIT_ASSERT_MESSAGE!
        testUpperLayer->RemoveLowerLayer();
        tcpClientLayer->RemoveHigherLayer();
#endif

        tcpClientLayer.reset();
        cout << "END OF TEST" << endl;
        fflush(stdout);
    }

private:
    static const u8 m_data[3];
    u32 m_messageCount;
    IPv4Address m_remoteIpAddress;
    u16 m_remotePort;
    u32 m_connectionId1;
    u32 m_connectionId2;
};

const u8 TcpClientLayerTest::m_data[] = {'S', 'S', 'H'};

TestUpperLayer::TestUpperLayer(TcpClientLayerTest& tcpClientLayerTest) :
    m_tcpClientLayerTest(tcpClientLayerTest)
{
}

void TestUpperLayer::ReceiveFromHigherLayer(shared_ptr<PDU> pdu)
{
}

void TestUpperLayer::ReceiveFromLowerLayer(shared_ptr<PDU> pdu)
{
    m_tcpClientLayerTest.ReceiveFromLowerLayer(pdu);
}

#endif
