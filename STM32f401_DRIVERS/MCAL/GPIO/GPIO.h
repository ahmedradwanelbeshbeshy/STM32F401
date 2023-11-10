/*
 * GPIO.h
 *
 *  Created on: Nov 7, 2023
 *      Author: ahmed radwan
 */
#ifndef MCAL_GPIO_H_
#define MCAL_GPIO_H_

#include"../../SERVICES/Standard_Data_Types.h"
#include"../../SERVICES/Bit_Wise_Operations.h"

#define PORTA_RESET_VAL         (0x0C000000)
#define PORTB_RESET_VAL         (0x00000280)
#define ALLPORTS_RESET_VAL      (0x00000000)
#define CLEAR_1BITMask          (0x00000001)
#define CLEAR_2BITMask          (0x00000003)
#define CLEAR_4BITMask          (0x0000000f)


#define GPIOA       ((GPIO_t*)(GPIOA_BASE_ADREES))
#define GPIOB       ((GPIO_t*)(GPIOB_BASE_ADREES))
#define GPIOC       ((GPIO_t*)(GPIOC_BASE_ADREES))
#define GPIOD       ((GPIO_t*)(GPIOD_BASE_ADREES))
#define GPIOE       ((GPIO_t*)(GPIOE_BASE_ADREES))
#define GPIOH       ((GPIO_t*)(GPIOH_BASE_ADREES))


typedef enum {
    GPIO_PIN_0,
    GPIO_PIN_1,
    GPIO_PIN_2,
    GPIO_PIN_3,
    GPIO_PIN_4,
    GPIO_PIN_5,
    GPIO_PIN_6,
    GPIO_PIN_7,
    GPIO_PIN_8,
    GPIO_PIN_9,
    GPIO_PIN_10,
    GPIO_PIN_11,
    GPIO_PIN_12,
    GPIO_PIN_13,
    GPIO_PIN_14,
    GPIO_PIN_16
}GPIO_enuPIN_NO_t;

typedef enum {
     GPIO_PORT_A,
     GPIO_PORT_B,
     GPIO_PORT_C,
     GPIO_PORT_D,
     GPIO_PORT_E,
     GPIO_PORT_H=7,
}GPIO_enuPORT_NO_t;

typedef enum { //moder reg
     Input,
     Output,
     Alternate_fn,
     Analog_mod
}GPIO_enuMode_t;

typedef enum {
    push_pull,
    Output_open_drain 
}GPIO_enuOutput_t;
typedef enum {
    NO_pull_UP_Down,
    pull_UP,
    pull_Down 
}GPIO_enuintval_t ;

typedef enum {
     Lowspeed,
     Mediumspeed,
     High_speed,
     Very_high_speed
}GPIO_enuSpeed_t;

typedef enum {
     AF_0,
     AF_1,
     AF_2,
     AF_3,
     AF_4,
     AF_5,
     AF_6,
     AF_7,
     AF_8,
     AF_9,
     AF_10,
     AF_11,
     AF_12,
     AF_13,
     AF_14,
     AF_15
}GPIO_enuAF_t;

typedef enum {
   GPIO_LOGIC_LOW,
   GPIO_LOGIC_HIGH
}GPIO_enuLogic_t;
typedef struct
{
  GPIO_enuPIN_NO_t Pin; 
  GPIO_enuPORT_NO_t port;      
  GPIO_enuMode_t  Mode;      
  GPIO_enuOutput_t outputCfg; 
  GPIO_enuintval_t out_in_val;    
  GPIO_enuSpeed_t Speed;                     
  GPIO_enuAF_t Alternate; 
}GPIO_stInit_t;

typedef struct{
	volatile u32 GPIOx_MODER;
	volatile u32 GPIOx_OTYPER;
	volatile u32 GPIOx_OSPEEDER;
	volatile u32 GPIOx_PUPDR;
	volatile u32 GPIOx_IDR;
	volatile u32 GPIOx_ODR;
	volatile u32 GPIOx_BSRR;
	volatile u32 GPIOx_LCKR;
	volatile u32 GPIOx_AFRL;
	volatile u32 GPIOx_AFRH;
} GPIO_t ;

typedef enum{
     Gpio_enuOk,
     Gpio_enuNULL_PTR,
     Gpio_enuINVALID_LOGIC,
     Gpio_enuINVALID_PORT,
     Gpio_enuINVALID_Action
} GPIO_tenuErrorStatus;
GPIO_tenuErrorStatus GPIO_PIN_INIT(GPIO_stInit_t* Locpin);
GPIO_tenuErrorStatus GPIO_set_PIN_value(GPIO_stInit_t* Locpin,GPIO_enuLogic_t Locu8value);
GPIO_tenuErrorStatus GPIO_togel_PIN(GPIO_stInit_t* Locpin);
GPIO_tenuErrorStatus GPIO_get_PIN_value(GPIO_stInit_t* Locpin,u32* Locu8value);
GPIO_tenuErrorStatus GPIO_set_Alternate(GPIO_stInit_t* Locpin);
GPIO_tenuErrorStatus GPIO_Port_Enable_clock(GPIO_enuPORT_NO_t port);
GPIO_tenuErrorStatus GPIO_Port_Disable_clock(GPIO_enuPORT_NO_t port);


#endif // MCAL_GPIO_H_

