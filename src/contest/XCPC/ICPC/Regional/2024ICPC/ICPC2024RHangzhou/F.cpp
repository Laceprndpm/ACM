#include <bits/stdc++.h>

#include <array>
#include <set>
#include <utility>
#include <vector>
using namespace std;
using i64 = long long;

struct SCC {
    int                           n;
    std::vector<std::vector<int>> adj;
    std::vector<int>              stk;
    std::vector<int>              dfn, low, bel;
    int                           cur, cnt;

    SCC() {}

    SCC(int n) { init(n); }

    void init(int n)
    {
        this->n = n;
        adj.assign(n, {});
        dfn.assign(n, -1);
        low.resize(n);
        bel.assign(n, -1);
        stk.clear();
        cur = cnt = 0;
    }

    void addEdge(int u, int v) { adj[u].push_back(v); }

    void dfs(int x)
    {
        dfn[x] = low[x] = cur++;
        stk.push_back(x);

        for (auto y : adj[x]) {
            if (dfn[y] == -1) {
                dfs(y);
                low[x] = std::min(low[x], low[y]);
            } else if (bel[y] == -1) {
                low[x] = std::min(low[x], dfn[y]);
            }
        }

        if (dfn[x] == low[x]) {
            int y;
            do {
                y      = stk.back();
                bel[y] = cnt;
                stk.pop_back();
            } while (y != x);
            cnt++;
        }
    }

    std::vector<int> work()
    {
        for (int i = 0; i < n; i++) {
            if (dfn[i] == -1) {
                dfs(i);
            }
        }
        return bel;
    }
};

#define int long long

void solve()
{
    int n, k, q;
    cin >> n >> k >> q;
    SCC                 scc(n);
    vector<vector<int>> board(k, vector<int>(n));
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j];
            board[i][j]--;
            if (j) scc.addEdge(board[i][j], board[i][j - 1]);
        }
    }
    scc.work();
    vector<i64> cnt(n);
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = scc.bel[board[i][j]];
        }
    }
    for (int j = 0; j < n; j++) {
        cnt[board[0][j]]++;
    }
    vector<array<vector<int>, 2>> ext(k);

    vector<vector<i64>> prefix(k, vector<i64>(n + 1));
    for (int i = 0; i < k; i++) {
        vector<int> lft(n, n);
        vector<int> rgt(n, -1);
        for (int j = 0; j < n; j++) {
            lft[board[i][j]] = min(lft[board[i][j]], j);
            rgt[board[i][j]] = max(rgt[board[i][j]], j + 1);
        }
        int ptr = 0;
        while (ptr < n) {
            i64 tmpval = cnt[board[i][ptr]] * (cnt[board[i][ptr]] - 1ll) / 2;
            ptr        = rgt[board[i][ptr]];
            prefix[i][ptr] += tmpval;
        }
        ext[i] = {lft, rgt};
        for (int j = 0; j < n; j++) {
            prefix[i][j + 1] += prefix[i][j];
        }
    }
    i64 v = 0;
    while (q--) {
        i64 id, l, r;
        cin >> id >> l >> r;
        id                = (id + v) % k;
        l                 = (l + v) % n;
        r                 = (r + v) % n + 1;
        const auto &curbd = board[id];
        i64         ll = ext[id][1][curbd[l]], rr = ext[id][0][curbd[r - 1]];
        if (ll > rr) {
            v = (r - l) * (r - l - 1) / 2;
        } else {
            i64 midval = prefix[id][rr] - prefix[id][ll];
            i64 lftval = (r - rr) * (r - rr - 1) / 2;
            i64 rgtval = (ll - l) * (ll - l - 1) / 2;
            v          = lftval + midval + rgtval;
        }
        cout << v << '\n';
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}