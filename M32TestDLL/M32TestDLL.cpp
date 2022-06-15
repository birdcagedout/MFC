// M32TestDLL.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "M32TestDLL.h"



/* 출처: 수까락의 프로그래밍 이야기 : http://sweeper.egloos.com/1792751

1. Static library

Dynamic (linking) library (흔히 얘기하는 DLL)을 설명하기 위해 간단하게 정리한다.

특정 기능의 라이브러리를 static 하게 제작한다는 것은 link 단계에서
라이브러리(*.lib 파일)를 실행 바이너리에 포함시킨다는 얘기이다.

즉, 라이브러리의 동작 코드가 이를 사용하는 실행 바이너리 속에
포함되기 때문에 별도의 추가 작업없이, 그리고 독립적으로(실행 바이너리만으로...)
라이브러리 함수들을 사용할 수 있다.

하지만, 정적 라이브러리를 사용하는 프로그램이 늘어나면 날수록
불필요하게 실행 파일들의 크기가 커지며,
라이브러리가 동시에 여러 실행 바이너리에 포함되어 실행되는 경우
메인 메모리의 공간 활용 효율이 떨어지는 등 multiple-caller program이 존재하는 경우 그다지 바람직하지 않다.

정적 라이브러리를 사용하기 위해서는 프로젝트 설정의 Link 옵션에
라이브러리를 추가해 주거나 아래의 #pragma 지시자를 사용하면 된다.

#pragma comment(lib, "NAME.lib")



2. Dynamic (linking) library : DLL

말 그대로 "동적으로 링크하여 사용하는 라이브러리" 이다.

동적 라이브러리는 이를 사용하고자 하는 실행 바이너리에서
필요시 사용할 수 있도록 최소한의 정보만 포함하여 링크하거나,
아예 독립적으로 DLL을 로드/사용/해제할 수 있다.

1) Implicit linking

DLL을 구현하고 컴파일하고 나면 static library와는 다르게  output file이 2개 생성된다.
하나는 *.lib 파일이고 하나는 *.dll 파일이다.
여기서 *.lib 파일은 static library의 *.lib 파일과는 전혀 다르다.

Static library의 *.lib 파일은 라이브러리 전체 코드를 포함하는 바이너리이며,
DLL의 *.lib 파일은 DLL이 제공하고자 하는 함수 정보(함수명)을 가지는 정보 파일이다.

DLL의 *.lib 파일을 이용하여 링킹하는 것을 암시적 링킹(implicit linking)이라고 한다.
실행 바이너리를 링크 단계에서 실행 바이너리의 *.obj 파일들과 DLL의 *.lib 파일을
함께 링크하여 이 정보를 토대로 runtime에 DLL의 함수 코드를 참조하게 되는 것이다.
(한 줄로 요약하면 *.lib 파일은 링크시 필요하고, *.dll 파일은 실행시 필요하다)

정적 라이브러리를 사용할 때와 같이 프로젝트 설정의 Link 옵션에
라이브러리를 추가해 주거나 아래의 #pragma 지시자를 사용하면 된다.

#pragma comment(lib, "NAME.lib")

2) Explicit linking

명시적 링킹에서는 *.lib 파일이 필요하지 않다.
실행 바이너리 링크 단계에서 DLL의 함수 정보가 필요하지 않기 때문이다.

명시적 링킹에서 사용되는 세 가지 함수와 역할은 다음과 같다.

1. LoadLibrary : 필요한 DLL을 프로세스 가상 메모리에 맵핑한다.
2. GetProcAddress : DLL 함수의 포인터를 획득한다.
3. FreeLibrary : 프로세스 가상 메모리에서 DLL을 반환한다.

프로세스는 내부적으로 DLL의 레퍼런스 카운트를 계산한다.
LoadLibrary 호출시 DLL의 (프로세스) 레퍼런스 카운트는 1씩 증가하고,
FreeLibrary 호출시 레퍼런스 카운트가 1씩 감소한다.
레퍼런스 카운트가 0이 될 때 해당 DLL은 프로세스 가상 메모리에서 해제된다.

여기서 주의할 점이 물리 메모리가 아닌 가상 메모리에서의 반환(해제)라는 것이다.
레퍼런스 카운트는 각 프로세스 내부의 호출 회수이지,
전체 프로세스 간의 호출 회수가 아니라는 것이다.

이러한 레퍼런스 카운트를 두는 이유는 프로그램 실행 중에
DLL을 가상 메모리에 할당, 해제할 수 있도록 하기 위함이다.
(Implicit linking 방식에서는 이러한 장점을 얻을 수 없다.)

정리해서 명시적 링킹의 장점을 세 가지 정도 정리해 보면...

1. DLL이 필요한 시점에서 로딩하고, 불필요해지면 반환하기 때문에 메모리가 절약된다.
2. 프로그램 실행 중에 DLL 교체 및 선택이 가능하다.
3. 암시적 링킹은 프로그램 실행 전에 필요한 모든 DLL을 메모리에 로딩한다.
때문에 실행까지 걸리는 시간이 길어질 수 있다. 반면에 명시적 링킹은 필요한 순간에
하나씩 DLL을 로딩할 수 있기 때문에 그만큼 실행까지 걸리는 시간이 짧고,
DLL 로딩에 걸리는 시간을 분산시킬 수 있다.

뭐 위와 같이 명확한 장점들이 있음에도 불구하고 암시적 링킹이 더 선호되는 경우가 있는데,
이는 사용하기 쉽기 때문이다. 코드가 간결해 진다는 것, 사용하기 쉽다는 것은
대부분의 경우에 있어서의 성능보다도 더 큰 장점을 지니는 것이 아닌가 생각해 본다.

* http://sweeper.egloos.com/1792751
*/




// implicit linking: *.lib 파일 사용하기
//#pragma comment (lib, "M32DLL.lib")
//int MyDLLSum(int a, int b);


// explicit linking: *.dll 파일 사용하기
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