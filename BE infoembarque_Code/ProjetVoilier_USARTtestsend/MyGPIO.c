#include "MyGPIO.h"

// Initialisation du GPIO
void MyGPIO_Init(MyGPIO_Struct_TypeDef *GPIOStructPtr) {
    // Activation de l'horloge pour le port GPIO correspondant
    if (GPIOStructPtr->GPIO == GPIOA) {
        RCC->APB2ENR |= (1 << 2);  // Activer l'horloge pour GPIOA
    } else if (GPIOStructPtr->GPIO == GPIOB) {
        RCC->APB2ENR |= (1 << 3);  // Activer l'horloge pour GPIOB
    } else if (GPIOStructPtr->GPIO == GPIOC) {
        RCC->APB2ENR |= (1 << 4);  // Activer l'horloge pour GPIOC
    }
    
    // Configuration de la broche GPIO
    if (GPIOStructPtr->GPIO_Pin < 8) { // Broche de 0 à 7 (config dans CRL)
        GPIOStructPtr->GPIO->CRL &= ~(0xF << (GPIOStructPtr->GPIO_Pin * 4));  // Effacer la configuration actuelle
        GPIOStructPtr->GPIO->CRL |= (GPIOStructPtr->GPIO_Conf << (GPIOStructPtr->GPIO_Pin * 4));  // Configurer
			
			  if (GPIOStructPtr->GPIO_Conf==In_PullUp){// Gestion de l'exception PULL UP
						GPIOStructPtr->GPIO->CRL |= (0x08 << (GPIOStructPtr->GPIO_Pin * 4));
						GPIOStructPtr->GPIO->ODR=1;
				}
				else if (GPIOStructPtr->GPIO_Conf==In_PullDown){// Gestion de l'exception PULL DOWN
						GPIOStructPtr->GPIO->ODR=0;
				}
    } else {  // Broche de 8 à 15 (config dans CRH)
        GPIOStructPtr->GPIO->CRH &= ~(0xF << ((GPIOStructPtr->GPIO_Pin - 8) * 4));  // Effacer la configuration actuelle
        GPIOStructPtr->GPIO->CRH |= (GPIOStructPtr->GPIO_Conf << ((GPIOStructPtr->GPIO_Pin - 8) * 4));  // Configurer
    }
}

// Lecture de l'état d'une broche GPIO
int MyGPIO_Read(GPIO_TypeDef *GPIO, char GPIO_Pin) {
    if (GPIO->IDR & (1 << GPIO_Pin)) { // Vérifier si la broche est à l'état haut
        return 1;
    } else {
        return 0;
    }
}

// Activer une broche GPIO (mettre à 1)
void MyGPIO_Set(GPIO_TypeDef *GPIO, char GPIO_Pin) {
    GPIO->BSRR = (1 << GPIO_Pin);  // Régistre BSRR pour mettre à 1
}

// Désactiver une broche GPIO (mettre à 0)
void MyGPIO_Reset(GPIO_TypeDef *GPIO, char GPIO_Pin) {
    GPIO->BRR = (1 << GPIO_Pin);  // Régistre BRR pour mettre à 0
}

// Inverser l'état d'une broche GPIO
void MyGPIO_Toggle(GPIO_TypeDef *GPIO, char GPIO_Pin) {
    GPIO->ODR ^= (1 << GPIO_Pin);  // XOR sur le régistre ODR pour inverser l'état
}