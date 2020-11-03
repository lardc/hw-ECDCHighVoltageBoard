// -----------------------------------------
// Global definitions
// ----------------------------------------

// Header
#include "Constraints.h"

// Constants
//
const TableItemConstraint NVConstraint[DATA_TABLE_NV_SIZE] = {
		{PS_ACTIVITY_TIME_MIN, PS_ACTIVITY_TIME_MAX, PS_ACTIVITY_TIME_DEF},			// 0
		{PULSE_WIDTH_MIN, PULSE_WIDTH_MAX, PULSE_WIDTH_DEF},						// 1
		{VOLTAGE_RATE_MIN, VOLTAGE_RATE_MAX, VOLTAGE_RATE_DEF},						// 2
		{ALOWED_ERROR_MIN, ALOWED_ERROR_MAX, ALOWED_ERROR_DEF},						// 3
		{HW_I_CUTOFF_K_MIN, HW_I_CUTOFF_K_MAX, HW_I_CUTOFF_K_DEF},					// 4
		{0, INT16U_MAX, 0},															// 5
		{0, INT16U_MAX, 0},															// 6
		{0, 0, 0},																	// 7
		{0, 0, 0},																	// 8
		{0, 0, 0},																	// 9
		{NO, YES, NO},																// 10
		{NO, YES, NO},																// 11
		{0, 0, 0},																	// 12
		{0, 0, 0},																	// 13
		{0, 0, 0},																	// 14
		{0, 0, 0},																	// 15
		{0, 0, 0},																	// 16
		{0, 0, 0},																	// 17
		{0, 0, 0},																	// 18
		{0, 0, 0},																	// 19
		{0, 0, 0},																	// 20
		{0, 0, 0},																	// 21
		{0, 0, 0},																	// 22
		{COEF_K_MIN, COEF_K_MAX, COEF_K_DEF},										// 23
		{OFFSET_MIN, OFFSET_MAX, OFFSET_DEF},										// 24
		{0, 0, 0},																	// 25
		{0, 0, 0},																	// 26
		{0, 0, 0},																	// 27
		{0, 0, 0},																	// 28
		{0, 0, 0},																	// 29
		{0, 0, 0},																	// 30
		{0, 0, 0},																	// 31
		{0, 0, 0},																	// 32
		{0, 0, 0},																	// 33
		{0, 0, 0},																	// 34
		{COEF_P2_MIN, COEF_P2_MAX, COEF_P2_DEF},									// 35
		{COEF_K_MIN, COEF_K_MAX, COEF_K_DEF},										// 36
		{OFFSET_MIN, OFFSET_MAX, OFFSET_DEF},										// 37
		{COEF_K_MIN, COEF_K_MAX, COEF_K_DEF},										// 38
		{OFFSET_MIN, OFFSET_MAX, OFFSET_DEF},										// 39
		{COEF_P2_MIN, COEF_P2_MAX, COEF_P2_DEF},									// 40
		{COEF_K_MIN, COEF_K_MAX, COEF_K_DEF},										// 41
		{OFFSET_MIN, OFFSET_MAX, OFFSET_DEF},										// 42
		{COEF_K_MIN, COEF_K_MAX, COEF_K_DEF},										// 43
		{OFFSET_MIN, OFFSET_MAX, OFFSET_DEF},										// 44
		{COEF_P2_MIN, COEF_P2_MAX, COEF_P2_DEF},									// 45
		{COEF_K_MIN, COEF_K_MAX, COEF_K_DEF},										// 46
		{OFFSET_MIN, OFFSET_MAX, OFFSET_DEF},										// 47
		{COEF_K_MIN, COEF_K_MAX, COEF_K_DEF},										// 48
		{OFFSET_MIN, OFFSET_MAX, OFFSET_DEF},										// 49
		{COEF_P2_MIN, COEF_P2_MAX, COEF_P2_DEF},									// 50
		{COEF_K_MIN, COEF_K_MAX, COEF_K_DEF},										// 51
		{OFFSET_MIN, OFFSET_MAX, OFFSET_DEF},										// 52
		{COEF_K_MIN, COEF_K_MAX, COEF_K_DEF},										// 53
		{OFFSET_MIN, OFFSET_MAX, OFFSET_DEF},										// 54
		{COEF_P2_MIN, COEF_P2_MAX, COEF_P2_DEF},									// 55
		{COEF_K_MIN, COEF_K_MAX, COEF_K_DEF},										// 56
		{OFFSET_MIN, OFFSET_MAX, OFFSET_DEF},										// 57
		{COEF_K_MIN, COEF_K_MAX, COEF_K_DEF},										// 58
		{OFFSET_MIN, OFFSET_MAX, OFFSET_DEF},										// 59
		{COEF_P2_MIN, COEF_P2_MAX, COEF_P2_DEF},									// 60
		{COEF_K_MIN, COEF_K_MAX, COEF_K_DEF},										// 61
		{OFFSET_MIN, OFFSET_MAX, OFFSET_DEF},										// 62
		{COEF_K_MIN, COEF_K_MAX, COEF_K_DEF},										// 63
		{OFFSET_MIN, OFFSET_MAX, OFFSET_DEF},										// 64
		{COEF_P2_MIN, COEF_P2_MAX, COEF_P2_DEF},									// 65
		{COEF_K_MIN, COEF_K_MAX, COEF_K_DEF},										// 66
		{OFFSET_MIN, OFFSET_MAX, OFFSET_DEF},										// 67
		{COEF_K_MIN, COEF_K_MAX, COEF_K_DEF},										// 68
		{OFFSET_MIN, OFFSET_MAX, OFFSET_DEF},										// 69
		{COEF_P2_MIN, COEF_P2_MAX, COEF_P2_DEF},									// 70
		{COEF_K_MIN, COEF_K_MAX, COEF_K_DEF},										// 71
		{OFFSET_MIN, OFFSET_MAX, OFFSET_DEF},										// 72
		{COEF_K_MIN, COEF_K_MAX, COEF_K_DEF},										// 73
		{OFFSET_MIN, OFFSET_MAX, OFFSET_DEF},										// 74
		{COEF_P2_MIN, COEF_P2_MAX, COEF_P2_DEF},									// 75
		{COEF_K_MIN, COEF_K_MAX, COEF_K_DEF},										// 76
		{OFFSET_MIN, OFFSET_MAX, OFFSET_DEF},										// 77
		{COEF_K_MIN, COEF_K_MAX, COEF_K_DEF},										// 78
		{OFFSET_MIN, OFFSET_MAX, OFFSET_DEF},										// 79
		{REGULATOR_KP_MIN, REGULATOR_KP_MAX, REGULATOR_KP_DEF},						// 80
		{REGULATOR_KI_MIN, REGULATOR_KI_MAX, REGULATOR_KI_DEF},						// 81
		{0, 0, 0},																	// 82
		{0, 0, 0},																	// 83
		{0, 0, 0},																	// 84
		{0, 0, 0},																	// 85
		{0, 0, 0},																	// 86
		{0, 0, 0},																	// 87
		{0, 0, 0},																	// 88
		{0, 0, 0},																	// 89
		{0, 0, 0},																	// 90
		{0, 0, 0},																	// 91
		{0, 0, 0},																	// 92
		{0, 0, 0},																	// 93
		{0, 0, 0},																	// 94
		{0, 0, 0},																	// 95
		{0, 0, 0},																	// 96
		{0, 0, 0},																	// 97
		{0, 0, 0},																	// 98
		{0, 0, 0},																	// 99
		{0, 0, 0},																	// 100
		{0, 0, 0},																	// 101
		{0, 0, 0},																	// 102
		{0, 0, 0},																	// 103
		{0, 0, 0},																	// 104
		{0, 0, 0},																	// 105
		{0, 0, 0},																	// 106
		{0, 0, 0},																	// 107
		{0, 0, 0},																	// 108
		{0, 0, 0},																	// 109
		{0, 0, 0},																	// 110
		{0, 0, 0},																	// 111
		{0, 0, 0},																	// 112
		{0, 0, 0},																	// 113
		{0, 0, 0},																	// 114
		{0, 0, 0},																	// 115
		{0, 0, 0},																	// 116
		{0, 0, 0},																	// 117
		{0, 0, 0},																	// 118
		{0, 0, 0},																	// 119
		{0, 0, 0},																	// 120
		{0, 0, 0},																	// 121
		{0, 0, 0},																	// 122
		{0, 0, 0},																	// 123
		{0, 0, 0},																	// 124
		{0, 0, 0},																	// 125
		{0, 0, 0},																	// 126
		{0, 0, 0}																	// 127
};

