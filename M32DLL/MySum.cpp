/*
DLL은 변수, 함수, C++ 클래스를 다른 모듈에 export 할 수 있다.

하지만, 코드의 계층적 추상화를 유지하고 DLL 코드를 좀 더 쉽게 유지 / 관리하기 위해
변수는 가급적 익스포트 하지 않는 것이 좋다.

또한, C++ 클래스는 export 한 C++ 클래스를 사용하는 모듈을
동일한 회사의 컴파일러를 사용하는 컴파일한 경우에만 사용할 수 있으므로 주의하도록 하자.

DLL을 작성할 때 export 하고자 하는 변수나 함수를 포함하고 있는 헤더 파일을 먼저 작성하는 것이 좋다.
이러한 헤더 파일에는 export 할 함수나 변수가 사용하는 심벌이나 데이터 구조체도 반드시 정의되어 있어야 한다.

이 헤더는 DLL과 함께 배포되어야 하며, 이 DLL을 사용하는 모듈은 이 헤더를 반드시 인클루드 해야 한다.

또한, 유지보수의 편의성을 위해 DLL 하나당 헤더 파일 1개씩 페어로 작성하는 것이 좋다.

출처 : http://egloos.zum.com/sweeper/v/2991664
*/



#include "pch.h"

#define DllExport   __declspec( dllexport )

// 1. 모듈 외부에서 사용할 수 있도록: __declspec(dllexport)
// 2. DLL파일을 이용하여 외부에서 사용할 수 있도록 함수 이름을 고정시킴: extern "C"

extern "C" DllExport int MyDLLSum(int a, int b)
{
	return a + b;
}
