
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     wr_smm_cfg.c

     Sid:      fc_smm_cfg.c@@/main/TeNB_Main_BR/7 - Mon Aug 11 16:52:01 2014

     Prg:      Sriky 

*********************************************************************21*/
static const char* RLOG_MODULE_NAME="SMM";
static int RLOG_MODULE_ID=2;

static int RLOG_FILE_ID=41;
/* header includes */
#include "wr.h"
#include "wr_emm.h"
#include "wr_umm.h"
#include "wr_lwr.h"
#include "wr_smm_init.h"
#include "wr_smm_smallcell.h"
#include "cm_os.h"       /* common hashing */
#include "cm_os.x"
#include "ss_diag.h"      /* Common logging header */
#include <stdlib.h>
#ifdef LTE_L2_MEAS
#include "lpj.h"
#include "lkw.h"
#include "lrg.h"
#endif/*LTE_L2_MEAS*/
#include "wr_kpi.h"
#include "wr_msm_common.h"
extern MsmLteeNodeBparams lteeNodeBparams[WR_MAX_CELLS];
extern MsmFapParameters   fapParameters;


#ifdef WR_WATCHDOG
EXTERN U16 softTimeout;
EXTERN U16 hardTimeout;
#endif
#define MAX_LOG_FILE_NAME_LENGTH  32
U8 logFileName[WR_MAX_LOG_PATH_VALUE]; 
U8 logPath[MAX_LOG_FILE_NAME_LENGTH]; 

#include "tip_cmn.h"
EXTERN TipVmAssocInfo vmAssocInfo[WR_MAX_CELLS];
EXTERN TipDrvrTskIpProcIdInfo drvrIpProcIdInfo[WR_MAX_CELLS];

EXTERN  U32 LL2_IP_ADDR;
EXTERN  U32 UL2_IP_ADDR;
EXTERN  U32 L3_IP_ADDR;
EXTERN  U32 UL2_PORT_TIP;
EXTERN  U32 LL2_PORT_TIP;
EXTERN U32 UL2_GTP_IP_ADDR;
EXTERN U32 L3_PORT_TIP;
EXTERN U32 L3_PORT;

#define WR_SMM_VALIDATE_CFG_PARAM(_param, _min, _max)\
{\
   if(_min > _param || _param > _max)\
   {\
      fprintf(stderr, "Invalid parameter value %s=%d, it should be min=%d, max=%d\n", \
      #_param, _param, _min, _max);\
      RETVALUE(RFAILED);\
   }\
}

PUBLIC Void wrSmmSetBandwidth(U32  freqBandwidth,U8  loopcnt);
/* SPS changes starts */
PUBLIC U32 wrSmDlCellBwInRbs(CtfBandwidth dlCellBw);
/* SPS changes ends */

 PUBLIC S16 smWrReadConfigParams (Void);
 PUBLIC S16 smL2ReadCfgParams (Void);
 PUBLIC Void getData(FILE *fptr,char *fieldName ,char *FieldValue);

/*ccpu00126694*/
/*
*
*       Fun:   wrGetNeghPlmn
*
*       Desc:  This function return neighbours plmn
*
*       Ret:   
*
*       Notes: None
*
*       File:  wr_smm_init_brcm.c
*
*/
#ifdef ANSI
PRIVATE S16 wrGetNeghPlmn
(
U32 plmn,
U8 *nghPlmn,
U8 *noMnc
)
#else
PRIVATE S16 wrGetNeghPlmn(plmn, nghPlmn, noMnc)
U32 plmn;
U8 *nghPlmn;
U8 *noMnc;
#endif
{
   S16 count=0;
   U32 temp;
   temp = plmn;
   while( temp>0)
   {
      temp =temp/10;
      count ++;
   }
   if( count == 6)
   {
      *noMnc = 3;
   }
   else if(count == 5)
   {
      *noMnc =2;
      nghPlmn[count] = -1;
   }
   else
   {
      RETVALUE(RFAILED);
   }
   count --;
   while( count >=0 )
   {
     nghPlmn[count] = plmn%10;
     plmn = plmn/10;
     count --;
    }
    RETVALUE(ROK);
}

/* SPS changes starts */
/*
*
*       Fun:  wrSmDlCellBwInRbs 
*
*       Desc:  Function Converts enum to exact value
*
*       Ret:   U8
*
*       Notes: None
*
*       File:  wr_smm_init.c
*
*/
PUBLIC U32 wrSmDlCellBwInRbs
(
 CtfBandwidth    dlCellBw
)
{
   U32 dlBwInRbs = 0;
   switch (dlCellBw)
   {
      case CTF_BW_RB_6:
         dlBwInRbs = 6;
         break;
      case CTF_BW_RB_15:
         dlBwInRbs = 15;
         break;
      case CTF_BW_RB_25:
         dlBwInRbs = 25;
         break;
      case CTF_BW_RB_50:
         dlBwInRbs = 50;
         break;
      case CTF_BW_RB_75:
         dlBwInRbs = 75;
         break;
      case CTF_BW_RB_100:
         dlBwInRbs = 100;
         break;
      default:
         break;
   }
   RETVALUE(dlBwInRbs);
}
/* SPS changes ends */
/*
 * *       Fun:   smL2ReadCfgParams
 * *
 * *       Desc:  Reads the No of the Cells  from 
 * *              the file wr_cfg.txt and stores them
 * *              use it Confguration part
 * *
 * *       Ret:   ROK, RFAILED
 * *
 * *       File:  wr_smm_cfg.c
 * *
 * */
#ifdef ANSI
PUBLIC S16 smL2ReadCfgParams
(
)
#else
PUBLIC S16 smL2ReadCfgParams (Void)
#endif
{  
   FILE  *fp;
   U16 tagNum = 0;
   U8 tag[10];
   U8 tagVal[50];

   TRC2(smL2ReadCfgParams);

   if((fp = fopen("wr_cfg.txt", "r")) == NULL)
   {
      /* configuration file checking */
      WR_LOGERROR(ERRCLS_DEBUG,0,ERRZERO,
            "FAILED to open the file wr_cfg.txt\n");
      RETVALUE (RFAILED);
   } /* end of if statement */

   /* Read the file line by line */
   for(;;)
   {
      cmMemset(tagVal, '\0', sizeof(tagVal));
      if (fscanf(fp, "%s %*s %s", tag, tagVal) != 2)
      {
         fprintf(stderr, " Error in while reading configuration file \n");
         fclose(fp);
         RETVALUE(RFAILED);
      }
      if ((0 == strcmp("INVLD", (S8 *)tagVal)))
         continue;

      if(NULLP == strcmp("CFGEND", (S8 *)tag))
         break;

      smWrCfgGetTagNum(tag, &tagNum);

      switch(tagNum)
      {
         case WR_TAG_NOS_OF_CELLS:
            {
               wrSmDfltNumCells = atoi((S8 *)tagVal);
               if(wrSmDfltNumCells == 1)
               {
                  fprintf(stderr, "No Of Cells Configured = %ld \n", wrSmDfltNumCells);
               }
            }
#ifndef LTE_UNLICENSED
            fclose(fp);
            RETVALUE (ROK);
#else
            break;   
        case WR_TAG_LTEU_NUM_CELLS:
            {
               wrSmDfltNumUnLicnsdCells = (U8)atoi((S8*)tagVal);
               fprintf(stdout, "\nL2: No Of Unlicensed Cells Configured = %d \n", wrSmDfltNumUnLicnsdCells);
               //RLOG1(L_INFO, "Number of Unlicensed Cells configured L2 %d\n", wrSmDfltNumUnLicnsdCells);
            }
            fclose(fp);
            RETVALUE (ROK);   
#endif  
         default :
            {
                  fprintf(stderr, "INVALID Read from wr_cfg.txt\n");
            }
            break;   
      }/* End of switch() */
      tagNum = MAX_CFG_PARAM;
   }/* End of for() */

   fprintf(stdout, "Read the wr_cfg.txt file successfully ");
   fclose(fp);

   RETVALUE (ROK);
} /* end of smL2ReadCfgParams */



/*ccpu00126694*/
/*
*
*       Fun:   smWrReadConfigParams
*
*       Desc:  Reads the values of the configurable parameters from 
*              the file wr_cfg.txt and stores them
*              in the smCfgCb
*
*       Ret:   ROK, RFAILED
*
*       File:  wr_smm_cfg.c
*
*/

/*
   U8    parm[30][40];
   S32   val[50];
   U8 tag[50];
   U8 tagVal[50];
   U8  paramLst[50][50];
   S8    numstr[30];*/
#ifdef ANSI
PUBLIC S16 smWrReadConfigParams
(
)
#else
PUBLIC S16 smWrReadConfigParams (Void)
#endif
{  
   FILE  *fp;
   U16 tagNum = 0;
   U8 tag[200];
   U8 tagVal[1048];
   Bool status = TRUE;
   U16 noOfParams = 0;
   U8 loopCnt = 0;
   U8 loopCntTmp = 0;
   U16 paramCnt = 0;
   U8 noOfElem = 0;
   U8  paramLst[600][100];
   U32 plmnVal;
   U8  plmnLen;
   WrPlmnId plmnId;
   SztPLMNidentity pLMNidentity;
   U8 dscp = 0;
   U32 qciWgtVal = 0;
#ifndef WR_RSYS_OAM
   U32 enbId = 0;
   LwrSmMmeCfg *mmeCfg = NULLP;
   U8 ipIdx;
#endif
   U32 peerId = 0;
   /*ccpu00126694*/
   U8 nghPlmn[6],noMnc;
   /* CSG_DEV */
   U8   tagLen = 0;
   U8   pIdx = 1;

   TRC2(smWrReadConfigParams);

   if((fp = fopen("wr_cfg.txt","r")) == NULL)
   {
      /* configuration file checking */
      WR_LOGERROR(ERRCLS_DEBUG,0,ERRZERO,
            "FAILED to open the file wr_cfg.txt\n");
      RETVALUE (RFAILED);
   } /* end of if statement */


   /* Read the file line by line */
   for(;;)
   {
      cmMemset(tagVal, '\0', sizeof(tagVal));
      if (fscanf(fp,"%s %*s %s",tag,tagVal) != 2)
      {
         fprintf(stderr, " Error in while reading configuration file \n");
         RETVALUE(RFAILED);
      }
      if ((0 == strcmp("INVLD",(S8 *)tagVal)))
         continue;

      if(NULLP == strcmp("CFGEND", (S8 *)tag))
         break;

      smWrCfgGetTagNum(tag,&tagNum);
#if TAG_DBG
      printf("tagNum= %ld, tagVal = %s\n", tagNum, tagVal);
#endif
      switch(tagNum)
      {
#ifdef LTE_UNLICENSED
         static Bool isNumLteURead = FALSE;
#endif
         case WR_TAG_NOS_OF_CELLS:
            {
               wrSmDfltNumCells = atoi((S8 *)tagVal); /*TODO - remove*/
               lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteEnbProtoCfg.numOfCells = atoi((S8 *)tagVal);
#ifndef TENB_MULT_CELL_SUPPRT
               if(lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteEnbProtoCfg.numOfCells > 1)
               {
                  fprintf(stderr, "Multi Cell not supported, so setting the nos of cells to 1 \n");
                  lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteEnbProtoCfg.numOfCells = 1;
                  wrSmDfltNumCells = 1; /*TODO - remove*/
               }
#endif
            }
            break;   
         case WR_TAG_CELL_ID:
            {
               status     = TRUE;
               noOfParams = 0;
               noOfElem   = 0;

               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  if(noOfParams >= wrSmDfltNumCells)
                  {
                     noOfParams = wrSmDfltNumCells;
                  }
                  else
                  {
                     fprintf(stderr, "Cell Ids not configured for all cells  \n");
                     RETVALUE(RFAILED);
                  }
                  for (loopCnt=0; loopCnt<noOfParams; loopCnt++)
                  {
                     lteeNodeBparams[loopCnt].lteCellSib1CfgGrp.cellAccessInfo.cellId = atoi((S8*)paramLst[loopCnt]);
                  }
               }
            }
            break;   
         case WR_TAG_DUP_MODE:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteSmCellCfg.duplexMode = (U16)atoi((S8 *)tagVal);
                  lteeNodeBparams[loopCnt].lteAddCellCfg.duplexMode = (U16)atoi((S8 *)tagVal);
               }
            }
            break;   
         case WR_TAG_MAX_UE_SUPPORT:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteSmCellCfg.maxUeSupp = (U8)atoi((S8 *)tagVal);
               }
            }
            break;   
         case WR_TAG_MCC_0:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellSib1CfgGrp.cellAccessInfo.plmnInfo[0]. \
                     plmnId.mcc[0] = (U8)atoi((S8 *)tagVal);
               }
            }
            break;   
         case WR_TAG_MCC_1:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellSib1CfgGrp.cellAccessInfo.plmnInfo[0]. \
                     plmnId.mcc[1] = (U8)atoi((S8 *)tagVal);
               }
            }
            break;   
         case WR_TAG_MCC_2:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellSib1CfgGrp.cellAccessInfo.plmnInfo[0]. \
                     plmnId.mcc[2] = (U8)atoi((S8 *)tagVal);
               }
            }
            break;   
         case WR_TAG_MNC_0:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellSib1CfgGrp.cellAccessInfo.plmnInfo[0]. \
                     plmnId.mnc[0] = (U8)atoi((S8 *)tagVal);

               }
            }
            break;   
         case WR_TAG_MNC_1:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellSib1CfgGrp.cellAccessInfo.plmnInfo[0]. \
                     plmnId.mnc[1] = (U8)atoi((S8 *)tagVal);
               }
            }
            break;   
         case WR_TAG_MNC_2:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  if (-1 == atoi((S8 *)tagVal))
                  {
                     lteeNodeBparams[loopCnt].lteCellSib1CfgGrp.cellAccessInfo.plmnInfo[0]. \
                        plmnId.mnc[2] = (U8)atoi((S8 *)tagVal);
                     lteeNodeBparams[loopCnt].lteCellSib1CfgGrp.cellAccessInfo.plmnInfo[0]. \
                        plmnId.numMncDigits = 2;
                  }
                  else
                  {
                     lteeNodeBparams[loopCnt].lteCellSib1CfgGrp.cellAccessInfo.plmnInfo[0]. \
                        plmnId.mnc[2] = (U8)atoi((S8 *)tagVal);
                     lteeNodeBparams[loopCnt].lteCellSib1CfgGrp.cellAccessInfo.plmnInfo[0]. \
                        plmnId.numMncDigits = 3;
                  }
               }
            }
            break;   
         case WR_TAG_TA_CODE:
            {
               status     = TRUE;
               noOfParams = 0;
               noOfElem   = 0;

               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  if(noOfParams > wrSmDfltNumCells)
                  {
                     noOfParams = wrSmDfltNumCells;
                  }
                  for (loopCnt=0; loopCnt<noOfParams; loopCnt++)
                  {
                     lteeNodeBparams[loopCnt].lteRemScanParameters.tac = (U16)atoi((S8*)paramLst[loopCnt]);
                     lteeNodeBparams[loopCnt].lteCellSib1CfgGrp.cellAccessInfo.tac = (U16)atoi((S8*)paramLst[loopCnt]);
                  }
               }
            }
            break;   
         case WR_TAG_FREQ_BAND_IND:
            {
               status     = TRUE;
               noOfParams = 0;
               noOfElem   = 0;

               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  if(noOfParams > wrSmDfltNumCells)
                  {
                     noOfParams = wrSmDfltNumCells;
                  }
                  for (loopCnt=0; loopCnt<noOfParams; loopCnt++)
                  {
                     lteeNodeBparams[loopCnt].lteCellSib1CfgGrp.freqBandInd = (U8)atoi((S8*)paramLst[loopCnt]);
                  }
               }
            }
            break;   
         case WR_TAG_ENB_IP_ADDR:
            {
               cmInetAddr((S8 *)tagVal,
                  &(fapParameters.lteEnodebIpAddr.enbIpAddr));
               fapParameters.lteEnodebIpAddr.enbIpAddr = 
                  CM_INET_HTON_U32(fapParameters.lteEnodebIpAddr.enbIpAddr);

               fapParameters.lteEnodebIpAddr.ipv4pres = TRUE;
            }
            break;  
         case WR_TAG_ENB_IP_ADDR_IPV6:
            {
               cmMemcpy((U8*)fapParameters.lteEnodebIpAddr.enbIpv6Addr,
                  (U8*)tagVal, sizeof(CmInetIpAddr6));
               fapParameters.lteEnodebIpAddr.ipv6pres = TRUE;
            }
            break;
         case WR_TAG_PCI_SELECT_TYPE :
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteSonGenericParams.isPciSelEnabled = (Bool) atoi((S8 *)tagVal);
                  if(lteeNodeBparams[loopCnt].lteSonGenericParams.isPciSelEnabled > 2)
                  {
                     fprintf(stderr, " Invalid PCI selection type configured \n");
                     RETVALUE(RFAILED);
                  }
               }
            }
            break;
            
         case WR_TAG_MAX_AVG_GBRPRB_USAGE:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteSmCellCfg.maxAvgGbrPrbUsage = (U8)atoi((S8 *)tagVal);
               }
            }
            break;
         case WR_TAG_PRACH_SELECT_TYPE :
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteSonGenericParams.isPrachSelEnabled = (Bool) atoi((S8 *)tagVal);  
                  if(lteeNodeBparams[loopCnt].lteSonGenericParams.isPrachSelEnabled > 2)
                  {
                     fprintf(stderr, " Invalid PRACH selection type configured \n");
                     RETVALUE(RFAILED);
                  }
               }
            }
            break;
         case WR_TAG_EARFCN_SELECT_TYPE :
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteSonGenericParams.isEarfcnSelEnabled = (Bool) atoi((S8 *)tagVal);
                  if(lteeNodeBparams[loopCnt].lteSonGenericParams.isEarfcnSelEnabled > 2)
                  {
                     fprintf(stderr, " Invalid EARFCN selection type configured \n");
                     RETVALUE(RFAILED);
                  }
               }
            }
            break;
         case WR_TAG_PCI_LIST :
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  status     = TRUE;
                  noOfParams = 0;
                  noOfElem   = 0;

                  wrCfgValdtInput(tagVal, &status, &noOfElem);
                  if (TRUE == status)
                  {
                     wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                     if(noOfParams > WR_SM_MAX_PCI)
                     {
                        noOfParams = WR_SM_MAX_PCI;
                     }
                     lteeNodeBparams[loopCnt].lteAddCellCfg.pciListCfg.numPci = noOfParams;
                     for (loopCntTmp=0; loopCntTmp<noOfParams; loopCntTmp++)
                     {
                        lteeNodeBparams[loopCnt].lteAddCellCfg.pciListCfg.pciLst[loopCntTmp] =
                           atoi((S8*)paramLst[loopCntTmp]);
                     }
                  }
               }
            }
            break;
         case WR_TAG_DL_EARFCN_LIST :
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  status     = TRUE;
                  noOfParams = 0;
                  noOfElem   = 0;
                  
                  wrCfgValdtInput(tagVal, &status, &noOfElem);
                  if (TRUE == status)
                  {
                     wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                     if(noOfParams > WR_SM_MAX_EARFCN)
                     {
                        noOfParams = WR_SM_MAX_EARFCN;
                     }
                     lteeNodeBparams[loopCnt].lteAddCellCfg.earfcnListCfg.numEarfcnDl = noOfParams;
                     for (loopCntTmp=0; loopCntTmp < noOfParams; loopCntTmp++)
                     {
                        lteeNodeBparams[loopCnt].lteAddCellCfg.earfcnListCfg. \
                           earfcnDlLst[loopCntTmp] = atoi((S8*)paramLst[loopCntTmp]);
                     }
                  }
               }
            }
            break;
         case WR_TAG_UL_EARFCN_LIST :
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  status     = TRUE;
                  noOfParams = 0;
                  noOfElem   = 0;
                  wrCfgValdtInput(tagVal, &status, &noOfElem);
                  if (TRUE == status)
                  {
                     wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                     if(noOfParams > WR_SM_MAX_EARFCN)
                     {
                        noOfParams = WR_SM_MAX_EARFCN;
                     }
                     lteeNodeBparams[loopCnt].lteAddCellCfg.earfcnListCfg.numEarfcnUl = noOfParams;
                     for (loopCntTmp=0; loopCntTmp < noOfParams; loopCntTmp++)
                     {
                        lteeNodeBparams[loopCnt].lteAddCellCfg.earfcnListCfg. \
                           earfcnUlLst[loopCntTmp] = atoi((S8*)paramLst[loopCntTmp]);
                     }
                  }
               }
            }
            break;
         case WR_TAG_ROOTSEQ_IDX_LIST:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  status     = TRUE;
                  noOfParams = 0;
                  noOfElem   = 0;
                  U16  rootSeqIdx = 0;
                  wrCfgValdtInput(tagVal, &status, &noOfElem);
                  if (TRUE == status)
                  {
                     wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                     if(noOfParams > WR_SM_MAX_ROOTSEQ_IDX)
                     {
                        noOfParams = WR_SM_MAX_ROOTSEQ_IDX;
                     }
                     lteeNodeBparams[loopCnt].ltePrachCfgCommon.prachParamLst.numRootSeqIndex = noOfParams;
                     for (loopCntTmp=0; loopCntTmp < noOfParams; loopCntTmp++)
                     {
                        rootSeqIdx = atoi((S8*)paramLst[loopCntTmp]);
                        lteeNodeBparams[loopCnt].ltePrachCfgCommon.prachParamLst.rootSequenceIndxLst[loopCntTmp]
                           = rootSeqIdx;
                     }
                  }
               }
            }
            break;
         case WR_TAG_PRACHCFG_IDX_LIST:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  status     = TRUE;
                  noOfParams = 0;
                  noOfElem   = 0;
                  U16 prachCfgIdx = 0;
                  wrCfgValdtInput(tagVal, &status, &noOfElem);
                  if (TRUE == status)
                  {
                     wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                     if(noOfParams > WR_SM_MAX_PRACHCFG_IDX)
                     {
                        noOfParams = WR_SM_MAX_PRACHCFG_IDX;
                     }
                     lteeNodeBparams[loopCnt].ltePrachCfgCommon.prachParamLst.numPrachCfgIdx = noOfParams;

                     for (loopCntTmp=0; loopCntTmp < noOfParams; loopCntTmp++)
                     {
                        prachCfgIdx = atoi((S8*)paramLst[loopCntTmp]);
                        lteeNodeBparams[loopCnt].ltePrachCfgCommon.prachParamLst.prachCfgIdxLst[loopCntTmp] =
                           prachCfgIdx;
                     }
                  }
               }
            }
            break;
         case WR_TAG_ZERO_CORR_ZONE_CFG_LIST:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  status     = TRUE;
                  noOfParams = 0;
                  noOfElem   = 0;
                  U16 zeroCorrZoneCfg = 0;
                  wrCfgValdtInput(tagVal, &status, &noOfElem);
                  if (TRUE == status)
                  {
                     wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                     if(noOfParams > WR_SM_MAX_ZEROCORRZONECFG_IDX)
                     {
                        noOfParams = WR_SM_MAX_ZEROCORRZONECFG_IDX;
                     }
                     lteeNodeBparams[loopCnt].ltePrachCfgCommon.prachParamLst.numZeroCorrZoneCfg =
                        noOfParams;

                     for (loopCntTmp=0; loopCntTmp < noOfParams; loopCntTmp++)
                     {
                        zeroCorrZoneCfg = atoi((S8*)paramLst[loopCntTmp]);
                        lteeNodeBparams[loopCnt].ltePrachCfgCommon.prachParamLst.zeroCorrelationZoneCfgLst[loopCntTmp]
                           = zeroCorrZoneCfg;
                     }
                  }
               }
            }
            break;
         case WR_TAG_PRACH_FREQ_OFFSET_LIST:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  status     = TRUE;
                  noOfParams = 0;
                  noOfElem   = 0;
                  U16 prachFreqOffset = 0;
                  wrCfgValdtInput(tagVal, &status, &noOfElem);
                  if (TRUE == status)
                  {
                     wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                     if(noOfParams > WR_SM_MAX_PRACHFREQOFFSET_IDX)
                     {
                        noOfParams = WR_SM_MAX_PRACHFREQOFFSET_IDX;
                     }
                     lteeNodeBparams[loopCnt].ltePrachCfgCommon.prachParamLst.numPrachFreqOffset = noOfParams;

                     for (loopCntTmp=0; loopCntTmp < noOfParams; loopCntTmp++)
                     {
                        prachFreqOffset = atoi((S8*)paramLst[loopCntTmp]);
                        lteeNodeBparams[loopCnt].ltePrachCfgCommon.prachParamLst.prachFreqOffsetLst[loopCntTmp] = prachFreqOffset;
                     }
                  }
               }
            }
            break;
         case WR_TAG_ROOTSEQ_IDX:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].ltePrachCfgCommon.rootSequenceIndx = (U16)atoi((S8 *)tagVal);
               }
            }
            break;
         case WR_TAG_ZERO_CORR_ZONE_CFG:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].ltePrachCfgCommon.prachCfgInfo.zeroCorrelationZoneCfg = (U8)atoi((S8 *)tagVal);
               }
            }
            break;
         case WR_TAG_PRACH_FREQ_OFFSET:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].ltePrachCfgCommon.prachCfgInfo.prachFreqOffset = (U8)atoi((S8 *)tagVal);
               }
            }
            break;
         case WR_TAG_NO_OF_MME_INFO:
         case WR_TAG_NO_OF_MME_INFO_IPV6:
            {
                  smCfgCb.noOfCfg = (U8)atoi((S8 *)tagVal);/*remove in
                                                             future*/
               fapParameters.lteeNodeBIPparams.lteS1connmode = 
                  (U8)atoi((S8 *)tagVal);
            }
            break;   
         case WR_TAG_MME_INFO:
         case WR_TAG_MME_INFO_IPV6:
            {
#ifndef WR_RSYS_OAM
               U8 loopCnt1 = 0;
               status = TRUE;
               noOfElem = 0;
               noOfParams = 0;
               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  if(noOfElem != fapParameters.lteeNodeBIPparams.lteS1connmode)
                  {
                     fprintf(stderr, " Number of parameters in %d mismatch \n",tagNum);
                     RETVALUE(RFAILED);
                  }
                  paramCnt = 0;
                  for(loopCnt1 = 0; loopCnt1 < noOfElem; loopCnt1++)
                  {
                     WR_ALLOC(&mmeCfg, sizeof(LwrMmeCfg));
                     mmeCfg->mmeId = (U16)atoi((S8 *)paramLst[paramCnt++]);
                     mmeCfg->noOfIps = (U8)atoi((S8 *)paramLst[paramCnt++]);
                     if (mmeCfg->noOfIps > LWR_MAX_IP_PER_MME)
                     {
                        mmeCfg->noOfIps = LWR_MAX_IP_PER_MME;
                     }
                     for(ipIdx = 0; ipIdx < mmeCfg->noOfIps; ipIdx++)  
                     {
                        wrUpdateIpAddr((U8 *)paramLst[paramCnt++], 
                              &(mmeCfg->mmeAddr[ipIdx]));
                     }
                     smCfgCb.mmeCfg[loopCnt1] = mmeCfg;
                  }
               }
               else
               {
                  fprintf(stderr, " Error in %d tag format\n ",tagNum);
                  RETVALUE(RFAILED);
               }