const TableItemConstraint VConstraint[DATA_TABLE_WP_START - DATA_TABLE_WR_START] = {
		{0, VOLTAGE_SETPOINT_MAX, 0},												// 128
		{0, INT16U_MAX, 0},															// 129
		{0, INT16U_MAX, 0},															// 130
		{0, 0, 0},																	// 131
		{0, 0, 0},																	// 132
		{0, 0, 0},																	// 133
		{0, 0, 0},																	// 134
		{0, 0, 0},																	// 135
		{0, 0, 0},																	// 136
		{0, 0, 0},																	// 137
		{0, 0, 0},																	// 138
		{0, 0, 0},																	// 139
		{0, 0, 0},																	// 140
		{0, 0, 0},																	// 141
		{0, 0, 0},																	// 142
		{0, 0, 0},																	// 143
		{0, 0, 0},																	// 144
		{0, 0, 0},																	// 145
		{0, 0, 0},																	// 146
		{0, 0, 0},																	// 147
		{0, 0, 0},																	// 148
		{0, 0, 0},																	// 149
		{0, INT16U_MAX, 0},															// 150
		{0, INT16U_MAX, 0},															// 151
		{0, INT16U_MAX, 0},															// 152
		{ALOWED_ERROR_MIN, ALOWED_ERROR_MAX, ALOWED_ERROR_DEF},						// 153
		{0, 0, 0},																	// 154
		{0, 0, 0},																	// 155
		{0, 0, 0},																	// 156
		{0, 0, 0},																	// 157
		{0, 0, 0},																	// 158
		{0, 0, 0},																	// 159
		{0, 0, 0},																	// 160
		{0, 0, 0},																	// 161
		{0, 0, 0},																	// 162
		{0, 0, 0},																	// 163
		{0, 0, 0},																	// 164
		{0, 0, 0},																	// 165
		{0, 0, 0},																	// 166
		{0, 0, 0},																	// 167
		{0, 0, 0},																	// 168
		{0, 0, 0},																	// 169
		{0, 0, 0},																	// 170
		{0, 0, 0},																	// 171
		{0, 0, 0},																	// 172
		{0, 0, 0},																	// 173
		{0, 0, 0},																	// 174
		{0, 0, 0},																	// 175
		{0, 0, 0},																	// 176
		{0, 0, 0},																	// 177
		{0, 0, 0},																	// 178
		{0, 0, 0},																	// 179
		{0, 0, 0},																	// 180
		{0, 0, 0},																	// 181
		{0, 0, 0},																	// 182
		{0, 0, 0},																	// 183
		{0, 0, 0},																	// 184
		{0, 0, 0},																	// 185
		{0, 0, 0},																	// 186
		{0, 0, 0},																	// 187
		{0, 0, 0},																	// 188
		{0, 0, 0},																	// 189
		{0, 0, 0},																	// 190
		{0, 0, 0}																	// 191
};
