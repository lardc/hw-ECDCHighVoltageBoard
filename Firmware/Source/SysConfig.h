#ifndef __SYSCONFIG_H
#define __SYSCONFIG_H


// Flash loader options
#define BOOT_LOADER_VARIABLE			(*((volatile uint32_t *)0x20000000))
#define BOOT_LOADER_REQUEST				0x12345678
#define BOOT_LOADER_MAIN_PR_ADDR		0x08008000
//-----------------------------------------------

// System clock
#define SYSCLK							70000000	// �������� ������� ��������� ���� ����������
#define QUARTZ_FREQUENCY				20000000	// ������� ������
// ----------------------------------------------

// USART
#define USART_BAUDRATE					115200		// �������� USART
#define USART_FIFOlen					32			// ����� FIFO USART
// ----------------------------------------------

// Timers
#define TIMER7_uS						1000		// � ���
#define TIMER6_uS						75			// � ���
// ----------------------------------------------

// CAN
#define CAN_BAUDRATE					1000000		// ������� CAN
// ----------------------------------------------

// SPI
#define SPI1_BAUDRATE_BITS				0x1			// ���� ������� �������� SPI
#define SPI1_LSB_FIRST					true		// �������� ������� ����� ������
// ----------------------------------------------

// ADC
#define DMA_ADC_DUT_U_CHANNEL			DMA1_Channel1	// ����� DMA ��� ��� ����
#define DMA_ADC_DUT_I_CHANNEL			DMA2_Channel1	// ����� DMA ��� ��� ����
#define ADC1_VOLTAGE_CHANNEL			1				// ���1 ����� ������ ����������
#define ADC2_CURRENT_CHANNEL			3				// ���1 ����� ������ ����
#define ADC_DMA_BUFF_SIZE				5				// ���������� ������ ��� DMA
// ----------------------------------------------

#endif // __SYSCONFIG_H
