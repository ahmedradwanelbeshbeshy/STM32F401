/*
 * rcc.h
 *
 *  Created on: Nov 6, 2023
 *      Author: ahmed radwan
 */
#ifndef MCAL_RCC_RCC_H_
#define MCAL_RCC_RCC_H_
//////////////////////GUARD FILE///////////////////////////////////////////
#include"../../SERVICES/Standard_Data_Types.h"
#include"../../SERVICES/Bit_Wise_Operations.h"

#define EXTERNAL_FREQ 8000000

/* ERROR STATUS ENUM */
typedef enum
{
	Rcc_enuOk,
	Rcc_enuTimeOutError,
	RCC_enuUnLogicActionError,
	RCC_enuNullPointerError,
	RCC_enuInvalid_M_Error,
	RCC_enuInvalid_N_Error,
	RCC_enuInvalid_P_Error,
	RCC_enuInvalid_ScrPll_Error,
	RCC_enuInvalid_Q_Error,
	RCC_enuPll_IS_On_Error,
	Rcc_enuWrongAHB_PrescalerError,
	Rcc_enuWrongAPB1_PrescalerError,
	Rcc_enuWrongAPB2_PrescalerError,
	Rcc_enuWrongAHB1_WRONG_PERIPHERAL,
	Rcc_enuWrongAHB2_WRONG_PERIPHERAL,
	Rcc_enuWrongAPB1_WRONG_PERIPHERAL,
	Rcc_enuWrongAPB2_WRONG_PERIPHERAL
} Rcc_tenuErrorStatus;


// Enumeration for AHB1 peripherals
typedef enum {
    RCC_AHB1Periph_GPIOA = 0,
    RCC_AHB1Periph_GPIOB,
    RCC_AHB1Periph_GPIOC,
    RCC_AHB1Periph_GPIOD,
    RCC_AHB1Periph_GPIOE,
	// Bits 5-6 are reserved
    RCC_AHB1Periph_GPIOH =7,
	// Bits 8-11 are reserved
    RCC_AHB1Periph_CRC = 12,
	// Bits 13-14 are reserved
    //the following two bits used only in low power mode in RCC_AHB1LPENR reg
    RCC_AHB1Periph_FLITF = 15,
    RCC_AHB1Periph_SRAM1 = 16,
    // Bits 17-20 are reserved
    RCC_AHB1Periph_DMA1 = 21,
    RCC_AHB1Periph_DMA2 = 22,
	// Bits 23-31 are reserved
} RCC_AHB1Periph_TypeDef;


// Enumeration for AHB2 peripherals
typedef enum {
    RCC_AHB2Periph_OTGFS = 7, // Bit 7 OTGFSEN: USB OTG FS clock enable
} RCC_AHB2Periph_TypeDef;



// Enumeration for APB1 peripherals
typedef enum {
    RCC_APB1Periph_TIM2 = 0, // Bit 0 TIM2EN: TIM2 clock enable
    RCC_APB1Periph_TIM3,     // Bit 1 TIM3EN: TIM3 clock enable
    RCC_APB1Periph_TIM4,     // Bit 2 TIM4EN: TIM4 clock enable
    RCC_APB1Periph_TIM5,     // Bit 3 TIM5EN: TIM5 clock enable
    // Bits 4-10 are reserved
    RCC_APB1Periph_WWDG = 11, // Bit 11 WWDGEN: Window watchdog clock enable
    // Bits 12-13 are reserved
    RCC_APB1Periph_SPI2 = 14, // Bit 14 SPI2EN: SPI2 clock enable
    RCC_APB1Periph_SPI3,      // Bit 15 SPI3EN: SPI3 clock enable
    // Bit 16 is reserved
    RCC_APB1Periph_USART2 = 17, // Bit 17 USART2EN: USART2 clock enable
    // Bits 18-20 are reserved
    RCC_APB1Periph_I2C1 = 21, // Bit 21 I2C1EN: I2C1 clock enable
    RCC_APB1Periph_I2C2,      // Bit 22 I2C2EN: I2C2 clock enable
    RCC_APB1Periph_I2C3,      // Bit 23 I2C3EN: I2C3 clock enable
    // Bits 24-27 are reserved
    RCC_APB1Periph_PWR = 28,  // Bit 28 PWREN: Power interface clock enable
    // Bits 29-31 are reserved
} RCC_APB1Periph_TypeDef;



