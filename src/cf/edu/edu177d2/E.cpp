#include <bits/stdc++.h>
using namespace std;
map<long long, long long> mp[130];
long long                 val[31];

long long solve(long long n, long long k)
{
    if (k >= 130 || k <= 0 || n == 0) return 0;
    if (mp[k].find(n) != mp[k].end()) return mp[k][n];
    long long i, ans = 0, c;
    for (i = 30; val[i] > n; i--)
        ;
    c = val[i]; // 选择c
    for (i = 0; i <= n; i += c) { // 选择先来i/c个
        if (i + c <= n)
            ans += solve(c - 1, k - i / c);
        else
            ans += solve(n % c, k - i / c);
        if (k - i / c == 0) ans++;
    }
    mp[k][n] = ans;
    return ans;
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int       T;
    long long l, r, k, i;
    val[0] = 1;
    for (i = 1; i < 31; i++)
        val[i] = val[i - 1] * 4 + 1;
    for (cin >> T; T > 0; T--) {
        cin >> l >> r >> k;
        cout << solve(r, k) - solve(l - 1, k) << '\n';
    }
    return 0;
}

