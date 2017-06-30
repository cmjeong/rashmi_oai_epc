/********************************************************************20**

     Name:     SON Application

     Type:     

     Desc:     This file contains 
               

     File:     nl_alarm.c

     Sid:      bk_alarm.c@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 17:50:59 2014

     Prg:      subhamay 

*********************************************************************21*/

//static const char* RLOG_MODULE_NAME="SON";
//static int RLOG_FILE_ID=10;
//static int RLOG_MODULE_ID=256;

/* Header include files (.h) */
#include "envopt.h"        /* Environment options */
#include "envdep.h"        /* Environment dependent */
#include "envind.h"        /* Environment independent */
#include "gen.h"           /* General */
#include "ssi.h"           /* System services */
#include "cm5.h"

#include "cm_tkns.h"       /* Common Token defines */
#include "cm_mblk.h"       /* Common Mem Allocation defines */
#include "cm_llist.h"      /* Common Link List defines */
#include "cm_hash.h"       /* Common Hashlist defines */
#include "cm_pasn.h"       /* Common Pasn defines */
#include "cm_lte.h"        /* Common Pasn defines */
#include "rl_common.h"     /* RLOG defines */   
#include "rl_interface.h"   
#include "lnl.h"           /* NL Interface defines */
#include "nlu.h"
#include "nl.h"            /* SON defines */
/* Header/extern include files (.x) */
#include "gen.x"           /* General */
#include "ssi.x"           /* System services */
#include "cm5.x"
#include "cm_tkns.x"       /* Common Token definitions */
#include "cm_mblk.x"       /* Common Memory Allocation */
#include "cm_llist.x"      /* Common Link List definitions */
#include "cm_hash.x"       /* Common Hashlist definitions */
#include "cm_lib.x"        /* Common Library definitions */
#include "cm_pasn.x"       /* Common Hashlist definitions */
#include "cm_lte.x"       /* Common Pasn defines */

#include "lnl.x"           /* NL Interface includes */
#include "nlu.x"
#include "nl.x"            /* SON includes */

/* local defines */

/* local typedefs */
 
/* local externs */
/* forward references */

/**
 * @brief clear the alarm raised for served cell PCI
 *
 * @details
 *
 *     Function : nlServCellPeerAlarmClear
 *
 *     This function will clear all the peer alarm raised for 
 *     serving cell PCI
 *
 *  @param[in]  NlCellCb : served cell control block 
 *  @return  S16
 *     -# Success       : ROK
 *     -# Failure       : RFAILED  
 *
 **/
