#include "stm32f10x.h"
#include "MyI2C.h"

// Callback en cas d'erreur I2C
void MyI2C_ErrorCallback(void)
{
    MyI2C_Err_Enum error = MyI2C_Get_Error(I2C1);
    // Gérer les erreurs ici (vous pouvez ajouter des logs ou des signaux)
    while (1)
    {
        // Boucle infinie pour signaler une erreur
    }
}

int main(void)
{
    // Initialisation de l'horloge du système (RCC) et des GPIO nécessaires
    SystemInit();

    // Initialisation de l'I2C1 avec une priorité d'interruption de 2 et la fonction de callback en cas d'erreur
    MyI2C_Init(I2C1, 2, MyI2C_ErrorCallback);

    // Définition des données à envoyer
    char dataToSend[] = {0x10, 0x20, 0x30}; // Exemple de données
    MyI2C_RecSendData_Typedef sendData;
    sendData.SlaveAdress7bits = 0x3C; // Adresse du slave en 7 bits
    sendData.Ptr_Data = dataToSend;
    sendData.Nb_Data = sizeof(dataToSend);

    // Écriture des données au slave à l'adresse interne 0x00
    MyI2C_PutString(I2C1, 0x00, &sendData);

    // Définition du tableau pour recevoir les données
    char dataReceived[5]; // Exemple : lecture de 5 octets
    MyI2C_RecSendData_Typedef receiveData;
    receiveData.SlaveAdress7bits = 0x3C; // Adresse du slave en 7 bits
    receiveData.Ptr_Data = dataReceived;
    receiveData.Nb_Data = sizeof(dataReceived);

    // Lecture des données depuis le slave à l'adresse interne 0x00
    MyI2C_GetString(I2C1, 0x00, &receiveData);

    // Boucle principale
    while (1)
    {
        // Vous pouvez ajouter du code pour traiter les données reçues
    }
}
