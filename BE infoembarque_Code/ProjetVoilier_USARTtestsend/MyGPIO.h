#ifndef MYGPIO_H
#define MYGPIO_H

#include "stm32f10x.h"

typedef struct {
    GPIO_TypeDef * GPIO; // Pointeur vers le port GPIO (ex. GPIOA, GPIOB)
    char GPIO_Pin;       // Num�ro de la broche (de 0 � 15)
    char GPIO_Conf;      // Configuration de la broche (voir ci-dessous)
} MyGPIO_Struct_TypeDef;

// D�finitions des modes de configuration des GPIO
#define In_Floating 0x04    // Entr�e flottante
#define In_PullDown 0x08    // Entr�e avec r�sistance pull-down
#define In_PullUp 0x09      // Entr�e avec r�sistance pull-up
#define In_Analog 0x00      // Entr�e analogique
#define Out_Ppull 0x02      // Sortie push-pull
#define Out_OD 0x06         // Sortie open-drain
#define AltOut_Ppull 0x0A   // Fonction alternative push-pull
#define AltOut_OD 0x0E      // Fonction alternative open-drain

// D�clarations des fonctions du driver
void MyGPIO_Init(MyGPIO_Struct_TypeDef *GPIOStructPtr);
int MyGPIO_Read(GPIO_TypeDef *GPIO, char GPIO_Pin); // Renvoie 0 ou une valeur diff�rente de 0
void MyGPIO_Set(GPIO_TypeDef *GPIO, char GPIO_Pin);
void MyGPIO_Reset(GPIO_TypeDef *GPIO, char GPIO_Pin);
void MyGPIO_Toggle(GPIO_TypeDef *GPIO, char GPIO_Pin);

#endif
