/********************************************************************16**

            (c) Copyright 2012 by RadiSys Corporation. All rights reserved.

     This software is confidential and proprietary to RadiSys Corporation.
     No part of this software may be reproduced, stored, transmitted, 
     disclosed or used in any form or by any means other than as expressly
     provided by the written Software License Agreement between Radisys 
     and its licensee.

     Radisys warrants that for a period, as provided by the written
     Software License Agreement between Radisys and its licensee, this
     software will perform substantially to Radisys specifications as
     published at the time of shipment, exclusive of any updates or 
     upgrades, and the media used for delivery of this software will be 
     free from defects in materials and workmanship.  Radisys also warrants 
     that has the corporate authority to enter into and perform under the 
     Software License Agreement and it is the copyright owner of the software 
     as originally delivered to its licensee.

     RADISYS MAKES NO OTHER WARRANTIES, EXPRESS OR IMPLIED, INCLUDING
     WITHOUT LIMITATION WARRANTIES OF MERCHANTABILITY OR FITNESS FOR
     A PARTICULAR PURPOSE WITH REGARD TO THIS SOFTWARE, SERVICE OR ANY RELATED
     MATERIALS.

     IN NO EVENT SHALL RADISYS BE LIABLE FOR ANY INDIRECT, SPECIAL,
     CONSEQUENTIAL DAMAGES, OR PUNITIVE DAMAGES IN CONNECTION WITH OR ARISING
     OUT OF THE USE OF, OR INABILITY TO USE, THIS SOFTWARE, WHETHER BASED
     ON BREACH OF CONTRACT, TORT (INCLUDING NEGLIGENCE), PRODUCT
     LIABILITY, OR OTHERWISE, AND WHETHER OR NOT IT HAS BEEN ADVISED
     OF THE POSSIBILITY OF SUCH DAMAGE.

                       Restricted Rights Legend:

     This software and all related materials licensed hereby are
     classified as "restricted computer software" as defined in clause
     52.227-19 of the Federal Acquisition Regulation ("FAR") and were
     developed entirely at private expense for nongovernmental purposes,
     are commercial in nature and have been regularly used for
     nongovernmental purposes, and, to the extent not published and
     copyrighted, are trade secrets and confidential and are provided
     with all rights reserved under the copyright laws of the United
     States.  The government's rights to the software and related
     materials are limited and restricted as provided in clause
     52.227-19 of the FAR.

                    IMPORTANT LIMITATION(S) ON USE

     The use of this software is limited to the use set
     forth in the written Software License Agreement between Radisys and
     its Licensee. Among other things, the use of this software
     may be limited to a particular type of Designated Equipment, as 
     defined in such Software License Agreement.
     Before any installation, use or transfer of this software, please
     consult the written Software License Agreement or contact Radisys at
     the location set forth below in order to confirm that you are
     engaging in a permissible use of the software.

                    RadiSys Corporation
                    Tel: +1 (858) 882 8800
                    Fax: +1 (858) 777 3388
                    Email: support@trillium.com
                    Web: http://www.radisys.com 
 
*********************************************************************17*/



//////////////////////////////////////////////////////////////////////
//   Local includes
//////////////////////////////////////////////////////////////////////
#include <mib-common/messages/MibCreateObjectReq.h>
#include <mib-common/messages/MibDeleteObjectReq.h>
#include <messaging/transport/AppMibAttributeCache.h>
#include "MessagingEntity.h"
#include "SmMultiInstanceObjectManager.h"
#include "SmApplication.h"

using namespace threeway;
using namespace boost;
using namespace Sm;

SmMultiInstanceObjectManager* SmMultiInstanceObjectManager::s_instance = NULL;

SmMultiInstanceObjectManager::SmMultiInstanceObjectManager()
{
}

SmMultiInstanceObjectManager & SmMultiInstanceObjectManager::GetInstance()
{
   if (!s_instance)
   {
      s_instance = new SmMultiInstanceObjectManager();
   }
   return *s_instance;
}


//////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//  Common functions for MIO management//////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////

