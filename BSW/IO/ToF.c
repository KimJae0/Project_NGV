#include "isr_priority.h"
#include "my_stdio.h"
#include "GPIO.h"
#include "can.h"

static unsigned int g_TofValue = 0;

volatile int flag = 0;

IFX_INTERRUPT(TofIsrHandler, 0, ISR_PRIORITY_CAN_RX);
void TofIsrHandler(void)
{
    unsigned int rxID;
    unsigned char rxData[8] = {0,};
    int rxLen;
    Can_RecvMsg(&rxID, rxData, &rxLen);
    unsigned char dis_status = rxData[3];
    unsigned short signal_strength = rxData[5] << 8 | rxData[4];

    if (signal_strength != 0) {
        g_TofValue = rxData[2] << 16 | rxData[1] << 8 | rxData[0];

        if (g_TofValue < 515) {
            flag = 1;

        }
    }
}

//unsigned int Tof_GetValue(void)
//{
//    return g_TofValue;
//}