// Enumeration for APB2 peripherals
typedef enum {
    RCC_APB2Periph_TIM1 = 0, // Bit 0 TIM1EN: TIM1 clock enable
    // Bits 1-3 are reserved
    RCC_APB2Periph_USART1 = 4, // Bit 4 USART1EN: USART1 clock enable
    RCC_APB2Periph_USART6,     // Bit 5 USART6EN: USART6 clock enable
    // Bit 6 is reserved
    RCC_APB2Periph_ADC1 = 8,   // Bit 8 ADC1EN: ADC1 clock enable
    // Bits 9-10 are reserved
    RCC_APB2Periph_SDIO = 11, // Bit 11 SDIOEN: SDIO clock enable
    RCC_APB2Periph_SPI1,  	  // Bit 12 SPI1EN: SPI1 clock enable
    RCC_APB2Periph_SPI4,      // Bit 13 SPI1EN: SPI4 clock enable
    RCC_APB2Periph_SYSCFG,    // Bit 14 SYSCFGEN: System configuration controller clock enable
    // Bit 15 is reserved
    RCC_APB2Periph_TIM9 = 16,   // Bit 16 TIM9EN: TIM9 clock enable
    RCC_APB2Periph_TIM10,       // Bit 17 TIM10EN: TIM10 clock enable
    RCC_APB2Periph_TIM11,       // Bit 18 TIM11EN: TIM11 clock enable
    // Bits 19-31 are reserved
} RCC_APB2Periph_TypeDef;

typedef enum {
    RCC_Periph_DISABLE,
	RCC_Periph_ENABLE,
} RCC_Periph_CFG_TypeDef;

typedef enum {
    RCC_MCO1_HSI,
	RCC_MCO1_LSE,
    RCC_MCO1_HSE,
    RCC_MCO1_PLL
} RCC_MCO1_Source_TypeDef;
typedef enum {
    RCC_MCO2_SYS_CLOCK,
	RCC_MCO2_PLLI2S,
    RCC_MCO2_HSE,
    RCC_MCO2_PLL
} RCC_MCO2_Source_TypeDef;
typedef enum {

    RCC_MCO_DIV_5} RCC_MCO_Prescaler_TypeDef;


/////////////////////////////////////////////////////////////////
/* SYSCLK OPTIONS AND INPUT PARAMETERS FOR Rcc_enuSelectSysCLk */

#define RCC_CLK_HSI 	0x00000000		//ALSO USED IN Rcc_enuCheckCLk
#define RCC_CLK_HSE 	0x00000001		//ALSO USED IN Rcc_enuCheckCLk
#define RCC_CLK_PLL 	0x00000002		//ALSO USED IN Rcc_enuCheckCLk

//chose if you need the old clock to stay enable or disabled
#define RCC_STATE_PRESERVE 		0
#define RCC_STATE_NOTPRESERVE 	1
/*CONTROL EACH CLK BY SELECTING THREE FROM THOSE INPUT PARAMETERS FOR Rcc_enuControlCLk*/
#define RCC_CNTROL_HSION 	3
#define RCC_CNTROL_HSIOFF	4
#define RCC_CNTROL_HSEON	5
#define RCC_CNTROL_HSEOFF	6
#define RCC_CNTROL_PLLON	7
#define RCC_CNTROL_PLLOFF	8
///////////////////////////////////////////////////////////////////////////////////////

//////VALUES OF THE CREATED VALUE FOR CHECKING READY OR NOT IN  Rcc_enuCheckCLk/////////
#define RCC_STATE_NOTREADY  	0
#define RCC_STATE_READY  		1

//////////////////////////////INPUTS FOR Rcc_enuCnfgrPll////////////////////////////////

/*PLLP INPUTS*/
#define RCC_PLLP_DIVBY_2        0
#define RCC_PLLP_DIVBY_4        1
#define RCC_PLLP_DIVBY_6        2
#define RCC_PLLP_DIVBY_8        3

/*SRCPLL INPUTS*/
#define RCC_PLLSRC_HSI			0
#define RCC_PLLSRC_HSE			1

/*PLLQ INPUTS*/
#define RCC_Q_DIVBY_2 			2
#define RCC_Q_DIVBY_3 			3
#define RCC_Q_DIVBY_4 			4
#define RCC_Q_DIVBY_5 			5
#define RCC_Q_DIVBY_6 			6
#define RCC_Q_DIVBY_7 			7
#define RCC_Q_DIVBY_8 			8
#define RCC_Q_DIVBY_9 			9
#define RCC_Q_DIVBY_10 			10
#define RCC_Q_DIVBY_11			11
#define RCC_Q_DIVBY_12			12
#define RCC_Q_DIVBY_13			13
#define RCC_Q_DIVBY_14			14
#define RCC_Q_DIVBY_15			15

