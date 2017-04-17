///////////////////////////////////////////////////////////////////////////////
//
// IDNNS.h
//
// Type definitions for IDNNS
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __IDNNS_h_
#define __IDNNS_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////
#include <Radisys.h>
#include <string>
#include <sstream>

namespace rsysmob
{
	
typedef enum
{
    UE_ID_LOCAL_PTMSI,
    UE_ID_TMSI_OF_SAME_PLMN,
    UE_ID_TMSI_OF_DIFFERENT_PLMN,
    UE_ID_IMSI_RESPONSE_TO_PAGING,
    UE_ID_IMSI_CAUSE_UE_INITIATED,
    UE_ID_IMEI
} RadisysUeIdType;


typedef struct
{
    // R99 - GSM-MAP - Routing Basis
    RadisysUeIdType m_choice;
	u8 m_routingParameter[2];
	u8 m_length;
} RadisysIntraDomainNASNodeSelector;


const char * IDNNSChoiceToString(RadisysUeIdType choice);
std::string IDNNSToString(const RadisysIntraDomainNASNodeSelector& nodeSelector);

}

#endif
