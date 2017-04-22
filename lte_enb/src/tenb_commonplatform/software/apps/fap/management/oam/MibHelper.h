///////////////////////////////////////////////////////////////////////////////
//
// MibHelper.h
//
// Helper/convenience functions for accessing the MIB.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibHelper_h_
#define __MibHelper_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>

#include <boost/shared_ptr.hpp>
#include <mib-core/MibManager.h>
#include <MibAttributeId.h>

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class MibHelper
{
public:
    /**
     * Build up set of MOs required in this build.
     */
    static void BuildMoTree(shared_ptr<MibManager> mibManager);

    static void ApplyDeveloperMibAttributes();

    /**
     * @Deprecated
     * Utility function to get the DN given an attribute ID.
     *
     * NOTE: Try to avoid using this, it makes assumptions about the MO tree that may
     * not be valid in all cases.  E.g. at time of writing it will only work for FAP.0,
     * FAP.0.COMMISSIONING.0 objects.
     */
    static MibDN GetMibObjectDn(MibAttributeId id);

    /**
     * @Deprecated
     * Get a MIB attribute by inferring the object it is on.
     * Prefer subscribe and ApplicationWithParamCache::GetMibAttribute().
     *
     * \param   mibManager      MibManager instance to use.
     * \param   mibAttributeId  Attribute to get.
     * \param   value           Value to be populated.
     * \return                  true for success
     */
    template <class T>
    static bool GetMibAttributeDirect(MibAttributeId mibAttributeId,
                                      T& value)
    {
        RSYS_ASSERT(s_mibManager != NULL);

        bool success = false;

        MibAttributeIds attributeIds;
        attributeIds.insert(mibAttributeId);
        MibAttributeValues mibAttributeValues;
        s_mibManager->GetAttributes(MibHelper::GetMibObjectDn(mibAttributeId),
                                    attributeIds,
                                    mibAttributeValues);
        if(mibAttributeValues.GetAttributeCount() == 1)
        {
            mibAttributeValues.GetAttributeValue(mibAttributeId, value);
            success = true;
        }

        return success;
    }

    template <class T>
    static bool GetMibAttributeDirect(MibDN dn,MibAttributeId mibAttributeId,
                                      T& value)
    {
        RSYS_ASSERT(s_mibManager != NULL);

        bool success = false;

        MibAttributeIds attributeIds;
        attributeIds.insert(mibAttributeId);
        MibAttributeValues mibAttributeValues;
        s_mibManager->GetAttributes(dn,
                                    attributeIds,
                                    mibAttributeValues);
        if(mibAttributeValues.GetAttributeCount() == 1)
        {
            mibAttributeValues.GetAttributeValue(mibAttributeId, value);
            success = true;
        }

        return success;
    }
    /**
     * @Deprecated
     * Get a MIB attribute by inferring the object it is on.
     * Prefer subscribe and ApplicationWithParamCache::GetMibAttribute().
     *
     * \param   moDn            Mib DN to use.
     * \param   mibAttributeId  Attribute to get.
     * \param   value           Value to be populated.
     * \return                  true for success
     */
    static boost::shared_ptr<MibAttributeValue> GetMibAttributeDirect(MibAttributeId mibAttributeId);
    static boost::shared_ptr<MibAttributeValue> GetMibAttributeDirect( const MibDN& moDn, MibAttributeId mibAttributeId);

    /**
     * Get MIB attribute in string format, regardless of the underlying type.
     *
     * \param   moDn            Mib DN to use.
     * \param   mibAttributeId  Attribute to get.
     * \param   value           Value to be populated.
     * \return                  true for success
     */
    static bool GetMibAttributeDirectAsString(MibAttributeId mibAttributeId,
                                              std::string& value);

    static bool GetMibAttributeDirectAsString(const MibDN& moDn,
                                              MibAttributeId mibAttributeId,
                                              std::string& value);

    /**
     * Search for MIB attributes by name and return list of IDs.
     */
    static MibAttributeIds FindAllMatchingMibAttributeIds(const string& val, bool (* matcher)(const std::string &, const std::string &));

    /**
     * Matching algorithms for above.
     */
    static bool LooseMatcher(const std::string & haystack, const std::string & needle);
    static bool ExactMatcher(const std::string & haystack, const std::string & needle);


protected:

private:

    static shared_ptr<MibManager> s_mibManager;

};

#endif
