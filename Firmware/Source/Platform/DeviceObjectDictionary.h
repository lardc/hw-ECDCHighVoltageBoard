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
// 12 - 19
#define REG_DAC_V_CELL0_P2				20	// ������ 0 - ����������� ������ ���������� �2 x1e6
#define REG_DAC_V_CELL0_P1				21	// ������ 0 - ����������� ������ ���������� �1 x1000
#define REG_DAC_V_CELL0_P0				22	// ������ 0 - �������� ������ ���������� �0
#define REG_DAC_V_CELL0_K				23	// ������ 0 - ����������� ������ ���������� �
#define REG_DAC_V_CELL0_B				24	// ������ 0 - �������� ������ ���������� B
//
#define REG_DAC_V_CELL1_K				25	// ������ 1 - ����������� ������ ���������� �
#define REG_DAC_V_CELL2_K				26	// ������ 2 - ����������� ������ ���������� �
#define REG_DAC_V_CELL3_K				27	// ������ 3 - ����������� ������ ���������� �
#define REG_DAC_V_CELL4_K				28	// ������ 4 - ����������� ������ ���������� �
#define REG_DAC_V_CELL5_K				29	// ������ 5 - ����������� ������ ���������� �
#define REG_DAC_V_CELL6_K				30	// ������ 6 - ����������� ������ ���������� �
#define REG_DAC_V_CELL7_K				31	// ������ 7 - ����������� ������ ���������� �
// 32 - 34
#define REG_DAC_I_RANGE0_P2				35	// �������� 0 - ����������� ������ ���������� �2 �1�6
#define REG_DAC_I_RANGE0_P1				36	// �������� 0 - ����������� ������ ���������� �1 x1000
#define REG_DAC_I_RANGE0_P0				37	// �������� 0 - �������� ������ ���������� �0
#define REG_DAC_I_RANGE0_K				38	// �������� 0 - ����������� ������ ���������� K
#define REG_DAC_I_RANGE0_B				39	// �������� 0 - �������� ������ ���������� B
//
#define REG_DAC_I_RANGE1_P2				40	// �������� 1 - ����������� ������ ���������� �2 �1�6
#define REG_DAC_I_RANGE1_P1				41	// �������� 1 - ����������� ������ ���������� �1 x1000
#define REG_DAC_I_RANGE1_P0				42	// �������� 1 - �������� ������ ���������� �0
#define REG_DAC_I_RANGE1_K				43	// �������� 1 - ����������� ������ ���������� K
#define REG_DAC_I_RANGE1_B				44	// �������� 1 - �������� ������ ���������� B
//
#define REG_DAC_I_RANGE2_P2				45	// �������� 2 - ����������� ������ ���������� �2 �1�6
#define REG_DAC_I_RANGE2_P1				46	// �������� 2 - ����������� ������ ���������� �1 x1000
#define REG_DAC_I_RANGE2_P0				47	// �������� 2 - �������� ������ ���������� �0
#define REG_DAC_I_RANGE2_K				48	// �������� 2 - ����������� ������ ���������� K
#define REG_DAC_I_RANGE2_B				49	// �������� 2 - �������� ������ ���������� B
//
#define REG_DAC_I_RANGE3_P2				50	// �������� 3 - ����������� ������ ���������� �2 �1�6
#define REG_DAC_I_RANGE3_P1				51	// �������� 3 - ����������� ������ ���������� �1 x1000
#define REG_DAC_I_RANGE3_P0				52	// �������� 3 - �������� ������ ���������� �0
#define REG_DAC_I_RANGE3_K				53	// �������� 3 - ����������� ������ ���������� K
#define REG_DAC_I_RANGE3_B				54	// �������� 3 - �������� ������ ���������� B
//
#define REG_ADC_VOLTAGE_P2				55	// ����������� ������ ���������� �2 �1�6
#define REG_ADC_VOLTAGE_P1				56	// ����������� ������ ���������� �1 �1000
#define REG_ADC_VOLTAGE_P0				57	// �������� ������ ���������� �0
#define REG_ADC_VOLTAGE_K				58	// ����������� ������ ���������� K
#define REG_ADC_VOLTAGE_B				59	// �������� ������ ���������� B
//
#define REG_ADC_I_RANGE0_P2				60	// �������� 0 - ����������� ������ ���������� �2 �1�6
#define REG_ADC_I_RANGE0_P1				61	// �������� 0 - ����������� ������ ���������� �1 x1000
#define REG_ADC_I_RANGE0_P0				62	// �������� 0 - �������� ������ ���������� �0
#define REG_ADC_I_RANGE0_K				63	// �������� 0 - ����������� ������ ���������� K
#define REG_ADC_I_RANGE0_B				64	// �������� 0 - �������� ������ ���������� B
//
#define REG_ADC_I_RANGE1_P2				65	// �������� 1 - ����������� ������ ���������� �2 �1�6
#define REG_ADC_I_RANGE1_P1				66	// �������� 1 - ����������� ������ ���������� �1 x1000
#define REG_ADC_I_RANGE1_P0				67	// �������� 1 - �������� ������ ���������� �0
#define REG_ADC_I_RANGE1_K				68	// �������� 1 - ����������� ������ ���������� K
#define REG_ADC_I_RANGE1_B				69	// �������� 1 - �������� ������ ���������� B
//
#define REG_ADC_I_RANGE2_P2				70	// �������� 2 - ����������� ������ ���������� �2 �1�6
#define REG_ADC_I_RANGE2_P1				71	// �������� 2 - ����������� ������ ���������� �1 x1000
#define REG_ADC_I_RANGE2_P0				72	// �������� 2 - �������� ������ ���������� �0
#define REG_ADC_I_RANGE2_K				73	// �������� 2 - ����������� ������ ���������� K
#define REG_ADC_I_RANGE2_B				74	// �������� 2 - �������� ������ ���������� B
//
#define REG_ADC_I_RANGE3_P2				75	// �������� 3 - ����������� ������ ���������� �2 �1�6
#define REG_ADC_I_RANGE3_P1				76	// �������� 3 - ����������� ������ ���������� �1 x1000
#define REG_ADC_I_RANGE3_P0				77	// �������� 3 - �������� ������ ���������� �0
#define REG_ADC_I_RANGE3_K				78	// �������� 3 - ����������� ������ ���������� K
#define REG_ADC_I_RANGE3_B				79	// �������� 3 - �������� ������ ���������� B
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
