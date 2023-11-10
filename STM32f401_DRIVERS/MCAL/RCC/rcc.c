#include"../../SERVICES/Standard_Data_Types.h"
#include"../../SERVICES/Bit_Wise_Operations.h"
#include"rcc_priv.h"
#include"rcc.h"
#define REGISTER_BIT_0  0
#define REGISTER_BIT_1	1
#define REGISTER_BIT_2	2
#define REGISTER_BIT_3	3
#define REGISTER_BIT_4	4
#define REGISTER_BIT_5	5
#define REGISTER_BIT_6	6
#define REGISTER_BIT_7	7
#define REGISTER_BIT_8	8
#define REGISTER_BIT_9	9
#define REGISTER_BIT_10	10
#define REGISTER_BIT_11	11
#define REGISTER_BIT_12	12
#define REGISTER_BIT_13	13
#define REGISTER_BIT_14	14
#define REGISTER_BIT_15	15
#define REGISTER_BIT_16	16
#define REGISTER_BIT_17	17
#define REGISTER_BIT_18	18
#define REGISTER_BIT_19	19
#define REGISTER_BIT_20	20
#define REGISTER_BIT_21	21
#define REGISTER_BIT_22	22
#define REGISTER_BIT_23	23
#define REGISTER_BIT_24	24
#define REGISTER_BIT_25	25
#define REGISTER_BIT_26	26
#define REGISTER_BIT_27	27
#define REGISTER_BIT_28	28
#define REGISTER_BIT_29	29
#define REGISTER_BIT_30	30
#define REGISTER_BIT_31	31
#define REGISTER_BIT_32	32

/********************************* RELATED to Rcc_enuCfg_Pll FN ********************************/
#define PLL_CFG(pllq,pllsrc,pllp,plln,pllm)  ((pllq<<24)|(pllsrc<<22)|(pllp<<16)|(plln<<6)|(pllm))

//used in cfg of pll reg to keep he reserved bits with the reset value 
#define PLL_RESERVED_BIT_MASK   0x20000000

#define PLL_N_MIN_VAL           192
#define PLL_N_MAX_VAL           432
#define PLL_M_MIN_VAL           2
#define PLL_M_MAX_VAL           63
/*************************************************************************************************/


#define HSI_SLECT_MASK 0xFFFFFFFC
#define HSE_SLECT_MASK 0xFFFFFFFD
#define PLL_slect_MASK 0xFFFFFFFE

//used in Rcc_enuGET_SYS_CLOCK fn
#define CLOCK_SLESCT_MASK 0x0C


#define Delay_value 10000 
/************************ SYSTEM FREQ SERVICE section***********************/

#ifndef EXTERNAL_FREQ
#error"EXTERNAL_FREQ not defined in rcc.h file "
#endif
// internal clock source freq
#define HSI_RC 16000000

// this var is aglopal var used to inform al other prephiral with the system freq
volatile u32 STM_SYS_FREQ=0;
volatile u32 PLL_source=0;
volatile u32 PLL_OUTPUT=0;

/************************ SYSTEM FREQ SERVICE section end************************/

