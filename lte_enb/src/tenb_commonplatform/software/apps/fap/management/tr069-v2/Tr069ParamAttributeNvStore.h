/*********************************************************************17*/
/**********************************************************************

Name:     Parameter Attribute Non Volatile Store - Tr069ParamAttributeNvStore.h

Type:     header file

Desc:     Stores the notification attribute of parameters configured from ACS so that the 
value persist across reboot. Notification type can be "Active, Passive or no notification"
This file can be further enhanced to store other attributes in future.

File:     ParamAttributeNvStore.h

 ***********************************************************************/

#ifndef __Tr069ParamAttributeNvStore_h_
#define __Tr069ParamAttributeNvStore_h_

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////
#include <fstream>
#include <mib-core/NonVolatileStoreInterface.h>
#include <mib-common/MibDN.h>
#include <system/StringUtils.h>

#include "DataModelTypes.h"

using namespace tr069;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

typedef std::map <NvAttributeDescriptor, ExtDMAttrNotificationType> NvParamAttributeMap;
typedef std::map<NvContainerDescriptor, NvParamAttributeMap > NvStoreMap;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class Tr069ParamAttributeNvStore 
{
   public:
      /**
       * Default constructor.
       */
      Tr069ParamAttributeNvStore();

      /**
       * Destructor.
       */
      virtual ~Tr069ParamAttributeNvStore();

      /**
       * Implement NonVolatileStoreUpgradeDowngradeInterface.
       */
      void InitialiseParamAttributeNvStore();
      bool IsNvAttributePresent(const NvContainerDescriptor& nvContainerDescriptor,
            const NvAttributeName& nvAttributeName) const;
      /**
       * Set the filename to be used in initialising the store
       */
      void SetParamAttStoreFileName(const std::string & nvStoreFileName) { m_nvStoreFileName = nvStoreFileName; };
      NvAttributeResult GetParamAttributeNvVal(MibDN dn, string name, ExtDMAttrNotificationType& notify);
      NvAttributeResult GetParamAttributeNvVal(const NvContainerDescriptor& nvContainerDescriptor,
            const NvAttributeDescriptor& nvAttributeDescriptor,
            ExtDMAttrNotificationType& nvNotificationType) const;
      void SetParamAttributeNvVal(MibDN dn, string name, ExtDMAttrNotificationType notify);
      void SetParamAttributeNvVal(const NvContainerDescriptor& nvContainerDescriptor,
            const NvAttributeDescriptor& nvAttributeDescriptor,
            ExtDMAttrNotificationType& nvNotificationType);
      NvContainerDescriptor GetNvContainerDescriptor(const MibDN& dn);
      void DeleteNvAttributes(MibDN dn);
      void DeleteNvAttributes(NvContainerDescriptor& nvContainerDescriptor,
            const vector<NvAttributeDescriptor>& nvAttributeDescriptors);
      /**
       * Allow a function with this prototype to access the private member variables
       */
      friend std::ostream & operator<<(std::ostream & os, const Tr069ParamAttributeNvStore &nvStore);
      friend std::ostream & operator<<(std::ostream & os, const NvParamAttributeMap::value_type &nvAttributeMapItem);

   private:
      /**
       * File name to load and save data to in the ini format
       */
      std::string m_nvStoreFileName;
      /**
       * This gets marked when the initialisation call has completed successfully.
       */
      bool m_initialised;

      /*Map to store Attributes of Containers and their notification values*/
      NvStoreMap m_nvParamAttStoreMap;
      void writeToNvFile();

};
#endif

