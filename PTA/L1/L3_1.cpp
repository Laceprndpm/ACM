#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;
using i64 = long long;

int main()
{
    int b, n, m, k;
    cin >> b >> n >> m >> k;
    vector<vector<pair<int, pair<int, int>>>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w, h;
        cin >> u >> v >> w >> h;
        graph[u].push_back({v, {w, h}});
        graph[v].push_back({u, {w, h}});
    }
    while (k--) {
        map<int, int>                           mp;
        function<void(int, int, int, set<int>)> dfs = [&](int u, int money, int happy, set<int> vis) -> void {
            vis.insert(u);
            mp[u] = max(mp[u], happy);
            for (auto it : graph[u]) {
                int adj = it.first, w = it.second.first, h = it.second.second;
                if (vis.count(adj) != 0) continue;
                if (money >= w) {
                    dfs(adj, money - w, happy + h, vis);
                }
            }
        };
        int cur;
        cin >> cur;
        dfs(cur, b, 0, set<int>());
        vector<pair<int, int>> vec;
        for (auto i : mp) {
            if (i.first == cur) continue;
            pair<int, int> j = i;
            swap(j.first, j.second);
            vec.push_back(j);
        }
        if (vec.empty()) {
            cout << "T_T\n";
            continue;
        }
        int len = vec.size();
        for (int i = 0; i < len; i++) {
            cout << vec[i].second << " \n"[i == len - 1];
        }
        auto cmp = [&](pair<int, int> a, pair<int, int> b) {
            if (a.first != b.first) {
                return a.first > b.first;
            } else {
                return a.second < b.second;
            }
        };
        sort(vec.begin(), vec.end(), cmp);
        for (int i = 0; i < len; i++) {
            if (vec[i].first != vec[0].first) break;
            cout << " \0"[i == 0] << vec[i].second;
        }
        cout << '\n';
    }

    return 0;
}