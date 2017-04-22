

/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for Entry point fucntions
  
     File:     rg_dhm.c
  
     Sid:      tf_ptui.c@@/main/3 - Sat Jul 30 02:22:24 2011
  
     Prg:      ps
  
**********************************************************************/

/** @file rg_dhm.c
@brief APIs related to Downlink HARQ.
*/


/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_tkns.h"       /* Common Token Defines */
#include "cm_llist.h"      /* Common Link List Defines */
#include "cm_hash.h"       /* Common Hash List Defines */
#include "cm_mblk.h"       /* common memory link list library */
#include "cm_lte.h"        /* Common LTE Defines */
#include "tfu.h"           /* RGU Interface defines */

/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_tkns.x"       /* Common Token Definitions */
#include "cm_llist.x"      /* Common Link List Definitions */
#include "cm_lib.x"        /* Common Library Definitions */
#include "cm_mblk.x"       /* common memory link list library */
#include "cm_hash.x"       /* Common Hash List Definitions */
#include "cm_lte.x"        /* Common LTE Defines */
#include "tfu.x"           /* RGU Interface includes */


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if !(defined(LCTFUITFU)  && defined(RG) && defined(LWLCTFUITFU))
#define PTTFUITFU
#endif


/* MAX Number of Service Users of TF */
#define TF_MAX_TFU_USR   3

#ifdef PTTFUITFU
/** @brief This API is used to receive a Bind Confirm from PHY to MAC.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param status Status of the bind request.
 * @return ROK/RFAILED
 */
EXTERN S16 PtUiTfuBndCfm ARGS((Pst * pst, SuId suId, U8 status));
/** @brief This API is used to receive a Bind Confirm from PHY to Scheduler.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param status Status of the bind request.
 * @return ROK/RFAILED
 */
EXTERN S16 PtUiTfuSchBndCfm ARGS((Pst * pst, SuId suId, U8 status));
/** @brief This API is used to indication Random Access Request reception from
 * PHY to Scheduler.
 * @details This primitive is used by physical layer to indicate the reception
 * of a Random Access Request from a set of UEs. The information passed consists
 * of the RA-RNTI and the list of preambles received. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param raReqInd Pointer to the TfuRaReqIndInfo structure.
 * @return ROK/RFAILED
 */
EXTERN S16 PtUiTfuRaReqInd ARGS((Pst * pst, SuId suId, TfuRaReqIndInfo * raReqInd));
/** @brief This Primitive carries the Data PDUs from PHY to MAC.
 * @details The uplink Data i.e. the data transmitted by the UEs received by the
 * physical layer at the eNodeB in the subframe (indicated by the timingInfo),
 * is relayed to MAC using this primitive. 
 * @param pst 
 * @param spId
 * @param tfuDatInd pointer to TfuDatIndInfo
 * @return 
 */
EXTERN S16 PtUiTfuDatInd ARGS((Pst * pst, SuId suId, TfuDatIndInfo * datInd));
/** @brief This Primitive carries the HARQ Feedback from PHY to scheduler
 * @details HARQ feedback is sent by the UE to the eNodeB, an ACK is sent if UE
 * could successfully recieve the data transmitted by the eNodeB, else a NACK is
 * sent. This feedback is utilized by MAC for further scheduling, for instance
 * it could schedule an adaptive retransmission of the same data. 
 * @param pst 
 * @param spId
 * @param tfuHqInd pointer to TfuHqIndInfo
 * @return 
 */
EXTERN S16 PtUiTfuHqInd ARGS((Pst * pst, SuId suId, TfuHqIndInfo * hqInd));
/** @brief This Primitive carries the SR Indication from PHY to scheduler. 
 * @details Scheduling Request (SR) is sent by the UE to the eNodeB to request
 * for Uplink (UL) grant. This primitive carries a list of SRs for a number of
 * UEs received in the indicated subframe. 
 * @param pst 
 * @param spId
 * @param tfqSrInd pointer to TfuSrIndInfo
 * @return 
 */
EXTERN S16 PtUiTfuSrInd ARGS((Pst * pst, SuId suId, TfuSrIndInfo * srInd));
/** @brief This API is used to indicate CQI reporting from PHY to Scheduler
 * @details This primitive carries an estimate of the uplink Channel quality
 * index (CQI) for a list of UEs. This is an extimate of the uplink channel
 * quality i.e. the transmission from UE as calculated at the Physical layer at
 * the eNodeB. 
 * It carries a list of subband CQIs for each UE. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param ulCqiInd Pointer to the TfuUlCqiIndInfo structure.
 * @return ROK/RFAILED
 */
EXTERN S16 PtUiTfuUlCqiInd ARGS((Pst * pst, SuId suId, TfuUlCqiIndInfo * ulCqiInd));
/** @brief This API is used by the Physical layer to indicate if the CRC Check
 * on the PUSCH Data was successful or not.
 * @details This primitive carries CRC indication for a list of UEs. This
 * is utilized in the scenario where MAC requested the reception of uplink data
 * for a particular UE. On reception of the PUSCH data, the CRC check on it
 * failed. This CRC failure is indicated to MAC, which would utillize this
 * information for further scheduling. 
 * Physical layer would indicate failure or success for each PUSCH transmission.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param crcInd Pointer to the TfuCrcIndInfo.
 * @return ROK/RFAILED
 */
EXTERN S16 PtUiTfuCrcInd ARGS((Pst * pst, SuId suId, TfuCrcIndInfo * crcIndInfo));
/** @brief This API is used to indicate a Timing Advance from PHY to Scheduler .
 * @details This primitive carries timing advance information for a number of
 * UEs that may need timing advance. Timing advance information is an estimate
 * of the timing adjustment that a UE would need to apply in order to be
 * synchronized in uplink. This estimate is to be calculated by physical layer. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param timingAdvInd Pointer to the TfuTimingAdvIndInfo structure.
 * @return ROK/RFAILED
 */
EXTERN S16 PtUiTfuTimingAdvInd ARGS((Pst * pst, SuId suId, TfuTimingAdvIndInfo * timingAdvInd));
/** @brief This API is the TTI indication from PHY to MAC . 
 * @details This primitive provides the timing information (SFN and subframe)
 * which is currently running on the physical layer. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param ttiInd Pointer to the TfuTtiIndInfo.
 * @return ROK/RFAILED
 */
EXTERN S16 PtUiTfuTtiInd ARGS((Pst * pst, SuId suId, TfuTtiIndInfo * ttiInd));

/** @brief This API is the Error indication from PHY to scheduler. 
 * @details This primitive provides the timing information (SFN and subframe)
 * for which LAA transmission failed. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param errInd Pointer to the TfuTtiIndInfo.
 * @return ROK/RFAILED
 */
