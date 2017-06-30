///////////////////////////////////////////////////////////////////////////////
//
// GsmRemPDUs.h
//
// TBD
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef GSMREMPDUS_H_
#define GSMREMPDUS_H_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <Radisys.h>
#include <system/Trace.h>
///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

/*namespace threeway
{*/

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

/**
 * Class to contain a binary bitstream in this case from a BCCH. Class contains methods to extract data from the stored bitstream. Each PDU has a reference to a MessageBitstream and can extract bits sequences from it
 */
class MessageBitstream
{
public:
    //construct with a pointer to a byte array bitstream (ond number of bytes thereof. Bits are in backwards bit endianess due to the way they are received in l1
    //MessageBitstream(u8 *inMessage,u32 numBytes):m_pMsg(inMessage),m_numBytes(numBytes),m_bitCounter(0){ReverseBits();}
    MessageBitstream(u8 *inMessage,u32 numBytes);
    virtual ~MessageBitstream();
    //extract numBits bits from the message stream, and increment the internal counter. Return value of the bits
    u32 IncrementalBits(u32 numBits);
    //Extract BCD field from message stream. BCD field is numBits ling. numBits must be an integer multiple of 4. Return result, increment internal counter
    u32 IncrementalBCD(u32 numBits);
    //Simply increment the internal counter to reflect padding in the PDU
    void IncrementalPadding(u32 numBits) {m_bitCounter+=numBits;}
    //Debugging tool that ensured that the internal counter lies on a byte boundary.
    bool CheckByteAligned(){return ((m_bitCounter % 8) == 0);}
    //Reverse bytecentric bit endianness of bitstream
    void  ReverseBits();
    //Give me a string representation of the bitstream
    std::string GetStringRepresentation(void);

private:
    //
    u8 *m_pMsg;
    u32 m_numBytes;
    u32 m_bitCounter;
    u32 GetBit(u32 bit) {return ((((m_pMsg[(bit / 8)]) >> (bit % 8)) & 1));}

};

//PDUBase class. Contains a member of type MessageBitstream which PDU data is extracted from. All derived classes contain either simple members e.g. u32 or members that are also derived from PDUBase.
//simple members
class PDUBase
{
public:
    PDUBase():m_pBitstream(NULL){};
    virtual ~PDUBase();
    /**
     * Do the extraction of data of the derived class from the bitstream.
     * \return success of operation
     */
    virtual bool Translate(void) = 0;
    /**
     * Set pointer to bitstream, and extract the relevant data. In the case of PDU nesting, we set this with the calling PDUs m_pBitstream
     * \param pointer to m_pBitstream type representing the raw data that the PDU will be extracted from
     * \return whether the operation has been performed successfully
     */
    bool SetBitstreamAndTranslate(MessageBitstream* pBitstream) {m_pBitstream = pBitstream; return(Translate());}
    /**
     * Simply check that at this point the MessageBitstream is byte aligned i.e. the bit pointer points to the start of an octet. This should be the case
     * when a Translate operation is complete. Really only a development check.
     */
    void CheckAlignment() {RSYS_ASSERT(m_pBitstream->CheckByteAligned());};
    /**
     * pointer to MessageBitstream type. Represents the raw data that the PDUs will be extracted from.
     */
    MessageBitstream* m_pBitstream;
private:

};

//the below PDUBase classes are derived from PDUBase and describe the SI3 message and its elements.
class RACHControlParameters : public PDUBase
{
public:
    RACHControlParameters():
    m_RE(0),
    m_CELL_BARR_ACCESS(0),
    m_tx_integer(0),
    m_maxRetrans(0),
    m_octet3(0),
    m_octet4(0) {};
    ~RACHControlParameters() {};
    /**
     * Do the extraction of data from the bitstream. Realisation of virtual function.
     * \return success or failure of operation
     */
    bool Translate(void);
private:
    u32 m_RE;
    u32 m_CELL_BARR_ACCESS;
    u32 m_tx_integer;
    u32 m_maxRetrans;
    u32 m_octet3;
    u32 m_octet4;
};

class CellSelectionParameters : public PDUBase
{
public:
    CellSelectionParameters():
        m_MS_TXPWR_MAX_CCH(0),
        m_CELL_RESELECT_HYSTERESIS(0),
        m_RXLEV_ACCESS_MIN(0),
        m_NECI(0),
        m_ACS(0)
        {};
    ~CellSelectionParameters() {}
    /**
     * Do the extraction of data from the bitstream. Realisation of virtual function.
     * \return success or failure of operation
     */
    bool Translate(void);
private:
    u32 m_MS_TXPWR_MAX_CCH;
    u32 m_CELL_RESELECT_HYSTERESIS;
    u32 m_RXLEV_ACCESS_MIN;
    u32 m_NECI;
    u32 m_ACS;
};

class CellOptions : public PDUBase
{
public:
    CellOptions():
        m_PWRC(0),
        m_DTX(0),
        m_RADIO_LINK_TIMEOUT(0)
    {};
    ~CellOptions() {};
    /**
     * Do the extraction of data from the bitstream. Realisation of virtual function.
     * \return success or failure of operation
     */
    bool Translate(void);
private:
    u32 m_PWRC;
    u32 m_DTX;
    u32 m_RADIO_LINK_TIMEOUT;
};

