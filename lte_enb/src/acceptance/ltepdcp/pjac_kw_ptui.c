

/********************************************************************20**

     Name:    LTE-PDCP - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    pjac_kw_ptui.c

     Sid:      pjac_kw_ptui.c@@/main/TeNB_Main_BR/1 - Tue Aug 12 15:44:02 2014

     Prg:     adarsh
*********************************************************************21*/

/* header (.h) include files */
/* header (.h) include files */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
                                                                                                                                                                        
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timer defines */
#include "cm_tkns.h"       /* common tokens defines */
#include "cm_mblk.h"       /* common memory allocation library defines */
#include "cm_llist.h"      /* common link list  defines  */
#include "cm_hash.h"       /* common hash list  defines */
#include "cm_lte.h"        /* common LTE defines */
#include "lkw.h"           /* LKW defines */
#include "kwu.h"           /* KWU defines */
                                                                                                                                                                        
                                                                                                                                                                        
/* extern (.x) include files */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
                                                                                                                                                                        
#include "cm5.x"           /* common timer library */
#include "cm_tkns.x"       /* common tokens */
#include "cm_mblk.x"       /* common memory allocation */
#include "cm_llist.x"      /* common link list */
#include "cm_hash.x"       /* common hash list */
#include "cm_lte.x"        /* common LTE includes */
#include "cm_lib.x"        /* common memory allocation library */
#include "lkw.x"           /* LKW */
#include "kwu.x"           /* KWU */

                                                                                                                                                                        
#ifndef LCKWUIKWU
#define PTKWKWU
#endif
                                                                                                                                                                        
#ifndef LCKWUICKW
#define PTKWCKW
#endif
                                                                                                                                                                        
#ifndef NH
#define PTKWKWU
#define PTKWCKW
#endif
                                                                                                                                                                        
