#ifndef MYTIMER_H
#define MYTIMER_H

#include "stm32f10x.h"  // Remplacer par l'inclusion correcte

typedef struct
{
    TIM_TypeDef *Timer;  // Pointeur vers TIM1 à TIM4
    unsigned short ARR;
    unsigned short PSC;
} MyTimer_Struct_TypeDef;

/*
*****************************************************************************************
* @brief  Initialisation de la base du timer
* @param  Timer -> Pointeur vers une structure contenant les informations de base
* @note   Fonction à appeler systématiquement avant d'aller dans des configurations plus 
*         fines (PWM, codeur, etc.)
*************************************************************************************************
*/
void MyTimer_Base_Init(MyTimer_Struct_TypeDef *Timer);
void MyTimer_ActivateIT(TIM_TypeDef *Timer, char Prio);
void MyTimer_ActivateIT1(TIM_TypeDef *Timer, char Prio, void (*IT_function)(void)); //fonction d'appel à l'interruption direct sur le programme principal 
void MyTimer_PWM( TIM_TypeDef * Timer , char Channel ) ;
void MyTimer_SetDutyCycle( TIM_TypeDef * Timer , char Channel ,int dutycycle);
#define MyTimer_Base_Start(Timer) (Timer->CR1 |= TIM_CR1_CEN)
#define MyTimer_Base_Stop(Timer)  (Timer->CR1 &=~TIM_CR1_CEN)

#endif
