#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int distance = 0;
    while (n > 4) {
        distance += 2;
        n = (n + 1) / 2;
    }

    if (n == 3)
        cout << distance << endl;
    else if (n == 4)
        cout << distance + 1 << endl;

    return 0;
}
