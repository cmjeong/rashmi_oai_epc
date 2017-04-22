///////////////////////////////////////////////////////////////////////////////
//
// MibManager.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <system/Trace.h>
#include <mib-common/MibObjectDescriptors.h>
#include <unistd.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibAttributes.h"
#include "IniFormatNvStore.h"

#include "MibManager.h"

#define MAX_DIR_LEN 50

using namespace std;
using namespace boost;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

MibManager::MibManager(MibSubscriptionNotifyInterface* subscriptionNotifyInterface) : numOfCells(2)
{
   string numCellStr = threeway::getConfigParam("OAM_NUM_CELL_ENTRIES", "");
   if(NULL != numCellStr.c_str())
   {
      numOfCells = atoi(numCellStr.c_str());
   }
   // Construct a subscription manager if requested.
   nvStoreInitialized = true;

   if(subscriptionNotifyInterface)
   {
      m_subscriptionManager.reset(new MibSubscriptionManager(*this, *subscriptionNotifyInterface));
   }

   string nvStorePath, factoryNvStoreFileName, operationalNvStoreFileName;

   shared_ptr<IniFormatNvStore> operationalNvStore(new IniFormatNvStore());

   m_operationalNvStore = dynamic_pointer_cast<NonVolatileStoreInterface>(operationalNvStore);

   UpdateNvDirPath("OAM_NV_DIR_PATH");
   nvStorePath = m_sOamConfigFilesDir + "/" ;

   factoryNvStoreFileName = nvStorePath + "mib-factory.nv";
#if defined(PRODUCT_hbs2_iu) || defined(PRODUCT_hbs2_factory)|| defined(PRODUCT_generic)
   operationalNvStoreFileName = nvStorePath + "mib-home-fap.nv";
#else
   operationalNvStoreFileName = nvStorePath + "mib-standalone.nv";
#endif

   operationalNvStore->SetStoreFileName(factoryNvStoreFileName);

   if(NULL != operationalNvStore)
   {
      if(!(operationalNvStore->InitialiseNvStore()))
      {
         nvStoreInitialized = false;
      }
   }
  UpdateNvDirPath("OAM_CONFIG_FILES_DIR");
  nvStorePath = m_sOamConfigFilesDir + "/config/" ;
  operationalNvStoreFileName = nvStorePath + "mib-home-fap.nv";
  operationalNvStore->SetStoreFileName(operationalNvStoreFileName); 
  ifstream activeNvfile(operationalNvStoreFileName.c_str());
  if(activeNvfile && (NULL != operationalNvStore))
  {
      if(!(operationalNvStore->InitialiseNvStore()))
      {
            nvStoreInitialized = false;
      }
  }
}

MibManager::~MibManager()
{
}

void MibManager::CreateObject(const MibDN& parent, const MibRDN & childRdn)
{
   MibAttributeValues attributeValues;
   CreateObject(parent, childRdn, attributeValues);
   TRACE_PRINTF("MibManager::CreateObject Trying to create having child only \"%s\" on \"%s\" child ",parent.ToString().c_str(),childRdn.ToString().c_str());
}

