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
	LL_SetStateExtMsrLed(TRUE);
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
