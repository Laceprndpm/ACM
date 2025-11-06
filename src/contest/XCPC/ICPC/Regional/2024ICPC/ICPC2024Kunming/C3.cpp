#include <bits/stdc++.h>
using namespace std;
using u64  = unsigned long long;
using u128 = unsigned __int128;

constexpr int INV_SIZE = 1 << 19;
u64           invs[INV_SIZE];  // invs[i] = floor(2^64 / i)

inline void init_invs()
{
    for (int i = 1; i < INV_SIZE; ++i) invs[i] = (u64)((u128(1) << 64) / (u128)i);
}

// 快速除法，确保与 a / b 完全等价
inline u64 udiv_fast(u64 a, u64 b)
{
    if (b < INV_SIZE) {
        u64 m = invs[b];
        u64 q = (u64)((u128)a * (u128)m >> 64);
        if ((u128)q * b > a) --q;
        if ((u128)(q + 1) * b <= a) ++q;
        return q;
    } else {
        return a / b;
    }
}

u64 n, k;

u64 work(u64 x)
{
    u64 num = 0;
    while (x != 1) {
        u64  d      = udiv_fast(x - 1, k) + 1;
        u64  nxtd   = d - 1;
        u128 tmp    = (u128)nxtd * (u128)k;
        u64  nxtn   = tmp > 0 ? (u64)tmp : 1ull;
        u64  remain = x - nxtn;
        u64  times  = udiv_fast(remain - 1, d) + 1;
        if (times < 1) times = 1;
        num += times;
        x -= times * d;
    }
    return num;
}

void solve()
{
    cin >> n >> k;
    init_invs();

    u64 num = work(n);
    u64 l = 1, r = n;
    u64 ans = -1;

    while (l <= r) {
        u64 mid = (l + r) >> 1;
        u64 val = work(mid);
        if (val == num) {
            ans = mid;
            r   = mid - 1;
        } else if (val > num)
            r = mid - 1;
        else
            l = mid + 1;
    }
    cout << ans << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) solve();
}