s32 SmMultiInstanceObjectManager::addMIO(MibDN parentDn, MibObjectClass mibObjectClass)
{
   u32 maxEntries,numberOfEntries;
   u32 nextEntry=0;
   std::vector<u32> srcList;

   MibAttributeId PARAM_ID_NUM_ENTRIES,PARAM_ID_SRC_LIST,PARAM_ID_MAX_ENTRIES;
   MibAccessInterface& m_mib = SmApplication::GetInstance().GetMibCache();

   if(MIOAutoManage::GetInstance().getMaxEntriesParamName(mibObjectClass,PARAM_ID_MAX_ENTRIES))
   {
      MIOAutoManage::GetInstance().getNumEntriesParamName(mibObjectClass,PARAM_ID_NUM_ENTRIES);
      MIOAutoManage::GetInstance().getSrcListParamName(mibObjectClass,PARAM_ID_SRC_LIST);

      m_mib.GetMibAttribute(parentDn, PARAM_ID_MAX_ENTRIES, maxEntries);
      m_mib.GetMibAttribute(parentDn, PARAM_ID_NUM_ENTRIES, numberOfEntries);
      if(PARAM_ID_INVALID == PARAM_ID_SRC_LIST)
      {
         if(srcMap.find(PARAM_ID_MAX_ENTRIES)==srcMap.end())
         {
            srcMap[PARAM_ID_MAX_ENTRIES] = srcList;
         }
         else
         {
            srcList = srcMap[PARAM_ID_MAX_ENTRIES];
         }

      }
      else
      {
         m_mib.GetMibAttribute(parentDn, PARAM_ID_SRC_LIST,srcList);
      }

      if( maxEntries == numberOfEntries)
      {
         //check for circural add else return false
         TRACE_PRINTF("%s:  failed to create MIO. !Entries exceeds MAX Limit"
               ,__FUNCTION__);

         return FAILED_MIO_CREATION;
      }
      //try to insert at end

      if(srcList.size() < maxEntries)//in this case shouldnot search for holes
      {
         if(!((srcList.size()==1)&&(srcList[0]==deleted)))
            // initial condition one element with default value in src vector
         {
            nextEntry=srcList.size();
            srcList.push_back(deleted);
         }
      }
      else
         //search for holes
      {
         for(nextEntry = 0; nextEntry < srcList.size(); nextEntry++)
         {
            if( deleted == srcList[nextEntry])
            {
               break;
            }
         }
      }
      if( nextEntry == srcList.size())
         //probabily it will never hit
      {
         return FAILED_MIO_CREATION;
      }
      ///////////////////////////////////////////////////////
      /////////////////////creating MIO//////////////////////

      MibRDN childRdn(mibObjectClass,nextEntry);
      MibAttributeValues attr,managementAttributes;
      MibDN dn = MibDN::GenerateMibDN(mibObjectClass, nextEntry);
      MibCreateObjectReq mibCreateObjectReq(parentDn, childRdn, attr);
      SmApplication::GetInstance().SendMessage(mibCreateObjectReq, ENTITY_MIB, ENTITY_SM);
      srcList[nextEntry]=added;
      numberOfEntries++;

      managementAttributes.AddAttribute( PARAM_ID_NUM_ENTRIES, numberOfEntries);
      if(PARAM_ID_INVALID != PARAM_ID_SRC_LIST)
      {
         managementAttributes.AddAttribute( PARAM_ID_SRC_LIST, srcList);
      }
      else
      {
         srcMap[PARAM_ID_MAX_ENTRIES] = srcList;
      }
      SmApplication::GetInstance().GetMibCache().SetMibAttributes
         (parentDn,managementAttributes, ENTITY_SM);
      return nextEntry;
   }
   else
   {
      TRACE_PRINTF("Could not found MIO details from DataBase (AppMibAttributeCache.cpp)");
      return FAILED_MIO_CREATION;//not found in MIO List
   }
}