#ifdef ANSI
PUBLIC S16 nlServCellPeerAlarmClear
(
NlCellCb *servCell
)
#else
PUBLIC S16 nlServCellPeerAlarmClear(servCell)
(
NlCellCb *servCell;
)
#endif
{
   NlCellCb          *nlCellCb    = NULLP;                               
   NlNghServCellCb   *nghServCb   = NULLP;                                 
   NlNghNghCellCb    *nghNghCb    = NULLP;                                
   U8                count;
   U8                nghCount; 

   TRC3(nlServCellPeerAlarmClear)

   if(servCell->cellInfo.alarmInfo.isAlarmRaised)                         
   {                                                
      for(count = 0; count < NL_MAX_NGH_ALARM; count ++)
      {
         if(servCell->cellInfo.alarmInfo.peerInfo[count].isActive)
         {
            servCell->cellInfo.alarmInfo.peerInfo[count].isActive = FALSE;
            if(NL_ALARM_PEER_SERV_CELL == servCell->
                  cellInfo.alarmInfo.peerInfo[count].peerType)      
            {                                                                    
               nlCellCb = (NlCellCb *)servCell->
                          cellInfo.alarmInfo.peerInfo[count].peerAddr;   
               if(NULLP != nlCellCb)                                             
               {
                  if(TRUE == nlCellCb->cellInfo.alarmInfo.isAlarmRaised)
                  {
                     for(nghCount = 0; nghCount < NL_MAX_NGH_ALARM; nghCount ++)
                     {
                        if(((NlCellCb *)nlCellCb->
                        cellInfo.alarmInfo.peerInfo[nghCount].peerAddr == servCell) &&
                        (TRUE == nlCellCb->cellInfo.alarmInfo.peerInfo[nghCount].isActive) &&
                        (NL_ALARM_PEER_SERV_CELL ==
                            nlCellCb->cellInfo.alarmInfo.peerInfo[nghCount].peerType))
                        {
                           nlCellCb->cellInfo.alarmInfo.peerInfo[nghCount].peerAddr = NULLP;
                           nlCellCb->cellInfo.alarmInfo.peerInfo[nghCount].isActive = FALSE;
                           nlCellCb->cellInfo.alarmInfo.numPeerAlarm --;
                           if(0 == nlCellCb->cellInfo.alarmInfo.numPeerAlarm)
                           {
                              nlCellCb->cellInfo.alarmInfo.isAlarmRaised = FALSE;
                              /*update the cell state to configured*/
                              NL_UPDATE_CELL_STATE(nlCellCb, NL_CELL_STATE_CONFIGURED);
                           }
                        }
                     }
                  }
               }
            }
            else if(NL_ALARM_PEER_NGH_SERV_CELL == servCell->
                             cellInfo.alarmInfo.peerInfo[count].peerType)       
            {                                                                    
               nghServCb = (NlNghServCellCb *)servCell->
                          cellInfo.alarmInfo.peerInfo[count].peerAddr;
               if(NULLP != nghServCb)                                            
               {
                  if(TRUE == nghServCb->servCellInfo.alarmInfo.isAlarmRaised)
                  {
                     for(nghCount = 0; nghCount < NL_MAX_NGH_ALARM; nghCount ++)
                     {
                        if(((NlCellCb *)nghServCb->
                        servCellInfo.alarmInfo.peerInfo[nghCount].peerAddr == servCell) &&
                        (TRUE == nghServCb->servCellInfo.alarmInfo.peerInfo[nghCount].isActive) &&
                        (NL_ALARM_PEER_SERV_CELL ==
                            nghServCb->servCellInfo.alarmInfo.peerInfo[nghCount].peerType))
                        {
                           nghServCb->servCellInfo.alarmInfo.peerInfo[nghCount].peerAddr = NULLP;
                           nghServCb->servCellInfo.alarmInfo.peerInfo[nghCount].isActive = FALSE;
                           nghServCb->servCellInfo.alarmInfo.numPeerAlarm --;
                           if(0 == nghServCb->servCellInfo.alarmInfo.numPeerAlarm)
                           {
                              nghServCb->servCellInfo.alarmInfo.isAlarmRaised = FALSE;
                           }
                        }
                     }
                  }
               }
            }   
            else if(NL_ALARM_PEER_NGH_NGH_CELL == servCell->
                          cellInfo.alarmInfo.peerInfo[count].peerType)   
            {                                                                    
               nghNghCb = (NlNghNghCellCb *)servCell->
                          cellInfo.alarmInfo.peerInfo[count].peerAddr;  
               if(NULLP != nghNghCb)                                             
               {
                  if(TRUE == nghNghCb->nghNghCellInfo.alarmInfo.isAlarmRaised)
                  {
                     for(nghCount = 0; nghCount < NL_MAX_NGH_ALARM; nghCount ++)
                     {
                        if(((NlCellCb *)nghNghCb->
                        nghNghCellInfo.alarmInfo.peerInfo[nghCount].peerAddr == servCell) &&
                        (TRUE == nghNghCb->nghNghCellInfo.alarmInfo.peerInfo[nghCount].isActive) &&
                        (NL_ALARM_PEER_SERV_CELL ==
                            nghNghCb->nghNghCellInfo.alarmInfo.peerInfo[nghCount].peerType))
                        {
                           nghNghCb->nghNghCellInfo.alarmInfo.peerInfo[nghCount].peerAddr = NULLP;
                           nghNghCb->nghNghCellInfo.alarmInfo.peerInfo[nghCount].isActive = FALSE;
                           nghNghCb->nghNghCellInfo.alarmInfo.numPeerAlarm --;
                           if(0 == nghNghCb->nghNghCellInfo.alarmInfo.numPeerAlarm)
                           {
                              nghNghCb->nghNghCellInfo.alarmInfo.isAlarmRaised = FALSE;
                           }
                        }
                     }
                  }
               }
            }
         }                                                                 
      }                                                                    
   }   
   for(count = 0; count < NL_MAX_NGH_ALARM; count ++)
   {
      if(servCell->cellInfo.alarmInfo.peerInfo[count].isActive)
      {
         break;
      }
   }
   if(count == NL_MAX_NGH_ALARM)
   {                                                                 
      servCell->cellInfo.alarmInfo.isAlarmRaised = FALSE; 
      NL_UPDATE_CELL_STATE(servCell, NL_CELL_STATE_CONFIGURED);
   }  
   RETVALUE(ROK);
}
/**
 * @brief clear the alarm raised for neighbor's neighbor PCI
 *
 * @details
 *
 *     Function : nlNghNghPeerAlarmClear
 *
 *     This function will clear all the peer alarm raised for
 *     neighbor's neighbor cell PCI
 *
 *  @param[in]  nghNghCell : neighbor's neighbor cell control block
 *  @return  S16
 *     -# Success       : ROK
 *     -# Failure       : RFAILED
 *
 **/
