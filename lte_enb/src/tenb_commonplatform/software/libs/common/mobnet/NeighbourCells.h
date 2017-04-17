///////////////////////////////////////////////////////////////////////////////
//
// NeighbourCell.h
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

#ifndef __NeighbourCell_h_
#define __NeighbourCell_h_

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

#include <list>
#include <boost/shared_ptr.hpp>
#include <mobnet/UmtsBandId.h>
#include <mobnet/GsmBandId.h>

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

using namespace boost;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// GlobalDeclarations
///////////////////////////////////////////////////////////////////////////////

static const u32 MAX_NUM_INTRA_FREQ_NEIGHBOUR_CELLS = 31; // only 31 coz it's serving + 31 neighbours = 32.
static const u32 MAX_NUM_INTER_FREQ_NEIGHBOUR_CELLS = 32;
static const u32 MAX_NUM_INTER_RAT_NEIGHBOUR_CELLS = 16;
static const u32 RNC_ID_INVALID = 4096;

class NeighbourCellFDD
{
public:
     // Constructor used for FDD Neighbour Cell declaration
    NeighbourCellFDD (u32 cellFrequency, u32 cellScramblingCode, u16 cellRncId,
                      u16 cellCid, u16 cellLac, u8 cellRac, u16 cellMcc,
                      u16 cellMnc);
    NeighbourCellFDD (const NeighbourCellFDD & rhs);
    virtual ~NeighbourCellFDD ();

    u16 GetCellCid  ()       const { return m_cellCid; }
    UmtsBandId GetCellBand() const {return m_cellBand; }
    u32 GetCellFrequency ()  const { return m_cellFrequency; }
    u32 GetScramblingCode()  const { return m_scramblingCode; }
    u16 GetCellRncId()       const { return m_cellRncId; }
    u16 GetCellLac()         const { return m_cellLac; }
    u8  GetCellRac()         const { return m_cellRac; }
    u16 GetCellMcc()         const { return m_cellMcc; }
    u16 GetCellMnc()         const { return m_cellMnc; }

    const char * GetCellBandAsString() const { return UmtsBandIdToDetailedString(m_cellBand); }

    bool CheckForAnyChanges(const NeighbourCellFDD &fddCell) const;
    bool CheckForSignallingChanges(const NeighbourCellFDD &fddCell) const;
    std::string TableHeaderToString() const;
    std::string ToTableString () const;
    std::string ToString () const;

private:

    UmtsBandId m_cellBand; // The band that the UE operates (derived from the UARFCN).
    u32 m_cellFrequency;  // The radio frequency (UARFCN) of the cell we are measuring.
    u32 m_scramblingCode; // The scrambling code of the cell we are measuring.
    u16 m_cellRncId;      // The RNC ID of the cell we are measuring.
    u32 m_cellCid;        // The cell c-id (RANAP facing used for cell id for relocation target cell - 16 bit) of the cell we are measuring.
    u16 m_cellLac;        // The LAC of the cell we are measuring.
    u8  m_cellRac;        // The RAC of the cell we are measuring.
    u16 m_cellMcc;        // The MCC of the cell we are measuring.
    u16 m_cellMnc;        // The MNC of the cell we are measuring.


};

class NeighbourCellGSM
{
public:
	NeighbourCellGSM (u32 cellIdentity, bool cellOnPscBand, u16 bcchArfcn, u8 networkColourCode, u8 basestationColourCode, u16 cellLac,
	                 u16 cellMcc, u16 cellMnc);
	NeighbourCellGSM (const NeighbourCellGSM & rhs);
	virtual ~NeighbourCellGSM ();

	u32 GetCellIdentity ()  const { return m_cellIdentity; }
	u8  GetNCC ()           const { return m_networkColourCode; }
	u8  GetBCC ()           const { return m_basestationColourCode; }
	u16 GetBcchArfcn ()     const { return m_bcchArfcn; }
	GsmBandId GetCellBand() const { return m_cellBand; }
	u16 GetCellLac ()       const { return m_cellLac; }
	u16 GetCellMcc ()       const { return m_cellMcc; }
	u16 GetCellMnc ()       const { return m_cellMnc; }

    bool CheckForAnyChanges(const NeighbourCellGSM &gsmCell) const;
    bool CheckForSignallingChanges(const NeighbourCellGSM &gsmCell) const;

    std::string TableHeaderToString() const;
    std::string ToTableString () const;
    std::string ToString () const;

private:

    GsmBandId m_cellBand;

	u32 m_cellIdentity;
	u16 m_bcchArfcn;
	u16 m_cellLac;
	u16 m_cellMcc;        // The MCC of the cell we are measuring.
	u16 m_cellMnc;        // The MNC of the cell we are measuring.

	u8 m_networkColourCode;
	u8 m_basestationColourCode;

};

// FSS and GSM Measured cell lists.
typedef std::list < NeighbourCellFDD > NeighbourCellListFDD;
typedef std::list < NeighbourCellGSM > NeighbourCellListGSM;

#endif
