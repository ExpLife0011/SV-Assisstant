
// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� CPU_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// CPU_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef ACPI_EXPORTS
#define ACPI_API __declspec(dllexport)
#else
#define ACPI_API __declspec(dllimport)
#endif
#include <windows.h>
#include "ACPI Defination.h"

// �����Ǵ� ACPI.dll ������
class ACPI_API CACPI {
public:
	CACPI(void);
	~CACPI();
	// TODO:  �ڴ�������ķ�����	
	virtual BOOL Excute() = 0;
	virtual const ACPI_MCFG_STRUCTURE ReturnMCFG() = 0;
};

ACPI_API CACPI* Instantiate(void);
ACPI_API void Free(CACPI* pBase);
