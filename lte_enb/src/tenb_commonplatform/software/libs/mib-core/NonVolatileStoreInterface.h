///////////////////////////////////////////////////////////////////////////////
//
// NonVolatileStoreInterface.h
//
// Provides an abstraction of a non-volatile store so the implementation
// details (e.g. INI file format, SQLite etc) are hidden and decoupled.
//
// Copyright radisys Limited
//
// Schema Version Definition
// =========================
//
// 1.  The schema version applies to the whole NV store.
//
// 2.  It represents a snapshot of the structure of the store i.e. the set of
//     containers, attributes and their metadata (type, format, valid range etc).
//
// 3.  The NV store keeps historical values such that setting the current schema
//     to a previous schema version results in client code getting the old values
//     and sets are applied to that schema version.  E.g.
//
//       - Schema is at 12345.
//
//       - ATTR1 is written with value "yo!".  ATTR2 is written with value "hi!".
//
//       - Schema is changed to 12500 and as part of 12345->12500 "upgrade" ATTR1
//         is changed to "YO!".  Getting ATTR2 will still return "hi!".
//
//       - Apps run and at some point modify ATTR1 to "YOYO!".
//
//       - At this point the NV store contains 3 values: ATTR1@12345 = "yo!",
//         ATTR1@12500="YOYO!", ATTR2@12345="hi!"
//
//       - Schema is returned to 12345.  Getting ATTR1 now returns "yo!", ATTR2 "hi!".
//
//       - Schema is changed back to 12500.  Upgrade code can either perform the
//         upgrade again and set ATTR1 to "YO!" or can recognise that there is a
//         value for schema 12500 ("YOYO!") and leave it untouched.  The latter
//         is probably the normal case but this decision has to be made by someone
//         who understands the system and how that attribute is used.
//
// Schema Version Rules
// ====================
//
// 1.  The schema version must increment (but not necessarily monotonically)
//     on each "relevant change" to the NV store format.
//
// 2.  A "relevant change" is one or more of the following:
//
//      - Deletion or addition of NV containers or attributes that are ALLOWED
//        to be present in the store but have not necessarily been written to NV.
//
//      - Change in meaning of a container or attribute such that client code
//        must interpret or validate it differently.  E.g. serial number changes
//        from a 10 digit string to a 12 digit string.
//
// MIB Related Notes
// =================
//
// When using this interface for the NV portion of a MIB based on XML the XML
// may be parsed to check if the NV bits have changed.  If so, the
// autogenerator can update the required schema version for the software
// build.  E.g.:
//
//  - Parse the MIB XML to extract and sort the NV attributes and their
//    MOs and strip all whitespace.
//
//  - Compare the result to committed version of the same parsed file.
//
//  - If they are the same, the schema version required for this build is
//    the SVN revision of the committed version.
//
//  - If they differ, the schema version required for this build is the
//    SVN revision of the committed version + 1.
//
//  - The autogenerator will create function prototypes for upgrading the
//    NV store.  E.g. Hbs2IuMibUpgrade12345To12346().
//
//  - Build will fail until that function is implemented.
//
//  - TODO: Hmmm bugger, needs a bit more thought.... this is a bit of a
//    pain coz when you finally commit the changed parsed MIB file it gets
//    a new version number and the code will no longer build.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __NonVolatileStoreInterface_h_
#define __NonVolatileStoreInterface_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////
#include <cstdlib> // atoi
#include <vector>
#include <string>
#include <Radisys.h>
#include <iostream>


///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

/**
 * NV store schema version.  The NV store can store multiple schemas
 * simultaneously.  At any point in time the NV store will be set to
 * a given schema version and gets will get the right version of an
 * attribute and sets will tag the attributes with the current schema
 * version.  Any up/downgrade code can query and set the current schema.
 */
typedef u32         NvStoreSchemaVersion;

/**
 * Unique name for a container within the NV store.
 */
typedef std::string NvContainerName;

/**
 * Unique identifier for an attribute within a particular container.
 */
typedef std::string NvAttributeName;

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

static const NvStoreSchemaVersion MIB_NV_SCHEMA_OLDSTYLE = 0;


