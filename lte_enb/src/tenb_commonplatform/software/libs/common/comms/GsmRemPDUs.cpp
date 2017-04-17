///////////////////////////////////////////////////////////////////////////////
//
// GsmRemPDUs.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include "GsmRemPDUs.h"

using namespace threeway;
using namespace boost;
using namespace std;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

MessageBitstream::MessageBitstream(u8 *inMessage, u32 numBytes) :
    m_numBytes(numBytes), m_bitCounter(0)
{
   m_pMsg = new u8[numBytes];
   //TRACE_PRINTF("MessageBitstream::MessageBitstream numBytes = %d",numBytes);
   RSYS_ASSERT(m_pMsg);
   memmove(m_pMsg, inMessage, numBytes);
   ReverseBits();
}

MessageBitstream::~MessageBitstream()
{
   if (m_pMsg)
   {
      delete[] m_pMsg;
   }
}

u32 MessageBitstream::IncrementalBits(u32 numBits)
{
    u32 retVal = 0;
    s32 numBytes = numBits / 8;
    u32 currentByte = m_bitCounter / 8;
    u32 bitOffset;
    u8 utilityByte;

    RSYS_ASSERT((m_pMsg != NULL));
    //TRACE_PRINTF("Incremental bits start =  %d numBits = %d numBytes = %d",m_bitCounter,numBits,numBytes);
    do
    {
        if (numBytes > 1)
        {
            //TRACE_PRINTF("Incremental bits start 2 =  %d numBits = %d numBytes = %d",m_bitCounter,numBits,numBytes);
            //if we start not on the byte boundary, we must not straddle a byte boundary
            //we are now doing whole byte copies
            RSYS_ASSERT((numBits % 8) == 0);
            utilityByte = (u8) (m_pMsg[currentByte]);
            retVal |= utilityByte;
            retVal <<= 8;
            currentByte++;
            RSYS_ASSERT((currentByte < m_numBytes));
            numBits -= 8;
            m_bitCounter += 8;
        }
        else
        {
            bitOffset = m_bitCounter % 8;
            utilityByte = (m_pMsg[currentByte] >> bitOffset);
            u8 mask = (u8) (((u32) 1 << numBits) - 1);
            utilityByte &= mask;
            retVal += utilityByte;
            m_bitCounter += numBits;
        }
        numBytes--;
    } while (numBytes > 0);

    //TRACE_PRINTF("Incremental bits returns %04X ",retVal);

    return retVal;
}

void MessageBitstream::ReverseBits()
{
    u8 out = 0;
    u8 in;

    for (u32 byteCounter = 0; byteCounter < m_numBytes; byteCounter++)
    {
        in = m_pMsg[byteCounter];
        out = 0;
        //TRACE_PRINTF("In = %02X",in);
        for (u32 i = 0; i < 8; i++)
        {
            out <<= 1;
            out |= ((in & 1));
            in >>= 1;
        }

        //TRACE_PRINTF("bit shifted out = %02X",out);
        m_pMsg[byteCounter] = out;
    }
}

u32 MessageBitstream::IncrementalBCD(u32 numBits)
{
    u32 returnBCD = 0;
    RSYS_ASSERT(numBits > 0);
    RSYS_ASSERT((numBits % 4) == 0);

    u32 bitsProcessed = 0;
    while (bitsProcessed < numBits)
    {
        returnBCD *= 10;
        returnBCD += IncrementalBits(4);
        bitsProcessed += 4;
    }

    return returnBCD;
}

std::string MessageBitstream::GetStringRepresentation(void)
{
    std::string outstr;
    char convertbuff[3];
    u32 byteOffset = m_bitCounter / 8;

    for(u32 bCtr = byteOffset;bCtr < m_numBytes;bCtr++)
    {
        sprintf(convertbuff,"%02X",m_pMsg[bCtr]);
        outstr += convertbuff;
    }
    return outstr;
}

