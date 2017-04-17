#ifndef __MIOAutoManage_h_
#define __MIOAutoManage_h_

#include<string>
#include <mib-common/MibAttributeValues.h>
#include <mib-common/MibObjectClassesByDn.h>
#include <MibAttributeId.h>
#include <mib-common/MibDN.h>

#define MIB_OBJECT_CLASS_STR_LENGTH 17 //length of string "MIB_OBJECT_CLASS_"

class MIOAutoManage
{
   enum {
      READ_ONLY,
      READ_WRITE
   }AccessMode;
   typedef struct MIO_Manage_enlements
   {
      MibObjectClass mibObjectClass;
      MibAttributeId numEntries;
      MibAttributeId src;
      MibAttributeId maxEntries;
      u32  accessMode;
   }MIO_Manage;
   u32 m_accessMode;

   typedef struct MIOCircularInsertion
   {
      const char *dnString;
   }MIOs_Needed_CircularInsertion;

   std::map<std::string,MibObjectClass> MappingMibObjClass;

   std::vector<std::string>mibObjectNameIndex;

   bool  getMIOManageInfo( std::string mibObjClassName, MibAttributeId &numEntries,
         MibAttributeId &src_list, MibAttributeId &maxEntries, MibObjectClass &className )
   {
      static  bool  indexingConfigiured = false;

      static MIO_Manage_enlements m_MIO_Manage_elements[]=
      {
         {
            MIB_OBJECT_CLASS_LTE_RAN_NEIGH_LIST_LTE_CELL,
            PARAM_ID_LTE_CELL_ENTRIES,
            PARAM_ID_LTE_X_RADISYS_LTE_CELL_SRC,
            PARAM_ID_LTE_MAX_LTE_CELL,
            READ_WRITE
         },
         {
            MIB_OBJECT_CLASS_LTE_RAN_MOB_IDLE_MODE_INTER_FREQ_CARRIER,
            PARAM_ID_LTE_NUM_CARRIER_ENTRIES_IDLE,
            PARAM_ID_LTE_X_RADISYS_NEIGH_FREQ_SRC,
            PARAM_ID_LTE_MAX_CARRIER_ENTRIES_IDLE,
            READ_WRITE
         },
         {
            MIB_OBJECT_CLASS_LTE_INTER_RAT_GERAN_NEIGHBOR_FREQ_LIST,
            PARAM_ID_LTE_GERAN_NUM_FREQ_ENTRIES,
            PARAM_ID_LTE_GERAN_FREQ_SRC,
            PARAM_ID_LTE_GERAN_MAX_FREQ_ENTRIES,
            READ_WRITE
         },
         {
            MIB_OBJECT_CLASS_LTE_UMTS_NEIGHBOR_IN_USE,
            PARAM_ID_LTE_UMTS_IN_USE_NUMBER_OF_ENTRIES,
            PARAM_ID_INVALID,
            PARAM_ID_LTE_MAX_UMTS_IN_USE_ENTRIES,
            READ_ONLY
         },
         {
            MIB_OBJECT_CLASS_LTE_UMTS_NEIGHBOR,
            PARAM_ID_LTE_NUM_UTRA_NEIGH_CELLS_ENTRIES,
            PARAM_ID_LTE_UMTS_NEIGHBOUR_LIST_SRC,
            PARAM_ID_LTE_MAX_UMTS_ENTRIES,
            READ_WRITE
         },
         {
            MIB_OBJECT_CLASS_LTE_TDS_CDMA_UTRAN_TDD_FREQ_LIST,
            PARAM_ID_LTE_TDS_CDMA_UTRANTDD_FREQ_NUM_ENTRIES,
            PARAM_ID_LTE_TDS_CDMA_FREQ_SRC,
            PARAM_ID_LTE_TDS_CDMA_MAX_UTRANTDD_FREQ_ENTRIES,
            READ_WRITE
         },
         {
            MIB_OBJECT_CLASS_LTE_TDS_CDMA_UTRAN_TDD_CELL_LIST,
            PARAM_ID_LTE_TDS_CDMA_UMTSTDD_NUM_ENTRIES,
            PARAM_ID_LTE_TDS_CDMA_CELL_SRC,
            PARAM_ID_LTE_TDS_CDMA_MAX_UMTSTDD_ENTRIES,
            READ_WRITE
         },
         {
            MIB_OBJECT_CLASS_LTE_CELL_PLMN_LIST,
            PARAM_ID_LTE_NUM_OF_PLMN_ENTRIES,
            PARAM_ID_LTE_CELL_PLMN_SRC,
            PARAM_ID_LTE_MAX_PLMN_ENTRIES,
            READ_WRITE
         },
         {
            MIB_OBJECT_CLASS_CRYPTO_PROFILES,
            PARAM_ID_FAP_TUNNEL_CRYPTO_NUM_ENTRIES,
            PARAM_ID_INVALID,
            PARAM_ID_FAP_TUNNEL_MAX_IKE_SESSIONS,
            READ_WRITE
         },
         {
            MIB_OBJECT_CLASS_LTE_INTER_RAT_GERAN_NEIGHBOR_CELL_LIST,
            PARAM_ID_LTE_GERAN_NUM_CELL_ENTRIES,
            PARAM_ID_LTE_GERAN_CELL_SRC,
            PARAM_ID_LTE_GERAN_MAX_CELL_ENTRIES,
            READ_WRITE
         },
         {
            MIB_OBJECT_CLASS_LTE_NEIGH_EUTRA_IN_USE,
            PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_CELL_ENTRIES,
            PARAM_ID_INVALID,
            PARAM_ID_LTE_OAM_NEIGH_EUTRA_IN_USE_MAX_LTE_CELL,
            READ_ONLY
         },
         {
            MIB_OBJECT_CLASS_LTE_INTER_RAT_GERAN_NEIGHBOR_CELL_IN_USE_LIST,
            PARAM_ID_LTE_GERAN_NUM_CELL_IN_USE_ENTRIES,
            PARAM_ID_INVALID,
            PARAM_ID_LTE_GERAN_MAX_CELL_IN_USE_ENTRIES,
            READ_ONLY
         },
         {
            MIB_OBJECT_CLASS_QUEUED_EVENT,
            PARAM_ID_ALARM_QUEUED_ENTRIES,
            PARAM_ID_INVALID,
            PARAM_ID_INVALID,
            READ_WRITE
         },
         {
            MIB_OBJECT_CLASS_TR196_CURRENT_ALARM,
            PARAM_ID_ALARM_CURRENT_ENTRIES,
            PARAM_ID_INVALID,
            PARAM_ID_ALARM_MAX_CURRENT_ENTRIES,
            READ_WRITE
         },
         {
            MIB_OBJECT_CLASS_TR196_HISTORY_EVENT,
            PARAM_ID_ALARM_HISTORY_ENTRIES,
            PARAM_ID_INVALID,
            PARAM_ID_INVALID,
            READ_WRITE
         },
         {
            MIB_OBJECT_CLASS_TR196_EXPEDITED_EVENT,
            PARAM_ID_ALARM_EXPEDITED_ENTRIES,
            PARAM_ID_INVALID,
            PARAM_ID_INVALID,
            READ_WRITE
         },
         {
            MIB_OBJECT_CLASS_TR196_SUPPORTED_ALARM,
            PARAM_ID_ALARM_SUPPORTED_ENTRIES,
            PARAM_ID_INVALID,
            PARAM_ID_INVALID,
            READ_WRITE
         },
         {
            MIB_OBJECT_CLASS_LTE_REM_SCANNED_CELL,
            PARAM_ID_LTE_NUM_REM_ENTRIES,
            PARAM_ID_INVALID,
            PARAM_ID_LTE_MAX_REM_ENTRIES,
            READ_WRITE
         },
         {
            MIB_OBJECT_CLASS_IP_INTERFACE_IPV6_ADDRESS,
            PARAM_ID_IP_INTERFACE_NUM_IPV6_ADDRESSES,
            PARAM_ID_INVALID,
            PARAM_ID_IP_MAX_IPV6_ENTRIES,
            READ_WRITE
         },
         {
            MIB_OBJECT_CLASS_UTRA_UTRAN_FDD_FREQ,
            PARAM_ID_LTE_NUM_UTRA_NEIGH_FREQ_ENTRIES,
            PARAM_ID_LTE_UTRA_FREQ_NEIGH_SRC,
            PARAM_ID_LTE_MAX_UTRANFDD_FREQ_ENTRIES,
            READ_WRITE
         },
         {
            MIB_OBJECT_CLASS_PERF_MGMT,
            PARAM_ID_PM_CONFIG_NUMBER_OF_ENTRIES,
            PARAM_ID_INVALID,
            PARAM_ID_PM_MAX_INSTANCES,
            READ_WRITE
         }

      };

      if(!indexingConfigiured)
      {
         for(u32 idx=0 ;idx<sizeof(m_MIO_Manage_elements)/sizeof(m_MIO_Manage_elements[0]);idx++)
         {
            const char* mibclass=   MibObjectClassToString(m_MIO_Manage_elements[idx].mibObjectClass);
            ostringstream stream;
            stream << &mibclass[17];
            //            MappingMibObjClass[ stream.str() ] = m_MIO_Manage_elements[idx].mibObjectClass;
            mibObjectNameIndex.push_back(stream.str() );
         }
         indexingConfigiured = true;
      }

      for(u32 idx=0; idx<mibObjectNameIndex.size();idx++)
      {
         if(mibObjClassName.find(mibObjectNameIndex[idx])  != string::npos)
         {
            numEntries = m_MIO_Manage_elements[idx].numEntries;
            src_list   = m_MIO_Manage_elements[idx].src;
            maxEntries = m_MIO_Manage_elements[idx].maxEntries;
            className  = m_MIO_Manage_elements[idx ].mibObjectClass;
            m_accessMode = m_MIO_Manage_elements[idx ].accessMode;
            return true;
         }
      }
      /*
         className = MappingMibObjClass[mibObjClassName];
         TRACE_PRINTF("OAM_TEAM %s",mibObjClassName.c_str());
         for(u32 idx=0 ;idx<sizeof(m_MIO_Manage_elements)/sizeof(m_MIO_Manage_elements[0]);idx++)
         {
         TRACE_PRINTF("OAM_TEAM %s == %s",MibObjectClassToString( m_MIO_Manage_elements[idx].mibObjectClass ),MibObjectClassToString( className));
         if( className.find( m_MIO_Manage_elements[idx].mibObjectClass) != string::npos  )
         {
         numEntries = m_MIO_Manage_elements[idx].numEntries;
         src_list   = m_MIO_Manage_elements[idx].src;
         maxEntries = m_MIO_Manage_elements[idx].maxEntries;
         return true;
         }
         }
         */

      return false;
   }

