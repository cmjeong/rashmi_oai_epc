
/************************************************************************
 
     Name:     LTE MAC Convergence Layer
  
     Type:     C source file
  
     Desc:     C source code for tables lookup  
     File:     ys_db.c
  
     Sid:      ys_db_fdd.c@@/main/1 - Thu Dec  2 02:27:13 2010
  
     Prg:      pk
  
**********************************************************************/

/** @file ys_db.c
@brief This module acts as an interface handler for upper interface and 
manages Pst and Sap related information for upper interface APIs.
*/

/* header include files -- defines (.h) */

/* header/extern include files (.x) */
/* header include files (.h) */
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
#include "lys.h"           /* layer management defines for LTE-CL */
#include "tfu.h"
#ifdef YS_MSPD
#else
#include "ys_pal.h"            /* defines and macros for CL */
#endif
#include "ys_pal_err.h"        /* YS error defines */

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
#ifdef YS_MSPD
#else /* YS_PICO */
#include "ys_pal.x"            /* typedefs for CL */

PUBLIC YsPrachTddCfgInfo ysPrachTddCfgDb[YS_NUM_PRACH_TDD_CFG] = 
{
   {
      0,
      YS_PREAM_FRMT_0,
      YS_DRA_0_POINT_5,
      YS_rRA_0
   },
   {
      1,
      YS_PREAM_FRMT_0,
      YS_DRA_0_POINT_5,
      YS_rRA_1
   },
   {
      2,
      YS_PREAM_FRMT_0,
      YS_DRA_0_POINT_5,
      YS_rRA_2
   },
   {
      3,
      YS_PREAM_FRMT_0,
      YS_DRA_1,
      YS_rRA_0
   },
   {
      4,
      YS_PREAM_FRMT_0,
      YS_DRA_1,
      YS_rRA_1
   },
   {
      5,
      YS_PREAM_FRMT_0,
      YS_DRA_1,
      YS_rRA_2
   },
   {
      6,
      YS_PREAM_FRMT_0,
      YS_DRA_2,
      YS_rRA_0
   },
   {
      7,
      YS_PREAM_FRMT_0,
      YS_DRA_2,
      YS_rRA_1
   },
   {
      8,
      YS_PREAM_FRMT_0,
      YS_DRA_2,
      YS_rRA_2
   },
   {
      9,
      YS_PREAM_FRMT_0,
      YS_DRA_3,
      YS_rRA_0
   },
   {
      10,
      YS_PREAM_FRMT_0,
      YS_DRA_3,
      YS_rRA_1
   },
   {
      11,
      YS_PREAM_FRMT_0,
      YS_DRA_3,
      YS_rRA_2
   },
   {
      12,
      YS_PREAM_FRMT_0,
      YS_DRA_4,
      YS_rRA_0
   },
   {
      13,
      YS_PREAM_FRMT_0,
      YS_DRA_4,
      YS_rRA_1
   },
   {
      14,
      YS_PREAM_FRMT_0,
      YS_DRA_4,
      YS_rRA_2
   },
   {
      15,
      YS_PREAM_FRMT_0,
      YS_DRA_5,
      YS_rRA_0
   },
   {
      16,
      YS_PREAM_FRMT_0,
      YS_DRA_5,
      YS_rRA_1
   },
   {
      17,
      YS_PREAM_FRMT_0,
      YS_DRA_5,
      YS_rRA_2
   },
   {
      18,
      YS_PREAM_FRMT_0,
      YS_DRA_6,
      YS_rRA_0
   },
   {
      19,
      YS_PREAM_FRMT_0,
      YS_DRA_6,
      YS_rRA_1
   },
   {
      20,
      YS_PREAM_FRMT_1,
      YS_DRA_0_POINT_5,
      YS_rRA_0
   },
   {
      21,
      YS_PREAM_FRMT_1,
      YS_DRA_0_POINT_5,
      YS_rRA_1
   },
   {
      22,
      YS_PREAM_FRMT_1,
      YS_DRA_0_POINT_5,
      YS_rRA_2
   },
   {
      23,
      YS_PREAM_FRMT_1,
      YS_DRA_1,
      YS_rRA_0
   },
   {
      24,
      YS_PREAM_FRMT_1,
      YS_DRA_1,
      YS_rRA_1
   },
   {
      25,
      YS_PREAM_FRMT_1,
      YS_DRA_2,
      YS_rRA_0
   },
   {
      26,
      YS_PREAM_FRMT_1,
      YS_DRA_3,
      YS_rRA_0
   },
   {
      27,
      YS_PREAM_FRMT_1,
      YS_DRA_4,
      YS_rRA_0
   },
   {
      28,
      YS_PREAM_FRMT_1,
      YS_DRA_5,
      YS_rRA_0
   },
   {
      29,
      YS_PREAM_FRMT_1,
      YS_DRA_6,
      YS_rRA_0
   },
   {
      30,
      YS_PREAM_FRMT_2,
      YS_DRA_0_POINT_5,
      YS_rRA_0
   },
   {
      31,
      YS_PREAM_FRMT_2,
      YS_DRA_0_POINT_5,
      YS_rRA_1
   },
   {
      32,
      YS_PREAM_FRMT_2,
      YS_DRA_0_POINT_5,
      YS_rRA_2
   },
   {
      33,
      YS_PREAM_FRMT_2,
      YS_DRA_1,
      YS_rRA_0
   },
   {
      34,
      YS_PREAM_FRMT_2,
      YS_DRA_1,
      YS_rRA_1
   },
   {
      35,
      YS_PREAM_FRMT_2,
      YS_DRA_2,
      YS_rRA_0
   },
   {
      36,
      YS_PREAM_FRMT_2,
      YS_DRA_3,
      YS_rRA_0
   },
   {
      37,
      YS_PREAM_FRMT_2,
      YS_DRA_4,
      YS_rRA_0
   },
   {
      38,
      YS_PREAM_FRMT_2,
      YS_DRA_5,
      YS_rRA_0
   },
   {
      39,
      YS_PREAM_FRMT_2,
      YS_DRA_6,
      YS_rRA_0
   },
   {
      40,
      YS_PREAM_FRMT_3,
      YS_DRA_0_POINT_5,
      YS_rRA_0
   },
   {
      41,
      YS_PREAM_FRMT_3,
      YS_DRA_0_POINT_5,
      YS_rRA_1
   },
   {
      42,
      YS_PREAM_FRMT_3,
      YS_DRA_0_POINT_5,
      YS_rRA_2
   },
   {
      43,
      YS_PREAM_FRMT_3,
      YS_DRA_1,
      YS_rRA_0
   },
   {
      44,
      YS_PREAM_FRMT_3,
      YS_DRA_1,
      YS_rRA_1
   },
   {
      45,
      YS_PREAM_FRMT_3,
      YS_DRA_2,
      YS_rRA_0
   },
   {
      46,
      YS_PREAM_FRMT_3,
      YS_DRA_3,
      YS_rRA_0
   },
   {
      47,
      YS_PREAM_FRMT_3,
      YS_DRA_4,
      YS_rRA_0
   },
   {
      48,
      YS_PREAM_FRMT_4,
      YS_DRA_0_POINT_5,
      YS_rRA_0
   },
   {
      49,
      YS_PREAM_FRMT_4,
      YS_DRA_0_POINT_5,
      YS_rRA_1
   },
   {
      50,
      YS_PREAM_FRMT_4,
      YS_DRA_0_POINT_5,
      YS_rRA_2
   },
   {
      51,
      YS_PREAM_FRMT_4,
      YS_DRA_1,
      YS_rRA_0
   },
   {
      52,
      YS_PREAM_FRMT_4,
      YS_DRA_1,
      YS_rRA_1
   },
   {
      53,
      YS_PREAM_FRMT_4,
      YS_DRA_2,
      YS_rRA_0
   },
   {
      54,
      YS_PREAM_FRMT_4,
      YS_DRA_3,
      YS_rRA_0
   },
   {
      55,
      YS_PREAM_FRMT_4,
      YS_DRA_4,
      YS_rRA_0
   },
   {
      56,
      YS_PREAM_FRMT_4,
      YS_DRA_5,
      YS_rRA_0
   },
   {
      57,
      YS_PREAM_FRMT_4,
      YS_DRA_6,
      YS_rRA_0
   },
   {
      58,
      YS_PREAM_FRMT_NA,
      YS_DRA_NA,
      YS_rRA_NA
   },
   {
      59,
      YS_PREAM_FRMT_NA,
      YS_DRA_NA,
      YS_rRA_NA
   },
   {
      60,
      YS_PREAM_FRMT_NA,
      YS_DRA_NA,
      YS_rRA_NA
   },
   {
      61,
      YS_PREAM_FRMT_NA,
      YS_DRA_NA,
      YS_rRA_NA
   },
   {
      62,
      YS_PREAM_FRMT_NA,
      YS_DRA_NA,
      YS_rRA_NA
   },
   {
      63,
      YS_PREAM_FRMT_NA,
      YS_DRA_NA,
      YS_rRA_NA
   }
};

