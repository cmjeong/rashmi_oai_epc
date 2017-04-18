
///////////////////////////////////////////////////////////////////////////////
//
// OamCli.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <set>
#include <stdio.h>

#include <boost/shared_ptr.hpp>
#include <MibAttributeId.h>
#include <system/AlarmEvent.h>
#include <platform/FapAlarmId.h>
#include <messaging/messages/rem/rem_msgs.h>
#include <messaging/messages/cli/CliExecuteCmdInd.h>
#include <messaging/messages/cli/CliExecuteCmdReq.h>
#include <messaging/messages/common/OamActionReq.h>
#include <messaging/messages/common/FtpGetReq.h>
#include <messaging/messages/common/FtpPutReq.h>
#include <messaging/messages/common/FtpReq.h>
#include <messaging/messages/common/FtpAbort.h>
#include <messaging/messages/common/ApplyUpdateReq.h>
#include <messaging/messages/common/RevertUpdateReq.h>
#include <messaging/messages/common/InstallUpdateReq.h>
#include <messaging/messages/common/InstallUpdateCnf.h>
#include <messaging/messages/common/ActivateUpdateReq.h>
#include <messaging/messages/common/ActivateUpdateCnf.h>
///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "OamUserApplication.h"
#include "OamCli.h"
#include "oam_env.h"
#include "MibHelper.h"
#include "managed-objects/FapMO.h"

using namespace std;
using namespace threeway;
using namespace boost;

///////////////////////////////////////////////////////////////////////////////
// Structs
///////////////////////////////////////////////////////////////////////////////

struct NamePair
{
   std::string left;
   std::string right;
};

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////
//
#ifdef _UPDATE_CLI_PROXY
const std::string OAM_CLI_VERSION("21");
#else
const std::string OAM_CLI_VERSION("30");
#endif

Mutex           m_Mutex;
Condition       m_Condition;

const NamePair namePairs[] =
{
   {"hlaMajorRev",    "HLA_MAJOR_REV"},
   {"hlaMinorRev",    "HLA_MINOR_REV"},
   {"hwPart",         "HW_PART"},
   {"hwPartMajorRev", "HW_PART_MAJOR_REV"},
   {"hwPartMinorRev", "HW_PART_MINOR_REV"},
   {"hwType",         "HARDWARE_TYPE"},
   {"hwRevision",     "HARDWARE_REVISION"},
   {"hwModState",     "HARDWARE_MOD_STATE"},
   {"serialNumber",   "LONG_SERIAL_NUMBER"},
   {"buildDesc",      "BUILD_DESC"},
   {"build",          "BUILD_DESC"},
   {"xtalSynced",     "XTAL_SYNCED"},
   {"manufacturer",   "MANUFACTURER"},
   {"oui",            "OUI_OF_MANUFACTURER"},
   {"productClass",   "PRODUCT_CLASS"},
};

void OamCli::RegisterOamCliCmds(shared_ptr<CliHandler> oamCliHandler)
{
   ENTER();

   CppCliPair cppOamCliPairs[] =
   {
      {
         {
            "set", 2, 3,  // min/max arguments
            "ate",
            "set <attribute-name> <attribute-value>",
            "Set a MIB attribute."
         },
         &CliCmdMibSetAttribute,
      },
      {
         {
            "get", 1, 2,  // min/max arguments
            "ate",
            "get <attribute-name>",
            "Get a MIB attribute."
         },
         &CliCmdMibGetAttribute,
      },
      {
         {
            "getwild", 0, 1,  // min/max arguments
            "dev",
            "getwild <attribute-name>",
            "Get a MIB attribute with wild card name search.  E.g. oam.getwild ENABLE"
         },
         &CliCmdMibGetAttributeWild,
      },
      {
         {
            "get-desc", 1, 1,  // min/max arguments
            "dev",
            "get-desc <attribute-name>",
            "Get a MIB attribute description."
         },
         &CliCmdMibGetAttributeDesc,
      },
      {
         {
            "get-ate-cli-version", 0, 0,  // min/max arguments
            "ate",
            "get-ate-cli-version",
            "Get the version of the cli."
         },
         &CliCmdGetCliVersion,
      },
      {
         {
            "mf.list", 0, 0,  // min/max arguments
            "dev",
            "mf.list",
            "List all Managed Fings (MFs) that have been registered including their managing messaging entity and current op state."
         },
         &CliCmdMfList,
      },
      {
         {
            "mf.set-admin-state", 2, 2,  // min/max arguments
            "dev",
            "mf.set-admin-state <mf-name> <locked|unlocked|shuttingdown>",
            "Set the admin state of a Managed Fing (MF).  This may have unexpected consequences, use with care!  E.g. \"mf.set-admin-state sctp locked\""
         },
         &CliCmdMfSetAdminState,
      },
      {
         {
            "sendalarm", 2, 4,
            "dev",
            "sendalarm <id> <cellId> [cleared|cl|warning|w|minor|mi|major|ma|critical|cr] [transient|t|nontransient|n]",
            "Send an alarm to OAM as if a real alarm event had occurred.  Should trigger all expected alarm event behaviour."
         },
         &CliCmdSendAlarmEvent,
      },
      {
         {
            "alarms", 0, 1,
            "dev",
            "alarms <file>",
            "Dump all alarms to <file> or STDERR."
         },
         &CliCmdAlarms,
      },
      {
         {
            "sendaction", 1, 1,
            "dev",
            "sendaction <id>",
            "Send an OAM action request to OAM.  Should trigger all expected action behaviour."
         },
         &CliCmdSendAction,
      },
      {
         {
            "rebootfap", 0, 0,
            "ate",
            "rebootfap",
            "Perform a FAP Reboot."
         },
         &CliCmdRebootFap,
      },
      {
         {
            "coverage", 0, 0, // min/max arguments
            "ate",
            "coverage",
            "Get coverage."
         },
         &CliCmdGetCoverage,
      },
#ifdef _UPDATE_CLI_PROXY
      {
         {
            "ftp.req", 9, 9,
            "ate",
            "ftp.req [Get|Put] <remoteIpAddress> <remoteDirectory> <filename> <localIpAddress> <localDirectory> <username> <password> <Request ID (u32)",
            "Send an FTP request message."
         },
         &CliCmdFtpReq,
      },
      {
         {
            "ftp.getupdate", 2, 4,
            "dev",
            "ftp.getupdate <remoteIpAddress> <update file pathname> [<username> <password>]",
            "FTP an update image to the default update location."
         },
         &CliCmdFtpGetUpdate,
      },
      {
         {
            "ftp.abort", 2, 2,
            "ate",
            "ftp.abort <Client Request ID (u32)> <OAM Request ID (u32)> ",
            "Send an FTP abort message."
         },
         &CliCmdFtpAbort,
      },
      {
         {
            "ftp.status", 0, 1,
            "ate",
            "ftp.status [extended]",
            "Check status of FTP requests."
         },
         &CliCmdFtpStatus,
      },
#endif
      {
         {
            "pollkpis", 1, 1,
            "dev",
            "pollkpis <interval|total>",
            "Trigger OAM to poll for all current KPI values without resetting them.\nCheck the oam trace file for the results.\n"
               "'interval' will give the KPIs for the current collection period i.e. since they were reset at the end of the last collection period.\n"
               "'total' will give the totals since power on."
         },
         &CliCmdPollKpis,
      },
#if 0
      {
         {
            "networking.get", 1, 2,  // min/max arguments
            "ate",
            "networking.get <IP|NETMASK|GW|MAC|NUMBER_MACS> <adapter/route>",
            "Get networking parameter value for the specified adapter/route (e.g. eth0)."
         },
         &CliCmdNetGetSwitch,
      },
      {
         {
            "networking.set", 2, 4,  // min/max arguments
            "ate",
            "networking.set <IP|NETMASK|GW|MAC|NUMBER_MACS> <adaptor/route> <address/value>",
            "Set networking parameter value for the specified adapter/route (e.g. eth0)."
         },
         &CliCmdNetSetSwitch,
      },
      {
         {
            "networking.dhcp", 2, 3,  // min/max arguments
            "ate",
            "networking.dhcp <adaptor> <enable|disable> [configuration string]",
            "This command is used to enable or disable the ise of DHCP on the FAP:\
               Adaptor is interface name; enable is 'enable or 'disable'."
         },
         &CliCmdNetDhcp,
      },
      {
         {
            "networking.ntp", 1, 1,  // min/max arguments
            "ate",
            "networking.ntp <enable|disable>", //<enable|disable>",
            "This command enable or disable NTP."
         },
         &CliCmdNetNtpEnable,
      },
      {
         {
            "networking.ntp.setserver", 2, 2,  // min/max arguments
            "ate",
            "networking.ntp.setserver <server number> <IP Address>",
            "Set the IP Address of the servers to be used for NTP syncronisation."
         },
         &CliCmdNetNtpSetServer,
      },
#ifdef PRODUCT_hbs2_iu
      {
         {
            "networking.cs.setserver", 2, 2,  // min/max arguments
            "ate",
            "networking.cs.setserver <server number> <IP Address>",
            "Set the configuration server Addresses to be used for FAP configuration."
         },
         &CliCmdNetCSSetServer,
      },
#endif
      {
         {
            "networking.restart", 0, 0,  // min/max arguments
            "ate",
            "networking.restart",
            "Restart the networking service."
         },
         &CliCmdNetRestart,
      },
#endif
      {
         {
            "scan", 0, 0,  // min/max arguments
            "dev",
            "scan",
            "Trigger a rem scan request towards rem"
         },
         &CliCmdScan,
      },
      {
         {
            "scanStatus", 0, 0,  // min/max arguments               
            "dev",
            "scanStatus",                                           
            "Trigger a rem scan Status towards oam"
         },                                                    
         &CliCmdDummyStatus,
      },
      {
         {
            "abortscan", 0, 0,  // min/max arguments
            "dev",
            "abortscan",
            "Trigger a abort scan request towards rem"
         },
         &CliCmdAbortScan,
      },
      {
         {
            "getstate", 0, 0,  // min/max arguments
            "dev",
            "getstate",
            "Get admin and operational state information."
         },
         &CliCmdGetState,
      },
      {
         {
            "rabstatus", 0, 0,  // min/max arguments
            "dev",
            "Report rabstatus ",
            "Report the rabstatus of all the UE's connected"
         },
         &CliCmdRabStatus,
      },
   } ;

   for (u32 i = 0; i < sizeof(cppOamCliPairs) / sizeof(cppOamCliPairs[0]); i++)
   {
      oamCliHandler->RegisterCliCmd(cppOamCliPairs[i].descriptor, cppOamCliPairs[i].cppFuncPtr);
   }

   EXIT();
}

