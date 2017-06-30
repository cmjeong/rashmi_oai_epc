///////////////////////////////////////////////////////////////////////////////
//
// GsmBands.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////
#include <system/GsmBands.h>
#include <system/FrequencyConversions.h>
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

GsmBands::GsmBands(bool populateWithAllValidBands)
{
    if(populateWithAllValidBands)
    {
        for( u32 i = u32(GSM_BAND_ID_FIRST); i <= u32(GSM_BAND_ID_LAST); i++)
        {
            m_gsmBands.insert( GsmBandId(i) );
        }
    }
}

GsmBands & GsmBands::Merge(const GsmBands& rhs)
{
    for( GsmBandIds::const_iterator i = rhs.m_gsmBands.begin(); i != rhs.m_gsmBands.end(); ++i)
    {
        GsmBandId band = *i;

        m_gsmBands.insert( band );
    }

    return *this;
}

std::string GsmBands::ToString() const
{
    std::ostringstream stream;

    stream << "{ ";

    for( GsmBandIds::const_iterator i = m_gsmBands.begin(); i != m_gsmBands.end(); ++i)
    {
        GsmBandId band = *i;

        stream << GsmBandIdToString(band) << " ";
    }
     stream << "}";

     return stream.str();
};

const GsmBandIds & GsmBands::Get() const
{
    return m_gsmBands;
}

void GsmBands::Clear()
{
    m_gsmBands.clear();
}

void GsmBands::Erase( GsmBandId band )
{
    m_gsmBands.erase( band );
}

void GsmBands::Erase(const GsmBands & rhs)
{
    for( u8 band = (u8) GSM_BAND_ID_FIRST; band <= (u8) GSM_BAND_ID_LAST; band++)
    {
        // Is the current bandId in both lists?
        if((m_gsmBands.find((GsmBandId) band) == m_gsmBands.end()) ||
           (rhs.m_gsmBands.find((GsmBandId) band) == rhs.m_gsmBands.end()))
        {
            // Nope, so remove it.
            m_gsmBands.erase((GsmBandId) band);
        }
    }
}

void GsmBands::Insert( GsmBandId band )
{
    m_gsmBands.insert( band );
}

bool GsmBands::Find( GsmBandId band ) const
{
    return (m_gsmBands.find(band) != m_gsmBands.end());
}

u16 GsmBands::Count() const
{
    return (m_gsmBands.size());
}

// Band        ARFCN Range  PSC Flag
// ---------------------------------
// P-GSM 900 - 1..124       false
// E-GSM 900 - 0..124       false
//             975..1023    false
// R-GSM 900   0..124       false
//             955..1023    false
// GSM 850     128..251     false
// GSM 450     259..293     false
// GSM 480     306..340     false
// GSM 750     438..511     false
// DCS 1800    512..885     false
// PCS 1900    512..810     true
//
// Not currently used (and ARFCNs are dynamic - based off of BCCH info).
//
// Also not currently supported by FAP.
//   T-GSM380
//   T-GSM410
//   GSM710
//   GSM810
//   T-GSM900
//

// In order for this method to function properly the GSM Band list should only have
// either DCS1800 or PSC1900 entry, or neither - but never both!
// If both are present then any PSC1900 cells will be incorrectly identified as DCS1800
GsmBandId GsmBands::ArfcnToGsmBand(u16 arfcn)
{
    GsmBandId bandId = GSM_BAND_ID_INVALID;
    bool pcs1900active = Find(GSM_BAND_ID_PCS1900);

    // Assert in case both DCS1800 & PSC1900 are in the same list.
    //RSYS_ASSERT_PRINTF(!(pcs1900active && Find(GSM_BAND_ID_DCS1800)), "DCS1800 & PCS 1900 are in the list.  Only one should be present (otherwise the returned band information will be invalid!)");

    // Downgraded assert to log message - it is *possible* that this could be happen in certain situation (to be fully analysed later).

    if(pcs1900active && Find(GSM_BAND_ID_DCS1800))
    {
        TRACE_MSG("GsmBands::ArfcnToGsmBand - DCS1800 & PCS 1900 are in the list.  Only one should be present (otherwise the returned band information will be invalid!)");
    }
    bandId = (GsmBandId) GetGsmBand(arfcn, pcs1900active); // This calls the C function in FrequencyConversions.c

    if(!Find(bandId))
    {
        // Returned band not in list - therfore reset band value to invalid.
        bandId = GSM_BAND_ID_INVALID;
    }
    return (bandId);
}
