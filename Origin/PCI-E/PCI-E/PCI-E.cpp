#include <vld.h>
#include "tchar.h"
#include "PCI-E.h"

typedef CACPI* (*ACPIExport)(void);
typedef CACPI* (*ACPI_Free)(CACPI*);

BOOL Initialize(HMODULE& hMoudle)
{
	hMoudle = LoadLibrary(_T("ACPI.dll"));
	if (hMoudle == NULL)
	{
		OutputDebugString("Dllδ�ܳɹ�����");
		return GetLastError();
	}
	return TRUE;
}

void Free(HMODULE& hMoudle)
{
	if (hMoudle)
	{
		FreeLibrary(hMoudle);
	}
}
BOOL GetPCIEBaseAddress(ULONGLONG& PCIE_BaseAddress)
{
	HMODULE hMoudule;
	if (Initialize(hMoudule) != TRUE)
	{
		return FALSE;
	}
	ACPIExport ACPIGet = (ACPIExport)GetProcAddress(hMoudule, "Instantiate");// ��ָ��ָ�����׵�ַ  
	ACPI_Free ACPIFree = (ACPI_Free)GetProcAddress(hMoudule, "Free");// ��ָ��ָ�����׵�ַ  
	if (ACPIGet == NULL || ACPIFree == NULL)
	{
		OutputDebugString("Dll��new��δ�ܳɹ�����");
		FreeLibrary(hMoudule);
		return FALSE;
	}
	CACPI* acpi = ACPIGet();
	acpi->Excute();
	ACPI_MCFG_STRUCTURE mcfg;
	mcfg = acpi->ReturnMCFG();
	PCIE_BaseAddress = mcfg.Configuration_space_base_address.Base_Address;

	ACPIFree(acpi);
	FreeLibrary(hMoudule);

	if (PCIE_BaseAddress)
	{
		return TRUE;
	}
	return FALSE;
}

int  main()
{
	ULONGLONG PCIE = 0;
	GetPCIEBaseAddress(PCIE);
}
