#include "Motor.h"
#include "motorDriver.h"
#include <stdint.h>

extern volatile int currentDuty;
extern volatile char currentDir;
extern volatile int baseDuty;
extern volatile int flag;

void Motor_keypad_PWM(char dir, int duty) {
    if (currentDuty == 0) {
        Motor_stopChA();
        Motor_stopChB();
        return;
    }

    int turnBoostDuty = currentDuty + 25;

    switch (dir) {
        case '8':  // 전진
            Motor_movChA_PWM(currentDuty, 1);
            Motor_movChB_PWM(currentDuty, 1);
            break;
        case '2':  // 후진
            Motor_movChA_PWM(currentDuty, 0);
            Motor_movChB_PWM(currentDuty, 0);
            break;
        case '4':  // 제자리 좌회전
            Motor_movChA_PWM(currentDuty, 0);
            Motor_movChB_PWM(currentDuty, 1);
            break;
        case '6':  // 제자리 우회전
            Motor_movChA_PWM(currentDuty, 1);
            Motor_movChB_PWM(currentDuty, 0);
            break;
        case '5':  // 정지
            Motor_stopChA();
            Motor_stopChB();
            break;
        case '1':  // 후진 좌회전
            Motor_stopChA();
            Motor_movChB_PWM(currentDuty, 0);
            break;
        case '3':  // 후진 우회전
            Motor_movChA_PWM(currentDuty, 0);
            Motor_stopChB();
            break;
        case '7':  // 전진 좌회전
            Motor_movChA_PWM(turnBoostDuty / 3 + 5, 1);
            Motor_movChB_PWM(turnBoostDuty, 1);
            break;
        case '9':  // 전진 우회전
            Motor_movChA_PWM(turnBoostDuty, 1);
            Motor_movChB_PWM(turnBoostDuty / 3 + 5, 1);
            break;
    }
}

void MotorDrive(char c, int isUnlocked) {
    // 속도 및 방향 설정은 인증 여부와 무관하게 항상 가능
    if (c == '8' || c == '2' || c == '4' || c == '6' || c == '5' ||
        c == '1' || c == '3' || c == '7' || c == '9') {
        currentDir = c;
        currentDuty = baseDuty;
    }
    else if (c == 'a') baseDuty = 10;
    else if (c == 's') baseDuty = 20;
    else if (c == 'd') baseDuty = 30;
    else if (c == 'f') baseDuty = 40;
    else if (c == 'g') baseDuty = 50;
    else if (c == 'h') baseDuty = 60;
    else if (c == 'j') baseDuty = 70;
    else if (c == 'k') baseDuty = 80;
    else if (c == 'l') baseDuty = 90;
    else if (c == ';') baseDuty = 100;
    else if (c == 'B') {
        if (currentDuty > 0)
            currentDuty = (currentDuty >= 10) ? currentDuty - 10 : 0;
    }

    // 인증 안된 상태에서는 동작하지 않음 (상태 설정만 허용)
    if (!isUnlocked) return;

    // 장애물 처리
    if (flag == 1) {
        if (c == '1' || c == '2' || c == '3') {
            currentDir = c;
            currentDuty = 30;
            Motor_keypad_PWM(currentDir, currentDuty);
        } else {
            Motor_stopChA();
            Motor_stopChB();
        }
    }
}