Rcc_tenuErrorStatus Rcc_enuSelectSysCLk(u8 Copy_u8SysClk , u8 Copy_u8OldSysClk) 
{
    Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
    u32 loc_counter=Delay_value;// used to get out from checking the flag in the simulation
    u32 old_clock=((RCC->RCC_CFGR)&0x03);// get the old system clock
    switch (Copy_u8SysClk)
    {
    case RCC_CLK_HSI:
        SET_BIT(RCC->RCC_CR,REGISTER_BIT_0);
        loc_counter=Delay_value;
        // wait untill clock source be ready
        while(!(GET_BIT(RCC->RCC_CR,REGISTER_BIT_1)))
        {
           if(loc_counter==0) 
           {
            break;
           }
           loc_counter--;
        }
        // switch to the desired clock
        RCC->RCC_CFGR&=HSI_SLECT_MASK;
        STM_SYS_FREQ= HSI_RC;
        break;
    case RCC_CLK_HSE:
        SET_BIT(RCC->RCC_CR,REGISTER_BIT_16);
         loc_counter=Delay_value;
         // wait untill clock source be ready
        while(!(GET_BIT(RCC->RCC_CR,REGISTER_BIT_17)))
        {
           if(loc_counter==0) 
           {
            break;
           }
           loc_counter--;
        }
        // switch to the desired clock
        RCC->RCC_CFGR&=(HSI_SLECT_MASK|RCC_CLK_HSE);
        STM_SYS_FREQ= EXTERNAL_FREQ;
        break;
    case RCC_CLK_PLL:
            SET_BIT(RCC->RCC_CR,REGISTER_BIT_24);
            loc_counter=Delay_value;
        while(!(GET_BIT(RCC->RCC_CR,REGISTER_BIT_25)))
        {
           if(loc_counter==0) 
           {
            break;
           }
           loc_counter--;
        }
        // switch to the desired clock
        RCC->RCC_CFGR&=(HSI_SLECT_MASK|RCC_CLK_PLL);
        STM_SYS_FREQ=PLL_OUTPUT;
        break;
    default:
        Locerrorstatus=RCC_enuUnLogicActionError;
        break;
    }
    if(Copy_u8OldSysClk==RCC_STATE_NOTPRESERVE)
    {
      switch(old_clock)
      {
        case RCC_CLK_HSI:
           CLR_BIT(RCC->RCC_CR,REGISTER_BIT_0);  
           break;
        case RCC_CLK_HSE:
            CLR_BIT(RCC->RCC_CR,REGISTER_BIT_16);
            break;
        case RCC_CLK_PLL:
            CLR_BIT(RCC->RCC_CR,REGISTER_BIT_26);
            break;
        default:
            Locerrorstatus=RCC_enuUnLogicActionError;
            break;
     } 
    }

    return Locerrorstatus;
}

Rcc_tenuErrorStatus Rcc_enuControlCLk(u8 Copy_u8ControlHSI  ,u8 Copy_u8ControlHSE ,u8 Copy_u8ControlPLL) 
{
    Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
    switch(Copy_u8ControlHSI)
    {
        case RCC_CNTROL_HSION:
            SET_BIT(RCC->RCC_CR,REGISTER_BIT_0);
            break;
        case RCC_CNTROL_HSIOFF:
            CLR_BIT(RCC->RCC_CR,REGISTER_BIT_0);
            break;
        default:
            Locerrorstatus=RCC_enuUnLogicActionError;
            break;
    }
    switch(Copy_u8ControlHSE)
    {
        case RCC_CNTROL_HSEON:
            SET_BIT(RCC->RCC_CR,REGISTER_BIT_16);
            break;
        case RCC_CNTROL_HSEOFF:
            CLR_BIT(RCC->RCC_CR,REGISTER_BIT_16);
            break;
        default:
            Locerrorstatus=RCC_enuUnLogicActionError;
            break;        
    }
    switch(Copy_u8ControlPLL)
    {
        case RCC_CNTROL_PLLON:
            SET_BIT(RCC->RCC_CR,REGISTER_BIT_24);
            break;
        case RCC_CNTROL_PLLOFF:
            CLR_BIT(RCC->RCC_CR,REGISTER_BIT_24);
            break;
        default:
            Locerrorstatus=RCC_enuUnLogicActionError;
            break;            
    }
    return Locerrorstatus;
}

Rcc_tenuErrorStatus Rcc_enuCheckCLk(u8 Copy_u8CLk, pu8 Add_pu8RdyStatus) 
{
    Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
    if (NULL==Add_pu8RdyStatus)
    {
        Locerrorstatus=RCC_enuNullPointerError;
    }
    else
    {
     switch(Copy_u8CLk)
      {
        case RCC_CLK_HSI:
            *Add_pu8RdyStatus=GET_BIT(RCC->RCC_CR,REGISTER_BIT_1);
           break;
        case RCC_CLK_HSE:
            *Add_pu8RdyStatus=GET_BIT(RCC->RCC_CR,REGISTER_BIT_17);
            break;
        case RCC_CLK_PLL:
           *Add_pu8RdyStatus=GET_BIT(RCC->RCC_CR,REGISTER_BIT_25);
            break;
        default:
             Locerrorstatus=RCC_enuUnLogicActionError;
            break;
      } 
    }
    return Locerrorstatus;
}

