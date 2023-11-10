#include"../../SERVICES/Standard_Data_Types.h"
/*********************** RCC DATA TYPE & reg base adress *********************/
typedef struct
{
    volatile u32 RCC_CR;
    volatile u32 RCC_PLLCFGR;
    volatile u32 RCC_CFGR;
    volatile u32 RCC_CIR;
    volatile u32 RCC_AHB1RSTR;
    volatile u32 RCC_AHB2RSTR;
    volatile u32 RCC_Reserved0[2];
    volatile u32 RCC_APB1RSTR;
    volatile u32 RCC_APB2RSTR;
    volatile u32 RCC_Reserved1[2];
    volatile u32 RCC_AHB1ENR;
    volatile u32 RCC_AHB2ENR;
    volatile u32 RCC_Reserved2[2];
    volatile u32 RCC_APB1ENR;
    volatile u32 RCC_APB2ENR;
    volatile u32 RCC_Reserved3[2];
    volatile u32 RCC_AHB1LPENR;
    volatile u32 RCC_AHB2LPENR;
    volatile u32 RCC_Reserved4[2];
    volatile u32 RCC_APB1LPENR;
    volatile u32 RCC_APB2LPENR;
    volatile u32 RCC_Reserved5[2];
    volatile u32 RCC_BDCR;
    volatile u32 RCC_CSR;
    volatile u32 RCC_Reserved6[2];
    volatile u32 RCC_SSCGR;
    volatile u32 RCC_PLLI2SCFGR;
    volatile u32 RCC_DCKCFGR;
} RCC_t;

// reg base adreees
#define RCC ((RCC_t *)(0x40023800))
