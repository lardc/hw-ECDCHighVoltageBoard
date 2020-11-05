#ifndef __DEV_OBJ_DIC_H
#define __DEV_OBJ_DIC_H

// �������
#define ACT_ENABLE_POWER				1	// ��������� �����
#define ACT_DISABLE_POWER				2	// ���������� �����
#define ACT_CLR_FAULT					3	// ������� ���� fault
#define ACT_CLR_WARNING					4	// ������� ���� warning

#define ACT_DBG_PULSE_SYNC1				50	// ��������� ������� � ����� SYNC_1
#define ACT_DBG_PULSE_SYNC2				51	// ��������� ������� � ����� SYNC_2
#define ACT_DBG_IS_STATE_SYNC_1			52	// ��������� ����� SYNC_1
#define ACT_DBG_IS_STATE_SYNC_2			53	// ��������� ����� SYNC_2
#define ACT_DBG_PULSE_EXT_LEDS			54	// ����������� ��������� ������� �����������
#define ACT_DBG_SET_CURRENT_RANGE		55	// ��������� ��������� �� ���� (0, 1, 2)
#define ACT_DBG_POWER_SUPPLY_EN			56	// �������� ���������� ���������� ������� �� 500�
#define ACT_DBG_SET_CURRENT_CUTOFF		57	// ��������� ������� �� ���� �� ���� ������� DiscreteOpAmp
#define ACT_DBG_SET_VOLTAGE_CELL		58	// ��������� ���������� �� �������� ������

#define ACT_START_PROCESS				100	// ����� ���������
#define ACT_STOP_PROCESS				101	// ���� ���������

#define ACT_START_CELL_CAL				150	// ���������� ����� DisOpAmp

#define ACT_SAVE_TO_ROM					200	// ���������� ���������������� ������ �� FLASH ����������
#define ACT_RESTORE_FROM_ROM			201	// �������������� ������ �� FLASH
#define ACT_RESET_TO_DEFAULT			202	// ����� DataTable � ��������� �� ���������

#define ACT_BOOT_LOADER_REQUEST			320	// ���������� ���������� � ����� ��������������������
// -----------------------------

