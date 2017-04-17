///////////////////////////////////////////////////////////////////////////////
//
// KpiGroup.cpp
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
#include <iomanip>

#include <system/Trace.h>
#include <system/SerialisationUtils.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "KpiGroup.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

const KpiDefinition* KpiGroup::GetKpiDefinition(KpiId kpiId)
{
    ENTER();

    for(u32 i = 0; i < sizeof(kpiDefinitions)/sizeof(KpiDefinition); i++)
    {
        if(kpiDefinitions[i].kpiId == kpiId)
        {
            RETURN(&(kpiDefinitions[i]));
        }
    }

    RETURN(NULL);
}

const KpiGroupDefinition* KpiGroup::GetKpiGroupDefinition(KpiGroupId kpiGroupId)
{
    ENTER();

    for(u32 i = 0; i < sizeof(kpiGroupDefinitions)/sizeof(KpiGroupDefinition); i++)
    {
        if(kpiGroupDefinitions[i].kpiGroupId == kpiGroupId)
        {
            RETURN(&(kpiGroupDefinitions[i]));
        }
    }

    RETURN(NULL);
}

bool KpiGroup::GetKpiGroupId(KpiId kpiId, KpiGroupId& kpiGroupId)
{
    ENTER();

    for(u32 i = 0; i < sizeof(kpiDefinitions)/sizeof(KpiDefinition); i++)
    {
        if(kpiDefinitions[i].kpiId == kpiId)
        {
            kpiGroupId = kpiDefinitions[i].kpiGroupId;
            RETURN(true);
        }
    }

    RETURN(false);
}

const char * KpiGroup::GetKpiDescription(KpiId kpiId)
{
    ENTER();

    const KpiDefinition* kpiDef = GetKpiDefinition(kpiId);
    if(kpiDef != NULL)
    {
        RETURN(kpiDef->description);
    }

    RETURN(NULL);
}

const char * KpiGroup::GetKpiGroupDescription(KpiGroupId kpiGroupId)
{
    ENTER();

    const KpiGroupDefinition* kpiGroupDef = GetKpiGroupDefinition(kpiGroupId);
    if(kpiGroupDef != NULL)
    {
        RETURN(kpiGroupDef->description);
    }

    RETURN(NULL);
}

const char * KpiGroup::GetKpiGroupDescription(KpiId kpiId)
{
    ENTER();

    KpiGroupId kpiGroupId = INVALID_KPI_GROUP_ID;
    bool gotKpiGroupId = GetKpiGroupId(kpiId, kpiGroupId);
    RSYS_ASSERT(gotKpiGroupId);

    RETURN(GetKpiGroupDescription(kpiGroupId));
}

KpiGroup::KpiGroup() :
    m_groupDefinition(NULL),
    m_timestampUpdated(false)
{

}

KpiGroup::KpiGroup(KpiGroupId kpiGroupId) :
    m_groupDefinition(NULL),
    m_timestampUpdated(false)
{
    ENTER();

    m_groupDefinition = GetKpiGroupDefinition(kpiGroupId);
    RSYS_ASSERT_PRINTF(m_groupDefinition != NULL, "kpiGroupId=%" PRIu32 ".", (u32)kpiGroupId);

    EXIT();
}

KpiGroup::~KpiGroup()
{
    ENTER();
    EXIT();
}

s32 KpiGroup::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    // Preconditions.
    RSYS_ASSERT(m_groupDefinition != NULL);
    u32 numKpis = m_kpiCounts.size();
    RSYS_ASSERT(dataMaxBytes >= (4 + 4 + 1 + 4 + (numKpis * (4+4+4)))); // ID + timestamp + timestamp touched + num KPIs + Cell id kpi id/value pairs

    // Serialise all the members.
    u8* serialisedData = data;

    // Group ID.
    SerialiseIt((u32)(m_groupDefinition->kpiGroupId), serialisedData);

    // Timestamp and whether it has been touched since object creation.
    SerialiseIt((u32)(m_timestamp.GetUnixTime()), serialisedData);
    SerialiseIt(m_timestampUpdated, serialisedData);

    // Number of KPIs to follow.
    SerialiseIt(numKpis, serialisedData);

    KpiCounts::const_iterator iter = m_kpiCounts.begin();
    while(iter != m_kpiCounts.end())
    {
        SerialiseIt((u32)get<0>(iter->first), serialisedData); // KPI ID
        SerialiseIt((u32)get<1>(iter->first), serialisedData); // CELL ID
        
        const KpiDefinition * definition = GetKpiDefinition(get<0>(iter->first));
      if(definition != NULL && definition->kpiType  == KPI_TYPE_FLOAT_INC_BY_N)
        SerialiseIt((any_cast<float>)(iter->second), serialisedData); // KPI Value
      else
      {
        SerialiseIt((any_cast<u32>)(iter->second), serialisedData); // KPI Value
      }

        ++iter;
    }

    RETURN(serialisedData - data);
}

