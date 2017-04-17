///////////////////////////////////////////////////////////////////////////////
//
// IniFormatNvStore.h
//
// Concrete implementation of NonVolatileStoreInterface based loosely on
// INI file format i.e. sections delimited by [] and use of string based
// name/value pairs.
//
// Current schema format: [[!schemaVersion]]
// Available schema format: [[@schemaVersion]]
// Container description format: [containerName@schemaVersion/containerInstance]
// Attribute description format: attributeName/attributeInstance
//
// E.g.:
//   Changes between 12000 and 12345 are:
//     - serialNumber format change.
//     - mnc format change.
//     - rndId attribute added.
//     - iu container and attributes added.
//
//   [[!12345]]
//
//   [[@12000]]
//
//   [fap/0]
//   uarfcn/0 = 10800
//   serialNumber/0 = ABCD12
//   [neighbourCell/0]
//   mcc/0 = 123
//   mnc/0 = 55
//   [neighbourCell/3]
//   mcc/0 = 99
//   mnc/0 = 66
//
//   [[@12345]]
//
//   [fap/0]
//   serialNumber/0 = 1234567890
//   [neighbourCell/0]
//   mnc/0 = AB
//   rndId/0 = 567
//   [neighbourCell/3]
//   mnc/0 = CD
//   rndId/0 = 789
//   [iu/0]
//   sctpLocalPort/0 = 5000
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __IniFormatNvStore_h_
#define __IniFormatNvStore_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <fstream>
#include <map>
#include <Radisys.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "NonVolatileStoreInterface.h"


///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

