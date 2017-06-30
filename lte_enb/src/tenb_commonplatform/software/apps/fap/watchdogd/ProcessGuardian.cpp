
///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sstream>

#include <Radisys.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ProcessGuardian.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

ProcessGuardian::ProcessGuardian(pid_t p, const char * descriptor) :
    m_pid(p),
    m_descriptor(descriptor)
{
    char          buf[1024];
    ostringstream s;
    s16           l;

    // Create the pid directory
    s << "/proc/" << m_pid;
    m_pidFile = s.str();

    // Now read the exe symlink
    s << "/exe";
    l = readlink(s.str().c_str(), buf, sizeof(buf) - 1);
    if(l > 0 && l < (signed)sizeof(buf))
    {
        buf[(unsigned)l] = '\0';
        m_exeName = buf;
    }
    else
    {
        m_exeName = "<unknown>";
    }
}

ProcessGuardian::~ProcessGuardian()
{
}


bool ProcessGuardian::IsGood(void)
{
    struct stat sb;

    // Stat the process directory to ensure the task exists
    return stat(m_pidFile.c_str(), &sb) == 0;
}


std::string ProcessGuardian::ToString()
{
    ostringstream s;

    s << "ProcessGuardian { pid=" << m_pid << ", descriptor=" << m_descriptor << ", exe=" << m_exeName << " }";

    return s.str();
}
