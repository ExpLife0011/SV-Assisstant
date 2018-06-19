#include "stdafx.h"
#include "service.h"

using namespace std;

void Enumservice()
{
	locale loc("chs");
	wcout.imbue(loc);
		SC_HANDLE SCMan = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS); //��ϵͳ���������   
		if (SCMan == NULL)
		{
			wcout << L"OpenSCManager Error" << endl;
			return;
		}
		LPENUM_SERVICE_STATUS service_status; //����ϵͳ����Ľṹ   
		DWORD cbBytesNeeded = NULL;
		DWORD ServicesReturned = NULL;
		DWORD ResumeHandle = NULL;

		service_status = (LPENUM_SERVICE_STATUS)LocalAlloc(LPTR, 1024 * 64);//�����ڴ棬ע���С   


																			//��ȡϵͳ����ļ���Ϣ   
		bool ESS = EnumServicesStatus(SCMan, //ϵͳ������   
			SERVICE_WIN32, //���������   
			SERVICE_STATE_ALL,  //�����״̬   
			(LPENUM_SERVICE_STATUS)service_status,  //���������ϵͳ����Ľṹ   
			1024 * 64,  // �ṹ�Ĵ�С   
			&cbBytesNeeded, //������������շ�������ķ���   
			&ServicesReturned, //������������շ��ط��������   
			&ResumeHandle); //���������������һ�ε��ñ���Ϊ0������Ϊ0����ɹ�   
		if (ESS == NULL)
		{
			wcout << L"EnumServicesStatus Error" << endl;
			return;
		}
		for (size_t i = 0; i < ServicesReturned; i++)
		{
			wcout << L"������:" << service_status[i].lpDisplayName << endl;
			switch (service_status[i].ServiceStatus.dwCurrentState)// ����״̬   
			{
			case SERVICE_CONTINUE_PENDING:
				wcout << L"״̬: ����" << endl;
				break;
			case SERVICE_PAUSE_PENDING:
				wcout << L"״̬: ������ͣ" << endl;
				break;
			case SERVICE_PAUSED:
				wcout << L"״̬: ����ͣ " << endl;
				break;
			case SERVICE_RUNNING:
				wcout << L"״̬: ���� " << endl;
				break;
			case SERVICE_START_PENDING:
				wcout << L"״̬: ���� " << endl;
				break;
			case SERVICE_STOPPED:
				wcout << L"״̬: ֹͣ " << endl;
				break;
			default:
				wcout << L"״̬: δ֪ " << endl;
				break;
			}
			LPQUERY_SERVICE_CONFIG lpServiceConfig = NULL; //������ϸ��Ϣ�ṹ   
			SC_HANDLE service_curren = NULL; //��ǰ�ķ�����   
			DWORD dw_Ret = 0;
			service_curren = OpenService(SCMan, service_status[i].lpServiceName, SERVICE_QUERY_CONFIG); //�򿪵�ǰ����   
			while (!QueryServiceConfig(service_curren, lpServiceConfig, dw_Ret, &ResumeHandle))
			{
				if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
				{
					if (lpServiceConfig)
						HeapFree(GetProcessHeap(), 0, lpServiceConfig);
					lpServiceConfig = (LPQUERY_SERVICE_CONFIG)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, ResumeHandle);
					dw_Ret = ResumeHandle;
				}
				else
					break;
			}
			dw_Ret = 0;
			if (lpServiceConfig)
			{
				switch (lpServiceConfig->dwStartType)
				{
				case SERVICE_AUTO_START:
				case SERVICE_BOOT_START:
					wcout << L"��������: �Զ� " << endl;
					break;
				case SERVICE_DEMAND_START:
				case SERVICE_SYSTEM_START:
					wcout << L"��������: �ֶ� " << endl;
					break;
				case SERVICE_DISABLED:
					wcout << L"��������: ���� " << endl;
					break;
				default:
					wcout << L"��������: δ֪ " << endl;
					break;
				}
			}
			LPSERVICE_DESCRIPTION descripton = NULL;
			while (!QueryServiceConfig2(service_curren, SERVICE_CONFIG_DESCRIPTION, (LPBYTE)descripton, dw_Ret, &ResumeHandle))
			{
				if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
				{
					if (descripton)
						HeapFree(GetProcessHeap(), 0, descripton);
					descripton = (LPSERVICE_DESCRIPTION)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, ResumeHandle);
					dw_Ret = ResumeHandle;
				}
				else
					break;
			}

			if (descripton)
			{
				wcout << L"����������:" << descripton->lpDescription << endl;
				HeapFree(GetProcessHeap(), 0, descripton);
				descripton = NULL;
			}
			dw_Ret = 0;

			wcout << L"·��: " <<lpServiceConfig->lpBinaryPathName <<endl;//�����·��   
			CloseServiceHandle(service_curren);//�رյ�ǰ����ľ��   
			if (lpServiceConfig)
			{
				HeapFree(GetProcessHeap(), 0, lpServiceConfig);
				lpServiceConfig = NULL;
			}
		}
		CloseServiceHandle(SCMan);//�رշ���������ľ��   
}