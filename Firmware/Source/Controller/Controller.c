// Header
#include "Controller.h"
//
// Includes
#include "Board.h"
#include "Delay.h"
#include "DeviceProfile.h"
#include "Interrupts.h"
#include "LowLevel.h"
#include "SysConfig.h"
#include "DebugActions.h"
#include "Diagnostic.h"
#include "Logic.h"
#include "BCCIxParams.h"
#include "DiscreteOpAmp.h"

// Types
//
typedef void (*FUNC_AsyncDelegate)();

// Variables
//
volatile DeviceState CONTROL_State = DS_None;
volatile DeviceSubState CONTROL_SubState = SS_None;
static Boolean CycleActive = false;
//
volatile Int64U CONTROL_TimeCounter = 0;
volatile Int64U	CONTROL_AfterPulsePause = 0;
volatile Int16U CONTROL_Values_Counter = 0;
volatile Int16U CONTROL_RegulatorErr_Counter = 0;
volatile Int16U CONTROL_ValuesVoltage[VALUES_x_SIZE];
volatile Int16U CONTROL_ValuesCurrent[VALUES_x_SIZE];
volatile Int16U CONTROL_RegulatorErr[VALUES_x_SIZE];
//
volatile MeasureSample SampleParams;

/// Forward functions
//
static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError);
void CONTROL_SetDeviceState(DeviceState NewState, DeviceSubState NewSubState);
void CONTROL_SwitchToFault(Int16U Reason);
void CONTROL_DelayMs(uint32_t Delay);
void CONTROL_UpdateWatchDog();
void CONTROL_ResetToDefaultState();
void CONTROL_LogicProcess();
void CONTROL_StopProcess(bool ExcessCurrent, Int16U Fault);
void CONTROL_StartProcess();
void CONTROL_ResetOutputRegisters();

// Functions
//
void CONTROL_Init()
{
	// Переменные для конфигурации EndPoint
	Int16U EPIndexes[EP_COUNT] = {EP_VOLTAGE, EP_CURRENT, EP_REGULATOR_ERR};
	Int16U EPSized[EP_COUNT] = {VALUES_x_SIZE, VALUES_x_SIZE, VALUES_x_SIZE};
	pInt16U EPCounters[EP_COUNT] = {(pInt16U)&CONTROL_Values_Counter, (pInt16U)&CONTROL_Values_Counter, (pInt16U)&CONTROL_RegulatorErr_Counter};
	pInt16U EPDatas[EP_COUNT] = {(pInt16U)CONTROL_ValuesVoltage, (pInt16U)CONTROL_ValuesCurrent, (pInt16U)CONTROL_RegulatorErr};

	// Конфигурация сервиса работы Data-table и EPROM
	EPROMServiceConfig EPROMService = {(FUNC_EPROM_WriteValues)&NFLASH_WriteDT, (FUNC_EPROM_ReadValues)&NFLASH_ReadDT};
	// Инициализация data table
	DT_Init(EPROMService, false);
	DT_SaveFirmwareInfo(CAN_SALVE_NID, 0);
	// Инициализация device profile
	DEVPROFILE_Init(&CONTROL_DispatchAction, &CycleActive);
	DEVPROFILE_InitEPService(EPIndexes, EPSized, EPCounters, EPDatas);
	// Сброс значений
	DEVPROFILE_ResetControlSection();
	CONTROL_ResetToDefaultState();
}
//------------------------------------------

void CONTROL_ResetOutputRegisters()
{
	DataTable[REG_FAULT_REASON] = DF_NONE;
	DataTable[REG_DISABLE_REASON] = DF_NONE;
	DataTable[REG_WARNING] = WARNING_NONE;
	DataTable[REG_PROBLEM] = PROBLEM_NONE;
	DataTable[REG_OP_RESULT] = OPRESULT_NONE;
	
	DataTable[REG_RESULT_VOLTAGE] = 0;
	DataTable[REG_RESULT_CURRENT_H] = 0;
	DataTable[REG_RESULT_CURRENT_L] = 0;

	DEVPROFILE_ResetScopes(0);
	DEVPROFILE_ResetEPReadState();
}
//------------------------------------------