bool SmMultiInstanceObjectManager::deleteMIO(MibDN dn, MibDN fapLteDn)
{
   u32 maxEntries,numberOfEntries;
   std::vector<u32> srcList;

   MibAttributeId PARAM_ID_NUM_ENTRIES,PARAM_ID_SRC_LIST,PARAM_ID_MAX_ENTRIES;
   MibAccessInterface& m_mib = SmApplication::GetInstance().GetMibCache();

   if( ! m_mib.IsMibObjectPresent(dn))
   {
      TRACE_PRINTF("%s Trying to Delete dn %s !! faild MibDn doesnot exist",__FUNCTION__,dn.ToString().c_str());
      return FAILED_MIO_OPERATION;
   }

   u32 instance = (u32) MibDN::GetMibObjectInstanceNum(dn);
   if(MIOAutoManage::GetInstance().getMaxEntriesParamName(dn,PARAM_ID_MAX_ENTRIES))
   {
      MIOAutoManage::GetInstance().getSrcListParamName(dn,PARAM_ID_SRC_LIST);
      MIOAutoManage::GetInstance().getNumEntriesParamName(dn,PARAM_ID_NUM_ENTRIES);

      m_mib.GetMibAttribute(fapLteDn, PARAM_ID_MAX_ENTRIES, maxEntries);
      m_mib.GetMibAttribute(fapLteDn, PARAM_ID_NUM_ENTRIES, numberOfEntries);
      if( PARAM_ID_INVALID == PARAM_ID_SRC_LIST)
      {
         if(srcMap.find(PARAM_ID_MAX_ENTRIES)==srcMap.end())
         {
            srcMap[PARAM_ID_MAX_ENTRIES] = srcList;
         }
         else
         {
            srcList = srcMap[PARAM_ID_MAX_ENTRIES];

         }
      }
      else
      {
         m_mib.GetMibAttribute(fapLteDn, PARAM_ID_SRC_LIST,srcList);
      }

      if((srcList.size()< instance)||(deleted == srcList[instance]))
      {
         TRACE_PRINTF(" %s Instance not present ",__FUNCTION__);
         return FAILED_MIO_OPERATION;//not found in MIO List
      }
      MibDeleteObjectReq mibDeleteObjectReq(dn);
      SmApplication::GetInstance().SendMessage(mibDeleteObjectReq, ENTITY_MIB, ENTITY_SM);

      MibAttributeValues attr;
      numberOfEntries--;
      srcList[instance]=deleted;
      if(PARAM_ID_INVALID == PARAM_ID_SRC_LIST )
      {
         srcMap[PARAM_ID_MAX_ENTRIES] = srcList;
      }
      else
      {
         attr.AddAttribute( PARAM_ID_SRC_LIST,srcList);
      }
      attr.AddAttribute( PARAM_ID_NUM_ENTRIES, numberOfEntries);
      SmApplication::GetInstance().GetMibCache().SetMibAttributes(fapLteDn, attr, ENTITY_SM);
   }
   else
   {
      TRACE_PRINTF("Could not found MIO details from DataBase (AppMibAttributeCache.cpp)");
      return FAILED_MIO_OPERATION;//not found in MIO List
   }
   return true;
}

void  SmMultiInstanceObjectManager::resetMIO(MibObjectClass mibObjectClass)
{
   u32 maxEntries,numberOfEntries;
   std::vector<u32> srcList;
   gsmCellToInstance.clear();
   u32 cellIdx = 0;
   MibAttributeId PARAM_ID_NUM_ENTRIES,PARAM_ID_SRC_LIST,PARAM_ID_MAX_ENTRIES;

   for(cellIdx = 0; cellIdx <SmApplication::GetInstance().numOfCells; cellIdx++)
   {
      MibDN fapLteDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);

      MibAccessInterface& m_mib = SmApplication::GetInstance().GetMibCache();

      if(MIOAutoManage::GetInstance().getMaxEntriesParamName(mibObjectClass,PARAM_ID_MAX_ENTRIES))
      {
         MIOAutoManage::GetInstance().getSrcListParamName(mibObjectClass,PARAM_ID_SRC_LIST);
         MIOAutoManage::GetInstance().getNumEntriesParamName(mibObjectClass,PARAM_ID_NUM_ENTRIES);

         m_mib.GetMibAttribute(fapLteDn, PARAM_ID_MAX_ENTRIES, maxEntries);
         m_mib.GetMibAttribute(fapLteDn, PARAM_ID_NUM_ENTRIES, numberOfEntries);
         if (PARAM_ID_INVALID == PARAM_ID_SRC_LIST)
         {
            srcList = srcMap[PARAM_ID_MAX_ENTRIES];
         }
         else
         {
            m_mib.GetMibAttribute(fapLteDn, PARAM_ID_SRC_LIST, srcList);
         }

         if ( 0 == numberOfEntries)
         {
            TRACE_PRINTF("Trying to reset MIO  !!alredy empty");
         }

         for(u32 idx= 0; idx<=srcList.size(); idx++)
         {
            MibDN mibDn = MibDN::GenerateMibDN(fapLteDn, mibObjectClass, idx);
            deleteMIO(mibDn,fapLteDn);
         }
         if (PARAM_ID_INVALID != PARAM_ID_SRC_LIST)
         {
            MibAttributeValues attr;
            std::vector<u32> cleanSrc;
            cleanSrc.push_back(2);
            attr.AddAttribute( PARAM_ID_SRC_LIST,cleanSrc);
            SmApplication::GetInstance().GetMibCache().SetMibAttributes(fapLteDn, attr, ENTITY_SM);
         }
      }
      else
      {
         TRACE_PRINTF("Could not found MIO details from DataBase (AppMibAttributeCache.cpp)");
      }
   }
}
