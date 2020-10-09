#ifndef __LOWLEVEL_H
#define __LOWLEVEL_H

// Include
#include "Board.h"
#include "stdinc.h"

// Defines
#define DAC_CHANNEL_B		BIT15

// Functions
//
void LL_ToggleBoardLED();
void LL_SetStateExtPowerLed(bool State);
void LL_SetStateExtMsrLed(bool State);
void LL_SetStateLineSync1(bool State);
void LL_SetStateLineSync2(bool State);
bool LL_GetStateLineSync1();
bool LL_GetStateLineSync2();
bool LL_ArePowerSuppliesReady();
void LL_SetCurrentRage(uint16_t Range);
void LL_WriteDACx(uint16_t Data, void (*SetState_CS_SYNC)(bool State));
void LL_GroupStateCS_SYNC(bool State);
void LL_SetStateCS_SYNC1(bool State);
void LL_SetStateCS_SYNC2(bool State);
void LL_SetStateCS_SYNC3(bool State);
void LL_SetStateCS_SYNC4(bool State);
void LL_SetStateCS_SYNC5(bool State);
void LL_SetStateCS_SYNC6(bool State);
void LL_SetStateCS_SYNC7(bool State);
void LL_SetStateCS_SYNC8(bool State);

#endif //__LOWLEVEL_H
