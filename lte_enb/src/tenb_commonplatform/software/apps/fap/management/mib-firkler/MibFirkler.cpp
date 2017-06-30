///////////////////////////////////////////////////////////////////////////////
//
// MibFirkler.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>
#include <iomanip> // hex

#include <cstdlib> // system
#include <cstring> // strcmp

#include <system/Trace.h>
#include <mib-core/MibManager.h>
#include <management/oam/MibHelper.h>
#include <system/Exception.h>
#include <system/Application.h>

#include "MibUpgrade.h"
///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace boost;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Static Data
///////////////////////////////////////////////////////////////////////////////

// Application version information template
// This is populated by bitstamp which edits the structure in the binary
static const ApplicationVersion s_appVer  = { {'$','S','T','T'},
                                               "", '\0', "", '\0', "", '\0', "", '\0',
                                              {'E','N','D','$'} };

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
    try
    {
        Trace::GetInstance().DisableFileLogging();

        // Check for operating in MIB Firkler mode.
        if(argc < 2 || argc > 6)
        {
            TRACE_PRINTF_CONSOLE("\nUsage: mib-firkler [-q] [-u] [-v] [-f] [<attribute-name> [<attribute-value>]]\n\n"
                     "  -q : Quiet mode, print minimal information\n"
                     "  -u : Upgrade mode, check for, and perform necessary MIB upgrades.\n"
                     "  -f : Force mode, allow write even for read-only\n"
                     "  -v : Print version information\n\n");
            return -1;
        }

        bool quiet = false;
        bool force = false;
        bool dumpVersion = false;
        bool upgrade = false;
        const char * attributeName = NULL;
        const char * attributeValue = NULL;
        for(int i = 1; i < argc; i++)
        {
            if(strcmp(argv[i], "-q") == 0)
            {
                quiet = true;
            }
            else if(strcmp(argv[i], "-u") == 0)
            {
                upgrade = true;
            }
            else if(strcmp(argv[i], "-v") == 0)
            {
                dumpVersion = true;
            }
            else if(strcmp(argv[i], "-f") == 0)
            {
                force = true;
            }
            else if(attributeName == NULL)
            {
                attributeName = argv[i];
            }
            else
            {
                attributeValue = argv[i];
            }
        }

        if(dumpVersion)
        {
            TRACE_PRINTF_CONSOLE(PRODUCT_STR" %s %s %s\n", s_appVer.buildDate, s_appVer.buildTime, s_appVer.version);
        }

        // If user wants to write to the MIB, check that OAM is not running...
        if ((upgrade || (attributeValue != NULL)) &&
            std::system("pidof oam >/dev/null 2>&1") == 0) // if a pid was found
        {
            if(!quiet)
            {
                fprintf(stderr, "oam is running, please use CLI!\n");
            }
            return(1);
        }

        if(upgrade)
        {
            if(!quiet)
            {
                Trace::GetInstance().EnableStdoutLogging();
            }
            // Upgrade the MIB
            MibUpgrade::DoMibUpgrade();
        }

        if(attributeName)
        {
            shared_ptr<MibManager> mibManager(new MibManager(NULL));
            MibHelper::BuildMoTree(mibManager);

            MibAttributeIds ids = MibHelper::FindAllMatchingMibAttributeIds(attributeName, MibHelper::ExactMatcher);
            if(ids.size() != 1)
            {
                if(!quiet)
                {
                    fprintf(stderr, "INVALID ATTRIBUTE NAME %s(%zu)\n", attributeName, ids.size());
                }
                return(1);
            }

            MibAttributeId id = *ids.begin();

            if(attributeValue)
            {
                // User wants to set a value.
                std::string attributeValueStr(attributeValue);

                // Create an attribute value object from the string supplied.
                MibAttributeValues mibAttributeValues;
                shared_ptr<MibAttributeValue> attrValue = MibAttributeValue::Create(getMibAttributeType(id), attributeValueStr);
                MibAttrValidationFailures failures;
                if(attrValue != NULL)
                {
                    mibAttributeValues.AddAttribute(id, attrValue);
                    failures = mibManager->ValidateAttributes(MibHelper::GetMibObjectDn(id), mibAttributeValues, !force);
                }
                else
                {
                    ValidationFailureDescriptor failure;
                    string description("Malformed/invalid value e.g. a negative U32");
                    failure.Set(ValidationFailureDescriptor::CAUSE_INVALID, description);
                    failures.push_back(MibAttrValidationFailure(id, failure));
                }

                if(failures.size() > 0)
                {
                    if(!quiet)
                    {
                        fprintf(stderr, "FAILED TO SET VALUE: %s\n", failures.ToString().c_str());
                    }
                    return(1);
                }

                mibManager->SetAttributes(MibHelper::GetMibObjectDn(id), mibAttributeValues, !force);
            }

            // Get value.
            shared_ptr<MibAttributeValue> value = MibHelper::GetMibAttributeDirect(id);
            if(value == NULL)
            {
                if(!quiet)
                {
                    fprintf(stderr, "VALUE NOT PRESENT\n");
                }
                return(1);
            }

            if(quiet)
            {
                TRACE_PRINTF_CONSOLE("%s", value->GetValueAsString().c_str());
            }
            else
            {
                TRACE_PRINTF_CONSOLE("%s = %s\n", attributeName, value->GetValueAsString(true /* long format */).c_str());
            }
        }
    }
    catch(const Exception& e)
    {
        TRACE_PRINTF("Exception caught: %s\n",e.what());
    }
    catch(...)
    {
        TRACE_PRINTF("Top level exception caught.\n");
    }

    return(0);
}
