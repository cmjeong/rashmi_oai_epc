///////////////////////////////////////////////////////////////////////////////
//
// OamCli.h
//
// Module for CLI handlers.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __OamCli_h_
#define __OamCli_h_
#ifdef PRODUCT_generic
extern "C" void __gcov_flush(void);
#endif

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <messaging/transport/CliHandler.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

// Remove this to disable "proxying" of FTP/Update CLI commands and bump ATE CLI
// version reported - provided to (more or less) preserve the current CLI interface
// for the moment but (hopefully) to be removed for V2.0 once ATE/Test/Commissioning
// tools have been tweaked appropriately.
#define _UPDATE_CLI_PROXY

class OamCli
{
public:
    static void RegisterOamCliCmds(shared_ptr<CliHandler> oamCliHandler);
    static void RegisterMibCliCmds(shared_ptr<CliHandler> mibCliHandler);
    void CliCmdRabStatusResponse(); 

private:
    static shared_ptr<CliResponse> CliCmdGetCliVersion(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdGetCoverage(const CliArguments& args);
    // MIB
    static shared_ptr<CliResponse> CliCmdMibSetAttribute(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdMibGetAttribute(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdMibDeleteAttribute(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdMibGetAttributeWild(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdMibGetAttributeDesc(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdMibGetDiffsFromDefaults(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdMibGetNv(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdMibGetCellConfig(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdMibSubscriptions(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdMibCreate(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdMibDelete(const CliArguments& args);


    // Managed Fings
    static shared_ptr<CliResponse> CliCmdMfList(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdMfSetAdminState(const CliArguments& args);

    static shared_ptr<CliResponse> CliCmdSendAlarmEvent(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdAlarms(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdSendAction(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdRebootFap(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdPollKpis(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdNetGetSwitch(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdNetSetSwitch(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdNetDhcp(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdNetNtpEnable(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdNetNtpSetServer(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdNetCSSetServer(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdNetRestart(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdScan(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdDummyStatus(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdAbortScan(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdGetState(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdSetLed(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdRabStatus(const CliArguments& args); 	

    static void CliCmdNetGetMac(const CliArguments& args, shared_ptr<CliResponse>& ptr);
    static void CliCmdNetSetMac(const CliArguments& args, shared_ptr<CliResponse>& ptr);
    static void CliCmdNetGetNumberMacs(const CliArguments& args, shared_ptr<CliResponse>& ptr);
    static void CliCmdNetSetNumberMacs(const CliArguments& args, shared_ptr<CliResponse>& ptr);
    static void CliCmdNetGetIp(const CliArguments& args, shared_ptr<CliResponse>& ptr);
    static void CliCmdNetSetIp(const CliArguments& args, shared_ptr<CliResponse>& ptr);
    static void CliCmdNetGetNetMask(const CliArguments& args, shared_ptr<CliResponse>& ptr);
    static void CliCmdNetSetNetMask(const CliArguments& args, shared_ptr<CliResponse>& ptr);
    static void CliCmdNetGetGW(const CliArguments& args, shared_ptr<CliResponse>& ptr);
    static void CliCmdNetSetGW(const CliArguments& args, shared_ptr<CliResponse>& ptr);

#ifdef _UPDATE_CLI_PROXY
    static shared_ptr<CliResponse> CliCmdFtpReq(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdFtpGetUpdate(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdFtpAbort(const CliArguments& args);
    static shared_ptr<CliResponse> CliCmdFtpStatus(const CliArguments& args);
    /*static shared_ptr<CliResponse> CliCmdStartUpdateApps(const CliArguments& args);*/
    /*static shared_ptr<CliResponse> CliCmdStartInstallApps(const CliArguments& args);*/
    /*static shared_ptr<CliResponse> CliCmdStartActivateApps(const CliArguments& args);*/
    /*static shared_ptr<CliResponse> CliCmdStartRevertApps(const CliArguments& args);*/
    /*static shared_ptr<CliResponse> CliCmdUpdateStatus(const CliArguments& args);*/

    static shared_ptr<CliResponse> ForwardFtpReq(const string command, const CliArguments& args) ;
    /*static shared_ptr<CliResponse> ForwardUpdateReq(const string command, const CliArguments& args) ;*/
#endif
};

#endif
