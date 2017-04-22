/********************************************************************20**
  
     Name:    Ring Buffer 
  
     Type:     C include file
  
     Desc:     This file implements the funcitons required to isolate
               freeing of packer buffers from Main stack processing. This will be 
               usefull in a hyper threaded environment where the freeing can be
               done from low priority thread
  
     File:    ss_rbuf.h 
  
     Sid:      ss_rbuf.h@@/main/TeNB_Main_BR/2 - Thu Apr 24 17:09:45 2014
   
     Prg:      
  
*********************************************************************21*/
#ifndef __SS_RBUF_H__
#define __SS_RBUF_H__

#ifdef __cplusplus
extern "C" {
#endif


#define SS_RNG_TX                    1
#define SS_RNG_RX                    0

#define SS_RNG_MAX_DLPDCP_TO_DLRLC_DQ_CNT 80 /* Max Buffer Read from Ring Buffer from PDCP to RLC in DL Direction */
#define SS_RNG_MAX_ULMAC_TO_ULRLC_DQ_CNT  25
#if 0
#define SS_RNG_DLPDCP_TO_DLRLC_SIZE       640
/* ccpu00143253: Changing SS_RNG_DLPDCP_TO_DLRLC_SIZE from 128 to 512, 
  * as the forwarded data packet drop observed during Handover */
#define SS_RNG_DLPDCP_TO_DLRLC_SIZE     1024
#endif

/* Ring Size Defines, powers of 2 only  */
//#define SS_RNG_ICPU_TO_DLPDCP_SIZE      128
#define SS_RNG_ICPU_TO_DLPDCP_SIZE      512
 /* ccpu00143253: Changing SS_RNG_DLPDCP_TO_DLRLC_SIZE from 128 to 512, as the 
  * forwarded data packet drop observed during Handover */
#define SS_RNG_DLPDCP_TO_DLRLC_SIZE     1024
//#define SS_RNG_L2_RT_TO_FREE_MGR_SIZE   512 
//#define SS_RNG_L2_NRT_TO_FREE_MGR_SIZE  640
/* Increasing from 512 to 1024
   Increasing from 1024 to 2048 to handle free after re-est */ 
#define SS_RNG_L2_RT_TO_FREE_MGR_SIZE   2048
#define SS_RNG_L2_NRT_TO_FREE_MGR_SIZE  2048 
#define SS_RNG_L2_DLRLC_TO_FREE_MGR_SIZE  2048 
#define SS_RNG_PRC_L1D_TO_CL_SIZE       32
#define SS_RNG_PRC_FREE_TO_CL_SIZE      256
#define SS_RNG_ICPU_TO_DAM_SIZE         1024
#define SS_RNG_PDCP_TO_CIPH_SIZE        2048
#define SS_RNG_CIPH_TO_PDCP_SIZE        1024
#define SS_RNG_ULMAC_TO_ULRLC_SIZE      128
#define SS_RNG_ICCRX_TO_DLRLC_SIZE      640
#define SS_RNG_DL_SMSG_REUSE_SIZE       384
#define SS_RNG_DLRLC_TO_DLMAC_SIZE      512
#define SS_RNG_BUF_MAC_HARQ_SIZE        256
#define SS_FREE_MGR_MAX_FREE            32
/* Ring Element Size Defines */
#define SS_RNG_BUF_ELEM           sizeof(SsRngBufElem)

#ifdef __cplusplus
}
#endif

#endif

