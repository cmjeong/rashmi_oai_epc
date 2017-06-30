/********************************************************************16**

            (c) Copyright 2012 by RadiSys Corporation. All rights reserved.

     This software is confidential and proprietary to RadiSys Corporation.
     No part of this software may be reproduced, stored, transmitted, 
     disclosed or used in any form or by any means other than as expressly
     provided by the written Software License Agreement between Radisys 
     and its licensee.

     Radisys warrants that for a period, as provided by the written
     Software License Agreement between Radisys and its licensee, this
     software will perform substantially to Radisys specifications as
     published at the time of shipment, exclusive of any updates or 
     upgrades, and the media used for delivery of this software will be 
     free from defects in materials and workmanship.  Radisys also warrants 
     that has the corporate authority to enter into and perform under the   
     Software License Agreement and it is the copyright owner of the software 
     as originally delivered to its licensee.

     RADISYS MAKES NO OTHER WARRANTIES, EXPRESS OR IMPLIED, INCLUDING
     WITHOUT LIMITATION WARRANTIES OF MERCHANTABILITY OR FITNESS FOR
     A PARTICULAR PURPOSE WITH REGARD TO THIS SOFTWARE, SERVICE OR ANY RELATED
     MATERIALS.

     IN NO EVENT SHALL RADISYS BE LIABLE FOR ANY INDIRECT, SPECIAL,
     CONSEQUENTIAL DAMAGES, OR PUNITIVE DAMAGES IN CONNECTION WITH OR ARISING
     OUT OF THE USE OF, OR INABILITY TO USE, THIS SOFTWARE, WHETHER BASED
     ON BREACH OF CONTRACT, TORT (INCLUDING NEGLIGENCE), PRODUCT
     LIABILITY, OR OTHERWISE, AND WHETHER OR NOT IT HAS BEEN ADVISED
     OF THE POSSIBILITY OF SUCH DAMAGE.

                       Restricted Rights Legend:
     
     This software and all related materials licensed hereby are
     classified as "restricted computer software" as defined in clause
     52.227-19 of the Federal Acquisition Regulation ("FAR") and were
     developed entirely at private expense for nongovernmental purposes,
     are commercial in nature and have been regularly used for
     nongovernmental purposes, and, to the extent not published and
     copyrighted, are trade secrets and confidential and are provided
     with all rights reserved under the copyright laws of the United
     States.  The government's rights to the software and related
     materials are limited and restricted as provided in clause
     52.227-19 of the FAR.

                    IMPORTANT LIMITATION(S) ON USE

     The use of this software is limited to the use set
     forth in the written Software License Agreement between Radisys and
     its Licensee. Among other things, the use of this software
     may be limited to a particular type of Designated Equipment, as 
     defined in such Software License Agreement.
     Before any installation, use or transfer of this software, please
     consult the written Software License Agreement or contact Radisys at
     the location set forth below in order to confirm that you are
     engaging in a permissible use of the software.

                    RadiSys Corporation
                    Tel: +1 (858) 882 8800
                    Fax: +1 (858) 777 3388
                    Email: support@trillium.com
                    Web: http://www.radisys.com 
 
*********************************************************************17*/

/**********************************************************************/
/*********************************************************************/
///////////////////////////////////////////////////////////////////////////////
//
// SmTr196Validator.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Trace.h>
#include <stdio.h>
///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "SmTr196Validator.h"

using namespace std;
using namespace boost;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

SmTr196Validator::SmTr196Validator()
{
    ENTER ();

    EXIT ();
}

SmTr196Validator::~SmTr196Validator()
{
    ENTER ();

    EXIT ();
}


u32 SmTr196Validator::arrSize;
s32 SmTr196Validator::arrPaInfo[] = {8,-600,-477,-300,-177,0,100,200,300};

u32 SmTr196Validator::arrAlphaInfo[] = {8,0,40,50,60,70,80,90,100};
s32 SmTr196Validator::arrdeltaPucchFormatInfo[] = {3,-2,0,2};
u32 SmTr196Validator::arrdeltaPucchFormat1bInfo[] = {3,1,3,5};
s32 SmTr196Validator::arrdeltaPucchFormat2Info[] = {4,-2,0,1,2};

