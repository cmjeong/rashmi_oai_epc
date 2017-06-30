///////////////////////////////////////////////////////////////////////////////
//
// ValidatorEarfcnList.cpp 
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

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorEarfcnList.h"

using namespace std;

struct DlFreq
{
	u32 minNDL;
	u32 maxNDL;   
};
struct DlFreq dlFreqList[41] = { {0,0}, //invalid
	{0,599},
	{600,1199},
	{1200,1949},
	{1950,2399},
	{2400,2649},
	{2650,2749},
	{2750,3449},
	{3450,3799},
	{3880,4149},
	{4150,4749},
	{4750,4949},
	{5010,5179},
	{5180,5279},
	{5280,5379},
	{0,0},
	{0,0},
	{5730,5849},
	{5850,5999},
	{6000,6149},
	{6150,6449},
	{6450,6599},
	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{36000,36199},
	{36200,36349},
	{36350,36949},
	{36950,37549},
	{37550,37749},
	{37750,38249},
	{38250,38649},
	{38650,39649},
}; 

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorEarfcnList::ValidateU32Array(const std::vector<u32>& value, u32 minValue, u32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
{
   if(value.size() > maxInstances)
   {
      ostringstream description;
      description << "numInstances=" << value.size() << ", maxInstances=" << maxInstances;
      failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_TOO_MANY, description.str());
      return false;
   }

   for(u32 i = 0; i < value.size(); i++)
   {
      ostringstream description;
      bool isValid = ValidatorU32::ValidateU32(value.at(i), minValue, maxValue, failureDescriptor);
      u32 itValue = 0;
      if (isValid )
      {
         isValid = false;
         if (BandSupported.size() > 0)
         {
            for ( std::vector<u32>::const_iterator it = BandSupported.begin(); it != BandSupported.end(); ++it )
            {
               itValue = ( itValue < *it ) ? *it : itValue;
               if( (value.at(i) >= dlFreqList[itValue].minNDL) &&  (value.at(i) <= dlFreqList[itValue].maxNDL) )
               {
                  isValid = true;
                  break;
               }
            }
            if (false == isValid)
            {
               description << value.at(i) << " Not supported in LTE_BANDS_SUPPORTED";
               failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str()); 
               return false;
            }
         }
         else
         {
            isValid = true;
         }
      }
      else
      {
         description << value.at(i) << " not supported, supported Earfcn values are (" << 
            "0 to 39649 for LTE Band from 1 to 40)";
         failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
         return false;
      }
   }
   return true;
}

void ValidatorEarfcnList::SetLteBands(std::vector<u32> bandSupported)
{
	BandSupported.clear();
	for (u32 idx=0;idx<bandSupported.size();idx++)
	{	
		BandSupported.push_back(bandSupported[idx]);
	}
}
