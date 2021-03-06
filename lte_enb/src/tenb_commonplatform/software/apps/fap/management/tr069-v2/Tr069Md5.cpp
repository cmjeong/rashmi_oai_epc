///////////////////////////////////////////////////////////////////////////////
//
// Md5
//
// Generates an MD5 sum
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <md5.h>
#include <system/Trace.h>
#include <system/StringUtils.h>

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "Tr069Md5.hpp"

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////
namespace tr069
{
///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

Md5::Md5( Filename filename ) :
    m_md5(),
    m_filename(filename)
{

}

Md5::Md5( string filename ) :
    m_md5(),
    m_filename(filename)
{

}

Md5::~Md5()
{

}


}