u32 SmTr196Validator::arrRaPreamblesInfo[] = {16,4,8,12,16,20,24,28,32,36,40,44,48,52,56,60,64};
u32 SmTr196Validator::arrgroupASize[] = {15,4,8,12,16,20,24,28,32,36,40,44,48,52,56,60};
u32 SmTr196Validator::arrmsgSizeGroupA[] = {4,56,144,208,256};
s32 SmTr196Validator::arrpwrOffstGrpB[] = {8,-1,0,5,8,10,12,15,18};
u32 SmTr196Validator::arrpowerRampingstep[] = {4,0,2,4,6};
s32 SmTr196Validator::arrinitRcvdTrgtPwr[] = {16,-120,-118,-116,-114,-112,-110,-108,-106,-104,-102,-100,-98,-96,-94,-92,-90};
u32 SmTr196Validator::arrpreambleTransMax[] = {11,3,4,5,6,7,8,10,20,50,100,200};
u32 SmTr196Validator::arrrarWindowSize[] = {9,2,3,4,5,6,7,8,10};
u32 SmTr196Validator::arrmacContResTimer[] = {9,8,16,24,32,40,48,56,64};

u32 SmTr196Validator::arrdrxOnDurTmrInfo[] = {16,1,2,3,4,5,6,8,10,20,30,40,50,60,80,100,200};
u32 SmTr196Validator::arrdrxInactvTmrInfo[] = {22,1,2,3,4,5,6,8,10,20,30,40,50,60,80,100,200,300,500,750,1280,1920,2560};
u32 SmTr196Validator::arrdrxRetxTmrInfo[] = {8,1,2,4,6,8,16,24,33};
u32 SmTr196Validator::arrlongDrxCycleInfo[] = {16,10,20,32,40,64,80,128,160,256,320,512,640,1024,1280,2048,2560};
u32 SmTr196Validator::arrshortDrxCycleInfo[] = {16,2,5,8,10,16,20,32,40,64,80,128,160,256,320,512,640};

u32 SmTr196Validator::arrqHystInfo[] = {16,0,1,2,3,4,5,6,8,10,12,14,16,18,20,22,24};
s32 SmTr196Validator::arrsfInfo[] = {4,-6,-4,-2,0};
u32 SmTr196Validator::arrtEvalulationInfo[] = {5,30,60,120,180,240};
u32 SmTr196Validator::arrtHystNormalInfo[] = {5,30,60,120,180,240};
u32 SmTr196Validator::arrtReselectionSfInfo[] = {4,25,50,75,100};

u32 SmTr196Validator::arrrsrpFltrCoeffInfo[] = {15,0,1,2,3,4,5,6,7,8,9,11,13,15,17,19};
u32 SmTr196Validator::arrrsrqFltrCoeffInfo[] = {15,0,1,2,3,4,5,6,7,8,9,11,13,15,17,19};
u32 SmTr196Validator::arrecnoFltrCoeffInfo[] = {15,0,1,2,3,4,5,6,7,8,9,11,13,15,17,19};
u32 SmTr196Validator::arrmaxHARQ_TxInfo[] = {14,1,2,3,4,5,6,7,8,10,12,16,20,24,28};
u32 SmTr196Validator::arrperiodicBSR_TimerInfo[] = {14,5,10,16,20,32,40,64,80,128,160,320,640,1280,2560};
u32 SmTr196Validator::arrretxBSR_TimerInfo[] = {6,320,640,1280,2560,5120,10240};
u32 SmTr196Validator::arrtpRetransmitInfo[] = {55,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180,185,190,195,200,205,210,215,220,225,230,235,240,245,250,300,350,400,450,500};
u32 SmTr196Validator::arrpollPduInfo[] = {8,4,8,16,32,64,128,256,0};
u32 SmTr196Validator::arrpollByteInfo[] = {15,25,50,75,100,125,250,375,500,750,1000,1250,1500,2000,3000,0};
u32 SmTr196Validator::arrmaxRetransThreshInfo[] = {8,1,2,3,4,6,8,16,32}; 
u32 SmTr196Validator::arrtimerReorderingInfo[] = {31,0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,110,120,130,140,150,160,170,180,190,200};
u32 SmTr196Validator::arrtimerStatusProhibitInfo[] = {57,0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180,185,190,195,200,205,210,215,220,225,230,235,240,245,250,300,350,400,450,500};

