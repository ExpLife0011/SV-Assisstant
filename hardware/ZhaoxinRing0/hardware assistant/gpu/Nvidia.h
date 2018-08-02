#pragma once

#include "Gpudata.h"

#define NVAPI_GPU_UTILIZATION_DOMAIN_GPU 0
#define NVAPI_GPU_UTILIZATION_DOMAIN_FB  1
#define NVAPI_GPU_UTILIZATION_DOMAIN_VID 2
#define NVAPI_GPU_UTILIZATION_DOMAIN_BUS 3

class CNvidia : public CGPU
{
public:
	CNvidia();
	using CGPU::CGPU;
	~CNvidia();
	bool CheckdllStatus();
	GPUTypes exec();
	const void* Returninfo();
	GPUTypes UpdateData();
private:
	NvAPI_Status EnumPhysicalGPUs();
	NvAPI_Status EnumNvidiaDisplayHandle();

	BOOL GetInterfaceVersion(string& version);
	BOOL GetsysDriverbranchVersion(string& driver, string& Branch);
	BOOL GetChipInfo();

	BOOL GetGPUFullName(string& GPUName, INT Index);
	BOOL GetGPUMem(NV_DISPLAY_DRIVER_MEMORY_INFO& mem, INT Index);
	BOOL GetGPUtemperature(INT Index, INT& MinTemp, INT& CurrentTemp, INT& MaxTemp);
	BOOL GetGPUFans(INT Index, ULONG& FansValue);
	BOOL GetGPUClock(INT Index, DEVICE_CLOCK& Device_clock);
	BOOL GetHDCPSupport(INT Index, BOOL& HDCPState);
	BOOL GetGpuCoreCount(INT Index, UINT& corecount);
	BOOL GetDynamicPstatesInfo(INT Index, NV_GPU_DYNAMIC_PSTATES_INFO_EX& percentage);
	BOOL GetVbiosVersion(INT Index, string& VbiosVersion);
	BOOL GetVbiosRevision(INT Index, string& VbiosRevision);
	BOOL GetVbiosOEMRevision(INT Index, string& VbiosOEMRevision);
	BOOL GetGpuType(INT Index, string& GPUType);
	BOOL GetSysType(INT Index, string& SysType);
	BOOL GetAGPAperture(INT Index, ULONG& AGPAperture);
	BOOL GetCurrentAGPRate(INT Index, ULONG& AGPRate);
	BOOL GetBUSID(INT Index, ULONG& BusID);
	BOOL GetBUSSlotID(INT Index, ULONG& BusSlotID);
	BOOL GetBusType(INT Index, string& BusType);
	BOOL GetPhysicalFrameBufferSize(INT Index, ULONG& PhysicalFrame);
	BOOL GetVirtualFrameBufferSize(INT Index, ULONG& VirtualFrame);
	BOOL GetGPUPState(INT Index, NV_GPU_PERF_PSTATES20_INFO& NV_PState);
	BOOL GetCurrentPState(INT Index, UINT& CurrentPState);
	BOOL GetDynamicInfo(INT Index, NVIDIA_USAGE& Nvidia_Usage);
	BOOL GetPCIEWidth(INT Index, ULONG& CurrentPCIEWidth);
	private:
	NvAPI_Status m_succeed_Nvidia;	//�жϼ���dll�Ƿ�ɹ�
	NvDisplayHandle hDisplay[NVAPI_MAX_PHYSICAL_GPUS * 2];
	NvPhysicalGpuHandle phys[NVAPI_MAX_PHYSICAL_GPUS];	//����GPU������
	NvU32 physcount;
	//out
	vector<NvidiaInfo> realnv;

	NV_CHIPSET_INFO Chipset;
};
