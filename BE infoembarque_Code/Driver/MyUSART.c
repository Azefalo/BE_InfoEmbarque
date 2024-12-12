#include "MyGPIO.h"
#include "MyUSART.h"
#include "stdio.h"
//void UART1_Init(void) {
//    // Activer l'horloge pour l'USART1 et le port GPIOA
//    RCC->APB2ENR |= RCC_APB2ENR_USART1EN; 
//    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; 

//    // Configurer PA10 (RX) en entr�e flottante (r�cepteur)
//    GPIOA->CRH &= ~GPIO_CRH_MODE10;
//    GPIOA->CRH |= GPIO_CRH_CNF10_0; // PA10 en entr�e flottante
//	
//    USART1->CR1 |= USART_CR1_UE; // Activer l'USART
//    USART1->CR1 &= ~USART_CR1_M; // 8 bits de donn�es
//    USART1->CR2 &= USART_CR2_STOP; // 1 bit de stop
//    USART1->BRR |= 468 << 4; // Baud rate � 9600 bps
//    USART1->BRR |= 75; // Baud rate � 9600 bps

//    USART1->CR1 |= USART_CR1_RE; // Activer la r�ception
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

//    // Configuration de PA10 (RX) en entr�e flottante
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
    USART1->CR1 &= ~USART_CR1_M;           // 8 bits de donn�es
    USART1->CR2 &= ~USART_CR2_STOP;        // 1 bit de stop
    USART1->BRR = 0x1D4C;                  // Baud rate � 9600 bauds (pour 72 MHz)

    USART1->CR1 |= USART_CR1_TE | USART_CR1_RE;  // Activer transmission et r�ception
    USART1->CR1 |= USART_CR1_RXNEIE;       // Activer interruption RXNE
    NVIC_EnableIRQ(USART1_IRQn);           // Activer interruption dans le NVIC
}
// Fonction pour recevoir un octet via UART1
char UART1_Receive(void) {
    while (!(USART1->SR & USART_SR_RXNE)); // Attendre que les donn�es soient pr�tes
    return (char)(USART1->DR); // Lire la donn�e re�ue
}

void UART1_SendChar(char c) {
    while (!(USART1->SR & USART_SR_TXE));  // Attendre que le registre soit pr�t
    USART1->DR = c;                       // Envoyer le caract�re
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

void UART1_SendDatatime(int8_t timeh, int8_t timem, int8_t times) {
    char buffer[32];
	snprintf(buffer, sizeof(buffer), "%d:%d:%d\n", timeh, timem, times); //conversion de la valeur en string
    UART1_SendString(buffer);
}