PDUBase::~PDUBase()
{
    //has to be defined 'out of line' duh! gcc!
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
bool GSMBCCHMessage::Translate(void)
{
    m_l2PseudoLength = m_pBitstream->IncrementalBits(8); //1
    m_rr_managementProtocolDiscriminator = m_pBitstream->IncrementalBits(4); //1.5
    m_skipIndicator = m_pBitstream->IncrementalBits(4); //2
    m_SIMessageType = m_pBitstream->IncrementalBits(8); //3
    CheckAlignment();
    //translate the SI message according to the type
    if (m_SIMessageType == SI3_MESSAGE_TYPE)
    {
        m_systemInformationType3Message.SetBitstreamAndTranslate(m_pBitstream);
    }
    else if (m_SIMessageType == SI2_MESSAGE_TYPE)
    {
        TRACE_PRINTF("SI2 message received");
        m_systemInformationType2Message.SetBitstreamAndTranslate(m_pBitstream);
    }
    else
    {
        //Don't do anything. We are not handling messages ither than SI2&3 yet
    }
    return true;
}

void GSMBCCHMessage::Display()
{
    ostringstream outstring;

    outstring << "Pseudo Length = " << m_l2PseudoLength << endl << "management Protocol Discriminator = " << m_rr_managementProtocolDiscriminator << endl
              << "skip Indicator = " << m_skipIndicator << endl << "Message Type = " << m_SIMessageType << endl;
    TRACE_PRINTF("%s",outstring.str().c_str());
    m_systemInformationType3Message.Display();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
bool SystemInformationType3Message::Translate(void)
{
    m_cellID = m_pBitstream->IncrementalBits(16); //5
    m_lac.SetBitstreamAndTranslate(m_pBitstream); //10
    m_controlChannelDescription.SetBitstreamAndTranslate(m_pBitstream); //13
    m_cellOptions.SetBitstreamAndTranslate(m_pBitstream); //14
    m_cellSelectionParameters.SetBitstreamAndTranslate(m_pBitstream); //16
    m_RACHControlParameters.SetBitstreamAndTranslate(m_pBitstream); //19
    m_SI3RestOctets = m_pBitstream->IncrementalBits(32); //23
    CheckAlignment();
    return true;
}

void SystemInformationType3Message::GenerateReportElement(ostringstream* inStr, u32 index)
{
    char mncString[4];
    snprintf(mncString, sizeof(mncString), "%02d", m_lac.GetMNC());
    mncString[sizeof(mncString) - 1] = '\0';
    char mccString[4];
    snprintf(mccString, sizeof(mccString), "%02d", m_lac.GetMCC());
    mccString[sizeof(mccString) - 1] = '\0';

    *inStr << "<ParameterValueStruct>"
        "<Name>Device.Services.X_NSN_COM_FAP.X_NSN_COM_FCEL.X_NSN_COM_ADJG." << index << ".AdjgCellId</Name>"
        "<Value>" << m_cellID << "</Value>"
        "</ParameterValueStruct>"
        "<ParameterValueStruct>"
        "<Name>Device.Services.X_NSN_COM_FAP.X_NSN_COM_FCEL.X_NSN_COM_ADJG." << index << ".LAC</Name>"
        "<Value>" << m_lac.GetLAC() << "</Value>"
        "</ParameterValueStruct>"
        "<ParameterValueStruct>"
        "<Name>Device.Services.X_NSN_COM_FAP.X_NSN_COM_FCEL.X_NSN_COM_ADJG." << index << ".AdjgMCC</Name>"
        "<Value>" << mccString << "</Value>"
        "</ParameterValueStruct>"
        "<ParameterValueStruct>"
        "<Name>Device.Services.X_NSN_COM_FAP.X_NSN_COM_FCEL.X_NSN_COM_ADJG." << index << ".AdjgMNC</Name>"
        "<Value>" << mncString << "</Value>"
        "</ParameterValueStruct>";

    //TRACE_PRINTF("SystemInformationType3Message to string = %s",(inStr->str()).c_str());
}

void SystemInformationType3Message::Display()
{
    ostringstream outstring;

    outstring << "cellID = " << m_cellID << endl;
    TRACE_PRINTF("%s",outstring.str().c_str());
    m_lac.Display();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
bool SystemInformationType2Message::Translate(void)
{
    CheckAlignment();
    m_stringRepresentation = m_pBitstream->GetStringRepresentation();
    TRACE_PRINTF("SystemInformationType2Message::Translate string = %s",m_stringRepresentation.c_str());
    return true;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CellSelectionParameters::Translate(void)
{
    m_MS_TXPWR_MAX_CCH = m_pBitstream->IncrementalBits(5);
    m_CELL_RESELECT_HYSTERESIS = m_pBitstream->IncrementalBits(3);
    m_RXLEV_ACCESS_MIN = m_pBitstream->IncrementalBits(6);
    m_NECI = m_pBitstream->IncrementalBits(1);
    m_ACS = m_pBitstream->IncrementalBits(1);
    CheckAlignment();
    return true;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
bool ControlChannelDescription::Translate(void)
{
    m_CCHCONF = m_pBitstream->IncrementalBits(3);
    m_BS_AG_BLKS_RES = m_pBitstream->IncrementalBits(3);
    m_ATT = m_pBitstream->IncrementalBits(1);
    m_MSCR = m_pBitstream->IncrementalBits(1);
    m_BS_PA_MFRMS = m_pBitstream->IncrementalBits(3);
    m_pBitstream->IncrementalPadding(2);
    m_CBQ3 = m_pBitstream->IncrementalBits(2);
    m_pBitstream->IncrementalPadding(1);
    m_timeoutvalue = m_pBitstream->IncrementalBits(8);
    CheckAlignment();
    return true;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
bool LocationAreaIdentificationMessage::Translate(void)
{
    m_MCC = m_pBitstream->IncrementalBCD(12);
    m_pBitstream->IncrementalPadding(4);
    m_MNC = m_pBitstream->IncrementalBCD(8);
    m_LAC = m_pBitstream->IncrementalBits(16);
    CheckAlignment();
    return true;
}

void LocationAreaIdentificationMessage::Display(void)
{
    ostringstream outstring;

    outstring << "MCC = " << m_MCC << endl << "MNC = " << m_MNC << endl << "LAC = " << m_LAC << endl;

    TRACE_PRINTF("%s",outstring.str().c_str());
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CellOptions::Translate(void)
{
    m_pBitstream->IncrementalPadding(1);
    m_PWRC = m_pBitstream->IncrementalBits(1);
    m_DTX = m_pBitstream->IncrementalBits(2);
    m_RADIO_LINK_TIMEOUT = m_pBitstream->IncrementalBits(4);
    CheckAlignment();
    return true;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
bool RACHControlParameters::Translate(void)
{
    m_RE = m_pBitstream->IncrementalBits(1);
    m_CELL_BARR_ACCESS = m_pBitstream->IncrementalBits(1);
    m_tx_integer = m_pBitstream->IncrementalBits(4);
    m_maxRetrans = m_pBitstream->IncrementalBits(2);
    m_octet3 = m_pBitstream->IncrementalBits(8);
    m_octet4 = m_pBitstream->IncrementalBits(8);
    CheckAlignment();
    return true;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

