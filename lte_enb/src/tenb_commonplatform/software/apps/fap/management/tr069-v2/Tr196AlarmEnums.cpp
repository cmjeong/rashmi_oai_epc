///////////////////////////////////////////////////////////////////////////////
//
// GsmBandId.cpp
//
// Implementation of EnumToString.h functions.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr196AlarmEnums.h"

/*
 * Generate the function that lets us get the string equivalent of an enum value.
 */

#define ENUM_GENERATE_STRINGS

#include "Tr196AlarmEnums.h"

#undef ENUM_GENERATE_STRINGS

#define ENUM_GENERATE_THE_FROM_STRING_FUNCTION

#include "Tr196AlarmEnums.h"

#undef ENUM_GENERATE_THE_FROM_STRING_FUNCTION

/*
 * Generate the function that lets us dump the whole enum as value / string pairs.
 */

#define ENUM_GENERATE_TABLE
// Not used.
//#include "MibAttributeId.h"

#undef ENUM_GENERATE_TABLE