bool KpiGroup::DeSerialise(const u8* data, u32 dataLen)
{
   ENTER();

   // Clear out current members.
   m_groupDefinition = NULL;
   m_kpiCounts.clear();

   // Get the group ID and look up group definition.
   u32 kpiGroupIdU32;
   DeSerialiseIt(kpiGroupIdU32, data);
   m_groupDefinition = GetKpiGroupDefinition((KpiGroupId)kpiGroupIdU32);
   if(m_groupDefinition == NULL)
   {
      TRACE_PRINTF("Unknown kpiGroupId=%" PRIu32, kpiGroupIdU32);
      RETURN(false);
   }

   // Get timestamp and whether it has been touched since creation.
   u32 unixTime;
   DeSerialiseIt(unixTime, data);
   m_timestamp.Set(unixTime, 0);
   DeSerialiseIt(m_timestampUpdated, data);

   // Get number of KPIs to follow.
   u32 numKpis = m_kpiCounts.size();
   DeSerialiseIt(numKpis, data);
   u32 expectedDataLen = 4 + 4 + 1 + 4 + (/*numCells* */ numKpis * (4+4+4)); // ID + timestamp + timestamp touched + num KPIs + Cell Idkpi id/value pairs
   if(dataLen != expectedDataLen)
   {
      TRACE_PRINTF_LEV(TRACE_WARNING, "KpiGroup::DeSerialise(): groupId=%"PRIu32", invalid length (got %"PRIu32", expected %"PRIu32,
            kpiGroupIdU32, dataLen, expectedDataLen);
      RETURN(false);
   }
   // Pull out KPI values and populate our map.
   u32 kpiIdU32 = 0;
   u32 cellId=0;
   for(u32 i = 0; i < numKpis; i++)
   {
      DeSerialiseIt(kpiIdU32, data);
      DeSerialiseIt(cellId, data);

      const KpiDefinition * definition = GetKpiDefinition((KpiId)kpiIdU32);
      if(definition != NULL)
      {
         if(definition->kpiType  == KPI_TYPE_FLOAT_INC_BY_N)
         {
            float kpiValue;
            DeSerialiseIt(kpiValue, data);
            KpiId kpi_id=(KpiId)kpiIdU32;
            cellId=(u32)cellId;
            m_kpiCounts[boost::make_tuple(kpi_id,cellId)] = kpiValue;
         }
         else
         {
            u32  kpiValue;     
            DeSerialiseIt(kpiValue, data);
            m_kpiCounts[boost::make_tuple((KpiId)kpiIdU32,(u32)cellId)] = kpiValue;
         }
      }
   }

   RETURN(true);
}


void KpiGroup::IncKpiByIntVal(KpiId kpiId,u32 cellId, u32 increment)
{
    ENTER();

    // Preconditions.
    RSYS_ASSERT(m_groupDefinition != NULL);
    bool kpiIdValid = (ValidateKpiId(kpiId, KPI_TYPE_U32_INC_BY_N) || ValidateKpiId(kpiId, KPI_TYPE_U32_COUNT));
    RSYS_ASSERT_PRINTF(kpiIdValid, "IncKpiBy(): kpiGroupId=%s(%" PRIu32 "), kpiId=%s(%" PRIu32 ")", GetKpiGroupDescription(m_groupDefinition->kpiGroupId),
                                                                                    (u32)(m_groupDefinition->kpiGroupId),
                                                                                    GetKpiDescription(kpiId),
                                                                                    (u32)kpiId);
    u32 kpiVal=GetIntTypKpi(kpiId,cellId);
    if(kpiVal == 0)
    {
       m_kpiCounts[boost::make_tuple(kpiId,cellId)] = 0u;
    }

    m_kpiCounts[boost::make_tuple(kpiId,cellId)] = any_cast<u32>(m_kpiCounts[boost::make_tuple(kpiId,cellId)]) + increment;
 
    KpiCounts::const_iterator iter = m_kpiCounts.begin();
   EXIT();
}

