#include "stm32f10x.h"
#include "MyPLATEAU.h"

//#include "Rotation_plateau.h"


void initPlateau(void) {
	
    // Initialisation du GPIO pour d�finir le sens du plateau 
    MyGPIO_Struct_TypeDef SensPlateau;
    SensPlateau.GPIO = GPIOA;
    SensPlateau.GPIO_Pin = 6;
    SensPlateau.GPIO_Conf = Out_Ppull;
    MyGPIO_Init(&SensPlateau);

    // Initialisation du GPIO pour le PWM du plateau (PB8)
    MyGPIO_Struct_TypeDef PWMPlateau;
    PWMPlateau.GPIO = GPIOB;
    PWMPlateau.GPIO_Pin = 8; //PB8=TIM4_CH3
    PWMPlateau.GPIO_Conf = AltOut_Ppull;
    MyGPIO_Init(&PWMPlateau);
		
	  // Calcul de la p�riode pour atteindre une fr�quence de 20 kHz
   	MyTimer_Struct_TypeDef TIM;
	  TIM.Timer=TIM4;
    TIM.ARR=89; //f=20kHZ
	  TIM.PSC=19;
	  MyTimer_Base_Init(&TIM);
		
		MyTimer_PWM(TIM.Timer,3);
		MyTimer_SetDutyCycle(TIM.Timer ,3 ,0);
    MyTimer_Base_Start(TIM4);
}

volatile int8_t receivedData = 0;  // Variable pour stocker la direction re�ue
volatile int vitesse = 0;   // Vitesse du bateau (0 � 100)



// Fonction pour d�finir le sens et la vitesse du bateau
void updateBoatDirectionAndSpeed(uint8_t receivedData) {
	  initPlateau();
	  if (receivedData >= 0x9C && receivedData < 0xFF) {
        vitesse=(int)(256-receivedData);
			  MyGPIO_Reset(GPIOA,6);                             // Avancer
		    MyTimer_SetDutyCycle(TIM4 ,3 ,vitesse);
    } else if (receivedData > 0x00 && receivedData <= 0x64) {
        vitesse=(int)(receivedData);
			  MyGPIO_Set(GPIOA,6);                            // Reculer
		    MyTimer_SetDutyCycle(TIM4 ,3 ,vitesse);
    }  
    else{
    vitesse = 0; // Arr�t
	  MyTimer_SetDutyCycle(TIM4 ,3 ,vitesse);
		}
}

// Fonction d'interruption pour la r�ception de donn�es
void USART1_IRQHandler(void) {
    if (USART1->SR & USART_SR_RXNE) {         // V�rifier si le registre de r�ception est pr�t
        uint8_t receivedData = (int8_t)USART1->DR;   // Lire la donn�e brute re�ue (0-255)
 			if(receivedData!=0)
         updateBoatDirectionAndSpeed(receivedData);  // Mettre � jour sens et vitesse
    }
}