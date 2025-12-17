#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include <set>
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

/**
 * @brief 并查集
 * 0-index
 */

struct DSU {
    int              component;
    std::vector<int> f, siz;

    DSU() {}

    DSU(int n) : component(n) { init(n); }

    void init(int n)
    {
        f.resize(n);
        std::iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
    }

    int find(int x)
    {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }

    bool same(int x, int y) { return find(x) == find(y); }

    bool merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        siz[x] += siz[y];
        f[y] = x;
        component--;
        return true;
    }

    int size(int x) { return siz[find(x)]; }
};

template <typename T>
struct MergeHeap {

    struct Node {
        T   v;  // T为权值类型
        int child = 0, sibling = 0;
        // child 指向该节点第一个儿子，sibling 指向该节点的下一个兄弟。
        // 若该节点没有儿子/下个兄弟则指针指向 nullptr。
        Node() {};

        Node(T x) { v = x; }
    };

    static vector<Node> data_;
    static int          cnt;
    int                 root;
    int                 siz;

    static void super_init()
    {
        cnt = 0;
        data_.resize(1);
    }

    MergeHeap()
    {
        root = 0;
        siz  = 0;
    }

    MergeHeap& push(T x)
    {
        int u    = newnode();
        data_[u] = x;
        root     = meld(root, u);
        siz++;
        return *this;
    }

    MergeHeap& pop(void)
    {
        root = delete_min(root);
        siz--;
        return *this;
    }

    MergeHeap& merges(MergeHeap& ot)
    {
        this->root = meld(this->root, ot.root);
        this->siz += ot.siz;
        ot.root = 0;
        ot.siz  = 0;
        return *this;
    }

    T top(void) { return data_[root].v; }

    bool empty() { return siz == 0; }

private:
    int newnode()
    {
        if (data_.size() <= cnt + 1) {
            data_.pb({});
        }
        return ++cnt;
    }

    int meld(int x, int y)
    {
        // 若有一个为空则直接返回另一个
        if (x == 0) return y;
        if (y == 0) return x;
        if (data_[x].v > data_[y].v)
            std::swap(x, y);  // swap后x为权值小的堆，y为权值大的堆
                              // 将y设为x的儿子
        data_[y].sibling = data_[x].child;
        data_[x].child   = y;
        return x;  // 新的根节点为 x
    }

    int merges_impl(int x)
    {
        if (x == 0 || data_[x].sibling == 0) return x;  // 如果该树为空或他没有下一个兄弟，就不需要合并了，return。
        int y            = data_[x].sibling;            // y 为 x 的下一个兄弟
        int c            = data_[y].sibling;            // c 是再下一个兄弟
        data_[x].sibling = data_[y].sibling = 0;        // 拆散
        return meld(merges_impl(c), meld(x, y));        // 核心部分
    }

    int delete_min(int x)
    {
        int t = merges_impl(data_[x].child);
        return t;
    }
};

template <typename T>
std::vector<typename MergeHeap<T>::Node> MergeHeap<T>::data_;

template <typename T>
int MergeHeap<T>::cnt = 0;

void solve()
{
    MergeHeap<pair<int, int>>::super_init();
    i64 n, m;
    cin >> n >> m;
    vector<array<int, 3>>             edges(m + 1);
    vector<int>                       idx(m + 1);
    vector<int>                       deg(n + 1);
    i64                               ans = 0;
    vector<MergeHeap<pair<int, int>>> nxtedge(n + 1);
    for (int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        edges[i] = {u, v, w};
        nxtedge[u].push({i, v});
        nxtedge[v].push({i, u});
        deg[u]++, deg[v]++;
        ans += w;
    }
    vector<int> cnt(n + 1);
    for (int i = 1; i <= n; i++) {
        if (deg[i] % 2) {
            cnt[i]++;
        }
    }
    iota(all(idx), 0);
    sort(idx.begin() + 1, idx.end(), [&](int a, int b) { return edges[a][2] < edges[b][2]; });
    DSU dsu(n + 1);
    for (int i = 1; i <= m; i++) {
        int curid = idx[i];
        int u     = edges[curid][0];
        int uid   = dsu.find(u);
        while (!nxtedge[uid].empty() && nxtedge[uid].top().first <= curid) {
            auto [_, cv] = nxtedge[uid].top();
            nxtedge[uid].pop();
            if (!dsu.same(u, cv)) {
                cnt[uid] += cnt[dsu.find(cv)];
                nxtedge[uid].merges(nxtedge[dsu.find(cv)]);
                dsu.merge(u, cv);
            }
        }
        ans += cnt[uid] / 2ll * edges[curid][2];
        cnt[dsu.find(edges[curid][0])] %= 2;
    }
    cout << ans << '\n';
}

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
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