class ControlChannelDescription : public PDUBase
{
public :
    ControlChannelDescription():
    m_CCHCONF(0),
    m_BS_AG_BLKS_RES(0),
    m_ATT(0),
    m_MSCR(0),
    m_BS_PA_MFRMS(0),
    m_CBQ3(0),
    m_timeoutvalue(0)
    {};
    ~ControlChannelDescription() {};
    /**
     * Do the extraction of data from the bitstream. Realisation of virtual function.
     * \return success or failure of operation
     */
    bool Translate(void);
private :
    u32 m_CCHCONF;
    u32 m_BS_AG_BLKS_RES;
    u32 m_ATT;
    u32 m_MSCR;
    u32 m_BS_PA_MFRMS;
    u32 m_CBQ3;
    u32 m_timeoutvalue;
};

class LocationAreaIdentificationMessage : public PDUBase
{
public:
    LocationAreaIdentificationMessage():
        m_MCC(0),
        m_MNC(0),
        m_LAC(0)
        {};
    ~LocationAreaIdentificationMessage() {};
    /**
     * Do the extraction of data from the bitstream. Realisation of virtual function.
     * \return success or failure of operation
     */
    bool Translate(void);
    /**
     * Display members to trace
     */
    void Display(void);
    /**
     * Accessors
     */
    u32 GetMCC() {return m_MCC;}
    u32 GetMNC() {return m_MNC;}
    u32 GetLAC() {return m_LAC;}
private:
    u32 m_MCC;
    u32 m_MNC;
    u32 m_LAC;
};

class SystemInformationType3Message : public PDUBase
{
public:
    SystemInformationType3Message():
        m_cellID(0),
        m_SI3RestOctets(0)
        {};
    ~SystemInformationType3Message() {};
    /**
     * Do the extraction of data from the bitstream. Realisation of virtual function.
     * \return success or failure of operation
     */
    bool Translate(void);
    /**
      * Display members to trace
      */
    void Display(void);
    /**
     * Generate the .xml string for the indexth GSM cell.
     */
    void GenerateReportElement(std::ostringstream* inStr, u32 index);
    /**
     * Accessors
     */
    u32 GetMCC() {return m_lac.GetMCC();}
    u32 GetMNC() {return m_lac.GetMNC();}
    u32 GetCellID() {return m_cellID;}
    u32 GetLAC() {return m_lac.GetLAC();}
private:
    u32 m_cellID;
    LocationAreaIdentificationMessage m_lac;
    ControlChannelDescription m_controlChannelDescription;
    CellOptions m_cellOptions;
    CellSelectionParameters m_cellSelectionParameters;
    RACHControlParameters m_RACHControlParameters;
    u32 m_SI3RestOctets;
};

class SystemInformationType2Message : public PDUBase
{
public:
    SystemInformationType2Message() {};
    ~SystemInformationType2Message() {};
    /**
     * Do the extraction of data from the bitstream. Realisation of virtual function.
     * \return success or failure of operation
     */
    bool Translate(void);
    /**
      * Display members to trace
      */
    void Display(void);
    //Generate the .xml string for the indexth GSM cell.
    void GenerateReportElement(std::ostringstream* inStr, u32 index) {};
    /**
     * Accessor
     */
    std::string GetStringRepresentation(void) {return m_stringRepresentation;}
private:
    /**
     * String representation of SystemInformationType2Message data (for CellXion)(
     */
    std::string m_stringRepresentation;
};


class GSMBCCHMessage : public PDUBase
{
public:
    static const u8 NUM_SI_MESSAGES = 17;
    static const u8 SI8_MESSAGE_TYPE = 0x18;
    static const u8 SI1_MESSAGE_TYPE = 0x19;
    static const u8 SI2_MESSAGE_TYPE = 0x1A;
    static const u8 SI3_MESSAGE_TYPE = 0x1B;
    static const u8 SI4_MESSAGE_TYPE = 0x1C;
    static const u8 SI5_MESSAGE_TYPE = 0x1D;
    static const u8 SI6_MESSAGE_TYPE = 0x1E;
    static const u8 SI7_MESSAGE_TYPE = 0x1F;
    static const u8 SI2BIS_MESSAGE_TYPE = 0x02;
    static const u8 SI2TER_MESSAGE_TYPE = 0x03;
    static const u8 SI2QUARTER_MESSAGE_TYPE = 0x07;
    static const u8 SI5BIS_MESSAGE_TYPE = 0x05;
    static const u8 SI5TER_MESSAGE_TYPE = 0x06;
    static const u8 SI9_MESSAGE_TYPE = 0x04;
    static const u8 SI13_MESSAGE_TYPE = 0x00;
    static const u8 SI16_MESSAGE_TYPE = 0x3D;
    static const u8 SI17_MESSAGE_TYPE = 0x3E;
    static const u8 NO_MESSAGE_TYPE = 0xFF;

public:
     GSMBCCHMessage():
             m_l2PseudoLength(0),
             m_rr_managementProtocolDiscriminator(0),
             m_skipIndicator(0),
             m_SIMessageType(0)
             {};
     ~GSMBCCHMessage() {};
     /**
      * Do the extraction of data from the bitstream. Realisation of virtual function.
      * \return success or failure of operation
      */
     bool Translate(void);
     //debugging display
     void Display(void);
     /**
      * Accessors
      */
     u8 GetSIMessageType() {return m_SIMessageType;}
     SystemInformationType3Message& GetSI3Message(void) {return m_systemInformationType3Message;}
     SystemInformationType2Message& GetSI2Message(void) {return m_systemInformationType2Message;}
private:
         u32 m_l2PseudoLength;
         u32 m_rr_managementProtocolDiscriminator;
         u32 m_skipIndicator;
         u32 m_SIMessageType;
         SystemInformationType3Message m_systemInformationType3Message;
         SystemInformationType2Message m_systemInformationType2Message;
};
//}

#endif
