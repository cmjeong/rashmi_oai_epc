///////////////////////////////////////////////////////////////////////////////
//
// CwmpInform.h
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CwmpInform_h_
#define __CwmpInform_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <string>
#include <boost/shared_ptr.hpp>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "Tr069Application.h"
#include "Tr069Event.h"
#include "Tr069DeviceId.h"
#include "Tr069ParameterList.h"
#include "Tr069XmlStringUtils.h"

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

class CwmpInform : public Xmlable
{
public:
    CwmpInform(): m_retryCount(0)
    {
    }

    CwmpInform(u32 retryCount): m_retryCount(retryCount)
    {
    }

    virtual ~CwmpInform()
    {}

    bool QueryValid() const
    {
        return m_event.QueryValid();
    }

    string Xmlise() const
    {
        string xmlString;

        if(QueryValid())
        {
            string currentTime;
            stringstream value;
            stringstream rc;
            rc << m_retryCount;

            string retryCount = rc.str();

            value
            << DeviceId::ToXml()
            << m_event.Xmlise()
            << XmlStringUtils::ToElementString("MaxEnvelopes", "1" )
            << XmlStringUtils::ToElementString("CurrentTime", Tr069Application::GetInstance().GetFormattedCurrentTime(currentTime) )
            << XmlStringUtils::ToElementString("RetryCount", retryCount)
            << m_parameterList.Xmlise();

            xmlString = XmlStringUtils::ToElementString("cwmp:Inform", value.str());
        }
        else
        {
            TRACE_PRINTF("Inform::Xmlise(invalid)");
        }

        return xmlString;
    }

    Event m_event;
    ParameterList m_parameterList;
    u32 m_retryCount;
};

}

#endif
