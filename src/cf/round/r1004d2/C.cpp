#include <bits/stdc++.h>
using namespace std;
using LL  = long long;
using PII = pair<LL, LL>;
int ans;

bool check(LL x)
{
    while (x > 0) {
        if (x % 10 == 7)
            return true;
        x /= 10;
    }
    return false;
}

void BFS(const LL x)
{
    // queue<PII> Q;  // depth, and num
    // Q.emplace(0, x);
    // while (!Q.empty()) {
    //     auto cur = Q.front();
    //     Q.pop();
    //     if (check(cur.second)) {
    //         ans = cur.first;
    //         return;
    //     }
    //     for (LL i = 9; i <= cur.second * 10; i = i * 10 + 9) {
    //         Q.emplace(cur.first + 1, cur.second + i);
    //     }
    // }
    ans          = INT32_MAX;
    int length_x = 0;
    int temp     = x;
    while (temp > 0) {
        temp /= 10;
        length_x++;
    }
    for (LL i = 9; i <= x * 10; i = i * 10 + 9) {
        for (int j = 0; j < 10; j++) {
            if (check(x + i * j)) {
                ans = min(j, ans);
                break;
            }
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int x;
        cin >> x;
        BFS(x);
        cout << ans << '\n';
    }
    return 0;
}