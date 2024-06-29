#include <iostream>
using namespace std;


int findmin(int a, int b) {
    if (a > b)
        return b;
    else
        return a;
}
void change(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
int main(void)
{
    int a[11][11] = { 0 };
    int b[11][11] = { 0 };
    int c[11][11] = { 0 };
    int i, j, k, o, n, num, ans = 1e9;
    cin >> n;
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= i; j++)
        {
            cin >> a[i][j];
        }
    }
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= i; j++)
        {
            cin >> b[i][j];
        }
    }
    for (i = 1; i <= 2; i++)
    {
        for (j = 1; j <= 3; j++)
        {
            num = 0;
            for (k = 1; k <= n; k++)
            {
                for (o = 1; o <= k; o++)
                {
                    if (a[k][o] != b[k][o])
                        num++;
                }
            }
            ans = findmin(ans, num);
            for (k = 1; k <= n; k++)
            {
                for (o = 1; o <= n; o++)
                {
                    c[k][o] = a[n + 1 - o][k];
                }
            }
            for (o = 1; o <= n; o++)
            {
                for (k = n; k >= o; k--)
                {
                    c[k][o] = c[k - o + 1][o];
                }
                for (k; k >= 1; k--)
                {
                    c[k][o] = 0;
                }
            }

            for (k = 1; k <= n; k++)
                for (o = 1; o <= k; o++)
                    a[k][o] = c[k][o];
        }
        for (k = 1; k <= n; k++)
            for (o = 1; o <= k / 2; o++)
                change(&a[k][o], &a[k][k - o + 1]);
    }
    cout << ans;
}