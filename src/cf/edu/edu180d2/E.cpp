#include <iostream>
#include <vector>

#include "vector"
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

struct Solve {
    vector<i64> tree, helper;

    Solve(int n)
    {
        sieve(n);
    }

    void sieve(int n)
    {
        tree.assign(n + 50, INF);
        helper.assign(n + 50, INF);
        tree[1]   = 1;
        helper[3] = 1;
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j * j <= i; j++) {
                if (i % j == 0) {
                    if (j - 2 >= 0) tree[i] = min(tree[i], tree[j - 2] + helper[i / j]);
                    if (i / j - 2 >= 0) tree[i] = min(tree[i], tree[i / j - 2] + helper[j]);
                }
            }
            for (int j = 1; j * (i + 2) <= n; j++) {
                helper[j * (i + 2)] = min(helper[j * (i + 2)], helper[j] + tree[i]);
            }
        }
    }
} pp(1e5);

// f为绿，则3**s,f非绿,2
// dp = dps累乘 + 2
// f = (x * y * z + 2)
// tree[i]为方案为i的子树中
// 至少要多少节点
// tree[t] = min{x,y,z|x * y * z... + 2 == t}(tree[x] + tree[y] + tree[z]... + 1) tree[t]为方案数为t的树支需要多少节点
// tree[t] = min{x, y, z | (x + 2)(y + 2)(z + 2)... = t}(tree[x] + tree[y] + tree[z]... + 1)
// tree[t]为方案数为t的树需要多少节点
//
void solve() {}

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    // the route on a tree of two points is fixed
    // so...
    // obvisouly，菊花图
    // 哦不，恰好。。。
    // 但是我可以算出来最高效率时
    // 考虑n+1节点的菊花图
    // 3**n
    // 增长一格，是最优的吗？即保持链状结构是否优秀？
    // 当增长一格，这一格在原本链可以为同色的情况下，这一格也可以为绿，然后归入根节点
    // 但是此时，会有重复考虑的情况，所以要-1
    // (3 * 2 - 1) * 2 - 1
    // (3 + 2 + 2)
    // 最终的方案数为 (3 + ki * 2) 的次方?
    // 当前点的DPg = accum_S(3) + sum(Sg) - 1
    //         Dng = 2
    // 1  2  3  4
    // 7  5  3  1
    // Y:
    // 1-2-3
    //   \4
    // 3:1
    // 4:1
    // 2:4 + 2
    // 1:2 + 6 = 8
    // Sum_v(2 ** v_Sons)
    // 也许没那么复杂，真就是3 + 2 + 2 然后相乘？
    // Y型，全g:1,一个不是g:2,两个不是g:4,三个不是g:2
    // 1 + 2 + 4 + 2 = 9
    // 如果是0-f-ssssss
    //
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        if (n % 2)
            cout << pp.tree[n] << '\n';
        else
            cout << -1 << '\n';
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