#ifndef PJ
#define PTKWKWU
#define PTKWCKW
#endif
                                                                                                                                                                        
                                                                                                                                                                        
#ifdef __cplusplus
EXTERN "C" {
#endif /* __cplusplus */

PUBLIC KwuBndCfm kwUiKwuBndCfmMt[] =
{
#ifdef LCKWUIKWU
   cmPkKwuBndCfm,            /* 0 - loosely coupled */
#else
   PtUiKwuBndCfm,            /* 0 - loosely coupled, portable  */
#endif /* LCKWUIKWU */
#ifdef NH
   NhLiKwuBndCfm,            /* 1 - tightly coupled, RRC  */
#else
   PtUiKwuBndCfm,            /* 1 - tightly coupled, portable */
#endif /* NH */
#ifndef KW_PDCP
#ifdef PJ
   PjLiKwuBndCfm,            /* 2 - tightly coupled, PDCP */
#else
   PtUiKwuBndCfm,      /* 2 - tightly coupled, portable */
#endif /* NH */
#endif /* KW_PDCP */
#ifndef TENB_ACC
#ifdef LWLCKWUIKWU
   cmPkKwuBndCfm,      /* 3 - light weight loosely coupled */
#else
   PtUiKwuBndCfm,      /* 3 - light weight loosely coupled, portable */
#endif /* LCKWUIKWU */
#endif /*TENB_ACC*/
};



#ifdef ANSI
PUBLIC S16 PtUiKwuReEstCmpInd
(
Pst               *pst,
SuId              suId,
CmLteRlcId        rlcId
)
#else
PUBLIC S16 PtUiKwuReEstCmpInd(pst, suId, rlcId)
Pst               *pst;
SuId              suId;
CmLteRlcId        rlcId;
#endif
{
   TRC3(PtUiKwuReEstCmpInd)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(rlcId);

   RETVALUE(ROK);

} /* end of PtUiKwuReEstCmpInd */


#ifdef ANSI
PUBLIC S16 PtUiKwuDatCfm
(
Pst               *pst,
SuId              suId,
CmLteRlcId        rlcId
)
#else
PUBLIC S16 PtUiKwuDatCfm(pst, suId, rlcId)
Pst               *pst;
SuId              suId;
CmLteRlcId        rlcId;
#endif
{
   TRC3(PtUiKwuDatCfm)
                                                                                                                                                                        
   UNUSED(pst);
   UNUSED(suId);
   UNUSED(rlcId);
                                                                                                                                                                        
   RETVALUE(ROK);
                                                                                                                                                                        
} /* end of PtUiKwuDatCfm */



/* KWU Data Indication primitive */
                                                                                                                                                                        
PUBLIC KwuDatInd kwUiKwuDatIndMt[] =
{
#ifdef LCKWUIKWU
   cmPkKwuDatInd,            /* 0 - loosely coupled */
#else
   PtUiKwuDatInd,            /* 0 - loosely coupled, portable  */
#endif /* LCKWUIKWU */
#ifdef NH
   NhLiKwuDatInd,            /* 1 - tightly coupled, RRC  */
#else
   PtUiKwuDatInd,            /* 1 - tightly coupled, portable */
#endif /* NH */
#ifdef PJ
   PjLiKwuDatInd,            /* 2 - tightly coupled, PDCP */
#else
   PtUiKwuDatInd,            /* 2 - tightly coupled, portable */
#endif /* PJ */
};



PUBLIC KwuReEstCmpInd kwUiKwuReEstCmpIndMt[] =
{
#ifdef LCKWUIKWU
   cmPkKwuReEstCmpInd,    /* 0 -loosely coupled */
#else
   PtUiKwuReEstCmpInd,    /* 0 -loosely coupled portable*/
#endif /* LCKWUIKWU */
   PtUiKwuReEstCmpInd,    /* 1 - tightly coupled, portable */ 
#ifdef PJ
   PjLiKwuReEstCmpInd,    /* 1 - tightly coupled, portable */
#else
   PtUiKwuReEstCmpInd,    /* 2 - tightly coupled, PDCP */ 
#endif /* PJ */
#if 0
#ifdef LWLCKWUIKWU
   cmPkKwuReEstCmpInd,    /* 3 - light weight loosely coupled */ 
#else
   PtUiKwuReEstCmpInd,    /* 3 - light weight loosely coupled, portable */
#endif /* LCKWUIKWU */
#endif
};


PUBLIC KwuDatCfm kwUiKwuDatCfmMt[] =
{
#ifdef LCKWUIKWU
   cmPkKwuDatCfm,         /* 0 -loosely coupled */ 
#else
   PtUiKwuDatCfm,         /* 0 -loosely coupled portable*/
#endif /* LCKWUIKWU */
   PtUiKwuDatCfm,         /* 1 - tightly coupled, portable */ 
#ifdef PJ
   PjLiKwuDatCfm,         /* 1 - tightly coupled, PDCP */
#else
   PtUiKwuDatCfm,         /* 2 - tightly coupled, portable */ 
#endif /* PJ */
#ifdef LWLCKWUIKWU
   cmPkKwuDatCfm,         /* 3 - light weight loosely coupled */ 
#else
   PtUiKwuDatCfm,         /* 3 - light weight loosely coupled, portable */
#endif /* LCKWUIKWU */
};


#ifdef ANSI
PUBLIC S16 KwUiKwuBndCfm
(
Pst *pst,                       /* post structure */
SuId suId,                      /* Service User Id */
U8   status                     /* Status */
)
#else
PUBLIC S16 KwUiKwuBndCfm(pst, suId, status)
Pst *pst;                       /* post structure */
SuId suId;                      /* Service User Id */
U8   status;                    /* Status */
#endif
{
   TRC3(KwUiKwuBndCfm)

   /* jump to specific primitive depending on configured selector */
   (*kwUiKwuBndCfmMt[pst->selector])(pst, suId, status);

   RETVALUE(ROK);

} /* end of KwUiKwuBndCfm */

/**
 *
 * @brief
 *
 *        Handler for sending the data(SDU) from upper layer.
 *
 * @b Description:
 *
 *        This function is used to transfer a SDU received from the peer
 *        RLC entity to the service user(RRC/PDCP).
 *
 *  @param[in] pst         Post structure
 *  @param[in] suId        Service User SAP ID
 *  @param[in] datIndInfo  Data Request Information
 *  @param[in] mBuf         Data Buffer (SDU)
 *
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 */
#ifdef ANSI
PUBLIC S16 KwUiKwuDatInd
(
Pst               *pst,
SuId              suId,
KwuDatIndInfo     *datInd,
Buffer            *mBuf
)
#else
PUBLIC S16 KwUiKwuDatInd(pst, suId, datInd, mBuf)
Pst               *pst;
SuId              suId;
KwuDatIndInfo     *datInd;
Buffer            *mBuf;
#endif
{
   TRC3(KwUiKwuDatInd)
                                                                                                                                                                        
   /* jump to specific primitive depending on configured selector */
   (*kwUiKwuDatIndMt[pst->selector])(pst, suId, datInd, mBuf);
                                                                                                                                                                        
   RETVALUE(ROK);
                                                                                                                                                                        
} /* end of KwUiKwuDatInd */


#ifdef ANSI
PUBLIC S16 KwUiKwuReEstCmpInd
(
Pst               *pst,
SuId              suId,
CmLteRlcId        rlcId
)
#else
PUBLIC S16 KwUiKwuReEstCmpInd(pst, suId, rlcId)
Pst               *pst;
SuId              suId;
CmLteRlcId        rlcId;
#endif
{
   TRC3(KwUiKwuDatInd)
                                                                                                                                                                        
   /* jump to specific primitive depending on configured selector */
   (*kwUiKwuReEstCmpIndMt[pst->selector])(pst, suId, rlcId);
                                                                                                                                                                        
   RETVALUE(ROK);
                                                                                                                                                                        
} /* end of KwUiKwuDatInd */

/**
 *
 * @brief 
 *
 *        Handler for sending the data confirmation to upper layer. 
 *
 * @b Description:
 *
 *        This function is used to send a confirmation to the service
 *        user about the data received by the peer RLC entity. 
 *
 *  @param[in] pst         Post structure  
 *  @param[in] suId        Service User SAP ID 
 *  @param[in] datCfmInfo  Data Confirmation Information
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED
 */
#ifdef ANSI
PUBLIC S16 KwUiKwuDatCfm
(
Pst               *pst,
SuId              suId,
KwuDatCfmInfo     *datCfm
)
#else
PUBLIC S16 KwUiKwuDatCfm(pst, suId, datCfm)
Pst               *pst;
SuId              suId;
KwuDatCfmInfo     *datCfm;
#endif
{
   TRC3(KwUiKwuDatCfm)

   /* jump to specific primitive depending on configured selector */
   (*kwUiKwuDatCfmMt[pst->selector])(pst, suId, datCfm);

   RETVALUE(ROK);

} /* end of KwUiKwuDatCfm */


/********************************************************************30**

         End of file:     pjac_kw_ptui.c@@/main/TeNB_Main_BR/1 - Tue Aug 12 15:44:02 2014

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
/main/1      ---      av         1. LTE PDCP Initial release 2.1
*********************************************************************91*/
