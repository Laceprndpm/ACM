#include <bits/stdc++.h>

#include <array>
#include <vector>
using namespace std;
using i64         = long long;
constexpr i64 INF = 1e9;
vector<int>   prime, minp;

void sieve(int n = 1e6)
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

int main()
{
    sieve();
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    if (n == 2) {
        if (minp[a[1] + a[2]]) {
            cout << 0 << '\n';
        } else
            cout << 1 << '\n';
        return 0;
    }
    vector<int> dp(n + 2, INF);
    dp[2] = 0;
    for (int i = 2; i <= n - 1; i++) {
        if (a[i - 1] % 2 == a[i + 1] % 2) {
            if (minp[a[i - 1] + a[i]] && minp[a[i] + a[i + 1]]) {
                dp[i + 1] = min(dp[i + 2], dp[i]);
            } else {
                dp[i + 1] = min(dp[i + 2], dp[i] + 1);
            }
            i += 2;
        } else {
            if
        }
    }
}