void OamCli::RegisterMibCliCmds(shared_ptr<CliHandler> mibCliHandler)
{
   ENTER();

   CppCliPair cppMibCliPairs[] =
   {
      {
         {
            "set", 2, 3,  // min/max arguments
            "dev",
            "set <attribute-name> <attribute-value> [dn]",
            "Set a MIB attribute. E.g. mib.set SECURITY_GATEWAY_1 hms.secgw.com FAP.0.COMMISSIONING.0"
         },
         &CliCmdMibSetAttribute,
      },
      {
         {
            "get", 1, 2,  // min/max arguments
            "dev",
            "get <attribute-name> [dn]",
            "Get a MIB attribute."
         },
         &CliCmdMibGetAttribute,
      },
      {
         {
            "delete", 1, 1,  // min/max arguments
            "dev",
            "delete <attribute-name>",
            "Delete a MIB attribute."
         },
         &CliCmdMibDeleteAttribute,
      },
      {
         {
            "get-desc", 1, 1,  // min/max arguments
            "dev",
            "get-desc <attribute-name>",
            "Get a MIB attribute description."
         },
         &CliCmdMibGetAttributeDesc,
      },
      {
         {
            "get-diffs-from-defaults", 0, 0,  // min/max arguments
            "dev",
            "get-diffs-from-defaults",
            "Get all MIB attribute values where they differ from the default."
         },
         &CliCmdMibGetDiffsFromDefaults,
      },
      {
         {
            "get-nv", 0, 0,  // min/max arguments
            "dev",
            "get-nv",
            "Get all MIB attribute values where they have been explicitly set in NV."
         },
         &CliCmdMibGetNv,
      },
      {
         {
            "getwild", 0, 1,  // min/max arguments
            "dev",
            "getwild <attribute-name>",
            "Get a MIB attribute with wild card name search.  E.g. mib.getwild ENABLE"
         },
         &CliCmdMibGetAttributeWild,
      },
#if 0
      {
         {
            "getcellconfig", 0, 0,  // min/max arguments
            "dev",
            "getcellconfig",
            "Get key cell configuration MIB attributes."
         },
         &CliCmdMibGetCellConfig,
      },
#endif
      {
         {
            "get-subscriptions", 0, 0,  // min/max arguments
            "dev",
            "get-subscriptions",
            "Get list of MIB subscriptions."
         },
         &CliCmdMibSubscriptions,
      },
      {
         {
            "create", 1, 1,  // min/max arguments
            "dev",
            "create <object-DN>",
            "**WARNING - Assert upon failure** Create a new MIB object.\nE.g.\n\tmib.create FAP.0.CONFIGURED_INTER_FREQ_NEIGHBOURS.30"
         },
         &CliCmdMibCreate,
      },
      {
         {
            "delete", 1, 1,  // min/max arguments
            "dev",
            "delete <object-DN>",
            "Attempt to delete a MIB object (will fail if has child objects).\nE.g.\n\tmib.delete FAP.0.CONFIGURED_INTER_FREQ_NEIGHBOURS.30"
         },
         &CliCmdMibDelete,
      },
   };

   for (u32 i = 0; i < sizeof(cppMibCliPairs) / sizeof(cppMibCliPairs[0]); i++)
   {
      mibCliHandler->RegisterCliCmd(cppMibCliPairs[i].descriptor, cppMibCliPairs[i].cppFuncPtr);
   }

   EXIT();
}

shared_ptr<CliResponse> OamCli::CliCmdGetCoverage(const CliArguments& args)
{

   s32 result = CLI_ERROR_NONE;
   ostringstream responseStream ;

   responseStream << "Generating coverage for OAM";
#ifdef PRODUCT_generic 
   __gcov_flush();
#endif 
   shared_ptr<CliResponse> response (new CliResponse(responseStream.str(), result)) ;

   return response;
}

shared_ptr<CliResponse> OamCli::CliCmdGetCliVersion(const CliArguments& args)
{
   /*************************************************************************
    * THIS COMMAND IS IN THE "ATE" GROUP SO IS USED BY AUTOMATED TOOLS.
    * BE CAREFUL NOT TO MODIFY THE USAGE, BEHAVIOUR OR RESPONSE TEXT FORMAT!!
    *************************************************************************/

   shared_ptr<CliResponse> response (new CliResponse (OAM_CLI_VERSION, CLI_ERROR_NONE)) ;

   return response;
}

shared_ptr<CliResponse> OamCli::CliCmdMibSetAttribute(const CliArguments& args)
{
   /*************************************************************************
    * THIS COMMAND IS IN THE "ATE" GROUP SO IS USED BY AUTOMATED TOOLS.
    * BE CAREFUL NOT TO MODIFY THE USAGE, BEHAVIOUR OR RESPONSE TEXT FORMAT!!
    *************************************************************************/

   s32 result = CLI_ERROR_NONE;
   ostringstream responseStream ;

   if(args.size() == 3)
   {
      string  givenParam;
      string  givenValue;

      if (0 == args.at(1).compare("\"\""))
      {
         givenValue = "";
      }
      else
      {
         givenValue = args.at(1);
      }

      for (int i = (sizeof(namePairs)/sizeof(NamePair)) - 1; i >= 0; --i)
      {
         if ( args.at(0).CaselessEquals(namePairs[i].left.c_str()) )
         {
            givenParam = namePairs[i].right;
            break;
         }
      }
      // otherwise
      if (givenParam.empty())
      {
         givenParam = string(args.at(0));
      }

      //now need to actually do a search to see if we have this mib param.
      MibAttributeIds ids = MibHelper::FindAllMatchingMibAttributeIds( givenParam, &MibHelper::ExactMatcher);
      if(ids.size() == 1)
      {
         MibAttributeId id = *(ids.begin());
         MibAttributeType type = getMibAttributeType(id);
         MibAttributeValues attrVals;

         if(MIB_ATTRIBUTE_TYPE_STRING == type)
         {   
            if(args.size() > 2)
            {
               if (args.at(2).find("FAP.0") == string::npos)
               {
                  //Scenario where the string paramters Ex: "L3 only", "Open Access"
                  //Shall Encounter this part of code
                  for(u8 i=2;i<args.size();i++)
                  {
                     givenValue.append(" ");
                     givenValue.append(args.at(i));
                  }
               }
            }   
         }
         shared_ptr<MibAttributeValue> attrVal = MibAttributeValue::Create(type, givenValue);
         MibAttrValidationFailures failures;

         MibDN dn;
         dn = MibDN::GenerateMibDN( args.at(2) );

         if(attrVal != NULL)
         {
            attrVals.AddAttribute(id, attrVal);
            failures = OamUserApplication::GetInstance().GetMibManager()->ValidateAttributes( dn, attrVals);
         }
         else
         {
            ValidationFailureDescriptor failure;
            string description("Malformed/invalid value e.g. a negative U32 or integer overflow");
            failure.Set(ValidationFailureDescriptor::CAUSE_INVALID, description);
            failures.push_back(MibAttrValidationFailure(id, failure));
         }

         if(failures.size() == 0)
         {
            OamUserApplication::GetInstance().HandleMIOdn(dn);
            OamUserApplication::GetInstance().checkForSONParameters( attrVals );
            OamUserApplication::GetInstance().GetMibManager()->SetAttributes(dn, attrVals);
            /* removing the logic of setting isCfgd param based on other csg params
             * after discussion with architects */
            //OamUserApplication::GetInstance().HandleCsgParam(givenParam);
            OamUserApplication::GetInstance().HandleGERANPmaxParam(givenParam);
            OamUserApplication::GetInstance().HandleGERANSpeedScaleParam(givenParam);
            OamUserApplication::GetInstance(). HandleNetCntrlOrdrParam(givenParam+" "+args.at(args.size()-1));
         }
         else
         {
            responseStream << failures.ToString();
            result = CLI_ERROR_COMMAND_FAILED ;
         }
      }
      else
      {
         responseStream << "Param " << args.at(0) << " not found.";
         result = CLI_ERROR_INVALID_ARGUMENT ;
      }
   }
   else
   {
      responseStream << "Not enough arguments. usage: oam.set <attribute-name> <attribute-value> [dn]";
      result = CLI_ERROR_TOO_FEW_ARGUMENTS ;
   }
   shared_ptr<CliResponse> response (new CliResponse(responseStream.str(), result)) ;
   return response;
}

