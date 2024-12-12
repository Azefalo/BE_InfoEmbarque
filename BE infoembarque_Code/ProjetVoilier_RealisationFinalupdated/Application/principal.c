#include "myApplication.h"

int main(void){
		// Initialisation de l'horloge du système (RCC) et des GPIO nécessaires
    //SystemInit();
	  initPlateau();
	  UART1_Init();
    Battery_init();
	  DS1307_TimeDate MARC;
    RTC_init(&MARC);
	  Roulis_init();
		
		float angle_roulis;
		
		//initialisation les pins
	  Encoder_GPIO_Init();
    // Initialisation du Timer 2 en mode encodeur
    Encoder_Timer_Init();
	  // Déclarer une broche avec Z pour reset
	  MyGPIO_Struct_TypeDef index;
    Index_init(&index); //initialisation de l'index Z de l'encodeur
	
	  MyTimer_Struct_TypeDef tim_SV;
    Servo_init(&tim_SV); //initialisation du servomoteur
    
    // Boucle principale
    while (1){
				angle_roulis = Demande_message();
				
				if (angle_roulis>=90){
					angle_roulis = fabs(angle_roulis-180);
				}
				
        Index_test(&index);

        Servo_update(&tim_SV, angle_roulis);
		
				Send_Data(&MARC, angle_roulis);
		 }
}
