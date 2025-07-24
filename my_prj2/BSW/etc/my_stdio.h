#ifndef BSW_ETC_MY_STDIO_H_
#define BSW_ETC_MY_STDIO_H_

#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"


#define BUFSIZE     128
#define KB_BS '\x7F'
#define KB_CR '\r'


void my_puts(const char *str);
void my_printf(const char *fmt, ...);
void my_scanf(const char *fmt, ...);
void remove_null(char *s);


#endif /* BSW_ETC_MY_STDIO_H_ */
