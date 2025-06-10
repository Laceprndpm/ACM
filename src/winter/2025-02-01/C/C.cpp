// #ifdef V1
// #include <bits/stdc++.h>
// using namespace std;
// using LL = long long;
// int m, k, n;

// inline int init()
// {
//     char c = getchar();
//     int  x = 0, f = 1;
//     for (; c < '0' || c > '9'; c = getchar())
//         if (c == '-')
//             f = -1;
//     for (; c >= '0' && c <= '9'; c = getchar())
//         x = (x << 1) + (x << 3) + (c ^ 48);
//     return x * f;
// }

// inline void print(int x)
// {
//     if (x < 0)
//         x = -x, putchar('-');
//     if (x > 9)
//         print(x / 10);
//     putchar(x % 10 + '0');
// }

// class SegmentTree {
// private:
//     std::vector<int> tree;
//     std::vector<int> lazy;
//     int              size;

//     inline void pushDown(int node, int start, int end)
//     {
//         if (lazy[node] == 1) {
//             if (start != end) {
//                 lazy[2 * node]     = 1;
//                 lazy[2 * node + 1] = 1;
//                 tree[2 * node]     = 0;
//                 tree[2 * node + 1] = 0;
//             }
//             lazy[node] = 0;
//         }
//     }

//     void rangeClear(int node, int start, int end, int l, int r)
//     {
//         if (r < start || end < l) {
//             return;
//         }
//         if (l <= start && end <= r) {
//             tree[node] = 0;
//             lazy[node] = 1;
//             return;
//         }
//         if (tree[node] == 0) {
//             return;
//         }
//         // pushDown(node, start, end);
//         int mid = (start + end) >> 1;
//         rangeClear(2 * node, start, mid, l, r);
//         rangeClear(2 * node + 1, mid + 1, end, l, r);
//         tree[node] = tree[2 * node] + tree[2 * node + 1];
//     }

//     int rangeQuery(int node, int start, int end, int l, int r)
//     {
//         if (r < start || end < l) {
//             return 0;
//         }
//         if (l <= start && end <= r) {
//             return tree[node];
//         }
//         if (tree[node] == 0) {
//             return 0;
//         }
//         pushDown(node, start, end);
//         int mid        = (start + end) >> 1;
//         int leftQuery  = rangeQuery(2 * node, start, mid, l, r);
//         int rightQuery = rangeQuery(2 * node + 1, mid + 1, end, l, r);
//         return leftQuery + rightQuery;
//     }

//     void pointUpdate(int node, int start, int end, int idx, int value)
//     {
//         // pushDown(node, start, end);
//         if (start == end) {
//             tree[node] = value;
//             return;
//         }
//         int mid = (start + end) >> 1;
//         if (idx <= mid) {
//             pointUpdate(2 * node, start, mid, idx, value);
//         } else {
//             pointUpdate(2 * node + 1, mid + 1, end, idx, value);
//         }
//         // tree[node] = tree[2 * node] + tree[2 * node + 1];
//     }

//     void everythinguptodate(int node, int start, int end)
//     {
//         if (start == end) {
//             return;
//         }
//         int mid = (start + end) >> 1;
//         everythinguptodate(2 * node, start, mid);
//         everythinguptodate(2 * node + 1, mid + 1, end);
//         tree[node] = tree[2 * node] + tree[2 * node + 1];
//     }

// public:
//     SegmentTree(int n) : tree(4 * (n + 1), 0), lazy(4 * (n + 1), 0), size(n)
//     {
//     }

//     void rangeClear(int l, int r)
//     {
//         rangeClear(1, 1, size, l, r);
//     }

//     int rangeQuery(int l, int r)
//     {
//         return rangeQuery(1, 1, size, l, r);
//     }

//     void pointUpdate(int idx, int value)
//     {
//         pointUpdate(1, 1, size, idx, value);
//     }

//     void everythinguptodate()
//     {
//         everythinguptodate(1, 1, size);
//     }
// };

// signed main(int argc, char** argv)
// {
// #ifndef ONLINE_JUDGE
//     freopen(argv[1], "r", stdin);
//     freopen(argv[2], "w", stdout);
// #endif

//     // ios::sync_with_stdio(false);
//     // cin.tie(0);
//     // cout.tie(0);
//     m = init();
//     k = init();
//     vector<int>             input(m);
//     unordered_map<int, int> countVal;
//     for (int i = 0; i < m; i++) {
//         input[i] = init();
//         countVal[input[i]]++;
//     }

