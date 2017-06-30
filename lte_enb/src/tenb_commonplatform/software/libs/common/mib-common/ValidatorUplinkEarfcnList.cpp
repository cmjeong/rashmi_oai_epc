///////////////////////////////////////////////////////////////////////////////
//
// ValidatorUplinkEarfcnList.cpp 
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

#include "ValidatorUplinkEarfcnList.h"

using namespace std;

struct UplinkFreq
{
	u32 minNUL;
	u32 maxNUL;   
};
struct UplinkFreq uplinkFreqList[41] = { {0,0}, //invalid
	{18000,18599},
	{18600,19199},
	{19200,19949},
	{19950,20399},
	{20400,20649},
	{20650,20749},
	{20750,21449},
	{21450,21799},
	{21800,22149},
	{22150,22749},
	{22750,22949},
	{23010,23179},
	{23180,23279},
	{23280,23379},
	{0,0},
	{0,0},
	{23730,23849},
	{23850,23999},
	{24000,24149},
	{24150,24449},
	{24450,24599},
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

bool ValidatorUplinkEarfcnList::ValidateU32Array(const std::vector<u32>& value, u32 minValue, u32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
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
				if( (value.at(i) >= uplinkFreqList[itValue].minNUL) &&  (value.at(i) <= uplinkFreqList[itValue].maxNUL) )
				{
					isValid = true;
					break;
				}
			}
			if (false == isValid)
			{

				description << "Uplink Earfcn value (" << value.at(i) << ") Not supported in LTE_BANDS_SUPPORTED"; 
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
		description << " supported Uplink Earfcn values are (" << 
			"0 to 39649 for LTE Band from 1 to 40)";
		failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
                return false;
	}
   }
   return true;
}

void ValidatorUplinkEarfcnList::SetLteBands(std::vector<u32> bandSupported)
{
	BandSupported.clear();
	for (u32 idx=0;idx<bandSupported.size();idx++)
	{	
		BandSupported.push_back(bandSupported[idx]);
	}
}
