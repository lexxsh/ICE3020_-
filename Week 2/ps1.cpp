#include <iostream>
using namespace std;
// 정렬 함수
void MySort(int arr[], int n) {
	int i, j, temp;
	for (i = n - 1; i > 0; i--) {
		for (j = 0; j < i; j++) {
			if (list[j] < list[j + 1]) {
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}
}
int main() {
	int n;
	cin >> n; // 첫 번째 줄에서 n 을 입력받음
	int* numbers = new int[n]; // 동적으로 정수 배열을 할당
	// 두 번째 줄에서 n 개의 정수를 입력받음
	for (int i = 0; i < n; i++) {
		cin >> numbers[i];
	}
	for (int i = 0; i < n; i++) {
		cout << numbers[i] << " ";
	}
	// 버블 정렬 수행
	MySort(numbers, n);
	// 정렬된 배열 출력
	for (int i = 0; i < n; i++) {
		cout << numbers[i] << " ";
	}
	return 0;
}