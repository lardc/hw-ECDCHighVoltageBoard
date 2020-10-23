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
#include "CellCalibration.h"

// Types
//
typedef void (*FUNC_AsyncDelegate)();

// Variables
//
volatile DeviceState CONTROL_State = DS_None;
static Boolean CycleActive = false;
//
volatile Int64U CONTROL_TimeCounter = 0;
volatile Int16U CONTROL_Values_Counter = 0;
volatile Int16U CONTROL_ValuesVoltage[VALUES_x_SIZE];
volatile Int16U CONTROL_ValuesCurrent[VALUES_x_SIZE];
//
volatile MeasureSample SampleParams;

/// Forward functions
//
static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError);
void CONTROL_SetDeviceState(DeviceState NewState);
void CONTROL_SwitchToFault(Int16U Reason);
void CONTROL_DelayMs(uint32_t Delay);
void CONTROL_UpdateWatchDog();
void CONTROL_ResetToDefaultState();
void CONTROL_PowerMonitor();
void CONTROL_StopProcess(bool ExcessCurrent, Int16U Fault);
void CONTROL_StartProcess();

// Functions
//
void CONTROL_Init()
{
	// ���������� ��� ������������ EndPoint
	Int16U EPIndexes[EP_COUNT] = {EP_VOLTAGE, EP_CURRENT};
	Int16U EPSized[EP_COUNT] = {VALUES_x_SIZE, VALUES_x_SIZE};
	pInt16U EPCounters[EP_COUNT] = {(pInt16U)&CONTROL_Values_Counter, (pInt16U)&CONTROL_Values_Counter};
	pInt16U EPDatas[EP_COUNT] = {(pInt16U)CONTROL_ValuesVoltage, (pInt16U)CONTROL_ValuesCurrent};

	// ������������ ������� ������ Data-table � EPROM
	EPROMServiceConfig EPROMService = {(FUNC_EPROM_WriteValues)&NFLASH_WriteDT, (FUNC_EPROM_ReadValues)&NFLASH_ReadDT};
	// ������������� data table
	DT_Init(EPROMService, false);
	DT_SaveFirmwareInfo(CAN_SALVE_NID, 0);
	// ������������� device profile
	DEVPROFILE_Init(&CONTROL_DispatchAction, &CycleActive);
	DEVPROFILE_InitEPService(EPIndexes, EPSized, EPCounters, EPDatas);
	// ����� ��������
	DEVPROFILE_ResetControlSection();
	CONTROL_ResetToDefaultState();

	LL_SetStateExtPowerLed(true);
}
//------------------------------------------

void CONTROL_ResetToDefaultState()
{
	DataTable[REG_FAULT_REASON] = DF_NONE;
	DataTable[REG_DISABLE_REASON] = DF_NONE;
	DataTable[REG_WARNING] = WARNING_NONE;
	DataTable[REG_PROBLEM] = PROBLEM_NONE;
	DataTable[REG_OP_RESULT] = OPRESULT_NONE;
	
	DEVPROFILE_ResetScopes(0);
	DEVPROFILE_ResetEPReadState();
	
	CONTROL_SetDeviceState(DS_None);
}

//------------------------------------------

void CONTROL_Idle()
{
	CONTROL_PowerMonitor();

	DEVPROFILE_ProcessRequests();
	CONTROL_UpdateWatchDog();
}
//------------------------------------------

static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError)
{
	*pUserError = ERR_NONE;
	
	switch (ActionID)
	{
		case ACT_START_PROCESS:
			if (CONTROL_State == DS_Ready)
			{
				CONTROL_SetDeviceState(DS_InProcess);
				CONTROL_StartProcess();
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
				CONTROL_SetDeviceState(DS_Ready);
			}
			else
				*pUserError = ERR_OPERATION_BLOCKED;
			break;

		case ACT_START_CELL_CAL:
			{
				if (CONTROL_State == DS_Ready)
				{
					LOGIC_StartPrepare();

					CELLCAL_SetVoltageCell((float)DataTable[REG_VOLTAGE_SETPOINT] / 10, DataTable[REG_DBG_CELL_NUM]);
					CONTROL_DelayMs(CELLCAL_PULSE_WIDTH);
					CELLCAL_SetVoltageCell(0, DataTable[REG_DBG_CELL_NUM]);
				}
				else
					*pUserError = ERR_OPERATION_BLOCKED;
			}
			break;

		case ACT_CLR_FAULT:
			if (CONTROL_State == DS_Fault)
			{
				CONTROL_SetDeviceState(DS_None);
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

void CONTROL_PowerMonitor()
{
	Int16U PowerState;

	PowerState = LOGIC_PowerMonitor();

	if(PowerState)
	{
		LOGIC_StopProcess();
		CONTROL_SwitchToFault(PowerState);
	}
	else
		if(CONTROL_State == DS_None)
			CONTROL_SetDeviceState(DS_Ready);
}
//-----------------------------------------------

void CONTROL_HighPriorityFastProcess()
{
	Int16U Fault;
	bool ExcessCurrent;

	if(CONTROL_State == DS_InProcess)
	{
		MEASURE_SampleParams(&SampleParams);

		ExcessCurrent = LOGIC_CheckExcessCurrentCutOff(SampleParams.Current);

		if(LOGIC_RegulatorCycle(SampleParams.Voltage, &Fault) || ExcessCurrent)
		{
			LOGIC_SaveMeasuredData(&SampleParams);
			CONTROL_StopProcess(ExcessCurrent, Fault);
		}

		LOGIC_LoggingProcess(&SampleParams);
	}
}
//-----------------------------------------------

void CONTROL_StartProcess()
{
	DEVPROFILE_ResetScopes(0);
	DEVPROFILE_ResetEPReadState();
	LOGIC_StartPrepare();

	TIM_Start(TIM6);
}
//-----------------------------------------------

void CONTROL_StopProcess(bool ExcessCurrent, Int16U Fault)
{
	LOGIC_StopProcess();

	if(ExcessCurrent && (Fault == DF_FOLOWING_ERROR))
	{
		DataTable[REG_OP_RESULT] = OPRESULT_FAIL;
		DataTable[REG_PROBLEM] = PROBLEM_SHORT_CICUIT;
		CONTROL_SetDeviceState(DS_Ready);
	}
	else if(ExcessCurrent)
	{
		DataTable[REG_OP_RESULT] = OPRESULT_OK;
		DataTable[REG_PROBLEM] = PROBLEM_CURRENT_CUTOFF;
		CONTROL_SetDeviceState(DS_Ready);
	}
	else if(Fault == DF_FOLOWING_ERROR)
	{
		DataTable[REG_OP_RESULT] = OPRESULT_FAIL;
		CONTROL_SwitchToFault(DF_FOLOWING_ERROR);
	}
	else
	{
		DataTable[REG_OP_RESULT] = OPRESULT_OK;
		CONTROL_SetDeviceState(DS_Ready);
	}
}
//-----------------------------------------------

void CONTROL_SwitchToFault(Int16U Reason)
{
	CONTROL_SetDeviceState(DS_Fault);
	DataTable[REG_FAULT_REASON] = Reason;
}
//------------------------------------------

void CONTROL_SetDeviceState(DeviceState NewState)
{
	CONTROL_State = NewState;
	DataTable[REG_DEV_STATE] = NewState;
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

