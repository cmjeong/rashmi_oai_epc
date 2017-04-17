///////////////////////////////////////////////////////////////////////////////
//
// RemCnf.h
//
// Message for confirming completion of a REM scan.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __RemCnf_h_
#define __RemCnf_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include <system/SerialisationUtils.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class RemCnf : public threeway::Serialisable
{
public:
	/*
	 * Items that a scan will need to return:
	 * A list of intra-freq cells, each containing PSC, RSCP, (ECNO?,) MCC/MNC,
	 * RAC, LAC, cellID.
	 * A list of inter-freq cells, each containing all the above plus UARFCN
	 * A list of cells on adjacent channels with their RSSI values. (How much do they
	 * need decoding? Do we need to filter on PLMN?)
	 * A list of inter-RAT cells, each containing MCC/MNC, NCC, BCC, LAC
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
	        stream << "MCC=" << mCC << " MNC=" << mNC;

	        return stream.str();
		}

		u16 mCC;
		u16 mNC;
	};

	class IntraFreqNeighbourCellDetails : public PLMN
	{
	public:
		IntraFreqNeighbourCellDetails() : pSC(0), rSCP(0), eCNO(0), rAC(0), lAC(0), cellId(0) {}
		void Serialise(u8*& pSerialisedData) const
		{
			PLMN::Serialise(pSerialisedData);
			SerialiseIt(pSC, pSerialisedData);
			SerialiseIt(rSCP, pSerialisedData);
			SerialiseIt(eCNO, pSerialisedData);
			SerialiseIt(rAC, pSerialisedData);
			SerialiseIt(lAC, pSerialisedData);
			SerialiseIt(cellId, pSerialisedData);
		}
		void DeSerialise(const u8*& pSerialisedData)
		{
		    PLMN::DeSerialise(pSerialisedData);
		    DeSerialiseIt(pSC, pSerialisedData);
		    DeSerialiseIt(rSCP, pSerialisedData);
		    DeSerialiseIt(eCNO, pSerialisedData);
		    DeSerialiseIt(rAC, pSerialisedData);
		    DeSerialiseIt(lAC, pSerialisedData);
		    DeSerialiseIt(cellId, pSerialisedData);
		}
	    std::string ToString() const
		{
	        ostringstream stream;
	        stream << PLMN::ToString() << " PSC=" << pSC << " RSCP=" << rSCP << " ECNO=" << eCNO <<
	        		" RAC=" << rAC << " LAC=" << lAC << " CellId=" << cellId;

	        return stream.str();
		}

		u16 pSC;
		s16 rSCP;
		s16 eCNO;
		s16 rAC;
		s16 lAC;
		s16 cellId;
	};

	class InterFreqNeighbourCellDetails : public IntraFreqNeighbourCellDetails
	{
	public:
		InterFreqNeighbourCellDetails() : uARFCN(0) {}
		void Serialise(u8*& pSerialisedData) const
		{
			IntraFreqNeighbourCellDetails::Serialise(pSerialisedData);
			SerialiseIt(uARFCN, pSerialisedData);
		}
		void DeSerialise(const u8*& pSerialisedData)
		{
			IntraFreqNeighbourCellDetails::DeSerialise(pSerialisedData);
			DeSerialiseIt(uARFCN, pSerialisedData);
		}
	    std::string ToString() const
		{
	        ostringstream stream;
	        stream << IntraFreqNeighbourCellDetails::ToString() << " UARFCN=" << uARFCN;

	        return stream.str();
		}

		u16 uARFCN;
	};

	class InterRatNeighbourCellDetails : public PLMN
	{
	public:
		InterRatNeighbourCellDetails () : nCC(0), bCC(0), lAC(0), rSCP(0) {}
		void Serialise(u8*& pSerialisedData) const
		{
			PLMN::Serialise(pSerialisedData);
			SerialiseIt(nCC, pSerialisedData);
			SerialiseIt(bCC, pSerialisedData);
			SerialiseIt(lAC, pSerialisedData);
			SerialiseIt(rSCP, pSerialisedData);
		}
		void DeSerialise(const u8*& pSerialisedData)
		{
			PLMN::DeSerialise(pSerialisedData);
			DeSerialiseIt(nCC, pSerialisedData);
			DeSerialiseIt(bCC, pSerialisedData);
			DeSerialiseIt(lAC, pSerialisedData);
			DeSerialiseIt(rSCP, pSerialisedData);
		}
	    std::string ToString() const
		{
	        ostringstream stream;
	        stream << PLMN::ToString() << " NCC=" << nCC << " BCC=" <<
	        		bCC << " LAC=" << lAC << " RSCP=" << rSCP;

	        return stream.str();
		}

		u16 nCC;
		u16 bCC;
		u16 lAC;
		s16 rSCP;
	};

	class AdjacentUarfcnCellDetails
	{
	public:
		AdjacentUarfcnCellDetails() : uARFCN(0), rSCP(0), pSC(0) {}
		void Serialise(u8*& pSerialisedData) const
		{
			SerialiseIt(uARFCN, pSerialisedData);
			SerialiseIt(rSCP, pSerialisedData);
			SerialiseIt(pSC, pSerialisedData);
		}
		void DeSerialise(const u8*& pSerialisedData)
		{
			DeSerialiseIt(uARFCN, pSerialisedData);
			DeSerialiseIt(rSCP, pSerialisedData);
			DeSerialiseIt(pSC, pSerialisedData);
		}
	    std::string ToString() const
		{
	        ostringstream stream;
	        stream << "UARFCN=" << uARFCN << " RSCP=" <<
	        		rSCP << " PSC=" << pSC;

	        return stream.str();
		}

		u16 uARFCN;
		s16 rSCP;
		u16 pSC;
	};

	static const u16 MAX_INTRA_FREQ_NEIGHBOURS = 32;
	static const u16 MAX_INTER_FREQ_NEIGHBOURS = 32;
	static const u16 MAX_INTER_RAT_NEIGHBOURS = 16;
	static const u16 MAX_ADJACENT_CHANNEL_NEIGHBOURS = 32;


	class RemResults
	{
	public:
		void Serialise(u8*& pSerialisedData) const
		{
			u16 count;

			SerialiseIt(numIntraFreqNeighbours, pSerialisedData);
			for(count = 0; count < MAX_INTRA_FREQ_NEIGHBOURS; count++)
			{
				intraFreqNeighbourCellDetails[count].Serialise(pSerialisedData);
			}
			SerialiseIt(numInterFreqNeighbours, pSerialisedData);
			for(count = 0; count < MAX_INTER_FREQ_NEIGHBOURS; count++)
			{
				interFreqNeighbourCellDetails[count].Serialise(pSerialisedData);
			}
			SerialiseIt(numInterRatNeighbours, pSerialisedData);
			for(count = 0; count < MAX_INTER_RAT_NEIGHBOURS; count++)
			{
				interRatNeighbourCellDetails[count].Serialise(pSerialisedData);
			}
			SerialiseIt(numAdjacentUarfcnCells, pSerialisedData);
			for(count = 0; count < MAX_ADJACENT_CHANNEL_NEIGHBOURS; count++)
			{
				adjacentUarfcnCellDetails[count].Serialise(pSerialisedData);
			}
		}
		void DeSerialise(const u8*& pSerialisedData)
		{
			u16 count;

			DeSerialiseIt(numIntraFreqNeighbours, pSerialisedData);
			for(count = 0; count < MAX_INTRA_FREQ_NEIGHBOURS; count++)
			{
				intraFreqNeighbourCellDetails[count].DeSerialise(pSerialisedData);
			}
			DeSerialiseIt(numInterFreqNeighbours, pSerialisedData);
			for(count = 0; count < MAX_INTER_FREQ_NEIGHBOURS; count++)
			{
				interFreqNeighbourCellDetails[count].DeSerialise(pSerialisedData);
			}
			DeSerialiseIt(numInterRatNeighbours, pSerialisedData);
			for(count = 0; count < MAX_INTER_RAT_NEIGHBOURS; count++)
			{
				interRatNeighbourCellDetails[count].DeSerialise(pSerialisedData);
			}
			DeSerialiseIt(numAdjacentUarfcnCells, pSerialisedData);
			for(count = 0; count < MAX_ADJACENT_CHANNEL_NEIGHBOURS; count++)
			{
				adjacentUarfcnCellDetails[count].DeSerialise(pSerialisedData);
			}
		}
	    std::string ToString() const
		{
	        ostringstream stream;
	        u16 i;

	        stream << "numIntraFreqNeighbours=" << numIntraFreqNeighbours << "\n";
	        for(i = 0; i < numIntraFreqNeighbours && i < MAX_INTRA_FREQ_NEIGHBOURS; i++)
	        {
	        	stream << "{" << intraFreqNeighbourCellDetails[i].ToString() << "}\n";
	        }
	        stream << "numInterFreqNeighbours=" << numInterFreqNeighbours << "\n";
	        for(i = 0; i < numInterFreqNeighbours && i < MAX_INTER_FREQ_NEIGHBOURS; i++)
	        {
	        	stream << "{" << interFreqNeighbourCellDetails[i].ToString() << "}\n";
	        }
	        stream << "numInterRatNeighbours=" << numInterRatNeighbours << "\n";
	        for(i = 0; i < numInterRatNeighbours && i < MAX_INTER_RAT_NEIGHBOURS; i++)
	        {
	        	stream << "{" << interRatNeighbourCellDetails[i].ToString() << "}\n";
	        }
	        stream << "numAdjacentUarfcnCells=" << numAdjacentUarfcnCells << "\n";
	        for(i = 0; i < numAdjacentUarfcnCells && i < MAX_ADJACENT_CHANNEL_NEIGHBOURS; i++)
	        {
	        	stream << "{" << adjacentUarfcnCellDetails[i].ToString() << "}\n";
	        }
	        return stream.str();
		}

	    u16 numIntraFreqNeighbours;
	    u16 numInterFreqNeighbours;
	    u16 numInterRatNeighbours;
	    u16 numAdjacentUarfcnCells;
	    IntraFreqNeighbourCellDetails intraFreqNeighbourCellDetails[MAX_INTRA_FREQ_NEIGHBOURS];
	    InterFreqNeighbourCellDetails interFreqNeighbourCellDetails[MAX_INTER_FREQ_NEIGHBOURS];
	    InterRatNeighbourCellDetails interRatNeighbourCellDetails[MAX_INTER_RAT_NEIGHBOURS];
	    AdjacentUarfcnCellDetails adjacentUarfcnCellDetails[MAX_ADJACENT_CHANNEL_NEIGHBOURS];
	};

    /**
     * Construction / destruction.
     */
    RemCnf(bool remSucceeded, RemResults& remResults);
    RemCnf();
    virtual ~RemCnf();

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_REM_CNF; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

    /**
     * Getters
     */
    bool GetRemSucceeded() const { return m_remSucceeded; }

    RemResults m_remResults;
    bool m_remSucceeded;
};

#endif // __RemCnf_h_
