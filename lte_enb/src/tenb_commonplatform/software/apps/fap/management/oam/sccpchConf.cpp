///////////////////////////////////////////////////////////////////////////////
//
// sccpchConf.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "sccpchConf.h"

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////
namespace threeway
{
const u8 SCCPCH_SPREADING_CODE = 1;
const spreading_factor_t SCCPCH_SPREADING_FACTOR = SF_64;
const bool SCCPCH_DTX_FIXED = false;
const u8 SCCPCH_SLOT_FORMAT = 8;
const u8 SCCPCH_TTI[SCCPCH_NTRCH] = {10, 10, 10};
const coding_scheme_t SCCPCH_CODING[SCCPCH_NTRCH] = {CS_C2, CS_C2, CS_T3};
const crc_length_t SCCPCH_CRC[SCCPCH_NTRCH] = {CRC_16, CRC_16, CRC_16};
const u8 SCCPCH_RM_ATTR[SCCPCH_NTRCH] = {230, 220, 130};
}
