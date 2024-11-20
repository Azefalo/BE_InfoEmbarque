#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyTimer.h"
#include "MyADC.h"

 
int main(void)
{ 
		int Teta=120; //valeur test
		int alpha=0; //valeur test
		MyGPIO_Struct_TypeDef Consigne_S;//On met notre consigne du servo moteur sur B0 vu qu'on utilise TIM3
    Consigne_S.GPIO = GPIOB;
    Consigne_S.GPIO_Pin = 0;
    Consigne_S.GPIO_Conf = AltOut_Ppull;
    MyGPIO_Init(&Consigne_S);
		
	  MyTimer_Struct_TypeDef tim_SV;//On définit notre timer sur le TIM3
	  tim_SV.Timer=TIM3;
		tim_SV.ARR=1999;
	  tim_SV.PSC=719;
	  MyTimer_Base_Init(&tim_SV);
		
		MyTimer_PWM(tim_SV.Timer,3);//On met
		MyTimer_Base_Start(TIM3);

	while(1){
		
		if (alpha >=0 & alpha<=45){
			Teta=0;
		}
		if (alpha >=45 & alpha<=180){
			Teta=120*alpha/(180-45) -120*45/(180-45);
		}
		
		MyTimer_SetDutyCycle(tim_SV.Timer ,3 ,(Teta/24)+5);
	}
}