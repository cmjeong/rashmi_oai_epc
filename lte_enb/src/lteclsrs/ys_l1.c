/**
 *
 * \section COPYRIGHT
 *
 * Copyright 2013-2015 Software Radio Systems Limited
 *
 * \section LICENSE
 *
 * This file is part of the srsLTE library.
 *
 * srsLTE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * srsLTE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * A copy of the GNU Affero General Public License can be found in
 * the LICENSE file in the top-level directory of this distribution
 * and at http://www.gnu.org/licenses/.
 *
 */
/* header include files -- defines (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timers defines */
#include "cm_hash.h"       /* common hash list defines */
#include "cm_llist.h"      /* common linked list defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_tkns.h"       /* common tokens */
#include "cm_lte.h"
#include "ctf.h"           /* CTF defines */
#include "lys.h"           /* layer management typedefs for CL */
#include "tfu.h"
#include <sys/time.h>
#include "ys_pal_err.h"        /* YS error defines */
#include "ys_pal.h"

/* header/extern include files (.x) */
#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_lte.x"
#include "ctf.x"           /* CTF types */
#include "lys.x"           /* layer management typedefs for CL */
#include "tfu.x"
#include "ys_pal.x" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/select.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include "srslte/srslte.h"
#include "ys_pal.x"

#include "srslte/rf/rf.h"
srslte_rf_t *rf;

#if 0
uint8_t sib1[17] =  {0x60, 0x40, 0x04, 0x0f, 0x00, 0x01, 0x00, 0x00, 0x00, 0x18, 0x03, 0x50, 0x80, 0x00, 0x00};  

unsigned  char sib2[30] =  {0x00, 0x00, 0x1c, 0x31, 0x18, 0x6f, 0xe1, 0x2a, 0x80,0x35, 0x03, 0xa2, 0xe0, 0x10, 0x00, 0x06, 0x00, 0xc8, 0x6b, 0xb1, 0x6a ,0xa1 ,0x37, 0x30 ,0xa0 ,0x60};  
#endif

/*RNTI Hash defines for different RNTIs*/
#define YS_TR_PRNTI  65534
#define YS_TR_SIRNTI 65535

/*Macros That are used for filling the DCI requests  */
#define YS_TR_IS_UL_DCI(_format) ((_format == TFU_DCI_FORMAT_0) ||\
                                  (_format == TFU_DCI_FORMAT_3) ||\
                                  (_format == TFU_DCI_FORMAT_3A ))

#define YS_TR_GET_MODULATION_ORDER(_mcs) \
((_mcs < 10) ? 2 : \
 (_mcs < 17) ? 4 : \
 (_mcs < 29) ? 6 : \
 (_mcs == 29) ? 2 : \
 (_mcs == 30) ? 4 : \
 (_mcs == 31) ? 6 : 2) 

char *rf_args = "";
float rf_amp = 0.8, rf_gain = 70.0, rf_freq = 1860000000;
float rf_freq_rx = 1765000000; 

srslte_enb_dl_t *dl_init;
srslte_enb_ul_t *ul_init;
srslte_softbuffer_tx_t softbuffer;

cf_t *output_buffer = NULL;
cf_t *input_buffer = NULL;
int sf_n_re, sf_n_samples;
bool start_of_burst = true; 
bool go_exit = false; 

srslte_prach_cfg_t prach_cfg;
srslte_refsignal_dmrs_pusch_cfg_t pusch_cfg;
srslte_pucch_cfg_t pucch_cfg;
uint32_t p_rachfreq_offset = 0;
void net_thread_fnc(void *args);
void net_thread_fnc_reader(void *args);

#if 1
#define SS_DEBUGP(fmt, args...)

#else

#endif
PUBLIC S16 YsUiTful1ReadReq
(
Pst * pst,
SpId spId,
U32 temp 
)
{
	static int decode_tti = 0;

	uint32_t indices[100];
	float offsets[100];
	float peak2avg[100];
	int numRach = 0;
	SS_DEBUGP("L1UL: Rach detection tti(%d)\n", decode_tti);
	numRach = srslte_enb_ul_detect_prach(ul_init,
			decode_tti,
			p_rachfreq_offset,
			&input_buffer[sf_n_samples* (decode_tti % 10)],
			indices,
			offsets,
			peak2avg);

	if(numRach) {
		SS_DEBUGP("Rach detected (%d)\n", numRach);
	}
	decode_tti++;
	RETVALUE(ROK);
}

void base_init() {

	/* init memory */
	dl_init = srslte_vec_malloc(sizeof(srslte_enb_dl_t) + 100);
	ul_init = srslte_vec_malloc(sizeof(srslte_enb_ul_t) + 100);

	rf = srslte_vec_malloc(sizeof(srslte_rf_t) + 100);
	if (!rf) {
		perror("malloc");
		exit(-1);
	}

	output_buffer = srslte_vec_malloc( (10 *(sizeof(cf_t) * sf_n_samples)) + 100);
	if (!output_buffer) {
		perror("malloc");
		exit(-1);
	}

	input_buffer = srslte_vec_malloc((sizeof(cf_t)*sf_n_samples *10) + 100);
	if (!input_buffer) {
		perror("malloc");
		exit(-1);
	}

	SS_DEBUGP("Opening RF device...\n");
	if (srslte_rf_open(rf, rf_args)) {
		fprintf(stderr, "Error opening rf\n");
		exit(-1);
	}
}

void sig_int_handler(int signo)
{
  SS_DEBUGP("SIGINT received. Exiting...\n");
  if (signo == SIGINT) {
    go_exit = true;
  }
}

int srslte_enb_rf_init(srslte_enb_dl_t *q)
{
	int srate = srslte_sampling_freq_hz(dl_init->cell.nof_prb);    
	if (srate != -1) {  
		if (srate < 10e6) {          
			srslte_rf_set_master_clock_rate(rf, 4*srate);        
		} else {
			srslte_rf_set_master_clock_rate(rf, srate);        
		}
		SS_DEBUGP("Setting sampling rate %.2f MHz\n", (float) srate/1000000);
		float srate_rf = srslte_rf_set_tx_srate(rf, (double) srate);
		if (srate_rf != srate) {
			fprintf(stderr, "Could not set sampling rate\n");
			exit(-1);
		}
	} else {
		exit(-1);
	}
	printf("Set TX gain: %.1f dB\n", srslte_rf_set_tx_gain(rf, rf_gain));
	printf("SS :Set TX freq: %.2f MHz\n",
			srslte_rf_set_tx_freq(rf, rf_freq) / 1000000);

	float srate_rf = srslte_rf_set_rx_srate(rf, (double) srate);

	srslte_rf_set_rx_gain(rf, 50);

	printf("SS :Set RX freq: %.2f MHz\n",
	srslte_rf_set_rx_freq(rf, rf_freq_rx)/1000000);

	srslte_rf_start_rx_stream(rf);
}

/*
*
*       Fun:   ysTrFillDlschInfo
*
*       Desc:  This function will be used to fill the  DLSCH Info
*
*       Ret:  ROK/RFAILED 
*
*       Notes: None
*
*       File:  ys_tr_msg.c
*
*/

