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
#include <system/Trace.h>
#include <system/StringUtils.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069Application.h"
#include "Tr069MultiInstanceMibObjectManager.h"
#include "Tr069AddObject_fsm.h"

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

static const MultiInstanceObjectDefintion s_multiInstanceObjectDefintion[] =
{
   {
      {
         "Device.Services.FAPService.1.REM.WCDMAFDD.Cell.",
         "Device.Services.FAPService.1.REM.WCDMAFDD.MaxCellEntries",
         "Device.Services.FAPService.1.REM.WCDMAFDD.CellNumberOfEntries"
      },
      {
         "FAP.0", MIB_OBJECT_CLASS_REM_SCANNED_WCDMA_CELL
      }
   },
   {
      {
         "Device.FaultMgmt.SupportedAlarm.",
         "Device.FaultMgmt.MaxSupportedAlarms",
         "Device.FaultMgmt.SupportedAlarmNumberOfEntries"
      },
      {
         "FAP.0", MIB_OBJECT_CLASS_TR196_SUPPORTED_ALARM
      }
   },
   {
      {
         "Device.FaultMgmt.CurrentAlarm.",
         "Device.FaultMgmt.MaxCurrentAlarmEntries",
         "Device.FaultMgmt.CurrentAlarmNumberOfEntries"
      },
      {
         "FAP.0", MIB_OBJECT_CLASS_TR196_CURRENT_ALARM
      }
   },
   {
      {
         "Device.FaultMgmt.HistoryEvent.",
         "Device.FaultMgmt.MaxHistoryEventEntries",
         "Device.FaultMgmt.HistoryEventNumberOfEntries"
      },
      {
         "FAP.0", MIB_OBJECT_CLASS_TR196_HISTORY_EVENT
      }
   },
   {
      {
         "Device.FaultMgmt.QueuedEvent.",
         "Device.FaultMgmt.MaxQueuedEventEntries",
         "Device.FaultMgmt.QueuedEventNumberOfEntries"
      },
      {
         "FAP.0", MIB_OBJECT_CLASS_QUEUED_EVENT
      }
   },
   {
      {
         "Device.FaultMgmt.ExpeditedEvent.",
         "Device.FaultMgmt.MaxExpeditedEventEntries",
         "Device.FaultMgmt.ExpeditedEventNumberOfEntries"
      },
      {
         "FAP.0", MIB_OBJECT_CLASS_TR196_EXPEDITED_EVENT
      }
   },
   {
      {
         "Device.Services.FAPService.1.REM.LTE.Cell.",
         "Device.Services.FAPService.1.REM.LTE.MaxCellEntries",
         "Device.Services.FAPService.1.REM.LTE.CellNumberOfEntries"
      },
      {
         "FAP.0", MIB_OBJECT_CLASS_LTE_REM_SCANNED_CELL
      }
   },
   {
      {
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.RAN.Mobility.IdleMode.InterFreq.Carrier.",
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.RAN.Mobility.IdleMode.InterFreq.MaxCarrierEntries",
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.RAN.Mobility.IdleMode.InterFreq.CarrierNumberOfEntries"
      },
      {
         "FAP.0.FAP_LTE.{CELL_IDX}",MIB_OBJECT_CLASS_LTE_RAN_MOB_IDLE_MODE_INTER_FREQ_CARRIER 
      }
   },
   {
      {
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.RAN.NeighborListInUse.LTECell.",
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.RAN.NeighborListInUse.MaxLTECellEntries",
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.RAN.NeighborListInUse.LTECellNumberOfEntries"
      },
      {
         "FAP.0.FAP_LTE.{CELL_IDX}", MIB_OBJECT_CLASS_LTE_NEIGH_EUTRA_IN_USE
      }
   },
   {
      {
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.RAN.Mobility.IdleMode.IRAT.GERAN.GERANFreqGroup.",
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.RAN.Mobility.IdleMode.IRAT.GERAN.MaxGERANFreqGroupEntries",
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.RAN.Mobility.IdleMode.IRAT.GERAN.GERANFreqGroupNumberOfEntries"
      },
      {
         "FAP.0.FAP_LTE.{CELL_IDX}", MIB_OBJECT_CLASS_LTE_INTER_RAT_GERAN_NEIGHBOR_FREQ_LIST
      }
   },
   {
      {
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.RAN.NeighborList.InterRATCell.GSM.",
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.RAN.NeighborList.InterRATCell.MaxGSMEntries",
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.RAN.NeighborList.InterRATCell.GSMNumberOfEntries"
      },
      {
         "FAP.0.FAP_LTE.{CELL_IDX}", MIB_OBJECT_CLASS_LTE_INTER_RAT_GERAN_NEIGHBOR_CELL_LIST
      }
   },
   {
      {
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.RAN.NeighborListInUse.InterRATCell.GSM.",
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.RAN.NeighborListInUse.InterRATCell.MaxGSMEntries",
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.RAN.NeighborListInUse.InterRATCell.GSMNumberOfEntries"
      },
      {
         "FAP.0.FAP_LTE.{CELL_IDX}", MIB_OBJECT_CLASS_LTE_INTER_RAT_GERAN_NEIGHBOR_CELL_IN_USE_LIST
      }
   },
   {
      {
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.RAN.NeighborList.LTECell.",
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.RAN.NeighborList.MaxLTECellEntries",
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.RAN.NeighborList.LTECellNumberOfEntries"
      },
      {
         "FAP.0.FAP_LTE.{CELL_IDX}", MIB_OBJECT_CLASS_LTE_RAN_NEIGH_LIST_LTE_CELL
      }
   },
   {
      {
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.RAN.Mobility.IdleMode.IRAT.UTRA.X_RADISYS_COM_UTRANTDDFreq.",
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.RAN.Mobility.IdleMode.IRAT.UTRA.X_RADISYS_COM_UTRANTDD.MaxUTRANTDDFreqEntries",
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.RAN.Mobility.IdleMode.IRAT.UTRA.X_RADISYS_COM_UTRANTDD.UTRANTDDFreqNumberOfEntries"
      },
      {
         "FAP.0.FAP_LTE.{CELL_IDX}", MIB_OBJECT_CLASS_LTE_TDS_CDMA_UTRAN_TDD_FREQ_LIST
      }
   },
   {
      {
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.RAN.NeighborList.InterRATCell.X_RADISYS_COM_UMTSTDD.cell.",
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.RAN.NeighborList.InterRATCell.X_RADISYS_COM_UMTSTDD.MaxUMTSTDDEntries",
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.RAN.NeighborList.InterRATCell.X_RADISYS_COM_UMTSTDD.UMTSTDDNumberOfEntries"
      },
      {
         "FAP.0.FAP_LTE.{CELL_IDX}", MIB_OBJECT_CLASS_LTE_TDS_CDMA_UTRAN_TDD_CELL_LIST
      }
   },
   {
      {
         "Device.FAP.Tunnel.CryptoProfile.",
         "Device.FAP.Tunnel.MaxIkeSessions",
         "Device.FAP.Tunnel.CryptoProfileNumberOfEntries"
      },
      {
         "FAP.0", MIB_OBJECT_CLASS_CRYPTO_PROFILES
      }
   },
   {
      {
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.EPC.PLMNList.",
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.EPC.MaxPLMNListEntries",
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.EPC.PLMNListNumberOfEntries"
      },
      {
         "FAP.0.FAP_LTE.{CELL_IDX}", MIB_OBJECT_CLASS_LTE_CELL_PLMN_LIST
      }
   },
   {
      {
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.RAN.NeighborList.InterRATCell.UMTS.",
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.RAN.NeighborList.InterRATCell.MaxUMTSEntries",
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.RAN.NeighborList.InterRATCell.UMTSNumberOfEntries",
      },
      {
         "FAP.0.FAP_LTE.{CELL_IDX}",MIB_OBJECT_CLASS_LTE_UMTS_NEIGHBOR
      }
   },
   {
      {
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.RAN.NeighborListInUse.InterRATCell.UMTS.",
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.RAN.NeighborListInUse.InterRATCell.MaxUMTSEntries",
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.RAN.NeighborListInUse.InterRATCell.UMTSNumberOfEntries",
      },
      {
         "FAP.0.FAP_LTE.{CELL_IDX}",MIB_OBJECT_CLASS_LTE_UMTS_NEIGHBOR_IN_USE
      }
   },
   {
      {
         "Device.IP.Interface.1.IPv6Address.",
         "Device.IP.InterfaceNumberOfEntries",
         "Device.IP.InterfaceNumberOfEntries"

      },
      {
         "FAP.0.IP_INTERFACE.0",MIB_OBJECT_CLASS_IP_INTERFACE_IPV6_ADDRESS
      }
   },
   {
      {
         "Device.IP.Interface.2.IPv6Address.",
         "Device.IP.InterfaceNumberOfEntries",
         "Device.IP.InterfaceNumberOfEntries"

      },
      {
         "FAP.0.IP_INTERFACE.0",MIB_OBJECT_CLASS_IP_INTERFACE_IPV6_ADDRESS
      }
   },
   {
      {
         "Device.FAP.PerfMgmt.Config.",
         "Device.Services.FAPService.1.CellConfig.LTE.RAN.Mobility.IdleMode.IRAT.UTRA.MaxUTRANFDDFreqEntries",
         "Device.FAP.PerfMgmt.ConfigNumberOfEntries"
      },
      {
         "FAP.0", MIB_OBJECT_CLASS_PERF_MGMT
      }
   },
   {
      {
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.RAN.Mobility.IdleMode.IRAT.UTRA.UTRANFDDFreq.",
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.RAN.Mobility.IdleMode.IRAT.UTRA.MaxUTRANFDDFreqEntries",
         "Device.Services.FAPService.{CELL_IDX}.CellConfig.LTE.RAN.Mobility.IdleMode.IRAT.UTRA..UTRANFDDFreqNumberOfEntries"

      },
      {
         "FAP.0.FAP_LTE.{CELL_IDX}",MIB_OBJECT_CLASS_UTRA_UTRAN_FDD_FREQ
      }
   }
};

