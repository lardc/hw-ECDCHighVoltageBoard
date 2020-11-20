#ifndef __GLOBAL_H
#define __GLOBAL_H

// Definitions
// 
#define	SCCI_TIMEOUT_TICKS						1000	// ������� ���������� SCCI (� ��)
#define EP_WRITE_COUNT							0		// ���������� �������� ��� ������
#define EP_COUNT								3		// ���������� �������� ��� ������
#define VALUES_x_SIZE							300		// ������ ��������
#define ENABLE_LOCKING							FALSE	// ������ NV ��������� �������

// ��������� DiscreteOpAmp
#define DISOPAMP_CURRENT_RANGE_QUANTITY			4
#define DISOPAMP_CURRENT_THRESHOLD_RANGE_3		20000	// uA
#define DISOPAMP_CURRENT_THRESHOLD_RANGE_2		2000	// uA
#define DISOPAMP_CURRENT_THRESHOLD_RANGE_1		250		// uA
#define DISOPAMP_CURRENT_THRESHOLD_RANGE_0		25		// uA
#define DISOPAMP_CELL_VOLATGE_MAX				510		// V
#define DISOPAMP_CELL_CURRENT_MAX				20000	// uA
#define DISOPAMP_TOTAL_CELL						5		//
#define DISOPAMP_POSITION_CELL0					0
#define DISOPAMP_POSITION_CELL1					1
#define DISOPAMP_POSITION_CELL2					2
#define DISOPAMP_POSITION_CELL3					3
#define DISOPAMP_POSITION_CELL4					4
#define DISOPAMP_POSITION_CELL5					5
#define DISOPAMP_POSITION_CELL6					6
#define DISOPAMP_POSITION_CELL7					7
#define DSIOPAMP_STACK_VOLTAGE_MAX				(DISOPAMP_CELL_VOLATGE_MAX * DISOPAMP_TOTAL_CELL)

// ��������� ���������
#define TIME_LED_BLINK							500		// ������� ����������� (� ��)

#endif //  __GLOBAL_H
