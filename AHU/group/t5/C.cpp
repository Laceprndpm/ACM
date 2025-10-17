#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>

using namespace std;
using ll   = long long;
using u8   = uint8_t;
using u16  = uint16_t;
using u32  = uint32_t;
using i64  = long long;
using u64  = uint64_t;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

// vectors
#define sz(x)   int(size(x))
#define bg(x)   begin(x)
#define all(x)  bg(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define sor(x)  sort(all(x))
#define rsz     resize
#define ins     insert
#define pb      push_back
#define eb      emplace_back
#define ft      front()
#define bk      back()
#define mt      make_tuple
#define fi      first
#define se      second

struct Basis {
    bool flag;  // 可以表示0

    static constexpr int MN = 60;

    u64 basis_arr[MN + 1];
    u64 tmp[MN + 1];
    int rk;

    Basis() : rk(0) { init(); }

    void init()
    {
        memset(basis_arr, 0, sizeof(basis_arr));
        flag = 0;
    }

    void retreat(int idx) { basis_arr[idx] = 0; }

    int insert(u64 x)
    {
        for (int i = MN; i >= 0; i--)
            if (x & (1ull << i)) {
                if (!basis_arr[i]) {
                    basis_arr[i] = x;
                    rk++;
                    return i;
                } else {
                    x ^= basis_arr[i];
                }
            }
        flag = true;
        return -1;
    }

    bool check(u64 x)
    {
        for (int i = MN; i >= 0; i--)
            if (x & (1ull << i)) {
                if (!basis_arr[i])
                    return false;
                else
                    x ^= basis_arr[i];
            }
        return true;
    }

    u64 qmax(u64 res = 0)
    {
        for (int i = MN; i >= 0; i--) res = max<u64>(res, res ^ basis_arr[i]);
        return res;
    }

    u64 qmin(u64 res = 0)
    {
        if (flag) return 0;
        for (int i = 0; i <= MN; i++)
            if (basis_arr[i]) return basis_arr[i];
        assert(0);
    }

    // -1ull为无值
    u64 query(u64 k)
    {
        u64 res = 0;
        int cnt = 0;
        k -= flag;
        if (!k) return 0;
        for (int i = 0; i <= MN; i++) {
            for (int j = i - 1; j >= 0; j--)
                if (basis_arr[i] & (1ull << j)) basis_arr[i] ^= basis_arr[j];
            if (basis_arr[i]) tmp[cnt++] = basis_arr[i];
        }
        if (k >= (1ull << cnt)) return -1ull;
        for (int i = 0; i < cnt; i++)
            if (k & (1ull << i)) res ^= tmp[i];
        return res;
    }
};

constexpr int MAXN = 2e5;
int           POW2[MAXN + 50];
constexpr int P = 998244353;
vector<int>   DIV[MAXN + 50];
array<int, 2> cnt[MAXN + 50];

void maininit()
{
    POW2[0] = 1;
    for (int i = 1; i <= MAXN; i++) {
        POW2[i] = POW2[i - 1] * 2ll % P;
    }
    for (int i = 1; i <= MAXN; i++) {
        for (int j = 2; j * i <= MAXN; j++) {
            DIV[i * j].pb(i);
        }
    }
    memset(cnt, 0x7f, sizeof cnt);
};

int t;

void solve()
{
    int n;
    cin >> n;
    Basis       total;
    i64         ans = 0;
    vector<int> ai(n);
    for (int& i : ai) {
        cin >> i;
        if (cnt[i][0] != t) {
            cnt[i][0] = t;
            cnt[i][1] = 0;
        }
        cnt[i][1]++;
        total.ins(i);
    }
    ans = POW2[n - total.rk];

    vector<int> lihua = ai;
    sor(lihua);
    lihua.erase(unique(all(lihua)), lihua.end());
    for (int i = 0; i < lihua.size(); i++) {
        int   val = lihua[i];
        Basis bias;
        i64   num = 0;
        for (int factor : DIV[val]) {
            if (cnt[factor][0] == t) {
                bias.ins(factor);
                num += cnt[factor][1];
            }
        }
        ans += 1ll * POW2[num - bias.rk] * (POW2[cnt[val][1] - 1]) % P;
        ans %= P;
    }
    cout << ans - 1 << '\n';
}

signed main(signed argc, char** argv)
{
    maininit();
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */