

/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for Entry point fucntions
  
     File:     rgac_tf_ex_ms.c
  
     Sid:      tf_ex_ms.c@@/main/3 - Sat Jul 30 02:22:24 2011
  
     Prg:      sm
  
**********************************************************************/

/** @file rgac_tf_ex_ms.c
@brief APIs related to Downlink HARQ.
*/

#include "rg.h"
#include "rgac_acc.x"

/* Global structure to contain timing information and also the timer queues. */
PUBLIC RgAcTfCb rgAcTfCb;

PRIVATE S16 rgAcTfInitTmr ARGS((Void));


/** @brief This function initializes the timers needed by Dummy PHY.
 * @return ROK
 */
#ifdef ANSI
PRIVATE S16 rgAcTfInitTmr
(
)
#else
PRIVATE S16 rgAcTfInitTmr()
#endif
{
   TRC2(rgAcTfInitTmr)
   cmInitTimers (rgAcTfCb.timers, RG_ACC_TFU_MAX_TIMERS);
   RETVALUE(ROK);
} /* end of rgAcTfInitTmr */

#ifdef ANSI
PRIVATE S16 rgAcTfStartTmr
(
 S16     tmrEvnt,
 U8      tmrVal
 )
#else
PRIVATE S16 rgAcTfStartTmr (tmrEvnt, tmrVal)
 S16     tmrEvnt;
 U8      tmrVal;
#endif
{
   CmTmrArg    arg;

   TRC3(rgAcTfStartTmr)

   arg.tqCp    = &rgAcTfCb.tqCp;
   arg.tq      = rgAcTfCb.tq;
   arg.timers  = rgAcTfCb.timers;
   arg.cb      = (PTR)&rgAcTfCb;
   arg.evnt    = tmrEvnt;
   arg.wait    = tmrVal;
   arg.tNum    = 0;
   arg.max     = RG_ACC_TFU_MAX_TIMERS;
   /*-- Put the timer into the timing queue. --*/
   cmPlcCbTq(&arg);
   RETVALUE(ROK);
} /* end of rgAcTfStartTmr */


#ifdef ANSI
PRIVATE S16 rgAcTfProcTmr
(
Ptr        cb,
S16        tmrEvnt
)
#else
PRIVATE S16 rgAcTfProcTmr (cb, tmrEvnt)
Ptr        cb;
S16        tmrEvnt;
#endif
{
   SuId                suId;
   Pst                 pst;
   TfuTtiIndInfo       ttiInd;

   TRC2(rgAcTfProcTmr)

      UNUSED(cb);
      UNUSED(tmrEvnt);

   /* This function is meant to process the expiry of the TTI timer. Here is a
    * list of things it needs to do as part of this processing. 
    * 1. Increment the subFrame number by one.
    *    if (crntSubFrame == 9)
    *       increment crntSfn taking care that it should wrap around after 1024.
    * 2. Create and call a TTI indication towards MAC.
    */
   RGADDTOCRNTTIME(rgAcTfCb.crntTime, rgAcTfCb.crntTime, 1);

   /* Start it again */
   rgAcTfStartTmr (RG_ACC_TF_TTI, 1);

   /* Note this would need modification to the cmXtaGetPst code as we are
    * passing the procIds but get Pst shouldnt be matching them at all. 
    */
   cmXtaGetPst(&pst, ENTTF, CMXTA_INST_ID, ENTRG, CMXTA_INST_ID, 
         CMXTA_PROCID_MASTER, CMXTA_PROCID_MASTER, FALSE);
   /* Now we can call the TTI indication towards MAC. */
   ttiInd.cells[0].cellId = RG_ACC_CELL_ID;/*TODO - check with Nawas*/

   suId = 0; 
   TfUiTfuTtiInd (&pst, suId, &ttiInd);
   RETVALUE(ROK);
} /* end of rgAcTfProcTmr */

/** @brief This is the timer activation function for dummy PHY.
 * @return ROK
 */
#ifdef ANSI
PUBLIC S16 rgAcTfActvTmr
(
Void
)
#else
PUBLIC S16 rgAcTfActvTmr ()
#endif
{
   TRC2(rgAcTfActvTmr)
   cmPrcTmr (&rgAcTfCb.tqCp, rgAcTfCb.tq, (PFV) rgAcTfProcTmr);
   RETVALUE (ROK);
} /* end of rgAcTfActvTmr */


/** @brief This is the activation task of the dummy PHY layer. 
 * @param pst pointer to the Pst structure
 * @param mBuf pointer to the Buffer. 
 * @return ROK/RFAILED
 */
