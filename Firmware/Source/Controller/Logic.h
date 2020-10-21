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
	SS_PulsePrepare = 3,
	SS_Pulse = 4,
	SS_Finished = 5
}SubState;

// Variables
extern float VoltageTarget;
extern float CurrentCutOff;
extern volatile SubState LOGIC_SubState;

// Functions
Int16U LOGIC_RegulatorCycle(float Voltage);
bool LOGIC_Process(volatile MeasureSample* Sample);
void LOGIC_SetSubState(SubState NewSubState);
Int16U LOGIC_PowerMonitor();
void LOGIC_StopProcess();
void LOGIC_StartPrepare();
bool LOGIC_CheckExcessCurrentCutOff(float Current);
void LOGIC_LoggingProcess(volatile MeasureSample* Sample);

#endif /* LOGIC_H_ */
