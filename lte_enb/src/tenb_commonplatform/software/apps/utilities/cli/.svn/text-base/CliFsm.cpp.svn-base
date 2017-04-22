///////////////////////////////////////////////////////////////////////////////
//
// CliApplication.h
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CliApplication.h"
#include "CliFsmInterface.h"

using namespace std;




void CliFsm::Start()
{
    m_fsm.InjectStart(NULL);
}

void CliFsm::Stop( const char * reason)
{
    shared_ptr<string> event(new string(reason));
    m_fsm.InjectStop(event);
}

void CliFsm::HandleMessage( shared_ptr<MessageSerialisedData> message )
{
    switch (message->GetSerialisationId())
    {

     case SERIALISATION_ID_CLI_EXECUTE_CMD_IND:
     {
         shared_ptr<CliExecuteCmdInd> event = Serialisable::DeSerialise<CliExecuteCmdInd>(message);
         m_fsm.InjectCommandResponse(event);
     }
     break;

     case SERIALISATION_ID_CLI_EXECUTE_CMD_PROGRESS_IND:
     {
         shared_ptr<CliExecuteCmdProgressInd> event = Serialisable::DeSerialise<CliExecuteCmdProgressInd>(message);
         m_fsm.InjectCommandProgressing(event);
     }
     break;

     case SERIALISATION_ID_CLI_EXECUTE_CMD_CNF:
     {
         shared_ptr<CliExecuteCmdCnf> event = Serialisable::DeSerialise<CliExecuteCmdCnf>(message);
         m_fsm.InjectCommandComplete(event);
     }
     break;

     default:
         break;
     }

     EXIT ();
}

bool CliFsm::HandleTimerExpiry( TimerHandle id )
{
    bool handled = m_interface->MatchedTimerHandle(id);

    if(handled)
    {
        m_fsm.InjectTimeout(NULL);
    }

    return handled;
}

void CliFsm::HandleCommandLine( shared_ptr<CliCommand> command )
{
    m_fsm.InjectCommandLine(command);
}

