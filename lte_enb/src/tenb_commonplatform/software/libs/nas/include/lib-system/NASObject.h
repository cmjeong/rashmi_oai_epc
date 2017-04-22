///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// NASObject.h
//
// If you want to keep track of some object in the NAS system, then derive
// it from here.  Information about creation, deletion and usage will then
// be logged using the NASTrace engine.
//
// Copyright © 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __NASObject_h_
#define __NASObject_h_

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/TimeWrap.h>

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

class NASTrace;

// This handy little structure is purely for debug use, when calculating
// ranges of connection numbers, etc. in use.
typedef struct tagNumberRange
{
	u32 rangeStart;
	u32 rangeEnd;
}NumberRange;

///////////////////////////////////////////////////////////////////////////////
// Class: NASObject
// Desc : Generic information is stored here that we can use to debug
//        object creation + deletion.
///////////////////////////////////////////////////////////////////////////////
class NASObject
{
// Define a very close relationship between the TRACE class, and the OBJECT
// class so the debug output can obtain access to all relevant information
// in an object, while it is not accessible to anyone else.  This prevents
// naughty user code from trying to access debug options that are private.
friend class NASTrace;

public:
	// Construction / destruction.
    NASObject ();
    virtual ~NASObject ();

	// Code obtained from MS to clear the console output window.
	static void ClearTheScreen ();

	// Retrieve object creation time.
	const threeway::TimeWrap &GetCreateTime () const;

protected:

	// Update the creation time: this is so objects created on the 
	// stack can mimic the create logic without actually allocating
	// a new object.
	void UpdateCreateTime ();

protected:

	// Time at which the contructor was run.
	threeway::TimeWrap m_creationTime;

	// Time at which the destructor was run.
	threeway::TimeWrap m_deletionTime;
};

#endif
