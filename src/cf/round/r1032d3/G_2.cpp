#include <iostream>
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

template <class T>
struct RangeFenwick {
    int        n;
    Fenwick<T> d1, d2;

    RangeFenwick(int n_) : n(n_), d1(n_), d2(n_) {}

    void add(i64 k, T v)
    {
        T v1 = k * v;
        d1.add(k, v), d2.add(k, v1);
        // 在diff的k位置+v
    }

    void add(i64 l, i64 r, T v)
    {
        add(l, v), add(r, -v);  // 将区间加差分为两个前缀加
    }

    T getsum(i64 x)
    {
        return x * d1.sum(x) - d2.sum(x);
    }

    T getsum(i64 l, i64 r)
    {
        return getsum(r) - getsum(l);
    }
};

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    int          cnt0_1 = n + 5;
    Fenwick<i64> fktree(2 * n + 50);
    fktree.add(cnt0_1, 1);
    i64 tmp = 0;
    i64 ans = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            cnt0_1--;
            // cnt0 - cnt1 < 0
            tmp += fktree.rangeSum(cnt0_1 + 1, 2 * n + 50);
        } else {
            cnt0_1++;
            tmp += fktree.rangeSum(0, cnt0_1);
        }
        fktree.add(cnt0_1, 1);
        ans += tmp;
    }
    cout << ans << '\n';
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
    // 当添加了一个字符时
    // 新增的贡献为
    // 对于前面的每个字符，如果作为left端点的贡献
    // 贡献可以是原本的不变，也可以是+1
    // 以0为例
    // 如果[l, i)中cnt_1 <= cnt_0,则需要额外+1
    // 如何维护所有后缀中，cnt_1 - cnt_0呢？
    //
    // 需要维护cnt_0-cnt_1的前缀和，那么[l, r)中cnt_0 - cnt_1 = prefix[r] - prefix[l - 1]，那么用Fenwick树维护这个前缀和
    // 就可以快速查询有多少个前缀和小于等于当前的前缀和
    //
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