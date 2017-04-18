///////////////////////////////////////////////////////////////////////////////
//
// MibAttributeIdsByDn.h
//
// Sets of IDs organised by DN.  As class so we can add ToString() etc.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibAttributeIdsByDn_h_
#define __MibAttributeIdsByDn_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <map>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibDN.h"
#include "MibAttributeIds.h"

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class MibAttributeIdsByDn : public std::map<MibDN, MibAttributeIds>
{
public:

    std::string ToString() const
    {
        std::ostringstream stream;

        for(const_iterator iter = begin();
            iter != end();
            ++iter)
        {
            stream << "[" << iter->first.ToString() << ": " << iter->second.ToString() << "]";
        }

        return stream.str();
    }

    std::vector<MibDN> GetDnList() const
    {
        std::vector<MibDN> dnList;

        for(MibAttributeIdsByDn::const_iterator iter = begin();
            iter != end();
            ++iter)
        {
            dnList.push_back(iter->first);
        }

        return dnList;
    }

protected:

private:

};

#endif
