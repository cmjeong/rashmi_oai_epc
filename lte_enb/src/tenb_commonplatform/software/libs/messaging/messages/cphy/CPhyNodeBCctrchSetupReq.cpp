///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBCctrchSetupReq.cpp 7696 2008-09-10 10:29:53Z manderson $
//
// See header file for documentation.
//
// Copyright radisys Inc
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <system/Trace.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CPhyNodeBCctrchSetupReq.h"
#include "FapUserLimits.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyNodeBCctrchSetupReq::CPhyNodeBCctrchSetupReq ()
{
    bzero (&m_cctrchSetup, sizeof (CphyNodeBCctrchSetupReq));
}

CPhyNodeBCctrchSetupReq::CPhyNodeBCctrchSetupReq (uint8_t ueNumber, uint32_t instanceId)
{
    bzero (&m_cctrchSetup, sizeof (CphyNodeBCctrchSetupReq));
    m_cctrchSetup.ue = ueNumber;
    m_cctrchSetup.instanceId = instanceId;
    m_cctrchSetup.actTime.now = true;
    m_cctrchSetup.Tdpch = 0;
    m_cctrchSetup.sync = L1_SYNC_A;
}

CPhyNodeBCctrchSetupReq::CPhyNodeBCctrchSetupReq (uint8_t ueNumber, uint32_t instanceId, uint16_t activationTime)
{
    bzero (&m_cctrchSetup, sizeof (CphyNodeBCctrchSetupReq));
    m_cctrchSetup.ue = ueNumber;
    m_cctrchSetup.instanceId = instanceId;
    m_cctrchSetup.actTime.now = false;
    m_cctrchSetup.actTime.sfn = activationTime;
    m_cctrchSetup.Tdpch = 0;
    m_cctrchSetup.sync = L1_SYNC_A;
}

CPhyNodeBCctrchSetupReq::CPhyNodeBCctrchSetupReq(const CphyNodeBCctrchSetupReq &cctrchSetup)
{
    memcpy (&m_cctrchSetup, &cctrchSetup, sizeof (CphyNodeBCctrchSetupReq));
}

u8 CPhyNodeBCctrchSetupReq::AddUplinkTrch ()
{
    u8 trchIndex = m_cctrchSetup.ulCctrch.nTrch++;
    return trchIndex;
}

void CPhyNodeBCctrchSetupReq::ConfigureUplinkTrch (u8 trchIndex, uint8_t tti, coding_scheme_t coding, crc_length_t crc, uint8_t rmAttr, uint8_t macHeaderBit)
{
    m_cctrchSetup.ulCctrch.trch[trchIndex].tti = tti;
    m_cctrchSetup.ulCctrch.trch[trchIndex].coding = coding;
    m_cctrchSetup.ulCctrch.trch[trchIndex].crc = crc;
    m_cctrchSetup.ulCctrch.trch[trchIndex].rmAttr = rmAttr;
    // TODO What's this MAC Header bit then?
    m_cctrchSetup.ulCctrch.trch[trchIndex].macHeaderBit = macHeaderBit;
}

