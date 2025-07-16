#include <array>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>
using namespace std;
using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;

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

constexpr int INF            = 1e9;
constexpr int prime_mods[10] = {1000000007, 1000000009, 1000000021, 1000000033, 1000000087};

i64 qpow(i64 n, i64 q, i64 mod)
{
    if (q == 0) {
        return 1;
    }
    i64 ans = 1;
    while (q > 0) {
        if (q & 1) {
            ans *= n;
            ans %= mod;
        }
        n *= n;
        n %= mod;
        q >>= 1;
    }
    return ans;
}

std::array<int, 3> get_three_distinct_mods()
{
    static std::mt19937 rng(time(0));
    std::array<int, 10> indices;
    std::iota(indices.begin(), indices.end(), 0);  // 0~9
    std::shuffle(indices.begin(), indices.end(), rng);
    return {prime_mods[indices[0]], prime_mods[indices[1]], prime_mods[indices[2]]};
}

struct S {
    vector<array<i64, 26>> arr;
    i64                    MOD;
    vector<i64>            inv;

    S() {}

    void init(string s, i64 MOD_)
    {
        MOD = MOD_;
        arr.eb(array<i64, 26>{0});
        i64 base = 4;
        for (char c : s) {
            auto tmp = arr.bk;
            base *= 2;
            base %= MOD;
            tmp[c - 'a'] = (tmp[c - 'a'] + base) % MOD;
            arr.pb(tmp);
        }

        inv.eb(qpow(2ll, MOD - 2, MOD));
        for (int i = 0; i < sz(s); i++) {
            inv.eb(inv.bk * inv[0] % MOD);
        }
    }

    auto get_seg(int l, int r)
    {
        auto r_arr = arr[r], &l_arr = arr[l];
        for (int i = 0; i < 26; i++) {
            r_arr[i] -= l_arr[i];
            r_arr[i] = (r_arr[i] + MOD) % MOD;
            r_arr[i] *= inv[l];
            r_arr[i] = (r_arr[i] + MOD) % MOD;
        }
        return r_arr;
    }
};

void solve() {}

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    auto      mods = get_three_distinct_mods();
    vector<S> sarr(3);
    int       n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    for (int i = 0; i < 3; i++) {
        sarr[i].init(s, mods[i]);
    }
    for (int i = 0; i < m; i++) {
        int x1, y1, len;
        cin >> x1 >> y1 >> len;
        x1--, y1--;
        int  x2 = x1 + len, y2 = y1 + len;
        bool ok = 1;
        for (int i = 0; i < 3; i++) {
            auto res1 = sarr[i].get_seg(x1, x2);
            auto res2 = sarr[i].get_seg(y1, y2);
            sor(res1), sor(res2);
            if (res1 != res2) {
                ok = 0;
            }
        }
        if (ok) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
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