MultiInstanceMibObjectManager* MultiInstanceMibObjectManager::s_instance = NULL;

MultiInstanceMibObjectManager& MultiInstanceMibObjectManager::GetInstance()
{
   if (s_instance == NULL)
   {
      s_instance = new MultiInstanceMibObjectManager( Tr069Application::GetInstance().GetMibCache(),  Tr069Application::GetInstance() );

      RSYS_ASSERT(s_instance);
   }

   return *s_instance;
}


MultiInstanceMibObjectManager::MultiInstanceMibObjectManager(MibAccessInterface& mib, SendMessageInterface &messenger) :
        m_mib(mib),
        m_messenger(messenger),
        numCells(2)
{
   string numCellStr = getConfigParam("OAM_NUM_CELL_ENTRIES", "");
   if(NULL != numCellStr.c_str())
   {
      numCells = atoi(numCellStr.c_str());
   }
   for(size_t idx = 0; idx < (sizeof(s_multiInstanceObjectDefintion)/sizeof(s_multiInstanceObjectDefintion[0]));idx++)
   {
      string mio_path(s_multiInstanceObjectDefintion[idx].DataModel.path);
      if(strstr(mio_path.c_str(),"{CELL_IDX}"))
      {
         if( numCells > 10)
         {
            return;
         }
            for(u32 i=1; i<= numCells; i++)
            {
               stringstream instance_nbr,parent_instance;

               string max_entries( s_multiInstanceObjectDefintion[idx].DataModel.maxEntriesParameter);
               string num_entries(s_multiInstanceObjectDefintion[idx].DataModel.currentEntriesParameter);
               string parent_dn(s_multiInstanceObjectDefintion[idx].Mib.parentDn);
               string mio_path(s_multiInstanceObjectDefintion[idx].DataModel.path);

               instance_nbr << i;
               parent_instance << (i-1);
               Str_replace(mio_path,(char *)"{CELL_IDX}",instance_nbr.str());
               Str_replace(max_entries,(char *)"{CELL_IDX}",instance_nbr.str());
               Str_replace(num_entries,(char *)"{CELL_IDX}",instance_nbr.str());
               Str_replace(parent_dn,(char *)"{CELL_IDX}",parent_instance.str());

               MultiInstanceObjectDefintion mio=
               {
                  {
                     mio_path.c_str(),
                     max_entries.c_str(),
                     num_entries.c_str(),
                  },
                  {
                     parent_dn.c_str(),s_multiInstanceObjectDefintion[idx].Mib.childClass
                  }
               };

               shared_ptr<Tr069MultiInstanceObject> tr069MultiInstanceObject(new Tr069MultiInstanceObject(m_messenger, m_mib, mio));

               m_multiInstanceObjects.insert(tr069MultiInstanceObject);
               m_mioByPath[ mio.DataModel.path ] = tr069MultiInstanceObject;
               m_mioMaxEntries[ mio.DataModel.maxEntriesParameter ] = tr069MultiInstanceObject;
               m_mioCurrentEntries[mio.DataModel.currentEntriesParameter ] = tr069MultiInstanceObject;
            }
      }
      else
      {
         shared_ptr<Tr069MultiInstanceObject> tr069MultiInstanceObject(new Tr069MultiInstanceObject(m_messenger, m_mib, s_multiInstanceObjectDefintion[idx]));

         m_multiInstanceObjects.insert(tr069MultiInstanceObject);
         m_mioByPath[ s_multiInstanceObjectDefintion[idx].DataModel.path ] = tr069MultiInstanceObject;
         m_mioMaxEntries[ s_multiInstanceObjectDefintion[idx].DataModel.maxEntriesParameter ] = tr069MultiInstanceObject;
         m_mioCurrentEntries[ s_multiInstanceObjectDefintion[idx].DataModel.currentEntriesParameter ] = tr069MultiInstanceObject;
      }
   }
}