u32 SmTr196Validator::arrt300Info[] = {8,100,200,300,400,600,1000,1500,2000};
u32 SmTr196Validator::arrt301Info[] = {8,100,200,300,400,600,1000,1500,2000};
u32 SmTr196Validator::arrt302Info[] = {8,100,200,300,400,600,1000,1500,2000};
u32 SmTr196Validator::arrt304Info[] = {7,50,100,150,200,500,1000,2000};
u32 SmTr196Validator::arrccoT304Info[] = {7,100,200,500,1000,2000,4000,8000};
u32 SmTr196Validator::arrt310Info[] = {7,0,50,100,200,500,1000,2000};
u32 SmTr196Validator::arrn310Info[] = {8,1,2,3,4,6,8,10,20};
u32 SmTr196Validator::arrt311Info[] = {7,1000,3000,5000,10000,15000,20000,30000};
u32 SmTr196Validator::arrn311Info[] = {8,1,2,3,4,5,6,8,10};
u32 SmTr196Validator::arrt320Info[] = {7,5,10,20,30,60,120,180};

s32 SmTr196Validator::arrqOffsetFreqInfo[] = {31,-24,-22,-20,-18,-16,-14,-12,-10,-8,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,8,10,12,14,16,18,20,22,24};
u32 SmTr196Validator::arrtResetEutraSFInfo[] = {4,25,50,75,100};
u32 SmTr196Validator::arrtimeToTriggerInfo[] = {16,0,40,64,80,100,128,160,256,320,480,512,640,1024,1280,2560,5120};
u32 SmTr196Validator::arrreportIntervalInfo[] = {13,120,240,480,640,1024,2048,5120,10240,60000,360000,720000,1800000,3600000};
u32 SmTr196Validator::arrNeighBandwidth[] = {6,6,15,25,50,75,100};
u8  SmTr196Validator::arrBitStringVals[] = {0,64,128,192};               

