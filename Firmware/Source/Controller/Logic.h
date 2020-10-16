#ifndef LOGIC_H_
#define LOGIC_H_

// Includes
#include "Measurement.h"

// Types
//
typedef enum __DeviceState
{
	DS_None = 0,
	DS_Fault = 1,
	DS_Disabled = 2,
	DS_Ready = 3,
	DS_InProcess = 4
} DeviceState;

typedef enum __SubState
{
	SS_None = 0,
	SS_PowerOn = 1,
	SS_PowerOnReady = 2,
	SS_PulseStart = 3,
	SS_Pulse = 4,
	SS_Pause = 5,
	SS_Interrupted = 6,
	SS_Finished = 7
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
Int16U LOGIC_PowerMonitor();

#endif /* LOGIC_H_ */
