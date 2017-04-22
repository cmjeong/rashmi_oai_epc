///////////////////////////////////////////////////////////////////////////////
//
// ValidatorT30SeriesTmr.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorT30SeriesTmr.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorT30SeriesTmr::ValidateU32Array(const std::vector<u32>& value, u32 min, u32 max, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
{
   ENTER();

   bool isValid = false;

   for(u32 i = 0; i < value.size(); i++)
   {
      switch ( value.at(i) )
      {
         case 100:
         case 200:
         case 300:
         case 400:
         case 600:
         case 1000:
         case 1500:
         case 2000:
            isValid = true;
            break;
         default:
            isValid = false;
            break;
      }
   }

   if(!isValid)
   {
      ostringstream description;
      description << "Supported T30SeriesTimer are (" <<
         "100, 200, 300, 400, 600, 1000, 1500, 2000)";
      failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
   }

   RETURN(isValid);
}
