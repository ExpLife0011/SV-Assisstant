#include "stdafx.h"
#include "IntelMSR.h"

const DWORD IA32_THERM_STATUS_MSR = 0x019C;
const DWORD IA32_TEMPERATURE_TARGET = 0x01A2;
const DWORD IA32_PERF_STATUS = 0x0198;
const DWORD MSR_PLATFORM_INFO = 0xCE;
const DWORD IA32_PACKAGE_THERM_STATUS = 0x1B1;
const DWORD MSR_RAPL_POWER_UNIT = 0x606;
const DWORD MSR_PKG_ENERY_STATUS = 0x611;
const DWORD MSR_DRAM_ENERGY_STATUS = 0x619;
const DWORD MSR_PP0_ENERY_STATUS = 0x639;
const DWORD MSR_PP1_ENERY_STATUS = 0x641;