const char* SmTr196Validator::arrreportAmountInfo[] = {"r1","r2","r4","r8","r16","r32","r64","infinity"};
const char* SmTr196Validator::arrduplexModeInfo[] = {"FDDMode","TDDMode"};
const char* SmTr196Validator::arrdlBandwidthInfo[] = {"n6","n15","n25","n50","n75","n100"};
const char* SmTr196Validator::arrcSrsInfo[] = {"bw0","bw1","bw2","bw3","bw4","bw5","bw6","bw7"};
const char* SmTr196Validator::arrintgAlgoInfo[] = {"EIA0","128-EIA1","128-EIA2","128-EIA3"};
const char* SmTr196Validator::arrciphAlgoInfo[] = {"EEA0","128-EEA1","128-EEA2","128-EEA3"};
const char* SmTr196Validator::arrumtsBandListInfo[] = {"I","II","III","IV","V","VI","VII"};
const char* SmTr196Validator::arrdeltaShiftInfo[] = {"ds1","ds2","ds3"};
const char* SmTr196Validator::arrhoppingModeInfo[] = {"InterSubFrame","IntraAndInterSubFrame"};
const char* SmTr196Validator::arrtriggerQtyInfo[] = {"RSRP","RSRQ"};
const char* SmTr196Validator::arrreportQtyInfo[] = {"SameAsTriggerQuantity","Both"};
const char* SmTr196Validator::arrmeasQtyUtraFddInfo[] = {"CPICH-RSCP","CPICH-EcN0"};
const char* SmTr196Validator::arrInServiceHandlingInfo[] = {"Immediate","Delayed"};
const char* SmTr196Validator::arrlteAccessModeInfo[] = {"Invalid","Open_Access","Closed_Access","Hybrid_Access"};
const char* SmTr196Validator::arrlteAccessMode[] = {"Invalid","Open Access","Closed Access","Hybrid Access"};
const char* SmTr196Validator::arrlteAccessBarringFactor[] = {"p00","p05","p10","p15","p20","p25","p30","p40","p50","p60","p70","p75","p80","p85","p90","p95"};
const char* SmTr196Validator::arrlteAccessBarringTime[] = {"s4","s8","s16","s32","s64","s128","s256","s512"};
const char* SmTr196Validator::arrAllowedMeasBandwidthInfo[]= {"mbw6", "mbw15", "mbw25", "mbw50", "mbw75", "mbw100"};
const char* SmTr196Validator::arrQOffsetRangeInfo[] = {"dB-24", "dB-22", "dB-20", "dB-18", "dB-16", "dB-14","dB-12", "dB-10", "dB-8", "dB-6", "dB-5", "dB-4", "dB-3","dB-2", "dB-1", "dB0", "dB1", "dB2", "dB3", "dB4", "dB5","dB6", "dB8", "dB10", "dB12", "dB14", "dB16", "dB18","dB20", "dB22", "dB24"};
const char* SmTr196Validator::arrNeighCellConfigInfo[] = {"00","01","10","11"};
const char* SmTr196Validator::arrCdmaCellType[] = {"1XRTT","HRPD"};
const char* SmTr196Validator::ecsfbReportCfgVal[] = {"ECSFB_NOT_SUPPORTED","ECSFB_WITHOUT_MEAS","ECSFB_WITH_MEAS"};
const char* SmTr196Validator::csfbReportCfgVal[] = {"CSFB_WITHOUT_MEAS","CSFB_WITH_MEAS"};
const char* SmTr196Validator::arrmeasQtyCdma2k[] = {"PilotStrength", "PilotPnPhaseAndPilotStrength"};
const char* SmTr196Validator::arrGeranBandInd[] = {"GSM850", "GSM900", "DCS1800", "PCS1900"};
const char* SmTr196Validator::arrUtraTddMode[] = {"UTRA_TDD_128", "UTRA_TDD_384", "UTRA_TDD_768"};
const char* SmTr196Validator::arrMeasQtyUtraTdd[] = {"PCCPCH-RSCP", "RSCP"};
const char* SmTr196Validator::arrAutoConfigTM[] = {"OFF", "ON"};
const char* SmTr196Validator::arrPreferredTransMode[] = {"TM2", "TM3","TM4"};

void SmTr196Validator::GetLteU32enums(u32 arrU32enums[], u32 elem, u32 &pos) const
{
    ENTER ();

    arrSize = arrU32enums[0];
    TRACE_PRINTF("Number of elements in u32 U32enums is %d", arrSize);
   
    for(u32 idx=1; idx<=arrSize; idx++)
    {
	if(elem == arrU32enums[idx])
	{
		pos = idx-1;
    		TRACE_PRINTF("Position in U32enums is %d", pos);
		break;
	}
    }

         	
    EXIT ();
}

void SmTr196Validator::GetLteU32enums(u32 arrU32enums[], u32 elem, u16 &pos) const
{
    ENTER ();

    arrSize = arrU32enums[0];
    TRACE_PRINTF("Number of elements in u16 U32enums is %d", arrSize);
   
    for(u32 idx=1; idx<=arrSize; idx++)
    {
	if(elem == arrU32enums[idx])
	{
		pos = idx-1;
    		TRACE_PRINTF("Position in U32enums is %d", pos);
		break;
	}
    }

         	
    EXIT ();
}