PUBLIC YsPrachTddMapLst ysPrachTddMapLstDb[YS_NUM_PRACH_TDD_MAP]
                                          [YS_NUM_TDD_SF_CFG]= 
{
   /* PRACH Configuration Index 0 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         1,
         {
            {
               YS_FREQ_RES_IDX_0,
               YS_EVEN_SFN,
               YS_SF_2
            }
         }  
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 1 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         1,
            {
               {
                  YS_FREQ_RES_IDX_0,
                  YS_ODD_SFN,
                  YS_SF_2
               }
            }
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 2 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         1,
         {
            {
               YS_FREQ_RES_IDX_0,
               YS_EVEN_SFN,
               YS_SF_7
            }
         }  
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 3 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         1,
         {
            {
               YS_FREQ_RES_IDX_0,
               YS_ALL_SFN,
               YS_SF_2
            }
         }  
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 4 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         1,
         {
            {
               YS_FREQ_RES_IDX_0,
               YS_ALL_SFN,
               YS_SF_7
            }
         }  
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 5 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 6 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         2,
         {
            {
               YS_FREQ_RES_IDX_0,
               YS_ALL_SFN,
               YS_SF_2
            },
            {
               YS_FREQ_RES_IDX_0,
               YS_EVEN_SFN,
               YS_SF_7
            }
         }  
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 7 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 8 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 9 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         3,
         {
            {
               YS_FREQ_RES_IDX_0,
               YS_ALL_SFN,
               YS_SF_2
            },
            {
               YS_FREQ_RES_IDX_0,
               YS_ALL_SFN,
               YS_SF_7
            },
            {
               YS_FREQ_RES_IDX_1,
               YS_ALL_SFN,
               YS_SF_2
            }
         }  
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 10 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         3,
         {
            {
               YS_FREQ_RES_IDX_0,
               YS_ALL_SFN,
               YS_SF_2
            },
            {
               YS_FREQ_RES_IDX_0,
               YS_ALL_SFN,
               YS_SF_7
            },
            {
               YS_FREQ_RES_IDX_1,
               YS_ALL_SFN,
               YS_SF_7
            }
         }  
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 11 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 12 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         4,
         {
            {
               YS_FREQ_RES_IDX_0,
               YS_ALL_SFN,
               YS_SF_2
            },
            {
               YS_FREQ_RES_IDX_0,
               YS_ALL_SFN,
               YS_SF_7
            },
            {
               YS_FREQ_RES_IDX_1,
               YS_ALL_SFN,
               YS_SF_2
            },
            {
               YS_FREQ_RES_IDX_1,
               YS_ALL_SFN,
               YS_SF_7
            }
         }  
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 13 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 14 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 15 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         5,
         {
            {
               YS_FREQ_RES_IDX_0,
               YS_ALL_SFN,
               YS_SF_2
            },
            {
               YS_FREQ_RES_IDX_0,
               YS_ALL_SFN,
               YS_SF_7
            },
            {
               YS_FREQ_RES_IDX_1,
               YS_ALL_SFN,
               YS_SF_2
            },
            {
               YS_FREQ_RES_IDX_1,
               YS_ALL_SFN,
               YS_SF_7
            },
            {
               YS_FREQ_RES_IDX_2,
               YS_ALL_SFN,
               YS_SF_2
            }
         }  
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 16 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         5,
         {
            {
               YS_FREQ_RES_IDX_0,
               YS_ALL_SFN,
               YS_SF_2
            },
            {
               YS_FREQ_RES_IDX_0,
               YS_ALL_SFN,
               YS_SF_7
            },
            {
               YS_FREQ_RES_IDX_1,
               YS_ALL_SFN,
               YS_SF_2
            },
            {
               YS_FREQ_RES_IDX_1,
               YS_ALL_SFN,
               YS_SF_7
            },
            {
               YS_FREQ_RES_IDX_2,
               YS_ALL_SFN,
               YS_SF_7
            }
         }  
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 17 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 18 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         6,
         {
            {
               YS_FREQ_RES_IDX_0,
               YS_ALL_SFN,
               YS_SF_2
            },
            {
               YS_FREQ_RES_IDX_0,
               YS_ALL_SFN,
               YS_SF_7
            },
            {
               YS_FREQ_RES_IDX_1,
               YS_ALL_SFN,
               YS_SF_2
            },
            {
               YS_FREQ_RES_IDX_1,
               YS_ALL_SFN,
               YS_SF_7
            },
            {
               YS_FREQ_RES_IDX_2,
               YS_ALL_SFN,
               YS_SF_2
            },
            {
               YS_FREQ_RES_IDX_2,
               YS_ALL_SFN,
               YS_SF_7
            }
         }  
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 19 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 20 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 21 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 22 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 23 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 24 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 25 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 26 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 27 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 28 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 29 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 30 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 31 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 32 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 33 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 34 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 35 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 36 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 37 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 38 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 39 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 40 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 41 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 42 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 43 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 44 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 45 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 46 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 47 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 48 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         1,
         {
            {
               YS_FREQ_RES_IDX_0,
               YS_EVEN_SFN,
               YS_SF_1
            }
         }  
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 49 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         1,
         {
            {
               YS_FREQ_RES_IDX_0,
               YS_ODD_SFN,
               YS_SF_1
            }
         }  
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 50 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         1,
         {
            {
               YS_FREQ_RES_IDX_0,
               YS_EVEN_SFN,
               YS_SF_6
            }
         }  
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 51 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         1,
         {
            {
               YS_FREQ_RES_IDX_0,
               YS_ALL_SFN,
               YS_SF_1
            }
         }  
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 52 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         1,
         {
            {
               YS_FREQ_RES_IDX_0,
               YS_ALL_SFN,
               YS_SF_6
            }
         }  
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 53 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         2,
         {
            {
               YS_FREQ_RES_IDX_0,
               YS_ALL_SFN,
               YS_SF_1
            },
            {
               YS_FREQ_RES_IDX_0,
               YS_ALL_SFN,
               YS_SF_6
            }
         }  
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 54 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         3,
         {
            {
               YS_FREQ_RES_IDX_0,
               YS_ALL_SFN,
               YS_SF_1
            },
            {
               YS_FREQ_RES_IDX_0,
               YS_ALL_SFN,
               YS_SF_6
            },
            {
               YS_FREQ_RES_IDX_1,
               YS_ALL_SFN,
               YS_SF_1
            }
         }  
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 55 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         4,
         {
            {
               YS_FREQ_RES_IDX_0,
               YS_ALL_SFN,
               YS_SF_1
            },
            {
               YS_FREQ_RES_IDX_0,
               YS_ALL_SFN,
               YS_SF_6
            },
            {
               YS_FREQ_RES_IDX_1,
               YS_ALL_SFN,
               YS_SF_1
            },
            {
               YS_FREQ_RES_IDX_1,
               YS_ALL_SFN,
               YS_SF_6
            }
         }  
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 56 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         5,
         {
            {
               YS_FREQ_RES_IDX_0,
               YS_ALL_SFN,
               YS_SF_1
            },
            {
               YS_FREQ_RES_IDX_0,
               YS_ALL_SFN,
               YS_SF_6
            },
            {
               YS_FREQ_RES_IDX_1,
               YS_ALL_SFN,
               YS_SF_1
            },
            {
               YS_FREQ_RES_IDX_1,
               YS_ALL_SFN,
               YS_SF_6
            },
            {
               YS_FREQ_RES_IDX_2,
               YS_ALL_SFN,
               YS_SF_1
            }
         }  
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 57 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         6,
         {
            {
               YS_FREQ_RES_IDX_0,
               YS_ALL_SFN,
               YS_SF_1
            },
            {
               YS_FREQ_RES_IDX_0,
               YS_ALL_SFN,
               YS_SF_6
            },
            {
               YS_FREQ_RES_IDX_1,
               YS_ALL_SFN,
               YS_SF_1
            },
            {
               YS_FREQ_RES_IDX_1,
               YS_ALL_SFN,
               YS_SF_6
            },
            {
               YS_FREQ_RES_IDX_2,
               YS_ALL_SFN,
               YS_SF_1
            },
            {
               YS_FREQ_RES_IDX_2,
               YS_ALL_SFN,
               YS_SF_6
            }
         }  
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 58 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 59 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 60 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 61 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 62 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   },
   /* PRACH Configuration Index 63 */
   {
      {       /* UL/DL Cfg 0 */
         0
      },
      {       /* UL/DL Cfg 1 */
         0
      },
      {       /* UL/DL Cfg 2 */
         0
      },
      {       /* UL/DL Cfg 3 */
         0
      },
      {       /* UL/DL Cfg 4 */
         0
      },
      {       /* UL/DL Cfg 5 */
         0
      },
      {       /* UL/DL Cfg 6 */
         0
      }
   }
};

