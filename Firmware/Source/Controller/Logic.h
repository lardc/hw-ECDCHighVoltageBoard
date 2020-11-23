#ifndef LOGIC_H_
#define LOGIC_H_

// Includes
#include "Measurement.h"

// Variables
extern float VoltageTarget;
extern float CurrentCutOff;

// Functions
bool LOGIC_RegulatorCycle(float Voltage, Int16U *Problem);
void LOGIC_StopProcess();
void LOGIC_StartPrepare();
bool LOGIC_CheckExcessCurrentCutOff(float Current);
void LOGIC_LoggingProcess(volatile MeasureSample* Sample);
Int16U LOGIC_GetVoltageTestResult();
Int32U LOGIC_GetCurrentTestResult();

#endif /* LOGIC_H_ */
