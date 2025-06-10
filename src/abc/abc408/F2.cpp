/*
 * _|_|_|_|_|  _|_|_|_|    _|_|_|  _|_|_|_|_|  _|_|_|      _|_|
 *       _|    _|        _|                _|        _|  _|    _|
 *     _|      _|_|_|      _|_|          _|      _|_|        _|
 *   _|        _|              _|      _|            _|    _|
 * _|_|_|_|_|  _|        _|_|_|      _|        _|_|_|    _|_|_|_|
 */

#include <bits/stdc++.h>

class SegmentTree {
    int              N;
    std::vector<int> tree;

    void Modify(int x, int v, int u, int L, int R)
    {
        if (R <= x || x < L) {
            return;
        }
        if (L + 1 == R) {
            return tree[u] = v, void();
        }
        int M = (L + R) >> 1;
        Modify(x, v, u << 1, L, M);
        Modify(x, v, u << 1 | 1, M, R);
        tree[u] = std::max(tree[u << 1], tree[u << 1 | 1]);
    }

    int Query(int l, int r, int u, int L, int R)
    {
        if (R <= l || r <= L) {
            return 0;
        }
        if (l <= L && R <= r) {
            return tree[u];
        }
        int M = (L + R) >> 1;
        return std::max(Query(l, r, u << 1, L, M), Query(l, r, u << 1 | 1, M, R));
    }

public:
    explicit SegmentTree(int N) : N(N), tree(N << 2) {}

    void modify(int x, int v)
    {
        Modify(x, v, 1, 0, N);
    }

    int query(int l, int r)
    {
        return Query(l, r, 1, 0, N);
    }
};

int main()
{
#ifdef LOCAL
    freopen("task.in", "r", stdin);
    freopen("task.out", "w", stdout);
    freopen("task.err", "w", stderr);
#endif
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, D, R;
    std::cin >> N >> D >> R;
    std::vector<int> ans(N), P(N), Q(N);
    for (int i = 0; i < N; i++) {
        std::cin >> P[i], Q[--P[i]] = i;
    }
    SegmentTree sgt(N);
    for (int i = 0; i < N; i++) {
        if (i - D >= 0) {
            sgt.modify(Q[i - D], ans[i - D] + 1);
        }
        ans[i] = sgt.query(Q[i] - R, Q[i] + R + 1);
    }
    std::cout << *std::ranges::max_element(ans) << '\n';

    return 0;
}