#include <bits/stdc++.h>

#include <ctime>
#include <random>
#include <vector>
using namespace std;
mt19937 rd(time(0));

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

int main()
{
    int n;
    int m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
    }
    int a, b;
    cin >> a >> b;
    vector<int> arrive(n + 1);
    vector<int> visited(n + 1);
    auto        dfs = [&](this auto &&self, int u) -> void {
        arrive[u] = 1;
        for (int v : adj[u]) {
            if (arrive[v]) continue;
            self(v);
        }
    };
    dfs(a);
    int  found = -1;
    auto dfs2  = [&](this auto &&self, int u) -> void {
        if (found != -1) return;
        if (arrive[u]) found = u;
        visited[u] = 1;
        for (int v : adj[u]) {
            if (visited[v]) continue;
            self(v);
        }
    };
    dfs2(b);
    if (found != -1) {
        cout << "yes\n";
        cout << found;
    } else {
        cout << "no\n";
    }
}