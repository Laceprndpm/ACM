#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
using Graph       = vector<vector<int>>;
constexpr int INF = INT32_MAX;
constexpr int inf = 1e9;
int           n, m, r, p;
#ifndef REMOVE_ME
#include <bits/stdc++.h>
using i64 = long long;
#endif
template <class T>
constexpr T power(T a, i64 b)
{
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

constexpr i64 mul(i64 a, i64 b, i64 p)
{
    i64 res = a * b - i64(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) {
        res += p;
    }
    return res;
}

template <i64 P>
struct MLong {
    i64 x;

    constexpr MLong() : x{} {}

    constexpr MLong(i64 x) : x{norm(x % getMod())} {}

    static i64 Mod;

    constexpr static i64 getMod()
    {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }

    constexpr static void setMod(i64 Mod_)
    {
        Mod = Mod_;
    }

    constexpr i64 norm(i64 x) const
    {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }

    constexpr i64 val() const
    {
        return x;
    }

    explicit constexpr operator i64() const
    {
        return x;
    }

    constexpr MLong operator-() const
    {
        MLong res;
        res.x = norm(getMod() - x);
        return res;
    }

    constexpr MLong inv() const
    {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }

    constexpr MLong &operator*=(MLong rhs) &
    {
        x = mul(x, rhs.x, getMod());
        return *this;
    }

    constexpr MLong &operator+=(MLong rhs) &
    {
        x = norm(x + rhs.x);
        return *this;
    }

    constexpr MLong &operator-=(MLong rhs) &
    {
        x = norm(x - rhs.x);
        return *this;
    }

    constexpr MLong &operator/=(MLong rhs) &
    {
        return *this *= rhs.inv();
    }

    friend constexpr MLong operator*(MLong lhs, MLong rhs)
    {
        MLong res = lhs;
        res *= rhs;
        return res;
    }

    friend constexpr MLong operator+(MLong lhs, MLong rhs)
    {
        MLong res = lhs;
        res += rhs;
        return res;
    }

    friend constexpr MLong operator-(MLong lhs, MLong rhs)
    {
        MLong res = lhs;
        res -= rhs;
        return res;
    }

    friend constexpr MLong operator/(MLong lhs, MLong rhs)
    {
        MLong res = lhs;
        res /= rhs;
        return res;
    }

    friend constexpr std::istream &operator>>(std::istream &is, MLong &a)
    {
        i64 v;
        is >> v;
        a = MLong(v);
        return is;
    }

    friend constexpr std::ostream &operator<<(std::ostream &os, const MLong &a)
    {
        return os << a.val();
    }

    friend constexpr bool operator==(MLong lhs, MLong rhs)
    {
        return lhs.val() == rhs.val();
    }

    friend constexpr bool operator!=(MLong lhs, MLong rhs)
    {
        return lhs.val() != rhs.val();
    }
};

template <>
i64 MLong<0LL>::Mod = i64(1E18) + 9;

template <int P>
struct MInt {
    int x;

    constexpr MInt() : x{} {}

    constexpr MInt(i64 x) : x{norm(x % getMod())} {}

    static int Mod;

    constexpr static int getMod()
    {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }

    constexpr static void setMod(int Mod_)
    {
        Mod = Mod_;
    }

    constexpr int norm(int x) const
    {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }

    constexpr int val() const
    {
        return x;
    }

    explicit constexpr operator int() const
    {
        return x;
    }

    constexpr MInt operator-() const
    {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }

    constexpr MInt inv() const
    {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }

    constexpr MInt &operator*=(MInt rhs) &
    {
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }

    constexpr MInt &operator+=(MInt rhs) &
    {
        x = norm(x + rhs.x);
        return *this;
    }

    constexpr MInt &operator-=(MInt rhs) &
    {
        x = norm(x - rhs.x);
        return *this;
    }

    constexpr MInt &operator/=(MInt rhs) &
    {
        return *this *= rhs.inv();
    }

    friend constexpr MInt operator*(MInt lhs, MInt rhs)
    {
        MInt res = lhs;
        res *= rhs;
        return res;
    }

    friend constexpr MInt operator+(MInt lhs, MInt rhs)
    {
        MInt res = lhs;
        res += rhs;
        return res;
    }

    friend constexpr MInt operator-(MInt lhs, MInt rhs)
    {
        MInt res = lhs;
        res -= rhs;
        return res;
    }

    friend constexpr MInt operator/(MInt lhs, MInt rhs)
    {
        MInt res = lhs;
        res /= rhs;
        return res;
    }

    friend constexpr std::istream &operator>>(std::istream &is, MInt &a)
    {
        i64 v;
        is >> v;
        a = MInt(v);
        return is;
    }

    friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a)
    {
        return os << a.val();
    }

    friend constexpr bool operator==(MInt lhs, MInt rhs)
    {
        return lhs.val() == rhs.val();
    }

    friend constexpr bool operator!=(MInt lhs, MInt rhs)
    {
        return lhs.val() != rhs.val();
    }
};

