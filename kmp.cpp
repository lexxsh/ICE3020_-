#include<iostream>
#include<algorithm>
#include<string>
#include<vector>

using namespace std;


vector<int>initNext(string p) {
	int m = p.length();
	vector<int>next(m);
	for (int i = 1, j = 0; i < m; i++) {
		while (j > 0 && p[i] != p[j]) j = next[j - 1];
		if (p[i] == p[j]) next[i] = ++j;
	}
	return next;
}

vector<int>kmp(string text, string p) {
	vector<int>next = initNext(p);
	int m = p.length();
	int n = text.length();
	vector<int>num;
	for (int i = 0, j = 0; i < n; i++) {
		while (j > 0 && text[i] != p[j]) j = next[j - 1];
		if (text[i] == p[j]) {
			if (j == m - 1) {
				num.push_back(i - j);
				j = next[j];
			}
			else j++;
		}
	}
	return num;
}


int main() {
	string A, B;
	cin >> A >> B;
	vector<int>Position = kmp(A, B);
	cout << Position.size() << endl;
	for (int i = 0; i < Position.size(); i++) {
		cout << Position[i] + 1;
		cout << " ";
	}

}