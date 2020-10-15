#ifndef DISCRETEOPAMP_H_
#define DISCRETEOPAMP_H_

// Includes
#include "ZwBase.h"

// Definitions
#define DISOPAMP_POSITION_CELL0		0
#define DISOPAMP_POSITION_CELL1		1
#define DISOPAMP_POSITION_CELL2		2
#define DISOPAMP_POSITION_CELL3		3
#define DISOPAMP_POSITION_CELL4		4
#define DISOPAMP_POSITION_CELL5		5
#define DISOPAMP_POSITION_CELL6		6
#define DISOPAMP_POSITION_CELL7		7

// Functions
void DISOPAMP_SetCurrentCutOff(float Current);
void DISOPAMP_SetVoltage(float Voltage);

#endif /* DISCRETEOPAMP_H_ */
