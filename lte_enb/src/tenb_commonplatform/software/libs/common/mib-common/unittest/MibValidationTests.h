///////////////////////////////////////////////////////////////////////////////
//
// MibValidationTests.h
//
// Unit tests for MIB attribute validators.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibValidationTests_h_
#define __MibValidationTests_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <cppunit/TestCase.h>

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorSerialNumber.h"
#include "ValidatorIpAddress.h"
#include "ValidatorMacAddress.h"
#include "ValidatorDownlinkUArfcn.h"
#include "ValidatorDownlinkArfcn.h"
#include "ValidatorUmtsBands.h"
#include "ValidatorRemGsmBands.h"
#include "ValidatorPlmnIds.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Test Cases
///////////////////////////////////////////////////////////////////////////////

class MibValidationTests : public CppUnit::TestCase
{
public:
    void runTest()
    {
        cout << endl << endl
             << "***************" << endl
             << "Validator tests" << endl
             << "***************" << endl << endl;

        TRACE_MSG("Testing ValidatorSerialNumber");

        ValidationFailureDescriptor failureDescriptor;

        //
        // Serial Number success cases
        //
        ValidatorSerialNumber validatorSN;

        bool pass = validatorSN.ValidateString("1234", 0, 10, failureDescriptor);
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), pass);

        pass = validatorSN.ValidateString("123456789", 9, 9, failureDescriptor);
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), pass);

        pass = validatorSN.ValidateString("0845400057", 10, 10, failureDescriptor);
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), pass);

        //
        // Serial Number failure cases
        //
        pass = validatorSN.ValidateString("1234", 5, 10, failureDescriptor);
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), !pass);

        pass = validatorSN.ValidateString("1234 ", 0, 10, failureDescriptor);
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), !pass);

        //
        // IP Address success cases
        //
        ValidatorIpAddress validatorIp;

        pass = validatorIp.ValidateString("1.2.3.4", 0, 0, failureDescriptor);
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), pass);

        pass = validatorIp.ValidateString("0.0.0.0", 0, 0, failureDescriptor);
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), pass);

        pass = validatorIp.ValidateString("255.255.255.255", 0, 0, failureDescriptor);
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), pass);

        //
        // IP Address failure cases
        //

        pass = validatorIp.ValidateString("1a.2.3.4", 0, 0, failureDescriptor);
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), !pass);

        pass = validatorIp.ValidateString("100.200.150", 0, 0, failureDescriptor);
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), !pass);

        pass = validatorIp.ValidateString("1234.1.2.3", 0, 0, failureDescriptor);
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), !pass);

        pass = validatorIp.ValidateString("1.2.3..", 0, 0, failureDescriptor);
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), !pass);

        pass = validatorIp.ValidateString("somehost", 0, 0, failureDescriptor);
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), !pass);

        //
        // MAC Address success cases
        //
        ValidatorMacAddress validatorMac;

        pass = validatorMac.ValidateString("01:23:45:67:89:AB", 0, 0, failureDescriptor);
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), pass);

        pass = validatorMac.ValidateString("AB:CD:EF:00:11:22", 0, 0, failureDescriptor);
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), pass);

        //
        // MAC Address failure cases
        //

        pass = validatorMac.ValidateString("AB:CD:EF:00:11:2", 0, 0, failureDescriptor);
        TRACE_MSG(failureDescriptor.ToString().c_str());
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), !pass);

        pass = validatorMac.ValidateString("AB:CD:EF:00:11:2X", 0, 0, failureDescriptor);
        TRACE_MSG(failureDescriptor.ToString().c_str());
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), !pass);

        //
        // UARFCN Validator cases
        //

        ValidatorDownlinkUArfcn validatorUarfcn;
        UmtsBands bandI(false);
        bandI.Insert(UBAND_I_2100);

        UmtsBands bandII_V(false);
        bandII_V.Insert(UBAND_II_1900);
        bandII_V.Insert(UBAND_V_850);

        validatorUarfcn.SetUBandsSupported(bandI);
        pass = validatorUarfcn.ValidateU32(32770, 0, 0, failureDescriptor); // Should fail, band I
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), !pass);

        pass = validatorUarfcn.ValidateU32(10770, 0, 0, failureDescriptor); // Should pass, band I
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), pass);

        pass = validatorUarfcn.ValidateU32(9662, 0, 0, failureDescriptor); // Should fail, band II
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), !pass);

        validatorUarfcn.SetUBandsSupported(bandII_V);
        pass = validatorUarfcn.ValidateU32(10770, 0, 0, failureDescriptor); // Should fail, band I
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), !pass);

        pass = validatorUarfcn.ValidateU32(9662, 0, 0, failureDescriptor); // Should pass, band II
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), pass);

        pass = validatorUarfcn.ValidateU32(4357, 0, 0, failureDescriptor); // Should pass, band V
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), pass);

        //
        // ARFCN Validator cases
        //

        ValidatorDownlinkArfcn validatorArfcn;
        GsmBands bands900_1800(false);
        bands900_1800.Insert(GSM_BAND_ID_E_GSM900);
        bands900_1800.Insert(GSM_BAND_ID_P_GSM900);
        bands900_1800.Insert(GSM_BAND_ID_DCS1800);

        GsmBands band1900_850(false);
        band1900_850.Insert(GSM_BAND_ID_GSM850);
        band1900_850.Insert(GSM_BAND_ID_PCS1900);

        validatorArfcn.SetBandsSupported(bands900_1800);
        pass = validatorArfcn.ValidateU32(128, 0, 256, failureDescriptor); // Should fail, band_E_GSM_900
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), !pass);

        pass = validatorArfcn.ValidateU32(1, 0, 256, failureDescriptor); // Should pass, band_E_GSM_900
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), pass);

        pass = validatorArfcn.ValidateU32(512, 0, 256, failureDescriptor); // Should pass, band_P_GSM_900
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), pass);

        validatorArfcn.SetBandsSupported(band1900_850);
        pass = validatorArfcn.ValidateU32(1, 0, 256, failureDescriptor); // Should fail, band_PCS_1900
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), !pass);

        pass = validatorArfcn.ValidateU32(512, 0, 256, failureDescriptor); // Should pass, band_PCS_1900
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), pass);

        pass = validatorArfcn.ValidateU32(128, 0, 256, failureDescriptor); // Should pass, band V
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), pass);

        //
        // UMTS Band Validator cases
        //

        cout << "UMTS Band Validator\n";
        ValidatorUmtsBands validatorUmtsBand;
        UmtsBands supportedBands(false);
        supportedBands.Insert(UBAND_II_1900);

        validatorUmtsBand.SetBandsSupported(supportedBands);

        std::vector<std::string> requestedBands;
        requestedBands.push_back("II");
        pass = validatorUmtsBand.ValidateStringArray(requestedBands, 0, 256, u32(UBAND_NUMBER_OF), failureDescriptor); // Should pass
        cout << "Testing UMTS Band II accepted\n";
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), pass);

        requestedBands.push_back("III");
        pass = validatorUmtsBand.ValidateStringArray(requestedBands, 0, 256, u32(UBAND_NUMBER_OF), failureDescriptor); // Should fail
        cout << "Testing UMTS Band III rejected..."<<pass<<endl;
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), pass);


        //
        // GSM Band Validator cases
        //

        cout << "GSM Band Validator\n";
        ValidatorRemGsmBands validatorRemBands;
        GsmBands gsmSupportedBands(false);
        gsmSupportedBands.Insert(GSM_BAND_ID_PCS1900);
        gsmSupportedBands.Insert(GSM_BAND_ID_DCS1800);

        validatorRemBands.SetBandsSupported(gsmSupportedBands);

        std::vector<u32> requestedGsmBands;
        GsmBandId gsmBandId;

        CPPUNIT_ASSERT_MESSAGE("Lookup PCS1900", GsmBandIdFromString("PCS1900", gsmBandId));
        requestedGsmBands.push_back( u32( gsmBandId ) );

        CPPUNIT_ASSERT_MESSAGE("Lookup DCS1800", GsmBandIdFromString("DCS1800", gsmBandId));
        requestedGsmBands.push_back( u32( gsmBandId ) );

        pass = validatorRemBands.ValidateU32Array(requestedGsmBands, GSM_BAND_ID_FIRST, GSM_BAND_ID_LAST, u32(GSM_BAND_ID_NUMBER_OF), failureDescriptor); // Should pass
        cout << "Testing REM GSM Bands accepted\n";
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), pass);

        CPPUNIT_ASSERT_MESSAGE("Lookup P-GSM900", GsmBandIdFromString("P-GSM900", gsmBandId));
        requestedGsmBands.push_back( u32( gsmBandId ) );

        pass = validatorRemBands.ValidateU32Array(requestedGsmBands,  GSM_BAND_ID_FIRST, GSM_BAND_ID_LAST, u32(GSM_BAND_ID_NUMBER_OF), failureDescriptor); // Should fail
        cout << "Testing REM GSM Band P-GSM900 rejected\n";
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), !pass);

        //
        // PlmnIds Validator cases
        //

        cout << "PlmnIds Validator\n";
        ValidatorPlmnIds validatorPlmnIds;

        vector<string> plmnIds1;
        plmnIds1.push_back("12345");
        plmnIds1.push_back("234567");
        plmnIds1.push_back("34567");
        plmnIds1.push_back("45678");
        plmnIds1.push_back("456790");

        pass = validatorPlmnIds.ValidateStringArray(plmnIds1, 5, 6, 64, failureDescriptor);
        cout << "Testing Plmn Id STRINGARRAY validates OK\n";
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), pass);

        plmnIds1.push_back("5Fail0");

        pass = validatorPlmnIds.ValidateStringArray(plmnIds1, 5, 6, 64, failureDescriptor);
        cout << "Testing Plmn Id STRINGARRAY validate fails\n";
        CPPUNIT_ASSERT_MESSAGE(failureDescriptor.ToString(), !pass);

        fflush(stdout);
    }

protected:

private:

};

#endif
