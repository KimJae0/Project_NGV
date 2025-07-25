#include "stm.h"
#include "IfxStm.h"


uint64 getTimeUs(void){
    uint64 result;
    float32 frequency = 100000000.0f; // 100MHz

    /* Read 64-bit System Timer */
    /* STM_TIM0를 읽는 순간, 현재 상위 32bit 값이 STM_CAP에 저장됨
     * 따라서, STM_TIM0 레지스터 값을 읽어온 후,
     * STM_CAP을 왼쪽으로 비트 쉬프트 연산하고 더하면 됨 */
    result = MODULE_STM0.TIM0.U;
    result |= ((uint64)MODULE_STM0.CAP.U) << 32;

    /* Calculate Us */
    return result / (frequency /1000000);
}

uint64 getTime_10Ns(void){
    uint64 result;

    /* Read 64-bit System Timer */
    /* STM_TIM0를 읽는 순간, 현재 상위 32bit 값이 STM_CAP에 저장됨
     * 따라서, STM_TIM0 레지스터 값을 읽어온 후,
     * STM_CAP을 왼쪽으로 비트 쉬프트 연산하고 더하면 됨 */
    result = MODULE_STM0.TIM0.U;
    result |= ((uint64)MODULE_STM0.CAP.U) << 32;

    return result;
}
