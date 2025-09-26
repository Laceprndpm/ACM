#include <algorithm>
#include <functional>
#include <iostream>
#include <set>
#include <vector>
using namespace std;
using i64 = long long;

constexpr int INF = 1e9;

template <class Info>
struct SegmentTree {
    int          n;
    vector<Info> info;

    SegmentTree() : n(0) {}

    SegmentTree(int n_, Info v_ = Info()) { init(n_, v_); }

    template <class T>
    SegmentTree(vector<T> init_)
    {
        init(init_);
    }

    void init(int n_, Info v_ = Info()) { init(vector(n_, v_)); }

    template <class T>
    void init(vector<T> init_)
    {
        n = init_.size();
        info.assign(4 << __lg(n), Info());
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

    void modify(int p, int l, int r, int x, const Info &v)
    {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
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
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }

    Info rangeQuery(int l, int r) { return rangeQuery(1, 0, n, l, r); }

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
        int m   = (l + r) / 2;
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
        int m   = (l + r) / 2;
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
};

struct Info {
    int x;

    Info() : x(INF) {}

    Info(int _x) : x(_x) {}
};

Info operator+(const Info &a, const Info &b) { return {min(a.x, b.x)}; }

int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> hi(n + 1);  // 读入每个点的高度
    for (int i = 1; i <= n; i++) {
        cin >> hi[i];
    }
    // 当前在i点，如果从j点跳过来
    SegmentTree<Info> seg_subtract(2e4);
    // 假设h_i > h_j，则dp[i] = dp[j] + |h_i - h_j| = (dp[j] - h_j) + h_i
    SegmentTree<Info> seg_add(2e4);
    // 即h_i <= h_j，的情况，同理，dp[i] = dp[j] + |h_i - h_j| = (dp[j] + h_j) - h_i
    //
    vector<multiset<int>> multisets(2e4);
    vector<int>           dp(n + 1, INF);  // 初始化为无穷大
    auto                  update = [&](int i) {
        multisets[hi[i]].insert(dp[i]);
        seg_subtract.modify(hi[i], Info{*multisets[hi[i]].begin() - hi[i]});
        seg_add.modify(hi[i], Info{*multisets[hi[i]].begin() + hi[i]});
    };

    auto remove = [&](int i) {
        multisets[hi[i]].extract(dp[i]);
        if (multisets[hi[i]].empty()) {
            seg_subtract.modify(hi[i], Info{});
            seg_add.modify(hi[i], Info{});
            return;
        }
        seg_subtract.modify(hi[i], Info{*multisets[hi[i]].begin() - hi[i]});
        seg_add.modify(hi[i], Info{*multisets[hi[i]].begin() + hi[i]});
    };
    dp[1] = 0;
    update(1);
    for (int i = 2; i <= n; i++) {
        if (i - k - 1 >= 1) {
            remove(i - k - 1);
        }
        dp[i] = min(dp[i], seg_add.rangeQuery(hi[i], 2e4).x - hi[i]);
        dp[i] = min(dp[i], seg_subtract.rangeQuery(0, hi[i]).x + hi[i]);
        update(i);
    }
    cout << dp[n] << '\n';
    return 0;
}
