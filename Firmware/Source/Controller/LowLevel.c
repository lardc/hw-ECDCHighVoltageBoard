// Header
#include "LowLevel.h"
// Include
#include "Board.h"
#include "Delay.h"

// Functions
//
void LL_ToggleBoardLED()
{
	GPIO_Toggle(GPIO_INT_LED);
}
//-----------------------------

void LL_SetStateExtPowerLed(bool State)
{
	GPIO_SetState(GPIO_EXT_LED1, !State);
}
//-----------------------------

void LL_SetStateExtMsrLed(bool State)
{
	GPIO_SetState(GPIO_EXT_LED2, !State);
}
//-----------------------------

void LL_SetStateLineSync1(bool State)
{
	GPIO_SetState(GPIO_SYNC1_OUT, !State);
}
//-----------------------------

void LL_SetStateLineSync2(bool State)
{
	GPIO_SetState(GPIO_SYNC2_OUT, !State);
}
//-----------------------------

bool LL_GetStateLineSync1()
{
	return GPIO_GetState(GPIO_SYNC1_IN);
}
//-----------------------------

bool LL_GetStateLineSync2()
{
	return GPIO_GetState(GPIO_SYNC2_IN);
}
//-----------------------------

bool LL_ArePowerSuppliesReady()
{
	return !GPIO_GetState(GPIO_PS_STATES);
}
//-----------------------------

void LL_SetCurrentRage(uint16_t Range)
{
	switch(Range)
	{
		case 0:
		{
			GPIO_SetState(GPIO_R0_M, true);
			GPIO_SetState(GPIO_R1_M, false);
			GPIO_SetState(GPIO_R2_M, false);
		}
		break;

		case 1:
		{
			GPIO_SetState(GPIO_R0_M, false);
			GPIO_SetState(GPIO_R1_M, true);
			GPIO_SetState(GPIO_R2_M, false);
		}
		break;

		case 2:
		{
			GPIO_SetState(GPIO_R0_M, false);
			GPIO_SetState(GPIO_R1_M, false);
			GPIO_SetState(GPIO_R2_M, true);
		}
		break;

		default:
		{
			GPIO_SetState(GPIO_R0_M, true);
			GPIO_SetState(GPIO_R1_M, false);
			GPIO_SetState(GPIO_R2_M, false);
		}
		break;
	}
}

void LL_WriteDACx(uint16_t Data, void (*SetState_CS_SYNC)(bool State))
{
	SetState_CS_SYNC(false);
	SPI_WriteByte(SPI1, Data);
	SetState_CS_SYNC(true);
	DELAY_US(1);

	GPIO_SetState(GPIO_LDAC, false);
	DELAY_US(5);
	GPIO_SetState(GPIO_LDAC, true);
	DELAY_US(1);
}
//---------------------

void LL_GroupStateCS_SYNC(bool State)
{
	GPIO_SetState(GPIO_CS_SYNC1, State);
	GPIO_SetState(GPIO_CS_SYNC2, State);
	GPIO_SetState(GPIO_CS_SYNC3, State);
	GPIO_SetState(GPIO_CS_SYNC4, State);
	GPIO_SetState(GPIO_CS_SYNC5, State);
	GPIO_SetState(GPIO_CS_SYNC6, State);
	GPIO_SetState(GPIO_CS_SYNC7, State);
	GPIO_SetState(GPIO_CS_SYNC8, State);
}
//---------------------

void LL_SetStateCS_SYNC1(bool State)
{
	GPIO_SetState(GPIO_CS_SYNC1, State);
}
//---------------------

void LL_SetStateCS_SYNC2(bool State)
{
	GPIO_SetState(GPIO_CS_SYNC2, State);
}
//---------------------

void LL_SetStateCS_SYNC3(bool State)
{
	GPIO_SetState(GPIO_CS_SYNC3, State);
}
//---------------------

void LL_SetStateCS_SYNC4(bool State)
{
	GPIO_SetState(GPIO_CS_SYNC4, State);
}
//---------------------

void LL_SetStateCS_SYNC5(bool State)
{
	GPIO_SetState(GPIO_CS_SYNC5, State);
}
//---------------------

void LL_SetStateCS_SYNC6(bool State)
{
	GPIO_SetState(GPIO_CS_SYNC6, State);
}
//---------------------

void LL_SetStateCS_SYNC7(bool State)
{
	GPIO_SetState(GPIO_CS_SYNC7, State);
}
//---------------------

void LL_SetStateCS_SYNC8(bool State)
{
	GPIO_SetState(GPIO_CS_SYNC8, State);
}
//---------------------