EXTERN S16 PtUiTfuErrInd ARGS((Pst * pst, SuId suId, TfuErrIndInfo * errInd));
/** @brief This API is the TTI indication from PHY to scheduler. 
 * @details This primitive provides the timing information (SFN and subframe)
 * which is currently running on the physical layer. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param ttiInd Pointer to the TfuTtiIndInfo.
 * @return ROK/RFAILED
 */
EXTERN S16 PtUiTfuSchTtiInd ARGS((Pst * pst, SuId suId, TfuTtiIndInfo * ttiInd));
/** @brief This API is used to indicate the reception of CQI report from PHY to
 * Scheduler, also carries the RI.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param dlCqiInd Pointer to the TfuDlCqiIndInfo structure.
 * @return ROK/RFAILED
 */
EXTERN S16 PtUiTfuDlCqiInd ARGS((Pst * pst, SuId suId, TfuDlCqiIndInfo * dlCqiInd));
/* rg009.201. Added changes of TFU_UPGRADE */
#ifdef TFU_UPGRADE
/** @brief This API is used to indicate the reception of a Raw CQI report from PHY to
 * Scheduler, also carries the RI.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param rawCqiInd Pointer to the TfuRawCqiIndInfo structure.
 * @return ROK/RFAILED
 */
EXTERN S16 PtUiTfuRawCqiInd ARGS((Pst * pst, SuId suId, TfuRawCqiIndInfo* rawCqiInd));

/** @brief This API is used to indicate the reception of a UL SRS report from PHY to
 * Scheduler.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param srsInd Pointer to the TfuSrsIndInfo structure.
 * @return ROK/RFAILED
 */
EXTERN S16 PtUiTfuSrsInd ARGS((Pst * pst, SuId suId, TfuSrsIndInfo* srsInd));
#endif /* TFU_UPGRADE */

#ifdef LTEMAC_MIMO
/** @brief This API is used to indicate the calculated DOA value from PHY to
 * Scheduler.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param doaInd Pointer to the TfuDoaIndInfo structure.
 * @return ROK/RFAILED
 */
EXTERN S16 PtUiTfuDoaInd ARGS((Pst * pst, SuId suId, TfuDoaIndInfo * doaInd));
#endif
/** @brief This Primitive is used to convey PUCCH Delta power calculated by the
 * Physical layer.
 * This information is utilized by Scheduler for power control. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param  Pointer to the TfuPucchDeltaPwrIndInfo structure.
 * @return ROK/RFAILED
 */
EXTERN S16 PtUiTfuPucchDeltaPwr ARGS((Pst * pst, SuId suId, TfuPucchDeltaPwrIndInfo * pucchDeltaPwr));
#endif /*--#ifdef PTTFUITFU--*/

/** @brief This API is used to receive a Bind Confirm from PHY to MAC.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param status Status of the bind request.
 * @return ROK/RFAILED
 */
PRIVATE CONSTANT TfuBndCfm TfUiTfuBndCfmMt[TF_MAX_TFU_USR] =
{
#ifdef LCTFUITFU
   cmPkTfuBndCfm,
#else
   PtUiTfuBndCfm,
#endif
#ifdef RG
   RgLiTfuBndCfm,
#else
   PtUiTfuBndCfm,
#endif
#ifdef LWLCTFUITFU
   cmPkTfuBndCfm
#else
   PtUiTfuBndCfm
#endif
};

/** @brief This API is used to receive a Bind Confirm from PHY to Scheduler.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param status Status of the bind request.
 * @return ROK/RFAILED
 */
PRIVATE CONSTANT TfuSchBndCfm TfUiTfuSchBndCfmMt[TF_MAX_TFU_USR] =
{
#ifdef LCTFUITFU
   cmPkTfuSchBndCfm,
#else
   PtUiTfuSchBndCfm,
#endif
#ifdef RG
   RgLiTfuSchBndCfm,
#else
   PtUiTfuSchBndCfm,
#endif
#ifdef LWLCTFUITFU
   cmPkTfuSchBndCfm
#else
   PtUiTfuSchBndCfm
#endif
};

/** @brief This API is used to indication Random Access Request reception from
 * PHY to Scheduler.
 * @details This primitive is used by physical layer to indicate the reception
 * of a Random Access Request from a set of UEs. The information passed consists
 * of the RA-RNTI and the list of preambles received. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param raReqInd Pointer to the TfuRaReqIndInfo structure.
 * @return ROK/RFAILED
 */
PRIVATE CONSTANT TfuRaReqInd TfUiTfuRaReqIndMt[TF_MAX_TFU_USR] =
{
#ifdef LCTFUITFU
   cmPkTfuRaReqInd,
#else
   PtUiTfuRaReqInd,
#endif
#ifdef RG
   RgLiTfuRaReqInd,
#else
   PtUiTfuRaReqInd,
#endif
#ifdef LWLCTFUITFU
   cmPkTfuRaReqInd
#else
   PtUiTfuRaReqInd
#endif
};

/** @brief This Primitive carries the Data PDUs from PHY to MAC.
 * @details The uplink Data i.e. the data transmitted by the UEs received by the
 * physical layer at the eNodeB in the subframe (indicated by the timingInfo),
 * is relayed to MAC using this primitive. 
 * @param pst 
 * @param spId
 * @param tfuDatInd pointer to TfuDatIndInfo
 * @return 
 */
PRIVATE CONSTANT TfuDatInd TfUiTfuDatIndMt[TF_MAX_TFU_USR] =
{
#ifdef LCTFUITFU
   cmPkTfuDatInd,
#else
   PtUiTfuDatInd,
#endif
#ifdef RG
   RgLiTfuDatInd,
#else
   PtUiTfuDatInd,
#endif
#ifdef LWLCTFUITFU
   cmPkTfuDatInd
#else
   PtUiTfuDatInd
#endif
};

/** @brief This Primitive carries the HARQ Feedback from PHY to scheduler
 * @details HARQ feedback is sent by the UE to the eNodeB, an ACK is sent if UE
 * could successfully recieve the data transmitted by the eNodeB, else a NACK is
 * sent. This feedback is utilized by MAC for further scheduling, for instance
 * it could schedule an adaptive retransmission of the same data. 
 * @param pst 
 * @param spId
 * @param tfuHqInd pointer to TfuHqIndInfo
 * @return 
 */
PRIVATE CONSTANT TfuHqInd TfUiTfuHqIndMt[TF_MAX_TFU_USR] =
{
#ifdef LCTFUITFU
   cmPkTfuHqInd,
#else
   PtUiTfuHqInd,
#endif
#ifdef RG
   RgLiTfuHqInd,
#else
   PtUiTfuHqInd,
#endif
#ifdef LWLCTFUITFU
   cmPkTfuHqInd
#else
   PtUiTfuHqInd
#endif
};

