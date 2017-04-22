///////////////////////////////////////////////////////////////////////////////
//
// Tr069MultiInstanceObject.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <mib-core/MibObject.h>
#include <mib-common/messages/MibDeleteObjectReq.h>
#include <mib-common/MIOAutoManage.h>
///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069Application.h"
#include "Tr069MultiInstanceMibObject.h"
#include "Tr069ParameterValueChangeNotificationManager.h"

using namespace std;
using namespace tr069;

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////
namespace tr069
{
   FreqCellMap CellMap;

   FreqCellInfo FreqCellDetails[] =
   {
      {
         "LTE_RAN_MOB_IDLE_MODE_INTER_FREQ_CARRIER",
         {
            PARAM_ID_LTE_INTER_FREQ_DL_EARFCN,
            MIB_OBJECT_CLASS_LTE_RAN_NEIGH_LIST_LTE_CELL,
            PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_EARFCN
         }
      },
      {
         "LTE_INTER_RAT_GERAN_NEIGHBOR_FREQ_LIST",
         {
            PARAM_ID_LTE_GERAN_FREQ_BCCH_ARFCN,
            MIB_OBJECT_CLASS_LTE_INTER_RAT_GERAN_NEIGHBOR_CELL_LIST,
            PARAM_ID_LTE_GERAN_CELL_BCCH_ARFCN
         }
      },
      {
         "LTE_TDS_CDMA_UTRAN_TDD_FREQ_LIST",
         {
            PARAM_ID_LTE_TDS_CDMA_UTRA_ARFCN,
            MIB_OBJECT_CLASS_LTE_TDS_CDMA_UTRAN_TDD_CELL_LIST,
            PARAM_ID_LTE_TDS_CDMA_UARFCN
         }
      },
      {
         "UTRA_UTRAN_FDD_FREQ",
         {
            PARAM_ID_LTE_UTRA_FDD_CARRIER_ARFCN,
            MIB_OBJECT_CLASS_LTE_UMTS_NEIGHBOR,
            PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_UARFCNDL
         }
      }
   };


   Tr069MultiInstanceObject::Tr069MultiInstanceObject( SendMessageInterface & messenger, MibAccessInterface& mib, MultiInstanceObjectDefintion  mioDef ) :
      m_messenger(messenger),
      m_mib(mib),
      m_mioDef(mioDef),
      m_previousMibInstance(s32(-1)),
      m_currentEntries(0),
      m_maxEntries(0),
      m_rolling(0),
      m_numObj(0)
   {
      m_parentDn = MibDN::GenerateMibDN( string(m_mioDef.Mib.parentDn) );
      const MibManagedObjectDescriptor* mibManagedObjectDescriptor = getManagedObjectDescriptor( m_parentDn.back().GetMibObjectClass() );

      if(mibManagedObjectDescriptor)
      {
         for(u32 idx = 0; idx < mibManagedObjectDescriptor->validChildClassesNum; ++idx)
         {
            // Needs other branch to allow to compile
            if(mibManagedObjectDescriptor->validChildClasses[idx].validChildClass == m_mioDef.Mib.childClass )
            {

               //Update Max instances of alarms as it does not have mib parameter for the same.
               if( (m_mioDef.Mib.childClass == MIB_OBJECT_CLASS_TR196_CURRENT_ALARM) ||
                     (m_mioDef.Mib.childClass == MIB_OBJECT_CLASS_TR196_EXPEDITED_EVENT) )
               {
                  //Expedited ,Queued and Current have max of 50
                  m_maxEntries = MAX_EXPEDITED_ALARMS; 
               }
               else if(m_mioDef.Mib.childClass == MIB_OBJECT_CLASS_TR196_HISTORY_EVENT) 
               {
                  m_maxEntries = MAX_HISTORY_ALARMS;
               }
               else
               {
                  MibAttributeId PARAM_ID_MAX_ENTRIES;
                  if(MIOAutoManage::GetInstance().getMaxEntriesParamName(m_mioDef.Mib.childClass,PARAM_ID_MAX_ENTRIES))
                  {
                     MIOAutoManage::GetInstance().getMaxEntriesParamName(m_mioDef.Mib.childClass,PARAM_ID_MAX_ENTRIES);
                     Tr069Application::GetInstance().GetMibCache().GetMibAttribute(m_parentDn, PARAM_ID_MAX_ENTRIES,m_maxEntries);
                  }
                  else
                  {
                     m_maxEntries = mibManagedObjectDescriptor->validChildClasses[idx].maxInstances;
                  }
               }
               //Update m_rolling for MIO that need circular insertion on reaching max entries
               if(MIOAutoManage::GetInstance().isNeedCircularInsertion(MibObjectClassToString(m_mioDef.Mib.childClass)))
               {
                  m_rolling = true;
               }
            }
         }
      }
   }