void MibManager::CreateObject(const MibDN& parent, const MibRDN & childRdn, const MibAttributeValues& attributeValues)
{
   bool isPresent = true;

   shared_ptr<MibObject> parentMibObject;
   MibObjectClass parentObjectClass = MIB_OBJECT_CLASS_INVALID;
   TRACE_PRINTF("MibManager::CreateObject Trying to create having attribute \"%s\" for \"%s\" attributes",parent.ToString().c_str(),childRdn.ToString().c_str());

   // Validate the parent node, if present
   if (not(parent.empty()))
   {
      TRACE_PRINTF("MibManager::CreateObject inside parent empty \"%s\" on \"%s\" child ",parent.ToString().c_str(),childRdn.ToString().c_str());
      RSYS_ASSERT_PRINTF(m_mibRoot.get() != NULL, "CreateObject \"%s\" on \"%s\" failed.",parent.ToString().c_str(), childRdn.ToString().c_str());
      weak_ptr<MibObject> mo = FindMibObjectNoAssert(parent, isPresent);
      if(isPresent)
      {
         parentMibObject = mo.lock();
         RSYS_ASSERT(parentMibObject != NULL);
         parentObjectClass = parentMibObject->GetRDN().GetMibObjectClass();
      }
      else
      {
         TRACE_PRINTF("MO not found.");
      }
   }
   else
   {
      TRACE_PRINTF("MibManager::CreateObject outside parent empty \"%s\" on \"%s\" child ",parent.ToString().c_str(),childRdn.ToString().c_str());
      RSYS_ASSERT_PRINTF(m_mibRoot.get() == NULL, "CreateObject \"%s\" on \"%s\" failed.",parent.ToString().c_str(), childRdn.ToString().c_str());
      TRACE_PRINTF("MibManager::CreateObject failed after mibRoot.get \"%s\" on \"%s\" child ",parent.ToString().c_str(),childRdn.ToString().c_str());
      parentObjectClass = MIB_OBJECT_CLASS_ROOT;
   }

   // Find MO descriptor
   const MibManagedObjectDescriptor* moDescriptor = getManagedObjectDescriptor(childRdn.GetMibObjectClass());

   if(NULL != moDescriptor)
   {
      TRACE_PRINTF("MibManager objectName %s",moDescriptor->mibObjectName);
      // Ensure that the parent MO also matched.
      RSYS_ASSERT_PRINTF(parentObjectClass == moDescriptor->validParentClass, "parentObjectClass=%s, validParentClass=%s",
            MibObjectClassToString(parentObjectClass),
            MibObjectClassToString(moDescriptor->validParentClass));
   }

   // Create the MibObject
   // Use the appropriate NV store based on object name... could do this by tagging MOs in XML with their NV store but seems overkill for now.
   shared_ptr<MibObject> currentMibObject;
   MibChangedAttributesNotifyInterface* changedAttributesNotifyInterface = NULL;
   if(m_subscriptionManager != NULL)
   {
      // We pass a normal pointer to MibObject but we own them and the subscription manager.
      changedAttributesNotifyInterface = m_subscriptionManager.get();
   }

   if(NULL != moDescriptor)
   {
         currentMibObject.reset(new MibObject(childRdn, *m_operationalNvStore, changedAttributesNotifyInterface)); // TODO: Ooo, bit mucky as nv store is shared_ptr...
         TRACE_PRINTF("MibManager outside modesc %s",moDescriptor->mibObjectName);
   }

   // Attach MibObject to parent
   if (parent.empty())
   {
      m_mibRoot = currentMibObject;
   }
   else if(parentMibObject->FindChildObject(currentMibObject->GetRDN())==NULL)
   {
      parentMibObject->AddChildObject(currentMibObject);
   }
   else
   {
      TRACE_PRINTF("Object Already Exists in NV file");
   }

   // Initialise the new MO.
   MibAttrValidationFailures mibAttrValidationFailures = currentMibObject->InitialiseMO(attributeValues);
   RSYS_ASSERT_PRINTF(mibAttrValidationFailures.size() == 0,
         "Validation failures while creating %s on %s: %s",
         childRdn.ToString().c_str(), parent.ToString().c_str(),
         mibAttrValidationFailures.ToString().c_str());

}

MibObjectDeleteResult MibManager::DeleteObject(const MibDN& dnToDelete)
{
   bool isPresent = true;

   MibObjectDeleteResult result = MIB_OBJ_DEL_INVALID;
   // Check exists.
   weak_ptr<MibObject> mibObjectWeak = FindMibObjectNoAssert(dnToDelete, isPresent);
   shared_ptr<MibObject> mibObject = mibObjectWeak.lock();

   if(mibObject && isPresent)
   {
      // Check no children.
      if(!mibObject->HasChildren())
      {
         mibObject->DeleteMibObject();

         MibObject* parentObject = mibObject->GetParentObject();

         result = MIB_OBJ_DEL_SUCCESS;

         if(parentObject == NULL)
         {
            // Deleting root object.
            m_mibRoot.reset();
         }
         else
         {
            parentObject->DeleteChildObject(dnToDelete.back());
         }

         MibChangedAttributesNotifyInterface* changedAttributesNotifyInterface = NULL;
         if(m_subscriptionManager != NULL)
         {
            // We pass a normal pointer to MibObject but we own them and the subscription manager.
            changedAttributesNotifyInterface = m_subscriptionManager.get();
            if(changedAttributesNotifyInterface)
            {
               MibAttributeIds mibAttributeIds;

               changedAttributesNotifyInterface->HandleDeletedAttributes(dnToDelete, mibAttributeIds);
            }
         }
      }
      else
      {
         TRACE_PRINTF("MibManager::DeleteObject Trying to delete %s but it has children", dnToDelete.ToString().c_str());
         result = MIB_OBJ_DEL_OBJECT_HAS_CHILDREN;
      }
   }
   else
   {
      TRACE_PRINTF("MibManager::DeleteObject Trying to delete %s but it doesn't exist", dnToDelete.ToString().c_str());
      result = MIB_OBJ_DEL_OBJECT_NOT_FOUND;
   }

   return result;
}

