#pragma once

// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� DRIVERDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// ZHAOXINSOFTWAREDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef ZHAOXINSOFTWAREDLL_EXPORTS
#define ZHAOXINSOFTWAREDLL_API __declspec(dllexport)
#else
#define ZHAOXINSOFTWAREDLL_API __declspec(dllimport)
#endif

#include <windows.h>
#include <list>

namespace SV_ASSIST
{
	namespace Software
	{
		namespace Ring0
		{
			ZHAOXINSOFTWAREDLL_API const std::list<M_EPROCESS>& GetCurrentProcess();
			ZHAOXINSOFTWAREDLL_API const std::list<DRIVER_MODULE>& GetCurrentModule();
			ZHAOXINSOFTWAREDLL_API const std::list<PLUGPLAY_STRUCT>& GetCurrentPowerSetting();
			ZHAOXINSOFTWAREDLL_API const std::list<PLUGPLAY_STRUCT>& GetCurrentFsNotifyChange();
			ZHAOXINSOFTWAREDLL_API const std::list<SHUTDOWN_STRUCT>& GetCurrentLastshutdown();
			ZHAOXINSOFTWAREDLL_API const std::list<SHUTDOWN_STRUCT>& GetCurrentShutdown();
			ZHAOXINSOFTWAREDLL_API const std::list<BUG_STRUCT>& GetCurrentBugReason();
			ZHAOXINSOFTWAREDLL_API const std::list<BUG_STRUCT>& GetCurrentBug();
			ZHAOXINSOFTWAREDLL_API const std::list<DWORD64>& GetCurrentCmpCallback();
			ZHAOXINSOFTWAREDLL_API const std::list<DWORD64>& GetCurrentLodImage();
			ZHAOXINSOFTWAREDLL_API const std::list<DWORD64>& GetCurrentProcessCallback();
			ZHAOXINSOFTWAREDLL_API const std::list<DWORD64>& GetCurrentThreadCallback();
			ZHAOXINSOFTWAREDLL_API const std::list<FILTERSYS_INFO>& GetCurrentFilter();
			ZHAOXINSOFTWAREDLL_API const std::list<DPCTIMER_STRUCT>& GetCurrentDpcTimer();
			ZHAOXINSOFTWAREDLL_API const std::list<GPTABLE_STRUCT>& GetCurrentGdtTable();
			ZHAOXINSOFTWAREDLL_API const std::list<IDTABLE_STRUCT>& GetCurrentIdtTable();
			ZHAOXINSOFTWAREDLL_API const std::list<DWORD64>& GetCurrentSCSI();
			ZHAOXINSOFTWAREDLL_API const std::list<DWORD64>& GetCurrentACPICallback();
			ZHAOXINSOFTWAREDLL_API const std::list<DWORD64>& GetCurrentAtapi();
			ZHAOXINSOFTWAREDLL_API const std::list<DWORD64>& GetCurrentDisk();
			ZHAOXINSOFTWAREDLL_API const std::list<DWORD64>& GetCurrentPartmgr();
			ZHAOXINSOFTWAREDLL_API const std::list<DWORD64>& GetCurrentI8042prt();
			ZHAOXINSOFTWAREDLL_API const std::list<DWORD64>& GetCurrentKeybroad();
			ZHAOXINSOFTWAREDLL_API const std::list<DWORD64>& GetCurrentMouse();
			ZHAOXINSOFTWAREDLL_API const std::list<DWORD64>& GetCurrentFSD();
			ZHAOXINSOFTWAREDLL_API const std::list<DWORD64>& GetCurrentTcpip();
			ZHAOXINSOFTWAREDLL_API const std::list<DWORD64>& GetCurrentTdx();
			ZHAOXINSOFTWAREDLL_API const std::list<DWORD64>& GetCurrentNsiproxy();
			ZHAOXINSOFTWAREDLL_API const std::list<DWORD64>& GetCurrentSSDT();
			ZHAOXINSOFTWAREDLL_API const std::list<DWORD64>& GetCurrentShadowSSDT();
			ZHAOXINSOFTWAREDLL_API void UpdateData();
		}
	}
}