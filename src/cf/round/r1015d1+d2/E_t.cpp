#include <bits/stdc++.h>
using namespace std;

struct Query {
    int l, r, idx;
};

const int     MAXN = 1e5 + 5;
int           n, q;
int           A[MAXN], last[MAXN], ans[MAXN];
vector<Query> queries;
vector<int>   pos[MAXN];  // pos[x] 存储 x 的所有出现位置

// 树状数组
int bit[MAXN];

void update(int x, int val)
{
    for (; x <= n; x += x & -x)
        bit[x] += val;
}

int query(int x)
{
    int res = 0;
    for (; x > 0; x -= x & -x)
        res += bit[x];
    return res;
}

int main()
{
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
        if (A[i] > n) A[i] = n + 1;  // 离散化，超过 n 的数不影响 mex
    }

    queries.resize(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].idx = i;
    }

    // 按右端点排序
    sort(queries.begin(), queries.end(), [](const Query &a, const Query &b) {
        return a.r < b.r;
    });

    memset(last, -1, sizeof(last));
    int ptr = 0;

    for (int i = 1; i <= n; i++) {
        int x = A[i];
        if (last[x] != -1) {
            update(last[x] + 1, -1);  // 删除之前的记录
        }
        update(i + 1, 1);  // 记录当前出现
        last[x] = i;

        // 处理所有右端点为 i 的查询
        while (ptr < q && queries[ptr].r == i) {
            int l = queries[ptr].l, idx = queries[ptr].idx;
            // 二分找 mex
            int low = 0, high = n, mex = n + 1;
            while (low <= high) {
                int mid = (low + high) / 2;
                if (query(mid + 1) < l) {  // [1..mid] 有数不在 [l..r] 中
                    mex  = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }
            ans[idx] = mex;
            ptr++;
        }
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}