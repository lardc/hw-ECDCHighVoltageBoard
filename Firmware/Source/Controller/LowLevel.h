#ifndef __LOWLEVEL_H
#define __LOWLEVEL_H

// Include
#include "stdinc.h"

// Functions
//
void LL_ToggleBoardLED();
void LL_SetStateExtPowerLed(bool State);
void LL_SetStateExtMsrLed(bool State);
void LL_SetStateInterruptLineSync1(bool State);
void LL_SetStateInterruptLineSync2(bool State);
bool LL_GetStateInterruptLineSync1();
bool LL_GetStateInterruptLineSync2();
bool LL_ArePowerSuppliesReady();
void LL_SetCurrentRage(uint16_t Range);
void LL_DiscreteOpAmpWriteDAC(uint16_t Data, GPIO_PortPinSetting CS_SYNC);

#endif //__LOWLEVEL_H
