#include "EDIDdefination.h"

/*************************************************
Copyright: 2017 Zhaoxin BJ-SV
Author:��˶
Date:2017-12-13
Description: ��ȡEDID����Ϣ
**************************************************/

namespace SV_ASSIST
{
	namespace Display
	{
		/**************************************************************
		*@Function				GetEDID
		*@brief					���EDID��ֵ
		*@author				��˶
		*@param
		*@return
			*@EDID				EDIDδ������ֵ
		****************************************************************/
		const std::vector<EDID>& GetEDID();

		/**************************************************************
		*@Function				Exec
		*@brief					ִ�л�ȡEDIDֵ
		*@author				��˶
		*@param
			*@null
		*@return
			*@null	
		*@Other					
								�����ļ�\\HardWare\\EDID\\edid%d.txt	
		****************************************************************/
		void Exec();

		/**************************************************************
		*@Function				UpdateData
		*@brief					����EDIDֵ
		*@author				��˶
		*@param
			*@null
		*@return
			*@null				����EDID ����Execǰ����ñ�����
		****************************************************************/

		void UpdateData();
	}
}



