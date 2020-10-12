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

// Types
//
typedef void (*FUNC_AsyncDelegate)();

// Variables
//
volatile DeviceState CONTROL_State = DS_None;
volatile SubState CONTROL_SubState = SS_None;
static Boolean CycleActive = false;
//
volatile Int64U CONTROL_TimeCounter = 0;
volatile Int64U CONTROL_PowerOnCounter = 0;
volatile Int16U CONTROL_ValuesVoltageCounter = 0;
volatile Int16U CONTROL_ValuesCurrentCounter = 0;
volatile Int16U CONTROL_ValuesVoltage[VALUES_x_SIZE];
volatile Int16U CONTROL_ValuesCurrent[VALUES_x_SIZE];

/// Forward functions
//
static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError);
void CONTROL_SetDeviceState(DeviceState NewState, SubState NewSubState);
void CONTROL_SwitchToFault(Int16U Reason);
void CONTROL_DelayMs(uint32_t Delay);
void CONTROL_UpdateWatchDog();
void CONTROL_ResetToDefaultState();
void CONTROL_PowerMonitor();
void CONTROL_Process();
void CONTROL_StopProcess();

// Functions
//
void CONTROL_Init()
{
	// Переменные для конфигурации EndPoint
	Int16U EPIndexes[EP_COUNT] = {EP_VOLTAGE, EP_CURRENT};
	Int16U EPSized[EP_COUNT] = {VALUES_x_SIZE, VALUES_x_SIZE};
	pInt16U EPCounters[EP_COUNT] = {(pInt16U)&CONTROL_ValuesVoltageCounter, (pInt16U)&CONTROL_ValuesCurrentCounter,};
	pInt16U EPDatas[EP_COUNT] = {(pInt16U)CONTROL_ValuesVoltage, (pInt16U)CONTROL_ValuesCurrent,};

	// Конфигурация сервиса работы Data-table и EPROM
	EPROMServiceConfig EPROMService = {(FUNC_EPROM_WriteValues)&NFLASH_WriteDT, (FUNC_EPROM_ReadValues)&NFLASH_ReadDT};
	// Инициализация data table
	DT_Init(EPROMService, false);
	// Инициализация device profile
	DEVPROFILE_Init(&CONTROL_DispatchAction, &CycleActive);
	DEVPROFILE_InitEPService(EPIndexes, EPSized, EPCounters, EPDatas);
	// Сброс значений
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
	
	CONTROL_SetDeviceState(DS_None, SS_None);
}

//------------------------------------------

void CONTROL_Idle()
{
	CONTROL_PowerMonitor();
	CONTROL_Process();

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
			{
				if(CONTROL_State == DS_None)
				{
					CONTROL_SetDeviceState(DS_InProcess, SS_PowerOn);
				}
				else if(CONTROL_State != DS_InProcess)
				{
					*pUserError = ERR_DEVICE_NOT_READY;
				}
				break;
			}
			
		case ACT_DISABLE_POWER:
			if(CONTROL_State == DS_Ready)
			{
				CONTROL_SetDeviceState(DS_None, SS_None);
			}
			else
				*pUserError = ERR_OPERATION_BLOCKED;
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

void CONTROL_PowerMonitor()
{
	if(CONTROL_State == DS_InProcess)
	{
		if(CONTROL_SubState == SS_PowerOn)
		{
			if(CONTROL_PowerOnCounter == 0)
				CONTROL_PowerOnCounter = CONTROL_TimeCounter + DataTable[REG_POWER_ON_TIMEOUT];
			else
			{
				if(!LL_ArePowerSuppliesReady())
				{
					if(CONTROL_TimeCounter >= CONTROL_PowerOnCounter)
						CONTROL_SwitchToFault(DF_POWER_SUPPLY);
				}
				else
					CONTROL_SetDeviceState(DS_Ready, SS_None);
			}
		}
		else
		{
			if(!LL_ArePowerSuppliesReady())
			{
				CONTROL_SwitchToFault(DF_POWER_SUPPLY);
				CONTROL_StopProcess();
			}
		}
	}
}
//-----------------------------------------------

void CONTROL_Process()
{

}
//-----------------------------------------------

void CONTROL_StopProcess()
{

}
//-----------------------------------------------

void CONTROL_SwitchToFault(Int16U Reason)
{
	CONTROL_SetDeviceState(DS_Fault, SS_None);
	DataTable[REG_FAULT_REASON] = Reason;
}
//------------------------------------------

void CONTROL_SetDeviceState(DeviceState NewState, SubState NewSubState)
{
	CONTROL_SubState = NewSubState;
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

