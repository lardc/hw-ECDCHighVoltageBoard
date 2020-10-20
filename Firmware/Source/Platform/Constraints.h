#ifndef __CONSTRAINTS_H
#define __CONSTRAINTS_H

// Include
#include "stdinc.h"
#include "DataTable.h"
#include "Global.h"

//Definitions
#define NO		0
#define YES		1

#define POWER_ON_TIMEOUT_MIN		0			// ��
#define POWER_ON_TIMEOUT_MAX		10000		// ��
#define POWER_ON_TIMEOUT_DEF		5000		// ��
//
#define COEF_P2_MIN					0
#define COEF_P2_MAX					INT16U_MAX
#define COEF_P2_DEF					0
//
#define COEF_K_MIN					1
#define COEF_K_MAX					1000
#define COEF_K_DEF					1
//
#define OFFSET_MIN					0
#define OFFSET_MAX					INT16U_MAX
#define OFFSET_DEF					0
//
#define REGULATOR_KP_MIN			0
#define REGULATOR_KP_MAX			INT16U_MAX
#define REGULATOR_KP_DEF			1000
//
#define REGULATOR_KI_MIN			0
#define REGULATOR_KI_MAX			INT16U_MAX
#define REGULATOR_KI_DEF			0
//
#define PULSE_WIDTH_MIN				1000		// (���)
#define PULSE_WIDTH_MAX				20000		// (���)
#define PULSE_WIDTH_DEF				10000		// (���)
//
#define BETWEN_PULSES_DELAY_MIN		10			// (��)
#define BETWEN_PULSES_DELAY_MAX		100			// (��)
#define BETWEN_PULSES_DELAY_DEF		10			// (��)
//
#define VOLTAGE_RATE_MIN			4			// (�10 �/��)
#define VOLTAGE_RATE_MAX			8000		// (�10 �/��)
#define VOLTAGE_RATE_DEF			40			// (�10 �/��)
//
#define TEST_TIME_MIN				1			// (��)
#define TEST_TIME_MAX				100			// (��)
#define TEST_TIME_DEF				10			// (��)
//
#define ALOWED_ERROR_MIN			0			// (% * 10)
#define ALOWED_ERROR_MAX			1000		// (% * 10)
#define ALOWED_ERROR_DEF			30			// (% * 10)
//
#define VOLTAGE_SETPOINT_MAX		40000		// (� * 10)

// Types
typedef struct __TableItemConstraint
{
	Int16U Min;
	Int16U Max;
	Int16U Default;
} TableItemConstraint;

// Variables
extern const TableItemConstraint NVConstraint[DATA_TABLE_NV_SIZE];
extern const TableItemConstraint VConstraint[DATA_TABLE_WP_START - DATA_TABLE_WR_START];

#endif // __CONSTRAINTS_H
