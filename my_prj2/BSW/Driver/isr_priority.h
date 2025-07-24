#ifndef ISR_PRIORITY_H_
#define ISR_PRIORITY_H_

#define ISR_PRIORITY_ASCLIN0_RX 18
#define ISR_PRIORITY_ASCLIN0_TX 19
#define ISR_PRIORITY_ERU_INT0 17

#define ISR_PRIORITY_ASCLIN1_RX 22
#define ISR_PRIORITY_ASCLIN1_TX 23
#define ISR_PRIORITY_ERU_INT1 21

#define ISR_PRIORITY_GPT1T3_TIMER 5 /* Define the GPT12 Timer interrupt priority */
#define ISR_PRIORITY_GPT2T6_TIMER 6 /* Define the GPT12 Timer interrupt priority */
#define ISR_PRIORITY_ATOM 20

#define ISR_PRIORITY_CAN_TX         2       /* Define the CAN TX interrupt priority */
#define ISR_PRIORITY_CAN_RX         1       /* Define the CAN RX interrupt priority */

#define ISR_PRIORITY_CANFD_RX       3       /* Define the CAN RX interrupt priority */
#define ISR_PRIORITY_CANFD_TX       4       /* Define the CAN TX interrupt priority */

#endif /* ISR_PRIORITY_H_ */
