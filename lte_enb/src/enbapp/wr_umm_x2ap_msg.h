
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_umm_x2ap_msg.h

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/
#ifndef __WR_UMM_X2AP_MSG_H__
#define __WR_UMM_X2AP_MSG_H__

#include "wr.h"
#include "wr_umm.h"

#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */

EXTERN S16 wrX2apFillCause (CztCause *ie, WrUmmMsgCause *cause);
EXTERN S16 wrX2apFillTnlAddr (CztEvnt *evnt, CmTptAddr *lclAddr,
      CztTportLyrAddr *ie);
EXTERN S16 wrX2apGetTnlAddr (CmTptAddr *lclAddr, CztTportLyrAddr *ie);
EXTERN S16 wrX2apGetTnlId (U32 *tnlId, CztGTP_TEI *remTeIdStr);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __WR_UMM_X2AP_MSG_H__ */

/********************************************************************30**

           End of file:    $SID$

*********************************************************************31*/


/********************************************************************40**
  
        Notes:
  
*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/

   
/********************************************************************60**
  
        Revision history:
  
*********************************************************************61*/
  
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
$SID$        ---      Sriky         1. initial release TotaleNodeB 1.1
*********************************************************************91*/