#else
#endif
            }
            break;   
         case WR_TAG_HI_DBG:
            {
                  smCfgCb.hiDbg = (U8)atoi((S8 *)tagVal);
               fapParameters.lteDbgParams.hiDbg = (U8)atoi((S8 *)tagVal);
            }
            break;   
         case WR_TAG_SB_DBG:
            {
                  smCfgCb.sbDbg = (U8)atoi((S8 *)tagVal);
               fapParameters.lteDbgParams.sbDbg = (U8)atoi((S8 *)tagVal);
            }
            break;   
         case WR_TAG_SZ_DBG:
            {
                  smCfgCb.szDbg = (U8)atoi((S8 *)tagVal);
               fapParameters.lteDbgParams.szDbg = (U8)atoi((S8 *)tagVal);
            }
            break;   
         case WR_TAG_EG_DBG:
            {
                  smCfgCb.egDbg = (U8)atoi((S8 *)tagVal);
               fapParameters.lteDbgParams.egDbg = (U8)atoi((S8 *)tagVal);
            }
            break;   
         case WR_TAG_WR_DBG:
            {
                  smCfgCb.wrDbg  = (U8)atoi((S8 *)tagVal);
               fapParameters.lteDbgParams.wrDbg = (U8)atoi((S8 *)tagVal);
            }
            break;   
         case WR_TAG_NH_DBG:
            {
                  smCfgCb.nhDbg = (U8)atoi((S8 *)tagVal);
               fapParameters.lteDbgParams.nhDbg = (U8)atoi((S8 *)tagVal);
            }
            break;   
         case WR_TAG_KW_DBG:
            {
                  smCfgCb.kwDbg = (U8)atoi((S8 *)tagVal);
               fapParameters.lteDbgParams.kwDbg = (U8)atoi((S8 *)tagVal);
            }
            break;   
         case WR_TAG_RG_DBG:
            {
                  smCfgCb.rgDbg = (U8)atoi((S8 *)tagVal);
               fapParameters.lteDbgParams.rgDbg = (U8)atoi((S8 *)tagVal);
            }
            break;   
         case WR_TAG_YS_DBG:
            {
                  smCfgCb.ysDbg = (U8)atoi((S8 *)tagVal);
               fapParameters.lteDbgParams.ysDbg = (U8)atoi((S8 *)tagVal);
            }
            break;   
         case WR_TAG_SM_DBG:
            {
                  smCfgCb.smDbg = (U8)atoi((S8 *)tagVal);
               fapParameters.lteDbgParams.smDbg = (U8)atoi((S8 *)tagVal);
            }
            break;   
         case WR_TAG_INACTIVITY_TIMER_VAL:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteEnbProtoCfg.inactvTmrVal = atoi((S8 *)tagVal);
               }
            }
            break;   
         case WR_TAG_END_MARKER_TIMER_VAL:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteEnbProtoCfg.endMrkTmrVal = atoi((S8 *)tagVal);
               }
            }
            break;   
         case WR_TAG_MAX_EXPIRY:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteEnbProtoCfg.maxExpires = atoi((S8 *)tagVal);
               }
            }
            break;   
         case WR_TAG_CZ_DBG:
            {
                  smCfgCb.czDbg = (U8)atoi((S8 *)tagVal);
               fapParameters.lteDbgParams.czDbg = (U8)atoi((S8 *)tagVal);
            }
            break;
         case WR_TAG_X2_PREP_TMR:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteProcTimerCfg.x2PrepTimerVal = atoi((S8 *)tagVal);
               }
            }
            break;
         case WR_TAG_X2_OVRALL_TMR:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteProcTimerCfg.x2OvrAllTimerVal = atoi((S8 *)tagVal);
               }
            }
            break;
         case WR_TAG_UE_HO_ATTACH_TMR:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  smCfgCb.ueHoAttachTimerVal = atoi((S8 *)tagVal);
               }
            }
            break;
         case WR_TAG_X2_TIME_TO_WAIT:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteProcTimerCfg.x2TimeToWaitTimerVal = atoi((S8 *)tagVal);
               }
            }
            break;
         case WR_TAG_NO_OF_BRDCST_PLMN:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellSib1CfgGrp.cellAccessInfo.numOfPlmns = (U8)atoi((S8 *)tagVal);
               }
            }
            break;
         case WR_TAG_PLMN_ID_LST:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  status = TRUE;
                  noOfElem = 0;
                  noOfParams = 0;
                  wrCfgValdtInput(tagVal, &status, &noOfElem);
                  if (TRUE == status)
                  {
                     wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                     for (loopCntTmp = 0; loopCntTmp < noOfParams; loopCntTmp++)
                     {
                        strcpy((S8 *)smCfgCb.plmnId[loopCntTmp], (S8 *)paramLst[loopCntTmp]);

                        plmnVal = atoi((S8*)&paramLst[loopCntTmp][0]);
                        plmnLen = strlen((S8 *)paramLst[loopCntTmp]);

                        if(plmnLen == 5)
                        {
                           smCfgCb.plmnId[loopCntTmp][0] = (((plmnVal/1000)%10)<<4)|((plmnVal/10000)%10);
                           smCfgCb.plmnId[loopCntTmp][1] = 0xF0|((plmnVal/100)%10);
                           smCfgCb.plmnId[loopCntTmp][2] = ((plmnVal%10)<<4)|((plmnVal/10)%10);
                        }
                        else if(plmnLen == 6)
                        {
                           smCfgCb.plmnId[loopCntTmp][0] = (((plmnVal/10000)%10)<<4)|((plmnVal/100000)%10);
                           smCfgCb.plmnId[loopCntTmp][1] = (((plmnVal/100)%10)<<4)|((plmnVal/1000)%10);
                           smCfgCb.plmnId[loopCntTmp][2] = ((plmnVal%10)<<4)|((plmnVal/10)%10);
                        }

                        pLMNidentity.val = &smCfgCb.plmnId[loopCntTmp][0];
                        wrUtlGetPlmnId(&plmnId, &pLMNidentity);
                        lteeNodeBparams[loopCnt].lteCellSib1CfgGrp.cellAccessInfo.plmnInfo[0].isPrimary = TRUE;
                        lteeNodeBparams[loopCnt].lteCellSib1CfgGrp.cellAccessInfo. \
                           plmnInfo[pIdx].plmnId.numMncDigits = plmnId.numMncDigits;
                        lteeNodeBparams[loopCnt].lteCellSib1CfgGrp.cellAccessInfo. \
                           plmnInfo[pIdx].plmnId.mcc[0] = plmnId.mcc[0];
                        lteeNodeBparams[loopCnt].lteCellSib1CfgGrp.cellAccessInfo. \
                           plmnInfo[pIdx].plmnId.mcc[1] = plmnId.mcc[1];
                        lteeNodeBparams[loopCnt].lteCellSib1CfgGrp.cellAccessInfo. \
                           plmnInfo[pIdx].plmnId.mcc[2] = plmnId.mcc[2];
                        lteeNodeBparams[loopCnt].lteCellSib1CfgGrp.cellAccessInfo. \
                           plmnInfo[pIdx].plmnId.mnc[0] = plmnId.mnc[0];
                        lteeNodeBparams[loopCnt].lteCellSib1CfgGrp.cellAccessInfo. \
                           plmnInfo[pIdx].plmnId.mnc[1] = plmnId.mnc[1];
                        lteeNodeBparams[loopCnt].lteCellSib1CfgGrp.cellAccessInfo. \
                           plmnInfo[pIdx].plmnId.mnc[2] = plmnId.mnc[2];
                        pIdx++;

                     }
                  }
                  else
                  {
                     fprintf(stderr, " Error in WR_TAG_PLMN_ID_LST tag format \n");
                  }
               }
            }
            break;
         case WR_TAG_NO_OF_UTRA_FDD_NGH_CFG:
            {
               status     = TRUE;
               noOfParams = 0;
               noOfElem   = 0;

               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  for(loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
                  {
                     lteeNodeBparams[loopCnt].lteNeighCellCfg.numUtraCells = \
                                          (U8)atoi((S8 *)paramLst[loopCnt]);
                     if( 0 == lteeNodeBparams[loopCnt].lteNeighFreqCfg.numUtraFreq)
                     {
                        lteeNodeBparams[loopCnt].lteNeighCellCfg.numUtraCells = 0;
                     }
                     if(lteeNodeBparams[loopCnt].lteNeighCellCfg.numUtraCells \
                           > MAX_NBR_UTRA_CELL)
                     {
                        fprintf(stderr, " Number of UTRA FDD cell exceeds MAX_NBR_UTRA_CELL \n");
                     }
                  }
               }
            }
            break;           
         case WR_TAG_NGH_UTRA_FDD_CELL_CFG:
            {
               status = TRUE;
               noOfElem = 0;
               noOfParams = 0;
               U8 idx = 0;

               U8   noOfUtraFddNghCell = 0;
               {
                  wrCfgValdtInput(tagVal, &status, &noOfElem);
                  if (TRUE == status)
                  {
                     wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                     paramCnt = 0;
                     for(loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
                     {
                        for (noOfUtraFddNghCell = 0; noOfUtraFddNghCell < \
                              lteeNodeBparams[loopCnt].lteNeighCellCfg.numUtraCells; \
                              noOfUtraFddNghCell++)
                        {
                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t.neighAddCfg[noOfUtraFddNghCell]. \
                              utranCell.rncId = (U16)atoi((S8 *)paramLst[paramCnt++]);
                           
                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t.neighAddCfg[noOfUtraFddNghCell]. \
                              utranCell.cId = (U16)atoi((S8 *)paramLst[paramCnt++]);

                           /* If extended RNC Id is used 
                            * then CID should be 12 bits */ 
                           if( lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                                 neighAddCfg[noOfUtraFddNghCell].utranCell.rncId >=  \
                                 WR_SM_START_EXT_RNC)
                           {
                              if( lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                                    neighAddCfg[noOfUtraFddNghCell].utranCell.cId >= \
                                    WR_SM_START_EXT_RNC)
                              {
                                 WR_LOGERROR(ERRCLS_DEBUG,0,ERRZERO, 
                                       "Invalid CID configured.RNC Id is 16 bits, \
                                       so CID should be 12 bits \n");
                                 RETVALUE(RFAILED);
                              }
                           }

                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfUtraFddNghCell].utranCell.arfcnDl = \
                              (U16)atoi((S8 *)paramLst[paramCnt++]);

                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfUtraFddNghCell].utranCell.arfcnUl = \
                              (U16)atoi((S8 *)paramLst[paramCnt++]);
                           
                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfUtraFddNghCell].utranCell.psc = \
                              atoi((S8*)paramLst[paramCnt++]);
                           
                           /* Removed one of the comparision to fix warning */

                           if(lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                                neighAddCfg[noOfUtraFddNghCell].utranCell.psc \
                                > WR_SM_MAX_PSC_VAL)
                           {
                              WR_LOGERROR(ERRCLS_DEBUG,0,ERRZERO, "Invalid PSC configured \n");
                              RETVALUE(RFAILED);
                           }
                          lteeNodeBparams[loopCnt].lteNeighCellCfg.t.neighAddCfg[noOfUtraFddNghCell]. \
                             utranCell.numPlmn = atoi((S8*)paramLst[paramCnt++]);
                           
                          plmnVal = atoi((S8*)paramLst[paramCnt++]);
                           if(wrGetNeghPlmn(plmnVal, nghPlmn, &noMnc) == RFAILED)
                           {
                              fprintf(stderr, "Plmn format is wrong");
                              RETVALUE(RFAILED);
                           }
                          lteeNodeBparams[loopCnt].lteNeighCellCfg.t.neighAddCfg[noOfUtraFddNghCell]. \
                             utranCell.plmnId[idx].numMncDigits = noMnc;

                          lteeNodeBparams[loopCnt].lteNeighCellCfg.t.neighAddCfg[noOfUtraFddNghCell]. \
                             utranCell.plmnId[idx].mcc[0] = nghPlmn[0];

                          lteeNodeBparams[loopCnt].lteNeighCellCfg.t.neighAddCfg[noOfUtraFddNghCell]. \
                             utranCell.plmnId[idx].mcc[1] = nghPlmn[1];
                          
                          lteeNodeBparams[loopCnt].lteNeighCellCfg.t.neighAddCfg[noOfUtraFddNghCell]. \
                             utranCell.plmnId[idx].mcc[2] = nghPlmn[2];
                          lteeNodeBparams[loopCnt].lteNeighCellCfg.t.neighAddCfg[noOfUtraFddNghCell]. \
                             utranCell.plmnId[idx].mnc[0] = nghPlmn[3];
                          lteeNodeBparams[loopCnt].lteNeighCellCfg.t.neighAddCfg[noOfUtraFddNghCell]. \
                             utranCell.plmnId[idx].mnc[1] = nghPlmn[4];
                          lteeNodeBparams[loopCnt].lteNeighCellCfg.t.neighAddCfg[noOfUtraFddNghCell]. \
                             utranCell.plmnId[idx].mnc[2] = nghPlmn[5];
                          idx++;

                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfUtraFddNghCell].utranCell.lac = \
                              atoi((S8*)paramLst[paramCnt++]);

                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfUtraFddNghCell].utranCell.rac = \
                              atoi((S8*)paramLst[paramCnt++]);

                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfUtraFddNghCell].utranCell.isRimSupported = \
                              atoi((S8*)paramLst[paramCnt++]); 

                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfUtraFddNghCell].utranCell.isVoipCapable = \
                              atoi((S8*)paramLst[paramCnt++]); 

                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfUtraFddNghCell].utranCell.isPsHOCapable = \
                              atoi((S8*)paramLst[paramCnt++]); 
                        }
                     }
                  }
                  else
                  {
                     fprintf(stderr, "Error in WR_TAG_NGH_UTRA_FDD_CELL_CFG tag format \n");
                  }
               }
            }
            break;
         case WR_TAG_NO_OF_UTRA_TDD_NGH_CFG:
            {
               status     = TRUE;
               noOfParams = 0;
               noOfElem   = 0;

               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  for(loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
                  {
                     lteeNodeBparams[loopCnt].lteNeighCellCfg.numUtraTddCells = \
                             (U8)atoi((S8 *)paramLst[loopCnt]);
                     if( 0 == lteeNodeBparams[loopCnt].lteNeighFreqCfg.numUtraTddFreq)
                     {
                        lteeNodeBparams[loopCnt].lteNeighCellCfg.numUtraTddCells = 0;
                     }
                     if(lteeNodeBparams[loopCnt].lteNeighCellCfg.numUtraTddCells \
                           > MAX_NBR_UTRA_CELL)
                     {
                        fprintf(stderr, " Number of UTRA TDD cell exceeds MAX_NBR_UTRA_CELL \n");
                     }
                  }
               }
            }
            break;
         case WR_TAG_NGH_UTRA_TDD_CELL_CFG:
            {
               status = TRUE;
               noOfElem = 0;
               noOfParams = 0;
               U8   noOfUtraTddNghCell = 0;
               U8 idx = 0;
#if 0 /* For multiCell is this check reqd ? */
               if(0 == smCfgCb.noOfUtraTddFreq[loopCnt])
               {
                  fprintf(stderr, "AS the number of UTRA frequency is zero \
                        no need to read the list");
               }
               else
#endif
               {
                  wrCfgValdtInput(tagVal, &status, &noOfElem);
                  if (TRUE == status)
                  {
                     wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                     paramCnt = 0;
                     for(loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
                     {
                        idx = 0;
                        for (noOfUtraTddNghCell = 0; noOfUtraTddNghCell < \
                              lteeNodeBparams[loopCnt].lteNeighCellCfg.numUtraTddCells; \
                              noOfUtraTddNghCell++)
                        {
                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfUtraTddNghCell].utranTddCell.rncId = \
                              (U16)atoi((S8 *)paramLst[paramCnt++]);

                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfUtraTddNghCell].utranTddCell.cId = \
                              (U16)atoi((S8 *)paramLst[paramCnt++]);

                           /* If extended RNC Id is used 
                            * then CID should be 12 bits */ 
                           if( lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                                 neighAddCfg[noOfUtraTddNghCell].utranTddCell. \
                                 rncId >= WR_SM_START_EXT_RNC)
                           {
                              if( lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                                    neighAddCfg[noOfUtraTddNghCell].utranTddCell. \
                                    cId >= WR_SM_START_EXT_RNC)
                              {
                                 WR_LOGERROR(ERRCLS_DEBUG,0,ERRZERO, 
                                       "Invalid CID configured.RNC Id is 16 bits, \
                                       so CID should be 12 bits \n");
                                 RETVALUE(RFAILED);
                              }
                           }

                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfUtraTddNghCell].utranTddCell.arfcn = \
                              (U16)atoi((S8*)paramLst[paramCnt++]);

                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfUtraTddNghCell].utranTddCell.lac = \
                              atoi((S8*)paramLst[paramCnt++]);

                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfUtraTddNghCell].utranTddCell.pccpch = \
                              atoi((S8*)paramLst[paramCnt++]);

                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfUtraTddNghCell].utranTddCell.cellParamId = \
                              atoi((S8*)paramLst[paramCnt++]);

                           if(lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                                 neighAddCfg[noOfUtraTddNghCell].utranTddCell.cellParamId \
                                 > WR_SM_MAX_CELL_PARAM_VAL)
                           {
                              WR_LOGERROR(ERRCLS_DEBUG,0,ERRZERO, "Invalid Cell Param Id configured \n");
                              RETVALUE(RFAILED);
                           }
                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfUtraTddNghCell].utranTddCell. \
                           numPlmn = atoi((S8*)paramLst[paramCnt++]);
                           plmnVal = atoi((S8*)paramLst[paramCnt++]);
                           if(wrGetNeghPlmn(plmnVal, nghPlmn, &noMnc) == RFAILED)
                           {
                              fprintf(stderr, "Plmn format is wrong");
                              RETVALUE(RFAILED);
                           }
                           
                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfUtraTddNghCell].utranTddCell. \
                              plmnId[idx].numMncDigits = noMnc;
                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfUtraTddNghCell].utranTddCell. \
                              plmnId[idx].mcc[0] = nghPlmn[0];
                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfUtraTddNghCell].utranTddCell. \
                              plmnId[idx].mcc[1] = nghPlmn[1];
                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfUtraTddNghCell].utranTddCell. \
                              plmnId[idx].mcc[2] = nghPlmn[2];
                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfUtraTddNghCell].utranTddCell. \
                              plmnId[idx].mnc[0] = nghPlmn[3];
                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfUtraTddNghCell].utranTddCell. \
                              plmnId[idx].mnc[1] = nghPlmn[4];
                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfUtraTddNghCell].utranTddCell. \
                              plmnId[idx].mnc[2] = nghPlmn[5];
                           idx++;
                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfUtraTddNghCell].utranTddCell.rac = \
                              atoi((S8*)paramLst[paramCnt++]);

                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfUtraTddNghCell].utranTddCell. \
                              isRimSupported = atoi((S8*)paramLst[paramCnt++]);

                        }
                     }
                  }
                  else
                  {
                     fprintf(stderr, "Error in WR_TAG_NGH_UTRA_CELL_CFG tag format \n");
                  }
               }
            }
            break;
         case WR_TAG_NUM_EUTRA_FREQ:
            {
               status     = TRUE;
               noOfParams = 0;
               noOfElem   = 0;

               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  for (loopCnt=0; loopCnt < wrSmDfltNumCells; loopCnt++)
                  {
                     /* Fix for the CR ccpu00127482  */
                     lteeNodeBparams[loopCnt].lteNeighFreqCfg.numEutraFreq = (U16)atoi((S8*)paramLst[loopCnt]);
                  }
               }
            }
            break;
         case WR_TAG_EUTRA_FREQ_CFG:
            {
               U8   noOfLteNghFreq = 0;
               status = TRUE;
               noOfElem = 0;
               noOfParams = 0;
               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
#if 0 /* Is this check required for multiCell ? */
                  if(noOfElem != smCfgCb.noOfEutraFreq)
                  {
                     fprintf(stderr, "Number of parameters in WR_TAG_EUTRA_FREQ_CFG mismatch \n");
                     RETVALUE(RFAILED);
                  }
#endif
                  paramCnt = 0;
                  for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
                  {
                     for(noOfLteNghFreq = 0; \
                           noOfLteNghFreq < lteeNodeBparams[loopCnt].lteNeighFreqCfg.numEutraFreq; \
                           noOfLteNghFreq ++)
                     {
                        lteeNodeBparams[loopCnt].lteNeighFreqCfg.t.addNeighFreq[noOfLteNghFreq]. \
                           eutranFreq.earfcnDl = (U16)atoi((S8 *)paramLst[paramCnt++]);                               
                        lteeNodeBparams[loopCnt].lteNeighFreqCfg.t.addNeighFreq[noOfLteNghFreq]. \
                           eutranFreq.earfcnUl = (U16)atoi((S8 *)paramLst[paramCnt++]);                               
                     }
                  }
               }
               else
               {
                  fprintf(stderr, "Error in WR_TAG_EUTRA_FREQ_CFG tag format \n");
               }
            }
            break;
         case WR_TAG_NUM_UTRA_FDD_FREQ:
            {
               status     = TRUE;
               noOfParams = 0;
               noOfElem   = 0;

               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  for(loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
                  {
                     lteeNodeBparams[loopCnt].lteNeighFreqCfg.numUtraFreq = (U16)atoi((S8 *)paramLst[loopCnt]);
                     if (lteeNodeBparams[loopCnt].lteNeighFreqCfg.numUtraFreq > MAX_NBR_UTRA_FREQ)
                     {
                        fprintf(stderr, " lteeNodeBparams[%d].lteNeighFreqCfg.numUtraFreq \
                              greater than MAX_NBR_UTRA_FREQ(%d)\n", 
                              lteeNodeBparams[loopCnt].lteNeighFreqCfg.numUtraFreq, MAX_NBR_UTRA_FREQ);
                        RETVALUE(RFAILED);
                     }
                  }
               }
            }
            break;
         case WR_TAG_UTRA_FDD_FREQ_CFG:
            {
               U8   noOfUtraNghFreq = 0;
               status = TRUE;
               noOfElem = 0;
               noOfParams = 0;
               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
#if 0 /* Is this check required for multiCell ? */
                  if(noOfElem != smCfgCb.noOfUtraFddFreq)
                  {
                     fprintf(stderr, " Number of parameters in WR_TAG_UTRA_FDD_FREQ_CFG mismatch \n");
                     RETVALUE(RFAILED);
                  }
#endif
                  paramCnt = 0;
                  for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
                  {
                     for(noOfUtraNghFreq = 0; noOfUtraNghFreq < \
                           lteeNodeBparams[loopCnt].lteNeighFreqCfg.numUtraFreq; noOfUtraNghFreq++)
                     {
                        lteeNodeBparams[loopCnt].lteNeighFreqCfg.t.addNeighFreq[noOfUtraNghFreq]. \
                           utranFreq.arfcnDl = (U16)atoi((S8 *)paramLst[paramCnt++]);
                        lteeNodeBparams[loopCnt].lteNeighFreqCfg.t.addNeighFreq[noOfUtraNghFreq]. \
                           utranFreq.arfcnUl = (U16)atoi((S8 *)paramLst[paramCnt++]);

                     }
                  }
               }
               else
               {
                  fprintf(stderr, " Error in WR_TAG_UTRA_FDD_FREQ_CFG tag format \n");
               }
            }
            break;
         case WR_TAG_NUM_UTRA_TDD_FREQ:
            {
               status     = TRUE;
               noOfParams = 0;
               noOfElem   = 0;

               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  for(loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
                  {
                     lteeNodeBparams[loopCnt].lteNeighFreqCfg.numUtraTddFreq = \
                                             (U16)atoi((S8 *)paramLst[loopCnt]);
                     if (lteeNodeBparams[loopCnt].lteNeighFreqCfg.numUtraTddFreq > MAX_NBR_UTRA_FREQ)
                     {
                        fprintf(stderr, " lteeNodeBparams(%d).lteNeighFreqCfg.numUtraTddFreq \
                              greater than MAX_NBR_UTRA_FREQ(%d)\n", 
                              lteeNodeBparams[loopCnt].lteNeighFreqCfg.numUtraTddFreq, MAX_NBR_UTRA_FREQ);
                        RETVALUE(RFAILED);
                     }
                  }
               }
            }
            break;
         case WR_TAG_UTRA_TDD_FREQ_CFG:
            {
               U8   noOfUtraNghFreq = 0;
               status = TRUE;
               noOfElem = 0;
               noOfParams = 0;
               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
#if 0 /* Is this check required for multiCell ? */
                  if(noOfElem != smCfgCb.noOfUtraTddFreq)
                  {
                     fprintf(stderr, " Number of parameters in WR_TAG_UTRA_TDD_FREQ_CFG mismatch \n");
                     RETVALUE(RFAILED);
                  }
#endif
                  paramCnt = 0;
                  for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
                  {
                     for (noOfUtraNghFreq = 0; noOfUtraNghFreq < \
                           lteeNodeBparams[loopCnt].lteNeighFreqCfg.numUtraTddFreq; noOfUtraNghFreq++)
                     {
                        lteeNodeBparams[loopCnt].lteNeighFreqCfg.t. \
                           addNeighFreq[noOfUtraNghFreq].utranTddFreq.arfcn = \
                          (U16)atoi((S8 *)paramLst[paramCnt++]);
                        lteeNodeBparams[loopCnt].lteNeighFreqCfg.t. \
                           addNeighFreq[noOfUtraNghFreq].utranTddFreq.tddMode = \
                           (U16)atoi((S8 *)paramLst[paramCnt++]);
                        lteeNodeBparams[loopCnt].lteNeighFreqCfg.t.addNeighFreq[noOfUtraNghFreq]. \
                           utranTddFreq.bandIndicator = (U8)atoi((S8 *)paramLst[paramCnt++]);
                     }
                  }
               }
               else
               {
                  fprintf(stderr, " Error in WR_TAG_UTRA_TDD_FREQ_CFG tag format \n");
               }
            }
            break;
         case WR_TAG_NUM_GERAN_NEIGH_FREQ:
            {
               status     = TRUE;
               noOfParams = 0;
               noOfElem   = 0;

               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
               }
               for(loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteNeighFreqCfg.numGeranFreq =  \
                  atoi((S8*)paramLst[loopCnt]) /*(U16)atoi((S8 *)tagVal)*/;
               }
            }
            break;
         case WR_TAG_GERAN_NEIGH_FREQ:
            {
               U8   noOfGeranNghFreq = 0;
               status = TRUE;
               noOfElem = 0;
               noOfParams = 0;
               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
#if 0 /* Whether to have this Check for multicell ? */
                  if((noOfElem != smCfgCb.noOfGeranFreq) ||
                        (LWR_MAX_NUM_NEIGH_GERAN_FREQS < noOfElem))
                  {
                     fprintf(stderr, " Number of parameters in WR_TAG_GERAN_NEIGH_FREQ mismatch \n");
                     RETVALUE(RFAILED);
                  }
#endif
                  paramCnt = 0;
                  for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
                  {
                     for (noOfGeranNghFreq = 0; noOfGeranNghFreq < \
                           lteeNodeBparams[loopCnt].lteNeighFreqCfg.numGeranFreq; \
                           noOfGeranNghFreq++)
                     {
                        lteeNodeBparams[loopCnt].lteNeighFreqCfg.t.addNeighFreq[noOfGeranNghFreq]. \
                           geranFreq.bandIndicator = (Bool)atoi((S8 *)paramLst[paramCnt++]);

                        lteeNodeBparams[loopCnt].lteNeighFreqCfg.t.addNeighFreq[noOfGeranNghFreq]. \
                           geranFreq.bcchArfcn = (U16)atoi((S8 *)paramLst[paramCnt++]);
                       
                        lteeNodeBparams[loopCnt].lteNeighFreqCfg.t.addNeighFreq[noOfGeranNghFreq]. \
                           geranFreq.cellReselectionPriority = (U8)atoi((S8 *)paramLst[paramCnt++]);
                        
                        lteeNodeBparams[loopCnt].lteNeighFreqCfg.t.addNeighFreq[noOfGeranNghFreq]. \
                           geranFreq.ncc_Permitted = (U8)atoi((S8 *)paramLst[paramCnt++]);
                     }
                  }
               }
               else
               {
                  fprintf(stderr, " Error in WR_TAG_GERAN_NEIGH_FREQ tag format \n");
               }
            }
            break;
         case WR_TAG_NUM_GERAN_NEIGH_CELL:
            {
               status     = TRUE;
               noOfParams = 0;
               noOfElem   = 0;

               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  for(loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
                  {
                     lteeNodeBparams[loopCnt].lteNeighCellCfg.numGeranCells = \
                                      (U8)atoi((S8 *)paramLst[loopCnt]);
                  }
               }
            }
            break;
         case WR_TAG_GERAN_NEIGH_CELL:
            {
               status = TRUE;
               noOfElem = 0;
               noOfParams = 0;
               U8   noOfGeranNghCell = 0;
               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
#if 0 /* Is this check required for multiCell */
                  if(noOfElem > LWR_MAX_NUM_NEIGH_GERAN_CELLS)
                  {
                     fprintf(stderr, " Number of nighbors in WR_TAG_GERAN_NEIGH_CELL are exceeding 16 \n");
                     RETVALUE(RFAILED);
                  }
#endif
                  paramCnt = 0;
                  for(loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
                  {
                     for (noOfGeranNghCell = 0; noOfGeranNghCell < \
                           lteeNodeBparams[loopCnt].lteNeighCellCfg.numGeranCells; \
                           noOfGeranNghCell++)
                     {
                        plmnVal = (U32)atoi((S8 *)paramLst[paramCnt++]);
                        if(wrGetNeghPlmn(plmnVal, nghPlmn, &noMnc) == RFAILED)
                        {
                           fprintf(stderr, " Plmn format is wrong \n");
                           RETVALUE(RFAILED);
                        }
                        lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                           neighAddCfg[noOfGeranNghCell].geranCell.plmnId. \
                           numMncDigits = noMnc;

                        lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                           neighAddCfg[noOfGeranNghCell].geranCell.plmnId.mcc[0] \
                           = nghPlmn[0];

                        lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                           neighAddCfg[noOfGeranNghCell].geranCell.plmnId.mcc[1] \
                           = nghPlmn[1];
                        
                        lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                           neighAddCfg[noOfGeranNghCell].geranCell.plmnId.mcc[2] \
                           = nghPlmn[2];
                        
                        lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                           neighAddCfg[noOfGeranNghCell].geranCell.plmnId.mnc[0] \
                           = nghPlmn[3];
                        
                        lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                           neighAddCfg[noOfGeranNghCell].geranCell.plmnId.mnc[1] \
                           = nghPlmn[4];
                        if(noMnc == 3)
                        {
                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfGeranNghCell].geranCell.plmnId.mnc[2] \
                              = nghPlmn[5];
                        }

                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfGeranNghCell].geranCell.lac \
                              = (U16)atoi((S8 *)paramLst[paramCnt++]);
                        
                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfGeranNghCell].geranCell.rac \
                              = (U8)atoi((S8 *)paramLst[paramCnt++]);

                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfGeranNghCell].geranCell.bsic \
                              = (U8)atoi((S8 *)paramLst[paramCnt++]);

                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfGeranNghCell].geranCell.ci \
                              = (U16)atoi((S8 *)paramLst[paramCnt++]);

                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfGeranNghCell].geranCell.bandIndicator \
                              = (Bool)atoi((S8 *)paramLst[paramCnt++]);

                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfGeranNghCell].geranCell.bcchArfcn \
                              = (U16)atoi((S8 *)paramLst[paramCnt++]);

                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfGeranNghCell].geranCell.ncc_PermittedMeas \
                              = (U8)atoi((S8 *)paramLst[paramCnt++]);
                       
                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfGeranNghCell].geranCell.isDTMCapable \
                              = (Bool)atoi((S8 *)paramLst[paramCnt++]);
                      
                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfGeranNghCell].geranCell.rimSupportForGeranNgh \
                              = (Bool)atoi((S8 *)paramLst[paramCnt++]);
                        
                        /* not reading nco from wr_cfg.txt but by default setting the value to 0
                      * and presence set to true*/
                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfGeranNghCell].geranCell. \
                              networkControlOrderPres = PRSNT_NODEF;
                       
                           lteeNodeBparams[loopCnt].lteNeighCellCfg.t. \
                              neighAddCfg[noOfGeranNghCell].geranCell. \
                              networkControlOrder = 0;


                     }
                  }
               }
               else
               {
                  fprintf(stderr, " Error in WR_TAG_GERAN_NEIGH_CELL tag format \n");
               }
            }
            break;
         case WR_TAG_GERAN_MEAS_CFG:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  status = TRUE;
                  noOfElem = 0;
                  noOfParams = 0;
                  wrCfgValdtInput(tagVal, &status, &noOfElem);
                  if (TRUE == status)
                  {
                     paramCnt = 0;
                     wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                     lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measGERANPeridRptCfg[0].reportInterval = \
                                                                                                atoi((S8 *)paramLst[paramCnt++]);
                     lteeNodeBparams[loopCnt].csfbToGeranCfg.isGERANMeasAllowedForCCO = \
                                                                               (Bool)atoi((S8 *)paramLst[paramCnt++]);
                     lteeNodeBparams[loopCnt].csfbToGeranCfg.isCCOAllowed = (Bool)atoi((S8 *)paramLst[paramCnt++]);
                     lteeNodeBparams[loopCnt].csfbToGeranCfg.GERANMeasWaitTmr = (U32)atoi((S8 *)paramLst[paramCnt++]);
                     lteeNodeBparams[loopCnt].csfbToGeranCfg.T304expWaitTmrVal = (U32)atoi((S8 *)paramLst[paramCnt++]);
                     lteeNodeBparams[loopCnt].csfbToGeranCfg.rrcDatCfmWaitTmr = (U32)atoi((S8 *)paramLst[paramCnt++]);
                  }
                  else
                  {
                     ALARM("Wrong WR_TAG_MEAS_GERAN tag format\n");
                  }
               }
            }
            break;
         case WR_TAG_NUM_CDMA_1XRTT_BAND_CLS:
            {
               status     = TRUE;
               noOfParams = 0;
               noOfElem   = 0;

               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  for(loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
                  {
                     lteeNodeBparams[loopCnt].cdmaBandClassParams.numBandClass = \
                                            (U16)atoi((S8 *)paramLst[loopCnt]);
                  }
               }
            }
            break;

         case WR_TAG_CDMA_1XRTT_BAND_CLS:
            {
               U8   noOfCdmaBndCls = 0;
               status = TRUE;
               noOfElem = 0;
               noOfParams = 0;
               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
#if 0 /* Is this check reqd for multiCell ? */
                  if(noOfElem != smCfgCb.noOfCdma1xBndCls)
                  {
                     fprintf(stderr, "Number of parameters in WR_TAG_CDMA_1XRTT_BAND_CLS mismatch");
                     RETVALUE(RFAILED);
                  }
#endif
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  paramCnt = 0;
                  for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
                  {
                     for (noOfCdmaBndCls = 0; noOfCdmaBndCls < \
                           lteeNodeBparams[loopCnt].cdmaBandClassParams.numBandClass; \
                           noOfCdmaBndCls++)
                     {
                           lteeNodeBparams[loopCnt].cdmaBandClassParams.t.bandClassAddCfg[noOfCdmaBndCls]. \
                              t.bandClass1XRtt.bandClass =  atoi((S8*)paramLst[paramCnt++]);
               
                             if(WR_CDMA_2K_BAND_CLASS_21 >= lteeNodeBparams[loopCnt]. \
                               cdmaBandClassParams.t.bandClassAddCfg[noOfCdmaBndCls]. \
                               t.bandClass1XRtt.bandClass)
                        {

                           lteeNodeBparams[loopCnt].cdmaBandClassParams.t.bandClassAddCfg[noOfCdmaBndCls]. \
                              t.bandClass1XRtt.cellReselectPrior =  atoi((S8*)paramLst[paramCnt++]);

                           lteeNodeBparams[loopCnt].cdmaBandClassParams.t.bandClassAddCfg[noOfCdmaBndCls]. \
                              t.bandClass1XRtt.threshXHigh =  atoi((S8*)paramLst[paramCnt++]);

                           lteeNodeBparams[loopCnt].cdmaBandClassParams.t.bandClassAddCfg[noOfCdmaBndCls]. \
                              t.bandClass1XRtt.threshXLow =  atoi((S8*)paramLst[paramCnt++]);
                           
                        }
                     }
                  }
               }
               else
               {
                  fprintf(stderr, "Error in WR_TAG_CDMA_1XRTT_BAND_CLS tag format");
               }
            }
            break;
         case WR_TAG_NUM_CDMA_1XRTT_NEIGH_FREQ:
            {
               status     = TRUE;
               noOfParams = 0;
               noOfElem   = 0;

               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  for(loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
                  {
                    /* lteeNodeBparams[loopCnt].cdmaBandClassParams.numBandClass = \
                         (U16)atoi((S8 *)paramLst[loopCnt]);*/
                     lteeNodeBparams[loopCnt].lteNeighFreqCfg.numCdma1xFreq = \
                         (U16)atoi((S8 *)paramLst[loopCnt]);
                  }
               }
            }
            break;
         case WR_TAG_CDMA_1XRTT_NEIGH_FREQ:
            {
               U8   noOfCdmaFreq = 0;
               status = TRUE;
               noOfElem = 0;
               noOfParams = 0;
               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  paramCnt = 0;
                  for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
                  {
                     for (noOfCdmaFreq = 0; noOfCdmaFreq < \
                          lteeNodeBparams[loopCnt].lteNeighFreqCfg.numCdma1xFreq; \
                           noOfCdmaFreq++)
                     {
                        lteeNodeBparams[loopCnt].lteNeighFreqCfg.t.addNeighFreq[noOfCdmaFreq]. \
                           cdma1xFreq.bandClass =  atoi((S8*)paramLst[paramCnt++]);
                        lteeNodeBparams[loopCnt].lteNeighFreqCfg.t.addNeighFreq[noOfCdmaFreq]. \
                           cdma1xFreq.arfcn = atoi((S8*)paramLst[paramCnt++]);
                        lteeNodeBparams[loopCnt].lteNeighFreqCfg.t.addNeighFreq[noOfCdmaFreq]. \
                           cdma1xFreq.freqPriority = atoi((S8*)paramLst[paramCnt++]);


                     }
                  }
               }
               else
               {
                  fprintf(stderr, "Error in WR_TAG_CDMA_1XRTT_BAND_CLS tag format");
               }
            }
            break;
         case WR_TAG_NUM_CDMA_1XRTT_NEIGH_CELL:
            {
               status     = TRUE;
               noOfParams = 0;
               noOfElem   = 0;

               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  for(loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
                  {
                     lteeNodeBparams[loopCnt].lteNeighCellCfg.numCdma1xCells = (U16)atoi((S8 *)paramLst[loopCnt]);
                  }
               }
            }
            break;
         case WR_TAG_CDMA_1XRTT_NEIGH_CELL:
            {
               U8   noOfCdmaCells = 0;
               status = TRUE;
               noOfElem = 0;
               noOfParams = 0;
               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
#if 0 /* Is this check reqd for multiCell ? */
                  if(noOfElem != smCfgCb.noOfNeighCdma1xCells)
                  {
                     fprintf(stderr, "Number of parameters in WR_TAG_CDMA_1XRTT_NEIGH_CELL mismatch");
                     RETVALUE(RFAILED);
                  }
#endif
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  paramCnt = 0;
                  for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
                  {
                     for (noOfCdmaCells = 0; noOfCdmaCells < \
                           lteeNodeBparams[loopCnt].lteNeighCellCfg.numCdma1xCells; noOfCdmaCells++)
                     {
                        lteeNodeBparams[loopCnt].lteNeighCellCfg.t.neighAddCfg[noOfCdmaCells]. \
                           cdma1xCell.bandClass =  atoi((S8*)paramLst[paramCnt++]);

                        lteeNodeBparams[loopCnt].lteNeighCellCfg.t.neighAddCfg[noOfCdmaCells]. \
                           cdma1xCell.arfcn = atoi((S8*)paramLst[paramCnt++]);
                       
                        lteeNodeBparams[loopCnt].lteNeighCellCfg.t.neighAddCfg[noOfCdmaCells]. \
                           cdma1xCell.pnOffset = atoi((S8*)paramLst[paramCnt++]);

                        lteeNodeBparams[loopCnt].lteNeighCellCfg.t.neighAddCfg[noOfCdmaCells]. \
                           cdma1xCell.curRank = atoi((S8*)paramLst[paramCnt++]);
                        lteeNodeBparams[loopCnt].lteNeighCellCfg.t.neighAddCfg[noOfCdmaCells]. \
                           cdma1xCell.neighCellFlag = atoi((S8*)paramLst[paramCnt++]);
                        

                     }
                  }
               }
               else
               {
                  fprintf(stderr, "Error in WR_TAG_CDMA_1XRTT_BAND_CLS tag format");
               }
            }
            break;
         case WR_TAG_CSFB_UTRA_CFG_VAL:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  /*0 withoutMeas, 1 withMeas */
                  lteeNodeBparams[loopCnt].csfbCfgGrp.csfbToUtranWithMeasEnabled = atoi((S8*)tagVal);
               }
            }
            break;
         case WR_TAG_CSFB_CDMA_CFG_VAL:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  /*0 withoutMeas, 1 withMeas */
                  lteeNodeBparams[loopCnt].csfbCfgGrp.csfbSupport = atoi((S8*)tagVal);
               }
            }
            break;
         case WR_TAG_ECSFB_CFG_VAL:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  /* 0 notSuporrted, 1 withoutMeas, 2 withMeas */
                  lteeNodeBparams[loopCnt].csfbCfgGrp.ecsfbSupport = atoi((S8*)tagVal);
               }
            }
            break;
         case WR_TAG_DUAL_RX_SUPPORTED:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].csfbCfgGrp.dualRxSup = atoi((S8*)tagVal);
               }
            }
            break;
         case WR_TAG_NO_OF_NGH_INFO:
            {
               smCfgCb.noOfNghInfo = (U16)atoi((S8 *)tagVal);
            }
            break;
         case WR_TAG_NO_OF_GU_GRP:
            {
               smCfgCb.noOfguGrp = (U8)atoi((S8 *)tagVal);
            }
            break;
         case WR_TAG_S1_PREP_TMR:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteProcTimerCfg.s1PrepTimerVal = atoi((S8 *)tagVal);
                  lteeNodeBparams[loopCnt].lteProcTimerCfg.s1RATPrepTimerVal = atoi((S8 *)tagVal);
               }
            }
            break;
         case WR_TAG_S1_OVRALL_TMR:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteProcTimerCfg.s1OvrAllTimerVal = atoi((S8 *)tagVal);
                  lteeNodeBparams[loopCnt].lteProcTimerCfg.s1RATOvrAllTimerVal = atoi((S8 *)tagVal);
               }
            }
            break;
         case WR_TAG_SRC_HO_CANCEL_TMR:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteProcTimerCfg. \
                     s1HandoverCancelTmr = atoi((S8*)tagVal);
                  if((lteeNodeBparams[loopCnt].lteProcTimerCfg.s1HandoverCancelTmr < 400) || \
                        (lteeNodeBparams[loopCnt].lteProcTimerCfg. \
                         s1HandoverCancelTmr > 1000))
                  {
                     lteeNodeBparams[loopCnt].lteProcTimerCfg.s1HandoverCancelTmr \
                        = wrSmDflts1HandoverCancelTmr;
                  } 
               }
            }
            break;
         case WR_TAG_NO_OF_NGH_CFG:
         case WR_TAG_NO_OF_NGH_CFG_IPV6:
            {
               status     = TRUE;
               noOfParams = 0;
               noOfElem   = 0;

               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  if(noOfParams > wrSmDfltNumCells)
                  {
                     noOfParams = wrSmDfltNumCells;
                  }
                  for (loopCnt=0; loopCnt<noOfParams; loopCnt++)
                  {
                       lteeNodeBparams[loopCnt].lteNeighCellCfg.numEutraCells = \
                                            (U8)atoi((S8*)paramLst[loopCnt]);
                     /* Fix for the CR ccpu00127482  */
                  }
               }
            }
            break;
         case WR_TAG_NGH_CELL_CFG:
         case WR_TAG_NGH_CELL_CFG_IPV6:
            {
               U8   noOfLteNghCell = 0;
               status = TRUE;
               U8    tmpPlmnId[LWR_SM_MAX_PLMN_IDS][3];
               noOfElem = 0;
               noOfParams = 0;
               U32 plmn = 0;
               U8 idx = 0;
               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  paramCnt = 0;
                  loopCnt = 0;
                  for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
                  {
                     idx = 0;
                     MsmNeighCellCfg * nghCellCfg = &(lteeNodeBparams[loopCnt].lteNeighCellCfg);
                     for (noOfLteNghCell = 0; noOfLteNghCell < nghCellCfg->numEutraCells; noOfLteNghCell++)
                     {
                        peerId = 0;

                           cmInetAddr((S8 *)paramLst[paramCnt++],&(nghCellCfg->t.neighAddCfg[noOfLteNghCell]. \
                                 eutraCell.enbAddr));

                        nghCellCfg->t.neighAddCfg[noOfLteNghCell].eutraCell.enbAddr =  \
                           CM_INET_HTON_U32(nghCellCfg->t.neighAddCfg[noOfLteNghCell].eutraCell.enbAddr);

                        nghCellCfg->t.neighAddCfg[noOfLteNghCell].eutraCell.pci = \
                                                                                  (U16)atoi((S8 *)paramLst[paramCnt++]);

                        nghCellCfg->t.neighAddCfg[noOfLteNghCell].eutraCell.tac = \
                                                                                  (U16)atoi((S8 *)paramLst[paramCnt++]);

                        nghCellCfg->t.neighAddCfg[noOfLteNghCell].eutraCell.cid = atoi((S8 *)paramLst[paramCnt++]);

                        plmnLen = strlen((S8 *)paramLst[paramCnt]);
                        plmn = atoi((S8 *)paramLst[paramCnt++]);

                        nghCellCfg->t.neighAddCfg[noOfLteNghCell].eutraCell.enbType = \
                             smGetEnbType(nghCellCfg->t.neighAddCfg[noOfLteNghCell]. \
                                              eutraCell.pci, loopCnt);
                        printf("CNM:nghCellCfg plmnId:%lu\n",plmn);

                        if(plmnLen == 5)
                        {
                           tmpPlmnId[loopCnt][0] = (((plmn / 1000) % 10) << 4) | ((plmn / 10000) % 10);
                           tmpPlmnId[loopCnt][1] = 0xF0 | ((plmn / 100) % 10);
                           tmpPlmnId[loopCnt][2] = ((plmn % 10) << 4) | ((plmn / 10) % 10);

                        }
                        else if(plmnLen == 6)
                        {
                           tmpPlmnId[loopCnt][0] = (((plmn / 10000) % 10) << 4) | ((plmn / 100000) % 10);
                           tmpPlmnId[loopCnt][1] = (((plmn / 100) % 10) << 4) | ((plmn / 1000) % 10);
                           tmpPlmnId[loopCnt][2] = ((plmn % 10) << 4) | ((plmn / 10) % 10);
                        }
                        else
                        {
                           fprintf(stderr, " Plmn format is wrong \n");
                           RETVALUE(RFAILED);
                        }
                        pLMNidentity.val = &tmpPlmnId[loopCnt][0];
                        wrUtlGetPlmnId(&plmnId, &pLMNidentity);
                        nghCellCfg->t.neighAddCfg[noOfLteNghCell]. \
                           eutraCell.plmnId[idx].numMncDigits = plmnId.numMncDigits;

                        nghCellCfg->t.neighAddCfg[noOfLteNghCell].eutraCell. \
                           plmnId[idx].mcc[0] = plmnId.mcc[0];

                        nghCellCfg->t.neighAddCfg[noOfLteNghCell].eutraCell. \
                           plmnId[idx].mcc[1] = plmnId.mcc[1];

                        nghCellCfg->t.neighAddCfg[noOfLteNghCell].eutraCell. \
                           plmnId[idx].mcc[2] = plmnId.mcc[2];

                        nghCellCfg->t.neighAddCfg[noOfLteNghCell].eutraCell. \
                           plmnId[idx].mnc[0] = plmnId.mnc[0];

                        nghCellCfg->t.neighAddCfg[noOfLteNghCell].eutraCell. \
                           plmnId[idx].mnc[1] = plmnId.mnc[1];

                        nghCellCfg->t.neighAddCfg[noOfLteNghCell].eutraCell. \
                           plmnId[idx].mnc[2] = plmnId.mnc[2];
                        idx++;

#ifndef WR_RSYS_OAM
                        if(nghCellCfg->t.neighAddCfg[noOfLteNghCell].eutraCell. \
                              enbType == WR_ENODEB_TYPE_MACRO)
                        {
                           enbId = nghCellCfg->t.neighAddCfg[noOfLteNghCell].eutraCell.cid >> 8;
                        }
                        else
                        {
                           enbId = nghCellCfg->t.neighAddCfg[noOfLteNghCell].eutraCell.cid;
                        }

                        WR_GET_PEERID_FROM_ENBID(enbId, peerId);

                        if(peerId == 0)
                        {
                           WR_GET_X2AP_PEER_ID(peerId, enbId);
                           nghCellCfg->t.neighAddCfg[noOfLteNghCell].eutraCell. \
                              isNewNbrEnb = TRUE;
                        }
                        nghCellCfg->t.neighAddCfg[noOfLteNghCell].eutraCell. \
                           peerId = peerId;
#endif
                        nghCellCfg->t.neighAddCfg[noOfLteNghCell].eutraCell. \
                           earfcnDl = (U16)atoi((S8 *)paramLst[paramCnt++]);

                        nghCellCfg->t.neighAddCfg[noOfLteNghCell].eutraCell. \
                           earfcnUl = (U16)atoi((S8 *)paramLst[paramCnt++]);

                        /* nghCellCfg->isX2Enabled = 
                           (Bool)atoi((S8 *)paramLst[paramCnt++]);*/
                        nghCellCfg->t.neighAddCfg[noOfLteNghCell].eutraCell. \
                           isX2Reqd = (Bool)atoi((S8 *)paramLst[paramCnt++]);

                        /* CSG_DEV start */
                        nghCellCfg->t.neighAddCfg[noOfLteNghCell]. \
                           eutraCell.csgAccessMode = (U8)atoi((S8 *)paramLst[paramCnt++]);

                        nghCellCfg->t.neighAddCfg[noOfLteNghCell]. \
                           eutraCell.csgId = (U32)atoi((S8 *)paramLst[paramCnt++]);

                        /* CSG_DEV end */
                        nghCellCfg->t.neighAddCfg[noOfLteNghCell]. \
                           eutraCell.numAntenna = (Bool)atoi((S8 *)paramLst[paramCnt++]);

                        nghCellCfg->t.neighAddCfg[noOfLteNghCell]. \
                           eutraCell.ulDlSubFrameCfg = (Bool)atoi((S8 *)paramLst[paramCnt++]);

                        nghCellCfg->t.neighAddCfg[noOfLteNghCell]. \
                           eutraCell.splSfCfg = (Bool)atoi((S8 *)paramLst[paramCnt++]);

                        nghCellCfg->t.neighAddCfg[noOfLteNghCell]. \
                           eutraCell.cpDl = (Bool)atoi((S8 *)paramLst[paramCnt++]);

                        nghCellCfg->t.neighAddCfg[noOfLteNghCell]. \
                           eutraCell.cpUl = (Bool)atoi((S8 *)paramLst[paramCnt++]);

                        nghCellCfg->t.neighAddCfg[noOfLteNghCell]. \
                           eutraCell.rsrp = (Bool)atoi((S8 *)paramLst[paramCnt++]);

                        nghCellCfg->t.neighAddCfg[noOfLteNghCell]. \
                           eutraCell.rssi = (Bool)atoi((S8 *)paramLst[paramCnt++]);
                     }
                  }
               }
               else
               {
                  RLOG0(L_ERROR, "Error in WR_TAG_NGH_CELL_CFG tag format ");
               }
            }
            break;
         case WR_TAG_RRM_RNTI_STRT:
            {
               status     = TRUE;
               noOfParams = 0;
               noOfElem   = 0;

               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  if(noOfParams > wrSmDfltNumCells)
                  {
                     noOfParams = wrSmDfltNumCells;
                  }
                  for (loopCnt=0; loopCnt<noOfParams; loopCnt++)
                  {
                     lteeNodeBparams[loopCnt].lteSmCellCfg.rrmRntiStart = (U16)atoi((S8*)paramLst[loopCnt]);
                  }
               }
            }
            break;
         case WR_TAG_MAX_RRM_RNTIS:
            {
               status     = TRUE;
               noOfParams = 0;
               noOfElem   = 0;

               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  if(noOfParams > wrSmDfltNumCells)
                  {
                     noOfParams = wrSmDfltNumCells;
                  }
                  for (loopCnt=0; loopCnt<noOfParams; loopCnt++)
                  {
                     lteeNodeBparams[loopCnt].lteSmCellCfg.maxRrmRntis = (U16)atoi((S8*)paramLst[loopCnt]);
                  }
               }
            }
            break;
         case WR_TAG_MAC_RNTI_STRT:
            {
               status     = TRUE;
               noOfParams = 0;
               noOfElem   = 0;

               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  if(noOfParams > wrSmDfltNumCells)
                  {
                     noOfParams = wrSmDfltNumCells;
                  }
                  for (loopCnt=0; loopCnt<noOfParams; loopCnt++)
                  {
                     lteeNodeBparams[loopCnt].lteSmCellCfg.macRntiStart = (U16)atoi((S8*)paramLst[loopCnt]);
                  }
               }
            }
            break;
         case WR_TAG_MAX_MAC_RNTIS:
            {
               status     = TRUE;
               noOfParams = 0;
               noOfElem   = 0;

               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  if(noOfParams > wrSmDfltNumCells)
                  {
                     noOfParams = wrSmDfltNumCells;
                  }
                  for (loopCnt=0; loopCnt<noOfParams; loopCnt++)
                  {
                     lteeNodeBparams[loopCnt].lteSmCellCfg.maxMacRntis = (U16)atoi((S8*)paramLst[loopCnt]);
                  }
               }
            }
            break;
         case WR_TAG_RRM_NO_OF_DED_PREMBL:
            {
               status     = TRUE;
               noOfParams = 0;
               noOfElem   = 0;

               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  if(noOfParams > wrSmDfltNumCells)
                  {
                     noOfParams = wrSmDfltNumCells;
                  }
                  for (loopCnt=0; loopCnt<noOfParams; loopCnt++)
                  {
                     lteeNodeBparams[loopCnt].lteSmCellCfg.maxRrmPrmbls = (U16)atoi((S8*)paramLst[loopCnt]);
                  }
               }
            }
            break;
         case WR_TAG_RRM_DED_PREMBL_STRT:
            {
               status     = TRUE;
               noOfParams = 0;
               noOfElem   = 0;

               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  if(noOfParams > wrSmDfltNumCells)
                  {
                     noOfParams = wrSmDfltNumCells;
                  }
                  for (loopCnt=0; loopCnt<noOfParams; loopCnt++)
                  {
                     lteeNodeBparams[loopCnt].lteSmCellCfg.rrmPrmblStart = (U16)atoi((S8*)paramLst[loopCnt]);
                  }
               }
            }
            break;
         case WR_TAG_MAC_NO_OF_PREMBL:
            {
               status     = TRUE;
               noOfParams = 0;
               noOfElem   = 0;

               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  if(noOfParams > wrSmDfltNumCells)
                  {
                     noOfParams = wrSmDfltNumCells;
                  }
                  for (loopCnt=0; loopCnt<noOfParams; loopCnt++)
                  {
                     lteeNodeBparams[loopCnt].lteSmCellCfg.numOfMacPrm = (U8)atoi((S8*)paramLst[loopCnt]);
                  }
               }
            }
            break;
            /* ccpu00124317 */
            /* start */
         case WR_TAG_A1_RSRP_THRSHLD_VAL:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measA1EvtRptCfg[0].threshold_RSRP = atoi((S8 *)tagVal);
               }
            }
            break;
            /*rsrq_ho*/
         case WR_TAG_A2_RSRP_THRSHLD_VAL:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measA2EvtRptCfg[0].threshold_RSRP = atoi((S8 *)tagVal);
               }
            }
            break;
