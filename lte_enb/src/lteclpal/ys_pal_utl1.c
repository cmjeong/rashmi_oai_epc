
/************************************************************************
 
     Name:     LTE MAC Convergence Layer
  
     Type:     C source file
  
     Desc:     C source code for Entry point fucntions
  
     File:     ys_utl.c
  
     Sid:      yw_utl.c@@/main/2 - Thu Dec  2 02:27:28 2010
  
     Prg:      pk
  
**********************************************************************/

/** @file ys_utl.c
@brief This module acts as an interface handler for upper interface and 
manages Pst and Sap related information for upper interface APIs.
*/

/* header include files -- defines (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timers defines */
#include "cm_hash.h"       /* common hash list defines */
#include "cm_llist.h"      /* common linked list defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_tkns.h"       /* common tokens */
#include "cm_inet.h"       /* common tokens */
#include "cm_lte.h"
#include "ctf.h"           /* CTF defines */
#include "lys.h"           /* layer management defines for LTE-CL */
#include "tfu.h"
#ifdef YS_MSPD
#else
#include "ys_pal.h"            /* defines and macros for CL */
#include <sys/time.h>
#endif /* YS_MSPD */
#include "ys_pal_err.h"        /* YS error defines */

/* header/extern include files (.x) */

#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_inet.x"       /* common tokens */
#include "cm_lte.x"
#include "ctf.x"           /* CTF types */
#include "lys.x"           /* layer management typedefs for CL */
#include "tfu.x"
#ifndef YS_MSPD
#include "ys_pal.x"
#endif


/*
*
*       Fun:   ysUtlMalloc
*
*       Desc:  This function allocates a static memory buffer of 
*              requested size.
*
*       Ret:   (Data *) - on success
*              NULLP    - on failure
*
*       Notes: None
*
*       File:  ys_util.c
*
*/

#ifdef ANSI
PUBLIC Data * ysUtlMalloc
(
Size               size                /* Static Buffer Size Requested */
)
#else
PUBLIC Data * ysUtlMalloc (size)
Size               size;               /* Static Buffer Size Requested */
#endif
{
   TskInit         *ysInit;            /* CL Task Init Structure */
   Data            *buf;               /* Buffer to be allocated */

   TRC2(ysUtlMalloc)

   buf    = NULLP;
   ysInit = &(ysCb.ysInit);

#if (ERRCLASS & ERRCLS_DEBUG)
   if (size <= 0)
   {
      YS_LOGERR_DBG(EYS018, size, "ysUtlMalloc(): invalid size\n");
      RETVALUE (NULLP);
   }
#endif /* ERRCLASS & ERRCLS_DEBUG */

   /* Obtain the Static Buffer */
   if((SGetSBuf(ysInit->region, ysInit->pool, &buf, size) != ROK) ||
      (buf == NULLP))
   {
      RETVALUE(NULLP);
   }

   /* Initialise the buffer */
   cmMemset (buf, 0, size);

   RETVALUE(buf);

} /* end of ysUtlMalloc */

/*
*
*       Fun:   ysUtlDeAlloc
*
*       Desc:  This function returns a static memory buffer to 
*              the buffer pool.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  ys_util.c
*
*/

#ifdef ANSI
PUBLIC Void ysUtlDeAlloc
(
Data               *buf,               /* Static Buffer to be freed */
Size               size                /* Size of Buffer */
)
#else
PUBLIC Void ysUtlDeAlloc (buf, size)
Data               *buf;               /* Static Buffer to be freed */
Size               size;               /* Size of Buffer */
#endif
{
   TskInit         *ysInit;            /* CL Task Init Structure */

   TRC2(ysUtlDeAlloc)

#if (ERRCLASS & ERRCLS_DEBUG)
   if ((buf == NULLP) || (size <= 0) )
   {
      Txt   prntBuf[PRNTSZE];

      sprintf(prntBuf, "ysUtlDeAlloc: buf=%p\n", buf);

      YS_LOGERR_DBG(EYS019, size, prntBuf);
      RETVOID;
   }
#endif /* ERRCLASS & ERRCLS_DEBUG */

   ysInit = &(ysCb.ysInit);

   /* Free the memory */
   SPutSBuf (ysInit->region, ysInit->pool, buf, size);

   RETVOID;

} /* end of ysUtlDeAlloc */

/*
*
*       Fun:   ysUtlAllocEventMem
*
*       Desc:  This function allocates event memory 
*
*       Ret:   (Data *) - on success
*              NULLP    - on failure
*
*       Notes: None
*
*       File:  ys_utl.c
*
*/

