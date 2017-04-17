///////////////////////////////////////////////////////////////////////////////
//
// MessageUnitTests.h
//
// Unit tests for Message classes.
//
// Copyright radisys Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MessageUnitTests_h_
#define __MessageUnitTests_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <ctype.h>
#include <cppunit/TestCase.h>
#include <string.h>

#include <3waytypes.h>
#include <system/Trace.h>
#include <system/Exception.h>
#include <system/Serialisable.h>
#include <messaging/messages/common/RemCnf.h>
#include <messaging/messages/common/RemReq.h>

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////
#define MAX_LEN_SERIALISED_DATA 3000

class MessageUnitTests : public CppUnit::TestCase
{
public:

    void runTest()
    {
    	u8 data[MAX_LEN_SERIALISED_DATA];

        cout << endl << endl
             << "******************" << endl
             << "Message unit tests" << endl
             << "******************" << endl << endl;

        //
        // Normal cases.
        //
        RemReq remReq, remReqDeserialised;
        remReq.m_remReqParams.numAdjUarfcns = 2;
        remReq.m_remReqParams.numUarfcns = 4;
        remReq.m_remReqParams.scanAdjacentUarfcns = true;
        remReq.m_remReqParams.scanNeighbours = false;
        remReq.m_remReqParams.adjUarfcnsToScan[0] = 12345;
        remReq.m_remReqParams.adjUarfcnsToScan[RemReq::MAX_ADJ_UARFCNS_TO_SCAN - 1] = 54321;
        remReq.m_remReqParams.equivalentPlmns[0].mCC = 212;
        remReq.m_remReqParams.equivalentPlmns[0].mNC = 121;
        remReq.m_remReqParams.equivalentPlmns[RemReq::MAX_EQUIV_PLMNS - 1].mCC = 212;
        remReq.m_remReqParams.equivalentPlmns[RemReq::MAX_EQUIV_PLMNS - 1].mNC = 121;
        remReq.m_remReqParams.uarfcnsToScan[0] = 23456;
        remReq.m_remReqParams.uarfcnsToScan[RemReq::MAX_UARFCNS_TO_SCAN - 1] = 65432;
        remReq.Serialise(data, MAX_LEN_SERIALISED_DATA);
        remReqDeserialised.DeSerialise(data, MAX_LEN_SERIALISED_DATA);
        cout << remReqDeserialised.ToString();
        CPPUNIT_ASSERT_MESSAGE("Conversion of remReq failed", remReqDeserialised.ToString() == remReq.ToString());

        RemCnf remCnf, remCnfDeserialised;
        remCnf.m_remResults.numAdjacentUarfcnCells = 1;
        remCnf.m_remResults.numInterFreqNeighbours = 2;
        remCnf.m_remResults.numInterRatNeighbours = 3;
        remCnf.m_remResults.numIntraFreqNeighbours = 4;
        remCnf.m_remResults.adjacentUarfcnCellDetails[0].pSC = 5;
        remCnf.m_remResults.adjacentUarfcnCellDetails[0].rSCP = 6;
        remCnf.m_remResults.adjacentUarfcnCellDetails[0].uARFCN = 7;
        remCnf.m_remResults.adjacentUarfcnCellDetails[RemCnf::MAX_ADJACENT_CHANNEL_NEIGHBOURS - 1].pSC = 8;
        remCnf.m_remResults.adjacentUarfcnCellDetails[RemCnf::MAX_ADJACENT_CHANNEL_NEIGHBOURS - 1].rSCP = 9;
        remCnf.m_remResults.adjacentUarfcnCellDetails[RemCnf::MAX_ADJACENT_CHANNEL_NEIGHBOURS - 1].uARFCN = 10;
        remCnf.m_remResults.interFreqNeighbourCellDetails[0].uARFCN = 11;
        remCnf.m_remResults.interFreqNeighbourCellDetails[RemCnf::MAX_INTER_FREQ_NEIGHBOURS].uARFCN = 12;
        remCnf.m_remResults.interRatNeighbourCellDetails[0].bCC = 13;
        remCnf.m_remResults.interRatNeighbourCellDetails[RemCnf::MAX_INTER_RAT_NEIGHBOURS].bCC = 14;
        remCnf.m_remResults.intraFreqNeighbourCellDetails[0].mCC = 15;
        remCnf.m_remResults.intraFreqNeighbourCellDetails[RemCnf::MAX_INTRA_FREQ_NEIGHBOURS].mCC = 16;
        remCnf.m_remSucceeded = true;
        remCnf.Serialise(data, MAX_LEN_SERIALISED_DATA);
        remCnfDeserialised.DeSerialise(data, MAX_LEN_SERIALISED_DATA);
        cout << remCnfDeserialised.ToString();
        CPPUNIT_ASSERT_MESSAGE("Conversion of remCnf failed!", remCnfDeserialised.ToString() == remCnf.ToString());

        fflush(stdout);
    }

private:

};

#endif
