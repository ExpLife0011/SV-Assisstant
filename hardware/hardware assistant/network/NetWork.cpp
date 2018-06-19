#include "stdafx.h"
#include "NetWork.h"

namespace SV_ASSIST
{
	namespace Net
	{
		NetWork::NetWork() : NNproperties(nullptr)
		{
			CoInitialize(NULL);//��ʼ��COM��
							   //��չ֪ʶ���������� Windows�Ե��̵߳ķ�ʽ����com����CoInitialize��CoUninitialize����ɶ�ʹ�á�
			CoCreateInstance(CLSID_ConnectionManager, NULL, CLSCTX_SERVER, IID_INetConnectionManager, (void**)&pManager);
		}


		NetWork::~NetWork()
		{
			pEnum = nullptr;
			pConnection = nullptr;
			pManager = nullptr;
			CoUninitialize();
		}

		void NetWork::Exec()
		{
			if (pManager == NULL)
			{
				OutputDebugString(L"�����쳣������ʧ��");
				return;
			}
			pManager->EnumConnections(NCME_DEFAULT, &pEnum);
			while (pEnum->Next(1, &pConnection, &celt) == S_OK)
			{
				pConnection->GetProperties(&NNproperties);
				if(NNproperties->pszwDeviceName)
					t.emplace_back(NNproperties->pszwDeviceName);
				pConnection = nullptr;
			}
		}

		void NetWork::Update()
		{
			pEnum = nullptr;
			pConnection = nullptr;

			this->t.clear();
			this->Exec();
		}

		const std::vector<std::wstring> &NetWork::GetData()
		{
			return t;
		}

		NetWorkInterface::NetWorkInterface()
		{
		}

		NetWorkInterface::~NetWorkInterface()
		{
		}
	}
}
