#include "MyGPIO.h"
#include "MyUSART.h"
#include "stdio.h"
//void UART1_Init(void) {
//    // Activer l'horloge pour l'USART1 et le port GPIOA
//    RCC->APB2ENR |= RCC_APB2ENR_USART1EN; 
//    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; 

//    // Configurer PA10 (RX) en entrée flottante (récepteur)
//    GPIOA->CRH &= ~GPIO_CRH_MODE10;
//    GPIOA->CRH |= GPIO_CRH_CNF10_0; // PA10 en entrée flottante
//	
//    USART1->CR1 |= USART_CR1_UE; // Activer l'USART
//    USART1->CR1 &= ~USART_CR1_M; // 8 bits de données
//    USART1->CR2 &= USART_CR2_STOP; // 1 bit de stop
//    USART1->BRR |= 468 << 4; // Baud rate à 9600 bps
//    USART1->BRR |= 75; // Baud rate à 9600 bps

//    USART1->CR1 |= USART_CR1_RE; // Activer la réception
//}
void UART1_Init(void) {
    // Activer les horloges pour USART1 et GPIOA
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN;

    // Configuration de PA9 (TX) en mode alternatif push-pull
//    GPIOA->CRH &= ~GPIO_CRH_MODE9;
//    GPIOA->CRH |= GPIO_CRH_MODE9_1;  
//    GPIOA->CRH &= ~GPIO_CRH_CNF9;
//    GPIOA->CRH |= GPIO_CRH_CNF9_1;

	  MyGPIO_Struct_TypeDef tx;
    // Configuration de PA9 comme TX (output push-pull)
    tx.GPIO = GPIOA;
    tx.GPIO_Pin = 9;
    tx.GPIO_Conf = AltOut_Ppull;
    MyGPIO_Init(&tx);

//    // Configuration de PA10 (RX) en entrée flottante
//    GPIOA->CRH &= ~GPIO_CRH_MODE10;
//    GPIOA->CRH &= ~GPIO_CRH_CNF10;
//    GPIOA->CRH |= GPIO_CRH_CNF10_0;
	
	  MyGPIO_Struct_TypeDef rx;
    // Configuration de PA10 comme TX (output push-pull)
    rx.GPIO = GPIOA;
    rx.GPIO_Pin = 10;
    rx.GPIO_Conf = In_Floating;
    MyGPIO_Init(&rx);

    // Configuration de l'USART1
    USART1->CR1 |= USART_CR1_UE;           // Activer l'USART
    USART1->CR1 &= ~USART_CR1_M;           // 8 bits de données
    USART1->CR2 &= ~USART_CR2_STOP;        // 1 bit de stop
    USART1->BRR = 0x1D4C;                  // Baud rate à 9600 bauds (pour 72 MHz)

    USART1->CR1 |= USART_CR1_TE | USART_CR1_RE;  // Activer transmission et réception
    USART1->CR1 |= USART_CR1_RXNEIE;       // Activer interruption RXNE
    NVIC_EnableIRQ(USART1_IRQn);           // Activer interruption dans le NVIC
}
// Fonction pour recevoir un octet via UART1
char UART1_Receive(void) {
    while (!(USART1->SR & USART_SR_RXNE)); // Attendre que les données soient prêtes
    return (char)(USART1->DR); // Lire la donnée reçue
}

void UART1_SendChar(char c) {
    while (!(USART1->SR & USART_SR_TXE));  // Attendre que le registre soit prêt
    USART1->DR = c;                       // Envoyer le caractère
}

void UART1_SendString(const char *str) {
    while (*str) {
        UART1_SendChar(*str++);
    }
}

void UART1_SendData(int8_t direction, int8_t battery, int8_t roll_angle) {
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%d,%d,%d\n", direction, battery, roll_angle); //conversion de la valeur en string
    UART1_SendString(buffer);
}