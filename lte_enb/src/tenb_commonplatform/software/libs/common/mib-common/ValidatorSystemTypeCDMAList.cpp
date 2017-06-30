#include <sstream>
#include <system/Trace.h>

#include"ValidatorSystemTypeCDMAList.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////


ValidatorSystemTypeCDMAList::ValidatorSystemTypeCDMAList()
{
}
ValidatorSystemTypeCDMAList::~ValidatorSystemTypeCDMAList()
{
}

bool ValidatorSystemTypeCDMAList::ValidateU32Array(const std::vector<u32>& value, u32 minValue, u32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor)
{
   for(u32 i = 0; i < value.size(); i++)
   {
      if(!m_validator.ValidateU32(value.at(i), minValue, TWO, failureDescriptor))
      {
         ostringstream description;
         description << "NotValidValue at Element " << i << ": " << "Valid values are 0,1 and 2"; 
         failureDescriptor.Set(failureDescriptor.GetCause(), description.str());
         return false;
      }
   }

   return true;
}
