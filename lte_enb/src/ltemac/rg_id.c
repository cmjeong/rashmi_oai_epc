


/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code to provide software part number, version and
               revision. 
  
     File:     rg_id.c 
  
     Sid:      rg_id.c@@/main/3 - Sat Jul 30 02:22:00 2011
  
     Prg:      sm
  
**********************************************************************/

/** @file rg_id.c
@brief This file contains the definition of this software's part number, 
       version and revision. Also provides an API to access the same.
*/

/* header include files (.h) */
#include "envopt.h"           /* environment options */  
#include "envdep.h"           /* environment dependent */
#include "envind.h"           /* environment independent */
#include "gen.h"              /* general layer */
#include "ssi.h"              /* system services */
#include "lrg.h"              /* layer manager */
   
/* header/extern include files (.x) */
#include "gen.x"              /* general layer */
#include "ssi.x"              /* system services */
#include "cm_lib.x"           /* common library */


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
EXTERN Void rgGetSId ARGS((SystemId *s));
#ifdef __cplusplus
}
#endif /* __cplusplus */

/* defines */
#define RGSWMV 3             /* LTE MAC- main version */
#define RGSWMR 1             /* LTE MAC - main revision */
#define RGSWBV 0             /* LTE MAC - branch version */
/* Updated the branch revision Number */
#define RGSWBR 2             /* LTE MAC - branch revision */
#define RGSWPN "1000372"     /* LTE MAC - part number */

/* system id */
PRIVATE CONSTANT SystemId sId ={
   RGSWMV,              /* LTE MAC - main version */
   RGSWMR,              /* LTE MAC - main revision */
   RGSWBV,              /* LTE MAC - branch version */
   RGSWBR,              /* LTE MAC - branch revision */
   (Txt *)RGSWPN               /* LTE MAC - part number */
};


/**
 * @brief Retrieve system id. 
 *
 * @details
 *
 *     Function : rgGetSId 
 *    
 *     Get system id consisting of part number, main version and
 *     revision and branch version and branch.
 *     
 *     
 *  @param[out] SystemId *s  
 *  @return  void
 **/
/*
*
*       Fun:   get system id
*
*       Desc:  Get system id consisting of part number, main version and
*              revision and branch version and branch.
*
*       Ret:   TRUE      - ok
*
*       Notes: None
*
*       File:  rg_id.c
*
*/
 
#ifdef ANSI
PUBLIC Void rgGetSId
(
SystemId *s                 /* system id */
)
#else
PUBLIC Void rgGetSId(s)
SystemId *s;                /* system id */
#endif
{
   TRC2(rgGetSId);

   s->mVer = sId.mVer;
   s->mRev = sId.mRev;
   s->bVer = sId.bVer;
   s->bRev = sId.bRev;
   cmMemcpy((U8 *)s->ptNmb, (U8 *)sId.ptNmb, LRG_MAX_PT_NUM_SIZE); 

   /* Stack Crash Problem for TRACE5 Changes. Added the return below */
  RETVOID; 
  
} /* end of rgGetSid */



/**********************************************************************
 
         End of file:     rg_id.c@@/main/3 - Sat Jul 30 02:22:00 2011
 
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
/main/1      ---       sm                1. Initial Release.
/main/1+     rg001.201 sd                1. Patch 1 for LTE MAC 2.1 
/main/1+     rg002.201 sm                1. Patch 2 for LTE MAC 2.1 
/main/1+     rg003.201 pk                1. Patch 3 for LTE MAC 2.1 
/main/1+     rg004.201 sd                1. Patch 4 for LTE MAC 2.1
/main/1+     rg005.201 sm                1. Patch 5 for LTE MAC 2.1
/main/1+     rg006.201 sm                1. Patch 6 for LTE MAC 2.1
/main/1+     rg007.201 gjahagirdar       1. Patch 7 for LTE MAC 2.1
/main/1+     rg008.201 rsharon           1. Patch 8 for LTE MAC 2.1
/main/1+     rg009.201 dv                1. Patch 9 for LTE MAC 2.1
/main/1+     rg010.201 av                1. Patch 10 for LTE MAC 2.1
/main/3      ---       gvj               1. LTE MAC 3.1 Release
/main/3      rg001.301 nudupi            1. Patch 1 for LTE MAC 3.1. 
/main/3      rg002.301 asehgal           1. Patch 2 for LTE MAC 3.1. 
$SID$        ---       rt                1. LTE MAC 4.1 Release.                           
*********************************************************************91*/
