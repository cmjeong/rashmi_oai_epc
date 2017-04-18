

/************************************************************************
 
     Name:     Common LTE
  
     Type:     C source file
  
     Desc:     C code for packing/unpacking of cm_lte data structures. 
  
     File:     cm_lte.c 
  
     Sid:      cm_lte.c@@/main/2 - Fri Nov 13 14:09:17 2009
  
     Prg:      sm
  
**********************************************************************/

/* header include files (.h) */

#include "envopt.h"             /* environment options */  
#include "envdep.h"             /* environment dependent */
#include "envind.h"             /* environment independent */

#include "gen.h"                /* general */
#include "ssi.h"                /* system services interface */
#include "cm_lte.h"             /* common lte header file */

/* header/extern include files (.x) */

#include "gen.x"                /* general */
#include "ssi.x"                /* system services interface */
#include "cm_lte.x"             /* common lte header file */
#include "cm_lib.x"             /* common library functions header file */

/* public variable declarations */
PUBLIC U32 cmLteTime;


/***********************************************************
*
*     Func : cmPkLteRlcId
*
*
*     Desc : RLC Identifier
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkLteRlcId
(
CmLteRlcId *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkLteRlcId(param, mBuf)
CmLteRlcId *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkLteRlcId);

   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   CMCHKPK(cmPkLteRnti, param->ueId, mBuf);
   CMCHKPK(SPkU8, param->rbType, mBuf);
   CMCHKPK(cmPkLteRbId, param->rbId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkLteRlcId
*
*
*     Desc : RLC Identifier
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkLteRlcId
(
CmLteRlcId *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLteRlcId(param, mBuf)
CmLteRlcId *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkLteRlcId);

   CMCHKUNPK(cmUnpkLteRbId, &param->rbId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->rbType, mBuf);
   CMCHKUNPK(cmUnpkLteRnti, &param->ueId, mBuf);
   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkLteTimingInfo
*
*
*     Desc : LTE Timing Info
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkLteTimingInfo
(
CmLteTimingInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkLteTimingInfo(param, mBuf)
CmLteTimingInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkLteTimingInfo);

   CMCHKPK(SPkU8, param->subframe, mBuf);
   CMCHKPK(SPkU16, param->sfn, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkLteTimingInfo
*
*
*     Desc : LTE Timing Info
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkLteTimingInfo
(
CmLteTimingInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLteTimingInfo(param, mBuf)
CmLteTimingInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkLteTimingInfo);

   CMCHKUNPK(SUnpkU16, &param->sfn, mBuf);
   CMCHKUNPK(SUnpkU8, &param->subframe, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkLtePdcpId
*
*
*     Desc : PDCP Id
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkLtePdcpId
(
CmLtePdcpId *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkLtePdcpId(param, mBuf)
CmLtePdcpId *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkLtePdcpId);

   CMCHKPK(SPkU8, param->rbType, mBuf);
   CMCHKPK(cmPkLteRbId, param->rbId, mBuf);
   CMCHKPK(cmPkLteRnti, param->ueId, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkLtePdcpId
*
*
*     Desc : PDCP Id
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkLtePdcpId
(
CmLtePdcpId *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLtePdcpId(param, mBuf)
CmLtePdcpId *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkLtePdcpId);

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteRnti, &param->ueId, mBuf);
   CMCHKUNPK(cmUnpkLteRbId, &param->rbId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->rbType, mBuf);
   RETVALUE(ROK);
}


/**********************************************************************
 
         End of file:     cm_lte.c@@/main/2 - Fri Nov 13 14:09:17 2009
 
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
/main/1      ---     sm                1. Initial Release.
*********************************************************************91*/
