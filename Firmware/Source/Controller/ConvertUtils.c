// Includes
//
#include "ConvertUtils.h"
#include "Global.h"
#include "LowLevel.h"
#include "DataTable.h"

// Definitions
#define DAC_MAX_VAL		0x0FFF

// Structs
typedef struct __DisOpAmpConvertParams
{
	float P2;
	float P1;
	Int16S P0;
	Int16U K;
	Int16S B;
}DisOpAmpConvertParams;

typedef struct __MeasurementConvertParams
{
	float P2;
	float P1;
	Int16S P0;
	Int16U K;
	Int16S B;
}MeasurementConvertParams;

// Variables
DisOpAmpConvertParams DisOpAmpVParams[DISOPAMP_TOTAL_CELL];
DisOpAmpConvertParams DisOpAmpIParams[DISOPAMP_CURRENT_RANGE_NUM];
MeasurementConvertParams MeasureVParams;
MeasurementConvertParams MeasureIParams[DISOPAMP_CURRENT_RANGE_NUM];

// Functions prototypes
Int16U CU_XtoDAC(float Value, DisOpAmpConvertParams Coefficients);
float CU_ADCtoX(Int16U Data, MeasurementConvertParams Coefficients);


// Functions
//
Int16U CU_XtoDAC(float Value, DisOpAmpConvertParams Coefficients)
{
	float Temp;

	Temp = Value * Value * Coefficients.P2 + Value * Coefficients.P1 + Coefficients.P0;
	Temp = (Temp + Coefficients.B) * Coefficients.K;

	if(Temp < 0)
		Temp = 0;

	return (Int16U)Temp;
}
//-----------------------------

Int16U CU_VtoDAC(float Voltage, Int16U CellNumber)
{
	Int16U Temp;

	Temp = CU_XtoDAC(Voltage, DisOpAmpVParams[CellNumber]);

	if (Temp > DAC_MAX_VAL)
		return DAC_MAX_VAL;
	else
		return Temp;
}
//-----------------------------

Int16U CU_ItoDAC(float Current, Int16U CurrentRange)
{
	Int16U Temp;

	Temp = CU_XtoDAC(Current, DisOpAmpIParams[CurrentRange]);

	if (Temp > DAC_MAX_VAL)
		return DAC_MAX_VAL;
	else
		return Temp;
}
//-----------------------------

float CU_ADCtoX(Int16U Data, MeasurementConvertParams Coefficients)
{
	float Temp;

	Temp = Data * Coefficients.K + Coefficients.B;
	Temp = Temp * Temp * Coefficients.P2 + Temp * Coefficients.P1 + Coefficients.P0;

	return Temp;
}
//-----------------------------

float CU_ADCtoI(Int16U Data, Int16U CurrentRange)
{
	return CU_ADCtoX(Data, MeasureIParams[CurrentRange]);
}
//-----------------------------

float CU_ADCtoV(Int16U Data)
{
	return CU_ADCtoX(Data, MeasureVParams);
}
//-----------------------------

void CU_LoadConvertParams()
{
	// Параметры преобразования напряжения
	DisOpAmpVParams[DISOPAMP_POSITION_CELL0].P2 = (float)(Int16S)DataTable[REG_DAC_V_CELL0_P2] / 1e6;
	DisOpAmpVParams[DISOPAMP_POSITION_CELL0].P1 = (float)DataTable[REG_DAC_V_CELL0_P1] / 1000;
	DisOpAmpVParams[DISOPAMP_POSITION_CELL0].P0 = (Int16S)DataTable[REG_DAC_V_CELL0_P0];
	DisOpAmpVParams[DISOPAMP_POSITION_CELL0].K = DataTable[REG_DAC_V_CELL0_K];
	DisOpAmpVParams[DISOPAMP_POSITION_CELL0].B = (Int16S)DataTable[REG_DAC_V_CELL0_B];

	MeasureVParams.P2 = (float)(Int16S)DataTable[REG_ADC_VOLTAGE_P2] / 1e6;
	MeasureVParams.P1 = (float)DataTable[REG_ADC_VOLTAGE_P1] / 1000;
	MeasureVParams.P0 = (Int16S)DataTable[REG_ADC_VOLTAGE_P0];
	MeasureVParams.K = DataTable[REG_ADC_VOLTAGE_K];
	MeasureVParams.B = (Int16S)DataTable[REG_ADC_VOLTAGE_B];

	for(int i = DISOPAMP_POSITION_CELL1; i < DISOPAMP_TOTAL_CELL; i++)
	{
		DisOpAmpVParams[i].P2 = 0;
		DisOpAmpVParams[i].P1 = 1;
		DisOpAmpVParams[i].P0 = 0;
		DisOpAmpVParams[i].K = DataTable[REG_DAC_V_CELL1_K + i - 1];
		DisOpAmpVParams[i].B = 0;
	}

	// Параметры преобразования тока
	for(int i = 0; i < DISOPAMP_CURRENT_RANGE_NUM; i++)
	{
		DisOpAmpIParams[i].P2 = (float)(Int16S)DataTable[REG_DAC_I_RANGE0_P2 + i * 5] / 1e6;
		DisOpAmpIParams[i].P1 = (float)DataTable[REG_DAC_I_RANGE0_P1 + i * 5] / 1000;
		DisOpAmpIParams[i].P0 = (Int16S)DataTable[REG_DAC_I_RANGE0_P0 + i * 5];
		DisOpAmpIParams[i].K = DataTable[REG_DAC_I_RANGE0_K + i * 5];
		DisOpAmpIParams[i].B = (Int16S)DataTable[REG_DAC_I_RANGE0_B + i * 5];

		MeasureIParams[i].P2 = (float)(Int16S)DataTable[REG_ADC_I_RANGE0_P2 + i * 5] / 1e6;
		MeasureIParams[i].P1 = (float)DataTable[REG_ADC_I_RANGE0_P1 + i * 5] / 1000;
		MeasureIParams[i].P0 = (Int16S)DataTable[REG_ADC_I_RANGE0_P0 + i * 5];
		MeasureIParams[i].K = DataTable[REG_ADC_I_RANGE0_K + i * 5];
		MeasureIParams[i].B = (Int16S)DataTable[REG_ADC_I_RANGE0_B + i * 5];
	}
}
//-----------------------------

