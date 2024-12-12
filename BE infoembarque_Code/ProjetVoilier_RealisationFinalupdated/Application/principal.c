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
//// Callback en cas d'erreur I2C
//void MyI2C_ErrorCallback(void)
//{
//    MyI2C_Err_Enum error = MyI2C_Get_Error(I2C1);
//    // Gérer les erreurs ici (vous pouvez ajouter des logs ou des signaux)
//    while (1)
//    {
//        // Boucle infinie pour signaler une erreur
//    }
//}


int main(void)
{   // Initialisation de l'horloge du système (RCC) et des GPIO nécessaires
    //SystemInit();
	  initPlateau();
	  UART1_Init();
	  uint8_t batterylevel = 0;
    int8_t direction = 0;
    	
	  DS1307_TimeDate MARC;
//	  // Définition des valeurs
//    MARC.seconds = 45;       // 30 secondes
//    MARC.minutes = 43;       // 45 minutes
//    MARC.hours = 14;         // 14 heures (2:00 PM en format 24h)
//    MARC.day_of_week = 4;    // Jeudi (1 = Dimanche, 7 = Samedi)
//    MARC.date = 12;          // 12 du mois
//    MARC.month = 12;         // Décembre 
//    MARC.year = 24; 
      DS1307_Init(I2C2);
//	  DS1307_SetTime(I2C2,&MARC);
	  MyGPIO_Struct_TypeDef battery;
	  battery.GPIO = GPIOA;
    battery.GPIO_Pin = 7;
    battery.GPIO_Conf = In_Analog;
    MyGPIO_Init(&battery);
	
	  configadc(7); // PA7 est sur le canal 7 de ADC1
	  convert_cont();//convertion continu
   
	 		unsigned char Demande =0xF2;
		int16_t x;
		int16_t y;
		int16_t z;
		unsigned char Message[6];
	
		
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
		
		//initialisation les pins
	  Encoder_GPIO_Init();
    // Initialisation du Timer 2 en mode encodeur
    Encoder_Timer_Init();
	  // Déclarer une broche avec Z pour reset
	  MyGPIO_Struct_TypeDef index;
	  // Initialisation de la LED sur PA5 (output push-pull)
    index.GPIO = GPIOA;
    index.GPIO_Pin = 4;
    index.GPIO_Conf = In_Floating;
    MyGPIO_Init(&index);
   	int zi= MyGPIO_Read(index.GPIO,index.GPIO_Pin);
	
		int Teta=0;
		int alpha=0;
		MyGPIO_Struct_TypeDef Consigne_S;//On met notre consigne du servo moteur sur B0 vu quon utilise TIM3
    Consigne_S.GPIO = GPIOB;
    Consigne_S.GPIO_Pin = 0;
    Consigne_S.GPIO_Conf = AltOut_Ppull;
    MyGPIO_Init(&Consigne_S);
		
	  MyTimer_Struct_TypeDef tim_SV;//On définit notre timer sur le TIM3
	  tim_SV.Timer=TIM3;
		tim_SV.ARR=1999;
	  tim_SV.PSC=719;
	  MyTimer_Base_Init(&tim_SV);
		
		MyTimer_PWM(tim_SV.Timer,3);//On met en marche la PWM
		MyTimer_Base_Start(TIM3);
		int encoder_position=0;
    
    // Boucle principale
    while (1)
    {
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
		
		 //Lire le signal de référence de l'encodeur
			  zi= MyGPIO_Read(index.GPIO,index.GPIO_Pin);
        // Lire la position de l'encodeur
        encoder_position = MyTimer_Encoder_Read(TIM2);
			  if(zi==1){
					MyTimer_Encoder_Reset(); //EXTI et/ou AFIO a faire apres
		    }
				
				alpha= (encoder_position/4);
				
				if (alpha >180){
					alpha=360-alpha;
				}
				
				if (alpha >=0 & alpha<=45){
					Teta=180;
				}
				if (alpha >=45 & alpha<=180){
					Teta=240-180*alpha/135;
				}
				
				if(angle_roulis>=40){
					Teta=0;
				}
		
				MyTimer_SetDutyCycle(tim_SV.Timer ,3 ,(Teta/36)+5);
		
			  DS1307_GetTime(I2C2,&MARC);
			  int8_t timeh = MARC.hours;
			  int8_t timem = MARC.minutes;
			  int8_t times = MARC.seconds;
			  batterylevel= ((ADC1->DR - 353) * 100.0) / (474 - 353);
			  direction=MyGPIO_Read(GPIOA,6);
        // Envoyer les données toutes les 100 ms
        UART1_SendData(timeh,timem,times,direction, batterylevel, angle_roulis);
        for (volatile int i = 0; i < 5000000; i++){  // Temporisation d'environ 100 ms
        }
		 }
			  
   
}
