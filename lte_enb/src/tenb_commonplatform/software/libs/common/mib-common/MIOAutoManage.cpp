#include "MIOAutoManage.h"

MIOAutoManage* MIOAutoManage::s_instance_mio_automanage=NULL;

MIOAutoManage& MIOAutoManage::GetInstance()
{
   if(NULL==s_instance_mio_automanage)
   {
      s_instance_mio_automanage= new  MIOAutoManage();
   }
   RETURN( *s_instance_mio_automanage);
}

///////////////////////////////////////////////////////////////////////////////////////////
//
//functions to get max extry
//
//////////////////////////////////////////////////////////////////////////////////////////
bool MIOAutoManage ::  getMaxEntriesParamName(MibDN dn, MibAttributeId &maxentry )
{
   return  readMioAutomanageParameter(dn.ToString() , maxentry,req_max_entries );
}

bool MIOAutoManage ::  getMaxEntriesParamName(MibRDN rDN, MibAttributeId &maxentry )
{
   return  readMioAutomanageParameter(rDN.ToString() , maxentry,req_max_entries );
}

bool MIOAutoManage ::  getMaxEntriesParamName(std::string mibObjClass, MibAttributeId &maxentry )
{
   return  readMioAutomanageParameter(mibObjClass, maxentry,req_max_entries );
}

bool MIOAutoManage ::  getMaxEntriesParamName(MibObjectClass mibObjectClass, MibAttributeId &maxentry )
{
   const char* mibclass=   MibObjectClassToString(mibObjectClass);
   ostringstream stream;
   stream << &mibclass[MIB_OBJECT_CLASS_STR_LENGTH];
   TRACE_PRINTF("OAM_TEAM mib obj class name =%s",stream.str().c_str());
   return  readMioAutomanageParameter(stream.str() , maxentry,req_max_entries );
}

///////////////////////////////////////////////////////////////////////////////////////////
//
//functions to get number of entries
//
///////////////////////////////////////////////////////////////////////////////////////////
bool MIOAutoManage :: getNumEntriesParamName(MibDN dn, MibAttributeId &num_entries )
{
   return  readMioAutomanageParameter(dn.ToString() , num_entries,req_num_entries  );
}

bool MIOAutoManage :: getNumEntriesParamName(MibRDN rDN, MibAttributeId &num_entries )
{
   return  readMioAutomanageParameter(rDN.ToString() , num_entries,req_num_entries  );
}

bool MIOAutoManage :: getNumEntriesParamName(std::string mibObjClass, MibAttributeId &num_entries )
{
   return  readMioAutomanageParameter(mibObjClass, num_entries,req_num_entries );
}

bool MIOAutoManage :: getNumEntriesParamName(MibObjectClass mibObjectClass, MibAttributeId &num_entries )
{
   const char* mibclass=   MibObjectClassToString(mibObjectClass);
   ostringstream stream;
   stream << &mibclass[MIB_OBJECT_CLASS_STR_LENGTH];
   return  readMioAutomanageParameter(stream.str() , num_entries,req_num_entries );
}

///////////////////////////////////////////////////////////////////////////////////////////
//
//functions to get   src vector
//
///////////////////////////////////////////////////////////////////////////////////////////
bool MIOAutoManage :: getSrcListParamName(MibDN dn, MibAttributeId &src_list)
{
   return  readMioAutomanageParameter(dn.ToString() , src_list,req_src_entries);
}

bool MIOAutoManage :: getSrcListParamName(MibRDN rDN, MibAttributeId &src_list)
{
   return  readMioAutomanageParameter(rDN.ToString() , src_list,req_src_entries);
}

bool MIOAutoManage :: getSrcListParamName(std::string mibObjClass, MibAttributeId &src_list )
{
   return  readMioAutomanageParameter(mibObjClass, src_list ,req_src_entries);
}

bool MIOAutoManage :: getSrcListParamName(MibObjectClass mibObjectClass, MibAttributeId &src_list)
{
   const char* mibclass=   MibObjectClassToString(mibObjectClass);
   ostringstream stream;
   stream << &mibclass[MIB_OBJECT_CLASS_STR_LENGTH];
   return  readMioAutomanageParameter(stream.str() , src_list,req_src_entries);
}

//////////////////////////////////////////////////////////////////////////////////////////
//
//      function to check MibObject Class Present or not
//
//////////////////////////////////////////////////////////////////////////////////////////