Rcc_tenuErrorStatus Rcc_enuCfg_Pll(u8 Copy_u8Q , u8 Copy_u8SrcPll , u8 Copy_u8P , u16 Copy_u16N,u8 COPY_u8M)
{
    Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
    if(((RCC->RCC_CFGR)&0x03)==RCC_CLK_PLL)
    {
        Locerrorstatus=RCC_enuPll_IS_On_Error;
    }
    if(Copy_u8Q>RCC_Q_DIVBY_15)
    {
        Locerrorstatus=RCC_enuInvalid_Q_Error;
    }
    if(Copy_u8SrcPll>RCC_PLLSRC_HSE)
    {
        Locerrorstatus=RCC_enuInvalid_ScrPll_Error;
    }
    if(Copy_u8P>RCC_PLLP_DIVBY_8)
    {
        Locerrorstatus=RCC_enuInvalid_P_Error;
    }
    if((Copy_u16N<PLL_N_MIN_VAL)||(Copy_u16N>PLL_N_MAX_VAL))
    {
        Locerrorstatus=RCC_enuInvalid_N_Error;
    }
    if((COPY_u8M<PLL_M_MIN_VAL)||(COPY_u8M>PLL_M_MAX_VAL))
    {
        Locerrorstatus=RCC_enuInvalid_M_Error;
    }
    if(Locerrorstatus==Rcc_enuOk)
    {
       RCC->RCC_PLLCFGR=PLL_RESERVED_BIT_MASK|PLL_CFG(Copy_u8Q,Copy_u8SrcPll,Copy_u8P,Copy_u16N,COPY_u8M);
       if (Copy_u8SrcPll==RCC_PLLSRC_HSI)
       {
         PLL_OUTPUT=(HSI_RC*Copy_u16N)/(COPY_u8M*Copy_u8P);
       }
       else
       {
         PLL_OUTPUT=(EXTERNAL_FREQ*Copy_u16N)/(COPY_u8M*Copy_u8P);
       }
       
    }
    return Locerrorstatus;
}

Rcc_tenuErrorStatus Rcc_enuGET_SYS_CLOCK(pu8 ADD_pu8SYSclocK)
{
    Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
    if (NULL==ADD_pu8SYSclocK)
    {
        Locerrorstatus=RCC_enuNullPointerError;
    }
    else
    {
        *ADD_pu8SYSclocK=((RCC->RCC_CFGR)&CLOCK_SLESCT_MASK);// get the old system clock
    }
    
    return Locerrorstatus;
}

Rcc_tenuErrorStatus Rcc_enuCfg_AHB_BusPrescalers(u32 Copy_u32Prescaler)
{
    Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
    switch(Copy_u32Prescaler)
    {
        case RCC_AHB_NOTDIV:
            (RCC->RCC_CFGR)&=RCC_AHB_NOTDIV;
            
            break;
         case RCC_AHB_DIV2:
            (RCC->RCC_CFGR)&=(RCC_AHB_NOTDIV|Copy_u32Prescaler);
            STM_SYS_FREQ/=2;//update system freq variable 
            break;
         case RCC_AHB_DIV4:
            (RCC->RCC_CFGR)&=(RCC_AHB_NOTDIV|Copy_u32Prescaler);
            STM_SYS_FREQ/=4;//update system freq variable 
            break;
         case RCC_AHB_DIV8:
            (RCC->RCC_CFGR)&=(RCC_AHB_NOTDIV|Copy_u32Prescaler);
            STM_SYS_FREQ/=8;//update system freq variable 
            break;
         case RCC_AHB_DIV16:
            (RCC->RCC_CFGR)&=(RCC_AHB_NOTDIV|Copy_u32Prescaler);
            STM_SYS_FREQ/=16;//update system freq variable 
            break;
        case RCC_AHB_DIV64:
            (RCC->RCC_CFGR)&=(RCC_AHB_NOTDIV|Copy_u32Prescaler);
            STM_SYS_FREQ/=64;//update system freq variable 
            break;
        case RCC_AHB_DIV128:
            (RCC->RCC_CFGR)&=(RCC_AHB_NOTDIV|Copy_u32Prescaler);
            STM_SYS_FREQ/=128;//update system freq variable 
            break;
        case RCC_AHB_DIV256:
            (RCC->RCC_CFGR)&=(RCC_AHB_NOTDIV|Copy_u32Prescaler);
            STM_SYS_FREQ/=256;//update system freq variable 
            break;
        case RCC_AHB_DIV512:
            (RCC->RCC_CFGR)&=(RCC_AHB_NOTDIV|Copy_u32Prescaler);
            STM_SYS_FREQ/=512;//update system freq variable 
            break;           
         default:
            Locerrorstatus=Rcc_enuWrongAHB_PrescalerError;
            break;
    }
    return Locerrorstatus;
}

