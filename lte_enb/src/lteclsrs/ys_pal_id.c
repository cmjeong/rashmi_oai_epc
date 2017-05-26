
/************************************************************************
 
     Name:     LTE MAC Convergence Layer
  
     Type:     C source file
  
     Desc:     C source code for Entry point fucntions
  
     File:     ys_id.c
  
     Sid:      ys_id.c@@/main/2 - Thu Dec  2 02:27:14 2010
  
     Prg:      rk
  
**********************************************************************/

/** @file ys_id.c
@brief This module acts as an interface handler for upper interface and 
manages Pst and Sap related information for upper interface APIs.
*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "lys.h"           /* layer management defines for LTE-CL */

/* header/extern include files (.x) */
#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm_lib.x"        /* common library */


/* defines */
#define YSSWMV 1             /* CL- main version */
#define YSSWMR 2             /* CL - main revision */
#define YSSWBV 0             /* CL - branch version */
#define YSSWBR 5             /* CL - branch revision ys005.102 */
#define YSSWPN "1000414"     /* CL - part number */

PUBLIC Void ysGetSId ARGS((SystemId *s));

/* system id */
PRIVATE CONSTANT SystemId sId ={
   YSSWMV,              /* CL - main version */
   YSSWMR,              /* CL - main revision */
   YSSWBV,              /* CL - branch version */
   YSSWBR,              /* CL - branch revision */
   YSSWPN               /* CL - part number */
};


/**
 * @brief Retrieve system id. 
 *
 * @details
 *
 *     Function : ysGetSId 
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
*       File:  ys_id.c
*
*/

#ifdef ANSI
PUBLIC Void ysGetSId
(
SystemId *s                 /* system id */
)
#else
PUBLIC Void ysGetSId(s)
SystemId *s;                /* system id */
#endif
{
   TRC2(ysGetSId);

   s->mVer = sId.mVer;
   s->mRev = sId.mRev;
   s->bVer = sId.bVer;
   s->bRev = sId.bRev;
   cmMemcpy((U8 *)s->ptNmb, (U8 *)sId.ptNmb, LYS_PT_NUM_SIZE); 
   RETVOID;
} /* end of ysGetSid */

/********************************************************************30**
  
         End of file:     ys_id.c@@/main/2 - Thu Dec  2 02:27:14 2010
  
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
----------- -------- ---- -----------------------------------------------
/main/2      ---     sgm                   1. eNodeB 1.2 release
/main/2     ys001.102 rk     1. Patch 1 release for LTE CL 1.2
/main/2     ys002.102 rk     1. Patch 2 release for LTE CL 1.2
/main/2     ys003.102 sgm    1. Fix for CID:1622-02-01 DefectId:ccpu00115333
                                adding Cell delete feature for PAL.
/main/2      ys004.102     pmacharla       1. Patch 4 release for LTE CL 1.2
/main/2      ys005.102     pbyadgi    1. Patch 5 release for LTE CL 1.2
*********************************************************************91*/
