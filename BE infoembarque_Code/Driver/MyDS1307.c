#include "DS1307.h"
static void (*func_Callback)(void) = 0;

void DS1307_Init(I2C_TypeDef *I2Cx) {
    // Initialise l'I2C avec une priorité d'interruption faible (ex. : 2)
    MyI2C_Init(I2Cx, 2, func_Callback);

    // Configure le registre de contrôle pour activer l'horloge
    char control = 0x13; // signal carré, horloge activée
    MyI2C_RecSendData_Typedef controlData = {DS1307_ADDRESS, &control, 1};
    MyI2C_PutString(I2Cx, DS1307_REG_CONTROL, &controlData);
}

static uint8_t BCD_to_Decimal(uint8_t bcd) { //conversion BCD vers décimal pour récupérer les données du RTC et les afficher par la suite(get time)
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}
static uint8_t Decimal_to_BCD(uint8_t decimal) { //conversion décimal vers BCD  pour envoyer des données vers le RTC (set time)
    return ((decimal / 10) << 4) | (decimal % 10);
}

void DS1307_SetTime(I2C_TypeDef *I2Cx, DS1307_TimeDate *timeDate) { // régler le temps perçu par le RTC
    uint8_t data[7];

    // Convertit les valeurs décimales en BCD
    data[0] = Decimal_to_BCD(timeDate->seconds);
    data[1] = Decimal_to_BCD(timeDate->minutes);
    data[2] = Decimal_to_BCD(timeDate->hours);
    data[3] = Decimal_to_BCD(timeDate->day_of_week);
    data[4] = Decimal_to_BCD(timeDate->date);
    data[5] = Decimal_to_BCD(timeDate->month);
    data[6] = Decimal_to_BCD(timeDate->year);

    // Écrit les données dans les registres correspondants du DS1307
    MyI2C_RecSendData_Typedef timeData = {DS1307_ADDRESS, (char *)data, 7};
    MyI2C_PutString(I2Cx, DS1307_REG_SECONDS, &timeData);  // Commence l'écriture à partir de DS1307_REG_SECONDS (0x00)
}

void DS1307_GetTime(I2C_TypeDef *I2Cx, DS1307_TimeDate *timeDate) { //récupérer le temps vu par le RTC
    uint8_t data[7];

    // Lit les 7 registres du DS1307 (de DS1307_REG_SECONDS à DS1307_REG_YEAR)
    MyI2C_RecSendData_Typedef timeData = {DS1307_ADDRESS, (char *)data, 7};
    MyI2C_GetString(I2Cx, DS1307_REG_SECONDS, &timeData);  // Commence la lecture à partir de DS1307_REG_SECONDS (0x00)

    // Convertit les valeurs BCD en décimal
    timeDate->seconds = BCD_to_Decimal(data[0]);
    timeDate->minutes = BCD_to_Decimal(data[1]);
    timeDate->hours = BCD_to_Decimal(data[2]);
    timeDate->day_of_week = BCD_to_Decimal(data[3]);
    timeDate->date = BCD_to_Decimal(data[4]);
    timeDate->month = BCD_to_Decimal(data[5]);
    timeDate->year = BCD_to_Decimal(data[6]);
}




