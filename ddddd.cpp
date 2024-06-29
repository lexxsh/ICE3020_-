#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

struct Save {
    long long M, P, R;
    double pivot;
};

int N, T;
Save save[51];
long long dp[51][100001];

long long solve(int idx, long long time) {
    if (idx == N)
        return 0;

    long long& ret = dp[idx][time];
    if (ret != -1)
        return ret;

    ret = 0;
    if (idx + 1 <= N && time + save[idx].R <= T)
        ret = max(ret, solve(idx + 1, time + save[idx].R) + save[idx].M - (time + save[idx].R) * save[idx].P);
    if (idx + 1 <= N)
        ret = max(ret, solve(idx + 1, time));

    return ret;
}

int main() {
    memset(dp, -1, sizeof dp);
    cin >> N >> T;
    for (int n = 0; n < N; n++)
        cin >> save[n].M;
    for (int n = 0; n < N; n++)
        cin >> save[n].P;
    for (int n = 0; n < N; n++)
        cin >> save[n].R;
    for (int n = 0; n < N; n++)
        save[n].pivot = save[n].R / (double)save[n].P;

    sort(save, save + N, [](Save const& a, Save const& b) -> bool {
        return a.pivot < b.pivot;
        });

    cout << solve(0, 0) << endl;
    return 0;
}
