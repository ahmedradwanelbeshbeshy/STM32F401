/*
 * GPIO_CFG.h
 *
 *  Created on: Nov 7, 2023
 *      Author: ahmed radwan
 */
#ifndef MCAL_GPIO_CFG_H_
#define MCAL_GPIO_CFG_H_

// mode_cfg
#define _MODE_INPUT_CFG    0
#define _MODE_OUTPUT_CFG   1
#define _MODE_ALTFN_CFG    2
#define _MODE_ANALOG_CFG   3
// PINCFG
#define    _PUSH_PULL_CFG  0
#define    _OPEN_DRAIN_CFG 1
//PUUL_UP or PULLDOWN
#define    _NO_PULL_UP_DOWN_CFG
#define    _PULL_UP_CFG
#define    _PULL_DOWN_CFG
//speed_cfg 

/**********************************************************
 *********************options******************************

 *   mode_cfg         |   speed_cfg   |      PIN_CFG   | PUUL_UP or PULLDOWN
 * ------------------------------------------------------------------------------ 
 *   _MODE_INPUT_CFG  |               | _PUSH_PULL_CFG  | _NO_PULL_UP_DOWN_CFG
 *   _MODE_ALTFN_CFG  |               | _OPEN_DRAIN_CFG | _PULL_UP_CFG
 *   _MODE_ANALOG_CFG |               |                 | _PULL_DOWN_CFG
 * 
 * *********************************************************
*/

/************************** PORTA ************************/
#define PORTA_PIN_0
#define PORTA_PIN_1
#define PORTA_PIN_2
#define PORTA_PIN_3
#define PORTA_PIN_4
#define PORTA_PIN_5
#define PORTA_PIN_6
#define PORTA_PIN_7
#define PORTA_PIN_8
#define PORTA_PIN_9
#define PORTA_PIN_10
#define PORTA_PIN_11
#define PORTA_PIN_12
#define PORTA_PIN_13
#define PORTA_PIN_14
#define PORTA_PIN_15

/************************** PORTB ************************/
#define PORTB_PIN_0
#define PORTB_PIN_1
#define PORTB_PIN_2
#define PORTB_PIN_3
#define PORTB_PIN_4
#define PORTB_PIN_5
#define PORTB_PIN_6
#define PORTB_PIN_7
#define PORTB_PIN_8
#define PORTB_PIN_9
#define PORTB_PIN_10
#define PORTB_PIN_11
#define PORTB_PIN_12
#define PORTB_PIN_13
#define PORTB_PIN_14
#define PORTB_PIN_15

/************************** PORTAC ************************/
#define PORTC_PIN_0
#define PORTC_PIN_1
#define PORTC_PIN_2
#define PORTC_PIN_3
#define PORTC_PIN_4
#define PORTC_PIN_5
#define PORTC_PIN_6
#define PORTC_PIN_7
#define PORTC_PIN_8
#define PORTC_PIN_9
#define PORTC_PIN_10
#define PORTC_PIN_11
#define PORTC_PIN_12
#define PORTC_PIN_13
#define PORTC_PIN_14
#define PORTC_PIN_15
/************************** PORTD ************************/
#define PORTD_PIN_0
#define PORTD_PIN_1
#define PORTD_PIN_2
#define PORTD_PIN_3
#define PORTD_PIN_4
#define PORTD_PIN_5
#define PORTD_PIN_6
#define PORTD_PIN_7
#define PORTD_PIN_8
#define PORTD_PIN_9
#define PORTD_PIN_10
#define PORTD_PIN_11
#define PORTD_PIN_12
#define PORTD_PIN_13
#define PORTD_PIN_14
#define PORTD_PIN_15

/************************** PORTE ************************/
#define PORTE_PIN_0
#define PORTE_PIN_1
#define PORTE_PIN_2
#define PORTE_PIN_3
#define PORTE_PIN_4
#define PORTE_PIN_5
#define PORTE_PIN_6
#define PORTE_PIN_7
#define PORTE_PIN_8
#define PORTE_PIN_9
#define PORTE_PIN_10
#define PORTE_PIN_11
#define PORTE_PIN_12
#define PORTE_PIN_13
#define PORTE_PIN_14
#define PORTE_PIN_15

/************************** PORTH ************************/
#define PORTH_PIN_0
#define PORTH_PIN_1
#define PORTH_PIN_2
#define PORTH_PIN_3
#define PORTH_PIN_4
#define PORTH_PIN_5
#define PORTH_PIN_6
#define PORTH_PIN_7
#define PORTH_PIN_8
#define PORTH_PIN_9
#define PORTH_PIN_10
#define PORTH_PIN_11
#define PORTH_PIN_12
#define PORTH_PIN_13
#define PORTH_PIN_14
#define PORTH_PIN_15
#endif // MCAL_GPIO_CFG_H_