Rcc_tenuErrorStatus Rcc_enuCfg_APB1_BusPrescalers(u32 Copy_u32Prescaler)
{
    Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
    switch(Copy_u32Prescaler)
    {
        case RCC_APB1_NOTDIV:
            (RCC->RCC_CFGR)&=(RCC_APB1_NOTDIV|Copy_u32Prescaler);
            break;
         case RCC_APB1_DIV2:
            (RCC->RCC_CFGR)&=(RCC_APB1_NOTDIV|Copy_u32Prescaler);
            break;
         case RCC_APB1_DIV4:
            (RCC->RCC_CFGR)&=(RCC_APB1_NOTDIV|Copy_u32Prescaler);
            break;
         case RCC_APB1_DIV8:
            (RCC->RCC_CFGR)&=(RCC_APB1_NOTDIV|Copy_u32Prescaler);
            break;
         case RCC_APB1_DIV16:
            (RCC->RCC_CFGR)&=(RCC_APB1_NOTDIV|Copy_u32Prescaler);
            break;
         default:
            Locerrorstatus=Rcc_enuWrongAPB1_PrescalerError;
            break;
    }
    return Locerrorstatus;
}

Rcc_tenuErrorStatus Rcc_enuCfg_APB2_BusPrescalers(u32 Copy_u32Prescaler)
{
    Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
    switch(Copy_u32Prescaler)
    {
        case RCC_APB2_NOTDIV:
            (RCC->RCC_CFGR)&=RCC_APB2_NOTDIV;
            break;
         case RCC_APB2_DIV2:
            (RCC->RCC_CFGR)&=(RCC_APB2_NOTDIV|Copy_u32Prescaler);
            break;
         case RCC_APB2_DIV4:
            (RCC->RCC_CFGR)&=(RCC_APB2_NOTDIV|Copy_u32Prescaler);
            break;
         case RCC_APB2_DIV8:
            (RCC->RCC_CFGR)&=(RCC_APB2_NOTDIV|Copy_u32Prescaler);
            break;
         case RCC_APB2_DIV16:
            (RCC->RCC_CFGR)&=(RCC_APB2_NOTDIV|Copy_u32Prescaler);
            break;
         default:
            //in valid input
            Locerrorstatus=Rcc_enuWrongAPB2_PrescalerError;
            break;
    }
    return Locerrorstatus;
}