PRIVATE S16 ysTrFillDlschInfo
(
srslte_enb_dl_t             *q,
srslte_ra_dl_grant_t       *grant,
TfuDatReqPduInfo           *datInfo,
U8                         *pduSize,
U8                         idx
)
{
   MsgLen length;
   if ((Buffer *)datInfo->mBuf[idx] == NULLP)
      RETVALUE(RFAILED);
   SFndLenMsg((Buffer *)datInfo->mBuf[idx], &length );
   *pduSize = length;
   srslte_ra_dl_dci_t dci; 

   SS_DEBUGP("L1 PDSCH DATA format(%d) riv(%d) rv(%d) mcs(%d) \n", datInfo->dciInfo.format, datInfo->dciInfo.u.format1aAllocInfo.alloc.u.riv, datInfo->dciInfo.u.format1aAllocInfo.rv, datInfo->dciInfo.u.format1aAllocInfo.mcs);

   switch(datInfo->dciInfo.format)
   {
      case TFU_DCI_FORMAT_1A:
     {
	     dci.alloc_type =  SRSLTE_RA_ALLOC_TYPE2;
	     dci.type2_alloc.mode = SRSLTE_RA_TYPE2_LOC;
	     dci.type2_alloc.L_crb = (datInfo->dciInfo.u.format1aAllocInfo.alloc.u.riv / 25) + 1;
	     dci.type2_alloc.RB_start = datInfo->dciInfo.u.format1aAllocInfo.alloc.u.riv % 25;
	     dci.type2_alloc.riv = datInfo->dciInfo.u.format1aAllocInfo.alloc.u.riv;
	     dci.type2_alloc.n_prb1a = 0;
	     dci.dci_is_1a = 1;
	     dci.rv_idx = datInfo->dciInfo.u.format1aAllocInfo.rv;
	     dci.mcs_idx = datInfo->dciInfo.u.format1aAllocInfo.mcs;

	     srslte_ra_dl_dci_to_grant(&dci, q->cell.nof_prb, datInfo->rnti, grant);
        }
    break;
#if 0
   /* MIMO */
   case TFU_DCI_FORMAT_2A:
   {
      dlschPdu->dlschPduLen = length;
      dlschPdu->rnti = datInfo->rnti;
      dlschPdu->resAllocationType = !datInfo->dciInfo.u.format2AAllocInfo.isAllocType0;

      cmMemcpy((U8 *)&dlschPdu->rbCoding, datInfo->dciInfo.u.format2AAllocInfo.resAllocMap, 4 );
      /* TODO: Resource Allocation Map Assignement */
      /* Fix for 20MHz RB Coding */
      if(cellCb->dlBw == CTF_BW_RB_100)
      {
         dlschPdu->rbCoding = (dlschPdu->rbCoding & 0xFFFFFF80) >> 7;
      }
      else
      {
         dlschPdu->rbCoding = (dlschPdu->rbCoding & 0xFFFF8000) >> 15;
      }
      dlschPdu->mcs = YS_TR_GET_MODULATION_ORDER(datInfo->dciInfo.u.format2AAllocInfo.tbInfo[idx].mcs); 
      dlschPdu->redundancyVersion = datInfo->dciInfo.u.format2AAllocInfo.tbInfo[idx].rv;
      dlschPdu->transportBlocks = idx + 1;

      dlschPdu->tbToCodeWordSwapFlag = datInfo->dciInfo.u.format2AAllocInfo.transSwap ? 1 : 0;
      dlschPdu->transmissionScheme   = 2; /* Spatial Multiplexing */
/*ccpu00126220  MIMO fix for one TB is disabled */
      if(((datInfo->dciInfo.u.format2AAllocInfo.tbInfo[0].mcs == 0) &&
         (datInfo->dciInfo.u.format2AAllocInfo.tbInfo[0].rv == 1)) ||
         ((datInfo->dciInfo.u.format2AAllocInfo.tbInfo[1].mcs == 0) &&
          (datInfo->dciInfo.u.format2AAllocInfo.tbInfo[1].rv == 1)))
      {
          dlschPdu->transmissionScheme = 1; /* Tx Diversity */
         /* Below setting is for L1 requirement as per the integ document */
         if((datInfo->dciInfo.u.format2AAllocInfo.tbInfo[0].mcs == 0 ) &&
            (datInfo->dciInfo.u.format2AAllocInfo.tbInfo[0].rv == 1))
         {
            dlschPdu->tbToCodeWordSwapFlag = 1; /* Only 2nd TB is present */
         }else
         {
            dlschPdu->tbToCodeWordSwapFlag = 0;  /* Only 1st TB is present */
         }
      }
      /* Fix for NACKS in case of MIMO SSF enabled */
      /* Changed from 2 to 1 in case of transmission scheme 2;
         as in case of Large Delay CDD, each TB is mapped to only 1 antenna */
      if(dlschPdu->transmissionScheme == 2) 
      {
         dlschPdu->numOfLayers          = 1; 
      }
      else
      {
         dlschPdu->numOfLayers          = 2; 
      }
      dlschPdu->numOfSubBand         = 0;       
      /* Mccabe Fix */
      ysTrFillUeCatPa(datInfo->rnti, cellCb, dlschPdu);   
      dlschPdu->deltaPowerOffsetAIndex = datInfo->deltaPowOffIdx;
      dlschPdu->numRbPerSubBand = 0;
      dlschPdu->numbfVector = 0;
      /* Below parameters are not used in DCI 2A, still filing it to avoid confusions */
      dlschPdu->nGap = 0;
      dlschPdu->nPRB = 0;
    }
    break;
    case TFU_DCI_FORMAT_1:
    {
       dlschPdu->dlschPduLen = length;
       dlschPdu->rnti = datInfo->rnti;
       dlschPdu->resAllocationType = !datInfo->dciInfo.u.format1AllocInfo.isAllocType0;
       dlschPdu->mcs = YS_TR_GET_MODULATION_ORDER(datInfo->dciInfo.u.format1AllocInfo.mcs);
       
       cmMemcpy((U8 *)&dlschPdu->rbCoding, datInfo->dciInfo.u.format1AllocInfo.resAllocMap, 4 );
       dlschPdu->rbCoding = (dlschPdu->rbCoding & 0xFFFF8000) >> 15;

       dlschPdu->redundancyVersion = datInfo->dciInfo.u.format1AllocInfo.rv;

       dlschPdu->transportBlocks = datInfo->nmbOfTBs;
       /* This is used in MIMO to indicate if only one TB
        * is used even when there is MIMO */
       dlschPdu->tbToCodeWordSwapFlag = 0;
#ifdef LTEMAC_MIMO
       /* MIMO Configuration Support */
       if(cellCb->cellCfg.txAntennaPorts == CTF_AP_CNT_1)
       {
          dlschPdu->transmissionScheme = 0; 
          dlschPdu->numOfLayers        = 1;
       }
       else
       {
          dlschPdu->transmissionScheme = 1; 
          dlschPdu->numOfLayers        = 2;
       }
#else
       dlschPdu->transmissionScheme = 0; 
       dlschPdu->numOfLayers        = 1;
#endif
       dlschPdu->numOfSubBand = 0;
       /* Mccabe Fix */
       ysTrFillUeCatPa(datInfo->rnti, cellCb, dlschPdu);   
       dlschPdu->deltaPowerOffsetAIndex = 0; /*Non MIMO mode */
       dlschPdu->nPRB = 0;
       dlschPdu->numRbPerSubBand = datInfo->numBfPrbPerSb;
       dlschPdu->numbfVector = datInfo->numBfVectors;
       /*Codebook index is not filled for DciFormat1*/
       /*TODO:If the transmission scheme is TM7 then beamforming vectors need to be filled*/
       /*ysTrFillBfVectorInfo((FAPI_beamFormingVectorInfo_st *)dlschPdu->bfVector ,
                            datInfo->bfVector ,
                            &pduSize); */
       /*TODO: If BfVector is filled then add this size to the pdusize */
     }
     break;
     
     case TFU_DCI_FORMAT_1B:
     {
        dlschPdu->dlschPduLen = length;
        dlschPdu->rnti = datInfo->rnti;
        dlschPdu->resAllocationType = 2;
        dlschPdu->vRBAssignmentFlag = !(datInfo->dciInfo.u.format1bAllocInfo.isLocal);
        dlschPdu->rbCoding = datInfo->dciInfo.u.format1bAllocInfo.alloc.u.riv;
        dlschPdu->mcs = YS_TR_GET_MODULATION_ORDER(datInfo->dciInfo.u.format1bAllocInfo.mcs);
        dlschPdu->redundancyVersion = datInfo->dciInfo.u.format1bAllocInfo.rv;

        dlschPdu->transportBlocks = datInfo->nmbOfTBs;
       /* This is used in MIMO to indicate if only one TB
        * is used even when there is MIMO */
        dlschPdu->tbToCodeWordSwapFlag = 0;
        dlschPdu->transmissionScheme = 3;/* Closed loop multiplexing */   
        dlschPdu->numOfLayers = 1; /*Number of layer should be 1*/
        dlschPdu->numOfSubBand = 1; 
        
        /*Codebook is indexed to 0 as we currently receive only 1 PMI from L2 */ 
        dlschPdu->subBandInfo[0] = datInfo->dciInfo.u.format1bAllocInfo.tPmi;/*PMI as determined*/
        
        /* Mccabe Fix */
        ysTrFillUeCatPa(datInfo->rnti, cellCb, dlschPdu);   
        
        dlschPdu->deltaPowerOffsetAIndex = datInfo->deltaPowOffIdx;/*Copy from what L2 sends
                                                                        This should be zero */
        dlschPdu->nGap = datInfo->dciInfo.u.format1bAllocInfo.nGap2.val;
        dlschPdu->nPRB = 0;
        dlschPdu->numRbPerSubBand = datInfo->numBfPrbPerSb;
        dlschPdu->numbfVector = datInfo->numBfVectors;
        ysTrFillBfVectorInfo((FAPI_beamFormingVectorInfo_st *)dlschPdu->bfVector ,
                            datInfo->bfVector ,
                            pduSize);
        /*TODO:remember to add to current pdu size the size of BFVector */
     } 
     break;

     case  TFU_DCI_FORMAT_1D:
     {
        dlschPdu->dlschPduLen = length;
        dlschPdu->rnti = datInfo->rnti;
        dlschPdu->resAllocationType = 2;
        dlschPdu->vRBAssignmentFlag = !(datInfo->dciInfo.u.format1dAllocInfo.isLocal);
        dlschPdu->rbCoding = datInfo->dciInfo.u.format1dAllocInfo.alloc.u.riv;
        dlschPdu->mcs = YS_TR_GET_MODULATION_ORDER(datInfo->dciInfo.u.format1dAllocInfo.mcs);
        dlschPdu->redundancyVersion = datInfo->dciInfo.u.format1dAllocInfo.rv;
       

        dlschPdu->transportBlocks = datInfo->nmbOfTBs;
       /* This is used in MIMO to indicate if only one TB
        * is used even when there is MIMO */
        dlschPdu->tbToCodeWordSwapFlag = 0;
        dlschPdu->transmissionScheme = 4;
        dlschPdu->numOfLayers = 2; 
        /* dlschPdu->numOfSubBand = 0; */
        dlschPdu->numOfSubBand = 1; /* We get only 1 PMI*/
          /*Codebook is indexed to 0 as we currently receive only 1 PMI from L2 */
        dlschPdu->subBandInfo[0] = datInfo->dciInfo.u.format1dAllocInfo.tPmi;/*PMI as determined*/

        /* Mccabe Fix */
        ysTrFillUeCatPa(datInfo->rnti, cellCb, dlschPdu);   
       
        dlschPdu->deltaPowerOffsetAIndex = datInfo->deltaPowOffIdx; /*MU-MIMO mode.Non-zero
                                                                        for this mode refer 36.213v8
                                                                        section 5.2 */
                                                                       
        dlschPdu->nGap = datInfo->dciInfo.u.format1dAllocInfo.nGap2.val;
        dlschPdu->nPRB = 0; 
        dlschPdu->numRbPerSubBand = datInfo->numBfPrbPerSb;
        dlschPdu->numbfVector = datInfo->numBfVectors;
       /*dlschPdu->codebook_index = 0; *//*Not applicable for 1 antenna port */
       /*ysTrFillBfVectorInfo((FAPI_beamFormingVectorInfo_st *)dlschPdu->bfVector ,
                            datInfo->bfVector ,
                            &pduSize); */
     }
     break;
  
     case TFU_DCI_FORMAT_2:
     {
        dlschPdu->dlschPduLen = length;
        dlschPdu->rnti = datInfo->rnti;
        dlschPdu->resAllocationType = !datInfo->dciInfo.u.format2AllocInfo.isAllocType0;

        cmMemcpy((U8 *)&dlschPdu->rbCoding, datInfo->dciInfo.u.format2AllocInfo.resAllocMap, 4 );
/*Right shifted to match the Lower ends of the byte  */
#if 1
   
        dlschPdu->rbCoding = (dlschPdu->rbCoding & 0xFFFF8000) >> 15;
#endif

        dlschPdu->mcs = YS_TR_GET_MODULATION_ORDER(datInfo->dciInfo.u.format2AllocInfo.tbInfo[idx].mcs);
        dlschPdu->redundancyVersion = datInfo->dciInfo.u.format2AllocInfo.tbInfo[idx].rv;
        dlschPdu->transportBlocks = idx + 1;
        dlschPdu->tbToCodeWordSwapFlag = datInfo->dciInfo.u.format2AllocInfo.transSwap ? 1 : 0;
        if(ROK != ysTrFillDciFormat2DlSchInfo(dlschPdu, datInfo))/*klocworks fix*/
        {
           RETVALUE(RFAILED);
        }

        /* Mccabe Fix */
        ysTrFillUeCatPa(datInfo->rnti, cellCb, dlschPdu);   

        dlschPdu->deltaPowerOffsetAIndex = datInfo->deltaPowOffIdx;
        dlschPdu->numRbPerSubBand        = 0;
        dlschPdu->numbfVector            = 0;
     }
     break;  
#endif
     default:
     {
        SS_DEBUGP("\n Invalid DCI formats in DL\n");
     }
     break;
   }/*End of switch */
     
   RETVALUE(ROK);
}

