
/********************************************************************20**

     Name:     eGTP Layer

     Type:     C source file

     Desc:     C Upper Interface structures

     File:     smeg_apputl.x

     Sid:      smeg_apputl.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:19:06 2015

     Prg:      ad

*********************************************************************21*/


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


PUBLIC Void egMakeIeEntry ARGS
((
LegIeEntry      *ieEntry,
U8             ieCode,
Bool           valid,
U8             dataType,
Ptr            fncPtr,
U16             minLen,
U16             maxLen
));

PUBLIC Void egMakeAppChildIeEntry ARGS
((
LegGroupedIe *grpIe,
U8             count,
U8            ieCode,
U8            ieClass,
U8            ieCr,
U8            ieInst,
U8             nmbGrpIe
));

PUBLIC Void egMakeAppIeProp ARGS
((
LegIeProperties *ieProp,     /* Ie Property to be filled */
U8             ieCode,      /* Ie Code */
U8             ieClass,     /* Mandatory/Conditional/Optional */
U8             instance,     /* Instance  */
U8                  cr
));


#ifdef __cplusplus
}
#endif /* __cplusplus */

/**********************************************************************
 
         End of file:     smeg_apputl.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:19:06 2015
 
**********************************************************************/

/********************************************************************40**
 
        Notes:
 
*********************************************************************41*/
 
/********************************************************************50**
 
*********************************************************************51*/
 
/********************************************************************60**
 
        Revision history:
 
*********************************************************************61*/

/********************************************************************80**
 
*********************************************************************81*/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      sn   Initial Release
/main/2      ---      rkumar   1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla         Initial for eGTP release 2.1
*********************************************************************91*/
