#include <bits/stdc++.h>

#include <cstdint>
#include <functional>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
constexpr int N   = 143;

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

constexpr i64 mul(i64 a, i64 b, i64 p)
{
    i64 res = a * b - i64(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) {
        res += p;
    }
    return res;
}

template <i64 P>
struct MLong {
    i64 x;

    constexpr MLong() : x{} {}

    constexpr MLong(i64 x) : x{norm(x % getMod())} {}

    static i64 Mod;

    constexpr static i64 getMod()
    {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }

    constexpr static void setMod(i64 Mod_)
    {
        Mod = Mod_;
    }

    constexpr i64 norm(i64 x) const
    {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }

    constexpr i64 val() const
    {
        return x;
    }

    explicit constexpr operator i64() const
    {
        return x;
    }

    constexpr MLong operator-() const
    {
        MLong res;
        res.x = norm(getMod() - x);
        return res;
    }

    constexpr MLong inv() const
    {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }

    constexpr MLong &operator*=(MLong rhs) &
    {
        x = mul(x, rhs.x, getMod());
        return *this;
    }

    constexpr MLong &operator+=(MLong rhs) &
    {
        x = norm(x + rhs.x);
        return *this;
    }

    constexpr MLong &operator-=(MLong rhs) &
    {
        x = norm(x - rhs.x);
        return *this;
    }

    constexpr MLong &operator/=(MLong rhs) &
    {
        return *this *= rhs.inv();
    }

    friend constexpr MLong operator*(MLong lhs, MLong rhs)
    {
        MLong res = lhs;
        res *= rhs;
        return res;
    }

    friend constexpr MLong operator+(MLong lhs, MLong rhs)
    {
        MLong res = lhs;
        res += rhs;
        return res;
    }

    friend constexpr MLong operator-(MLong lhs, MLong rhs)
    {
        MLong res = lhs;
        res -= rhs;
        return res;
    }

    friend constexpr MLong operator/(MLong lhs, MLong rhs)
    {
        MLong res = lhs;
        res /= rhs;
        return res;
    }

    friend constexpr std::istream &operator>>(std::istream &is, MLong &a)
    {
        i64 v;
        is >> v;
        a = MLong(v);
        return is;
    }

    friend constexpr std::ostream &operator<<(std::ostream &os, const MLong &a)
    {
        return os << a.val();
    }

    friend constexpr bool operator==(MLong lhs, MLong rhs)
    {
        return lhs.val() == rhs.val();
    }

    friend constexpr bool operator!=(MLong lhs, MLong rhs)
    {
        return lhs.val() != rhs.val();
    }
};

template <>
i64 MLong<0LL>::Mod = i64(1E18) + 9;

template <int P>
struct MInt {
    int x;

    constexpr MInt() : x{} {}

    constexpr MInt(i64 x) : x{norm(x % getMod())} {}

    static int Mod;

    constexpr static int getMod()
    {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }

    constexpr static void setMod(int Mod_)
    {
        Mod = Mod_;
    }

    constexpr int norm(int x) const
    {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }

    constexpr int val() const
    {
        return x;
    }

    explicit constexpr operator int() const
    {
        return x;
    }

    constexpr MInt operator-() const
    {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }

    constexpr MInt inv() const
    {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }

    constexpr MInt &operator*=(MInt rhs) &
    {
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }

    constexpr MInt &operator+=(MInt rhs) &
    {
        x = norm(x + rhs.x);
        return *this;
    }

    constexpr MInt &operator-=(MInt rhs) &
    {
        x = norm(x - rhs.x);
        return *this;
    }

    constexpr MInt &operator/=(MInt rhs) &
    {
        return *this *= rhs.inv();
    }

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

    friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a)
    {
        return os << a.val();
    }

    friend constexpr bool operator==(MInt lhs, MInt rhs)
    {
        return lhs.val() == rhs.val();
    }

    friend constexpr bool operator!=(MInt lhs, MInt rhs)
    {
        return lhs.val() != rhs.val();
    }
};