void SmTr196Validator::GetLteU32enums(u32 arrU32enums[], u32 elem, u8 &pos) const
{
    ENTER ();

    arrSize = arrU32enums[0];
    TRACE_PRINTF("Number of elements in u8 U32enums is %d", arrSize);
   
    for(u32 idx=1; idx<=arrSize; idx++)
    {
	if(elem == arrU32enums[idx])
	{
		pos = idx-1;
    		TRACE_PRINTF("Position in U32enums is %d", pos);
		break;
	}
    }

         	
    EXIT ();
}

void SmTr196Validator::GetLteS32enums(s32 arrS32enums[], s32 elem, u32 &pos) const
{
    ENTER ();

    arrSize = arrS32enums[0];
    TRACE_PRINTF("Number of elements in u32 S32enum is %d", arrSize);
    
    for(u32 idx=1; idx<=arrSize; idx++)
    {
	if(elem == arrS32enums[idx])
	{
		pos = idx-1;
    		TRACE_PRINTF("Position in S32enum is %d", pos);
		break;
	}
    }
         	
    EXIT ();
}

void SmTr196Validator::GetLteS32enums(s32 arrS32enums[], s32 elem, u16 &pos) const
{
    ENTER ();

    arrSize = arrS32enums[0];
    TRACE_PRINTF("Number of elements in u16 S32enum is %d", arrSize);
    
    for(u32 idx=1; idx<=arrSize; idx++)
    {
	if(elem == arrS32enums[idx])
	{
		pos = idx-1;
    		TRACE_PRINTF("Position in S32enum is %d", pos);
		break;
	}
    }
         	
    EXIT ();
}

void SmTr196Validator::GetLteS32enums(s32 arrS32enums[], s32 elem, u8 &pos) const
{
    ENTER ();

    arrSize = arrS32enums[0];
    TRACE_PRINTF("Number of elements in u8 S32enum is %d", arrSize);
    
    for(u32 idx=1; idx<=arrSize; idx++)
    {
	if(elem == arrS32enums[idx])
	{
		pos = idx-1;
    		TRACE_PRINTF("Position in S32enum is %d", pos);
		break;
	}
    }
         	
    EXIT ();
}

bool SmTr196Validator::GetLteStringenums(const char* arrStringenums[], string elem, u8 &pos, u8 size)const
{
   ENTER ();

   arrSize = size;

   TRACE_PRINTF("Number of elements in Stringenum is %d", arrSize);

   for(u32 idx=0; idx<arrSize; idx++)
   {
      if(!strcmp(elem.c_str(),arrStringenums[idx]))
      {
         pos = idx;
         TRACE_PRINTF("Position in Stringenum is %d", pos);
         return (true);
      }
   }

   return (false);
   EXIT ();
}

void SmTr196Validator::GetLteStringArrayenums(const char* arrStringenums[], std::vector<std::string> elem, std::vector<u8> &pos, u8 size)const
{
    ENTER ();

    arrSize = size;
    TRACE_PRINTF("Number of elements in u8 StringArrayenum is %d", arrSize);
    
    for (u8 idxelem=0; idxelem<elem.size(); idxelem++)
    {
	    TRACE_PRINTF("Elem StringArrayenum[%d] is %s",idxelem,elem[idxelem].c_str());
	    for(u8 idx=0; idx<arrSize; idx++)
	    {
		    TRACE_PRINTF("Orig StringArrayenum[%d] is %s",idx,arrStringenums[idx]);
		    if((!elem[idxelem].empty())&&(!strcmp(elem[idxelem].c_str(),arrStringenums[idx])))
		    {
			    pos.push_back(idx);
			    TRACE_PRINTF("Position of StringArrayenum[%d] is %d with pos[%d] = %d",idx,idx,idxelem,pos[idxelem]);
		    }
	    }
    }
         	
    EXIT ();
}

