///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyTypes.c 28519 2010-07-21 14:39:46Z mmcternan $
//
// CPHY message types helper functions.
//
// Copyright radisys Ltd
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CPhyTypes.h"

///////////////////////////////////////////////////////////////////////////////
// Message Constants
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Message Structures
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////


const char *CphyL1StatusToString(l1status_t status)
{
    switch(status)
    {
        case L1_SOK:              return "L1_SOK";
        case L1_SFAILED:          return "L1_SFAILED";
        case L1_SNOT_IMPLEMENTED: return "L1_SNOT_IMPLEMENTED";
        case L1_SNOT_SUPPORTED:   return "L1_SNOT_SUPPORTED";
        case L1_SNOT_READY:       return "L1_SNOT_READY";
        case L1_SBUSY:            return "L1_SBUSY";
        case L1_SBAD_BUFFER:      return "L1_SBAD_BUFFER";
        case L1_SBAD_PARAM:       return "L1_SBAD_PARAM";
        case L1_SBAD_STATE:       return "L1_SBAD_STATE";
        case L1_SNO_MEM:          return "L1_SNO_MEM";
        case L1_SNOT_FOUND:       return "L1_SNOT_FOUND";

        default:                  return "<unknown l1status_t>";
    }
}


const char *CphyL1ModeToString(l1mode_t mode)
{
    switch(mode)
    {
        case L1_MODE_NULL:        return "L1_MODE_NULL";
        case L1_MODE_NODEB:       return "L1_MODE_NODEB";
        case L1_MODE_REM_WCDMA:   return "L1_MODE_REM_WCDMA";
        case L1_MODE_REM_GSM:     return "L1_MODE_REM_GSM";

        default:                  return "<unknown l1mode_t>";
    }
}


const char *CphySpreadingFactorToString(spreading_factor_t sf)
{
    switch(sf)
    {
      case SF_256:      return "SF_256";
      case SF_128:      return "SF_128";
      case SF_64:       return "SF_64";
      case SF_32:       return "SF_32";
      case SF_16:       return "SF_16";
      case SF_8:        return "SF_8";
      case SF_4:        return "SF_4";
      case SF_4x2:      return "SF_4x2";
      case SF_2x2:      return "SF_2x2";
      case SF_2x2_4x2:  return "SF_2x2_4x2";

      default:          return "<unknown spreading_factor_t>";
    }
}


const char *CphyBandToString(band_t band)
{
    switch(band)
    {
        case BAND_INVALID:       return "BAND_INVALID";
        case BAND_GSM900:        return "GSM900";
        case BAND_RGSM900:       return "RGSM900";
        case BAND_DCS1800:       return "DCS1800";
        case BAND_PCS1900:       return "PCS1900";
        case BAND_GSM450:        return "GSM450";
        case BAND_GSM480:        return "GSM480";
        case BAND_GSM850:        return "GSM850";

        default:                 return "<unknown band_t>";
    }
}


void CphyPrintArrayU16(FILE *out, const char *name, const uint16_t *array, uint8_t n)
{
    uint16_t t;

    fprintf(out, "%s{", name);
    for(t = 0; t < n; t++)
    {
        fprintf(out, "%5u%c", array[t], t + 1 < n ? ',' : ' ');
    }
    fprintf(out, "}");
}


void CphyPrintArrayS16(FILE *out, const char *name, const int16_t *array, uint8_t n)
{
    uint16_t t;

    fprintf(out, "%s{", name);
    for(t = 0; t < n; t++)
    {
        fprintf(out, "%5d%c", array[t], t + 1 < n ? ',' : ' ');
    }
    fprintf(out, "}");
}


///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////


