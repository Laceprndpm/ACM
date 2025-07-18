#include <bits/stdc++.h>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,popcnt")
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

constexpr int INF = 1e9;

struct Point {
    i64 x, y;

    friend Point operator-(Point& a, Point& b)
    {
        Point x{a.x - b.x, a.y - b.y};
        return x;
    }

    friend i64 operator*(const Point& a, const Point& b)
    {
        return a.x * b.y - a.y * b.x;
    }

    friend i64 dist2(Point& a, Point& b)
    {
        return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    }
};

void solve()
{
    i64 n, x, y;
    cin >> n >> x >> y;

    vector<Point> point(n);
    for (int i = 0; i < n; i++) {
        cin >> point[i].x >> point[i].y;
    }
    Point p{x, y};
    bool  baohan  = 0;
    auto  contain = [&](Point a, Point b, Point c) {
        auto a_b = b - a, a_c = c - a, a_p = p - a, b_p = p - b, c_p = p - c;
        return abs(a_b * a_c) == abs(a_b * a_p) + abs(b_p * c_p) + abs(a_c * a_p);
    };

    for (int i = 1; i + 1 < n; i++) {
        if (contain(point[0], point[i], point[i + 1])) {
            baohan = 1;
            break;
        }
    }
    if (!baohan) {
        cout << "6.283185307179586\n";
        return;
    }
    vector<Point> bianjie;
    bianjie.pb(point[0]);
    for (int i = 1; i < n; i++) {

        if (dist2(p, bianjie[0]) < dist2(p, point[i])) {
            bianjie.clear();
            bianjie.pb(point[i]);
        } else if (dist2(p, bianjie[0]) == dist2(p, point[i])) {
            bianjie.pb(point[i]);
        }
    }
    vector<i64> dis;
    for (int i = 0; i < sz(bianjie); i++) {
        i64   tmpx = 2 * p.x - bianjie[i].x, tmpy = 2 * p.y - bianjie[i].y;
        Point mirror = {tmpx, tmpy};

        i64 cha = (bianjie[(i + 1) % sz(bianjie)] - bianjie[i]) * (mirror - bianjie[i]);
        dis.pb(dist2(bianjie[i], bianjie[(i + 1) % sz(bianjie)]));

        if (cha < 0) {
            i64    d2  = dis[i];
            i64    yao = dist2(p, bianjie[0]);
            double di = sqrtl(d2), yy = sqrtl(yao);
            double ans = 6.283185307179586 - asin(di / 2 / yy) * 2;
            printf("%.8lf\n", ans);
            return;
        }
    }
    int place1 = max_element(all(dis)) - bg(dis);
    int palce2 = (place1 + 1) % sz(bianjie);
    if (sz(bianjie) == 1) {
        cout << "6.283185307179586\n";
        return;
    }
    auto   one = bianjie[place1] - p, two = bianjie[palce2] - p;
    i64    d2  = dis[place1];
    i64    yao = dist2(p, bianjie[0]);
    double di = sqrtl(d2), yy = sqrtl(yao);
    double ans = asin(di / 2 / yy) * 2;
    printf("%.8lf\n", ans);
}

signed main(signed argc, char** argv)
{
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