#ifdef ANSI
PUBLIC S16 nlNghNghPeerAlarmClear
(
NlNghNghCellCb *nghNghCell
)
#else
PUBLIC S16 nlNghNghPeerAlarmClear(nghNghCell)
(
NlNghNghCellCb *nghNghCell;
)
#endif
{
   NlCellCb          *nlCellCb    = NULLP;                                      
   NlNghServCellCb   *nghServCb   = NULLP;                                       
   NlNghNghCellCb    *nghNghCb    = NULLP;
   U8                count;
   U8                nghCount;    
   TRC3(nlNghNghPeerAlarmClear);                                    
   if(nghNghCell->nghNghCellInfo.alarmInfo.isAlarmRaised)                        
   {
      for(count = 0; count < NL_MAX_NGH_ALARM; count ++)
      {
         if(nghNghCell->nghNghCellInfo.alarmInfo.peerInfo[count].isActive)
         {
            nghNghCell->nghNghCellInfo.alarmInfo.peerInfo[count].isActive = FALSE;
            if(NL_ALARM_PEER_SERV_CELL == nghNghCell->
                  nghNghCellInfo.alarmInfo.peerInfo[count].peerType)     
            {                                                                           
               nlCellCb = (NlCellCb *)nghNghCell->
                          nghNghCellInfo.alarmInfo.peerInfo[count].peerAddr;  
               if(NULLP != nlCellCb)                                                    
               {
                  if(TRUE == nlCellCb->cellInfo.alarmInfo.isAlarmRaised)
                  {
                     for(nghCount = 0; nghCount < NL_MAX_NGH_ALARM; nghCount ++)
                     {
                        if(((NlNghNghCellCb *)nlCellCb->
                        cellInfo.alarmInfo.peerInfo[nghCount].peerAddr == nghNghCell) &&
                        (TRUE == nlCellCb->cellInfo.alarmInfo.peerInfo[nghCount].isActive) &&
                        (NL_ALARM_PEER_NGH_NGH_CELL ==
                            nlCellCb->cellInfo.alarmInfo.peerInfo[nghCount].peerType))
                        {
                           nlCellCb->cellInfo.alarmInfo.peerInfo[nghCount].peerAddr = NULLP;
                           nlCellCb->cellInfo.alarmInfo.peerInfo[nghCount].isActive = FALSE;
                           nlCellCb->cellInfo.alarmInfo.numPeerAlarm --;
                           if(0 == nlCellCb->cellInfo.alarmInfo.numPeerAlarm)
                           {
                              nlCellCb->cellInfo.alarmInfo.isAlarmRaised = FALSE;
                              NL_UPDATE_CELL_STATE(nlCellCb, NL_CELL_STATE_CONFIGURED);
                           }
                        }
                     }
                  }
               }
            }                       
            else if(NL_ALARM_PEER_NGH_SERV_CELL == nghNghCell->
                         nghNghCellInfo.alarmInfo.peerInfo[count].peerType)
            {                                                                           
               nghServCb = (NlNghServCellCb *)nghNghCell->
                           nghNghCellInfo.alarmInfo.peerInfo[count].peerAddr;
               if(NULLP != nghServCb)                                                   
               {
                  if(TRUE == nghServCb->servCellInfo.alarmInfo.isAlarmRaised)
                  {
                     for(nghCount = 0; nghCount < NL_MAX_NGH_ALARM; nghCount ++)
                     {
                        if(((NlNghNghCellCb *)nghServCb->
                        servCellInfo.alarmInfo.peerInfo[nghCount].peerAddr == nghNghCell) &&
                        (TRUE == nghServCb->servCellInfo.alarmInfo.peerInfo[nghCount].isActive) &&
                        (NL_ALARM_PEER_NGH_NGH_CELL ==
                            nghServCb->servCellInfo.alarmInfo.peerInfo[nghCount].peerType))
                        {
                           nghServCb->servCellInfo.alarmInfo.peerInfo[nghCount].peerAddr = NULLP;
                           nghServCb->servCellInfo.alarmInfo.peerInfo[nghCount].isActive = FALSE;
                           nghServCb->servCellInfo.alarmInfo.numPeerAlarm --;
                           if(0 == nghServCb->servCellInfo.alarmInfo.numPeerAlarm)
                           {
                              nghServCb->servCellInfo.alarmInfo.isAlarmRaised = FALSE;
                           }
                        }
                     }
                  }
               }                                                                        
            }      
            else if(NL_ALARM_PEER_NGH_NGH_CELL == nghNghCell->
                      nghNghCellInfo.alarmInfo.peerInfo[count].peerType)  
            {                                                                           
               nghNghCb = (NlNghNghCellCb *)nghNghCell->
                           nghNghCellInfo.alarmInfo.peerInfo[count].peerAddr; 
               if(NULLP != nghNghCb)                                                    
               {  
                  if(TRUE == nghNghCb->nghNghCellInfo.alarmInfo.isAlarmRaised)
                  {
                     for(nghCount = 0; nghCount < NL_MAX_NGH_ALARM; nghCount ++)
                     {
                        if(((NlNghNghCellCb *)nghNghCb->
                        nghNghCellInfo.alarmInfo.peerInfo[nghCount].peerAddr == nghNghCell) &&
                        (TRUE == nghNghCb->nghNghCellInfo.alarmInfo.peerInfo[nghCount].isActive) &&
                        (NL_ALARM_PEER_NGH_NGH_CELL ==
                            nghNghCb->nghNghCellInfo.alarmInfo.peerInfo[nghCount].peerType))
                        {
                           nghNghCb->nghNghCellInfo.alarmInfo.peerInfo[nghCount].peerAddr = NULLP;
                           nghNghCb->nghNghCellInfo.alarmInfo.peerInfo[nghCount].isActive = FALSE;
                           nghNghCb->nghNghCellInfo.alarmInfo.numPeerAlarm --;
                           if(0 == nghNghCb->nghNghCellInfo.alarmInfo.numPeerAlarm)
                           {
                              nghNghCb->nghNghCellInfo.alarmInfo.isAlarmRaised = FALSE;
                           }
                        }
                     }
                  }
               }
            }             
         }                                                                        
      }                                                                           
   } 
   for(count = 0; count < NL_MAX_NGH_ALARM; count ++)
   {
      if(nghNghCell->nghNghCellInfo.alarmInfo.peerInfo[count].isActive)
      {
         break;
      }
   }
   if(count == NL_MAX_NGH_ALARM)
   {                                                                             
      nghNghCell->nghNghCellInfo.alarmInfo.isAlarmRaised = FALSE;   
   } 
   RETVALUE(ROK);               
}

/**
 * @brief clear the alarm raised for neighbor PCI
 *
 * @details
 *
 *     Function : nlNghPeerAlarmClear
 *
 *     This function will clear all the peer alarm raised for
 *     neighbor cell PCI
 *
 *  @param[in]  nghServCell : neighbor cell control block
 *  @return  S16
 *     -# Success       : ROK
 *     -# Failure       : RFAILED
 *
 **/
#ifdef ANSI
PUBLIC S16 nlNghPeerAlarmClear
(
NlNghServCellCb *nghServCell
)
#else
PUBLIC S16 nlNghPeerAlarmClear(nghServCell)
(
NlNghServCellCb *nghServCell;
)
#endif
{
   NlCellCb          *nlCellCb      = NULLP;                                      
   NlNghServCellCb   *nghServCb   = NULLP;                                        
   NlNghNghCellCb    *nghNghCb    = NULLP;                                        
   U8                count;    
   U8                nghCount;                                                   
   if(nghServCell->servCellInfo.alarmInfo.isAlarmRaised)                         
   {                                                                              
      for(count = 0; count < NL_MAX_NGH_ALARM; count ++)                          
      {
         if(nghServCell->servCellInfo.alarmInfo.peerInfo[count].isActive)      
         {
            nghServCell->servCellInfo.alarmInfo.peerInfo[count].isActive = FALSE;                                                                        
            if(NL_ALARM_PEER_SERV_CELL == nghServCell->
                 servCellInfo.alarmInfo.peerInfo[count].peerType)      
            {                                                                           
               nlCellCb = (NlCellCb *)nghServCell->
                          servCellInfo.alarmInfo.peerInfo[count].peerAddr;  
               if(NULLP != nlCellCb)                                                    
               {                                                                        
                  if(TRUE == nlCellCb->cellInfo.alarmInfo.isAlarmRaised)
                  {
                     for(nghCount = 0; nghCount < NL_MAX_NGH_ALARM; nghCount ++)
                     {
                        if(((NlNghServCellCb *)nlCellCb->
                        cellInfo.alarmInfo.peerInfo[nghCount].peerAddr == nghServCell) && 
                        (TRUE == nlCellCb->cellInfo.alarmInfo.peerInfo[nghCount].isActive) &&
                        (NL_ALARM_PEER_NGH_SERV_CELL == 
                            nlCellCb->cellInfo.alarmInfo.peerInfo[nghCount].peerType))
                        {                   
                           nlCellCb->cellInfo.alarmInfo.peerInfo[nghCount].peerAddr = NULLP;
                           nlCellCb->cellInfo.alarmInfo.peerInfo[nghCount].isActive = FALSE;
                           nlCellCb->cellInfo.alarmInfo.numPeerAlarm --;
                           if(0 == nlCellCb->cellInfo.alarmInfo.numPeerAlarm)
                           {
                              nlCellCb->cellInfo.alarmInfo.isAlarmRaised = FALSE;
                              NL_UPDATE_CELL_STATE(nlCellCb, NL_CELL_STATE_CONFIGURED);
                           }                           
                        }
                     }
                  }                       
               }
            }
            else if(NL_ALARM_PEER_NGH_SERV_CELL == nghServCell->
                    servCellInfo.alarmInfo.peerInfo[count].peerType)
            {                                                                           
               nghServCb = (NlNghServCellCb *)nghServCell->
                              servCellInfo.alarmInfo.peerInfo[count].peerAddr;
               if(NULLP != nghServCb)                                                   
               {                                                                        
                  if(TRUE == nghServCb->servCellInfo.alarmInfo.isAlarmRaised)
                  {
                     for(nghCount = 0; nghCount < NL_MAX_NGH_ALARM; nghCount ++)
                     {          
                        if(((NlNghServCellCb *)nghServCb->
                          servCellInfo.alarmInfo.peerInfo[nghCount].peerAddr == nghServCell) &&
                          (TRUE == nghServCb->servCellInfo.alarmInfo.peerInfo[nghCount].isActive) &&
                          (NL_ALARM_PEER_NGH_SERV_CELL == 
                            nghServCb->servCellInfo.alarmInfo.peerInfo[nghCount].peerType))
                        {   
                           nghServCb->servCellInfo.alarmInfo.peerInfo[nghCount].peerAddr = NULLP; 
                           nghServCb->servCellInfo.alarmInfo.peerInfo[nghCount].isActive = FALSE; 
                           nghServCb->servCellInfo.alarmInfo.numPeerAlarm --;
                           if(0 == nghServCb->servCellInfo.alarmInfo.numPeerAlarm)
                           {
                              nghServCb->servCellInfo.alarmInfo.isAlarmRaised = FALSE;
                           }
                        }
                     }
                  }          
               }                 
            }                                                                      
            else if(NL_ALARM_PEER_NGH_NGH_CELL == nghServCell->
                   servCellInfo.alarmInfo.peerInfo[count].peerType)   
            {                                                                           
               nghNghCb = (NlNghNghCellCb *)nghServCell->
                           servCellInfo.alarmInfo.peerInfo[count].peerAddr;  
               if(NULLP != nghNghCb)                                                    
               {                                                                        
                  if(TRUE == nghNghCb->nghNghCellInfo.alarmInfo.isAlarmRaised)
                  {
                     for(nghCount = 0; nghCount < NL_MAX_NGH_ALARM; nghCount ++)
                     {  
                        if(((NlNghServCellCb *)nghNghCb->
                           nghNghCellInfo.alarmInfo.peerInfo[nghCount].peerAddr == nghServCell) &&
                           (TRUE == nghNghCb->nghNghCellInfo.alarmInfo.peerInfo[nghCount].isActive) &&
                           (NL_ALARM_PEER_NGH_SERV_CELL == 
                             nghNghCb->nghNghCellInfo.alarmInfo.peerInfo[nghCount].peerType))
                        {           
                           nghNghCb->nghNghCellInfo.alarmInfo.peerInfo[nghCount].peerAddr = NULLP;
                           nghNghCb->nghNghCellInfo.alarmInfo.peerInfo[nghCount].isActive = FALSE;
                           nghNghCb->nghNghCellInfo.alarmInfo.numPeerAlarm --;
                           if(0 == nghNghCb->nghNghCellInfo.alarmInfo.numPeerAlarm)
                           {
                              nghNghCb->nghNghCellInfo.alarmInfo.isAlarmRaised = FALSE;
                           }
                        }
                     }
                  }
               }
            }       
         }                                                                        
      }                                                                           
   }
   /*If all the peer alarm cleared then make the alarm raised flag as FALSE*/    
   for(count = 0; count < NL_MAX_NGH_ALARM; count ++)
   {
      if(nghServCell->servCellInfo.alarmInfo.peerInfo[count].isActive)
      {
         break;
      }
   }
   if(count == NL_MAX_NGH_ALARM)
   {
      nghServCell->servCellInfo.alarmInfo.isAlarmRaised = FALSE;   
   }                 
   RETVALUE(ROK);
}

