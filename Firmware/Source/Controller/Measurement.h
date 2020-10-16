#ifndef MEASUREMENT_H_
#define MEASUREMENT_H_

// Includes
#include "SysConfig.h"
#include "ZwBase.h"

// Definitions
#define PULSE_ARR_MAX_LENGTH			300				// ���������� ����� ���������

// Variables
extern Int16U MEASURE_ADC_VoltageRaw[ADC_DMA_BUFF_SIZE];
extern Int16U MEASURE_ADC_CurrentRaw[ADC_DMA_BUFF_SIZE];

// Functions
float MEASURE_SampleVoltage();
float MEASURE_SampleCurrent();
#endif /* MEASUREMENT_H_ */
