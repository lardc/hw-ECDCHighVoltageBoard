// Includes
#include "Board.h"
#include "Logic.h"
#include "ConvertUtils.h"
#include "DataTable.h"
#include "DiscreteOpAmp.h"
#include "LowLevel.h"

// Definitions
#define CURRENT_RANGE0		0
#define CURRENT_RANGE1		1
#define CURRENT_RANGE2		2
#define CURRENT_RANGE3		3

// Variables
float VoltageTarget, VoltageSetpoint, CurrentCutOff, RegulatorPcoef, RegulatorIcoef, RegulatorAlowedError, dV;
float  Qi;
Int16U RegulatorPulseCounter = 0;
Int16U PulsePointsQuantity = 0;
volatile SubState LOGIC_SubState = SS_None;
volatile Int64U LOGIC_PowerOnCounter = 0;
volatile Int64U LOGIC_BetweenPulsesDelay = 0;
volatile Int64U LOGIC_TestTime = 0;

// Functions prototypes
void LOGIC_ChangeVoltageAmplitude();
void LOGIC_LoggingProcess(MeasureSample* Sample);
void LOGIC_SaveMeasuredData(MeasureSample* Sample);
void LOGIC_SetCurrentCutOff(float Current);
void LOGIC_CacheVariables();

// Functions
//
void LOGIC_StartPrepare()
{
	LOGIC_CacheVariables();
	CU_LoadConvertParams();
	LOGIC_SetCurrentCutOff(CurrentCutOff);
}
//-----------------------------

void LOGIC_CacheVariables()
{
	VoltageSetpoint = (float)DataTable[REG_VOLTAGE_SETPOINT] / 10;
	CurrentCutOff = (float)((Int32U)((DataTable[REG_CURRENT_CUTOFF_H] << 16) | DataTable[REG_CURRENT_CUTOFF_L])) / 10;
	PulsePointsQuantity = DataTable[REG_PULSE_WIDTH] / TIMER6_uS;
	RegulatorPcoef = (float)DataTable[REG_REGULATOR_Kp] / 1000;
	RegulatorIcoef = (float)DataTable[REG_REGULATOR_Ki] / 1000;
	dV = (float)DataTable[REG_VOLATGE_RATE] / 10 * (DataTable[REG_BETWEEN_PULSES_DELAY] + (float)DataTable[REG_PULSE_WIDTH] / 1000);
	RegulatorAlowedError = (float)DataTable[REG_REGULATOR_ALOWED_ERR] / 1000;
}
//-----------------------------

Int16U LOGIC_RegulatorCycle(float Voltage)
{
	float RegulatorError, Qp, RegulatorOut, ErrorX;

	RegulatorError = (RegulatorPulseCounter == 0) ? 0 : (VoltageTarget - Voltage);
	ErrorX = RegulatorError / VoltageSetpoint;

	if(ErrorX <= RegulatorAlowedError)
	{
		Qi += RegulatorError * RegulatorIcoef;
		LOGIC_SetSubState(SS_Pulse);
	}
	else
	{
		if(!DataTable[REG_MUTE_FOLLOWING_ERR])
		{
			LOGIC_StopProcess();
			return DF_FOLOWING_ERROR;
		}
	}

	Qp = RegulatorError * RegulatorPcoef;
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

	return DF_NONE;
}
//-----------------------------

bool LOGIC_Process(MeasureSample* Sample, Int16U* Fault)
{
	LOGIC_LoggingProcess(Sample);

	switch(LOGIC_SubState)
	{
		case SS_PulseStart:
		case SS_Pulse:
			if(Sample->Current >= CurrentCutOff)
			{
				DataTable[REG_WARNING] = WARNING_CURRENT_CUTOFF;
				LOGIC_SetSubState(SS_Finished);
			}
			else
			{
				*Fault = LOGIC_RegulatorCycle(Sample->Voltage);

				if(*Fault != DF_NONE)
					LOGIC_SetSubState(SS_Finished);
			}
			break;

		case SS_Pause:
			LOGIC_ChangeVoltageAmplitude(Sample->Voltage);
			break;

		case SS_Finished:
			LOGIC_SaveMeasuredData(Sample);
			LOGIC_StopProcess();
			return true;
			break;

		default:
			break;
	}

	return false;
}
//-----------------------------

