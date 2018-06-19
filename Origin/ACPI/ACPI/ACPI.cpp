// ACPI.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "ACPI Source.h"
#include "ACPI.h"
#include <memory>



// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� ACPI.h

CACPI::CACPI(void)
{
	return;
}

CACPI::~CACPI()
{
	return;
}

//�����ǵ������ʵ��
class CACPI_info : public CACPI
{
public:
	CACPI_info();
	virtual ~CACPI_info();
	BOOL Excute();
	const ACPI_MCFG_STRUCTURE ReturnMCFG();
private:
	std::tr1::shared_ptr<ACPI> acpi;
};

CACPI_info::CACPI_info() : acpi(new ACPI())
{
}

CACPI_info::~CACPI_info()
{
}

BOOL CACPI_info::Excute()
{
	if (acpi->isSupportACPI)
	{
		acpi->Get();
	}
	return acpi->isSupportACPI;
}

const ACPI_MCFG_STRUCTURE CACPI_info::ReturnMCFG()
{
	return acpi->mcfg;
}

ACPI_API CACPI * Instantiate(void)
{
	return new CACPI_info;
}

ACPI_API void Free(CACPI * pBase)
{
	if (pBase)
	{
		delete pBase;
		pBase = NULL;
	}
}
