// dllmain.cpp : DLL 애플리케이션의 진입점을 정의합니다.
#include "pch.h"


HINSTANCE g_hInstance;                  // 전역변수로 기억
HHOOK g_hNextHook;                      // hook을 건 다음번 프로그램
HWND g_hTargetWnd;                      // 이 모듈을 이용할 모니터 프로그램



BOOL APIENTRY DllMain( HMODULE hModule,
					   DWORD  ul_reason_for_call,
					   LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}

	g_hInstance = hModule;              // 전역변수로 기억

	return TRUE;
}


// 키후킹시 처리함수(함수 프로토타입이 정해져있음) ==> 이 함수는 외부에서 사용하지 않은 거라 extern "C" / __declspec(dllexport) 필요없음
LRESULT CALLBACK KeyProc(int a_code, WPARAM wParam, LPARAM lParam)
{
	if (a_code == HC_ACTION) {
		::PostMessage(g_hTargetWnd, 27001, wParam, lParam);					// 이 함수를 call 하는 모니터 프로그램에 메시지 보냄
	}

	return CallNextHookEx(g_hNextHook, a_code, wParam, lParam);
}


// 후킹 시작 ==> 현재 활성화된 윈도에 후킹 연결
extern "C" __declspec(dllexport) void InstallKeyHook(HWND a_hTargetWnd)
{
	g_hTargetWnd = a_hTargetWnd;													// 이 함수를 call하는 모니터 프로그램을 기억
	g_hNextHook = SetWindowsHookEx(WH_KEYBOARD, KeyProc, g_hInstance, 0);			// hook을 건 다음 프로그램에 넘김
}


// 후킹 해제
extern "C" __declspec(dllexport) void UninstallKeyHook()
{
	UnhookWindowsHookEx(g_hNextHook);
}