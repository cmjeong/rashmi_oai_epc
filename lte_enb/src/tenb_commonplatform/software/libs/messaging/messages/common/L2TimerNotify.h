///////////////////////////////////////////////////////////////////////////////
//
// EventNotify.h
//
// Class is used for indication between OAM and OAM-SM
//
// Copyright radisys Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __L2TimerNotify_h_
#define __L2TimerNotify_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class L2TimerNotify : public threeway::Serialisable
{
public:
    /**
     * Construction / destruction.
     */
	L2TimerNotify():m_timeoutPeriodMs(0) {} 
    L2TimerNotify(u32 timeoutPeriodMs):m_timeoutPeriodMs(timeoutPeriodMs) {}
    virtual ~L2TimerNotify() {};

    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_L2TIMER_NOTIFY; }
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const 
	{ 
	   // Serialise all the members.
       u8* serialisedData = data;
       SerialiseIt(m_timeoutPeriodMs, serialisedData);
       RETURN(serialisedData - data); 
	}
    virtual bool DeSerialise(const u8* data, u32 dataLen) 
	{ 
	   DeSerialiseIt(m_timeoutPeriodMs, data);
       RETURN(true);
	}

    virtual std::string ToString() const 
	{ 
	   ostringstream stream;
       stream << "L2TimerNotify with timeoutPeriodMs "<< m_timeoutPeriodMs;
	  
	   RETURN(stream.str());
	}
	
	u32 GetTimeoutPeriodMs() const { return m_timeoutPeriodMs; };

private:
    u32 m_timeoutPeriodMs;
};

#endif