   Tr069MultiInstanceObject::~Tr069MultiInstanceObject()
   {

   }

   shared_ptr<MibCreateObjectReq> Tr069MultiInstanceObject::New( MibAttributeValues & attr)
   {
      shared_ptr<MibCreateObjectReq> mibCreateObjectReq;
      std::vector<u32> geranSrcLst;
      std::vector<u32> tdsCdmaSrcLst;
      std::vector<u32> plmnSrcLst;
      std::vector<u32> umtsNbrInuseSrcLst,umtsNbrSrcLst;
      set<u32> currentInstances = m_mib.GetMibObjectInstances(m_parentDn, m_mioDef.Mib.childClass);
      u32 numEntries;
      if( m_rolling && m_previousMibInstance != -1)
      {
         s32 instanceToDelete = (m_previousMibInstance + 1) % m_maxEntries;

         Delete(instanceToDelete);

         currentInstances.erase( instanceToDelete );
      }

      if(currentInstances.size() < m_maxEntries)
      {
         s32 newMibInstance = (m_previousMibInstance + 1) % m_maxEntries;
         while( currentInstances.end() != currentInstances.find(newMibInstance) )
         {
            TRACE_PRINTF("AddObject: Searching... (%"PRIu32" already exists).", newMibInstance);
            newMibInstance = (newMibInstance + 1) % m_maxEntries;
         }

         MibRDN childRdn(m_mioDef.Mib.childClass, newMibInstance);
         mibCreateObjectReq.reset(new MibCreateObjectReq(m_parentDn, childRdn, attr));
         TRACE_PRINTF("MibCreateObjectReq=%s", mibCreateObjectReq->ToString().c_str());

         m_previousMibInstance = newMibInstance;
         TRACE_PRINTF("Child dn = %s",childRdn.ToString().c_str());

         MibAttributeValues attrs;
         MibAttributeId PARAM_ID_NUM_INSTNCE,PARAM_ID_SRC_LIST,PARAM_ID_MAX_ENTRIES;

         if(MIOAutoManage::GetInstance().getMaxEntriesParamName(childRdn,PARAM_ID_MAX_ENTRIES))
         {
            MIOAutoManage::GetInstance().getSrcListParamName(childRdn,PARAM_ID_SRC_LIST);
            std::vector<u32> src_list;
            TRACE_PRINTF("setting mibinstance as %d newMibinstance=%d",m_numObj,newMibInstance);

            if(PARAM_ID_INVALID != PARAM_ID_SRC_LIST)
            {
               Tr069Application::GetInstance().GetMibCache().GetMibAttribute(m_parentDn,
                     PARAM_ID_SRC_LIST,src_list);

               if(newMibInstance ==  (u32)oam_ret_zero )
               {
                  src_list[oam_ret_zero] = added;
               }
               else
               {
                  src_list.push_back(added);
               }

               attrs.AddAttribute( PARAM_ID_SRC_LIST,src_list);
            }
         }
         MIOAutoManage::GetInstance().getNumEntriesParamName(childRdn,PARAM_ID_NUM_INSTNCE);
         Tr069Application::GetInstance().GetMibCache().GetMibAttribute(m_parentDn,
               PARAM_ID_NUM_INSTNCE,numEntries);
         numEntries++;
         attrs.AddAttribute( PARAM_ID_NUM_INSTNCE,numEntries);
         Tr069Application::GetInstance().GetMibCache().SetMibAttributes(m_parentDn,
               attrs, ENTITY_TR069);
         TRACE_PRINTF("Child dn = %s",childRdn.ToString().c_str());

      }
      // If instance reaches the highest instance range, reset to zero.
      else
      {
         TRACE_PRINTF("%s: Instance reached highest instance range",__FUNCTION__);
         MibRDN childRdn(m_mioDef.Mib.childClass, m_previousMibInstance);

         if((childRdn.ToString().find("TR196_SUPPORTED_ALARM") != string::npos) || 
               (childRdn.ToString().find("QUEUED_EVENT") != string::npos) ||
               (childRdn.ToString().find("TR196_CURRENT_ALARM") != string::npos) ||
               (childRdn.ToString().find("TR196_HISTORY_EVENT") != string::npos) ||
               (childRdn.ToString().find("TR196_EXPEDITED_EVENT") != string::npos))
         {
            s32 instanceToDelete = (m_previousMibInstance + 1) % m_maxEntries;
            Delete(instanceToDelete);
            currentInstances.erase( instanceToDelete );

            u32 newMibInstance = instanceToDelete;
            MibRDN childRdn(m_mioDef.Mib.childClass, newMibInstance);
            mibCreateObjectReq.reset(new MibCreateObjectReq(m_parentDn, childRdn, attr));
            TRACE_PRINTF("MibCreateObjectReq =%s with instance %d", mibCreateObjectReq->ToString().c_str(),newMibInstance);
            m_previousMibInstance = newMibInstance;
         }
      }
      return mibCreateObjectReq;
   }

