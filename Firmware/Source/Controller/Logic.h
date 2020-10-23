#ifndef LOGIC_H_
#define LOGIC_H_

// Includes
#include "Measurement.h"

// Variables
extern float VoltageTarget;
extern float CurrentCutOff;

// Functions
bool LOGIC_RegulatorCycle(float Voltage, Int16U *Fault);
Int16U LOGIC_PowerMonitor();
void LOGIC_StopProcess();
void LOGIC_StartPrepare();
bool LOGIC_CheckExcessCurrentCutOff(float Current);
void LOGIC_LoggingProcess(volatile MeasureSample* Sample);
void LOGIC_SaveMeasuredData(volatile MeasureSample* Sample);

#endif /* LOGIC_H_ */
