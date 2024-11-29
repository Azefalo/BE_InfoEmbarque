
#include "stm32f10x.h"
#include "MyUSART.h"
#include "MyGPIO.h"
#include "MyADC.h"
#include <stdint.h>  // Pour uint8_t, int8_t

#define seuilmin 9 //353 et 358  en hexa
#define seuilmax 12 //463 et 474

//int main(void) {
//    UART1_Init();
//	
//	  int8_t direction = 0;
//    int batterylevel = 100;    // Niveau de batterie simul�
//    int8_t roll_angle = 0;    // Angle de roulis simul�
//    //char receivedData;
//	
//	  MyGPIO_Struct_TypeDef battery;
//	  battery.GPIO = GPIOA;
//    battery.GPIO_Pin = 7;
//    battery.GPIO_Conf = In_Analog;
//    MyGPIO_Init(&battery);
//	
//	  configadc(7); // PA7 est sur le canal 7 de ADC1
//	  convert_cont();//convertion continu
//    

//    while (1) {
//	  batterylevel=(ADC1->DR & ~((0x0F) << 12))*100/(4095);
//		//if(batterylevel>=8.62 && batterylevel<=8.74)
//    UART1_SendData(direction,batterylevel,roll_angle);
//			  
//    }

//    return 0;
//}



volatile int8_t received_direction = 0;  // Variable pour stocker la direction re�ue

// Fonction d'interruption pour la r�ception de donn�es
void USART1_IRQHandler(void) {
    if (USART1->SR & USART_SR_RXNE) {     // V�rifier si le registre de r�ception est pr�t
        received_direction = (int8_t)USART1->DR;  // Lire la direction re�ue depuis la t�l�commande
    }
}

int main(void) {
    // Initialisation de l'UART
    UART1_Init();

    int8_t direction = 0;
    uint8_t batterylevel = 100;    // Niveau de batterie simul�
    int8_t roll_angle = 0;    // Angle de roulis simul�
    	
	  MyGPIO_Struct_TypeDef battery;
	  battery.GPIO = GPIOA;
    battery.GPIO_Pin = 7;
    battery.GPIO_Conf = In_Analog;
    MyGPIO_Init(&battery);
	
	  configadc(7); // PA7 est sur le canal 7 de ADC1
	  convert_cont();//convertion continu
	
    while (1) {
//			batterylevel=(ADC1->DR & ~((0x0F) << 12))*100*3.6/(4095);
			  batterylevel= ((ADC1->DR - 353) * 100.0) / (474 - 353);
        // Envoyer les donn�es toutes les 100 ms
        UART1_SendData(direction, batterylevel, roll_angle);
        for (volatile int i = 0; i < 5000000; i++);  // Temporisation d'environ 100 ms
    }

    return 0;
}
