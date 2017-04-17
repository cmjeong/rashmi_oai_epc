

/********************************************************************20**
  
        Name:     <name for the file for readability>
    
        Type:     <File type - C include file, C source file, make file>
  
        Desc:     <description of file contents>
 
        File:     kw_id.c

        Sid:      kw_id.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:47 2014
  
        Prg:      gk
  
*********************************************************************21*/
 

/*
 *      This software may be combined with the following TRILLIUM
 *      software:
 *
 *      part no.                      description
 *      --------    ----------------------------------------------
 *    
 */

  
/* header include files (.h) */
  
#include "envopt.h"             /* environment options */  
#include "envdep.h"             /* environment dependent */
#include "envind.h"             /* environment independent */

#include "gen.h"                /* general */
#include "ssi.h"                /* system services interface */

/* header/extern include files (.x) */

#include "gen.x"                /* general */
#include "ssi.x"                /* system services interface */

  
/* local defines */

#define KWSWMV 2             /* rlc - main version */
#define KWSWMR 1             /* rlc - main revision */
#define KWSWBV 0             /* rlc - branch version */
#define KWSWBR 5             /* rlc -  kw005.201 patch level */
#define KWSWPN "1000371"     /* rlc - part number */

/* local typedefs */

/* local externs */
  
/* forward references */

/* public variable declarations */

#ifdef __cplusplus
EXTERN "C" {
#endif /* CPLUSPLUS */

EXTERN S16 kwGetSId ARGS((SystemId *s));
#ifdef __cplusplus
}
#endif /* CPLUSPLUS */

/* copyright banner */

PUBLIC CONSTANT Txt kwBan1[] =
   {"(c) COPYRIGHT 1989-2002, Trillium Digital Systems, Inc."};

PUBLIC CONSTANT Txt kwBan2[] =
   {"                 All rights reserved."};

/* system id */

PRIVATE CONSTANT SystemId sId ={
   KWSWMV,              /* rlc - main version */
   KWSWMR,              /* rlc - main revision */
   KWSWBV,              /* rlc - branch version */
   KWSWBR,              /* rlc - branch revision */
   KWSWPN               /* rlc - part number */
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
*       File:  kw_id.c
*
*/

#ifdef ANSI
PUBLIC S16 kwGetSId
(
SystemId *s                 /* system id */
)
#else
PUBLIC S16 kwGetSId(s)
SystemId *s;                /* system id */
#endif
{
   TRC2(kwGetSId);

   s->mVer = sId.mVer;
   s->mRev = sId.mRev;
   s->bVer = sId.bVer;
   s->bRev = sId.bRev;
   s->ptNmb = sId.ptNmb;

   RETVALUE(TRUE);

} /* end of kwGetSId */

  
/********************************************************************30**
  
         End of file:     kw_id.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:47 2014
  
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
/main/1      ---         gk   1. initial release.
/main/2      ---         nm   1. LTERLC Release 2.1
/main/3      kw001.201   vp   1. Patch  for HENB, changes for max RBs
                               in cell and avoidance of float variables.
/main/4      kw002.201   vp   1. Patch for optimization,fixes for multi-region
                                 and retransmission.
/main/5      kw003.201 vp  1. Fixes for re-segmentation, segement offset
                               value and optimization 
/main/6      kw004.201   ap 1. Added traces.
                            2. Modified the trace Indication function
/main/7      kw005.201   ap 1. Support for R9 in RLC and PDCP
                            2. Support for L2 Measurement in RLC and PDCP
                            3. Fixes for internal CR.
                            4. Fixes for Customer raised defects.
*********************************************************************91*/

