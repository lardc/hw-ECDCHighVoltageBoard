// Header
#include "DebugActions.h"

// Include
//
#include "LowLevel.h"
#include "Board.h"
#include "Delay.h"
#include "Controller.h"
#include "DataTable.h"

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
	return LL_GetStateLineSync1();
}
//-----------------------------

bool DBGACT_ReadStateLineSync2()
{
	return LL_GetStateLineSync2();
}
//-----------------------------

void DBGACT_SetCurrentRange(uint16_t Range)
{
	LL_SetCurrentRage(Range);
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
		case 0:
			LL_WriteDACx((Data & ~DAC_CHANNEL_B), &LL_SetStateCS_SYNC1);
			break;
		case 1:
			LL_WriteDACx((Data & ~DAC_CHANNEL_B), &LL_SetStateCS_SYNC2);
			break;
		case 2:
			LL_WriteDACx((Data & ~DAC_CHANNEL_B), &LL_SetStateCS_SYNC3);
			break;
		case 3:
			LL_WriteDACx((Data & ~DAC_CHANNEL_B), &LL_SetStateCS_SYNC4);
			break;
		case 4:
			LL_WriteDACx((Data & ~DAC_CHANNEL_B), &LL_SetStateCS_SYNC5);
			break;
		case 5:
			LL_WriteDACx((Data & ~DAC_CHANNEL_B), &LL_SetStateCS_SYNC6);
			break;
		case 6:
			LL_WriteDACx((Data & ~DAC_CHANNEL_B), &LL_SetStateCS_SYNC7);
			break;
		case 7:
			LL_WriteDACx((Data & ~DAC_CHANNEL_B), &LL_SetStateCS_SYNC8);
			break;
	}
}
//-----------------------------
