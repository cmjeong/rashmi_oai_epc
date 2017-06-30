

/********************************************************************20**
  
        Name:     LTE UE Simulator 
    
        Type:     C source file
  
        Desc:     This is the ID file.
 
        File:     ue_id.c

        Sid:      ue_id.c@@/main/1 - Sun Mar 28 22:59:23 2010
  
        Prg:      vp
  
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

  
/* ue010.101 : changes for placing correct prefix */
/* local defines */

#define UESWMV 1             /* UESIM - main version */
#define UESWMR 1             /* UESIM - main revision */
#define UESWBV 0             /* UESIM - branch version */
#define UESWBR 10             /* UESIM - branch revision */
#define UESWPN "1000421"     /* UESIM - part number */

/* local typedefs */

/* local externs */
  
/* forward references */

/* public variable declarations */

#ifdef __cplusplus
EXTERN "C" {
#endif /* CPLUSPLUS */

EXTERN S16 ueGetSId ARGS((SystemId *s));
#ifdef __cplusplus
}
#endif /* CPLUSPLUS */

/* copyright banner */

PUBLIC CONSTANT Txt ueBan1[] =
   {"(c) COPYRIGHT 1989-2002, Trillium Digital Systems, Inc."};

PUBLIC CONSTANT Txt ueBan2[] =
   {"                 All rights reserved."};

/* system id */

PRIVATE CONSTANT SystemId sId ={
   UESWMV,              /* UESIM - main version */
   UESWMR,              /* UESIM - main revision */
   UESWBV,              /* UESIM - branch version */
   UESWBR,              /* UESIM - branch revision */
   UESWPN               /* UESIM - part number */
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
*       File:  ue_id.c
*
*/

#ifdef ANSI
PUBLIC S16 ueGetSId
(
SystemId *s                 /* system id */
)
#else
PUBLIC S16 ueGetSId(s)
SystemId *s;                /* system id */
#endif
{
   TRC2(ueGetSId);

   s->mVer = sId.mVer;
   s->mRev = sId.mRev;
   s->bVer = sId.bVer;
   s->bRev = sId.bRev;
   s->ptNmb = sId.ptNmb;

   RETVALUE(TRUE);

} /* end of ueGetSId */

  
/********************************************************************30**
  
         End of file:     ue_id.c@@/main/1 - Sun Mar 28 22:59:23 2010
  
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
/main/1      ---       vp   1. initial release.
/main/1      ue001.101 rrm  2. decoding NAS pdu from RRC reconfig req.
                              correcting product part number
/main/1+     ue002.101 sv   1. Multi ue support changes.
                            2. Changes to support MSPD CL.
                            3. Changes to read the configuration parameters
                               from file. 
                            4. Changes to support TDD mode. 
                            5. Klocworks and memory leak fixes.
/main/1+     ue003.101 rp   1. Dedicated bearer support changes.
                            2. Ue Detach support changes.
                            3. Paging support changes.
                            4. TimingAdvance command Support.
                            5. SystemInformations(SI) handling changes.
/main/1+     ue004.101 rk   1. Patch ue004.101 Release
/main/1+     ue005.101 cshekar 1. Ue Capability support changes.
/main/1+     ue006.101 sgm  1. Fixed compiler warning due to #define being too 
                               big for parameter to ueAppStartTmr().
/main/1+     ue007.101 pmacharla  1. Patch ue007.101 release
/main/1+     ue008.101 ragrawal   1. Patch ue008.101 release
/main/1+     ue010.101 akaranth   1. Patch ue010.101 release
*********************************************************************91*/
