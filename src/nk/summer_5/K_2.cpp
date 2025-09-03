#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#define endl '\n'
#define ios  ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr)
using namespace std;
typedef long long LL;

const int N   = 2e5 + 10;
const int M   = 22;
const int MOD = 998244353;

int                    n, m, k;
vector<pair<int, int>> g[N];
int                    sm[N];
int                    fa[N][20], dep[N];
int                    msk[N];

LL cnt[1 << M];
LL sos[1 << M];
LL fact[N], infact[N];

LL qmi(LL a, LL b)
{
    LL res = 1;
    while (b) {
        if (b & 1) res = (LL)res * a % MOD;
        a = (LL)a * a % MOD;
        b >>= 1;
    }
    return res;
}

LL inv(LL a)
{
    return qmi(a, MOD - 2);
}

void init(int max_val)
{
    fact[0]   = 1;
    infact[0] = 1;
    for (int i = 1; i <= max_val; i++) {
        fact[i]   = (fact[i - 1] * i) % MOD;
        infact[i] = inv(fact[i]);
    }
}

LL C(int n, int k)
{
    if (k < 0 || k > n) return 0;
    return fact[n] * infact[k] % MOD * infact[n - k] % MOD;
}

void dfs_lca(int u, int p, int d, int msks)
{
    dep[u]   = d;
    fa[u][0] = p;
    msk[u]   = msks;
    for (auto& e : g[u]) {
        int v   = e.first;
        int idx = e.second;
        if (v == p) continue;
        int nxt = msks;
        if (sm[idx] != -1) {
            nxt ^= (1 << sm[idx]);
        }
        dfs_lca(v, u, d + 1, nxt);
    }
}

void build()
{
    memset(fa, 0, sizeof(fa));
    memset(dep, 0, sizeof(dep));
    memset(msk, 0, sizeof(msk));
    dfs_lca(1, 0, 1, 0);
    for (int j = 1; j < 20; ++j) {
        for (int i = 1; i <= n; ++i) {
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
        }
    }
}

void solve()
{
    cin >> n >> m >> k;

    for (int i = 0; i <= n; ++i) g[i].clear();
    memset(sm, -1, sizeof(sm));
    memset(cnt, 0, sizeof(cnt));

    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].emplace_back(v, i);
        g[v].emplace_back(u, i);
    }

    for (int i = 0; i < m; ++i) {
        int x;
        cin >> x;
        sm[x] = i;
    }

    build();

    int ms = 0;
    for (int i = 0; i < k; ++i) {
        int u, v;
        cin >> u >> v;
        int tmp = msk[u] ^ msk[v];
        cnt[tmp]++;
        ms |= tmp;
    }

    if (ms != (1 << m) - 1) {
        cout << -1 << endl;
        return;
    }

    memcpy(sos, cnt, sizeof(sos));
    for (int i = 0; i < m; ++i) {
        for (int mask = 0; mask < (1 << m); ++mask) {
            if (mask & (1 << i)) {
                sos[mask] += sos[mask ^ (1 << i)];
            }
        }
    }

    vector<LL> dp(1 << m);
    for (int mask = 0; mask < (1 << m); ++mask) {
        int bits = __builtin_popcount(mask);
        if ((m - bits) % 2 == 0) {
            dp[mask] = 1;
        } else {
            dp[mask] = MOD - 1;
        }
    }

    for (int c = 1; c <= m; ++c) {
        LL res = 0;
        for (int mask = 0; mask < (1 << m); ++mask) {
            LL tim = C(sos[mask], c);
            res    = (res + dp[mask] * tim) % MOD;
        }
        if (res != 0) {
            cout << c << " " << res << endl;
            return;
        }
    }

    cout << -1 << endl;
}

signed main()
{
    ios;
    init(N - 1);
    int T = 1;
    //    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}