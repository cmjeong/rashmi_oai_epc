
/********************************************************************20**

     Name:     eGTP layer

     Type:     C source file

     Desc:     

     File:     egac_hitutl.c

     Sid:      egac_hitutl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:33 2015

     Prg:      an

*********************************************************************21*/

/* header include files (.h) */

#include "egac_acc.x"
#include "egac_hit.x"



/*
 *
 *       Fun:    egAcHitAssocFindnCreate 
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   egac_hitutl.c
 *
 */

#ifdef ANSI
PUBLIC EgAcHitAssocCb* egAcHitAssocFindnCreate
(
CmXtaTCCb    *tcCb,
U32   assocIdx,
UConnId   suAssocId,
UConnId   spAssocId
)
#else
PUBLIC EgAcHitAssocCb* egAcHitAssocFindnCreate(tcCb, assocIdx,suAssocId,spAssocId)
CmXtaTCCb    *tcCb;
U32       assocIdx;
UConnId   suAssocId;
UConnId   spAssocId;
#endif
{
   EgAcHitAssocCb* assocCb;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHitAssocFindnCreate)

   assocCb = NULLP;

   CMXTA_DBG_PARAM((_cmxtap, "egAcHitAssocFindnCreate(): \n"));

   /*-- SOAC_ENHANCE:  Change to Hash Defines --*/
   if (assocIdx >= 10)
   {
      CMXTA_DBG_FATAL((_cmxtap, "egAcHitAssocFindnCreate(): resource error\n"));
      RETVALUE(NULLP);
   }

   assocCb = &egAccCb.hitCb.assoc[assocIdx];

   /*-- DTUCL does not maintain the state of the assocCb, if the user
        tries to reuse the same index again, it will result in the old
        values being overwritten by the new values. This is done to 
        aid the use of the same assocCb between different TCs. TA may
        not reset the values in assocCb between different TCs. All TCs
        on DTUCL anyway will not run in parallel with other TCs --*/

   /*-- Generate spAssocId --*/
   if (spAssocId == EGT_CONNID_NOTUSED)
      assocCb->spConId = ++egAccCb.hitCb.nxtConnId;
   else
      assocCb->spConId = spAssocId;

   assocCb->suConId = suAssocId;

   assocCb->inUse = TRUE;

   RETVALUE(assocCb);
} /* end of egAcHitAssocFindnCreate() */

/*
 *
 *       Fun:    egAcHitAssocFind 
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   egac_hitutl.c
 *
 */
#ifdef ANSI
PUBLIC EgAcHitAssocCb* egAcHitAssocFind
(
CmXtaTCCb    *tcCb,
U32   assocIdx
)
#else
PUBLIC EgAcHitAssocCb* egAcHitAssocFind(tcCb, assocIdx)
CmXtaTCCb    *tcCb;
U32   assocIdx;
#endif /* ANSI */
{
   EgAcHitAssocCb* assocCb;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHitAssocFind)

   assocCb = NULLP;

   CMXTA_DBG_PARAM((_cmxtap, "egAcHitAssocFind(): \n"));

   /*-- SOAC_ENHANCE:  Change to Hash Defines --*/
   if (assocIdx >= 10)
   {
      CMXTA_DBG_FATAL((_cmxtap, "egAcHitAssocFind(): resource error\n"));
      RETVALUE(NULLP);
   }

   assocCb = &egAccCb.hitCb.assoc[assocIdx];

   /*-- DSCTP does not maintain the state of the assocCb, if the user
        tries to reuse the same index again, it will result in the old
        values being overwritten by the new values. This is done to 
        aid the use of the same assocCb between different TCs. TA may
        not reset the values in assocCb between different TCs. All TCs
        on DSCTP anyway will not run in parallel with other TCs --*/

   /*-- Use this function only if you do want to do validation --*/
   if (assocCb->inUse == FALSE)
   {
#ifdef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : call not found: exp (%d)\n",
                      assocIdx), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : call not found: exp (%ld)\n",
                      assocIdx), 2);
#endif
      RETVALUE(NULLP);
   }

   RETVALUE(assocCb);

} /* end of egAcHitAssocFind() */

/*
 *
 *       Fun:    egAcHitTstCbFind -
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   egac_hitutl.c
 *
 */
#ifdef ANSI
PUBLIC CmXtaTCCb*  egAcHitTstCbFind
(
)
#else
PUBLIC CmXtaTCCb*  egAcHitTstCbFind ()
#endif
{
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcHitTstCbFind)

   /*-- Optimization, check if only one TC running --*/
#ifdef CMXTA_EXTENSION
   /*-- Change SOAC_ENHANCE --*/
   if (cmXtaCb.curTCCb != NULLP)
      RETVALUE(cmXtaCb.curTCCb);
