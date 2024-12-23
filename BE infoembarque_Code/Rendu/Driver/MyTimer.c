#include "MyTimer.h"
#include "MyGPIO.h"

//active IT avec pointeur de fonction 
static void (*Timer_Callback)(void) = 0; // Pointeur de fonction pour le callback

void MyTimer_Base_Init(MyTimer_Struct_TypeDef *Timer)
{
  if(Timer->Timer == TIM1)
	{
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
		TIM1->ARR=Timer->ARR;
		TIM1->PSC=Timer->PSC;
	}
	  if(Timer->Timer == TIM2)
	{
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
		TIM2->ARR=Timer->ARR;
		TIM2->PSC=Timer->PSC;
	}
	  if(Timer->Timer == TIM3)
	{
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
		TIM3->ARR=Timer->ARR;
		TIM3->PSC=Timer->PSC;
	}
	  if(Timer->Timer == TIM4)
	{
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
		TIM4->ARR=Timer->ARR;
		TIM4->PSC=Timer->PSC;
	}
}	
void TIM1_UP_IRQHandler(void) { //programme d'interruption pour le timer2
    TIM1->SR &= ~TIM_SR_UIF;	
    if (Timer_Callback) {
    Timer_Callback(); // Appeler la fonction d�finie par l'utilisateur
    }
}

void TIM2_IRQHandler(void) { //programme d'interruption pour le timer2
    TIM2->SR &= ~TIM_SR_UIF;
        // Utilisez `encoder_position` pour ajuster la rotation totale si besoin
    if (Timer_Callback) {
    Timer_Callback(); // Appeler la fonction d�finie par l'utilisateur
    }
}

void TIM3_IRQHandler(void) { //programme d'interruption pour le timer3
    TIM3->SR &= ~TIM_SR_UIF;	
    if (Timer_Callback) {
    Timer_Callback(); // Appeler la fonction d�finie par l'utilisateur
    }
}
void TIM4_IRQHandler(void) { //programme d'interruption pour le timer4
    TIM4->SR &= ~TIM_SR_UIF;
    if (Timer_Callback) {
    Timer_Callback(); // Appeler la fonction d�finie par l'utilisateur
    }
}

void MyTimer_ActivateIT(TIM_TypeDef *Timer, char Prio)
{
	  if(Timer==TIM1)
		{
			TIM1->DIER |= TIM_DIER_UIE;
      NVIC_EnableIRQ(TIM1_UP_IRQn);
      NVIC_SetPriority(TIM1_UP_IRQn, Prio);
		}
	  if(Timer ==TIM2)
		{
			TIM2->DIER |= TIM_DIER_UIE;
      NVIC_EnableIRQ(TIM2_IRQn);
      NVIC_SetPriority(TIM2_IRQn, Prio);
		}
	  if(Timer ==TIM3)
		{
			TIM3->DIER |= TIM_DIER_UIE;
      NVIC_EnableIRQ(TIM3_IRQn);
      NVIC_SetPriority(TIM3_IRQn, Prio);
		}
		if(Timer ==TIM4)
		{
			TIM4->DIER |= TIM_DIER_UIE;
      NVIC_EnableIRQ(TIM4_IRQn);
      NVIC_SetPriority(TIM4_IRQn, Prio);
		}
		
}


void MyTimer_ActivateIT1(TIM_TypeDef *Timer, char Prio, void (*IT_function)(void)) {
    // Enregistrer le pointeur de fonction
    Timer_Callback = IT_function;
	  if(Timer==TIM1)
		{
			TIM1->DIER |= TIM_DIER_UIE;
      NVIC_EnableIRQ(TIM1_UP_IRQn);
      NVIC_SetPriority(TIM1_UP_IRQn, Prio);
		}
	  if(Timer ==TIM2)
		{
			TIM2->DIER |= TIM_DIER_UIE;
      NVIC_EnableIRQ(TIM2_IRQn);
      NVIC_SetPriority(TIM2_IRQn, Prio);
		}
	  if(Timer ==TIM3)
		{
			TIM3->DIER |= TIM_DIER_UIE;
      NVIC_EnableIRQ(TIM3_IRQn);
      NVIC_SetPriority(TIM3_IRQn, Prio);
		}
		if(Timer ==TIM4)
		{
			TIM4->DIER |= TIM_DIER_UIE;
      NVIC_EnableIRQ(TIM4_IRQn);
      NVIC_SetPriority(TIM4_IRQn, Prio);
		}
}

void MyTimer_PWM( TIM_TypeDef * Timer , char Channel ) 
{ 
	
	  if(Channel==1){
			Timer->CCMR1 &= ~TIM_CCMR1_OC1M;          // Effacer les bits du mode de comparaison
			Timer->CCMR1 |= (0x6 << 4);  // R�gler le mode PWM 1 (0x6)
			Timer->CCMR1 |= TIM_CCMR1_OC1PE;          // Activer le pr�chargement pour la comparaison
			Timer->CCER |= TIM_CCER_CC1E;             // Activer la capture/comparaison pour le canal 1 (activer le canal 1 )
		}
		if(Channel==2){
			Timer->CCMR1 &= ~TIM_CCMR1_OC2M;          // Effacer les bits du mode de comparaison
			Timer->CCMR1 |= (0x6 << 12);  // R�gler le mode PWM 1 (0x6)
			Timer->CCMR1 |= TIM_CCMR1_OC2PE;          // Activer le pr�chargement pour la comparaison
			Timer->CCER |= TIM_CCER_CC2E;             // Activer la capture/comparaison pour le canal 2 (activer le canal 2 )
		}
		
		if(Channel==3){
			Timer->CCMR2 &= ~TIM_CCMR2_OC3M;          // Effacer les bits du mode de comparaison
			Timer->CCMR2 |= (0x6 << 4);  // R�gler le mode PWM 1 (0x6)
			Timer->CCMR2 |= TIM_CCMR2_OC3PE;          // Activer le pr�chargement pour la comparaison
			Timer->CCER |= TIM_CCER_CC3E;             // Activer la capture/comparaison pour le canal 1 (activer le canal 1 )
		}
		if(Channel==4){
			Timer->CCMR2 &= ~TIM_CCMR2_OC4M;          // Effacer les bits du mode de comparaison
			Timer->CCMR2 |= (0x6 << 12);  // R�gler le mode PWM 1 (0x6)
			Timer->CCMR2 |= TIM_CCMR2_OC4PE;          // Activer le pr�chargement pour la comparaison
			Timer->CCER |= TIM_CCER_CC4E;             // Activer la capture/comparaison pour le canal 2 (activer le canal 2 )
		}
}


void MyTimer_SetDutyCycle( TIM_TypeDef * Timer , char Channel ,int dutycycle) {
	int pulse=dutycycle*(Timer->ARR+1)/100;
  if(Channel==1){
		Timer->CCR1=pulse;
	}
	if(Channel==2){
		Timer->CCR2=pulse;
	}
	if(Channel==3){
		Timer->CCR3=pulse;
	}
	if(Channel==4){
		Timer->CCR4=pulse;
	}

}

