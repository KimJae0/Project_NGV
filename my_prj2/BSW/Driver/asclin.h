#ifndef BSW_DRIVER_ASCLIN_H_
#define BSW_DRIVER_ASCLIN_H_


#define numerator 576
#define denominator 3125

#define ISR_PRIORITY_ASCLIN0_RX 18
#define ISR_PRIORITY_ASCLIN0_TX 19

void Asclin0_InitUart(void);
int Asclin0_PollUart(unsigned char *chr);
unsigned char Asclin0_InUart(void);
char Asclin0_InUartNonBlock(void);
void Asclin0_OutUart(const unsigned char chr);
void Asclin0RxIsrHandler(void);

void Asclin1_InitUart(void);
int Asclin1_PollUart(unsigned char *chr);
unsigned char Asclin1_InUart(void);
char Asclin1_InUartNonBlock(void);
void Asclin1_OutUart(const unsigned char chr);

#endif /* BSW_DRIVER_ASCLIN_H_ */
