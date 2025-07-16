#include <algorithm>
#include <iostream>
#include <utility>
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

constexpr int INF = 1e9;

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
        a.assign(n, T{0});
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
    int n, q;
    cin >> n >> q;
    vector<i64> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    auto                   num = arr;
    auto                   tmp = arr;
    vector<pair<i64, i64>> query(q);
    for (int i = 0; i < q; i++) {
        i64 p, v;
        cin >> p >> v;
        p--;
        tmp[p] += v;
        num.eb(tmp[p]);
        query[i] = {p, v};
    }
    sor(num);
    num.erase(unique(all(num)), num.end());
    Fenwick<int> fk(num.size() + 1);
    for (i64 i : arr) {
        fk.add(lower_bound(all(num), i) - bg(num), 1);
    }
    for (auto it : query) {
        auto [p, v] = it;
        int idx1    = lower_bound(all(num), arr[p]) - bg(num);
        fk.add(idx1, -1);
        arr[p] += v;
        int idx2 = lower_bound(all(num), arr[p]) - bg(num);
        fk.add(idx2, 1);
        int res = fk.select((n + 1) / 2);
        cout << fk.sum(res) << '\n';
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