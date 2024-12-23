#ifndef _DS1307_H_
#define _DS1307_H_
#include "MyI2C.h"
#include "stm32f10x.h"
// Adresse I2C du DS1307 (7 bits)
#define DS1307_ADDRESS 0x68  // Adresse en 7 bits

// Définition des registres du DS1307
#define DS1307_REG_SECONDS    0x00
#define DS1307_REG_MINUTES    0x01
#define DS1307_REG_HOURS      0x02
#define DS1307_REG_DAY        0x03
#define DS1307_REG_DATE       0x04
#define DS1307_REG_MONTH      0x05
#define DS1307_REG_YEAR       0x06
#define DS1307_REG_CONTROL    0x07

// Structure pour l'heure et la date
typedef struct {
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day_of_week;
    uint8_t date;
    uint8_t month;
    uint8_t year;
} DS1307_TimeDate;

static uint8_t BCD_to_Decimal(uint8_t bcd);
void DS1307_Init(I2C_TypeDef *I2Cx);
void DS1307_SetTime(I2C_TypeDef *I2Cx, DS1307_TimeDate *timeDate);
void DS1307_GetTime(I2C_TypeDef *I2Cx, DS1307_TimeDate *timeDate);


#endif // _DS1307_H_


