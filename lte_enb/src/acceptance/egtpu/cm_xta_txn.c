
/********************************************************************20**

     Name:    Common XML TA 

     Type:    C source file

     Desc:    C code 

     File:    

     Sid:      cm_xta_txn.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:59:30 2015

     Prg:     up 

*********************************************************************21*/
/* header include files (.h) */
#include "envopt.h"         /* environment options          */
#include "envdep.h"         /* environment dependent        */
#include "envind.h"         /* environment independent      */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_llist.h"      /* common link list */
/*Updated for FTHA Integration*/
#ifdef CMXTA_FTHA_INTEGRATED
#include "cm_ftha.h"
#include "lmr.h"
#include "lsh.h"
#include "lsg.h"
#endif

#include "cm_xta.h"
/* cm_xta_txn_c_001.main_6 Removed cm_xta_app.h for Psf-Diameter 1.1 */
/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_llist.x"      /* common link list */

/*Updated for FTHA Integration*/
#ifdef CMXTA_FTHA_INTEGRATED
#include "cm_ftha.x"
#include "lmr.x"
#include "lsh.x"
#include "lsg.x"
#endif
#include "cm_xta.x"

/* cm_xta_txn_c_001.main_6 Removed cm_xta_app.x for Psf-Diameter 1.1 */
/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC Void cmXtaInitHdr
(
Header     *hdr,          /* Management header */
U32        txnId,
Ent         ent,
Inst        inst,
Elmnt       elem,
Selector    selector
)
#else
PUBLIC Void cmXtaInitHdr(hdr, txnId, ent, inst, elem, selector)
Header     *hdr;         /* Management header */
U32        txnId;
Ent         ent;
Inst        inst;
Elmnt       elem;
Selector    selector;
#endif
{
   TRC2(cmXtaInitHdr)

   hdr->msgType          = 0;
   hdr->msgLen           = 0;
   hdr->entId.ent        = ent;
   hdr->entId.inst       = inst;
   hdr->elmId.elmnt      = elem;
   hdr->elmId.elmntInst1 = 0;
   hdr->elmId.elmntInst2 = 0;
   hdr->elmId.elmntInst3 = 0;
   hdr->seqNmb           = 0;
   hdr->version          = 0;

   hdr->response.prior      = PRIOR0;
   hdr->response.route      = RTESPEC;
   hdr->response.mem.region = DFLT_REGION;
   hdr->response.mem.pool   = DFLT_POOL;

   hdr->transId = txnId;
   hdr->response.selector   = selector;

   RETVOID;
} /* End of cmXtaInitHdr */

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
/*cm_xta_txn_c_001.main_2 :Support for multiple proc */
/*Updated cmXtaGetPst.Moved outside MULTIPLE PROC flag*/
#ifdef ANSI 
PUBLIC Void cmXtaGetPst
(
Pst  *pst,
Ent srcEnt,
Inst srcInst,
Ent  dstEnt,
Inst dstInst,
ProcId srcProcId,
ProcId dstProcId,
Bool   matchProc
)
#else
PUBLIC Void cmXtaGetPst(pst, srcEnt, srcInst, dstEnt, dstInst,srcProcId,dstProcId, matchProc)
Pst  *pst;
Ent srcEnt;
Inst srcInst;
Ent  dstEnt;
Inst dstInst;
ProcId srcProcId;
ProcId dstProcId;
Bool   matchProc;
#endif
{
   U16 j;
   Pst *tmpPst;

   TRC2(cmXtaGetPst)

   CMXTA_ZERO(pst, sizeof(Pst));

   for (j = 0; j < CMXTA_MAX_INTERFACE; j++)
   {
      tmpPst = &cmXtaCb.pst[j];

      if ((tmpPst->srcEnt  == srcEnt)   &&
          (tmpPst->srcInst == srcInst)  &&
          (tmpPst->dstEnt  == dstEnt)   &&
          (tmpPst->dstInst == dstInst)  
          && ((tmpPst->srcProcId == srcProcId) || (matchProc == FALSE)) &&
          ((tmpPst->dstProcId == dstProcId) || (matchProc == FALSE)))
      {
         *pst = *tmpPst;
         break; 
      } /* end of if statement */
   } /* end of for loop */

   RETVOID;
}

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC CmXtaTCCb*  cmXtaTxnTstCbFind
(
U32            txnId,      /* Transaction Id      --*/
Bool           del
)
#else
PUBLIC CmXtaTCCb*  cmXtaTxnTstCbFind (txnId, del)
U32            txnId;       /* Transaction Id      --*/
Bool           del;
#endif
{
   U32      tcId;
   S16      ret;
   CmXtaTxnCb      *txnCb;/* Transaction Block   */
   CmXtaTCCb *  tcCb;

   TRC2(cmXtaTxnTstCbFind)

   /* cm_xta_txn_c_001.main_4: Fix for 64bit compilation warning */
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaTxnTstCbFind(): txnId (%d)\n", txnId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaTxnTstCbFind(): txnId (%ld)\n", txnId));
#endif /* ALIGN_64BIT */

   /* cm_xta_txn_c_001.main_5 - Fix for compilation warnings */
   tcCb = NULLP; 
   txnCb = NULLP;
   tcId  = ~0;

   /*-- The logic for txn cb is not complete. TA creates a new Txn Cb
        for any request on LMI interface. If the response message is
        delayed, the failure is reported through guard timer expiry.

        Since there is no way in the present design to find out which
        txnId timed out, so the txnCb is left hanging.

        If the messge is receieved later, it may still find the txnCb
        and the associated pointer to tcCb. But the test case may have
        finished and tcCb pointer may be invalid.

        This will require an overhaul of the guard timer design. The
        present design is to find the txnCb and release it and pass
        the message to the current tcCb. This will result in unexpected
        message getting handled as well.

        The design does not support running multiple TCs at one time.
        This shall be enhanced --*/
