struct MCFGraph {
    struct Edge {
        int v, c, f;

        Edge(int v, int c, int f) : v(v), c(c), f(f) {}
    };

    const int                     n;
    std::vector<Edge>             e;
    std::vector<std::vector<int>> g;
    std::vector<i64>              h, dis;
    std::vector<int>              pre;

    bool spfa(int s, int t)
    {
        dis.assign(n, std::numeric_limits<i64>::max());
        pre.assign(n, -1);
        std::deque<int>   que;
        std::vector<bool> inq(n, false);
        dis[s] = 0;
        inq[s] = true;
        que.emplace_back(s);
        while (!que.empty()) {
            int u  = que.front();
            i64 d  = dis[u];
            inq[u] = false;
            que.pop_front();
            for (int i : g[u]) {
                int v = e[i].v;
                int c = e[i].c;
                int f = e[i].f;
                if (c > 0 && dis[v] > d + f) {
                    dis[v] = d + f;
                    pre[v] = i;
                    if (!inq[v]) {
                        que.emplace_back(v);
                        inq[v] = 1;
                    }
                }
            }
        }
        return dis[t] != std::numeric_limits<i64>::max();
    }

    bool dijkstra(int s, int t)
    {
        dis.assign(n, std::numeric_limits<i64>::max());
        pre.assign(n, -1);
        std::priority_queue<std::pair<i64, int>, std::vector<std::pair<i64, int>>, std::greater<std::pair<i64, int>>>
            que;
        dis[s] = 0;
        que.emplace(0, s);
        while (!que.empty()) {
            i64 d = que.top().first;
            int u = que.top().second;
            que.pop();
            if (dis[u] < d) continue;
            for (int i : g[u]) {
                int v = e[i].v;
                int c = e[i].c;
                int f = e[i].f;
                if (c > 0 && dis[v] > d + h[u] - h[v] + f) {
                    dis[v] = d + h[u] - h[v] + f;
                    pre[v] = i;
                    que.emplace(dis[v], v);
                }
            }
        }
        return dis[t] != std::numeric_limits<i64>::max();
    }

    MCFGraph(int n) : n(n), g(n) {}

    // void addEdge(int u, int v, int c, int f)
    // {
    //     g[u].push_back(e.size());
    //     e.emplace_back(v, c, f);
    //     g[v].push_back(e.size());
    //     e.emplace_back(u, 0, -f);
    // }

    // 代码同(07A - 费用流（MCFGraph 最小费用可行流）)，但是需要注释掉建边限制。以下为参考：
    void addEdge(int u, int v, int c, int f)
    {  // 可行流
        if (f < 0) {
            g[u].push_back(e.size());
            e.emplace_back(v, 0, f);
            g[v].push_back(e.size());
            e.emplace_back(u, c, -f);
        } else {
            g[u].push_back(e.size());
            e.emplace_back(v, c, f);
            g[v].push_back(e.size());
            e.emplace_back(u, 0, -f);
        }
    }

    std::pair<int, i64> flow(int s, int t)
    {
        int flow = 0;
        i64 cost = 0;
        h.assign(n, 0);

        // // init with spfa
        // do {
        //     bool result = spfa(s, t);
        //     for (int i = 0; i < n; ++i) h[i] += dis[i];
        //     int aug = std::numeric_limits<int>::max();
        //     for (int i = t; i != s; i = e[pre[i] ^ 1].v) aug = std::min(aug, e[pre[i]].c);
        //     for (int i = t; i != s; i = e[pre[i] ^ 1].v) {
        //         e[pre[i]].c -= aug;
        //         e[pre[i] ^ 1].c += aug;
        //     }
        //     flow += aug;
        //     cost += i64(aug) * h[t];
        //     if (!result) return std::make_pair(flow, cost);
        // } while (0);
        // // end

        while (dijkstra(s, t)) {
            for (int i = 0; i < n; ++i) h[i] += dis[i];
            int aug = std::numeric_limits<int>::max();
            for (int i = t; i != s; i = e[pre[i] ^ 1].v) aug = std::min(aug, e[pre[i]].c);
            for (int i = t; i != s; i = e[pre[i] ^ 1].v) {
                e[pre[i]].c -= aug;
                e[pre[i] ^ 1].c += aug;
            }
            flow += aug;
            cost += i64(aug) * h[t];
        }
        return std::make_pair(flow, cost);
    }
};