/**
 * @brief store the alarm information in neighbor control block
 *
 * @details
 *
 *     Function : nlStoreNghPeerAlarmInfo
 *
 *     This function will store the peer neighbor alarm related information
 *     
 *
 *  @param[in]  alarmInfo : alarm information of the serving cell
 *  @param[in]  alarmId   : alarm information raised either PCI collision/confusion
 *  @param[in]  peerType  : peer type for raising alarm
 *  @param[in]  peerAddr  : peer address
 *  @return  S16
 *     -# Success       : ROK
 *     -# Failure       : RFAILED
 *
 **/
#ifdef ANSI
PUBLIC S16 nlStoreNghPeerAlarmInfo
(
NlAlarmInfo     *alarmInfo, 
LnlDgnAlarm     alarmId, 
NlAlarmPeerType peerType, 
Void            *peerAddr
)
#else
PUBLIC S16 nlStoreNghPeerAlarmInfo(alarmInfo, alarmId, peerType, peerAddr)
(
NlAlarmInfo     *alarmInfo;
LnlDgnAlarm     alarmId;
NlAlarmPeerType peerType;
Void            *peerAddr;
)
#endif
{
   U8   count;
   TRC3(nlStoreNghPeerAlarmInfo);                                                     
   alarmInfo->isAlarmRaised = TRUE;                                
   for(count = 0; count < NL_MAX_NGH_ALARM; count ++)              
   {                                                               
      if(FALSE == alarmInfo->peerInfo[count].isActive)             
      {                                                            
         alarmInfo->peerInfo[count].peerType = peerType;          
         alarmInfo->peerInfo[count].peerAddr = peerAddr;          
         alarmInfo->peerInfo[count].isActive = TRUE;              
         alarmInfo->numPeerAlarm ++;                              
         break;                                                   
      }                                                           
   }                                                              
   if(count < NL_MAX_NGH_ALARM)                                   
   {                                                              
      if(LNL_ALARM_PCI_CONFLICT == alarmId)     
      {                                                               
         alarmInfo->peerInfo[count].alarmId = NL_ALARM_PCI_CONFLICT;  
      }                                                               
      if(LNL_ALARM_PCI_CONFUSION == alarmId)      
      {                                                              
         alarmInfo->peerInfo[count].alarmId = NL_ALARM_PCI_CONFUSION;
      }                                                              
   }                        
   RETVALUE(ROK);
}

