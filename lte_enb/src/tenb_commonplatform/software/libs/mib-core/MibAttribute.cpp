///////////////////////////////////////////////////////////////////////////////
//
// MibAttribute.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <sstream>

#include <system/Trace.h>
#include<mib-common/ValidationReferences.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibAttribute.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool MibAttribute::ValidateValue(MibDN Dn, MibAttributeId id, shared_ptr<MibAttributeValue> value, MibAttrValidationFailure& failureDescriptor)
{
   ENTER();

   bool SetValidatorForReference = false;
   ValidationReferences validationReferences;

   MibAttributeId m_parListTobeSetInValidator[] = {
      PARAM_ID_BANDS_SUPPORTED,
      PARAM_ID_LTE_NRBCQI,
      PARAM_ID_LTE_N1PUCCHAN,
      PARAM_ID_LTE_TDD_SPECIAL_SUB_FRAME_PATTERNS,
      PARAM_ID_LTE_INTRA_HO_A3_OFFSET,
      PARAM_ID_DUPLEX_MODE,
      PARAM_ID_LTE_INTRA_ANR_A3_OFFSET,
      PARAM_ID_LTE_INTER_A5_THRESHOLD_1_RSRP,
      PARAM_ID_LTE_INTER_A5_THRESHOLD_2_RSRP,
      PARAM_ID_LTE_DL_BANDWIDTH,
      PARAM_ID_LTE_INTER_ANR_A5_THRESHOLD_1_RSRP,
      PARAM_ID_LTE_INTER_ANR_A5_THRESHOLD_2_RSRP,
      PARAM_ID_LTE_DRX_QCI_ENABLE,
      PARAM_ID_LTE_DRX_ENABLE,
      PARAM_ID_LTE_ANR_REPORT_CFG_VAL,
      PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_RNCID, 
      PARAM_ID_LTE_TDD_SPECIAL_SUB_FRAME_PATTERNS,
      PARAM_ID_LTE_CDMA2K_ECSFB_REPORT_CFG_VAL,
      PARAM_ID_LTE_IS_DUAL_RXTX_ALLOWED,
      PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A11_FOR_MOSIG,
      PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A12_FOR_MOSIG,
      PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A13_FOR_MOSIG,
      PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A14_FOR_MOSIG,
      PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A15_FOR_MOSIG,
      PARAM_ID_LTE_X_RADISYS_AC_BARRING_FACTOR_FOR_MOSIG,
      PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A11_FOR_MODATA,
      PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A12_FOR_MODATA,
      PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A13_FOR_MODATA,
      PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A14_FOR_MODATA,
      PARAM_ID_LTE_X_RADISYS_AC_BARRING_SP_A15_FOR_MODATA,
      PARAM_ID_LTE_X_RADISYS_AC_BARRING_FACTOR_FOR_MODATA,
      PARAM_ID_LTE_TDS_CDMA_UTRATDD_MODE,
      PARAM_ID_LTE_TDS_CDMA_UTRATDD_BAND_INDICATOR,
      PARAM_ID_LTE_GERAN_T304_EXP_WAIT_TMR,
      PARAM_ID_LTE_T304IRAT,
      PARAM_ID_LTE_X_RADISYS_CA_ENABLE,
      PARAM_ID_LTE_X_RADISYS_NUM_OF_CELLS
   };

   MibAttributeId m_parListEmptyStringAllowed[] = 
   {
      PARAM_ID_LTE_REM_SCAN_PLMN_LIST,
      PARAM_ID_LTE_REM_SCAN_BAND_LIST,
      PARAM_ID_LTE_REM_SCAN_ARFCN_LIST
   };
   for(u32 i = 0; i < sizeof(m_parListTobeSetInValidator)/sizeof(m_parListTobeSetInValidator[0]); i++)
   {
      if(m_parListTobeSetInValidator[i]==id)
      {
         SetValidatorForReference=true;
      }
   }
   if(value == NULL)
   {
      string description = getMibAttributeName(id);
      description += ": Value is NULL.  May have been due to earlier malformed/invalid value e.g. a negative U32";
      failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_INVALID, description);
      failureDescriptor.SetMibAttributeId(id);
      RETURN(false);
   }

   MibAttributeType vType = value->GetType();
   MibAttributeType aType = getMibAttributeType(id);

   bool typesCompatible =
      ( aType == vType)
      || ((aType == MIB_ATTRIBUTE_TYPE_ENUM)      && (vType == MIB_ATTRIBUTE_TYPE_U32))
      || ((aType == MIB_ATTRIBUTE_TYPE_ENUMARRAY) && (vType == MIB_ATTRIBUTE_TYPE_U32ARRAY));

   if( !typesCompatible )
   {
      string description = getMibAttributeName(id);
      description += ": Value is of wrong type.  Is ";
      description += getMibAttributeTypeName(value->GetType());
      description += ", expected ";
      description += getMibAttributeTypeName(getMibAttributeType(id));
      failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_INVALID, description);
      failureDescriptor.SetMibAttributeId(id);
      RETURN(false);
   }

   bool descriptorFound = false;

   switch(value->GetType())
   {
      case MIB_ATTRIBUTE_TYPE_ENUM:
      case MIB_ATTRIBUTE_TYPE_U32:
         {
            const MibAttributeU32Descriptor* descriptor = getMibAttributeU32Descriptor(id);
            if(descriptor != NULL)
            {
               RSYS_ASSERT(descriptor->validator);

               descriptorFound = true;
               if(descriptor->validator->ValidateU32(Dn,value->GetValueU32(), descriptor->minValue, descriptor->maxValue, failureDescriptor))
               {
                  if(SetValidatorForReference )
                  {
                     validationReferences.setParameterValue(id,value,Dn);

                  }
                  RETURN(true);
               }
            }
         }
         break;

      case MIB_ATTRIBUTE_TYPE_ENUMARRAY:
      case MIB_ATTRIBUTE_TYPE_U32ARRAY:
         {
            const MibAttributeU32ArrayDescriptor* descriptor = getMibAttributeU32ArrayDescriptor(id);
            if(descriptor != NULL)
            {
               RSYS_ASSERT(descriptor->validator);

               descriptorFound = true;
               if(descriptor->validator->ValidateU32Array(Dn,value->GetValueU32Array(), descriptor->minValue, descriptor->maxValue, descriptor->maxInstances, failureDescriptor))
               {
                  if(SetValidatorForReference )
                  {
                     validationReferences.setParameterValue(id,value,Dn);
                  }

                  RETURN(true);
               }
            }
         }
         break;

      case MIB_ATTRIBUTE_TYPE_S32:
         {
            const MibAttributeS32Descriptor* descriptor = getMibAttributeS32Descriptor(id);
            if(descriptor != NULL)
            {
               RSYS_ASSERT(descriptor->validator);

               descriptorFound = true;
               if(descriptor->validator->ValidateS32(Dn,value->GetValueS32(), descriptor->minValue, descriptor->maxValue, failureDescriptor))
               {
                  if(SetValidatorForReference )
                  {
                     validationReferences.setParameterValue(id,value,Dn);
                  }

                  RETURN(true);
               }
            }
         }
         break;

      case MIB_ATTRIBUTE_TYPE_S32ARRAY:
         {
            const MibAttributeS32ArrayDescriptor* descriptor = getMibAttributeS32ArrayDescriptor(id);
            if(descriptor != NULL)
            {
               RSYS_ASSERT(descriptor->validator);

               descriptorFound = true;
               if(descriptor->validator->ValidateS32Array(Dn,value->GetValueS32Array(), descriptor->minValue, descriptor->maxValue, descriptor->maxInstances, failureDescriptor))
               {
                  if(SetValidatorForReference )
                  {
                     validationReferences.setParameterValue(id,value,Dn);
                  }

                  RETURN(true);
               }
            }
         }
         break;

      case MIB_ATTRIBUTE_TYPE_STRING:
         {
            const MibAttributeStringDescriptor* descriptor = getMibAttributeStringDescriptor(id);
            if(descriptor != NULL)
            {
               RSYS_ASSERT(descriptor->validator);

               descriptorFound = true;
               if(descriptor->validator->ValidateString(Dn,value->GetValueString(), descriptor->minLength, descriptor->maxLength, failureDescriptor))
               {
                  if(SetValidatorForReference )
                  {
                     validationReferences.setParameterValue(id,value,Dn);
                  }

                  RETURN(true);
               }
            }
         }
         break;

      case MIB_ATTRIBUTE_TYPE_STRINGARRAY:
         {
            std::vector<std::string> str = value->GetValueStringArray();
            u32 size = sizeof(m_parListEmptyStringAllowed)/sizeof(m_parListEmptyStringAllowed[0]);
            for(u32 i =0 ;(str.size() == 0)&&(i < size); i++)
            {
               if(m_parListEmptyStringAllowed[i] == id)
               {
                  return true;
               }
            }
            const MibAttributeStringArrayDescriptor* descriptor = getMibAttributeStringArrayDescriptor(id);
            if(descriptor != NULL)
            {
               RSYS_ASSERT(descriptor->validator);

               descriptorFound = true;
               std::vector<std::string> str = value->GetValueStringArray();
               if(str.size())
               {
                  if(descriptor->validator->ValidateStringArray(Dn,value->GetValueStringArray(), descriptor->minLength, descriptor->maxLength, descriptor->minValue, descriptor->maxValue, descriptor->maxInstances, failureDescriptor))
                  {
                     if(SetValidatorForReference )
                     {
                        validationReferences.setParameterValue(id,value,Dn);
                     }
                     RETURN(true);
                  }
               }
               else
               {
                  string desc = getMibAttributeName(id);
                  failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE, desc);
                  failureDescriptor.SetMibAttributeId(id);
                  RETURN(false);
               }
            } // if descriptor NULL
         } // end case STRINGARRAY
         break;
   }

   if(!descriptorFound)
   {
      string desc = getMibAttributeName(id);
      failureDescriptor.Set(ValidationFailureDescriptor::CAUSE_ATTRIBUTE_ID_NOT_FOUND, desc);
      failureDescriptor.SetMibAttributeId(id);
      RETURN(false);
   }

   failureDescriptor.SetMibAttributeId(id);
   RETURN(false);
}

MibAttribute::MibAttribute(MibAttributeId mibAttributeId, shared_ptr<MibAttributeValue> attributeValue) :
    m_mibAttributeId(mibAttributeId),
    m_value(attributeValue)
{
    ENTER();

    EXIT();
}

MibAttribute::~MibAttribute()
{
    ENTER();

    EXIT();
}

void MibAttribute::PopulateWithValue(MibAttributeValues& mibAttributeValues) const
{
    ENTER();

    mibAttributeValues.AddAttribute(m_mibAttributeId, m_value);

    EXIT();
}

bool MibAttribute::IsValueEqual(const MibAttribute& rhs) const
{
    ENTER();

    if(getMibAttributeType(m_mibAttributeId) != getMibAttributeType(rhs.GetMibAttributeId()))
    {
        return false;
    }

    RETURN(m_value->IsValueEqual(*rhs.GetValue()));
}

string MibAttribute::ToString() const
{
    ENTER();

    ostringstream stream;

    const char * idAsString = getMibAttributeName(m_mibAttributeId);
    RSYS_ASSERT(idAsString != NULL);

    stream << idAsString << "=" << m_value->ToString();

    RETURN(stream.str());
}
