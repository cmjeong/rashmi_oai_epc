


/********************************************************************20**
  
        Name:    PDCP - Database module file
    
        Type:    C source file
  
        Desc:    Source code for Database Module functions such as, 

                  -  pjDbmBufInit
                  -  pjDbmInsTxEnt
                  -  pjDbmGetTxEnt
                  -  pjDbmGetTxEntSn
                  -  pjDbmDelTxEnt
                  -  pjDbmTxDeInit
                  -  pjDbmInsRxEnt
                  -  pjDbmGetRxEnt
                  -  pjDbmDelRxEnt
                  -  pjDbmRxDeInit

        File:    gp_pj_dbm.c

        Sid:      eq_dbm.c@@/main/TeNB_Main_BR/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:52:47 2016
 
        Prg:     mn
  
*********************************************************************21*/
static const char* RLOG_MODULE_NAME="PDCP";
static int RLOG_MODULE_ID=1024;
static int RLOG_FILE_ID=214;


/* header (.h) include files */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"                /* general */
#include "ssi.h"                /* system services interface */
#include "cm5.h"                /* Timer Functions */
#include "cm_lte.h"             /* common LTE header file */
#include "cm_hash.h"            /* common hash module  file */
#include "cm_llist.h"           /* common list header file */
#include "cpj.h"                /* RRC layer */
#include "pju.h"                /* PDCP service user */
#include "lpj.h"                /* RRC layer */
#include "pj_env.h"             /* RLC environment options */
#include "pj.h"                 /* RLC layer */
#include "pj_err.h"

/* extern (.x) include files */
#include "gen.x"                /* general */
#include "ssi.x"                /* system services interface */
#include "cm_lib.x"             /* common library */
#include "cm5.x"                /* Timer Functions */
#include "cm_hash.x"            /* common hash module */
#include "cm_lte.x"             /* common LTE file */
#include "cm_llist.x"           /* common list header file */
#include "cpj.x"                /* RRC layer */
#include "pju.x"                /* PDCP service user */
#include "lpj.x"                /* LM Interface */
#include "pj.x"                 /* RLC layer */



/* local defines */

/* local externs */

/* forward references */

/* public variable declarations */

/* This structure holds all the global structs we need. */

/* private variable declarations */

/* private function declarations */

/** @file gp_pj_dbm.c
@brief PDCP DBM Module
**/

/*****************************************************************************
 *                  HANDLER FOR THE TRANSMISSION BUFFER
 ****************************************************************************/

/**
 *
 * @brief Handler to initialize  Buffer
 *
 * @b Description
 *        This function is invoked by config to initialize the Buffer
 *        hash List
 *
 *  @param[in]    buf       Rx/Tx Buffer Control Point
 *  @param[in]    numBins   number of Bins
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
*/
#ifdef ANSI
PUBLIC S16 pjDbmBufInit
(
PjCb        *gCb,
PjBuf       *buf,            /* !< Rx/Tx Buffer */
U8          numBins          /* !< number of Bins */
)
#else
PUBLIC S16 pjDbmBufInit(gCb,buf, numBins)
PjCb        *gCb;
PjBuf       *buf;            /* !< Rx/Tx Buffer */ 
U8          numBins;         /* !< number of Bins */             
#endif
{
   U8       hashIndex;        /* HashIndex of array */

   TRC3(pjDbmBufInit)

   RLOG1(L_DEBUG, "pjDbmBufInit(buf, numBins(%d)", numBins);

   /* Initialize CmLListCps*/
   PJ_ALLOC(gCb,buf->datQ, (sizeof(CmLListCp) * numBins));
#if (ERRCLASS & ERRCLS_DEBUG)
   if (buf->datQ == NULLP)
   {
      RLOG0(L_FATAL, "Memory Allocation failed.");
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

   for(hashIndex = 0; hashIndex < numBins; hashIndex++)
   {
      cmLListInit(&buf->datQ[hashIndex]);
   }

   /* Initialistations of buf */
   buf->numEntries = 0;
   buf->numBins    = numBins;

   RETVALUE(ROK);
} /* pjDbmBufInit */


/********************************************************************30**
  
         End of file:     eq_dbm.c@@/main/TeNB_Main_BR/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:52:47 2016
  
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
/main/1      ---      mn   1. LTERLC Release 2.1
*********************************************************************91*/
