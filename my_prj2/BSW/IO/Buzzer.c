#include "Ifx_reg.h"
#include "Buzzer.h"
#include "isr_priority.h"
#include "asclin.h"
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "IfxAsclin_reg.h"
#include "IfxAsclin_bf.h"

int beepCnt = 0;
int beepOnOff = 0;

IFX_INTERRUPT(IsrGpt1T3Handler_Beep, 0, ISR_PRIORITY_GPT1T3_TIMER);
//void IsrGpt1T3Handler_Beep(void)
//{
//    MODULE_P02.OUT.B.P3 ^= 1; // 토글
//}

void IsrGpt1T3Handler_Beep(void)
{
    if ((beepCnt < beepOnOff) || (beepOnOff == 1)) {
        MODULE_P02.OUT.B.P3 ^= 1;
    } else if (beepCnt < beepOnOff * 2) {
        MODULE_P02.OUT.B.P3 = 0;
    } else {
        beepCnt = 0;
    }
    beepCnt++;
}

void setBeepCycle(int cycle)
{
    beepOnOff = cycle;
}

void Buzzer_Init(void)
{
    /* Set P02.3 (Buzzer) as a general output pin */
    MODULE_P02.IOCR0.B.PC3 = 0x10;


}

/* Busy wait to generate specific hertz (1 period) */
/**
 * loop: number of instruction
 * CPU frequency: 200Mhz -> 1 cycle takes 5ns
 *
 * <Calculation of loop count>
 * loop = 10^9ns(1s) / Hz / 2(half of 1 period time) / 5ns(1 cycle cpu time) / 2(each for loop takes 2 cycle time)
 */
void Buzzer_Buzz(unsigned int Hz)
{
    /*
     * 기능: 주어진 주파수(Hz)에 따라 부저를 1회 ON/OFF 진동
     * PWM 개념 활용: 주어진 주파수에 해당하는 시간 동안 HIGH → LOW 신호를 1회 출력하여 소리 생성
     * 듀티 비율: 항상 50% 고정
     * / 2 : HIGH/LOW 반반 → 듀티 50%
     * / 5 : for 루프 1회당 약 5ns 가정
     * / 2 : 함수에서 HIGH/LOW 각각 딜레이 적용하므로 또 나눔
     */
    volatile int loop = 1000000000 / Hz / 2 / 5 / 2;
    MODULE_P02.OUT.B.P3 = 1; // 부저 ON (High 출력)
    for (int i = 0; i < loop; i++);
    MODULE_P02.OUT.B.P3 = 0; // 부저 OFF (Low 출력)
    for (int i = 0; i < loop; i++);
}

void Buzzer_Beep(unsigned int Hz, int duration_ms)
{
    float second = (float)duration_ms / 1000.0f;
    volatile unsigned int i = 0, j = Hz * second;
    while (i++ < j) {
        Buzzer_Buzz(Hz);
    }
}