#ifdef CM_XTA_ENHANCE
   /*-- Optimization, check if only one TC running --*/
   if (cmXtaCb.curTCCb != NULLP)
      RETVALUE(cmXtaCb.curTCCb);
   else
   {
#endif

   /*-- Find the transaction control block in
    *   the hash list --*/
   ret = cmHashListFind (&cmXtaCb.txnLstCp,
                         (U8  *) &txnId,
                         (U16  ) sizeof(U32),
                         0,
                         (PTR *) &txnCb);

   if (txnCb != NULLP)
   {
      tcCb = (CmXtaTCCb *)txnCb->cb;

      tcId = txnCb->tcId;

      if (del == TRUE)
         cmXtaTxnDelete(txnCb);

#ifdef CM_XTA_ENHANCE
      RETVALUE(tcCb);
#endif
   }

   /*-- With this broken SM Txn functionality, it is possible that a previous 
        TC did not handle all his messages and messages from the previous test
        case arrive later and they may get passed to the new test case. It
        may result in failure for the new test case. To help debug such conditions,
        flags an error if the tcCb is different for the incoming message
        from the previous one --*/
   if ((tcId != ~0u) && (tcId != cmXtaCb.curTCCb->tcId))
   {
       /* cm_xta_txn_c_001.main_4: Fix for 64bit compilation warning */
#ifdef ALIGN_64BIT
      CMXTA_DBG_FATAL((_cmxtap, "cmXtaTxnTstCbFind(): Invalid TC Id exp(%d) rcv(%d)\n", tcCb->tcId, tcId));
#else
      CMXTA_DBG_FATAL((_cmxtap, "cmXtaTxnTstCbFind(): Invalid TC Id exp(%ld) rcv(%ld)\n", tcCb->tcId, tcId));
#endif /* ALIGN_64BIT */
      CMXTA_DBG_FATAL((_cmxtap, "cmXtaTxnTstCbFind(): Message arrived for a previous TC most likely\n"));
   }

   /*-- We may not have a Txn Cb in case of any kind of indications, pass them
        to the global Test Control Block, if present --*/
   if (cmXtaCb.curTCCb != NULLP)
      RETVALUE(cmXtaCb.curTCCb);

   RETVALUE(NULLP);
} /* cmXtaTxnTstCbFind */

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC CmXtaTxnCb*  cmXtaTxnFind
(
U32            txnId       /* Transaction Id      --*/
)
#else
PUBLIC CmXtaTxnCb* cmXtaTxnFind (txnId)
U32            txnId;       /* Transaction Id      --*/
#endif
{
   S16      ret;
   CmXtaTxnCb      *txnCb;/* Transaction Block   */

   TRC2(cmXtaTxnFind)

   /* cm_xta_txn_c_001.main_4: Fix for 64bit compilation warning */
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaTxnFind(): txnId (%d)\n", txnId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaTxnFind(): txnId (%ld)\n", txnId));
#endif /* ALIGN_64BIT */

   txnCb = NULLP;

   /*-- Find the transaction control block in
    *   the hash list --*/
   ret = cmHashListFind (&cmXtaCb.txnLstCp,
                         (U8  *) &txnId,
                         (U16  ) sizeof(U32),
                         0,
                         (PTR *) &txnCb);

   RETVALUE(txnCb);
} /* cmXtaTxnFind */

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC CmXtaTxnCb*  cmXtaTxnCreate
(
U32            txnId,       /* Transaction Id      --*/
Ptr            cb
)
#else
PUBLIC CmXtaTxnCb*  cmXtaTxnCreate (txnId, cb)
U32            txnId;       /* Transaction Id      --*/
Ptr            cb;
#endif
{
   S16 ret;
   CmXtaTxnCb *txnCb;

   TRC2(cmXtaTxnCreate)

   /* cm_xta_txn_c_001.main_4: Fix for 64bit compilation warning */
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaTxnCreate(): txnId (%d)\n", txnId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaTxnCreate(): txnId (%ld)\n", txnId));
#endif /* ALIGN_64BIT */

   txnCb = NULLP;

   /*-- Allocate Transaction control block --*/
   CMXTA_ALLOC(&txnCb, sizeof (CmXtaTxnCb));
   if (txnCb == NULLP)
   {
      RETVALUE(NULLP);
   }

   /* Get new Transaction Id if invalid */
   if (txnId == CMXTA_TXN_INVALID)
   {
      txnCb->txnId = ++(cmXtaCb.txnCounter);

      /*-- If the value is reset, increment again --*/
      if (txnCb->txnId == 0)
         txnCb->txnId = ++(cmXtaCb.txnCounter);
   }
   else
      txnCb->txnId = txnId;

   /* Initialize the Transaction Control Block */
   txnCb->cb    = cb;

   /*-- Store tcId in txn Cb itself, because during validation
        tcCb pointer may not be around anymore --*/
   txnCb->tcId = ((CmXtaTCCb *)cb)->tcId;

   /*-- Insert Transaction into global transaction list --*/
   ret = cmHashListInsert (&cmXtaCb.txnLstCp, 
                           (PTR) txnCb, (U8 *) &txnCb->txnId, 
                           sizeof(U32));
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaTxnCreate(): resource error\n"));
      cmXtaTxnDelete (txnCb); 
      RETVALUE (NULLP);
   }

   /* cm_xta_txn_c_001.main_4: Fix for 64bit compilation warning */
