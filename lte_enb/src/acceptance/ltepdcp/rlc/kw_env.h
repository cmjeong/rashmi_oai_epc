/********************************************************************16**

                         (c) COPYRIGHT 2009 by 
                         Continuous Computing Corporation.
                         All rights reserved.

     This software is confidential and proprietary to Continuous Computing 
     Corporation (CCPU).  No part of this software may be reproduced,
     stored, transmitted, disclosed or used in any form or by any means
     other than as expressly provided by the written Software License 
     Agreement between CCPU and its licensee.

     CCPU warrants that for a period, as provided by the written
     Software License Agreement between CCPU and its licensee, this
     software will perform substantially to CCPU specifications as
     published at the time of shipment, exclusive of any updates or 
     upgrades, and the media used for delivery of this software will be 
     free from defects in materials and workmanship.  CCPU also warrants 
     that has the corporate authority to enter into and perform under the   
     Software License Agreement and it is the copyright owner of the software 
     as originally delivered to its licensee.

     CCPU MAKES NO OTHER WARRANTIES, EXPRESS OR IMPLIED, INCLUDING
     WITHOUT LIMITATION WARRANTIES OF MERCHANTABILITY OR FITNESS FOR
     A PARTICULAR PURPOSE WITH REGARD TO THIS SOFTWARE, SERVICE OR ANY RELATED
     MATERIALS.

     IN NO EVENT SHALL CCPU BE LIABLE FOR ANY INDIRECT, SPECIAL,
     CONSEQUENTIAL DAMAGES, OR PUNITIVE DAMAGES IN CONNECTION WITH OR ARISING
     OUT OF THE USE OF, OR INABILITY TO USE, THIS SOFTWARE, WHETHER BASED
     ON BREACH OF CONTRACT, TORT (INCLUDING NEGLIGENCE), PRODUCT
     LIABILITY, OR OTHERWISE, AND WHETHER OR NOT IT HAS BEEN ADVISED
     OF THE POSSIBILITY OF SUCH DAMAGE.

                       Restricted Rights Legend

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
     forth in the written Software License Agreement between CCPU and
     its Licensee. Among other things, the use of this software
     may be limited to a particular type of Designated Equipment, as 
     defined in such Software License Agreement.
     Before any installation, use or transfer of this software, please
     consult the written Software License Agreement or contact CCPU at
     the location set forth below in order to confirm that you are
     engaging in a permissible use of the software.

                    Continuous Computing Corporation
                    9450, Carroll Park Drive
                    San Diego, CA-92121, USA

                    Tel: +1 (858) 882 8800
                    Fax: +1 (858) 777 3388

                    Email: support@trillium.com
                    Web: http://www.ccpu.com

*********************************************************************17*/


/********************************************************************20**
  
        Name:     LTE RLC file 
    
        Type:     C include file
  
        Desc:     This file contains the constants required for LTE-RLC.
                  The defines in this file need to be changed by the customer 
                  to reflect the software architecture needed to run under the 
                  target system hardware architecture.

        File:     kw_env.h

        Sid:      kw_env.h@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:46 2014
  
        Prg:      nm 
  
*********************************************************************21*/
/** @file kw_env.h
@brief RLC Hash definitions
*/

#ifndef __KWENVH__
#define __KWENVH__

#define KW_MAX_RLC_INSTANCES            2
#define KW_MAXIMUM_LI                   10
/* kw003.201 Adding new environment variables */
/* This parameter is utilized when KW_BG_DL_PROC enbled. This parameter */
/* defines how many PDUs may be released in one go without affecting    */
/* TTI response time                                                    */
/* kw004.201 modifed the value from 20 to 15 */
/* kw006.201 CR ccpu00111716 */
#define KW_AM_MAX_PDUS_RLS              15
/* This parameter governs maximum number of PDUs to processed at a      */
/* given point when KW_BG_UL_PROC is enabled in both AM and UM modes.   */
/* kw004.201 modifed the value from 20 to 5 */
/* kw006.201 CR ccpu00117290 */
#define KW_AM_UM_MAX_UL_PDUS            5 

#define PJ_MAX_PDCP_INSTANCES   2
#endif /* __KWENVH__ */
  
/********************************************************************30**
  
         End of file:     kw_env.h@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:46 2014
  
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
/main/1      ---       nm   1. Initial release.
/main/2      ---       nm   1. LTERLC Release 2.1
/main/3      kw003.201 vp   1. Fixes for re-segmentation, segement offset
                               value and optimization 
/main/4      kw004.201 ap   1. Modified the values of KW_AM_MAX_PDUS_RLS and
                               KW_AM_MAX_UL_PDUS
/main/5      kw006.201 rd   1. Changed the name of KW_AM_MAX_UL_PDUS to 
                               KW_AM_UM_MAX_UL_PDUS.
*********************************************************************91*/

