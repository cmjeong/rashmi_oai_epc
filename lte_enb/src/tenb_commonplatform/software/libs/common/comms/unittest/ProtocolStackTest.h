///////////////////////////////////////////////////////////////////////////////
//
// ProtocolStackTest.h
//
// Unit tests for ProtocolStack class.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ProtocolStackTest_h_
#define __ProtocolStackTest_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <unistd.h>

#include <cppunit/TestCase.h>
#include <iostream>

#include <3waytypes.h>
#include <system/Trace.h>
#include <comms/SerialisingProtocolLayer.h>
#include <comms/SerialisingProtocolRelay.h>
#include <comms/ProtocolStack.h>

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class TestSerialisingProtocolLayer : public SerialisingProtocolLayer
{
protected:
    void ProcessPdu(shared_ptr<PDU> pdu, PduDirection direction)
    {
        cout << ToString() << ": Received a PDU!" << endl;
        SendOn(pdu, direction);
    }

    void ProcessTimerExpiry(TimerHandle expiredTimer)
    {
        cout << ToString() << ": Timer expired, handle=" << expiredTimer << endl;
    }
};

class ProtocolStackTest : public CppUnit::TestCase
{
public:
    void runTest()
    {
        cout << endl << endl
             << "*******************" << endl
             << "ProtocolStack tests" << endl
             << "*******************" << endl << endl;

        shared_ptr<TestSerialisingProtocolLayer> layer1(new TestSerialisingProtocolLayer);
        shared_ptr<TestSerialisingProtocolLayer> layer2(new TestSerialisingProtocolLayer);
        ProtocolStack stack1;
        ProtocolStack stack2;
        
        layer1->SetLayerName("Layer 1");
        layer2->SetLayerName("Layer 2");

        stack1.SetStackName("Stack 1");
        stack1.AddLayer(layer1, ProtocolStack::TOP_OF_STACK);

        stack2.SetStackName("Stack 2");
        stack2.AddLayer(layer2, ProtocolStack::TOP_OF_STACK);
        
        shared_ptr<SerialisingProtocolRelay> relay1(new SerialisingProtocolRelay(stack1, stack2));
        relay1->SetLayerName("Test Relay");
        
        shared_ptr<PDU> pdu(new SimplePDU);
        stack1.Receive(pdu);
        pdu.reset();

        // Wait for threads to run.
        sleep(1);

        fflush(stdout);
        
    }

private:
};

#endif
