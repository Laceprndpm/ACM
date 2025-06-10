#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <utility>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

struct Hungary {
private:
    int                 totalNum;  // 传入总的点数
    int                 leftNum;   // 左边去和别人配对的点
    int                 Maxedge;
    bool                worked = false;
    vector<vector<int>> adj;
    vector<int>         match;
    vector<int>         vis;

    bool dfs(int cur, int op)
    {
        if (vis[cur] == op) return false;
        vis[cur] = op;
        for (int x : adj[cur]) {
            if (!match[x] || dfs(match[x], op)) {
                match[x] = cur;
                return true;
            }
        }
        return false;
    }

public:
    Hungary(int _leftNum, int _rightNum) : leftNum(_leftNum), totalNum(_leftNum + _rightNum)
    {
        Maxedge = 0;
        adj.assign(totalNum + 1, {});
        match.assign(totalNum + 1, 0);
        vis.assign(totalNum + 1, 0);
    }

    void addedge(int u, int v)
    {
        adj[u].push_back(v);
    }

    void work()
    {
        for (int i = 1; i <= leftNum; i++) {
            if (dfs(i, i)) {
                Maxedge++;
            }
        }
        worked = true;
    }

    int getMaxedge()
    {
        assert(worked);
        return Maxedge;
    }

    vector<std::pair<i64, i64>> getExatctlyMatch()
    {
        assert(worked);
        vector<std::pair<i64, i64>> exactmatch;
        for (int i = 1; i <= totalNum; i++) {
            if (match[i]) {
                exactmatch.push_back({match[i], i});
            }
        }
        return exactmatch;
    }
};

void solve()
{
    int n;
    cin >> n;
    map<int, set<pair<int, int>>> row, col;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        row[x].insert({y, 1});
        col[y].insert({x, 1});
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        row[x].insert({y, 0});
        col[y].insert({x, 0});
    }

    struct left {
        i64 row;
        i64 col1, col2;
    };

    struct right {
        i64 col;
        i64 row1, row2;
    };

    vector<left> lfvec;
    lfvec.push_back({});
    int lidx = 0;
    for (auto [rowTh, row_iter] : row) {
        for (auto it = row_iter.begin(); next(it) != row_iter.end(); it++) {
            if (it->second == 1 && next(it)->second == 1) {
                lidx++;
                lfvec.push_back({rowTh, it->first + 1, next(it)->first - 1});
                if (next(it)->first - it->first == 1) {
                    cout << -1 << '\n';
                    return;
                }
            }
        }
    }
    vector<right> rtvec;
    rtvec.push_back({});
    int ridx = 0;
    for (auto [colTh, col_iter] : col) {
        for (auto it = col_iter.begin(); next(it) != col_iter.end(); it++) {
            if (it->second == 1 && next(it)->second == 1) {
                ridx++;
                rtvec.push_back({colTh, it->first + 1, next(it)->first - 1});
                if (next(it)->first - it->first == 1) {
                    cout << -1 << '\n';
                    return;
                }
            }
        }
    }
    function<bool(left u, right v)> check = [&](left u, right v) -> bool {
        return (v.row1 <= u.row && u.row <= v.row2) && (u.col1 <= v.col && v.col <= u.col2);
    };
    Hungary h(lidx, ridx);
    for (int i = 1; i <= lidx; i++) {
        for (int j = 1; j <= ridx; j++) {
            if (check(lfvec[i], rtvec[j])) {
                h.addedge(i, j);
            }
        }
    }
    h.work();
    vector<bool>           lflag(lidx + 1);
    vector<bool>           rflag(ridx + 1);
    auto                   res = h.getExatctlyMatch();
    vector<pair<i64, i64>> ans;
    for (pair<i64, i64> it : res) {
        lflag[it.first]  = true;
        rflag[it.second] = true;
        ans.push_back({lfvec[it.first].row, rtvec[it.second].col});
    }
    for (int i = 1; i <= lidx; i++) {
        if (!lflag[i]) {
            ans.push_back({lfvec[i].row, (lfvec[i].col1 + lfvec[i].col2) / 2});
        }
    }
    for (int i = 1; i <= ridx; i++) {
        if (!rflag[i]) {
            ans.push_back({(rtvec[i].row1 + rtvec[i].row2) / 2, rtvec[i].col});
        }
    }
    cout << ans.size() << '\n';
    for (auto i : ans) {
        cout << i.first << ' ' << i.second << '\n';
    }
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