//     set<int> uniqueSet(input.begin(), input.end());
//     uniqueSet.insert(0);  // padding
//     uniqueSet.insert(INT32_MAX);
//     countVal[0]         = 0;
//     countVal[INT32_MAX] = 0;

//     int                     rank = 0;
//     unordered_map<int, int> val2rank;
//     vector<int>             rank2val(uniqueSet.size() + 1);
//     for (int i : uniqueSet) {
//         val2rank[i]    = rank;
//         rank2val[rank] = i;
//         rank++;
//     }
//     n                   = init();
//     int         lastans = 0;
//     SegmentTree tre(rank);
//     for (int i = 0; i <= rank; i++) {
//         tre.pointUpdate(i, countVal[rank2val[i]]);
//     }
//     tre.everythinguptodate();
//     // map<int, pair<int, int>> buffer;
//     for (int i = 1; i <= n; i++) {
//         int ai;
//         ai = init();
//         ai ^= lastans;
//         int r = *--uniqueSet.upper_bound(ai + k);
//         int l = *uniqueSet.lower_bound(ai - k);
//         r     = val2rank[r];
//         l     = val2rank[l];
//         if (l > r) {
//             print(lastans);
//             putchar('\n');
//             continue;
//         }
//         int ans = tre.rangeQuery(l, r);
//         if (ans != 0)
//             tre.rangeClear(l, r);
//         lastans += ans;
//         print(lastans);
//         putchar('\n');
//     }
//     return 0;
// }
// #endif

// #ifdef V2
// #include <bits/stdc++.h>
// using namespace std;
// #define LL int

// set<LL>                 uniqueSet;
// unordered_map<int, int> g;

// int main()
// {
//     LL n, k;
//     scanf("%d%d", &n, &k);
//     for (int i = 1; i <= n; i++) {
//         LL x;
//         scanf("%d", &x);
//         uniqueSet.insert(x);
//         g[x]++;
//     }
//     int m;
//     cin >> m;
//     LL lastans = 0;
//     for (int i = 1; i <= m; i++) {
//         LL x;
//         scanf("%d", &x);
//         x ^= lastans;
//         auto it = uniqueSet.lower_bound(x - k);
//         while (it != uniqueSet.end() && *it <= x + k) {
//             lastans += g[*it];
//             it = uniqueSet.erase(it);
//         }
//         printf("%d\n", lastans);
//     }
//     return 0;
// }
// #endif
// #define V3pro
// #ifdef V3
// #include <cstdio>

// int init()
// {
//     char c = getchar();
//     int  x = 0, f = 1;
//     for (; c < '0' || c > '9'; c = getchar())
//         if (c == '-')
//             f = -1;
//     for (; c >= '0' && c <= '9'; c = getchar())
//         x = (x << 1) + (x << 3) + (c & 15);
//     return x * f;
// }

// void print(int x)
// {
//     if (x < 0)
//         putchar('-'), x = -x;
//     if (x / 10)
//         print(x / 10);
//     putchar(x % 10 + '0');
// }

// int mx(int x, int y)
// {
//     return x > y ? x : y;
// }

// int mn(int x, int y)
// {
//     return x < y ? x : y;
// }

// int ab(int x)
// {
//     return x < 0 ? -x : x;
// }

// const int N = (int)5e5 + 5;
// int       tree[N << 5], L[N << 5], R[N << 5];
// /* tree[root] 表示以 root 为根的区间和 */
// /* L[root] 表示以 root 为根的区间所表示的左端点 */
// /* R[root] 表示以 root 为根的区间所表示的右端点 */
// int cnt, ls[N << 5], rs[N << 5];

// /* ls[root] 表示线段树上结点 root 的左孩子结点 */
// /* rs[root] 表示线段树上结点 root 的右孩子结点 */
// void rebuild(int root, int id, int x)
// {
//     int nL = L[root], nR = R[root];
//     if (nL == nR) {
//         tree[root] += x;
//         return;
//     }
//     int mid = (nL + nR) >> 1;
//     if (id <= mid) {
//         if (!ls[root])
//             ls[root] = ++cnt;
//         L[ls[root]] = nL;
//         R[ls[root]] = mid;
//         rebuild(ls[root], id, x);
//     }
//     if (id >= mid + 1) {
//         if (!rs[root])
//             rs[root] = ++cnt;
//         L[rs[root]] = mid + 1;
//         R[rs[root]] = nR;
//         rebuild(rs[root], id, x);
//     }
//     tree[root] = tree[ls[root]] + tree[rs[root]];
// }