void CPhyNodeBCctrchSetupReq::ConfigureUplinkTransportFormat (u8 trchIndex, uint8_t blockCount, uint16_t blockSize)
{
    u8 tfsIndex = m_cctrchSetup.ulCctrch.trch[trchIndex].nTf;
    m_cctrchSetup.ulCctrch.trch[trchIndex].nTf++;

    m_cctrchSetup.ulCctrch.trch[trchIndex].tfs[tfsIndex].blockCount = blockCount;
    m_cctrchSetup.ulCctrch.trch[trchIndex].tfs[tfsIndex].blockSize = blockSize;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// void CPhyNodeBCctrchSetupReq::ConfigureUplinkTfcs (u8 trch, u8 tfci, u8 tfi)
// trch - Values depends on RAB. Examples are..
//             Voice - (0...3) => 4 with (1 TrCh for SRBs) + (3 TrCh for Class A, B, C )
//             PS 64 - (0,1)   => 2 with (1 TrCh for SRBs) + (1 for PS 64)
//        Voice+Ps64 - (0...4) => 5 with (1 TrCh for SRBs) + (3 TrCh for Class A,B,C AMR bits) + (1 for PS64)
//        Order depends on the manner in which the transport channel id is assigned
//        in ConfigureUplinkCctrch(). Better to follow the order as in 34.108 given in TFCS for
//        possible Radio Bearer combinations.
//
// tfci - TFCI value
//
// tfi  - Values depend on number of TFs. Example in Voice(1,2 for SRBs) and ()
//
//////////////////////////////////////////////////////////////////////////////////////////////////
void CPhyNodeBCctrchSetupReq::ConfigureUplinkTfcs (u8 trch, u8 tfci, u8 tfi)
{
    RSYS_ASSERT(tfci < MAX_L1_TFCI);
    RSYS_ASSERT(trch < MAX_L1_TRCH);
    RSYS_ASSERT(tfi  < MAX_L1_TF);
    m_cctrchSetup.ulCctrch.tfIdx[trch][tfci] = tfi;

    if(tfci >= m_cctrchSetup.ulCctrch.nTfci)
        m_cctrchSetup.ulCctrch.nTfci = tfci + 1;
}

u8 CPhyNodeBCctrchSetupReq::AddDownlinkTrch ()
{
    u8 trchIndex = m_cctrchSetup.dlCctrch.nTrch++;
    return trchIndex;
}

void CPhyNodeBCctrchSetupReq::ConfigureDownlinkTrch (u8 trchIndex, uint8_t tti, coding_scheme_t coding, crc_length_t crc, uint8_t rmAttr)
{
    m_cctrchSetup.dlCctrch.trch[trchIndex].tti = tti;
    m_cctrchSetup.dlCctrch.trch[trchIndex].coding = coding;
    m_cctrchSetup.dlCctrch.trch[trchIndex].crc = crc;
    m_cctrchSetup.dlCctrch.trch[trchIndex].rmAttr = rmAttr;
}

void CPhyNodeBCctrchSetupReq::ConfigureDownlinkTransportFormat (u8 trchIndex, uint8_t blockCount, uint16_t blockSize)
{
    u8 tfsIndex = m_cctrchSetup.dlCctrch.trch[trchIndex].nTf;
    m_cctrchSetup.dlCctrch.trch[trchIndex].nTf++;

    m_cctrchSetup.dlCctrch.trch[trchIndex].tfs[tfsIndex].blockCount = blockCount;
    m_cctrchSetup.dlCctrch.trch[trchIndex].tfs[tfsIndex].blockSize = blockSize;
}

void CPhyNodeBCctrchSetupReq::ConfigureDownlinkTfcs (u8 trch, u8 tfci, u8 tfi)
{
    RSYS_ASSERT(tfci < MAX_L1_TFCI);
    RSYS_ASSERT(trch < MAX_L1_TRCH);
    RSYS_ASSERT(tfi  < MAX_L1_TF);
    m_cctrchSetup.dlCctrch.tfIdx[trch][tfci] = tfi;

    if(tfci >= m_cctrchSetup.dlCctrch.nTfci)
        m_cctrchSetup.dlCctrch.nTfci = tfci + 1;
}

void CPhyNodeBCctrchSetupReq::ConfigureUplinkPhy (upsc_t psc, spreading_factor_t minSf, uint8_t punctureLimit100, uint16_t maxDpdchBitsPerFrame)
{
    m_cctrchSetup.ulPhy.psc = psc;                                   /**< Uplink primary scrambling code. */
    m_cctrchSetup.ulPhy.minSf = minSf;                               /**< Minimum spreading factor. */
    m_cctrchSetup.ulPhy.punctureLimit100 = punctureLimit100;         /**< Puncturing limit * 100. */
    m_cctrchSetup.ulPhy.maxDpdchBitsPerFrame = maxDpdchBitsPerFrame; /**< Max DPDCH bits per frame. */
}

void CPhyNodeBCctrchSetupReq::ConfigureDownlinkPhy (bool dtxPositionFixed, spreading_factor_t sf, uint8_t ovsf, uint16_t tfciBitsPerSlot, uint16_t tpcBitsPerSlot, uint16_t pilotBitsPerSlot, uint16_t dataBitsPerSlot, uint16_t dataBitsPerFrame)
{
    m_cctrchSetup.dlPhy.dtxPositionFixed = dtxPositionFixed;     /**< Whether DTX bits are fixed or flexible. */
    m_cctrchSetup.dlPhy.sf = sf;                                 /**< Spreading factor. */
    m_cctrchSetup.dlPhy.ovsf = ovsf;                             /**< OVSF code number. */

    /* DPCCH Parameters */
    m_cctrchSetup.dlPhy.tfciBitsPerSlot = tfciBitsPerSlot;
    m_cctrchSetup.dlPhy.tpcBitsPerSlot = tpcBitsPerSlot;
    m_cctrchSetup.dlPhy.pilotBitsPerSlot = pilotBitsPerSlot;

    /* DPDCH Parameters */
    m_cctrchSetup.dlPhy.dataBitsPerSlot = dataBitsPerSlot;
    m_cctrchSetup.dlPhy.dataBitsPerFrame = dataBitsPerFrame;
}

void CPhyNodeBCctrchSetupReq::ConfigureHsupa (tti_length_t ttiLen)
{
    m_cctrchSetup.hsupa.active = true;
    m_cctrchSetup.hsupa.ttiLen = ttiLen;
}

void CPhyNodeBCctrchSetupReq::ConfigureHsupaUl (uint8_t plNonMax, uint8_t trnsBlockTabId,
                                                uint8_t ueCat, spreading_factor_t minSf, bool rvFlag)
{
    m_cctrchSetup.hsupa.ul.plNonMax = plNonMax;
    m_cctrchSetup.hsupa.ul.trnsBlockTabId = trnsBlockTabId;
    m_cctrchSetup.hsupa.ul.minSf = minSf;
    m_cctrchSetup.hsupa.ul.ueCat = ueCat;
    m_cctrchSetup.hsupa.ul.rvFlag = rvFlag;
}

void CPhyNodeBCctrchSetupReq::ConfigureHsupaDl (uint8_t ehichSig, uint8_t ehichSpreadingCode, uint16_t ernti)
{
    m_cctrchSetup.hsupa.dl.ehichSig = ehichSig;
    m_cctrchSetup.hsupa.dl.ehichSpreadingCode = ehichSpreadingCode;
    m_cctrchSetup.hsupa.dl.ernti = ernti;
}

void CPhyNodeBCctrchSetupReq::ConfigurePowerControl (uint16_t const * const blerToAchieve)
{
    u8 i;
    m_cctrchSetup.olpc.enable = true;
    m_cctrchSetup.olpc.perTrchBler = true;
    for(i = 0; i < MAX_L1_TRCH; i++)
        m_cctrchSetup.olpc.trchBlerToAchieve[i] = blerToAchieve[i];
}

void CPhyNodeBCctrchSetupReq::ConfigurePowerControl (uint16_t const * const blerToAchieve, uint16_t const hsupaBler)
{
    u8 i;
    m_cctrchSetup.olpc.enable = true;
    m_cctrchSetup.olpc.perTrchBler = true;
    for(i = 0; i < MAX_L1_TRCH; i++)
        m_cctrchSetup.olpc.trchBlerToAchieve[i] = blerToAchieve[i];
    m_cctrchSetup.olpc.hsupaBler = hsupaBler;
}

void CPhyNodeBCctrchSetupReq::ConfigureHsdpa (bool active)
{
    m_cctrchSetup.hsdpa.active = active;
}

void CPhyNodeBCctrchSetupReq::ConfigureSync(l1_sync_procedure_t procedure)
{
    m_cctrchSetup.sync = procedure;
}

s32 CPhyNodeBCctrchSetupReq::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CPhyNodeBCctrchSetupReq_Serialise(&m_cctrchSetup, data, dataMaxBytes);
}

