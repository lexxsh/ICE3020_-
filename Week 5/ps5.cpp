#include<iostream>
using namespace std;

void heapify(int A[], int k,int n, int& cnt,int K ) {
	int left = 2 * k;
	int right = 2 * k + 1;
	int smaller = k;

	if (right <= n) {
		if (A[left] < A[right]) {
			smaller = left;
		}
		else {
			smaller = right;
		}
	}
	else if (left <= n) {
		smaller = left;
	}
	else
		return;
	if (A[smaller] < A[k]) {
		if (cnt < K) {
			swap(A[k], A[smaller]);
			heapify(A, smaller, n);
		}
		else {
			if (cnt == K) {
				cout << A[k] << " " << A[smaller] << endl;
			}
			return;
		}
		heapify(A, smaller, n, cnt, K);
	}
}
void build_min_heap(int A[], int n) {
	for (int i = n / 2; i >= 1; i--) {
		heapify(A, i, n);
	}
}
void heap_sort(int A[], int n,int& cnt,int K) {
	build_min_heap(A, n);
	for (int i = n; i >= 2; i--) {
		if (cnt < K){
			swap(A[1], A[i]);
			heapify(A, 1, i - 1);
		}
		else {
			if (cnt == K) {
				cout << A[1] << " " << A[i] << endl;
				cout << "A " << K << "S " << endl;
				for (int j = 1; j < = n; j++) {
					cout << A[j] << " ";
				}
				cout << endl;
			}
			return;
		}
		heapify(A, 1, i - 1, cnt, K);
	}
}
int main() {
	int N, K;
	cin >> N;
	cin >> K;
	int* A = new int[N + 1];
	for (int i = 1; i <= N; i++) {
		cin >> A[i];
	}
	int cnt  0;
	heap_sort(A, N, cnt, K);
	if (cnt < K) {
		cout << -1 << endl;
	}
	delete[] A;
	return 0;
}