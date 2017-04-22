
/**********************************************************************
 
    Name:   RRC layer
 
    Type:   C include file
 
    Desc:   Defines required by LTE-RRC
 
    File:   nhac_acc.h
 
    Sid:      nhac_acc_cpj.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 20:18:07 2015
 
    Prg:    rer
 
**********************************************************************/
 

/*
*     The defines in this file correspond to structures and variables 
*     used by the following TRILLIUM software:
*
*     part no.             description
*     --------     ----------------------------------------------
*     1000369       RRC
*
*/
 
#ifndef __NHACACCCPJX__
#define __NHACACCCPJX__

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_tkns.h"        /* common tokens                */
#include "cm_inet.h"        /* Inet header file             */
#include "cm_mblk.h"        /* common memory allocation     */
#include "cm_llist.h"      /* common link list */
#include "cm_lte.h"        /* common LTE structures */
#include "cm_xta.h"
#include "cm_pasn.h"
/* external headers */


/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_tkns.x"        /* common tokens                */
#include "cm_mblk.x"        /* common memory allocation     */
#include "cm_inet.x"        /* Inet header file             */
#include "cm_llist.x"      /* common link list */
#include "cm_lte.x"        /* common LTE structures */
#include "cm_xta.x"
#include "cm_pasn.x"

#ifdef __cplusplus
EXTERN "C" {
#endif
typedef struct nhaccCpjEnt
{
   U8  rbId;
   U8  pdcpId;
   U8  cfgType;
   U8  cfgReqBitMask;
   CpjRlcInfo rlcInfo;
   U32  discardTmr;
   CpjHdrCompCfg hdrComCfg;
}NhaccCpjEnt;

typedef struct nhAccCpjSecVal
{
   NhuIntgKeyAlgoInfo   intgCfgInfo;
   NhuCiphKeyAlgoInfo   cipCfgInfo;
   CpjSecCfg            secCfg;
   Bool                 conReCfgCause;
   U8                   secCfgBitMsk;
}NhAccCpjSecVal;

typedef struct nhAccCpjVal
{
   CmLteRnti ueId;
   Bool used;
   U16 tCrnti;
   CmLteCellId cellId;
   U32     transId;
   U8 numEnt;
   NhaccCpjEnt entity[CPJ_MAX_CFG];
   NhAccCpjSecVal secInfo;
}NhAccCpjVal;

#ifdef __cplusplus
}
#endif


#endif

/**********************************************************************
         End of file:     nhac_acc_cpj.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 20:18:07 2015
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      rer                1. LTE RRC Initial Release.
/main/2      ---      ch                 1. RRC Release 2.1.
/main/3      ---      sbalakrishna       1. Updated for Release of 3.1
*********************************************************************91*/


