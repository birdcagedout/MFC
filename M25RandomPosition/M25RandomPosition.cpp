// Snake Game 개선판에서 사용되는 랜덤 먹이 위치 결정하기
// 가로 80, 세로 60개의 길이 480인 배열에서 
// 랜덤으로 300개의 먹이의 위치를 결정하기

#include <iostream>

int main()
{
	// 길이 480인 배열에 순서대로 0 ~ 479까지 초기화
	int arr[480];
	for (int i = 0; i < 480; i++) {
		arr[i] = i;
	}

	srand((unsigned int)time(NULL));

	// 처음부터 끝까지 배열값 1개당 랜덤찍은 1개와 쌍으로 맞바꾸기
	for (int j = 0; j < 480; j++) {
		int second = rand() % 480;
		
		int temp = arr[second];
		arr[second] = arr[j];
		arr[j] = temp;
	}

	// 무작위 2개 찍어서 맞바꾸기
	for (int k = 0; k < 4800; k++) {
		int first = rand() % 480;
		int second = rand() % 480;

		int temp = arr[second];
		arr[second] = arr[first];
		arr[first] = temp;
	}

	// 출력하기
	for (int l = 0; l < 300; l++) {
		printf("%3d ", arr[l]);
		if (l % 10 == 9) {
			std::cout << std::endl;
		}
	}
}