/**
 * All values are currently stored as strings.
 * Client code is responsible for type conversion.
 * NOTE: Do *not* add attributes to this class because the base class destructor isn't virtual
 */
class NvAttributeValue
{
public:
    NvAttributeValue() {}
    NvAttributeValue(const char* s) : value(s) {}
    NvAttributeValue(const std::string& s) : value(s) {}
    NvAttributeValue(const NvAttributeValue& s) : value(s.value) {}

    u32 GetAsU32() const { return (u32)std::atoi(value.c_str()); }
    s32 GetAsS32() const { return (s32)std::atoi(value.c_str()); }
    std::string GetAsString() const { return value;}
    bool operator==(const NvAttributeValue & outside) const
    {
        return (value == outside.value);
    }

    void assign(const std::string & str) {  value.assign(str);return;}
private:
    std::string value;
};



/**
 * Result codes when fetching a NV attribute from the store.
 */
typedef enum
{
    NV_ATTRIBUTE_RESULT_OK = 0,
    NV_ATTRIBUTE_RESULT_NO_SUCH_CONTAINER,
    NV_ATTRIBUTE_RESULT_NO_SUCH_ATTRIBUTE,
} NvAttributeResult;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

/**
 * References a particular container within the NV store.
 */
class NvContainerDescriptor
{
public:
    NvContainerDescriptor() :
        m_nvContainerInstance(0)
        {};
    NvContainerDescriptor(const NvContainerName& nvContainerName, u32 nvContainerInstance) :
        m_nvContainerName(nvContainerName),
        m_nvContainerInstance(nvContainerInstance) {};
    ~NvContainerDescriptor() {};

    NvContainerName m_nvContainerName;
    u32             m_nvContainerInstance;

    /**
     * Operator required for Strict Weak ordering by std::map
     * Importance order: name then instance.
     * @param outsideVal
     * @return
     */
    bool operator<(const NvContainerDescriptor & outsideVal) const
    {
        return ((m_nvContainerName < outsideVal.m_nvContainerName)
                || ((m_nvContainerName == outsideVal.m_nvContainerName) && (m_nvContainerInstance < outsideVal.m_nvContainerInstance)));
    }

    bool operator==(const NvContainerDescriptor & outsideVal) const
    {
        return ((m_nvContainerName == outsideVal.m_nvContainerName) && (m_nvContainerInstance == outsideVal.m_nvContainerInstance));
    }
};

std::ostream & operator<< (std::ostream & os, NvContainerDescriptor nvContainerDescriptor);


/**
 * References a particular attribute within the NV store.
 */
class NvAttributeDescriptor
{
public:
    NvAttributeDescriptor() :
        m_nvAttributeInstance(0)
        {};
    NvAttributeDescriptor(NvAttributeName nvAttributeName, u32 nvAttributeInstance /*, u16 nvAttributeSchema*/) :
        m_nvAttributeName(nvAttributeName),
        m_nvAttributeInstance(nvAttributeInstance)
        {};

    NvAttributeName m_nvAttributeName;
    u32             m_nvAttributeInstance;

    /***
     * Returns true if all attributes in the class are equal
     * @param outsideVal
     * @return
     */
    bool operator==(const NvAttributeDescriptor & outsideVal) const
    {
        return ((m_nvAttributeName == outsideVal.m_nvAttributeName) &&
                (m_nvAttributeInstance == outsideVal.m_nvAttributeInstance));
    }

    /***
     * Returns true if attribute name is less, or if equal then instance numbers.
     * This is implemented for StrictWeakOrdering containers.
     * @param outsideVal Value to compare against
     * @return
     */
    bool operator<(const NvAttributeDescriptor & outsideVal) const
    {
        return ((m_nvAttributeName < outsideVal.m_nvAttributeName) ||
                ((m_nvAttributeName == outsideVal.m_nvAttributeName) && (m_nvAttributeInstance < outsideVal.m_nvAttributeInstance)));
    }
};

std::ostream & operator<<(std::ostream & os, NvAttributeDescriptor nvAttributeDescriptor);


/**
 * Representation of an attribute stored in the NV store.
 */
