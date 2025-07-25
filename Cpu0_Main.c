#include "main.h"
#include <stdint.h>
#include <string.h>

extern void delay_ms(unsigned int ms);

extern volatile int flag;

void core0_main (void)
{
    // Init 함수//

    SYSTEM_Init();

    Bluetooth_printf("Sexy Jongmin!\n");

    int duty;

    char c;
    float distance;
    while (1) {
//        c = Asclin0_InUart();
        c = Bluetooth_RecvByteNonBlocked();
//        if(c >= 0) {
//        Bluetooth_SendByteBlocked(c);
//        }

        // 다시 주행하고 싶다면 'r'을 입력하여 flag = 0으로 바꿔줌.
        if (c == 'r') {
            flag = 0;
            my_printf("Restart!\n");
        }


        else if (c == 'c') { // 후진
            duty = 30;
            Motor_movChA_PWM(duty, 0);
            Motor_movChB_PWM(duty, 0);
            Asclin1_OutUart(c);

        }


        // flag == 1일 때는 아래 코드 실행하지 않음
        if(flag == 1){
            continue;
        }

        if (c == 'a') {
            duty = 10;
        }
        else if (c == 's') {
            duty = 20;
        }
        else if (c == 'd') {
            duty = 30;
        }
        else if (c == 'f') {
            duty = 40;
        }
        else if (c == 'g') {
            duty = 50;
        }

        Motor_keypad_PWM(c, duty);
    }

}

