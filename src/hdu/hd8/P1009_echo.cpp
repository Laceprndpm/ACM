#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
#define int long long
#define inf (int)1e18
#define pii pair<int, int>
using i128 = __int128;

std::ostream &operator<<(std::ostream &os, i128 n)
{
    if (n == 0) {
        return os << 0;
    }
    std::string s;
    while (n > 0) {
        s += char('0' + n % 10);
        n /= 10;
    }
    std::reverse(s.begin(), s.end());
    return os << s;
}

i128 toi128(const std::string &s)
{
    i128 n = 0;
    for (auto c : s) {
        n = n * 10 + (c - '0');
    }
    return n;
}

i128 sqrti128(i128 n)
{
    i128 lo = 0, hi = 1E16;
    while (lo < hi) {
        i128 x = (lo + hi + 1) / 2;
        if (x * x <= n) {
            lo = x;
        } else {
            hi = x - 1;
        }
    }
    return lo;
}

i128 gcd(i128 a, i128 b)
{
    while (b) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

void Echo2()
{
    int n, w;
    cin >> n >> w;
    int  round  = 0;
    int  person = 0;
    int  tmp    = n;
    i128 ans    = 0;
    while (tmp >= w) {
        i128 cut    = tmp / w;
        i128 edline = cut * w;
        i128 t      = (tmp - edline) / cut + 1;
        ans += round * (2 * person * cut * t + t * t * cut * cut + cut * t) / 2;
        ans += (2 * person * cut * t * (t + 1) / 2 + 2 * cut * cut * t * (t + 1) * (2 * t + 1) / 6
                - cut * cut * t * (t + 1) / 2 + cut * t * (t + 1) / 2)
               / 2;
        round += t;
        person += t * cut;
        tmp = n - person;
        // cout << ans << ' ';
    }
    // cout << person << ' ';
    ans += (i128)(n + person + 1) * tmp / 2 * (round + 1);
    cout << ans << '\n';
}

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _;
    cin >> _;
    while (_--) Echo2();
}