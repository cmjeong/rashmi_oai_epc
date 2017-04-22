       //////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////
	//
	// ValidatorEmptyChkU32Array.cpp
	//
	// See header file for documentation.
	//
	// Copyright Radisys Limited
	//
	// //////////////////////////////////////////////////////////////////////////
	// /////////////////////////////////////////////////////////////////////////
	 
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	// System Incudes
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	 
	#include <sstream>
	#include <system/Trace.h>
	#include <set>
	#include <vector>
	 
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	// Local Include
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	 
	#include"ValidatorEmptyChkU32Array.h"
	 
	 
	using namespace std;
	 
	///////////////////////////////////////////////////////////////////////////////
	// Class Functions
	///////////////////////////////////////////////////////////////////////////////
	 
	 
	ValidatorEmptyChkU32Array::ValidatorEmptyChkU32Array()
	{
	}
	ValidatorEmptyChkU32Array::~ValidatorEmptyChkU32Array()
	{
	}
	 
	bool ValidatorEmptyChkU32Array::ValidateU32Array(const std::vector<u32>& value, u32 minValue, u32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
	{
	   ostringstream description;
	 
	   if(value.size() == 0 )
	   {
	      description << "numInstances="<< value.size() << " , minimum 1 value required"<< endl;
	      failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_BELOW_MINIMUM, description.str());
	      return false;
	   }
	   if(value.size() > maxInstances)
	   {  
	      description << "numInstances="<< value.size() << ",maxInstances=" << maxInstances << endl;
	      failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_TOO_MANY, description.str());
	      return false;
	   }
	 
	   for(u32 i = 0; i < value.size(); i++)
	   {
	      bool isValid = ValidatorU32::ValidateU32(value.at(i), minValue, maxValue, failureDescriptor);
	 
	      if (!isValid)
	      {
	   
	         description << "Value ="<< value.at(i) << ", should be with in the range =" << minValue <<" - "  <<maxValue << endl;
	         failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_TOO_MANY, description.str());
	         return false;
	      }
	 
	   }  
	 
	   return true;
	 
	}
