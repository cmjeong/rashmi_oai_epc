
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_smm_watchdog_tmr.h

     Sid:      wr_smm_watchdog_tmr.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/Br_Tenb_Mspd_T2K_Intg_MS8.0_RC/1 - Tue Jul 23 17:01:22 2013

     Prg:      Sriky 

*********************************************************************21*/
#ifndef __WR_SMM_WATCHDOG_TMR_H__
#define __WR_SMM_WATCHDOG_TMR_H__

#define WR_WATCHDOG_TMR_PORT   6019 /*watchdog application listening port */
#define WR_SOFT_TIMEOUT_VAL    5    /*time interval for which watchdog application expecting kick */
#define WR_HARD_TIMEOUT_VAL    15  /*maximum time for whitch watchdog application 
                                       can wait for receiving kick without rebbot*/
#define WR_WATCHDOG_TIMER_VAL  5   /*local timer which will monitor lower arm */
/*message types */
#define WR_MSG_TYPE_WATCHDOG_ADD_PID_REQ        0x4701  /*add pid request*/
#define WR_MSG_TYPE_WATCHDOG_REMOVE_PID_REQ     0x4702  /*remove pid request*/
#define WR_MSG_TYPE_WATCHDOG_KICK_REQ           0x4703  /*kick request*/
#define WR_MSG_TYPE_WATCHDOG_KICK_STOP_REQ      0x4704  /*stop request*/

EXTERN Void wrRegWatchDog(Void);
EXTERN Void wrWatchdogSendRemovePid(int dummy);

#endif /* end of __WR_SMM_WATCHDOG_TMR_H__ */
