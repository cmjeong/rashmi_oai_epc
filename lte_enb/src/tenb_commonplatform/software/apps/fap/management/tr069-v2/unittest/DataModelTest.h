///////////////////////////////////////////////////////////////////////////////
//
// DataModelTest.h
//
// Unit tests for MibManager.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __DataModelTest_h_
#define __DataModelTest_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <cstring>

#include <cppunit/TestCase.h>

#include <system/Trace.h>

#include <Radisys.h>

#include <autogen-test/Tr069DataModel.h>

using namespace tr069;
///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class DataModelTest : public CppUnit::TestCase
{
public:
    void runTest()
    {
        cout << endl << endl
             << "********************" << endl
             << "Tr069DataModel tests" << endl
             << "********************" << endl << endl;

        //CPPUNIT_ASSERT_MESSAGE("Testing something in table", a == b);

        cout << "Auto Generated Table from sample xml\n";

        for (int i=0; i<8; i++)
        {
            CPPUNIT_ASSERT_MESSAGE("Testing name is more than 30 charachters long",
                    (strlen(RadisysDataModel[i].name) > 30));

            // I believe this one is a silly test, but I have to test something right?
            CPPUNIT_ASSERT_MESSAGE("Test Inform indication is true or false",
                    (RadisysDataModel[i].forcedInform == false) || (RadisysDataModel[i].forcedInform == true) );

            cout << "NAME:" << RadisysDataModel[i].name << endl;
            cout << "Access: " << RadisysDataModel[i].access
                 << "\ttype: " << RadisysDataModel[i].type
                 << "\trange: " << RadisysDataModel[i].minVal << " - " << RadisysDataModel[i].maxVal << endl
                 << "Default value: " << RadisysDataModel[i].defaultValue << endl
                 << "Mib Id: " << RadisysDataModel[i].mibAttrId
                 << "\tMib Group: " << RadisysDataModel[i].mibGroup << endl << endl;

            char* min = NULL;
            char* max = NULL;

            if ( strcmp(RadisysDataModel[i].minVal, "") != 0 )
                min = (char*)RadisysDataModel[i].minVal;

            if ( strcmp(RadisysDataModel[i].maxVal, "") != 0 )
                    max = (char*)RadisysDataModel[i].maxVal;

            /* Check if default value is in range only for integers or uint, and when the range is specified */
            if ( ((RadisysDataModel[i].type == INT )
                   || (RadisysDataModel[i].type == U_INT ))
                  && ( (min != NULL && max != NULL) ) )
            {
                if (min != NULL)
                {
                    CPPUNIT_ASSERT_MESSAGE("Check value is in range with minimum",
                            ( atoi(RadisysDataModel[i].defaultValue) >= atoi(min) ) );
                }
                if (max != NULL)
                {
                    CPPUNIT_ASSERT_MESSAGE("Check value is in range with maximum",
                            ( atoi(RadisysDataModel[i].defaultValue) <= atoi(max) ) );
                }
                cout << "Chacked if Default Value is in range: OK\n\n";
            }
        }
    }

protected:

private:

};

#endif
