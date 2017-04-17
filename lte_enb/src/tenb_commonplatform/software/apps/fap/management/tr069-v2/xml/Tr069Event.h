///////////////////////////////////////////////////////////////////////////////
//
// Tr069Event.h
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069Event_h_
#define __Tr069Event_h_

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
#include "Tr069EventStruct.h"

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
typedef map< string /* eventCode */, shared_ptr<EventStruct> > EventList_t;

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class Event : public Xmlable
{
public:
    Event()
    {}

    virtual ~Event()
    {}

    bool QueryValid() const
    {
        return !(m_eventList.empty());
    }

    string Xmlise() const
    {
        stringstream ss;

        if(QueryValid())
        {
            string elValue;

            for( EventList_t::const_iterator i = m_eventList.begin();
                 i != m_eventList.end();
                 ++i)
            {
                shared_ptr<EventStruct> es = i->second;
                elValue += es->Xmlise();
            }

            stringstream elAttrib;
            elAttrib << "soap-enc:arrayType=\"cwmp:EventStruct[" << m_eventList.size() << "]\"";

            ss << XmlStringUtils::ToElementString("Event", elValue, elAttrib.str());
        }

        return ss.str();
    }

    void AddEvent( const string & eventCode, const string & commandKey = "" )
    {
        EventList_t::iterator i = m_eventList.find(eventCode);

        if(i != m_eventList.end())
        {
            if(!commandKey.empty())
            {
                shared_ptr<EventStruct> es = i->second;
                es->m_commandKey = commandKey;
            }
        }
        else
        {
            shared_ptr<EventStruct> es(new EventStruct(eventCode, commandKey));
            m_eventList[eventCode] = es;
        }
    }

    EventList_t m_eventList;
};

}

#endif