///////////////////////INPUTS FOR Rcc_enuCfgBusPrescalers///////////////////////////////////


/*PPRE2 OPTIONS*/
#define RCC_APB2_NOTDIV  0xFFFF1FFF
#define RCC_APB2_DIV2    0x8000
#define RCC_APB2_DIV4    0xA000
#define RCC_APB2_DIV8    0xC000
#define RCC_APB2_DIV16   0xE000

/*PPRE1 OPTIONS*/
#define RCC_APB1_NOTDIV  0xFFFFE3FF
#define RCC_APB1_DIV2    0x1000
#define RCC_APB1_DIV4    0x1400
#define RCC_APB1_DIV8    0x1800
#define RCC_APB1_DIV16   0x1C00

/*HPRE OPTIONS*/
#define RCC_AHB_NOTDIV  0xFFFFFF0F
#define RCC_AHB_DIV2    0x80
#define RCC_AHB_DIV4    0x90
#define RCC_AHB_DIV8    0xA0
#define RCC_AHB_DIV16   0xB0
#define RCC_AHB_DIV64   0xC0
#define RCC_AHB_DIV128  0xD0
#define RCC_AHB_DIV256  0xE0
#define RCC_AHB_DIV512  0xF0

//used in slection the clock output source and prescaler

#define MCO1_CLK_SOURCE_MASK     0xFF9FFFFF
#define MCO2_CLK_SOURCE_MASK     0x3FFFFFFF

#define MCO1_CLK_SOURCE_HSI      0x00000000
#define MCO1_CLK_SOURCE_LSE      0x00200000
#define MCO1_CLK_SOURCE_HSE      0x00400000
#define MCO1_CLK_SOURCE_PLL      0x00600000

#define MCO2_CLK_SOURCE_SYSCLK   0x00000000
#define MCO2_CLK_SOURCE_PLLI2S   0x40000000
#define MCO2_CLK_SOURCE_HSE      0x80000000
#define MCO2_CLK_SOURCE_PLL      0xC0000000

#define MCO1_PRESCALER_MASK 0xF8FFFFFF
#define MCO2_PRESCALER_MASK 0xC7FFFFFF

#define     RCC_MCO1_NO_DIV_MASK   0xF8FFFFFF
#define	    RCC_MCO1_DIV_2_MASK    0xFCFFFFFF
#define     RCC_MCO1_DIV_3_MASK    0xFDFFFFFF
#define     RCC_MCO1_DIV_4_MASK    0xFEFFFFFF
#define     RCC_MCO1_DIV_5_MASK    0xFFFFFFFF

#define     RCC_MCO2_NO_DIV_MASK   0xC7FFFFFF
#define	    RCC_MCO2_DIV_2_MASK    0xEFFFFFFF
#define     RCC_MCO2_DIV_3_MASK    0xE7FFFFFF
#define     RCC_MCO2_DIV_4_MASK    0xF7FFFFFF 
#define     RCC_MCO2_DIV_5_MASK    0xFFFFFFFF

///////////////////////////////////////*FUNCTIONS*///////////////////////////////////////////

Rcc_tenuErrorStatus Rcc_enuSelectSysCLk(u8 Copy_u8SysClk , u8 Copy_u8OldSysClk) ;

Rcc_tenuErrorStatus Rcc_enuControlCLk(u8 Copy_u8ControlHSI  ,u8 Copy_u8ControlHSE ,u8 Copy_u8ControlPLL) ;

Rcc_tenuErrorStatus Rcc_enuCheckCLk(u8 Copy_u8CLk, pu8 Add_pu8RdyStatus) ;

Rcc_tenuErrorStatus Rcc_enuCfg_Pll(u8 Copy_u8Q , u8 Copy_u8SrcPll , u8 Copy_u8P , u16 Copy_u16N,u8 COPY_u8M);

Rcc_tenuErrorStatus Rcc_enuGET_SYS_CLOCK(pu8 ADD_pu8SYSclocK);

/*******************************config buss prescaller*************************/
Rcc_tenuErrorStatus Rcc_enuCfg_AHB_BusPrescalers(u32 Copy_u32Prescaler);

