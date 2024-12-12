#include "MyGPIO.h"
#include "MyTimer.h"
#include "stm32f10x.h"

#define PULSES_PER_ROTATION 360  // Résolution du codeur (360 impulsions par rotation)
#define TIMER_ENCODER TIM2       // Utiliser TIM2 pour encoder le canal A

int16_t MyTimer_Encoder_Read(TIM_TypeDef *Timer) {
    return Timer->CNT;
}

void MyTimer_Encoder_Reset(TIM_TypeDef *Timer) {
    Timer->CNT = 0;
}


// Initialisation des GPIOs pour le codeur incrémental
void Encoder_GPIO_Init(void) {
    MyGPIO_Struct_TypeDef encoderA;
    MyGPIO_Struct_TypeDef encoderB;


    // Configurer la broche A du codeur en entrée capture (PA0)
    encoderA.GPIO = GPIOA;
    encoderA.GPIO_Pin = 0;
    encoderA.GPIO_Conf = In_Floating;
    MyGPIO_Init(&encoderA);

    // Configurer la broche B du codeur en entrée capture (PA1)
    encoderB.GPIO = GPIOA;
    encoderB.GPIO_Pin = 1;
    encoderB.GPIO_Conf = In_Floating;
    MyGPIO_Init(&encoderB);
}

// Initialisation des Timers en mode capture pour le codeur incrémental
void Encoder_Timer_Init(void) {
    MyTimer_Struct_TypeDef TimerConfigA, TimerConfigB;

    // Configurer TIM2 pour le canal A en mode capture
    TimerConfigA.Timer = TIMER_ENCODER;
    TimerConfigA.PSC = 0; // Pas de prédivision
    TimerConfigA.ARR = PULSES_PER_ROTATION - 1; // Valeur maximale de comptage
    MyTimer_Base_Init(&TimerConfigA);


    // 3. Configurer le Timer en mode encodeur
    TIMER_ENCODER->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;   // SMS = 011 (Mode Encodeur 3)
    TIMER_ENCODER->CCMR1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;  // Configurer IC1 et IC2 pour les signaux de l'encodeur
    TIMER_ENCODER->CCER &=~ (TIM_CCER_CC1P| TIM_CCER_CC2P);      // Détection des fronts montants et descendants pour les deux canaux
    // 4. Activer les canaux de capture/compare
    TIMER_ENCODER->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E;  // Activer les canaux 1 et 2

    // 5. Initialiser le compteur à 0
    TIMER_ENCODER->CNT = 0;

    // 6. Démarrer le Timer
    TIMER_ENCODER->CR1 |= TIM_CR1_CEN;
}



int main(void) {
	  //initialisation les pins
	  Encoder_GPIO_Init();
    // Initialisation du Timer 2 en mode encodeur
    Encoder_Timer_Init();

    while (1) {
        // Lire la position de l'encodeur
        int16_t encoder_position = MyTimer_Encoder_Read(TIM2);

        // Traitement de la position de l'encodeur
        // Par exemple : afficher ou utiliser cette position
    }
}