bool CPhyNodeBCctrchSetupReq::DeSerialise(const u8* data, u32 dataLen)
{
    if(CPhyNodeBCctrchSetupReq_Deserialise(data, dataLen, &m_cctrchSetup) < 0)
        return false;
    else
        return true;
}

u32 CPhyNodeBCctrchSetupReq::GetStruct(CphyMessageData *const msg)
{
    msg->nodeBCctrchSetupReq = &m_cctrchSetup;

    return GetSerialisationId();
}

string CPhyNodeBCctrchSetupReq::ToBriefString() const
{
    ostringstream stream;

    stream << "  ue=" << (u16)m_cctrchSetup.ue << " sfn=";
    if(m_cctrchSetup.actTime.now)
      stream << "now";
    else
      stream << (u16)m_cctrchSetup.actTime.sfn;

    return(stream.str());
}

string CPhyNodeBCctrchSetupReq::ToString() const
{
    ostringstream stream;

    stream << "CPhyNodeBCctrchSetupReq v2" << endl;

    stream << "{ actTime=" << endl;
    stream << "  { now=" << (m_cctrchSetup.actTime.now ? "yes" : "no") << endl;
    stream << "    sfn=" << (u16)m_cctrchSetup.actTime.sfn << endl;
    stream << "  }" << endl;

    stream << "  ue=" << (u16)m_cctrchSetup.ue << endl;
    stream << "  instanceId=" << m_cctrchSetup.instanceId;
    stream << "  Tdpch=" << (u16)m_cctrchSetup.Tdpch << endl;

    stream << "{ ul-cctrch=" << endl;
    stream << ToString (m_cctrchSetup.ulCctrch);
    stream << "}" << endl;

    stream << "{ dl-cctrch=" << endl;
    stream << ToString (m_cctrchSetup.dlCctrch);
    stream << "}" << endl;

    stream << "{ ul-phy=" << endl;
    stream << "   upsc=" << m_cctrchSetup.ulPhy.psc << endl;
    stream << "   minSf=" << SfToString (m_cctrchSetup.ulPhy.minSf) << endl;

    stream << "   punctureLimit=" << (float) (m_cctrchSetup.ulPhy.punctureLimit100 / 100.0) << endl;
    stream << "   maxDpdchBitsPerFrame=" << m_cctrchSetup.ulPhy.maxDpdchBitsPerFrame << endl;
    stream << "}" << endl;

    stream << "{ dl-phy=" << endl;
    stream << "   dtxPositionFixed=" << (u16) m_cctrchSetup.dlPhy.dtxPositionFixed << endl;
    stream << "   sf=" << SfToString (m_cctrchSetup.dlPhy.sf) << endl;
    stream << "   ovsf=" << (u16) m_cctrchSetup.dlPhy.ovsf << endl;
    stream << "   tfciBitsPerSlot=" << m_cctrchSetup.dlPhy.tfciBitsPerSlot << endl;
    stream << "   tpcBitsPerSlot=" << m_cctrchSetup.dlPhy.tpcBitsPerSlot << endl;
    stream << "   pilotBitsPerSlot=" << m_cctrchSetup.dlPhy.pilotBitsPerSlot << endl;
    stream << "   dataBitsPerSlot=" << m_cctrchSetup.dlPhy.dataBitsPerSlot << endl;
    stream << "   dataBitsPerFrame=" << m_cctrchSetup.dlPhy.dataBitsPerFrame << endl;
    stream << "}" << endl;

    stream << "{ olpc=" << endl;
    stream << ToString (m_cctrchSetup.olpc);
    stream << "}" << endl;

    stream << "  sync=" << (u16)m_cctrchSetup.sync << endl;
    stream << "  { ul-hsdpa=" << endl;
    stream << ToString (m_cctrchSetup.hsdpa);
    stream << "  }" << endl;
    stream << "  { ul-hsupa=" << endl;
    stream << ToString (m_cctrchSetup.hsupa);
    stream << "  }" << endl;
    stream << "}" << endl;

    return(stream.str());
}