   void SetFreqCellMap()
   {
      int size = sizeof(FreqCellDetails)/sizeof(FreqCellInfo) ;
      for(int freqElem = 0; freqElem < size ; freqElem++)
      {
         CellMap.insert(pair<string,CellInfo *>(FreqCellDetails[freqElem].freq,&FreqCellDetails[freqElem].cellinfo));
      }
   }

   bool Tr069MultiInstanceObject::ValidateFreqCell(MibDN dn)
   {
      SetFreqCellMap();
      struct CellInfo *val;
      string freqstr;
      u32 freq,cellfreq;
      for(map<string,struct CellInfo *>::iterator itr = CellMap.begin(); itr != CellMap.end(); ++itr )
      {
         freqstr = itr->first;
         if(strstr(dn.ToString().c_str(),freqstr.c_str()))
         {  
            MibDN cellDn;
            MibAttributeId PARAM_ID_MAX_ENTRIES;
            u32 maxinstances;
            val = itr->second;
            MIOAutoManage::GetInstance().getMaxEntriesParamName(val->cellObjectClass,PARAM_ID_MAX_ENTRIES);
            m_mib.GetMibAttribute(m_parentDn,PARAM_ID_MAX_ENTRIES, maxinstances);
            m_mib.GetMibAttribute(dn,val->freqname,freq);

            for(u32 dnInstance = 0 ; dnInstance < maxinstances  ; dnInstance++)
            {
               cellDn =  MibDN::GenerateMibDN(m_parentDn,val->cellObjectClass,dnInstance);
               if(m_mib.IsMibObjectPresent(cellDn))
               {
                  m_mib.GetMibAttribute(cellDn,val->cellfreq,cellfreq);
                  if(freq == cellfreq)
                  {
                     TRACE_PRINTF("Unable To Delete Freq.Cell Already Exists");
                     return false;
                  }
               }
            }
         }
      }
      return true;
   }