   static MIOAutoManage *s_instance_mio_automanage;

   public:
   static MIOAutoManage& GetInstance();
   bool getMIOManageParameters( MibObjectClass, MibAttributeId &numEntries,
         MibAttributeId &src_list,MibAttributeId &maxEntries );

   bool getMIOManageParameters(MibRDN ,MibAttributeId&,MibAttributeId&, MibAttributeId&);
   bool getMIOManageParameters(MibDN ,MibAttributeId&,MibAttributeId&, MibAttributeId&);
   bool getMIOManageParameters(std::string ,MibAttributeId&,MibAttributeId&, MibAttributeId&);

   bool getMaxEntriesParamName(MibRDN , MibAttributeId&);
   bool getMaxEntriesParamName(MibDN , MibAttributeId&);
   bool getMaxEntriesParamName(std::string , MibAttributeId&);
   bool getMaxEntriesParamName(MibObjectClass , MibAttributeId&);

   bool getNumEntriesParamName(MibRDN , MibAttributeId&);
   bool getNumEntriesParamName(MibDN , MibAttributeId&);
   bool getNumEntriesParamName(std::string , MibAttributeId&);
   bool getNumEntriesParamName(MibObjectClass , MibAttributeId&);

   bool getSrcListParamName(MibRDN , MibAttributeId&);
   bool getSrcListParamName(MibDN , MibAttributeId&);
   bool getSrcListParamName(std::string , MibAttributeId&);
   bool getSrcListParamName(MibObjectClass , MibAttributeId&);

   bool getMibObjectClass(MibRDN , MibObjectClass&);
   bool getMibObjectClass(MibDN , MibObjectClass&);
   bool getMibObjectClass(std::string , MibObjectClass&);

   bool readMioAutomanageParameter(std::string , MibAttributeId& ,u32);
   bool readMibObjClass(std::string, MibObjectClass&);
   bool isMibObjectClassPresent(MibObjectClass mibObjectClass);

   bool isNeedCircularInsertion(std::string);
   bool isNeedCircularInsertion(MibRDN rDN);
   bool isNeedCircularInsertion(MibDN DN);
   bool isNeedCircularInsertion(MibObjectClass);

   bool isReadOnly( MibObjectClass MOC);

   enum { req_max_entries , req_num_entries , req_src_entries , req_mib_obj_class } request_flag;
};

#endif