weak_ptr<MibObject> MibManager::FindMibObjectNoAssert(const MibDN& dn, bool &isPresent) const
{
   return FindMibObjectByRelativeDnNoAssert(dn, m_mibRoot, isPresent);
}

weak_ptr<MibObject> MibManager::FindMibObject(const MibDN& dn) const
{
   return FindMibObjectByRelativeDn(dn, m_mibRoot);
}

MibAttrValidationFailures MibManager::ValidateAttributes(const MibDN& moDn, const MibAttributeValues& attributeValues, bool checkAccessClass) const
{
   bool isPresent = true;

   MibAttrValidationFailures failureDescriptors;

   // Find the MO.
   weak_ptr<MibObject> mo = FindMibObjectNoAssert(moDn, isPresent);

   shared_ptr<MibObject> moLocked = mo.lock();
   if((moLocked != NULL) && isPresent)
   {
      // Found the object.
      failureDescriptors = moLocked->ValidateAttributes(attributeValues, checkAccessClass);
   }
   else
   {
      MibAttrValidationFailure failure(PARAM_ID_INVALID);
      string desc = "MO not found: ";
      desc += moDn.ToString();
      failure.Set(ValidationFailureDescriptor::CAUSE_OBJECT_DOES_NOT_EXIST, desc);
      failureDescriptors.push_back(failure);
   }

   return failureDescriptors;
}

void MibManager::SetAttributes(const MibDN& moDn, const MibAttributeValues& attributeValues , bool checkAccessClass)
{
   bool isPresent = true;

   // Find the MO.
   weak_ptr<MibObject> mo = FindMibObjectNoAssert(moDn, isPresent);

   if(isPresent)
   {
      shared_ptr<MibObject> moLocked = mo.lock();

      RSYS_ASSERT_PRINTF(moLocked != NULL, "MO not found %s", moDn.ToString().c_str());

      // Found the object.
      moLocked->SetMibAttributes(attributeValues , checkAccessClass);
   }
}

void MibManager::ResetNvToFactoryDefaults()
{
   string val = threeway::getConfigParam("OAM_CONFIG_FILES_DIR", "");
   std::string sOamConfigFilesDir;
   string tracePath = threeway::getConfigParam("OAM_LOGGING_DIR", "");
   ostringstream command;
   command <<"cd " << sOamConfigFilesDir.c_str() << " && rm -rf config && cd " << tracePath.c_str() << " && rm -f *";
   TRACE_PRINTF("Factory Reset Command : %s", command.str().c_str());
   if(system(command.str().c_str()) != false)
   {
      TRACE_MSG("ResetNvToFactoryDefaults::Factory Reset command Failed");
   }
}

void MibManager::GetAttributes(const MibDN& moDn, const MibAttributeIds& attributeIds, MibAttributeValues& mibAttributeValues) const
{
   bool isPresent = true;

   // Preconditions.
   // Start with an empty container.
   RSYS_ASSERT_PRINTF(mibAttributeValues.GetAttributeCount() == 0, "%s", moDn.ToString().c_str());

   // Find the MO.
   weak_ptr<MibObject> mo = FindMibObjectNoAssert(moDn, isPresent);

   shared_ptr<MibObject> moLocked = mo.lock();
   if((moLocked != NULL) && isPresent)
   {
      // Found the object.
      // TODO: worry about a return value from this?  failure codes?
      moLocked->GetMibAttributes(attributeIds, mibAttributeValues);
   }
   else
   {
      // TODO: What to do?
      TRACE_PRINTF_LEV(TRACE_WARNING, "MO doesn't exist: %s", moDn.ToString().c_str());
   }
}

void MibManager::DeleteAttributes(const MibDN& moDn, const MibAttributeIds& attributeIds)
{
   bool isPresent = true;

   // Find the MO.
   weak_ptr<MibObject> mo = FindMibObjectNoAssert(moDn, isPresent);

   shared_ptr<MibObject> moLocked = mo.lock();
   if((moLocked != NULL) && isPresent)
   {
      // Found the object.
      // TODO: worry about a return value from this?  failure codes?
      moLocked->DeleteMibAttributes(attributeIds);
   }
   else
   {
      // TODO: What to do?
      TRACE_PRINTF_LEV(TRACE_WARNING, "MO doesn't exist: %s", moDn.ToString().c_str());
   }
}

