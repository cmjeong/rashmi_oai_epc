

/***********************************************************************

    Name: Header file for defines for LM configuration

    Type: C Source

    Desc: 

    File: eg_dbsm.h

    Sid:      eg_dbsm.h@@/main/1 - Fri Feb  4 18:18:08 2011

    Prg: an

************************************************************************/

#ifdef EGTP_C

/* Message Codes   */

#define EG_SM_MBMSESNSTOPREQ_CMD_CODE  235       
#define EG_SM_MBMSESNSTOPREQ_NMB_IES   2         
#define EG_SM_MBMSESNSTOPRSP_CMD_CODE  236       
/* eg014.201: ccpu00139510 Egtpc release 10 upgrade */
#ifdef EG_REL_AC0 
#define EG_SM_MBMSESNSTOPRSP_NMB_IES   3         
#else 
#define EG_SM_MBMSESNSTOPRSP_NMB_IES   2         
#endif 
#define EG_SM_MBMSESNSTRTREQ_CMD_CODE  231       
/* eg014.201: ccpu00139510 Egtpc release 10 upgrade */
#ifdef EG_REL_AC0 
#define EG_SM_MBMSESNSTRTREQ_NMB_IES   11        
#else 
#define EG_SM_MBMSESNSTRTREQ_NMB_IES   10        
#endif 
#define EG_SM_MBMSESNSTRTRSP_CMD_CODE  232       
#define EG_SM_MBMSESNSTRTRSP_NMB_IES   6         
#define EG_SM_MBMSESNUPDREQ_CMD_CODE   233       
#ifdef EG_REL_AC0 
#define EG_SM_MBMSESNUPDREQ_NMB_IES    9         
#else 
#define EG_SM_MBMSESNUPDREQ_NMB_IES    8         
#endif 
#define EG_SM_MBMSESNUPDRSP_CMD_CODE   234       
#define EG_SM_MBMSESNUPDRSP_NMB_IES    5         


#endif
/********************************************************************30**

         End of file:     eg_dbsm.h@@/main/1 - Fri Feb  4 18:18:08 2011

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
/main/1      ---      svenkat           1. Initial for eGTP 2.1 Release
/main/1     eg014.201    rss            1. Egtpc release 10 upgrade
*********************************************************************91*/