// ��������
// ����������� ��������
#define REG_PS_ACTIVITY_TIME			0	// ����� ������ ������ ������� ��� ������ ������������� (��)
#define REG_PULSE_WIDTH					1	// ������������ �������� (��)
#define REG_VOLATGE_RATE				2	// �������� ���������� ���������� (�10 �/��)
#define REG_REGULATOR_ALOWED_ERR		3	// ���������� ������ ������������� (% * 10)
#define REG_I_CUTOFF_HW_LEVEL_K			4	// ����������� ������ ������ ����������� ����������� ���� (%)
#define REG_FOLLOWING_ERR_CNT_NUM		5	// �������� �������� FollowingError, ��� ������� ������������ ������ DF_FOLLOWING_ERR
#define REG_SCOPE_STEP					6	// ���������� ���������� ������ � �������� �����
// 7 - 9
#define REG_MUTE_FOLLOWING_ERR			10	// ��������� �������� �� ������� DF_FOLOWING_ERROR
#define REG_MUTE_EXCESS_CURRENT			11	// ���������� �������� �� �������� �� ����
// 12 - 22
#define REG_DAC_V_CELL_K				20	// ������ 0 - ����������� ������ ���������� �
#define REG_DAC_V_CELL_B				21	// ������ 0 - �������� ������ ���������� B
// 25 - 34
#define REG_DAC_I_RANGE0_P2				22	// �������� 0 - ����������� ������ ���������� �2 �1�6
#define REG_DAC_I_RANGE0_P1				23	// �������� 0 - ����������� ������ ���������� �1 x1000
#define REG_DAC_I_RANGE0_P0				24	// �������� 0 - �������� ������ ���������� �0
#define REG_DAC_I_RANGE0_N				25	// �������� 0 - ��������� ������������ ������ ����������
#define REG_DAC_I_RANGE0_D				26	// �������� 0 - ����������� ������������ ������ ����������
#define REG_DAC_I_RANGE0_B				27	// �������� 0 - �������� ������ ���������� B
//
#define REG_DAC_I_RANGE1_P2				28	// �������� 1 - ����������� ������ ���������� �2 �1�6
#define REG_DAC_I_RANGE1_P1				29	// �������� 1 - ����������� ������ ���������� �1 x1000
#define REG_DAC_I_RANGE1_P0				30	// �������� 1 - �������� ������ ���������� �0
#define REG_DAC_I_RANGE1_N				31	// �������� 1 - ��������� ������������ ������ ����������
#define REG_DAC_I_RANGE1_D				32	// �������� 1 - ����������� ������������ ������ ����������
#define REG_DAC_I_RANGE1_B				33	// �������� 1 - �������� ������ ���������� B
//
#define REG_DAC_I_RANGE2_P2				34	// �������� 2 - ����������� ������ ���������� �2 �1�6
#define REG_DAC_I_RANGE2_P1				35	// �������� 2 - ����������� ������ ���������� �1 x1000
#define REG_DAC_I_RANGE2_P0				36	// �������� 2 - �������� ������ ���������� �0
#define REG_DAC_I_RANGE2_N				37	// �������� 2 - ��������� ������������ ������ ����������
#define REG_DAC_I_RANGE2_D				38	// �������� 2 - ����������� ������������ ������ ����������
#define REG_DAC_I_RANGE2_B				39	// �������� 2 - �������� ������ ���������� B
//
#define REG_DAC_I_RANGE3_P2				40	// �������� 3 - ����������� ������ ���������� �2 �1�6
#define REG_DAC_I_RANGE3_P1				41	// �������� 3 - ����������� ������ ���������� �1 x1000
#define REG_DAC_I_RANGE3_P0				42	// �������� 3 - �������� ������ ���������� �0
#define REG_DAC_I_RANGE3_N				43	// �������� 3 - ��������� ������������ ������ ����������
#define REG_DAC_I_RANGE3_D				44	// �������� 3 - ����������� ������������ ������ ����������
#define REG_DAC_I_RANGE3_B				45	// �������� 3 - �������� ������ ���������� B
//
#define REG_ADC_VOLTAGE_P2				46	// ����������� ������ ���������� �2 �1�6
#define REG_ADC_VOLTAGE_P1				47	// ����������� ������ ���������� �1 �1000
#define REG_ADC_VOLTAGE_P0				48	// �������� ������ ���������� �0
#define REG_ADC_VOLTAGE_K				49	// ����������� ������ ���������� K
#define REG_ADC_VOLTAGE_B				50	// �������� ������ ���������� B
//
#define REG_ADC_I_RANGE0_P2				51	// �������� 0 - ����������� ������ ���������� �2 �1�6
#define REG_ADC_I_RANGE0_P1				52	// �������� 0 - ����������� ������ ���������� �1 x1000
#define REG_ADC_I_RANGE0_P0				53	// �������� 0 - �������� ������ ���������� �0
#define REG_ADC_I_RANGE0_N				54	// �������� 0 - ��������� ������������ ������ ����������
#define REG_ADC_I_RANGE0_D				55	// �������� 0 - ����������� ������������ ������ ����������
#define REG_ADC_I_RANGE0_B				56	// �������� 0 - �������� ������ ���������� B
//
#define REG_ADC_I_RANGE1_P2				57	// �������� 1 - ����������� ������ ���������� �2 �1�6
#define REG_ADC_I_RANGE1_P1				58	// �������� 1 - ����������� ������ ���������� �1 x1000
#define REG_ADC_I_RANGE1_P0				59	// �������� 1 - �������� ������ ���������� �0
#define REG_ADC_I_RANGE1_N				60	// �������� 1 - ��������� ������������ ������ ����������
#define REG_ADC_I_RANGE1_D				61	// �������� 1 - ����������� ������������ ������ ����������
#define REG_ADC_I_RANGE1_B				62	// �������� 1 - �������� ������ ���������� B
//
#define REG_ADC_I_RANGE2_P2				63	// �������� 2 - ����������� ������ ���������� �2 �1�6
#define REG_ADC_I_RANGE2_P1				64	// �������� 2 - ����������� ������ ���������� �1 x1000
#define REG_ADC_I_RANGE2_P0				65	// �������� 2 - �������� ������ ���������� �0
#define REG_ADC_I_RANGE2_N				66	// �������� 2 - ��������� ������������ ������ ����������
#define REG_ADC_I_RANGE2_D				67	// �������� 2 - ����������� ������������ ������ ����������
#define REG_ADC_I_RANGE2_B				68	// �������� 2 - �������� ������ ���������� B
//
#define REG_ADC_I_RANGE3_P2				69	// �������� 3 - ����������� ������ ���������� �2 �1�6
#define REG_ADC_I_RANGE3_P1				70	// �������� 3 - ����������� ������ ���������� �1 x1000
#define REG_ADC_I_RANGE3_P0				71	// �������� 3 - �������� ������ ���������� �0
#define REG_ADC_I_RANGE3_N				72	// �������� 3 - ��������� ������������ ������ ����������
#define REG_ADC_I_RANGE3_D				73	// �������� 3 - ����������� ������������ ������ ����������
#define REG_ADC_I_RANGE3_B				74	// �������� 3 - �������� ������ ���������� B
//
#define REG_REGULATOR_Kp				80	// ���������������� ����������� ����������
#define REG_REGULATOR_Ki				81	// ������������ ����������� ����������

#define REG_VOLTAGE_SETPOINT			128	// ������� �� ����������, � � 10
#define REG_CURRENT_CUTOFF_H			129	// ����������� �� ���� (������� �����), ��� � 10
#define REG_CURRENT_CUTOFF_L			130	// ����������� �� ���� (������� �����), ��� � 10

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
#define REG_RESULT_VOLTAGE				198	// ����������� ���������� �� ����� ����� (� * 10)
#define REG_RESULT_CURRENT_H			199	// ���������� ��� (������� �����), ��� �������� ���������� (��� * 10)
#define REG_RESULT_CURRENT_L			200	// ���������� ��� (������� �����), ��� �������� ���������� (��� * 10)
// -----------------------------
#define REG_FWINFO_SLAVE_NID			256	// Device CAN slave node ID
#define REG_FWINFO_MASTER_NID			257	// Device CAN master node ID (if presented)
// 258 - 259
#define REG_FWINFO_STR_LEN				260	// Length of the information string record
#define REG_FWINFO_STR_BEGIN			261	// Begining of the information string record


// Operation results
#define OPRESULT_NONE					0	// No information or not finished
#define OPRESULT_OK						1	// Operation was successful
#define OPRESULT_FAIL					2	// Operation failed

//  Fault and disable codes
#define DF_NONE							0
#define DF_POWER_SUPPLY					1
#define DF_FOLOWING_ERROR				2

// Problem
#define PROBLEM_NONE					0
#define PROBLEM_SHORT_CICUIT			1
#define PROBLEM_CURRENT_CUTOFF			2

//  Warning
#define WARNING_NONE					0
#define WARNING_CURRENT_CUTOFF			1

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
