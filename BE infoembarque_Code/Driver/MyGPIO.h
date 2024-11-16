#ifndef MYGPIO_H
#define MYGPIO_H

#include "stm32f10x.h"

typedef struct {
    GPIO_TypeDef * GPIO; // Pointeur vers le port GPIO (ex. GPIOA, GPIOB)
    char GPIO_Pin;       // Numéro de la broche (de 0 à 15)
    char GPIO_Conf;      // Configuration de la broche (voir ci-dessous)
} MyGPIO_Struct_TypeDef;

// Définitions des modes de configuration des GPIO
#define In_Floating 0x04    // Entrée flottante
#define In_PullDown 0x08    // Entrée avec résistance pull-down
#define In_PullUp 0x09      // Entrée avec résistance pull-up
#define In_Analog 0x00      // Entrée analogique
#define Out_Ppull 0x02      // Sortie push-pull
#define Out_OD 0x06         // Sortie open-drain
#define AltOut_Ppull 0x0A   // Fonction alternative push-pull
#define AltOut_OD 0x0E      // Fonction alternative open-drain

// Déclarations des fonctions du driver
void MyGPIO_Init(MyGPIO_Struct_TypeDef *GPIOStructPtr);
int MyGPIO_Read(GPIO_TypeDef *GPIO, char GPIO_Pin); // Renvoie 0 ou une valeur différente de 0
void MyGPIO_Set(GPIO_TypeDef *GPIO, char GPIO_Pin);
void MyGPIO_Reset(GPIO_TypeDef *GPIO, char GPIO_Pin);
void MyGPIO_Toggle(GPIO_TypeDef *GPIO, char GPIO_Pin);

#endif
