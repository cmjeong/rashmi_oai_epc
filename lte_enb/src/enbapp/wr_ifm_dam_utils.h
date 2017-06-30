


/***********************************************************************
^L
************************************************************************

   Name: DAM Layer

   Type: C Include File
   
   Desc: Defines required by DAM

   File: wr_ifm_dam_utils.h

   Sid:      wr_ifm_dam_utils.h@@/main/TeNB_Main_BR/5 - Mon Aug 11 16:53:14 2014

   Prg : mm

************************************************************************/

#ifndef __WRIFMDAMUTL_H__
#define __WRIFMDAMUTL_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "wr.h"
#include "wr_umm.h"
#include "wr_dam.h"
#include "wr_lwr.h"

#define DAM_SEL_LC 2
#define DAM_SEL_TC 1
#define DAM_SEL_LWLC 0

/* added event types for DAM  */
#define    EVTDAMPRNTTHPTREQ        1  /*  DAM  Throughput Req */
#define    EVTDAMTNLCRETREQ         2  /*  DAM  Tunnel Create Request */
#define    EVTDAMTNLCRETCFM         3  /*  DAM  Tunnel Create Confirm */
#define    EVTDAMTNLDELTREQ         4  /*  DAM  Tunnel Delete Request */
#define    EVTDAMUEDELTREQ          5  /*  DAM  UE Delete Request */
#define    EVTDAMUEDELTCFM          6  /*  DAM  UE Delete Confirm */
#define    EVTDAMCELLADDREQ         7  /*  DAM  CELL Add Request */
#define    EVTDAMRECFGREQ           8  /*  DAM  Reconfiguration Request */
#define    EVTDAMRESTREQ            9   /* DAM Re-Establishment Request */
#define    EVTDAMTNLSTCHNGREQ       10  /* DAM Tunnel State Change Req */
#define    EVTDAMREESTABCFM         11  /* DAM Re-establishement Confirm */
#define    EVTDAMINACTIVITYTMR      12  /* DAM UE Inactivity Timer */
#define    EVTDAMUESTOPTMR          13  /* DAM UE Stop Timer    */
#define    EVTDAMALARMIND           14  /* DAM Alarm indication    */
#define    EVTDAMCFGREQ             15  /* DAM Gen Config Request    */
#define    EVTDAMCNTRLREQ           16  /* DAM Control Request    */
#define    EVTDAMCFGCFM             17  /* DAM Gen Config Confirm    */
#define    EVTDAMCNTRLCFM           18  /* DAM Control Confirm    */
#define    EVTDAMTNLMODCFM          19  /* DAM  Tunnel Modify Confirm */
#define    EVTDAMTNLMODREQ          20  /* DAM  Tunnel Modify Req */
#define    EVTDAMPDCPDATCFM         21  /* DAM  PDCP DAT CFM*/
#define    EVTDAMCTXTRELREQ         22  /* DAM  UE Ctxt Rel Req*/
#define    EVTDAMHDLHOFAIL          23  /* DAM  Handle HO Req */
#define    EVTDAMEGTERRIND          24  /* DAM  to WR EGT-U Err Ind*/
#define    EVTDAMDATRCVDFLAG        25  /* DAM Set Data Rcvd Flag */
#define    EVTDAMBNDREQ             26  /* DAM Bind Req */
#define    EVTDAMBNDCFM             27  /* DAM Bind Cfm */
#define   ERRDAM       0         /* error base */

#define   EDAM001      (ERRDAM +    1)   /*wr_ifm_dam_utils.c: 163 */
#define   EDAM002      (ERRDAM +    2)   /*wr_ifm_dam_utils.c: 164 */
#define   EDAM003      (ERRDAM +    3)   /*wr_ifm_dam_utils.c: 187 */
#define   EDAM004      (ERRDAM +    4)   /*wr_ifm_dam_utils.c: 188 */
#define   EDAM005      (ERRDAM +    5)   /*wr_ifm_dam_utils.c: 214 */
#define   EDAM006      (ERRDAM +    6)   /*wr_ifm_dam_utils.c: 215 */
#define   EDAM007      (ERRDAM +    7)   /*wr_ifm_dam_utils.c: 239 */
#define   EDAM008      (ERRDAM +    8)   /*wr_ifm_dam_utils.c: 240 */
#define   EDAM009      (ERRDAM +    9)   /*wr_ifm_dam_utils.c: 265 */
#define   EDAM010      (ERRDAM +   10)   /*wr_ifm_dam_utils.c: 266 */
#define   EDAM011      (ERRDAM +   11)   /*wr_ifm_dam_utils.c: 290 */
#define   EDAM012      (ERRDAM +   12)   /*wr_ifm_dam_utils.c: 291 */
#define   EDAM013      (ERRDAM +   13)   /*wr_ifm_dam_utils.c: 329 */
#define   EDAM014      (ERRDAM +   14)   /*wr_ifm_dam_utils.c: 332 */
#define   EDAM015      (ERRDAM +   15)   /*wr_ifm_dam_utils.c: 334 */
#define   EDAM016      (ERRDAM +   16)   /*wr_ifm_dam_utils.c: 335 */
#define   EDAM017      (ERRDAM +   17)   /*wr_ifm_dam_utils.c: 336 */
#define   EDAM018      (ERRDAM +   18)   /*wr_ifm_dam_utils.c: 337 */
#define   EDAM019      (ERRDAM +   19)   /*wr_ifm_dam_utils.c: 338 */
#define   EDAM020      (ERRDAM +   20)   /*wr_ifm_dam_utils.c: 339 */
#define   EDAM021      (ERRDAM +   21)   /*wr_ifm_dam_utils.c: 340 */
#define   EDAM022      (ERRDAM +   22)   /*wr_ifm_dam_utils.c: 384 */
#define   EDAM023      (ERRDAM +   23)   /*wr_ifm_dam_utils.c: 385 */
#define   EDAM024      (ERRDAM +   24)   /*wr_ifm_dam_utils.c: 386 */
#define   EDAM025      (ERRDAM +   25)   /*wr_ifm_dam_utils.c: 387 */
#define   EDAM026      (ERRDAM +   26)   /*wr_ifm_dam_utils.c: 388 */
#define   EDAM027      (ERRDAM +   27)   /*wr_ifm_dam_utils.c: 389 */
#define   EDAM028      (ERRDAM +   28)   /*wr_ifm_dam_utils.c: 390 */
#define   EDAM029      (ERRDAM +   29)   /*wr_ifm_dam_utils.c: 398 */
#define   EDAM030      (ERRDAM +   30)   /*wr_ifm_dam_utils.c: 435 */
#define   EDAM031      (ERRDAM +   31)   /*wr_ifm_dam_utils.c: 438 */
#define   EDAM032      (ERRDAM +   32)   /*wr_ifm_dam_utils.c: 440 */
#define   EDAM033      (ERRDAM +   33)   /*wr_ifm_dam_utils.c: 441 */
#define   EDAM034      (ERRDAM +   34)   /*wr_ifm_dam_utils.c: 442 */

/*ccpu00138576 - end*/
#endif /* __WRIFMDAMUTL_H__ */

/********************************************************************30**

           End of file:    $SID$

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
$SID$        ---      Sriky         1. initial release TotaleNodeB 1.1
*********************************************************************91*/