/** @brief This Primitive carries the SR Indication from PHY to scheduler. 
 * @details Scheduling Request (SR) is sent by the UE to the eNodeB to request
 * for Uplink (UL) grant. This primitive carries a list of SRs for a number of
 * UEs received in the indicated subframe. 
 * @param pst 
 * @param spId
 * @param tfqSrInd pointer to TfuSrIndInfo
 * @return 
 */
PRIVATE CONSTANT TfuSrInd TfUiTfuSrIndMt[TF_MAX_TFU_USR] =
{
#ifdef LCTFUITFU
   cmPkTfuSrInd,
#else
   PtUiTfuSrInd,
#endif
#ifdef RG
   RgLiTfuSrInd,
#else
   PtUiTfuSrInd,
#endif
#ifdef LWLCTFUITFU
   cmPkTfuSrInd
#else
   PtUiTfuSrInd
#endif
};

/** @brief This API is used to indicate CQI reporting from PHY to Scheduler
 * @details This primitive carries an estimate of the uplink Channel quality
 * index (CQI) for a list of UEs. This is an extimate of the uplink channel
 * quality i.e. the transmission from UE as calculated at the Physical layer at
 * the eNodeB. 
 * It carries a list of subband CQIs for each UE. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param ulCqiInd Pointer to the TfuUlCqiIndInfo structure.
 * @return ROK/RFAILED
 */
PRIVATE CONSTANT TfuUlCqiInd TfUiTfuUlCqiIndMt[TF_MAX_TFU_USR] =
{
#ifdef LCTFUITFU
   cmPkTfuUlCqiInd,
#else
   PtUiTfuUlCqiInd,
#endif
#ifdef RG
   RgLiTfuUlCqiInd,
#else
   PtUiTfuUlCqiInd,
#endif
#ifdef LWLCTFUITFU
   cmPkTfuUlCqiInd
#else
   PtUiTfuUlCqiInd
#endif
};

/** @brief This API is used by the Physical layer to indicate if the CRC Check
 * on the PUSCH Data was successful or not.
 * @details This primitive carries CRC indication for a list of UEs. This
 * is utilized in the scenario where MAC requested the reception of uplink data
 * for a particular UE. On reception of the PUSCH data, the CRC check on it
 * failed. This CRC failure is indicated to MAC, which would utillize this
 * information for further scheduling. 
 * Physical layer would indicate failure or success for each PUSCH transmission.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param crcInd Pointer to the TfuCrcIndInfo.
 * @return ROK/RFAILED
 */
PRIVATE CONSTANT TfuCrcInd TfUiTfuCrcIndMt[TF_MAX_TFU_USR] =
{
#ifdef LCTFUITFU
   cmPkTfuCrcInd,
#else
   PtUiTfuCrcInd,
#endif
#ifdef RG
   RgLiTfuCrcInd,
#else
   PtUiTfuCrcInd,
#endif
#ifdef LWLCTFUITFU
   cmPkTfuCrcInd
#else
   PtUiTfuCrcInd
#endif
};

/** @brief This API is used to indicate a Timing Advance from PHY to Scheduler .
 * @details This primitive carries timing advance information for a number of
 * UEs that may need timing advance. Timing advance information is an estimate
 * of the timing adjustment that a UE would need to apply in order to be
 * synchronized in uplink. This estimate is to be calculated by physical layer. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param timingAdvInd Pointer to the TfuTimingAdvIndInfo structure.
 * @return ROK/RFAILED
 */
PRIVATE CONSTANT TfuTimingAdvInd TfUiTfuTimingAdvIndMt[TF_MAX_TFU_USR] =
{
#ifdef LCTFUITFU
   cmPkTfuTimingAdvInd,
#else
   PtUiTfuTimingAdvInd,
#endif
#ifdef RG
   RgLiTfuTimingAdvInd,
#else
   PtUiTfuTimingAdvInd,
#endif
#ifdef LWLCTFUITFU
   cmPkTfuTimingAdvInd
#else
   PtUiTfuTimingAdvInd
#endif
};

/** @brief This API is the TTI indication from PHY to MAC . 
 * @details This primitive provides the timing information (SFN and subframe)
 * which is currently running on the physical layer. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param ttiInd Pointer to the TfuTtiIndInfo.
 * @return ROK/RFAILED
 */
PRIVATE CONSTANT TfuTtiInd TfUiTfuTtiIndMt[TF_MAX_TFU_USR] =
{
#ifdef LCTFUITFU
   cmPkTfuTtiInd,
#else
   PtUiTfuTtiInd,
#endif
#ifdef RG
   RgLiTfuTtiInd,
#else
   PtUiTfuTtiInd,
#endif
#ifdef LWLCTFUITFU
   cmPkTfuTtiInd
#else
   PtUiTfuTtiInd
#endif
};

/** @brief This API is the TTI indication from PHY to scheduler. 
 * @details This primitive provides the timing information (SFN and subframe)
 * which is currently running on the physical layer. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param ttiInd Pointer to the TfuTtiIndInfo.
 * @return ROK/RFAILED
 */
PRIVATE CONSTANT TfuSchTtiInd TfUiTfuSchTtiIndMt[TF_MAX_TFU_USR] =
{
#ifdef LCTFUITFU
   cmPkTfuSchTtiInd,
#else
   PtUiTfuSchTtiInd,
#endif
#ifdef RG
   RgLiTfuSchTtiInd,
#else
   PtUiTfuSchTtiInd,
#endif
#ifdef LWLCTFUITFU
   cmPkTfuSchTtiInd
#else
   PtUiTfuSchTtiInd
#endif
};

/** @brief This API is the Error indication from PHY to scheduler. 
 * @details This primitive provides the timing information (SFN and subframe)
 * for which LAA transmission failed. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param errInd Pointer to the TfuTtiIndInfo.
 * @return ROK/RFAILED
 */
PRIVATE CONSTANT TfuErrInd TfUiTfuErrIndMt[TF_MAX_TFU_USR] =
{
#ifdef LCTFUITFU
   cmPkTfuErrInd,
#else
   PtUiTfuErrInd,
#endif
#ifdef RG
   RgLiTfuErrInd,
#else
   PtUiTfuErrInd,
#endif
#ifdef LWLCTFUITFU
   cmPkTfuErrInd
#else
   PtUiTfuErrInd
#endif
};

