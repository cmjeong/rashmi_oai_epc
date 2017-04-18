


  
  
/********************************************************************20**
  
     Name:     common functions - linked list management
  
     Type:     C source file
  
     Desc:     common functions for linked lists
  
     File:     rg_sch_utl_clist.c
  
     Sid:      gk_sch_utl_clist.c@@/main/2 - Sat Jul 30 02:21:53 2011
 
     Prg:      rr
  
*********************************************************************21*/
  
/* header include files (.h) */

#include "envopt.h"        /* environment options */  
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */

/* header/extern include files (.x) */
  
#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */
#include "rg_sch_clist.x"      /* common functions */


/* Linked List functions */


/*
*
*       Fun:   rgSCHRrCListInit
*
*       Desc:  initializes a linked list control pointer.
*
*       Ret:   ROK   - ok
*
*       Notes: None
*
*       File:  rr_clist.c
*
*/
#ifdef ANSI
PUBLIC Void rgSCHRrCListInit
(
RgSchRrCListCp *lCp                /* list control point */
)
#else 
PUBLIC Void rgSCHRrCListInit(lCp)
RgSchRrCListCp *lCp;               /* list control point */
#endif
{
   TRC2(rgSCHRrCListInit);
   
   lCp->first = (RgSchRrCList *)NULLP;
   lCp->crnt  = (RgSchRrCList *)NULLP;
   lCp->count = 0;

   RETVOID;
} /* end of rgSCHRrCListInit */

/* LTE_ADV_FLAG_REMOVED_START */
/*
 *        Fun:   rgSCHRrCListAdd2Crnt
 * 
 *        Desc:  adds node to linked list behind crnt.
 * 
 *        Ret:   ROK   - ok
 * 
 *        Notes: None
 * 
 *        File:  rr_clist.c
 */
#ifdef ANSI
PUBLIC Void rgSCHRrCListAdd2Crnt
(
 RgSchRrCListCp *lCp,               /* list control point */
 RgSchRrCList   *node               /* node to be added */
 )
#else
PUBLIC Void rgSCHRrCListAdd2Crnt(lCp, node)
   RgSchRrCListCp *lCp;               /* list control point */
   RgSchRrCList   *node;              /* node to be added */
#endif
{
   TRC2(rgSCHRrCListAdd2Crnt);
#ifdef ERRCHK
   if (lCp == (RgSchRrCListCp *)NULLP)
      RETVOID;
#endif

   lCp->count++;

   if(!lCp->first)
   {
      node->prev = node;
      node->next = node;
      lCp->first = node;

      lCp->crnt = lCp->first;

      RETVOID;
   }

   node->next = lCp->crnt;
   node->prev = lCp->crnt->prev;
   lCp->crnt->prev->next = node;
   lCp->crnt->prev = node;

   RETVOID;
}
/* LTE_ADV_FLAG_REMOVED_END */

/*
*
*       Fun:   rgSCHRrCListAdd2Tail
*
*       Desc:  adds node to linked list after last.
*
*       Ret:   ROK   - ok
*
*       Notes: None
*
*       File:  rr_clist.c
*
*/
#ifdef ANSI
PUBLIC Void rgSCHRrCListAdd2Tail
(
RgSchRrCListCp *lCp,               /* list control point */
RgSchRrCList   *node               /* node to be added */
)
#else 
PUBLIC Void rgSCHRrCListAdd2Tail(lCp, node)
RgSchRrCListCp *lCp;               /* list control point */
RgSchRrCList   *node;              /* node to be added */
#endif
{
   TRC2(rgSCHRrCListAdd2Tail);

#ifdef ERRCHK
   if (lCp == (RgSchRrCListCp *)NULLP)
      RETVOID;
#endif
 
   lCp->count++;

   if(!lCp->first)
   {
      node->prev = node;
      node->next = node;
      lCp->first = node;

      lCp->crnt = lCp->first;

      RETVOID;
   }

   node->next = lCp->first;
   node->prev = lCp->first->prev;
   lCp->first->prev->next = node;
   lCp->first->prev = node;

   RETVOID;
} /* end of rgSCHRrCListAdd2Tail */

