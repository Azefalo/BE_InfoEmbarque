
#include "MyTimer.h"
#include "MyGPIO.h"
#include "MYPLATEAU.h"

void initPlateau(void) {
	
    // Initialisation du GPIO pour définir le sens du plateau 
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
		
	  // Calcul de la période pour atteindre une fréquence de 20 kHz
   	MyTimer_Struct_TypeDef TIM;
	  TIM.Timer=TIM4;
    TIM.ARR=359; //f=20kHZ
	  TIM.PSC=99;
	  MyTimer_Base_Init(&TIM);
		
		MyTimer_PWM(TIM.Timer,3);
		MyTimer_SetDutyCycle(TIM.Timer ,3 ,20);
    MyTimer_Base_Start(TIM4);
}

// Fonction pour orienter le plateau avec un sens et un duty cycle
void orientationPlateau(int sens, float dutycycle) {
    if (sens == 1) {
        MyGPIO_Set(GPIOB, 8);   // Régler le sens à 1
    } else {
        MyGPIO_Reset(GPIOB, 8); // Régler le sens à 0
    }
    MyTimer_SetDutyCycle(TIM4 ,3 ,dutycycle);
}