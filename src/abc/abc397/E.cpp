#include <cstdlib>
#include <iostream>
#include <vector>
#define REMOVE_ME
using namespace std;
using i64               = long long;
using PII               = pair<int, int>;
constexpr int       INF = 1e9;
vector<vector<int>> graph;
int                 n, k;

int mydfs(int root, int last)
{
    vector<int> cur;
    for (int i : graph[root]) {
        if (i == last) continue;
        int adj = mydfs(i, root);
        if (adj != 0) {
            cur.emplace_back(adj);
        }
    }
    if (cur.size() == 1) {
        return (cur[0] + 1) % k;
    }
    if (cur.size() == 2) {
        if (cur[0] + cur[1] == k - 1) {
            return 0;
        } else {
            cout << "No\n";
            exit(0);
        }
    }
    if (cur.size() > 2) {
        cout << "No\n";
        exit(0);
    }
    return 1 % k;
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
    cin >> n >> k;
    graph.assign(n * k + 1, vector<int>());
    for (int i = 1; i <= n * k - 1; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].emplace_back(v);
        graph[v].emplace_back(u);
    }
    if (mydfs(1, 0) == 0)
        cout << "Yes\n";
    else {
        cout << "No\n";
    }
    return 0;
}