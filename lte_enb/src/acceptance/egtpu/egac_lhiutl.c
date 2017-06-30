
/********************************************************************20**
  
     Name:     TCP UDP Convegence Layer Sample Stack Manager
  
     Type:     C source file
  
     Desc:     Sample code for Management Interface primitives supplied 
               by TRILLIUM
              
     File:     egac_lhiutl.c
  
     Sid:      egac_lhiutl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:38 2015

     Prg:      an
  
*********************************************************************21*/
/* header include files (.h) */

#include "egac_acc.x"
#include "egac_lhi.x"


/*
*
*       Fun:   egAcUtlLhiCb 
*
*       Desc:  This function is an utility function
*
*       Ret:   None
*
*       Notes: None
*
*       File:  egac_lhiutl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcUtlLhiCb
(
CmXtaMsgQElm *qElm
)
#else
PUBLIC S16 egAcUtlLhiCb(qElm)
CmXtaMsgQElm *qElm;
#endif /* ANSI */
{
   EgAccMsgQElm *egtpMsg;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcUtlLhiCb)

   egtpMsg = (EgAccMsgQElm *)qElm->data;

   if ((qElm->pst.event == EVTLHITRCIND) &&
       (egtpMsg->mBuf != NULLP))
   {
      CMXTA_FREEMBUF(egtpMsg->mBuf);
   }

   CMXTA_FREE(egtpMsg, sizeof (EgAccMsgQElm));

   RETVALUE(CMXTA_ERR_NONE);
} /* End of egAcUtlLhiCb() */


/********************************************************************30**

         End of file:     egac_lhiutl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:38 2015

*********************************************************************31*/


/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************80**

*********************************************************************81*/

/********************************************************************90**

    ver       pat    init                  description
----------- -------- ---- -----------------------------------------------
/main/1      ---      ad          1. Created for Initial release 1.1
/main/2      ---      svenkat     1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
/main/3  eg003.201    psingh      1. Merged code from eg006.102 to Fix 
                                     TRACE5 macro related issue
*********************************************************************91*/