string CPhyNodeBCctrchSetupReq::ToString (const l1_cctrch_param_t &cctrchParam) const
{
    ostringstream stream;

    stream << "  { nTrch=" << (u16) cctrchParam.nTrch << endl;
    for (u16 i=0;i<cctrchParam.nTrch;i++)
    {
        stream << "    { trch=" << i << endl;
        stream << "      { nTf=" << (u16) cctrchParam.trch[i].nTf << endl;
        stream << "      { tti=" << (u16) (cctrchParam.trch[i].tti * 10) << endl;
        stream << "      { coding=" << CodingToString (cctrchParam.trch[i].coding) << endl;
        stream << "      { crc=" << CrcToString (cctrchParam.trch[i].crc) << endl;
        stream << "      { rmAttr=" << (u16) cctrchParam.trch[i].rmAttr << endl;
        stream << "      { macHeaderBit=" << (u16) cctrchParam.trch[i].macHeaderBit << endl;

        for (u16 j=0;j<cctrchParam.trch[i].nTf;j++)
        {
            stream << "        { tfs=" << j << endl;
            stream << "          { blockCount=" << (u16) cctrchParam.trch[i].tfs[j].blockCount << endl;
            stream << "          { blockSize=" << cctrchParam.trch[i].tfs[j].blockSize << endl;
            stream << "        }" << endl;
        }

        stream << "      }" << endl;
        stream << "    }" << endl;
    }

    stream << "  }" << endl;
    stream << "  { nTfci=" << (u16) cctrchParam.nTfci << endl;
    for (u16 i=0;i<MAX_L1_TRCH;i++)
    {
        stream << "    Trch" << i << "{ ";
        for (u16 j = 0; j < cctrchParam.nTfci; j++)
        {
            stream << (u16) cctrchParam.tfIdx[i][j];
            if (j != cctrchParam.nTfci - 1)
                stream << ", ";
        }

        stream << " }" << endl;
    }

    return stream.str ();
}

