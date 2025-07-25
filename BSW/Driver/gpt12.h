#ifndef BSW_DRIVER_GPT12_H_
#define BSW_DRIVER_GPT12_H_

void IsrGpt2T6Handler (void);
void gpt12_Init(void);
void gpt1_init (void);
void gpt2_init(void);
void runGpt12_T3(void);
void runGpt12_T6(void);
void stopGpt12_T3(void);
void stopGpt12_T6(void);
void setcntDelay(unsigned int n);
unsigned int getcntDelay(void);


#endif /* BSW_DRIVER_GPT12_H_ */
