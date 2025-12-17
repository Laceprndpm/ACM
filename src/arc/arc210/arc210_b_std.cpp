#include <bits/stdc++.h>

using namespace std;
template <typename T>
using vc = vector<T>;
using ll = long long;

struct T {
    int cnt;
    ll  sum;
};

void solve()
{
    int N, M, Q;
    cin >> N >> M >> Q;
    vc<int> A(N + M), I(Q), X(Q);
    for (int i = 0; i < N + M; ++i) cin >> A[i];

    for (int q = 0; q < Q; ++q) {
        int t, i, x;
        cin >> t >> i >> x;
        i    = (t == 1 ? i - 1 : i - 1 + N);
        I[q] = i, X[q] = x;
    }

    int                n = N + M + Q;
    vc<pair<int, int>> ALL(n);
    for (int i = 0; i < N + M; ++i) ALL[i] = {A[i], i};
    for (int i = 0; i < Q; ++i) ALL[N + M + i] = {X[i], N + M + i};
    sort(ALL.begin(), ALL.end());

    for (int i = 0; i < n; ++i) {
        int idx = ALL[i].second;
        if (idx < N + M)
            A[idx] = i;
        else
            X[idx - (N + M)] = i;
    }

    // Fenwick Tree to count elements / sum elements
    vc<T> bit(n + 1, T{0, 0});
    auto  add = [&](int i) -> void {
        int a = ALL[i].first;
        for (++i; i <= n; i += i & -i) {
            bit[i].cnt += 1;
            bit[i].sum += a;
        }
    };
    auto rm = [&](int i) -> void {
        int a = ALL[i].first;
        for (++i; i <= n; i += i & -i) {
            bit[i].cnt -= 1;
            bit[i].sum -= a;
        }
    };
    auto get_sum = [&](int k) -> ll {
        // sum of smallest k elements
        int cnt = 0;
        ll  sum = 0;
        int i   = 0;
        for (int b = 19; b >= 0; --b) {
            int j = i | (1 << b);
            if (j <= n && cnt + bit[j].cnt <= k) {
                cnt += bit[j].cnt;
                sum += bit[j].sum;
                i = j;
            }
        }
        assert(cnt == k);
        return sum;
    };

    for (int i = 0; i < N + M; ++i) {
        add(A[i]);
    }

    for (int q = 0; q < Q; ++q) {
        int i = I[q];
        rm(A[i]);
        A[i] = X[q];
        add(A[i]);

        int K      = N / 2;
        ll  ans_lo = get_sum(K);
        ll  ans_hi = get_sum(N + M) - get_sum(N + M - K);
        ll  ans    = ans_lo + ans_hi;
        cout << ans << "\n";
    }
}

signed main()
{
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    solve();
}
