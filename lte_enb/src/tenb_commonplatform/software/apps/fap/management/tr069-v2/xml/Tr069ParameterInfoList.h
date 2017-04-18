///////////////////////////////////////////////////////////////////////////////
//
// Tr069ParameterInfoList.h
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069ParameterInfoList_h_
#define __Tr069ParameterInfoList_h_

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
#include "Tr069ParameterInfoStruct.h"
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

class ParameterInfoList_t : public map< string /* name */, shared_ptr<ParameterInfoStruct> >
{
public:
    string ToString() const
    {
        stringstream ss;

        ss << "ParameterInfoList_t: ";
        for( ParameterInfoList_t::const_iterator i = begin();
             i != end();
             ++i)
        {
            ss << "[" << i->first << "]=" << (i->second?i->second->m_writable : string("{null}")) << "; ";
        }

        return ss.str();
    }
};

class ParameterInfoList : public Xmlable
{
   public:
      ParameterInfoList()
      {
      }

      /*
      ParameterInfoList(xmlNodePtr cur)
      {
         cur = cur->xmlChildrenNode;
         while (cur != NULL)
         {
            string curName((const char*)cur->name);

            if( curName == "ParameterInfoStruct")
            {
               shared_ptr<ParameterInfoStruct> pis(new ParameterInfoStruct(cur));

               if( pis && pis->QueryValid())
               {
                  m_parameters[pis->m_name] = pis;
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

      virtual ~ParameterInfoList()
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

            for( ParameterInfoList_t::const_iterator i = m_parameters.begin();
                  i != m_parameters.end();
                  ++i)
            {
               const shared_ptr<ParameterInfoStruct> pis = i->second;

               plValue += pis->Xmlise();
            }

            stringstream plAttrib;
            plAttrib << "soap-enc:arrayType=\"cwmp:ParameterInfoStruct[" << m_parameters.size() << "]\"";

            ss << XmlStringUtils::ToElementString("ParameterList", plValue, plAttrib.str());
         }

         return ss.str();
      }

      void AppendParameter( const string & name, const string & writable = "")
      {
         shared_ptr<ParameterInfoStruct> pis(new ParameterInfoStruct(name, writable));

         ParameterInfoList_t::iterator i = m_parameters.find(name);

         if(i != m_parameters.end())
         {
             //Need to debug why this happens
             //TRACE_PRINTF("Parameter %s already exists", name.c_str());
         }
         else
         {
            m_parameters[name] = pis;
         }

      }

      void AppendParameters( const ParameterInfoList & additionalParameters )
      {
         for(ParameterInfoList_t::const_iterator i = additionalParameters.m_parameters.begin(); i != additionalParameters.m_parameters.end(); ++i)
         {
            shared_ptr<ParameterInfoStruct> pis = i->second;

            AppendParameter(pis->m_name, pis->m_writable);
         }
      }

      ParameterInfoList_t m_parameters;
};

}

#endif
