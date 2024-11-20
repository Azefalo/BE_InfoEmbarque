//#include "stm32f10x.h"
//#include "MyGPIO.h"
//#include "MyTimer.h"

//void UART2_Init(void) {
//    // Activer l'horloge pour USART2 et GPIOA
//    RCC->APB1ENR |= RCC_APB1ENR_USART2EN; // Activer l'horloge pour USART2
//    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;  // Activer l'horloge pour GPIOA

//    MyGPIO_Struct_TypeDef tx;

//    // Configuration de PA2 comme TX (output push-pull)
//    tx.GPIO = GPIOA;
//    tx.GPIO_Pin = 2;
//    tx.GPIO_Conf = AltOut_Ppull;
//    MyGPIO_Init(&tx);

//    // Configurer l'USART2
//    USART2->CR1 |= USART_CR1_UE;         // Activer l'USART
//    USART2->CR1 &= ~USART_CR1_M;         // Mode 8 bits
//    USART2->CR2 &= ~USART_CR2_STOP;      // 1 bit de stop

//    // Configurer le baud rate pour 9600 bps
//    // Avec un clock APB1 � 36 MHz (par d�faut pour STM32F103RB)
//    USART2->BRR = 0xEA6;                // Calcul pour 9600 bps (36 MHz / (16 * 9600))

//    // Activer la transmission
//    USART2->CR1 |= USART_CR1_TE;         // Activer le mode transmission
//}

//// Fonction pour envoyer un caract�re via UART2
//void UART2_SendChar(char c) {
//    while (!(USART2->SR & USART_SR_TXE)); // Attendre que le buffer de transmission soit vide
//    USART2->DR = c;                       // Envoyer le caract�re
//}

//// Fonction pour envoyer l'alphabet en boucle
//void UART2_SendAlphabet(void) {
//    char letter = 'A';

//    while (1) {
//        UART2_SendChar(letter);           // Envoyer la lettre actuelle
//        letter++;                         // Passer � la lettre suivante

//        if (letter > 'Z') {               // Si on atteint 'Z', repartir � 'A'
//            letter = 'A';
//        }

//        for (volatile int i = 0; i < 500000; i++); // Petit d�lai entre les lettres
//    }
//}

//int main(void) {
//    UART2_Init(); // Initialiser UART2

//    UART2_SendAlphabet(); // Envoyer l'alphabet en boucle

//    return 0;
//}

#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyTimer.h"

// Fonction pour initialiser l'UART1
void UART1_Init(void) {
    // Activer l'horloge pour USART1 et GPIOA
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // Activer l'horloge pour USART1
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;  // Activer l'horloge pour GPIOA

    // Configurer PA9 (TX) comme sortie alternative push-pull
    MyGPIO_Struct_TypeDef tx;

    // Configuration de PA2 comme TX (output push-pull)
    tx.GPIO = GPIOA;
    tx.GPIO_Pin = 9;
    tx.GPIO_Conf = AltOut_Ppull;
    MyGPIO_Init(&tx);

    // Configurations de l'USART
    USART1->CR1 |= USART_CR1_UE;         // Activer l'USART
    USART1->CR1 &= ~USART_CR1_M;         // Configurer le format des donn�es : 8 bits
    USART1->CR2 &= ~USART_CR2_STOP;      // Configurer 1 bit de stop

    // Configurer la vitesse en bauds (9600 bps, pour un clock � 72 MHz)
    USART1->BRR = 0x1D4C;

    // Activer la transmission
    USART1->CR1 |= USART_CR1_TE;         // Activer l'�metteur
}

// Fonction pour envoyer un caract�re via UART1
void UART1_SendChar(char c) {
    while (!(USART1->SR & USART_SR_TXE)); // Attendre que le buffer de transmission soit vide
    USART1->DR = c;                       // Envoyer le caract�re
}

// Fonction pour envoyer l'alphabet complet
void UART1_SendAlphabet(void) {
    char letter = 'A';

    while (1) {
        UART1_SendChar(letter);           // Envoyer la lettre actuelle
        letter++;                          // Passer � la lettre suivante

        if (letter > 'Z') {               // Si on d�passe 'Z', recommencer � 'A'
            letter = 'A';
        }

        for (volatile int i = 0; i < 500000; i++); // Petit d�lai entre l'envoi des lettres
    }
}

int main(void) {
    UART1_Init(); // Initialiser l'UART1

    UART1_SendAlphabet(); // Envoyer l'alphabet de fa�on continue

    return 0;
}

//#include "stm32f10x.h"
//#include "MyGPIO.h"
//#include "MyTimer.h"

//void UART1_Init(void) {
//    // Activer l'horloge pour l'USART1 et le port GPIOA
//    RCC->APB2ENR |= RCC_APB2ENR_USART1EN; 
//    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; 

//    // Configurer PA10 (RX) en entr�e flottante (r�cepteur)
//    GPIOA->CRH &= ~GPIO_CRH_MODE10;
//    GPIOA->CRH |= GPIO_CRH_CNF10_0; // PA10 en entr�e flottante

//    USART1->CR1 |= USART_CR1_UE; // Activer l'USART
//    USART1->CR1 &= ~USART_CR1_M; // 8 bits de donn�es
//    USART1->CR2 &= USART_CR2_STOP; // 1 bit de stop
//    USART1->BRR |= 468 << 4; // Baud rate � 9600 bps
//    USART1->BRR |= 75; // Baud rate � 9600 bps

//    USART1->CR1 |= USART_CR1_RE; // Activer la r�ception
//}

//// Fonction pour recevoir un octet via UART1
//char UART1_Receive(void) {
//    while (!(USART1->SR & USART_SR_RXNE)); // Attendre que les donn�es soient pr�tes
//    return (char)(USART1->DR); // Lire la donn�e re�ue
//}

//int main(void) {
//    UART1_Init();
//    char receivedData;

//    while (1) {
//        receivedData = UART1_Receive(); // Recevoir un caract�re
//        // Vous pouvez ajouter du code pour afficher ou traiter les donn�es re�ues
//    }

//    return 0;
//}