Rcc_tenuErrorStatus Rcc_enuCfg_APB1_BusPrescalers(u32 Copy_u32Prescaler);

Rcc_tenuErrorStatus Rcc_enuCfg_APB2_BusPrescalers(u32 Copy_u32Prescaler);

/** enable OR disabled clock for the input Peripheral depending on action parameter**/
Rcc_tenuErrorStatus Rcc_enuControl_AHB1_Peripheral(RCC_AHB1Periph_TypeDef Peripheral,RCC_Periph_CFG_TypeDef action);
Rcc_tenuErrorStatus Rcc_enuControl_AHB2_Peripheral(RCC_AHB2Periph_TypeDef Peripheral,RCC_Periph_CFG_TypeDef action);

Rcc_tenuErrorStatus Rcc_enuControl_APB1_Peripheral(RCC_APB1Periph_TypeDef Peripheral,RCC_Periph_CFG_TypeDef action);
Rcc_tenuErrorStatus Rcc_enuControl_APB2_Peripheral(RCC_APB2Periph_TypeDef Peripheral,RCC_Periph_CFG_TypeDef action);


/** reset for the input Peripheral **/

Rcc_tenuErrorStatus Rcc_enuReset_AHB1_Peripheral(RCC_AHB1Periph_TypeDef Peripheral);

Rcc_tenuErrorStatus Rcc_enuReset_AHB2_Peripheral(RCC_AHB2Periph_TypeDef Peripheral);

Rcc_tenuErrorStatus Rcc_enuReset_APB1_Peripheral(RCC_APB1Periph_TypeDef Peripheral);

Rcc_tenuErrorStatus Rcc_enuReset_APB2_Peripheral(RCC_APB2Periph_TypeDef Peripheral);

/** enable OR disabled clock in low power mode for the input Peripheral depending on action parameter**/
Rcc_tenuErrorStatus Rcc_enuControl_LOWPOW_MODE_AHB1_Peripheral(RCC_AHB1Periph_TypeDef Peripheral,RCC_Periph_CFG_TypeDef action);
Rcc_tenuErrorStatus Rcc_enuControl_LOWPOW_MODE_AHB2_Peripheral(RCC_AHB2Periph_TypeDef Peripheral,RCC_Periph_CFG_TypeDef action);

Rcc_tenuErrorStatus Rcc_enuControl_LOWPOW_MODE_APB1_Peripheral(RCC_APB1Periph_TypeDef Peripheral,RCC_Periph_CFG_TypeDef action);
Rcc_tenuErrorStatus Rcc_enuControl_LOWPOW_MODE_APB2_Peripheral(RCC_APB2Periph_TypeDef Peripheral,RCC_Periph_CFG_TypeDef action);


/* chose CLOCK source for the MCO1 
*  input options: 
*     MCO1_CLK_SOURCE_HSI
*     MCO1_CLK_SOURCE_LSE
*     MCO1_CLK_SOURCE_HSE
*     MCO1_CLK_SOURCE_PLL 
*/
Rcc_tenuErrorStatus Rcc_enuMCO1_CLOCK_slector(u32 Source);
/* chose CLOCK source for the MCO2
*  input options: 
*     MCO2_CLK_SOURCE_SYSCLK
*     MCO2_CLK_SOURCE_PLLI2S
*     MCO2_CLK_SOURCE_HSE   
*     MCO2_CLK_SOURCE_PLL   
*/
Rcc_tenuErrorStatus Rcc_enuMCO2_CLOCK_slector(u32 Source);

/* chose Prescaler for the MCO2
*  input options:
*       RCC_MCO1_NO_DIV_MASK 
*       RCC_MCO1_DIV_2_MASK  
*       RCC_MCO1_DIV_3_MASK  
*       RCC_MCO1_DIV_4_MASK  
*       RCC_MCO1_DIV_5_MASK  
*/
Rcc_tenuErrorStatus Rcc_enuMCO1_Prescaler(u32 Prescaler);

/* chose Prescaler for the MCO2
*  input options:
*       RCC_MCO2_NO_DIV_MASK 
*       RCC_MCO2_DIV_2_MASK  
*       RCC_MCO2_DIV_3_MASK  
*       RCC_MCO2_DIV_4_MASK  
*       RCC_MCO2_DIV_5_MASK  
*/
Rcc_tenuErrorStatus Rcc_enuMCO2_Prescaler(u32 Prescaler);


#endif //MCAL_RCC_RCC_H
