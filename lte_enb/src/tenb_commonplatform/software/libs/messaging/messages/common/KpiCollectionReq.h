/*
 * KpiCollectionReq.h
 *
 *  Created on: 03 Oct 2012
 *      Author: Chiranjeevi
 */

#ifndef KPICOLLECTIONREQ_H_
#define KPICOLLECTIONREQ_H_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include <system/SerialisationUtils.h>

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class KpiCollectionReq : public threeway::Serialisable
{
public:
    KpiCollectionReq():m_force(false) {};
    KpiCollectionReq(bool force):m_force(force) {};
    virtual ~KpiCollectionReq(){};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_KPI_COLL_REQ; }
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const 
    {
       // Serialise all the members.
       u8* serialisedData = data;
       
       SerialiseIt(m_force, serialisedData);
       
       RETURN(serialisedData - data); 
    };
    virtual bool DeSerialise(const u8* data, u32 dataLen) 
    {
        ENTER();
	
        DeSerialiseIt(m_force, data);
	
        RETURN(true);
    }
    

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const {ostringstream stream; stream<<"KPICollectionReq "<<"IsReqAfterReboot is "<<m_force<<"collectionPeriod is "<<m_collectionPeriod<<endl; return (stream.str());};
    
    bool IsReqAfterReboot() const { return m_force; };

private:
     bool m_force;
     u32 m_collectionPeriod;
};

#endif /* KPICOLLECTIONREQ_H_ */



///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