void CONTROL_ResetToDefaultState()
{
	CONTROL_ResetOutputRegisters();
	
	LL_SetStateExtPowerLed(true);
	LL_SetStateExtMsrLed(false);
	LL_PowerSupplyEnable(false);

	DISOPAMP_SetVoltage(0);

	CONTROL_SetDeviceState(DS_None, SS_None);
}
//------------------------------------------

void CONTROL_Idle()
{
	CONTROL_LogicProcess();

	DEVPROFILE_ProcessRequests();
	CONTROL_UpdateWatchDog();
}
//------------------------------------------

static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError)
{
	*pUserError = ERR_NONE;
	
	switch (ActionID)
	{
		case ACT_ENABLE_POWER:
			if(CONTROL_State == DS_None)
				CONTROL_SetDeviceState(DS_InProcess, SS_PowerOn);
			else if(CONTROL_State != DS_Ready)
				*pUserError = ERR_OPERATION_BLOCKED;
			break;

		case ACT_DISABLE_POWER:
			if(CONTROL_State == DS_Ready)
			{
				LOGIC_StopProcess();
				CONTROL_SetDeviceState(DS_None, SS_None);
			}
			else
				if(CONTROL_State != DS_None)
					*pUserError = ERR_OPERATION_BLOCKED;
			break;

		case ACT_START_PROCESS:
			if (CONTROL_State == DS_Ready)
			{
				CONTROL_ResetOutputRegisters();
				LOGIC_StartPrepare();
				CONTROL_SetDeviceState(DS_InProcess, SS_PowerPrepare);
			}
			else
				if (CONTROL_State == DS_InProcess)
					*pUserError = ERR_OPERATION_BLOCKED;
				else
					*pUserError = ERR_DEVICE_NOT_READY;
			break;

		case ACT_STOP_PROCESS:
			if (CONTROL_State == DS_InProcess)
			{
				LOGIC_StopProcess();
				CONTROL_SetDeviceState(DS_Ready, SS_None);
			}
			break;

		case ACT_START_CELL_CAL:
			{
				if (CONTROL_State == DS_Ready)
				{
					LOGIC_CalibrationPrepare();
					CONTROL_SetDeviceState(DS_InProcess, SS_PowerPrepare);
				}
				else
					*pUserError = ERR_OPERATION_BLOCKED;
			}
			break;

		case ACT_CLR_FAULT:
			if (CONTROL_State == DS_Fault)
			{
				CONTROL_SetDeviceState(DS_None, SS_None);
				DataTable[REG_FAULT_REASON] = DF_NONE;
			}
			break;

		case ACT_CLR_WARNING:
			DataTable[REG_WARNING] = WARNING_NONE;
			break;

		default:
			return DIAG_HandleDiagnosticAction(ActionID, pUserError);
			
	}
	return true;
}
//-----------------------------------------------

void CONTROL_LogicProcess()
{
	static Int64U PowerPrepareTimer = 0;

	switch(CONTROL_SubState)
	{
		case SS_PowerOn:
			CONTROL_SetDeviceState(DS_Ready, SS_None);
			break;

		case SS_PowerPrepare:
			{
				if(CONTROL_TimeCounter > CONTROL_AfterPulsePause)
				{
					if(!PowerPrepareTimer)
					{
						LL_SetStateExtMsrLed(true);
						LL_PowerSupplyEnable(true);
						PowerPrepareTimer = CONTROL_TimeCounter + DataTable[REG_PS_ACTIVITY_TIME];
					}

					if(CONTROL_TimeCounter > PowerPrepareTimer)
					{
						PowerPrepareTimer = 0;
						LL_PowerSupplyEnable(false);

						CONTROL_SetDeviceState(DS_InProcess, SS_PowerPrepareDelay);
					}
				}
			}
			break;

		case SS_PowerPrepareDelay:
			{
				if(!PowerPrepareTimer)
					PowerPrepareTimer = CONTROL_TimeCounter + DataTable[REG_START_DELAY];

				if(CONTROL_TimeCounter > PowerPrepareTimer)
				{
					PowerPrepareTimer = 0;
					CONTROL_SetDeviceState(DS_InProcess, SS_Pulse);
					CONTROL_StartProcess();
				}
			}
			break;

		default:
			break;
	}
}
//-----------------------------------------------

