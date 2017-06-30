///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// Timer.h
//
// Wrapper class that manages NASTimer objects.
//
// Copyright © 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __NASTimer_h_
#define __NASTimer_h_

#include <system/TimerInterface.h>

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

// Maximum number of characters allowed in a NASTimer name: no need to
// be silly about this!
#define MAX_NASTimer_NAME	64

class NASTimer
{
public:
	// Construction / destruction
	NASTimer (u32 timeoutPeriod, bool deleteOnExpiry, const char *NASTimerName);
	virtual ~NASTimer ();

	threeway::TimerHandle GetHandle () const;
	u32 GetTimerPeriod () const;
	bool DeleteOnExpiry () const;
	const char *GetTimerName () const;

private:

	// Unique handle identifying this NASTimer.
	threeway::TimerHandle m_timerHandle;

	// Duration (in milliseconds) of this NASTimer.
	u32 m_timerPeriod;

	// When this NASTimer expires, should be delete it from the main NASTimer engine?
	bool m_deleteOnExpiry;

	// Debug information: give a name to our NASTimer to help us find
	// out what is going on when a NASTimer expires.
	char m_timerName[MAX_NASTimer_NAME];

	// Seeding used when creating new NASTimers.
	static threeway::TimerHandle s_nextTimerHandle;
};


#endif

