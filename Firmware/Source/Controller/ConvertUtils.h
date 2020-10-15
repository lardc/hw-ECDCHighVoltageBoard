#ifndef CONVERTUTILS_H_
#define CONVERTUTILS_H_

// Includes
#include "ZwBase.h"

// Functions
Int16U CU_VtoDAC(float Voltage, Int16U CellNumber);
Int16U CU_ItoDAC(float Current, Int16U CurrentRange);

#endif /* CONVERTUTILS_H_ */
