#include "stm32f10x.h"
#include "MyI2C.h"
#include "DS1307.h"
#include "MyUSART.h"
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
	  UART1_Init();
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

    
    // Boucle principale
    while (1)
    {
			  DS1307_GetTime(I2C2,&MARC);
			  int8_t timeh = MARC.hours;
			  int8_t timem = MARC.minutes;
			  int8_t times = MARC.seconds;
			  UART1_SendDatatime(timeh,timem,times);
        for (volatile int i = 0; i < 5000000; i++){  // Temporisation d'environ 100 ms
        }
		 }
			  
   
}