void CONTROL_HighPriorityFastProcess()
{
	Int16U Fault;
	bool ExcessCurrent, RegulatorWasFinishedProcess;

	if(CONTROL_SubState == SS_Pulse)
	{
		MEASURE_SampleParams(&SampleParams);

		ExcessCurrent = LOGIC_CheckExcessCurrentCutOff(SampleParams.Current);

		if(!ExcessCurrent)
			RegulatorWasFinishedProcess = LOGIC_RegulatorCycle(SampleParams.Voltage, &Fault);

		if(RegulatorWasFinishedProcess || ExcessCurrent)
		{
			CONTROL_StopProcess(ExcessCurrent, Fault);

			if(ExcessCurrent)
				LOGIC_SaveLastSampledTestResult(&SampleParams);
			else
				LOGIC_SaveAveragedTestResult();
		}

		LOGIC_LoggingProcess(&SampleParams);
	}
}
//-----------------------------------------------

void CONTROL_StartProcess()
{
	MEASURE_DMABuffersClear();
	LL_SetStateLineSync2(true);
	TIM_Start(TIM6);
}
//-----------------------------------------------

void CONTROL_StopProcess(bool ExcessCurrent, Int16U Fault)
{
	LOGIC_StopProcess();

	LL_SetStateLineSync2(false);
	LL_SetStateExtMsrLed(false);

	if(ExcessCurrent && (Fault == DF_FOLOWING_ERROR))
	{
		DataTable[REG_OP_RESULT] = OPRESULT_FAIL;
		DataTable[REG_PROBLEM] = PROBLEM_SHORT_CICUIT;
		CONTROL_SetDeviceState(DS_Ready, SS_None);
	}
	else if(ExcessCurrent)
	{
		DataTable[REG_OP_RESULT] = OPRESULT_OK;
		DataTable[REG_PROBLEM] = PROBLEM_CURRENT_CUTOFF;
		CONTROL_SetDeviceState(DS_Ready, SS_None);
	}
	else if(Fault == DF_FOLOWING_ERROR)
	{
		DataTable[REG_OP_RESULT] = OPRESULT_FAIL;
		CONTROL_SwitchToFault(DF_FOLOWING_ERROR);
	}
	else
	{
		DataTable[REG_OP_RESULT] = OPRESULT_OK;
		CONTROL_SetDeviceState(DS_Ready, SS_None);
	}

	CONTROL_AfterPulsePause = CONTROL_TimeCounter + DataTable[REG_AFTER_PULSE_PAUSE];
}
//-----------------------------------------------

void CONTROL_SwitchToFault(Int16U Reason)
{
	CONTROL_SetDeviceState(DS_Fault, SS_None);
	DataTable[REG_FAULT_REASON] = Reason;
}
//------------------------------------------

void CONTROL_SetDeviceState(DeviceState NewState, DeviceSubState NewSubState)
{
	CONTROL_State = NewState;
	CONTROL_SubState = NewSubState;
	DataTable[REG_DEV_STATE] = NewState;
	DataTable[REG_SUB_STATE] = NewSubState;
}
//------------------------------------------

void CONTROL_DelayMs(uint32_t Delay)
{
	uint64_t Counter = (uint64_t)CONTROL_TimeCounter + Delay;
	while(Counter > CONTROL_TimeCounter)
		CONTROL_UpdateWatchDog();
}
//------------------------------------------

void CONTROL_UpdateWatchDog()
{
	if(BOOT_LOADER_VARIABLE != BOOT_LOADER_REQUEST)
		IWDG_Refresh();
}
//------------------------------------------

