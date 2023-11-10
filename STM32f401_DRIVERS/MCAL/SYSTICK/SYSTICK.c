#include"../../SERVICES/Standard_Data_Types.h"
#include"../../SERVICES/Bit_Wise_Operations.h"
#include"SYSTICK_PRIV.h"
#include"SYSTICK.h"
#include"SYSTICK_CFG.h"

static CALL_BACK_FN_TYPE SYSTICK_ISR=NULL;
extern u32 STM_SYS_FREQ;


void SYSTICK_INIT(u32 Preload_value)
{
    // set the preload value
    STK_LOAD=Preload_value;
    //Chose the clock source for SYSTICK
    if (SYSTICK_CLOCK_SOURCE==SSYSTICK_CLOCK_PROCESSOR)
    {
        //PROCESSOR CLOOCK chosen (AHB)
        SYSTICK_PROCESSOR_CLOOCK_SLECT();
    }
    else if(SYSTICK_CLOCK_SOURCE==SSYSTICK_CLOCK_DIV_8)
    {
        //PROCESSOR CLOOCK div on 8 chosen (AHB/8)
        SYSTICK_PROCESSOR_CLOOCK_DIV8_SLECT();
    }
    
    //SYSTICK ENABLE
    SYSTICK_ENABLE();
}
void SYSTICK_EXCEPTION_ENABLE(void)
{
    SYSTICK_ENABLE_EXCEPTION();
}
void SYSTICK_EXCEPTION_DISABLE(void)
{
    SYSTICK_DISABLE_EXCEPTION();
}
void SYSTICK_START(void)
{
    SYSTICK_ENABLE();
}
void SYSTICK_STOP(void)
{
    SYSTICK_DISABLE();
}
void SysTick_CALLBACK_ASSIGN(CALL_BACK_FN_TYPE Ptrcall_back_FN)
{
    SYSTICK_ISR=Ptrcall_back_FN;
}
void SysTick_Handler(void)
{
    SYSTICK_ISR();
}