/**
 * @brief update the alarm information related to neighbor
 *
 * @details
 *
 *     Function : nlUpdateNghCellAlarmInfo
 *
 *     This function will update the alarm related information in neighbor cell
 *     control block as well as existing neighbor cell information
 *
 *  @param[in]  nghNghServCellCb : neighbor cell information in SON
 *  @param[in]  alarm            : alarm information
 *  @return  S16
 *     -# Success       : FALSE
 *     -# Failure       : TRUE
 *
 **/

#ifdef ANSI
PUBLIC S16 nlUpdateNghCellAlarmInfo
(
NlNghServCellCb *nghCellCb,
NlAlarm         *alarm
)
#else
PUBLIC S16 nlUpdateNghCellAlarmInfo(nghCellCb, alarm)
(
NlNghServCellCb *nghCellCb;
NlAlarm         *alarm;
)
#endif
{
   NlCellCb         *cellCb       = NULLP;
   NlNghNghCellCb   *nghNghCellCb = NULLP;
   NlNghServCellCb  *nghCb        = NULLP;
   U32               alarmCount;
   TRC3(nlUpdateNghCellAlarmInfo);
   if(alarm->isAlarmRaised)
   {
      for(alarmCount = 0; alarmCount < alarm->numAlarmRaised; alarmCount ++)
      {
         if((nghCellCb->servCellInfo.pci == alarm->
               alarmRaised[alarmCount].dgn.u.addInfo.pci) &&
            (nghCellCb->servCellInfo.ecgi.cellId == alarm->
               alarmRaised[alarmCount].dgn.u.addInfo.cellId))
         {
            nlStoreNghPeerAlarmInfo(&(nghCellCb->servCellInfo.alarmInfo), 
              alarm->alarmRaised[alarmCount].dgn.alarmId, 
              alarm->alarmRaised[alarmCount].peerType, 
              alarm->alarmRaised[alarmCount].peerAddr);
            /*Update the Peer neighbor information also for which PCI collision/confusion arise*/
            if(NL_ALARM_PEER_SERV_CELL == alarm->alarmRaised[alarmCount].peerType)
            {
               cellCb = (NlCellCb *)alarm->alarmRaised[alarmCount].peerAddr;
               nlStoreNghPeerAlarmInfo(&(cellCb->cellInfo.alarmInfo), 
                 alarm->alarmRaised[alarmCount].dgn.alarmId, 
                 NL_ALARM_PEER_NGH_SERV_CELL, nghCellCb);
            }
            else if(NL_ALARM_PEER_NGH_NGH_CELL == alarm->alarmRaised[alarmCount].peerType)
            {
               nghNghCellCb = (NlNghNghCellCb *)alarm->alarmRaised[alarmCount].peerAddr;
               nlStoreNghPeerAlarmInfo(&(nghNghCellCb->nghNghCellInfo.alarmInfo), 
                 alarm->alarmRaised[alarmCount].dgn.alarmId, 
                 NL_ALARM_PEER_NGH_SERV_CELL, nghCellCb);
            }
            else if(NL_ALARM_PEER_NGH_SERV_CELL == alarm->alarmRaised[alarmCount].peerType)
            {
               nghCb = (NlNghServCellCb *)alarm->alarmRaised[alarmCount].peerAddr;
               if(nghCb != nghCellCb)
               {
                  nlStoreNghPeerAlarmInfo(&(nghCb->servCellInfo.alarmInfo), 
                    alarm->alarmRaised[alarmCount].dgn.alarmId, 
                    NL_ALARM_PEER_NGH_SERV_CELL, nghCellCb);
               }
               else
               {
                  alarm->isAlarmRaised = FALSE;
                  alarm->isAlarmSend = FALSE;
               }
            }
         }
      }
   }
   RETVALUE(ROK);
}

