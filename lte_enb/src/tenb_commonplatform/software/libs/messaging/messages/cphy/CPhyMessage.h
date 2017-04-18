///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyMessage.h 17546 2009-09-16 17:21:49Z mmcternan $
//
// CPHY message type and serialisation interface.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyMessage_h_
#define __CPhyMessage_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
#include <system/Serialisable.h>
#endif
#include <3waytypes.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Message Constants
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Message Structures
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __DOXYGEN__

/** Union of all CPhy message pointers.
 */
typedef union
{
    struct CphyHwConfigReqTag               *hwConfigReq;
    struct CphyHwConfigCnfTag               *hwConfigCnf;
    struct CphyModeChangeReqTag             *modeChangeReq;
    struct CphyModeChangeCnfTag             *modeChangeCnf;
    struct CphyNodeBConfigReqTag            *nodeBConfigReq;
    struct CphyNodeBConfigCnfTag            *nodeBConfigCnf;
    struct CphyNodeBCctrchSetupReqTag       *nodeBCctrchSetupReq;
    struct CphyNodeBCctrchRemoveReqTag      *nodeBCctrchRemoveReq;
    struct CphyNodeBCctrchRemoveCnfTag      *nodeBCctrchRemoveCnf;
    struct CphyNodeBCctrchCnfTag            *nodeBCctrchCnf;
    struct CphyNodeBTxEnableReqTag          *nodeBTxEnableReq;
    struct CphyNodeBTxEnableCnfTag          *nodeBTxEnableCnf;
    struct CphyNodeBTxDpchEnableReqTag      *nodeBTxDpchEnableReq;
    struct CphyNodeBTxDpchEnableCnfTag      *nodeBTxDpchEnableCnf;
    struct CphyNodeBCompressedModeReqTag    *nodeBCompressedModeReq;
    struct CphyNodeBSfnReqTag               *nodeBSfnReq;
    struct CphyNodeBSfnCnfTag               *nodeBSfnCnf;
    struct CphyNodeBStatIndTag              *nodeBStatInd;
    struct CphyNodeBPchAddReqTag            *nodeBPchAddReq;
    struct CphyNodeBPchAddCnfTag            *nodeBPchAddCnf;
    struct CphyNodeBPchRemoveReqTag         *nodeBPchRemoveReq;
    struct CphyNodeBPchRemoveCnfTag         *nodeBPchRemoveCnf;
    struct CphyNodeBSccpchConfigReqTag      *nodeBSccpchConfigReq;
    struct CphyNodeBSccpchConfigCnfTag      *nodeBSccpchConfigCnf;
    struct CphyNodeBSyncIndTag              *nodeBSyncInd;
    struct CphyNodeBOutOfSyncIndTag         *nodeBOutOfSyncInd;
    struct CphyNodeBRachConfigReqTag        *nodeBRachConfigReq;
    struct CphyRemWcdmaFindCellReqTag       *remWcdmaFindCellReq;
    struct CphyRemWcdmaFindCellCnfTag       *remWcdmaFindCellCnf;
    struct CphyRemWcdmaFreqOffsetMeasReqTag *remWcdmaFreqOffsetMeasReq;
    struct CphyRemWcdmaFreqOffsetMeasCnfTag *remWcdmaFreqOffsetMeasCnf;
    struct CphyRemWcdmaCoarseFreqLockReqTag *remWcdmaCoarseFreqLockReq;
    struct CphyRemWcdmaCoarseFreqLockCnfTag *remWcdmaCoarseFreqLockCnf;
    struct CphyRemSibDecodeReqTag           *remSibDecodeReq;
    struct CphyRemSibDecodeIndTag           *remSibDecodeInd;
    struct CphyRemSibDecodeCnfTag           *remSibDecodeCnf;
    /* qc_cl_changes*/
    struct CphyRemSibDecodeCompleteTag      *remSibDecodeComplete;
    struct CphyRemGsmRssiScanReqTag         *remGsmRssiScanReq;
    struct CphyRemGsmRssiScanCnfTag         *remGsmRssiScanCnf;
    struct CphyRemGsmFindCellReqTag         *remGsmFindCellReq;
    struct CphyRemGsmFindCellCnfTag         *remGsmFindCellCnf;
    struct CphyRemGsmBcchDecodeIndTag       *remGsmBcchDecodeInd;
    struct CphyRemGsmStopBcchDecodeReqTag   *remGsmStopBcchDecodeReq;
    struct CphyRemGsmStopBcchDecodeCnfTag   *remGsmStopBcchDecodeCnf;
    /* changes for freq-sync */
    struct CphyNlmCoscReqTag                *nlmCoscReq;
    struct CphyNlmCoscCnfTag                *nlmCoscCnf; 
    struct CphyNlmErrIndTag                 *nlmErrInd; 
}
CphyMessageData;

#endif

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

u32 Cphy_Serialise(u32                    serialId,
                   const CphyMessageData  msg,
                   u8 *const              buf,
                   u32                    bufLen);

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

/**
 * Base class for a CPHY message.
 *
 * This gives a base class for CPHY messages.  It adds one method that allows
 * a pointer to the message as a C structure to be retrieved such that the
 * messages can easily interwork with C.
 */
class CPhyMessage : public threeway::Serialisable
{
public:

    /**
     * Get a pointer to the message as a C structure.
     *
     * This should return a pointer to the message as a C structure while
     * returning the message serialisation ID.
     *
     * Typically this will be used in a C++ backbone to a C application in the
     * following manner:
     * \code
     *   const CphyMessageData *msgBuf;
     *
     *   switch(Message->GetStruct(&msgBuf))
     *   {
     *       case SERIALISATION_ID_CPHY_REM_FIND_CELL_REQ:
     *           doRemFindCellReq(&(msgBuf->remWcdmaFindCellReq)));
     *           break;
     *       ....
     *   }
     *
     * \endcode
     *
     * \param  msg   Pointer to a pointer to be set to point at the message
     *                structure.  The passed pointer should be declared const
     *                to be compatible.
     * \return The ID of the serialised message.
     *
     * \note The returned pointer refers to data held within an instance of
     *        this class, and should not be modified or accessed beyond the
     *        lifetime of the parent object.
     */
    virtual u32 GetStruct(CphyMessageData *const msg) = 0;

};

}

#endif /* __cplusplus */

#endif
