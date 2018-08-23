#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include "ACPI Defination.h"

using namespace std;

class UnCopyable
{
protected:
	UnCopyable() {}
	~UnCopyable() {}

private:
	explicit UnCopyable(const UnCopyable& x);
	UnCopyable& operator=(const UnCopyable& x);
};


class CACPI : private UnCopyable
{
public:
	CACPI();
	~CACPI();

	/****************************************************
	*@Function				Excute
	*@brief					����ACPI Tableֵ
	*@author				��˶
	*@param					��
		*@Table_Type		ACPI��ͷ��
	*@return				��
	****************************************************/
	void Excute();	

private:
	/****************************************************
	*@Function				GetACPIAddress
	*@brief					��ȡACPI�����ڴ��еĵ�ַ
	*@author				��˶
	*@param
	*@other
		*@isSupportACPI		�����øñ����ж�ִ���Ƿ�ɹ�
	****************************************************/
	void GetACPIAddress();

	/****************************************************
	*@Function				GetXSDT_RSDT
	*@brief					��ȡACPI���RSDP RSDT XSDT
	*@author				��˶
	*@param
	*@other
		*@isSupportACPI		�����øñ����ж�ִ���Ƿ�ɹ�
	****************************************************/
	void GetXSDT_RSDT();


	void GetOtherTabels();
public:
	ACPI_RSDP_STRUCTURE						acpi_rsdp;
	ACPI_RSDT_STRUCTURE						acpi_rsdt;
	ACPI_XSDT_STRUCTURE						acpi_xsdt;
	ACPI_MCFG_STRUCTURE						acpi_mcfg;
	ACPI_FADT_STRUCTURE						acpi_facp;
	std::shared_ptr<ACPI_FPDT_STRUCTURE>	acpi_fpdt;
	std::shared_ptr<ACPI_FACS_STRUCTURE>	acpi_facs;
	ACPI_HPET_STRUCTURE						acpi_hpet;
	std::shared_ptr<ACPI_SBST_STRUCTURE>	acpi_sbst;
	std::shared_ptr<ACPI_BGRT_STRUCTURE>	acpi_bgrt;
	bool isSupportACPI;	//�Ƿ�֧�ֻ�ȡACPI��
private:
	bool IsUEFI;
	size_t ACPIAddress;

};