/*
*
*       Fun:   ysTrFillDciFormat1A
*
*       Desc:  This function will be used to fill the DCI format 1A
*
*       Ret:  ROK/RFAILED 
*
*       Notes: None
*
*       File:  ys_tr_msg.c
*
*/

PRIVATE S16 ysTrFillDciFormat1A
(
 TfuPdcchInfo       *pdcch,
 srslte_ra_dl_dci_t     *dciFormat1A
)
{
    TfuDciInfo* dciInfo          = &pdcch->dci;
    TfuDciFormat1aInfo format1A  = dciInfo->u.format1aInfo;

    dciFormat1A->alloc_type =  SRSLTE_RA_ALLOC_TYPE2;
    dciFormat1A->type2_alloc.mode = SRSLTE_RA_TYPE2_LOC;
    dciFormat1A->type2_alloc.L_crb = (format1A.t.pdschInfo.allocInfo.alloc.u.riv / 25) + 1;
    dciFormat1A->type2_alloc.RB_start = format1A.t.pdschInfo.allocInfo.alloc.u.riv % 25;
    dciFormat1A->type2_alloc.riv = format1A.t.pdschInfo.allocInfo.alloc.u.riv;
    dciFormat1A->type2_alloc.n_prb1a = 0;
    dciFormat1A->dci_is_1a = 1;
    dciFormat1A->ndi = format1A.t.pdschInfo.allocInfo.ndi;
    dciFormat1A->harq_process = format1A.t.pdschInfo.allocInfo.harqProcId.val;
    dciFormat1A->rv_idx = format1A.t.pdschInfo.allocInfo.rv;
    dciFormat1A->mcs_idx = format1A.t.pdschInfo.allocInfo.mcs;

    RETVALUE (ROK);
}

#if 0
/*      
*
*       Fun:   ysTrFillDciFormat1B
*
*       Desc:  This function will be used to fill the DCI format 1B
*
*       Ret:  ROK/RFAILED
*
*       Notes: None
*
*       File:  ys_tr_msg.c
*
*/

PRIVATE S16 ysTrFillDciFormat1B
(
 TfuPdcchInfo       *pdcch,
 srslte_ra_dl_dci_t     *dlpdu
)
{
    /* This format is not tested */
    TfuDciInfo* dciInfo          = &pdcch->dci;
    TfuDciFormat1bInfo format1B  = dciInfo->u.format1bInfo;
    switch (pdcch->aggrLvl)
    {
      case CM_LTE_AGGR_LVL1:
         dciFormat1B->aggregationLevel = 1;
      break;
      case CM_LTE_AGGR_LVL2:
        dciFormat1B->aggregationLevel = 2;
      break;
      case CM_LTE_AGGR_LVL4:
        dciFormat1B->aggregationLevel = 4;
      break;
      case CM_LTE_AGGR_LVL8:
        dciFormat1B->aggregationLevel = 8;
      break;
   }
 
    dciFormat1B->tPMI=format1B.allocInfo.tPmi;
    dciFormat1B->pmi=format1B.allocInfo.pmiCfm;
    dciFormat1B->vRBAssignmentFlag = !(format1B.allocInfo.isLocal) ;
    dciFormat1B->tpc = format1B.tpcCmd ;
    
    dciFormat1B->rbCoding = format1B.allocInfo.alloc.u.riv;
    dciFormat1B->newDataIndicator_1 = format1B.allocInfo.ndi;
    dciFormat1B->harqProcessNum  = format1B.allocInfo.harqProcId;
    dciFormat1B->redundancyVersion_1 = format1B.allocInfo.rv;
#ifdef LTE_TDD
    dciFormat1B->dlAssignmentIndex = format1B.dai;
#else
    dciFormat1B->dlAssignmentIndex = 0;
#endif
    dciFormat1B->mcs_1 = format1B.allocInfo.mcs;
    dciFormat1B->txPower  = YS_TR_TXPOWER_SET;


    dciFormat1B->nGAP=format1B.allocInfo.nGap2.val;
    RETVALUE (ROK);
}

/*
*
*       Fun:   ysTrFillDciFormat1D
*
*       Desc:  This function will be used to fill the DCI format 1D
*
*       Ret:  ROK/RFAILED
*
*       Notes: None
*
*       File:  ys_tr_msg.c
*
*/

