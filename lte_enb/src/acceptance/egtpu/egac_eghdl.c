
/********************************************************************20**

     Name:    EGTP 

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    egac_eghdl.c

     Sid:      egac_eghdl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:27 2015

     Prg:     pc 

*********************************************************************21*/

/* header include files (.h) */
#include "egac_acc.x"

/*
*
*       Fun:   egAcHdlEgGlobalDirective
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  tq_aghdlr.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlEgGlobalDirective
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlEgGlobalDirective(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   TRC2(egAcHdlEgGlobalDirective)
   RETVALUE(CMXTA_ERR_NONE);
}/* egAcHdlEgGlobalDirective */

/*
*
*       Fun:   egAcHdlEgDirective
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_eghdl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlEgDirective
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlEgDirective(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   EgAcTCCb *egTcCb;
   Bool   resetSeqCounter=0;

   TRC2(egAcHdlEgDirective)

   egTcCb = (EgAcTCCb *)tcCb->tcCb;

   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEgDirective(): tcCb (%ld)\n", tcCb->tcId));

   /*-- TC Directives : Changes the setting across for a particular instance of
        a test case. The values do not affect the global settings.

        Instructions : These values shall not be used only till the point an 
        associated test case is not found. After that the directives inside
        the tcCb shall be used for all decisions. Essentially that means all
        handlers shall use the tcCb based directive values all the time. --*/

   /*-- EGTP command to set global and TC level settings --*/

   /*-- The global and TC settings may be set from outside as well, hence
        do not assign a default value here, instead just override the 
        values if specified by the test case --*/

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
     using XML --*/

   /* Take resetting of Seq counter to zero  */
   cmXtaXmlGetVal(NULLP,spCb->curStep, CMXTA_ATTRIB_ENUM_U8, "resetSeqCounter",  &resetSeqCounter);

   if( resetSeqCounter == 0)
   {
      egTcCb->directives.egtSeqCounter = 0;
   }

   /*-- dummy entity value --*/
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "dummy",  &egTcCb->dummyEntity);

   RETVALUE(CMXTA_ERR_NONE);
}/* egAcHdlEgDirective */

/*
*
*       Fun:   egAcHdlEgDelay
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  tq_aghdlr.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHdlEgDelay
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 egAcHdlEgDelay(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   TRC2(egAcHdlEgDelay)

   CMXTA_DBG_PARAM((_cmxtap, "egAcHdlEgDelay(): tcCb (%ld)\n", tcCb->tcId));

   /*-- Internal command to handle delay --*/

   /*-- Check if we are to skip delay command delays --*/
   if (tcCb->directives.ignoreDelay == TRUE)
   {
      CMXTA_DBG_CALLIND((_cmxtap, " Info      : Skipping EGTP delay\n"), 3);
      RETVALUE(CMXTA_ERR_NONE);
   }
   /*-- Just Pass to Internal Delay Handler --*/
   RETVALUE(cmXtaHdlIntDelay(tcCb, spCb));

}/* egAcHdlEgDelay */

/********************************************************************30**

         End of file:     egac_eghdl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:27 2015

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
/main/1      ---      ad          1. Created for Initial release 1.1
/main/2      ---      rkumar      1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
*********************************************************************91*/