typedef std::map <NvAttributeDescriptor, NvAttribute> NvAttributeMap;
typedef std::map<NvContainerDescriptor, NvAttributeMap > NvStoreMap;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class IniFormatNvStore : public NonVolatileStoreUpgradeDowngradeInterface
{
public:
    /**
     * Default constructor.
     */
    IniFormatNvStore();

    /**
     * Destructor.
     */
    virtual ~IniFormatNvStore();

    /**
     * Implement NonVolatileStoreUpgradeDowngradeInterface.
     */
    virtual bool InitialiseNvStore();
    virtual bool IsNvContainerPresent(const NvContainerDescriptor& nvContainerDescriptor) const;
    virtual std::vector<u32> GetNvContainerInstances(const NvContainerName& nvContainerName) const;
    virtual bool IsNvAttributePresent(const NvContainerDescriptor& nvContainerDescriptor,
                                      const NvAttributeName& nvAttributeName) const;
    virtual std::vector<u32> GetNvAttributeInstances(const NvContainerDescriptor& nvContainerDescriptor,
                                                     const NvAttributeName& nvAttributeName) const;
    virtual std::vector<NvAttributeName> GetNvAttributeNames(const NvContainerDescriptor& nvContainerDescriptor) const;
    virtual NvAttributeResult GetNvAttribute(const NvContainerDescriptor& nvContainerDescriptor,
                                             const NvAttributeDescriptor& nvAttributeDescriptor,
                                             NvAttributeValue& nvAttributeValue) const;
    virtual void SetNvAttributes(const NvContainerDescriptor& nvContainerDescriptor,
                                 const std::vector<NvAttribute>& nvAttributes);
    virtual void DeleteNvAttributes(const NvContainerDescriptor& nvContainerDescriptor,
                                    const std::vector<NvAttributeDescriptor>& nvAttributeDescriptors);
    virtual void StartNvTransaction();
    virtual void SetNvDeleteTransactionExceptions(const NvContainerDescriptor& nvContainerDescriptor);
    virtual void SetNvDeleteTransactionExceptions(const NvContainerDescriptor& nvContainerDescriptor,
                                                  const std::vector<NvAttributeDescriptor>& nvAttributeDescriptors);
    virtual void EndNvTransaction();
    virtual void CancelNvTransaction();
    virtual void MakeNvReadOnly();
    virtual void ForceNvFlush() ;
    virtual void SetCurrentNvStoreSchemaVersion(NvStoreSchemaVersion newSchemaVersion);
    virtual NvStoreSchemaVersion GetCurrentNvStoreSchemaVersion() const { RETURN(m_currentVersion); }

    /**
     * Set the filename to be used in initialising the store
     */
    void SetStoreFileName(const std::string & nvStoreFileName) { m_nvStoreFileName = nvStoreFileName; };
    virtual void DeleteNvContainer( NvContainerDescriptor& nvContainerDescriptor);
    void writeToNvFile();

    /**
     * Allow a function with this prototype to access the private member variables
     */
    friend std::ostream & operator<<(std::ostream & os, const IniFormatNvStore &iniFormatNvStore);
    friend std::ostream & operator<<(std::ostream & os, const NvAttributeMap::value_type &nvAttributeMapItem);

private:

    /***
     * Common initialisation routine that copies previous variables into the current version
     */
    void UpdateInheritedNvStore();

    /**
     * To help with backwards compatibility we clear out values in later schemas as the old NV format
     * would write new values into whatever the current overall schema is set to but new scheme
     * writes values into actual schema for that particular attribute.
     */
    void DeleteFromIntermediateSchemas(NvStoreSchemaVersion attrSchema, const NvContainerDescriptor& container, const NvAttributeDescriptor& attrDesc);

    /**
     * The current version number is stored here
     */
    NvStoreSchemaVersion m_currentVersion;

    /**
     * File name to load and save data to in the ini format
     */
    std::string m_nvStoreFileName;

    /** This represents the transaction state that may exist at any one time
	 * IDLE - out of transaction
     * DECIDEACTION - inside transaction but of undeterminded type
     * ADD - inside an additive transaction where attributes may only be added and set
     * DELETE - inside a subtractive transaction where attributes may only be deleted
     * RESET - inside a subtraction transaction where attributes may only be protected from deletion
     */
    enum NvTransactionState { IDLE, DECIDEACTION, ADD, DELETE, RESET };
    NvTransactionState m_transactionState;

    /**
     * This gets marked when the initialisation call has completed successfully.
     */
    bool m_initialised;

    /**
     * This gets marked when the initialisation call has completed but needs to be rerun
     * because the current version number is now different from the file.
     */
    bool m_updateInheritedStoreRequired;

    /**
     * This gets marked as soon as any attributes are changed within a transaction.
     * The attribute to do list only copes with 1 version, hence this enforces that we don't
     * change the version mid transaction.
     */
    bool m_prohibitSchemaVersionChange;

    /**
     * This holds all the attributes over all versions
     */
    std::map<NvStoreSchemaVersion, NvStoreMap> m_nvCompleteAttributeStore;

    /**
     * This is the attribute store after compressing down the current and all
     * previous schemas to make accessing current values quicker.  Each
     * attribute indicates from which schema it was taken and will be the
     * latest available in NV up to and including the current schema.
     */
    NvStoreMap m_nvInheritedAttributeStore;

    /**
     * This holds all the attributes to be added or overwrite into the current attribute store.
     * These attributes will be written when ForceNvFlush is called.
     */
    NvStoreMap m_nvAttributesTodo;
    
    /**
	 * This holds the containers that are used with the delete transactions. There are 2
     * types of delete transaction; Delete and Reset.
     * Delete: Any container attribute combinations stored here will be deleted. Everything else will be spared.
     * Reset: Any container attribute combinations stored here will be saved. Everything else will be deleted.
     */
    std::map<NvContainerDescriptor, std::vector<NvAttributeDescriptor> > m_nvAttributesMarked;
    std::vector<NvContainerDescriptor> m_nvContainersMarked;

    /**
     * Should we consider our NV file read-only?
     */
    bool m_forceReadOnly;

    /**
     * Only save the file if something has changed
     */
    bool m_doSave;
};

#endif
