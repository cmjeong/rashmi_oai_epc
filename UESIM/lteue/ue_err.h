

/********************************************************************20**
  
        Name:     LTE UE Simulator 
    
        Type:     C include file
  
        Desc:     This file contain the hash definations for UE
 
        File:     ue_err.h

        Sid:      ue_err.h@@/main/1 - Sun Mar 28 22:59:23 2010
  
        Prg:      vp
  
*********************************************************************21*/

#ifndef __UE_ERR_H__
#define __UE_ERR_H__


/* Error Codes */
#define   ERRUE        0
#define   EUEXXX       0

#define   EUE001      (ERRUE +    1)    /*     ue_app.c: 351 */
#define   EUE002      (ERRUE +    2)    /*     ue_app.c: 365 */
#define   EUE003      (ERRUE +    3)    /*     ue_app.c: 451 */
#define   EUE004      (ERRUE +    4)    /*     ue_app.c: 462 */
#define   EUE005      (ERRUE +    5)    /*     ue_app.c: 523 */
#define   EUE006      (ERRUE +    6)    /*     ue_app.c: 603 */
#define   EUE007      (ERRUE +    7)    /*     ue_app.c: 610 */
#define   EUE008      (ERRUE +    8)    /*     ue_app.c: 671 */
#define   EUE009      (ERRUE +    9)    /*     ue_app.c: 728 */
#define   EUE010      (ERRUE +   10)    /*     ue_app.c: 887 */
#define   EUE011      (ERRUE +   11)    /*     ue_app.c: 930 */
#define   EUE012      (ERRUE +   12)    /*     ue_app.c: 973 */
#define   EUE013      (ERRUE +   13)    /*     ue_app.c:1015 */
#define   EUE014      (ERRUE +   14)    /*     ue_app.c:1022 */
#define   EUE015      (ERRUE +   15)    /*     ue_app.c:1074 */
#define   EUE016      (ERRUE +   16)    /*     ue_app.c:1117 */
#define   EUE017      (ERRUE +   17)    /*     ue_app.c:1160 */

#define   EUE018      (ERRUE +   18)    /*  ue_app_li.c: 323 */
#define   EUE019      (ERRUE +   19)    /*  ue_app_li.c: 524 */
#define   EUE020      (ERRUE +   20)    /*  ue_app_li.c: 631 */
#define   EUE021      (ERRUE +   21)    /*  ue_app_li.c: 702 */
#define   EUE022      (ERRUE +   22)    /*  ue_app_li.c: 712 */
#define   EUE023      (ERRUE +   23)    /*  ue_app_li.c: 719 */
#define   EUE024      (ERRUE +   24)    /*  ue_app_li.c: 846 */
#define   EUE025      (ERRUE +   25)    /*  ue_app_li.c: 892 */
#define   EUE026      (ERRUE +   26)    /*  ue_app_li.c:1073 */
#define   EUE027      (ERRUE +   27)    /*  ue_app_li.c:1147 */
#define   EUE028      (ERRUE +   28)    /*  ue_app_li.c:1163 */

#define   EUE029      (ERRUE +   29)    /* ue_app_utl.c: 251 */
#define   EUE030      (ERRUE +   30)    /* ue_app_utl.c: 658 */
#define   EUE031      (ERRUE +   31)    /* ue_app_utl.c: 938 */
#define   EUE032      (ERRUE +   32)    /* ue_app_utl.c:1044 */
#define   EUE033      (ERRUE +   33)    /* ue_app_utl.c:1212 */
#define   EUE034      (ERRUE +   34)    /* ue_app_utl.c:1304 */

#define   EUE035      (ERRUE +   35)    /* ue_appperf_li.c: 284 */
#define   EUE036      (ERRUE +   36)    /* ue_appperf_li.c: 383 */

