#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
#define fi first
#define se second
#define pb push_back

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

    void init(int n_, Info v_ = Info()) { init(vector<Info>(n_, v_)); }

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

    void update(int p, int l, int r, int x, const int &v)
    {
        if (r - l == 1) {
            info[p].x += v;
            return;
        }
        int m = (l + r) / 2;
        push(p);
        if (x < m) {
            update(2 * p, l, m, x, v);
        } else {
            update(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }

    void update(int p, const int &v) { update(1, 0, n, p, v); }

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
};

struct Tag {
    // nothing
    void apply(const Tag &t) {}
};

struct Info {
    i64 x = 0;

    Info(i64 x_) { x = x_; }

    Info() {}

    void apply(const Tag &t) {}
};

Info operator+(const Info &a, const Info &b) { return {max(a.x, b.x)}; }

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> farr(n + 1);
    vector<int> isfrind(k + 1);
    for (int i = 1; i <= n; i++) {
        cin >> farr[i];
        isfrind[farr[i]] = 1;
    }
    vector<pair<int, int>> arr(m + 1);
    vector<vector<int>>    go(k + 1);
    int                    baseans = 0;
    vector<int>            bounds(k + 1);
    for (int i = 1; i <= m; i++) {
        cin >> arr[i].fi;
        cin >> arr[i].se;
        if (arr[i].fi > arr[i].se) swap(arr[i].fi, arr[i].se);
        if (isfrind[arr[i].fi] && isfrind[arr[i].se]) {
            baseans++;
        } else if (isfrind[arr[i].fi]) {
            bounds[arr[i].se]++;
        } else if (isfrind[arr[i].se]) {
            bounds[arr[i].fi]++;
        } else if (arr[i].fi == arr[i].se) {
            bounds[arr[i].fi]++;
        } else {
            go[arr[i].fi].pb(arr[i].se);
        }
    }
    LazySegmentTree<Info, Tag> lzt(bounds);
    i64                        ans = 0;
    for (int i = 1; i <= k; i++) {
        i64 cur = bounds[i];
        for (int v : go[i]) {
            lzt.update(v, 1);
        }
        ans = max(ans, baseans + cur + lzt.rangeQuery(i + 1, k + 1).x);
        for (int v : go[i]) {
            lzt.update(v, -1);
        }
    }
    cout << ans << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}