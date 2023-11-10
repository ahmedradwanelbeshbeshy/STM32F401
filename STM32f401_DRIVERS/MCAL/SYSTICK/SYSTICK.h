#ifndef MCAL_SYSTICK_H_
#define MCAL_SYSTICK_H_

#include "../../SERVICES/Standard_Data_Types.h"
#include "../../SERVICES/Bit_Wise_Operations.h"
#include"SYSTICK_PRIV.h"




#define SYSTICK_GET_FLAG()                       GET_BIT(STK_CTRL,16)
#define SYSTICK_ENABLE()                         SET_BIT(STK_CTRL,0)
#define SYSTICK_DISABLE()                        CLR_BIT(STK_CTRL,0)

#define SYSTICK_ENABLE_EXCEPTION()               SET_BIT(STK_CTRL,1)
#define SYSTICK_DISABLE_EXCEPTION()              CLR_BIT(STK_CTRL,1)

#define SYSTICK_PROCESSOR_CLOOCK_SLECT()         SET_BIT(STK_CTRL,2)
#define SYSTICK_PROCESSOR_CLOOCK_DIV8_SLECT()    CLR_BIT(STK_CTRL,2)

 #define SSYSTICK_CLOCK_PROCESSOR 1
 #define SSYSTICK_CLOCK_DIV_8 0

void SYSTICK_INIT(u32 preload);
void SYSTICK_START(void);
void SYSTICK_STOP(void);
void SYSTICK_EXCEPTION_ENABLE(void);
void SYSTICK_EXCEPTION_DISABLE(void);
void SysTick_CALLBACK_ASSIGN(CALL_BACK_FN_TYPE Ptrcall_back_FN);


#endif //MCAL_SYSTICK_H_
