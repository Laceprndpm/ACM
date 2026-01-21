#include <deque>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>
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

template <class Info, class Tag>
struct LazySegmentTree {
    int          n;
    vector<Info> info;
    vector<Tag>  tag;

    LazySegmentTree() : n(0) {}

    LazySegmentTree(int n_, Info v_ = Info()) { init(n_, v_); }

    template <class T>
    LazySegmentTree(vector<T> init_)
    {
        init(init_);
    }

    void init(int n_, Info v_ = Info()) { init(vector(n_, v_)); }

    template <class T>
    void init(vector<T> init_)
    {
        n = init_.size();
        info.assign(4 << __lg(n), Info());
        tag.assign(4 << __lg(n), Tag());
        function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init_[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }

    void pull(int p) { info[p] = info[2 * p] + info[2 * p + 1]; }

    void apply(int p, const Tag &v)
    {
        info[p].apply(v);
        tag[p].apply(v);
    }

    void push(int p)
    {
        apply(2 * p, tag[p]);
        apply(2 * p + 1, tag[p]);
        tag[p] = Tag();
    }

    void modify(int p, int l, int r, int x, const Info &v)
    {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        push(p);
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }

    void modify(int p, const Info &v) { modify(1, 0, n, p, v); }

    Info rangeQuery(int p, int l, int r, int x, int y)
    {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        push(p);
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }

    Info rangeQuery(int l, int r) { return rangeQuery(1, 0, n, l, r); }

    void rangeApply(int p, int l, int r, int x, int y, const Tag &v)
    {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            apply(p, v);
            return;
        }
        int m = (l + r) / 2;
        push(p);
        rangeApply(2 * p, l, m, x, y, v);
        rangeApply(2 * p + 1, m, r, x, y, v);
        pull(p);
    }

    void rangeApply(int l, int r, const Tag &v) { return rangeApply(1, 0, n, l, r, v); }

    void half(int p, int l, int r)
    {
        if (info[p].act == 0) {
            return;
        }
        if ((info[p].min + 1) / 2 == (info[p].max + 1) / 2) {
            apply(p, {-(info[p].min + 1) / 2});
            return;
        }
        int m = (l + r) / 2;
        push(p);
        half(2 * p, l, m);
        half(2 * p + 1, m, r);
        pull(p);
    }

    void half() { half(1, 0, n); }

    template <class F>
    int findFirst(int p, int l, int r, int x, int y, F &&pred)
    {
        if (l >= y || r <= x) {
            return -1;
        }
        if (l >= x && r <= y && !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        push(p);
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }

    template <class F>
    int findFirst(int l, int r, F &&pred)
    {
        return findFirst(1, 0, n, l, r, pred);
    }

    template <class F>
    int findLast(int p, int l, int r, int x, int y, F &&pred)
    {
        if (l >= y || r <= x) {
            return -1;
        }
        if (l >= x && r <= y && !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        push(p);
        int res = findLast(2 * p + 1, m, r, x, y, pred);
        if (res == -1) {
            res = findLast(2 * p, l, m, x, y, pred);
        }
        return res;
    }

    template <class F>
    int findLast(int l, int r, F &&pred)
    {
        return findLast(1, 0, n, l, r, pred);
    }

    void maintainL(int p, int l, int r, int pre)
    {
        if (info[p].difl > 0 && info[p].maxlowl < pre) {
            return;
        }
        if (r - l == 1) {
            info[p].max  = info[p].maxlowl;
            info[p].maxl = info[p].maxr = l;
            info[p].maxlowl = info[p].maxlowr = -INF;
            return;
        }
        int m = (l + r) / 2;
        push(p);
        maintainL(2 * p, l, m, pre);
        pre = max(pre, info[2 * p].max);
        maintainL(2 * p + 1, m, r, pre);
        pull(p);
    }

    void maintainL() { maintainL(1, 0, n, -1); }

    void maintainR(int p, int l, int r, int suf)
    {
        if (info[p].difr > 0 && info[p].maxlowr < suf) {
            return;
        }
        if (r - l == 1) {
            info[p].max  = info[p].maxlowl;
            info[p].maxl = info[p].maxr = l;
            info[p].maxlowl = info[p].maxlowr = -INF;
            return;
        }
        int m = (l + r) / 2;
        push(p);
        maintainR(2 * p + 1, m, r, suf);
        suf = max(suf, info[2 * p + 1].max);
        maintainR(2 * p, l, m, suf);
        pull(p);
    }

    void maintainR() { maintainR(1, 0, n, -1); }
};

struct Tag {
    int x = 0;

    void apply(const Tag &t) & { x = x + t.x; }
};

struct Info {
    int x = INF;

    void apply(const Tag &t) & { x = x + t.x; }
};

Info operator+(const Info &a, const Info &b) { return {min(a.x, b.x)}; }

void solve()
{
    // 假设i没有和i-1或i+1相切，则一定劣
    // 能不能只用状态0,1表示？前者为没有和前一个相切，后者为和前一个相切了
    // 暴力搞的话，就是[i..j]，i可以算出一个r的范围，是[0, min(i, i+1)]，然后i+1再搞[i+1 - min(i, i+1), min(i+1, i+2)]
    // 假设第一位为j1 + r，第二位为j2 - j1 - r，第三位为j3 - j2 + r，第四位为j4 - j3 + j2 - r,最后这些只要都为正数即可
    //  max(-j1, -j3 + j2 - j1, -j5 + j4 - j3 + j2) < r 奇数
    // 即r < min(j2 - j1, j4 - j3 + j2 - j1, j6 - j5 + j4 - j3 + 2)
    // 移动的话
    // 似乎只不需要>=max(0...)
    // 再移动，又是之不需要<=min(j2)

    int n;
    cin >> n;
    vector<i64> arr(n + 1, -(ll)1e10);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    if (n == 1) {
        cout << 0 << '\n';
        return;
    }
    vector<i64> gap(n + 1);
    for (int i = 1; i <= n; i++) {
        gap[i] = arr[i] - arr[i - 1];
    }
    vector<i64> prefix(n + 1);
    for (int i = 1; i <= n; i++) {
        prefix[i] = prefix[i - 1] + (i % 2 == 1 ? -1 : 1) * gap[i];
    }
    int                   ptr = 1;
    deque<pair<i64, i64>> minque, maxque;
    vector<int>           satis(n + 1);
    for (int i = 1; i <= n; i++) {
        while (!minque.empty() && minque.front().fi < i) {
            minque.pop_front();
        }
        while (!maxque.empty() && maxque.front().fi < i) {
            maxque.pop_front();
        }
        while (ptr <= n) {
            if (ptr % 2 == 1) {
                if (!minque.empty() && minque.front().se <= prefix[ptr]) break;
                while (!maxque.empty() && maxque.back().se <= prefix[ptr]) {
                    maxque.pop_back();
                }
                maxque.pb({ptr, prefix[ptr]});
            } else {
                if (!maxque.empty() && maxque.front().se >= prefix[ptr]) break;
                while (!minque.empty() && minque.back().se >= prefix[ptr]) {
                    minque.pop_back();
                }
                minque.pb({ptr, prefix[ptr]});
            }
            ptr++;
        }
        satis[i] = ptr - 1;
    }
    LazySegmentTree<Info, Tag> dp(n + 1, {INF});
    dp.modify(n, {0});

    for (int i = n - 1; i >= 1; i--) {
        int  r   = satis[i];
        auto res = dp.rangeQuery(i + 1, r + 1);
        res.x += 1;
        dp.modify(i, res);
    }

    cout << n - dp.rangeQuery(1, 2).x << '\n';
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