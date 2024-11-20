////#include "stm32f10x.h"
////#include "MyGPIO.h"
////#include "MyTimer.h"

////void UART1_Init(void) {
//// 
////// Activer l'horloge pour l'USART1 et le port GPIOA
//// 
////RCC->APB2ENR |= RCC_APB2ENR_USART1EN; 
////RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; 


//// 
////// Configurer PA9 (TX) en mode alternatif push-pull (émetteur)
////GPIOA->CRH &= ~GPIO_CRH_MODE9;  // Effacer les bits de configuration de la vitesse de sortie pour PA9.
////GPIOA->CRH |= GPIO_CRH_MODE9_1;  // Définir PA9 en mode de sortie à 2 MHz (vitesse standard pour UART).
////GPIOA->CRH |= GPIO_CRH_CNF9_1;  // Configurer PA9 en mode alternatif push-pull pour la transmission (TX).

////// Configurer PA10 (RX) en entrée flottante (récepteur)
////GPIOA->CRH &= ~GPIO_CRH_MODE10;  // Effacer les bits de configuration de la vitesse de sortie pour PA10, car c'est une entrée.
////GPIOA->CRH |= GPIO_CRH_CNF10_0;  // Configurer PA10 en mode entrée flottante (pas de résistance pull-up ou pull-down).

////USART1->CR1 |= USART_CR1_UE; // Activation de l'USART
////USART1->CR1 &= ~USART_CR1_M; // Choix d'une taille de 8 bits de données
////USART1->CR2 &= USART_CR2_STOP; // Choix d'un seul bit de stop
////USART1->BRR |= 468 << 4; // Fixe le baud rate à 9600bps
////USART1->BRR |= 75; // Fixe le baud rate à 9600bps

////USART1->CR1 |= USART_CR1_TE; // Activer la transmission
//////USART1->CR1 |= USART_CR1_RE; // Activer la réception

////}

////void send(char data){
////    USART1->DR |= data; // Ecriture de la donnée dans le registre DR
////    while(!(USART1->SR & USART_SR_TC)) {} // Attente de la fin de transmission
////}


////// Fonction pour recevoir un octet via UART1
//////int8_t UART1_Receive(void) {
//////while (!(USART1->SR & USART_SR_RXNE)); // Attendre les données
//////return (int8_t)(USART1->DR); // Lire la donnée reçue
//////}


////int main(void) {
////UART1_Init();
////char data = 'A';
////char datar;

////  int cmpt = 0;

////  while (cmpt < 26) {
////     send(data+cmpt);
////		 //datar= UART1_Receive()+'0';
////     cmpt ++;
//// }
//// return 0;
////}
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