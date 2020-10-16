// Includes
#include "Board.h"
#include "Logic.h"
#include "ConvertUtils.h"
#include "DataTable.h"

// Variables
float VoltageTarget = 0;
float CurrentCutOff = 0;

void LOGIC_CacheVariables()
{
	CU_LoadConvertParams();

	VoltageTarget = (float)DataTable[REG_VOLTAGE_SETPOINT] / 10;
	CurrentCutOff = (float)((Int32U)((DataTable[REG_CURRENT_CUTOFF_H] << 16) | DataTable[REG_CURRENT_CUTOFF_L])) / 10;
}
//-----------------------------
