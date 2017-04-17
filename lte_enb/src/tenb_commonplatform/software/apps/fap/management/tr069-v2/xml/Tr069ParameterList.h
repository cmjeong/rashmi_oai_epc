///////////////////////////////////////////////////////////////////////////////
//
// Tr069ParameterList.h
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069ParameterList_h_
#define __Tr069ParameterList_h_

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
#include "Tr069ParameterValueStruct.h"
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

class ParameterList_t : public map< string /* name */, shared_ptr<ParameterValueStruct> >
{
public:
    string ToString() const
    {
        stringstream ss;

        ss << "ParameterList_t: ";
        for( ParameterList_t::const_iterator i = begin();
             i != end();
             ++i)
        {
            ss << "[" << i->first << "]=" << (i->second?i->second->m_value : string("{null}")) << "; ";
        }

        return ss.str();
    }
};

class ParameterList : public Xmlable
{
   public:
      ParameterList()
      {
      }

      ParameterList(xmlNodePtr cur)
      {
         /* We don't care what the top level element name is */
         cur = cur->xmlChildrenNode;
         while (cur != NULL)
         {
            string curName((const char*)cur->name);

            if( curName == "ParameterValueStruct")
            {
               shared_ptr<ParameterValueStruct> pvs(new ParameterValueStruct(cur));

               if( pvs && pvs->QueryValid())
               {
                  m_parameters[pvs->m_name] = pvs;
               }
            }
            else
            {
               TRACE_PRINTF("TR069-Parse:" "Unhandled %s", (const char*)cur->name);
            }

            cur = cur->next;
         }
      }

      virtual ~ParameterList()
      {}


      bool QueryValid() const
      {
         return !(m_parameters.empty());
      }

      string Xmlise() const
      {
         stringstream ss;

         if(QueryValid())
         {
            string plValue;

            for( ParameterList_t::const_iterator i = m_parameters.begin();
                  i != m_parameters.end();
                  ++i)
            {
               const shared_ptr<ParameterValueStruct> pvs = i->second;

               plValue += pvs->Xmlise();
            }

            stringstream plAttrib;
            plAttrib << "soap-enc:arrayType=\"cwmp:ParameterValueStruct[" << m_parameters.size() << "]\"";

            ss << XmlStringUtils::ToElementString("ParameterList", plValue, plAttrib.str());
         }

         return ss.str();
      }

      void AppendParameter( const string & name, const string & value = "" , ExtDMAttrDataType type = INT)
      {
         shared_ptr<ParameterValueStruct> pvs(new ParameterValueStruct(name, value, type));

         ParameterList_t::iterator i = m_parameters.find(name);

         if(i != m_parameters.end())
         {
            shared_ptr<ParameterValueStruct> oldPvs = i->second;

            if(pvs->m_value != oldPvs->m_value)
            {
               TRACE_PRINTF("Parameter %s appends different value (was:%s, now:%s)", name.c_str(), oldPvs->m_value.c_str(), pvs->m_value.c_str() );
            }
            oldPvs->m_value = pvs->m_value;
         }
         else
         {
            m_parameters[name] = pvs;
         }

      }

      void AppendParameters( const ParameterList & additionalParameters )
      {
         for(ParameterList_t::const_iterator i = additionalParameters.m_parameters.begin(); i != additionalParameters.m_parameters.end(); ++i)
         {
            shared_ptr<ParameterValueStruct> pvs = i->second;

            AppendParameter( pvs->m_name, pvs->m_value, pvs->m_type);
         }
      }

      ParameterList_t m_parameters;
};

}

#endif
