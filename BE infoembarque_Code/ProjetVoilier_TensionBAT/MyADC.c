#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyTimer.h"
#include "MyADC.h"

void configadc(int canal){
	  RCC->APB2ENR|=RCC_APB2ENR_ADC1EN; //définir une horloge pour l'adc1
    RCC->CFGR|=RCC_CFGR_ADCPRE_DIV6; //frequence  de l'adc a 12MHZ
  	ADC1->CR2|= ADC_CR2_ADON; //activer la conversion
	  ADC1->SQR1&=~(0xF<<20); // mettre L à 0 pour ne faire qu'une seule conversion
	  ADC1->SQR3|=canal; //choix du canal 8 pour la conversion 
	  ADC1->CR2 |= ADC_CR2_CAL; //calibrer pour limiter les erreurs de mesure
    while (ADC1->CR2 & ADC_CR2_CAL); //attendre la fin de calibration
}

int convert_single(){
    ADC1->CR2 |= ADC_CR2_ADON; // lancement de la conversion
    while(!(ADC1->SR & ADC_SR_EOC) ); // attente de la fin de conversion
    ADC1->SR &= ~ADC_SR_EOC; // validation de la conversion
    return ADC1->DR & ~((0x0F) << 12); // retour de la conversion
}

int convert_cont(){
    ADC1->CR2 |= ADC_CR2_ADON; // lancement de la conversion
		ADC1->CR2 |=1<<1; //continu
    while(!(ADC1->SR & ADC_SR_EOC) ); // attente de la fin de conversion
    ADC1->SR &= ~ADC_SR_EOC; // validation de la conversion
    return ADC1->DR & ~((0x0F) << 12); // retour de la conversion
}