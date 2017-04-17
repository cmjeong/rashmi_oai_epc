///////////////////////////////////////////////////////////////////////////////
//
// MibObject.h
//
// Represents a MIB object including its RDN, relationship to other MOs (parent
// and children) and its attributes.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibObject_h_
#define __MibObject_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>
#include <map>
#include <limits>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <mib-common/MibAttrValidationFailure.h>
#include <mib-common/MibAttributeValues.h>
#include <mib-common/MibObjectDescriptors.h>

// Auto-generated headers
#include <MibAttributeId.h>
#include <MibObjectClass.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibAttribute.h"
#include "NonVolatileStoreInterface.h"
#include "MibChangedAttributesNotifyInterface.h"

///////////////////////////////////////////////////////////////////////////////
// Forward declarations
///////////////////////////////////////////////////////////////////////////////

class MibObject; // self references exist in this file

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

typedef std::map<MibAttributeId, boost::shared_ptr<MibAttribute> > MibAttributesById;
typedef std::map<MibRDN, boost::shared_ptr<MibObject> > MibObjectsByRdn;
typedef struct validArfcnRange
{
       string bandInd;
       struct{
          u32 min;
          u32 max;
       }range;
}ValidArfcnRange;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class MibObject
{
public:
    /**
     * Convert DN to a NV container descriptor that is used for this MIB object in the NV store.
     * [Only public for test purposes]
     */
    static NvContainerDescriptor GetNvContainerDescriptor(const MibDN& dn);

    /**
     * Constructor.
     */
    MibObject(const MibRDN& rdn, NonVolatileStoreInterface& nvStore, MibChangedAttributesNotifyInterface* changedAttributesNotifyInterface = NULL);

    /**
     * Destructor.
     */
    virtual ~MibObject();

    /**
     * Initialise the MO.
     * This includes checking NV and setting default values.
     */
    virtual MibAttrValidationFailures InitialiseMO(const MibAttributeValues& attributeValues);

    /**
     * Get this object's RDN.
     */
    MibRDN GetRDN() const { return m_rdn; };

    /**
     * Get this object's DN by traversing parent RDNs to root.
     */
    MibDN GetDN() const;

    /**
     * Get the parent object.
     *
     * \return Pointer to parent object or NULL if root object.
     */
    MibObject* GetParentObject() const { return m_parentObject; }

    /**
     * Check if object has any children.
     */
    bool HasChildren() const;

    /**
     * Add an object as a child of this object.
     * Adds to set of children and sets the parent pointer on the child
     * to reference this object.  Will assert if child already exists.
     *
     * \param childObject Child object to add - RDN will already be set.
     */
    void AddChildObject(boost::shared_ptr<MibObject> childObject);

    /**
     * Delete a child object.
     * Object must exist and cannot have any children.
     */
    void DeleteChildObject(const MibRDN& rdnToDelete);

    /**
     * Search
     * @param rdn The MibRDN of the child to be returned.
     */
    boost::shared_ptr<MibObject> FindChildObject(MibRDN rdn);

    void GetChildObjects(MibObjectClass objectClass, set< boost::shared_ptr<MibObject> > & childObjects) const;

    /**
     * Validate a set of attributes before applying.
     */
    MibAttrValidationFailures ValidateAttributes(const MibAttributeValues& attributeValues, bool checkAccessClass = true);

    void InitialiseMibAttributes(const MibAttributeValues& attributeValues );

    /**
     * Set attributes.
     */
    void SetMibAttributes(const MibAttributeValues& attributeValues, bool checkAccessClass = true);

    /**
     * Get a bunch of attributes.
     *
     * \attributeIds        IDs of attributes to get.
     * \mibAttributeValues  IDs and got values.
     */
    void GetMibAttributes(const MibAttributeIds& attributeIds,
                          MibAttributeValues& mibAttributeValues) const;

    /**
     * Get all of the attributes.
     *
     * \mibAttributeValues  IDs and got values.
     */
    void GetMibAttributes(MibAttributeValues& mibAttributeValues) const;

    /**
     * Delete (unset) a bunch of attributes.
     *
     * \attributeIds        IDs of attributes to delete.
     */
    void DeleteMibAttributes(const MibAttributeIds& attributeIds);
    void DeleteMibObject();
    /**
     * Get attribute values where values differ from defaults.
     */
    void GetMibAttributesDiffFromDefaults(MibAttributeValues& diffFromDefaultValues);

    /**
     * Get attribute values where values are explicitly set in NV.
     */
    void GetMibAttributesSetInNv(MibAttributeValues& setInNvValues);

    /**
     * Function to retrieve instance number from DN
     */
    char * GetMibObjectInstanceNum(string dn) const;

    /**
     * Get as string for trace/debug.
     */
    virtual std::string ToString() const;

    /**
     * Declare ostream operator<<
     * @param os Stream to insert data into
     * @param s Source of data to be inserted
     * @return Updated stream object
     */
    friend std::ostream& operator<< (std::ostream& os, const MibObject& s);

private:

    /**
     * Set parent.
     * This has to be an external function. Since using *this in the
     * addChildObject function is not a smart pointer.
     */
    void SetParentObject(MibObject* parentObject);

    /**
     * Validate an individual value.
     */
    bool ValidateValue(MibAttributeId attributeId,
                       boost::shared_ptr<MibAttributeValue> mibAttributeValue,
                       MibAttrValidationFailure& mibAttrValidationFailure);

    /**
     * Get default value for an attribute.
     */
    shared_ptr<MibAttributeValue> GetDefaultValue(MibAttributeId id);

    /**
     * NV store to use for getting/setting NV values.  MO can assume
     * this is at the correct schema for the current code as any
     * up/downgrade steps will have been performed before creating MOs.
     */
    NonVolatileStoreInterface& m_nvStore;

    /**
     * The corresponding container in the NV store.
     * Calculated and cached when object is initialised.
     */
    NvContainerDescriptor m_nvContainerDescriptor;

    /**
     * Notify on changed attributes.  Can be null if no-one cares about changed attributes...
     */
    MibChangedAttributesNotifyInterface* m_changedAttributesNotifyInterface;

    /**
     * RDN of this object.
     */
    const MibRDN m_rdn;

    /**
     * Pointer to parent object.  NULL if this is the root
     * or an orphaned object.
     */
    MibObject* m_parentObject;

    /**
     * Child objects.  Map of RDN -> shared pointer so that child
     * objects should be destroyed when removed... assuming no one's
     * cheekily kept hold of a shared pointer.  We can validate this
     * and thus ensure orphaned objects are detected.
     */
     MibObjectsByRdn m_childObjects;

     /**
      * Descriptor for use when adding children or attributes.
      */
     const MibManagedObjectDescriptor *m_moDescriptor;

     /**
      * Indicates if object has been initialised (Initialise() called).
      */
     bool m_moInitialised;

     /**
      * Indication if MO is configured correctly or not.
      * At time of writing this is based on whether all mandatory-on-create
      * attributes are available when Initialise() is called.
      */
     bool m_attributesValid;

     /**
      * Object attributes.
      */
     MibAttributesById m_attributes;

     /**
      * This function is used to populate Mib attrabute ids 's values to other parameters 's validator during initialisation.
      * It is used when validation is across different parameters
     */
     void SetParamValueInValidator(const MibAttributeValues& mibattrValues);    
     bool ValidateGeranFreqParam(MibAttributeId id, shared_ptr<MibAttributeValue> mibAttributeValue, MibAttrValidationFailure& failureDescriptor);
     bool ValidateGeranCellParam(MibAttributeId id, shared_ptr<MibAttributeValue> mibAttributeValue, MibAttrValidationFailure& failureDescriptor);

     bool ValidateLteInterFreqParam(MibAttributeId id, shared_ptr<MibAttributeValue> mibAttributeValue, MibAttrValidationFailure& failureDescriptor);
	/**
      * This function is used to populate Mib attrabute ids 's values to other parameters 's validator while setting values for Mibattributes
      * It is used when validation is across different parameters
      * This function is important as we have volatile parameters whose value is not available in the NV file
     */

     void SetParamNewValueInValidator(MibAttributeId mibattId, boost::shared_ptr<MibAttributeValue> mibAttributeValue);
     bool ValidateGeranArfcn(string bandInd,u32 arfcn);
};

/***
 * Retrieve the attribute descriptor for the attribute that exists in the object that references it.
 * @param moId
 * @param attrId
 * @return
 */
const MibObjectAttributeDescriptor* getMibObjectAttributeDescriptor(MibObjectClass moId, MibAttributeId attrId);


#endif