shared_ptr<CliResponse> OamCli::CliCmdMibGetAttribute(const CliArguments& args)
{
   /*************************************************************************
    * THIS COMMAND IS IN THE "ATE" GROUP SO IS USED BY AUTOMATED TOOLS.
    * BE CAREFUL NOT TO MODIFY THE USAGE, BEHAVIOUR OR RESPONSE TEXT FORMAT!!
    *************************************************************************/

   ostringstream responseStream;
   s32 result = CLI_ERROR_NONE;

   if(args.size() == 2)
   {
      string paramString;
      string givenParam;

      if(not(args.empty()))
      {
         for (int i = (sizeof(namePairs)/sizeof(NamePair)) - 1; i >= 0; --i)
         {
            if ( args.at(0).CaselessEquals(namePairs[i].left.c_str()) )
            {
               givenParam = namePairs[i].right;
               break;
            }
         }
         // otherwise
         if (givenParam.empty())
         {
            givenParam = string(args[0]);
         }
      }
      else
      {
         givenParam = string("");
      }

      //now need to actually do a search to see if we have this mib param.
      MibAttributeIds ids = MibHelper::FindAllMatchingMibAttributeIds( givenParam, &MibHelper::ExactMatcher);

      if(ids.size() == 1)
      {
         MibAttributeId id = *(ids.begin());

         MibDN dn;
         dn = MibDN::GenerateMibDN( args.at(1) );

         // The default name to report
         std::string attributeNameString = getMibAttributeName(id);

         responseStream << attributeNameString << ' ';

         shared_ptr<MibAttributeValue> attrValue = MibHelper::GetMibAttributeDirect(dn, id);

         if(attrValue != NULL)
         {
            responseStream << attrValue->GetValueAsString(true /* long format */) << endl;
         }
         else
         {
            responseStream << "(NOT SET)" << endl;
         }
      }
      else
      {
         responseStream << "No exact matching MIB attribute";
      }

   }
   else
   {
      responseStream << "Not enough arguments. usage: oam.set <attribute-name> <attribute-value> [dn]";
      result = CLI_ERROR_TOO_FEW_ARGUMENTS ;
   }
   shared_ptr<CliResponse> response (new CliResponse (responseStream.str(), result)) ;

   return response;
}


shared_ptr<CliResponse> OamCli::CliCmdMibDeleteAttribute(const CliArguments& args)
{
   ostringstream responseStream;
   s32 result = CLI_ERROR_NONE;

   //now need to actually do a search to see if we have this mib param.
   MibAttributeIds ids = MibHelper::FindAllMatchingMibAttributeIds(args.at(0), &MibHelper::ExactMatcher);

   if(ids.size() == 1)
   {
      MibAttributeId id = *(ids.begin());
      OamUserApplication::GetInstance().GetMibManager()->DeleteAttributes(MibHelper::GetMibObjectDn(id), ids);
   }
   else
   {
      responseStream << "No exact matching MIB attribute";
   }

   shared_ptr<CliResponse> response (new CliResponse (responseStream.str(), result)) ;

   return response;
}


shared_ptr<CliResponse> OamCli::CliCmdMibGetAttributeDesc(const CliArguments& args)
{
   s32 result = CLI_ERROR_NONE;
   ostringstream responseStream ;
   stringstream descString;

   // TODO: Consider future case where min/max/default differ according to associated object
   if(args.size() > 0)
   {
      //now need to actually do a search to see if we have this mib param.
      MibAttributeIds ids = MibHelper::FindAllMatchingMibAttributeIds(args.at(0), &MibHelper::ExactMatcher);
      if(ids.size() == 1)
      {
         MibAttributeId id = *(ids.begin());
         MibAttributeType type = getMibAttributeType(id);
         bool hasDefault = getMibAttributeCommonDesc(id)->hasDefault;
         const MibAttributeU32Descriptor* descriptorU32;
         const MibAttributeS32Descriptor* descriptorS32;
         const MibAttributeStringDescriptor* descriptorString;
         const MibAttributeStringArrayDescriptor* descriptorStringArray;

         switch(type)
         {
            case MIB_ATTRIBUTE_TYPE_U32:
            case MIB_ATTRIBUTE_TYPE_ENUM:
               descriptorU32 = getMibAttributeU32Descriptor(id);
               if(hasDefault)
               {
                  descString << "default=" << descriptorU32->defaultValue << ", ";
               }
               descString << "minValue=" << descriptorU32->minValue \
                  << ", maxValue=" << descriptorU32->maxValue;

               break;
            case MIB_ATTRIBUTE_TYPE_S32:
               descriptorS32 = getMibAttributeS32Descriptor(id);
               if(hasDefault)
               {
                  descString << "default=" << descriptorS32->defaultValue << ", ";
               }
               descString << "minValue=" << descriptorS32->minValue \
                  << ", maxValue=" << descriptorS32->maxValue;
               break;
            case MIB_ATTRIBUTE_TYPE_STRING:
               descriptorString = getMibAttributeStringDescriptor(id);
               if(hasDefault)
               {
                  descString << "default=\"" << descriptorString->defaultValue << "\", ";
               }
               descString << "minLength=" << descriptorString->minLength \
                  << ", maxLength=" << descriptorString->maxLength;
               break;
            case MIB_ATTRIBUTE_TYPE_STRINGARRAY:
               descriptorStringArray = getMibAttributeStringArrayDescriptor(id);
               descString << "minLength=" << descriptorStringArray->minLength \
                  << ", maxLength=" << descriptorStringArray->maxLength \
                  << ", maxInstances=" << descriptorStringArray->maxInstances;
               break;
            case MIB_ATTRIBUTE_TYPE_U32ARRAY:
            case MIB_ATTRIBUTE_TYPE_ENUMARRAY:
               {
                  const MibAttributeU32ArrayDescriptor* descriptorU32Array = getMibAttributeU32ArrayDescriptor(id);
                  descString << "minValue=" << descriptorU32Array->minValue \
                     << ", maxValue=" << descriptorU32Array->maxValue \
                     << ", maxInstances=" << descriptorU32Array->maxInstances;
               }
               break;
            case MIB_ATTRIBUTE_TYPE_S32ARRAY:
               {
                  const MibAttributeS32ArrayDescriptor* descriptorS32Array = getMibAttributeS32ArrayDescriptor(id);
                  descString << "minValue=" << descriptorS32Array->minValue \
                     << ", maxValue=" << descriptorS32Array->maxValue \
                     << ", maxInstances=" << descriptorS32Array->maxInstances;
               }
               break;
         }

         // Find attribute descriptor parts that are MO specific
         responseStream << getMibAttributeName(id) << ' ';

         string attrValueString;
         // The following call may not necessarily come back with a valid value as the function
         // MibHelper::GetMibObjectDn() (used under-the-hood) is not fully functional (see its description).
         bool success = MibHelper::GetMibAttributeDirectAsString(id, attrValueString);
         if(success)
         {
            responseStream << attrValueString << ' ';
         }

         responseStream << ": " << descString.str() << ", id=" << id
            << ", moc=" << (getMibAttributeCommonDesc(id)->mandatoryOnCreate?'y':'n')
            << ", type=" << getMibAttributeTypeName(getMibAttributeType(id));

         // The following call may not necessarily come back with a valid pointer as the function
         // MibHelper::GetMibObjectDn() is not fully functional (see its description).
         const MibObjectAttributeDescriptor* mibObjectAttributeDescriptor = getMibObjectAttributeDescriptor(MibHelper::GetMibObjectDn(id).back().GetMibObjectClass(), id);
         if(mibObjectAttributeDescriptor != NULL)
         {
            responseStream << ", access=" << getMibAttributeAccessClassName(mibObjectAttributeDescriptor->accessClass)
               << ", storage=" << getMibAttributeStorageClassName(mibObjectAttributeDescriptor->storageClass);
         }
         else
         {
            responseStream << ", [access + storage info unavailable]";
         }
         responseStream << endl;
      }
      else
      {
         responseStream << "MIB attribute " << args.at(0) << " not found.";
         result = CLI_ERROR_INVALID_ARGUMENT ;
      }
   }
   else
   {
      responseStream << "Not enough arguments. usage: oam.get-desc <attribute-name>";
      result = CLI_ERROR_TOO_FEW_ARGUMENTS ;
   }
   shared_ptr<CliResponse> response (new CliResponse(responseStream.str(), result)) ;
   return response;
}

shared_ptr<CliResponse> OamCli::CliCmdMibGetDiffsFromDefaults(const CliArguments& args)
{
   ostringstream responseStream;
   s32 result = CLI_ERROR_NONE;

   MibAttributeValuesByDn diffFromDefaultsValuesByDn;
   OamUserApplication::GetInstance().GetMibManager()->GetAttributesDiffFromDefaults(diffFromDefaultsValuesByDn);

   responseStream << diffFromDefaultsValuesByDn.ToString();

   shared_ptr<CliResponse> response (new CliResponse (responseStream.str(), result)) ;
   return response;
}

