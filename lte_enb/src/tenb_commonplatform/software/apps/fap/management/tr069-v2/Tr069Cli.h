///////////////////////////////////////////////////////////////////////////////
//
// Tr069Cli.h
//
// Module for cli handlers.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069Cli_h_
#define __Tr069Cli_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include "messaging/transport/CliHandler.h"

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

namespace tr069
{



class Tr069CliCommands
{
public:
    Tr069CliCommands(ApplicationWithMessaging & appWithMess);
    ~Tr069CliCommands(){}

    void Register();
private:
    ApplicationWithMessaging & m_appWithMess;
    static CppCliPair s_cppCliPairs[];
    static shared_ptr<CliResponse> CliCmdAddObject(const CliArguments& args);
#ifdef PRODUCT_generic
    static shared_ptr<CliResponse> CliCmdGetCoverage(const CliArguments& args);
#endif
    static shared_ptr<CliResponse> CliCmdDeleteObject(const CliArguments& args);    
    static shared_ptr<CliResponse> CliCmdDownloadRequest(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdUploadRequest(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdClocks(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdAlarms(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdUploadFmFile(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdGenPmFile(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdGenAndUploadPmFile(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdGenMibXmlAndUpload(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdActionFactoryReset(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdSetParameterAttributeNotificationActive(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdSetParameterAttributeNotificationOff(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdSetParameterAttributeNotificationPassive(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdGetParameterValue(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdSetParameterValue(const CliArguments& args);
};
}
#endif
