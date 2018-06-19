#pragma once

typedef DWORD(WINAPI *PFNGetExtendedUdpTable)(
	__out         PVOID pUdpTable,//���ز�ѯ�ṹ��ָ��
	__inout       PDWORD pdwSize,//���ƽṹ���С
	__in          BOOL bOrder,//�Ƿ�����
	__in          ULONG ulAf,//��AF_INET����AF_INET6
	__in          UDP_TABLE_CLASS TableClass,//���ؽṹ�������
	__in          ULONG Reserved//����ֵ
	);

typedef DWORD(WINAPI *PFNGetExtendedTcpTable)(
	__out         PVOID pTcpTable,
	__inout		  PDWORD pdwSize,//��С
	__in          BOOL bOrder,
	__in          ULONG ulAf,
	__in          TCP_TABLE_CLASS TableClass,
	__in          ULONG Reserved
	);

typedef DWORD(WINAPI *PFNSetTcpEntry)(
	IN PMIB_TCPROW pTcpRow
	);

class CConnect
{
public:
	CConnect();
	int GetTcpConnect(std::vector<ConnInfo>& connInfo);
	static std::wstring GetState(int nState);
	int GetUdpConnect(std::vector<ConnInfo>& connInfo);
	~CConnect();
private:
	HMODULE hMod;
	PFNGetExtendedTcpTable m_pfnGetTcpTable;
	PFNGetExtendedUdpTable m_pfnGetUdpTable;
};

