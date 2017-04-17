
/********************************************************************20**

     Name:     REM Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_nmm.h

     Sid:      wr_nmm.h@@/main/Tenb_Intg_Branch_CC/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/Br_Tenb_Mspd_T2K_Intg_MS8.0_RC/1 - Tue Jul 23 17:01:21 2013

     Prg:      Sushant

*********************************************************************21*/

#ifndef __WR_NMM_H__
#define __WR_NMM_H__

#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */

void initNmmTask(void);
#ifndef TENB_T2K3K_SPECIFIC_CHANGES
typedef struct stMac2PhyApiQueueElem
{
    U16 frameNumber;
    U8 MessageType;
    U8 subframeNumber;
    U32 MessageLen;
    struct stMac2PhyApiQueueElem* Next;
    U8* MessagePtr;
} MAC2PHY_QUEUE_EL, *PMAC2PHY_QUEUE_EL;
#endif /* TENB_T2K3K_SPECIFIC_CHANGES */
EXTERN U16 wrHandleNmmMsg ARGS((
   Buffer *mBuf
));
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* End of __WR_NMM_H_*/