class NvAttribute
{
public:
    NvAttribute(NvAttributeDescriptor nvAttributeDescriptor, NvAttributeValue nvAttributeValue, u16 schemaVersion) :
        m_nvAttributeDescriptor(nvAttributeDescriptor),
        m_nvAttributeValue(nvAttributeValue),
        m_schemaVersion(schemaVersion) {}

    NvAttributeDescriptor m_nvAttributeDescriptor;
    NvAttributeValue m_nvAttributeValue;

    // Which schema is this attribute from.
    u16 m_schemaVersion;
};

std::ostream & operator<<(std::ostream & os, NvAttribute nvAttribute);


/**
 * Abstract interface for accessing an NV store.  Makes no assumptions
 * about schema version... the schema version is what it is and is expected
 * to be correct for the client code.
 *
 * See NonVolatileStoreUpgradeDowngradeInterface below for an interface
 * that allows querying/setting of current schema.
 */
class NonVolatileStoreInterface
{
public:

    virtual ~NonVolatileStoreInterface() {};


    ////////////////////////////////
    // INITIALISATION
    ////////////////////////////////

    /**
     * Initialise the store.  May include opening files/databases, reading
     * values into a local cache etc
     */
    virtual bool InitialiseNvStore() = 0;


    ////////////////////////////////
    // CONTAINER PRESENCE QUERIES
    ////////////////////////////////

    /**
     * Check if a particular container is present in the NV store.
     */
    virtual bool IsNvContainerPresent(const NvContainerDescriptor& nvContainerDescriptor) const = 0;

    /**
     * Get a list of the instances of a container of a given name.  Can be sparse e.g. 0, 3, 4.
     */
    virtual std::vector<u32> GetNvContainerInstances(const NvContainerName& nvContainerName) const = 0;


    ////////////////////////////////
    // ATTRIBUTE PRESENCE QUERIES
    ////////////////////////////////

    /**
     * Check to see if an attribute is present in the container.  Returns true if there
     * is one or more instances of the attribute.
     */
    virtual bool IsNvAttributePresent(const NvContainerDescriptor& nvContainerDescriptor,
                                      const NvAttributeName& nvAttributeName) const = 0;

    /**
     * Get a list of the instances of an attribute of a given name.  Can be sparse e.g. 0, 3, 4.
     */
    virtual std::vector<u32> GetNvAttributeInstances(const NvContainerDescriptor& nvContainerDescriptor,
                                                     const NvAttributeName& nvAttributeName) const = 0;

    /**
     * Get all NV attribute names stored in a particular container.
     */
    virtual std::vector<NvAttributeName> GetNvAttributeNames(const NvContainerDescriptor& nvContainerDescriptor) const = 0;


    //////////////////////////////////
    // ATTRIBUTE VALUE GET/SET/DELETE
    //////////////////////////////////

    /**
     * Get an NV attribute value from the NV store.
     */
    virtual NvAttributeResult GetNvAttribute(const NvContainerDescriptor& nvContainerDescriptor,
                                             const NvAttributeDescriptor& nvAttributeDescriptor,
                                             NvAttributeValue& nvAttributeValue) const = 0;

    /**
     * Set one or more NV attributes on a container.
     */
    virtual void SetNvAttributes(const NvContainerDescriptor& nvContainerDescriptor,
                                 const std::vector<NvAttribute>& nvAttributes) = 0;

    /**
     * Delete one or more NV attributes on a container.
     */
    virtual void DeleteNvAttributes(const NvContainerDescriptor& nvContainerDescriptor,
                                    const std::vector<NvAttributeDescriptor>& nvAttributeDescriptors) = 0;

   virtual void DeleteNvContainer( NvContainerDescriptor& nvContainerDescriptor) = 0;

    ////////////////////////////////
    // TRANSACTION MANAGEMENT
    ////////////////////////////////

