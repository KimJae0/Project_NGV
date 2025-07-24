#include "GPIO.h"
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"

void GPIO_Init (void)
{
    // 10번 포트, 2번 핀 = LED1 = 파란색
    MODULE_P10.IOCR0.B.PC2 = 0x10; // 0001 0000
    // 10번 포트, 1번 핀 = LED2 = 빨간색
    MODULE_P10.IOCR0.B.PC1 = 0x10; // 0001 0000

    // 2번 포트, 0번 핀 = SW1
    MODULE_P02.IOCR0.B.PC0 = 0x02; // 0000 0010
    // 2번 포트, 1번 핀 = SW2
    MODULE_P02.IOCR0.B.PC1 = 0x02; // 0000 0010
}

void GPIO_SetLed (unsigned char num_LED, unsigned char on)
{
    on = !!(on);
    if (num_LED == 1)
    {
        MODULE_P10.OUT.B.P2 = on; // 파란색 LED1 ON
    }
    else if (num_LED == 2)
    {
        MODULE_P10.OUT.B.P1 = on; // 빨간색 LED2 ON
    }
}

void GPIO_ToggleLed (unsigned char num_LED)
{
    if (num_LED == 1)
    {
        MODULE_P02.OUT.B.P1 ^= 1;
    }
    else
    {
        MODULE_P02.OUT.B.P2 ^= 1;
    }
}

int GPIO_getSW1 (void)
{
    if (MODULE_P02.IN.B.P0 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int GPIO_getSW2 (void)
{
    if (MODULE_P02.IN.B.P1 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
