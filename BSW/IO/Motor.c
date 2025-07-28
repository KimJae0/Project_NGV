#include "Motor.h"
#include "main.h"



void Motor_Init(void)
{
    MODULE_P02.IOCR4.B.PC7 = 0x10;  // PWM A Break
    MODULE_P02.IOCR4.B.PC6 = 0x10;  // PWM B Break

    // Init GTM for PWM generation
    GtmAtomPwm_Init();

    // Set duty 0
    GtmAtomPwmA_SetDutyCycle(0);
    GtmAtomPwmB_SetDutyCycle(0);
}

///* 1: 정방향, 2: 역방향 */
void Motor_movChA(int dir)
{
    if(dir)
    {
        MODULE_P10.OUT.B.P1 = 1; /* 모터 회전 방향 (1: 앞, 0: 뒤) */
    }
    else {
        MODULE_P10.OUT.B.P1 = 0; /* 모터 회전 방향 (1: 앞, 0: 뒤) */
    }
    MODULE_P02.OUT.B.P7 = 0;   /* 모터 Brake 해제 (1: 정지, 0: PWM-A에 따라 동작) */
    GtmAtomPwm_SetDutyCycle(1000); /* 100% PWM duty  */
}

void Motor_stopChA(void)
{
    MODULE_P02.OUT.B.P7 = 1;   /* 모터 Brake 신호 인가 (1: 정지, 0: PWM-A에 따라 동작) */
}


///* 1: 정방향, 0: 역방향 */
void Motor_movChA_PWM(int duty, int dir)
{
//    GtmAtomPwm_SetDutyCycle(duty);
    GtmAtomPwmA_SetDutyCycle(duty*10);
    if(dir)
    {
        MODULE_P10.OUT.B.P1 = 1; /* 모터 회전 방향 (1: 앞, 0: 뒤) */
    }
    else {
        MODULE_P10.OUT.B.P1 = 0; /* 모터 회전 방향 (1: 앞, 0: 뒤) */
    }

    MODULE_P02.OUT.B.P7 = 0;   /* 모터 Brake 해제 (1: 정지, 0: PWM-A에 따라 동작) */
}

///* 1: 정방향, 2: 역방향 */
void Motor_movChB(int dir)
{
    if(dir)
    {
        MODULE_P10.OUT.B.P2 = 1; /* 모터 회전 방향 (1: 앞, 0: 뒤) */
    }
    else {
        MODULE_P10.OUT.B.P2 = 0; /* 모터 회전 방향 (1: 앞, 0: 뒤) */
    }
    MODULE_P02.OUT.B.P6 = 0;   /* 모터 Brake 해제 (1: 정지, 0: PWM-A에 따라 동작) */
    GtmAtomPwm_SetDutyCycle(1000); /* 100% PWM duty  */
}

void Motor_stopChB(void)
{
    MODULE_P02.OUT.B.P6 = 1;   /* 모터 Brake 신호 인가 (1: 정지, 0: PWM-A에 따라 동작) */
}


///* 1: 정방향, 0: 역방향 */
void Motor_movChB_PWM(int duty, int dir)
{
//    GtmAtomPwm_SetDutyCycle(duty);
    GtmAtomPwmB_SetDutyCycle(duty*10);

    if(dir)
    {
        MODULE_P10.OUT.B.P2 = 1; /* 모터 회전 방향 (1: 앞, 0: 뒤) */
    }
    else {
        MODULE_P10.OUT.B.P2 = 0; /* 모터 회전 방향 (1: 앞, 0: 뒤) */
    }

    MODULE_P02.OUT.B.P6 = 0;   /* 모터 Brake 해제 (1: 정지, 0: PWM-A에 따라 동작) */
}


extern volatile int currentDuty;   // a~g 키로 설정되는 전역 속도
extern volatile char currentDir;   // '8','2','4','6','5' 로 설정되는 전역 방향

void Motor_keypad_PWM(char dir, int duty)
{
    // 마지막으로 실제 이동했던 방향을 기억
    static char lastDir = '5';  // 초기: 정지

    // 방향키가 들어올 때만 lastDir 업데이트
    if (dir!='B' && dir!='5') {
        lastDir = dir;
    }

    switch (dir) {
      case '8': // 전진
      case '2': // 후진
      case '4': // 제자리 좌회전
      case '6': // 제자리 우회전
      case '5': // 정지
        // 일반 이동/정지 명령은 duty와 dir 그대로 처리
        break;
      case 'B': // 자동 감속
        if (currentDuty > 0) {
            currentDuty = (currentDuty > 10 ? currentDuty - 10 : 0);
        }
        // B 신호일 때는 마지막 방향으로 다시 이동
        dir = lastDir;
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
    }

    Asclin1_OutUart(dir);
}
