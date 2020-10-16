#ifndef LOGIC_H_
#define LOGIC_H_

// Includes
#include "Measurement.h"

// Types
typedef enum __SubState
{
	SS_None = 0,
	SS_PowerOn = 1,
	SS_Pulse = 2,
	SS_Pause
}SubState;

// Variables
extern float VoltageTarget;
extern float CurrentCutOff;
extern volatile SubState LOGIC_SubState;

// Functions
void LOGIC_CacheVariables();
void LOGIC_RegulatorCycle(float Voltage);
void LOGIC_Process(float Voltage, float Current);
void LOGIC_SetSubState(SubState NewSubState);

#endif /* LOGIC_H_ */
