///////////////////////////////////////////////////////////////////////////////
//
// Tr069ParameterValueStruct.h
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069ParameterValueStruct_h_
#define __Tr069ParameterValueStruct_h_

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



class ParameterValueStruct : public Xmlable
{
public:
    ParameterValueStruct(const string & name = "", const string & value = "", const ExtDMAttrDataType type = INT) :
        m_name(name),
        m_value(value),
        m_type(type)
        
    {
    }

    ParameterValueStruct(xmlNodePtr cur)
    {
        TRACE_PRINTF("TR069-Parse:" "ParameterValueStruct");

        /* We don't care what the top level element name is */
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

    virtual ~ParameterValueStruct()
    {}

    bool QueryValid() const
    {
        return !(m_name.empty());
    }

    virtual string Xmlise() const
    {
        stringstream ss;
		string xsdType = GetType(m_type);

        if(QueryValid())
        {
            string pvsValue = XmlStringUtils::ToElementString("Name",  XmlStringUtils::Filter(m_name))
                            + XmlStringUtils::ToElementString("Value", XmlStringUtils::Filter(m_value), "", XmlStringUtils::Filter(xsdType));

            ss << XmlStringUtils::ToElementString("ParameterValueStruct", pvsValue);
        }

        return ss.str();
    }

	string GetType(ExtDMAttrDataType dmtype) const
	{
		string typeStr;
		switch(dmtype)
		{
			case 0:
				typeStr = "int";
				break;
			case 1:
				typeStr = "unsignedInt";
				break;
			case 2:
				typeStr = "string";
				break;
			case 3:
				typeStr = "boolean";
				break;
			case 4:
				typeStr = "dateTime";
				break;
			default:
				typeStr = "";
				break;

		}
				
		return typeStr;
	}

    string m_name;
    string m_value;
	ExtDMAttrDataType m_type;
};

}

#endif
