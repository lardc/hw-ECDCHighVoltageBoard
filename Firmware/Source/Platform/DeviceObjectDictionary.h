#ifndef __DEV_OBJ_DIC_H
#define __DEV_OBJ_DIC_H

// �������
#define ACT_ENABLE_POWER				1	// ������� � ��������� ��������
#define ACT_DISABLE_POWER				2	// ���������� �����
#define ACT_CLR_FAULT					3	// ������� ���� fault
#define ACT_CLR_WARNING					4	// ������� ���� warning

#define ACT_DBG_PULSE_SYNC1				50	// ��������� ������� � ����� SYNC_1
#define ACT_DBG_PULSE_SYNC2				51	// ��������� ������� � ����� SYNC_2
#define ACT_DBG_IS_STATE_SYNC_1			52	// ��������� ����� SYNC_1
#define ACT_DBG_IS_STATE_SYNC_2			53	// ��������� ����� SYNC_2
#define ACT_DBG_PULSE_EXT_LEDS			54	// ����������� ��������� ������� �����������
#define ACT_DBG_SET_CURRENT_RANGE		55	// ��������� ��������� �� ���� (0, 1, 2)
#define ACT_DBG_ARE_PS_STATE			56	// �������� ���������� ���������� ������� �� 500�
#define ACT_DBG_SET_CURRENT_CUTOFF		57	// ��������� ������� �� ���� �� ���� ������� DiscreteOpAmp
#define ACT_DBG_SET_VOLTAGE_CELL		58	// ��������� ���������� �� �������� ������

#define ACT_SAVE_TO_ROM					200	// ���������� ���������������� ������ �� FLASH ����������
#define ACT_RESTORE_FROM_ROM			201	// �������������� ������ �� FLASH
#define ACT_RESET_TO_DEFAULT			202	// ����� DataTable � ��������� �� ���������

#define ACT_BOOT_LOADER_REQUEST			320	// ���������� ���������� � ����� ��������������������
// -----------------------------

// ��������
// ����������� ��������
#define REG_POWER_ON_TIMEOUT			0	// ������� �������� ���������� ������ �������

// ������������ �������� ������-������
#define REG_DBG							150	// ������� ������ ������� 1
#define REG_DBG_CELL_NUM				151	// ������� ������ ������� 2

// �������� ������ ������
#define REG_DEV_STATE					192	// ������� ���������
#define REG_FAULT_REASON				193	// ������� Fault
#define REG_DISABLE_REASON				194	// ������� Disable
#define REG_WARNING						195	// ������� Warning
#define REG_PROBLEM						196	// ������� Problem
#define REG_OP_RESULT					197	// ������� ���������� ��������
// -----------------------------

// Operation results
#define OPRESULT_NONE					0	// No information or not finished
#define OPRESULT_OK						1	// Operation was successful
#define OPRESULT_FAIL					2	// Operation failed

//  Fault and disable codes
#define DF_NONE							0
#define DF_POWER_SUPPLY					1

// Problem
#define PROBLEM_NONE					0

//  Warning
#define WARNING_NONE					0

//  User Errors
#define ERR_NONE						0
#define ERR_CONFIGURATION_LOCKED		1	//  ���������� �������� �� ������
#define ERR_OPERATION_BLOCKED			2	//  �������� �� ����� ���� ��������� � ������� ��������� ����������
#define ERR_DEVICE_NOT_READY			3	//  ���������� �� ������ ��� ����� ���������
#define ERR_WRONG_PWD					4	//  ������������ ����

// Endpoints
#define EP_VOLTAGE						1
#define EP_CURRENT						2

#endif //  __DEV_OBJ_DIC_H
