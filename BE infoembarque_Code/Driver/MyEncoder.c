#include "MyGPIO.h"
#include "MyTimer.h"
#include "MyEncoder.h"
#include "stm32f10x.h"

#define PULSES_PER_ROTATION 1440  // Résolution du codeur (360 impulsions par rotation)
#define TIMER_ENCODER TIM2       // Utiliser TIM2 pour encoder le canal A

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
    MyTimer_Struct_TypeDef TimerConfigA;

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

//lecture du compteur du timer de la girouette
int16_t MyTimer_Encoder_Read(TIM_TypeDef *Timer) {
    return Timer->CNT;
}
//remise à zéro du compteur
void MyTimer_Encoder_Reset(void) {
    TIM2->CNT = 0;
}