string CPhyNodeBCctrchSetupReq::ToString (const l1_hsdpa_param_t &hsdpa) const
{
    ostringstream stream;

    stream << "  { active=" << (u16) hsdpa.active << endl;
    stream << "    uecat=" << (u16) hsdpa.ueCat << endl;
    stream << "    nHarqProcs=" << (u16) hsdpa.nHarqProcs << endl;
    stream << "    hmPartMode=" << (u16) hsdpa.hmPartMode << endl;
    stream << "    harqBufLen={";
    for(int t = 0; t < NUM_MAX_HSDPA_HARQ_PROCS; t++)
    {
        stream << hsdpa.harqBufLen[t];
        if(t != NUM_MAX_HSDPA_HARQ_PROCS-1)
        {
            stream << ", ";
        }
    }
    stream << "}" << endl;
    stream << "  }" << endl;

    return stream.str ();
}

string CPhyNodeBCctrchSetupReq::ToString (const l1_hsupa_param_t &hsupa) const
{
    ostringstream stream;

    stream << "  { active=" << (u16) hsupa.active << endl;

    if(hsupa.active)
    {
        stream << "    ttiLen=" << (u16) hsupa.ttiLen << endl;
        stream << "    Uplink Parameters:" << endl;
        stream << "    { uecat=" << (u16) hsupa.ul.ueCat << endl;
        stream << "      trnsBlockTabId=" << (u16) hsupa.ul.trnsBlockTabId << endl;
        stream << "      plNonMax=" << (u16) hsupa.ul.plNonMax << endl;
        stream << "      minSf=" << (u16) hsupa.ul.minSf << endl;
        stream << "      rvFlag=" << (u16) hsupa.ul.rvFlag << endl;
        stream << "    }" << endl;
        stream << "    Downlink Parameters:" << endl;
        stream << "    { ehichSig=" << (u16) hsupa.dl.ehichSig << endl;
        stream << "      ehichSpreadingCode=" << (u16) hsupa.dl.ehichSpreadingCode << endl;
        stream << "      ernti=" << (u16) hsupa.dl.ernti << endl;
        stream << "    }" << endl;
    }
    stream << "  }" << endl;

    return stream.str ();
}