shared_ptr<CliResponse> OamCli::CliCmdMibGetNv(const CliArguments& args)
{
   ostringstream responseStream;
   s32 result = CLI_ERROR_NONE;

   MibAttributeValuesByDn nvValuesByDn;
   OamUserApplication::GetInstance().GetMibManager()->GetAttributesSetInNv(nvValuesByDn);

   responseStream << nvValuesByDn.ToString();

   shared_ptr<CliResponse> response (new CliResponse (responseStream.str(), result)) ;
   return response;
}

shared_ptr<CliResponse> OamCli::CliCmdMibGetAttributeWild(const CliArguments& args)
{
   ostringstream responseStream;
   int result = 0 ;
   string paramString;
   string arg0String;

   if(not(args.empty()))
   {
      // This is the default
      arg0String = string(args[0]);
   }
   else
   {
      arg0String = string("");
   }

   //now need to actually do a search to see if we have this mib param.
   MibAttributeIds ids = MibHelper::FindAllMatchingMibAttributeIds(arg0String, &MibHelper::LooseMatcher);

   if(not(ids.empty()))
   {
      for(MibAttributeIds::const_iterator id = ids.begin(); id != ids.end(); id++)
      {
         bool   mibAttrSet = FALSE;
         // The default name to report
         std::string attributeNameString = getMibAttributeName(*id);
         responseStream << attributeNameString << ' ';

         if((mibAttrSet = MibHelper::GetMibAttributeDirectAsString(*id, paramString)) == TRUE)
         {
            // TODO: add status and default info back in

            //pStatus = oamMib_getParamStatusAsString(OamUserApplication::GetInstance().m_pMib, *id);
            //responseStream << getMibAttributeName(*id) << " " << paramString << " (" << pStatus << ") Default=" << paramString2 << endl;
            responseStream << paramString << endl;
         }
         if(mibAttrSet == FALSE)
         {
            responseStream << "(NOT SET)" << endl;
         }
      }
   }
   else
   {
      responseStream << "No matching MIB attributes";
   }

   shared_ptr<CliResponse> response (new CliResponse (responseStream.str(), result)) ;

   return response;
}

#if 0
shared_ptr<CliResponse> OamCli::CliCmdMibGetCellConfig(const CliArguments& args)
{
   s32 result = CLI_ERROR_NONE;
   ostringstream responseStream ;

   MibAttributeIds ids;
   ids.insert(PARAM_ID_DL_UARFCN);
   ids.insert(PARAM_ID_PRIM_SC);
   ids.insert(PARAM_ID_LAC);
   ids.insert(PARAM_ID_RAC);
   ids.insert(PARAM_ID_SAC);
   ids.insert(PARAM_ID_RNC_ID);
   ids.insert(PARAM_ID_L2_CYPHERING_ENABLE);
   ids.insert(PARAM_ID_SIB1_CS_DOMAIN_ENABLE);
   ids.insert(PARAM_ID_SIB1_PS_DOMAIN_ENABLE);
   ids.insert(PARAM_ID_SIB1_NMO);
   ids.insert(PARAM_ID_CELL_IDENTITY);
   ids.insert(PARAM_ID_CPICH_POWER_USED);

   string value;
   for(MibAttributeIds::const_iterator iter = ids.begin(); iter != ids.end(); ++iter)
   {
      if(MibHelper::GetMibAttributeDirectAsString(*iter, value))
      {
         responseStream << getMibAttributeName(*iter) << " = " << value << endl;
      }
      else
      {
         responseStream << getMibAttributeName(*iter) << " not present" << endl;
      }
   }

   shared_ptr<CliResponse> response (new CliResponse(responseStream.str(), result)) ;
   return response;
}
#endif

shared_ptr<CliResponse> OamCli::CliCmdMibSubscriptions(const CliArguments& args)
{
   shared_ptr<CliResponse> rsp;

   shared_ptr<MibManager> mibManager = OamUserApplication::GetInstance().GetMibManager();
   RSYS_ASSERT(mibManager != NULL);
   rsp.reset(new CliResponse(mibManager->SubscriptionsToString(), CLI_ERROR_NONE));

   return rsp;
}

shared_ptr<CliResponse> OamCli::CliCmdMibCreate(const CliArguments& args)
{
   shared_ptr<CliResponse> rsp;

   shared_ptr<MibManager> mibManager = OamUserApplication::GetInstance().GetMibManager();
   RSYS_ASSERT(mibManager != NULL);

   RSYS_ASSERT(args.size() == 1);

   MibDN dn = MibDN::GenerateMibDN( args.at(0) );

   MibDN parent = dn;
   parent.pop_back();

   MibRDN child = dn.back();

   mibManager->CreateObject(parent, child);

   rsp.reset(new CliResponse( "Mib object created", CLI_ERROR_NONE));

   return rsp;
}

shared_ptr<CliResponse> OamCli::CliCmdMibDelete(const CliArguments& args)
{
   shared_ptr<CliResponse> rsp;

   shared_ptr<MibManager> mibManager = OamUserApplication::GetInstance().GetMibManager();
   RSYS_ASSERT(mibManager != NULL);

   RSYS_ASSERT(args.size() == 1);

   MibDN dn = MibDN::GenerateMibDN( args.at(0) );

   MibObjectDeleteResult delResult = mibManager->DeleteObject(dn);

   stringstream ss;
   ss << "Mib object deletion: " << MibObjectDeleteResultToString(delResult);

   rsp.reset(new CliResponse( ss.str() , CLI_ERROR_NONE));

   return rsp;
}

shared_ptr<CliResponse> OamCli::CliCmdMfList(const CliArguments& args)
{
   shared_ptr<CliResponse> rsp(new CliResponse(OamUserApplication::GetInstance().GetMfManager().ToString(), CLI_ERROR_NONE));

   return rsp;
}

shared_ptr<CliResponse> OamCli::CliCmdMfSetAdminState(const CliArguments& args)
{
   ManagedFing mf = MF_INVALID;

   // First argument must be matched against an MF.
   for(u32 searchMf = MF_RADIO; searchMf < MF_INVALID; searchMf++)
   {
      string searchMfString(ManagedFingToString((ManagedFing)searchMf));
      searchMfString = searchMfString.substr(3); // Remove the MF_ prefix

      if(args.at(0).CaselessEquals(searchMfString.c_str()))
      {
         // Match!
         mf = (ManagedFing)searchMf;
      }
   }

   if(mf == MF_INVALID)
   {
      shared_ptr<CliResponse> rsp(new CliResponse("Invalid MF", CLI_ERROR_INVALID_ARGUMENT));
      return rsp;
   }

   // Second argument must be one of 'unlocked', 'locked' or 'shuttingdown'
   bool success = false;
   if(args.at(1).CaselessEquals("unlocked"))
   {
      success = OamUserApplication::GetInstance().GetMfManager().SetMfAdminState(mf, ManagedObject::ADMIN_STATE_UNLOCKED);
   }
   else if(args.at(1).CaselessEquals("locked"))
   {
      success = OamUserApplication::GetInstance().GetMfManager().SetMfAdminState(mf, ManagedObject::ADMIN_STATE_LOCKED);
   }
   else if(args.at(1).CaselessEquals("shuttingdown"))
   {
      shared_ptr<CliResponse> rsp(new CliResponse("Shutting down not yet supported", CLI_ERROR_INVALID_ARGUMENT));
      return rsp;
   }
   else
   {
      shared_ptr<CliResponse> rsp(new CliResponse("Invalid 2nd arg, must be unlocked, locked or shuttingdown", CLI_ERROR_INVALID_ARGUMENT));
      return rsp;
   }

   shared_ptr<CliResponse> rsp;
   if(success)
   {
      rsp.reset(new CliResponse("Done!", CLI_ERROR_NONE));
   }
   else
   {
      rsp.reset(new CliResponse("Failed to set admin state.  Check MF is registered with oam.mf.list", CLI_ERROR_COMMAND_FAILED));
   }

   return rsp;
}

