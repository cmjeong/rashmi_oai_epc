///////////////////////////////////////////////////////////////////////////////
//
// Tr069AttributeList.h
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069AttributeList_h_
#define __Tr069AttributeList_h_

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
#include "Tr069ParameterAttributeStruct.h"
#include "Xmlable.h"

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

class AttributeList_t : public map< string /* name */, shared_ptr<ParameterAttributeStruct> >
{
public:
    string ToString() const
    {
        stringstream ss;

        ss << "AttributeList_t: ";
        for( AttributeList_t::const_iterator i = begin();
             i != end();
             ++i)
        {
            ss << "[" << i->first << "]=" << (i->second?i->second->m_notification : string("{null}")) << "; ";
        }

        return ss.str();
    }
};

class AttributeList : public Xmlable
{
   public:
      AttributeList()
      {
      }

      /*(
      AttributeList(xmlNodePtr cur)
      {
         // We don't care what the top level element name is
         cur = cur->xmlChildrenNode;
         while (cur != NULL)
         {
            string curName((const char*)cur->name);

            if( curName == "ParameterAttributeStruct")
            {
               shared_ptr<ParameterAttributeStruct> pvs(new ParameterAttributeStruct(cur));

               if( pvs && pvs->QueryValid())
               {
                  m_attributes[pvs->m_name] = pvs;
               }
            }
            else
            {
               TRACE_PRINTF("TR069-Parse:" "Unhandled %s", (const char*)cur->name);
            }

            cur = cur->next;
         }
      }
      */

      virtual ~AttributeList()
      {}


      bool QueryValid() const
      {
         return !(m_attributes.empty());
      }

      string Xmlise() const
      {
         stringstream ss;

         if(QueryValid())
         {
            string plValue;

            for( AttributeList_t::const_iterator i = m_attributes.begin();
                  i != m_attributes.end();
                  ++i)
            {
               const shared_ptr<ParameterAttributeStruct> pvs = i->second;

               plValue += pvs->Xmlise();
            }

            stringstream plAttrib;
            plAttrib << "soap-enc:arrayType=\"cwmp:ParameterAttributeStruct[" << m_attributes.size() << "]\"";

            ss << XmlStringUtils::ToElementString("AttributeList", plValue, plAttrib.str());
         }

         return ss.str();
      }

      void AppendParameter( const string & name, const string & notification = "")
      {
         shared_ptr<ParameterAttributeStruct> pas(new ParameterAttributeStruct(name, notification));

         AttributeList_t::iterator i = m_attributes.find(name);

         if(i == m_attributes.end())
         {
            m_attributes[name] = pas;
         }

      }

      void AppendParameters( const AttributeList & additionalAttributes )
      {
         for(AttributeList_t::const_iterator i = additionalAttributes.m_attributes.begin(); i != additionalAttributes.m_attributes.end(); ++i)
         {
            shared_ptr<ParameterAttributeStruct> pas = i->second;

            AppendParameter(pas->m_name, pas->m_notification);
         }
      }

      AttributeList_t m_attributes;
};

}

#endif



