#include <cstdint>
#include <functional>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

struct point {
    i64 x, y;
};

i64 df(const point& x, const point& y)
{
    return abs(x.x - y.x) + abs(x.y - y.y);
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
    int n;
    cin >> n;
    vector<point>       pointVector(n + 1);
    vector<vector<i64>> dist(n + 1, vector<i64>(n + 1));
    for (int i = 1; i <= n; i++) {
        i64 x, y;
        cin >> x >> y;
        pointVector[i] = {x, y};
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            i64 dis    = df(pointVector[i], pointVector[j]);
            dist[i][j] = dis;
            dist[j][i] = dis;
        }
    }
    vector<i64>         minDis(n + 1, INT64_MAX);
    vector<vector<int>> graph(n + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j == i) continue;
            if (minDis[i] > dist[i][j]) {
                minDis[i] = dist[i][j];
                graph[i].clear();
                graph[i].emplace_back(j);
            } else if (minDis[i] == dist[i][j]) {
                graph[i].emplace_back(j);
            }
        }
    }
    int cnt = 0;
    function<int(int)> check = [&](int root) {
        vector<int> sons;
        for (int i : graph[root]) {
            sons.emplace_back(i);
        }
        
    };
    return 0;
}