#define   EUE037      (ERRUE +   37)    /* ue_data_app.c: 627 */
#define   EUE038      (ERRUE +   38)    /* ue_data_app.c: 725 */
#define   EUE039      (ERRUE +   39)    /* ue_data_app.c: 910 */
#define   EUE040      (ERRUE +   40)    /* ue_data_app.c: 968 */
#define   EUE041      (ERRUE +   41)    /* ue_data_app.c: 979 */
#define   EUE042      (ERRUE +   42)    /* ue_data_app.c: 994 */
#define   EUE043      (ERRUE +   43)    /* ue_data_app.c:1003 */
#define   EUE044      (ERRUE +   44)    /* ue_data_app.c:1028 */
#define   EUE045      (ERRUE +   45)    /* ue_data_app.c:1048 */
#define   EUE046      (ERRUE +   46)    /* ue_data_app.c:1090 */
#define   EUE047      (ERRUE +   47)    /* ue_data_app.c:1201 */
#define   EUE048      (ERRUE +   48)    /* ue_data_app.c:1228 */
#define   EUE049      (ERRUE +   49)    /* ue_data_app.c:1237 */
#define   EUE050      (ERRUE +   50)    /* ue_data_app.c:1246 */
#define   EUE051      (ERRUE +   51)    /* ue_data_app.c:1254 */
#define   EUE052      (ERRUE +   52)    /* ue_data_app.c:1580 */
#define   EUE053      (ERRUE +   53)    /* ue_data_app.c:1695 */

#define   EUE054      (ERRUE +   54)    /* ue_data_app_cav.c: 966 */
#define   EUE055      (ERRUE +   55)    /* ue_data_app_cav.c: 995 */
#define   EUE056      (ERRUE +   56)    /* ue_data_app_cav.c:1004 */
#define   EUE057      (ERRUE +   57)    /* ue_data_app_cav.c:1013 */
#define   EUE058      (ERRUE +   58)    /* ue_data_app_cav.c:1126 */
#define   EUE059      (ERRUE +   59)    /* ue_data_app_cav.c:1165 */

#define   EUE060      (ERRUE +   60)    /*     ue_emm.c: 186 */
#define   EUE061      (ERRUE +   61)    /*     ue_emm.c: 220 */
#define   EUE062      (ERRUE +   62)    /*     ue_emm.c: 228 */
#define   EUE063      (ERRUE +   63)    /*     ue_emm.c: 266 */
#define   EUE064      (ERRUE +   64)    /*     ue_emm.c: 305 */
#define   EUE065      (ERRUE +   65)    /*     ue_emm.c: 313 */
#define   EUE066      (ERRUE +   66)    /*     ue_emm.c: 352 */
#define   EUE067      (ERRUE +   67)    /*     ue_emm.c: 367 */
#define   EUE068      (ERRUE +   68)    /*     ue_emm.c: 407 */
#define   EUE069      (ERRUE +   69)    /*     ue_emm.c: 419 */
#define   EUE070      (ERRUE +   70)    /*     ue_emm.c: 468 */
#define   EUE071      (ERRUE +   71)    /*     ue_emm.c: 507 */
#define   EUE072      (ERRUE +   72)    /*     ue_emm.c: 521 */
#define   EUE073      (ERRUE +   73)    /*     ue_emm.c: 567 */
#define   EUE074      (ERRUE +   74)    /*     ue_emm.c: 582 */
#define   EUE075      (ERRUE +   75)    /*     ue_emm.c: 628 */
#define   EUE076      (ERRUE +   76)    /*     ue_emm.c: 642 */

#define   EUE077      (ERRUE +   77)    /*     ue_esm.c: 178 */
#define   EUE078      (ERRUE +   78)    /*     ue_esm.c: 190 */
#define   EUE079      (ERRUE +   79)    /*     ue_esm.c: 215 */
#define   EUE080      (ERRUE +   80)    /*     ue_esm.c: 255 */
#define   EUE081      (ERRUE +   81)    /*     ue_esm.c: 274 */
#define   EUE082      (ERRUE +   82)    /*     ue_esm.c: 305 */
#define   EUE083      (ERRUE +   83)    /*     ue_esm.c: 560 */
#define   EUE084      (ERRUE +   84)    /*     ue_esm.c: 602 */
#define   EUE085      (ERRUE +   85)    /*     ue_esm.c: 620 */
#define   EUE086      (ERRUE +   86)    /*     ue_esm.c: 763 */

