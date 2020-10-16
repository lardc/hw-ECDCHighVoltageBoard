#ifndef DISCRETEOPAMP_H_
#define DISCRETEOPAMP_H_

// Includes
#include "ZwBase.h"

// Variables
extern Int16U CurrentCutOffRange;

// Functions
void DISOPAMP_SetCurrentCutOff(float Current);
void DISOPAMP_SetVoltage(float Voltage);

#endif /* DISCRETEOPAMP_H_ */
