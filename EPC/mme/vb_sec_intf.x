
/********************************************************************20**

     Name:    Trillium LTE CNE - MME Controller Module

     Type:    C Include file

     Desc:    This file contains c structure for security module inteface

     File:    vb_mme_sec_intf.x

     Sid:     vb_mme_sec_intf.x@@/main/1 - Mon Jun 28 19:35:38 2010

     Prg:     sk 
*********************************************************************21*/

#ifndef __VB_MME_SEC_INTF__
#define __VB_MME_SEC_INTF__ 1

#ifdef __cplusplus
EXTERN "C" {
#endif /* end of __cplusplus */

#ifdef VB_MME_NAS_SEC

EXTERN S16 vbMmeGetAuthVector ARGS((VbMmeUeCb *ueCb));

EXTERN S16 vbMmeProcessSyncFlr ARGS((VbMmeUeCb  *ueCb,
                                     U8         *auts,
                                     U8         *rnd));
#endif

#ifdef __cplusplus
} /* end of extern "C" */
#endif /* end of __cplusplus */
#endif