// int search(int root, int l, int r)
// {
//     if (!tree[root])
//         return 0;
//     int nL = L[root], nR = R[root];
//     if (l <= nL && nR <= r) {
//         int ret    = tree[root];
//         tree[root] = 0;
//         return ret;
//     }  // 注意特殊处理：每把锁只能开一次
//     int mid = (nL + nR) >> 1, ans = 0;
//     if (l <= mid && ls[root])
//         ans = ans + search(ls[root], l, r);
//     if (r >= mid + 1 && rs[root])
//         ans = ans + search(rs[root], l, r);
//     tree[root] = tree[ls[root]] + tree[rs[root]];
//     return ans;
// }

// void build(int n)
// {
//     tree[++cnt] = 0, L[cnt] = 1, R[cnt] = n;
// }

// signed main(signed argc, char** argv)
// {
// #ifndef ONLINE_JUDGE
//     freopen(argv[1], "r", stdin);
//     freopen(argv[2], "w", stdout);
// #endif
//     int m = init(), k = init();
//     build((int)1e9);
//     for (int i = 1; i <= m; ++i)
//         rebuild(1, init(), 1);
//     int n = init(), lastans = 0;
//     while (n--) {
//         int a = init() ^ lastans;
//         lastans += search(1, mx(1, a - k), mn((int)1e9, a + k));
//         print(lastans), putchar('\n');
//     }
// }
// #endif
#define V3pro
#ifdef V3pro

#include <bits/stdc++.h>
using namespace std;
using LL = long long;

constexpr LL MOD = 1e9 + 7;

class SegmentTree {
private:
    vector<LL> left, right;
    vector<LL> leftSon, rightSon;
    LL         cnt = 1;
    vector<LL> val;
    LL         __n;

    void update(LL root, LL idx, LL value)
    {
        LL l = left[root], r = right[root];
        if (l == r) {
            val[root] = value;
            return;
        }
        LL mid = (l + r) >> 1;
        if (idx <= mid) {
            if (leftSon[root] == 0) {
                leftSon[root] = ++cnt;
                leftSon.emplace_back(0);
                rightSon.emplace_back(0);
                val.emplace_back(0);
                left.emplace_back(l);
                right.emplace_back(mid);
            }
            update(leftSon[root], idx, value);
        } else {
            if (rightSon[root] == 0) {
                rightSon[root] = ++cnt;
                rightSon.emplace_back(0);
                leftSon.emplace_back(0);
                val.emplace_back(0);
                left.emplace_back(mid + 1);
                right.emplace_back(r);
            }
            update(rightSon[root], idx, value);
        }
        val[root] = (val[leftSon[root]] + val[rightSon[root]]) % MOD;
    }

    LL quary(LL root, LL start, LL end)
    {
        if (val[root] == 0) {
            return 0;
        }
        if (start > right[root] || end < left[root]) {
            return 0;
        }
        LL l = left[root], r = right[root];
        if (start <= l && r <= end) {
            return val[root];
        }
        LL sum = 0;
        if (leftSon[root] != 0) {
            sum += quary(leftSon[root], start, end);
            sum %= MOD;
        }

        if (rightSon[root] != 0) {
            sum += quary(rightSon[root], start, end);
            sum %= MOD;
        }
        return sum;
    }

public:
    SegmentTree(LL n) : left(2), right(2), leftSon(2, 0), rightSon(2, 0), val(2, 0), __n(n)
    {
        left[cnt]  = 1;
        right[cnt] = n;
    }

    void update(LL idx, LL value)
    {
        if (idx > __n) {
            perror("Index out of bound.(SegmentTree->update)");
            throw exception();
        }
        value += MOD;
        value %= MOD;
        update(1, idx, value);
    }

    LL quary(LL l, LL r)
    {
        if (l > r) {
            perror("\"l\" could not larger than \"r\".(SegmentTree->quary)");
            throw exception();
        }
        if (l < 1 || r > __n) {
            perror("Index out of bound.(SegmentTree->quary)");
            throw exception();
        }
        return quary(1, l, r);
    }
};

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    LL N, M;
    cin >> N >> M;
    SegmentTree stree(3e6 + 5);
    LL          lastans = 0;
    while (M--) {
        int type;
        cin >> type;
        LL x, y;
        cin >> x >> y;
        x ^= lastans;
        y ^= lastans;
        if (type == 1) {
            stree.update(x, y);
        } else {
            lastans = stree.quary(x, y);
            cout << lastans << '\n';
        }
    }
    return 0;
}

#endif