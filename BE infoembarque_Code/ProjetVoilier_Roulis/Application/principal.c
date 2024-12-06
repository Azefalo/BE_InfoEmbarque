#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyTimer.h"
#include "MyADC.h"
#include "MySPI.h"
#include <math.h>
 
int main(void)
{ 
		unsigned char Demande =0xF2;
		int16_t x;
		int16_t y;
		int16_t z;
		unsigned char Message[6];
	
		/*MyGPIO_Struct_TypeDef SPI_CLK;//On met notre consigne du servo moteur sur B0 vu qu'on utilise TIM3
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
    SPI_MOSI.GPIO_Conf = AltOut_Ppull;
    MyGPIO_Init(&SPI_MOSI);
	
		MyGPIO_Struct_TypeDef SPI_CS;
		SPI_CS.GPIO = GPIOB;
    SPI_CS.GPIO_Pin = 6;
    SPI_CS.GPIO_Conf = Out_Ppull;
    MyGPIO_Init(&SPI_CS);*/
	
	  //MyTimer_Struct_TypeDef tim_SV;//On définit notre timer sur le TIM3
	  //tim_SV.Timer=TIM3;
		//tim_SV.ARR=1999;
	  //tim_SV.PSC=719;
	  //MyTimer_Base_Init(&tim_SV);
		
		//MyTimer_PWM(tim_SV.Timer,3);//On met
		//MyTimer_Base_Start(TIM3);
		MySPI_Init(SPI2);
		MySPI_Clear_NSS();
		MySPI_Send(0x2D);
		MySPI_Send(0x08);
		MySPI_Set_NSS();
		MySPI_Clear_NSS();
		MySPI_Send(0x2C);
		MySPI_Send(0x0A);
		MySPI_Set_NSS();
		MySPI_Clear_NSS();
		MySPI_Send(0x31);
		MySPI_Send(0x0B);
		MySPI_Set_NSS();
		
		float angle_roulis;

	while(1){
		MySPI_Clear_NSS();
		MySPI_Send(Demande);
		
		for(int i=0; i<6;i++){
			Message[i]=MySPI_Read();
		}
		MySPI_Set_NSS();
		x=((uint16_t)Message[1]<<8)+(uint16_t)Message[0];
		y=((uint16_t)Message[3]<<8)+(uint16_t)Message[2];//messge 2et 4 info utile
		z=((uint16_t)Message[5]<<8)+(uint16_t)Message[4];
		angle_roulis=360*atanf((float)z/(float)y)/(2*3.1415)+90;
		
		if (angle_roulis>=90){
			angle_roulis=fabs(angle_roulis-180);
		}
		
	}
	
}