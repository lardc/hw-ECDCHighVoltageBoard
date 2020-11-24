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
#define ACT_SECOND_START_PROCESS		102	// ������� ������� ������� ����� ������������ ��������

#define ACT_SAVE_TO_ROM					200	// ���������� ���������������� ������ �� FLASH ����������
#define ACT_RESTORE_FROM_ROM			201	// �������������� ������ �� FLASH
#define ACT_RESET_TO_DEFAULT			202	// ����� DataTable � ��������� �� ���������

#define ACT_BOOT_LOADER_REQUEST			320	// ���������� ���������� � ����� ��������������������
// -----------------------------

// ��������
// ����������� ��������
#define REG_PS_ACTIVITY_TIME			0	// ����� ������ ������ ������� ��� ������ ������������� (��)
#define REG_PULSE_WIDTH					1	// ������������ �������� (��)
#define REG_PULSE_FRONT_WIDTH			2	// ������������ ������ �������� � (��)
#define REG_REGULATOR_ALOWED_ERR		3	// ���������� ������ ������������� (% * 10)
#define REG_START_DELAY					4	// �������� ������ ��������� ����� ���������� ������ �������������
#define REG_FOLLOWING_ERR_CNT_NUM		5	// �������� �������� FollowingError, ��� ������� ������������ ������ DF_FOLLOWING_ERR
#define REG_SCOPE_STEP					6	// ���������� ���������� ������ � �������� �����
#define REG_AFTER_PULSE_PAUSE			7	// ����� �������� ����� ������� ���������� ��������� (��)
#define REG_REGULATOR_QI_MAX			8	// ����������� ���������� �������� Qi ����������
#define REG_MEASURE_ALLOWED_ERR			9	// ���������� ������ ��� ��������� (% * 10)
#define REG_MUTE_FOLLOWING_ERR			10	// ��������� �������� �� ������� DF_FOLOWING_ERROR
#define REG_MUTE_EXCESS_CURRENT			11	// ���������� �������� �� �������� �� ����
#define REG_POST_CHARGE_WAIT_TIME		12	// ����� �������� �������� ������� ����� ��������� ������ (��)
// 13 - 19
#define REG_DAC_V_CELL_K				20	// ����������� ������ ���������� �
#define REG_DAC_V_CELL_B				21	// �������� ������ ���������� B
//
#define REG_DAC_I_RANGE0_N				22	// �������� 0 - ��������� ������������ ������ ����������
#define REG_DAC_I_RANGE0_D				23	// �������� 0 - ����������� ������������ ������ ����������
#define REG_DAC_I_RANGE0_B				24	// �������� 0 - �������� ������ ���������� B
//
#define REG_DAC_I_RANGE1_N				25	// �������� 1 - ��������� ������������ ������ ����������
#define REG_DAC_I_RANGE1_D				26	// �������� 1 - ����������� ������������ ������ ����������
#define REG_DAC_I_RANGE1_B				27	// �������� 1 - �������� ������ ���������� B
//
#define REG_DAC_I_RANGE2_N				28	// �������� 2 - ��������� ������������ ������ ����������
#define REG_DAC_I_RANGE2_D				29	// �������� 2 - ����������� ������������ ������ ����������
#define REG_DAC_I_RANGE2_B				30	// �������� 2 - �������� ������ ���������� B
//
#define REG_DAC_I_RANGE3_N				31	// �������� 3 - ��������� ������������ ������ ����������
#define REG_DAC_I_RANGE3_D				32	// �������� 3 - ����������� ������������ ������ ����������
#define REG_DAC_I_RANGE3_B				33	// �������� 3 - �������� ������ ���������� B
// 34 - 41
#define REG_ADC_V_RANGE0_P2				41	// �������� 0 - ����������� ������ ���������� �2 �1�6
#define REG_ADC_V_RANGE0_P1				42	// �������� 0 - ����������� ������ ���������� �1 �1000
#define REG_ADC_V_RANGE0_P0				43	// �������� 0 - �������� ������ ���������� �0
#define REG_ADC_V_RANGE0_K				44	// �������� 0 - ����������� ������ ���������� K
#define REG_ADC_V_RANGE0_B				45	// �������� 0 - �������� ������ ���������� B
//
#define REG_ADC_V_RANGE1_P2				46	// �������� 1 - ����������� ������ ���������� �2 �1�6
#define REG_ADC_V_RANGE1_P1				47	// �������� 1 - ����������� ������ ���������� �1 �1000
#define REG_ADC_V_RANGE1_P0				48	// �������� 1 - �������� ������ ���������� �0
#define REG_ADC_V_RANGE1_K				49	// �������� 1 - ����������� ������ ���������� K
#define REG_ADC_V_RANGE1_B				50	// �������� 1 - �������� ������ ���������� B
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
#define REG_CURRENT_CUTOFF_L			129	// ����������� �� ���� (������� �����), ��� � 10
#define REG_CURRENT_CUTOFF_H			130	// ����������� �� ���� (������� �����), ��� � 10

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
#define REG_SUB_STATE					198	// ������� ���������������� ���������

#define REG_RESULT_VOLTAGE				200	// ����������� ���������� �� ����� ����� (� * 10)
#define REG_RESULT_CURRENT_L			201	// ���������� ��� (������� �����), ��� �������� ���������� (��� * 10)
#define REG_RESULT_CURRENT_H			202	// ���������� ��� (������� �����), ��� �������� ���������� (��� * 10)
//
#define REG_MEASURE_ERR_FLAG			205	// ����, ������������ ��� ���������� ������ ������������� ��������� ��������
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

// Problem
#define PROBLEM_NONE					0
#define PROBLEM_FOLOWING_ERROR			1

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
#define EP_REGULATOR_ERR				3

#endif //  __DEV_OBJ_DIC_H
