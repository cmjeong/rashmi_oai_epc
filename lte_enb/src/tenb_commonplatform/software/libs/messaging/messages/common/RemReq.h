///////////////////////////////////////////////////////////////////////////////
//
// RemReq.h
//
// Message for requesting a REM scan.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __RemReq_h_
#define __RemReq_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include <mib-common/MibAttributeValues.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

/*
 * Note that frequency sync decision is now handled outside of REM itself - it
 * just returns a candidate DAC value which OAM can then use/ignore. It also
 * doesn't calculate any power margin value - again, the information needed to
 * calculate this is returned so that OAM can make the calculation according
 * to whatever criteria are deemed appropriate at the time.
 * Do we need to do the scrambling code selection here? Probably better to
 * return the relevant info and let OAM do that.
 */
class RemReq : public threeway::Serialisable
{
public:
	 /* Things that need to go into the RemReq:
	 * A list of UARFCNs to scan
	 * The current UARFCN, for intrafreq cells
	 * A list of ARFCNs to scan
	 * PLMN
	 * List of equivalent PLMNs
	 * List of UARFCNs to protect from adjacent channel interference
	 *
	 */

	class PLMN
	{
	public:
		PLMN() : mCC(0), mNC(0) {}
		void Serialise(u8*& pSerialisedData) const
		{
		    SerialiseIt(mCC, pSerialisedData);
		    SerialiseIt(mNC, pSerialisedData);
		}
		void DeSerialise(const u8*& pSerialisedData)
		{
		    DeSerialiseIt(mCC, pSerialisedData);
		    DeSerialiseIt(mNC, pSerialisedData);
		}
	    std::string ToString() const
		{
	        ostringstream stream;
	        stream << "MCC=" << mCC << " MNC=" << mNC << "\n";

	        return stream.str();
		}

		u16 mCC;
		u16 mNC;
	};


	static const u8 MAX_UARFCNS_TO_SCAN = 5;
	static const u8 MAX_ADJ_UARFCNS_TO_SCAN = 10;
	static const u8 MAX_EQUIV_PLMNS = 16;

	class RemReqParams
	{
	public:
		RemReqParams() : numAdjUarfcns(0), numUarfcns(0), numEquivalentPlmns(0),
		        scanNeighbours(false), scanAdjacentUarfcns(false)
		{
			int i;

			for(i = 0; i < MAX_UARFCNS_TO_SCAN; i++)
			{
				uarfcnsToScan[i] = 0;
			}
			for(i = 0; i < MAX_ADJ_UARFCNS_TO_SCAN; i++)
			{
				adjUarfcnsToScan[i] = 0;
			}
		}

		void Serialise(u8*& pSerialisedData) const
		{
			u32 i;
			for(i = 0; i < MAX_UARFCNS_TO_SCAN; i++)
			{
				SerialiseIt(uarfcnsToScan[i], pSerialisedData);
			}
			for(i = 0; i < MAX_ADJ_UARFCNS_TO_SCAN; i++)
			{
				SerialiseIt(adjUarfcnsToScan[i], pSerialisedData);
			}
			for(i = 0; i < MAX_EQUIV_PLMNS; i++)
			{
				equivalentPlmns[i].Serialise(pSerialisedData);
			}
			currentPlmn.Serialise(pSerialisedData);
			SerialiseIt(numAdjUarfcns, pSerialisedData);
			SerialiseIt(numUarfcns, pSerialisedData);
			SerialiseIt(numEquivalentPlmns, pSerialisedData);
			SerialiseIt(scanNeighbours, pSerialisedData);
			SerialiseIt(scanAdjacentUarfcns, pSerialisedData);
		}
		void DeSerialise(const u8*& pSerialisedData)
		{
			u32 i;
			for(i = 0; i < MAX_UARFCNS_TO_SCAN; i++)
			{
				DeSerialiseIt(uarfcnsToScan[i], pSerialisedData);
			}
			for(i = 0; i < MAX_ADJ_UARFCNS_TO_SCAN; i++)
			{
				DeSerialiseIt(adjUarfcnsToScan[i], pSerialisedData);
			}
			for(i = 0; i < MAX_EQUIV_PLMNS; i++)
			{
				equivalentPlmns[i].DeSerialise(pSerialisedData);
			}
			currentPlmn.DeSerialise(pSerialisedData);
			DeSerialiseIt(numAdjUarfcns, pSerialisedData);
			DeSerialiseIt(numUarfcns, pSerialisedData);
			DeSerialiseIt(numEquivalentPlmns, pSerialisedData);
			DeSerialiseIt(scanNeighbours, pSerialisedData);
			DeSerialiseIt(scanAdjacentUarfcns, pSerialisedData);
		}
		string ToString() const
		{
		    ENTER();

		    ostringstream stream;
		    u16 i;

		    stream << currentPlmn.ToString() <<
		    		"scan neighbours=" << (scanNeighbours ? "true" : "false") <<
					"\nNum UARFCNs to scan=" << numUarfcns << " {";

		    for(i = 0; i < numUarfcns && i < MAX_UARFCNS_TO_SCAN; i++)
		    {
		    	stream << uarfcnsToScan[i] << " ";
		    }
		    stream << "}\nscan adjacent UARFCNS=" << (scanAdjacentUarfcns ? "true" : "false") <<
		    "\nNum Adjacent UARFCNs to scan=" << numAdjUarfcns << " {";
		    for(i = 0; i < numAdjUarfcns && i < MAX_ADJ_UARFCNS_TO_SCAN; i++)
		    {
		    	stream << adjUarfcnsToScan[i] << " ";
		    }
		    stream << "}\nNum Equivalent PLMNs=" << numEquivalentPlmns << " {\n ";
		    for(i = 0; i < numEquivalentPlmns && i < MAX_EQUIV_PLMNS; i++)
		    {
		    	stream << equivalentPlmns[i].ToString() << " ";
		    }
		    stream <<"}\n";

		    RETURN(stream.str());
		}
		u16 uarfcnsToScan[MAX_UARFCNS_TO_SCAN];
		u16 adjUarfcnsToScan[MAX_ADJ_UARFCNS_TO_SCAN];
		PLMN equivalentPlmns[MAX_EQUIV_PLMNS];
		PLMN currentPlmn;
		u16 numAdjUarfcns;
		u16 numUarfcns;
		u16 numEquivalentPlmns;
		bool scanNeighbours;
		bool scanAdjacentUarfcns;
	};

    /**
     * Construction / destruction.
     */
    RemReq();
    RemReq(const RemReqParams& params);

    virtual ~RemReq();

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_REM_REQ; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;

    // The set of parameters to inform this entity about.
    RemReqParams m_remReqParams;
};

#endif // __RemReq_h_
