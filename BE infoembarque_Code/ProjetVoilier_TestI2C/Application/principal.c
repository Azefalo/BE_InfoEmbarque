#include "stm32f10x.h"
#include "MyI2C.h"
#include "DS1307.h"
#include "MyUSART.h"
//// Callback en cas d'erreur I2C
//void MyI2C_ErrorCallback(void)
//{
//    MyI2C_Err_Enum error = MyI2C_Get_Error(I2C1);
//    // Gérer les erreurs ici (vous pouvez ajouter des logs ou des signaux)
//    while (1)
//    {
//        // Boucle infinie pour signaler une erreur
//    }
//}

int main(void)
{   // Initialisation de l'horloge du système (RCC) et des GPIO nécessaires
    SystemInit();
	  UART1_Init();
	  DS1307_TimeDate MARC;

    DS1307_Init(I2C2);


    // Boucle principale
    while (1)
    {
        DS1307_GetTime(I2C2, &MARC);
			  
    }
}
