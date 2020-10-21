// Includes
#include "Board.h"
#include "Logic.h"
#include "ConvertUtils.h"
#include "DataTable.h"
#include "DiscreteOpAmp.h"
#include "LowLevel.h"

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
void LOGIC_SaveMeasuredData(volatile MeasureSample* Sample);
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
	static Int16U FollowingErrorCounter = 0;

	float RegulatorError, Qp, RegulatorOut, ErrorX;

	RegulatorError = (RegulatorPulseCounter == 0) ? 0 : (VoltageTarget - Voltage);
	ErrorX = RegulatorError / VoltageSetpoint;

	if(ErrorX <= RegulatorAlowedError)
	{
		FollowingErrorCounter = 0;
		Qi += RegulatorError * RegulatorIcoef;
	}
	else
	{
		if(!DataTable[REG_MUTE_FOLLOWING_ERR])
		{
			FollowingErrorCounter++;

			if(FollowingErrorCounter >= DataTable[REG_FOLLOWING_ERR_CNT_NUM])
			{
				FollowingErrorCounter = 0;
				return DF_FOLOWING_ERROR;
			}
		}
	}

	Qp = RegulatorError * RegulatorPcoef;
	RegulatorOut = VoltageTarget + Qp +Qi;

	if(RegulatorOut > DSIOPAMP_STACK_VOLTAGE_MAX)
		RegulatorOut = DSIOPAMP_STACK_VOLTAGE_MAX;

	DISOPAMP_SetVoltage(RegulatorOut);

	RegulatorPulseCounter++;

	if(RegulatorPulseCounter >= PulsePointsQuantity)
	{
		Qi = 0;
		RegulatorPulseCounter = 0;
		DISOPAMP_SetVoltage(0);
		TIM_Stop(TIM6);
		LOGIC_SetSubState(SS_PulsePrepare);
	}

	return DF_NONE;
}
//-----------------------------

bool LOGIC_Process(volatile MeasureSample* Sample)
{
	switch(LOGIC_SubState)
	{
		case SS_PulsePrepare:
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

void LOGIC_SaveMeasuredData(volatile MeasureSample* Sample)
{
	Int32U Current;

	DataTable[REG_RESULT_VOLTAGE] = (Int16U)(Sample->Voltage * 10);
	Current = (Int16U)(Sample->Current * 10);
	DataTable[REG_RESULT_CURRENT_H] = (Int16U)(Current >> 16);
	DataTable[REG_RESULT_CURRENT_L] = (Int16U)Current;
}
//-----------------------------

void LOGIC_LoggingProcess(volatile MeasureSample* Sample)
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
	DISOPAMP_SetVoltage(0);

	Qi = 0;
	RegulatorPulseCounter = 0;
	VoltageTarget = 0;
	LOGIC_TestTime = 0;

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
			LOGIC_SetSubState(SS_Pulse);
			LL_SetStateExtPowerLed(false);
			LL_SetStateExtMsrLed(true);
		}
		else
		{
			LL_SetStateExtPowerLed(true);
			LL_SetStateExtMsrLed(false);
			VoltageTarget = VoltageSetpoint;

			if(!LOGIC_TestTime)
			{
				LOGIC_TestTime = CONTROL_TimeCounter + DataTable[REG_TEST_TIME];
				LOGIC_SetSubState(SS_Pulse);
			}

			if(CONTROL_TimeCounter >= LOGIC_TestTime)
			{
				LL_SetStateExtMsrLed(true);
				LOGIC_SetSubState(SS_Finished);
				return;
			}
			else
				LOGIC_SetSubState(SS_Pulse);
		}

		TIM_Start(TIM6);
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

bool LOGIC_CheckExcessCurrentCutOff(float Current)
{
	if(Current >= CurrentCutOff)
		return true;
	else
		return false;
}
//-----------------------------