template <>
int MInt<0>::Mod = 998244353;

template <int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();

constexpr int P = 998244353;
using Z         = MInt<P>;

template <class Info, class Tag>
struct LazySegmentTree {
    int          n;
    vector<Info> info;
    vector<Tag>  tag;
    vector<i64>  leftB;
    vector<i64>  rightB;

    LazySegmentTree() : n(0) {}

    LazySegmentTree(int _n, Info _v = Info())
    {
        init(_n, _v);
    }

    template <class T>
    LazySegmentTree(vector<T> _init)
    {
        init(_init);
    }

    void init(int _n, Info _v = Info())
    {
        init(vector(_n, _v));
    }

    template <class T>
    void init(vector<T> _init)
    {
        n = _init.size();
        info.assign(4 << __lg(n), Info());
        tag.assign(4 << __lg(n), Tag());
        leftB.resize(4 << __lg(n));
        rightB.resize(4 << __lg(n));
        function<void(int, int, int)> build = [&](int p, int l, int r) {
            leftB[p]  = l;
            rightB[p] = r;
            if (r == l) {
                info[p] = _init[l];
                return;
            }
            int m = (r - l) / 2 + l;
            build(2 * p, l, m);
            build(2 * p + 1, m + 1, r);
            pull(p);
        };
        build(1, 0, n);
    }

    void pull(int p)
    {
        info[p] = info[2 * p] + info[2 * p + 1];
    }

    void apply(int p, const Tag &v)
    {
        info[p].apply(v, rightB[p] - leftB[p] + 1);
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
        if (r == l) {
            info[p] = v;
            return;
        }
        int m = (r - l) / 2 + l;
        push(p);
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m + 1, r, x, v);
        }
        pull(p);
    }

    void modify(int p, const Info &v)
    {
        modify(1, 0, n, p, v);
    }

    Info rangeQuery(int p, int l, int r, int x, int y)
    {
        if (l >= x && r <= y) {
            return info[p];
        }
        if (l > y || r < x) {
            return Info();
        }
        int m = (r - l) / 2 + l;
        push(p);
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m + 1, r, x, y);
    }

    Info rangeQuery(int l, int r)
    {
        return rangeQuery(1, 0, n, l, r);
    }

    void rangeApply(int p, int l, int r, int x, int y, const Tag &v)
    {
        if (l > y || r < x) {
            return;
        }
        if (l >= x && r <= y) {
            apply(p, v);
            return;
        }
        int m = (r - l) / 2 + l;
        push(p);
        rangeApply(2 * p, l, m, x, y, v);
        rangeApply(2 * p + 1, m + 1, r, x, y, v);
        pull(p);
    }

    void rangeApply(int l, int r, const Tag &v)
    {
        return rangeApply(1, 0, n, l, r, v);
    }
};

struct Tag {
    i64 x = 0;

    void apply(const Tag &t) &
    {
        x = x + t.x;
    }
};

struct Info {
    i64 x = 0;

    void apply(const Tag &t, i64 c) &
    {
        x = x + t.x * c;
    }
};

// Removed operator= function as it should be a member function

Info operator+(const Info &a, const Info &b)
{
    return {a.x + b.x};
}

int init()
{
    char c = getchar();
    int  x = 0, f = 1;
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-') f = -1;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = (x << 1) + (x << 3) + (c ^ 48);
    return x * f;
}