void MibManager::GetAttributesDiffFromDefaults(MibAttributeValuesByDn& diffFromDefaultValuesByDn)
{
   RSYS_ASSERT(m_mibRoot != NULL);

   diffFromDefaultValuesByDn.clear();

   // TODO: Extend to child objects.
   MibDN dn = m_mibRoot->GetDN();
   MibAttributeValues attributeValues;
   m_mibRoot->GetMibAttributesDiffFromDefaults(attributeValues);
   diffFromDefaultValuesByDn.insert(make_pair(dn, attributeValues));
}

void MibManager::GetAttributesSetInNv(MibAttributeValuesByDn& setInNvValuesByDn)
{
   RSYS_ASSERT(m_mibRoot != NULL);

   setInNvValuesByDn.clear();

   // TODO: Extend to child objects.
   MibDN dn = m_mibRoot->GetDN();
   MibAttributeValues attributeValues;
   m_mibRoot->GetMibAttributesSetInNv(attributeValues);
   setInNvValuesByDn.insert(make_pair(dn, attributeValues));
}

void MibManager::AddSubscription(
      u32 subscriberId,
      const char * subscriberName,
      u32 subscriptionId,
      const MibAttributeIdsByDn& subscribedAttributes,
      const MibObjectClassesByDn& subscribedObjects)
{
   RSYS_ASSERT(m_subscriptionManager != NULL);

   TRACE_PRINTF("Adding subscription: subscriberId=%"PRIu32"(%s), subscriptionId=%"PRIu32", Attr=%s, Obj=%s",
         subscriberId, subscriberName, subscriptionId, subscribedAttributes.ToString().c_str(), subscribedObjects.ToString().c_str() );

   m_subscriptionManager->AddSubscription(subscriberId, subscriberName, subscriptionId, subscribedAttributes, subscribedObjects);
}

void MibManager::RemoveSubscription(u32 subscriberId, u32 subscriptionId)
{
   RSYS_ASSERT(m_subscriptionManager != NULL);

   TRACE_PRINTF("Removing subscription: subscriberId=%"PRIu32", subscriptionId=%"PRIu32,
         subscriberId, subscriptionId);

   if(m_subscriptionManager->RemoveSubscription(subscriberId, subscriptionId) != MibSubscriptionManager::REMOVE_SUBSCRIPTION_OK)
   {
      TRACE_PRINTF_LEV(TRACE_WARNING,
            "Failed to remove subscription (not found?): subscriberId=%"PRIu32", subscriptionId=%"PRIu32,
            subscriberId, subscriptionId);
   }
}

std::string MibManager::SubscriptionsToString() const
{
   if(m_subscriptionManager)
   {
      return m_subscriptionManager->ToString();
   }

   return "No subscription manager.";
}

weak_ptr<MibObject> MibManager::FindMibObjectByRelativeDn(MibDN dn, shared_ptr<MibObject> current) const
{
   RSYS_ASSERT(not(dn.empty())); // should never be empty
   RSYS_ASSERT(current != NULL);

   while (dn.size() > 1 && current)
   {
      RSYS_ASSERT(dn.front() == current->GetRDN()); // first should always be equal

      // Remove current RDN from the list
      dn.pop_front();

      // Move onto next MibObject
      current = current->FindChildObject(dn.front());
   }

   if(current)
   {
      // First should always be equal to current RDN.
      RSYS_ASSERT_PRINTF(dn.front() == current->GetRDN(),
            "dn=%s, current=%s",
            dn.ToString().c_str(), current->GetDN().ToString().c_str());
   }

   weak_ptr<MibObject> result(current);

   return result;
}

weak_ptr<MibObject> MibManager::FindMibObjectByRelativeDnNoAssert(MibDN dn, shared_ptr<MibObject> current, bool &isPresent) const
{
   RSYS_ASSERT(not(dn.empty())); // should never be empty
   RSYS_ASSERT(current != NULL);

   while (dn.size() > 1 && current)
   {
      RSYS_ASSERT(dn.front() == current->GetRDN()); // first should always be equal

      // Remove current RDN from the list
      dn.pop_front();

      // Move onto next MibObject
      current = current->FindChildObject(dn.front());
   }

   if(current)
   {
      // First should always be equal to current RDN.
      if(!(dn.front() == current->GetRDN()))
      {
         isPresent = false;
      }
   }

   weak_ptr<MibObject> result(current);

   return result;
}

void MibManager::UpdateNvDirPath(const char *path)
{
   string val = threeway::getConfigParam(path, "");

   m_pOamConfigFilesDir = (char *)val.c_str();

   if(NULL != m_pOamConfigFilesDir)
   {
      m_sOamConfigFilesDir = m_pOamConfigFilesDir ;
   }
   m_sOamConfigFilesDir = m_sOamConfigFilesDir ;
}
