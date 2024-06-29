#include<iostream>
using namespace std;

int answer = 0;
void heapify(int A[],int k, int n, int K) {
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
		swap(A[k], A[smaller]);
		answer++;
		if (answer == K) {
			cout << A[k] << " " << A[smaller] << endl;
			for (int i = 1; i <= n; i++) {
				cout << A[i] << " ";
			}
			cout << endl;
		}
		heapify(A, smaller, n ,K);
	}
}
void build_min_heap(int A[], int n,int K) {
	for (int i = n / 2; i >= 1; i--) {
		heapify(A, i, n,K);
	}
}
void heap_sort(int A[], int n,int K) {
	build_min_heap(A, n,K);
	for (int i = n; i >= 2; i--) {
		swap(A[1], A[i]);
		answer++;
		if (answer == K) {
			cout << A[1] << " " << A[i] << endl;
			for (int i = 1; i <= n; i++) {
				cout << A[i] << " ";
			}
			cout << endl;
		}
		heapify(A, 1, i - 1,K);
	}
}
int main() {
	int N,K;
	cin >> N;
	cin >> K;
	int* A = new int[N+1];
	for (int i = 1; i <= N; i++) {
		cin >> A[i];
	}
	heap_sort(A, N,K);
	if (answer < K) {
		cout << -1;
	}
	return 0;
}