/*
*
*       Fun:   rgSCHRrCListDelFrm
*
*       Desc:  remove node pointed to by nodePtr from list and return node.
*              nodePtr could be anywhere in the list.
*              - resets crnt to NULLP.
*
*       Ret:   pointer
*
*       Notes: None
*
*       File:  rr_clist.c
*
*/
#ifdef ANSI
PUBLIC RgSchRrCList *rgSCHRrCListDelFrm
(
RgSchRrCListCp *lCp,                /* list control pointer */
RgSchRrCList *node                  /* node to be removed */
)
#else 
PUBLIC RgSchRrCList *rgSCHRrCListDelFrm(lCp, node)
RgSchRrCListCp *lCp;               /* list control pointer */
RgSchRrCList *node;                /* node to be removed */
#endif
{
   TRC2(rgSCHRrCListDelFrm);
  
#ifdef ERRCHK
   if (lCp == (RgSchRrCListCp *)NULLP)
      RETVALUE(NULLP);
#endif

   if(lCp->count == 0)
   {
      RETVALUE(NULLP);
   }
   if (lCp->count == 1)
   {
      if(lCp->first == node)
      {
         lCp->first = lCp->crnt = (RgSchRrCList *)NULLP;
         lCp->count = 0;
         node->next = node->prev = (RgSchRrCList *)NULLP;
         RETVALUE(node);
      }
      RETVALUE(NULLP);
   }
   
   if (lCp->first == node)
   {
      lCp->first->prev->next = node->next;
      node->next->prev = lCp->first->prev;
      lCp->first = node->next;
      if(lCp->crnt == node)
      {
         lCp->crnt = node->next;
      }
      node->next = node->prev = (RgSchRrCList *)NULLP;
       /* Adding this check and guarding the decrement of counter when
       node is deleted with reshuffling */
      lCp->count--;
      RETVALUE(node);
   }

   if(node->prev && node->next)
   {
      node->prev->next = node->next;
      node->next->prev = node->prev;
      lCp->count--;
   }
   if(lCp->crnt == node)
   {
      lCp->crnt = node->next;
   }
   node->next = node->prev = (RgSchRrCList *)NULLP;
   RETVALUE(node);
} /* end of rgSCHRrCListDelFrm */

/*
*
*       Fun:   rgSCHRrCListInsrtAtCrnt
*
*       Desc:  Inserting the given node at CuRRENT and Moving present CURRENT 
*              node to next.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  rr_clist.c
*
*/
#ifdef ANSI
PUBLIC Void rgSCHRrCListInsrtAtCrnt
(
RgSchRrCListCp *lCp,                /* list control pointer */
RgSchRrCList *node                  /* node to be removed */
)
#else 
PUBLIC Void rgSCHRrCListInsrtAtCrnt(lCp, node)
RgSchRrCListCp *lCp;               /* list control pointer */
RgSchRrCList *node;                /* node to be inserted */
#endif
{
   RgSchRrCList *crnt;
   TRC2(rgSCHRrCListInsrtAtCrnt);

#ifdef ERRCHK
   if (lCp == (RgSchRrCListCp *)NULLP)
      RETVOID;
#endif

   crnt = lCp->crnt;
   lCp->crnt = node;

   node->prev = crnt->prev;
   crnt->prev->next = node;
   node->next = crnt;
   crnt->prev = node;

   lCp->count++;

   RETVOID;
}

/********************************************************************30**
  
         End of file:     gk_sch_utl_clist.c@@/main/2 - Sat Jul 30 02:21:53 2011
   
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

  version    pat  init                   description
----------- ----- ----  ------------------------------------------------
/main/1      ---  rr    1. initial release
        rg003.201 ns    1. tarce added to functions.
        rg004.201 ms    1. Functions and Datatypes starting 
                           with rr are renamed as rgSchRr
        rg005.201 sm    1. Fix for CR ccpu00110744
/main/2      ---        gvj  1. Updated for LTE MAC Rel 3.1           
$SID$        ---  rt    1. LTE MAC 4.1 release
*********************************************************************91*/
