///////////////////////////////////////////////////////////////////////////////
//
// Tr069ParameterInfoStruct.h
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069ParameterInfoStruct_h_
#define __Tr069ParameterInfoStruct_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <string>
#include <libxml/parser.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Xmlable.h"
#include "Tr069XmlStringUtils.h"
#include "DataModelTypes.h"

using namespace std;
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



class ParameterInfoStruct : public Xmlable
{
public:
    ParameterInfoStruct(const string & name = "", const string & writable = "") :
        m_name(name),
        m_writable(writable)
    {
    }

    /*
    ParameterInfoStruct(xmlNodePtr cur)
    {
        TRACE_PRINTF("TR069-Parse:" "ParameterInfoStruct");

        cur = cur->xmlChildrenNode;
        while (cur != NULL)
        {
            string curName((const char*)cur->name);

            if(curName == "Name")
            {
                m_name = XmlStringUtils::ExtractFromNode(cur);

                TRACE_PRINTF("TR069-Parse:" "Name=%s", m_name.c_str() );
            }
            else if(curName == "Value")
            {
                m_value = XmlStringUtils::ExtractFromNode(cur);

                TRACE_PRINTF("TR069-Parse:" "Value=%s", m_value.c_str() );
            }
            else
            {
                TRACE_PRINTF("TR069-Parse:" "Unhandled %s", (const char*)cur->name);
            }
            cur = cur->next;
        }
    }
    */

    virtual ~ParameterInfoStruct()
    {}

    bool QueryValid() const
    {
        return !(m_name.empty());
    }

    virtual string Xmlise() const
    {
        stringstream ss;

        if(QueryValid())
        {
            string pisValue = XmlStringUtils::ToElementString("Name",  XmlStringUtils::Filter(m_name))
                            + XmlStringUtils::ToElementString("Writable", XmlStringUtils::Filter(m_writable));
            ss << XmlStringUtils::ToElementString("ParameterInfoStruct", pisValue);
        }

        return ss.str();
    }

    string m_name;
    string m_writable;
};

}

#endif
