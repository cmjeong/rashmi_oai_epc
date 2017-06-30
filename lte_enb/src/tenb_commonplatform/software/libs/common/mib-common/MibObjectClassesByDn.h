///////////////////////////////////////////////////////////////////////////////
//
// MibObjectClassesByDn.h
//
// Sets of IDs organised by DN.  As class so we can add ToString() etc.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibObjectClassesByDn_h_
#define __MibObjectClassesByDn_h_

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
#include "MibObjectClasses.h"

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class MibObjectClassesByDn : public std::map<MibDN, MibObjectClasses>
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

        for(MibObjectClassesByDn::const_iterator iter = begin();
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
