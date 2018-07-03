#include "stdafx.h"
#include "service.h"

using namespace std;

void SV_ASSIST::Software::Origin::Enumservice(std::list<Service_Struct>& data)
{
		SC_HANDLE SCMan = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS); //��ϵͳ���������   
		if (SCMan == NULL)
		{
			OutputDebugString(L"OpenSCManager Error");
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
			OutputDebugString(L"EnumServicesStatus Error");
			return;
		}
		for (size_t i = 0; i < ServicesReturned; i++)
		{
			Service_Struct temp = {};
			if (service_status[i].lpDisplayName)
			temp.ServiceDisplayName = service_status[i].lpDisplayName;
			if (service_status[i].lpServiceName)
			temp.ServiceName = service_status[i].lpServiceName;
			switch (service_status[i].ServiceStatus.dwCurrentState)// ����״̬   
			{
			case SERVICE_CONTINUE_PENDING:
				temp.CurrentStatus = CONTINUE_PENDING;
				break;
			case SERVICE_PAUSE_PENDING:
				temp.CurrentStatus = PAUSE_PENDING;
				break;
			case SERVICE_PAUSED:
				temp.CurrentStatus = PAUSED;
				break;
			case SERVICE_RUNNING:
				temp.CurrentStatus = RUNNING;
				break;
			case SERVICE_START_PENDING:
				temp.CurrentStatus = START_PENDING;
				break;
			case SERVICE_STOPPED:
				temp.CurrentStatus = STOPPED;
				break;
			default:
				temp.CurrentStatus = SERVICE_UNKNOWN;
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
				if(lpServiceConfig->lpBinaryPathName)
				temp.ServicePath = lpServiceConfig->lpBinaryPathName;
				switch (lpServiceConfig->dwStartType)
				{
				case SERVICE_AUTO_START:
				case SERVICE_BOOT_START:
					temp.Startype = AUTO_START;
					break;
				case SERVICE_DEMAND_START:
				case SERVICE_SYSTEM_START:
					temp.Startype = DEMAND_START;
					break;
				case SERVICE_DISABLED:
					temp.Startype = DISABLED;
					break;
				default:
					temp.Startype = UNKNOWN_START;
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
				if (descripton->lpDescription)
				temp.descripton = descripton->lpDescription;
				HeapFree(GetProcessHeap(), 0, descripton);
				descripton = NULL;
			}
			dw_Ret = 0;

			CloseServiceHandle(service_curren);//�رյ�ǰ����ľ��   
			if (lpServiceConfig)
			{
				HeapFree(GetProcessHeap(), 0, lpServiceConfig);
				lpServiceConfig = NULL;
			}
			data.emplace_back(temp);
		}
		CloseServiceHandle(SCMan);//�رշ���������ľ��   
}