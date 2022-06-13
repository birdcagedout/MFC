#include "pch.h"



// 1. *.lib파일을 외부에서 사용할 수 있도록: __declspec(dllexport)
// 2. DLL파일을 이용하여 외부에서 사용할 수 있도록 함수 이름을 고정시킴: extern "C"

extern "C" __declspec(dllexport) int MyDLLSum(int a, int b)
{
	return a + b;
}
