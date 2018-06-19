#pragma once
#include <PowrProf.h>
#include <initguid.h>

#pragma comment(lib, "PowrProf.lib")

/*************************************************
Copyright:Zhaoxin
Author:��˶
Date:2017-12-26
Description:���ĵ�Դ����ѡ������Ƿ�����������ǽ�Ƿ��
**************************************************/
namespace SV_ASSIST
{
	namespace Software
	{
		namespace Origin
		{
			// ʡ����	�������ܣ����ܻ����ӽ��ܡ�	a1841308 - 3541 - 4fab - bc81 - f71556f20b4a
			// ����	���������Զ�ƽ�����ܺ͹��ġ�	381b4222 - f694 - 41f0 - 9685 - ff5bb260df2e
			// ������	�Ը��ߵĹ���Ϊ�����ṩ��ߵ����ܡ�	8c5e7fda - e8bf - 4a96 - 9a85 - a6e23a8c635c

			DEFINE_GUID(BALANCEMODE, 0x381B4222, 0xF694, 0x41F0, 0x96, 0x85, 0xFF, 0x5B, 0xB2, 0x60, 0xDF, 0x2E);
			DEFINE_GUID(HIGHPERFORMANCEMODE, 0x8C5E7FDA, 0xE8BF, 0x4A96, 0x9A, 0x85, 0xA6, 0xE2, 0x3A, 0x8C, 0x63, 0x5C);
			DEFINE_GUID(POWERSAVEMODE, 0xA1841308, 0x3541, 0x4FAB, 0xBC, 0x81, 0xF7, 0x15, 0x56, 0xF2, 0x0B, 0x4A);

			typedef struct _SYSTEM_POWER_INFORMATION {
				ULONG MaxIdlenessAllowed;
				ULONG Idleness;
				ULONG TimeRemaining;
				UCHAR CoolingMode;
			} SYSTEM_POWER_INFORMATION, *PSYSTEM_POWER_INFORMATION;

			/*************************************************
			Function:       // PowerManagement
			Description:    // ����Դ��������Ϊ�����ܡ����ر���Ļ
			Input:          // ��
			Output:         // ��
			Return:         // �Ƿ�ɹ�
			Others:         // ��
			*************************************************/
			BOOL PowerManagement();

			/*************************************************
			Function:       // ChangeBlueCrash
			Description:    // ������������������
			Input:          // ��
			AutoReboot	//�Ƿ������� TRUE������ FALSE�������� Others������ֵ
			Output:         // ��
			Return:         // �Ƿ�ɹ�
			Others:         // ��
			*************************************************/
			BOOL ChangeBlueCrash(BOOL AutoReboot);

			/*************************************************
			Function:       // FireWall
			Description:    // ������ǽ��������
			Input:          // ��
			AutoReboot	//�Ƿ�������ǽ TRUE������ FALSE�������� Others������ֵ
			Output:         // ��
			Return:         // �Ƿ�ɹ�
			Others:         // ��
			*************************************************/
			BOOL FireWall(BOOL EnableFireWall);
		}
	}
}