//suhas_sprint12
#ifdef LTE_ADV
         case WR_TAG_A4_RSRP_THRSHLD_VAL:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measA4EvtRptCfg[MSM_MEAS_EVENTA4_SCELL_ADD].threshold_RSRP = atoi((S8 *)tagVal);
               }
            }
            break;
#endif
//suhas_sprint12
         case WR_TAG_INTRA_A5_RSRP_THRSD1_VAL:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measEvtA5Cfg[MSM_MEAS_EVENTA5_INTRA_FREQ_HO].\
                     threshold1_RSRP = atoi((S8 *)tagVal);
               }
            }
            break;
         case WR_TAG_INTRA_A5_RSRP_THRSD2_VAL:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp. \
                     measEvtA5Cfg[MSM_MEAS_EVENTA5_INTRA_FREQ_HO].threshold2_RSRP = atoi((S8 *)tagVal);
               }
            }
            break;
         case WR_TAG_INTER_A5_RSRP_THRSD1_VAL:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measEvtA5Cfg[MSM_MEAS_EVENTA5_INTER_FREQ_HO_RSRP]. \
                     threshold1_RSRP = atoi((S8 *)tagVal);
               }
            }
            break;
         case WR_TAG_UTRA_B2_RSRP_THRSD1_VAL:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measUtraEventB2RptCfg[WR_MEAS_UTRA_EVENTB2_HO]. \
                     b2Threshold1RSRQ = atoi((S8 *)tagVal);
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measUtraEventB2RptCfg[WR_MEAS_UTRA_EVENTB2_REDIR].\
                     b2Threshold1RSRP= atoi((S8 *)tagVal);
               }
            }
            break;
         case WR_TAG_GERAN_B2_RED_RSRP_THRSD1_VAL:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.\
                            measGeranEventB2RptCfg[WR_MEAS_GERAN_EVENTB2_INTER_RAT_REDIR].\
                                   b2Threshold1RSRP = (U8)atoi((S8 *)tagVal);
               }
            }
            break;
         case WR_TAG_GERAN_B2_HO_RSRP_THRSD1_VAL:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.\
                            measGeranEventB2RptCfg[WR_MEAS_GERAN_EVENTB2_INTER_RAT_HO].\
                                   b2Threshold1RSRP = (U8)atoi((S8 *)tagVal);
               }
            }
            break;
         case WR_TAG_GERAN_B2_RED_THRSD2_VAL:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.\
                            measGeranEventB2RptCfg[WR_MEAS_GERAN_EVENTB2_INTER_RAT_REDIR].\
                                   b2Threshold2Geran = (U8)atoi((S8 *)tagVal);
               }
            }
            break;
         case WR_TAG_GERAN_B2_HO_THRSD2_VAL:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.\
                            measGeranEventB2RptCfg[WR_MEAS_GERAN_EVENTB2_INTER_RAT_HO].\
                                   b2Threshold2Geran = (U8)atoi((S8 *)tagVal);
               }
            }
            break;
         case WR_TAG_UTRA_FDD_B2_RSCP_THRSD2_VAL:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measUtraEventB2RptCfg[WR_MEAS_UTRA_EVENTB2_HO]. \
                     b2Threshold2UtraRSCP = atoi((S8 *)tagVal);
               }
            }
            break;
         case WR_TAG_UTRA_TDD_B2_RSCP_THRSD2_VAL:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  wrSmDfltUtraTddB2ThresRSCP = atoi((S8 *)tagVal);
               }
            }
            break;
         case WR_TAG_INTER_A5_RSRP_THRSD2_VAL:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measEvtA5Cfg[MSM_MEAS_EVENTA5_INTER_FREQ_HO_RSRP]. \
                     threshold2_RSRP = atoi((S8 *)tagVal);
               }
            }
            break;
         case WR_TAG_INTRA_HO_A3_OFFSET:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measEvtA3Cfg[MSM_MEAS_EVENTA3_INTRA_FREQ_HO]. \
                     offset = atoi((S8*)tagVal);
               }
            }
            break;
         case WR_TAG_INTRA_ANR_A3_OFFSET:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measEvtA3Cfg[MSM_MEAS_EVENTA3_INTRA_FREQ_ANR].offset \
                     = atoi((S8*)tagVal);
               }
            }
            break;
         case WR_TAG_INTER_ANR_A5_RSRP_THRSD1_VAL:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measEvtA5Cfg[MSM_MEAS_EVENTA5_INTER_FREQ_ANR]. \
                     threshold1_RSRP = atoi((S8*)tagVal);
               }
            }
            break;
         case WR_TAG_INTER_ANR_A5_RSRP_THRSD2_VAL:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measEvtA5Cfg[MSM_MEAS_EVENTA5_INTER_FREQ_ANR]. \
                     threshold2_RSRP = atoi((S8*)tagVal);
               }
            }
            break;
         case WR_TAG_ANR_EPOC_TMR_VAL_IN_SECS:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteFapControlParams.anrEpochPeriod = atoi((S8*)tagVal);
               }
            }
            break;
         case WR_TAG_ANR_TRICE_INTV_COUNT:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteFapControlParams.anrTricePeriod = atoi((S8*)tagVal);
               }
            }
            break;
         case  WR_TAG_ANR_REPORT_CFG_VAL:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.anrRptCfg = atoi((S8*)tagVal);
               }
            }
            break;
         case  WR_TAG_ANR_CELL_VALID_AGE_VAL:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteFapControlParams.anrCellValidAge = atoi((S8*)tagVal);
               }
            }
            break;
         case  WR_TAG_HO_REPORT_CFG_VAL:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.hoRptCfg = atoi((S8*)tagVal);
               }
            }
            break;
         case WR_TAG_RSRQ_THRSHLD_VAL:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  wrSmDfltThresRSRQ = atoi((S8 *)tagVal);
               }
            }
            break;
            /*ccpu00130010*/
         case WR_TAG_S_MEASURE_VAL:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measSpeedCfg.sMeasure = atoi((S8*)tagVal);
               }
            }
            break;
         case WR_TAG_INTRA_TTT_VAL:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  wrSmDfltTimeToTrig = atoi((S8*)tagVal);
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measA1EvtRptCfg[0].timeToTrigger =  atoi((S8*)tagVal); 
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measA2EvtRptCfg[0].timeToTrigger =  atoi((S8*)tagVal); 
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measEvtA3Cfg[MSM_MEAS_EVENTA3_INTRA_FREQ_HO]. \
                     timeToTrigger =  atoi((S8*)tagVal); 
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measEvtA3Cfg[MSM_MEAS_EVENTA3_INTER_FREQ_HO_RSRP]. \
                     timeToTrigger = atoi((S8*)tagVal);
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measEvtA3Cfg[MSM_MEAS_EVENTA3_INTRA_FREQ_ANR]. \
                     timeToTrigger = atoi((S8*)tagVal);
