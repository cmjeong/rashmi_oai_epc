
/********************************************************************20**

     Name:    eGTP product

     Type:    C Header file

     Desc:    Macros and hash defines related with test engine

     File:    egac_acc.h

     Sid:      egac_edm.h@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:24 2015

     Prg:     an 

*********************************************************************21*/


/***************************************************
 *******  FOR STUB TESTING ONLY *******************
***************************************************/
#define  EVTEDMENCREQ            1
#define  EVTEDMDECREQ            2
#define  EVTEDMSIGIND            3
#define  EVTEDMSIGCFM            4
#define  EVTEDMERRIND            5
#define  EVTEDMCFGCFM            6
#define  EGAC_MAX_INTF           6

/*********************************************
   Encoder Decoder specific #defines 
*********************************************/

#define EGAC_MEM_SDU_SIZE     2048

#define EGAC_MAX_INST         10
#define EGAC_MAX_IE           255
#define EGAC_MAX_CHILD_IE     10
#define EGAC_MAX_NUM_GRP_IE   5
#define EGAC_MAX_IES_PER_MSG  30
#define EGAC_INTF_GMDICT_BIN_SIZE      1024


#define  EGAC_IE_INST_ZERO                0 
#define  EGAC_IE_INST_ONE                 1
#define  EGAC_IE_RECOVERY                 3
#define  EGAC_IE_PVT_EXTN                 255

/*****************************************************
 *  * Macro to generate encode decode mapping functions *
 *   *****************************************************/
#define IEPARSEMAPFUNCTION(NAME)  { egAcEnc##NAME, egAcDec##NAME }

#define EGAC_FREE_GM_MSG(_egMsg) \
{ \
   if (_egMsg) \
   { \
      if (EgUtilDeAllocGmMsg(&_egMsg) != ROK) \
      { \
         EGLOGERROR(ERRCLS_DEBUG, EEGXXX,0,"Failed to deallocate egMsg"); \
      } \
   } \
}

#define EGAC_FILL_ERR_EVNT_MSG(_evntMsg, _resultType, _ieType, _ieInst, _msgType) \
{ \
   _evntMsg->resultType = _resultType; \
   _evntMsg->failedIeInst = _ieInst; \
   _evntMsg->failedIeType = _ieType; \
   _evntMsg->failedMsgType = _msgType; \
}
   
#define EGAC_CHK_MSGLEN(_msgLen, _retVal, _evntMsg, _ieFlag, _ieType) \
{ \
   if ( ( (_msgLen == 0 ) || (_msgLen < EGAC_LEN_FOUR)) && (_ieType != EGAC_OCTET_STRING)) \
   { \
      _retVal =  EGT_ERR_INV_MSG_LEN; \
      if(_ieFlag) \
         EGAC_FILL_ERR_EVNT_MSG(_evntMsg, _retVal, _ieFlag, _ieType, 1) \
      else \
         EGAC_FILL_ERR_EVNT_MSG(_evntMsg, _retVal, _ieFlag, _ieType, 0); \
      RETVALUE(_retVal); \
   } \
}

/* To fill the IE Level Info struct */
#define EGAC_FILL_IE_LVL_INFO(_ieLvlInfo, _ieLvl, _ieType, _ieInst) \
{ \
   (_ieLvlInfo)->ieInfo[_ieLvl].ieTypePres = TRUE; \
   (_ieLvlInfo)->ieInfo[_ieLvl].ieType = _ieType; \
   (_ieLvlInfo)->ieInfo[_ieLvl].ieInst = _ieInst; \
   (_ieLvlInfo)->ieInfo[_ieLvl].occrPres = FALSE; \
   (_ieLvlInfo)->ieInfo[_ieLvl].posPres = FALSE; \
   (_ieLvlInfo)->ieInfo[_ieLvl].refValue = FALSE; \
}

/* raise alarm for memory allocation failure */
#define EGAC_SND_ALARM_MEM_ALLOC_FAIL(_mem, _dgn, _retVal) \
{ \
      _dgn.dgnVal[0].type         = LEGAC_USTA_DGNVAL_MEM; \
      _dgn.dgnVal[0].t.mem.region = egCb.init.region;  \
      _dgn.dgnVal[0].t.mem.pool   = egCb.init.pool; \
      egSendLmAlarm (LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                     LCM_CAUSE_MEM_ALLOC_FAIL,(EgUstaDgn *)&_dgn); \
      _retVal = EGAC_ERR_MEM_ALLOC_FAILED; \
}

/********************************************************************30**

         End of file:     egac_edm.h@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:24 2015

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
/main/1      ---      ad                1. Created for Initial Release 1.1
/main/2      ---      rkumar      1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
*********************************************************************91*/
