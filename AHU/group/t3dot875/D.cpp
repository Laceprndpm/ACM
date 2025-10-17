#include <bits/stdc++.h>

#include <unordered_map>
#include <vector>
using namespace std;
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
#define pii pair<int, int>
constexpr int MOD1 = 1e9 + 7;
constexpr int MOD2 = 998244353;
constexpr int base = 114514;

template <int MOD>
constexpr int power(int a, u64 b, int res = 1)
{
    for (; b != 0; b /= 2, a = (1ll * a * a) % MOD) {
        if (b & 1) {
            res = (1ll * res * a) % MOD;
        }
    }
    return res;
}

int POWM1[5010];
int POWM2[5010];

int POWinvM1[5010];
int POWinvM2[5010];

i64 totalans  = 0;
i64 singleans = 0;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <iostream>
using namespace __gnu_pbds;
const u64 RANDOM = time(NULL);

struct MyHash {
    int operator()(u64 x) const { return x ^ RANDOM; }
};

unordered_map<u64, int, MyHash> cnt;

void solve(string s, string t)
{
    int n = s.size();
    int m = t.size();
    s     = '@' + s;
    t     = '@' + t;

    vector<vector<int>> lcs(n + 2, vector<int>(m + 2));
    vector<vector<int>> lcp(n + 1, vector<int>(n + 2));
    vector<vector<int>> dp = vector<vector<int>>(n + 1, vector<int>(n + 2));

    for (int l = 1; l <= n; l++) {
        for (int r = l + 1; r <= n; r++) {
            if (s[l] != s[r]) continue;
            int curlen = 0;
            lcp[l][r]  = lcp[l - 1][r - 1] + 1;
            curlen     = lcp[l][r];
            dp[l + 1][r - curlen]++;
            dp[l + 1][r]--;
        }
    }
    for (int l = n; l >= 1; l--) {
        for (int r = m; r >= 1; r--) {
            if (s[l] != t[r]) continue;
            lcs[l][r] = lcs[l + 1][r + 1] + 1;
        }
    }
    i64 ans = 0;
    i64 sng = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] += dp[i][j - 1];
        }
        vector<int> appearcnt(n + 1);
        for (int j = 1; j <= m; j++) {
            int curlen = lcs[i][j];
            appearcnt[curlen]--;
            appearcnt[0]++;
        }
        for (int i = 1; i <= n; i++) {
            appearcnt[i] += appearcnt[i - 1];
        }
        for (int j = i; j <= n; j++) {
            int weight = dp[i][j];
            ans += (weight)*appearcnt[j - i];
            sng += appearcnt[j - i];
        }
    }
    singleans = sng;
    totalans += ans;
}

void Solve()
{
    string a, b;
    cin >> a >> b;
    int big = max(a.size(), b.size());
    cnt.reserve(big * big);
    solve(a, b);
    cnt.clear();
    solve(b, a);
    cout << totalans + singleans << '\n';
}

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _ = 1;
    while (_--) Solve();
}