#ifdef ANSI
PUBLIC S16 rgAcTfActvTsk
(
 Pst     *pst,
 Buffer  *mBuf
 )
#else
PUBLIC S16 rgAcTfActvTsk (pst, mBuf)
 Pst     *pst;
 Buffer  *mBuf;
#endif
{
   S16 ret = ROK;

   TRC3(rgAcTfActvTsk)

   ret = ROK;
   /* Dummy TF shall function in the following fashion. It primarily runs a 1ms
    * timer that keeps track of the crntSfn and crntSubFrame. This timer however
    * should start only once all the layers are intialized and hence would need
    * an XML command to intialize and start the timer. 
    */
   switch(pst->srcEnt)
   {
      
      case ENTTST:
         {
            /* This has to be the init message from the test entity meant to start
             * the TTI timer in Dummy Phy.
             */
            CMXTA_DBG_INFO((_cmxtap, "rgAcTfActvTsk(): intializing TTI timer in Dummy TF! \n"));
            rgAcTfInitTmr();
            rgAcTfCb.tqCp.nxtEnt = 0;
            /* Plan to have one timer resolution and a single timer at that also */
            rgAcTfCb.tqCp.tmrLen = 1; 
            ret = SRegCfgTmr ( ENTTF,
                  CMXTA_INST_ID,
                  (S16)1,
                  (S16)SS_1MS,
                  rgAcTfActvTmr);
            if (ret != ROK)
               CMXTA_DBG_ERR((_cmxtap, "rgAcTfActvTsk(): Could not configure Timers! \n"));

            /* Now we are all set lets start the timer */
            rgAcTfStartTmr(RG_ACC_TF_TTI, 1);
            SPutMsg(mBuf);
            break;
         } /* end of ENTTST */
      case ENTRG:
         {
            switch (pst->event)
            {
#ifdef LCTFU
               case EVTTFUBNDREQ:
                  ret = cmUnpkTfuBndReq (TfUiTfuBndReq, pst, mBuf);
                  break;
               case EVTTFUUBNDREQ:
                  ret = cmUnpkTfuUbndReq (TfUiTfuUbndReq, pst, mBuf);
                  break;
               case EVTTFUDATREQ:
                  ret = cmUnpkTfuDatReq (TfUiTfuDatReq, pst, mBuf);
                  break;
               case EVTTFUSCHBNDREQ:
                  ret = cmUnpkTfuSchBndReq(TfUiTfuSchBndReq, pst, mBuf);
                  break;
               case EVTTFUSCHUBNDREQ:
                  ret = cmUnpkTfuSchUbndReq(TfUiTfuSchUbndReq, pst, mBuf);
                  break;
               case EVTTFUCNTRLREQ:
                  ret = cmUnpkTfuCntrlReq(TfUiTfuCntrlReq, pst, mBuf);
                  break;
               case EVTTFURECPREQ:
                  ret = cmUnpkTfuRecpReq(TfUiTfuRecpReq, pst, mBuf);
                  break;
#endif
               default:
                  break;

            } /* end of switch (evnt) */
         }
         break;
      default:
         CMXTA_DBG_ERR((_cmxtap, "rgAcTfActvTsk(): Message from an invalid entity! \n"));
         ret = RFAILED;

   } /* end of switch */

   SExitTsk();
   RETVALUE (ret);
} /* end of rgAcTfActvTsk */

/** @brief This is the activation task of Dummy Physical layer, its called by
 * SSI to initialize the layer. 
 * @param ent entity Id
 * @param inst instance Id
 * @param region Region 
 * @param reason Reason
 * @return ROK/RFAILED
 */
#ifdef ANSI
PUBLIC S16 rgAcTfActvInit
(
 Ent     ent,
 Inst    inst,
 Region  region,
 Reason  reason
 )
#else
PUBLIC S16 rgAcTfActvInit (ent, inst, region, reason)
 Ent     ent;
 Inst    inst;
 Region  region;
 Reason  reason;
#endif
{
   TRC2(rgAcTfActvInit)
      /* need to do nothing here, all intialization shall happen once an XML
       * command is issued from the test case.
       */
      UNUSED(ent);
      UNUSED(inst);
      UNUSED(region);
      UNUSED(reason);
   RETVALUE(ROK);
}


/**********************************************************************
 
         End of file:     tf_ex_ms.c@@/main/3 - Sat Jul 30 02:22:24 2011
 
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
/main/1      ---     sm              1. Initial Release.
/main/2      ---     sm              1. LTE MAC 2.1 release
/main/3      ---     gj              1. LTE MAC 3.1 Release.
*********************************************************************91*/
