#include "stm32f10x.h"
#include "MyGPIO.h"

int TIMER(void)
{
   
  // RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN);
	//RCC->APB2ENR = RCC->APB2ENR | RCC_IOPAEN ;

    // Activer l'horloge pour le Timer 2
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    // Configuration du Timer
    TIM2->PSC = 35999;  // Préscaler
    TIM2->ARR = 999;    // Valeur de rechargement automatique

    // Démarrage du Timer
    TIM2->CR1 |= TIM_CR1_CEN; // Activer le compteur CEN=Clock Enable
    

		MyGPIO_Struct_TypeDef led, button;

    // Initialisation de la LED sur PA5 (output push-pull)
    led.GPIO = GPIOA;
    led.GPIO_Pin = 5;
    led.GPIO_Conf = Out_Ppull;
    MyGPIO_Init(&led);

    // Initialisation du bouton poussoir sur PC12 (input floating)
    button.GPIO = GPIOC;
    button.GPIO_Pin =12 ;
    button.GPIO_Conf = In_Floating;
    MyGPIO_Init(&button);
   while(1) {
			if (TIM2->SR!=0){
				MyGPIO_Toggle(led.GPIO,led.GPIO_Pin);
				TIM2->SR=0;
			}
        // Le code principal tourne ici
    }



}