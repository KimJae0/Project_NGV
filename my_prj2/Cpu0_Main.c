#include "main.h"
#include <stdint.h>
#include <string.h>

extern void delay_ms(unsigned int ms);

void core0_main (void)
{
    // Init 함수//

    SYSTEM_Init();

    Bluetooth_printf("Sexy Jongmin!\n");

    int duty = 80;

    char c;

    while (1) {
//        c = Asclin0_InUart();
        c = Bluetooth_RecvByteNonBlocked();
//        if(c >= 0) {
//        Bluetooth_SendByteBlocked(c);
//        }

        if (c == '\r') {
            Asclin0_OutUart('\n');
        }

        if (c == '8') { // 전진
            Motor_movChA_PWM(duty, 1);
            Motor_movChB_PWM(duty, 1);
            Asclin0_OutUart(c);
        }
        else if (c == '2') { // 후진
            Motor_movChA_PWM(duty, 0);
            Motor_movChB_PWM(duty, 0);
            Asclin0_OutUart(c);

        }
        else if (c == '4') { // 제자리 좌회전
            Motor_movChA_PWM(duty, 0);
            Motor_movChB_PWM(duty, 1);
            Asclin0_OutUart(c);
        }
        else if (c == '6') { // 제자리 우회전
            Motor_movChA_PWM(duty, 1);
            Motor_movChB_PWM(duty, 0);
            Asclin0_OutUart(c);
        }
        else if (c == '5') { // 정지
            Motor_stopChA();
            Motor_stopChB();
            Asclin0_OutUart(c);
        }
        else if (c == '7') { // 앞 좌회전
            Motor_stopChA();
            Motor_movChB_PWM(duty, 1);
            Asclin0_OutUart(c);
        }
        else if (c == '9') { // 앞 우회전
            Motor_movChA_PWM(duty, 1);
            Motor_stopChB();
            Asclin0_OutUart(c);
        }
        else if (c == '1') { // 뒤 좌회전
            Motor_stopChA();
            Motor_movChB_PWM(duty, 0);
            Asclin0_OutUart(c);
        }
        else if (c == '3') { // 뒤 우회전
            Motor_movChA_PWM(duty, 0);
            Motor_stopChB();
            Asclin0_OutUart(c);
        }
    }

}