void print(int x)
{
    if (x < 0) x = -x, putchar('-');
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

class DivTree {
private:
    const vector<vector<int>> &graph;

    int         n;
    vector<int> sizeSons;
    vector<int> weightChild;
    vector<int> depthNode;
    vector<int> topWeightChainNode;
    vector<int> DFSnum;
    vector<int> father;
    int         dfsCnt;

    LazySegmentTree<Info, Tag> lazyST_obj;

    void dfs1(int root, int last)
    {
        sizeSons[root] = 1;
        for (int i : graph[root]) {
            if (i == last) continue;
            depthNode[i] = depthNode[root] + 1;
            father[i]    = root;
            dfs1(i, root);
            sizeSons[root] += sizeSons[i];
            if (weightChild[root] == 0 || sizeSons[weightChild[root]] < sizeSons[i]) {
                weightChild[root] = i;
            }
        }
    };

    void dfs2(int root, int top, int last)
    {
        topWeightChainNode[root] = top;
        DFSnum[root]             = ++dfsCnt;
        if (weightChild[root] != 0) dfs2(weightChild[root], top, root);
        for (int i : graph[root]) {
            if (i == weightChild[root] || i == last) continue;
            dfs2(i, i, root);
        }
    };

public:
    DivTree(const vector<vector<int>> &_graph, int r, const vector<Info> &arr)
        : graph(_graph),
          n(graph.size() - 1),
          sizeSons(n + 1),
          weightChild(n + 1),
          depthNode(n + 1),
          topWeightChainNode(n + 1),
          DFSnum(n + 1),
          father(n + 1)
    {
        dfsCnt       = 0;
        depthNode[r] = 1;
        dfs1(r, -1);
        dfs2(r, r, -1);
        vector<Info> brr(n + 1);
        for (int i = 1; i <= n; i++) {
            brr[DFSnum[i]] = arr[i];
        }
        lazyST_obj.init(brr);
    };

    void update(int x, int y, Tag z)
    {
        while (topWeightChainNode[x] != topWeightChainNode[y]) {
            if (depthNode[topWeightChainNode[x]] < depthNode[topWeightChainNode[y]]) {
                swap(x, y);
            }
            lazyST_obj.rangeApply(DFSnum[topWeightChainNode[x]], DFSnum[x], z);
            x = father[topWeightChainNode[x]];
        }
        lazyST_obj.rangeApply(min(DFSnum[x], DFSnum[y]), max(DFSnum[x], DFSnum[y]), z);
    };

    void update(int x, Tag z)
    {
        lazyST_obj.rangeApply(DFSnum[x], DFSnum[x] + sizeSons[x] - 1, z);
    }

    Info query(int x, int y)
    {
        Info ans;
        while (topWeightChainNode[x] != topWeightChainNode[y]) {
            if (depthNode[topWeightChainNode[x]] < depthNode[topWeightChainNode[y]]) {
                swap(x, y);
            }
            ans = ans + lazyST_obj.rangeQuery(DFSnum[topWeightChainNode[x]], DFSnum[x]);
            x   = father[topWeightChainNode[x]];
        }
        ans = ans + lazyST_obj.rangeQuery(min(DFSnum[x], DFSnum[y]), max(DFSnum[x], DFSnum[y]));
        return ans;
    };

    Info query(int x)
    {
        return lazyST_obj.rangeQuery(DFSnum[x], DFSnum[x] + sizeSons[x] - 1);
    }
};

signed main(int argc, char **argv)
{
    n = init();
    m = init();
    r = init();
    p = init();
    Graph        graph(n + 1);
    vector<Info> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        arr[i].x = init();
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        u = init();
        v = init();
        graph[u].emplace_back(v);
        graph[v].emplace_back(u);
    }
    DivTree dt(graph, r, arr);
    for (int i = 0; i < m; i++) {
        int op;
        op = init();
        int x, y, z;
        switch (op) {
            case 1:
                x = init(), y = init(), z = init();
                dt.update(x, y, {z});
                break;
            case 2:
                x = init(), y = init();
                print(dt.query(x, y).x % p);
                putchar('\n');
                break;
            case 3:
                x = init(), z = init();
                dt.update(x, {z});
                break;
            case 4:
                x = init();
                print(dt.query(x).x % p);
                putchar('\n');
                break;
        }
    }
    return 0;
}
