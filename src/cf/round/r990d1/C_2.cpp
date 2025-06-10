#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
constexpr int INF = 1e9;
using i64         = long long;
using u64         = unsigned long long;
using u32         = unsigned;
using u128        = unsigned __int128;

template <typename T>
struct Fenwick {
    int            n;
    std::vector<T> a;

    Fenwick(int n_ = 0)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        a.assign(n, T{});
    }

    void add(int x, const T &v)
    {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] = a[i - 1] + v;
        }
    }

    T sum(int x)
    {
        T ans{};
        for (int i = x; i > 0; i -= i & -i) {
            ans = ans + a[i - 1];
        }
        return ans;
    }

    T rangeSum(int l, int r)
    {
        return sum(r) - sum(l);
    }

    int select(const T &k)
    {
        int x = 0;
        T   cur{};
        for (int i = 1 << std::__lg(n); i; i /= 2) {
            if (x + i <= n && cur + a[x + i - 1] <= k) {
                x += i;
                cur = cur + a[x - 1];
            }
        }
        return x;
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    auto xs = x, ys = y;
    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    for (int i = 0; i < n; i++) {
        x[i] = lower_bound(xs.begin(), xs.end(), x[i]) - xs.begin();
        y[i] = lower_bound(ys.begin(), ys.end(), y[i]) - ys.begin();
    }
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    sort(p.begin(), p.end(), [&](int u, int v) {
        return x[u] > x[v];
    });
    int          k = 0;
    Fenwick<i64> fr(n), fl(n);
    int          X0 = 0, Y0 = 0;
    for (int i = 0; i < n; i++) {
        fr.add(y[i], 1);
    }
    for (int i = 0; i < n; i++) {
        int j = p[i];
        fr.add(y[j], -1);
        fl.add(y[j], 1);
        if (i + 1 < n && x[j] == x[p[i + 1]]) {
            continue;
        }
        while (true) {
            if (i + 1 < 2 * (k + 1)) {
                break;
            }
            if (n - i - 1 < 2 * (k + 1)) {
                break;
            }
            int yl = std::max(fl.select(k), fr.select(k));
            int yr = std::min(fl.select(i - k), fr.select(n - 1 - i - 1 - k));
            if (yl >= yr) {
                break;
            }
            k++;
            X0 = xs[x[j]];
            Y0 = ys[yr];
        }
    }
    cout << k << '\n';
    cout << X0 << ' ' << Y0 << '\n';
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
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}