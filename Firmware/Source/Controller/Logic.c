// Includes
#include "Board.h"
#include "Logic.h"
#include "ConvertUtils.h"
#include "DataTable.h"
#include "DiscreteOpAmp.h"
#include "LowLevel.h"

// Variables
float VoltageTarget, CurrentCutOff, RegulatorPcoef, RegulatorIcoef, RegulatorAlowedError;
float  Qi;
Int16U RegulatorPulseCounter = 0;
Int16U PulsePointsQuantity = 0;
volatile SubState LOGIC_SubState = SS_None;
volatile Int64U LOGIC_PowerOnCounter = 0;

void LOGIC_CacheVariables()
{
	CU_LoadConvertParams();

	VoltageTarget = (float)DataTable[REG_VOLTAGE_SETPOINT] / 10;
	CurrentCutOff = (float)((Int32U)((DataTable[REG_CURRENT_CUTOFF_H] << 16) | DataTable[REG_CURRENT_CUTOFF_L])) / 10;
	PulsePointsQuantity = DataTable[REG_PULSE_WIDTH] / TIMER6_uS;
	RegulatorPcoef = (float)DataTable[REG_REGULATOR_Kp] / 1000;
	RegulatorIcoef = (float)DataTable[REG_REGULATOR_Ki] / 1000;
}
//-----------------------------

void LOGIC_RegulatorCycle(float Voltage)
{
	float RegulatorError, Qp, RegulatorOut;

	if(LOGIC_SubState == SS_PulseStart || LOGIC_SubState == SS_Pulse)
	{
		RegulatorError = (RegulatorPulseCounter == 0) ? 0 : (VoltageTarget - Voltage);

		if(RegulatorError <= RegulatorAlowedError)
		{
			Qi += RegulatorError * RegulatorIcoef;
			LOGIC_SetSubState(SS_Pulse);
		}
		Qp = RegulatorError * RegulatorIcoef;
		RegulatorOut = VoltageTarget + Qp +Qi;

		DISOPAMP_SetVoltage(RegulatorOut);

		RegulatorPulseCounter++;

		if(RegulatorPulseCounter >= PulsePointsQuantity)
		{
			Qi = 0;
			RegulatorPulseCounter = 0;
			DISOPAMP_SetVoltage(0);
			LOGIC_SetSubState(SS_Pause);
		}
	}
}
//-----------------------------

void LOGIC_Process(float Voltage, float Current)
{
	switch(LOGIC_SubState)
	{
		case SS_Pulse:
			if(Current >= CurrentCutOff)
				LOGIC_SetSubState(SS_Interrupted);
			break;

		case SS_Pause:
			break;

		case SS_Interrupted:
			break;

		case SS_Finished:
			break;

		default:
			break;
	}
}
//-----------------------------

Int16U LOGIC_PowerMonitor()
{
	if(LOGIC_SubState == SS_PowerOn)
	{
		if(LOGIC_PowerOnCounter == 0)
			LOGIC_PowerOnCounter = CONTROL_TimeCounter + DataTable[REG_POWER_ON_TIMEOUT];
		else
		{
			if(!LL_ArePowerSuppliesReady())
			{
				if(CONTROL_TimeCounter >= LOGIC_PowerOnCounter)
					return DF_POWER_SUPPLY;
			}
			else
				LOGIC_SetSubState(SS_PowerOnReady);
		}
	}
	else
	{
		if(!LL_ArePowerSuppliesReady())
			return DF_POWER_SUPPLY;
	}

	return 0;
}
//-----------------------------

void LOGIC_SetSubState(SubState NewSubState)
{
	LOGIC_SubState = NewSubState;
}
//-----------------------------
