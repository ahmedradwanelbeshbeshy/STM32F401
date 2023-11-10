/*
 * Standard_Data_Types.h
 *
 * Created: 10/20/2023 9:03:28 PM
 *  Author: ahmed radwan
 */

#ifndef STANDARD_DATA_TYPES_H_
#define STANDARD_DATA_TYPES_H_

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;

typedef signed char s8;
typedef signed short s16;
typedef signed long s32;
typedef signed long long s64;

typedef float f32;
typedef double f64;

typedef unsigned char *pu8;
// typedef unsigned char*        ptr_u8;
typedef unsigned short *ptr_u16;
typedef unsigned long *ptr_u32;

typedef signed char *ptr_s8;
typedef signed short *ptr_s16;
typedef signed long *ptr_s32;

#define ZERO_INIT 0

#define NULL ((void *)0)



typedef void (*CALL_BACK_FN_TYPE)(void);

#endif /* STANDARD_DATA_TYPES_H_ */