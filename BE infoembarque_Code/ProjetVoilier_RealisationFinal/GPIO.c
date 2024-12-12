#include "stm32f10x.h"
#include "MyGPIO.h"

int GPIO(void)
{
   
//    RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN);
//    
//    // Configurer PA5 (LED verte) 
//    GPIOA->CRL &= ~(0xF << 20);  
//    GPIOA->CRL |= (0x3 << 20);
//		GPIOA->CRL &= ~(0xF << 24);  
//    GPIOA->CRL |= (0x3  << 24);
//    // Configurer PC13 (bouton poussoir)
//    GPIOC->CRH &= ~(0xF << 20);  
//    GPIOC->CRH |= (0x4 << 20);
//		GPIOC->CRH &= ~(0xF << 16);  
//    GPIOC->CRH |= (0x8 << 16); 
//    
//    // POUR ALLUMER LA PA5
////    GPIOA->ODR |= (1 << 5);
//		//GPIOA->ODR &= ~(1 << 6);

//    while (1)
//    {
//        // Lire l'état du bouton poussoir (PC13)
//        if ((GPIOC->IDR & (1 << 12)))  // Si bouton est pressé (PC13 est 0)
//        {
//            GPIOA->BSRR = (1 << 6);     // Allumer la LED (PA5)
//        }
//        else
//        {
//            GPIOA->BRR = (1 << 6);      // Éteindre la LED (PA5)
//        }
//    }

// Structure de configuration GPIO pour la LED et le bouton poussoir
    MyGPIO_Struct_TypeDef led, button;

    // Initialisation de la LED sur PA6 (output push-pull)
    led.GPIO = GPIOB;
    led.GPIO_Pin = 5;
    led.GPIO_Conf = Out_Ppull;
    MyGPIO_Init(&led);

    // Initialisation du bouton poussoir sur PC12 (input floating)
    button.GPIO = GPIOC;
    button.GPIO_Pin =12 ;
    button.GPIO_Conf = In_Floating;
    MyGPIO_Init(&button);

    while (1) {
        // Lire l'état du bouton poussoir et allumer/éteindre la LED en conséquence
        if (MyGPIO_Read(button.GPIO, button.GPIO_Pin)) {
            MyGPIO_Set(led.GPIO, led.GPIO_Pin);  // Allumer la LED
        } else {
            MyGPIO_Reset(led.GPIO, led.GPIO_Pin);  // Éteindre la LED
        }
			}
		}    