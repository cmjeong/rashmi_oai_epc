

/********************************************************************20**

     Name:    LTE-PDCP - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    pjac_pjucb.c

     Sid:      pjac_libutl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:56 2015

     Prg:     Adarsh
*********************************************************************21*/

/* header (.h) include files */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timer defines */
#include "cm_tkns.h"       /* common tokens defines */
#include "cm_mblk.h"       /* common memory allocation library defines */
#include "cm_llist.h"      /* common link list  defines  */
#include "cm_hash.h"       /* common hash list  defines */
#include "cm_lte.h"        /* common LTE defines */
#include "kwu.h"           /* KWU defines */
#include "pju.h"           /* PJU defines */
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "pj_env.h"        /* RLC environment options */
#include "pj.h"

#include "cm_xta.h"
#include "pjac_lib.h"      /* LIB Acceptance defines */
#include "pjac_acc.h"      /* Acceptance defines */

/* extern (.x) include files */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */

#include "cm5.x"           /* common timer library */
#include "cm_tkns.x"       /* common tokens */
#include "cm_mblk.x"       /* common memory allocation */
#include "cm_llist.x"      /* common link list */
#include "cm_hash.x"       /* common hash list */
#include "cm_lte.x"        /* common LTE includes */
#include "cm_lib.x"        /* common memory allocation library */
#include "kwu.x"           /* KWU */
#include "pju.x"           /* PJU */
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "pj.x"

#include "cm_xta.x"
#include "pjac_lib.x"      /* LIB Acceptance defines */
#include "pjac_acc.x"      /* Acceptance defines */


/*************************************************************************
 *                LIB LISTCP PRIMITIVES START
 *************************************************************************/
  
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
PUBLIC S16 pjAcLibUtlBufInit
(
)
#else
PUBLIC S16 pjAcLibUtlBufInit( )
#endif
{
   TRC2(pjAcBufInit);
   cmLListInit(&libCb.intCb.intList);
   cmLListInit(&libCb.intCb.intOutList);
   cmLListInit(&libCb.cipCb.cipList);
   cmLListInit(&libCb.cipCb.cipOutList);
   cmLListInit(&libCb.compCb.compOutList);
   RETVALUE(ROK);
}/* end of pjAcLibUtlBufInit */

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
PUBLIC S16 pjAcLibUtlGetEnt
(
CmLListCp   *lCp,
PTR         fd,
KwAcLibSecEnt **ent
)
#else
PUBLIC S16 pjAcLibUtlGetEnt(lCp, fd, ent)
CmLListCp   *lCp;
PTR         fd;
KwAcLibSecEnt **ent;
#endif
{
   KwAcLibSecEnt *tmpEnt;
   TRC2(pjAcLibUtlGetEnt);

   cmLListFirst(lCp);
   while(cmLListCrnt(lCp))
   {
      tmpEnt   =  (KwAcLibSecEnt *)cmLListNode(cmLListCrnt(lCp));
      if(tmpEnt->fd == fd)
      {
         (*ent)   =  tmpEnt;
         RETVALUE(ROK);
      }
      cmLListNext(lCp);
   }
   (*ent)   =  NULLP;
   RETVALUE(ROK);
}/* end of pjAcLibUtlGetEnt */

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
PUBLIC Void pjAcLibUtlDelEnt
(
CmLListCp   *lCp,
PTR         fd
)
#else
PUBLIC Void pjAcLibUtlDelEnt(lCp, fd)
CmLListCp   *lCp;
PTR         fd;
#endif
{
   KwAcLibSecEnt  *ent;
   TRC2(pjAcLibUtlDelEnt);

   pjAcLibUtlGetEnt(lCp, fd, &ent);
   if(ent == NULLP)
   {
      return;
   }

   cmLListDelFrm(lCp, &ent->listEnt);
   PJ_FREE_ACC(ent, sizeof(KwAcLibSecEnt));
   return;
}/* end of pjAcLibUtlDelEnt */

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
PUBLIC S16 pjAcLibUtlInsOutEnt
(
CmLListCp   *lCp,
KwAcLibOutEnt *ent
)
#else
PUBLIC S16 pjAcLibUtlInsOutEnt(lCp, ent)
CmLListCp   *lCp;
KwAcLibOutEnt *ent;
#endif
{

   TRC2(pjAcLibUtlInsOutEnt);

   ent->listEnt.node   =  (PTR)ent;
   cmLListAdd2Tail(lCp, &ent->listEnt);

   RETVALUE(ROK);
}/* end of pjAcLibUtlInsOutEnt */

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
PUBLIC S16 pjAcLibUtlGetOutEnt
(
CmLListCp   *lCp,
U32         id,
KwAcLibOutEnt **ent
)
#else
PUBLIC S16 pjAcLibUtlGetOutEnt(lCp, id, ent)
CmLListCp   *lCp;
U32         id;
KwAcLibOutEnt **ent;
#endif
{
   KwAcLibOutEnt *tmpEnt;
   TRC2(pjAcLibUtlGetOutEnt);

   cmLListFirst(lCp);
   while(cmLListCrnt(lCp))
   {
      tmpEnt   =  (KwAcLibOutEnt *)cmLListNode(cmLListCrnt(lCp));
      if(tmpEnt->id == id)
      {
         (*ent)   =  tmpEnt;
         RETVALUE(ROK);
      }
      cmLListNext(lCp);
   }
   (*ent)   =  NULLP;
   RETVALUE(ROK);
}/* end of pjAcLibUtlGetOutEnt */
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
PUBLIC Void pjAcLibUtlDelOutEnt
(
CmLListCp   *lCp,
KwAcLibOutEnt  *ent
)
#else
PUBLIC Void pjAcLibUtlDelOutEnt(lCp, ent)
CmLListCp   *lCp;
KwAcLibOutEnt  *ent;
#endif
{
   TRC2(pjAcLibUtlDelOutEnt);

   cmLListDelFrm(lCp, &ent->listEnt);
   PJ_FREE_BUF(ent->mBuf);
   PJ_FREE_ACC(ent, sizeof(KwAcLibOutEnt));
   return;
}/* end of pjAcLibUtlDelOutEnt */
/********************************************************************30**

         End of file:     pjac_libutl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:56 2015

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
/main/1      ---       vb         1. LTE PDCP Initial Release 2.1
*********************************************************************91*/

