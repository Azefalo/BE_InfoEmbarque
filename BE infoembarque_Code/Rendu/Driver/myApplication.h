#include "stm32f10x.h"
#include "MyI2C.h"
#include "DS1307.h"
#include "MyUSART.h"
#include "MyGPIO.h"
#include "MyADC.h"
#include "MyTimer.h"
#include "MyPLATEAU.h"
#include "MyEncoder.h"
#include "MySPI.h"
#include <math.h>

void Battery_init();
void RTC_init(DS1307_TimeDate *timeDate);
void Roulis_init();
void Index_init(MyGPIO_Struct_TypeDef * index);
void Index_test(MyGPIO_Struct_TypeDef * index);
void Servo_init(MyTimer_Struct_TypeDef * tim_SV);
void Servo_update(MyTimer_Struct_TypeDef * tim_SV, float angle_roulis);
float Demande_message();
void Send_Data(DS1307_TimeDate *MARC, float angle_roulis);