#else 
   if ((cmXtaCb.curTCCb != NULLP)   &&
       (cmXtaCb.curTCCb->state != CMXTA_END_SHUTDOWN))
      RETVALUE(cmXtaCb.curTCCb);
#endif

   RETVALUE(NULLP);
}

#ifdef HI_TLS

/*
*
*       Fun:    hiOSSLPasswdCb
*
*       Desc:   Called from OpenSSL to provide a password to
*               decrypt the private key file. Must be implemented
*               by the customer.
*
*       Ret:    password length - ok
*
*       Notes:  None
*
*       File:   hi_acc1.c
*
*/
#ifdef ANSI
PUBLIC int hiOSSLPasswdCb
(
char            *buf,           /* buffer for password */
int             size,           /* available buffer size */
int             rwflag,         /* reading or writing */
void            *userdata       /* specified at time of cb registration */
)
#else
PUBLIC int hiOSSLPasswdCb(buf, size, rwflag, userdata)
char            *buf;           /* buffer for password */
int             size;           /* available buffer size */
int             rwflag;         /* reading or writing */
void            *userdata;      /* specified at time of cb registration */
#endif
{
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(hiOSSLPasswdCb);

   cmMemcpy((U8 *)buf, (U8 *)"yabbadabbadoo", 14);

   return 13;
}


/*
*
*       Fun:    hiOSSLPostConCheck
*
*       Desc:   Called from TUCL to perform TLS post connection
*               verification. Typically ensures that the peer's
*               FQDN is present in the certificate it provides.
*               Must be implemented by the customer.
*
*       Ret:    X509_V_OK                               - ok
*               X509_V_ERR_APPLICATION_VERIFICATION     - failed
*
*       Notes:  None
*
*       File:   hi_acc1.c
*
*/
#ifdef ANSI
PUBLIC long hiOSSLPostConCheck
(
SSL             *ssl,           /* TLS connection */
CmTptAddr       *peerAddr       /* peer's address */
)
#else
PUBLIC long hiOSSLPostConCheck(ssl, peerAddr)
SSL             *ssl;           /* TLS connection */
CmTptAddr       *peerAddr;      /* peer's address */
#endif
{
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(hiOSSLPostConCheck);


   return X509_V_OK;
}
#endif

/*
*
*       Fun:   egAcUtlHitCb 
*
*       Desc:  This function is used to 
*
*       Ret:   None
*
*       Notes: None
*
*       File:  xx_lhicb.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcUtlHitCb
(
CmXtaMsgQElm *qElm
)
#else
PUBLIC S16 egAcUtlHitCb(qElm)
CmXtaMsgQElm *qElm;
#endif /* ANSI */
{
   EgAccMsgQElm  *egtpMsg;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcUtlHitCb)

   CMXTA_DBG_PARAM((_cmxtap, "egAcUtlHitCb(): \n"));

   egtpMsg = (EgAccMsgQElm *)qElm->data;

   if (egtpMsg != NULLP)
   {
      if (NULLP != egtpMsg->u.hitInfo.mBuf)
         CMXTA_FREEMBUF(egtpMsg->u.hitInfo.mBuf);

      CMXTA_FREE(egtpMsg, sizeof (EgAccMsgQElm));

      qElm->data = NULLP;
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* End of egAcUtlHitCb() */

/*
 *
 *       Fun:    egAcDmSmGetTSapIdFromProt - configuration confirm
 *
 *       Desc:   prints the config confirm status
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   xx_dmsm.c
 *
 */

#ifdef ANSI
PUBLIC SpId egAcDmSmGetTSapIdFromProt
(
U8    protType
)
#else
PUBLIC SpId egAcDmSmGetTSapIdFromProt(protType)
U8    protType;
#endif /* ANSI */
{
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcDmSmGetTSapIdFromProt)

   CMXTA_DBG_PARAM((_cmxtap, "egAcDmSmGetTSapIdFromProt(): \n"));

   /*-- Treat TUCL and D-TUCL as same, we come here only
        for dummy layers --*/
   if ((protType == LEG_TSAP_TYPE_TUCL)       ||
       (protType == LEG_TSAP_TYPE_DTUCL))
      RETVALUE(egAccCb.taCb.dtuclId);

   RETVALUE(0);
} /* end of TSapIdFromProt() */



/********************************************************************30**

         End of file:     egac_hitutl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:33 2015

*********************************************************************31*/


/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************80**

*********************************************************************81*/

/********************************************************************90**

    ver       pat    init                  description
----------- -------- ---- -----------------------------------------------
/main/1      ---      ad          1. Created for Initial release 1.1
/main/2      ---      rss         1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
/main/3     eg003.201 psingh      1. Merged code from eg006.102 to Fix TRACE5
                                     macro related issue
*********************************************************************91*/
