#ifndef BSW_IO_BUZZER_H_
#define BSW_IO_BUZZER_H_

void IsrGpt1T3Handler_Beep(void);
void setBeepCycle(int cycle);
void Buzzer_Init(void);
void Buzzer_Buzz(unsigned int Hz);
void Buzzer_Beep(unsigned int Hz, int duration_ms);

#endif /* BSW_IO_BUZZER_H_ */
