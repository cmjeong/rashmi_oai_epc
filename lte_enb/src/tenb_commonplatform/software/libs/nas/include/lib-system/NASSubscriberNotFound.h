///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// NASException.h
//
// Base application Exception class.
//
// Copyright ? 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __NASSubscriberNotFound_h_
#define __NASSubscriberNotFound_h_

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

#include <ed_c.h>
#include "NASException.h"

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Class: NASException
// Desc : Base exception class holding generic information about the
//        problem that has occured.
///////////////////////////////////////////////////////////////////////////////
class NASSubscriberNotFound : public NASException
{
public:
	NASSubscriberNotFound (const char *fileId, u32 lineNum, const c_MobileId &subscriberIdentity);
	virtual ~NASSubscriberNotFound ();

	const c_MobileId &GetSubscriberIdentity () const;

private:

	// Identity that caused the problem.
	c_MobileId m_subscriberIdentity;	
};

#endif

