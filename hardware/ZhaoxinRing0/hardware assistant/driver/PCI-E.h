#pragma once

/*************************************************
Copyright: 2017 Zhaoxin BJ-SV
Author:��˶
Date:2017-12-13
Description: ��ȡPCIE CFG����Ϣ
**************************************************/

/**************************************************************
*@Function				GetPCIEConfigSpace
*@brief					��ȡPCIE Configuration Space
*@author				��˶
*@param
	*@PCIE_BaseAddress	IN PCIE�ڴ��ַ
	*@bus				bus
	*@dev				device
	*@func				function
	*@Data				INOut PCIE���ÿռ�����
	*@DataSize			INOut PCIE���ÿռ��С4096
*@return
	*@BOOL				��ȡConfiguration Space�Ƿ�ɹ�(����GetAllpciinfo��ȷ��)
****************************************************************/
BOOL GetPCIEConfigSpace(const ULONGLONG PCIE_BaseAddress, ULONG bus, ULONG dev, ULONG func, PVOID& Data, size_t DataSize);