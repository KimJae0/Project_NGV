#include "main.h"

void SYSTEM_Init(void)
{
    IfxCpu_enableInterrupts();
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());

    GPIO_Init();
    Asclin0_InitUart();
//    scueru_Init();
//    gpt12_Init();
//    Buzzer_Init();
//    Ultrasonics_Init();
    Bluetooth_Init();
//    Evadc_Init();
//    GtmAtomPwm_Init();
    Motor_Init();
//    Can_Init(BD_500K, CAN_NODE0);
//    CanFd_Init(BD_500K, HS_BD_2M, CANFD_NODE2);
}
