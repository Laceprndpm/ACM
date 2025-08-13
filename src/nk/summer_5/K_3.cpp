#include <bits/stdc++.h>

#define x first
#define y second

using namespace std;

typedef long long          ll;
typedef pair<ll, ll>       PLL;
typedef unsigned long long ull;

mt19937_64 rng(time(0));

void chmax(ll &x, ll y)
{
    if (x < y) x = y;
}

void chmin(ll &x, ll y)
{
    if (x > y) x = y;
}

const ll N = 2e5 + 10, P = 998244353;

ll n, m, k;
ll h[N], e[N << 1], ne[N << 1], idx;
ll cnt[1ll << 22], f[1ll << 22], dp[1ll << 22];
ll val[N], pre[N];

void add(ll a, ll b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(ll u, ll fa)
{
    for (ll i = h[u]; ~i; i = ne[i]) {
        ll v = e[i];
        if (v == fa) continue;
        pre[v] = pre[u] + val[i / 2];
        dfs(v, u);
    }
}

void solve()
{
    cin >> n >> m >> k;

    memset(h, -1, sizeof h);

    for (ll i = 1; i < n; i++) {
        ll a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }

    for (ll i = 0; i < m; i++) {
        ll x;
        cin >> x;
        x--;
        val[x] = 1ll << i;
    }

    dfs(1, 0);

    for (ll i = 0; i < k; i++) {
        ll a, b;
        cin >> a >> b;
        cnt[pre[a] ^ pre[b]]++;
    }

    memset(dp, 0x3f, sizeof dp);
    f[0]  = 1;
    dp[0] = 0;
    for (ll i = 1; i < 1ll << m; i++)
        if (cnt[i]) {
            for (ll j = 0; j < 1ll << m; j++)
                if (dp[i | j] > dp[j] + 1) {
                    dp[i | j] = dp[j] + 1;
                    f[i | j]  = f[j] * cnt[i] % P;
                } else if (dp[i | j] == dp[j] + 1)
                    f[i | j] = (f[i | j] + f[j] * cnt[i]) % P;
        }

    if (!f[(1ll << m) - 1]) {
        cout << -1 << '\n';
        return;
    }

    cout << dp[(1ll << m) - 1] << ' ' << f[(1ll << m) - 1] << '\n';
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

    ll _ = 1;
    // cin >> _;

    while (_--)
        solve();

    return 0;
}
