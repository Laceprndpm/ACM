#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <map>
#include <set>
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

template <class Info>
struct SegmentTree {
    int          n;
    vector<Info> info;

    SegmentTree() : n(0) {}

    SegmentTree(int n_, Info v_ = Info())
    {
        init(n_, v_);
    }

    template <class T>
    SegmentTree(vector<T> init_)
    {
        init(init_);
    }

    void init(int n_, Info v_ = Info())
    {
        init(vector(n_, v_));
    }

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

    void pull(int p)
    {
        info[p] = info[2 * p] + info[2 * p + 1];
    }

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

    void modify(int p, const Info &v)
    {
        modify(1, 0, n, p, v);
    }

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

    Info rangeQuery(int l, int r)
    {
        return rangeQuery(1, 0, n, l, r);
    }

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
    pair<int, int> x{};
};

Info operator+(const Info &a, const Info &b)
{
    Info c;

    return {max(a.x, b.x)};
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

    int n;
    cin >> n;
    vector<int> vec(n);
    vector<int> sr;
    sr.reserve(n);
    for (int &i : vec) {
        cin >> i;
        sr.push_back(i + 1);
        sr.push_back(i);
        sr.push_back(i - 1);
    }
    sor(sr);
    sr.erase(unique(all(sr)), sr.end());
    for (int &i : vec) {
        i = lower_bound(all(sr), i) - bg(sr);
    }
    map<int, int> cnt;
    for (int i : vec) {
        cnt[i]++;
    }
    SegmentTree<Info> seg(3e3 + 50);
    auto              md = [&](int j) {
        seg.modify(j, {{cnt[j], j}});
    };
    for (auto [k, v] : cnt) {
        seg.modify(k, {{v, k}});
    }
    set<int> ans;
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            if (i == j) continue;
            cnt[vec[j]]--;
            cnt[vec[j] - 1]++;
            cnt[vec[i]]--;
            cnt[vec[i] + 1]++;
            md(vec[j]);
            md(vec[j] - 1);
            md(vec[i] + 1);
            md(vec[i]);
            auto mx = seg.rangeQuery(0, 3e3 + 50).x;
            ans.insert(mx.second);
            cnt[vec[j]]++;
            cnt[vec[j] - 1]--;
            cnt[vec[i]]++;
            cnt[vec[i] + 1]--;
            md(vec[j]);
            md(vec[j] - 1);
            md(vec[i] + 1);
            md(vec[i]);
        }
    }
    for (int i : ans) {
        cout << sr[i] << ' ';
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
// 先统计出当前众数，然后
// 看看有哪几个数可以被转换出来
// 以到达当前众数
// 优先转换考虑的众数
// 如果+1/-1无法转换到目标数，则用于减少
//
// 可以被转换，说明与众数数量差距小于等于2
// 对于数量<=1的，那么如果可以被其他数转换过来，那么一定可以
// 数量<=2的，如果两个都可以转换，则可以‘
// 如果其中有一个不能，则看看是否只有唯一一个众数
// 如果唯一，转换后会不会产生新的众数
//

// int n;
// cin >> n;
// map<int, int>            cnt;
// map<pair<int, int>, int> dto;
// for (int i = 0; i < n; i++) {
//     int u;
//     cin >> u;
//     cnt[u]++;
//     cnt[u - 1];
//     cnt[u + 1];
// }
// int         mxK = 0;
// vector<int> mx;
// for (auto it = cnt.begin(); it != cnt.end(); it++) {
//     if (it->second > cnt[mxK]) {
//         mx.clear();
//         mx.push_back(it->first);
//         mxK = it->first;
//     } else if (it->second == cnt[mxK]) {
//         mx.push_back(it->first);
//     }
// }
// vector<int> submx;
// vector<int> subsubmx;
// int         mxVal = cnt[mxK];
// for (auto it = cnt.begin(); it != cnt.end(); it++) {
//     if (it->second == mxVal - 1) {
//         submx.push_back(it->first);
//     } else if (it->second == mxVal - 2) {
//         subsubmx.push_back(it->first);
//     }
// }
// vector<int> ans = mx;
// for (int i : submx) {
//     if (cnt[i - 1] != 0 || cnt[i + 1] != 0) {
//         ans.push_back(i);
//     } else if (sz(mx) == 1 && (cnt[mxK - 1] < mxVal - 1 || cnt[mxK + 1] < mxVal - 1)) {
//         ans.push_back(i);
//     }
// }
// if (sz(mx) == 1) {
//     for (int i : subsubmx) {
//         if (cnt[i - 1] == 0 && cnt[i + 1] == 0) {
//             continue;
//         }
//         if (cnt[i - 1] == 0 && cnt[mxK + 1] + 1 == mxVal) {
//             continue;
//         }
//         if (cnt[i + 1] == 0 && cnt[mxK - 1] + 1 == mxVal) {
//             continue;
//         }
//         ans.push_back(i);
//     }
// }
// sor(ans);
// ans.erase(unique(all(ans)), ans.end());
// for (int i : ans) {
//     if (i == 0) continue;
//     cout << i << ' ';
// }
