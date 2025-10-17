#include <bits/stdc++.h>

#include <algorithm>
#include <array>
#include <vector>
using namespace std;
using i64         = long long;
constexpr i64 INF = 1e9;
vector<int>   prime, minp;
#define bg(x)  begin(x)
#define all(x) bg(x), end(x)

void sieve(int n = 3e5)
{
    minp.resize(n + 1);
    for (int i = 2; i <= n; i++) {
        if (!minp[i]) {
            minp[i] = i;
            prime.push_back(i);
        }
        for (auto j : prime) {
            if (j > minp[i] || j > n / i) break;
            minp[i * j] = j;
        }
    }
}

bool isprime(int n) { return minp[n] == n; }

void relax(int& a, int b) { a = min(a, b); }

int main()
{
    sieve();
    // map<int, int> mp;
    // for (int i : prime) {
    //     mp[i]++;
    // }
    // cout << prime.size() << '\n';
    // for (auto x : prime) {
    //     if (x > 100 && mp.count(x + 2)) {
    //         cout << "XXX" << ' ';
    //         break;
    //     }
    // }
    int n;
    cin >> n;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    vector<array<int, 4>> dp(n + 1, {INF, INF, INF, INF});
    // 0是偶数
    // 1是奇数
    // 2是1
    // 3是raw
    if (arr[1] != 1) {
        dp[1][2] = 1;
    } else {
        dp[1][2] = 0;
    }
    dp[1][0] = 1, dp[1][1] = 1, dp[1][3] = 0;
    for (int i = 2; i <= n; i++) {
        int raw = arr[i - 1] + arr[i];
        if (isprime(raw)) {
            relax(dp[i][3], dp[i - 1][3]);
        }
        if (arr[i] % 2 == 0) {
            relax(dp[i][3], dp[i - 1][1]);
        } else {
            relax(dp[i][3], dp[i - 1][0]);
        }
        if (isprime(arr[i] + 1)) {
            relax(dp[i][3], dp[i - 1][2]);
        }
        if (arr[i] != 1) {
            relax(dp[i][2], dp[i - 1][0] + 1);
            relax(dp[i][2], dp[i - 1][2] + 1);
            if (isprime(arr[i - 1] + 1)) {
                relax(dp[i][2], dp[i - 1][3] + 1);
            }
        } else {
            relax(dp[i][2], dp[i - 1][0]);
            relax(dp[i][2], dp[i - 1][2]);
            if (isprime(arr[i - 1] + 1)) {
                relax(dp[i][2], dp[i - 1][3]);
            }
        }
        if (arr[i - 1] % 2 == 0) {
            relax(dp[i][1], dp[i - 1][3] + 1);
        } else {
            relax(dp[i][0], dp[i - 1][3] + 1);
        }
        relax(dp[i][1], dp[i - 1][0] + 1);

        relax(dp[i][0], dp[i - 1][2] + 1);
        relax(dp[i][0], dp[i - 1][1] + 1);
    }
    cout << *min_element(all(dp[n])) << '\n';
    // for (int i = 1; i <= n; i++) {
    //     for (int j = 0; j < 4; j++) {
    //         cout << dp[i][j] << ' ';
    //     }
    //     cout << '\n';
    // }
}