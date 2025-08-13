#include <bits/stdc++.h>

using namespace std;
using i8 = signed char;
using u8 = unsigned char;

using i16 = short;
using u16 = unsigned short;

using i64 = long long;
using u64 = unsigned long long;

using i128 = __int128_t;
using u128 = __uint128_t;
#pragma GCC optimize("O2,unroll-loops")
#define pii pair<int, int>
const int  N   = 1e5;
const int  M   = 1e6;
const int  INF = 1e9;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());  // 64位哈希种子
const int  digit[10] = {0b1111110, 0b0110000, 0b1101101, 0b1111001, 0b0110011,
                        0b1011011, 0b1011111, 0b1110000, 0b1111111, 0b1111011};
static int vis[1 << 21];
static int tin = 0;

int next_comb(int x)
{
    int c = x & -x;
    int r = x + c;
    return (((r ^ x) >> 2) / c) | r;
}

bool cal(int mask, const vector<int>& a)
{
    if (++tin == INT_MAX) {
        memset(vis, 0, sizeof(vis));
        tin = 0;
    }
    int  tag = tin++;
    bool ok  = true;
    for (auto d : a) {
        int p = d & mask;
        if (vis[p] == tag) {
            return false;
        }
        vis[p] = tag;
    }
    return true;
}

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> arr;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int mask = 0;
        for (int pos = 0; pos < m; pos++) {
            int d = s[m - 1 - pos] - '0';
            mask |= digit[d] << (7 * pos);
        }
        arr.push_back(mask);
    }
    if (n == 1) {
        cout << "0\n";
        return;
    }
    int tot = 7 * m;
    int k0  = (int)ceil(log2(n));
    for (int k = max(1, k0); k <= tot; k++) {
        int comb = (1 << k) - 1;
        for (; comb < (1 << tot); comb = next_comb(comb)) {
            if (cal(comb, arr)) {
                cout << k << '\n';
                return;
            }
        }
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
}