void LOGIC_SaveMeasuredData(MeasureSample* Sample)
{
	Int32U Current;

	DataTable[REG_RESULT_VOLTAGE] = (Int16U)(Sample->Voltage * 10);
	Current = (Int16U)(Sample->Current * 10);
	DataTable[REG_RESULT_CURRENT_H] = (Int16U)(Current >> 16);
	DataTable[REG_RESULT_CURRENT_L] = (Int16U)Current;
}
//-----------------------------

void LOGIC_LoggingProcess(MeasureSample* Sample)
{
	static Int16U ScopeLogStep = 0, LocalCounter = 0;

	// —брос локального счЄтчика в начале логгировани€
	if (CONTROL_Values_Counter == 0)
		LocalCounter = 0;

	if (ScopeLogStep++ >= DataTable[REG_SCOPE_STEP])
	{
		ScopeLogStep = 0;

		CONTROL_ValuesVoltage[LocalCounter] = (Int16U)Sample->Voltage;

		switch(DISOPAMP_GetCurrentRange())
		{
			case CURRENT_RANGE0:
			case CURRENT_RANGE1:
				CONTROL_ValuesCurrent[LocalCounter] = (Int16U)(Sample->Current * 10);
				break;

			case CURRENT_RANGE2:
			case CURRENT_RANGE3:
				CONTROL_ValuesCurrent[LocalCounter] = (Int16U)(Sample->Current);
				break;
		}

		++LocalCounter;
	}

	// ”словие обновлени€ глобального счЄтчика данных
	if (CONTROL_Values_Counter < VALUES_x_SIZE)
		CONTROL_Values_Counter = LocalCounter;

	// —брос локального счЄтчика
	if (LocalCounter >= VALUES_x_SIZE)
		LocalCounter = 0;
}
//-----------------------------

void LOGIC_StopProcess()
{
	Qi = 0;
	RegulatorPulseCounter = 0;
	VoltageTarget = 0;
	LOGIC_TestTime = 0;
	DISOPAMP_SetVoltage(0);
	TIM_Stop(TIM6);

	LOGIC_SetSubState(SS_None);
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

	return DF_NONE;
}
//-----------------------------

void LOGIC_ChangeVoltageAmplitude()
{
	if(!LOGIC_BetweenPulsesDelay)
		LOGIC_BetweenPulsesDelay = CONTROL_TimeCounter + DataTable[REG_BETWEEN_PULSES_DELAY];

	if(CONTROL_TimeCounter >= LOGIC_BetweenPulsesDelay)
	{
		LOGIC_BetweenPulsesDelay = 0;

		if((VoltageTarget + dV) <= VoltageSetpoint)
		{
			VoltageTarget += dV;
			LOGIC_SetSubState(SS_PulseStart);
		}
		else
		{
			if(!LOGIC_TestTime)
			{
				VoltageTarget = VoltageSetpoint;
				LOGIC_TestTime = CONTROL_TimeCounter + DataTable[REG_TEST_TIME];

				LOGIC_SetSubState(SS_PulseStart);
			}

			if(CONTROL_TimeCounter >= LOGIC_TestTime)
				LOGIC_SetSubState(SS_Finished);
			else
				LOGIC_SetSubState(SS_PulseStart);
		}
	}
}
//-----------------------------

void LOGIC_SetCurrentCutOff(float Current)
{
	DISOPAMP_SetCurrentCutOff(Current);
}
//-----------------------------

void LOGIC_SetSubState(SubState NewSubState)
{
	LOGIC_SubState = NewSubState;
}
//-----------------------------