shared_ptr <CliResponse> OamCli::CliCmdSendAlarmEvent(const CliArguments& args)
{
   ostringstream responseString;
   s32 result = CLI_ERROR_NONE ;
   bool validated = true;
	u32 numOfCells = 1;

   u32 alarmId = atoi(args[0].c_str());
   ostringstream valCheck;

   valCheck << alarmId;

   string numCellStr = getConfigParam("OAM_NUM_CELL_ENTRIES", "");
	if(NULL != numCellStr.c_str())
		{
			numOfCells = (u16)atoi(numCellStr.c_str());
		}

   u32 numAlarms = FapAlarmId::MAX_ALARMS  * numOfCells;
   if(alarmId >= numAlarms)
   {
      responseString << "Alarm ID out-of-range, max=" << ((u32)FapAlarmId::NUM_ALARM_IDS - 1);
   }
   else
   {
      AlarmEvent::AlarmSeverity severity = AlarmEvent::ALARM_SEVERITY_CLEARED;
      AlarmEvent::AlarmEventLifetime lifetime = AlarmEvent::ALARM_EVENT_TRANSIENT;
      // note that 'cleared' or 'cl' are actually the default anyway, but make it explicit for clarity
      if(args.size() >= 2)
      {
         if((args[1].compare("cleared") == 0) || (args[1].compare("cl") == 0))
         {
            severity = AlarmEvent::ALARM_SEVERITY_CLEARED;
         }
         else if((args[2].compare("warning") == 0) || (args[2].compare("w") == 0))
         {
            severity = AlarmEvent::ALARM_SEVERITY_WARNING;
         }
         else if((args[2].compare("minor") == 0) || (args[2].compare("mi") == 0))
         {
            severity = AlarmEvent::ALARM_SEVERITY_MINOR;
         }
         else if((args[2].compare("major") == 0) || (args[2].compare("ma") == 0))
         {
            severity = AlarmEvent::ALARM_SEVERITY_MAJOR;
         }
         else if((args[2].compare("critical") == 0) || (args[2].compare("cr") == 0))
         {
            severity = AlarmEvent::ALARM_SEVERITY_CRITICAL;
         }
         else
         {
            responseString << "Alarm Severity invalid";
            validated = false;
         }

         if((args.size() >= 4) && validated)
         {
            if((args[3].compare("nontransient") == 0) || (args[3].compare("n") == 0))
            {
               lifetime = AlarmEvent::ALARM_EVENT_NONTRANSIENT;
            }
            else if((args[3].compare("transient") == 0) || (args[3].compare("t") == 0))
            {
               lifetime = AlarmEvent::ALARM_EVENT_TRANSIENT;
            }
            else
            {
               responseString << "Alarm Lifetime invalid";
               validated = false;
            }
         }
      }
      if(validated)
      {
         shared_ptr<FapAlarmId> rsysAlarmId(new FapAlarmId((FapAlarmId::Id)alarmId));
         AlarmEvent alarmEvent(rsysAlarmId,
               lifetime,
               severity,
               "Test alarm only!",
               AlarmEvent::ALARM_TYPE_PROCESSING);

         OamUserApplication::GetInstance().SendMessage(alarmEvent, ENTITY_OAM, ENTITY_OAM);
         responseString << "Sent alarm event to OAM: " << alarmEvent.ToString();
      }
   }

   shared_ptr<CliResponse> response (new CliResponse (responseString.str(), result)) ;
   return response ;
}



class CliOamAlarmVisitor : public AlarmEventListVisitor
{
   public:
      CliOamAlarmVisitor( string filename ) : m_file(NULL)
   {
      m_file = fopen( filename.c_str(), "w" );
   }
      CliOamAlarmVisitor( ) : m_file(NULL) {}
      virtual ~CliOamAlarmVisitor()
      {
         if(m_file)
         {
            fclose(m_file);
         }
      }

      void VisitAlarmEvent(const AlarmEvent& alarmEvent)
      {
         const char * severity[] = { "Cleared ", "Warning ", "Minor   ", "Major   ", "Critical" };

         char buffer[400];

         snprintf( buffer, sizeof(buffer),
               "%"PRIu32" %s %c%s %s %s %s\n",
               alarmEvent.GetSequenceNumber(),
               alarmEvent.GetObservationTime().ToString().c_str(),
               AlarmEvent::ALARM_EVENT_TRANSIENT == alarmEvent.GetLifetime()? '~':' ',
               severity[alarmEvent.GetSeverity()],
               alarmEvent.GetAlarmId()->ToString().c_str(),
               alarmEvent.GetAdditionalInfo().c_str(),
               alarmEvent.GetAddtnlInfo().c_str()
               );

         if(m_file)
         {
            fprintf( m_file,
                  "%s\n",
                  buffer
                  );
         }
         else
         {
            CliExecuteCmdInd cliInd( buffer );
            OamUserApplication::GetInstance().SendMessage(cliInd, ENTITY_CLI, ENTITY_TR069);
         }

      }

   private:
      FILE * m_file;
};

shared_ptr <CliResponse> OamCli::CliCmdAlarms(const CliArguments& args)
{
   ostringstream responseString;
   shared_ptr<CliOamAlarmVisitor> visitor;

   if(args.size())
   {
      visitor.reset(new CliOamAlarmVisitor(args[0]));
   }
   else
   {
      visitor.reset(new CliOamAlarmVisitor);
   }

   OamUserApplication::GetInstance().GetAlarmMgr().AcceptAlarmEventLogVisitor( *visitor );


   shared_ptr<CliResponse> response (new CliResponse (responseString.str(), CLI_ERROR_NONE)) ;
   return response ;
}

shared_ptr<CliResponse> OamCli::CliCmdSendAction(const CliArguments& args)
{
   ostringstream responseString;
   s32 result = CLI_ERROR_NONE ;

   u32 actionId = atoi(args[0].c_str());

   if(actionId > (u32)OAM_ACTION_UNDEFINED)
   {
      responseString << "Action ID out-of-range, max=" << ((u32)OAM_ACTION_UNDEFINED - 1);
   }
   else
   {
      shared_ptr<OamAction> oamActionId(new OamAction((OamAction)actionId));
      OamActionReq actionEvent(*oamActionId);

      OamUserApplication::GetInstance().SendMessage(actionEvent, ENTITY_OAM, ENTITY_OAM);
      responseString << "Sent action request to OAM: " << actionEvent.ToString();
   }

   shared_ptr<CliResponse> response (new CliResponse (responseString.str(), result)) ;
   return response ;
}

shared_ptr<CliResponse> OamCli::CliCmdRebootFap(const CliArguments& args)
{
   /*************************************************************************
    * THIS COMMAND IS IN THE "ATE" GROUP SO IS USED BY AUTOMATED TOOLS.
    * BE CAREFUL NOT TO MODIFY THE USAGE, BEHAVIOUR OR RESPONSE TEXT FORMAT!!
    *************************************************************************/

   OamActionReq oamActionReq(OAM_ACTION_REBOOT);
   OamUserApplication::GetInstance().SendMessage(oamActionReq, ENTITY_OAM, ENTITY_OAM);

   shared_ptr<CliResponse> response (new CliResponse ("Sent \"Reboot Fap\" to OAM.", CLI_ERROR_NONE)) ;
   return response ;
}



shared_ptr <CliResponse> OamCli::CliCmdPollKpis(const CliArguments& args)
{
   shared_ptr<CliResponse> response;

   if((args.size() != 1) || (!args.at(0).CaselessEquals("total") && !args.at(0).CaselessEquals("interval")))
   {
      response.reset(new CliResponse ("Argument must be 'total' or 'interval'.", CLI_ERROR_INVALID_ARGUMENT)) ;
   }
   else
   {
      OamUserApplication::GetInstance().GetKpiMgr().PollKpisWithoutReset(args.at(0).CaselessEquals("total"));
      response.reset(new CliResponse ("I've done it!  Now go check the oam trace file...", CLI_ERROR_NONE)) ;
   }

   return response ;
}

#if 0
shared_ptr<CliResponse> OamCli::CliCmdNetGetSwitch(const CliArguments& args)
{
   /*************************************************************************
    * THIS COMMAND IS IN THE "ATE" GROUP SO IS USED BY AUTOMATED TOOLS.
    * BE CAREFUL NOT TO MODIFY THE USAGE, BEHAVIOUR OR RESPONSE TEXT FORMAT!!
    *************************************************************************/

   shared_ptr<CliResponse> response;

   if ( args.at(0).CaselessEquals("MAC") )
   {
      CliCmdNetGetMac(args, response);
   }
   else if ( args.at(0).CaselessEquals("NUMBER_MACS") )
   {
      CliCmdNetGetNumberMacs(args, response);
   }
   else if ( args.at(0).CaselessEquals("IP") )
   {
      CliCmdNetGetIp(args, response);
   }
   else if ( args.at(0).CaselessEquals("NETMASK") )
   {
      CliCmdNetGetNetMask(args, response);
   }
   else if ( args.at(0).CaselessEquals("GW") )
   {
      CliCmdNetGetGW(args, response);
   }
   else
   {
      response.reset(new CliResponse("Invalid argument. Select from IP|NETMASK|GW|MAC|NUMBER_MACS", CLI_ERROR_INVALID_ARGUMENT));
   }

   return response;
}

shared_ptr<CliResponse> OamCli::CliCmdNetSetSwitch(const CliArguments& args)
{
   /*************************************************************************
    * THIS COMMAND IS IN THE "ATE" GROUP SO IS USED BY AUTOMATED TOOLS.
    * BE CAREFUL NOT TO MODIFY THE USAGE, BEHAVIOUR OR RESPONSE TEXT FORMAT!!
    *************************************************************************/

   shared_ptr<CliResponse> response;

   if ( args.at(0).CaselessEquals("MAC") )
   {
      CliCmdNetSetMac(args, response);
   }
   else if ( args.at(0).CaselessEquals("NUMBER_MACS") )
   {
      CliCmdNetSetNumberMacs(args, response);
   }
   else if ( args.at(0).CaselessEquals("IP") )
   {
      CliCmdNetSetIp(args, response);
   }
   else if ( args.at(0).CaselessEquals("NETMASK") )
   {
      CliCmdNetSetNetMask(args, response);
   }
   else if ( args.at(0).CaselessEquals("GW") )
   {
      CliCmdNetSetGW(args, response);
   }
   else
   {
      response.reset(new CliResponse("Invalid argument. Select from IP|NETMASK|GW|MAC|NUMBER_MACS", CLI_ERROR_INVALID_ARGUMENT));
   }

   return response;
}

