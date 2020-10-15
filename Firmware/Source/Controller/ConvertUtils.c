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

// Variables
DisOpAmpConvertParams DisOpAmpVParams[DISOPAMP_TOTAL_CELL];
DisOpAmpConvertParams DisOpAmpIParams[DISOPAMP_CURRENT_RANGE_NUM];

// Functions prototypes
Int16U CU_XtoDAC(float Value, DisOpAmpConvertParams Coefficients);


// Functions
//
Int16U CU_XtoDAC(float Value, DisOpAmpConvertParams Coefficients)
{
	float Temp;

	Temp = Value * Value * Coefficients.P2 + Value * Coefficients.P1 + Coefficients.P0;
	Temp = (Temp + Coefficients.B) * Coefficients.K;

	return (Int16U)Temp;
}
//-----------------------------

Int16U CU_VtoDAC(float Voltage, Int16U CellNumber)
{
	Int16U Temp;

	Temp = CU_XtoDAC(Voltage, DisOpAmpVParams[CellNumber]);

	if (Temp > DAC_MAX_VAL)
		return (DAC_MAX_VAL  | DAC_CHANNEL_B);
	else
		return (Temp | DAC_CHANNEL_B);
}
//-----------------------------

Int16U CU_ItoDAC(float Current, Int16U CurrentRange)
{
	Int16U Temp;

	Temp = CU_XtoDAC(Current, DisOpAmpIParams[CurrentRange]) & ~DAC_CHANNEL_B;

	if (Temp > DAC_MAX_VAL)
		return DAC_MAX_VAL;
	else
		return Temp;
}
//-----------------------------

void CU_LoadConvertParams()
{
	// Параметры преобразования напряжения
	DisOpAmpVParams[DISOPAMP_POSITION_CELL0].P2 = (float)(Int16S)DataTable[REG_DAC_V_CELL0_P2] / 1e6;
	DisOpAmpVParams[DISOPAMP_POSITION_CELL0].P1 = (float)(Int16S)DataTable[REG_DAC_V_CELL0_P1] / 1000;
	DisOpAmpVParams[DISOPAMP_POSITION_CELL0].P0 = (float)(Int16S)DataTable[REG_DAC_V_CELL0_P0];
	DisOpAmpVParams[DISOPAMP_POSITION_CELL0].K = DataTable[REG_DAC_V_CELL0_K];
	DisOpAmpVParams[DISOPAMP_POSITION_CELL0].B = DataTable[REG_DAC_V_CELL0_B];

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
		DisOpAmpIParams[i].P1 = (float)(Int16S)DataTable[REG_DAC_I_RANGE0_P1 + i * 5] / 1000;
		DisOpAmpIParams[i].P0 = (float)(Int16S)DataTable[REG_DAC_I_RANGE0_P0 + i * 5];
		DisOpAmpIParams[i].K = DataTable[REG_DAC_I_RANGE0_K + i * 5];
		DisOpAmpIParams[i].B = DataTable[REG_DAC_I_RANGE0_B + i * 5];
	}
}
//-----------------------------

