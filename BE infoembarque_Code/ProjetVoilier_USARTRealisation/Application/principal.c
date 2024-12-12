#include "stm32f10x.h"
#include "MyI2C.h"
#include "DS1307.h"
#include "MyUSART.h"
#include "MyGPIO.h"
#include "MyADC.h"
#include "MyTimer.h"
#include "MyPLATEAU.h"
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
    int8_t roll_angle = 0;    // Angle de roulis simulé
    	
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

    
    // Boucle principale
    while (1)
    {
			  
			  DS1307_GetTime(I2C2,&MARC);
			  int8_t timeh = MARC.hours;
			  int8_t timem = MARC.minutes;
			  int8_t times = MARC.seconds;
			  batterylevel= ((ADC1->DR - 353) * 100.0) / (474 - 353);
			  direction=MyGPIO_Read(GPIOA,6);
        // Envoyer les données toutes les 100 ms
        UART1_SendData(timeh,timem,times,direction, batterylevel, roll_angle);
        for (volatile int i = 0; i < 5000000; i++){  // Temporisation d'environ 100 ms
        }
		 }
			  
   
}
