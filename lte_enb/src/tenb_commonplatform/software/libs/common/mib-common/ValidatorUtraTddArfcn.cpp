///////////////////////////////////////////////////////////////////////////////
//
// ValidatorUtraTddArfcn.cpp 
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
#include <stdlib.h>
#include <system/Trace.h>
#include <string.h>
#include <iostream>
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "mib-common/ValidationReferences.h"
#include "ValidatorUtraTddArfcn.h"

using namespace std;

#if 0
struct UtraDlFreq
{
	u32 minNDL;
	u32 maxNDL;   
	u32 size;
};

struct UtraDlFreq tddFreqList[7] = { {0,0}, //invalid
	{9512,9588},    /* band-indicator 1 */
	{10062,10113},  /* band-indicator 2 */
	{9262,9538},    /* band-indicator 3 */
	{9662,9938},    /* band-indicator 4 */
	{9562,9638},    /* band-indicator 5 */
	{12862,13088},  /* band-indicator 6 */
};
#endif

u16 UTRATDD384_band_ab[2][4]={{9512,9588,10062,10113},
                                 {9262,9538,9662,9938}
};

u16 UTRATDD384_band_cd[2][2]={
      {9562,9638},
         {12862,13088}
};

u16 UTRATDD128_band_ab[2][4]={
      {9504,9596,10054,10121},
         {9254,9546,9654,9946}
};

u16 UTRATDD128_band_cdef[4][2]={
      {9554,9646},
         {12854,13096},
            {11504,11996},
               {9404,9596}
};

u16 UTRATDD768_band_ab[2][4]={
      {9512,9588,10062,10113},
         {9262,9538,9662,9938}
};

u16 UTRATDD768_band_cd[2][2]={
      {9562,9638},
         {12874,13076}
};


///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool ValidatorUtraTddArfcn::ValidateU32(MibDN fapLteDn, u32 value, u32 min, u32 max, ValidationFailureDescriptor& failureDescriptor)
{
   ValidationReferences::GetInstance().getParameterValue(PARAM_ID_LTE_TDS_CDMA_UTRATDD_MODE,tddMode,fapLteDn);
   ValidationReferences::GetInstance().getParameterValue(PARAM_ID_LTE_TDS_CDMA_UTRATDD_BAND_INDICATOR,bandIndicator,fapLteDn);

   bool isValid = ValidatorU32::ValidateU32(value, min, max, failureDescriptor);

   if (isValid)
   {
      isValid = false;

      if(tddMode == "UTRA_TDD_128")
      {
         if (bandIndicator ==1 || bandIndicator ==2)
         {
            if((value >= UTRATDD128_band_ab[bandIndicator-1][0] &&
                     value <= UTRATDD128_band_ab[bandIndicator-1][1]) ||
                  (value >= UTRATDD128_band_ab[bandIndicator-1][2] &&
                   value <= UTRATDD128_band_ab[bandIndicator-1][3]))
            {
               return true;
            }
         }
         else if (bandIndicator >= 3 && bandIndicator <= 6)
         {
            if((value >= UTRATDD128_band_cdef[bandIndicator-3][0] &&
                     value <= UTRATDD128_band_cdef[bandIndicator-3][1]))
            {
               return true;
            }
         }
         else
         {
            isValid = false;
         }
      }
      else if(tddMode == "UTRA_TDD_384")
      {
         if (bandIndicator == 1 || bandIndicator == 2)
         {
            if((value >= UTRATDD384_band_ab[bandIndicator-1][0] &&
                     value <= UTRATDD384_band_ab[bandIndicator-1][1]) ||
                  (value >= UTRATDD384_band_ab[bandIndicator-1][2] &&
                   value <= UTRATDD384_band_ab[bandIndicator-1][3]))
            {
               return true;
            }
         }
         else if (bandIndicator == 3 || bandIndicator == 4)
         {
            if((value >= UTRATDD384_band_cd[bandIndicator-3][0] &&
                     value <= UTRATDD384_band_cd[bandIndicator-3][1]))
            {
               return true;
            }
         }
         else
         {
            isValid = false;
         }
      }
      else if(tddMode == "UTRA_TDD_768")
      {
         if (bandIndicator ==1 || bandIndicator ==2)
         {
            if((value >= UTRATDD768_band_ab[bandIndicator-1][0] &&
                     value <= UTRATDD768_band_ab[bandIndicator-1][1]) ||
                  (value >= UTRATDD768_band_ab[bandIndicator-1][2] &&
                   value <= UTRATDD768_band_ab[bandIndicator-1][3]))
            {
               return true;
            }
         }
         else if (bandIndicator == 3 || bandIndicator == 4)
         {
            if((value >= UTRATDD768_band_cd[bandIndicator-3][0] &&
                     value <= UTRATDD768_band_cd[bandIndicator-3][1]))
            {
               return true;
            }
         }
         else
         {
            isValid = false;
         }
      }
   }
   if (false == isValid)
   {
      ostringstream description;
      description << "LTE_TDS_CDMA_UTRA_ARFCN value (" << value << ") is not allowed when LTE_TDS_CDMA_UTRATDD_MODE value (" << tddMode << ") and bandIndicator value (" << bandIndicator <<")";
      failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, description.str()); 
   }
	RETURN(isValid);
}