//suhas_sprint12
#ifdef LTE_ADV
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measA4EvtRptCfg[MSM_MEAS_EVENTA4_SCELL_ADD].timeToTrigger =  atoi((S8*)tagVal); 
#endif
//suhas_sprint12
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measEvtA5Cfg[MSM_MEAS_EVENTA5_INTRA_FREQ_HO]. \
                     timeToTrigger = atoi((S8*)tagVal);
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measEvtA5Cfg[MSM_MEAS_EVENTA5_INTER_FREQ_HO_RSRP]. \
                     timeToTrigger = atoi((S8*)tagVal);
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measEvtA5Cfg[MSM_MEAS_EVENTA5_INTER_FREQ_ANR]. \
                     timeToTrigger = atoi((S8*)tagVal);
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measUtraEventB2RptCfg[WR_MEAS_UTRA_EVENTB2_HO]. \
                     timeToTrigger = atoi((S8*)tagVal);
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measUtraEventB2RptCfg[WR_MEAS_UTRA_EVENTB2_REDIR]. \
                     timeToTrigger = atoi((S8*)tagVal);
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.\
                            measGeranEventB2RptCfg[WR_MEAS_GERAN_EVENTB2_INTER_RAT_REDIR].timeToTrigger = \
                                 atoi((S8*)tagVal);
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.\
                            measGeranEventB2RptCfg[WR_MEAS_GERAN_EVENTB2_INTER_RAT_HO].timeToTrigger = \
                                 atoi((S8*)tagVal);
               }
            }
            break;
         case WR_TAG_INTRA_HYTERISIS:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  wrSmDfltHysteresis = atoi((S8*)tagVal);
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measA1EvtRptCfg[0].hysteresis = atoi((S8*)tagVal);
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measA2EvtRptCfg[0].hysteresis = atoi((S8*)tagVal);
//suhas_sprint12
#ifdef LTE_ADV
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measA4EvtRptCfg[MSM_MEAS_EVENTA4_SCELL_ADD].hysteresis = atoi((S8*)tagVal);
#endif
//suhas_sprint12

                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measEvtA3Cfg[MSM_MEAS_EVENTA3_INTRA_FREQ_HO]. \
                     hysteresis = atoi((S8*)tagVal);
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measEvtA3Cfg[MSM_MEAS_EVENTA3_INTER_FREQ_HO_RSRP]. \
                     hysteresis = atoi((S8*)tagVal);
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measEvtA3Cfg[MSM_MEAS_EVENTA3_INTRA_FREQ_ANR]. \
                     hysteresis = atoi((S8*)tagVal);
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measEvtA5Cfg[MSM_MEAS_EVENTA5_INTRA_FREQ_HO]. \
                     hysteresis = atoi((S8*)tagVal);
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measEvtA5Cfg[MSM_MEAS_EVENTA5_INTER_FREQ_HO_RSRP]. \
                     hysteresis = atoi((S8*)tagVal);
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measEvtA5Cfg[MSM_MEAS_EVENTA5_INTER_FREQ_ANR]. \
                     hysteresis = atoi((S8*)tagVal);
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measUtraEventB2RptCfg[WR_MEAS_UTRA_EVENTB2_HO]. \
                     hysteresis = atoi((S8*)tagVal);
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measUtraEventB2RptCfg[WR_MEAS_UTRA_EVENTB2_REDIR]. \
                     hysteresis = atoi((S8*)tagVal);
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp. \
                     measGeranEventB2RptCfg[WR_MEAS_GERAN_EVENTB2_INTER_RAT_REDIR].hysteresis = \
                     atoi((S8*)tagVal);
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp. \
                     measGeranEventB2RptCfg[WR_MEAS_GERAN_EVENTB2_INTER_RAT_HO].hysteresis = \
                     atoi((S8*)tagVal);
               }
            }
            /*ccpu00130010*/
            break;
         case WR_TAG_PCI_VAL:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  status     = TRUE;
                  noOfParams = 0;
                  noOfElem   = 0;

                  wrCfgValdtInput(tagVal, &status, &noOfElem);
                  if (TRUE == status)
                  {
                     wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                     if(noOfParams > wrSmDfltNumCells)
                     {
                        noOfParams = wrSmDfltNumCells;
                     }
                     lteeNodeBparams[loopCnt].lteRemScanParameters.pci =  atoi((S8 *)paramLst[loopCnt]);
                     lteeNodeBparams[loopCnt].lteAddCellCfg.physCellId = atoi((S8 *)paramLst[loopCnt]); 
                  }
               }
               /*SON will do PCI validation and select a valid PCI, henece no need to validate PCI here*/
            }
            break;
         case WR_TAG_DL_NUM_UE_PER_TTI:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  wrSmDfltMaxUePerDlSf = (U8)atoi((S8 *)tagVal); 
                  lteeNodeBparams[loopCnt].lteCellDlSchdCfgGrp.maxUePerDlSf = \
                                                                     (U8)atoi((S8 *)tagVal); 
                  WR_SMM_VALIDATE_CFG_PARAM(lteeNodeBparams[loopCnt].lteCellDlSchdCfgGrp. \
                        maxUePerDlSf, 1, 4);
               }
            }
            break;
         case WR_TAG_UL_NUM_UE_PER_TTI:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellUlSchdCfgGrp.maxUePerUlSf = \
                                                                     (U8)atoi((S8 *)tagVal); 
                  WR_SMM_VALIDATE_CFG_PARAM(lteeNodeBparams[loopCnt].lteCellUlSchdCfgGrp. \
                        maxUePerUlSf, 1, 4);
               }
            }
            break;
         case WR_TAG_MAX_DL_UE_PER_TTI:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellDlSchdCfgGrp.maxDlUeNewTxPerTti = (U8)atoi((S8 *)tagVal);
                  WR_SMM_VALIDATE_CFG_PARAM(lteeNodeBparams[loopCnt].lteCellDlSchdCfgGrp.maxDlUeNewTxPerTti, 1, 4);
               }
            }
            break;
         case WR_TAG_MAX_UL_UE_PER_TTI:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellUlSchdCfgGrp.maxUlUeNewTxPerTti = (U8)atoi((S8 *)tagVal);
                  WR_SMM_VALIDATE_CFG_PARAM(lteeNodeBparams[loopCnt].lteCellUlSchdCfgGrp.maxUlUeNewTxPerTti, 1, 4);
               }
            }
            break;
         case WR_TAG_DL_SCHD_TYPE:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellDlSchdCfgGrp.dlSchedulingAlg = (U8)atoi((S8 *)tagVal);
                  WR_SMM_VALIDATE_CFG_PARAM(lteeNodeBparams[loopCnt].lteCellDlSchdCfgGrp.dlSchedulingAlg, 1, 2);
               }
            }
            break;
         case WR_TAG_UL_SCHD_TYPE:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellUlSchdCfgGrp.ulSchedulingAlg = (U8)atoi((S8 *)tagVal);
                  WR_SMM_VALIDATE_CFG_PARAM(lteeNodeBparams[loopCnt].lteCellUlSchdCfgGrp.ulSchedulingAlg, 1, 2);
               }
            }
            break;
         case WR_TAG_DLFS_SCHD_TYPE:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellDlSchdCfgGrp.dlfsSchd = (U8)atoi((S8 *)tagVal);
                  if(lteeNodeBparams[loopCnt].lteCellDlSchdCfgGrp.dlfsSchd > 1)
                  {
                     fprintf(stderr, "Invalid parameter value wrSmDfltDLFSSchdTyp = %d,\
                           it should not be more than 1 \n", 
                           lteeNodeBparams[loopCnt].lteCellDlSchdCfgGrp.dlfsSchd);
                     RETVALUE(RFAILED);\
                  }   
               }   
            }
            break;
         case WR_TAG_PFS_DL_TPT_COEFFICIENT:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  if ((atol((S8*)tagVal)) > 10)
                  {
                     fprintf(stderr, "Invalid parameter, auto config value should not be more than 1 \n");
                     RETVALUE(RFAILED);
                  }
                  lteeNodeBparams[loopCnt].lteCellDlSchdCfgGrp.pfsDlTptCoefficient = (U8)atoi((S8 *)tagVal); 
               }
            }
            break;
         case WR_TAG_PFS_DL_FAIRNESS_COEFFICIENT:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  if ((atol((S8*)tagVal)) > 10)
                  {
                     fprintf(stderr, "Invalid parameter, auto config value should not be more than 1 \n");
                     RETVALUE(RFAILED);
                  }
                  lteeNodeBparams[loopCnt].lteCellDlSchdCfgGrp.pfsDlFairCoefficient = (U8)atoi((S8 *)tagVal); 
               }
            }
            break;
         case WR_TAG_PFS_UL_TPT_COEFFICIENT:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  if ((atol((S8*)tagVal)) > 10)
                  {
                     fprintf(stderr, "Invalid parameter, auto config value should not be more than 1 \n");
                     RETVALUE(RFAILED);
                  }
                  lteeNodeBparams[loopCnt].lteCellUlSchdCfgGrp.pfsUlTptCoefficient = (U8)atoi((S8 *)tagVal); 
               }
            }
            break;
         case WR_TAG_PFS_UL_FAIRNESS_COEFFICIENT:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  if ((atol((S8*)tagVal)) > 10)
                  {
                     fprintf(stderr, "Invalid parameter, auto config value should not be more than 1 \n");
                     RETVALUE(RFAILED);
                  }
                  lteeNodeBparams[loopCnt].lteCellUlSchdCfgGrp.pfsUlFairCoefficient = (U8)atoi((S8 *)tagVal); 
               }
            }
            break;
         case WR_TAG_TM_AUTO_CONFIG:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  if ((atol((S8*)tagVal)) > 1)
                  {
                     fprintf(stderr, "Invalid parameter, auto config value should not be more than 1 \n");\
                        RETVALUE(RFAILED);\
                  }
                  lteeNodeBparams[loopCnt].lteTransModeCellCfg.bIsAutoConfigEnabled
                     = ((atol((S8*)tagVal)) == 1) ? TRUE : FALSE;
               }
            }
            break;
         case WR_TAG_PREFERRED_TM:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteTransModeCellCfg.preferredTransMode = (U8)atoi((S8 *)tagVal);
                  if(lteeNodeBparams[loopCnt].lteTransModeCellCfg.preferredTransMode < 1 || 
                        lteeNodeBparams[loopCnt].lteTransModeCellCfg.preferredTransMode > 4)
                  {
                     fprintf(stderr, "Invalid parameter value wrSmDfltPreferredTm = %d, it should be among 2,3,4 \n", \
                           wrSmDfltPreferredTm);\
                        RETVALUE(RFAILED);\
                  }
                  if(1 == lteeNodeBparams[loopCnt].lteTransModeCellCfg.bIsAutoConfigEnabled)
                  {
                     lteeNodeBparams[loopCnt].lteTransModeCellCfg.transModeUse = 4;
                  }
                  else
                  {
                     lteeNodeBparams[loopCnt].lteTransModeCellCfg.transModeUse =
                        lteeNodeBparams[loopCnt].lteTransModeCellCfg.preferredTransMode;
                  }
               }
            }
            break;
         case WR_TAG_MAX_X2_PEERS:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteSmCellCfg.maxX2Peers = atoi((S8 *)tagVal);
               }
            }
            break;
         case WR_TAG_OP_MODE:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteMsCellCfgReq.opMode = atoi((S8 *)tagVal);
               }
            }
            break;
         case WR_TAG_PERIOD:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteMsCellCfgReq.period = (U32)atoi((S8 *)tagVal);
               }
            }
            break;
         case WR_TAG_DL_EARFCN:
            {
               status     = TRUE;
               noOfParams = 0;
               noOfElem   = 0;

               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  if(noOfParams > wrSmDfltNumCells)
                  {
                     noOfParams = wrSmDfltNumCells;
                  }
                  for (loopCnt=0; loopCnt<noOfParams; loopCnt++)
                  {
                     lteeNodeBparams[loopCnt].lteAddCellCfg.earfdnDl = (U16)atoi((S8 *)paramLst[loopCnt]);
                  }
               }
               break;
            }
         case WR_TAG_UL_EARFCN:
            {
               status     = TRUE;
               noOfParams = 0;
               noOfElem   = 0;

               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  if(noOfParams > wrSmDfltNumCells)
                  {
                     noOfParams = wrSmDfltNumCells;
                  }
                  for (loopCnt=0; loopCnt<noOfParams; loopCnt++)
                  {
                     lteeNodeBparams[loopCnt].lteULFrequencyInfo.eARFCN = (U16)atoi((S8 *)paramLst[loopCnt]);
                     lteeNodeBparams[loopCnt].lteAddCellCfg.earfdnUl = (U16)atoi((S8 *)paramLst[loopCnt]);
                  }
               }
               break;
            }
