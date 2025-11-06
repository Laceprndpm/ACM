#include <bits/stdc++.h>

#include <utility>
using namespace std;
#define int long long
constexpr int N = 2e6, M = 2e6;
using PII         = pair<int, int>;
constexpr int INF = 1e16;
int           h[N], e[M], f[M], w[M], ne[M], idx;
int           dis[N], cur[N];  // d表示最短距离,cur为当前弧
int           n, m, S, T;
bool          vis[N];
int           height[N];  // 势能函数
vector<int>   dot;        // 点数

void add(int a, int b, int c, int d)
{
    e[idx] = b, f[idx] = c, w[idx] = d, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, f[idx] = 0, w[idx] = -d, ne[idx] = h[b], h[b] = idx++;
}

bool dijk()
{
    for (auto &i : dot) dis[i] = INF, cur[i] = h[i];
    priority_queue<PII, vector<PII>, greater<>> pq;
    dis[S] = 0;
    pq.emplace(0, S);
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (dis[u] != d) continue;
        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            if (f[i] && dis[v] > d + height[u] - height[v] + w[i]) {
                dis[v] = d + height[u] - height[v] + w[i];
                pq.emplace(dis[v], v);
            }
        }
    }
    return dis[T] != INF;
}

int find(int u, int limit)
{
    if (!limit || u == T) return limit;
    int flow = 0;
    vis[u]   = 1;
    for (int &i = cur[u]; ~i && flow < limit; i = ne[i]) {
        int v = e[i];
        if (dis[v] == dis[u] + height[u] - height[v] + w[i] && f[i] && !vis[v]) {
            int t = find(v, min(f[i], limit - flow));
            f[i] -= t, f[i ^ 1] += t, flow += t;
            if (flow == limit) break;
        }
    }
    vis[u] = 0;
    return flow;
}

void mcmf(int &flow, int &cost)
{
    flow = cost = 0;
    int r;
    while (dijk()) {
        int r = find(S, INF);
        flow += r;
        for (auto &i : dot) height[i] += dis[i];
        cost += height[T] * r;
    }
}

void solve()
{
    int n;
    cin >> n;
    unordered_map<int, int> mp;
    int                     tot = n;
    auto                    id  = [&](int x) {
        if (!mp.count(x)) mp[x] = ++tot;
        return mp[x];
    };
    vector<int> a(n + 1);
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        vector<PII> tmp;
        int         x = a[i], all = 0;
        for (int j = 2; j * j <= x; j++) {
            if (x % j == 0) {
                int cnt = 0;
                while (x % j == 0) x /= j, cnt++;
                tmp.emplace_back(j, cnt);
                all += cnt;
            }
        }
        if (x > 1) tmp.emplace_back(x, 1), all++;
        vector<array<int, 2>>         edge;
        function<void(int, int, int)> dfs = [&](int x, int c, int sum) {
            if (x == tmp.size()) {
                edge.push_back({sum, all - c});
                return;
            }
            auto &[p, cnt] = tmp[x];
            int y          = 1;
            for (int j = 0; j <= cnt; j++, y *= p) dfs(x + 1, c + j, y * sum);
        };
        sort(edge.begin(), edge.end());
        dfs(0, 0, 1);
        for (int j = 0; j < edge.size() && j < n; j++) add(i, id(edge[j][0]), 1, -edge[j][1]);
    }
    S = 0, T = ++tot;
    for (int i = 0; i <= tot; i++) dot.push_back(i);
    for (int i = 1; i <= n; i++) add(S, i, 1, 0);
    for (int i = n + 1; i < tot; i++) add(i, T, 1, 0);
    int flow, cost;
    mcmf(flow, cost);
    cout << -cost << "\n";
}

signed main() { solve(); }