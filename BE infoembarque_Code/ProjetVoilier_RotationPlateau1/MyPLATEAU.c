#include "MyTimer.h"
#include "MyGPIO.h"
#include "MYPLATEAU.h"

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
    TIM.ARR=359; //f=20kHZ
	  TIM.PSC=99;
	  MyTimer_Base_Init(&TIM);
		
		MyTimer_PWM(TIM.Timer,3);
		MyTimer_SetDutyCycle(TIM.Timer ,3 ,0);
    MyTimer_Base_Start(TIM4);
}


volatile int8_t sens = 0;       // 1 pour avancer, -1 pour reculer, 0 pour arr�t
volatile int8_t vitesse = 0;   // Vitesse du bateau (0 � 100)

// Fonction pour mapper une valeur de la plage [0, 255] vers [-100, 100]
int8_t mapToDirection(uint8_t receivedData) {
    // Conversion lin�aire : y = (receivedData * 200 / 255) - 100
    return (int8_t)((receivedData * 200 / 255) - 100);
}

// Fonction pour d�finir le sens et la vitesse du bateau
void updateBoatDirectionAndSpeed(uint8_t receivedData) {
	  //initPlateau();
    vitesse = mapToDirection(receivedData);  // Convertir la donn�e en direction
		if (vitesse >= 2 && vitesse <= 100) {
        MyGPIO_Set(GPIOA,6);                             // Avancer
		    MyTimer_SetDutyCycle(TIM4 ,3 ,vitesse);
    } else if (vitesse <= -2 && vitesse >= -100) {
        MyGPIO_Reset(GPIOA,6);                            // Reculer
			  vitesse=-vitesse;
		    MyTimer_SetDutyCycle(TIM4 ,3 ,vitesse);
    } else {                        // Arr�t
        vitesse = 0;
			  MyTimer_SetDutyCycle(TIM4 ,3 ,vitesse);
			

// Fonction d'interruption pour la r�ception de donn�es
void USART1_IRQHandler(void) {
    if (USART1->SR & USART_SR_RXNE) {         // V�rifier si le registre de r�ception est pr�t
        uint8_t receivedData = USART1->DR;   // Lire la donn�e brute re�ue (0-255)
        updateBoatDirectionAndSpeed(receivedData);  // Mettre � jour sens et vitesse
    }
}
