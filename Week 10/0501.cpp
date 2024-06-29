#include<iostream>

using namespace std;


int main() {
	int t;
	int n;
	int fibonacci[42][2];
	fibonacci[0][0] = 1;
	fibonacci[0][1] = 0;
	fibonacci[1][0] = 0;
	fibonacci[1][1] = 1;
	for (int i = 2; i < 42; i++) {
		fibonacci[i][0] = fibonacci[i - 1][0] + fibonacci[i - 2][0];
		fibonacci[i][1] = fibonacci[i - 1][1] + fibonacci[i - 2][1];
	}
	int k = 0;
	cin >> k;
	for (int i = 0; i < k; i++) {
		int num;
		cin >> num;
		cout << fibonacci[num][0] << " " << fibonacci[num][1] << endl;
	}
}