/**
 * @brief update the alarm information related to neighbor's neighbor
 *
 * @details
 *
 *     Function : nlUpdateNghNghCellAlarmInfo 
 *
 *     This function will update the alarm related information in neighbor's neighbor cell
 *     control block as well as existing neighbor cell information
 *
 *  @param[in]  nghNghCellCb : neighbor's neighbor cell information in SON
 *  @param[in]  alarm        : alarm information 
 *  @return  S16
 *     -# Success       : FALSE
 *     -# Failure       : TRUE
 *
 **/
#ifdef ANSI
PUBLIC S16 nlUpdateNghNghCellAlarmInfo
(
NlNghNghCellCb *nghNghCellCb,
NlAlarm         *alarm
)
#else
PUBLIC S16 nlUpdateNghNghCellAlarmInfo(nghNghCellCb, alarm)
(
NlNghNghCellCb *nghNghCellCb;
NlAlarm         *alarm;
)
#endif
{
   NlCellCb         *cellCb    = NULLP;
   NlNghServCellCb  *nghCellCb = NULLP;
   NlNghNghCellCb   *nghNghCb  = NULLP;
   U8                alarmCount;
   TRC3(nlUpdateNghNghCellAlarmInfo);
   if(alarm->isAlarmRaised)
   {
      for(alarmCount = 0; alarmCount < alarm->numAlarmRaised; alarmCount ++)
      {
         if((nghNghCellCb->nghNghCellInfo.pci == 
              alarm->alarmRaised[alarmCount].dgn.u.addInfo.pci) && 
           (nghNghCellCb->nghNghCellInfo.ecgi.cellId == 
              alarm->alarmRaised[alarmCount].dgn.u.addInfo.cellId))
         {
            nlStoreNghPeerAlarmInfo(&(nghNghCellCb->nghNghCellInfo.alarmInfo), 
              alarm->alarmRaised[alarmCount].dgn.alarmId, 
              alarm->alarmRaised[alarmCount].peerType, 
              alarm->alarmRaised[alarmCount].peerAddr);
            /*Update the Peer neighbor information also for which PCI collision/confusion arise*/
            if(NL_ALARM_PEER_SERV_CELL == alarm->alarmRaised[alarmCount].peerType)
            {
               cellCb = (NlCellCb *)alarm->alarmRaised[alarmCount].peerAddr;
               nlStoreNghPeerAlarmInfo(&(cellCb->cellInfo.alarmInfo), 
                alarm->alarmRaised[alarmCount].dgn.alarmId,
                  NL_ALARM_PEER_NGH_NGH_CELL, nghNghCellCb);
            }
            else if(NL_ALARM_PEER_NGH_SERV_CELL == alarm->alarmRaised[alarmCount].peerType)
            {
               nghCellCb = (NlNghServCellCb *)alarm->alarmRaised[alarmCount].peerAddr;
               nlStoreNghPeerAlarmInfo(&(nghCellCb->servCellInfo.alarmInfo), 
                 alarm->alarmRaised[alarmCount].dgn.alarmId,
                  NL_ALARM_PEER_NGH_NGH_CELL, nghNghCellCb);
            }
            else if (NL_ALARM_PEER_NGH_NGH_CELL == alarm->alarmRaised[alarmCount].peerType)
            {
               nghNghCb = (NlNghNghCellCb *)alarm->alarmRaised[alarmCount].peerAddr;
               if(nghNghCb != nghNghCellCb)
               {
                  nlStoreNghPeerAlarmInfo(&(nghNghCb->nghNghCellInfo.alarmInfo), 
                    alarm->alarmRaised[alarmCount].dgn.alarmId,
                     NL_ALARM_PEER_NGH_NGH_CELL, nghNghCellCb);
               }
               else
               {
                  alarm->isAlarmRaised = FALSE;
                  alarm->isAlarmSend = FALSE;
               }
            }
         }
      }
   }
   RETVALUE(ROK);
}

/********************************************************************30**

           End of file:     bk_alarm.c@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 17:50:59 2014

*********************************************************************31*/

/********************************************************************40**
  
        Notes:
  
*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/

/********************************************************************60**
  
        Revision history:
  
*********************************************************************61*/
  
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
*********************************************************************91*/

