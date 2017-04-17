
#ifndef __ProcessGuardian_h_
#define __ProcessGuardian_h_


///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sys/types.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Guardian.h"

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class ProcessGuardian : public Guardian
{
public:
    ProcessGuardian(pid_t p, const char * descriptor);
    ~ProcessGuardian();

    // Checks if the guarded process is alive
    bool  IsGood();

    // Get the pid of the process being guarded
    pid_t GetPid() { return m_pid; };

    std::string ToString();

private:
    // Information provided by the process being checked.
    pid_t       m_pid;
    std::string m_descriptor;

    // Locally generated information.
    std::string m_exeName;
    std::string m_pidFile;
};

#endif
