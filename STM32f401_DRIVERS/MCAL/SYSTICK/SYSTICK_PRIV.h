/*
 * SYSTICK_PRIV.h
 *
 *  Created on: Nov 7, 2023
 *      Author: ahmed radwan
 */
#ifndef SYSTICK_PRIV_H
#define SYSTICK_PRIV_H
#include"../../SERVICES/Standard_Data_Types.h"

/********************************* SYSTICK REG *******************************/
#define STK_CTRL     (*((u32*)(0xE000E010)))
#define STK_LOAD     (*((u32*)(0xE000E014)))
#define STK_VAL      (*((u32*)(0xE000E018)))
#define STK_CALIB    (*((u32*)(0xE000E01C)))

#endif//SYSTICK_PRIV_H
