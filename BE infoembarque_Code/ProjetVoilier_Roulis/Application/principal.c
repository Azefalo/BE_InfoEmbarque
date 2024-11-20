#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyTimer.h"
#include "MyADC.h"

 
int main(void)
{ 
		int Teta=120; //valeur test
		int alpha=0; //valeur test
	
		MyGPIO_Struct_TypeDef SPI_CLK;//On met notre consigne du servo moteur sur B0 vu qu'on utilise TIM3
    SPI_CLK.GPIO = GPIOB;
    SPI_CLK.GPIO_Pin = 1;
    SPI_CLK.GPIO_Conf = AltOut_Ppull;
    MyGPIO_Init(&SPI_CLK);
		
		MyGPIO_Struct_TypeDef SPI_MISO;
		SPI_MISO.GPIO = GPIOB;
    SPI_MISO.GPIO_Pin = 2;
    SPI_MISO.GPIO_Conf = In_PullDown;
    MyGPIO_Init(&SPI_MISO);
	
		MyGPIO_Struct_TypeDef SPI_MOSI;
		SPI_MOSI.GPIO = GPIOB;
    SPI_MOSI.GPIO_Pin = 5;
    SPI_MOSI.GPIO_Conf = Out_Ppull;
    MyGPIO_Init(&SPI_MOSI);
	
		MyGPIO_Struct_TypeDef SPI_CS;
		SPI_CS.GPIO = GPIOB;
    SPI_CS.GPIO_Pin = 6;
    SPI_CS.GPIO_Conf = Out_Ppull;
    MyGPIO_Init(&SPI_CS);
	
	  //MyTimer_Struct_TypeDef tim_SV;//On définit notre timer sur le TIM3
	  //tim_SV.Timer=TIM3;
		//tim_SV.ARR=1999;
	  //tim_SV.PSC=719;
	  //MyTimer_Base_Init(&tim_SV);
		
		//MyTimer_PWM(tim_SV.Timer,3);//On met
		//MyTimer_Base_Start(TIM3);

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