template <>
int MInt<0>::Mod = 998244353;

template <int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();

constexpr int P = 998244353;
using Z         = MInt<P>;
Z dp[N][N];

struct Comb {
    int       n;
    vector<Z> _fac;
    vector<Z> _invfac;
    vector<Z> _inv;

    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}

    Comb(int n) : Comb()
    {
        init(n);
    }

    void init(int m)
    {
        if (m <= n) return;
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);

        for (int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        _invfac[m] = _fac[m].inv();
        for (int i = m; i > n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
            _inv[i]        = _invfac[i] * _fac[i - 1];
        }
        n = m;
    }

    Z fac(int m)
    {
        if (m > n) init(2 * m);
        return _fac[m];
    }

    Z invfac(int m)
    {
        if (m > n) init(2 * m);
        return _invfac[m];
    }

    Z inv(int m)
    {
        if (m > n) init(2 * m);
        return _inv[m];
    }

    Z binom(int n, int m)
    {
        if (n < m || m < 0) return 0;
        return fac(n) * invfac(m) * invfac(n - m);
    }
} comb(1e5);

struct point {
    i64 x, y;
};

i64 df(const point &x, const point &y)
{
    return abs(x.x - y.x) + abs(x.y - y.y);
}

Z A(i64 n, i64 k)
{
    return comb.fac(n) / comb.fac(n - k);
}

signed main(int argc, char **argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n;
    cin >> n;
    vector<point>       pointVector(n + 1);
    vector<vector<i64>> dist(n + 1, vector<i64>(n + 1));
    for (int i = 1; i <= n; i++) {
        i64 x, y;
        cin >> x >> y;
        pointVector[i] = {x, y};
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            i64 dis    = df(pointVector[i], pointVector[j]);
            dist[i][j] = dis;
            dist[j][i] = dis;
        }
        dist[i][i] = INT64_MAX;
    }
    vector<i64>         minDis(n + 1, INT64_MAX);
    vector<vector<i64>> graph(n + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j == i) continue;
            if (minDis[i] > dist[i][j]) {
                minDis[i] = dist[i][j];
                graph[i].clear();
                graph[i].emplace_back(j);
            } else if (minDis[i] == dist[i][j]) {
                graph[i].emplace_back(j);
            }
        }
    }
    vector<int>         color(n + 1);
    vector<i64>         compsize;
    set<i64>            pts;
    function<void(int)> dfs1 = [&](int root) {
        if (pts.count(root) == 1) return;
        pts.insert(root);
        for (int adj : graph[root]) {
            dfs1(adj);
        }
    };
    function<void(int, int)> dfs2 = [&](int root, int c) {
        if (color[root] == c) return;
        color[root] = c;
        for (auto v : graph[root])
            dfs2(v, c);
    };
    // for (pair<i64, i64> i : mp) {
    //     compsize.emplace_back(i.second);
    // }
    int cc = 0;
    for (int i = 1; i <= n; i++) {
        if (color[i] != 0) continue;
        cc++;
        pts.clear();
        dfs1(i);
        // cerr << "!" << endl;
        int      d    = *min_element(dist[i].begin() + 1, dist[i].begin() + 1 + n);
        set<i64> pts2 = pts;
        bool     bad  = false;
        for (auto x : pts)
            for (auto y : pts2)
                if (x != y && dist[x][y] != d) bad = true;
        if (bad) {
            color[i] = cc;
            compsize.push_back(1);
        } else {
            dfs2(i, cc);
            compsize.push_back(pts.size());
        }
    }
    dp[0][0] = 1;
    int m    = compsize.size();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (dp[i][j] == 0) continue;
            dp[i + 1][j + 1] += dp[i][j];
            if (compsize[i] != 1) {
                dp[i + 1][j + compsize[i]] += dp[i][j];
            }
        }
    }
    Z ans = 0;
    for (int i = 1; i <= n; i++)
        ans += dp[m][i] * A(n, i);
    cout << ans << '\n';
    return 0;
}