///////////////////////////////////////////////////////////////////////////////
//
// SerialisationIds.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "SerialisationIds.h"

/*
 * Generate the function that lets us get the string equivalent of an enum value.
 */

#define ENUM_GENERATE_STRINGS

#include "SerialisationIds.h"

#undef ENUM_GENERATE_STRINGS

/*
 * Generate the function that lets us dump the whole enum as value / string pairs.
 */

#define ENUM_GENERATE_TABLE

#include "SerialisationIds.h"

#undef ENUM_GENERATE_TABLE