#ifdef OAM_PH0_SUPPORT
         case WR_TAG_S1_RESET_TMR:
            {
               smCfgCb.s1ResetTmr = atoi((S8 *)tagVal);
            }
            break;
         case WR_TAG_X2_RESET_TMR:
            {
               smCfgCb.x2ResetTmr = atoi((S8 *)tagVal);
            }
            break;
#endif
#ifdef TENB_AS_SECURITY
         case WR_TAG_AS_PRI_INTG_ALGO_LST:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  /*reset default values when an entry is present in config file*/
                  for(loopCntTmp = 0; loopCntTmp < WR_MAX_AS_SEC_ALGOS; loopCntTmp++)
                  {
                     wreNodBPriIntgAlgo[loopCntTmp].pres = FALSE;
                  }
                  status = TRUE;
                  noOfElem = 0;
                  noOfParams = 0;
                  wrCfgValdtInput(tagVal, &status, &noOfElem);
                  if (TRUE == status)
                  {
                     wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                     if(noOfElem == 0 || noOfElem > WR_MAX_AS_SEC_ALGOS)
                     {
                        fprintf(stderr, "Number of parameters in WR_TAG_AS_PRI_INTG_ALGO_LST invalid");
                        RETVALUE(RFAILED);
                     }
                     paramCnt = 0;
                     for(loopCntTmp = 0; loopCntTmp < noOfElem; loopCntTmp++)
                     {
                        wreNodBPriIntgAlgo[loopCntTmp].val = atoi((S8*)paramLst[paramCnt]);
                        lteeNodeBparams[loopCnt].lteSmCellCfg.genUeCfg.intgAlgo[loopCntTmp] = atoi((S8*)paramLst[paramCnt++]);
                        if(lteeNodeBparams[loopCnt].lteSmCellCfg.genUeCfg.intgAlgo[loopCntTmp] > \
                              (WR_MAX_AS_SEC_ALGOS - 1) || lteeNodeBparams[loopCnt].lteSmCellCfg.genUeCfg. \
                              intgAlgo[loopCntTmp] < 0)
                        {
                           fprintf(stderr, "Invalid values in WR_TAG_AS_PRI_INTG_ALGO_LST");
                           RETVALUE(RFAILED);
                        }
                        wreNodBPriIntgAlgo[loopCntTmp].pres = TRUE;
                     }
                  }
                  else
                  {
                     fprintf(stderr, "Error in WR_TAG_AS_PRI_INTG_ALGO_LST tag format");
                     RETVALUE(RFAILED);
                  }
               }
            }
            break;
         case WR_TAG_AS_PRI_CIPH_ALGO_LST:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  /*reset default values when an entry is present in config file*/
                  for(loopCntTmp = 0; loopCntTmp < WR_MAX_AS_SEC_ALGOS; loopCntTmp++)
                  {
                     wreNodBPriCiphAlgo[loopCntTmp].pres = FALSE;
                  }
                  status = TRUE;
                  noOfElem = 0;
                  noOfParams = 0;
                  wrCfgValdtInput(tagVal, &status, &noOfElem);
                  if (TRUE == status)
                  {
                     wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                     if(noOfElem == 0 || noOfElem > WR_MAX_AS_SEC_ALGOS)
                     {
                        fprintf(stderr, "Number of parameters in WR_TAG_AS_PRI_CIPH_ALGO_LST: invalid");
                        RETVALUE(RFAILED);
                     }
                     paramCnt = 0;
                     for(loopCntTmp = 0; loopCntTmp < noOfElem; loopCntTmp++)
                     {
                        wreNodBPriCiphAlgo[loopCntTmp].val = atoi((S8*)paramLst[paramCnt]);
                        lteeNodeBparams[loopCnt].lteSmCellCfg.genUeCfg.ciphAlgo[loopCntTmp] = 
                           atoi((S8*)paramLst[paramCnt++]);
                        if(lteeNodeBparams[loopCnt].lteSmCellCfg.genUeCfg.ciphAlgo[loopCntTmp] \
                              > (WR_MAX_AS_SEC_ALGOS - 1) || lteeNodeBparams[loopCnt].\
                              lteSmCellCfg.genUeCfg.ciphAlgo[loopCntTmp] < 0)
                        {
                           fprintf(stderr, "Invalid values in WR_TAG_AS_PRI_CIPH_ALGO_LST");
                           RETVALUE(RFAILED);
                        }

                        wreNodBPriCiphAlgo[loopCntTmp].pres = TRUE;
                     }
                  }
                  else
                  {
                     //RLOG0(L_ERROR, "Error in WR_TAG_AS_PRI_CIPH_ALGO_LST: tag format");
                     RETVALUE(RFAILED);
                  }
               }
            }
            break;