void SmTr196Validator::GetLteStringArrayenums(const char* arrStringenums[], std::vector<std::string> elem, std::vector<u32> &pos, u8 size)const
{
    ENTER ();

    arrSize = size;
    TRACE_PRINTF("Number of elements in u32 StringArrayenum is %d", arrSize);

    for (u32 idxelem=0; idxelem<elem.size(); idxelem++)
    {
	    TRACE_PRINTF("Elem StringArrayenum[%d] is %s",idxelem,elem[idxelem].c_str());
	    for(u32 idx=0; idx<arrSize; idx++)
	    {
		    TRACE_PRINTF("Orig StringArrayenum[%d] is %s",idx,arrStringenums[idx]);
		    if((!elem[idxelem].empty())&&(!strcmp(elem[idxelem].c_str(),arrStringenums[idx])))
		    {
			    pos.push_back(idx);
			    TRACE_PRINTF("Position of StringArrayenum[%d] is %d with pos[%d] = %d",idx,idx,idxelem,pos[idxelem]);
		    }
	    }
    }

    EXIT ();
}

void SmTr196Validator::GetLteBitStringArraryVals(const char* arrStringenums[], std::vector<std::string> elem, std::vector<u8> &value, u8 size)const
{
    ENTER ();

    arrSize = size;
    TRACE_PRINTF("Number of elements in StringArrayenum   is %d", arrSize);

 for (u32 idxelem=0; idxelem<elem.size(); idxelem++)
    {
            TRACE_PRINTF("Elem StringArrayenum at index [%d] is %s",idxelem,elem[idxelem].c_str());
            for(u32 idx=0; idx<arrSize; idx++)
            {
                    if((!elem[idxelem].empty())&&(!strcmp(elem[idxelem].c_str(),arrStringenums[idx])))
                    {
                            value.push_back(arrBitStringVals[idx]);
                    }
            }
    }

    EXIT ();
}

void SmTr196Validator::GetLteBitStringVals(const char* arrStringenums[], string elem, u8 &value, u8 size)const
{
    ENTER ();

    arrSize = size;
    TRACE_PRINTF("Number of elements in StringArrayenum   is %d", arrSize);

    TRACE_PRINTF("Elem received is %s",elem.c_str());
    
    for(u32 idx=0; idx<arrSize; idx++)
    {
       if((!elem.empty())&&(!strcmp(elem.c_str(),arrStringenums[idx])))
       {
          value = idx;
       }
    }

    EXIT ();
}

void SmTr196Validator::ExpandString(vector<string> & valueAsStringArray)
{
   ENTER();

   bool isNegative = false;

   for(u32 strIdx = 0; strIdx < valueAsStringArray.size(); strIdx++)
   {
      char digit[1];
      string str = valueAsStringArray[strIdx];
      u32 pos = 0;

      for(u32 dotPos = 0; dotPos < strlen(str.c_str()); dotPos++)
      {
         if((str[dotPos] == '.') && (str[dotPos+1] == '.'))
         {
            pos = dotPos;
            break;
         }
      }

      if(pos > 0)
      {
         s32 min = 0;
         for(u32 idx = 0; idx < pos; idx++)
         {
            digit[0] = str[idx];
            if(digit[0]  == '-')
            {
               isNegative = true;
            }

            min = min*10 + atoi(digit);
         }

         if(isNegative)
         {
            min = min * (-1);
            isNegative = false;
         }
         s32 max = 0;
         for(u32 idx = pos+2; idx < strlen(valueAsStringArray[strIdx].c_str()); idx++)
         {
            digit[0] = str[idx];
            if(digit[0]  == '-')
            {
               isNegative = true;
            }
            if(NULL != digit)
            {
               max = max*10 + ((u16)atoi(digit));
            }
         }

         if(isNegative)
         {
            max = max * (-1);
            isNegative = false;
         }

         valueAsStringArray.erase(valueAsStringArray.begin() + strIdx);
         s32 index = 0;
         u32 valIdx = 0;

         if(max < min )
         {
            return ;
         }
            for(valIdx = strIdx, index = min; index <= max; index++, valIdx++)
            {
               stringstream toString;
               toString << index;
               valueAsStringArray.insert(valueAsStringArray.begin() + valIdx,toString.str());
            }
      }
   }

   EXIT();
}
