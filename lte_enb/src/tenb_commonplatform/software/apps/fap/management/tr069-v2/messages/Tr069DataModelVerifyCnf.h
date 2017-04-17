///////////////////////////////////////////////////////////////////////////////
//
// Tr069DataModelVerifyCnf.h
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069DataModelVerifyCnf_h_
#define __Tr069DataModelVerifyCnf_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <boost/shared_ptr.hpp>
#include <mib-common/MibAttributeValuesByDn.h>
///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069QueueableEvent.h"
#include "Tr069FtpFile.h"

namespace tr069
{

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////
#define MAX_NO_OF_FAULT 5


class DataModelVerifyCnf : public tr069::Tr069QueueableEvent
{
public:

    DataModelVerifyCnf(bool verifiedOk, shared_ptr<MibAttributeValuesByDn> mibAttributeValuesByDn, std::string fault[],std::string name[], int faultinstances) :
        tr069::Tr069QueueableEvent( TR069_EVENT(DATA_MODEL_VERIFY_CNF), SPV_FSM),
        m_verifiedOk(verifiedOk),
        m_mibAttributeValuesByDn(mibAttributeValuesByDn),
        no_of_fault(faultinstances)
        {
           for(int i = 0; i < MAX_NO_OF_FAULT; i++)
           {
              m_fault[i] = fault[i];
              p_name[i] = name[i];
           }
        };
    virtual ~DataModelVerifyCnf(){}

    bool VerifiedOk() const { return m_verifiedOk; }
    shared_ptr<MibAttributeValuesByDn> GetMibAttributeValuesByDn() const { return m_mibAttributeValuesByDn; }
    const std::string& GetFault(int i) const { return m_fault[i]; }
    const std::string& GetFaultParameter(int i) const { return p_name[i]; }
    int GetNoOfFaults(){ return no_of_fault; }

private:
    bool m_verifiedOk;
    std::string m_fault[MAX_NO_OF_FAULT];
    std::string p_name[MAX_NO_OF_FAULT];
    int no_of_fault;
    shared_ptr<MibAttributeValuesByDn> m_mibAttributeValuesByDn;
};

}

#endif
