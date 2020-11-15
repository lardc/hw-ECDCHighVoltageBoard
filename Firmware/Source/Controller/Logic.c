// Includes
#include "Board.h"
#include "Logic.h"
#include "ConvertUtils.h"
#include "DataTable.h"
#include "DiscreteOpAmp.h"
#include "LowLevel.h"

// Definitions
#define MAF_BUFFER_LENGTH				128
#define MAF_BUFFER_INDEX_MASK			MAF_BUFFER_LENGTH - 1
//

// Variables
float VoltageTarget, VoltageSetpoint, CurrentCutOff, RegulatorPcoef, RegulatorIcoef, RegulatorAlowedError, dV;
float  Qi;
Int16U RegulatorPulseCounter = 0;
Int16U PulsePointsQuantity = 0;
volatile Int64U LOGIC_PowerOnCounter = 0;
volatile Int64U LOGIC_BetweenPulsesDelay = 0;
volatile Int64U LOGIC_TestTime = 0;

// Arrays
float RingBuffer_Current[MAF_BUFFER_LENGTH];
float RingBuffer_Voltage[MAF_BUFFER_LENGTH];

// Functions prototypes
void LOGIC_SetCurrentCutOff(float Current);
void LOGIC_CacheVariables();
void LOGIC_SaveToRingBuffer(volatile MeasureSample* Sample);
Int32U LOGIC_ExtractAveragedDatas(float* Buffer, Int16U BufferLength);
void LOGIC_SaveRegulatorErr(float Error);

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
	LOGIC_SetCurrentCutOff(DISOPAMP_CELL_CURRENT_MAX);
	RegulatorPcoef = 0;
	RegulatorIcoef = 0;
}
//-----------------------------

void LOGIC_CacheVariables()
{
	VoltageSetpoint = (float)DataTable[REG_VOLTAGE_SETPOINT] / 10;
	CurrentCutOff = (float)((Int32U)((DataTable[REG_CURRENT_CUTOFF_H] << 16) | DataTable[REG_CURRENT_CUTOFF_L])) / 100;
	PulsePointsQuantity = DataTable[REG_PULSE_WIDTH] * 1000 / TIMER6_uS;
	RegulatorPcoef = (float)DataTable[REG_REGULATOR_Kp] / 1000;
	RegulatorIcoef = (float)DataTable[REG_REGULATOR_Ki] / 1000;
	dV = VoltageSetpoint / DataTable[REG_PULSE_FRONT_WIDTH] * TIMER6_uS / 1000;
	RegulatorAlowedError = (float)DataTable[REG_REGULATOR_ALOWED_ERR] / 1000;
}
//-----------------------------

bool LOGIC_RegulatorCycle(float Voltage, Int16U *Fault)
{
	static Int16U FollowingErrorCounter = 0;
	float RegulatorError, Qp, RegulatorOut, ErrorX;

	// Формирование линейно нарастающего фронта импульса напряжения
	VoltageTarget += dV;
	if(VoltageTarget > VoltageSetpoint)
		VoltageTarget = VoltageSetpoint;

	RegulatorError = (RegulatorPulseCounter == 0) ? 0 : (VoltageTarget - Voltage);
	ErrorX = RegulatorError / VoltageSetpoint;

	if(ErrorX <= RegulatorAlowedError)
	{
		FollowingErrorCounter = 0;

		Qi += RegulatorError * RegulatorIcoef;

		if(Qi > DataTable[REG_REGULATOR_QI_MAX])
			Qi = DataTable[REG_REGULATOR_QI_MAX];

		if(Qi < (-1) * DataTable[REG_REGULATOR_QI_MAX])
			Qi = (-1) * DataTable[REG_REGULATOR_QI_MAX];

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

	LOGIC_SaveRegulatorErr(RegulatorOut);

	RegulatorPulseCounter++;

	if(RegulatorPulseCounter >= PulsePointsQuantity)
		return true;
	else
		return false;
}
//-----------------------------

void LOGIC_SaveRegulatorErr(float Error)
{
	static Int16U ScopeLogStep = 0, LocalCounter = 0;

	// Сброс локального счетчика в начале логгирования
	if (CONTROL_RegulatorErr_Counter == 0)
		LocalCounter = 0;

	if (ScopeLogStep++ >= DataTable[REG_SCOPE_STEP])
	{
		ScopeLogStep = 0;

		CONTROL_RegulatorErr[LocalCounter] = (Int16S)(Error * 10);
		CONTROL_RegulatorErr_Counter = LocalCounter;

		++LocalCounter;
	}

	// Условие обновления глобального счетчика данных
	if (CONTROL_RegulatorErr_Counter < VALUES_x_SIZE)
		CONTROL_RegulatorErr_Counter = LocalCounter;

	// Сброс локального счетчика
	if (LocalCounter >= VALUES_x_SIZE)
		LocalCounter = 0;
}

void LOGIC_SaveAveragedTestResult()
{
	Int32U Current;

	DataTable[REG_RESULT_VOLTAGE] = (Int16U)(LOGIC_ExtractAveragedDatas(&RingBuffer_Voltage[0], MAF_BUFFER_LENGTH) / 10);
	Current = LOGIC_ExtractAveragedDatas(&RingBuffer_Current[0], MAF_BUFFER_LENGTH);
	DataTable[REG_RESULT_CURRENT_H] = (Int16U)(Current >> 16);
	DataTable[REG_RESULT_CURRENT_L] = (Int16U)Current;
}
//-----------------------------

void LOGIC_SaveLastSampledTestResult(volatile MeasureSample* Sample)
{
	Int32U Current;

	DataTable[REG_RESULT_VOLTAGE] = (Int16U)(Sample->Voltage * 10);
	Current = (Int32U) (Sample->Current * 100);
	DataTable[REG_RESULT_CURRENT_H] = (Int16U)(Current >> 16);
	DataTable[REG_RESULT_CURRENT_L] = (Int16U)Current;
}
//-----------------------------

Int32U LOGIC_ExtractAveragedDatas(float* Buffer, Int16U BufferLength)
{
	float Temp = 0;

	for(int i = 0; i < BufferLength; i++)
		Temp += *(Buffer + i);

	return (Int32U) (Temp / BufferLength * 100);
}
//-----------------------------

void LOGIC_SaveToRingBuffer(volatile MeasureSample* Sample)
{
	static Int16U BufferIndex = 0;

	RingBuffer_Current[BufferIndex] = Sample->Current;
	RingBuffer_Voltage[BufferIndex] = Sample->Voltage;

	BufferIndex++;
	BufferIndex &= MAF_BUFFER_INDEX_MASK;
}
//-----------------------------

void LOGIC_LoggingProcess(volatile MeasureSample* Sample)
{
	static Int16U ScopeLogStep = 0, LocalCounter = 0;

	// Сброс локального счётчика в начале логгирования
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

	LOGIC_SaveToRingBuffer(Sample);

	// Условие обновления глобального счётчика данных
	if (CONTROL_Values_Counter < VALUES_x_SIZE)
		CONTROL_Values_Counter = LocalCounter;

	// Сброс локального счётчика
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
	DISOPAMP_SetCurrentCutOff(Current);
}
//-----------------------------

bool LOGIC_CheckExcessCurrentCutOff(float Current)
{
	if(!DataTable[REG_MUTE_EXCESS_CURRENT] && (Current >= CurrentCutOff))
		return true;
	else
		return false;
}
//-----------------------------
