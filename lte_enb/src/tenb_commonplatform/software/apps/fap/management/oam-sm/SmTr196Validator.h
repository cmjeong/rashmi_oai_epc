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
// SmTr196Validator.h
//
// Class for SmTr196Validator.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __SmTr196Validator_h_
#define __SmTr196Validator_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////
#include <vector>
#include <string.h>
#include <sstream>
///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class SmTr196Validator
{
private:
public:
    SmTr196Validator();
    virtual ~SmTr196Validator();

    static u32 arrSize; 
    virtual void GetLteU32enums(u32 arrU32enums[], u32 elem, u32 &pos)const;
    virtual void GetLteU32enums(u32 arrU32enums[], u32 elem, u16 &pos)const;
    virtual void GetLteU32enums(u32 arrU32enums[], u32 elem, u8 &pos)const;
    virtual void GetLteS32enums(s32 arrS32enums[], s32 elem, u32 &pos)const;
    virtual void GetLteS32enums(s32 arrS32enums[], s32 elem, u16 &pos)const;
    virtual void GetLteS32enums(s32 arrS32enums[], s32 elem, u8 &pos)const;
    virtual bool GetLteStringenums(const char* arrStringenums[], std::string elem, u8 &pos, u8 size)const;
    virtual void GetLteStringArrayenums(const char* arrStringenums[], std::vector<std::string> elem, std::vector<u8> &pos, u8 size)const;
    virtual void GetLteStringArrayenums(const char* arrStringenums[], std::vector<std::string> elem, std::vector<u32> &pos, u8 size)const;
    virtual void GetLteBitStringArraryVals (const char* arrStringenums[],std::vector<std::string> elem, std::vector<u8> &val, u8 size) const;

    static u32 arrAntennaInfo[4];
    static s32 arrPaInfo[9];
    static u32 arrAlphaInfo[9];
    static s32 arrdeltaPucchFormatInfo[4];
    static u32 arrdeltaPucchFormat1bInfo[4];
    static s32 arrdeltaPucchFormat2Info[5];
    static u32 arrRaPreamblesInfo[17];
    static u32 arrgroupASize[16];
    static u32 arrmsgSizeGroupA[5];
    static s32 arrpwrOffstGrpB[9];
    static u32 arrpowerRampingstep[5];
    static s32 arrinitRcvdTrgtPwr[17];
    static u32 arrpreambleTransMax[12];
    static u32 arrrarWindowSize[9];
    static u32 arrmacContResTimer[9];
    static u32 arrdrxOnDurTmrInfo[17];
    static u32 arrdrxInactvTmrInfo[23];
    static u32 arrdrxRetxTmrInfo[9];
    static u32 arrlongDrxCycleInfo[17];
    static u32 arrshortDrxCycleInfo[17];

    static u32 arrqHystInfo[17];
    static s32 arrsfInfo[5];
    static u32 arrtEvalulationInfo[6];
    static u32 arrtHystNormalInfo[6];
    static u32 arrtReselectionSfInfo[5];

    static u32 arrrsrpFltrCoeffInfo[16];
    static u32 arrrsrqFltrCoeffInfo[16];
    static u32 arrecnoFltrCoeffInfo[16];
    static u32 arrmaxHARQ_TxInfo[15];
    static u32 arrperiodicBSR_TimerInfo[15];
    static u32 arrretxBSR_TimerInfo[7];
    static u32 arrtpRetransmitInfo[56];
    static u32 arrpollPduInfo[9];
    static u32 arrpollByteInfo[16];
    static u32 arrmaxRetransThreshInfo[9]; 
    static u32 arrtimerReorderingInfo[32];
    static u32 arrtimerStatusProhibitInfo[57];

    static u32 arrt300Info[9];
    static u32 arrt301Info[9];
    static u32 arrt302Info[9];
    static u32 arrt304Info[8];
    static u32 arrccoT304Info[8];
    static u32 arrt310Info[8];
    static u32 arrn310Info[9];
    static u32 arrt311Info[8];
    static u32 arrn311Info[9];
    static u32 arrt320Info[8];

    static s32 arrqOffsetFreqInfo[32];
    static u32 arrtResetEutraSFInfo[5];

    static u32 arrtimeToTriggerInfo[17];
    static u32 arrreportIntervalInfo[14];
    static u8  arrBitStringVals[4];

    static const char* arrreportAmountInfo[10];
    static const char* arrduplexModeInfo[50];
    static const char* arrdlBandwidthInfo[50];
    static const char* arrcSrsInfo[50];
    static const char* arrintgAlgoInfo[50];
    static const char* arrciphAlgoInfo[50];
    static const char* arrumtsBandListInfo[50];
    static const char* arrdeltaShiftInfo[50];
    static const char* arrhoppingModeInfo[50];
    static const char* arrtriggerQtyInfo[50];
    static const char* arrreportQtyInfo[50];
    static const char* arrmeasQtyUtraFddInfo[50];
    static const char* arrInServiceHandlingInfo[50];
    static const char* arrlteAccessModeInfo[50];
    static const char* arrlteAccessMode[50];
    static const char* arrCdmaCellType[50];
    static const char* arrlteAccessBarringFactor[20];
    static const char* arrlteAccessBarringTime[10];

    static const char* arrAllowedMeasBandwidthInfo[6];
    static const char* arrQOffsetRangeInfo[31];
    static const char* arrNeighCellConfigInfo[4];
    static const char* csfbReportCfgVal[20];
    static const char* ecsfbReportCfgVal[20];
    static const char* arrmeasQtyCdma2k[50];  
    static const char* arrGeranBandInd[50];
    static const char* arrUtraTddMode[50];
    static const char* arrMeasQtyUtraTdd[50];
    static const char* arrAutoConfigTM[50];
    static const char* arrPreferredTransMode[50];

    virtual void GetLteBitStringVals(const char* arrStringenums[], std::string elem, u8 &value, u8 size)const;
    void ExpandString(std::vector<std::string> & valueAsStringArray);
    static u32 arrNeighBandwidth[7];
};
#endif
