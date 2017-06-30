


/**********************************************************************
  
     Name:     LTE RRC  Software Identifier
  
     Type:     C source file
  
     Desc:     Structure for software part number, version, and
               revision.

     File:     nh_id.c
  
     Sid:      ni_id.c@@/main/3 - Fri Jul  1 01:13:18 2011
 
     Prg:      vk
  
**********************************************************************/
  


/*
*     This software may be combined with the following TRILLIUM
*     software:
*
*     part no.                      description
*     --------    ----------------------------------------------
*     1000369     LTE RRC
*
*/



/* Header include files (.h) */

#include "envopt.h"           /* Environment options */  
#include "envdep.h"           /* Environment dependent */
#include "envind.h"           /* Environment independent */

#include "gen.h"              /* General layer */
#include "ssi.h"              /* System services */


/* Header/extern include files (.x) */

#include "gen.x"              /* General layer */
#include "ssi.x"              /* System services */

/* defines */

#define NHSWMV 3             /* RRC - main version */
#define NHSWMR 1             /* RRC - main revision */
#define NHSWBV 0             /* RRC - branch version */
#define NHSWBR 2             /* RRC - branch revision nh002.301*/
#define NHSWPN "1000369"     /* RRC - part number. Caution: When this
                              * string is modified the 
                              * LNH_PART_NUM_SIZE must be modified in
                              * lnh.h
                              */

/* Public variable declarations */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

EXTERN S16 nhGetSId ARGS((SystemId *sysId));

#ifdef __cplusplus
}
#endif /* __cplusplus */
  
/* Copyright banner */
  
PUBLIC CONSTANT Txt nhBan1[] =
   {"(c)Copyright 2012 by RadiSys Corporation." };

PUBLIC CONSTANT Txt nhBan2[] =
   {"                 All rights reserved."};
  
/* System ID */
  
PRIVATE CONSTANT SystemId sId ={
   NHSWMV,              /* RRC - main version */
   NHSWMR,              /* RRC - main revision */
   NHSWBV,              /* RRC - branch version */
   NHSWBR,              /* RRC - branch revision */
   NHSWPN               /* RRC - part number */
};

   
/******************************************************************************
*
*       Fun:   nhGetSId
*
*       Desc:  Get system ID consisting of part number, main version and
*              revision, and branch version and branch.
*
*       Ret:   TRUE - OK
*
*       Notes: None
*
*       File:  nh_id.c
*
******************************************************************************/
 
#ifdef ANSI
PUBLIC S16 nhGetSId
(
SystemId *sysId                 /* System ID */
)
#else /* ANSI */
PUBLIC S16 nhGetSId(sysId)
SystemId *sysId;                /* System ID */
#endif /* ANSI */
{
   TRC2(nhGetSId);


   sysId->mVer = sId.mVer;
   sysId->mRev = sId.mRev;
   sysId->bVer = sId.bVer;
   sysId->bRev = sId.bRev;
   sysId->ptNmb = sId.ptNmb;

   RETVALUE(TRUE);

} /* end of function nhGetSid */

/**********************************************************************
         End of file:     ni_id.c@@/main/3 - Fri Jul  1 01:13:18 2011
**********************************************************************/

/**********************************************************************
        Revision history:
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      vk                1. RRC Initial Release.
/main/2      ---      vk                1. Updated for RRC release 2.1
             ---      chebli            1. Patch Release nh001.201.
             ---      vkulkarni         1. Patch Release nh002.201.
             ---      vkulkarni         1. Patch Release nh003.201.
             ---      vkulkarni         1. Patch Release nh004.201.
/main/3      ---      sbalakrishna      1. Updated for Release of 3.1.
/main/3      ---      sbalakrishna      1. Patch Release nh001.301.
             ---      mpatel            1. Patch Release nh002.301.         
             ---      njha              1. Patch Release nh003.301. 
*********************************************************************91*/
