


/********************************************************************20**
  
     Name:     common - linked list functions
  
     Type:     C include file
  
     Desc:     Structures, variables and typedefs required by the
               linked list management routines.
 
     File:     rg_sch_clist.x
  
     Sid:      rg_sch_clist.x@@/main/2 - Sat Jul 30 02:22:01 2011
    
     Prg:      rr
 
*********************************************************************21*/
  
#ifndef __RGSCHRRCLIST__
#define __RGSCHRRCLIST__

#ifdef __cplusplus
extern "C" {
#endif


typedef struct rgSchRrCList   RgSchRrCList;
typedef struct rgSchRrCListCp RgSchRrCListCp;

/* doubly linked list */
struct rgSchRrCList
{
   RgSchRrCList *next;        /* next */
   RgSchRrCList *prev;        /* previous */
   PTR    node;          /* node */
};

struct rgSchRrCListCp
{
   RgSchRrCList *first;       /* first entry in list */
   RgSchRrCList *crnt;        /* entry last accessed */
   U32     count;        /* number of entries */
};

EXTERN Void         rgSCHRrCListInit     ARGS ((RgSchRrCListCp *lList));
EXTERN Void         rgSCHRrCListAdd2Tail ARGS ((RgSchRrCListCp *lList, \
                                                    RgSchRrCList *node));
/* Renamed functions to start with rgSCH */
EXTERN RgSchRrCList *rgSCHRrCListDelFrm   ARGS ((RgSchRrCListCp *lList, \
                                                    RgSchRrCList *node));
EXTERN Void         rgSCHRrCListInsrtAtCrnt ARGS ((RgSchRrCListCp *lList, \
                                                    RgSchRrCList *node));
/* LTE_ADV_FLAG_REMOVED_START */
EXTERN Void rgSCHRrCListAdd2Crnt ARGS ((RgSchRrCListCp *lList, \
                                        RgSchRrCList   *node));
/* LTE_ADV_FLAG_REMOVED_END */


#ifdef __cplusplus
}
#endif

#endif /* __RRCLIST__ */

/**********************************************************************
 
         End of file:     rg_sch_clist.x@@/main/2 - Sat Jul 30 02:22:01 2011
 
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
/main/1      ---     rr   1. LTE MAC 2.1 release
          rg004.201  ms   1. Functions and Datatypes starting 
                             with rr are renamed as rgSchRr
/main/2      ---        gvj  1. Updated for LTE MAC Rel 3.1           
$SID$        ---     rt   1. LTE MAC 4.1 Release.                           
*********************************************************************91*/