#ifdef ANSI
PUBLIC S16 ysUtlAllocEventMem
(
Ptr       *memPtr,
Size      memSize
)
#else
PUBLIC S16 ysUtlAllocEventMem(memPtr, memSize)
Ptr       *memPtr;
Size      memSize;
#endif
{
   Mem   sMem;

   TRC2(ysUtlAllocEventMem)

   sMem.region = ysCb.ysInit.region;
   sMem.pool = ysCb.ysInit.pool;

#if (ERRCLASS & ERRCLS_DEBUG)
   if (memSize<= 0)
   {
      YS_LOGERR_DBG(EYS020, memSize, "ysUtlAllocEventMem(): invalid size\n");
      RETVALUE (RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_DEBUG */

   if(ROK != cmAllocEvnt(memSize, YS_MEM_SDU_SIZE, &sMem, memPtr))
   {
      YS_DBG_ERR((_ysp, "Returning RFAILED form ysUtlAllocEventMem because \
                    cmAllocEvnt returned RFAILED\n"));
      *memPtr = NULLP;
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);

} /* end of ysUtlAllocEventMem*/

#ifndef YS_MSPD
#ifdef ANSI
PUBLIC S16 ysUtlAllocEventMem1
(
Ptr       *memPtr,
Size      memSize
)
#else
PUBLIC S16 ysUtlAllocEventMem1(memPtr, memSize)
Ptr       *memPtr;
Size      memSize;
#endif
{
   Mem   sMem;

   TRC2(ysUtlAllocEventMem)

   sMem.region = ysCb.ysInit.region;
   sMem.pool = ysCb.ysInit.pool;

#if (ERRCLASS & ERRCLS_DEBUG)
   if (memSize<= 0)
   {
      YS_LOGERR_DBG(EYS020, memSize, "ysUtlAllocEventMem(): invalid size\n");
      RETVALUE (RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_DEBUG */

   if(ROK != cmAllocEvnt(memSize, 1500, &sMem, memPtr))
   {
      YS_DBG_ERR((_ysp, "Returning RFAILED form ysUtlAllocEventMem because \
                    cmAllocEvnt returned RFAILED\n"));
      *memPtr = NULLP;
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);

} /* end of ysUtlAllocEventMem*/

#endif
/*
*
*       Fun:   ysUtlFreeEventMem
*
*       Desc:  This function frees event memory 
*
*       Ret:   
*
*       Notes: None
*
*       File:  ys_utl.c
*
*/

#ifdef ANSI
PUBLIC S16 ysUtlFreeEventMem
(
Ptr       memPtr
)
#else
PUBLIC S16 ysUtlFreeEventMem(memPtr)
Ptr       memPtr;
#endif
{
   TRC2(ysUtlFreeEventMem)

#if (ERRCLASS & ERRCLS_DEBUG)
   if (memPtr == NULLP)
   {
      YS_LOGERR_DBG(EYS021, 0, "ysUtlFreeEventMem(): invalid ptr\n");
      RETVALUE (RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_DEBUG */

   cmFreeMem(memPtr);

   RETVALUE(ROK);
} /* end of ysUtlFreeEventMem */

/*
*
*       Fun:    ysUtlFreeDatReq 
*
*       Desc:   This function return UE control block 
*
*       Ret:   Pointer to ue control block 
*
*       Notes: None 
*
*       File:   ys_utl.c
*/
#ifdef ANSI
PUBLIC Void ysUtlFreeDatReq
(
TfuDatReqInfo   *datReq
)
#else
PUBLIC Void ysUtlFreeDatReq(datReq)
TfuDatReqInfo   *datReq;
#endif
{
   U8                idx; 
   TfuDatReqPduInfo  *pduInfo;
   CmLList           *cmLstEnt;
   if (datReq->bchDat.pres == PRSNT_NODEF)
   {
      SPutMsg (datReq->bchDat.val);
      datReq->bchDat.val = NULLP;
   }
   cmLstEnt = datReq->pdus.first;
   while (cmLstEnt != NULLP)
   {
      pduInfo = (TfuDatReqPduInfo *)cmLstEnt->node;
      for (idx = 0; idx < TFU_MAX_TB; idx++)
      {
         if((pduInfo) && (pduInfo->mBuf[idx] != NULLP))
         {
            SPutMsg (pduInfo->mBuf[idx]);
            pduInfo->mBuf[idx] = NULLP;
         }
      }
      cmLstEnt = cmLstEnt->next;
   }
   ysUtlFreeEventMem((Ptr)datReq);
}

#ifndef YS_MSPD
#if (defined YS_PICO || defined YS_LTE_PAL)
/*
*
*       Fun:   ysUtlGetCellCfg
*
*       Desc:  
*
*       Ret:   
*
*       Notes: None
*
*       File:  ys_utl.c
*
*/

#ifdef ANSI
PUBLIC YsCellCb *ysUtlGetCellCfg
(
CmLteCellId    cellId 
)
#else
PUBLIC YsCellCb *ysUtlGetCellCfg(cellId)
CmLteCellId    cellId;
#endif
{
   YsCellCb *cellCb;
   
   TRC2(ysUtlGetCellCfg)

   cellCb = NULLP;

#if (ERRCLASS & ERRCLS_INT_PAR)      
   if(cellId >= YS_NUM_LOG_CELLS)
   {
      YS_LOGERR_INTPAR(EYS022, (ErrVal)cellId,
            "Invalid cellId:ysUtlGetCellCfg failed\n");
      RETVALUE(NULLP);
   }
#endif
   
#ifdef YS_LTE_PAL   
   cellCb = &ysCb.cellCb;
#else   
   cellCb = ysCb.cellCfgLst[cellId];
#endif
   
   RETVALUE(cellCb);
} /* end of ysUtlGetCellCfg */

/*
*
*       Fun:    ysUtlGetUe 
*
*       Desc:   This function return UE control block 
*
*       Ret:   Pointer to ue control block 
*
*       Notes: None 
*
*       File:   ys_utl.c
*/
#ifdef ANSI
PUBLIC YsUeCb *ysUtlGetUe
(
YsCellCb        *cellCb,
CmLteRnti       ueId
)
#else
PUBLIC YsUeCb *ysUtlGetUe(cellCb, ueId)
YsCellCb        *cellCb;
CmLteRnti       ueId; 
#endif
{
   YsUeCb    *ueCb;
   CmLList   *cmLstEnt;

   TRC2(ysUtlGetUe)

   ueCb = NULLP;

   cmLstEnt = cellCb->ueLstCb.ueLst.first;
   while (cmLstEnt != NULLP)
   {
      if (((YsUeCb *)cmLstEnt->node)->ueId == ueId)
      {
         ueCb = (YsUeCb *)(cmLstEnt->node);
         break;
      }

      /* Move to next entry */
      cmLstEnt = cmLstEnt->next;
   }

   RETVALUE (ueCb);
} /* end of ysUtlGetUe () */

/**
 * @brief API for delete cell configuration
 *
 * @details
 *
 *     Function: ysUtlDelCellCfg
 *     
 *     This API for handle delete cell configuration request from RRM
 *           
 *  @param[in]
 *  @param[in]
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PUBLIC S16 ysUtlDelCellCfg
(
CmLteCellId    cellId
)
#else
PUBLIC S16 ysUtlDelCellCfg(cellId)
CmLteCellId    cellId;
#endif
{
   S16       ret;
   YsCellCb  *cellCb;
   YsUeCb    *ueCb;

   TRC2(ysUtlDelCellCfg)
   
   YS_DBG_PARAM((_ysp, "ysUtlDelCellCfg(): cellId = %d \n", cellId));

   ret    = ROK;
   cellCb = NULLP;
   ueCb   = NULLP;

   if((cellCb = ysUtlGetCellCfg(cellId)) == NULLP) 
   {
      YS_DBG_ERR((_ysp, "Cell Configuration doesnt exist for cell (%d). \
                     ysUtlDelCellCfg Failed \n", cellId));
      RETVALUE(RFAILED);
   }
/*  ys003.102: Fix for DefectId:ccpu00115333
   ELSE part has been removed*/
   /*Else code has been removed ys004.102:Cell Delete Fix CRID:ccpu00117556*/
   RETVALUE(ret);
}  /* ysUtlDelCellCfg*/

/*
*
*       Fun:   ysUtlDeAllocUeCb
*
*       Desc:  
*
*       Ret:   
*
*       Notes: None
*
*       File:  ys_utl.c
*
*/

#ifdef ANSI
PUBLIC S16 ysUtlDeAllocUeCb
(
YsCellCb        *cellCb,
YsUeCb          *ueCb
)
#else
PUBLIC S16 ysUtlDeAllocUeCb(cellCb, ueCb)
YsCellCb        *cellCb;
YsUeCb          *ueCb;
#endif
{

   TRC2(ysUtlDeAllocUeCb)

   /* Delete from UE list */
   cmLListDelFrm(&(cellCb->ueLstCb.ueLst), &(ueCb->lnkUeLst));

   /* Free the transaction control block memory */
   ysUtlDeAlloc((Data *)ueCb, sizeof(YsUeCb));

   RETVALUE(ROK);
} /* end of ysUtlDeAllocUeCb */
#endif /* YS_PICO or YS_LTE_PAL */
/* ys005.102 : changes done to keep wireshark code outside of ifndef MSPD part*/
#endif

#ifdef YS_WIRESHARK_LOG
   int                     g_sockfd;
   struct sockaddr_in      g_serv_addr;
int  ysInitLogWireless()
{
   CmInetIpAddr   ipAddr = 0;
   g_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
 
   if (g_sockfd < 0)
   {
      printf("Failed to create socket\n");
      return (-1);
   }
   g_serv_addr.sin_family = AF_INET;
   g_serv_addr.sin_port   = htons(9999);
   if(ROK == cmInetAddr( (S8 *)WIRESHARK_SRVR_IP_ADDR , &ipAddr))
   {
      g_serv_addr.sin_addr.s_addr = CM_INET_NTOH_U32(ipAddr);
   }

   bind(g_sockfd, &g_serv_addr, sizeof(g_serv_addr));

   RETVALUE(ROK);

   
}

void ysTrillWiresharkMsg(Buffer *mBuf, U8 radioType, U8 direction, U8 rntiType,
                 U16     rnti, U16 ueid,     U16       subframe,
                 U8      isPredefinedData, U8 retx, U8 crcStatus)
{
   MsgLen len;
   U8     statBuffer[9999];
   MsgLen cLen;
   U32     bufOffset=0;
   U16     tmp16;

   memset(statBuffer, 0, sizeof(statBuffer));
   /* Start Buffer Tag for logging */
   memcpy(statBuffer+bufOffset, MAC_LTE_START_STRING,
         strlen(MAC_LTE_START_STRING));
   bufOffset += strlen(MAC_LTE_START_STRING);

   /* MAC Packet Info fileds */
   statBuffer[bufOffset++]    = radioType;
   statBuffer[bufOffset++]    = direction;
   statBuffer[bufOffset++]    = rntiType;

   /* RNTI */
   statBuffer[bufOffset++] = MAC_LTE_RNTI_TAG;
   tmp16 = htons(rnti);
   memcpy(statBuffer+bufOffset, &tmp16, 2);
   bufOffset+= 2;

   /* UEId */
   statBuffer[bufOffset++] = MAC_LTE_UEID_TAG;
   tmp16 = htons(ueid);
   memcpy(statBuffer+bufOffset, &tmp16, 2);
   bufOffset+= 2;

   /* Subframe number */
   statBuffer[bufOffset++] = MAC_LTE_SUBFRAME_TAG;
   tmp16 = htons(subframe);
   memcpy(statBuffer+bufOffset, &tmp16, 2);
   bufOffset+= 2;

   statBuffer[bufOffset++] = MAC_LTE_CRC_STATUS_TAG;
   statBuffer[bufOffset++] = crcStatus;

    /***********************************************************/
    /* For these optional fields, no need to encode if value is default */
    if (!isPredefinedData) {
        statBuffer[bufOffset++] = MAC_LTE_PREDFINED_DATA_TAG;
        statBuffer[bufOffset++] = isPredefinedData;
    }

    if (retx != 0) {
        statBuffer[bufOffset++] = MAC_LTE_RETX_TAG;
        statBuffer[bufOffset++] = retx;
    }

    /* Actual Payload */
    statBuffer[bufOffset++] = MAC_LTE_PAYLOAD_TAG;

    SFndLenMsg(mBuf, &len);
    if (len==0)
     return;

    SCpyMsgFix(mBuf, (MsgLen)0, (MsgLen)len,
                        (Data*) (statBuffer+bufOffset), (MsgLen*)&cLen);
    bufOffset += len;
    sendto(g_sockfd, statBuffer, bufOffset, 0, &g_serv_addr, sizeof(g_serv_addr));

}
/* ys005.102 : changes done to keep wireshark code outside of ifndef MSPD part*/
#endif


void postToApp(Buffer *mBuf, U8 radioType, U8 direction, U8 rntiType,
                       U16     rnti, U16 ueid,     U16       subframe,
                       U8      isPredefinedData, U8 retx, U8 crcStatus)
{
}

/************************************************************30**
  
         End of file:     yw_utl.c@@/main/2 - Thu Dec  2 02:27:28 2010
  
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
/main/2      ---     sgm    1. eNodeB 1.2 release
/main/2    ys003.102 sgm    1. Fix for CID:1622-02-01 DefectId:ccpu00115333
/main/2    ys004.102 pkd    1. Cell Delete Fix CRID:ccpu00117556 
/main/2    ys005.102 pbyadgi 1. Wireshark changes 
*********************************************************************91*/
