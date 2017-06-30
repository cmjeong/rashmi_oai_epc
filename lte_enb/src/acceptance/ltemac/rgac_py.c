


/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for the functions needed by CM XTA to execute 
               layer specific code. 
  
     File:     rgac_py.c 
  
     Sid:      rgac_py.c@@/main/2 - Sat Jul 30 02:21:00 2011
  
     Prg:     sm 
  
**********************************************************************/

/** @file rgac_py.c.
@brief It has The functions that are neede by CM XTA to execute any layer 
specific python code, during intialization and shutdown.
*/


#include "rgac_acc.x"
#include "cm_xta_py.x"

 /** @brief This function is called by CM XTA to intialize the python module, if
  * the layer wishes to have any special handling/parsing the code can be put
  * here.
  *
  * @details
  *
  *     Function: cmXtaAppPyInit
  *
  *         Processing steps:
  *         - 
  *
  * @return CMXTA_ERR_NONE
  */
#ifdef ANSI
PUBLIC S16 cmXtaAppPyInit
(
 Void
 )
#else
PUBLIC S16 cmXtaAppPyInit ()
#endif
{
   PyObject *pName;
   PyObject *pModule;
   PyObject *pDict;

   TRC2(cmXtaAppPyInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppPyInit(): Initializing python interpreter\n"));
   pName = NULLP;
   pModule = NULLP;
   pDict = NULLP;
   /*-- Load module --*/
   pModule = PyImport_ImportModule("cm_xta_py");
   if (pModule == NULLP)
   {
      if (PyErr_Occurred() != NULLP)
         PyErr_Print();

      CMXTA_DBG_ERR((_cmxtap, "cmXtaAppPyInit(): init failed\n"));
      /*-- Shutdown python interpreter --*/
      cmXtaPyDeInit();
      RETVALUE(CMXTA_ERR_INT);
   }
   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaAppPyInit */ 

 /** @brief This function is called by CM XTA to deinit any layer specific
  * python handling
  *
  * @details
  *
  *     Function: cmXtaPyDeInit
  *
  *         Processing steps:
  *         - 
  * @return CMXTA_ERR_NONE
  */
#ifdef ANSI
PUBLIC S16 cmXtaAppPyDeInit
(
Void
)
#else
PUBLIC S16 cmXtaAppPyDeInit ()
#endif
{
   TRC2(cmXtaAppPyDeInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaAppPyDeInit(): Shutting down python interpreter\n"));

   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaAppPyDeInit */


/**********************************************************************
 
         End of file:     rgac_py.c@@/main/2 - Sat Jul 30 02:21:00 2011
 
**********************************************************************/
 
/**********************************************************************
 
        Notes:
 
**********************************************************************/
 
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     sm   1. Initial Release.
/main/2      ---     dvasisht          1. Updated for LTE MAC Release 3.1          
$SID$        ---       rt   1. LTE MAC 4.1 release
*********************************************************************91*/

