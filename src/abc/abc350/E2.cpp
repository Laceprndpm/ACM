#include <cstdio>
#include <iostream>
#include <map>
using namespace std;
using i64            = long long;
using PII            = pair<int, int>;
constexpr int    INF = 1e9;
map<i64, double> mp;
i64              n, a, x, y;

double DFS(i64 val)
{
    if (val == 0) return 0;
    if (mp[val]) return mp[val];
    double ans1 = y * 1.2, ans2 = DFS(val / a) + x;
    for (i64 i = 2; i <= 6; i++) {
        ans1 += DFS(val / i) / 5;
    }
    return mp[val] = min(ans1, ans2);
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    cin >> n >> a >> x >> y;
    printf("%.10lf", DFS(n));
    return 0;
}