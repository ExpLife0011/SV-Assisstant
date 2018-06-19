// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� DRIVERDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// DRIVERDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef DRIVERDLL_EXPORTS
#define DRIVERDLL_API __declspec(dllexport)
#else
#define DRIVERDLL_API __declspec(dllimport)
#endif

#include <windows.h>
#include "Ring0Defination.h"

DRIVERDLL_API BOOL RdIOPort(IN USHORT IO_Port_Addr, IN USHORT IO_DataSize, OUT DWORD64& IO_Data);
DRIVERDLL_API BOOL WrIOPort(IN USHORT IO_Port_Addr, IN USHORT IO_DataSize, IN ULONG IO_Data);
DRIVERDLL_API BOOL RdMsrTx(IN DWORD Index, OUT DWORD64& Data, IN DWORD_PTR threadAffinityMask);
DRIVERDLL_API BOOL WrMsrTx(IN DWORD Index, IN DWORD64 Data, IN DWORD_PTR threadAffinityMask);
DRIVERDLL_API BOOL RdMsr(IN DWORD Index, OUT DWORD64& Data);
DRIVERDLL_API BOOL WrMsr(IN DWORD Index, IN DWORD64 Data);
DRIVERDLL_API BOOL RdMemory(IN LONGLONG Memory_Addr, IN USHORT Mem_DataSize, OUT ULONG& Memory_Data);
DRIVERDLL_API BOOL WrMemory(IN LONGLONG Memory_Addr, IN USHORT Mem_DataSize, IN ULONG Memory_Data);
DRIVERDLL_API BOOL ReadPci(IN USHORT bus, IN USHORT dev, IN USHORT func, OUT PCI_COMMON_CONFIG& pci_config);
DRIVERDLL_API BOOL WritePci(IN USHORT bus, IN USHORT dev, IN USHORT func, IN UCHAR offset, IN ULONG Data);
DRIVERDLL_API BOOL ReadSPD(USHORT Base_Address, USHORT Slave_Address, DDR3_INFO & data);
DRIVERDLL_API BOOL GetECData(Embedded_Controller_Data& EC_Data);
DRIVERDLL_API BOOL SetECData(BYTE EC_Addr, BYTE EC_Write_Data);
DRIVERDLL_API BOOL GetSMbusBaseAddr(const USHORT VendorID,USHORT& SMbusBaseAddress);
DRIVERDLL_API USHORT GetPCIVendorID();