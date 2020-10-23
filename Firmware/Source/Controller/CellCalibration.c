// Header
#include "CellCalibration.h"

// Includes
#include "DiscreteOpAmp.h"
#include "Delay.h"
#include "LowLevel.h"
#include "ConvertUtils.h"


// Functions
void CELLCAL_SetVoltageCell(Int16U Voltage, Int16U CellNumber)
{
	LL_WriteDACx(CU_VtoDAC(Voltage, CellNumber) | DAC_CHANNEL_B, CellNumber, 1, true);
}

