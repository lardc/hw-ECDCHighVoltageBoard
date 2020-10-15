#ifndef __GLOBAL_H
#define __GLOBAL_H

// Definitions
// 
#define	SCCI_TIMEOUT_TICKS						1000	// ������� ���������� SCCI (� ��)
#define EP_WRITE_COUNT							0		// ���������� �������� ��� ������
#define EP_COUNT								2		// ���������� �������� ��� ������
#define VALUES_x_SIZE							300		// ������ ��������
#define ENABLE_LOCKING							FALSE	// ������ NV ��������� �������

// ��������� DiscreteOpAmp
#define DISOPAMP_CURRENT_RANGE_NUM				4
#define DISOPAMP_CURRENT_THRESHOLD_RANGE_3		20000	// uA x 10
#define DISOPAMP_CURRENT_THRESHOLD_RANGE_2		2500	// uA x 10
#define DISOPAMP_CURRENT_THRESHOLD_RANGE_1		250		// uA x 10
#define DISOPAMP_CELL_VOLATGE_MAX				500		// V
#define DISOPAMP_TOTAL_CELL						8		//
#define DISOPAMP_POSITION_CELL0					0
#define DISOPAMP_POSITION_CELL1					1
#define DISOPAMP_POSITION_CELL2					2
#define DISOPAMP_POSITION_CELL3					3
#define DISOPAMP_POSITION_CELL4					4
#define DISOPAMP_POSITION_CELL5					5
#define DISOPAMP_POSITION_CELL6					6
#define DISOPAMP_POSITION_CELL7					7

// ��������� ���������
#define TIME_LED_BLINK							500		// ������� ����������� (� ��)

#endif //  __GLOBAL_H
