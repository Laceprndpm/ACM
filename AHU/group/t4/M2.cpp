#include <bits/stdc++.h>
#define inf   0x3f3f3f3f
#define llinf 0x3f3f3f3f3f3f3f3f
#define endl  '\n'
#define ll    long long
using namespace std;

constexpr int mod = 998244353, N = 5005, M = 2e5 + 5;

using i64 = long long;

template <class T>
constexpr T power(T a, i64 b)
{
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

template <int P>
struct MInt {
    int x;

    constexpr MInt() : x{} {}

    constexpr MInt(i64 x) : x{norm(x % P)} {}

    constexpr int norm(int x) const
    {
        if (x < 0) {
            x += P;
        }
        if (x >= P) {
            x -= P;
        }
        return x;
    }

    constexpr int val() const { return x; }

    explicit constexpr operator int() const { return x; }

    constexpr MInt operator-() const
    {
        MInt res;
        res.x = norm(P - x);
        return res;
    }

    constexpr MInt inv() const
    {
        assert(x != 0);
        return power(*this, P - 2);
    }

    constexpr MInt &operator*=(MInt rhs)
    {
        x = 1LL * x * rhs.x % P;
        return *this;
    }

    constexpr MInt &operator+=(MInt rhs)
    {
        x = norm(x + rhs.x);
        return *this;
    }

    constexpr MInt &operator-=(MInt rhs)
    {
        x = norm(x - rhs.x);
        return *this;
    }

    constexpr MInt &operator/=(MInt rhs) { return *this *= rhs.inv(); }

    friend constexpr MInt operator*(MInt lhs, MInt rhs)
    {
        MInt res = lhs;
        res *= rhs;
        return res;
    }

    friend constexpr MInt operator+(MInt lhs, MInt rhs)
    {
        MInt res = lhs;
        res += rhs;
        return res;
    }

    friend constexpr MInt operator-(MInt lhs, MInt rhs)
    {
        MInt res = lhs;
        res -= rhs;
        return res;
    }

    friend constexpr MInt operator/(MInt lhs, MInt rhs)
    {
        MInt res = lhs;
        res /= rhs;
        return res;
    }

    friend constexpr std::istream &operator>>(std::istream &is, MInt &a)
    {
        i64 v;
        is >> v;
        a = MInt(v);
        return is;
    }

    friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) { return os << a.val(); }

    friend constexpr bool operator==(MInt lhs, MInt rhs) { return lhs.val() == rhs.val(); }

    friend constexpr bool operator!=(MInt lhs, MInt rhs) { return lhs.val() != rhs.val(); }
};

constexpr int MOD = 998244353;
using Z           = MInt<MOD>;

Z pow2[N];

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    Z            ans = 1;
    vector<Z>    pre(n + 1, Z(1));
    vector<bool> used(n + 1, false);
    vector       dp(n + 1, vector<Z>(2, 0));

    for (int i = 1; i < n; i++) {
        int x;
        cin >> x;
        used[x] = true;

        auto dfs = [&](auto &&dfs, int u, int fa) -> void {
            if (pre[u] != 1) ans /= pre[u], pre[u] = 1;
            int c    = 0;
            dp[u][0] = 1, dp[u][1] = 0;
            for (int v : adj[u]) {
                if (used[v]) c++;
                if (v == fa || !used[v]) continue;
                dfs(dfs, v, u);
                dp[u][1] = dp[v][1] * dp[u][0] + dp[u][1] * (2 * dp[v][1] + dp[v][0]);
                dp[u][0] *= (2 * dp[v][1] + dp[v][0]);
            }
            c = adj[u].size() - c;
            dp[u][1] *= pow2[c];
            if (c) dp[u][1] += dp[u][0] * c * pow2[c - 1];
            dp[u][0] *= pow2[c];
        };

        dfs(dfs, x, 0);
        pre[x] = dp[x][1];
        ans *= dp[x][1];
        cout << ans << endl;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);  // cout.tie(0);

    pow2[0] = 1;
    for (int i = 1; i <= 5000; i++) pow2[i] = pow2[i - 1] * 2;

    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}