MultiInstanceMibObjectManager::~MultiInstanceMibObjectManager()
{
}

void MultiInstanceMibObjectManager::PerformMibSubscriptions( u32 subscriptionId )
{
   for( set< shared_ptr<Tr069MultiInstanceObject> >::iterator i = m_multiInstanceObjects.begin();
         i != m_multiInstanceObjects.end();
         i++)
   {
      shared_ptr<Tr069MultiInstanceObject> mio = *i;

      m_mioMibSubscription[subscriptionId] = mio;
      mio->SubscribeToMib( subscriptionId );

      ++subscriptionId;
   }
}

void MultiInstanceMibObjectManager::HandleMibSubscribeAttributesInd( u32 subscriptionId )
{
   map< u32, shared_ptr<Tr069MultiInstanceObject> >::iterator i = m_mioMibSubscription.find(subscriptionId);

   if(i != m_mioMibSubscription.end())
   {
      shared_ptr<Tr069MultiInstanceObject> mioMibSubs = i->second;

      mioMibSubs->MibUpdated();
   }
}

void MultiInstanceMibObjectManager::AddParameterToParameterList( const string & name, ParameterList & parameterList )
{
   u32 value = 0;
   map< string, shared_ptr<Tr069MultiInstanceObject> >::iterator i;

   TRACE_PRINTF("MultiInstanceMibObjectManager::AddParameterToParameterList(%s)", name.c_str() );
   if( m_mioMaxEntries.end() != (i = m_mioMaxEntries.find( name )) )
   {
      value = i->second->GetMaxEntries();
   }
   else if( (i = m_mioCurrentEntries.find( name )) != m_mioCurrentEntries.end() )
   {
      value = i->second->GetNumberOfEntries();
   }

   stringstream ss;
   ss << value;

   parameterList.AppendParameter(name, ss.str() );
}

void MultiInstanceMibObjectManager::Str_replace(std::string &str,char *subStr, string newValue)
{
   u32 pos=str.find(subStr);
   if(pos !=std::string::npos)
   {
      str.replace(pos,strlen(subStr),(char *)newValue.c_str());
   }
}

shared_ptr<Tr069MultiInstanceObject> MultiInstanceMibObjectManager::GetMio( const string & path )
{
   shared_ptr<Tr069MultiInstanceObject> mio;

   map< string, shared_ptr<Tr069MultiInstanceObject> >::iterator i;
   TRACE_PRINTF("MultiInstanceMibObjectManager::GetMio(%s)", path.c_str() );
   if( m_mioByPath.end() != (i = m_mioByPath.find( path )) )
   {
      mio = i->second;
   }

   return mio;
}
}

