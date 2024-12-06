#include "MyI2C.h"
#include "stm32f10x.h"
void DS1307_Init(I2C_TypeDef *I2Cx);
void DS1307_SetTime(I2C_TypeDef *I2Cx, DS1307_TimeDate *timeDate);
void DS1307_GetTime(I2C_TypeDef *I2Cx, DS1307_TimeDate *timeDate);
static uint8_t BCD_to_Decimal(uint8_t bcd);
static uint8_t Decimal_to_BCD(uint8_t decimal);