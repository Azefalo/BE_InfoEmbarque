
#include <stdint.h>  // Pour uint8_t, int8_t
#include "stm32f10x.h"
#include "MyUSART.h"
#include "MyTimer.h"
#include "MyGPIO.h"

void initPlateau(void);
int8_t mapToDirection(uint8_t receivedData);
void updateBoatDirectionAndSpeed(uint8_t receivedData);