void OamCli::CliCmdNetGetMac(const CliArguments& args, shared_ptr<CliResponse>& rsp)
{
   if ( args.size() > 2 )
   {
      rsp.reset( new CliResponse("Wrong number of parameters", CLI_ERROR_TOO_MANY_ARGUMENTS) );
      return;
   }

   if ( args.size() < 2 )
   {
      rsp.reset( new CliResponse("Wrong number of parameters", CLI_ERROR_TOO_FEW_ARGUMENTS) );
      return;
   }

   if ( args.at(1).CaselessEquals("eth0") )
   {
      string str;
      if(MibHelper::GetMibAttributeDirectAsString(PARAM_ID_UNIT_MAC_ADDRESS, str))
      {
         rsp.reset( new CliResponse( str, CLI_ERROR_NONE) );
      }
      else
      {
         rsp.reset( new CliResponse("Error on reading MAC address", CLI_ERROR_COMMAND_FAILED) );
      }
   }
   else
   {
      rsp.reset( new CliResponse("Unsupported network adapter", CLI_ERROR_COMMAND_FAILED) );
   }
}

void OamCli::CliCmdNetSetMac(const CliArguments& args, shared_ptr<CliResponse>& rsp)
{
   if ( args.size() > 3 )
   {
      rsp.reset( new CliResponse("Wrong number of parameters", CLI_ERROR_TOO_MANY_ARGUMENTS) );
      return;
   }

   if ( args.size() < 3 )
   {
      rsp.reset( new CliResponse("Wrong number of parameters", CLI_ERROR_TOO_FEW_ARGUMENTS) );
      return;
   }

   if ( !args.at(1).CaselessEquals("eth0") )
   {
      rsp.reset( new CliResponse("Unsupported network adapter", CLI_ERROR_COMMAND_FAILED) );
      return;
   }

   MibAttributeValues attrVals;
   attrVals.AddAttribute(PARAM_ID_UNIT_MAC_ADDRESS, args.at(2));
   MibAttrValidationFailures failures = OamUserApplication::GetInstance().GetMibManager()
      ->ValidateAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING), attrVals);
   if(failures.size() != 0)
   {
      rsp.reset( new CliResponse( failures.ToString(), CLI_ERROR_COMMAND_FAILED) );
      return;
   }

   OamUserApplication::GetInstance().GetMibManager()->SetAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING), attrVals);
   rsp.reset( new CliResponse( args.at(2), CLI_ERROR_NONE) );
}

void OamCli::CliCmdNetGetNumberMacs(const CliArguments& args, shared_ptr<CliResponse>& rsp)
{
   if ( args.size() > 1 )
   {
      rsp.reset( new CliResponse("Wrong number of parameters", CLI_ERROR_TOO_MANY_ARGUMENTS) );
      return;
   }

   if ( args.size() < 1 )
   {
      rsp.reset( new CliResponse("Wrong number of parameters", CLI_ERROR_TOO_FEW_ARGUMENTS) );
      return;
   }

   string str;
   if (MibHelper::GetMibAttributeDirectAsString(PARAM_ID_NUMBER_MACS, str))
   {
      rsp.reset( new CliResponse( str, CLI_ERROR_NONE) );
   }
   else
   {
      rsp.reset( new CliResponse("Error on reading Number of MAC addresses", CLI_ERROR_COMMAND_FAILED) );
   }
}

void OamCli::CliCmdNetSetNumberMacs(const CliArguments& args, shared_ptr<CliResponse>& rsp)
{
   if ( args.size() > 2 )
   {
      rsp.reset( new CliResponse("Wrong number of parameters", CLI_ERROR_TOO_MANY_ARGUMENTS) );
      return;
   }

   if ( args.size() < 2 )
   {
      rsp.reset( new CliResponse("Wrong number of parameters", CLI_ERROR_TOO_FEW_ARGUMENTS) );
      return;
   }

   MibAttributeValues attrVals;
   attrVals.AddAttribute(PARAM_ID_NUMBER_MACS, args.at(1).GetU32());
   MibAttrValidationFailures failures = OamUserApplication::GetInstance().GetMibManager()
      ->ValidateAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), attrVals);
   if(failures.size() != 0)
   {
      rsp.reset( new CliResponse( failures.ToString(), CLI_ERROR_COMMAND_FAILED) );
      return;
   }

   OamUserApplication::GetInstance().GetMibManager()->SetAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), attrVals);
   rsp.reset( new CliResponse( args.at(1), CLI_ERROR_NONE) );
}

void OamCli::CliCmdNetGetIp(const CliArguments& args, shared_ptr<CliResponse>& rsp)
{
   if ( args.size() > 2 )
   {
      rsp.reset( new CliResponse("Wrong number of parameters", CLI_ERROR_TOO_MANY_ARGUMENTS) );
      return;
   }

   if ( args.size() < 2 )
   {
      rsp.reset( new CliResponse("Wrong number of parameters", CLI_ERROR_TOO_FEW_ARGUMENTS) );
      return;
   }

   if ( args.at(1).CaselessEquals("eth0") )
   {
      string str;
      if (MibHelper::GetMibAttributeDirectAsString(PARAM_ID_STATIC_IP_CONFIG_IP_ADDRESS, str))
      {
         rsp.reset( new CliResponse( str, CLI_ERROR_NONE) );
      }
      else
      {
         rsp.reset( new CliResponse("Error on reading IP address", CLI_ERROR_COMMAND_FAILED) );
      }
   }
   else
   {
      rsp.reset( new CliResponse("Unsupported network adapter", CLI_ERROR_COMMAND_FAILED) );
   }
}

void OamCli::CliCmdNetSetIp(const CliArguments& args, shared_ptr<CliResponse>& rsp)
{
   if ( args.size() > 3 )
   {
      rsp.reset( new CliResponse("Wrong number of parameters", CLI_ERROR_TOO_MANY_ARGUMENTS) );
      return;
   }

   if ( args.size() < 3 )
   {
      rsp.reset( new CliResponse("Wrong number of parameters", CLI_ERROR_TOO_FEW_ARGUMENTS) );
      return;
   }

   if ( !args.at(1).CaselessEquals("eth0") )
   {
      rsp.reset( new CliResponse("Unsupported network adapter", CLI_ERROR_COMMAND_FAILED) );
      return;
   }

   MibAttributeValues attrVals;
   attrVals.AddAttribute(PARAM_ID_STATIC_IP_CONFIG_IP_ADDRESS, args.at(2));
   MibAttrValidationFailures failures = OamUserApplication::GetInstance().GetMibManager()
      ->ValidateAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING), attrVals);
   if(failures.size() != 0)
   {
      rsp.reset( new CliResponse( failures.ToString(), CLI_ERROR_COMMAND_FAILED) );
      return;
   }

   OamUserApplication::GetInstance().GetMibManager()->SetAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING), attrVals);
   rsp.reset( new CliResponse( args.at(2), CLI_ERROR_NONE) );
}

void OamCli::CliCmdNetGetNetMask(const CliArguments& args, shared_ptr<CliResponse>& rsp)
{
   if ( args.size() > 2 )
   {
      rsp.reset( new CliResponse("Wrong number of parameters", CLI_ERROR_TOO_MANY_ARGUMENTS) );
      return;
   }

   if ( args.size() < 2 )
   {
      rsp.reset( new CliResponse("Wrong number of parameters", CLI_ERROR_TOO_FEW_ARGUMENTS) );
      return;
   }

   if ( args.at(1).CaselessEquals("eth0") )
   {
      string str;
      if (MibHelper::GetMibAttributeDirectAsString(PARAM_ID_STATIC_IP_CONFIG_NET_MASK, str))
      {
         rsp.reset( new CliResponse( str, CLI_ERROR_NONE) );
      }
      else
      {
         rsp.reset( new CliResponse("Error on reading Netmask value", CLI_ERROR_COMMAND_FAILED) );
      }
   }
   else
   {
      rsp.reset( new CliResponse("Unsupported network adapter", CLI_ERROR_COMMAND_FAILED) );
   }
}


void OamCli::CliCmdNetSetNetMask(const CliArguments& args, shared_ptr<CliResponse>& rsp)
{
   if ( args.size() > 3 )
   {
      rsp.reset( new CliResponse("Wrong number of parameters", CLI_ERROR_TOO_MANY_ARGUMENTS) );
      return;
   }

   if ( args.size() < 3 )
   {
      rsp.reset( new CliResponse("Wrong number of parameters", CLI_ERROR_TOO_FEW_ARGUMENTS) );
      return;
   }

   if ( !args.at(1).CaselessEquals("eth0") )
   {
      rsp.reset( new CliResponse("Unsupported network adapter", CLI_ERROR_COMMAND_FAILED) );
      return;
   }

   MibAttributeValues attrVals;
   attrVals.AddAttribute(PARAM_ID_STATIC_IP_CONFIG_NET_MASK, args.at(2));
   MibAttrValidationFailures failures = OamUserApplication::GetInstance().GetMibManager()
      ->ValidateAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING), attrVals);
   if(failures.size() != 0)
   {
      rsp.reset( new CliResponse( failures.ToString(), CLI_ERROR_COMMAND_FAILED) );
      return;
   }

   OamUserApplication::GetInstance().GetMibManager()->SetAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING), attrVals);
   rsp.reset( new CliResponse( args.at(2), CLI_ERROR_NONE) );
}

