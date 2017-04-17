///////////////////////////////////////////////////////////////////////////////
//
// Tr069SetParameterValues.h
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069SetParameterValues_h_
#define __Tr069SetParameterValues_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <string>
#include <boost/shared_ptr.hpp>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069XmlStringUtils.h"
#include "Xmlable.h"
#include "Tr069ParameterList.h"

using namespace std;
using namespace boost;
using namespace tr069;

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

class SetParameterValues
{
public:
    SetParameterValues()
    {}

    SetParameterValues(xmlNodePtr cur)
    {
        TRACE_PRINTF("TR069-Parse:" "SetParameterValues");

        /* We don't care what the top level element name is */
        cur = cur->xmlChildrenNode;

        while (cur != NULL)
        {
            string curName((const char*)cur->name);

            if(curName == "ParameterList")
            {
                m_parameterList = shared_ptr<ParameterList>(new ParameterList(cur));
            }
            else if(curName == "ParameterKey")
            {
                m_parameterKey = XmlStringUtils::ExtractFromNode(cur);

                TRACE_PRINTF("TR069-Parse:" "ParameterKey=%s", m_parameterKey.c_str() );
            }
            else
            {
                TRACE_PRINTF("TR069-Parse:" "Unhandled %s", (const char*)cur->name);
            }

            cur = cur->next;
        }
    }

    virtual ~SetParameterValues()
    {}

    shared_ptr<ParameterList> m_parameterList;
    std::string m_parameterKey;
};

}

#endif
