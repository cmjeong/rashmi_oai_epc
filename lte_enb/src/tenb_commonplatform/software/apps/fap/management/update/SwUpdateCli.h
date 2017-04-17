///////////////////////////////////////////////////////////////////////////////
//
// SwUpdateCli.h
//
// Module for CLI handlers.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __SwUpdateCli_h_
#define __SwUpdateCli_h_

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

class FtpCli
{
    public:
		/**
		 * Register all FTP CLI commands with CLI handler.
		 *
		 * \param UpdateCliHandler CLI handler to register commands with.
		 */
        static void RegisterFtpCliCmds(shared_ptr<CliHandler> UpdateCliHandler);

    private:
        /**
         * FTP related CLI command handling functions.
         *
         * \param args Arguments to CLI command.
         */
        static shared_ptr<CliResponse> CliCmdFtpReq(const CliArguments& args);
#ifdef PRODUCT_generic
        static shared_ptr<CliResponse> CliCmdFtpGetCoverage(const CliArguments& args);
#endif
        static shared_ptr<CliResponse> CliCmdFtpGetUpdate(const CliArguments& args);
        static shared_ptr<CliResponse> CliCmdFtpAbort(const CliArguments& args);
        static shared_ptr<CliResponse> CliCmdFtpStatus(const CliArguments& args);
};

#endif
