

/**********************************************************************
     Name:    MAC to MAC interface (PRG)

     Type:    C header file

     Desc:    Constants needed for PRG(MAC to MAC) interface

     File:    rg_prg.h

     Sid:      rg_prg.h

     Prg:      

*********************************************************************21*/

#ifndef __RGPRG_H__ 
#define __RGPRG_H__

#ifdef LTE_ADV

#define RG_PRG_MAX                     1             /* MAC interface support only LC and TC*/
#define PRG_DIR_TX                     CRG_DIR_TX    /*!< Macreo for Transmit 
                                                      *   direction Mask */
#define PRG_DIR_RX                     CRG_DIR_RX    /*!< Macro For Receive
                                                      *   direction Mask */
#define PRG_DIR_TX_RX                  CRG_DIR_TX_RX /*!< Macro for Transmitt and Receive
                                                      *   direction Mask */
/* Event corresponding to each primitive at this interface. PRG interface
 *events values starts from 50 onwards and 1 to 49 reserved for SCH interface*/
#define EVTPRGUESCELLCFGREQ           50  /* Add Ue SCell Config Req from PMAC
                                            to SMAC*/
#define EVTPRGUESCELLCFGCFM           51  /* Config confirm for Add Ue Scell on PRG
                                            interface from SMAC to PMAC*/
#define EVTPRGUESCELLDELREQ           52  /* Ue SCell delete Req from PMAC to
                                            SMAC*/
#define EVTPRGUESCELLLCHMODREQ        53    /*  SCell Lch recfg Req from PMAC to
                                            SMAC*/

#define EVTPRGUESCELLLCHMODCFM        54    /* Lch ReConfig confirm for Scell on PRG
                                            interface from SMAC to PMAC*/

#define EVTPRGUESCELLLCHDELCFM        55    /* Delete Lch  confirm for Scell on PRG
                                            interface from SMAC to PMAC*/

#define EVTPRGUESCELLLCHDELREQ        56    /* Delete Lch request for Scell on PRG
                                            interface from SMAC to PMAC*/

#define EVTPRGUESCELLLCHADDREQ        57    /* Lch config req for Scell on PRG 
                                                  interface from SMAC to PMAC */

#define EVTPRGUESCELLLCHADDCFM        58    /* Lch Config confirm for Scell on PRG
                                            interface from SMAC to PMAC*/
#define PRG_CFG_CFM_OK    CRG_CFG_CFM_OK  /* mapping to CRG NOK macro*/
#define PRG_CFG_CFM_NOK   CRG_CFG_CFM_NOK /* mapping to CRG NOK macro*/

#define RGPRG_FREE_MSG(_buf)\
{\
   if (NULLP != (_buf)) \
   { \
      SPutMsg((_buf)); \
      _buf = NULLP; \
   } \
}

#endif /* LTE_ADV*/
#endif /* __RGPRG_H__ */

/********************************************************************30**

         End of file:     rg_prg.h

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
/main/1      ---      mpatel  1. CA release
*********************************************************************91*/

