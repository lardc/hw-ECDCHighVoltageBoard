#ifndef __CONTROLLER_H
#define __CONTROLLER_H

// Include
//
#include "stdinc.h"
#include "Global.h"

// Types
//
typedef enum __DeviceState
{
	DS_None = 0,
	DS_Fault = 1,
	DS_Disabled = 2,
	DS_Enabled = 3,
	DS_InProcess = 4
} DeviceState;

// Variables
//
extern volatile Int64U CONTROL_TimeCounter;
extern Int64U CONTROL_LEDTimeout;
extern volatile Int16U CONTROL_ValuesVoltageCounter;
extern volatile Int16U CONTROL_ValuesCurrentCounter;
extern volatile Int16U CONTROL_ValuesVoltage[VALUES_x_SIZE];
extern volatile Int16U CONTROL_ValuesCurrent[VALUES_x_SIZE];

// Functions
//
void CONTROL_Init();
void CONTROL_Idle();
void CONTROL_DelayMs(uint32_t Delay);

#endif // __CONTROLLER_H
