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

template <class Info>
struct SegmentTree {
    vector<i64>  leftSon, rightSon;
    vector<Info> info;
    i64          cnt = 1;
    i64          n;

    void pull(int p)
    {
        info[p] = info[leftSon[p]] + info[rightSon[p]];
    }

    int newnode()
    {
        leftSon.emplace_back(0);
        rightSon.emplace_back(0);
        info.emplace_back(Info());
        return ++cnt;
    }

    void modify(i64 p, i64 l, i64 r, i64 x, const Info &v)
    {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        i64 mid = (r - l) / 2 + l;
        if (x < mid) {
            if (leftSon[p] == 0) {
                leftSon[p] = newnode();
            }
            modify(leftSon[p], l, mid, x, v);
        } else {
            if (rightSon[p] == 0) {
                rightSon[p] = newnode();
            }
            modify(rightSon[p], mid, r, x, v);
        }
        pull(p);
    }

    Info rangeQuery(i64 p, i64 l, i64 r, i64 x, i64 y)
    {

        if (l >= y || r <= x || p == 0) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        i64 m = (r - l) / 2 + l;
        return rangeQuery(leftSon[p], l, m, x, y) + rangeQuery(rightSon[p], m, r, x, y);
    }

    SegmentTree(i64 n_, i64 siz_ = 2e5) : n(n_)
    {
        leftSon.reserve(siz_ * 4);
        rightSon.reserve(siz_ * 4);
        info.reserve(siz_ * 4);
        leftSon.assign(2, 0);
        rightSon.assign(2, 0);
        info.assign(2, Info());
    }

    void modify(i64 x, const Info &value)
    {
        modify(1, 0, n, x, value);
    }

    Info rangeQuery(i64 l, i64 r)
    {
        return rangeQuery(1, 0, n, l, r);
    }

    void rangeClear(i64 p, i64 l, i64 r, i64 x, i64 y)
    {

        if (l >= y || r <= x || p == 0) {
            return;
        }
        if (l >= x && r <= y) {
            info[p]     = Info();
            leftSon[p]  = 0;
            rightSon[p] = 0;  // 此处可控泄露
            return;
        }
        i64 m = (r - l) / 2 + l;
        rangeClear(leftSon[p], l, m, x, y);
        rangeClear(rightSon[p], m, r, x, y);
        pull(p);
    }

    void rangeClear(i64 l, i64 r)
    {
        rangeClear(1, 0, n, l, r);
    }
};

struct Info {
    i64 num = 0;
    i64 val = 0;
};

Info operator+(const Info &a, const Info &b)
{
    return {a.num + b.num, a.val + b.val};
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
    int n, m;
    cin >> n >> m;
    vector<int>       arr(n);
    SegmentTree<Info> seg((i64)1e9 + 50);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    for (int i = 0; i < n; i++) {
        auto x = seg.rangeQuery(arr[i], arr[i] + 1);
        seg.modify(arr[i], x + Info{1, arr[i]});
    }
    cout << seg.rangeQuery(0, 1e9 + 1).val << '\n';
    while (m--) {
        i64 L, R, X;
        cin >> L >> R >> X;
        R++;
        auto rangeNum = seg.rangeQuery(L, R);
        rangeNum.val  = rangeNum.num * X;
        seg.rangeClear(L, R);
        auto origin = seg.rangeQuery(X, X + 1);
        seg.modify(X, rangeNum + origin);
        cout << seg.rangeQuery(0, 1e9 + 1).val << '\n';
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