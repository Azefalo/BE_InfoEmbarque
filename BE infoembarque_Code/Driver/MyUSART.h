#include "stm32f10x.h"


void UART1_Init(void);
char UART1_Receive(void);
void UART1_SendDatatime(int8_t timeh, int8_t timem, int8_t times);
void UART1_SendData(int8_t timeh, int8_t timem, int8_t times,int8_t direction, int8_t battery, int8_t roll_angle);