PUBLIC Bool               ysPrachPresDb[YS_NUM_PRACH_PRES_ARR];
PUBLIC YsSrCfgInfo        ysSrCfgDb[YS_NUM_SR_CFG];
PUBLIC YsSrsCfgInfo       ysSrsCfgDb[YS_NUM_SRS_CFG];
PUBLIC YsCqiPmiCfgIdxInfo ysCqiPmiCfgDb[YS_NUM_CQI_CFG];

PUBLIC YsCqiPmiRiMap      ysCqiPmiRiMapDb[YS_NUM_TRANS_MODE] = 
{
   /* Cqi , Pmi, Ri */
   /* dummy transmission mode  */
   {
      FALSE,
      FALSE,
      FALSE
   },
   /* Transmission mode 1 */
   {
      TRUE,
      FALSE,
      FALSE
   },
   /* Transmission mode 2 */
   {
      TRUE,
      FALSE,
      FALSE
   },
   /* Transmission mode 3 */
   {
      TRUE,
      FALSE,
      TRUE
   },
   /* Transmission mode 4 */
   {
      TRUE,
      TRUE,
      TRUE
   },
   /* Transmission mode 5 */
   {
      TRUE,
      TRUE,
      FALSE
   },
   /* Transmission mode 6 */
   {
      TRUE,
      TRUE,
      FALSE
   },
   /* Transmission mode 7 */
   {
      TRUE,
      FALSE,
      FALSE
   }
};

/********************************************************************30**
  
         End of file:     ys_db_fdd.c@@/main/1 - Thu Dec  2 02:27:13 2010
  
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
----------- -------- ---- -----------------------------------------------
/main/1      ---     sgm                   1. eNodeB 1.2 release
*********************************************************************91*/
