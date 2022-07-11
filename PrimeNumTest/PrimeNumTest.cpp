// PrimeNumTest.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

bool IsPrimeNumber(int num)
{
	if (num < 2) {
		return false;
	}

	for (int i = 2; i < num; i++) {
		if (num % i == 0) {
			return false;
		}
	}
	return true;
}


int main()
{
	long long int count = 0;				// 최소 64bit int(표준) cf. MS에서 __int64와 같음
	long long int arr[20000] = { 0, };
	int arrIndex = 0;

	for (int i = 2; i < 200000; i++) {

		if (IsPrimeNumber(i) == true) {
			count++;
			arr[arrIndex++] = i;
		}
	}

	wprintf_s(L"Total count of the prime numbers: %lld\n", count);

	for (int j = 0; j < arrIndex; j++) {
		wprintf_s(L"%lld, ", arr[j]);
	}
}
