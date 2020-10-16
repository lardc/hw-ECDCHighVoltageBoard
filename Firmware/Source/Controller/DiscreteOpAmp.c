// Includes
#include "DiscreteOpAmp.h"
#include "LowLevel.h"
#include "ConvertUtils.h"
#include "Global.h"

// Variables
Int16U CurrentCutOffRange = 0;

// Functions prototypes
void DISOPAMP_SetCurrentRange(float Current);


// Functions
//
void DISOPAMP_SetCurrentCutOff(float Current)
{
	DISOPAMP_SetCurrentRange(Current);
	LL_WriteDACx(CU_ItoDAC(Current, CurrentCutOffRange) & ~DAC_CHANNEL_B, DISOPAMP_POSITION_CELL0, DISOPAMP_TOTAL_CELL, true);
}
//-----------------------------

void DISOPAMP_SetCurrentRange(float Current)
{
	if(Current >= DISOPAMP_CURRENT_THRESHOLD_RANGE_3)
	{
		LL_SetCurrentRange3();
		CurrentCutOffRange = 3;
	}
	else if(Current >= DISOPAMP_CURRENT_THRESHOLD_RANGE_2)
	{
		LL_SetCurrentRange2();
		CurrentCutOffRange = 2;
	}
	else if(Current >= DISOPAMP_CURRENT_THRESHOLD_RANGE_1)
	{
			LL_SetCurrentRange1();
			CurrentCutOffRange = 1;
	}
	else
	{
		LL_SetCurrentRange0();
		CurrentCutOffRange = 0;
	}
}
//-----------------------------

void DISOPAMP_SetVoltage(float Voltage)
{
	Int16U CellCounter = 0;

	while(Voltage >= DISOPAMP_CELL_VOLATGE_MAX)
	{
		Voltage -= DISOPAMP_CELL_VOLATGE_MAX;
		CellCounter++;
	}

	LL_WriteDACx(CU_VtoDAC(Voltage, DISOPAMP_POSITION_CELL0) | DAC_CHANNEL_B, DISOPAMP_POSITION_CELL0, 1, false);

	if(CellCounter)
	{
		for(int i = DISOPAMP_POSITION_CELL1; i <= CellCounter; i++)
			LL_WriteDACx(CU_VtoDAC(DISOPAMP_CELL_VOLATGE_MAX, i) | DAC_CHANNEL_B, DISOPAMP_POSITION_CELL1, 1, false);
	}

	LL_WriteDACx(DAC_CHANNEL_B, DISOPAMP_POSITION_CELL1 + CellCounter, DISOPAMP_TOTAL_CELL - CellCounter - 1, false);

	LL_ToggleLDAC();
}
//-----------------------------