bool MIOAutoManage :: isMibObjectClassPresent(MibObjectClass mibObjectClass)
{

   const char* mibclass = MibObjectClassToString(mibObjectClass);
   ostringstream stream;
   stream << &mibclass[MIB_OBJECT_CLASS_STR_LENGTH];
   return readMibObjClass( stream.str(), mibObjectClass);
}

///////////////////////////////////////////////////////////////////////////////////////////
//
//functions to get   mibObject Class
//
///////////////////////////////////////////////////////////////////////////////////////////
bool MIOAutoManage :: getMibObjectClass(MibDN dn, MibObjectClass &mibObjClass)
{
   return  readMibObjClass(dn.ToString() , mibObjClass);
}

bool MIOAutoManage :: getMibObjectClass(MibRDN rDN, MibObjectClass &mibObjClass)
{
   return  readMibObjClass(rDN.ToString() ,mibObjClass);
}

bool MIOAutoManage :: getMibObjectClass(std::string mibObjClsString, MibObjectClass &mibObjClass)
{
   return  readMibObjClass(mibObjClsString ,mibObjClass);
}

bool MIOAutoManage :: readMioAutomanageParameter(std::string mibObjectClass, MibAttributeId &attribute, u32 element_mask)
{
   MibAttributeId numEntries = PARAM_ID_INVALID;
   MibAttributeId src_list   = PARAM_ID_INVALID;
   MibAttributeId maxEntries = PARAM_ID_INVALID;
   MibObjectClass className;
   bool present = getMIOManageInfo( mibObjectClass,numEntries,src_list,maxEntries,className );

   if(!present)
   {
      return false;
   }

   if( req_max_entries == element_mask)
      attribute = maxEntries;
   else if( req_num_entries  == element_mask)
      attribute = numEntries;
   else if ( req_src_entries == element_mask)
      attribute = src_list;
   else //probabily it will not it
      return false;

   if(attribute == PARAM_ID_INVALID)
   {
      return false;
   }
   return true;
}

bool MIOAutoManage :: readMibObjClass(std::string mibObjectClass_name , MibObjectClass &mibObjClass)
{
   MibAttributeId numEntries = PARAM_ID_INVALID;
   MibAttributeId src_list   = PARAM_ID_INVALID;
   MibAttributeId maxEntries = PARAM_ID_INVALID;
   return getMIOManageInfo( mibObjectClass_name ,numEntries,src_list,maxEntries,mibObjClass );
}

bool MIOAutoManage ::isNeedCircularInsertion(MibRDN rDN)
{
   return isNeedCircularInsertion(rDN.ToString());
}

bool MIOAutoManage ::isNeedCircularInsertion(MibDN dN)
{
   return isNeedCircularInsertion(dN.ToString());
}

bool MIOAutoManage ::isNeedCircularInsertion(MibObjectClass mibObjectClass)
{
   MibDN dN= MibDN::GenerateMibDN(mibObjectClass,0);
   return isNeedCircularInsertion(dN.ToString());
}

bool MIOAutoManage ::isNeedCircularInsertion(std::string dnString)
{
   MIOs_Needed_CircularInsertion m_MIOs_Needed_CircularInsertion[]=
   {
      { "LTE_CELL_PLMN_LIST" },
      { "TR196_SUPPORTED_ALARM" },
      { "TR196_CURRENT_ALARM" },
      { "TR196_HISTORY_EVENT" },
      { "TR196_EXPEDITED_EVENT" },
      { "QUEUED_EVENT"}
      
   };

   for(u32 idx=0; idx<sizeof(m_MIOs_Needed_CircularInsertion)/sizeof(m_MIOs_Needed_CircularInsertion[0]);idx++)
   {
      if(dnString.find(m_MIOs_Needed_CircularInsertion[idx].dnString) != string::npos)
      {
         return true;
      }
   }
   return false;
}

bool MIOAutoManage ::isReadOnly( MibObjectClass MOC)
{

   MibAttributeId numEntries = PARAM_ID_INVALID;
   MibAttributeId src_list   = PARAM_ID_INVALID;
   MibAttributeId maxEntries = PARAM_ID_INVALID;

   const char* mibclass=   MibObjectClassToString(MOC);
   ostringstream stream;
   stream << &mibclass[MIB_OBJECT_CLASS_STR_LENGTH];
   readMioAutomanageParameter(stream.str() , src_list,req_src_entries);

   getMIOManageInfo(stream.str() ,numEntries,src_list,maxEntries,MOC );
   if(READ_ONLY == m_accessMode)
   {
      return true;
   }
   else
   {
      return false;
   }
}
