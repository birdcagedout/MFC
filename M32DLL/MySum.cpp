#include "pch.h"



// 1. *.lib������ �ܺο��� ����� �� �ֵ���: __declspec(dllexport)
// 2. DLL������ �̿��Ͽ� �ܺο��� ����� �� �ֵ��� �Լ� �̸��� ������Ŵ: extern "C"

extern "C" __declspec(dllexport) int MyDLLSum(int a, int b)
{
	return a + b;
}
