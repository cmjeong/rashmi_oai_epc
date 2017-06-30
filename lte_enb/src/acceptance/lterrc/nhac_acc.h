
/********************************************************************20**

     Name:    RRC - acc test file

     Type:    C Include file

     Desc:    This file contains the acc defines and macros

     File:    nhac_acc.h

     Sid:      nhac_acc.h@@/main/3 - Fri Jul  1 01:12:55 2011

     Prg:     rer 

*********************************************************************21*/
#ifndef __NHAC_ACC_H__
#define __NHAC_ACC_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#define NHAC_XML_GET_VALLIST(_parseStr, _strName, _strTok, _dstArray,  _size, _ret)    \
{                                                                                      \
      Txt   *_token   =  NULLP;                                                        \
      U8    _i        =  0;                                                            \
      CMXTA_ZERO(_parseStr, sizeof(_parseStr));                                        \
      _ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, _strName, _parseStr);    \
      _token =  strtok(_parseStr, _strTok);                                            \
      for(_i=0;_token != NULLP;(_token =  strtok(NULLP, _strTok)), _i++)               \
         _dstArray[_i]  =  (_size )atoi(_token);                                       \
}
 
#define NHAC_FILL_U8_U32_TKN(_ie, _pres, _val) {\
   _ie.pres = _pres;\
   _ie.val = _val;\
}

#define NHAC_FILL_TKN_64(_ie,_pres,_val,_size){\
   _ie.pres = _pres; \
        cmMemset((U8 *)&_ie.val, '\0', 64);\
   cmMemcpy((U8 *)&_ie.val,(CONSTANT U8 *)&_val ,64);\
        _ie.len = 8;\
}

#define FILL_UINT_TKN(_ie, _val) {\
   _ie.pres = PRSNT_NODEF;\
   _ie.val = _val;\
}

#define FILL_BIT_STR(_ptr, _len, _val, _pdu) {\
   U8      i;                                    \
   U16     _tmpLen;                             \
   _ptr.pres = PRSNT_NODEF;                     \
   _ptr.len =  _len;                            \
\
   _tmpLen = _len;                              \
   if((_len%8) > 0)                              \
   {                                             \
      _tmpLen = (_len/8)+1;                         \
   }                                             \
   else                                          \
   {                                             \
      _tmpLen = _len/8;                             \
   }                                             \
   CMXTA_GET_MEM(_pdu, _tmpLen * sizeof(U8), (Ptr *)&(_ptr.val));  \
                   \
   if(_ptr.val != NULLP)                         \
   {                                             \
      for(i = 0; i < _tmpLen; i++)                  \
      {                                          \
         _ptr.val[i] = _val;                  \
      }                                          \
   }                                             \
}

#define FILL_OCT_STR(_ptr, _len, _val, _pdu) {\
   U8      i;                                    \
   _ptr.pres = PRSNT_NODEF;                      \
   _ptr.len =  _len;                             \
                   \
   CMXTA_GET_MEM(_pdu, _len * sizeof(U8), (Ptr *)&(_ptr.val));  \
                   \
   if(_ptr.val != NULLP)                         \
   {                                             \
      for(i = 0; i < _len; i++)                  \
      {                                          \
         _ptr.val[i] = _val;                  \
      }                                          \
   }                                             \
}

#define FILL_U8_FRAMENUM(_ie, _sfn, _subFrmNo) {\
   _ie.sfn = _sfn;\
   _ie.subframe = _subFrmNo;\
}

#define NHAC_CHK(_lvalue , _rvalue) { \
Txt pBuf[256]; \
      if(_lvalue != _rvalue) \
      {\
         sprintf(pBuf, "Validation failed %s file %d line",__FILE__, __LINE__ );\
         SPrint(pBuf);\
         RETVALUE(RFAILED);\
      }\
}

#define MAX_U32     65535
#define NHACTSTREG  0
#define NHACTSTPOOL 0