/** @brief This API is used to indicate the reception of CQI report from PHY to
 * Scheduler, also carries the RI.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param dlCqiInd Pointer to the TfuDlCqiIndInfo structure.
 * @return ROK/RFAILED
 */
PRIVATE CONSTANT TfuDlCqiInd TfUiTfuDlCqiIndMt[TF_MAX_TFU_USR] =
{
#ifdef LCTFUITFU
   cmPkTfuDlCqiInd,
#else
   PtUiTfuDlCqiInd,
#endif
#ifdef RG
   RgLiTfuDlCqiInd,
#else
   PtUiTfuDlCqiInd,
#endif
#ifdef LWLCTFUITFU
   cmPkTfuDlCqiInd
#else
   PtUiTfuDlCqiInd
#endif
};
/* rg009.201. Added changes of TFU_UPGRADE */
#ifdef TFU_UPGRADE
/** @brief This API is used to indicate the reception of Raw CQI report from PHY to
 * Scheduler, also carries the RI.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param rawCqiInd Pointer to the TfuRawCqiIndInfo structure.
 * @return ROK/RFAILED
 */
PRIVATE CONSTANT TfuRawCqiInd TfUiTfuRawCqiIndMt[TF_MAX_TFU_USR] =
{
#ifdef LCTFUITFU
   cmPkTfuRawCqiInd,
#else
   PtUiTfuRawCqiInd,
#endif
#ifdef RG
   RgLiTfuRawCqiInd,
#else
   PtUiTfuRawCqiInd,
#endif
#ifdef LWLCTFUITFU
   cmPkTfuRawCqiInd
#else
   PtUiTfuRawCqiInd
#endif
};

/** @brief This API is used to indicate the reception of UL SRS report from PHY to
 * Scheduler.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param srsInd Pointer to the TfuSrsIndInfo structure.
 * @return ROK/RFAILED
 */
PRIVATE CONSTANT TfuSrsInd TfUiTfuSrsIndMt[TF_MAX_TFU_USR] =
{
#ifdef LCTFUITFU
   cmPkTfuSrsInd,
#else
   PtUiTfuSrsInd,
#endif
#ifdef RG
   RgLiTfuSrsInd,
#else
   PtUiTfuSrsInd,
#endif
#ifdef LWLCTFUITFU
   cmPkTfuSrsInd
#else
   PtUiTfuSrsInd
#endif
};
#endif /*TFU_UPGRADE */ 

#ifdef LTEMAC_MIMO
/** @brief This API is used to indicate the Calculated DOA value from PHY to
 * Scheduler
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param doaInd Pointer to the TfuDoaIndInfo structure.
 * @return ROK/RFAILED
 */
PRIVATE CONSTANT TfuDoaInd TfUiTfuDoaIndMt[TF_MAX_TFU_USR] =
{
#ifdef LCTFUITFU
   cmPkTfuDoaInd,
#else
   PtUiTfuDoaInd,
#endif
#ifdef RG
   RgLiTfuDoaInd,
#else
   PtUiTfuDoaInd,
#endif
#ifdef LWLCTFUITFU
   cmPkTfuDoaInd
#else
   PtUiTfuDoaInd
#endif
};
#endif

/** @brief This Primitive is used to convey PUCCH Delta power calculated by the
 * Physical layer.
 * This information is utilized by Scheduler for power control. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param  Pointer to the TfuPucchDeltaPwrIndInfo structure.
 * @return ROK/RFAILED
 */
