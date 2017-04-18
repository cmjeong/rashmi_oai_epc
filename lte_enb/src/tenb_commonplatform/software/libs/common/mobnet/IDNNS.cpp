
///////////////////////////////////////////////////////////////////////////////
//
// IDNNS.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "IDNNS.h"

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

namespace rsysmob
{


const char * IDNNSChoiceToString(RadisysUeIdType choice)
{
	switch(choice)
	{
		case rsysmob::UE_ID_LOCAL_PTMSI: return "UE_ID_LOCAL_PTMSI"; break;
		case rsysmob::UE_ID_TMSI_OF_SAME_PLMN: return "UE_ID_TMSI_OF_SAME_PLMN"; break;
		case rsysmob::UE_ID_TMSI_OF_DIFFERENT_PLMN: return "UE_ID_TMSI_OF_DIFFERENT_PLMN"; break;
		case rsysmob::UE_ID_IMSI_RESPONSE_TO_PAGING: return "UE_ID_IMSI_RESPONSE_TO_PAGING"; break;
		case rsysmob::UE_ID_IMSI_CAUSE_UE_INITIATED: return "UE_ID_IMSI_CAUSE_UE_INITIATED"; break;
		case rsysmob::UE_ID_IMEI: return "UE_ID_IMEI"; break;
	}

	return "IDNNSChoice???";
}

std::string IDNNSToString(const RadisysIntraDomainNASNodeSelector& nodeSelector)
{
	std::ostringstream stream;

	stream << ", IDNNS Choice=" << IDNNSChoiceToString(nodeSelector.m_choice);	
	// Cast done to u16 below, otherwise with unsigned char(u8) it is interpreted as ASCII character 
   	stream << ", Length=" << (u16)nodeSelector.m_length;
	u16 rouParam = 0;
	memcpy(&rouParam, &nodeSelector.m_routingParameter, sizeof(rouParam));
	stream << ", Value=" << rouParam;

	return(stream.str());
}

}

