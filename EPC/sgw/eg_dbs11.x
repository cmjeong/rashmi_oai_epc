

/***********************************************************************

    Name: typedef file for LM configuration

    Type: C Source

    Desc: 

    File: eg_dbs11.x

    Sid:      eg_dbs11.x@@/main/3 - Fri Feb  4 18:18:03 2011

    Prg : an

************************************************************************/


/***********************************************************************
    This file contains automatically generated code
************************************************************************/

#ifdef EGTP_C
/*-- eg003.201 : changes from eg006.102 : Deleted egMakeIeDict --*/
EXTERN S16 egMakes11GmDict  ARGS((LegMsgEntry *gmEntry, U8 *nmbGmMsgs));
#endif

#ifdef EGTP_U
EXTERN S16 egUMakeIeDict ARGS((EgIeEntry *ieEntry, U16 *posIdx));
EXTERN S16 egUMakeGmDict ARGS ((EgUMsgEntry *gmEntry, U16 *posIdx));
PUBLIC void egUMakeECHOREQGmEntry ARGS((EgUMsgEntry *gmCb));
PUBLIC void egUMakeECHORSPGmEntry ARGS((EgUMsgEntry *gmCb));
PUBLIC void egUMakeERRORINDGmEntry ARGS((EgUMsgEntry *gmCb));
PUBLIC void egUMakeSUPPEXTHDRNTFGmEntry ARGS((EgUMsgEntry *gmCb));
PUBLIC void egUMakeENDMARKGmEntry ARGS((EgUMsgEntry *gmCb));
#endif

/********************************************************************30**

         End of file:     eg_dbs11.x@@/main/3 - Fri Feb  4 18:18:03 2011

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
/main/1      ---      an                1. Created for Initial Release 1.1
/main/2      ---      kchaitanya        1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla       Initial Release of eGTP 2.1 release
/main/3     eg003.201 psingh            1. Merged code from eg006.102 
*********************************************************************91*/

