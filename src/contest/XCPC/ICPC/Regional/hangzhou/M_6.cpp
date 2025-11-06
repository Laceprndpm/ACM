#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

i64 gcd(i64 a, i64 b)
{
#define tz __builtin_ctzll
    if (!a || !b) return a | b;
    int t = tz(a | b);
    a >>= tz(a);
    while (b) {
        b >>= tz(b);
        if (a > b) swap(a, b);
        b -= a;
    }
    return a << t;
#undef tz
}

constexpr auto gcd_multi(auto x, auto... args)
{
    if constexpr (sizeof...(args) == 0) {
        return x;
    } else {
        if (x == 1) return 1;
        return gcd(x, gcd_multi(args...));
    }
}

template <class T>
class CartesianTree {
    const int   n;
    vector<int> rs;
    vector<int> ls;
    vector<T>   data;
    int         treeRoot;
    vector<int> nodeGcd;

public:
    // 1-idx
    CartesianTree(vector<T>&& _init) : n(_init.size() - 1), rs(n + 1), ls(n + 1), data(std::move(_init))
    {
        assert(!_init.empty());
        init(data);
    }

    CartesianTree(const vector<T>& _init) : n(_init.size() - 1), rs(n + 1), ls(n + 1), data(_init)
    {
        assert(!_init.empty());
        init(data);
    }

    void init(const vector<T>& w)
    {
        // stk 维护笛卡尔树中节点对应到序列中的下标
        int         top = 0;
        vector<int> stk(n + 1);
        for (int i = 1; i <= n; i++) {
            int k = top;                            // top 表示操作前的栈顶，k 表示当前栈顶
            while (k > 0 && w[stk[k]] > w[i]) k--;  // 维护右链上的节点
            if (k) rs[stk[k]] = i;                  // 栈顶元素.右儿子 := 当前元素
            if (k < top) ls[i] = stk[k + 1];        // 当前元素.左儿子 := 上一个被弹出的元素
            stk[++k] = i;                           // 当前元素入栈
            top      = k;
        }
        treeRoot = stk[1];
        nodeGcd.assign(n + 1, 0);
        DFS1(treeRoot);
    }

    void DFS1(int root)
    {
        int curGcd = 0;
        if (ls[root] != 0) {
            DFS1(ls[root]);
            curGcd = gcd_multi(curGcd, nodeGcd[ls[root]], data[ls[root]] - data[root]);
        }
        if (rs[root] != 0) {
            DFS1(rs[root]);
            curGcd = gcd_multi(curGcd, nodeGcd[rs[root]], data[rs[root]] - data[root]);
        }
        nodeGcd[root] = curGcd;
    }

    bool check(int x) { return DFS2(treeRoot, x); }

    bool DFS2(int root, int x)
    {
        if (nodeGcd[root] % (data[root] + x) != 0) {
            return false;
        }
        bool res = true;
        if (ls[root] != 0) {
            res &= DFS2(ls[root], x);
        }
        if (res && rs[root] != 0) {
            res &= DFS2(rs[root], x);
        }
        return res;
    }
};

void solve()
{
    i64 n, k;
    cin >> n >> k;

    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    CartesianTree<int> cartree(arr);
    sort(arr.begin() + 1, arr.end());
    arr.erase(unique(arr.begin() + 1, arr.end()), arr.end());
    n = arr.size() - 1;
    if (n == 1) {
        cout << k << ' ' << (k + 1) * k / 2 << '\n';
        return;
    }
    i64 gcdans = 0;
    for (int i = 2; i <= n; i++) {
        gcdans = gcd(gcdans, arr[i] - arr[i - 1]);
    }
    i64         totalans = 0;
    i64         cnt      = 0;
    vector<i64> candi;
    for (i64 factor = 1; factor * factor <= gcdans; factor++) {
        if (gcdans % factor == 0) {
            candi.push_back(gcdans / factor);
            if (factor * factor != gcdans) candi.push_back(factor);
        }
    }
    sort(candi.begin(), candi.end());
    for (i64 ca : candi) {
        i64 x = ca - arr[1];
        if (x < 1) continue;
        if (x > k) break;
        if (cartree.check(x)) {
            totalans += x;
            cnt++;
        }
    }
    cout << cnt << ' ' << totalans << '\n';
}

signed main(int argc, char** argv)
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