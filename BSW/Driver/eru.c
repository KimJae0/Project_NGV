#include "IfxScuWdt.h"
#include "IfxSrc_regdef.h"
#include "IfxPort_reg.h"
#include "isr_priority.h"
#include "IfxSrc_reg.h"

IFX_INTERRUPT(SCUERU_Int0_Handler, 0, ISR_PRIORITY_ERU_INT0);
void SCUERU_Int0_Handler (void)
{
//    my_printf("SCU_ERU_INT0!\n");
//    GPIO_ToggleLed(2);
}

void scueru_Init() {
    uint16 password = IfxScuWdt_getSafetyWatchdogPasswordInline();
    IfxScuWdt_clearSafetyEndinitInline(password);

    MODULE_P02.IOCR0.B.PC1 = 0x02; /* Set P2.1 as pull-up input */
    /* EICR.EXIS 레지스터 설정 : ESR2, 1번 신호 */
    MODULE_SCU.EICR[1].B.EXIS0 = 1;
    /* rising, falling edge 트리거 설정 */
    MODULE_SCU.EICR[1].B.REN0 = 0;
    MODULE_SCU.EICR[1].B.FEN0 = 1;
    /* Enable Trigger Pulse */
    MODULE_SCU.EICR[1].B.EIEN0 = 1;
    /* Determination of output channel for trigger event (Register INP) */
    MODULE_SCU.EICR[1].B.INP0 = 0;
    /* Configure Output channels, outputgating unit OGU (Register IGPy) */
    MODULE_SCU.IGCR[0].B.IGP0 = 1;

    volatile Ifx_SRC_SRCR *src;
    src = (volatile Ifx_SRC_SRCR*) (&MODULE_SRC.SCU.SCUERU);
    src->B.SRPN = ISR_PRIORITY_ERU_INT0;
    src->B.TOS = 0;
    src->B.CLRR = 1; /* clear request */
    src->B.SRE = 1; /* interrupt enable */
    IfxScuWdt_setSafetyEndinitInline(password);
}

