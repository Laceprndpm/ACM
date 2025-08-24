#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

struct SegTree {
    struct Node {
        int mx;
        int idx;
        int lazy;
    };

    int          n;
    vector<Node> st;

    SegTree(int n_ = 0)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        st.assign(4 * n + 10, {0, 0, 0});
        build(1, 1, n);
    }

    void build(int p, int l, int r)
    {
        if (l == r) {
            st[p].mx   = 0;
            st[p].idx  = l;
            st[p].lazy = 0;
            return;
        }
        int m = (l + r) >> 1;
        build(p << 1, l, m);
        build(p << 1 | 1, m + 1, r);
        pull(p);
        st[p].lazy = 0;
    }

    void apply(int p, int v)
    {
        st[p].mx += v;
        st[p].lazy += v;
    }

    void push(int p)
    {
        if (st[p].lazy != 0) {
            apply(p << 1, st[p].lazy);
            apply(p << 1 | 1, st[p].lazy);
            st[p].lazy = 0;
        }
    }

    void pull(int p)
    {
        if (st[p << 1].mx >= st[p << 1 | 1].mx) {
            st[p].mx  = st[p << 1].mx;
            st[p].idx = st[p << 1].idx;
        } else {
            st[p].mx  = st[p << 1 | 1].mx;
            st[p].idx = st[p << 1 | 1].idx;
        }
    }

    void addRange(int p, int l, int r, int L, int R, int val)
    {
        if (L > R || L > r || R < l) return;
        if (L <= l && r <= R) {
            apply(p, val);
            return;
        }
        push(p);
        int m = (l + r) >> 1;
        addRange(p << 1, l, m, L, R, val);
        addRange(p << 1 | 1, m + 1, r, L, R, val);
        pull(p);
    }

    // helpers
    void addRange(int L, int R, int val)
    {
        if (L > R) return;
        L = max(L, 1);
        R = min(R, n);
        if (L > R) return;
        addRange(1, 1, n, L, R, val);
    }

    // get global max and its index
    pair<int, int> getMax()
    {
        return {st[1].mx, st[1].idx};
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    // compress values to ids
    unordered_map<int, int> mp;
    mp.reserve(n * 2);
    int         idc = 0;
    vector<int> id(n + 1);
    for (int i = 1; i <= n; i++) {
        int  v  = a[i];
        auto it = mp.find(v);
        if (it == mp.end()) {
            mp[v] = ++idc;
            id[i] = idc;
        } else
            id[i] = it->second;
    }

    // positions per id
    vector<vector<int>> pos(idc + 1);
    for (int i = 1; i <= n; i++) pos[id[i]].push_back(i);

    // pos_values: for each position p, which ids appear at p
    vector<vector<int>> at(n + 2);
    for (int v = 1; v <= idc; ++v) {
        for (int p : pos[v]) at[p].push_back(v);
    }

    // prepare per-value data
    vector<int> first(idc + 1), last(idc + 1);
    for (int v = 1; v <= idc; ++v) {
        first[v] = pos[v][0];
        last[v]  = pos[v].back();
    }

    // idx[v] = pointer to first occurrence >= current b1
    vector<int> idx(idc + 1, 0);
    int         b1_init = 2;
    for (int v = 1; v <= idc; ++v) {
        // lower_bound on pos[v] for >= 2
        auto it = lower_bound(pos[v].begin(), pos[v].end(), b1_init);
        idx[v]  = (int)(it - pos[v].begin());  // may == size
    }

    // segment tree over b2 in [2..n], but we'll index tree from 1..n (we won't use index 1)
    // To keep indexing simple, we build tree for [1..n], answers will only be valid for b2 in [2..n]
    SegTree st(n);
    // initial add for those with first < 2 (i.e., first==1)
    for (int v = 1; v <= idc; ++v) {
        if (first[v] < b1_init && idx[v] < (int)pos[v].size()) {
            int mid = pos[v][idx[v]];
            int L   = mid + 1;
            int R   = last[v];
            if (L <= R) st.addRange(L, R, +1);
        }
    }

    int bestCnt = -1, bestB1 = 2, bestB2 = 2;
    // iterate b1 from 2..n-1
    for (int b1 = 2; b1 <= n - 1; ++b1) {
        // query best b2 for this b1
        auto pr     = st.getMax();  // {count, b2_index}
        int  curCnt = pr.first;
        int  curB2  = pr.second;
        if (curB2 < 2) curB2 = 2;  // safety
        if (curCnt > bestCnt) {
            bestCnt = curCnt;
            bestB1  = b1;
            bestB2  = curB2;
        }
        // prepare moving b1 -> b1+1 : handle position p = b1
        int p = b1;
        if (p <= n) {
            for (int v : at[p]) {
                if (first[v] == p) {
                    // becomes eligible at new b1 (b1+1)
                    // advance idx[v] if necessary to first >= b1+1
                    // current idx maybe points to >= b1 (we set earlier). But recompute lower_bound for robustness.
                    auto it = lower_bound(pos[v].begin(), pos[v].end(), b1 + 1);
                    idx[v]  = (int)(it - pos[v].begin());
                    if (idx[v] < (int)pos[v].size()) {
                        int mid = pos[v][idx[v]];
                        int L   = mid + 1;
                        int R   = last[v];
                        if (L <= R) st.addRange(L, R, +1);
                    }
                } else {
                    // first[v] < p, so v was possibly active. If its current mid_pos == p, we need to remove old
                    // interval and advance pointer
                    if (idx[v] < (int)pos[v].size() && pos[v][idx[v]] == p) {
                        // remove old [p+1, last]
                        int Lold = p + 1;
                        int Rold = last[v];
                        if (Lold <= Rold) st.addRange(Lold, Rold, -1);
                        // advance idx
                        idx[v]++;
                        if (idx[v] < (int)pos[v].size()) {
                            int mid = pos[v][idx[v]];
                            int L   = mid + 1;
                            int R   = last[v];
                            if (L <= R) st.addRange(L, R, +1);
                        }
                    }
                }
            }
        }
    }

    if (bestCnt < 0) bestCnt = 0;  // safety
    // output: print max count and one partition achieving it
    // ensure b1 in [2..n-1], b2 in [b1+1..n]
    if (bestB2 <= bestB1) bestB2 = bestB1 + 1;
    cout << bestCnt << "\n" << bestB1 << " " << bestB2 << "\n";
    return 0;
}