Rcc_tenuErrorStatus Rcc_enuControl_AHB1_Peripheral(RCC_AHB1Periph_TypeDef Peripheral,RCC_Periph_CFG_TypeDef action)
{
        Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
        u32 bitMASK=0;
        switch (Peripheral)
         {
            case RCC_AHB1Periph_GPIOA:
            case RCC_AHB1Periph_GPIOB:
            case RCC_AHB1Periph_GPIOC:
            case RCC_AHB1Periph_GPIOD:
            case RCC_AHB1Periph_GPIOE:
            case RCC_AHB1Periph_GPIOH:
            case RCC_AHB1Periph_CRC:
            case RCC_AHB1Periph_DMA1:
            case RCC_AHB1Periph_DMA2:
                // Valid peripheral, proceed with enabling or disabling
                if(action==RCC_Periph_ENABLE)
                {
                    bitMASK=1<<Peripheral;
                    RCC->RCC_AHB1ENR|=bitMASK;
                }
                else if(action==RCC_Periph_DISABLE)
                {
                    bitMASK=1<<Peripheral;
                    RCC->RCC_AHB1ENR&=~bitMASK;
                }
                else
                {
                    Locerrorstatus=RCC_enuUnLogicActionError; 
                }

                break;
            default:
                // Invalid peripheral
                Locerrorstatus=Rcc_enuWrongAHB1_WRONG_PERIPHERAL;  
                break; 
    }
    return Locerrorstatus;
}
Rcc_tenuErrorStatus Rcc_enuControl_AHB2_Peripheral(RCC_AHB2Periph_TypeDef Peripheral,RCC_Periph_CFG_TypeDef action)
{
    Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
    if(Peripheral==RCC_AHB2Periph_OTGFS)
    {
        if(action==RCC_Periph_ENABLE)
        {
            SET_BIT(RCC->RCC_AHB2ENR,Peripheral);
        }
        else if(action==RCC_Periph_DISABLE)
        {
            CLR_BIT(RCC->RCC_AHB2ENR,Peripheral);
        }
        else
        {
           Locerrorstatus=RCC_enuUnLogicActionError;  
        }
    }
    else
    {
        Locerrorstatus=Rcc_enuWrongAHB2_WRONG_PERIPHERAL;
    }
    return Locerrorstatus;
}

Rcc_tenuErrorStatus Rcc_enuControl_APB1_Peripheral(RCC_APB1Periph_TypeDef Peripheral,RCC_Periph_CFG_TypeDef action)
{
    Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
        u32 bitMASK=0;
        switch (Peripheral)
         {
            case RCC_APB1Periph_TIM2:
            case RCC_APB1Periph_TIM3:
            case RCC_APB1Periph_TIM4:
            case RCC_APB1Periph_TIM5:
            case RCC_APB1Periph_WWDG:
            case RCC_APB1Periph_SPI2:
            case RCC_APB1Periph_SPI3:
            case RCC_APB1Periph_I2C1:
            case RCC_APB1Periph_I2C2:
            case RCC_APB1Periph_I2C3:
            case RCC_APB1Periph_PWR:
                // Valid peripheral, proceed with enabling or disabling
                if(action==RCC_Periph_ENABLE)
                {
                    bitMASK=1<<Peripheral;
                    RCC->RCC_APB1ENR|=bitMASK;
                }
                else if(action==RCC_Periph_DISABLE)
                {
                    bitMASK=1<<Peripheral;
                    RCC->RCC_APB1ENR&=~bitMASK;
                }
                else
                {
                    Locerrorstatus=RCC_enuUnLogicActionError; 
                }

                break;
            default:
                // Invalid peripheral
                Locerrorstatus=Rcc_enuWrongAPB1_WRONG_PERIPHERAL;  
                break; 
    }
    return Locerrorstatus;
}
Rcc_tenuErrorStatus Rcc_enuControl_APB2_Peripheral(RCC_APB2Periph_TypeDef Peripheral,RCC_Periph_CFG_TypeDef action)
{
    Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
    u32 bitMASK=0;
    switch (Peripheral)
    {
            case RCC_APB2Periph_TIM1:
            case RCC_APB2Periph_USART1:
            case RCC_APB2Periph_USART6:
            case RCC_APB2Periph_ADC1:
            case RCC_APB2Periph_SDIO:
            case RCC_APB2Periph_SPI1:
            case RCC_APB2Periph_SPI4:
            case RCC_APB2Periph_SYSCFG:
            case RCC_APB2Periph_TIM9:
            case RCC_APB2Periph_TIM10:
            case RCC_APB2Periph_TIM11:
                // Valid peripheral, proceed with enabling or disabling
                if(action==RCC_Periph_ENABLE)
                {
                    bitMASK=1<<Peripheral;
                    RCC->RCC_APB2ENR|=bitMASK;
                }
                else if(action==RCC_Periph_DISABLE)
                {
                    bitMASK=1<<Peripheral;
                    RCC->RCC_APB2ENR&=~bitMASK;
                }
                else
                {
                    Locerrorstatus=RCC_enuUnLogicActionError; 
                }

                break;
            default:
                // Invalid peripheral
                Locerrorstatus=Rcc_enuWrongAPB2_WRONG_PERIPHERAL;  
                break; 
    }
    return Locerrorstatus;
}

