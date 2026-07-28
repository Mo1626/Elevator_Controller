/*
 * PrimitiveType.h
 *
 *  Created on: Feb 25, 2026
 *      Author: Ahmed El-Gaafrawy
 */

#ifndef INC_PRIMITIVETYPE_H_
#define INC_PRIMITIVETYPE_H_


/*************************************************************/
/********* Solid Definition Of Booleans and NULL  ************/
/*************************************************************/
#define TRUE                        (1U)
#define FALSE                       (0U)

#ifndef NULL
    #define NULL                    ((void *) 0x00)
#endif
/*************************************************************/
/*************************************************************/


/*************************************************************/
/********* New type defs of Primitive Data Types  ************/
/*************************************************************/
typedef unsigned char               u8;
typedef signed char                 s8;
typedef unsigned short              u16;
typedef signed short                s16;
typedef unsigned long               u32;
typedef signed long                 s32;
typedef unsigned long long          u64;
typedef signed long long            s64;
typedef unsigned char               BOOL;

/*************************************************************/
/*************************************************************/


#endif /* INC_PRIMITIVETYPE_H_ */