void OamCli::CliCmdNetGetGW(const CliArguments& args, shared_ptr<CliResponse>& rsp)
{
   if ( args.size() > 2 )
   {
      rsp.reset( new CliResponse("Wrong number of parameters", CLI_ERROR_TOO_MANY_ARGUMENTS) );
      return;
   }

   if ( args.size() < 2 )
   {
      rsp.reset( new CliResponse("Wrong number of parameters", CLI_ERROR_TOO_FEW_ARGUMENTS) );
      return;
   }

   if ( !args.at(1).CaselessEquals("eth0") )
   {
      rsp.reset( new CliResponse("Unsupported network adapter", CLI_ERROR_COMMAND_FAILED) );
      return;
   }

   string str;
   if (MibHelper::GetMibAttributeDirectAsString(PARAM_ID_STATIC_IP_CONFIG_GATEWAY, str))
   {
      rsp.reset( new CliResponse( str, CLI_ERROR_NONE) );
   }
   else
   {
      rsp.reset( new CliResponse("Error on reading Gateway value for given address", CLI_ERROR_COMMAND_FAILED) );
   }
}

void OamCli::CliCmdNetSetGW(const CliArguments& args, shared_ptr<CliResponse>& rsp)
{
   if ( args.size() > 3 )
   {
      rsp.reset( new CliResponse("Wrong number of parameters", CLI_ERROR_TOO_MANY_ARGUMENTS) );
      return;
   }

   if ( args.size() < 3 )
   {
      rsp.reset( new CliResponse("Wrong number of parameters", CLI_ERROR_TOO_FEW_ARGUMENTS) );
      return;
   }

   if ( !args.at(1).CaselessEquals("eth0") )
   {
      rsp.reset( new CliResponse("Unsupported network adapter", CLI_ERROR_COMMAND_FAILED) );
      return;
   }

   MibAttributeValues attrVals;
   attrVals.AddAttribute(PARAM_ID_STATIC_IP_CONFIG_GATEWAY, args.at(2));
   MibAttrValidationFailures failures = OamUserApplication::GetInstance().GetMibManager()
      ->ValidateAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING), attrVals);
   if(failures.size() != 0)
   {
      rsp.reset( new CliResponse( failures.ToString(), CLI_ERROR_COMMAND_FAILED) );
      return;
   }

   OamUserApplication::GetInstance().GetMibManager()->SetAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING), attrVals);
   rsp.reset( new CliResponse( args.at(2), CLI_ERROR_NONE) );
}

shared_ptr<CliResponse> OamCli::CliCmdNetDhcp(const CliArguments& args)
{
   /*************************************************************************
    * THIS COMMAND IS IN THE "ATE" GROUP SO IS USED BY AUTOMATED TOOLS.
    * BE CAREFUL NOT TO MODIFY THE USAGE, BEHAVIOUR OR RESPONSE TEXT FORMAT!!
    *************************************************************************/

   shared_ptr<CliResponse> rsp;

   if ( args.size() > 3 )
   {
      rsp.reset( new CliResponse("Wrong number of parameters", CLI_ERROR_TOO_MANY_ARGUMENTS) );
      return rsp;
   }

   if ( args.size() < 2 )
   {
      rsp.reset( new CliResponse("Wrong number of parameters", CLI_ERROR_TOO_FEW_ARGUMENTS) );
      return rsp;
   }

   if ( args.at(0).CaselessEquals("eth0") )
   {
      MibAttributeValues attrVals;
      if ( args.at(1).CaselessEquals("enable") )
      {
         attrVals.AddAttribute(PARAM_ID_DHCP, (u32)1);

         if ( args.size() == 3 )
         {
            char commandString[255];

            snprintf(commandString, sizeof(commandString), "echo \"%s\" > /mnt/config/eth0_dhcp_enable",
                  args.at(2).c_str() );
            if(system(commandString) != oam_ret_zero)
            {
               TRACE_MSG(" OamCli::CliCmdNetDhcp, System command Echo failed");
            }	
         }
      }
      else if ( args.at(1).CaselessEquals("disable") )
      {
         attrVals.AddAttribute(PARAM_ID_DHCP, (u32)0);
      }
      else
      {
         rsp.reset(new CliResponse("Invalid argument. It must be 'enable' or 'disable'", CLI_ERROR_INVALID_ARGUMENT));
         return rsp;
      }

      MibAttrValidationFailures failures = OamUserApplication::GetInstance().GetMibManager()
         ->ValidateAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING), attrVals);
      if(failures.size() != 0)
      {
         rsp.reset( new CliResponse( failures.ToString(), CLI_ERROR_COMMAND_FAILED) );
         return rsp;
      }

      OamUserApplication::GetInstance().GetMibManager()->SetAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING), attrVals);
   }
   else
   {
      rsp.reset(new CliResponse("Invalid argument. The only adaptor supported is eth0", CLI_ERROR_INVALID_ARGUMENT));
      return rsp;
   }

   rsp.reset( new CliResponse( args.at(0), CLI_ERROR_NONE) );

   return rsp;
}

shared_ptr<CliResponse> OamCli::CliCmdNetNtpEnable(const CliArguments& args)
{
   /*************************************************************************
    * THIS COMMAND IS IN THE "ATE" GROUP SO IS USED BY AUTOMATED TOOLS.
    * BE CAREFUL NOT TO MODIFY THE USAGE, BEHAVIOUR OR RESPONSE TEXT FORMAT!!
    *************************************************************************/

   shared_ptr<CliResponse> rsp;

   if ( args.size() > 1 )
   {
      rsp.reset( new CliResponse("Wrong number of parameters", CLI_ERROR_TOO_MANY_ARGUMENTS) );
      return rsp;
   }

   if ( args.size() < 1 )
   {
      rsp.reset( new CliResponse("Wrong number of parameters", CLI_ERROR_TOO_FEW_ARGUMENTS) );
      return rsp;
   }

   MibAttributeValues attrVals;
   if ( args.at(0).CaselessEquals("enable") )
   {
      attrVals.AddAttribute(PARAM_ID_FREQ_SYNC_ADMIN_STATE, (u32)1);
   }
   else if ( args.at(0).CaselessEquals("disable") )
   {
      attrVals.AddAttribute(PARAM_ID_FREQ_SYNC_ADMIN_STATE, (u32)0);
   }
   else
   {
      rsp.reset(new CliResponse("Invalid argument. Value should be enable or disable", CLI_ERROR_INVALID_ARGUMENT));
      return rsp;
   }

   MibAttrValidationFailures failures = OamUserApplication::GetInstance().GetMibManager()
      ->ValidateAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), attrVals);
   if(failures.size() != 0)
   {
      rsp.reset( new CliResponse( failures.ToString(), CLI_ERROR_COMMAND_FAILED) );
      return rsp;
   }

   OamUserApplication::GetInstance().GetMibManager()->SetAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), attrVals);
   rsp.reset( new CliResponse( args.at(0), CLI_ERROR_NONE) );

   return rsp;
}

shared_ptr<CliResponse> OamCli::CliCmdNetNtpSetServer(const CliArguments& args)
{
   /*************************************************************************
    * THIS COMMAND IS IN THE "ATE" GROUP SO IS USED BY AUTOMATED TOOLS.
    * BE CAREFUL NOT TO MODIFY THE USAGE, BEHAVIOUR OR RESPONSE TEXT FORMAT!!
    *************************************************************************/

   shared_ptr<CliResponse> rsp;
   MibAttributeId id = PARAM_ID_INVALID;

   if ( args.size() > 2 )
   {
      rsp.reset( new CliResponse("Wrong number of parameters", CLI_ERROR_TOO_MANY_ARGUMENTS) );
      return rsp;
   }

   if ( args.size() < 2 )
   {
      rsp.reset( new CliResponse("Wrong number of parameters", CLI_ERROR_TOO_FEW_ARGUMENTS) );
      return rsp;
   }

   if ( args.at(0).CaselessEquals("1") )
   {
      id = PARAM_ID_FREQ_SYNC_NTP_SERVER_1;
   }
   else if ( args.at(0).CaselessEquals("2") )
   {
      id = PARAM_ID_FREQ_SYNC_NTP_SERVER_2;
   }
   else if ( args.at(0).CaselessEquals("3") )
   {
      id = PARAM_ID_FREQ_SYNC_NTP_SERVER_3;
   }
   else if ( args.at(0).CaselessEquals("4") )
   {
      id = PARAM_ID_FREQ_SYNC_NTP_SERVER_4;
   }
   else
   {
      rsp.reset(new CliResponse("Invalid argument. Supported Server numbers are 1, 2, 3, 4", CLI_ERROR_INVALID_ARGUMENT));
      return rsp;
   }

   MibAttributeValues attrVals;
   attrVals.AddAttribute(id, args.at(1));
   MibAttrValidationFailures failures = OamUserApplication::GetInstance().GetMibManager()
      ->ValidateAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), attrVals);
   if(failures.size() != 0)
   {
      rsp.reset( new CliResponse( failures.ToString(), CLI_ERROR_COMMAND_FAILED) );
      return rsp;
   }

   OamUserApplication::GetInstance().GetMibManager()->SetAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), attrVals);
   rsp.reset( new CliResponse( args.at(1), CLI_ERROR_NONE) );

   return rsp;
}

