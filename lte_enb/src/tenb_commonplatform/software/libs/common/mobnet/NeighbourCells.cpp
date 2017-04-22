///////////////////////////////////////////////////////////////////////////////
//
// Radisys Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// NeighbourCells.cpp
//
// Defined the classes that hold the neighbour cell data required in
// connected mode.  Currenly this is used by RRCRelocationControl as
// relocation control compiles the list of neighbours needed and maintains
// that list for use during a relocation attempt, and also for UeMeasuremenControl
// to use for it's signalling requirements.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <iostream>
#include <iomanip>
#include <system/NumberConversions.h>
#include <system/UmtsBands.h>
#include <system/GsmBands.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "NeighbourCells.h"

///////////////////////////////////////////////////////////////////////////////
// Local Definitions
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Class: NeighbourCellFDD
//
///////////////////////////////////////////////////////////////////////////////

NeighbourCellFDD::NeighbourCellFDD (u32 cellFrequency, u32 cellScramblingCode,
                                    u16 cellRncId, u16 cellCid, u16 cellLac,
                                    u8 cellRac, u16 cellMcc, u16 cellMnc) :
    m_cellFrequency (cellFrequency),
    m_scramblingCode (cellScramblingCode),
    m_cellRncId (cellRncId),
    m_cellCid (cellCid),
    m_cellLac (cellLac),
    m_cellRac (cellRac),
    m_cellMcc (cellMcc),
    m_cellMnc (cellMnc)
{
    UmtsBands listofAllBands (true);

    // Find band id for the cell.
    m_cellBand = listofAllBands.UarfcnToUband(cellFrequency);
}

// Copy constructor
NeighbourCellFDD::NeighbourCellFDD (const NeighbourCellFDD & rhs)
{
    m_cellBand       = rhs.m_cellBand;
    m_cellFrequency  = rhs.m_cellFrequency;
    m_scramblingCode = rhs.m_scramblingCode;
    m_cellRncId      = rhs.m_cellRncId;
    m_cellCid        = rhs.m_cellCid;
    m_cellLac        = rhs.m_cellLac;
    m_cellRac        = rhs.m_cellRac;
    m_cellMcc        = rhs.m_cellMcc;
    m_cellMnc        = rhs.m_cellMnc;
}

NeighbourCellFDD::~NeighbourCellFDD ()
{
}

bool NeighbourCellFDD::CheckForAnyChanges(const NeighbourCellFDD &fddCell) const
{
    bool changes = false;
    if((m_cellFrequency  != fddCell.GetCellFrequency()) ||
       (m_scramblingCode != fddCell.GetScramblingCode()) ||
       (m_cellCid != fddCell.GetCellCid()) ||
       (m_cellRncId != fddCell.GetCellRncId()) ||
       (m_cellLac   != fddCell.GetCellLac()) ||
       (m_cellRac   != fddCell.GetCellRac()) ||
       (m_cellMcc   != fddCell.GetCellMcc()) ||
       (m_cellMnc   != fddCell.GetCellMnc()))
    {
        changes = true;
    }
    else
    {
        changes = false;
    }
    return(changes);
}
bool NeighbourCellFDD::CheckForSignallingChanges(const NeighbourCellFDD &fddCell) const
{
    bool changes = false;
    if((m_cellFrequency  != fddCell.GetCellFrequency()) ||
       (m_scramblingCode != fddCell.GetScramblingCode()))
    {
        changes = true;
    }
    else
    {
        changes = false;
    }
    return(changes);
}

std::string NeighbourCellFDD::TableHeaderToString () const
{
     std::ostringstream stream;

    stream << "BAND        UARFCN   SC  RNCID     C-ID   LAC   RAC   MCC   MNC" << std::endl;
    return (stream.str ());
}

std::string NeighbourCellFDD::ToTableString () const
{
	std::ostringstream stream;

    stream << setw(10) << UmtsBandIdToDetailedString(m_cellBand);
	stream << setw(6) << m_cellFrequency;

	stream << setw(5) << m_scramblingCode;
	stream << setw(7) << m_cellRncId;

	stream << setw(9) << m_cellCid;

	stream << setw(6) << m_cellLac;
	stream << setw(6) << (u16) m_cellRac;
	stream << setw(6) << m_cellMcc;
	stream << setw(6) << m_cellMnc << std::endl;

	return (stream.str ());
}

std::string NeighbourCellFDD::ToString () const
{
    std::ostringstream stream;

    stream << "UARFCN: " << m_cellFrequency;
    stream << " (" << UmtsBandIdToDetailedString(m_cellBand) << ")";

    stream << " PSC: " << m_scramblingCode;
    stream << " RNCid: " << m_cellRncId;

    stream << " C-ID: " << m_cellCid;

    stream << " LAC: " << m_cellLac;
    stream << " RAC: " << (u16) m_cellRac;
    stream << " MCC: " << m_cellMcc;
    stream << " MNC: " << m_cellMnc << std::endl;

    return (stream.str ());
}

