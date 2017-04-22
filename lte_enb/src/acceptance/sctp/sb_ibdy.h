

/********************************************************************20**
  
     Name:     configurator
  
     Type:     C header file
  
     Desc:     Defines required by configurator
  
     File:     cf.h
  
     Sid:      sb_ibdy.h@@/main/2 - Thu Jul 26 07:54:16 2007
  
     Prg:      ak
  
*********************************************************************21*/

#ifndef __SCTPINOPH__
#define __SCTPINOPH__

#define MAXCMDLEN      50
#define MAXARGS        20
#define MAXBLOCKS      10

#define ASSOCREQ 1
#define ENDPREQ  2
#define DATAREQ  3
#define ASSOC_SERVER 1
#define ASSOC_CLIENT 2


#define MAXARGS 20
#define LINELEN 91
#define CF_LAYER_ID 0

/* high level states */
#define CF_INIT  0
#define CF_STACK 1
#define CF_LAYER 2
#define CF_CNFG  3
#define CF_NOP   4

/* crnt layer states */
#define CF_OPEN   1
#define CF_CLOSED 2

#define MAGIC_ID 1
#define STK_ID 2
#define BEG_LAY_ID 3
#define BEG_CFG_ID 4
#define END_CFG_ID 5
#define END_LAY_ID 6
#define RECFG_ID 7

/* proc id's */
#define PROC_STK 1
#define PROC_VCM 2
#define PROC_IPM 3
#define PROC_APP 4
#define PROC_860 5

#define MATCH_FAILED -1
#define MAX_BRDS 64

#define MAX_U8  0xff
#define MAX_U16 0xffff
#define MAX_U32 0xffffffff

#define CF_RY_HST  0
#define CF_RY_IMP  1
#define CF_RY_BIT3 0

/* Addition for Version 2 configurator */
#define CF_RY_UDPSOCK  0

#define CURRENT_TRANS_ID   1
#define CFM_WAIT_TMR       100
#define MAX_RETRIES        5
#define TRANS_ID_WINDOW_SZ 0xF000

#define INVALID_CMD 0
#define CFG_CMD     1
#define CTL_CMD     2
#define STA_CMD     3
#define STS_CMD     4

#define IGN 1
#define INV -1

/* For demultiplexing purpose */
#define ENTSNPSF  255  /* MTP3 PSF function */
#define ENTSPPSF  254  /* SCCP PSF function */

/* data types for bake_off */
#define PING_REQ        1
#define PING_CFM        2
#define NORMAL_DATA        3
#define PKTCNT_DATA        4

/* for file transfer */
#define FILE_START        1
#define FILE_DATA        2

#endif /* __SCTPINOPH__ */


/********************************************************************30**

         End of file:     sb_ibdy.h@@/main/2 - Thu Jul 26 07:54:16 2007

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
/main/1      ---      sb    1. File Added for inter-op SCTP Testing 
/main/2      ---   rsr/ag   1. Updated for Release of 1.3  
*********************************************************************91*/


