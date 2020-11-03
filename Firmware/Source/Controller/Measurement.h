#ifndef MEASUREMENT_H_
#define MEASUREMENT_H_

// Includes
#include "SysConfig.h"
#include "ZwBase.h"

typedef struct __MeasureSample
{
	float Current;
	float Voltage;
}MeasureSample;

// Definitions
#define PULSE_ARR_MAX_LENGTH			300				// Количество точек оцифровки

// Variables
extern Int16U MEASURE_ADC_VoltageRaw[ADC_DMA_BUFF_SIZE];
extern Int16U MEASURE_ADC_CurrentRaw[ADC_DMA_BUFF_SIZE];

// Functions
float MEASURE_SampleVoltage();
float MEASURE_SampleCurrent();
void MEASURE_SampleParams(volatile MeasureSample* Sample);
void MEASURE_DMABuffersClear();

#endif /* MEASUREMENT_H_ */
