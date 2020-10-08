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
	GPIO_SetState(GPIO_EXT_LED1, State);
}
//-----------------------------

void LL_SetStateExtMsrLed(bool State)
{
	GPIO_SetState(GPIO_EXT_LED2, State);
}
//-----------------------------

void LL_SetStateInterruptLineSync1(bool State)
{
	GPIO_SetState(GPIO_INT_SYNC1_OUT, State);
}
//-----------------------------

void LL_SetStateInterruptLineSync2(bool State)
{
	GPIO_SetState(GPIO_INT_SYNC2_OUT, State);
}
//-----------------------------

bool LL_GetStateInterruptLineSync1()
{
	return GPIO_GetState(GPIO_INT_SYNC1_IN);
}
//-----------------------------

bool LL_GetStateInterruptLineSync2()
{
	return GPIO_GetState(GPIO_INT_SYNC2_IN);
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

void LL_DiscreteOpAmpWriteDAC(uint16_t Data, GPIO_PortPinSetting CS_SYNC)
{
	GPIO_SetState(CS_SYNC, false);
	SPI_WriteByte(SPI1, Data);
	GPIO_SetState(CS_SYNC, true);
	DELAY_US(1);

	GPIO_SetState(GPIO_LDAC, false);
	DELAY_US(5);
	GPIO_SetState(GPIO_LDAC, true);
	DELAY_US(1);
}
//---------------------
