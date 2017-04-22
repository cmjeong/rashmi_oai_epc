///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyRemWcdmaFindCellCnf.h 28519 2010-07-21 14:39:46Z mmcternan $
//
// CPhyRemWcdmaFindCellCnf message.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyRemWcdmaFindCellCnf_h_
#define __CPhyRemWcdmaFindCellCnf_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
#include <string.h> // for memset
#endif
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CPhyTypes.h"
#include "CPhyMessage.h"

///////////////////////////////////////////////////////////////////////////////
// Message Constants
///////////////////////////////////////////////////////////////////////////////

/** Maximum number of cells that can be returned by a REM search.
 * This limits the number of cells that can be reported on a single frequency.
 */
#define CPHY_REM_FIND_CELL_CNF_MAX_REM_FOUND_CELLS  8
#define CPHY_REM_FIND_CELL_CNF_MAX_WCDMA_NBRS       32

///////////////////////////////////////////////////////////////////////////////
// Message Structures
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

/** Response to a ChyRemWcdmaFindCelReq.
 * Sent in response to a ChyRemWcdmaFindCelReq, this returns the count of cells
 * that have been identified, as well as their identity and basic signal
 * strength measurements.
 *
 * \ingroup CPhyRemWcdma
 */

typedef struct wcdmaNbrList
{
    /** Count of how many cells were found. */
    uint8_t  nCells;

    /** The frequency that was searched. */
    uarfcn_t frequency;

    /** The band that was searched. */
    uband_t  band;

    /** Wideband signal strength indication for the searched frequency in 1/8ths of a dBm. */
    int16_t rssi;

    /** The Primary Scrambling codes for each located cell. */
    uint16_t psc[CPHY_REM_FIND_CELL_CNF_MAX_REM_FOUND_CELLS];

    /** EcN0 value for each located cell in 1/8ths of a dB. */
    int16_t ecn0[CPHY_REM_FIND_CELL_CNF_MAX_REM_FOUND_CELLS];

    /** RSCP value for each located cell in 1/8ths of a dBm. */
    int16_t rscp[CPHY_REM_FIND_CELL_CNF_MAX_REM_FOUND_CELLS];

}
WcdmaNbrs;

typedef struct CphyRemWcdmaFindCellCnfTag
{
    /** Status code.
     * Normally indicates a sucessful search, but may also indicate errors
     * such as an unsupported band or frequency.
     */
    l1status_t status;
    
    /** The number of neighbors . For Picochip the number is always 1*/
    uint8_t  nbrCount;

    /** The neighbors per Uarfcn. The value is always 1 in case of Picochip*/
    WcdmaNbrs nbrList[CPHY_REM_FIND_CELL_CNF_MAX_WCDMA_NBRS];

 }
CphyRemWcdmaFindCellCnf;

#ifdef __cplusplus
}
#endif


///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////


#ifdef __cplusplus
extern "C" {
#endif

/** Function to serialise a CphyRemWcdmaFindCellCnf structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyRemWcdmaFindCellCnf_Serialise(const CphyRemWcdmaFindCellCnf *msg, u8 *const buffer, u32 maxLen);


/** Function to deserialise a CphyRemWcdmaFindCellCnf structure from some buffer
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyRemWcdmaFindCellCnf_Deserialise(const u8 *buffer, u32 maxLen, CphyRemWcdmaFindCellCnf *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyRemWcdmaFindCellCnf : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyRemWcdmaFindCellCnf() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    CPhyRemWcdmaFindCellCnf(const CphyRemWcdmaFindCellCnf *cStruct);
    virtual ~CPhyRemWcdmaFindCellCnf() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_REM_FIND_CELL_CNF; };
    virtual s32  Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Implement CphyMessage pure virtual.
     */
    virtual u32 GetStruct(CphyMessageData *const msg);

    /**
     * Accessors.
     */
     l1status_t GetStatus() const { return m_Struct.status; }
    /** Count of how many cells were found. */
     uint8_t  GetNumCells() const { return m_Struct.nbrList[0].nCells; }

     /** The frequency that was searched. */
     uarfcn_t GetFrequency() const { return m_Struct.nbrList[0].frequency; }

     /** The band that was searched. */
     uband_t  GetBand() const { return m_Struct.nbrList[0].band; }

     /** Wideband signal strength indication for the searched frequency. */
     int16_t GetRssi() const { return m_Struct.nbrList[0].rssi; }

     /** The Primary Scrambling codes for each located cell. */
     uint16_t GetPsc(uint8_t cellNo) const { return m_Struct.nbrList[0].psc[cellNo]; }

     /** EcN0 value for each located cell. */
     int16_t GetEcn0(uint8_t cellNo) const { return m_Struct.nbrList[0].ecn0[cellNo]; }

     /** RSCP value for each located cell. */
     int16_t GetRscp(uint8_t cellNo) const { return m_Struct.nbrList[0].rscp[cellNo]; }

    /** Count of how many cells were found. */
     uint8_t  GetNbrCount() const { return m_Struct.nbrCount; }

    /** Count of how many cells were found. */
     WcdmaNbrs GetNbrList() const { return m_Struct.nbrList[CPHY_REM_FIND_CELL_CNF_MAX_WCDMA_NBRS - 1]; }

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;
    virtual std::string ToBriefString() const;

private:

    /** Embedded C structure carrying parameters.
     */
    CphyRemWcdmaFindCellCnf m_Struct;
};

}

#endif /* __cplusplus */

#endif
