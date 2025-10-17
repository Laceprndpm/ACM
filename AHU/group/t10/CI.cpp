#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

inline i64 work(i64 x, i64 k) noexcept
{
    if (k == 1) return x - 1;
    i64 num = 0;
    while (x > 1) {
        i64 d      = (x - 1) / k + 1;
        i64 nxtd   = d - 1;
        i64 nxtn   = nxtd ? nxtd * k : 1;
        i64 remain = x - nxtn;
        i64 times  = (remain - 1) / d + 1;
        num += times;
        x -= times * d;
    }
    return num;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        i64 n, k;
        cin >> n >> k;

        i64 num = work(n, k);
        i64 l = n - n / k, r = n;
        while (l < r) {
            i64 mid = (l + r) >> 1;
            (work(mid, k) >= num ? r = mid : l = mid + 1);
        }
        cout << r << '\n';
    }
}
