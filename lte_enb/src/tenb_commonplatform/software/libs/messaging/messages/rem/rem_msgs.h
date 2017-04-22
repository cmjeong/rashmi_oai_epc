/**************************************************************************************************

     Name:     REM-APP

     Type:     C++ Header file

     Desc:     Consists of Classes for all incoming and outgoing messages for REM.
     	 	   Each class consists of serialisation and deserialisation member functions and
     	 	   member variables

     File:     rem_msgs.h

     Sid:      rem_msgs.h@@/main/tenb_commonplatform_H8PLUS/1 - Tue Feb  5 14:01:09 2013

     Prg:      Ambika S


**************************************************************************************************/

#ifndef REM_MSGS_H_
#define REM_MSGS_H_

///////////////////////////////////////////////////////////////////////////////////////////////////
//	  System Includes
///////////////////////////////////////////////////////////////////////////////////////////////////
#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

#include "rem_common.h"
#include "rem_interface.h"

#define REM_MAX_PCI_LIST        32

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//   @class CRemOamStartScanCmd
//
///////////////////////////////////////////////////////////////////////////////////////////////////
class CRemOamStartScanCmd : public threeway::Serialisable
{
	public:

	// Implement Serialisable pure virtuals.
        s32 Serialise(u8* data, u32 dataMaxBytes) const ;
    	u8 getScanType();
    	void setScanType(u8 remScanType);
    	u32 GetSerialisationId() const { return SERIALISATION_ID_REM_OAM_START_SCAN; };
    	std::string ToString() const {return std::string();};
    	bool DeSerialise(const u8* data,u32 dataLen);

    private:
    	u8 m_bScanType;

};

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//   @class CRemOamStartAbortCmd
//
///////////////////////////////////////////////////////////////////////////////////////////////////
class CRemOamAbortScanCmd : public threeway::Serialisable
{
	public:

	// Implement Serialisable pure virtuals.
    	bool DeSerialise(const u8* data, u32 dataLen){return true;};
    	s32 Serialise(u8* data, u32 dataMaxBytes) const {return (1);};
    	u32 GetSerialisationId() const { return SERIALISATION_ID_REM_OAM_ABORT_SCAN; };
    	std::string ToString() const {return std::string();};

    private:
    	u8 m_bScanType;

};

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//   @class CRemSonStartCarrExpScan
//
///////////////////////////////////////////////////////////////////////////////////////////////////
class CRemSonStartCarrExpScan : public threeway::Serialisable
{
	public:

       	//Implement Serialisable pure virtuals.

        bool DeSerialise(const u8* data, u32 dataLen);
        s32 Serialise(u8* data, u32 dataMaxBytes) const {return (1);};
        u8 getScanType();
        u32 GetSerialisationId() const { return SERIALISATION_ID_REM_SON_START_CARRIER_EXPRESS_SCAN; };
        std::string ToString() const {return std::string(); };
        u8 getEARFCNCount();
        u16* getEARFCNList();

        u8					m_bNumOfEarfcn;
        u16		 			m_usEARFCNList[REM_MAX_CARRIER_LIST];
        u16		 			m_usscanTimeOut;

    private:
};


///////////////////////////////////////////////////////////////////////////////////////////////////
//
//   @class CRemSonStartPciExpScan
//
///////////////////////////////////////////////////////////////////////////////////////////////////
class CRemSonStartPciExpScan : public threeway::Serialisable
{

	public:
    	//Implement Serialisable pure virtuals.
		bool DeSerialise(const u8* data, u32 dataLen);
		u8 getScanType();
        s32 Serialise(u8* data, u32 dataMaxBytes) const {return (1);};
        u32 GetSerialisationId() const { return SERIALISATION_ID_REM_SON_START_PCI_EXPRESS_SCAN; };
        std::string ToString() const {return std::string(); };

        u8		  		m_bNumOfPci;
        u16  			m_usPCIList[REM_MAX_PCI_LIST];
        u8		 		m_bscanTimeOut;

    private:

};

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//   @class CRemScanStatus
//
///////////////////////////////////////////////////////////////////////////////////////////////////
class CRemScanStatus : public threeway::Serialisable
{
	public:
        CRemScanStatus();
        virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
        virtual bool DeSerialise(const u8* data, u32 dataLen);
        // Constructor for Scan Status messages
        CRemScanStatus(std::string errString,u8 bScanType,u8 bScanStatus);
        u32 GetSerialisationId() const { return SERIALISATION_ID_REM_SCAN_STATUS; };
        virtual std::string ToString() const {return std::string();};

	u8 getScanType();
	u8 getScanStatus();
	std::string getErrString();

	private:
	u8      m_bScanType;
        u8      m_bScanStatus;
        std::string  m_strError;

};

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//   @class CRemSonCarrScanResult
//
///////////////////////////////////////////////////////////////////////////////////////////////////
class CRemSonCarrScanResult : public threeway::Serialisable
{
	public:

		virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
		virtual u32 GetSerialisationId() const { return SERIALISATION_ID_REM_SON_CARRIER_SCAN_RESULT; };
        virtual bool DeSerialise(const u8* data, u32 dataLen){return true;};
		virtual std::string ToString() const {return std::string();};

	private:
		__stRemMsgSonCarrierScanRes		 *m_stcarrscanres;

};

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//   @class CRemSonPciScanResult
//
///////////////////////////////////////////////////////////////////////////////////////////////////
class CRemSonPciScanResult : public threeway::Serialisable
{
	public:
        virtual bool DeSerialise(const u8* data, u32 dataLen){return true;};
		virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
		virtual u32 GetSerialisationId() const { return SERIALISATION_ID_REM_SON_PCI_SCAN_RESULT; };
		virtual std::string ToString() const {return std::string();};

	private:
		__stRemMsgSonPciScanRes          *m_stpciscanres;
};

#if 0
///////////////////////////////////////////////////////////////////////////////////////////////////
//
//   @class CRemLteScanResult
//
///////////////////////////////////////////////////////////////////////////////////////////////////
class CRemLteScanResult : public threeway::Serialisable
{
	public:
		virtual s32 Serialise(u8* data, u32 dataMaxBytes) const {return 1;};
		virtual u32 GetSerialisationId() const { return SERIALISATION_ID_REM_LTE_SCAN_RESULT; };
	        virtual bool DeSerialise(const u8* data, u32 dataLen){return true;};
		virtual std::string ToString() const {return std::string();};

	private:


};

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//   @class CRemWcdmaScanResult
//
///////////////////////////////////////////////////////////////////////////////////////////////////
class CRemWcdmaScanResult : public threeway::Serialisable
{
	public:

		virtual s32 Serialise(u8* data, u32 dataMaxBytes) const {return 1;};
        	virtual bool DeSerialise(const u8* data, u32 dataLen){return true;};
		virtual u32 GetSerialisationId() const { return SERIALISATION_ID_REM_WCDMA_SCAN_RESULT; };
		virtual std::string ToString() const {return std::string();};

	private:

};
#endif
#endif /* REM_MSGS_H_ */
