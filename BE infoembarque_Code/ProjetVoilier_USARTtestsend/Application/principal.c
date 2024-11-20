

//#include "stm32f10x.h"
//#include "MyGPIO.h"
//#include "MyTimer.h"

//// Fonction pour initialiser l'UART1
//void UART1_Init(void) {
//    // Activer l'horloge pour USART1 et GPIOA
//    RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // Activer l'horloge pour USART1
//    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;  // Activer l'horloge pour GPIOA

//    // Configurer PA9 (TX) comme sortie alternative push-pull
//    MyGPIO_Struct_TypeDef tx;

//    // Configuration de PA2 comme TX (output push-pull)
//    tx.GPIO = GPIOA;
//    tx.GPIO_Pin = 9;
//    tx.GPIO_Conf = AltOut_Ppull;
//    MyGPIO_Init(&tx);

//    // Configurations de l'USART
//    USART1->CR1 |= USART_CR1_UE;         // Activer l'USART
//    USART1->CR1 &= ~USART_CR1_M;         // Configurer le format des données : 8 bits
//    USART1->CR2 &= ~USART_CR2_STOP;      // Configurer 1 bit de stop

//    // Configurer la vitesse en bauds (9600 bps, pour un clock à 72 MHz)
//    USART1->BRR = 0x1D4C;

//    // Activer la transmission
//    USART1->CR1 |= USART_CR1_TE;         // Activer l'émetteur
//}

//// Fonction pour envoyer un caractère via UART1
//void UART1_SendChar(char c) {
//    while (!(USART1->SR & USART_SR_TXE)); // Attendre que le buffer de transmission soit vide
//    USART1->DR = c;                       // Envoyer le caractère
//}

//// Fonction pour envoyer l'alphabet complet
//void UART1_SendAlphabet(void) {
//    char letter = 'A';

//    while (1) {
//        UART1_SendChar(letter);           // Envoyer la lettre actuelle
//        letter++;                          // Passer à la lettre suivante

//        if (letter > 'Z') {               // Si on dépasse 'Z', recommencer à 'A'
//            letter = 'A';
//        }

//        for (volatile int i = 0; i < 500000; i++); // Petit délai entre l'envoi des lettres
//    }
//}

//int main(void) {
//    UART1_Init(); // Initialiser l'UART1

//    UART1_SendAlphabet(); // Envoyer l'alphabet de façon continue

//    return 0;
//}

//commande du servomoteur
#include "stm32f10x.h"
#include "MyUSART.h"



int main(void) {
    UART1_Init();
	  
    char receivedData;

    while (1) {
        receivedData = UART1_Receive(); // Recevoir un caractère
			  
    }

    return 0;
}