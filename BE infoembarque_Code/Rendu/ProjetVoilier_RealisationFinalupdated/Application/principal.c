#include "myApplication.h"

int main(void){

	  initPlateau(); //initialisation de la commande du plateau  
	  UART1_Init(); // communication USART activ� en mode r�ception et transmission 
    Battery_init();  //initialisation de la lecture de la batterie
	  DS1307_TimeDate MARC;
    RTC_init(&MARC); //initialisattion de la lecture du RTC
	  Roulis_init(); //initialisation pour d�terminer l'angle de roulis
		
		float angle_roulis;
		
		//initialisation des pins de l'encodeur (A et B)
	  Encoder_GPIO_Init();
    // Initialisation du Timer 2 en mode encodeur 3 pour lire A et B
    Encoder_Timer_Init();
	  // d�finition de la pin permettant de lire z pour reset alpha
	  MyGPIO_Struct_TypeDef index;
    Index_init(&index); //initialisation de l'index z de l'encodeur
	
	  MyTimer_Struct_TypeDef tim_SV;
    Servo_init(&tim_SV); //initialisation du servomoteur
    
    // Boucle principale
    while (1){
				angle_roulis = Demande_message();
				
				if (angle_roulis>=90){
					angle_roulis = fabs(angle_roulis-180); // mise � jour de l'angle de roulis 
				}
				
        Index_test(&index); //r�initialisation de l'angle alpha de la girouette d�s que l'index z est atteint 

        Servo_update(&tim_SV, angle_roulis); // mise � jour de l'angle du servomoteur en fonction de la position  de la girouette
		
				Send_Data(&MARC, angle_roulis); //envoi des donn�es utiles � la t�l�commande
		 }
}
