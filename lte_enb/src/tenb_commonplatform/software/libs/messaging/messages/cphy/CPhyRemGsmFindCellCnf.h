///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyRemGsmFindCellCnf.h 28519 2010-07-21 14:39:46Z mmcternan $
//
// CPhyRemGsmFindCellCnf message.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyRemGsmFindCellCnf_h_
#define __CPhyRemGsmFindCellCnf_h_

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
#define CPHY_REM_FIND_CELL_CNF_MAX_GSM_NBRS  32

///////////////////////////////////////////////////////////////////////////////
// Message Structures
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

/** Confirmation that a cell search on some frequency has concluded.
 * This is sent once the cell search on some frequency, as directed by a
 * CphyRemGsmFindCellReq has concluded, or that the search could not be
 * conducted for some reason.
 *
 * \note In error situations \a status will contain a reason code, while
 *        in cases where a cell was found the \a status will be L1_SOK.
 *        A failed search is indicated by a L1_SOK \a status, but with \a
 *        bsic of #INVALID_BSIC.
 *
 * \ingroup CPhyRemGsm
 */
typedef struct gsmNbrList
{
    /** Frequency on which the cell search was conducted.
     * In GSM900 and DCS1800.
     */
    arfcn_t         arfcn;

    /** Base Station Identity Code of the found cell or INVALID_BSIC.
     * In the case of a failed search this will be set to INVALID_BSIC,
     * otherwise it is set to the decoded BSIC of the cell found on the
     * searched ARFCN.
     *
     * \a Structure: NCC (Network colour code, 3 bits) +
     *               BCC (Base station colour code ,3 bits)
     *
     */
    bsic_t          bsic;

    /** Measured frequency offset between a found cell and the FAP.
     * This gives the frequency offset of the cell being decoded in the case
     * that \a useAfc was not set in the corresponding CphyRemGsmFindCellReq.
     */
    int16_t         freqOffsetHz;

    /** The current AFC DAC value.
     * This gives the current AFC DAC value, which may have been updated as a
     * result of finding a cell when \a useAfc was set in the corresponding
     * CphyRemGsmFindCellReq.
     */
    uint16_t        dacValue;

    /** Wideband signal strength indication for the searched frequency in 1/8ths of a dBm. */
    int16_t rssi;
    
    /**
    LAC of the cell 
    **/
    uint8_t lac[2];

    /**
     RAC of the cell
    **/
    uint8_t rac;

    /**
     PLMN of the GSM
    **/
    plmnId_t plmnId;

    /**
     Cell Id
    **/
    uint32_t cellId;
} 
GsmNbrs;
typedef struct CphyRemGsmFindCellCnfTag
{
    /** Status code
     * Normally indicates a sucessful search, but may also indicate errors
     * such as an unsupported band or frequency, or the number of frequencies
     * to scan exceeds maximum supported value.
     */
    l1status_t      status;
    uint16_t        nbrCount;
    GsmNbrs         nbrList[CPHY_REM_FIND_CELL_CNF_MAX_GSM_NBRS];

}
CphyRemGsmFindCellCnf;

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

/** Function to serialise a CphyRemGsmFindCellCnf structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyRemGsmFindCellCnf_Serialise(const CphyRemGsmFindCellCnf *msg,
                                    u8 *const                  buffer,
                                    u32                        maxLen);


/** Function to deserialise a CphyRemGsmFindCellCnf structure from a buffer.
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyRemGsmFindCellCnf_Deserialise(const u8                  *buffer,
                                      u32                        maxLen,
                                      CphyRemGsmFindCellCnf *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyRemGsmFindCellCnf : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyRemGsmFindCellCnf() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    CPhyRemGsmFindCellCnf(const CphyRemGsmFindCellCnf *msg);
    virtual ~CPhyRemGsmFindCellCnf() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_REM_GSM_FIND_CELL_CNF; };
    virtual s32  Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Implement CPhyMessage pure virtual.
     */
    virtual u32 GetStruct(CphyMessageData *const msg);

    /**
     * Accessors.
     */
    CphyRemGsmFindCellCnf GetActualStruct() { return m_Struct; }
    l1status_t GetStatus() { return m_Struct.status; }
    uint16_t GetDacValue() {return m_Struct.nbrList[0].dacValue;}
    uint16_t GetFreqOffsetHz() {return m_Struct.nbrList[0].freqOffsetHz;}

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;
    virtual std::string ToBriefString() const;

private:

    /** Embedded C structure carrying parameters.
     */
    CphyRemGsmFindCellCnf m_Struct;
};

}

#endif // __cplusplus

#endif // __CPhyHwConfigCnf_h_