Rcc_tenuErrorStatus Rcc_enuReset_AHB1_Peripheral(RCC_AHB1Periph_TypeDef Peripheral)
{
        Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
        u32 bitMASK=0;
        switch (Peripheral)
         {
            case RCC_AHB1Periph_GPIOA:
            case RCC_AHB1Periph_GPIOB:
            case RCC_AHB1Periph_GPIOC:
            case RCC_AHB1Periph_GPIOD:
            case RCC_AHB1Periph_GPIOE:
            case RCC_AHB1Periph_GPIOH:
            case RCC_AHB1Periph_CRC:
            case RCC_AHB1Periph_DMA1:
            case RCC_AHB1Periph_DMA2:
                // Valid peripheral, proceed with reset
                    bitMASK=1<<Peripheral;
                    RCC->RCC_AHB1RSTR|=bitMASK;
                break;
            default:
                // Invalid peripheral
                Locerrorstatus=Rcc_enuWrongAHB1_WRONG_PERIPHERAL;  
                break; 
    }
    return Locerrorstatus;
}
Rcc_tenuErrorStatus Rcc_enuReset_AHB2_Peripheral(RCC_AHB2Periph_TypeDef Peripheral)
{
    Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
    if(Peripheral==RCC_AHB2Periph_OTGFS)
    {
        SET_BIT(RCC->RCC_AHB2RSTR,Peripheral);
    }
    else
    {
        Locerrorstatus=Rcc_enuWrongAHB2_WRONG_PERIPHERAL;
    }
    return Locerrorstatus;
}

Rcc_tenuErrorStatus Rcc_enuReset_APB1_Peripheral(RCC_APB1Periph_TypeDef Peripheral)
{
    Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
        u32 bitMASK=0;
        switch (Peripheral)
         {
            case RCC_APB1Periph_TIM2:
            case RCC_APB1Periph_TIM3:
            case RCC_APB1Periph_TIM4:
            case RCC_APB1Periph_TIM5:
            case RCC_APB1Periph_WWDG:
            case RCC_APB1Periph_SPI2:
            case RCC_APB1Periph_SPI3:
            case RCC_APB1Periph_I2C1:
            case RCC_APB1Periph_I2C2:
            case RCC_APB1Periph_I2C3:
            case RCC_APB1Periph_PWR:
                // Valid peripheral, proceed with enabling or disabling
                bitMASK=1<<Peripheral;
                RCC->RCC_APB1RSTR|=bitMASK;
                break;
            default:
                // Invalid peripheral
                Locerrorstatus=Rcc_enuWrongAPB1_WRONG_PERIPHERAL;  
                break; 
    }
    return Locerrorstatus;
}
Rcc_tenuErrorStatus Rcc_enuReset_APB2_Peripheral(RCC_APB2Periph_TypeDef Peripheral)
{
    Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
    u32 bitMASK=0;
    switch (Peripheral)
    {
            case RCC_APB2Periph_TIM1:
            case RCC_APB2Periph_USART1:
            case RCC_APB2Periph_USART6:
            case RCC_APB2Periph_ADC1:
            case RCC_APB2Periph_SDIO:
            case RCC_APB2Periph_SPI1:
            case RCC_APB2Periph_SPI4:
            case RCC_APB2Periph_SYSCFG:
            case RCC_APB2Periph_TIM9:
            case RCC_APB2Periph_TIM10:
            case RCC_APB2Periph_TIM11:
                // Valid peripheral, proceed with enabling or disabling
                bitMASK=1<<Peripheral;
                RCC->RCC_APB2RSTR|=bitMASK;
                break;
            default:
                // Invalid peripheral
                Locerrorstatus=Rcc_enuWrongAPB2_WRONG_PERIPHERAL;  
                break; 
    }
    return Locerrorstatus;
}