shared_ptr<CliResponse> OamCli::CliCmdNetRestart(const CliArguments& args)
{
   /*************************************************************************
    * THIS COMMAND IS IN THE "ATE" GROUP SO IS USED BY AUTOMATED TOOLS.
    * BE CAREFUL NOT TO MODIFY THE USAGE, BEHAVIOUR OR RESPONSE TEXT FORMAT!!
    *************************************************************************/

   shared_ptr<CliResponse> rsp;

   if(system("/mnt/dbx/network-restart") != oam_ret_zero)
   {
      TRACE_MSG("OamCli::CliCmdNetRestart, Network restart command failed");
   }

   rsp.reset(new CliResponse("Networking should restart now...", CLI_ERROR_NONE));
   return rsp;
}
#endif

shared_ptr<CliResponse> OamCli::CliCmdScan(const CliArguments& args)
{
   shared_ptr<CliResponse> rsp;

   //OamUserApplication::GetInstance().TriggerFullRemScan();
   OamUserApplication::GetInstance().SendRemScanReq();

   rsp.reset(new CliResponse("Rem Scan requested...", CLI_ERROR_NONE));

   return rsp;
}

shared_ptr<CliResponse> OamCli::CliCmdDummyStatus(const CliArguments& args)
{
   shared_ptr<CliResponse> rsp;
   CRemScanStatus oRemScanStatus ("errorString",
         1,
         1); 
   //RSYS_ASSERT(oRemScanStatus != NULL);
   OamUserApplication::GetInstance().SendMessage(oRemScanStatus, ENTITY_OAM, ENTITY_CLI);

   rsp.reset(new CliResponse("Rem Scan status...", CLI_ERROR_NONE));

   return rsp;
}

shared_ptr<CliResponse> OamCli::CliCmdAbortScan(const CliArguments& args)
{
   shared_ptr<CliResponse> rsp;

   OamUserApplication::GetInstance().SendAbortRemScanReq();

   rsp.reset(new CliResponse("Abort Rem Scan Requested...", CLI_ERROR_NONE));

   return rsp;
}

#if 0
#ifdef PRODUCT_hbs2_iu
shared_ptr<CliResponse> OamCli::CliCmdNetCSSetServer(const CliArguments& args)
{
   /*************************************************************************
    * THIS COMMAND IS IN THE "ATE" GROUP SO IS USED BY AUTOMATED TOOLS.
    * BE CAREFUL NOT TO MODIFY THE USAGE, BEHAVIOUR OR RESPONSE TEXT FORMAT!!
    *************************************************************************/

   shared_ptr<CliResponse> rsp;
   MibAttributeId id = PARAM_ID_INVALID;

   if ( args.size() > 2 )
   {
      rsp.reset( new CliResponse("Wrong number of parameters", CLI_ERROR_TOO_MANY_ARGUMENTS) );
      return rsp;
   }

   if ( args.size() < 2 )
   {
      rsp.reset( new CliResponse("Wrong number of parameters", CLI_ERROR_TOO_FEW_ARGUMENTS) );
      return rsp;
   }

   if ( args.at(0).CaselessEquals("1") )
   {
      id = PARAM_ID_LTE_SEC_GW_SERVER_1;
   }
   else if ( args.at(0).CaselessEquals("2") )
   {
      id = PARAM_ID_LTE_SEC_GW_SERVER_2;
   }
   else if ( args.at(0).CaselessEquals("3") )
   {
      id = PARAM_ID_LTE_SEC_GW_SERVER_3;
   }
   else
   {
      rsp.reset(new CliResponse("Invalid argument. Supported Server numbers are 1, 2, 3", CLI_ERROR_INVALID_ARGUMENT));
      return rsp;
   }

   MibAttributeValues attrVals;
   attrVals.AddAttribute(id, args.at(1));
   MibAttrValidationFailures failures = OamUserApplication::GetInstance().GetMibManager()
      ->ValidateAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING), attrVals);
   if(failures.size() != 0)
   {
      rsp.reset( new CliResponse( failures.ToString(), CLI_ERROR_COMMAND_FAILED) );
      return rsp;
   }

   OamUserApplication::GetInstance().GetMibManager()->SetAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING), attrVals);
   rsp.reset( new CliResponse( args.at(1), CLI_ERROR_NONE) );

   return rsp;
}
#endif
#endif

shared_ptr<CliResponse> OamCli::CliCmdGetState(const CliArguments& args)
{
   shared_ptr<CliResponse> rsp(new CliResponse(FapMO::GetInstance().ToString(), CLI_ERROR_NONE));

   return rsp;
}

shared_ptr<CliResponse> OamCli::CliCmdRabStatus(const CliArguments& args)
{
   ostringstream responseStream ;
   string attrValueString;
   struct timespec absTimeout;
   Thread::InitialiseMutex(m_Mutex);
   Thread::ConditionInit(m_Condition);
   bool bFetchStringValueSuccess;
   u32 timeoutMilliSecs = 20000;
   shared_ptr<CliResponse> response;

   if ( args.size() > 0 )
   {
      response.reset( new CliResponse("Wrong number of parameters", CLI_ERROR_TOO_MANY_ARGUMENTS) );
      return response;
   }

   MibAttributeValues attrVals;
   u32 getValue = 1;
   attrVals.AddAttribute(PARAM_ID_RAB_STATUS_REQUEST, getValue);
   MibAttrValidationFailures failures = OamUserApplication::GetInstance().GetMibManager()
      ->ValidateAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), attrVals);
   if(failures.size() != 0)
   {
      response.reset( new CliResponse( failures.ToString(), CLI_ERROR_COMMAND_FAILED) );
      return response;
   }
   OamUserApplication::GetInstance().GetMibManager()->SetAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), attrVals);

   Thread::ConditionGetAbsTimeout(timeoutMilliSecs, &absTimeout);

   //wait here for the event before proceedin
   Thread::ConditionTimedWait(m_Condition, m_Mutex, &absTimeout);

   bFetchStringValueSuccess = MibHelper::GetMibAttributeDirectAsString(PARAM_ID_RAB_STATUS_REPORT, attrValueString);
   //fill the structure into rabstatus

   if ( (true == bFetchStringValueSuccess) && (NULL != attrValueString.c_str()) )
   {
      TRACE_PRINTF("%s:Fetching RabStatus successfull",__FUNCTION__);
      responseStream << attrValueString;
      response.reset(new CliResponse (responseStream.str(), CLI_ERROR_NONE)) ;
   }
   else
   {
      TRACE_PRINTF("%s:Unable to fetch RabStatus",__FUNCTION__);
      responseStream << "Unable to fetch RabStatus";
      response.reset(new CliResponse (responseStream.str(), CLI_ERROR_NONE)) ;
   }

   //This is just to make sure that the request is set back to 0 before the next request
   getValue = 0;
   attrVals.AddAttribute(PARAM_ID_RAB_STATUS_REQUEST, getValue);
   failures = OamUserApplication::GetInstance().GetMibManager()->ValidateAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), attrVals);
   if(failures.size() != 0)
   {
      TRACE_PRINTF("%s: cli command failed while setting rabstatus request to 0",__FUNCTION__);
   }
   OamUserApplication::GetInstance().GetMibManager()->SetAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), attrVals);
   //The above code of setting the value to 0 and is nothing to do to cli request/response
   return response;
}

void OamCli::CliCmdRabStatusResponse()
{
   TRACE_PRINTF("%s: Entry-unlocking the mutex lock and releasing the condition",__FUNCTION__);
   Thread::ConditionSignal(m_Condition);
   TRACE_PRINTF("%s: Exit-unlocking the mutex lock and releasing the condition",__FUNCTION__);
}

#ifdef _UPDATE_CLI_PROXY
shared_ptr<CliResponse> OamCli::CliCmdFtpReq(const CliArguments& args)
{
   return ForwardFtpReq("req", args) ;
}

shared_ptr<CliResponse> OamCli::CliCmdFtpGetUpdate(const CliArguments& args)
{
   return ForwardFtpReq("getupdate", args);
}

shared_ptr<CliResponse> OamCli::CliCmdFtpAbort(const CliArguments& args)
{
   return ForwardFtpReq("abort", args) ;
}

shared_ptr<CliResponse> OamCli::CliCmdFtpStatus(const CliArguments& args)
{
   return ForwardFtpReq("status", args);
}

shared_ptr<CliResponse> OamCli::ForwardFtpReq(const string command, const CliArguments& args)
{
   ostringstream argString;
   for (uint argCount = 0; argCount < args.size(); argCount++)
   {
      argString << args[argCount] << " ";
   }
   TRACE_PRINTF ("Forwarding command %s: %s to ENTITY_FTP", command.c_str(), argString.str().c_str()) ;
   shared_ptr<CliExecuteCmdReq> cliCmd (new CliExecuteCmdReq (command.c_str(),
            argString.str().c_str()));

   OamUserApplication::GetInstance().SendMessage(*cliCmd, ENTITY_FTP, ENTITY_CLI);
   shared_ptr<CliResponse> response ((CliResponse *)NULL) ;
   return response ;
}

#endif