#define NHAC_DFLT_MAX_USAP_CFG 1
#define NHAC_DFLT_MEM_UPPER_THR_CFG 9
#define NHAC_DFLT_MEM_LOWER_THR_CFG 2
#define NHAC_DFLT_MSEC_TMR_CFG 1
#define NHAC_DFLT_SEC_TMR_CFG 1
#define NHAC_DFLT_MAX_QLEN_CFG 255
#define NHAC_DFLT_RNC_NUMCONN_PCFG 10
#define NHAC_DFLT_RNC_RLSRPT_PCFG 1
#define NH_DFLT_RNC_RLSRPT_PCFG 1
#define NHAC_DFLT_RNC_NUMRLSRPT_PCFG 1
#define NHAC_DFLT_SPID_LCFG 0
#define NHAC_DFLT_SUID_LCFG 0
#define NHAC_DFLT_BNDRTYCNT_LCFG 1
#define NHAC_DFLT_BNDTMR_LCFG 20
#define NHAC_DFLT_MEMID_REG_LCFG  0
#define NHAC_DFLT_MEMID_POOL_LCFG 0
#define NHAC_DFLT_DST_PROC_ID_LCFG 0
#define NHAC_DFLT_DST_ENT_LCFG 0
#define NHAC_DFLT_SPID_UCFG 0
#define NHAC_DFLT_SUID_UCFG 0
#define NHAC_DFLT_SEL_UCFG 0
#define NHAC_DFLT_SEL_LCFG 0
#define NHAC_DFLT_MEMID_REG_UCFG 0
#define NHAC_DFLT_MEMID_POOL_UCFG 0
#define NHAC_DFLT_PRIOR_UCFG 0
#define NHAC_DFLT_PRIOR_LCFG 0
#define NHAC_DFLT_DST_PROC_ID_UCFG 0
#define NHAC_DFLT_DST_ENT_UCFG 0
#define NHAC_DFLT_DST_INST_UCFG 0
#define NHAC_DFLT_DST_ROUT_UCFG 0
#define NHAC_DFLT_DST_ROUT_LCFG 0
#define NHAC_DFLT_RLM1_PCFG 0
#define NHAC_DFLT_RLM2_PCFG 0
#define NHAC_DFLT_RLM3_PCFG 0
#define NHAC_DFLT_DATMOD_PCFG 0
#define NHAC_DFLT_DST_INST_LCFG 0
#define NHAC_DFLT_INIT_TMR_ENB_LCFG 0
#define NHAC_DFLT_DST_INST_LCFG 0
#define NHAC_DFLT_INIT_TMR_ENB_LCFG  0
#define NHAC_DFLT_INIT_TMR_VAL_LCFG 0
#define NHAC_CAUSE_TCP_IPSEC_SRV_OPEN_SUCC 0
#define NHAC_USTA_DGNVAL_SAPID 0
#define NHAC_BND_OK            1       /* bind request OK */
#define NHAC_BND_NOK           2       /* bind request not OK */
#define NHAC_START             3
#define NHAC_SUCCESS           0

#define NHAC_DFLT_PROCID      0x01

#define NHAC_CAUSE_TCP_IPSEC_SRV_OPEN_SUCC 0

#define MAX_CRG_ID       12
#define MAX_CPJ_ID       10
#define CKW_MAX_CFG      10
#define MAX_CTF_ID       8
#define CTF_MAX_CFG      10

#define CCCH_RBID1       1
#define CCCH_RBID2       2
#define BCCH_RBID1       3
#define BCCH_RBID2       4
#define BCCH_RBID3       5
#define PCCH_RBID        6

#define CCCH_UL_SCH_ID   1
#define CCCH_DL_SCH_ID   2
#define BCCH_DL_BCH_ID   3
#define BCCH_DL_SCH_ID1  4
#define BCCH_DL_SCH_ID2  5
#define PCCH_DL_PCH_ID   6
#define NHAC_ZERO_VAL         0
#define NHAC_INVALID_TRANSID  NHAC_ZERO_VAL
#define NHAC_INVALID_UEID     NHAC_ZERO_VAL
#define NHAC_INVALID_CELLID  NHAC_ZERO_VAL 

#define CMXTA_DFLT_PROCID 0x01
#define CMXTA_DBGLEVEL_NH 3
/* The max size of RRC PDU */
#define NHAC_MEM_PDU_SIZE    3584

/* Constants for Conditional IEs */
#ifdef NH_ASN_COND_VALIDATE
#define NHAC_SRB_RLC_CFG              1
#define NHAC_SRB_LGCL_CHANNEL_CFG     2
#define NHAC_DRB_EPS_BEARERIDENTITY   3
#define NHAC_DRB_LGCL_CHANNEL_ID_1    4
#define NHAC_DRB_PDCP_CFG_1           5
#define NHAC_DRB_PDCP_CFG_2           6
#define NHAC_DRB_RLC_CFG              7
#define NHAC_DRB_LGCL_CHANNEL_ID_2    8
#define NHAC_DRB_LGCL_CHANNEL_CFG     9
#define NHAC_DRB_UL_SPCFCPARAMS_1     10
#define NHAC_DRB_UL_SPCFCPARAMS_2     11
#define NHAC_DISCRD_TMR               12
#define NHAC_DRB_RLC_UM               13
#define NHAC_DRB_RLC_AM               14
#define NHAC_CODEBK_SUBSET_RSTRCN     15
#define NHAC_TDD_ACKNACKFB_MOD        16
#define NHAC_SRB_TOADDMDLST           17
#define NHAC_DRB_TOADDMDLST           18
#endif /* #ifdef NH_ASN_COND_VALIDATE */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif 
/********************************************************************30**

         End of file:     nhac_acc.h@@/main/3 - Fri Jul  1 01:12:55 2011

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

     ver       pat         init                  description
------------ -----------   ---- ----------------------------------------------
/main/1      ---           rer                1. LTE RRC Initial Release.
/main/2      ---           ch                 1. RRC Release 2.1.
/main/3      ---           sbalakrishna       1. Updated for Release of 3.1
*********************************************************************91*/
