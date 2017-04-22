///////////////////////////////////////////////////////////////////////////////
//
// FrequencyBandsSupported.cpp
//
// Derive UMTS and GSM bands supported by Hadrware
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <system/Trace.h>
#include <system/StringUtils.h>
#include <system/FrequencyBandsSupported.h>
#include <system/FapHardwareConfig.h>

#include <system/FrequencyConversions.h>


///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////



FrequencyBandsSupported::FrequencyBandsSupported(u32 hardwareType, u32 hardwareRevision) :
    m_umtsBands(false),
    m_remUmtsBands(false),
    m_rxOnlyUmtsBands(false),
    m_remGsmBands(false)
{
    switch(hardwareType)
    {
        case HARDWARE_TYPE_TYPE5:

            switch(hardwareRevision)
            {
                case HARDWARE_REVISION_TYPE5REV0_2100_RF:
                case HARDWARE_REVISION_TYPE5REV1_2100_RF:
                    m_umtsBands.Insert(UBAND_I_2100);
                    m_remGsmBands.Insert(GSM_BAND_ID_P_GSM900);
                    m_remGsmBands.Insert(GSM_BAND_ID_E_GSM900);
                    m_remGsmBands.Insert(GSM_BAND_ID_DCS1800);
                    break;
                case HARDWARE_REVISION_TYPE5REV2_1900_RF:
                case HARDWARE_REVISION_TYPE5REV3_1900_RF:
                case HARDWARE_REVISION_TYPE5REV7_1900_RF:
                    m_umtsBands.Insert(UBAND_II_1900);
                    m_remGsmBands.Insert(GSM_BAND_ID_GSM850);
                    m_remGsmBands.Insert(GSM_BAND_ID_PCS1900);
                    break;
                case HARDWARE_REVISION_TYPE5REV4_BAND_VIII:
                    m_umtsBands.Insert(UBAND_VIII);
                    m_rxOnlyUmtsBands.Insert(UBAND_I_2100);
                    m_remGsmBands.Insert(GSM_BAND_ID_DCS1800);
                    m_remGsmBands.Insert(GSM_BAND_ID_P_GSM900);
                    m_remGsmBands.Insert(GSM_BAND_ID_E_GSM900);
                    break;
                case HARDWARE_REVISION_TYPE5REV5_BAND_V:
                    m_umtsBands.Insert(UBAND_V_850);
                    m_rxOnlyUmtsBands.Insert(UBAND_II_1900);
                    m_remGsmBands.Insert(GSM_BAND_ID_GSM850);
                    m_remGsmBands.Insert(GSM_BAND_ID_PCS1900);
                    break;

                case HARDWARE_REVISION_TYPE5REV6_BAND_IV_AWS:
                    m_umtsBands.Insert(UBAND_IV_1700);
                    break;

                default:
                    TRACE_PRINTF_LEV(TRACE_CRITICAL, "Unknown hardware type/revision: %u %u",
                                     hardwareType, hardwareRevision);
                    break;
            }
            break;

        case HARDWARE_TYPE_TYPE6:

            switch(hardwareRevision)
            {
                case HARDWARE_REVISION_TYPE6REV0_2100_RF:
                case HARDWARE_REVISION_TYPE6REV2_2100_RF_DEMO:
                    m_umtsBands.Insert(UBAND_I_2100);
                    m_remGsmBands.Insert(GSM_BAND_ID_P_GSM900);
                    m_remGsmBands.Insert(GSM_BAND_ID_E_GSM900);
                    m_remGsmBands.Insert(GSM_BAND_ID_DCS1800);
                    break;
                case HARDWARE_REVISION_TYPE6REV1_1900_850_RF:
                case HARDWARE_REVISION_TYPE6REV3_1900_850_RF_DEMO:
                    m_umtsBands.Insert(UBAND_II_1900);
                    m_umtsBands.Insert(UBAND_V_850);
                    m_remGsmBands.Insert(GSM_BAND_ID_GSM850);
                    m_remGsmBands.Insert(GSM_BAND_ID_PCS1900);
                    break;
                default:
                    TRACE_PRINTF_LEV(TRACE_CRITICAL, "Unknown hardware type/revision: %u %u",
                                     hardwareType, hardwareRevision);
                    break;
            }
            break;

        case HARDWARE_TYPE_TYPE7:

            switch(hardwareRevision)
            {
                case HARDWARE_REVISION_TYPE7REV0_2100_RF:
                    m_umtsBands.Insert(UBAND_I_2100);
                    m_remGsmBands.Insert(GSM_BAND_ID_P_GSM900);
                    m_remGsmBands.Insert(GSM_BAND_ID_E_GSM900);
                    m_remGsmBands.Insert(GSM_BAND_ID_DCS1800);
                    break;
                case HARDWARE_REVISION_TYPE7REV1_1900_850_RF:
                    m_umtsBands.Insert(UBAND_II_1900);
                    m_umtsBands.Insert(UBAND_V_850);
                    m_remGsmBands.Insert(GSM_BAND_ID_GSM850);
                    m_remGsmBands.Insert(GSM_BAND_ID_PCS1900);
                    break;
                default:
                    TRACE_PRINTF_LEV(TRACE_CRITICAL, "Unknown hardware type/revision: %u %u",
                                     hardwareType, hardwareRevision);
                    break;
            }
            break;

        case HARDWARE_TYPE_TYPE8:

            switch(hardwareRevision)
            {
                /* V4R with Spartan-6 LX150, UBand-I Node-B, UBand-I UMTS-REM,
                 * E-GSM900/DCS1800 GSM-REM and no beacon
                 */
                case HARDWARE_REVISION_TYPE8REV0:
                    m_umtsBands.Insert(UBAND_I_2100);
                    m_remGsmBands.Insert(GSM_BAND_ID_P_GSM900);
                    m_remGsmBands.Insert(GSM_BAND_ID_E_GSM900);
                    m_remGsmBands.Insert(GSM_BAND_ID_DCS1800);
                    break;

                /* V4R with Spartan-6 LX150, UBand-IV Node-B, UBand-IV UMTS-REM,
                 * GSM850/PCS1900 GSM-REM and no beacon
                 */
                case HARDWARE_REVISION_TYPE8REV4:
                    m_umtsBands.Insert(UBAND_IV_1700);
                    m_remGsmBands.Insert(GSM_BAND_ID_GSM850);
                    m_remGsmBands.Insert(GSM_BAND_ID_PCS1900);
                    break;

                default:
                    TRACE_PRINTF_LEV(TRACE_CRITICAL, "Unknown hardware type/revision: %u %u",
                                     hardwareType, hardwareRevision);
                    break;
            }
            break;

        default:
            TRACE_PRINTF_LEV(TRACE_CRITICAL, "Unknown hardware type/revision: %u %u",
                             hardwareType, hardwareRevision);
            break;
    }

    m_remUmtsBands.Insert( m_umtsBands.Get() );
    m_remUmtsBands.Insert( m_rxOnlyUmtsBands.Get() );

    TRACE_MSG(ToString().c_str());
}

std::string FrequencyBandsSupported::ToString() const
{
    std::ostringstream stream;

    stream << "UMTS: " << m_umtsBands.ToString();

    stream << "\nUMTS.RX-Only: " << m_rxOnlyUmtsBands.ToString();

    stream << "\nUMTS.REM: " << m_remUmtsBands.ToString();

    stream << "\nGSM.REM: " << m_remGsmBands.ToString();

    return stream.str();
};