///////////////////////////////////////////////////////////////////////////////
// Class: NeighbourCellGSM
//
///////////////////////////////////////////////////////////////////////////////
NeighbourCellGSM::NeighbourCellGSM (u32 cellIdentity, bool cellOnPscBand, u16 bcchArfcn, u8 networkColourCode, u8 basestationColourCode,
                                  u16 cellLac, u16 cellMcc, u16 cellMnc) :
    m_cellIdentity (cellIdentity),
    m_bcchArfcn (bcchArfcn),
    m_networkColourCode (networkColourCode),
    m_basestationColourCode (basestationColourCode),
    m_cellLac (cellLac),
    m_cellMcc (cellMcc),
    m_cellMnc (cellMnc)
{
    GsmBands allBands;
    // Figure out the cell band..
    // Now before we find out we must remove either 1800 or 1900pcs bands.
    // (which we can do with the cellOnPcsBand flag - otherwise calculation
    // would not work - 1800 & 1900 are mutually exclusive).
    if(cellOnPscBand)
    {
        allBands.Erase(GSM_BAND_ID_DCS1800);
    }
    else
    {
        allBands.Erase(GSM_BAND_ID_PCS1900);
    }
    // Now get the band
    m_cellBand = allBands.ArfcnToGsmBand(bcchArfcn);
}

// Copy constructor
NeighbourCellGSM::NeighbourCellGSM (const NeighbourCellGSM & rhs)
{
    m_cellIdentity  = rhs.m_cellIdentity;
    m_cellBand      = rhs.m_cellBand;
    m_bcchArfcn     = rhs.m_bcchArfcn;
    m_cellLac       = rhs.m_cellLac;
    m_cellMcc       = rhs.m_cellMcc;
    m_cellMnc       = rhs.m_cellMnc;

    m_networkColourCode     = rhs.m_networkColourCode;
    m_basestationColourCode = rhs.m_basestationColourCode;

}

NeighbourCellGSM::~NeighbourCellGSM ()
{
}

bool NeighbourCellGSM::CheckForAnyChanges(const NeighbourCellGSM &gsmCell) const
{
    bool changes = false;
    if((m_bcchArfcn  != gsmCell.GetBcchArfcn()) ||
       (m_cellBand != gsmCell.GetCellBand()) ||
       (m_networkColourCode != gsmCell.GetNCC()) ||
       (m_basestationColourCode != gsmCell.GetBCC()) ||
       (m_cellIdentity != gsmCell.GetCellIdentity()) ||
       (m_cellLac   != gsmCell.GetCellLac()) ||
       (m_cellMcc   != gsmCell.GetCellMcc()) ||
       (m_cellMnc   != gsmCell.GetCellMnc()))
    {
        changes = true;
    }
    else
    {
        changes = false;
    }
    return(changes);
}
bool NeighbourCellGSM::CheckForSignallingChanges(const NeighbourCellGSM &gsmCell) const
{
    bool changes = false;
    if((m_bcchArfcn  != gsmCell.GetBcchArfcn()) ||
       (m_networkColourCode != gsmCell.GetNCC()) || // TODO: signalling?
       (m_basestationColourCode != gsmCell.GetBCC()) || // TODO: Signalling?
       (m_cellBand != gsmCell.GetCellBand())) // TODO: Signalling?
    {
        changes = true;
    }
    else
    {
        changes = false;
    }
    return(changes);
}
std::string NeighbourCellGSM::TableHeaderToString () const
{
    std::ostringstream stream;
    stream << "CELLID    ARFCN  BAND      NCC  BCC   LAC  MCC  MNC " << std::endl;
    return (stream.str ());
}

std::string NeighbourCellGSM::ToTableString () const
{
    std::ostringstream stream;

    stream << setw(9) << m_cellIdentity;
    stream << setw(6) << m_bcchArfcn;

    stream << setw(10) << GsmBandIdToString(m_cellBand);

    stream << setw(5) << (u16) m_networkColourCode;
    stream << setw(5) << (u16) m_basestationColourCode;
    stream << setw(6) << m_cellLac;
    stream << setw(5) << m_cellMcc;
    stream << setw(5) << m_cellMnc << std::endl;

    return (stream.str ());
}

std::string NeighbourCellGSM::ToString () const
{
    std::ostringstream stream;

    stream << "CellID: " << m_cellIdentity;
    stream << " ARFCN: " << m_bcchArfcn;

    stream << " (" << GsmBandIdToString(m_cellBand) << ")";

    stream << " NCC: " << (u16) m_networkColourCode;
    stream << " BCC: " << (u16) m_basestationColourCode;
    stream << " LAC: " << m_cellLac;
    stream << " MCC: " << m_cellMcc;
    stream << " MNC: " << m_cellMnc << std::endl;

    return (stream.str ());
}

// End of file.
