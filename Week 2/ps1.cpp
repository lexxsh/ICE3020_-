#include <iostream>
using namespace std;
// ���� �Լ�
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
	cin >> n; // ù ��° �ٿ��� n �� �Է¹���
	int* numbers = new int[n]; // �������� ���� �迭�� �Ҵ�
	// �� ��° �ٿ��� n ���� ������ �Է¹���
	for (int i = 0; i < n; i++) {
		cin >> numbers[i];
	}
	for (int i = 0; i < n; i++) {
		cout << numbers[i] << " ";
	}
	// ���� ���� ����
	MySort(numbers, n);
	// ���ĵ� �迭 ���
	for (int i = 0; i < n; i++) {
		cout << numbers[i] << " ";
	}
	return 0;
}