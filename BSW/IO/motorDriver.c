#include "Motor.h"

extern volatile int currentDuty;   // a~g 키로 설정되는 전역 속도
extern volatile char currentDir;   // '1','2','3','4','5','6','7','8','9'로 설정되는 전역 방향



void Motor_keypad_PWM(char dir, int duty)
{
    // 마지막으로 실제 이동했던 방향을 기억
    static char lastDir = '5';  // 초기: 정지
    int tmp, tmp2;

    // 방향키가 들어올 때만 lastDir 업데이트
    if (dir!='B' && dir!='5') {
        lastDir = dir;
    }

    switch (dir) {
      case '8': // 전진
      case '2': // 후진
      case '4': // 제자리 좌회전
      case '6': // 제자리 우회전
      case '1': // 후진 좌회전
      case '3': // 후진 우회전
      case '7': // 전진 좌회전
      case '9': // 전진 우회전
      case '5': // 정지
        // 일반 이동/정지 명령은 duty와 dir 그대로 처리
        break;
      default:
        // 그 외 키는 무시
        return;
    }

    // 실제 모터 구동
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
      case '1':
    Motor_stopChA();
    Motor_movChB_PWM(currentDuty, 0);
    break;
      case '3':
    Motor_movChA_PWM(currentDuty, 0);
    Motor_stopChB();
    break;
      case '7':
//    Motor_stopChA();
    tmp = currentDuty + 25;
    Motor_movChA_PWM(tmp / 3, 1);
    Motor_movChB_PWM(tmp, 1);
    break;
      case '9':
    tmp2 = currentDuty + 25;
    Motor_movChA_PWM(tmp2, 1);
//    Motor_stopChB();
    Motor_movChB_PWM(tmp2 / 3, 1);
    break;

    }

    Asclin1_OutUart(dir);
}
