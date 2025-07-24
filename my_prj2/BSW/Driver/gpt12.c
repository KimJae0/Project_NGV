#include <gpt12.h>
#include <Ifx_reg.h>
#include <Ifx_Types.h>
#include <IfxGpt12.h>
#include <IfxPort.h>
#include "Ifx_Types.h"
#include "IfxGpt12.h"
#include "IfxPort.h"
#include "asclin.h"
#include "isr_priority.h"
#include "GPIO.h"
#include "Buzzer.h"

static volatile unsigned int cntDelay = 0;

IFX_INTERRUPT(IsrGpt2T6Handler, 0, ISR_PRIORITY_GPT2T6_TIMER);
void IsrGpt2T6Handler (void)
{
    cntDelay++;
//    if(cntDelay % 100000 == 0 && cntDelay <= 600000){
//        GPIO_ToggleLed(2);
//        if(cntDelay >= 600000) cntDelay = 0;
//    }
}

void gpt12_Init(void)
{
    IfxScuWdt_clearCpuEndinit(IfxScuWdt_getGlobalEndinitPassword());
    MODULE_GPT120.CLC.U = 0;
    IfxScuWdt_setCpuEndinit(IfxScuWdt_getGlobalEndinitPassword());

    gpt1_init();
    gpt2_init();
}

void runGpt12_T3 (void)
{
    MODULE_GPT120.T3CON.B.T3R = 1;
}

void runGpt12_T6 (void)
{
    MODULE_GPT120.T6CON.B.T6R = 1;
}

void gpt1_init (void)
{
    /* Initialize the Timer T6 for delay_ms */
    /*
     * BPS1(GPT1 Block Prescaler Control) 10 : fgpt/1024
     * T3M(Timer T3 Mode Control) 000 : 타이머 모드
     * T3UD(Timer T3 Up/Down Control) 1 : 카운트 다운
     * T3I(Timer T3 Input Parameter Selection) 101
     * 1 tick = 10.24us
     * 1 tick = 10.24us 이므로, T3 = 3846/10.24 = 375 로 설정하면 130Hz
     */
    MODULE_GPT120.T3CON.B.BPS1 = 0x2; /* Set GPT1 block prescaler: 32 */
    MODULE_GPT120.T3CON.B.T3M = 0x0; /* Set T3 to timer mode */
    MODULE_GPT120.T3CON.B.T3UD = 0x1; /* Set T3 count direction(down) */
    MODULE_GPT120.T3CON.B.T3I = 0x5; /* Set T3 input prescaler(2^5=32) */
    MODULE_GPT120.T3.U = 375u; /* Set T6 start value (10us) */

    /* Calculate dutyUpTime and dutyDownTime for reloading timer T3 */
    /*
     * T2M(Timer T2 Mode Control) 100 : Reload Mode
     * T2I(Timer T2 Input Parameter Selection) 111 : Rising/Falling edge 둘다 트리거
     * → T3의 출력 토글 신호(T3OTL)가 상승 또는 하강할 때마다 리로드 발생
     */
    MODULE_GPT120.T2CON.B.T2M = 0x4; /* Set the timer T2 in reload mode */
    MODULE_GPT120.T2CON.B.T2I = 0x7; /* Reload Input Mode : Rising/Falling Edge T3OTL */
    MODULE_GPT120.T2.U = 375u;

    /* Initialize the interrupt */
    /*
     * SRPN(Service Request Priority Number)
     * TOS(Type of Service) 000 : CPU0
     * CLRR 1 : SRR 클리어
     * SRE(Service Request Enable) 1 : 활성
     */
    volatile Ifx_SRC_SRCR *src;
    src = (volatile Ifx_SRC_SRCR*) (&MODULE_SRC.GPT12.GPT12[0].T3);
    src->B.SRPN = ISR_PRIORITY_GPT1T3_TIMER;
    src->B.TOS = 0;
    src->B.CLRR = 1; /* clear request */
    src->B.SRE = 1; /* interrupt enable */

    runGpt12_T3();
}

void gpt2_init (void)
{
    /* Initialize the Timer T6 for delay_ms */
    /*
     * BPS2(GPT2 Block Prescaler Control) 00 : fgpt/4
     * T6M(Timer T6 Mode Control) 000 : 타이머 모드
     * T6UD(Timer T6 Up/Down Control) 1 : 카운트 다운
     * T6I(Timer T6 Input Parameter Selection) 00 :
     * T6OE(Overflow/Underflow Output Enable) 1 : 토글 래치가 외부 핀 T6OUT으로 출력
     * T6SR(Timer T6 Reload Mode Enable) 1 : CAPREL 레지스터의 값을 타이머에 자동으로 다시 로드하는 기능 활성
     * 250 tick = 10us
     */
    MODULE_GPT120.T6CON.B.BPS2 = 0x0; /* Set GPT2 block prescaler: 4 */
    MODULE_GPT120.T6CON.B.T6M = 0x0; /* Set T6 to timer mode */
    MODULE_GPT120.T6CON.B.T6UD = 0x1; /* Set T6 count direction(down) */
    MODULE_GPT120.T6CON.B.T6I = 0x0; /* Set T6 input prescaler(2^0=1) */
    MODULE_GPT120.T6CON.B.T6OE = 0x1; /* Overflow/Underflow Output Enable */
    MODULE_GPT120.T6CON.B.T6SR = 0x1; /* Reload from register CAPREL Enabled */
    MODULE_GPT120.T6.U = 250u; /* Set T6 start value (10us) */
    MODULE_GPT120.CAPREL.U = 250u; /* Set CAPREL reload value *//* Set CAPREL reload value */

    /* Initialize the interrupt */
    /*
     * SRPN(Service Request Priority Number)
     * TOS(Type of Service) 000 : CPU0
     * CLRR 1 : SRR 클리어
     * SRE(Service Request Enable) 1 : 활성
     */
    volatile Ifx_SRC_SRCR *src;
    src = (volatile Ifx_SRC_SRCR*) (&MODULE_SRC.GPT12.GPT12[0].T6);
    src->B.SRPN = ISR_PRIORITY_GPT2T6_TIMER;
    src->B.TOS = 0;
    src->B.CLRR = 1; /* clear request */
    src->B.SRE = 1; /* interrupt enable */

    runGpt12_T6();
}

void stopGpt12_T3 (void)
{
    MODULE_GPT120.T3CON.B.T3R = 0;
}

void stopGpt12_T6 (void)
{
    MODULE_GPT120.T6CON.B.T6R = 0;
}

void setcntDelay (unsigned int n)
{
    cntDelay = n;
}

unsigned int getcntDelay (void)
{
    return cntDelay;
}
