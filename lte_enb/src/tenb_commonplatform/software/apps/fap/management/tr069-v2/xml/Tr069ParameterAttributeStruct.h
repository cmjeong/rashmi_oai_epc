///////////////////////////////////////////////////////////////////////////////
//
// Tr069ParamterAttributeStruct.h
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069ParamterAttributeStruct_h_
#define __Tr069ParamterAttributeStruct_h_

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



class ParameterAttributeStruct : public Xmlable
{
public:
    ParameterAttributeStruct(const string & name = "", const string & notification = "") :
        m_name(name),
        m_notification(notification)
    {
    }

    /*
    ParamterAttributeStruct(xmlNodePtr cur)
    {
        TRACE_PRINTF("TR069-Parse:" "ParameterAttributeStruct");

        // We don't care what the top level element name is
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

    virtual ~ParameterAttributeStruct()
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
            string pvsValue = XmlStringUtils::ToElementString("Name",  XmlStringUtils::Filter(m_name))
                            + XmlStringUtils::ToElementString("Notification", XmlStringUtils::Filter(m_notification))
                            + XmlStringUtils::ToElementString("AccessList", XmlStringUtils::Filter(""));

            ss << XmlStringUtils::ToElementString("ParameterAttributeStruct", pvsValue);
        }

        return ss.str();
    }

    string m_name;
    string m_notification;
};

}

#endif

