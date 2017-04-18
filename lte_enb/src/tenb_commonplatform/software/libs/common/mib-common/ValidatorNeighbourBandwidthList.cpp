///////////////////////////////////////////////////////////////////////////////
//
// ValidatorNeighbourBandwidthList.cpp 
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
#include <vector>
#include <set>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorNeighbourBandwidthList.h"

using namespace std;


///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorNeighbourBandwidthList::ValidateU32Array(const std::vector<u32>& value, u32 minValue, u32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
{
   set<u32> allowedBandwidthValues;
   set<u32>::iterator allowedBandwidthValuesIter;
   allowedBandwidthValues.insert(6);
   allowedBandwidthValues.insert(15);
   allowedBandwidthValues.insert(25);
   allowedBandwidthValues.insert(50);
   allowedBandwidthValues.insert(75);
   allowedBandwidthValues.insert(100);

   bool isValid = false;
   ostringstream failureDescription;
   for(size_t index = 0; index < value.size(); index++)
   {
      u32 bandwidth = value[index];
      isValid = ValidateU32(value.at(index), minValue, maxValue, failureDescriptor);
      if(!isValid)
      {
         RETURN(isValid);
      }
      allowedBandwidthValuesIter = allowedBandwidthValues.find(bandwidth);
      if(allowedBandwidthValuesIter == allowedBandwidthValues.end())
      {
         failureDescription << "Bandwidth " << bandwidth << " is not supported." << "Allowed values for LTE_OAM_NEIGHBOUR_EUTRA_CELL_DL_BW/LTE_OAM_NEIGHBOUR_EUTRA_CELL_UL_BW are 6,15,25,50,75 and 100.";
         failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, failureDescription.str());
         RETURN(false);
      }
   } 
   RETURN(true);
}

