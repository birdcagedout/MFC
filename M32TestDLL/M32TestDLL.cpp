// M32TestDLL.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "M32TestDLL.h"


// *.lib 파일 사용하기
//#pragma comment (lib, "M32DLL.lib")
//int MyDLLSum(int a, int b);


// *.dll 파일 사용하기
// ==> 함수 프로토타입을 MY_DLL_SUM이라는 이름으로 정의
typedef int(*MY_DLL_SUM)(int, int);



LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg == WM_CREATE) {

    }
    else if (uMsg == WM_LBUTTONDOWN) {

        // dll 파일을 연결
        HMODULE hMyDLLSum = LoadLibrary(L"M32DLL.dll");

        // 원하는 함수를 담을 함수포인터 만들기
        //int (*pSum)(int, int);


        // dll 파일에서 원하는 함수 찾기
        //pSum = (int(*)(int, int))GetProcAddress(hMyDLLSum, "MyDLLSum");
        MY_DLL_SUM pSum = (MY_DLL_SUM)GetProcAddress(hMyDLLSum, "MyDLLSum");

        wchar_t str[16];
        /*wsprintf(str, L"5 + 6 = %d", MyDLLSum(5, 6));*/
        wsprintf(str, L"4 + 7 = %d", (*pSum)(4, 7));
        MessageBox(hWnd, str, L"결과", MB_OK);

        // dll 파일을 해제할 때
        FreeLibrary(hMyDLLSum);

    }
    else if (uMsg == WM_RBUTTONDOWN) {

    }
    else if (uMsg == WM_PAINT) {
        PAINTSTRUCT ps;
        HDC h_dc = BeginPaint(hWnd, &ps);


        EndPaint(hWnd, &ps);
        return 0;
    }
    else if (uMsg == WM_DESTROY) {
        PostQuitMessage(0);
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASS wc;

    wchar_t my_class_name[] = L"Win32프로그램";
    wc.cbClsExtra = NULL;
    wc.cbWndExtra = NULL;
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance = hInstance;
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = my_class_name;
    wc.lpszMenuName = NULL;
    wc.style = CS_HREDRAW | CS_VREDRAW;

    RegisterClass(&wc);

    HWND hWnd = CreateWindow(my_class_name, L"Win32프로그램",
        WS_OVERLAPPEDWINDOW, 100, 90, 400, 350, NULL, NULL, hInstance, NULL);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}