PRIVATE S16 ysTrFillDciFormat1D
(
 TfuPdcchInfo       *pdcch,
 srslte_ra_dl_dci_t     *dlpdu
)
{
    /* This format is not tested */
   TfuDciInfo* dciInfo          = &pdcch->dci;
   TfuDciFormat1dInfo format1D  = dciInfo->u.format1dInfo;
   switch (pdcch->aggrLvl)
   {
   case CM_LTE_AGGR_LVL1:
      dciFormat1D->aggregationLevel = 1;
      break;
   case CM_LTE_AGGR_LVL2:
      dciFormat1D->aggregationLevel = 2;
      break;
   case CM_LTE_AGGR_LVL4:
      dciFormat1D->aggregationLevel = 4;
      break;
   case CM_LTE_AGGR_LVL8:
      dciFormat1D->aggregationLevel = 8;
      break;
   }
 
    dciFormat1D->tPMI=format1D.allocInfo.tPmi;
    dciFormat1D->vRBAssignmentFlag = !(format1D.allocInfo.isLocal);
    dciFormat1D->tpc = format1D.tpcCmd;
    
    dciFormat1D->rbCoding = format1D.allocInfo.alloc.u.riv;
    dciFormat1D->newDataIndicator_1 = format1D.ndi;
    dciFormat1D->harqProcessNum  = format1D.harqProcId;
    dciFormat1D->redundancyVersion_1 = format1D.allocInfo.rv;
#ifdef LTE_TDD
    dciFormat1D->dlAssignmentIndex = format1D.dai;
#else
    dciFormat1D->dlAssignmentIndex = 0;
#endif
    dciFormat1D->mcs_1 = format1D.allocInfo.mcs;
    dciFormat1D->txPower  = YS_TR_TXPOWER_SET;


    dciFormat1D->nGAP=format1D.allocInfo.nGap2.val;
    dciFormat1D->dlPowerOffset=format1D.dlPwrOffset;
    
    RETVALUE (ROK);
}

/*
*
*       Fun:   ysTrFillDciFormat1
*
*       Desc:  This function will be used to fill the DCI format 1
*
*       Ret:  ROK/RFAILED 
*
*       Notes: None
*
*       File:  ys_tr_msg.c
*
*/

PRIVATE S16 ysTrFillDciFormat1
(
 TfuPdcchInfo       *pdcch,
 srslte_ra_dl_dci_t     *dlpdu
)
{
   /* This format is not tested */
   TfuDciInfo dciInfo         = pdcch->dci;
   TfuDciFormat1Info format1  = dciInfo.u.format1Info;
   switch (pdcch->aggrLvl)
   {
      case CM_LTE_AGGR_LVL1:
         dciFormat1->aggregationLevel = 1;
      break;
      case CM_LTE_AGGR_LVL2:
         dciFormat1->aggregationLevel = 2;
      break;
      case CM_LTE_AGGR_LVL4:
         dciFormat1->aggregationLevel = 4;
      break;
      case CM_LTE_AGGR_LVL8:
         dciFormat1->aggregationLevel = 8;
      break;
   }

    dciFormat1->resAllocationType = (format1.allocInfo.isAllocType0) ? 0 : 1;
    dciFormat1->mcs_1  = format1.allocInfo.mcs;
    dciFormat1->redundancyVersion_1 = format1.allocInfo.rv;
    cmMemcpy((U8 *)&dciFormat1->rbCoding, format1.allocInfo.resAllocMap,4 );
    dciFormat1->rbCoding = (dciFormat1->rbCoding & 0xFFFF8000) >> 15;
    dciFormat1->newDataIndicator_1 = format1.allocInfo.ndi;
    dciFormat1->harqProcessNum = format1.allocInfo.harqProcId ;
    dciFormat1->tpc  = format1.tpcCmd ;
#if LTE_TDD
    dciFormat1->dlAssignmentIndex = format1.dai;
#else
    dciFormat1->dlAssignmentIndex = 0;
#endif
    dciFormat1->txPower = YS_TR_TXPOWER_SET;
    YS_TR_GET_RNTI_TYPE( pdcch->rnti,dciFormat1->rntiType );
    dciFormat1->padding[1] = 0;
    RETVALUE (ROK);
} 

/*      
*
*       Fun:   ysTrFillDciFormat2
*
*       Desc:  This function will be used to fill the DCI format 2
*
*       Ret:  ROK/RFAILED
*
*       Notes: None
*
*       File:  ys_tr_msg.c
*
*/

PRIVATE S16 ysTrFillDciFormat2
(
 TfuPdcchInfo       *pdcch,
 FAPI_dciFormat2_st  *dciFormat2
)
{

TfuDciInfo* dciInfo          = &pdcch->dci;
    TfuDciFormat2Info format2  = dciInfo->u.format2Info;

   switch (pdcch->aggrLvl)
   {
   case CM_LTE_AGGR_LVL1:
      dciFormat2->aggregationLevel = 1;
      break;
   case CM_LTE_AGGR_LVL2:
      dciFormat2->aggregationLevel = 2;
      break;
   case CM_LTE_AGGR_LVL4:
      dciFormat2->aggregationLevel = 4;
      break;
   case CM_LTE_AGGR_LVL8:
      dciFormat2->aggregationLevel = 8;
      break;
   }
 
    
    dciFormat2->tpc = format2.tpcCmd ;
    dciFormat2->resAllocationType=!format2.allocInfo.isAllocType0;
    dciFormat2->tbToCodeWordSwapFlag=format2.allocInfo.transSwap;
     
    /*Need to fill with the right bit mask for Rb allocation  */
    cmMemcpy((U8 *)&dciFormat2->rbCoding, format2.allocInfo.resAllocMap,4 );
    /*Right shifted to match the Lower ends of the byte  */
#if 1 
   dciFormat2->rbCoding = (dciFormat2->rbCoding & 0xFFFF8000) >> 15;
#endif
 
 
    
    dciFormat2->newDataIndicator_1 = format2.allocInfo.tbInfo[0].ndi;
    dciFormat2->harqProcessNum  = format2.allocInfo.harqProcId;
    dciFormat2->redundancyVersion_1 = format2.allocInfo.tbInfo[0].rv;
#ifdef LTE_TDD
    dciFormat2->dlAssignmentIndex = format2.dai;
#else
    dciFormat2->dlAssignmentIndex = 0;
#endif
    dciFormat2->mcs_1 = format2.allocInfo.tbInfo[0].mcs;
    dciFormat2->txPower  = YS_TR_TXPOWER_SET;
    
    dciFormat2->newDataIndicator_2=format2.allocInfo.tbInfo[1].ndi;
    dciFormat2->redundancyVersion_2=format2.allocInfo.tbInfo[1].rv;
    dciFormat2->mcs_2=format2.allocInfo.tbInfo[1].mcs;

    dciFormat2->preCodingInfo=format2.allocInfo.precoding;
    YS_TR_GET_RNTI_TYPE( pdcch->rnti,dciFormat2->rntiType);


  
    RETVALUE (ROK);
}

/*
*
*       Fun:   ysTrFillDciFormat2a
*
*       Desc:  This function will be used to fill the DCI format 2a
*
*       Ret:  ROK/RFAILED 
*
*       Notes: None
*
*       File:  ys_tr_msg.c
*
*/

