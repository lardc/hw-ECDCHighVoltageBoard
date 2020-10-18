// Includes
#include "Measurement.h"
#include "ConvertUtils.h"
#include "Board.h"
#include "DiscreteOpAmp.h"

// Variables
Int16U MEASURE_ADC_VoltageRaw[ADC_DMA_BUFF_SIZE];
Int16U MEASURE_ADC_CurrentRaw[ADC_DMA_BUFF_SIZE];

// Functions prototypes
Int16U MEASURE_DMAExtractX(Int16U* InputArray, Int16U ArraySize);
Int16U MEASURE_DMAExtractVoltage();
Int16U MEASURE_DMAExtractCurrent();
void MEASURE_StartSamplingVoltage();
void MEASURE_StartSamplingCurrent();

// Functions
//
void MEASURE_SampleParams(MeasureSample* Sample)
{
	Sample->Voltage = MEASURE_SampleVoltage();
	Sample->Current = MEASURE_SampleCurrent();
}
//-----------------------------------------------

float MEASURE_SampleVoltage()
{
	float SampleVoltage;

	SampleVoltage = CU_ADCtoV(MEASURE_DMAExtractVoltage());
	MEASURE_StartSamplingVoltage();

	return SampleVoltage;
}
//-----------------------------------------------

float MEASURE_SampleCurrent()
{
	float SampleCurrent;

	SampleCurrent = CU_ADCtoI(MEASURE_DMAExtractCurrent(), DISOPAMP_GetCurrentRange());
	MEASURE_StartSamplingCurrent();

	return SampleCurrent;
}
//-----------------------------------------------

Int16U MEASURE_DMAExtractX(Int16U* InputArray, Int16U ArraySize)
{
	Int32U AverageData = 0;

	for(int i = 0; i < ArraySize; i++)
		AverageData += *(InputArray + i);

	return (Int16U)((float)AverageData / ArraySize);
}
//-----------------------------------------------

Int16U MEASURE_DMAExtractVoltage()
{
	return MEASURE_DMAExtractX(&MEASURE_ADC_VoltageRaw[0], ADC_DMA_BUFF_SIZE);
}
//-----------------------------------------------

Int16U MEASURE_DMAExtractCurrent()
{
	return MEASURE_DMAExtractX(&MEASURE_ADC_CurrentRaw[0], ADC_DMA_BUFF_SIZE);
}
//-----------------------------------------------

void MEASURE_StartSamplingVoltage()
{
	DMA_TransferCompleteReset(DMA1, DMA_TRANSFER_COMPLETE);
	ADC_SamplingStart(ADC1);
}
//-----------------------------------------------

void MEASURE_StartSamplingCurrent()
{
	DMA_TransferCompleteReset(DMA2, DMA_TRANSFER_COMPLETE);
	ADC_SamplingStart(ADC2);
}
//-----------------------------------------------


