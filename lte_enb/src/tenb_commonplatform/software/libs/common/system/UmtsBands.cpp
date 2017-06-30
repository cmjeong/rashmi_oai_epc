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
#include <system/UmtsBands.h>
#include <system/FrequencyConversions.h>

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

UmtsBands::UmtsBands(bool populateWithAllValidBands)
{
    if(populateWithAllValidBands)
    {
        for( u32 i = u32(UBAND_FIRST); i <= u32(UBAND_LAST); i++)
        {
            m_umtsBands.insert( UmtsBandId(i) );
        }
    }
}

UmtsBands & UmtsBands::Merge(const UmtsBands& rhs)
{
    for( UmtsBandIds::const_iterator i = rhs.m_umtsBands.begin(); i != rhs.m_umtsBands.end(); ++i)
    {
        UmtsBandId band = *i;

        m_umtsBands.insert( band );
    }

    return *this;
}

std::string UmtsBands::ToString() const
{
    std::ostringstream stream;

    stream << "{ ";

    for( UmtsBandIds::const_iterator i = m_umtsBands.begin(); i != m_umtsBands.end(); ++i)
    {
        UmtsBandId band = *i;

        stream << UmtsBandIdToString(band) << " ";
    }
     stream << "}";
    return stream.str();
};

std::string UmtsBands::ToDetailedString() const
{
    std::ostringstream stream;

    stream << "{ ";

    for( UmtsBandIds::const_iterator i = m_umtsBands.begin(); i != m_umtsBands.end(); ++i)
    {
        UmtsBandId band = *i;

        stream << UmtsBandIdToDetailedString(band) << " ";
    }
     stream << "}";
    return stream.str();
};

const UmtsBandIds & UmtsBands::Get() const
{
    return m_umtsBands;
}

void UmtsBands::Clear()
{
    m_umtsBands.clear();
}

void UmtsBands::Erase( UmtsBandId band )
{
    m_umtsBands.erase( band );
}

void UmtsBands::Erase(const UmtsBands& rhs)
{
    for( u8 band = (u8) UBAND_FIRST; band <= (u8) UBAND_LAST; band++)
    {
        // Is the current bandId in both lists?
        if((m_umtsBands.find((UmtsBandId) band) == m_umtsBands.end()) ||
           (rhs.m_umtsBands.find((UmtsBandId) band) == rhs.m_umtsBands.end()))
        {
            // Nope, so remove it.
            m_umtsBands.erase((UmtsBandId) band);
        }
    }
}

void UmtsBands::Insert(const UmtsBandIds& bands)
{
    for( UmtsBandIds::const_iterator i = bands.begin(); i != bands.end(); ++i)
    {
        UmtsBandId band = *i;

        Insert( band );
    }
}

void UmtsBands::Insert( UmtsBandId band )
{
    m_umtsBands.insert( band );
}

bool UmtsBands::Find( UmtsBandId band ) const
{
    return (m_umtsBands.find(band) != m_umtsBands.end());
}

u16 UmtsBands::Count() const
{
    return (m_umtsBands.size());
}

// In order for this method to function properly the UMTS Band list should only have
// either band V (850) or band VI entry, or neither - but never both!
// If both are present then any band VI cells will be incorrectly identified as band V (850).
UmtsBandId UmtsBands::UarfcnToUband(u16 uarfcn)
{
    UmtsBandId bandId = UBAND_INVALID;
    bool bandVIactive = Find(UBAND_VI);

    bandId = (UmtsBandId) GetUmtsFddBand(uarfcn, bandVIactive); // This calls the C function in FrequencyConversions.c
    return (bandId);
}