PRIVATE CONSTANT TfuPucchDeltaPwrInd TfUiTfuPucchDeltaPwrMt[TF_MAX_TFU_USR] =
{
#ifdef LCTFUITFU
   cmPkTfuPucchDeltaPwr,
#else
   PtUiTfuPucchDeltaPwr,
#endif
#ifdef RG
   RgLiTfuPucchDeltaPwrInd,
#else
   PtUiTfuPucchDeltaPwr,
#endif
#ifdef LWLCTFUITFU
   cmPkTfuPucchDeltaPwr
#else
   PtUiTfuPucchDeltaPwr
#endif
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#ifdef TF



/***********************************************************
*
*     Func : TfUiTfuBndCfm
*
*
*     Desc : This API is used to receive a Bind Confirm from PHY to MAC.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param status Status of the bind request.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 TfUiTfuBndCfm
(
Pst * pst,
SuId suId,
U8 status
)
#else
PUBLIC S16 TfUiTfuBndCfm(pst, suId, status)
Pst * pst;
SuId suId;
U8 status;
#endif
{

   TRC3(TfUiTfuBndCfm)

   RETVALUE((*TfUiTfuBndCfmMt[pst->selector])(pst, suId, status));

}



/***********************************************************
*
*     Func : TfUiTfuSchBndCfm
*
*
*     Desc : This API is used to receive a Bind Confirm from PHY to Scheduler.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param status Status of the bind request.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 TfUiTfuSchBndCfm
(
Pst * pst,
SuId suId,
U8 status
)
#else
PUBLIC S16 TfUiTfuSchBndCfm(pst, suId, status)
Pst * pst;
SuId suId;
U8 status;
#endif
{

   TRC3(TfUiTfuSchBndCfm)

   RETVALUE((*TfUiTfuSchBndCfmMt[pst->selector])(pst, suId, status));

}



/***********************************************************
*
*     Func : TfUiTfuRaReqInd
*
*
*     Desc : This API is used to indication Random Access Request reception from
 * PHY to Scheduler.
 * @details This primitive is used by physical layer to indicate the reception
 * of a Random Access Request from a set of UEs. The information passed consists
 * of the RA-RNTI and the list of preambles received. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param raReqInd Pointer to the TfuRaReqIndInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 TfUiTfuRaReqInd
(
Pst * pst,
SuId suId,
TfuRaReqIndInfo * raReqInd
)
#else
PUBLIC S16 TfUiTfuRaReqInd(pst, suId, raReqInd)
Pst * pst;
SuId suId;
TfuRaReqIndInfo * raReqInd;
#endif
{

   TRC3(TfUiTfuRaReqInd)

   RETVALUE((*TfUiTfuRaReqIndMt[pst->selector])(pst, suId, raReqInd));

}



/***********************************************************
*
*     Func : TfUiTfuDatInd
*
*
*     Desc : This Primitive carries the Data PDUs from PHY to MAC.
 * @details The uplink Data i.e. the data transmitted by the UEs received by the
 * physical layer at the eNodeB in the subframe (indicated by the timingInfo),
 * is relayed to MAC using this primitive. 
 * @param pst 
 * @param spId
 * @param tfuDatInd pointer to TfuDatIndInfo
 * @return
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 TfUiTfuDatInd
(
Pst * pst,
SuId suId,
TfuDatIndInfo * datInd
)
#else
PUBLIC S16 TfUiTfuDatInd(pst, suId, datInd)
Pst * pst;
SuId suId;
TfuDatIndInfo * datInd;
#endif
{

   TRC3(TfUiTfuDatInd)

   RETVALUE((*TfUiTfuDatIndMt[pst->selector])(pst, suId, datInd));

}



/***********************************************************
*
*     Func : TfUiTfuHqInd
*
*
*     Desc : This Primitive carries the HARQ Feedback from PHY to scheduler
 * @details HARQ feedback is sent by the UE to the eNodeB, an ACK is sent if UE
 * could successfully recieve the data transmitted by the eNodeB, else a NACK is
 * sent. This feedback is utilized by MAC for further scheduling, for instance
 * it could schedule an adaptive retransmission of the same data. 
 * @param pst 
 * @param spId
 * @param tfuHqInd pointer to TfuHqIndInfo
 * @return
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 TfUiTfuHqInd
(
Pst * pst,
SuId suId,
TfuHqIndInfo * hqInd
)
#else
PUBLIC S16 TfUiTfuHqInd(pst, suId, hqInd)
Pst * pst;
SuId suId;
TfuHqIndInfo * hqInd;
#endif
{

   TRC3(TfUiTfuHqInd)

   RETVALUE((*TfUiTfuHqIndMt[pst->selector])(pst, suId, hqInd));

}



/***********************************************************
*
*     Func : TfUiTfuSrInd
*
*
*     Desc : This Primitive carries the SR Indication from PHY to scheduler. 
 * @details Scheduling Request (SR) is sent by the UE to the eNodeB to request
 * for Uplink (UL) grant. This primitive carries a list of SRs for a number of
 * UEs received in the indicated subframe. 
 * @param pst 
 * @param spId
 * @param tfqSrInd pointer to TfuSrIndInfo
 * @return
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 TfUiTfuSrInd
(
Pst * pst,
SuId suId,
TfuSrIndInfo * srInd
)
#else
PUBLIC S16 TfUiTfuSrInd(pst, suId, srInd)
Pst * pst;
SuId suId;
TfuSrIndInfo * srInd;
#endif
{

   TRC3(TfUiTfuSrInd)

   RETVALUE((*TfUiTfuSrIndMt[pst->selector])(pst, suId, srInd));

}



/***********************************************************
*
*     Func : TfUiTfuUlCqiInd
*
*
*     Desc : This API is used to indicate CQI reporting from PHY to Scheduler
 * @details This primitive carries an estimate of the uplink Channel quality
 * index (CQI) for a list of UEs. This is an extimate of the uplink channel
 * quality i.e. the transmission from UE as calculated at the Physical layer at
 * the eNodeB. 
 * It carries a list of subband CQIs for each UE. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param ulCqiInd Pointer to the TfuUlCqiIndInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 TfUiTfuUlCqiInd
(
Pst * pst,
SuId suId,
TfuUlCqiIndInfo * ulCqiInd
)
#else
PUBLIC S16 TfUiTfuUlCqiInd(pst, suId, ulCqiInd)
Pst * pst;
SuId suId;
TfuUlCqiIndInfo * ulCqiInd;
#endif
{

   TRC3(TfUiTfuUlCqiInd)

   RETVALUE((*TfUiTfuUlCqiIndMt[pst->selector])(pst, suId, ulCqiInd));

}



/***********************************************************
*
*     Func : TfUiTfuCrcInd
*
*
*     Desc : This API is used by the Physical layer to indicate if the CRC Check
 * on the PUSCH Data was successful or not.
 * @details This primitive carries CRC indication for a list of UEs. This
 * is utilized in the scenario where MAC requested the reception of uplink data
 * for a particular UE. On reception of the PUSCH data, the CRC check on it
 * failed. This CRC failure is indicated to MAC, which would utillize this
 * information for further scheduling. 
 * Physical layer would indicate failure or success for each PUSCH transmission.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param crcInd Pointer to the TfuCrcIndInfo.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 TfUiTfuCrcInd
(
Pst * pst,
SuId suId,
TfuCrcIndInfo * crcIndInfo
)
#else
PUBLIC S16 TfUiTfuCrcInd(pst, suId, crcIndInfo)
Pst * pst;
SuId suId;
TfuCrcIndInfo * crcIndInfo;
#endif
{

   TRC3(TfUiTfuCrcInd)

   RETVALUE((*TfUiTfuCrcIndMt[pst->selector])(pst, suId, crcIndInfo));

}



/***********************************************************
*
*     Func : TfUiTfuTimingAdvInd
*
*
*     Desc : This API is used to indicate a Timing Advance from PHY to Scheduler .
 * @details This primitive carries timing advance information for a number of
 * UEs that may need timing advance. Timing advance information is an estimate
 * of the timing adjustment that a UE would need to apply in order to be
 * synchronized in uplink. This estimate is to be calculated by physical layer. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param timingAdvInd Pointer to the TfuTimingAdvIndInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 TfUiTfuTimingAdvInd
(
Pst * pst,
SuId suId,
TfuTimingAdvIndInfo * timingAdvInd
)
#else
PUBLIC S16 TfUiTfuTimingAdvInd(pst, suId, timingAdvInd)
Pst * pst;
SuId suId;
TfuTimingAdvIndInfo * timingAdvInd;
#endif
{

   TRC3(TfUiTfuTimingAdvInd)

   RETVALUE((*TfUiTfuTimingAdvIndMt[pst->selector])(pst, suId, timingAdvInd));

}



/***********************************************************
*
*     Func : TfUiTfuTtiInd
*
*
*     Desc : This API is the TTI indication from PHY to MAC . 
 * @details This primitive provides the timing information (SFN and subframe)
 * which is currently running on the physical layer. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param ttiInd Pointer to the TfuTtiIndInfo.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 TfUiTfuTtiInd
(
Pst * pst,
SuId suId,
TfuTtiIndInfo * ttiInd
)
#else
PUBLIC S16 TfUiTfuTtiInd(pst, suId, ttiInd)
Pst * pst;
SuId suId;
TfuTtiIndInfo * ttiInd;
#endif
{

   TRC3(TfUiTfuTtiInd)

   RETVALUE((*TfUiTfuTtiIndMt[pst->selector])(pst, suId, ttiInd));

}



/***********************************************************
*
*     Func : TfUiTfuSchTtiInd
*
*
*     Desc : This API is the TTI indication from PHY to scheduler. 
 * @details This primitive provides the timing information (SFN and subframe)
 * which is currently running on the physical layer. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param ttiInd Pointer to the TfuTtiIndInfo.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 TfUiTfuSchTtiInd
(
Pst * pst,
SuId suId,
TfuTtiIndInfo * ttiInd
)
#else
PUBLIC S16 TfUiTfuSchTtiInd(pst, suId, ttiInd)
Pst * pst;
SuId suId;
TfuTtiIndInfo * ttiInd;
#endif
{

   TRC3(TfUiTfuSchTtiInd)

   RETVALUE((*TfUiTfuSchTtiIndMt[pst->selector])(pst, suId, ttiInd));

}


/***********************************************************
*
*     Func : TfUiTfuErrInd
*
*
*  @brief This API is the Error indication from PHY to scheduler. 
* @details This primitive provides the timing information (SFN and subframe)
* for which LAA transmission failed. 
* @param pst Pointer to the post structure.
* @param suId SAP ID of the service user.
* @param errInd Pointer to the TfuErrIndInfo.
* @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 TfUiTfuErrInd
(
Pst * pst,
SuId suId,
TfuErrIndInfo * errInd
)
#else
PUBLIC S16 TfUiTfuErrInd(pst, suId, errInd)
Pst * pst;
SuId suId;
TfuErrIndInfo * errInd;
#endif
{

   TRC3(TfUiTfuErrInd)

   RETVALUE((*TfUiTfuErrIndMt[pst->selector])(pst, suId, errInd));

}

/* rg007.201 - Changes for MIMO feature addition */
#ifdef LTEMAC_MIMO
/***********************************************************
*
*     Func : TfUiTfuDoaInd
*
*
*     Desc : This API is used to indicate the caculated DOA value report from PHY to
 * Scheduler, also carries the RI.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param doaInd Pointer to the TfuDoaIndInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 TfUiTfuDoaInd
(
Pst * pst,
SuId suId,
TfuDoaIndInfo * doaInd
)
#else
PUBLIC S16 TfUiTfuDoaInd(pst, suId, doaInd)
Pst * pst;
SuId suId;
TfuDoaIndInfo * doaInd;
#endif
{

   TRC3(TfUiTfuDoaInd)

   RETVALUE((*TfUiTfuDoaIndMt[pst->selector])(pst, suId, doaInd));

}
#endif

/***********************************************************
*
*     Func : TfUiTfuDlCqiInd
*
*
*     Desc : This API is used to indicate the reception of CQI report from PHY to
 * Scheduler, also carries the RI.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param dlCqiInd Pointer to the TfuDlCqiIndInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 TfUiTfuDlCqiInd
(
Pst * pst,
SuId suId,
TfuDlCqiIndInfo * dlCqiInd
)
#else
PUBLIC S16 TfUiTfuDlCqiInd(pst, suId, dlCqiInd)
Pst * pst;
SuId suId;
TfuDlCqiIndInfo * dlCqiInd;
#endif
{

   TRC3(TfUiTfuDlCqiInd)

   RETVALUE((*TfUiTfuDlCqiIndMt[pst->selector])(pst, suId, dlCqiInd));

}

/* rg009.201. Added changes of TFU_UPGRADE */
#ifdef TFU_UPGRADE
/***********************************************************
*
*     Func : TfUiTfuRawCqiInd
*
*
*     Desc : This API is used to indicate the reception of Raw CQI report from PHY to
 * Scheduler, also carries the RI.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param rawCqiInd Pointer to the TfuRawCqiIndInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 TfUiTfuRawCqiInd
(
Pst * pst,
SuId suId,
TfuRawCqiIndInfo *rawCqiInd
)
#else
PUBLIC S16 TfUiTfuRawCqiInd(pst, suId, rawCqiInd)
Pst * pst;
SuId suId;
TfuRawCqiIndInfo *rawCqiInd;
#endif
{

   TRC3(TfUiTfuRawCqiInd)

   RETVALUE((*TfUiTfuRawCqiIndMt[pst->selector])(pst, suId, rawCqiInd));

}

/***********************************************************
*
*     Func : TfUiTfuSrsInd
*
*
*     Desc : This API is used to indicate the reception of UL SRS report from PHY to
 * Scheduler.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param rawCqiInd Pointer to the TfuRawCqiIndInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 TfUiTfuSrsInd
(
Pst * pst,
SuId suId,
TfuSrsIndInfo *srsInd
)
#else
PUBLIC S16 TfUiTfuSrsInd(pst, suId, srsInd)
Pst * pst;
SuId suId;
TfuSrsIndInfo *srsInd;
#endif
{

   TRC3(TfUiTfuSrsInd)

   RETVALUE((*TfUiTfuSrsIndMt[pst->selector])(pst, suId, srsInd));

}
#endif 

/***********************************************************
*
*     Func : TfUiTfuPucchDeltaPwr
*
*
*     Desc : This Primitive is used to convey PUCCH Delta power calculated by the
 * Physical layer.
 * This information is utilized by Scheduler for power control. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param  Pointer to the TfuPucchDeltaPwrIndInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 TfUiTfuPucchDeltaPwrInd
(
Pst * pst,
SuId suId,
TfuPucchDeltaPwrIndInfo * pucchDeltaPwr
)
#else
PUBLIC S16 TfUiTfuPucchDeltaPwrInd(pst, suId, pucchDeltaPwr)
Pst * pst;
SuId suId;
TfuPucchDeltaPwrIndInfo * pucchDeltaPwr;
#endif
{

   TRC3(TfUiTfuPucchDeltaPwrInd)

   RETVALUE((*TfUiTfuPucchDeltaPwrMt[pst->selector])(pst, suId, pucchDeltaPwr));

}


#endif /*--ifdef TF--*/

#ifdef PTTFUITFU



/***********************************************************
*
*     Func : PtUiTfuBndCfm
*
*
*     Desc : This API is used to receive a Bind Confirm from PHY to MAC.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param status Status of the bind request.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 PtUiTfuBndCfm
(
Pst * pst,
SuId suId,
U8 status
)
#else
PUBLIC S16 PtUiTfuBndCfm(pst, suId, status)
Pst * pst;
SuId suId;
U8 status;
#endif
{

   TRC3(PtUiTfuBndCfm)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(status);

   RETVALUE(ROK);

}



/***********************************************************
*
*     Func : PtUiTfuSchBndCfm
*
*
*     Desc : This API is used to receive a Bind Confirm from PHY to Scheduler.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param status Status of the bind request.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 PtUiTfuSchBndCfm
(
Pst * pst,
SuId suId,
U8 status
)
#else
PUBLIC S16 PtUiTfuSchBndCfm(pst, suId, status)
Pst * pst;
SuId suId;
U8 status;
#endif
{

   TRC3(PtUiTfuSchBndCfm)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(status);

   RETVALUE(ROK);

}



/***********************************************************
*
*     Func : PtUiTfuRaReqInd
*
*
*     Desc : This API is used to indication Random Access Request reception from
 * PHY to Scheduler.
 * @details This primitive is used by physical layer to indicate the reception
 * of a Random Access Request from a set of UEs. The information passed consists
 * of the RA-RNTI and the list of preambles received. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param raReqInd Pointer to the TfuRaReqIndInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 PtUiTfuRaReqInd
(
Pst * pst,
SuId suId,
TfuRaReqIndInfo * raReqInd
)
#else
PUBLIC S16 PtUiTfuRaReqInd(pst, suId, raReqInd)
Pst * pst;
SuId suId;
TfuRaReqIndInfo * raReqInd;
#endif
{

   TRC3(PtUiTfuRaReqInd)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(raReqInd);

   RETVALUE(ROK);

}



/***********************************************************
*
*     Func : PtUiTfuDatInd
*
*
*     Desc : This Primitive carries the Data PDUs from PHY to MAC.
 * @details The uplink Data i.e. the data transmitted by the UEs received by the
 * physical layer at the eNodeB in the subframe (indicated by the timingInfo),
 * is relayed to MAC using this primitive. 
 * @param pst 
 * @param spId
 * @param tfuDatInd pointer to TfuDatIndInfo
 * @return
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 PtUiTfuDatInd
(
Pst * pst,
SuId suId,
TfuDatIndInfo * datInd
)
#else
PUBLIC S16 PtUiTfuDatInd(pst, suId, datInd)
Pst * pst;
SuId suId;
TfuDatIndInfo * datInd;
#endif
{

   TRC3(PtUiTfuDatInd)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(datInd);

   RETVALUE(ROK);

}



/***********************************************************
*
*     Func : PtUiTfuHqInd
*
*
*     Desc : This Primitive carries the HARQ Feedback from PHY to scheduler
 * @details HARQ feedback is sent by the UE to the eNodeB, an ACK is sent if UE
 * could successfully recieve the data transmitted by the eNodeB, else a NACK is
 * sent. This feedback is utilized by MAC for further scheduling, for instance
 * it could schedule an adaptive retransmission of the same data. 
 * @param pst 
 * @param spId
 * @param tfuHqInd pointer to TfuHqIndInfo
 * @return
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 PtUiTfuHqInd
(
Pst * pst,
SuId suId,
TfuHqIndInfo * hqInd
)
#else
PUBLIC S16 PtUiTfuHqInd(pst, suId, hqInd)
Pst * pst;
SuId suId;
TfuHqIndInfo * hqInd;
#endif
{

   TRC3(PtUiTfuHqInd)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(hqInd);

   RETVALUE(ROK);

}



/***********************************************************
*
*     Func : PtUiTfuSrInd
*
*
*     Desc : This Primitive carries the SR Indication from PHY to scheduler. 
 * @details Scheduling Request (SR) is sent by the UE to the eNodeB to request
 * for Uplink (UL) grant. This primitive carries a list of SRs for a number of
 * UEs received in the indicated subframe. 
 * @param pst 
 * @param spId
 * @param tfqSrInd pointer to TfuSrIndInfo
 * @return
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 PtUiTfuSrInd
(
Pst * pst,
SuId suId,
TfuSrIndInfo * srInd
)
#else
PUBLIC S16 PtUiTfuSrInd(pst, suId, srInd)
Pst * pst;
SuId suId;
TfuSrIndInfo * srInd;
#endif
{

   TRC3(PtUiTfuSrInd)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(srInd);

   RETVALUE(ROK);

}



/***********************************************************
*
*     Func : PtUiTfuUlCqiInd
*
*
*     Desc : This API is used to indicate CQI reporting from PHY to Scheduler
 * @details This primitive carries an estimate of the uplink Channel quality
 * index (CQI) for a list of UEs. This is an extimate of the uplink channel
 * quality i.e. the transmission from UE as calculated at the Physical layer at
 * the eNodeB. 
 * It carries a list of subband CQIs for each UE. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param ulCqiInd Pointer to the TfuUlCqiIndInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 PtUiTfuUlCqiInd
(
Pst * pst,
SuId suId,
TfuUlCqiIndInfo * ulCqiInd
)
#else
PUBLIC S16 PtUiTfuUlCqiInd(pst, suId, ulCqiInd)
Pst * pst;
SuId suId;
TfuUlCqiIndInfo * ulCqiInd;
#endif
{

   TRC3(PtUiTfuUlCqiInd)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(ulCqiInd);

   RETVALUE(ROK);

}



/***********************************************************
*
*     Func : PtUiTfuCrcInd
*
*
*     Desc : This API is used by the Physical layer to indicate if the CRC Check
 * on the PUSCH Data was successful or not.
 * @details This primitive carries CRC indication for a list of UEs. This
 * is utilized in the scenario where MAC requested the reception of uplink data
 * for a particular UE. On reception of the PUSCH data, the CRC check on it
 * failed. This CRC failure is indicated to MAC, which would utillize this
 * information for further scheduling. 
 * Physical layer would indicate failure or success for each PUSCH transmission.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param crcInd Pointer to the TfuCrcIndInfo.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 PtUiTfuCrcInd
(
Pst * pst,
SuId suId,
TfuCrcIndInfo * crcIndInfo
)
#else
PUBLIC S16 PtUiTfuCrcInd(pst, suId, crcIndInfo)
Pst * pst;
SuId suId;
TfuCrcIndInfo * crcIndInfo;
#endif
{

   TRC3(PtUiTfuCrcInd)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(crcIndInfo);

   RETVALUE(ROK);

}



/***********************************************************
*
*     Func : PtUiTfuTimingAdvInd
*
*
*     Desc : This API is used to indicate a Timing Advance from PHY to Scheduler .
 * @details This primitive carries timing advance information for a number of
 * UEs that may need timing advance. Timing advance information is an estimate
 * of the timing adjustment that a UE would need to apply in order to be
 * synchronized in uplink. This estimate is to be calculated by physical layer. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param timingAdvInd Pointer to the TfuTimingAdvIndInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 PtUiTfuTimingAdvInd
(
Pst * pst,
SuId suId,
TfuTimingAdvIndInfo * timingAdvInd
)
#else
PUBLIC S16 PtUiTfuTimingAdvInd(pst, suId, timingAdvInd)
Pst * pst;
SuId suId;
TfuTimingAdvIndInfo * timingAdvInd;
#endif
{

   TRC3(PtUiTfuTimingAdvInd)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(timingAdvInd);

   RETVALUE(ROK);

}



/***********************************************************
*
*     Func : PtUiTfuTtiInd
*
*
*     Desc : This API is the TTI indication from PHY to MAC . 
 * @details This primitive provides the timing information (SFN and subframe)
 * which is currently running on the physical layer. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param ttiInd Pointer to the TfuTtiIndInfo.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 PtUiTfuTtiInd
(
Pst * pst,
SuId suId,
TfuTtiIndInfo * ttiInd
)
#else
PUBLIC S16 PtUiTfuTtiInd(pst, suId, ttiInd)
Pst * pst;
SuId suId;
TfuTtiIndInfo * ttiInd;
#endif
{

   TRC3(PtUiTfuTtiInd)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(ttiInd);

   RETVALUE(ROK);

}



/***********************************************************
*
*     Func : PtUiTfuSchTtiInd
*
*
*     Desc : This API is the TTI indication from PHY to scheduler. 
 * @details This primitive provides the timing information (SFN and subframe)
 * which is currently running on the physical layer. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param ttiInd Pointer to the TfuTtiIndInfo.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 PtUiTfuSchTtiInd
(
Pst * pst,
SuId suId,
TfuTtiIndInfo * ttiInd
)
#else
PUBLIC S16 PtUiTfuSchTtiInd(pst, suId, ttiInd)
Pst * pst;
SuId suId;
TfuTtiIndInfo * ttiInd;
#endif
{

   TRC3(PtUiTfuSchTtiInd)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(ttiInd);

   RETVALUE(ROK);

}

/***********************************************************
*
*     Func : PtUiTfuErrInd
*
*
* @brief This API is the Error indication from PHY to scheduler. 
 * @details This primitive provides the timing information (SFN and subframe)
 * for which LAA transmission failed. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param errInd Pointer to the TfuTtiIndInfo.
 * @return ROK/RFAILED
 *
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 PtUiTfuErrInd
(
Pst * pst,
SuId suId,
TfuErrIndInfo * errInd
)
#else
PUBLIC S16 PtUiTfuErrInd(pst, suId, errInd)
Pst * pst;
SuId suId;
TfuErrIndInfo * errInd;
#endif
{

   TRC3(PtUiTfuErrInd)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(errInd);

   RETVALUE(ROK);

}
/* rg007.201 - Changes for MIMO feature addition */
#ifdef LTEMAC_MIMO

/***********************************************************
*
*     Func : PtUiTfuDoaInd
*
*
*     Desc : This API is used to indicate the calculated DOA from PHY to
 * Scheduler.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param doaInd Pointer to the TfuDoaIndInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 PtUiTfuDoaInd
(
Pst * pst,
SuId suId,
TfuDoaIndInfo * doaInd
)
#else
PUBLIC S16 PtUiTfuDoaInd(pst, suId, doaInd)
Pst * pst;
SuId suId;
TfuDoaIndInfo * doaInd;
#endif
{

   TRC3(PtUiTfuDoaInd)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(doaInd);

   RETVALUE(ROK);

}
#endif

/***********************************************************
*
*     Func : PtUiTfuDlCqiInd
*
*
*     Desc : This API is used to indicate the reception of CQI report from PHY to
 * Scheduler, also carries the RI.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param dlCqiInd Pointer to the TfuDlCqiIndInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 PtUiTfuDlCqiInd
(
Pst * pst,
SuId suId,
TfuDlCqiIndInfo * dlCqiInd
)
#else
PUBLIC S16 PtUiTfuDlCqiInd(pst, suId, dlCqiInd)
Pst * pst;
SuId suId;
TfuDlCqiIndInfo * dlCqiInd;
#endif
{

   TRC3(PtUiTfuDlCqiInd)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(dlCqiInd);

   RETVALUE(ROK);

}


/* rg009.201. Added changes of TFU_UPGRADE */
#ifdef TFU_UPGRADE
/***********************************************************
*
*     Func : PtUiTfuRawCqiInd
*
*
*     Desc : This API is used to indicate the reception of Raw CQI report from PHY to
 * Scheduler, also carries the RI.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param rawCqiInd Pointer to the TfuRawCqiIndInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 PtUiTfuRawCqiInd
(
Pst * pst,
SuId suId,
TfuRawCqiIndInfo * rawCqiInd
)
#else
PUBLIC S16 PtUiTfuRawCqiInd(pst, suId, rawCqiInd)
Pst * pst;
SuId suId;
TfuRawCqiIndInfo * rawCqiInd;
#endif
{

   TRC3(PtUiTfuRawCqiInd)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(rawCqiInd);

   RETVALUE(ROK);

}

/***********************************************************
*
*     Func : PtUiTfuSrsInd
*
*
*     Desc : This API is used to indicate the reception of UL SRS report from PHY to
 * Scheduler.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param srsInd Pointer to the TfuSrsIndInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 PtUiTfuSrsInd
(
Pst * pst,
SuId suId,
TfuSrsIndInfo * srsInd
)
#else
PUBLIC S16 PtUiTfuSrsInd(pst, suId, srsInd)
Pst * pst;
SuId suId;
TfuSrsIndInfo * srsInd;
#endif
{

   TRC3(PtUiTfuSrsInd)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(srsInd);

   RETVALUE(ROK);

}

#endif 

/***********************************************************
*
*     Func : PtUiTfuPucchDeltaPwr
*
*
*     Desc : This Primitive is used to convey PUCCH Delta power calculated by the
 * Physical layer.
 * This information is utilized by Scheduler for power control. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param  Pointer to the TfuPucchDeltaPwrIndInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 PtUiTfuPucchDeltaPwr
(
Pst * pst,
SuId suId,
TfuPucchDeltaPwrIndInfo * pucchDeltaPwr
)
#else
PUBLIC S16 PtUiTfuPucchDeltaPwr(pst, suId, pucchDeltaPwr)
Pst * pst;
SuId suId;
TfuPucchDeltaPwrIndInfo * pucchDeltaPwr;
#endif
{

   TRC3(PtUiTfuPucchDeltaPwr)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(pucchDeltaPwr);

   RETVALUE(ROK);

}


#endif /*--ifdef PTTFUITFU--*/


/**********************************************************************
 
         End of file:     tf_ptui.c@@/main/3 - Sat Jul 30 02:22:24 2011
 
**********************************************************************/
 
/**********************************************************************
 
        Notes:
 
**********************************************************************/
 
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     ps              1. Initial Release.
/main/2      ---     ps              1. LTE MAC 2.1 release
           rg007.201   ap  1. Added support for MIMO
           rg009.201   dv  1. Added support for TFU upgrade
/main/3      --        dv              1. LTE MAC 3.1 Release
*********************************************************************91*/
