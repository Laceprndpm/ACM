#include <bits/stdc++.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,popcnt")
using namespace std;
using ll   = long long;
using u8   = uint8_t;
using u16  = uint16_t;
using u32  = uint32_t;
using u64  = uint64_t;
using i64  = long long;
using i128 = __int128;

istream &operator>>(istream &in, i128 &num)
{
    string s;
    in >> s;
    num      = 0;
    bool neg = (s[0] == '-');
    for (size_t i = neg; i < s.size(); ++i) {
        num = num * 10 + (s[i] - '0');
    }
    if (neg) num = -num;
    return in;
}

ostream &operator<<(ostream &out, const i128 &num)
{
    if (num == 0) {
        return out << '0';
    }
    i128 temp = num;
    if (temp < 0) {
        out << '-';
        temp = -temp;
    }
    string result;
    while (temp > 0) {
        result += char('0' + temp % 10);
        temp /= 10;
    }
    reverse(result.begin(), result.end());
    return out << result;
}

// vectors
#define len(x)  int(x.size())
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
#define mp      make_pair
#define mt      make_tuple
#define fi      first
#define se      second

// https://trap.jp/post/1224/
#define FOR1(a)                       for (i64 _ = 0; _ < i64(a); ++_)
#define FOR2(i, a)                    for (i64 i = 0; i < i64(a); ++i)
#define FOR3(i, a, b)                 for (i64 i = a; i < i64(b); ++i)
#define FOR4(i, a, b, c)              for (i64 i = a; i < i64(b); i += (c))
#define FOR1_R(a)                     for (i64 i = (a) - 1; i >= i64(0); --i)
#define FOR2_R(i, a)                  for (i64 i = (a) - 1; i >= i64(0); --i)
#define FOR3_R(i, a, b)               for (i64 i = (b) - 1; i >= i64(a); --i)
#define overload4(a, b, c, d, e, ...) e
#define overload3(a, b, c, d, ...)    d
#define FOR(...)                      overload4(__VA_ARGS__, FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)
#define FOR_R(...)                    overload3(__VA_ARGS__, FOR3_R, FOR2_R, FOR1_R)(__VA_ARGS__)

constexpr i64 INF = 1e18;

template <typename T>
T floor(T a, T b)
{
    return a / b - (a % b && (a ^ b) < 0);
}

template <typename T>
T ceil(T x, T y)
{
    return floor(x + y - 1, y);
}

struct Line {
    i64 a, b;
    i64 xleft;  // 与前一条线交点的横坐标（下凸包的转折点）

    i64 eval(i64 x) const
    {
        return a * x + b;
    }
};

vector<i64> help(vector<pair<i64, i64>> lines, vector<i64> x_query)
{
    sort(lines.begin(), lines.end(), [](const auto &p1, const auto &p2) {
        if (p1.fi == p2.fi) {
            return p1.se < p2.se;
        }
        return p1.fi > p2.fi;
    });

    lines.erase(unique(all(lines)), lines.end());
    vector<Line> hull;

    auto no_D = [](const Line &l1, const Line &l2, const Line &l3) -> bool {
        // a1 * x + b1 = a2 * x + b2
        // (l2.b - l1.b) / (l1.a - l2.a) >= (l3.b - l2.b) / (l2.a - l3.a)
        return ((i128)(l2.b - l1.b)) * (i128)(l2.a - l3.a) >= ((i128)(l3.b - l2.b)) * (i128)(l1.a - l2.a);
    };

    auto xiangxia_jiao = [](const Line &l1, const Line &l2) -> i64 {
        // a1 x + b >= a2 * x + b
        return ceil((l2.b - l1.b), (l1.a - l2.a));
    };

    for (auto [a, b] : lines) {
        Line l = {a, b, -(i64)1e18};
        if (!hull.empty() && l.a == hull.bk.a) continue;

        while (hull.size() >= 2 && no_D(hull[sz(hull) - 2], hull.bk, l)) {
            hull.pop_back();
        }

        if (!hull.empty()) {
            l.xleft = xiangxia_jiao(hull.back(), l);
        }
        hull.push_back(l);
    }

    vector<i64> res;
    for (i64 x : x_query) {
        i64 ans = 0;
        int l = 0, r = (int)hull.size() - 1;
        while (l <= r) {
            int m = (l + r) / 2;
            if (hull[m].xleft <= x) {
                ans = m;
                l   = m + 1;
            } else {
                r = m - 1;
            }
        }
        res.push_back(hull[ans].eval(x));
    }
    return res;
}

void solve()
{
    i64 n, m;
    cin >> n >> m;
    vector<vector<pair<i64, i64>>> graph(n + 1);
    vector<vector<pair<i64, i64>>> r_graph(n + 1);
    vector<pair<i64, i64>>         linear;

    vector<array<i64, 4>> input;
    for (int i = 0; i < m; i++) {
        i64 u, v, ti, wi;
        cin >> u >> v >> ti >> wi;
        graph[u].pb({v, ti});
        r_graph[v].pb({u, ti});
        input.pb({u, v, ti, wi});
    }

    vector<i64> dist1(n + 1, INF);
    vector<i64> dist2(n + 1, INF);

    auto dijstra1 = [&]() {
        vector<int> vis(n + 1);

        priority_queue<pair<i64, i64>, vector<pair<i64, i64>>, greater<>> pq;
        pq.push({0, 1});
        while (!pq.empty()) {
            auto [dist, u] = pq.top();
            pq.pop();

            if (vis[u]) continue;
            vis[u]   = 1;
            dist1[u] = dist;

            for (auto [v, t] : graph[u]) {
                pq.push({t + dist, v});
            }
        }
    };

    auto dijstra2 = [&]() {
        vector<int> vis(n + 1);

        priority_queue<pair<i64, i64>, vector<pair<i64, i64>>, greater<>> pq;
        pq.push({0, n});
        while (!pq.empty()) {
            auto [dist, u] = pq.top();
            pq.pop();
            if (vis[u]) continue;

            vis[u]   = 1;
            dist2[u] = dist;

            for (auto [v, t] : r_graph[u]) {
                pq.push({t + dist, v});
            }
        }
    };

    dijstra1();
    dijstra2();

    for (auto [u, v, ti, wi] : input) {
        linear.eb(-wi, ti + dist1[u] + dist2[v]);
    }

    int q;
    cin >> q;
    vector<i64> query(q);
    for (int i = 0; i < q; i++) {
        cin >> query[i];
    }

    auto res = help(linear, query);
    for (i64 i : res) {
        cout << i << '\n';
    }
}

signed main(signed argc, char **argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int t;
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