   bool Tr069MultiInstanceObject::Delete( u32 instance)
   {
      MibDN dn = m_parentDn;
      std::vector<u32> geranSrcLst;
      std::vector<u32> tdsCdmaSrcLst;
      std::vector<u32> plmnSrcLst;
      u32 numEntries;
      MibAttributeId PARAM_ID_NUM_INSTNCE,PARAM_ID_SRC_LIST;
      MibAttributeValues attrs;

      dn.push_back(MibRDN(m_mioDef.Mib.childClass, instance));
      MibRDN childRdn(m_mioDef.Mib.childClass, instance);
      if (m_mib.IsMibObjectPresent(dn))
      {
         if(ValidateFreqCell(dn))
         {

            MIOAutoManage::GetInstance().getNumEntriesParamName(childRdn,PARAM_ID_NUM_INSTNCE);
            Tr069Application::GetInstance().GetMibCache().GetMibAttribute(m_parentDn,PARAM_ID_NUM_INSTNCE,numEntries);
            numEntries--;
            attrs.AddAttribute( PARAM_ID_NUM_INSTNCE,numEntries);
            if(MIOAutoManage::GetInstance().getSrcListParamName(childRdn,PARAM_ID_SRC_LIST))
            {
               if(PARAM_ID_SRC_LIST != PARAM_ID_INVALID)
               {
                  std::vector<u32> src_list;
                  Tr069Application::GetInstance().GetMibCache().GetMibAttribute(m_parentDn,PARAM_ID_SRC_LIST,src_list);
                  src_list[instance] = deleted;
                  attrs.AddAttribute( PARAM_ID_SRC_LIST,src_list);
               }
            }

            Tr069Application::GetInstance().GetMibCache().SetMibAttributes(m_parentDn,attrs, ENTITY_TR069);
            //Delete from mib attribute NV store that stores notification attribute
            Tr069Application::GetInstance().GetParamAttNvStore()->DeleteNvAttributes(dn);
            MibDeleteObjectReq mibDeleteObjectReq(dn);
            m_messenger.SendMessage(mibDeleteObjectReq, ENTITY_MIB, ENTITY_TR069 );
         }
         else
         {
            return false;
         }
      }
      else if(strstr(dn.ToString().c_str(),"LTE_RAN_NEIGH_LIST_LTE_CELL"))
      {
            MibDeleteObjectReq mibDeleteObjectReq(dn);
            m_messenger.SendMessage(mibDeleteObjectReq, ENTITY_MIB, ENTITY_TR069 );
      }
      return true;
   }

   u32 Tr069MultiInstanceObject::GetNumberOfEntries()
   {
      return m_mib.GetMibObjectCount(m_parentDn, m_mioDef.Mib.childClass);
   }

   u32 Tr069MultiInstanceObject::GetMaxEntries()
   {
      return m_maxEntries;
   }

   void Tr069MultiInstanceObject::SubscribeToMib( u32 subId )
   {
      // Object subscriptions
      MibAttributeIdsByDn attributeIdsByDn;
      MibObjectClassesByDn objectClassesByDn;

      objectClassesByDn[m_parentDn].insert(m_mioDef.Mib.childClass);

      m_mib.SubscribeMibAttributes(
            subId,
            ENTITY_TR069,
            attributeIdsByDn,
            objectClassesByDn,
            true);
   }

   void Tr069MultiInstanceObject::MibUpdated()
   {
      u32 mibContentCount = m_mib.GetMibObjectCount(m_parentDn, m_mioDef.Mib.childClass);

      TRACE_PRINTF("Tr069MultiInstanceObject::MibUpdated(%s=%"PRIu32")",m_mioDef.DataModel.currentEntriesParameter, mibContentCount);

      if(m_currentEntries != mibContentCount)
      {
         m_currentEntries = mibContentCount;

         Tr069ParameterValueChangeNotificationManager::GetInstance().NotificationValueChange(m_mioDef.DataModel.currentEntriesParameter);
      }
   }

   bool Tr069MultiInstanceObject::check_if_instance_exist(u32 instance)
   {
      set<u32> currentInstances = m_mib.GetMibObjectInstances(m_parentDn, m_mioDef.Mib.childClass);
      if (currentInstances.find(instance)!=currentInstances.end())
         return true;
      else      
         return false;

   }

}
MibObjectClass Tr069MultiInstanceObject::GetChildClass()
{
   return m_mioDef.Mib.childClass;
}