Rcc_tenuErrorStatus Rcc_enuControl_LOWPOW_MODE_AHB1_Peripheral(RCC_AHB1Periph_TypeDef Peripheral,RCC_Periph_CFG_TypeDef action)
{
        Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
        u32 bitMASK=0;
        switch (Peripheral)
         {
            case RCC_AHB1Periph_GPIOA:
            case RCC_AHB1Periph_GPIOB:
            case RCC_AHB1Periph_GPIOC:
            case RCC_AHB1Periph_GPIOD:
            case RCC_AHB1Periph_GPIOE:
            case RCC_AHB1Periph_GPIOH:
            case RCC_AHB1Periph_FLITF:
            case RCC_AHB1Periph_SRAM1:
            case RCC_AHB1Periph_CRC:
            case RCC_AHB1Periph_DMA1:
            case RCC_AHB1Periph_DMA2:
                // Valid peripheral, proceed with enabling or disabling
                if(action==RCC_Periph_ENABLE)
                {
                    bitMASK=1<<Peripheral;
                    RCC->RCC_AHB1LPENR|=bitMASK;
                }
                else if(action==RCC_Periph_DISABLE)
                {
                    bitMASK=1<<Peripheral;
                    RCC->RCC_AHB1LPENR&=~bitMASK;
                }
                else
                {
                    Locerrorstatus=RCC_enuUnLogicActionError; 
                }

                break;
            default:
                // Invalid peripheral
                Locerrorstatus=Rcc_enuWrongAHB1_WRONG_PERIPHERAL;  
                break; 
    }
    return Locerrorstatus;
}
Rcc_tenuErrorStatus Rcc_enuControl_LOWPOW_MODE_AHB2_Peripheral(RCC_AHB2Periph_TypeDef Peripheral,RCC_Periph_CFG_TypeDef action)
{
    Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
    if(Peripheral==RCC_AHB2Periph_OTGFS)
    {
        if(action==RCC_Periph_ENABLE)
        {
            SET_BIT(RCC->RCC_AHB2LPENR,Peripheral);
        }
        else if(action==RCC_Periph_DISABLE)
        {
            CLR_BIT(RCC->RCC_AHB2LPENR,Peripheral);
        }
        else
        {
           Locerrorstatus=RCC_enuUnLogicActionError;  
        }
    }
    else
    {
        Locerrorstatus=Rcc_enuWrongAHB2_WRONG_PERIPHERAL;
    }
    return Locerrorstatus;
}

Rcc_tenuErrorStatus Rcc_enuControl_LOWPOW_MODE_APB1_Peripheral(RCC_APB1Periph_TypeDef Peripheral,RCC_Periph_CFG_TypeDef action)
{
    Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
        u32 bitMASK=0;
        switch (Peripheral)
         {
            case RCC_APB1Periph_TIM2:
            case RCC_APB1Periph_TIM3:
            case RCC_APB1Periph_TIM4:
            case RCC_APB1Periph_TIM5:
            case RCC_APB1Periph_WWDG:
            case RCC_APB1Periph_SPI2:
            case RCC_APB1Periph_SPI3:
            case RCC_APB1Periph_I2C1:
            case RCC_APB1Periph_I2C2:
            case RCC_APB1Periph_I2C3:
            case RCC_APB1Periph_PWR:
                // Valid peripheral, proceed with enabling or disabling
                if(action==RCC_Periph_ENABLE)
                {
                    bitMASK=1<<Peripheral;
                    RCC->RCC_APB1LPENR|=bitMASK;
                }
                else if(action==RCC_Periph_DISABLE)
                {
                    bitMASK=1<<Peripheral;
                    RCC->RCC_APB1LPENR&=~bitMASK;
                }
                else
                {
                    Locerrorstatus=RCC_enuUnLogicActionError; 
                }

                break;
            default:
                // Invalid peripheral
                Locerrorstatus=Rcc_enuWrongAPB1_WRONG_PERIPHERAL;  
                break; 
    }
    return Locerrorstatus;
}
Rcc_tenuErrorStatus Rcc_enuControl_LOWPOW_MODE_APB2_Peripheral(RCC_APB2Periph_TypeDef Peripheral,RCC_Periph_CFG_TypeDef action)
{
    Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
    u32 bitMASK=0;
    switch (Peripheral)
    {
            case RCC_APB2Periph_TIM1:
            case RCC_APB2Periph_USART1:
            case RCC_APB2Periph_USART6:
            case RCC_APB2Periph_ADC1:
            case RCC_APB2Periph_SDIO:
            case RCC_APB2Periph_SPI1:
            case RCC_APB2Periph_SPI4:
            case RCC_APB2Periph_SYSCFG:
            case RCC_APB2Periph_TIM9:
            case RCC_APB2Periph_TIM10:
            case RCC_APB2Periph_TIM11:
                // Valid peripheral, proceed with enabling or disabling
                if(action==RCC_Periph_ENABLE)
                {
                    bitMASK=1<<Peripheral;
                    RCC->RCC_APB2LPENR|=bitMASK;
                }
                else if(action==RCC_Periph_DISABLE)
                {
                    bitMASK=1<<Peripheral;
                    RCC->RCC_APB2LPENR&=~bitMASK;
                }
                else
                {
                    Locerrorstatus=RCC_enuUnLogicActionError; 
                }

                break;
            default:
                // Invalid peripheral
                Locerrorstatus=Rcc_enuWrongAPB2_WRONG_PERIPHERAL;  
                break; 
    }
    return Locerrorstatus;
}


