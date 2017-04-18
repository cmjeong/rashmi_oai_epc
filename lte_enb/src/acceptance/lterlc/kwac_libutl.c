

/********************************************************************20**

     Name:    LTE-RLC - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    kwac_pjucb.c

     Sid:      kwac_libutl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:31 2014

     Prg:     cp
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
#include "lkw.h"           /* LKW defines */
#include "ckw.h"           /* CKW defines */
#include "kwu.h"           /* KWU defines */
#include "pju.h"           /* PJU defines */
#include "rgu.h"           /* RGU defines */
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "kw_env.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */

#include "cm_xta.h"
#include "kwac_lib.h"      /* LIB Acceptance defines */
#include "kwac_acc.h"      /* Acceptance defines */

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
#include "lkw.x"           /* LKW */
#include "ckw.x"           /* CKW */
#include "kwu.x"           /* KWU */
#include "pju.x"           /* PJU */
#include "rgu.x"           /* RGU */
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "kw.x"

#include "cm_xta.x"
#include "kwac_lib.x"      /* LIB Acceptance defines */
#include "kwac_acc.x"      /* Acceptance defines */



#ifdef KW_PDCP
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
PUBLIC S16 kwAcLibUtlBufInit
(
)
#else
PUBLIC S16 kwAcLibUtlBufInit( )
#endif
{
   TRC2(kwAcBufInit);
   cmLListInit(&libCb.intCb.intList);
   cmLListInit(&libCb.intCb.intOutList);
   cmLListInit(&libCb.cipCb.cipList);
   cmLListInit(&libCb.cipCb.cipOutList);
   cmLListInit(&libCb.compCb.compOutList);
   RETVALUE(ROK);
}/* end of kwAcLibUtlBufInit */

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
PUBLIC S16 kwAcLibUtlGetEnt
(
CmLListCp   *lCp,
PTR         fd,
KwAcLibSecEnt **ent
)
#else
PUBLIC S16 kwAcLibUtlGetEnt(lCp, fd, ent)
CmLListCp   *lCp;
PTR         fd;
KwAcLibSecEnt **ent;
#endif
{
   KwAcLibSecEnt *tmpEnt;
   TRC2(kwAcLibUtlGetEnt);

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
}/* end of kwAcLibUtlGetEnt */

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
PUBLIC Void kwAcLibUtlDelEnt
(
CmLListCp   *lCp,
PTR         fd
)
#else
PUBLIC Void kwAcLibUtlDelEnt(lCp, fd)
CmLListCp   *lCp;
PTR         fd;
#endif
{
   KwAcLibSecEnt  *ent;
   TRC2(kwAcLibUtlDelEnt);

   kwAcLibUtlGetEnt(lCp, fd, &ent);
   if(ent == NULLP)
   {
      return;
   }

   cmLListDelFrm(lCp, &ent->listEnt);
   PJ_FREE(ent, sizeof(KwAcLibSecEnt));
   return;
}/* end of kwAcLibUtlDelEnt */

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
PUBLIC S16 kwAcLibUtlInsOutEnt
(
CmLListCp   *lCp,
KwAcLibOutEnt *ent
)
#else
PUBLIC S16 kwAcLibUtlInsOutEnt(lCp, ent)
CmLListCp   *lCp;
KwAcLibOutEnt *ent;
#endif
{

   TRC2(kwAcLibUtlInsOutEnt);

   ent->listEnt.node   =  (PTR)ent;
   cmLListAdd2Tail(lCp, &ent->listEnt);

   RETVALUE(ROK);
}/* end of kwAcLibUtlInsOutEnt */

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
PUBLIC S16 kwAcLibUtlGetOutEnt
(
CmLListCp   *lCp,
U32         id,
KwAcLibOutEnt **ent
)
#else
PUBLIC S16 kwAcLibUtlGetOutEnt(lCp, id, ent)
CmLListCp   *lCp;
U32         id;
KwAcLibOutEnt **ent;
#endif
{
   KwAcLibOutEnt *tmpEnt;
   TRC2(kwAcLibUtlGetOutEnt);

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
}/* end of kwAcLibUtlGetOutEnt */
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
PUBLIC Void kwAcLibUtlDelOutEnt
(
CmLListCp   *lCp,
KwAcLibOutEnt  *ent
)
#else
PUBLIC Void kwAcLibUtlDelOutEnt(lCp, ent)
CmLListCp   *lCp;
KwAcLibOutEnt  *ent;
#endif
{
   TRC2(kwAcLibUtlDelOutEnt);

   cmLListDelFrm(lCp, &ent->listEnt);
   PJ_FREE_BUF(ent->mBuf);
   PJ_FREE(ent, sizeof(KwAcLibOutEnt));
   return;
}/* end of kwAcLibUtlDelOutEnt */
#endif
/********************************************************************30**

         End of file:     kwac_libutl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:31 2014

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
/main/1      ---   mn         1. Initial Release.
*********************************************************************91*/


