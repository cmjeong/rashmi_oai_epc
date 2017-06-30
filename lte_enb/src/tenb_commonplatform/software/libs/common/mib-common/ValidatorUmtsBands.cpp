///////////////////////////////////////////////////////////////////////////////
//
// ValidatorUmtsBands.cpp
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
#include <algorithm>
#include <stdlib.h>
#include <system/Trace.h>
#include <mobnet/UmtsBandId.h>
#include<cstring>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorUmtsBands.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

ValidatorUmtsBands::ValidatorUmtsBands()
{
   stringstream allBands;

   for( int i = int(UBAND_FIRST); i < int(UBAND_LAST); i++)
   {
      allBands << UmtsBandIdToString( UmtsBandId(i) ) << "|";
   }

   allBands << UmtsBandIdToString( UmtsBandId(UBAND_LAST) );

   // Initially, set "all bands supported",
   // until OAM correctly configures the validator
   // dependent upon hardware config.
   m_umtsBandsRegex.reset( new threeway::Regex( allBands.str() ) );
}

bool ValidatorUmtsBands::ValidateStringArray(const std::vector<std::string>& value, u32 minLength, u32 maxLength, s32 minValue, s32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
{
   if(!ValidatorStringArray::ValidateStringArray(value, minLength, maxLength, minValue, maxValue, maxInstances, failureDescriptor))
   {
      return false;
   }

   for(u32 i = 0; i < value.size(); i++)
   {
      if(m_umtsBandsRegex)
      {
         bool valid=false;
         char Band[10];
         strcpy(Band,value.at(i).c_str());

         for( int j = int(UBAND_FIRST); j < int(UBAND_LAST); j++)
         {
            if(strcmp(Band, UmtsBandIdToString( UmtsBandId(j) ) )==0)
            {
               valid=true;
            }
         }
         if(strcmp(Band,  UmtsBandIdToString( UmtsBandId(UBAND_LAST) )) ==0)
         {
            valid=true;
         }
         if(!valid)
         {  
            ostringstream description;
            description << "Element " << i << ": " << value.at(i) << " invalid. (" << m_umtsBandsRegex->ToString() << ")";
            failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
            return false;
         }
      }
      else
      {
         ostringstream description;
         description << "Element " << i << ": " << value.at(i) << " invalid. ()";
         failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str());
         return false;
      }
   }

   return true;
}

void ValidatorUmtsBands::SetBandsSupported(const UmtsBands & bandsSupported)
{
   stringstream regularExpression;

   regularExpression << ERE_START;

   for( UmtsBandIds::const_iterator i = bandsSupported.Get().begin();
         i != bandsSupported.Get().end();
         i++ )
   {
      if(i != bandsSupported.Get().begin())
      {
         regularExpression << "|";
      }

      regularExpression << UmtsBandIdToString(*i);
   }

   regularExpression << ERE_END;

   //m_umtsBandsRegex.reset( new threeway::Regex( regularExpression.str() ) );
}