string CPhyNodeBCctrchSetupReq::ToString (const l1_olpc_param_t &olpc) const
{
    ostringstream stream;

    stream << "  { active=" << (u16) olpc.enable << endl;
    if(!olpc.perTrchBler)
    {
        stream << "    blerToAchieve = " << BlerToString(olpc.blerToAchieve) << endl;
    }
    else
    {
        u8 t;

        stream << "    trchBlerToAchieve[] = { ";
        for(t = 0; t < MAX_L1_TRCH; t++)
        {
             stream << BlerToString(olpc.trchBlerToAchieve[t]);
             if(t != MAX_L1_TRCH -1)
                stream << ", ";
        }
        stream << " }" << endl << "    hsupaBler = " << BlerToString(olpc.hsupaBler) << endl;
    }
    stream << "  }" << endl;

    return stream.str();
}


string CPhyNodeBCctrchSetupReq::BlerToString (u16 bler) const
{
    ostringstream stream;

    stream << (bler / 10) << "." << (bler % 10) << "%";

    return stream.str();
}


const char *CPhyNodeBCctrchSetupReq::CodingToString (coding_scheme_t coding) const
{
    if (coding == CS_C2)
        return "conv-half";

    if (coding == CS_C3)
        return "conv-third";

    if (coding == CS_T3)
        return "turbo-third";

    return "coding-?";
}

const char *CPhyNodeBCctrchSetupReq::CrcToString (crc_length_t crc) const
{
    if (crc == CRC_0)
        return "crc0";
    if (crc == CRC_8)
        return "crc8";
    if (crc == CRC_12)
        return "crc12";
    if (crc == CRC_16)
        return "crc16";
    if (crc == CRC_24)
        return "crc24";

    return "crc-?";
}

const char *CPhyNodeBCctrchSetupReq::SfToString (spreading_factor_t sf) const
{
    if (sf == SF_4)
        return "SF 4";
    if (sf == SF_8)
        return "SF 8";
    if (sf == SF_16)
        return "SF 16";
    if (sf == SF_32)
        return "SF 32";
    if (sf == SF_64)
        return "SF 64";
    if (sf == SF_128)
        return "SF 128";
    if (sf == SF_256)
        return "SF 256";

    return "SF ?";

}

extern "C"
{


s32 CPhyNodeBCctrchSetupReq_Serialise(const CphyNodeBCctrchSetupReq *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBCctrchSetupReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyNodeBCctrchSetupReq));
    RSYS_ASSERT(msg->ue < MAX_DCH_USERS);
    return sizeof(CphyNodeBCctrchSetupReq);
}


s32 CPhyNodeBCctrchSetupReq_Deserialise(const u8 *buffer, u32 maxLen, CphyNodeBCctrchSetupReq *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBCctrchSetupReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyNodeBCctrchSetupReq));
    RSYS_ASSERT(msg->ue < MAX_DCH_USERS);
    return sizeof(CphyNodeBCctrchSetupReq);
}

}

// END OF FILE

