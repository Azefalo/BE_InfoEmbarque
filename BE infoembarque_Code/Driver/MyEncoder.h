#include "stm32f10x.h"

void Encoder_GPIO_Init(void);
int16_t MyTimer_Encoder_Read(TIM_TypeDef *Timer);
void MyTimer_Encoder_Reset(void);
void Encoder_Timer_Init(void);