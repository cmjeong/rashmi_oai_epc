


/********************************************************************20**
  
        Name:    LTE PDCP-PAL Interface file 
    
        Type:    C include file
  
        Desc:    This file contains all the data structures and 
                 prototypes for LTE PDCP.
 
        File:    pj_ptsec_pal.x

        Sid:      pj_ptsec_pal.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:50 2015
  
        Prg:     N/A 
  
*********************************************************************21*/
/** @file pj_ptsec_pal.x
@brief PDCP Product Structures, prototypes
*/

#ifndef __PJPTSECPALX__
#define __PJPTSECPALX__


/*
 *     The structures and variables declared in this file
 *     correspond to structures and variables used by
 *     the following TRILLIUM software:
 *
 *     part no.             description
 *     --------     ----------------------------------------------
 *     1000371      LTE-PDCP
 *
*/
 
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

EXTERN S16 pjUtlChekTxEnqReq ARGS ((PjCb *gCb, PjDlRbCb *pjRbCb, PjTxEnt *txEnt));
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PJPTSECPALX__ */

  
/********************************************************************30**
  
         End of file:     pj_ptsec_pal.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:50 2015
  
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
/main/1      ---       nm  1. Initial release.
*********************************************************************91*/

