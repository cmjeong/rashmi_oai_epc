///////////////////////////////////////////////////////////////////////////////
//
// MibObjectDeleteResult.cpp
//
// Implementation of EnumToString.h functions.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibObjectDeleteResult.h"

/*
 * Generate the function that lets us get the string equivalent of an enum value.
 */

#define ENUM_GENERATE_STRINGS

#include "MibObjectDeleteResult.h"

#undef ENUM_GENERATE_STRINGS

/*
 * Generate the function that lets us dump the whole enum as value / string pairs.
 */

#define ENUM_GENERATE_TABLE
// Not used.
//#include "MibAttributeId.h"

#undef ENUM_GENERATE_TABLE