    /**
     * Start a transaction.  If this is called an immediate flush of any dirty values is
     * performed then any subsequent Set's are guaranteed to not be flushed until
     * EndNvTransaction() or ForceNvFlush() are called - at which point an atomic write is performed
     * (or at least an atomic write is cached until a ForceFlush() or next internally
     * scheduled flush).
     *
     *
     * Depending on the subsequent actions...:
     *
     * SetNvAttributes() called:
     * Transactions allow, for example, MIB managed objects to individually write their own NV
     * attributes and while some higher entity manages the start/end of the transaction to
     * allow atomic commits across multiple MOs.
     *
     * SetNvDeleteTransactionExceptions() called:
     * Start a transaction for deleting attributes only.  Will delete all containers
     * and attributes *including all their history* except those specified as invariant
     * by call(s) to SetNvDeleteTransactionExceptions().  Typical use case is "reset to
     * factory defaults". It is an error for a delete transaction and a normal transaction to
     * overlap. The deletion will occur upon either EndNvTransaction() or FlushNv. Attribute
     * deletion may not occur outside a delete transaction unlike attribute addition. During
     * a delete transaction attributes may not be added.
     *
     * DeleteNvAttributes() called:
     * Start a transaction for deleting attributes only. This is identical to SetNvDeleteTransactionExceptions
     * except that the attributes specified are the ones to be deleted. If no attributes are specified
     * then nothing will be deleted upon calling EndNvTransaction().
     */
    virtual void StartNvTransaction() = 0;

    /**
     */
    //virtual void StartNvDeleteTransaction() = 0;

    /**
     * Specify exceptions if using StartNvDeleteTransaction().
     */
    virtual void SetNvDeleteTransactionExceptions(const NvContainerDescriptor& nvContainerDescriptor) = 0;
    virtual void SetNvDeleteTransactionExceptions(const NvContainerDescriptor& nvContainerDescriptor,
                                                  const std::vector<NvAttributeDescriptor>& nvAttributeDescriptors) = 0;

    /**
     * Finish the transaction and mark all Set's since StartNvTransaction as an atomic set.
     * TODO: Add return value indicating success or details of failures?  But what about
     * failures that occur on background periodic writes to NV?  Perhaps we don't worry about
     * that until we have an implementation that does that?!
     */
    virtual void EndNvTransaction() = 0;

    /**
     * Cancel any outstanding transaction and discard the pending changes.
     */
    virtual void CancelNvTransaction() = 0;


    ////////////////////////////////
    // ACCESS
    ////////////////////////////////

    /**
     * Make the NV store read-only.
     */
    virtual void MakeNvReadOnly() = 0;


    ////////////////////////////////
    // FLUSHING
    ////////////////////////////////

    /**
     * Perform an atomic flush of any dirty values to NV. This has no effect outside of a transaction because it
     * is implicitly called by SetNvAttributes/DeleteNvAttributeExceptions.
     * TODO: Add return value indicating success or details of failures?
     */
    virtual void ForceNvFlush() = 0;

};

/**
 * Abstract interface for upgrading or downgrading an NV store.
 *
 * Allows client to query and set schema version.
 *
 * Note: There is a requirement on the client of NonVolatileStoreInterface
 * not to break the current schema e.g. it shouldn't store attributes that
 * don't exist in that schema or store values in the wrong format / range
 * for that schema.  This is easily achievable if the client code is
 * autogenerated.
 *
 * The up/downgrade code can firkle with the schema and attributes as it
 * pleases so much care is required to ensure the NV store remains consistent.
 */
class NonVolatileStoreUpgradeDowngradeInterface: public NonVolatileStoreInterface
{
public:

    virtual ~NonVolatileStoreUpgradeDowngradeInterface() {}

    /**
     * Get the current schema version.
     */
    virtual NvStoreSchemaVersion GetCurrentNvStoreSchemaVersion() const = 0;

    /**
     * Set the current schema version.
     * Subsequent use of NonVolatileStoreInterface onto the same NV store
     * will use the new schema.  Creates a new schema if it doesn't currently
     * exist in the NV store.  This has the effect that subsequent SetNvAttributes()
     * calls will tag each attribute as belonging to the current schema.
     * When the NV store is initialised for normal access and a request for an
     * NV attribute is made it will choose the attribute with the latest schema
     * version up to and including the current schema version (but no later coz it
     * won't understand it...).
     */
    virtual void SetCurrentNvStoreSchemaVersion(NvStoreSchemaVersion newSchemaVersion) = 0;
};



#endif // __NonVolatileStoreInterface_h_

