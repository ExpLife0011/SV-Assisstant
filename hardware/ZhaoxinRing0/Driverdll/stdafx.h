// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <windows.h>

// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�

// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� DRIVERDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// DRIVERDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�

#ifdef DRIVERDLL_EXPORTS
#define DRIVERDLL_API __declspec(dllexport)
#else
#define DRIVERDLL_API __declspec(dllimport)
#endif

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <memory>
#include <tchar.h>
#include <vector>
#include <map>
#include <string>
#include <array>
#include <bitset>
#include "Defination\Ring0Defination.h"

void OutputDebugPrintf(const TCHAR* strOutputString, ...);





