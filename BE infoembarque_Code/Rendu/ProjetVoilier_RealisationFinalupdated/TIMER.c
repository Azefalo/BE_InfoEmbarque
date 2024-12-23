#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyTimer.h"


//void Toggle_LED(void); prototype 
// void Toggle_LED(void) 
// {
//    MyGPIO_Struct_TypeDef led;
//	  // Initialisation de la LED sur PA5 (output push-pull)
//    led.GPIO = GPIOA;
//    led.GPIO_Pin = 5;
//    led.GPIO_Conf = Out_Ppull;
//    MyGPIO_Init(&led);
//	  MyGPIO_Toggle(led.GPIO,led.GPIO_Pin);
// }
  void delay(volatile uint32_t delay_time) {
    while (delay_time--) {
        // Boucle vide pour créer un délai
    }
}
int Timer(void)
{
   
//    // Activer l'horloge pour le Timer 2
//    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

//    // Configuration du Timer
//    TIM2->PSC = 35999;  // Préscaler
//    TIM2->ARR = 999;    // Valeur de rechargement automatique

//    // Démarrage du Timer
//    TIM2->CR1 |= TIM_CR1_CEN; // Activer le compteur CEN=Clock Enable
    

//		MyGPIO_Struct_TypeDef led, button;
//	    // Initialisation de la LED sur PA5 (output push-pull)
//    led.GPIO = GPIOA;
//    led.GPIO_Pin = 5;
//    led.GPIO_Conf = Out_Ppull;
//    MyGPIO_Init(&led);

//    // Initialisation du bouton poussoir sur PC12 (input floating)
//    button.GPIO = GPIOC;
//    button.GPIO_Pin =12 ;
//    button.GPIO_Conf = In_Floating;
//    MyGPIO_Init(&button);
		MyGPIO_Struct_TypeDef led;
	  // Initialisation de la LED sur PA5 (output push-pull)
    led.GPIO = GPIOA;
    led.GPIO_Pin = 0;
    led.GPIO_Conf = AltOut_Ppull;
    MyGPIO_Init(&led);
		
	  MyTimer_Struct_TypeDef tim;
	  tim.Timer=TIM2;
//    tim.ARR=35999;
//	  tim.PSC=999;
		tim.ARR=89;
	  tim.PSC=7;
	  MyTimer_Base_Init(&tim);
//		
//	  TIM2->DIER |= TIM_DIER_UIE; //demander au coeur d'activer l'interruption
//    //Configuration de l’interruption sur le coeur
//    NVIC->ISER[0] |= NVIC_ISER_SETENA_28; // activation de l'interruption par le coeur 
//    NVIC->IPR[28] |= (7 << 4);// interruption mis en priorité 7

		//MyTimer_ActivateIT1(TIM2,7,Toggle_LED);

		//NVIC_EnableIRQ(TIM3_IRQn);
    //NVIC_SetPriority(TIM3_IRQn, 7); // Définir la priorité (1 est plus élevé que 0)
		MyTimer_PWM(tim.Timer,1);
		MyTimer_SetDutyCycle(tim.Timer ,1 ,20);

	  MyTimer_Base_Start(TIM2);
	  

    while(1) {
//			if (TIM2->SR!=0){
//				MyGPIO_Toggle(led.GPIO,led.GPIO_Pin);
//				TIM2->SR=0;
//			}
			int i;
			for(i=0;i<100;i++){
				MyTimer_SetDutyCycle(tim.Timer ,1 ,i);
				delay(100000);
			}
			for(i=100;i>0;i--){
				MyTimer_SetDutyCycle(tim.Timer ,1 ,i);
				delay(100000);
			}
    }



}