// Header
#include "DebugActions.h"

// Include
//
#include "LowLevel.h"
#include "Board.h"
#include "Delay.h"
#include "Controller.h"
#include "DataTable.h"

// Defines
#define DBG_CELL_0				0
#define DBG_CELL_1				1
#define DBG_CELL_2				2
#define DBG_CELL_3				3
#define DBG_CELL_4				4
#define DBG_CELL_5				5
#define DBG_CELL_6				6
#define DBG_CELL_7				7
//
#define DBG_CURRENT_RANGE_0		0
#define DBG_CURRENT_RANGE_1		1
#define DBG_CURRENT_RANGE_2		2
#define DBG_CURRENT_RANGE_3		3

// Functions
//
void DBGACT_BlinkExtLeds()
{
	LL_SetStateExtPowerLed(TRUE);
	LL_SetStateExtMsrLed(TRUE);
	CONTROL_DelayMs(1000);
	LL_SetStateExtPowerLed(FALSE);
	LL_SetStateExtMsrLed(FALSE);
}
//-----------------------------

void DBGACT_GenerateImpulseToLineSync1()
{
	LL_SetStateLineSync1(TRUE);
	CONTROL_DelayMs(100);
	LL_SetStateLineSync1(FALSE);
}
//-----------------------------

void DBGACT_GenerateImpulseToLineSync2()
{
	LL_SetStateLineSync2(TRUE);
	CONTROL_DelayMs(100);
	LL_SetStateLineSync2(FALSE);
}
//-----------------------------

bool DBGACT_ReadStateLineSync1()
{
	bool LineState;

	(DataTable[REG_DBG]) ? LL_SetStateLineSync1(true) : LL_SetStateLineSync1(false);
	CONTROL_DelayMs(100);
	LineState = LL_GetStateLineSync1();
	LL_SetStateLineSync1(false);
	return LineState;
}
//-----------------------------

bool DBGACT_ReadStateLineSync2()
{
	bool LineState;

	(DataTable[REG_DBG]) ? LL_SetStateLineSync2(true) : LL_SetStateLineSync2(false);
	CONTROL_DelayMs(100);
	LineState = LL_GetStateLineSync2();
	LL_SetStateLineSync2(false);
	return LineState;
}
//-----------------------------

void DBGACT_SetCurrentRange(uint16_t Range)
{
	switch(Range)
	{
		case DBG_CURRENT_RANGE_0:
			LL_SetCurrentRange0();
			break;

		case DBG_CURRENT_RANGE_1:
			LL_SetCurrentRange1();
			break;

		case DBG_CURRENT_RANGE_2:
			LL_SetCurrentRange2();
			break;

		case DBG_CURRENT_RANGE_3:
			LL_SetCurrentRange3();
			break;
	}
}
//-----------------------------

bool DBGACT_ReadStatePowerSupplies()
{
	return LL_ArePowerSuppliesReady();
}
//-----------------------------

void DBGACT_SetCurrentCutoff(uint16_t Data)
{
	LL_WriteDACx((Data | DAC_CHANNEL_B), &LL_GroupStateCS_SYNC);
}
//-----------------------------

void DBGACT_SetVoltageCell(uint16_t CellNumber, uint16_t Data)
{
	switch(CellNumber)
	{
		case DBG_CELL_0:
			LL_WriteDACx((Data & ~DAC_CHANNEL_B), &LL_SetStateCS_SYNC1);
			break;
		case DBG_CELL_1:
			LL_WriteDACx((Data & ~DAC_CHANNEL_B), &LL_SetStateCS_SYNC2);
			break;
		case DBG_CELL_2:
			LL_WriteDACx((Data & ~DAC_CHANNEL_B), &LL_SetStateCS_SYNC3);
			break;
		case DBG_CELL_3:
			LL_WriteDACx((Data & ~DAC_CHANNEL_B), &LL_SetStateCS_SYNC4);
			break;
		case DBG_CELL_4:
			LL_WriteDACx((Data & ~DAC_CHANNEL_B), &LL_SetStateCS_SYNC5);
			break;
		case DBG_CELL_5:
			LL_WriteDACx((Data & ~DAC_CHANNEL_B), &LL_SetStateCS_SYNC6);
			break;
		case DBG_CELL_6:
			LL_WriteDACx((Data & ~DAC_CHANNEL_B), &LL_SetStateCS_SYNC7);
			break;
		case DBG_CELL_7:
			LL_WriteDACx((Data & ~DAC_CHANNEL_B), &LL_SetStateCS_SYNC8);
			break;
	}
}
//-----------------------------
