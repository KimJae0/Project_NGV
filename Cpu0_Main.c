#include "main.h"

char c;

// 전역 변수
volatile int currentDuty = 0;   // a~g 키로 duty값을 변경한다.
volatile int baseDuty = 0;    // ← 항상 기억해둘 기본 속도
volatile char  currentDir  = '5'; // '8','2','4','6','1','3','7','9' 중 하나, 기본은 정지('5')

// 인증 관련 선언
#define MAX_PASS_LEN 16
volatile int isUnlocked = 0; // 잠금(0), 해제(1)
const char storedPassword[] = "12345678";
char passwordBuffer[MAX_PASS_LEN + 1];
int passIndex = 0;

void core0_main(void) {
    SYSTEM_Init();

    Bluetooth_printf("연결 성공\n");


    while (1) {

        c = Bluetooth_RecvByteNonBlocked();

        if (!isUnlocked) {
            if (c == '\n' || c == '\r') {
                // 문자열 종료 전에 개행 문자 제거
                while (passIndex > 0 &&
                          (passwordBuffer[passIndex - 1] == '\n' || passwordBuffer[passIndex - 1] == '\r')) {
                        passIndex--;
                    }

                passwordBuffer[passIndex] = '\0';
                if (strcmp(passwordBuffer, storedPassword) == 0) {
                    isUnlocked = 1;
                    my_printf("잠금 해제\n");
                }
                else {
                    my_printf("비밀번호가 틀렸습니다\n");
                }
                passIndex = 0;
            }
            else if (passIndex < MAX_PASS_LEN) {
                passwordBuffer[passIndex++] = c;
                my_printf("%c", c);
            }
            continue;
        }

        MotorDrive(c, isUnlocked);

        // 최종 동작 호출: 이전에 저장한 방향 + 속도로
        Motor_keypad_PWM(currentDir, currentDuty);
    }

}

