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
    vector<int> arr(n);
    vector<int> cnt(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        cnt[arr[i]]++;
    }
    int top = 0;
    while (cnt[top]) {
        top++;
    }
    vector<int> cntPre(1);
    for (int r : cnt) {
        cntPre.push_back(cntPre.back() + r);
    }
    RangeFenwick<int> ansArr(n + 2);
    for (int i = 0; i <= top; i++) {
        int l = cnt[i];
        int r = cntPre[i] - i + (cntPre.back() - cntPre[i]);
        ansArr.add(l, r + 1, 1);
    }
    for (int i = 0; i < n + 1; i++) {
        cout << ansArr.getsum(i, i + 1) << ' ';
    }
    cout << '\n';
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
    // 连续性不保证，考虑[0, 1, 2, 3 * 10000, 4, 5]
    // 此时几乎不可能说存在mex = 3
    // dp
    // 贪心
    // 可以用前缀和优化查找范围
    // 假如考虑每个数，可以求出mex(s) = x时至少删除几个数？即删除全部的ai = x
    // 最多删除几个数？即前面恰好为n,后面全删，中间不退化
    //
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