#endif
         case WR_TAG_DIAG_TUCL:
            {
               status = TRUE;
               noOfElem = 0;
               noOfParams = 0;
               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  for (loopCnt = 0; loopCnt < noOfElem; loopCnt++)
                  {
                     smCfgCb.diagInfo.tucl.diagState = (Bool)atoi((S8 *)paramLst[loopCnt++]);
                     smCfgCb.diagInfo.tucl.diagLvl = atoi((S8 *)paramLst[loopCnt++]);
                  }
               }
               else
               {
                  ALARM("Wrong WR_TAG_DIAG_TUCL tag format\n");
               }
            }
            break;
         case WR_TAG_DIAG_S1AP:
            {
               status = TRUE;
               noOfElem = 0;
               noOfParams = 0;
               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  for (loopCnt = 0; loopCnt < noOfElem; loopCnt++)
                  {
                     smCfgCb.diagInfo.s1ap.diagState = (Bool)atoi((S8 *)paramLst[loopCnt++]);
                     smCfgCb.diagInfo.s1ap.diagLvl = atoi((S8 *)paramLst[loopCnt++]);
                  }
               }
               else
               {
                  ALARM("Wrong WR_TAG_DIAG_S1AP tag format\n");
               }
            }           
            break;   
         case WR_TAG_DIAG_EGTP:
            {
               status = TRUE;
               noOfElem = 0;
               noOfParams = 0;
               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  for (loopCnt = 0; loopCnt < noOfElem; loopCnt++)
                  {
                     smCfgCb.diagInfo.egtp.diagState = (Bool)atoi((S8 *)paramLst[loopCnt++]);
                     smCfgCb.diagInfo.egtp.diagLvl = atoi((S8 *)paramLst[loopCnt++]);
                  }
               }
               else
               {
                  ALARM("Wrong WR_TAG_DIAG_EGTP tag format\n");
               }
            }
            break;   
         case WR_TAG_DIAG_APP:
            {
               status = TRUE;
               noOfElem = 0;
               noOfParams = 0;
               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  for (loopCnt = 0; loopCnt < noOfElem; loopCnt++)
                  {
                     smCfgCb.diagInfo.app.diagState = (Bool)atoi((S8 *)paramLst[loopCnt++]);
                     smCfgCb.diagInfo.app.diagLvl = atoi((S8 *)paramLst[loopCnt++]);
                  }
               }
               else
               {
                  ALARM("Wrong WR_TAG_DIAG_APP tag format\n");
               }
            }
            break;   
         case WR_TAG_DIAG_LTERRC:
            {
               status = TRUE;
               noOfElem = 0;
               noOfParams = 0;
               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  for (loopCnt = 0; loopCnt < noOfElem; loopCnt++)
                  {
                     smCfgCb.diagInfo.lteRrc.diagState = (Bool)atoi((S8 *)paramLst[loopCnt++]);
                     smCfgCb.diagInfo.lteRrc.diagLvl = atoi((S8 *)paramLst[loopCnt++]);
                  }
               }
               else
               {
                  ALARM("Wrong WR_TAG_DIAG_LTERRC tag format\n");
               }
            }
            break;   
         case WR_TAG_DIAG_LTERLC:
            {
               status = TRUE;
               noOfElem = 0;
               noOfParams = 0;
               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  for (loopCnt = 0; loopCnt < noOfElem; loopCnt++)
                  {
                     smCfgCb.diagInfo.lteRlc.diagState = (Bool)atoi((S8 *)paramLst[loopCnt++]);
                     smCfgCb.diagInfo.lteRlc.diagLvl = atoi((S8 *)paramLst[loopCnt++]);
                  }
               }
               else
               {
                  ALARM("Wrong WR_TAG_DIAG_LTERLC tag format\n");
               }
            }
            break;   
         case WR_TAG_DIAG_LTEPDCP:
            {
               status = TRUE;
               noOfElem = 0;
               noOfParams = 0;
               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  for (loopCnt = 0; loopCnt < noOfElem; loopCnt++)
                  {
                     smCfgCb.diagInfo.ltePdcp.diagState = (Bool)atoi((S8 *)paramLst[loopCnt++]);
                     smCfgCb.diagInfo.ltePdcp.diagLvl = atoi((S8 *)paramLst[loopCnt++]);
                  }
               }
               else
               {
                  ALARM("Wrong WR_TAG_DIAG_LTEPDCP tag format\n");
               }
            }
            break;   
         case WR_TAG_DIAG_LTECL:
            {
               status = TRUE;
               noOfElem = 0;
               noOfParams = 0;
               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  for (loopCnt = 0; loopCnt < noOfElem; loopCnt++)
                  {
                     smCfgCb.diagInfo.lteCl.diagState = (Bool)atoi((S8 *)paramLst[loopCnt++]);
                     smCfgCb.diagInfo.lteCl.diagLvl = atoi((S8 *)paramLst[loopCnt++]);
                  }
               }
               else
               {
                  ALARM("Wrong WR_TAG_DIAG_LTECL tag format\n");
               }
            }
            break;   
         case WR_TAG_DIAG_LTEMAC:
            {
               status = TRUE;
               noOfElem = 0;
               noOfParams = 0;
               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  for (loopCnt = 0; loopCnt < noOfElem; loopCnt++)
                  {
                     smCfgCb.diagInfo.lteMac.diagState = (Bool)atoi((S8 *)paramLst[loopCnt++]);
                     smCfgCb.diagInfo.lteMac.diagLvl = atoi((S8 *)paramLst[loopCnt++]);
                  }
               }
               else
               {
                  ALARM("Wrong WR_TAG_DIAG_LTEMAC tag format\n");
               }
            }
            break;   
         case WR_TAG_DIAG_X2AP:
            {
               status = TRUE;
               noOfElem = 0;
               noOfParams = 0;
               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  for (loopCnt = 0; loopCnt < noOfElem; loopCnt++)
                  {
                     smCfgCb.diagInfo.x2ap.diagState = (Bool)atoi((S8 *)paramLst[loopCnt++]);
                     smCfgCb.diagInfo.x2ap.diagLvl = atoi((S8 *)paramLst[loopCnt++]);
                  }
               }
               else
               {
                  ALARM("Wrong WR_TAG_DIAG_LTEX2AP tag format\n");
               }
            }
            break;   
         case WR_TAG_DIAG_SCTP:
            {
               status = TRUE;
               noOfElem = 0;
               noOfParams = 0;
               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  for (loopCnt = 0; loopCnt < noOfElem; loopCnt++)
                  {
                     smCfgCb.diagInfo.sctp.diagState = (Bool)atoi((S8 *)paramLst[loopCnt++]);
                     smCfgCb.diagInfo.sctp.diagLvl = atoi((S8 *)paramLst[loopCnt++]);
                  }
               }
               else
               {
                  ALARM("Wrong WR_TAG_DIAG_LTESCTP tag format\n");
               }
            }
            break;   
#ifdef PHY_ERROR_LOGING
         case  WR_TAG_UL_ENABLE_TIME:
            {    
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteUlAllocInfoCbParams. \
                     logTime = (U16)atoi((S8 *)tagVal);
               }
            }
            break;
#endif /* PHY_ERROR_LOGING */
            /* ccpu00126774 : Added the WR_TAG_DEFAULT_PAGING_CYCLE 
             * and WR_TAG_DEFAULT_PCCH_CFG_NB to read from config file */
         case WR_TAG_DEFAULT_PAGING_CYCLE: 
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].ltePCCHCfgCommon. \
                     defaultPagingCycle = atoi((S8 *)tagVal);
                  if( lteeNodeBparams[loopCnt].ltePCCHCfgCommon.defaultPagingCycle > \
                        WR_PCCHCONFLOGIC_DEFAULTPAGINGCYCLE_MAX )
                  {
                     lteeNodeBparams[loopCnt].ltePCCHCfgCommon.defaultPagingCycle = \
                                                                           WR_PCCHCONFLOGIC_DEFAULTPAGINGCYCLE_MIN;
                  }
               }
               break;
            }
         case WR_TAG_DEFAULT_PCCH_CFG_NB: 
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].ltePCCHCfgCommon.nB = atoi((S8 *)tagVal);
                  if(lteeNodeBparams[loopCnt].ltePCCHCfgCommon.nB > WR_PCCHCONFLOGIC_NB_MAX)
                  {
                     lteeNodeBparams[loopCnt].ltePCCHCfgCommon.nB = WR_PCCHCONFLOGIC_NB_MAX;
                  }
               } 
               break;
            }
         case  WR_TAG_SCTP_RTO_MIN:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteSctpCfgParams.rtoMin = (atoi((S8 *)(tagVal))/100);
               }
            }
            break;
         case  WR_TAG_SCTP_RTO_MAX:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteSctpCfgParams.rtoMax= (atoi((S8 *)(tagVal))/100);
               }
            }
            break;
         case  WR_TAG_SCTP_RTO_INITIAL:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteSctpCfgParams.rtoInitial= \
                                                               (atoi((S8 *)(tagVal))/100);
               }
            }
            break;
         case  WR_TAG_SCTP_HRTBEAT_INTERVAL:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteSctpCfgParams.heartBeatInterval= \
                                                                      (atoi((S8 *)(tagVal))/100);
               }
            }
            break;

            /*DRX QCI*/
         case  WR_TAG_DRX_QCI_SUPPORT_ENABLED:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteDrxCfgParams.isDRXQCIEnabled \
                     = atoi((S8*)tagVal);
                  if( lteeNodeBparams[loopCnt].lteDrxCfgParams.isDRXQCIEnabled == TRUE)
                  {
                     if(lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.anrRptCfg == FALSE \
                           && lteeNodeBparams[loopCnt].lteDrxCfgParams.isDrxEnabled ==FALSE)
                     {
                        lteeNodeBparams[loopCnt].lteDrxCfgParams.isDRXQCIEnabled = FALSE;	
                     }
                  }
               }
            }
            break;
            /*removed DRX flag*/ 
         case  WR_TAG_DRX_ENABLED:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteDrxCfgParams.isDrxEnabled = atoi((S8 *)tagVal);
               }  
            } 
            break;
         case  WR_TAG_DRX_INACTIVITY_TMR:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteDrxCfgParams.drxInactvTmr = atoi((S8 *)tagVal);
               }  
            } 
            break;
         case  WR_TAG_DRX_RETX_TMR:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteDrxCfgParams.drxRetxTmr = atoi((S8 *)tagVal);
               }  
            } 
            break;
         case WR_TAG_BANDWIDTH:
            {
               status = TRUE;
               noOfParams = 0;
               noOfElem = 0;
               U32 freqBandwidth[WR_MAX_CELLS]={0};

               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  if(noOfParams > wrSmDfltNumCells)
                  {
                     noOfParams = wrSmDfltNumCells;
                  }
                  for (loopCnt=0; loopCnt<noOfParams; loopCnt++)
                  {
                     freqBandwidth[loopCnt] = (U8)atoi((S8*)paramLst[loopCnt]);
                     wrSmmSetBandwidth(freqBandwidth[loopCnt],loopCnt);
                  }
               }
            }
            break;
         case WR_TAG_ANR_DRX_LONG_CYCLE:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteFapControlParams. \
                     anrDrxLongCycle= atoi((S8*)tagVal);
               }
            }
            break;
         case  WR_TAG_ANR_DRX_ON_DURATION_TMR:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteFapControlParams. \
                     anrDrxOnDurTmr= atoi((S8*)tagVal);
               }  
            } 
            break;
         case  WR_TAG_ANR_DRX_INACTIVITY_TMR:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteFapControlParams. \
                     anrDrxInactvTmr= atoi((S8*)tagVal);
               }  
            } 
            break;
#ifdef E_TM
         case WR_TAG_BOOT_MODE:
            {
               wrSmDfltBootMode = atoi((S8 *)tagVal);
            }
            break;
#endif            
#ifdef WR_WATCHDOG
         case  WR_TAG_WATCHDOG_SOFT_LIMIT:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].watchDogTmrCfg.softTimeout = atoi((S8 *)tagVal);
               }  
            } 
            break;  
         case  WR_TAG_WATCHDOG_HARD_LIMIT:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].watchDogTmrCfg.hardTimeout = atoi((S8 *)tagVal);
               }  
            } 
            break;
#endif
         case  WR_TAG_DRX_LONG_CYCLE_GBR:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteDrxCfgParams.drxLongCycleOffst. \
                     longDrxCycleGbr  = atoi((S8 *)tagVal);
               }  
            } 
            break;
         case  WR_TAG_DRX_LONG_CYCLE_NON_GBR:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteDrxCfgParams.drxLongCycleOffst. \
                     longDrxCycleNonGbr  = atoi((S8 *)tagVal);
               }  
            } 
            break;
            /* ccpu00128279 */
#ifdef LTE_TDD
         case WR_TAG_TDD_ULDL_CFG_MODE:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteTddParam.subframeAssignment =  atoi((S8*)tagVal);
               }
            }
            break;
         case WR_TAG_TDD_SPCL_SF_CONFIG:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteTddParam.specialSubFramePattern = atoi((S8*)tagVal);
               }
            }
            break;
#endif
         case WR_TAG_LOG_PATH:
            {
#ifndef WR_RSYS_OAM
                  if(strlen((S8*)tagVal) < WR_MAX_LOG_PATH_VALUE)
                  {
                     strcpy((S8*)logPath,(S8 *)tagVal);
                  }
                  else
                  {
                     ALARM("WR_TAG_LOG_PATH tag value is greater than \
                           WR_MAX_LOG_PATH_VALUE ,taking default log path:/var/log/\n");
                     strcpy((S8*)logPath,"/var/log/");
                  }

               rlSetLogPath((const char*)logPath);
#endif
            }
            break;   
         case WR_TAG_LOG_MASK:
            {
               char* token = strtok((S8*)tagVal, ",");
               while( token) {
                  rlSetModuleMask((U32)atoi((S8*)token));
                  token = strtok(NULL, ",");
               }
            }
            break;

         case WR_TAG_LOG_FILE:
#ifndef WR_RSYS_OAM
            rlSetLogFile((S8 *)tagVal);
