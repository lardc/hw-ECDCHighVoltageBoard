// Header
#include "Diagnostic.h"

// Includes
#include "DataTable.h"
#include "LowLevel.h"
#include "Controller.h"
#include "DebugActions.h"

// Functions
bool DIAG_HandleDiagnosticAction(uint16_t ActionID, uint16_t *pUserError)
{
	switch (ActionID)
	{
		case ACT_DBG_PULSE_SYNC1:
			{
				DBGACT_GenerateImpulseToLineSync1();
			}
			break;

		case ACT_DBG_PULSE_SYNC2:
			{
				DBGACT_GenerateImpulseToLineSync2();
			}
			break;

		case ACT_DBG_IS_STATE_SYNC_1:
			{
				DataTable[REG_DBG] = DBGACT_ReadStateLineSync1();
			}
			break;

		case ACT_DBG_IS_STATE_SYNC_2:
			{
				DataTable[REG_DBG] = DBGACT_ReadStateLineSync2();
			}
			break;

		case ACT_DBG_PULSE_EXT_LEDS:
			{
				DBGACT_BlinkExtLeds();
			}
			break;

		default:
			return false;
	}

	return true;
}