PRIVATE S16 ysTrFillDciFormat2a
(
 TfuPdcchInfo       *pdcch,
 FAPI_dciFormat2A_st  *dciFormat2a
)
{
   TfuDciInfo dciInfo          = pdcch->dci;
   TfuDciFormat2AInfo format2a = dciInfo.u.format2AInfo;
   YsCellCb *cellCb;                    
    
   cellCb = ysUtlGetCellCfg(ysCb.cellId); 
  
   switch (pdcch->aggrLvl)
   {
   case CM_LTE_AGGR_LVL1:
      dciFormat2a->aggregationLevel = 1;
      break;
   case CM_LTE_AGGR_LVL2:
      dciFormat2a->aggregationLevel = 2;
      break;
   case CM_LTE_AGGR_LVL4:
      dciFormat2a->aggregationLevel = 4;
      break;
   case CM_LTE_AGGR_LVL8:
      dciFormat2a->aggregationLevel = 8;
      break;
   }

   dciFormat2a->resAllocationType = format2a.allocInfo.isAllocType0 ? 0 : 1; /* For DCI Format 2A it should Be explicitly signalled 
                                                                               whether it is Type 0 or Type 1 */

   dciFormat2a->mcs_1 = format2a.allocInfo.tbInfo[0].mcs;  /* Range 0-31 */ 
   dciFormat2a->redundancyVersion_1 = format2a.allocInfo.tbInfo[0].rv; /*Range 0- 3 */
   dciFormat2a->newDataIndicator_1 =  format2a.allocInfo.tbInfo[0].ndi;

   /*Need to fill with the right bit mask for Rb allocation  */
   cmMemcpy((U8 *)&dciFormat2a->rbCoding, format2a.allocInfo.resAllocMap,4 );

   /*Right shifted to match the Lower ends of the byte  */
   /* Fix for 20Mhz RB coding*/
   if(cellCb->dlBw == CTF_BW_RB_100)
   {
      dciFormat2a->rbCoding = (dciFormat2a->rbCoding & 0xFFFFFF80) >> 7;
   }
   else
   {
      dciFormat2a->rbCoding = (dciFormat2a->rbCoding & 0xFFFF8000) >> 15;
   }


   dciFormat2a->tbToCodeWordSwapFlag = format2a.allocInfo.transSwap ? 1 : 0; /* 0-> No swapping 1 Swapping */ 
   dciFormat2a->mcs_2 = format2a.allocInfo.tbInfo[1].mcs;/* Range 0-31 */ 
   dciFormat2a->redundancyVersion_2 = format2a.allocInfo.tbInfo[1].rv;/*Range 0- 3 */

   dciFormat2a->newDataIndicator_2 = format2a.allocInfo.tbInfo[1].ndi;

   /*Need to fill with the right bit mask for Rb allocation  */
   dciFormat2a->harqProcessNum = format2a.allocInfo.harqProcId; /* Range 0-8 */
   /*Check for the values : 0-7 (2 ant) 0-63 (4 ant) */
#if LTE_TDD
    dciFormat2a->dlAssignmentIndex = format2a.dai;
#else
    dciFormat2a->dlAssignmentIndex = 0;
#endif

   dciFormat2a->preCodingInfo = 1 ; /* Not valid for dci 2a in case of 2 ant ports.*/
   dciFormat2a->tpc = format2a.tpcCmd;
   dciFormat2a->txPower = YS_TR_TXPOWER_SET; 
   YS_TR_GET_RNTI_TYPE( pdcch->rnti,dciFormat2a->rntiType );
   RETVALUE (ROK);
}
#endif
/*
*
*       Fun:   ysTrFillDlDciInfo
*
*       Desc: Fills DCI info 
*
*       Ret: ROK/ RFAILED
*
*       Notes: None
*
*       File: ys_tr_msg.c
*
*/
PRIVATE S16 ysTrFillDlDciInfo
(
TfuPdcchInfo           *pdcch,
srslte_ra_dl_dci_t     *dlpdu
)
{
   S16        ret = ROK;
   TRC2(ysTrFillDlDciInfo);
   
   switch(pdcch->dci.dciFormat)
   {
       case TFU_DCI_FORMAT_1:
       {
#if 0
           ysTrFillDciFormat1(pdcch , dlpdu);
#endif
       }
       break;
       case TFU_DCI_FORMAT_1A:
       {
           ysTrFillDciFormat1A(pdcch, dlpdu);
       break;
       }
       case TFU_DCI_FORMAT_1B:
       {
#if 0
           ysTrFillDciFormat1B(pdcch, dlpdu);
#endif
           break;
       }
       case TFU_DCI_FORMAT_1C:
       {
           SS_DEBUGP("\nFormat 1C Not supported.");
           break;
       }
       case TFU_DCI_FORMAT_1D:
       {
#if 0
           ysTrFillDciFormat1D(pdcch, dlpdu);
#endif
           break;
       }
       case TFU_DCI_FORMAT_2:
       {
#if 0
           ysTrFillDciFormat2(pdcch , dlpdu);
#endif
       break;
       }

       case TFU_DCI_FORMAT_2A:
       {
#if 0
          ysTrFillDciFormat2a(pdcch , dlpdu);
#endif
       break;
       }
       default: 
       {
          break;
       }
   }/* End of switch */
   RETVALUE (ret);
}/* End of ysTrFillDlDciInfo() */

/*
*
*       Fun:   ysTrFillDlConfigPdu
*
*       Desc:  This function will be used to fill the DL Configuration values 
*
*       Ret:  ROK/RFAILED 
*
*       Notes: None
*
*       File:  ys_tr_msg.c
*
*/
PRIVATE S16 ysTrFillDlConfigPdu 
(
srslte_enb_dl_t             *q,
U32                          tti,
TfuPdcchInfo               *pdcch,   
TfuDatReqPduInfo           *data,
U8                         pduIndex,
U8                         tbIndex
)
{
	U8 size = 0;
	S16 ret = ROK;
	srslte_dci_format_t format;
	srslte_dci_location_t location;
	srslte_ra_dl_dci_t dl_dci;
	srslte_ra_dl_grant_t grant;
	if(pdcch && (!YS_TR_IS_UL_DCI(pdcch->dci.dciFormat)))
	{
		switch(pdcch->dci.dciFormat) {
			case TFU_DCI_FORMAT_1:
				{
					format = SRSLTE_DCI_FORMAT1;
				}
				break;
			case TFU_DCI_FORMAT_1A:
				{
					format = SRSLTE_DCI_FORMAT1A;
					ysTrFillDlDciInfo(pdcch, &dl_dci);
					break;
				}
			case TFU_DCI_FORMAT_1B:
				{
					format = SRSLTE_DCI_FORMAT1B;
					break;
				}
			case TFU_DCI_FORMAT_1C:
				{
					format = SRSLTE_DCI_FORMAT1C;
					SS_DEBUGP("\nFormat 1C Not supported.");
					break;
				}
			case TFU_DCI_FORMAT_1D:
				{
					format = SRSLTE_DCI_FORMAT1D;
					break;
				}
			case TFU_DCI_FORMAT_2:
				{
					format = SRSLTE_DCI_FORMAT2;
					break;
				}

			case TFU_DCI_FORMAT_2A:
				{
					format = SRSLTE_DCI_FORMAT2A;
					break;
				}
		}

		location.L = pdcch->aggrLvl;
		location.ncce = pdcch->nCce;
		/* fill sfidx */
		if(pdcch->rnti == 65535 ) {
			SS_DEBUGP("AR: putting PDCCH L(%d) ncce(%d)\n", location.L, location.ncce);
			srslte_enb_dl_put_pdcch_dl(q, &dl_dci, format,location, 0/*pdcch->rnti*/, tti % 10);
		} else {
			srslte_enb_dl_put_pdcch_dl(q, &dl_dci, format,location, pdcch->rnti, tti % 10);
		}
	}
	if(data)
	{ 
		static Data send_data[1000];

		ret= ysTrFillDlschInfo(q,
				&grant,
				data,
				&size,
				tbIndex); 
		if(RFAILED == ret) {
			return RFAILED;
		}
		SRemPreMsgMult((Data*)send_data, size, data->mBuf[tbIndex]);
		if(data->rnti == 65535 ) {
			srslte_enb_dl_put_pdsch(q, &grant, &softbuffer, 0/*65535*/, data->dciInfo.u.format1aAllocInfo.rv, tti % 10,
					send_data);
		} else {

			srslte_enb_dl_put_pdsch(q, &grant, &softbuffer,
					data->rnti, data->dciInfo.u.format1aAllocInfo.rv, tti % 10,
					send_data);
		}
	}
	RETVALUE(ret);
}

/*
*
*       Fun:   ysTrFillDlCfgReq
*
*       Desc: This function only fills the DCIDL Pdus as the remaining 
*             informations are comes as a part of Dat.Request from MAC 
*             and filled at the handler of same.
*
*       Ret:
*
*       Notes: None
*
*       File: 
*
*/
PRIVATE S16 ysTrFillDlCfgReq
(
TfuCntrlReqInfo    *cntrlReq,
TfuDatReqInfo      *dataReq,
srslte_enb_dl_t    *q,
U32 tti
)
{
   S16            ret           = ROK;
   CmLList        *cmLstEnt;
   TfuPdcchInfo   *pdcchInfo    = NULLP;
  
   TRC2(ysTrFillDlCfgReq);

   cmLstEnt = cntrlReq->dlPdcchLst.first;
int i = 0; 
   while (cmLstEnt != NULLP)
   {
      pdcchInfo = (TfuPdcchInfo *)cmLstEnt->node;

	SS_DEBUGP("L1: control request i (%d) \n", i);
      if(YS_TR_PRNTI == pdcchInfo->rnti)
      {
         cmLstEnt = cmLstEnt->next;
         continue;
      }
      ret = ysTrFillDlConfigPdu(q, tti,
                            pdcchInfo, 
                            NULLP, 
                            0,0); 
      cmLstEnt = cmLstEnt->next;
	i++;
   }

   RETVALUE (ret);
}