#endif

            break;        

         case WR_TAG_LOG_MAX_FILES:
            rlSetNumOfLogFiles(atoi((S8*)tagVal));
            break;        

         case WR_TAG_LOG_FILESIZE_LIMIT: 
            rlSetLogFileSizeLimit(atol((S8*)tagVal));
            break;        

         case WR_TAG_LOG_LEVEL:
            wrSmDfltRlLogLvl = atoi((S8*)tagVal);
            break;        

         case WR_TAG_LOG_PORT: 
            rlSetLogPort(atoi((S8*)tagVal));
            break;        

         case WR_TAG_LOG_REMOTE_LOGGING:
            rlSetRemoteLoggingFlag(atoi((S8*)tagVal));
            break;

         case WR_TAG_LOG_CIRBUF_SIZE:
            rlSetCircularBufferSize(atol((S8*)tagVal));
            break;

         case WR_TAG_LOG_COREDUMP_FLAG:
            rlEnableDisableCore(atoi((S8*)tagVal));
            break;
         case WR_TAG_INT_FREQ_MEAS_GAP:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measGap. \
                     gapPatternForInterFA = atoi((S8*)tagVal);
               }
            }
            break;
         case WR_TAG_ANR_MEAS_GAP_CONFIG:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.measGap. \
                     gapPatternForANR = atoi((S8*)tagVal);
               }
            }
            break;
         case WR_TAG_RRM_SR_PRDCTY:
            {
               status     = TRUE;
               noOfParams = 0;
               noOfElem   = 0;

               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  if(noOfParams > wrSmDfltNumCells)
                  {
                     noOfParams = wrSmDfltNumCells;
                  }
                  for (loopCnt=0; loopCnt<noOfParams; loopCnt++)
                  {
                     lteeNodeBparams[loopCnt].lteRrmTddParam.srPrdcty \
                        = atoi((S8*)paramLst[loopCnt]);
                  }
               }
            }
            break;
         case WR_TAG_RRM_CQI_PRDCTY:
            {
               status     = TRUE;
               noOfParams = 0;
               noOfElem   = 0;

               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  if(noOfParams > wrSmDfltNumCells)
                  {
                     noOfParams = wrSmDfltNumCells;
                  }
                  for (loopCnt=0; loopCnt<noOfParams; loopCnt++)
                  {
                     lteeNodeBparams[loopCnt].lteRrmTddParam.cqiPrdcty \
                        = atoi((S8*)paramLst[loopCnt]);
                  }
               }
            }
            break;
         case WR_TAG_RRM_NUM_SR_PER_TTI:
            {
               status     = TRUE;
               noOfParams = 0;
               noOfElem   = 0;

               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  if(noOfParams > wrSmDfltNumCells)
                  {
                     noOfParams = wrSmDfltNumCells;
                  }
                  for (loopCnt=0; loopCnt<noOfParams; loopCnt++)
                  {
                     lteeNodeBparams[loopCnt].lteRrmTddParam.numSrPerTti \
                        = atoi((S8*)paramLst[loopCnt]);
                  }
               }
            }
            break;
         case WR_TAG_RRM_NUM_CQI_PER_TTI:
            {
               status     = TRUE;
               noOfParams = 0;
               noOfElem   = 0;

               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  if(noOfParams > wrSmDfltNumCells)
                  {
                     noOfParams = wrSmDfltNumCells;
                  }
                  for (loopCnt=0; loopCnt<noOfParams; loopCnt++)
                  {
                     lteeNodeBparams[loopCnt].lteRrmTddParam.numCqiPerTti \
                        = atoi((S8*)paramLst[loopCnt]);
                  }
               }
            }
            break;
         case WR_TAG_RRM_N1_PUCCH:
            {
               status     = TRUE;
               noOfParams = 0;
               noOfElem   = 0;

               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  if(noOfParams > wrSmDfltNumCells)
                  {
                     noOfParams = wrSmDfltNumCells;
                  }
                  for (loopCnt=0; loopCnt<noOfParams; loopCnt++)
                  {
                     lteeNodeBparams[loopCnt].ltePucchCfgCommon.n1PucchAn \
                        = atoi((S8*)paramLst[loopCnt]);
                  }
               }
            }
            break;
         case WR_TAG_PWS_ETWS_CMAS_CNTRL:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteEnbProtoCfg.pwsEtwsCmas = atoi((S8*)tagVal);
                  if(lteeNodeBparams[loopCnt].lteEnbProtoCfg.pwsEtwsCmas > 2)
                  {
                     fprintf(stderr, "Invalid value enetered to enable ETWS or CMAS\n");
                     fprintf(stderr, "Disabling PWS in the System\n");
                  }
               }
            }
            break;
            /* SPS changes starts */
         case WR_TAG_SPS_ENABLE_FLAG:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  if ((atol((S8*)tagVal)) == 1)
                  {
                     lteeNodeBparams[loopCnt].stSpsCellCfg.bIsSpsEnabled = TRUE;
                  }
               }
            }
            break;

         case WR_TAG_DL_NUM_SPS_UE_PER_TTI:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  if (((atol((S8*)tagVal)) > 0) && ((atol((S8*)tagVal)) <= \
                           lteeNodeBparams[loopCnt].lteCellDlSchdCfgGrp.maxUePerDlSf))
                  {
                     lteeNodeBparams[loopCnt].stSpsCellCfg.maxDlSpsUePerTti = (U16)atol((S8*)tagVal);
                  }
               }
            }
            break;

         case WR_TAG_UL_NUM_SPS_UE_PER_TTI:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  if (((atol((S8*)tagVal)) > 0) && ((atol((S8*)tagVal)) <= \
                           lteeNodeBparams[loopCnt].lteCellUlSchdCfgGrp.maxUePerUlSf))
                  {
                     lteeNodeBparams[loopCnt].stSpsCellCfg.maxUlSpsUePerTti = \
                                                                     (U16)atol((S8*)tagVal);
                  }
               }
            }
            break;
         case WR_TAG_MAX_SPS_RB:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  U32  dlCellBw = 0;
                  dlCellBw = wrSmDlCellBwInRbs(lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteCellMibCfgGrp.dlBw[0]);
                  lteeNodeBparams[loopCnt].stSpsCellCfg.maxDlBwInRbs = (U32)atol((S8*)tagVal);
                  if (( lteeNodeBparams[loopCnt].stSpsCellCfg.maxDlBwInRbs <= 0) || \
                        ( lteeNodeBparams[loopCnt].stSpsCellCfg.maxDlBwInRbs > dlCellBw))
                  {
                     /* default value is taken as 50% of the cell bandwidth */
                     lteeNodeBparams[loopCnt].stSpsCellCfg.maxDlBwInRbs = \
                                                                 (dlCellBw * 50) / 100; /* By default 50% */
                  }
               }
            }
            break;
            /* SPS changes ends */
         case  WR_TAG_DSCP_ENABLE:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteRabPolicyCfgGrp.isDscpEnable=atoi((S8*)tagVal);
               }
            }
            break;
         case  WR_TAG_QCI_DSCP_MAP:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  status = TRUE;
                  noOfParams = 0;
                  wrCfgValdtInput(tagVal, &status, &noOfElem);
                  if (TRUE == status && lteeNodeBparams[loopCnt].lteRabPolicyCfgGrp.isDscpEnable == TRUE)
                  {
                     wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                     for (loopCntTmp=0;loopCntTmp<noOfParams;loopCntTmp++)
                     {
                        dscp = atoi((S8*)paramLst[loopCntTmp]);
                        if(!(dscp & DSCP_ECN_BITS))
                        {
                           lteeNodeBparams[loopCnt].lteRabPolicyCfgGrp.drbPolicy[loopCntTmp].dscpInfo.dscp=dscp;
                        }
                        else
                        {
                           fprintf(stderr, "Invalid value for DSCP");
                           RETVALUE(RFAILED);
                        }   
                     }
                  }
                  else
                  {
                     fprintf(stderr, "DSCP is disabled");
                  }
               }
            }
            break;
         case  WR_TAG_DL_QCI_SCHD_WGT:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  status = TRUE;
                  noOfParams = 0;
                  wrCfgValdtInput(tagVal, &status, &noOfElem);
                  if (TRUE == status)
                  {
                     wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                     for (loopCntTmp=0;loopCntTmp<noOfParams;loopCntTmp++)
                     {
                        qciWgtVal = atoi((S8*)paramLst[loopCntTmp]);
                        if(qciWgtVal)
                        {
                           lteeNodeBparams[loopCnt].lteCellDlSchdCfgGrp.dlQciWgtList[loopCntTmp]= qciWgtVal;
                        }
                        else
                        {
                           fprintf(stderr, "Invalid value ");
                           RETVALUE(RFAILED);
                        }   
                     }
                  }
                  else
                  {
                     fprintf(stderr, "Dl Qci Wgt is disabled");
                  }
               }
            }
            break;
         case  WR_TAG_UL_QCI_SCHD_WGT:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  status = TRUE;
                  noOfParams = 0;
                  wrCfgValdtInput(tagVal, &status, &noOfElem);
                  if (TRUE == status)
                  {
                     wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                     for (loopCntTmp=0;loopCntTmp<noOfParams;loopCntTmp++)
                     {
                        qciWgtVal = atoi((S8*)paramLst[loopCntTmp]);
                        if(qciWgtVal)
                        {
                           lteeNodeBparams[loopCnt].lteCellUlSchdCfgGrp.ulQciWgtList[loopCntTmp]= qciWgtVal;
                        }
                        else
                        {
                           fprintf(stderr, "Invalid value ");
                           RETVALUE(RFAILED);
                        }   
                     }
                  }
                  else
                  {
                     fprintf(stderr, "Ul Qci Wgt is disabled");
                  }
               }
            }
            break;

            /* CSG_DEV start CSG configuration parameters */
         case WR_TAG_CSG_CSG_ID:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellSib1CfgGrp.cellAccessInfo.csgIdentity = (U32)atoi((S8 *)tagVal);
                  /* one csgId parameter from neighbor structure   */
               }
            }
            break;
         case WR_TAG_CSG_ACCESS_MODE:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteFapAccessParams.accessMode = (U8)atoi((S8 *)tagVal);
                  /* TODO in neighbour structure*/
               }
            }
            break;
         case WR_TAG_CSG_CSG_PCI_START:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteSib4CsgInfo.isCsgPciCfgd = TRUE;
                  lteeNodeBparams[loopCnt].lteSib4CsgInfo.csgStartPhyCellId  = (U16)atoi((S8 *)tagVal);
               }
            }
            break;
         case WR_TAG_CSG_CSG_PCI_RANGE:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteSib4CsgInfo.csgPciRange = (U16)atoi((S8 *)tagVal);
               }
            }
            break;
         case WR_TAG_CSG_SMCELL_PCI_START:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteAddCellCfg.isSmallCellPciCfgd  = TRUE;
                  lteeNodeBparams[loopCnt].lteAddCellCfg.startPci = (U16)atoi((S8 *)tagVal);
               } 
            }
            break;
         case WR_TAG_CSG_SMCELL_PCI_RANGE:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteAddCellCfg.pciRange  = (U16)atoi((S8 *)tagVal);
               }
            }
            break;
         case WR_TAG_CSG_HENB_NAME:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  tagLen = strlen((S8 *)tagVal);
                  if(48 < tagLen)
                  {
                     tagLen = 48;
                     fprintf(stderr, "Shrinking HeNB name to 48 charectors");
                  }
                  cmMemcpy((U8*)&lteeNodeBparams[loopCnt].lteEnbProtoCfg.henbName,(U8*)tagVal, tagLen);
                  cmMemcpy((U8*)&lteeNodeBparams[loopCnt].lteCellSib9CfgGrp.henbName,(U8*)tagVal, tagLen);
               }
            }
            break;
         case WR_TAG_MAX_CSG_UES:
            {
               wrSmDfltMaxCsgUEs = (U16)atoi((S8 *)tagVal);
            }
            break;
         case WR_TAG_MAX_NON_CSG_UES:
            {
               wrSmDfltMaxNonCsgUEs = (U16)atoi((S8 *)tagVal);
            }
            break;
         case WR_TAG_MIN_DL_RSRC_FOR_NON_CSG:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteAddCellCfg.minDlResNonCsg = (U8)atoi((S8 *)tagVal);
               }
            }
            break;
         case WR_TAG_MIN_UL_RSRC_FOR_NON_CSG:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteAddCellCfg.minUlResNonCsg = (U8)atoi((S8 *)tagVal);
               }
            }
            break;
            /* CSG_DEV end CSG configuration parameters */
            /*UE History info - start*/
         case WR_TAG_CELL_SIZE_TYPE:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteAddCellCfg.cellSizeType = (U8)atoi((S8*)tagVal);
                  if((lteeNodeBparams[loopCnt].lteAddCellCfg.cellSizeType < \
                           WR_ENB_CELL_SIZE_TYPE_VERY_SMALL) || \
                        (lteeNodeBparams[loopCnt].lteAddCellCfg.cellSizeType > \
                         WR_ENB_CELL_SIZE_TYPE_LARGE))
                  {
                     lteeNodeBparams[loopCnt].lteAddCellCfg.cellSizeType = \
                                                                  WR_ENB_CELL_SIZE_TYPE_VERY_SMALL;
                  }
               }
            }
            break;
            /*UE History info - end*/

            /* LTE_ADV starts */
            /* LTE_ADV_ABS starts */
         case WR_TAG_ARP_EMER_SERV:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteAddCellCfg.emergencyServicePriorityLevel = \
                                                                                (U8)atoi((S8*)tagVal);
                  if(lteeNodeBparams[loopCnt].lteAddCellCfg.emergencyServicePriorityLevel > 15)
                  {
                     lteeNodeBparams[loopCnt].lteAddCellCfg.emergencyServicePriorityLevel = 1;
                  }
               }
            }
            break;
         case WR_TAG_ABS_A3_OFFSET:
            {
               smCfgCb.lteAdvancedConfig.a3Offset = (S8)atoi((S8*)tagVal); 
            }
            break;
         case WR_TAG_PICO_OFFSET:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].absSfrCfg.neighCIO= (U8)atoi((S8*)tagVal);
               }
            }
            break;
         case WR_TAG_ABS_PATTERN_TYPE:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].absSfrCfg.absPatternType   = (U32)atoi((S8*)tagVal); 
                  if(RGR_ABS_TRANSMIT == lteeNodeBparams[loopCnt].absSfrCfg.absPatternType)
                  {
                     smCfgCb.lteAdvancedConfig.enbType = WR_LTE_ADV_PICO_ENB;
                  }
                  else
                  {
                     smCfgCb.lteAdvancedConfig.enbType = WR_LTE_ADV_MACRO_ENB;
                  }
               }
            }
            break;
         case WR_TAG_CELL_PMAX:
            {
               wrSmDfltPMax = (S8)atoi((S8*)tagVal);
            }
            break; 
         case  WR_TAG_CNM_ENABLED:
            {
               wrSmDfltIsCnmEnabled = atoi((S8 *)tagVal);
               printf("\n CNM Status ::%d\n",wrSmDfltIsCnmEnabled);
            }   
            break;
         case  WR_TAG_CNM_BOARD_TYPE:
            {
               wrSmDfltTddBoardType = atoi((S8 *)tagVal);
               printf("\n CNM board type is  ::%d\n",wrSmDfltTddBoardType);
            }   
            break;

         case WR_TAG_ABS_PATTERN:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  U8   temp[RGR_ABS_PATTERN_LEN]; 
                  Bool invalidValue =FALSE;
                  U32 idx;
                  const U32 baseAscii2Num = 48;
                  cmMemcpy((U8 *) temp,  (U8 *) &tagVal, RGR_ABS_PATTERN_LEN);
                  for (idx = 0; idx < RGR_ABS_PATTERN_LEN; idx++)
                  {
                     if (temp[idx] != '0' && temp[idx] != '1')
                     {
                        fprintf(stderr, "Please check the Value.The pattern should have only 0 and 1\n");
                        invalidValue = TRUE;
                        break;
                     }
                     lteeNodeBparams[loopCnt].absSfrCfg.absPattern[idx] = temp[idx] - baseAscii2Num;
                  }
               }
            }
            break;
         case WR_TAG_ABS_LOAD_PERIODICITY:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].absSfrCfg.absLoadPeriodicity = (U32)atoi((S8*)tagVal);
               }
            }
            break;
            /* LTE_ADV_ABS ends */
         case WR_TAG_SFR_START_RB:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].absSfrCfg.startRb = (U8)atoi((S8*)tagVal);
               }
            }
            break;

         case WR_TAG_SFR_END_RB:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].absSfrCfg.endRb  = (U8)atoi((S8*)tagVal); 
               }
            }
            break;

#ifdef TFU_UPGRADE            
         case WR_TAG_SFR_POWER_LOW:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].absSfrCfg.pLow = (U32)atoi((S8*)tagVal);
               }
            }
            break;

         case WR_TAG_SFR_POWER_HIGH:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].absSfrCfg.pHigh = (U32)atoi((S8*)tagVal);
               }
            }
            break;
#endif            
            /* LTE_ADV ends */
         case WR_TAG_RIM_CFG:
            {   
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  status     = TRUE;
                  noOfElem   = 0;
                  noOfParams = 0;
                  loopCntTmp    = 0;
                  wrCfgValdtInput(tagVal, &status, &noOfElem);
                  if (TRUE == status)
                  {
                     wrCfgGetParamVal(tagVal, paramLst, &noOfParams);

                     lteeNodeBparams[loopCnt].lteRimParams.rimOvrlTmrVal = (U32)atoi((S8*)paramLst[loopCntTmp++]);
                     if(( lteeNodeBparams[loopCnt].lteRimParams.rimOvrlTmrVal < WR_RIM_OVRL_TMR_MIN_VAL ) || 
                           ( lteeNodeBparams[loopCnt].lteRimParams.rimOvrlTmrVal > WR_RIM_OVRL_TMR_MAX_VAL ))
                     {
                        lteeNodeBparams[loopCnt].lteRimParams.rimOvrlTmrVal =\
                                                                    WR_RIM_OVRL_TMR_DFLT_VAL;
                     RLOG0(L_ERROR, "rimOvrlTmr out of range.Assigned rimOvrlTmr with default value ");
                     }

                     lteeNodeBparams[loopCnt].lteRimParams.rimRirTmr = \
                                                              (U32)atoi((S8*)paramLst[loopCntTmp++]);
                     if(( lteeNodeBparams[loopCnt].lteRimParams.rimRirTmr < WR_RIM_TMR_MIN_VAL ) || \
                           ( lteeNodeBparams[loopCnt].lteRimParams.rimRirTmr > \
                             WR_RIM_TMR_MAX_VAL ))
                     {
                        lteeNodeBparams[loopCnt].lteRimParams.rimRirTmr = WR_RIM_TMR_DFLT_VAL;
                     RLOG0(L_ERROR, "rimRirTmr out of range.Assigned rimRirTmr with default value ");
                     }

                     lteeNodeBparams[loopCnt].lteRimParams.rimRiTmr = (U32)atoi((S8*)paramLst[loopCntTmp++]);
                     if(( lteeNodeBparams[loopCnt].lteRimParams.rimRiTmr < WR_RIM_TMR_MIN_VAL ) || \
                           ( lteeNodeBparams[loopCnt].lteRimParams.rimRiTmr > WR_RIM_TMR_MAX_VAL ))
                     {
                        lteeNodeBparams[loopCnt].lteRimParams.rimRiTmr = WR_RIM_TMR_DFLT_VAL;
                     RLOG0(L_ERROR, "rimRiTmr out of range.Assigned rimRiTmr with default value ");
                     }

                     lteeNodeBparams[loopCnt].lteRimParams.rimRiaeTmr = (U32)atoi((S8*)paramLst[loopCntTmp++]);
                     if(( lteeNodeBparams[loopCnt].lteRimParams.rimRiaeTmr < WR_RIM_TMR_MIN_VAL ) || \
                           ( lteeNodeBparams[loopCnt].lteRimParams.rimRiaeTmr > WR_RIM_TMR_MAX_VAL ))
                     {
                        lteeNodeBparams[loopCnt].lteRimParams.rimRiaeTmr = WR_RIM_TMR_DFLT_VAL;
                        RLOG0(L_ERROR, "rimRiaeTmr out of range.Assigned rimRiaeTmr \
                              with default value \n");
                     }

                     lteeNodeBparams[loopCnt].lteRimParams.rimMaxRetryCnt = \
                                                                   (U32)atoi((S8*)paramLst[loopCntTmp]);
                     if(( lteeNodeBparams[loopCnt].lteRimParams.rimMaxRetryCnt < \
                              WR_RIM_RETRY_CNT_MIN_VAL ) || \
                           ( lteeNodeBparams[loopCnt].lteRimParams.rimMaxRetryCnt > \
                             WR_RIM_RETRY_CNT_MAX_VAL ))
                     {
                        lteeNodeBparams[loopCnt].lteRimParams.rimMaxRetryCnt = \
                                                                      WR_RIM_RETRY_CNT_DFLT_VAL;
                        RLOG0(L_ERROR, "rimMaxRetryCnt out of range.Assigned \
                              rimMaxRetryCnt with default value \n");
                     }
                  }
                  else
                  {
                     fprintf(stderr, "Failed reading the RIM Parameters");
                     RETVALUE(RFAILED);
                  }
               }
            }
            break;

         case WR_TAG_DCFI_ENABLE:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteDynCfiParams.isDynCfiEnb = (Bool)atoi((S8*)tagVal);  
               }
            }
            break;

         case WR_TAG_CFI:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteSmCellCfg.dfltCfiCfg = (U32)atoi((S8*)tagVal);
               }
            }
            break; 
         case WR_TAG_GRP_PUCCH_PWR_CTRL_ENABLE:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].ltecellSchdPwrCfg.isUlGrpPwrCntrlPucchEnable = 
                     (U8)atoi((S8*)tagVal);
               }
            }
            break;
         case WR_TAG_GRP_PUSCH_PWR_CTRL_ENABLE:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].ltecellSchdPwrCfg.isUlGrpPwrCntrlPuschEnable
                     = (U8)atoi((S8*)tagVal);
               }
            }
            break;
         case WR_TAG_LTE_PUCCH_PWR_FMT3A_ENABLE:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
               lteeNodeBparams[loopCnt].ltecellSchdPwrCfg.pucchPwrFmt3aEnable = (U8)atoi((S8*)tagVal);
               }
            }
            break;
         case WR_TAG_LTE_PUSCH_PWR_FMT3A_ENABLE:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
               lteeNodeBparams[loopCnt].ltecellSchdPwrCfg.puschPwrFmt3aEnable = (U8)atoi((S8*)tagVal);
               }
            }
            break;
         case  WR_TAG_TA_TMR_CMN:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
               lteeNodeBparams[loopCnt].sib2Cfg.timeAlignmentCommon = atoi((S8 *)tagVal);
               }
            }   
            break;
         case  WR_TAG_TA_TMR_DED:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
               lteeNodeBparams[loopCnt].macMainConfig.timeAlignmentTimerDedicated = atoi((S8 *)tagVal);
               }
            }
            break;
         case WR_TAG_DUAL_RX_TX_SUPPORTED:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].csfbCfgGrp.dualRxTxSup = atoi((S8 *)tagVal);
               }
            }
            break;
#ifdef LTE_ADV
         case  WR_TAG_ENABLE_CA:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].caGenCfg.isCaEnabled = (Bool)atoi((S8 *)tagVal);
               }
            }
            break;
#ifdef LTE_ADV_UECAP
         case WR_TAG_CELL_FREQ_CONTIGUOUS:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].caGenCfg.isCellFreqCont = (Bool)atoi((S8 *)tagVal);
               }
            }
            break;
#endif /*LTE_ADV_UECAP*/            
#endif /* LTE_ADV/ */
#ifdef TENB_STATS
        case WR_TAG_TENB_STATS:
            {
               status     = TRUE;
               noOfParams = 0;
               noOfElem   = 0;
               loopCnt    = 0;
               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  if(noOfParams > 5)
                  {
                     fprintf(stderr, "Error in Configuring TeNB Stats Config \n");
                     RETVALUE(RFAILED);
                  }
                  wrSmDfltTenbSocketStats = atoi((S8*)paramLst[loopCnt]);
                  wrSmDfltTenbFileStats = atoi((S8*)paramLst[loopCnt + 1]);
                  wrSmDfltTenbConsoleStats = atoi((S8*)paramLst[loopCnt + 2]);
                  wrSmDfltTenbStatsPeriodicity = atoi((S8*)paramLst[loopCnt + 3]);
                  wrSmDfltTenbStatsSocketPort = atoi((S8*)paramLst[loopCnt + 4 ]);
               }
            }
            break;
#endif /* TENB_STATS */
            /*RBC_SP1_X*/
         case WR_TAG_NUM_PRB_RPTS:
            {
               wrSmDfltNoOfPrbRpts = atoi((S8*)tagVal);
            }
            break;
         case WR_TAG_PRB_RPT_INTERVAL:
            {
               wrSmDfltPrbRptInterval = atoi((S8*)tagVal);
            }
            break;
            /*RBC_SP1_Y*/
#ifdef RSYS_WIRESHARK
         case WR_TAG_WIRESHARK_PORT:
            {
             //  wrSmDfltWiresharkPort = atoi((S8*)tagVal);
               lteeNodeBparams[0].lteGostLog.portNumber = atoi((S8*)tagVal);
            }
            break;
         case WR_TAG_WIRESHARK_DST_IP_ADDR:
            {
              /* cmInetAddr((S8 *)tagVal,&(wrSmDfltWiresharkDstIpAddr));
               wrSmDfltWiresharkDstIpAddr = CM_INET_HTON_U32(wrSmDfltWiresharkDstIpAddr);*/
               cmMemcpy((U8*)lteeNodeBparams[0].lteGostLog.ipAddress,
                  (U8*)tagVal, sizeof(lteeNodeBparams[0].lteGostLog.ipAddress));
            }
            break;
         case  WR_TAG_RRC_LOG_ENABLE:
            {
               lteeNodeBparams[0].lteGostLog.rrcLogEnable = atoi((S8 *)tagVal); /*TODO - remove*/
            }
            break;
