///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// HLRData.h
//
// Structures, enums, defines etc. used by any application involved in HLR
// operations.
//
// Copyright � 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __HLRData_h_
#define __HLRData_h_

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

// Header to allow a _very_ simple subscriber management.
typedef struct structHLRDatabaseHeader
{
	// Keep track of our allocated TMSI numbers, to try and prevent
	// multiple MS ending up with the same one!
	// For now, we will simply start at 0 and count to 9999 allocating
	// TMSI in an increment of 1.  Probably need to make this system better in
	// the future, but it will do for now...
	u32 nextTmsi;

	// Number of valid subscriber records following in the HLR.
	u32 numberOfSubscribers;

}HLRDatabaseHeader;

#define K_KEY_SIZE			16	// Bytes, or 128 Bits.

// Look, it's not a REAL HLR: so we limit the number of subscribers
// in the database.  No need to be silly about this...
#define MAX_NUMBER_OF_SUBSCRIBERS	128


#endif