void KpiGroup::IncKpiByRealVal(KpiId kpiId,u32 cellId, float increment)
{
    ENTER();

    // Preconditions.
    RSYS_ASSERT(m_groupDefinition != NULL);
    bool kpiIdValid = ValidateKpiId(kpiId, KPI_TYPE_FLOAT_INC_BY_N);
    RSYS_ASSERT_PRINTF(kpiIdValid, "IncKpiBy(): kpiGroupId=%s(%" PRIu32 "), kpiId=%s(%" PRIu32 ")", GetKpiGroupDescription(m_groupDefinition->kpiGroupId),
                                                                                    (u32)(m_groupDefinition->kpiGroupId),
                                                                                    GetKpiDescription(kpiId),
                                                                                    (u32)kpiId);
   float  kpiVal=GetRealTypKpi(kpiId,cellId);
    if(kpiVal == 0.0)
    {
     m_kpiCounts[boost::make_tuple(kpiId,cellId)] = 0.0f;
    }

    m_kpiCounts[boost::make_tuple(kpiId,cellId)] = any_cast<float>(m_kpiCounts[boost::make_tuple(kpiId,cellId)]) + increment;
    EXIT();
}

u32 KpiGroup::GetIntTypKpi(KpiId kpiId,u32 cellId) const
{
    ENTER();

    bool kpiIdValid = (ValidateKpiId(kpiId, KPI_TYPE_U32_COUNT) || ValidateKpiId(kpiId, KPI_TYPE_U32_INC_BY_N));
    RSYS_ASSERT_PRINTF(kpiIdValid, "GetIntTypKpi(): kpiGroupId=%" PRIu32 ", kpiId=%" PRIu32, (u32)(m_groupDefinition->kpiGroupId), (u32)kpiId);

    KpiCounts::const_iterator iter = m_kpiCounts.find(boost::make_tuple(kpiId,cellId));
    if(iter != m_kpiCounts.end())
    {
        RETURN(any_cast<u32>(iter->second));
    }

    RETURN(0);
}

float  KpiGroup::GetRealTypKpi(KpiId kpiId,u32 cellId) const
{
    ENTER();

    bool kpiIdValid = ValidateKpiId(kpiId, KPI_TYPE_FLOAT_INC_BY_N);
    RSYS_ASSERT_PRINTF(kpiIdValid, "GetRealTypKpi(): kpiGroupId=%" PRIu32 ", kpiId=%" PRIu32, (u32)(m_groupDefinition->kpiGroupId), (u32)kpiId);

    KpiCounts::const_iterator iter = m_kpiCounts.find(boost::make_tuple(kpiId,cellId));
    if(iter != m_kpiCounts.end())
    {
        RETURN(any_cast<float>(iter->second));
    }

    RETURN(0.0);
}

void KpiGroup::ResetKpis()
{
    ENTER();

    KpiCounts::iterator iter = m_kpiCounts.begin();
    while(iter != m_kpiCounts.end())
    {
        const KpiDefinition * definition = GetKpiDefinition(get<0>(iter->first));
      if(definition != NULL && definition->kpiType  == KPI_TYPE_FLOAT_INC_BY_N)
         iter->second = 0.0f;
      else
         iter->second = 0u;
        ++iter;
    }

    EXIT();
}

void KpiGroup::TouchTimestamp()
{
    ENTER();

    m_timestamp.Touch();
    m_timestampUpdated = true;

    EXIT();
}

void KpiGroup::TouchAndAlignTimeStampToUploadInterval(u32 uploadIntervalInSeconds)
{
    ENTER();

    m_timestamp.Touch();
    time_t nowInUnixTime = m_timestamp.GetUnixTime();
    time_t alignedUnixTime = (nowInUnixTime / uploadIntervalInSeconds) * uploadIntervalInSeconds;
    m_timestamp.Set(alignedUnixTime, 0);
    
    EXIT();
}

bool KpiGroup::GetTimestamp(TimeWrap& timestamp) const
{
    ENTER();

    timestamp = m_timestamp;

    RETURN(m_timestampUpdated);
}