#define   EUE087      (ERRUE +   87)    /*     ue_mac.c: 765 */
#define   EUE088      (ERRUE +   88)    /*     ue_mac.c: 819 */
#define   EUE089      (ERRUE +   89)    /*     ue_mac.c: 883 */
#define   EUE090      (ERRUE +   90)    /*     ue_mac.c: 954 */
#define   EUE091      (ERRUE +   91)    /*     ue_mac.c:1097 */
#define   EUE092      (ERRUE +   92)    /*     ue_mac.c:1115 */
#define   EUE093      (ERRUE +   93)    /*     ue_mac.c:1133 */
#define   EUE094      (ERRUE +   94)    /*     ue_mac.c:1219 */
#define   EUE095      (ERRUE +   95)    /*     ue_mac.c:1234 */
#define   EUE096      (ERRUE +   96)    /*     ue_mac.c:1302 */
#define   EUE097      (ERRUE +   97)    /*     ue_mac.c:1329 */
#define   EUE098      (ERRUE +   98)    /*     ue_mac.c:1353 */

#define   EUE099      (ERRUE +   99)    /*     ue_rlc.c: 473 */
#define   EUE100      (ERRUE +  100)    /*     ue_rlc.c: 592 */
#define   EUE101      (ERRUE +  101)    /*     ue_rlc.c: 599 */
#define   EUE102      (ERRUE +  102)    /*     ue_rlc.c: 610 */
#define   EUE103      (ERRUE +  103)    /*     ue_rlc.c: 622 */
#define   EUE104      (ERRUE +  104)    /*     ue_rlc.c: 701 */

#define   EUE105      (ERRUE +  105)    /*     ue_rrc.c: 282 */
#define   EUE106      (ERRUE +  106)    /*     ue_rrc.c: 334 */
#define   EUE107      (ERRUE +  107)    /*     ue_rrc.c: 401 */
#define   EUE108      (ERRUE +  108)    /*     ue_rrc.c: 492 */
#define   EUE109      (ERRUE +  109)    /*     ue_rrc.c: 555 */
#define   EUE110      (ERRUE +  110)    /*     ue_rrc.c: 602 */
#define   EUE111      (ERRUE +  111)    /*     ue_rrc.c: 666 */
#define   EUE112      (ERRUE +  112)    /*     ue_rrc.c: 721 */
#define   EUE113      (ERRUE +  113)    /*     ue_rrc.c: 785 */
#define   EUE114      (ERRUE +  114)    /*     ue_rrc.c: 845 */
#define   EUE115      (ERRUE +  115)    /*     ue_rrc.c:1026 */
#define   EUE116      (ERRUE +  116)    /*     ue_rrc.c:1098 */
#define   EUE117      (ERRUE +  117)    /*     ue_rrc.c:1107 */
#define   EUE118      (ERRUE +  118)    /*     ue_rrc.c:1119 */
#define   EUE119      (ERRUE +  119)    /*     ue_rrc.c:1213 */
#define   EUE120      (ERRUE +  120)    /*     ue_rrc.c:1228 */
#define   EUE121      (ERRUE +  121)    /*     ue_rrc.c:1296 */
#define   EUE122      (ERRUE +  122)    /*     ue_rrc.c:1312 */

#define   EUE123      (ERRUE +  123)    /*     ue_uim.c: 203 */
#define   EUE124      (ERRUE +  124)    /*     ue_uim.c: 297 */
#define   EUE125      (ERRUE +  125)    /*     ue_uim.c: 307 */
#define   EUE126      (ERRUE +  126)    /*     ue_uim.c: 367 */
#define   EUE127      (ERRUE +  127)    /*     ue_uim.c: 382 */
#define   EUE128      (ERRUE +  128)    /*     ue_uim.c: 393 */

#define   EUE129      (ERRUE +  129)    /*     ue_utl.c: 189 */

#endif /* __UE_ERR_H__ */
  
/********************************************************************30**
  
         End of file:     ue_err.h@@/main/1 - Sun Mar 28 22:59:23 2010
  
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
/main/1      ---      vp    1.Initial release.
*********************************************************************91*/
