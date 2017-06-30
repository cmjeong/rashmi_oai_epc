

/**********************************************************************
 
    Name:   LTE RLC layer
 
    Type:   C include file
 
    Desc:   Defines required by LIb interface of XTA LTE RLC
 
    File:   kwac_lib.h
 
    Sid:      kwac_lib.h@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:29 2014
 
    Prg:    gk 
 
**********************************************************************/
 

/*
*     The defines in this file correspond to structures and variables 
*     used by the following TRILLIUM software:
*
*     part no.             description
*     --------     ----------------------------------------------
*     1000371       LTE RLC
*
*/

#ifndef __KWAC_LIB_H__
#define __KWAC_LIB_H__

#ifdef KW_PDCP

/*--------------------------------------------------------- 
 *          SNOW_3G.h 
 *---------------------------------------------------------*/ 
 
#define OBD_SNOW_KEY 1
#define OBD_KASUMI_KEY 2

/* TODO: This need to relook, LTE PDCP supports only Snow3G, AES and NULL */
#define CPJ_SEC_ALG_KASUMI 0x04

/* The number of columns comprising a state in AES. This is a constant in AES. Value=4 */
#define Nb 4

/* XTIME is a macro that finds the product of {02} and the argument to XTIME modulo {1b}   */
#define XTIME(x)   ((x<<1) ^ (((x>>7) & 1) * 0x1b))


/* Multiplty is a macro used to multiply numbers in the field GF(2^8) */
#define MULTIPLY(x,y) (((y & 1) * x) ^ ((y>>1 & 1) * XTIME(x)) ^ ((y>>2 & 1) * XTIME(XTIME(x))) ^ ((y>>3 & 1) * XTIME(XTIME(XTIME(x)))) ^ ((y>>4 & 1) * XTIME(XTIME(XTIME(XTIME(x))))))

#define ROL16(a,b) (U16)((a<<b)|(a>>(16-b)))

#define LIB_SEL_LC                        0

#define OBD_EVT_CMP_INIT_REQ              0x00
#define OBD_EVT_CMP_REQ                   0x01
#define OBD_EVT_DECMP_REQ                 0x02
#define OBD_EVT_CMP_CLOSE_REQ             0x03
#define OBD_EVT_CMP_RESET_REQ             0x04
#define OBD_EVT_CMP_FB_REQ                0x05

#define OBD_EVT_INT_INIT_REQ              0x10
#define OBD_EVT_INT_PROT_REQ              0x11
#define OBD_EVT_INT_VER_REQ               0x12
#define OBD_EVT_INT_CLOSE_REQ             0x13

#define OBD_EVT_CP_INIT_REQ               0x20
#define OBD_EVT_UP_INIT_REQ               0x21
#define OBD_EVT_CIPHER_REQ                0x22
#define OBD_EVT_DECIPHER_REQ              0x23
#define OBD_EVT_CIPHER_CLOSE_REQ          0x24

#define PJ_ACC_COMP_BYTE   0xF0

#define ERROBD                  0

#define EOBD001         (ERROBD + 1)
#define EOBD002         (ERROBD + 2)
#define EOBD003         (ERROBD + 3)
#define EOBD004         (ERROBD + 4)
#define EOBD005         (ERROBD + 5)
#define EOBD006         (ERROBD + 6)
#define EOBD007         (ERROBD + 7)
#define EOBD008         (ERROBD + 8)
#define EOBD009         (ERROBD + 9)
#define EOBD010         (ERROBD + 10)
#define EOBD011         (ERROBD + 11)
#define EOBD012         (ERROBD + 12)
#define EOBD013         (ERROBD + 13)
#define EOBD014         (ERROBD + 14)
#define EOBD015         (ERROBD + 15)
#define EOBD016         (ERROBD + 16)
#define EOBD017         (ERROBD + 17)
#define EOBD018         (ERROBD + 18)
#define EOBD019         (ERROBD + 19)
#define EOBD020         (ERROBD + 20)
#define EOBD021         (ERROBD + 21)
#define EOBD022         (ERROBD + 22)
#define EOBD023         (ERROBD + 23)
#define EOBD024         (ERROBD + 24)
#define EOBD025         (ERROBD + 25)
#define EOBD026         (ERROBD + 26)
#define EOBD027         (ERROBD + 27)
#define EOBD028         (ERROBD + 28)
#define EOBD029         (ERROBD + 29)
#define EOBD030         (ERROBD + 30)
#define EOBD031         (ERROBD + 31)
#define EOBD032         (ERROBD + 32)
#define EOBD033         (ERROBD + 33)
#define EOBD034         (ERROBD + 34)
#define EOBD035         (ERROBD + 35)
#define EOBD036         (ERROBD + 36)
#define EOBD037         (ERROBD + 37)
#define EOBD038         (ERROBD + 38)
#define EOBD039         (ERROBD + 39)
#define EOBD040         (ERROBD + 40)
#define EOBD041         (ERROBD + 41)
#define EOBD042         (ERROBD + 42)
#define EOBD043         (ERROBD + 43)
#define EOBD044         (ERROBD + 44)
#define EOBD045         (ERROBD + 45)
#define EOBD046         (ERROBD + 46)
#define EOBD047         (ERROBD + 47)
#define EOBD048         (ERROBD + 48)
#define EOBD049         (ERROBD + 49)
#define EOBD050         (ERROBD + 50)
#define EOBD051         (ERROBD + 51)
#define EOBD052         (ERROBD + 52)
#define EOBD053         (ERROBD + 53)
#define EOBD054         (ERROBD + 54)
#define EOBD055         (ERROBD + 55)
#define EOBD056         (ERROBD + 56)
#define EOBD057         (ERROBD + 57)
#define EOBD058         (ERROBD + 58)
#define EOBD059         (ERROBD + 59)
#define EOBD060         (ERROBD + 60)
#define EOBD061         (ERROBD + 61)
#define EOBD062         (ERROBD + 62)
#define EOBD063         (ERROBD + 63)
#define EOBD064         (ERROBD + 64)
#define EOBD065         (ERROBD + 65)
#define EOBD066         (ERROBD + 66)
#define EOBD067         (ERROBD + 67)
#define EOBD068         (ERROBD + 68)
#define EOBD069         (ERROBD + 69)
#define EOBD070         (ERROBD + 70)
#define EOBD071         (ERROBD + 71)
#define EOBD072         (ERROBD + 72)
#define EOBD073         (ERROBD + 73)
#define EOBD074         (ERROBD + 74)
#define EOBD075         (ERROBD + 75)
#define EOBD076         (ERROBD + 76)
#define EOBD077         (ERROBD + 77)
#define EOBD078         (ERROBD + 78)
#define EOBD079         (ERROBD + 79)
#define EOBD080         (ERROBD + 80)
#define EOBD081         (ERROBD + 81)
#define EOBD082         (ERROBD + 82)
#define EOBD083         (ERROBD + 83)
#define EOBD084         (ERROBD + 84)
#define EOBD085         (ERROBD + 85)
#define EOBD086         (ERROBD + 86)
#define EOBD087         (ERROBD + 87)
#define EOBD088         (ERROBD + 88)
#define EOBD089         (ERROBD + 89)
#define EOBD090         (ERROBD + 90)
#define EOBD091         (ERROBD + 91)
#define EOBD092         (ERROBD + 92)

#endif /* KW_PDCP */

#endif /* __KWAC_LIB_H__ */


/**********************************************************************
         End of file:     kwac_lib.h@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:29 2014
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---   gk         1. Initial Release.
*********************************************************************91*/