#endif/*RSYS_WIRESHARK*/
         case WR_TAG_SRS_ENABLE:
            {
               wrSmEnableSrs = atoi((S8*)tagVal);
               if (wrSmEnableSrs > 1)
               {
#ifdef DEBUGP
                  WR_DBGP(DBGMASK_SM, (SM_PRNT_BUF, \
                           "Please enter value which is in valid range 0 or 1 for enabling or disabling SRS \n"));
                  WR_DBGP(DBGMASK_SM, (SM_PRNT_BUF, \
                           "Current disabling by default"));
#endif
                  wrSmEnableSrs = FALSE;
                  RETVALUE(RFAILED);
               }
               printf("[SRS] SRS status [%d] 0- Disabled, 1 - enabled", wrSmEnableSrs);
            }
            break;
         case WR_TAG_SRS_PERIODICITY:
            {
               wrSmUlSrsPeriod = atoi((S8*)tagVal);
               if ((wrSmUlSrsPeriod < LWR_SM_MIN_ULSRS_PERIOD) && (wrSmUlSrsPeriod > LWR_SM_MAX_ULSRS_PERIOD))
               {
#ifdef DEBUGP
                  WR_DBGP(DBGMASK_SM, (SM_PRNT_BUF, \
                           "Please enter value which is in valid range Min [%d] ms and Max [%d] ms for UL SRS Periodicity\n", LWR_SM_MIN_ULSRS_PERIOD, LWR_SM_MAX_ULSRS_PERIOD));
                  WR_DBGP(DBGMASK_SM, (SM_PRNT_BUF, \
                           "Current support only for 20 millisecond only"));
#endif
                  wrSmUlSrsPeriod = 20;
                  RETVALUE(RFAILED);
               }
               if(wrSmUlSrsPeriod == SRS_PERIODICITY_20MS)
               {
                  /* SUBBU Need to check */
                  wrSmDfltSrsSubfrmCfg = 0;
                  wrSmDfltSrsCfgPrdEnum = 5;
               }
               else
               {
                  //printf("[SRS] configured BW is not 20ms, it is [%d], need to visit for srsCfgPrdenum[%d]",(U32)wrSmUlSrsPeriod, (U32 )wrSmDfltSrsCfgPrdEnum);
               }
            }
            break;

         case WR_TAG_SRS_CELL_BANDWIDTH:
            {
               wrSmDfltSrsBandwidthCfg = atoi((S8*)tagVal);

               if(wrSmDfltSrsBandwidthCfg > 7)
               {
#ifdef DEBUGP
                  WR_DBGP(DBGMASK_SM, (SM_PRNT_BUF, \
                           "Please enter value which is in valid range Min [0] ms and Max [7] ms for UL CELL SRS Bandwidth\n"));
                  WR_DBGP(DBGMASK_SM, (SM_PRNT_BUF, \
                           "Current support only for bandwidth 2"));
#endif
                  wrSmDfltSrsBandwidthCfg = 2;
                  RETVALUE(RFAILED);
               }

            }
            break;

         case WR_TAG_SRS_CELL_SUBFRAME_CFG:
            {
               wrSmDfltSrsSubfrmCfg = atoi((S8*)tagVal);
               if(wrSmDfltSrsSubfrmCfg > 15)
               {
#ifdef DEBUGP
                  WR_DBGP(DBGMASK_SM, (SM_PRNT_BUF, \
                           "Please enter value which is in valid range Min [0] ms and Max [15] ms for UL CELL SRS Subframe Config\n"));
                  WR_DBGP(DBGMASK_SM, (SM_PRNT_BUF, \
                           "Current support only for bandwidth 0"));
#endif
                  wrSmDfltSrsSubfrmCfg = 0;
                  RETVALUE(RFAILED);
               }
            }
            break;

         case WR_TAG_SRS_CELL_ACKNACK_SIMTX:
            {
               if ((atol((S8*)tagVal)) == 1)
               {
                  wrSmDfltAckNackSrsSimTrns = TRUE;
               }
               else
               {
                  wrSmDfltAckNackSrsSimTrns = FALSE;
#ifdef DEBUGP     
                  WR_DBGP(DBGMASK_SM, (SM_PRNT_BUF, \
                           "AckNack SRS simultaneous is set to FALSE"));
#endif

               }
            }
            break;

         case WR_TAG_SRS_CELL_MAX_UPPTS:
            {
               wrSmDfltSrsMaxUpPts = atoi((S8*)tagVal);
               if(wrSmDfltSrsMaxUpPts > 1)
               {
#ifdef DEBUGP
                  WR_DBGP(DBGMASK_SM, (SM_PRNT_BUF, \
                           "Please enter value which is in valid value either 0 or 1 for UL CELL SRS Max UpPTS\n"));
                  WR_DBGP(DBGMASK_SM, (SM_PRNT_BUF, \
                           "Current support only for 0 (disalbing)"));
#endif
                  wrSmDfltSrsMaxUpPts = 0;
                  RETVALUE(RFAILED);
               }

            }
            break;

         case WR_TAG_SRS_UE_BANDWIDTH:
            {
               wrSmDfltSrsUeBandwidthCfg = atoi((S8*)tagVal);
               if(wrSmDfltSrsUeBandwidthCfg > 3)
               {
#ifdef DEBUGP
                  WR_DBGP(DBGMASK_SM, (SM_PRNT_BUF, \
                           "Please enter value which is in valid range Min [0] ms and Max [3] ms for UL UE SRS Bandwidth\n"));
                  WR_DBGP(DBGMASK_SM, (SM_PRNT_BUF, \
                           "Current support only for bandwidth 0"));
#endif
                  wrSmDfltSrsUeBandwidthCfg = 0;
                  RETVALUE(RFAILED);
               }
            }

            break;

         case WR_TAG_SRS_UE_HOPPING_BW:
            {
               wrSmDfltSrsUEHoppingBandwidth = atoi((S8*)tagVal);
               if(wrSmDfltSrsUEHoppingBandwidth > 3)
               {
#ifdef DEBUGP
                  WR_DBGP(DBGMASK_SM, (SM_PRNT_BUF, \
                           "Please enter value which is in valid range Min [0] ms and Max [3] ms for UL UE SRS Bandwidth\n"));
                  WR_DBGP(DBGMASK_SM, (SM_PRNT_BUF, \
                           "Current support only for hopping bandwidth 0"));
#endif
                  wrSmDfltSrsUEHoppingBandwidth = 0;
                  RETVALUE(RFAILED);
               }
            }
            break;
         case WR_TAG_RSYS_TPM_TGT_RSRP:
            {
               smCfgCb.tpmCfg.tgtRsrp = atoi((S8 *)tagVal);
            }
            break;
         case WR_TAG_RSYS_TPM_ATTN_CONST_IDX:
            {
               smCfgCb.tpmCfg.attnConstIdx = atoi((S8 *)tagVal);
            }
            break;
         case WR_TAG_RSYS_TPM_MIN_RSRP:
            {
               smCfgCb.tpmCfg.minRsrp = atoi((S8 *)tagVal);
            }
            break;
         case WR_TAG_RSYS_TPM_MAX_RSRP:
            {
               smCfgCb.tpmCfg.maxRsrp = atoi((S8 *)tagVal);
            }
            break;
         case WR_TAG_NUM_TX_ANTENNA:         
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteAntenna_Common_Config.numAntPorts = atoi((S8 *)tagVal);
                  printf("\n Num of Tx antenna is  ::%d\n", 
                        lteeNodeBparams[loopCnt].lteAntenna_Common_Config.numAntPorts);
               }
            }   
            break;
#ifdef LTE_ADV
          case WR_TAG_MEAS_SCELL_ADD_REL:
            {
               for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
               {
                  lteeNodeBparams[loopCnt].lteCellMeasCfgGrp.isMeasReqForSCellAdd = atoi((S8 *)tagVal);
               }
            }
            break;
#endif
#ifdef LTE_UNLICENSED
          case WR_TAG_LTEU_NUM_CELLS:
            {
               wrSmDfltNumUnLicnsdCells = (U8)atoi((S8*)tagVal);
               printf("\n2: No Of Unlicensed Cells Configured = %d \n", wrSmDfltNumUnLicnsdCells);
              // RLOG1(L_DEBUG, "Number of Unlicensed Cells configured L3 %d\n", wrSmDfltNumUnLicnsdCells);
               if ((wrSmDfltNumUnLicnsdCells != 0) && (isNumLteURead == TRUE) && \
                     (lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteUCfg.numFreq < wrSmDfltNumUnLicnsdCells))
               {
                //  RLOG2(L_DEBUG, "Error in WR_TAG_LTEU_FREQ_CFG less than WR_TAG_LTEU_NUM_SDL_CELLS \n", \
                        lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteUCfg.numFreq, wrSmDfltNumUnLicnsdCells);
                  break;
               }
               isNumLteURead = TRUE; /* To avoid dependency of sequence in wr_cfg.txt */
            }
            break;
          case  WR_TAG_LTEU_CELL_TYPE:
            {

               lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteUCfg.isLaaCell = (U8)atoi((S8*)tagVal);
             //  RLOG1(L_DEBUG, "Type  of Unlicensed Cells configured L3 %d\n", \
                     lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteUCfg.isLaaCell);
            }
            break;
          case WR_TAG_LTEU_COEXIST_METHOD:
            {
               lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteUCfg.coExistMethod = (U8)atoi((S8*)tagVal);
            }
            break;    
        case WR_TAG_LTEU_ON_PERIOD:
            {
               lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteUCfg.lteOnPeriod = (U8)atoi((S8*)tagVal);
            }
            break;    
        case WR_TAG_LTEU_CCA_METHOD:
            {
               lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteUCfg.caeMethod= (U8)atoi((S8*)tagVal);
            }
            break;    
        case WR_TAG_LTEU_ADPT_PRD_TX_ENB:
            {
               lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteUCfg.adaptiveTx = (U8)atoi((S8*)tagVal);
            }
            break;    
        case WR_TAG_LTEU_TX_PERIOD:
            {
               lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteUCfg.transPeriod = (U16)atoi((S8*)tagVal);
            }
            break;
        case WR_TAG_LTEU_LISTENING_PERIOD:
            {
               lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteUCfg.listenPrd = (U16)atoi((S8*)tagVal);
            }
            break;
        case WR_TAG_LTEU_ENERGY_THRESHOLD:
            {
               lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteUCfg.energyTh = (S16)atoi((S8*)tagVal);
            }
            break;
        case WR_TAG_LTEU_SCAN_TIME_PERIOD:
            {
               lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteUCfg.scanTimePrd = (U16)atoi((S8*)tagVal);
            }
            break;
        case WR_TAG_LTEU_ACTIVITY_THRESHOLD:
            {
               lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteUCfg.activityTh = (U16)atoi((S8*)tagVal);
            }
            break;
        case WR_TAG_LTEU_MAX_RSRP:
            {
               lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteUCfg.txPowerLimit = (S16)atoi((S8*)tagVal);
            }
            break;
        case WR_TAG_LTEU_FREQ_CFG:
            {
               status = TRUE;
               noOfElem = 0;
               noOfParams = 0;
               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  if ((wrSmDfltNumUnLicnsdCells != 0)  && (isNumLteURead == TRUE) && \
                     (noOfParams < wrSmDfltNumUnLicnsdCells))
                  {
                     RLOG0(L_DEBUG, "Error in WR_TAG_LTEU_FREQ_CFG less than WR_TAG_LTEU_NUM_SDL_CELLS \n");
                     break;
                  }

                  lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteUCfg.numFreq = noOfParams;

                  for (loopCnt = 0; loopCnt < noOfParams; loopCnt++)
                  {
                     lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteUCfg.earfcn[loopCnt] = (U16)atoi((S8 *)paramLst[loopCnt]);
                  }
               }
               else
               {
                  fprintf(stderr, "Error in WR_TAG_LTEU_FREQ_CFG tag format \n");
               }
               isNumLteURead = TRUE;
            }
            break;
#endif
        case WR_TAG_L3_IP:
            {
               status     = TRUE;
               noOfParams = 0;
               noOfElem   = 0;

               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  cmInetAddr((S8 *)paramLst[0], &(L3_IP_ADDR));
                  L3_IP_ADDR =  CM_INET_HTON_U32(L3_IP_ADDR);
                  L3_PORT_TIP  =  (U16)atoi((S8 *)paramLst[1]);
               }
            }
            break;
        case WR_TAG_UL2_IP:
            {
               status     = TRUE;
               noOfParams = 0;
               noOfElem   = 0;

               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  cmInetAddr((S8 *)paramLst[0], &(UL2_IP_ADDR));
                  UL2_IP_ADDR =  CM_INET_HTON_U32(UL2_IP_ADDR);
                  UL2_PORT_TIP =  (U16)atoi((S8 *)paramLst[1]);
               }
            }
            break;
        case WR_TAG_LL2_IP:
            {
               status     = TRUE;
               noOfParams = 0;
               noOfElem   = 0;

               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  cmInetAddr((S8 *)paramLst[0], &(LL2_IP_ADDR));
                  LL2_IP_ADDR =  CM_INET_HTON_U32(LL2_IP_ADDR);
                  LL2_PORT_TIP =  (U16)atoi((S8 *)paramLst[1]);
               }
            }
            break;
        case WR_TAG_UL2_IP_LIST:
            {
               status = TRUE;
               noOfElem = 0;
               noOfParams = 0;
               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  paramCnt = 0;
                  for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
                  {
                     vmAssocInfo[loopCnt].cellId = loopCnt+1; /*Cell ID starts from 1*/
                     vmAssocInfo[loopCnt].l2uIpAddr.type = CM_IPV4ADDR_TYPE;
                     cmInetAddr((S8 *)paramLst[paramCnt++],
                     &(vmAssocInfo[loopCnt].l2uIpAddr.u.ipv4TptAddr.address));
                     vmAssocInfo[loopCnt].l2uIpAddr.u.ipv4TptAddr.address =  \
                            CM_INET_HTON_U32( vmAssocInfo[loopCnt].l2uIpAddr.u.ipv4TptAddr.address);                             
                     vmAssocInfo[loopCnt].l2uIpAddr.u.ipv4TptAddr.port =
                     (U16)atoi((S8 *)paramLst[paramCnt++]);
                     drvrIpProcIdInfo[loopCnt].cellId = loopCnt+1;
                     drvrIpProcIdInfo[loopCnt].ul2ProcId = WR_UL2_OFFSET + 
                        (vmAssocInfo[loopCnt].l2uIpAddr.u.ipv4TptAddr.address & 0x0000ffff);
                        //vmAssocInfo[loopCnt].l2uIpAddr.u.ipv4TptAddr.port;
                     drvrIpProcIdInfo[loopCnt].l2uIpAddr.u.ipv4TptAddr.address = 
                        vmAssocInfo[loopCnt].l2uIpAddr.u.ipv4TptAddr.address;
                  }
               }
               else
               {
                  fprintf(stderr, "Error in WR_TAG_UL2_IP_LIST tag format \n");
               }
            }
            break;
        case WR_TAG_LL2_IP_LIST:
            {
               status = TRUE;
               noOfElem = 0;
               noOfParams = 0;
               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  paramCnt = 0;
                  for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
                  {
                     vmAssocInfo[loopCnt].l2lIpAddr.type = CM_IPV4ADDR_TYPE;
                     cmInetAddr((S8 *)paramLst[paramCnt++], 
                           &(vmAssocInfo[loopCnt].l2lIpAddr.u.ipv4TptAddr.address));
                     vmAssocInfo[loopCnt].l2lIpAddr.u.ipv4TptAddr.address =  
                        CM_INET_HTON_U32( vmAssocInfo[loopCnt].l2lIpAddr.u.ipv4TptAddr.address);
                     vmAssocInfo[loopCnt].l2lIpAddr.u.ipv4TptAddr.port =
                        (U16)atoi((S8 *)paramLst[paramCnt++]);
                     drvrIpProcIdInfo[loopCnt].ll2ProcId = WR_LL2_OFFSET + 
                        (vmAssocInfo[loopCnt].l2lIpAddr.u.ipv4TptAddr.address & 0x0000ffff);
                        //vmAssocInfo[loopCnt].l2lIpAddr.u.ipv4TptAddr.port;
                     drvrIpProcIdInfo[loopCnt].l2lIpAddr.u.ipv4TptAddr.address = 
                        vmAssocInfo[loopCnt].l2lIpAddr.u.ipv4TptAddr.address;
                  }
               }
               else
               {
                  fprintf(stderr, "Error in WR_TAG_LL2_IP_LIST tag format \n");
               }
            }
            break;
        case WR_TAG_UL2_EGTP_IP_LIST:
            {
               status = TRUE;
               noOfElem = 0;
               noOfParams = 0;
               wrCfgValdtInput(tagVal, &status, &noOfElem);
               if (TRUE == status)
               {
                  wrCfgGetParamVal(tagVal, paramLst, &noOfParams);
                  paramCnt = 0;
                  for (loopCnt = 0; loopCnt < wrSmDfltNumCells; loopCnt++)
                  {
                     vmAssocInfo[loopCnt].cellId = loopCnt+1; /*Cell ID starts from 1*/
                     vmAssocInfo[loopCnt].l2uEgtpIpAddr.type = CM_IPV4ADDR_TYPE;
                     cmInetAddr((S8 *)paramLst[paramCnt++],
                     &(vmAssocInfo[loopCnt].l2uEgtpIpAddr.u.ipv4TptAddr.address));
                     vmAssocInfo[loopCnt].l2uEgtpIpAddr.u.ipv4TptAddr.address =  \
                            CM_INET_HTON_U32( vmAssocInfo[loopCnt].l2uEgtpIpAddr.u.ipv4TptAddr.address);                             
                     vmAssocInfo[loopCnt].l2uEgtpIpAddr.u.ipv4TptAddr.port =
                     (U16)atoi((S8 *)paramLst[paramCnt++]);
                  }
               }
               else
               {
                  fprintf(stderr, "Error in WR_TAG_UL2_IP_LIST tag format \n");
               }
            }
            break;

         case WR_TAG_DUL2_IP:
            cmInetAddr((S8 *)tagVal, &(UL2_GTP_IP_ADDR));
            UL2_GTP_IP_ADDR =  CM_INET_HTON_U32(UL2_GTP_IP_ADDR);
            break;

        case WR_TAG_L3_PORT:
            L3_PORT_TIP = atoi((S8 *)tagVal);
            L3_PORT = L3_PORT_TIP + 10;
            break;

        default :
            {
            }
            break;   
      }/* End of switch() */
      tagNum = MAX_CFG_PARAM;
   }/* End of for() */

   fprintf(stdout, "Read the wr_cfg.txt file successfully ");
   fclose(fp);
#ifdef WR_RSYS_OAM
   char config_log_path[WR_MAX_LOG_PATH_VALUE*2];
   char config_log_file[MAX_LOG_FILE_NAME_LENGTH*2];
   FILE *fptr;
   fapParameters.configFilePath = SGetConfigPath();
   if ((fptr=fopen(SGetConfigPath(), "r")))
   {
      getData(fptr,"OAM_LOGGING_DIR",config_log_path);
      if(strlen(config_log_path) >= 100)//WR_MAX_LOG_PATH_VALUE)
      {
         ALARM("WR_TAG_LOG_PATH tag value is greater than \
               WR_MAX_LOG_PATH_VALUE ,taking default log path:/var/log/\n");
         strcpy((S8*)logPath,"/var/log");
      }
      else
      {
         strcpy((S8*)logPath,config_log_path);
      }
      getData(fptr,"OAM_TAG_LOG_FILE_NAME",config_log_file);
      if(strlen(config_log_file) >= MAX_LOG_FILE_NAME_LENGTH)
      {
         ALARM("OAM_TAG_LOG_FILE_NAME length is greater than  MAX_LOG_FILE_NAME_LENGTH");
         RETVALUE (RFAILED);
      }
      else
      {
         strcpy((S8*)logFileName, config_log_file);
      }
      rlSetLogFile((S8 *)logFileName);
      rlSetLogPath((const char*)logPath);
      fclose(fptr);
   }

   fprintf(stdout, "Read the configFile file successfully ");
#endif


   RETVALUE (ROK);
} /* end of smWrReadConfigParams */

PUBLIC Void getData
 (
  FILE *fptr,
  char *fieldName ,
  char *FieldValue
  )
{
   *FieldValue='\0';
   char buff[75];
   U8 ret;
   while(fscanf(fptr,"%74s",buff)!=EOF)
   {
      if(!strcmp(buff,fieldName))
      {
         ret = fscanf(fptr,"%74s",buff); // read value
         strcpy(FieldValue,buff);
         break;
      }
   }
}