KpiGroup& KpiGroup::operator+=(const KpiGroup& rhs)
{
    ENTER();

    RSYS_ASSERT(m_groupDefinition);
    RSYS_ASSERT(rhs.m_groupDefinition);
    RSYS_ASSERT_PRINTF(m_groupDefinition->kpiGroupId == rhs.m_groupDefinition->kpiGroupId, "KPI Group IDs must match when adding groups together!");

    KpiCounts::const_iterator rhsIter = rhs.m_kpiCounts.begin();
    while(rhsIter != rhs.m_kpiCounts.end())
    {
        KpiId rhsKpiId = get<0>(rhsIter->first);
        u32 cellId=get<1>(rhsIter->first);
        
        // Check if LHS has this KPI ID.
        KpiCounts::iterator iter = m_kpiCounts.find(boost::make_tuple(rhsKpiId,cellId));
        
         const KpiDefinition * definition = GetKpiDefinition(rhsKpiId);
        if(iter != m_kpiCounts.end())
        {
            // Yup, we already have it, so add them together.
            if(definition != NULL && definition->kpiType  == KPI_TYPE_FLOAT_INC_BY_N) 
            iter->second =  any_cast<float> (iter->second) + any_cast<float>(rhsIter->second);
            else
             iter->second =  any_cast<u32> (iter->second) + any_cast<u32> (rhsIter->second); 
        }
        else
        {
            // Nope, so just merge it in.
            m_kpiCounts[rhsKpiId] = rhsIter->second;
        }

        ++rhsIter;
    }

    RETURN(*this);
}

bool KpiGroup::operator==(const KpiGroup& rhs) const
{
   ENTER();

   if(m_kpiCounts.size() != rhs.m_kpiCounts.size())
   {
      RETURN(false);
   }

   KpiCounts::const_iterator iter = m_kpiCounts.begin();
   while(iter != m_kpiCounts.end())
   {
      KpiId kpiId = get<0>(iter->first);

      float kpiValue = 0;
      u32   kpiVal = 0;
      const KpiDefinition * definition = GetKpiDefinition(kpiId);
      if(definition != NULL && definition->kpiType  == KPI_TYPE_FLOAT_INC_BY_N)
      {
         kpiValue = any_cast<float>(iter->second);
      }
      else
      {
         kpiVal = any_cast<u32>(iter->second);
      } 

      // Check if RHS has this KPI ID.
      KpiCounts::const_iterator rhsIter = rhs.m_kpiCounts.find(kpiId);
      if(rhsIter == rhs.m_kpiCounts.end())
      {
         RETURN(false);
      }
      // Check value is the same.

      const KpiDefinition * definition1 = GetKpiDefinition(get<0>(rhsIter->first));
      if(definition1 != NULL && definition1->kpiType  == KPI_TYPE_FLOAT_INC_BY_N)
      {
         if(kpiValue != any_cast<float>(rhsIter->second))
         {
            RETURN(false);
         }       
      }
      else
      {
         if(kpiVal != any_cast<u32>(rhsIter->second))
         {
            RETURN(false);
         }
      } 
      ++iter;
   }

   RETURN((m_groupDefinition == rhs.m_groupDefinition) &&
         (m_timestamp.GetUnixTime() == rhs.m_timestamp.GetUnixTime()) &&
         (m_timestampUpdated == rhs.m_timestampUpdated))
}

std::string KpiGroup::ToString() const
{
    ENTER();

    // Preconditions.
    RSYS_ASSERT(m_groupDefinition != NULL);

    ostringstream stream;

    stream << setiosflags(ios::left) << setw(25) << m_groupDefinition->description << ": ";

    const KpiDefinition * definition;
    KpiCounts::const_iterator iter = m_kpiCounts.begin();
    while(iter != m_kpiCounts.end())
    {
        KpiId kpiId = (KpiId)get<0>(iter->first);
        u32 cellId=(u32)get<1>(iter->first);
        definition = GetKpiDefinition(kpiId);

        if(definition != NULL && definition->kpiType  == KPI_TYPE_FLOAT_INC_BY_N)
         { 
        stream << "[" << (definition != NULL ? definition->description : "")
               << "=" << (any_cast<float>)(iter->second) ;
         }
        else
        {
        stream << "[" << (definition != NULL ? definition->description : "")
               << "=" << (any_cast<u32>)(iter->second) ;
        }
        stream<<" cellid :"<<cellId<<" ]" ;
        ++iter;
    }

    stream << m_timestamp.ToString();

    if(m_timestampUpdated)
    {
        stream << "(touched)";
    }
    else
    {
        stream << "(created)";
    }

    RETURN(stream.str());
}

bool KpiGroup::ValidateKpiId(KpiId kpiId, KpiType kpiType) const
{
    ENTER();

    // Preconditions.
    RSYS_ASSERT(m_groupDefinition != NULL);

    const KpiDefinition * definition = GetKpiDefinition(kpiId);
    if(definition != NULL)
    {
        if((definition->kpiGroupId == m_groupDefinition->kpiGroupId) &&
           (definition->kpiType == kpiType))
        {
            RETURN(true);
        }
    }

    RETURN(false);
}