Rcc_tenuErrorStatus Rcc_enuMCO1_CLOCK_slector(u32 Source)
{   
    Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
    switch(Source)
    {
        case MCO1_CLK_SOURCE_HSI:
        case MCO1_CLK_SOURCE_LSE:
        case MCO1_CLK_SOURCE_HSE:
        case MCO1_CLK_SOURCE_PLL:
        // clear the  two bits respnsibol of slecting the clock source then config them to chose the desired source 
        (RCC->RCC_CFGR)&=(MCO1_CLK_SOURCE_MASK|Source);
        break;
        default:
            // Invalid source
            Locerrorstatus=RCC_enuUnLogicActionError; 
            break;
    }
    return Locerrorstatus;
}
Rcc_tenuErrorStatus Rcc_enuMCO2_CLOCK_slector(u32 Source)
{
    Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
    switch(Source)
    {
        case MCO2_CLK_SOURCE_SYSCLK:
        case MCO2_CLK_SOURCE_PLLI2S:
        case MCO2_CLK_SOURCE_HSE:
        case MCO2_CLK_SOURCE_PLL:
        // clear the  two bits respnsibol of slecting the clock source then config them to chose the desired source 
        (RCC->RCC_CFGR)&=(MCO2_CLK_SOURCE_MASK|Source);
        break;
        default:
            // Invalid source
            Locerrorstatus=RCC_enuUnLogicActionError; 
            break;
    }
    return Locerrorstatus;

}

Rcc_tenuErrorStatus Rcc_enuMCO1_Prescaler(u32 Prescaler)
{
    Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
    switch(Prescaler)
    {
        case RCC_MCO1_NO_DIV_MASK:
        case RCC_MCO1_DIV_2_MASK :
        case RCC_MCO1_DIV_3_MASK :
        case RCC_MCO1_DIV_4_MASK :
        case RCC_MCO1_DIV_5_MASK :

        // clear the  three bits respnsibol of slecting the Prescaler  then config them to chose the desired Prescaler 
        (RCC->RCC_CFGR)&=(MCO1_PRESCALER_MASK|Prescaler);
        break;
        default:
            // Invalid Prescaler
            Locerrorstatus=RCC_enuUnLogicActionError; 
            break;
    }
    return Locerrorstatus;
}
Rcc_tenuErrorStatus Rcc_enuMCO2_Prescaler(u32 Prescaler)
{
    Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
    switch(Prescaler)
    {
        case RCC_MCO2_NO_DIV_MASK:
        case RCC_MCO2_DIV_2_MASK :
        case RCC_MCO2_DIV_3_MASK :
        case RCC_MCO2_DIV_4_MASK :
        case RCC_MCO2_DIV_5_MASK :

        // clear the  three bits respnsibol of slecting the Prescaler  then config them to chose the desired Prescaler 
        (RCC->RCC_CFGR)&=(MCO2_PRESCALER_MASK|Prescaler);
        break;
        default:
            // Invalid Prescaler
            Locerrorstatus=RCC_enuUnLogicActionError; 
            break;
    }
    return Locerrorstatus;    
}