PRIVATE S16 ysTrFillMacPduTlv
(
Buffer                *mBuf
)
{
   U16                pduSize;
   MsgLen             length;

   SFndLenMsg(mBuf, &length);
   if(0 == length)
   {
      SS_DEBUGP("Mac Pdu Size is Zero!\n");
   }
   pduSize = length;
/* TODO:
   SRemPreMsgMult((Data*)&macPduTlvPtr->value[0], length, mBuf);
*/

   RETVALUE(ROK);
}
/*
*
*       Fun:   ysTrFillTxRequest
*
*       Desc:  This message is used to fill the Tx Request 
*
*       Ret:   ROK/RFAFILED
*
*       Notes: None
*
*       File:  ys_tr_msg.c
*
*/
PRIVATE S16 ysTrFillTxRequest
(
srslte_enb_dl_t *q,
U32             tti,
TfuDatReqInfo            *datReq
)
{
   CmLList               *cmLstEnt;
   TfuDatReqPduInfo      *datReqPduInfo = NULLP;
   U16                   pduIndex = 0;
   MsgLen                length;
   U8                    idx;
   U8                    size;

   TRC2(ysTrFillTxReq)

   cmLstEnt = datReq->pdus.first;
	int i = 0;
   while (NULLP != cmLstEnt)
   {
      datReqPduInfo = (TfuDatReqPduInfo *)cmLstEnt->node;
     /* Fill Dl config for PCH and DLSCH PDU's */
     /* PCH */
      size = 0;
	SS_DEBUGP("L1: DATA request i(%d) \n", i);
      if(datReqPduInfo->rnti == YS_TR_PRNTI)
      {
	SS_DEBUGP("Sorry no Paging \n");
      }
      else
      {
         for (idx = 0; idx < datReqPduInfo->nmbOfTBs; idx++)
         {
            if (datReqPduInfo->mBuf[idx]== NULLP)
            {
               continue;
            }

            /* Fill DLSCH PDU's related to Tx Request */ 
            ysTrFillDlConfigPdu(q, tti,
                       NULLP,
                       datReqPduInfo,
                       pduIndex,
                       idx);

            pduIndex++;
         }
      }
      cmLstEnt = cmLstEnt->next;
   }
 
   RETVALUE(ROK);
}
#if 0
/*
*  
*       Fun:   ysTrFillUlDci3Pdu
*
*       Desc:  This function will be used to fill the UL DCi PDU
*
*       Ret:  ROK/RFAILED
*  
*       Notes: None
*   
*       File:  ys_tr_msg.c
*
*/
PRIVATE S16 ysTrFillUlDci3Pdu
(
srslte_enb_dl_t *q,
U32 tti,
TfuPdcchInfo* pdcch,
srslte_ra_ul_dci_t *ulDciPdu
)
{  
   /* This format is not tested */
     U8                   idxx;
 
    ulDciPdu->format = DCI_FORMAT_3;
    ulDciPdu->cceIndex = pdcch->nCce;
    ulDciPdu->rnti = pdcch->rnti;


switch (pdcch->aggrLvl)
   {
   case CM_LTE_AGGR_LVL1:
      ulDciPdu->aggLevel = 1;
      break;
   case CM_LTE_AGGR_LVL2:
      ulDciPdu->aggLevel = 2;
      break;
   case CM_LTE_AGGR_LVL4:
      ulDciPdu->aggLevel = 4;
      break;
   case CM_LTE_AGGR_LVL8:
      ulDciPdu->aggLevel = 8;
      break;
   }
    
    ulDciPdu->tpcBitMap = 0;
    
   for(idxx=0;idxx<16;idxx++)
   {
     /* TODO: The TPC commands and filled from msb to lsb.Need to confirm with TR if this true */   
     ulDciPdu->tpcBitMap |= ((pdcch->dci.u.format3Info.tpcCmd[idxx] & 0x3) << (30-2*idxx));
   }

     ulDciPdu->ulDCIPDUSize = sizeof(FAPI_dlDCIPduInfo_st);
     *size = ulDciPdu->ulDCIPDUSize;
     RETVALUE(ROK);
}

/*
*
*       Fun:   ysTrFillUlDci3APdu
*
*       Desc:  This function will be used to fill the UL DCi PDU
*
*       Ret:  ROK/RFAILED 
*
*       Notes: None
*
*       File:  ys_tr_msg.c
*
*/
PRIVATE S16 ysTrFillUlDci3APdu
(
srslte_enb_dl_t *q,
U32 tti,
TfuPdcchInfo* pdcch,
srslte_ra_ul_dci_t *msg
)
{
   /* This format is not tested */
    U8                   idxx;

    FAPI_dlDCIPduInfo_st * ulDciPdu = (*configPdu);
    ulDciPdu->pduType =  YS_TR_DCI_UL_PDU;
    ulDciPdu->ulDCIFormat = DCI_FORMAT_3A;
    ulDciPdu->cceIndex = pdcch->nCce;
    ulDciPdu->rnti = pdcch->rnti;

   switch (pdcch->aggrLvl)
   {
   case CM_LTE_AGGR_LVL1:
      ulDciPdu->aggLevel = 1;
      break;
   case CM_LTE_AGGR_LVL2:
      ulDciPdu->aggLevel = 2;
      break;
   case CM_LTE_AGGR_LVL4:
      ulDciPdu->aggLevel = 4;
      break;
   case CM_LTE_AGGR_LVL8:
      ulDciPdu->aggLevel = 8;
      break;
   }


    ulDciPdu->tpcBitMap = 0;
    for(idxx =0;idxx<32;idxx++)
    {
        /* TODO: The TPC commands and filled from msb to lsb.Need to confirm with TR if this true */
        ulDciPdu->tpcBitMap |=((pdcch->dci.u.format3AInfo.tpcCmd[idxx] &0x1) << (31-idxx));
    }
    
    ulDciPdu->ulDCIPDUSize = sizeof(FAPI_dlDCIPduInfo_st);
    *size = ulDciPdu->ulDCIPDUSize;
    RETVALUE(ROK);
}
#endif
/*
*
*       Fun:   ysTrFillUlDciPdu
*
*       Desc:  This function will be used to fill the UL DCi PDU
*
*       Ret:  ROK/RFAILED 
*
*       Notes: None
*
*       File:  ys_tr_msg.c
*
*/
PRIVATE S16 ysTrFillUlDciPdu 
(
srslte_enb_dl_t *q,
U32 tti,
TfuPdcchInfo             *pdcch,   
 srslte_ra_ul_dci_t *ulDciPdu
)
{
   switch (pdcch->aggrLvl)
   {
   case CM_LTE_AGGR_LVL1:
	ulDciPdu->type2_alloc.L_crb = 1;
      break;
   case CM_LTE_AGGR_LVL2:
	ulDciPdu->type2_alloc.L_crb = 2;
      break;
   case CM_LTE_AGGR_LVL4:
	ulDciPdu->type2_alloc.L_crb = 4;
      break;
   case CM_LTE_AGGR_LVL8:
	ulDciPdu->type2_alloc.L_crb = 8;
      break;
   }
   ulDciPdu->type2_alloc.RB_start = pdcch->dci.u.format0Info.rbStart;
   ulDciPdu->type2_alloc.mode = SRSLTE_RA_TYPE2_LOC;
   /* TODO: ??? */
   ulDciPdu->type2_alloc.riv = pdcch->nCce;
   ulDciPdu->mcs_idx = pdcch->dci.u.format0Info.mcs;
   ulDciPdu->n_dmrs = pdcch->dci.u.format0Info.nDmrs;
   ulDciPdu->ndi = pdcch->dci.u.format0Info.ndi;
   ulDciPdu->cqi_request = pdcch->dci.u.format0Info.cqiReq;
   /* TODO: ??? */
   ulDciPdu->freq_hop_fl = pdcch->dci.u.format0Info.hoppingEnbld;
   ulDciPdu->tpc_pusch = pdcch->dci.u.format0Info.tpcCmd;

   RETVALUE(ROK);
}

