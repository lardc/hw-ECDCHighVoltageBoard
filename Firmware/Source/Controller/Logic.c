// Includes
#include "Board.h"
#include "Logic.h"
#include "ConvertUtils.h"
#include "DataTable.h"
#include "DiscreteOpAmp.h"
#include "LowLevel.h"

// Definitions
#define CURRENT_CUTOFF_LEVEL_SHIFT		1.1

// Variables
float VoltageTarget, VoltageSetpoint, CurrentCutOff, RegulatorPcoef, RegulatorIcoef, RegulatorAlowedError, dV;
float  Qi;
Int16U RegulatorPulseCounter = 0;
Int16U PulsePointsQuantity = 0;
volatile Int64U LOGIC_PowerOnCounter = 0;
volatile Int64U LOGIC_BetweenPulsesDelay = 0;
volatile Int64U LOGIC_TestTime = 0;

// Functions prototypes
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

void LOGIC_CalibrationPrepare()
{
	LOGIC_StartPrepare();
	LOGIC_SetCurrentCutOff(DISOPAMP_CURRENT_THRESHOLD_RANGE_3);
	RegulatorPcoef = 0;
	RegulatorIcoef = 0;
}
//-----------------------------

void LOGIC_CacheVariables()
{
	VoltageSetpoint = (float)DataTable[REG_VOLTAGE_SETPOINT] / 10;
	CurrentCutOff = (float)((Int32U)((DataTable[REG_CURRENT_CUTOFF_H] << 16) | DataTable[REG_CURRENT_CUTOFF_L])) / 10;
	PulsePointsQuantity = DataTable[REG_PULSE_WIDTH] * 1000 / TIMER6_uS;
	RegulatorPcoef = (float)DataTable[REG_REGULATOR_Kp] / 1000;
	RegulatorIcoef = (float)DataTable[REG_REGULATOR_Ki] / 1000;
	dV = (float)DataTable[REG_VOLATGE_RATE] / 10 * TIMER6_uS / 1000;
	RegulatorAlowedError = (float)DataTable[REG_REGULATOR_ALOWED_ERR] / 1000;
}
//-----------------------------

bool LOGIC_RegulatorCycle(float Voltage, Int16U *Fault)
{
	static Int16U FollowingErrorCounter = 0;
	float RegulatorError, Qp, RegulatorOut, ErrorX;

	// ������������ ������� ������������ ������ �������� ����������
	VoltageTarget += dV;
	if(VoltageTarget > VoltageSetpoint)
		VoltageTarget = VoltageSetpoint;

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
				*Fault = DF_FOLOWING_ERROR;
				return true;
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
		return true;
	else
		return false;
}
//-----------------------------

void LOGIC_SaveMeasuredData(volatile MeasureSample* Sample)
{
	Int32U Current;

	DataTable[REG_RESULT_VOLTAGE] = (Int16U)(Sample->Voltage * 10);
	Current = (Int32U)(Sample->Current * 10);
	DataTable[REG_RESULT_CURRENT_H] = (Int16U)(Current >> 16);
	DataTable[REG_RESULT_CURRENT_L] = (Int16U)Current;
}
//-----------------------------

void LOGIC_LoggingProcess(volatile MeasureSample* Sample)
{
	static Int16U ScopeLogStep = 0, LocalCounter = 0;

	// ����� ���������� �������� � ������ ������������
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

	// ������� ���������� ����������� �������� ������
	if (CONTROL_Values_Counter < VALUES_x_SIZE)
		CONTROL_Values_Counter = LocalCounter;

	// ����� ���������� ��������
	if (LocalCounter >= VALUES_x_SIZE)
		LocalCounter = 0;
}
//-----------------------------

void LOGIC_StopProcess()
{
	TIM_Stop(TIM6);
	DISOPAMP_SetVoltage(0);

	Qi = 0;
	RegulatorPulseCounter = 0;
	VoltageTarget = 0;
	LOGIC_TestTime = 0;
}
//-----------------------------

void LOGIC_SetCurrentCutOff(float Current)
{
	// ���������� ����������� ���� ������������ ���� ���������
	DISOPAMP_SetCurrentCutOff(Current * CURRENT_CUTOFF_LEVEL_SHIFT);
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
