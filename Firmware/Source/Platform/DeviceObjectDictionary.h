#ifndef __DEV_OBJ_DIC_H
#define __DEV_OBJ_DIC_H

// Команды
#define ACT_ENABLE_POWER				1	// Переход в состояние ожидания
#define ACT_DISABLE_POWER				2	// Отключение блока
#define ACT_CLR_FAULT					3	// Очистка всех fault
#define ACT_CLR_WARNING					4	// Очистка всех warning

#define ACT_DBG_PULSE_SYNC1				50	// Одиночный импусль в линию SYNC_1
#define ACT_DBG_PULSE_SYNC2				51	// Одиночный импусль в линию SYNC_2
#define ACT_DBG_IS_STATE_SYNC_1			52	// Состояние линии SYNC_1
#define ACT_DBG_IS_STATE_SYNC_2			53	// Состояние линии SYNC_2
#define ACT_DBG_PULSE_EXT_LEDS			54	// Однократное зажигание внешних светодиодов
#define ACT_DBG_SET_CURRENT_RANGE		55	// Установка диапазона по току (0, 1, 2)
#define ACT_DBG_ARE_PS_STATE			56	// Проверка активности источников питания на 500В
#define ACT_DBG_SET_CURRENT_CUTOFF		57	// Установка отсечки по току на всех ячейках DiscreteOpAmp
#define ACT_DBG_SET_VOLTAGE_CELL		58	// Установка напряжения на заданной ячейке

#define ACT_SAVE_TO_ROM					200	// Сохранение пользовательских данных во FLASH процессора
#define ACT_RESTORE_FROM_ROM			201	// Восстановление данных из FLASH
#define ACT_RESET_TO_DEFAULT			202	// Сброс DataTable в состояние по умолчанию

#define ACT_BOOT_LOADER_REQUEST			320	// Перезапуск процессора с целью перепрограммирования
// -----------------------------

// Регистры
// Сохраняемые регистры
#define REG_POWER_ON_TIMEOUT			0	// Таймаут ожидания готовности блоков питания

// Несохраняемы регистры чтения-записи
#define REG_DBG							150	// Регистр режима Отладки 1
#define REG_DBG_CELL_NUM				151	// Регистр режима Отладки 2

// Регистры только чтение
#define REG_DEV_STATE					192	// Регистр состояния
#define REG_FAULT_REASON				193	// Регистр Fault
#define REG_DISABLE_REASON				194	// Регистр Disable
#define REG_WARNING						195	// Регистр Warning
#define REG_PROBLEM						196	// Регистр Problem
#define REG_OP_RESULT					197	// Регистр результата операции
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
#define ERR_CONFIGURATION_LOCKED		1	//  Устройство защищено от записи
#define ERR_OPERATION_BLOCKED			2	//  Операция не может быть выполнена в текущем состоянии устройства
#define ERR_DEVICE_NOT_READY			3	//  Устройство не готово для смены состояния
#define ERR_WRONG_PWD					4	//  Неправильный ключ

// Endpoints
#define EP_VOLTAGE						1
#define EP_CURRENT						2

#endif //  __DEV_OBJ_DIC_H
