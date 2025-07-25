#ifndef BSW_IO_GPIO_H_
#define BSW_IO_GPIO_H_

void GPIO_Init(void);

void GPIO_SetLed(unsigned char num_LED, unsigned char onOff);

void GPIO_ToggleLed(unsigned char num_LED);

int GPIO_getSW1(void);

int GPIO_getSW2(void);


#endif /* BSW_IO_GPIO_H_ */
