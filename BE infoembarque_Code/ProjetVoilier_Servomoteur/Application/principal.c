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
	
		int Teta=0;
		int alpha=0;
		MyGPIO_Struct_TypeDef Consigne_S;//On met notre consigne du servo moteur sur B0 vu quon utilise TIM3
    Consigne_S.GPIO = GPIOB;
    Consigne_S.GPIO_Pin = 0;
    Consigne_S.GPIO_Conf = AltOut_Ppull;
    MyGPIO_Init(&Consigne_S);
		
	  MyTimer_Struct_TypeDef tim_SV;//On définit notre timer sur le TIM3
	  tim_SV.Timer=TIM3;
		tim_SV.ARR=1999;
	  tim_SV.PSC=719;
	  MyTimer_Base_Init(&tim_SV);
		
		MyTimer_PWM(tim_SV.Timer,3);//On met en marche la PWM
		MyTimer_Base_Start(TIM3);
		int encoder_position=0;
			
    while (1) {
			  //Lire le signal de référence de l'encodeur
			  z= MyGPIO_Read(index.GPIO,index.GPIO_Pin);
        // Lire la position de l'encodeur
        encoder_position = MyTimer_Encoder_Read(TIM2);
			  if(z==1){
					MyTimer_Encoder_Reset(); //EXTI et/ou AFIO a faire apres
		    }
				
				alpha= (encoder_position/4);
				
				if (alpha >180){
					alpha=360-alpha;
				}
				
				if (alpha >=0 & alpha<=45){
					Teta=0;
				}
				if (alpha >=45 & alpha<=180){
					Teta=90*alpha/(180-45) -90*45/(180-45);
				}
		
				MyTimer_SetDutyCycle(tim_SV.Timer ,3 ,(Teta/24)+5);
			
    }
}