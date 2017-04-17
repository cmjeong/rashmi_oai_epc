///////////////////////////////////////////////////////////////////////////////
//
// Tr069FtpFile.h
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069FtpFile_h_
#define __Tr069FtpFile_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069TransactionSessionCommand.h"

namespace tr069
{

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////


class FtpFile
{
public:
    typedef enum Type_tag
    {

        SwLoad,
        SwTransfer,
        AlarmSituation,
        AlarmLog,
        PmData,
        SwDiagnostics,
        Unspecified,

        NumberOfTypes

    } Type;

    FtpFile() {}
    virtual ~FtpFile() {}

    virtual Type GetType() const { return Unspecified; }
    virtual const char * ToString() const { return "Unspecified"; }
    virtual const char * GetResponseEventCodeSuccessString() const { return "7 TRANSFER COMPLETE"; }
    virtual const char * GetResponseEventCodeFailureString() const { return "7 TRANSFER COMPLETE"; }
};

class SwLoadFile : public FtpFile
{
    Type GetType() const { return SwLoad; }
    const char * ToString() const { return "X 000FBB SW load"; }
    const char * GetResponseEventCodeSuccessString() const { RSYS_ASSERT_PRINTF(false, "Upon success, reboot, don't respond using this mechanism"); return ""; }
    const char * GetResponseEventCodeFailureString() const { return "X 000FBB SW activation failed"; }
};

class SwTransferFile : public FtpFile
{
    Type GetType() const { return SwTransfer; }
    const char * ToString() const { return "X 000FBB SW Transfer"; }
    const char * GetResponseEventCodeSuccessString() const { return "X 000FBB SW transfered"; }
    const char * GetResponseEventCodeFailureString() const { return "X 000FBB SW transfer failed"; }
};

class AlarmSituationFile : public FtpFile
{
    Type GetType() const { return AlarmSituation; }
    const char * ToString() const { return "X 000FBB Alarm Situation"; }
    const char * GetResponseEventCodeSuccessString() const { return "X 000FBB active alarm list upload complete"; }
    const char * GetResponseEventCodeFailureString() const { return "X 000FBB active alarm list upload failed"; }
};

class AlarmLogFile : public FtpFile
{
    Type GetType() const { return AlarmLog; }
    const char * ToString() const { return "X 000FBB Alarm Log"; }
    const char * GetResponseEventCodeSuccessString() const { return "X 000FBB Alarm Log File upload complete"; }
    const char * GetResponseEventCodeFailureString() const { return "X 000FBB Alarm Log File upload failed"; }
};

class PmDataFile : public FtpFile
{
    Type GetType() const { return PmData; }
    const char * ToString() const { return "X 000FBB Pm data"; }
    const char * GetResponseEventCodeSuccessString() const { return "X 000FBB measurement data upload complete"; }
    const char * GetResponseEventCodeFailureString() const { return "X 000FBB measurement data upload failed"; }
};

class SwDiagnosticsFile : public FtpFile
{
    Type GetType() const { return SwDiagnostics; }
    const char * ToString() const { return "X 000FBB SW diagnostics"; }
    const char * GetResponseEventCodeSuccessString() const { return "X 000FBB SW diagnostics upload complete"; }
    const char * GetResponseEventCodeFailureString() const { return "X 000FBB SW diagnostics upload failed"; }
};



}
#endif
