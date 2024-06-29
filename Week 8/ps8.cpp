#include <iostream>
#include <limits.h>

using namespace std;

typedef int index;

int minmult(int n, const int d[], int P[][501]);
void order(index i, index j, const int P[][501]);

int main() {
    int n;
    cin >> n;

    int d[501];
    int P[501][501];

    for (int i = 0; i < n; ++i) {
        int rows, cols;
        cin >> rows >> cols;
        if (i == 0) {
            d[i] = rows;
        }
        d[i + 1] = cols;
    }
    int minCost = minmult(n, d, P);
    cout << minCost << endl;
    order(1, n, P);
    cout << endl;
    return 0;
}

int minmult(int n, const int d[], int P[][501]) {
    int M[501][501] = { 0 };

    for (int diagonal = 1; diagonal <= n - 1; ++diagonal) {
        for (int i = 1; i <= n - diagonal; ++i) {
            int j = i + diagonal;
            M[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; ++k) {
                int cost = M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j];
                if (cost < M[i][j]) {
                    M[i][j] = cost;
                    P[i][j] = k;
                }
            }
        }
    }
    return M[1][n];
}

void order(index i, index j, const int P[][501]) {
    if (i == j) {
        cout << "M" << i;
    }
    else {
        int k = P[i][j];
        cout << "(";
        order(i, k, P);
        cout << "*";
        order(k + 1, j, P);
        cout << ")";
    }
}