/*
*
*       Fun:   ysTrFillHiDci0Req
*
*       Desc:
*
*       Ret:
*
*       Notes: None
*
*       File: 
*
*/
PRIVATE S16 ysTrFillHiDci0Req
(
TfuCntrlReqInfo          *cntrlReq,
srslte_enb_dl_t *q,
U32 tti
)
{
   CmLList               *cmLstEnt   = NULLP;
   U8                    cntr        = 0;
   TfuPdcchInfo          *pdcchInfo  = NULLP;
   TfuPhichInfo          *phichInfo  = NULLP;
   U8                    size        = 0;
   YsUeCb                *ueCb;
   YsCellCb  *cellCb = &ysCb.cellCb;

   srslte_ra_ul_dci_t msg;
   srslte_dci_msg_t dci_msg;
   srslte_dci_location_t location;
   TRC2(ysTrFillHiDci0Req);

   cmLstEnt = cntrlReq->ulPdcchLst.first;    
   while (NULLP != cmLstEnt)
   {
      pdcchInfo = (TfuPdcchInfo *)cmLstEnt->node;
      if(YS_TR_IS_UL_DCI(pdcchInfo->dci.dciFormat))
      {
         ueCb = ysUtlGetUe(cellCb, pdcchInfo->rnti);
         if(ueCb == NULLP)
         {
            cmLstEnt = cmLstEnt->next;
            continue;
         }

         switch((pdcchInfo->dci.dciFormat))
         {
            case TFU_DCI_FORMAT_0:
            {
               if(ysTrFillUlDciPdu(q, tti,
                                pdcchInfo, &msg) != ROK )
               {
                  SS_DEBUGP("fail to fill UL DCI\n");
                  RETVALUE(RFAILED);
               }
		location.L = msg.type2_alloc.L_crb;
		location.ncce =  pdcchInfo->nCce;
	       srslte_dci_msg_pack_pusch(&msg, &dci_msg, pdcchInfo->dci.u.format0Info.numRb);
		srslte_enb_dl_put_pdcch_ul(q, &msg, location, /*pdcchInfo->rnti*/ 0, tti % 10);
               break;
            }
#if 0
            case TFU_DCI_FORMAT_3:
            {
               if(ysTrFillUlDci3Pdu(q, tti,
                               pdcchInfo, &msg) != ROK )
               {
                  SS_DEBUGP("fail to fill UL DCI\n");
                  RETVALUE(RFAILED);
               }
               break;
            }
            case  TFU_DCI_FORMAT_3A:
            {
               if(ysTrFillUlDci3APdu(q,
 			      tti,
                              pdcchInfo, &msg) != ROK )
               {
                  SS_DEBUGP("fail to fill UL DCI\n");
                  RETVALUE(RFAILED);
               }
               break;
            }
#endif
            default:
                SS_DEBUGP("\n Invalid DCI format in UL\n");
            break;
         }
       }
       /* Move to next entry */
       cmLstEnt = cmLstEnt->next;
   }

   cmLstEnt = cntrlReq->phichLst.first; 
   while (cmLstEnt != NULLP)
   {
       phichInfo = (TfuPhichInfo *)cmLstEnt->node;

       srslte_enb_dl_put_phich(q, phichInfo->isAck,phichInfo->rbStart, phichInfo->nDmrs, tti % 10);
       
       /* Move to next entry */
       cmLstEnt = cmLstEnt->next;
   }/* End of while() */   
   
   RETVALUE(ROK);
}

/*
*
*       Fun:   ysTrFillEncSndReqMsgs
*
*       Desc:  This function will be used to fill the 
*              Request Messages like DCI0Req, ReceptionReq, CntrlReq
*              That is generated by LTEMAC.After extracting the information in these
*              messages the same will be transferred to PHY. 
*
*       Ret:  ROK/RFAILED 
*
*       Notes: None
*
*       File:  ys_tr_msg.c
*
*/
PUBLIC S16 ysFillEncMsgs 
(
 srslte_enb_dl_t *q,
 U32 tti
)
{

   U8 cntrlReqSf = tti % 10;
   U8 datReqSf   = tti % 10;
   U8 recpReqSf  = tti % 10;
   YsCellCb  *cellCb = &ysCb.cellCb;
   TfuCntrlReqInfo  *cntrlReq = cellCb->txMsgInfo[cntrlReqSf].cntrlReq;
   TfuCntrlReqInfo  *hiDciCntrlReq = cellCb->txMsgInfo[cntrlReqSf].hiDciReq;
   TfuRecpReqInfo   *recpReq  = cellCb->txMsgInfo[recpReqSf].recpReq;
   TfuDatReqInfo    *datReq   = cellCb->txMsgInfo[datReqSf].datReq;

   /* As per section 2.2.3 
    * the order of the message is 
    *  1. DLConfig
    *  2. UL Config
    *  3. Tx.Request
    *  4. HI_DCI0*/
   if (cntrlReq) 
   {
	SS_DEBUGP("L1: control request is present \n");
      if (ROK != ysTrFillDlCfgReq(
                          cntrlReq,
                          datReq, 
                         q,
			 tti 
                          ))
      {   
         RETVALUE(RFAILED);
      }
      YS_FREE_SDU(cntrlReq);
      cellCb->txMsgInfo[cntrlReqSf].cntrlReq = NULLP;
   }

#if 0
   if (recpReq)
   {
      ulConfigMsg = cellCb->ulConfigMsg;
      /* TelRad Specific Changes - Start*/
      cmMemset((U8 *)ulConfigMsg, 0, YS_UL_CONFIG_MAX_SIZE);
      /* TelRad Specific Changes - End*/

      ulConfigMsg->msgId = PHY_UL_CONFIG_REQUEST;
      ulConfigMsg->lenVendorSpecific = 0;

      ulConfigReq = (FAPI_ulConfigRequest_st *)&ulConfigMsg->msgBody[0];
      if(ROK != ysTrFillUlCfgReq(cellCb,  
                             ulConfigReq, 
                             recpReq,
                             &ulConfigMsg->msgLen,
                             &ulConfigMsg->lenVendorSpecific))
      {   
         YS_DBG_ERR((_ysp, "ysTrEncAndSend2Phy(): failed\n"));
         RETVALUE(RFAILED);
      }
   }
#endif

   if (hiDciCntrlReq) /* rohit : kw_warning_fixes */
   {
      if ((0 != hiDciCntrlReq->ulPdcchLst.count) || (0 != hiDciCntrlReq->phichLst.count))
      {
      
         if (ROK != ysTrFillHiDci0Req(
                                 hiDciCntrlReq, 
                                 q, tti))
         {
            SS_DEBUGP("HI framing failed\n") ;
            YS_DBG_ERR((_ysp, "ysTrEncAndSend2Phy(): failed\n"));
            RETVALUE(RFAILED);
         } 
      }
	YS_FREE_SDU(hiDciCntrlReq);
	cellCb->txMsgInfo[cntrlReqSf].hiDciReq = NULLP;
   }

   if (datReq)
   {
	SS_DEBUGP("L1: DATA request is present \n");
      if (ROK != ysTrFillTxRequest(q, tti,
                           datReq))
      {
         RETVALUE(RFAILED);
      }
      ysUtlFreeDatReq(datReq);
      cellCb->txMsgInfo[datReqSf].datReq = NULLP;
   }

   RETVALUE (ROK);
}

void start_dl(){
/* create 2 threads for DL and UL */
	pthread_t      tskId_smmApp;
	pthread_attr_t attr;
	/* mt021.201 - Addition to set stack size */
	pthread_attr_setstacksize(&attr, (size_t)MT_TASK_STACK);
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
	struct sched_param param_sched;
	param_sched.sched_priority = sched_get_priority_max(SCHED_FIFO);
	pthread_attr_setschedparam(&attr, &param_sched);
	/* mt02.301 addition , setting the Real Time Scheduling class */
	if (pthread_create(&tskId_smmApp , NULL, net_thread_fnc, NULL)) {
		perror("pthread_create");
		exit(-1);
	}
#if 0
	if (pthread_create(&tskId_smmApp , NULL, net_thread_fnc_reader, NULL)) {
		perror("pthread_create");
		exit(-1);
	}
#endif
}

