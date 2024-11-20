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
//    // Avec un clock APB1 à 36 MHz (par défaut pour STM32F103RB)
//    USART2->BRR = 0xEA6;                // Calcul pour 9600 bps (36 MHz / (16 * 9600))

//    // Activer la transmission
//    USART2->CR1 |= USART_CR1_TE;         // Activer le mode transmission
//}

//// Fonction pour envoyer un caractère via UART2
//void UART2_SendChar(char c) {
//    while (!(USART2->SR & USART_SR_TXE)); // Attendre que le buffer de transmission soit vide
//    USART2->DR = c;                       // Envoyer le caractère
//}

//// Fonction pour envoyer l'alphabet en boucle
//void UART2_SendAlphabet(void) {
//    char letter = 'A';

//    while (1) {
//        UART2_SendChar(letter);           // Envoyer la lettre actuelle
//        letter++;                         // Passer à la lettre suivante

//        if (letter > 'Z') {               // Si on atteint 'Z', repartir à 'A'
//            letter = 'A';
//        }

//        for (volatile int i = 0; i < 500000; i++); // Petit délai entre les lettres
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

void UART1_Init(void) {
    // Ativar o clock para USART1 e GPIOA
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN; 
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; 

    // Configurar PA9 (TX) como saída alternativa push-pull
    GPIOA->CRH &= ~GPIO_CRH_MODE9;       // Limpar bits de configuração
    GPIOA->CRH |= GPIO_CRH_MODE9_1;      // PA9 em modo de saída a 2MHz
    GPIOA->CRH |= GPIO_CRH_CNF9_1;       // PA9 como função alternativa push-pull

    // Configurações do USART
    USART1->CR1 |= USART_CR1_UE;         // Habilitar o USART
    USART1->CR1 &= ~USART_CR1_M;         // 8 bits de dados
    USART1->CR2 &= ~USART_CR2_STOP;      // 1 bit de parada

    // Configurar baud rate para 9600 bps (presume clock de 72MHz)
    USART1->BRR = 0x1D4C;

    // Habilitar a transmissão
    USART1->CR1 |= USART_CR1_TE;         // Habilitar o transmissor
}

// Função para enviar um caractere via UART1
void UART1_SendChar(char c) {
    while (!(USART1->SR & USART_SR_TXE)); // Esperar o buffer de transmissão estar vazio
    USART1->DR = c;                       // Enviar o caractere
}

// Função para enviar o alfabeto completo
void UART1_SendAlphabet(void) {
    char letter = 'A';

    while (1) {
        UART1_SendChar(letter);           // Enviar letra atual
        letter++;                          // Próxima letra

        if (letter > 'Z') {               // Se chegou em 'Z', reinicia para 'A'
            letter = 'A';
        }

        for (volatile int i = 0; i < 500000; i++); // Pequeno delay entre letras
    }
}

int main(void) {
    UART1_Init(); // Inicializar UART1

    UART1_SendAlphabet(); // Enviar o alfabeto de forma contínua

    return 0;
}

//#include "stm32f10x.h"
//#include "MyGPIO.h"
//#include "MyTimer.h"

//void UART1_Init(void) {
//    // Activer l'horloge pour l'USART1 et le port GPIOA
//    RCC->APB2ENR |= RCC_APB2ENR_USART1EN; 
//    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; 

//    // Configurer PA10 (RX) en entrée flottante (récepteur)
//    GPIOA->CRH &= ~GPIO_CRH_MODE10;
//    GPIOA->CRH |= GPIO_CRH_CNF10_0; // PA10 en entrée flottante

//    USART1->CR1 |= USART_CR1_UE; // Activer l'USART
//    USART1->CR1 &= ~USART_CR1_M; // 8 bits de données
//    USART1->CR2 &= USART_CR2_STOP; // 1 bit de stop
//    USART1->BRR |= 468 << 4; // Baud rate à 9600 bps
//    USART1->BRR |= 75; // Baud rate à 9600 bps

//    USART1->CR1 |= USART_CR1_RE; // Activer la réception
//}

//// Fonction pour recevoir un octet via UART1
//char UART1_Receive(void) {
//    while (!(USART1->SR & USART_SR_RXNE)); // Attendre que les données soient prêtes
//    return (char)(USART1->DR); // Lire la donnée reçue
//}

//int main(void) {
//    UART1_Init();
//    char receivedData;

//    while (1) {
//        receivedData = UART1_Receive(); // Recevoir un caractère
//        // Vous pouvez ajouter du code pour afficher ou traiter les données reçues
//    }

//    return 0;
//}