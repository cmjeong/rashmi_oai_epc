///////////////////////////////////////////////////////////////////////////////
//
// GsmBands.h
//
// Class to do with handling GSM Bands.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __GsmBands_h_
#define __GsmBands_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <set>
#include <sstream>
#include <Radisys.h>
#include <system/ArfcnTypes.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

typedef std::set<GsmBandId> GsmBandIds;

class GsmBands
{
public:
    GsmBands(bool populateWithAllValidBands = true);

    GsmBands & Merge(const GsmBands& rhs);

    std::string ToString() const;

    const GsmBandIds & Get() const;

    void Clear();

    void Erase( GsmBandId band );

    void Erase(const GsmBands & rhs);

    void Insert( GsmBandId band );

    bool Find( GsmBandId band ) const;

    u16 Count() const;

    GsmBandId ArfcnToGsmBand(u16 arfcn);

private:
    GsmBandIds m_gsmBands;

};

#endif

