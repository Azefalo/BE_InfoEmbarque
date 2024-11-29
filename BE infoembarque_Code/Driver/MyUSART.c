#include "MyGPIO.h"
#include "MyUSART.h"
#include "stdio.h"

void UART1_Init(void) {
    // Activer l'horloge pour l'USART1 et le port GPIOA
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN; 
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; 

    // Configurer PA10 (TX) en entr�e flottante (�metteur)
    GPIOA->CRH &= ~GPIO_CRH_MODE10;
    GPIOA->CRH |= GPIO_CRH_CNF10_0; // PA10 en entr�e flottante
	
	  // Configurer PA9 en mode Input Floating pour RX
	  GPIOA->CRH &= ~(GPIO_CRH_MODE9 | GPIO_CRH_CNF9);  // Effacer les bits pour PA9
    GPIOA->CRH |= GPIO_CRH_CNF9_0;  // Input Floating (mode 01)
	
    USART1->CR1 |= USART_CR1_UE; // Activer l'USART
    USART1->CR1 &= ~USART_CR1_M; // 8 bits de donn�es
    USART1->CR2 &= USART_CR2_STOP; // 1 bit de stop
    USART1->BRR |= 468 << 4; // Baud rate � 9600 bps
    USART1->BRR |= 75; // Baud rate � 9600 bps

    USART1->CR1 |= USART_CR1_RE; // Activer la r�ception
    USART1->CR1 |= USART_CR1_RXNEIE;            // Activer l'interruption pour RXNE

    // Activer l'interruption dans NVIC
    NVIC_EnableIRQ(USART1_IRQn);
}

//void UART1_Init(void) {
//    // Activer l'horloge pour USART1
//    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

//    // Configuration des broches pour USART1 (TX: PA9, RX: PA10)
//    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;  // Activer l'horloge GPIOA
//    GPIOA->CRH &= ~(GPIO_CRH_CNF9 | GPIO_CRH_MODE9);  // Clear TX pin config
//    GPIOA->CRH |= GPIO_CRH_MODE9_1 | GPIO_CRH_CNF9_1; // TX en mode alternatif push-pull
//    GPIOA->CRH &= ~(GPIO_CRH_CNF10);                 // Clear RX pin config
//    GPIOA->CRH |= GPIO_CRH_CNF10_0;                  // RX en mode input floating

//    // Configurer USART1 (baudrate, data bits, stop bits, etc.)
//    USART1->BRR = 72000000 / 9600;  // Configurer le baudrate pour 9600 bps (72 MHz clock)
//    USART1->CR1 |= USART_CR1_RE | USART_CR1_TE;  // Activer la r�ception et la transmission
//    USART1->CR1 |= USART_CR1_UE;                // Activer USART1
//    USART1->CR1 |= USART_CR1_RXNEIE;            // Activer l'interruption pour RXNE

//    // Activer l'interruption dans NVIC
//    NVIC_EnableIRQ(USART1_IRQn);
//}

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

void UART1_SendData(int8_t direction, uint8_t battery, int8_t roll_angle) {
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%d,%d,%d\n", direction, battery, roll_angle); //conversion de la valeur en string
    UART1_SendString(buffer);
}