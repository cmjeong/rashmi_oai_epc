

/********************************************************************20**

     Name:     System Services -- identification file

     Type:     C source file

     Desc:     Version information

     File:     ss_id.c

     Sid:      ss_id.c@@/main/2 - Mon Apr  5 18:01:16 2010

     Prg:      kp

*********************************************************************21*/


/* header include files (.h) */

#include "envopt.h"           /* environment options */
#include "envdep.h"           /* environment dependent */
#include "envind.h"           /* environment independent */

#include "gen.h"              /* general layer */
#include "ssi.h"              /* system services */


/* header/extern include files (.x) */

#include "gen.x"              /* general layer */
#include "ssi.x"              /* system services */


/* defines */

#define SSSWMV 3              /* main version */
#define SSSWMR 1              /* main revision */
#define SSSWBV 0              /* branch version */
#define SSSWBR 0            /* branch revision */
#define SSSWPN "1078001"      /* part number */


/* public variable declarations */


/* copyright banner */

CONSTANT PUBLIC Txt ssBan1[] ={"(c) COPYRIGHT 1989-1998, Trillium Digital Systems, Inc."};
CONSTANT PUBLIC Txt ssBan2[] ={"                 All rights reserved."};

/* system id */

/* ss041.103 */
PRIVATE CONSTANT SystemId ssSId =  
{
   SSSWMV,                    /* main version */
   SSSWMR,                    /* main revision */
   SSSWBV,                    /* branch version */
   SSSWBR,                    /* branch revision */
   SSSWPN,                    /* part number */
};

/* ss041.103 */
#ifdef SS_SID_CHANGE
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
*       File:  ss_id.c
*
*/

#ifdef ANSI
PUBLIC S16 SGetInDepSId
(
SystemId *s                 /* system id */
)
#else
PUBLIC S16 SGetInDepSId(s)
SystemId *s;                /* system id */
#endif
{
   TRC2(ssGetSId)
   s->mVer = ssSId.mVer;
   s->mRev = ssSId.mRev;
   s->bVer = ssSId.bVer;
   s->bRev = ssSId.bRev;
   s->ptNmb = ssSId.ptNmb;
   RETVALUE(TRUE);
} /* end of SGetInDepSId */
#endif /* SS_SID_CHANGE */

/* ss038.103 */

/********************************************************************30**

         End of file:     ss_id.c@@/main/2 - Mon Apr  5 18:01:16 2010

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
/main/3      ---      ch   1. initial release
*********************************************************************91*/
