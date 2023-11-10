/*
 * GPIO.c
 *
 *  Created on: Nov 7, 2023
 *      Author: ahmed radwan
 */
#include"../../SERVICES/Standard_Data_Types.h"
#include"../../SERVICES/Bit_Wise_Operations.h"
#include"GPIO_PRIV.h"
#include"GPIO.h"
#include"GPIO_CFG.h"
#include"../RCC/rcc.h"

static GPIO_t* const portARR[]={GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOH};

GPIO_tenuErrorStatus GPIO_PIN_INIT(GPIO_stInit_t* Locpin)
{
    GPIO_tenuErrorStatus Locerrorstatus=Gpio_enuOk;
    if(NULL==Locpin)
    {
        Locerrorstatus=Gpio_enuNULL_PTR;
    }
    else
    {
        //mode_cfg
        portARR[Locpin->port]->GPIOx_MODER&=(~(CLEAR_2BITMask<<((Locpin->Pin)*2)));//clear the desired two bits
        portARR[Locpin->port]->GPIOx_MODER|=((Locpin->Mode)<<((Locpin->Pin)*2));//set the desired bits
    
        //speed cfg
        portARR[Locpin->port]->GPIOx_OSPEEDER&=(~(CLEAR_2BITMask<<((Locpin->Pin)*2)));//clear the desired two bits
        portARR[Locpin->port]->GPIOx_OSPEEDER|=((Locpin->Speed)<<((Locpin->Pin)*2));//set the desired speed

        //output_cfg
        if(Output==Locpin->Mode)
        {
            if (Output_open_drain == Locpin->outputCfg)
            {
                SET_BIT(portARR[Locpin->port]->GPIOx_OTYPER,Locpin->Pin);//open drain cfg
            }
            else if (push_pull == Locpin->outputCfg)
            {
                CLR_BIT(portARR[Locpin->port]->GPIOx_OTYPER,Locpin->Pin);//pushpull cfg
            }
            else
            {
                /*ERORR*/
                Locerrorstatus=Gpio_enuINVALID_Action;
            }
        }
        //pull-up/pull-down cfg
        portARR[Locpin->port]->GPIOx_PUPDR&=(~(CLEAR_2BITMask<<((Locpin->Pin)*2)));//clear the desired two bits
        portARR[Locpin->port]->GPIOx_PUPDR|=((Locpin->out_in_val)<<((Locpin->Pin)*2));//set the desired speed
    }    

}
GPIO_tenuErrorStatus GPIO_set_PIN_value(GPIO_stInit_t* Locpin,GPIO_enuLogic_t Locu8value)
{
    GPIO_tenuErrorStatus Locerrorstatus=Gpio_enuOk;
    if(NULL==Locpin)
    {
        Locerrorstatus=Gpio_enuNULL_PTR;
    }
    else
    {
        switch(Locu8value)
        {
            case GPIO_LOGIC_LOW:
            case GPIO_LOGIC_HIGH:
                CLR_BIT(portARR[Locpin->port]->GPIOx_ODR,Locpin->Pin);
                 portARR[Locpin->port]->GPIOx_ODR|=(Locu8value<<(Locpin->Pin));
            default: 
            Locerrorstatus=Gpio_enuINVALID_LOGIC;       
        } 
    }
    return Locerrorstatus;
}
GPIO_tenuErrorStatus GPIO_get_PIN_value(GPIO_stInit_t* Locpin,u32* Locu8value)
{
    GPIO_tenuErrorStatus Locerrorstatus=Gpio_enuOk;
    if((NULL==Locpin)||(NULL==Locu8value))
    {
        Locerrorstatus=Gpio_enuNULL_PTR;
    }
    else
    {
        *Locu8value=portARR[Locpin->port]->GPIOx_IDR;
        *Locu8value&=(*Locu8value&(1<<(Locpin->Pin)))>>(Locpin->Pin);
    }
    return Locerrorstatus;
}
GPIO_tenuErrorStatus GPIO_set_Alternate(GPIO_stInit_t* Locpin)
{
    GPIO_tenuErrorStatus Locerrorstatus=Gpio_enuOk;
    if(NULL==Locpin)
    {
        Locerrorstatus=Gpio_enuNULL_PTR;
    }
    else
    {
        if (Locpin->Pin<8)
        {
            portARR[Locpin->port]->GPIOx_AFRL&=(~(CLEAR_4BITMask<<((Locpin->Pin)*4)));//clear the desired four bits
            portARR[Locpin->port]->GPIOx_AFRL|=((Locpin->Alternate)<<((Locpin->Pin)*4));//set the desired bits
        }
        else
        {
            portARR[Locpin->port]->GPIOx_AFRL&=(~(CLEAR_4BITMask<<((Locpin->Pin-8)*4)));//clear the desired four bits
            portARR[Locpin->port]->GPIOx_AFRL|=((Locpin->Alternate)<<((Locpin->Pin-8)*4));//set the desired bits
        }
    }
    return Locerrorstatus;
}
GPIO_tenuErrorStatus GPIO_Port_Enable_clock(GPIO_enuPORT_NO_t port)
{
    Rcc_enuControl_AHB1_Peripheral(port,RCC_Periph_ENABLE);

}
GPIO_tenuErrorStatus GPIO_Port_Disable_clock(GPIO_enuPORT_NO_t port)
{
    Rcc_enuControl_AHB1_Peripheral(port,RCC_Periph_DISABLE);
}
GPIO_tenuErrorStatus GPIO_togel_PIN(GPIO_stInit_t* Locpin)
{
    GPIO_tenuErrorStatus Locerrorstatus=Gpio_enuOk;
    if(NULL==Locpin)
    {
        Locerrorstatus=Gpio_enuNULL_PTR;
    }
    else
    {
        (portARR[Locpin->port]->GPIOx_ODR)^=(1<<(Locpin->Pin));
    }
    return Locerrorstatus;
}
void GPIO_PIN_INIT_FULL(void)
{

}

