#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyTimer.h"
#include "MyADC.h"

int ADC(void)
{ 
//	  RCC->APB2ENR|=RCC_APB2ENR_ADC1EN; //définir une horloge pour l'adc1
//    RCC->CFGR|=RCC_CFGR_ADCPRE_DIV6; //frequence  de l'adc a 12MHZ
//  	ADC1->CR2|= ADC_CR2_ADON; //activer la conversion
//	  ADC1->SQR1&=~(0xF<<20); // mettre L à 0 pour ne faire qu'une seule conversion
//	  ADC1->SQR3|=8; //choix du canal 8 pour la conversion 
//	  ADC1->CR2 |= ADC_CR2_CAL; //calibrer pour limiter les erreurs de mesure*
//    while (ADC1->CR2 & ADC_CR2_CAL); //attendre la fin de calibration
    
	  MyGPIO_Struct_TypeDef led,potentio;
	  // Initialisation de la LED sur PA5 (output push-pull)
    led.GPIO = GPIOA;
    led.GPIO_Pin = 0;
    led.GPIO_Conf = AltOut_Ppull;
    MyGPIO_Init(&led);
	
		potentio.GPIO = GPIOB;
    potentio.GPIO_Pin = 0;
    potentio.GPIO_Conf = In_Analog;
    MyGPIO_Init(&potentio);
	  configadc(8);
	  convert_cont();//convertion continu
	  MyTimer_Struct_TypeDef tim;
	  tim.Timer=TIM2;
//    tim.ARR=35999;
//	  tim.PSC=999;
		tim.ARR=89;
	  tim.PSC=7;
	  MyTimer_Base_Init(&tim);
		MyTimer_PWM(tim.Timer,1);

	  MyTimer_Base_Start(TIM2);
		int res;
    while(1) {
			 res=(ADC1->DR & ~((0x0F) << 12))*100/(4095);
       MyTimer_SetDutyCycle(tim.Timer ,1 ,res);
    }



}