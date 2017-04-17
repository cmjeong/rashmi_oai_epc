
/********************************************************************20**
  
     Name:     x2ap - id
  
     Type:     C source file
  
     Desc:     Structure for software part number, version and
               revision.

     File:     cz_id.c
  
     Sid:      tr_id.c@@/main/2 - Tue Aug 30 18:36:12 2011
 
     Prg:      sy
  
*********************************************************************21*/

/* header include files (.h) */

#include "envopt.h"           /* environment options */
#include "envdep.h"           /* environment dependent */
#include "envind.h"           /* environment independent */

#include "gen.h"              /* general layer */
#include "ssi.h"              /* system services */
#include "cm5.h"              /* Common timer library            */
#include "lcz.h"              /* layer manager macros */

/* header/extern include files (.x) */

#include "gen.x"              /* general layer */
#include "ssi.x"              /* system services */
#include "cm5.x"           /* Common timer module             */
#include "cm_lib.x"        /* Common library function         */

/* defines */

#define CZSWMV 3             /* x2ap - main version */
#define CZSWMR 1             /* x2ap - main revision */
#define CZSWBV 0             /* x2ap - branch version */
/*cz001.301:Modified GPR label*/
#define CZSWBR 1             /* x2ap - cz001.301 */
#define CZSWPN "1000373"     /* x2ap - part number */

/* public variable declarations */

#ifdef __cplusplus
extern "C" {
#endif

EXTERN S16 czGetSId ARGS((SystemId *s));

#ifdef __cplusplus
}
#endif

/* copyright banner */

PUBLIC CONSTANT Txt czBan1[] =
   {"(c) COPYRIGHT 1989-2002, Trillium Digital Systems, Inc."};

PUBLIC CONSTANT Txt czBan2[] =
   {"                 All rights reserved."};

/* system id */

PRIVATE CONSTANT SystemId sId ={
   CZSWMV,              /* x2ap - main version */
   CZSWMR,              /* x2ap - main revision */
   CZSWBV,              /* x2ap - branch version */
   CZSWBR,              /* x2ap - branch revision */
   CZSWPN               /* x2ap - part number */
};

/*
*     support functions
*/

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
*       File:  cz_id.c
*
*/

#ifdef ANSI
PUBLIC S16 czGetSId
(
SystemId *s                 /* system id */
)
#else
PUBLIC S16 czGetSId(s)
SystemId *s;                /* system id */
#endif
{
   TRC2(czGetSId);

   s->mVer = sId.mVer;
   s->mRev = sId.mRev;
   s->bVer = sId.bVer;
   s->bRev = sId.bRev;
   cmMemcpy((U8 *)s->ptNmb, (U8 *)sId.ptNmb, LCZ_MAX_PT_NUM_SIZE);

   RETVALUE(TRUE);

} /* end of czGetSid */

/*********************************************************************
  
         End of file:     tr_id.c@@/main/2 - Tue Aug 30 18:36:12 2011
 
**********************************************************************/

/**********************************************************************
  
        Notes:
  
**********************************************************************/

/**********************************************************************

**********************************************************************/

/********************************************************************
  
        Revision history:
  
**********************************************************************/

/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---        sy             1. LTE-X2AP Initial Release.
            cz001.101   mm             1. CR Fixes, Memory Leak fixes.
/main/2      ---        pt             1. LTE-X2AP 3.1 release.
/main/3     cz001.301  akaranth        1. Updated for cz001.301 patch.
*********************************************************************91*/
