#include "MyGPIO.h"
#include "MyTimer.h"
#include "stm32f10x.h"
#include "MyEncoder.h"




int main(void) {
	  //initialisation les pins
	  Encoder_GPIO_Init();
    // Initialisation du Timer 2 en mode encodeur
    Encoder_Timer_Init();
	  // Déclarer une broche avec Z pour reset
	  MyGPIO_Struct_TypeDef index;
	  // Initialisation de la LED sur PA5 (output push-pull)
    index.GPIO = GPIOA;
    index.GPIO_Pin = 4;
    index.GPIO_Conf = In_Floating;
    MyGPIO_Init(&index);
   	int z= MyGPIO_Read(index.GPIO,index.GPIO_Pin);
	

		
    while (1) {
			  //Lire le signal de référence de l'encodeur
			  z= MyGPIO_Read(index.GPIO,index.GPIO_Pin);
        // Lire la position de l'encodeur
        int16_t encoder_position = MyTimer_Encoder_Read(TIM2);
			  if(z==1){
					MyTimer_Encoder_Reset(); //EXTI et/ou AFIO à faire après
		    }
			
    }
}