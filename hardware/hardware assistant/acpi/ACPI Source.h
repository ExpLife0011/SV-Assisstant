#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include "ACPI Defination.h"

using namespace std;

//ACPI �������
typedef enum _ACPI_Head 
{
	RSDP = 'PDSR',
	XSDT = 'TDSX',
	RSDT = 'TDSR',
	FACP = 'PCAF',
	FADT = 'TDAF',
	APIC = 'CIPA',
	FPDT = 'TDPF',
	MCFG = 'GFCM',
	HPET = 'TEPH',
	BGRT = 'TRGB',
	SSDT = 'TDSS',
	FACS = 'SCAF',
	DSDT = 'TDSD'
}ACPI_Head;

//
typedef struct _ACPI_TABLE
{
	PUCHAR FireWareTable;
	size_t FireWareTableSize;
}ACPI_TABLE;

class UnCopyable
{
protected:
	UnCopyable() {}
	~UnCopyable() {}

private:
	UnCopyable(const UnCopyable& x);
	UnCopyable& operator=(const UnCopyable& x);
};


class CACPI : private UnCopyable
{
public:
	CACPI();
	virtual ~CACPI();
	/****************************************************
	*@Function				Get
	*@brief					��ȡACPI Tableֵ
	*@author				��˶
	*@param					��
	*@return				��
	****************************************************/
	void Get();

	/****************************************************
	*@Function				Excute
	*@brief					����ACPI Tableֵ
	*@author				��˶
	*@param					��
		*@Table_Type		ACPI��ͷ��
	*@return				��
	****************************************************/
	void Excute(const DWORD Table_Type);	

private:
	/****************************************************
	*@Function				SafeDeleteArray
	*@brief					��ȫ�ͷ�����
	*@author				��˶
	*@param					��
		*@Array				����
	*@return				��
	****************************************************/
	template<class T>
	void SafeDeleteArray(T*& Array);

	/****************************************************
	*@Function				SafeDeletePoint
	*@brief					��ȫ�ͷ�ָ��
	*@author				��˶
	*@param					
		*@Point				ָ��
	*@return				��
	****************************************************/
	template<class T>
	void SafeDeletePoint(T*& Point);

	/****************************************************
	*@Function				Get_FirmWare_Enum
	*@brief					ö��ACPI��������Լ�������� �������б���FirmwareTableID
	*@author				��˶
	*@param					��
	*@return				
		*@bool				ִ���Ƿ�ɹ�
	****************************************************/
	bool Get_FirmWare_Enum();

	/****************************************************
	*@Function				PrintACPITable
	*@brief					��ӡ�������
	*@author				��˶
	*@param					
		*@TableName			������֣�������ʽ��
	*@return
		*@bool				ִ���Ƿ�ɹ�
	****************************************************/
	void PrintACPITable(DWORD TableName);

	/****************************************************
	*@Function				Get_ACPI_Table
	*@brief					��ȡACPI������� ���������FirewareTable��
	*@author				��˶
	*@param
		*@Table_Type		������֣�������ʽ��
		*@Num				��������λ��
	*@return
		*@BOOL				ִ���Ƿ�ɹ�
	****************************************************/
	BOOL Get_ACPI_Table(const DWORD Table_Type, const size_t Num);
public:
	ACPI_FADT_STRUCTURE				facp;
	ACPI_HPET_STRUCTURE				hpet;
	ACPI_MCFG_STRUCTURE				mcfg;
	PACPI_FPDT_STRUCTURE			fpdt;
	ACPI_BGRT_STRUCTURE				bgrt;
	bool isSupportACPI;	//�Ƿ�֧�ֻ�ȡACPI��
private:
	vector<DWORD> FirmwareTableID;	//�ɻ�ȡ��ACPI��ͷ������
	ACPI_TABLE FirewareTable[30];	//ACPI�������

};
