#include "main.h"
#include <stdint.h>
#include <string.h>

extern void delay_ms(unsigned int ms);

extern volatile int flag;


// 전역 변수
volatile int currentDuty = 0;   // a~g 키로만 바뀌는 값
volatile char  currentDir  = '5'; // '8','2','4','6' 중 하나, 기본은 정지('5')
void core0_main (void)
{
    // Init 함수//

    SYSTEM_Init();

    Bluetooth_printf("Sexy Jongmin!\n");


    char c;
    float distance;

    while (1) {
        char c = Bluetooth_RecvByteNonBlocked();

        // 비상 해제
        if (c == 'r') {
            flag = 0;
        }
        // 전진/후진 등 방향키
        else if (c == '8' || c == '2' || c == '4' || c == '6' || c == '5') {
            currentDir = c;      // 방향만 바꾼다
            Asclin1_OutUart(c);
        }
        // 속도 변경키
        else if (c == 'a') currentDuty = 10;
        else if (c == 'b') currentDuty = 20;  // 'b' 대신 's' 등 원하시는 키
        else if (c == 'c') currentDuty = 30;
        else if (c == 'd') currentDuty = 40;
        else if (c == 'e') currentDuty = 50;  // 예시

        // 장애물 멈춤
        if (flag == 1) {
            // 멈추기
            Motor_stopChA();
            Motor_stopChB();
            continue;
        }

        // 최종 동작 호출: 이전에 저장한 방향 + 속도로
        Motor_keypad_PWM(currentDir, currentDuty);
    }

}

