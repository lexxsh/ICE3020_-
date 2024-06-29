#include<iostream>
#include<algorithm>

using namespace std;

struct node {
	char left;
	char right;
};
node K[26];

void preorder(char root);
void inorder(char root);
void lastorder(char root);
void print();

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		char A, B, C;
		cin >> A >> B >> C;
		K[A - 'A'].left = B;
		K[A - 'A'].right = C;
	}
	print();
}

void print() {
	preorder('A');
	cout << "\n";
	inorder('A');
	cout << "\n";
	lastorder('A');
	cout << "\n";
}
void preorder(char root) {
	if (root != '.') {
		cout << root;
		preorder(K[root - 'A'].left);
		preorder(K[root - 'A'].right);
	}
}

void inorder(char root) {
	if (root != '.') {
		inorder(K[root - 'A'].left);
		cout << root;
		inorder(K[root - 'A'].right);
	}
}
void lastorder(char root) {
	if (root != '.') {
		lastorder(K[root - 'A'].left);
		lastorder(K[root - 'A'].right);
		cout << root;
	}
}