void encodeDl()
{
	static U32 tti_rx = 0;
	static U32 cnt_sfn = 0;
	static U32 cnt_sf = 0;
	CmLteTimingInfo  timingInfo;
	TfuTtiIndInfo   ttiInd;
	TfuTtiIndInfo   schTtiInd;

	SS_DEBUGP("L1 SFN(%d) SF(%d)\n", cnt_sfn, cnt_sf );
	timingInfo.sfn = cnt_sfn;
	timingInfo.subframe = cnt_sf;

	srslte_enb_dl_clear_sf(dl_init);

	srslte_enb_dl_put_base(dl_init, tti_rx);

	ysFillEncMsgs(dl_init, tti_rx);

	SS_DEBUGP("Transform OFDM SYMBOLS output_buffer(%p)\n", &output_buffer[sf_n_samples * cnt_sf]);
	srslte_enb_dl_gen_signal(dl_init, &output_buffer[sf_n_samples * cnt_sf]);	
#if 0
	SGetSBuf(ysCb.schTfuSap.sapPst.region, ysCb.schTfuSap.sapPst.pool, 
			(Data **)&schTtiInd, sizeof(TfuTtiIndInfo));

	SGetSBuf(ysCb.tfuSap.sapPst.region, ysCb.tfuSap.sapPst.pool, 
			(Data **)&ttiInd, sizeof(TfuTtiIndInfo));
#endif

	/* fill TTI indication for MAC */
	ysCb.cellCb.timingInfo.subframe =  cnt_sf;
	ysCb.cellCb.timingInfo.sfn =  cnt_sfn;
#if 0
	ttiInd->cellId = ysCb.cellCb.cellId;
	ttiInd->timingInfo = timingInfo;
	ttiInd->isDummyTti = FALSE;
#else
        ttiInd.numCells = 1;
        ttiInd.cells[0].cellId = ysCb.cellCb.cellId;
        ttiInd.cells[0].timingInfo = timingInfo;
        ttiInd.cells[0].isDummyTti = 0;   
        ttiInd.cells[0].schTickDelta = 0; 
        ttiInd.cells[0].dlBlankSf = 0;    
        ttiInd.cells[0].ulBlankSf = 0; 
#endif
        //printf("SFN:SF [%d :%d]\n", cnt_sfn, cnt_sf);
	/* fill TTI indication for scheduler */
	schTtiInd = ttiInd;

	/* Give TTI indication to scheduler */
	YsUiTfuSchTtiInd(&ysCb.schTfuSap.sapPst, ysCb.schTfuSap.suId, &schTtiInd);

	/* Give TTI indication to MAC */
	YsUiTfuTtiInd(&ysCb.tfuSap.sapPst, ysCb.tfuSap.suId, &ttiInd);
	tti_rx++;
        cnt_sf++;
        if((cnt_sf % 10) == 0)
        {
           cnt_sf = 0;
           if(cnt_sfn == 1023)
           {
              cnt_sfn = 0;
           }
           else
	   {
	      cnt_sfn++;
	   }
        }
}


void myttiHandler()
{
	static U32 g_dltti = 0;
	SS_DEBUGP("LRF SFN(%d) SF(%d)\n", g_dltti / 10, g_dltti % 10 );

	srslte_rf_send2(rf, &output_buffer[sf_n_samples * (g_dltti % 10)], sf_n_samples, true, start_of_burst, false);

	ysPalPkTful1EncodeReq(&ysCb.cellCb.peerPst, ysCb.schTfuSap.spId, g_dltti);

	start_of_burst=false; 

	g_dltti++;
}

int main7(CtfCellCfgInfo*       cellCfg) {
	srslte_cell_t cell;
   srslte_pusch_hopping_cfg_t hopping_cfg;
	/* TODO: Generic cell configuration validate the ranges from APP to L1 */
	if(CTF_BW_RB_25 == cellCfg->bwCfg.dlBw)
	{
		cell.nof_prb = 25;   // nof_prb
	}
	else if(CTF_BW_RB_50 == cellCfg->bwCfg.dlBw) 
	{
		cell.nof_prb = 50;
	}
	else {
		cell.nof_prb = 100;
	}

	if(CTF_AP_CNT_1 == cellCfg->antennaCfg.antPortsCnt) {
		cell.nof_ports = 1;            // nof_ports
	} else if (CTF_AP_CNT_2 == cellCfg->antennaCfg.antPortsCnt) {
		cell.nof_ports = 2;            // nof_ports
	} else {
		cell.nof_ports = 1;            // nof_ports
	}
		
        cell.nof_ports = 1;            // nof_ports

	cell.bw_idx = 0;            // bw idx 
	cell.id =  cellCfg->cellId;  // cell_id 
	if (cellCfg->txCfg.cycPfx == CTF_CP_NORMAL) {
		cell.cp =  SRSLTE_CP_NORM;       // cyclic prefix
	} else if(cellCfg->txCfg.cycPfx == CTF_CP_EXTENDED) {
		cell.cp = SRSLTE_CP_EXT;       // cyclic prefix
	} else {
		cell.cp =  SRSLTE_CP_NORM;       // cyclic prefix
	}

	// PHICH length
	if ( cellCfg->phichCfg.duration == CTF_PHICH_DUR_NORMAL) {
		cell.phich_length = SRSLTE_PHICH_NORM;           
	} else if(cellCfg->phichCfg.duration ==  CTF_PHICH_DUR_EXTENDED) {
		cell.phich_length = SRSLTE_PHICH_EXT;           
	} else {
		cell.phich_length = SRSLTE_PHICH_NORM;       
	}

	// PHICH resources 
	if( cellCfg->phichCfg.resource == CTF_PHICH_RSRC_ONESIXTH) {
		cell.phich_resources = SRSLTE_PHICH_R_1_6;    // PHICH resources 
	} else if (cellCfg->phichCfg.resource == CTF_PHICH_RSRC_HALF) {
		cell.phich_resources = SRSLTE_PHICH_R_1_2;    
	} else if (cellCfg->phichCfg.resource == CTF_PHICH_RSRC_ONE) {
		cell.phich_resources = SRSLTE_PHICH_R_1;    
	} else if (cellCfg->phichCfg.resource == CTF_PHICH_RSRC_TWO) {
		cell.phich_resources = SRSLTE_PHICH_R_2;    
	} else {
		cell.phich_resources = SRSLTE_PHICH_R_1;    
	}
	/* TODO: Prach configuration validate the ranges from APP to L1 */
	prach_cfg.config_idx = cellCfg->prachCfg.prachCfgIndex;
	prach_cfg.root_seq_idx = cellCfg->prachCfg.rootSequenceIndex;
	prach_cfg.zero_corr_zone = cellCfg->prachCfg.zeroCorrelationZoneCfg;
	prach_cfg.hs_flag = cellCfg->prachCfg.highSpeedFlag;
	p_rachfreq_offset = cellCfg->prachCfg.prachFreqOffset;	
#if 0
	/* TODO: pucch_cfg configuration validate the ranges from APP to L1 */ 
	pucch_cfg.delta_pucch_shift = cellCfg->pucchCfg.deltaShift; 
	pucch_cfg.n_rb_2 =  cellCfg->pucchCfg.nRB;
	pucch_cfg.N_cs = cellCfg->pucchCfg.nCS; 

	/* TODO: Not filling it currently */
	pucch_cfg.srs_configured = false; // ?????
	pucch_cfg.srs_cs_subf_cfg = 0; // ????
	pucch_cfg.srs_simul_ack = 0; // ?????
#endif
	/*TODO: Not filling pusch configuration also */ 

	sf_n_re = 2 * SRSLTE_CP_NORM_NSYMB * cell.nof_prb * SRSLTE_NRE;
	sf_n_samples = 2 * SRSLTE_SLOT_LEN(srslte_symbol_sz(cell.nof_prb));

	base_init();

	srslte_enb_dl_init(dl_init, cell, 2);

	srslte_enb_dl_set_cfi(dl_init, 3);

	 if (srslte_softbuffer_tx_init(&softbuffer, dl_init->cell.nof_prb)) {
                SS_DEBUGP("Error initiating soft buffer\n");
                exit(-1);
        }

	srslte_softbuffer_tx_reset(&softbuffer);

	srslte_enb_ul_init(ul_init, cell, &prach_cfg, &pusch_cfg, &hopping_cfg, &pucch_cfg, 2);
	//srslte_enb_ul_init(ul_init, cell, &prach_cfg, &pusch_cfg,  &pucch_cfg, 2);
	srslte_enb_rf_init(dl_init);

		return(1);
}

void net_thread_fnc(void *args)
{
    extern U8 isStartDl;
        while(isStartDl == 0)
          usleep(500);
	while(!go_exit)
	{
		myttiHandler();
	}
	return(1);
}

void net_thread_fnc_reader(void *args)
{
	srslte_timestamp_t tstamp;
	Buffer *mBuf;
	static U32 g_ultti = 0;
	while(!go_exit)
	{
		srslte_rf_recv_with_time(rf, &input_buffer[sf_n_samples* (g_ultti % 10)], sf_n_samples, true,
				&tstamp.full_secs, &tstamp.frac_secs);

		ysPalPkTful1ReadReq(&ysCb.cellCb.peerPst, ysCb.schTfuSap.spId, g_ultti);

		g_ultti++;
	}
}

