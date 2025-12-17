#include <iostream>
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
 *@brief 笛卡尔树
 */

template <class T>
struct CartesianTree {
    int                        n;
    vector<int>                stk;
    vector<std::array<int, 2>> child;
    vector<T>                  data;
    int                        treeRoot;

public:
    // 1-idx
    CartesianTree(vector<T>&& _init) : n(_init.size() - 1), stk(n + 1), child(n + 1), data(std::move(_init)) { init(); }

    CartesianTree(const vector<T>& _init) : n(_init.size() - 1), stk(n + 1), child(n + 1), data(_init) { init(); }

    void init() noexcept
    {
        // stk 维护笛卡尔树中节点对应到序列中的下标
        int top = 0;
        for (int i = 1; i <= n; i++) {
            int k = top;                                  // top 表示操作前的栈顶，k 表示当前栈顶
            while (k > 0 && data[stk[k]] < data[i]) k--;  // 维护右链上的节点
            if (k) child[stk[k]][1] = i;                  // 栈顶元素.右儿子 := 当前元素
            if (k < top) child[i][0] = stk[k + 1];        // 当前元素.左儿子 := 上一个被弹出的元素
            stk[++k] = i;                                 // 当前元素入栈
            top      = k;
        }
        treeRoot = stk[1];
    }

    i64 dfs(int u)
    {
        i64 val = 0;
        for (int i = 0; i < 2; i++) {
            if (child[u][i]) {
                val = max(val, dfs(child[u][i]) + abs(u - child[u][i]));
            }
        }
        return val;
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    CartesianTree<int> ct(arr);
    cout << ct.dfs(ct.treeRoot) << '\n';
}

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int t = 1;
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