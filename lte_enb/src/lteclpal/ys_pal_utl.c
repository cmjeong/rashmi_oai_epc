/************************************************************************
 
     Name:     LTE MAC Convergence layer
  
     Type:     C source file
  
     Desc:     C source code for Entry point fucntions
  
     File:     ys_pal_utl.c
  
     Sid:      ys_pal_utl.c@@/main/2 - Thu Dec  2 02:27:20 2010
  
     Prg:      hsingh
  
**********************************************************************/

/** @file ys_pal_utl.c
@brief This module acts as an interface handler for upper interface and 
manages Pst and Sap related information for upper interface APIs.
*/

/* header include files -- defines (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timers defines */
#include "cm_hash.h"       /* common hash list defines */
#include "cm_llist.h"      /* common linked list defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_tkns.h"       /* common tokens */
#include "cm_lte.h"
#include "ctf.h"           /* CTF defines */
#include "lys.h"           /* layer management typedefs for CL */
#include "tfu.h"
#include <sys/time.h>      /* System timer management header files */
#include "ys_pal_err.h"        /* YS error defines */
#include "ys_pal.h"

/* header/extern include files (.x) */
#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_lte.x"
#include "ctf.x"           /* CTF types */
#include "lys.x"           /* layer management typedefs for CL */
#include "tfu.x"
#include "ys_pal.x" 


/*
*
*       Fun:   ysPalUtlSetTfuMsg
*
*       Desc:  
*
*       Ret:   
*
*       Notes: None
*
*       File:  ys_pal_utl.c

*/

#ifdef ANSI
PUBLIC S16 ysPalUtlSetTfuMsg
(
YsCellCb *cellCb,
Void     *tfuMsg,
Event    event,
CmLteTimingInfo  *timingInfo
)
#else
PUBLIC S16 ysPalUtlSetTfuMsg(cellCb, tfuMsg, event, timingInfo)
YsCellCb *cellCb;
Void     *tfuMsg;
Event    event;
CmLteTimingInfo  *timingInfo;
#endif
{
   YsTxMsgArr      *txMsgArr;
   YsTxMsgInfo     *txMsgInfo;

   /* ys002.102: Added missed trace macro */
   TRC2(ysPalUtlSetTfuMsg)

   txMsgArr = &(cellCb->txMsgArr[timingInfo->subframe]);

   if(txMsgArr->num >= YS_NUM_MSG_INFO)
   {
      YS_DBG_ERR((_ysp, "can't queue msg\n"));
      RETVALUE(RFAILED);
   }

   txMsgInfo = &(txMsgArr->txMsgInfo[txMsgArr->num]);
   txMsgInfo->event = event;
   txMsgInfo->tfuMsg = tfuMsg;
   txMsgArr->num++;

   RETVALUE(ROK);
} /* end of ysPalUtlSetTfuMsg */

/********************************************************************30**
  
         End of file:     ys_pal_utl.c@@/main/2 - Thu Dec  2 02:27:20 2010
  
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
----------- -------- ---- -----------------------------------------------
/main/2      ---     sgm                   1. eNodeB 1.2 release
/main/2    ys002.102  rk                   1. Added missed trace macro.
*********************************************************************91*/
