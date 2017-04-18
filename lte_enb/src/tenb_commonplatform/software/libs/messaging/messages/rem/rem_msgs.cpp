/**************************************************************************************************

     Name:     REM-APP

     Type:     C++ Header file

     Desc:     Consists of Serialisation and Deserialisation functions for REM Messages

     File:     rem_msgs.cpp

     Sid:      rem_msgs.cpp@@/main/tenb_commonplatform_H8PLUS/1 - Tue Feb  5 14:01:09 2013

     Prg:      Ambika S

**************************************************************************************************/


///////////////////////////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <system/Trace.h>
#include <system/SerialisationUtils.h>


///////////////////////////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////////////////////////
#include "rem_msgs.h"


///////////////////////////////////////////////////////////////////////////////////////////////////
// @ param[in]  : *data - pointer to u8
//				   dataLen - u32
// This is the deserialise function for the incoming
// OAM START SCAN COMMAND message from OAM
//
///////////////////////////////////////////////////////////////////////////////////////////////////
bool CRemOamStartScanCmd::DeSerialise(const u8* data, u32 dataLen)
{
    TRACE_MSG("CRemOamStartScanCmd::DeSerialise");
	if (dataLen < sizeof(u8))
	{
		//remLog(REM_TRACE_WARNING,"Invalid Data Length");
		return false;
	}

    DeSerialiseIt(m_bScanType, data);

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// @ param[in]  : *data - pointer to u8
//                                 dataLen - u32
// This is the Serialise function for the incoming
// OAM START SCAN COMMAND message from OAM
//
///////////////////////////////////////////////////////////////////////////////////////////////////
s32 CRemOamStartScanCmd::Serialise(u8* data, u32 dataMaxBytes) const
{
    u8* serialisedData = data;

    SerialiseIt(m_bScanType, serialisedData);
    return (1);

}

///////////////////////////////////////////////////////////////////////////////////////////////////
// @ param[in]  : void
//
// This function sets the scan type from the incoming
// OAM START SCAN COMMAND message
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void CRemOamStartScanCmd::setScanType(u8 remScanType)
{
	TRACE_MSG("CRemOamStartScanCmd::setScanType");
	m_bScanType = remScanType;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// @ param[in]  : void
//
// This function gets the scan type from the incoming
// OAM START SCAN COMMAND message
//
///////////////////////////////////////////////////////////////////////////////////////////////////
u8 CRemOamStartScanCmd::getScanType()
{
	TRACE_MSG("CRemOamStartScanCmd::getScanType");
	return m_bScanType;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// @ param[in]  : data - pointer to u8
//				  dataLen - u32
// This is the deserialise function for the incoming START CARRIER
// EXPRESS SCAN message from SON
//
///////////////////////////////////////////////////////////////////////////////////////////////////
bool CRemSonStartCarrExpScan::DeSerialise(const u8* data, u32 dataLen)
{
	u32 uiPayLoadLen = sizeof(m_usscanTimeOut) + sizeof(m_bNumOfEarfcn);

	if (dataLen < uiPayLoadLen )
	{
		//remLog(REM_TRACE_WARNING,"Invalid Data Length");
		return 	false;
	}

    DeSerialiseIt(m_usscanTimeOut, data);
    DeSerialiseIt(m_bNumOfEarfcn, data);

    if((dataLen - uiPayLoadLen) < (m_bNumOfEarfcn * sizeof(u8)))
    {
    	//remLog(REM_TRACE_WARNING,"Invalid Data Length");
    	return false;
    }

    for(u8 index=0;index < m_bNumOfEarfcn ; index++)
    	DeSerialiseIt(m_usEARFCNList[index], data);

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// @ param[in]  : void
//
// This function gets the EARFCN count from the incoming 
// SON CARRIER EXPRESS SCAN COMMAND message
//
///////////////////////////////////////////////////////////////////////////////////////////////////
u8 CRemSonStartCarrExpScan::getEARFCNCount()
{
    TRACE_MSG("CRemSonStartCarrExpScan::getEARFCNCount");
    return m_bNumOfEarfcn;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// @ param[in]  : void
//
// This function gets the EARFCN list from the incoming
// SON CARRIER EXPRESS SCAN COMMAND message
//
///////////////////////////////////////////////////////////////////////////////////////////////////
u16* CRemSonStartCarrExpScan::getEARFCNList()
{
	return	m_usEARFCNList;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// @ param[in]  : data - pointer to u8
//				  dataLen - u32
// This is the deserialise function for the incoming START PCI
// EXPRESS SCAN message from SON
//
///////////////////////////////////////////////////////////////////////////////////////////////////
bool CRemSonStartPciExpScan::DeSerialise(const u8* data, u32 dataLen)
{
	u32 uiPayLoadLen = sizeof(m_bscanTimeOut) + sizeof(m_bNumOfPci);
    if (dataLen < uiPayLoadLen)
    {
    	//remLog(REM_TRACE_WARNING,"Invalid Data Length");
    	return false;
    }

    DeSerialiseIt(m_bscanTimeOut, data);
    DeSerialiseIt(m_bNumOfPci, data);

    if((dataLen - uiPayLoadLen) < (m_bNumOfPci * sizeof(u8)))
    {
    	//remLog(REM_TRACE_WARNING,"Invalid Data Length");
    	return false;
    }

    for(u8 index=0;index < m_bNumOfPci ; index++)
       	DeSerialiseIt(m_usPCIList[index], data);

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// @ param[in]  : data - pointer to u8
//				  dataMaxBytes - u32
// This is the serialise function for the REM SCAN STATUS MESSAGE
//
///////////////////////////////////////////////////////////////////////////////////////////////////
s32 CRemScanStatus::Serialise(u8* data, u32 dataMaxBytes) const
{
    // Serialise all the members.
    TRACE_MSG("CRemScanStatus::Serialise");

    u8* serialisedData = data;

    SerialiseIt(m_bScanType, serialisedData);
    SerialiseIt(m_bScanStatus, serialisedData);
    SerialiseIt((u16)(m_strError.length()), serialisedData);
    SerialiseIt(m_strError, serialisedData);

    return (serialisedData - data);
}
CRemScanStatus::CRemScanStatus()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////
// @ param[in]  : data - pointer to u8
//                                dataMaxBytes - u32
// This is the deserialise function for the REM SCAN STATUS Message
//
///////////////////////////////////////////////////////////////////////////////////////////////////
bool CRemScanStatus::DeSerialise(const u8* data, u32 dataLen)
{
    TRACE_MSG("CRemScanStatus::DeSerialise");
    /*u32 uiPayLoadLen = sizeof(m_bScanType)+sizeof(m_bScanStatus)+ sizeof(u16);
    if (dataLen < uiPayLoadLen)
    {
        TRACE_MSG("CRemScanStatus::DeSerialise:Null");
        //remLog(REM_TRACE_WARNING,"Invalid Data Length");
        return false;
    }*/

    u16 usStrLen = 0;
    DeSerialiseIt(m_bScanType, data);
    DeSerialiseIt(m_bScanStatus, data);
    DeSerialiseIt(usStrLen, data);
    DeSerialiseIt(m_strError, data,usStrLen);

    return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// @ param[in]  :
//
// This is the constructor function that populates REM SCAN STATUS MESSAGE
//
///////////////////////////////////////////////////////////////////////////////////////////////////
CRemScanStatus::CRemScanStatus(std::string strError,u8 bScanType,u8 bScanStatus)
{
	m_strError = strError;
	m_bScanType = (__enSupportedRAT)bScanType;
	m_bScanStatus = (__enRemScanStatus)bScanStatus;
}


u8 CRemScanStatus::getScanType()
{
	return m_bScanType;
}

u8 CRemScanStatus::getScanStatus()
{
	return m_bScanStatus;
}

std::string CRemScanStatus::getErrString()
{
	return m_strError;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
// @ param[in]  : data, dataMaxBytes
//
// This is the serialise function for the SON CARRIER SCAN RESULT Message
//
///////////////////////////////////////////////////////////////////////////////////////////////////
s32 CRemSonCarrScanResult::Serialise(u8* data, u32 dataMaxBytes) const
{
	u8* serialisedData = data;
	u32 uiExpPayLoadLen = sizeof(m_stcarrscanres->enScanStatus) +
						 sizeof(m_stcarrscanres->bNumRssi) +
						 ((m_stcarrscanres->bNumRssi)* sizeof(m_stcarrscanres->sNRssi))+
						 (m_stcarrscanres->strErrorDeatails.length());
	if(dataMaxBytes < uiExpPayLoadLen )
	{
		//remLog(REM_TRACE_WARNING,"Invalid Data Length");
		return 0;
	}

	SerialiseIt(m_stcarrscanres->enScanStatus,serialisedData);
	SerialiseIt(m_stcarrscanres->bNumRssi,serialisedData);
	SerialiseIt(&(m_stcarrscanres->strErrorDeatails),serialisedData);

	for(u8 index=0;index<m_stcarrscanres->bNumRssi;index++)
		SerialiseIt(m_stcarrscanres->sNRssi,serialisedData);

	return (1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// @ param[in]  : data, dataMaxBytes
//
// This is the serialise function for the SON PCI SCAN RESULT Message
//
///////////////////////////////////////////////////////////////////////////////////////////////////
s32 CRemSonPciScanResult::Serialise(u8* data, u32 dataMaxBytes) const
{
	u8* serialisedData = data;
	u32 uiExpPayLoadLen = sizeof(m_stpciscanres->enScanStatus) +
						 sizeof(m_stpciscanres->bNumRsrp) +
						 ((m_stpciscanres->bNumRsrp)* sizeof(m_stpciscanres->sNRsrp))+
						 (m_stpciscanres->strErrorDeatils.length());
	if(dataMaxBytes < uiExpPayLoadLen )
	{
		//remLog(REM_TRACE_WARNING,"Invalid Data Length");
		return 0;
	}

	SerialiseIt(m_stpciscanres->enScanStatus,serialisedData);
	SerialiseIt(m_stpciscanres->bNumRsrp,serialisedData);
	SerialiseIt(&(m_stpciscanres->strErrorDeatils),serialisedData);

	for(u8 index=0;index<m_stpciscanres->bNumRsrp;index++)
		SerialiseIt(m_stpciscanres->sNRsrp,serialisedData);

	return (1);
}


