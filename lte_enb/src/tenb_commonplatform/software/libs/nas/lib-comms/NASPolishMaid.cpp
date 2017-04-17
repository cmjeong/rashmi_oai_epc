///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// NASPolishMaid.cpp
//
// Housekeeping thread, calling various virtuals that allow a user
// application to perform any periodic tidying and maintenance.  This is
// a bit of a avgue description, but I'm sure what I'll use it for right
// now!
//
// Copyright � 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <unistd.h>

#include <lib-system/NASTrace.h>
#include <system/TimeWrap.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "NASPolishMaid.h"
#include "NASApp.h"

///////////////////////////////////////////////////////////////////////////////
// Local Definitions
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Class: NASPolishMaid
// Desc : Wake up every <user defined> period and call the NASApp class
//        virtual to allow periodic housekeeping to take place.
///////////////////////////////////////////////////////////////////////////////
NASPolishMaid::NASPolishMaid (NASApplication &nasApp, u32 cleaningPeriodInSeconds) :
	m_nasApp (nasApp),
	m_cleaningPeriod (cleaningPeriodInSeconds)
{
    SetThreadName("NASPolishMaid");
}

NASPolishMaid::~NASPolishMaid ()
{
}

u32 NASPolishMaid::ThreadProcedure ()
{
	NAS_ENTER ();
	NAS_TRACE ("The Maid Has Her Feet Up: Cleaning Period Is", m_cleaningPeriod);

	while (!ThreadStopped ())
	{
		NAS_MSG ("Maid Will Be Sleeping Heavily - No Response To ThreadStop() request!!");
		sleep (m_cleaningPeriod);

		// Housekeeping period has expired.
		threeway::TimeWrap timeNow;
		NAS_TRACE ("Maid Started Work At", timeNow);

		// Virtual call to leaf classes to get maintenance tasks done.
		m_nasApp.HouseKeeper ();

		timeNow.Touch ();
		NAS_TRACE ("Maid Has Exited The Building At", timeNow);

        // Check stack usage for this thread.
        //CheckStackUsage();

	}//end while

	NAS_MSG ("Maid Has Downed Tools And Left Permanently");
	NAS_RETURN (1);
}
