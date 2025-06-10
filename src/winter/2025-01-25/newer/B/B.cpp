#include <bits/stdc++.h>
using namespace std;
using LL = long long;

constexpr int N = 8.64e4 + 5;

int    aVal[N];
int    bVal[N];
int    cVal[N];
double cOperatedVal[N];
double dp[N];  // 消耗了i天获取了val分

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, T;
    cin >> n >> T;
    for (int i = 1; i <= n; i++) {
        cin >> aVal[i] >> bVal[i] >> cVal[i];
    }

    LL sum_c = 0;
    for (int i = 1; i <= n; i++) {
        sum_c += cVal[i];
    }
    for (int i = 1; i <= n; i++) {
        cOperatedVal[i] = cVal[i] / (double)sum_c;
    }

    for (int i = 1; i <= n; i++) {  // 第i件物品
        queue<pair<int, int>> que;

        int numFull = 100 / bVal[i];

        int j_ = 1;
        for (; j_ << 1 <= numFull; j_ <<= 1) {
            que.emplace(aVal[i] * j_, bVal[i] * j_);
        }
        j_--;
        que.emplace(aVal[i] * (numFull - j_), bVal[i] * (numFull - j_));

        que.emplace(aVal[i], 100 % bVal[i]);
        while (!que.empty()) {
            auto queTop = que.front();
            que.pop();
            for (int j = T; j >= queTop.first; j--) {
                dp[j] = max(dp[j - queTop.first] + queTop.second * cOperatedVal[i], dp[j]);
            }
        }
    }
    printf("%.4lf", dp[T]);
    return 0;
}