#ifdef ALIGN_64BIT
   CMXTA_DBG_INFO((_cmxtap, "cmXtaTxnCreate(): txnId (%d) created\n", txnCb->txnId));
#else
   CMXTA_DBG_INFO((_cmxtap, "cmXtaTxnCreate(): txnId (%ld) created\n", txnCb->txnId));
#endif /* ALIGN_64BIT */

   RETVALUE(txnCb);
} /* cmXtaTxnCreate */

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16  cmXtaTxnDelete
(
CmXtaTxnCb      *txnCb  /* Transaction Block   */
)
#else
PUBLIC S16  cmXtaTxnDelete (txnCb)
CmXtaTxnCb      *txnCb; /* Transaction Block   */
#endif
{
   TRC2(cmXtaTxnDelete)

   /* cm_xta_txn_c_001.main_4: Fix for 64bit compilation warning */
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaTxnDelete(): txnId (%d)\n", txnCb->txnId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaTxnDelete(): txnId (%ld)\n", txnCb->txnId));
#endif /* ALIGN_64BIT */
   /*-- Release from BCP Transaction List --*/
   cmHashListDelete (&cmXtaCb.txnLstCp, (PTR) txnCb);

   /*-- Finally, delete transaction control block (TCB) --*/
   CMXTA_FREE(txnCb, sizeof (CmXtaTxnCb));

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaTxnDelete */

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaTxnInit
(
Void
)
#else
PUBLIC S16 cmXtaTxnInit ()
#endif
{
   S16      ret;

   TRC2(cmXtaTxnInit)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaTxnInit(): Init SM\n"));

   /*-- Initialize hash list --*/
   ret = cmHashListInit(&cmXtaCb.txnLstCp,   /* HL Control point */
                        100,   /* HL Bins for a txn */
                        CMXTA_OFFSET_OF(CmXtaTxnCb, txnHlEnt),
                        FALSE,             /* Allow dup keys */
                        CM_HASH_KEYTYPE_U32MOD,
                        cmXtaCb.init.region,  /* Mem region */
                        cmXtaCb.init.pool);   /* Mem Pool */

   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaTxnInit(): init failed\n"));
   } 

   RETVALUE(ret);
} /* cmXtaTxnInit */

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaTxnDeInit
(
Void
)
#else
PUBLIC S16 cmXtaTxnDeInit ()
#endif
{
   CmXtaTxnCb   *txnCb;

   TRC2(cmXtaTxnDeInit)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaTxnDeInit(): shutdown initiated\n"));

   /*-- Delete all pending transactions --*/
   while (cmHashListGetNext(&cmXtaCb.txnLstCp,
            NULLP, (PTR *)&txnCb) == CMXTA_ERR_NONE)
      cmXtaTxnDelete(txnCb);

   cmHashListDeinit(&cmXtaCb.txnLstCp);

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaTxnDeInit */

/********************************************************************30**

         End of file:     cm_xta_txn.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:59:30 2015

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
/main/2      ----     up  1. Main release
/main/3      ---      cm_xta_txn_c_001.main_2  sk  1. Support for multiple proc
/main/4      ---      aj  1. Updated for FTHA Integration 
                          2. Moved cmXtaGetPst outside the MULTIPLE PROC flag 
/main/5      ---      cm_xta_txn_c_001.main_4  pkaX  1. Fix for 64bit compilation warning
/main/6  cm_xta_txn_c_001.main_5  spoovalingam  1. Fix for compilation warnings
/main/7      ----     cm_xta_txn_c_001.main_6 nh 1. Updated for Psf-Diameter 1.1
                          release Removed cm_xta_app.[hx]
*********************************************************************91*/
