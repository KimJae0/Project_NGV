#include "Delay.h"
#include "Bsp.h"

void delay_ms(unsigned int ms)
{
    for (volatile int i = 0; i < 25000 * ms; i++) {
        // 시간 지연용 루프 (최적화 방지)
    }
}
