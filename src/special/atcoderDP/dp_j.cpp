#include <array>
#include <cstdio>
#include <functional>
#include <iostream>
#include <map>
#include <unordered_map>
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

constexpr int INF = 1e9;
using Status      = array<int, 4>;

namespace std {
template <>
struct hash<Status> {
    size_t operator()(const Status& s) const
    {
        size_t h = 0;
        for (auto x : s) {
            h ^= std::hash<int>{}(x) + 0x9e3779b9 + (h << 6) + (h >> 2);
        }
        return h;
    }
};
}  // namespace std

unordered_map<Status, double> mp;

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    i64 n;
    cin >> n;
    mp.reserve(1e7);
    Status s = {0};
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        s[x]++;
    }
    auto dfs = [&](auto&& dfs, Status s) -> double {
        if (mp[s]) {
            return mp[s];
        }
        if (s[0] == n) return 0;
        double cur = 1;
        double pos = 1.0 - double(s[0]) / n;
        for (int i = 1; i < 4; i++) {
            if (!s[i]) continue;
            auto   tmp    = s;
            double weight = double(s[i]) / n;
            tmp[i]--, tmp[i - 1]++;
            cur += dfs(dfs, tmp) * weight;
        }
        return mp[s] = cur / pos;
    };
    printf("%.8lf", dfs(dfs, s));
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */