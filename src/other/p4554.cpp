#include <bits/stdc++.h>
using namespace std;
using LL  = long long;
using PII = pair<int, int>;

int                    dist[505][505];
char                   input[505][505];
deque<pair<int, int>>  dequeBFS;
vector<pair<int, int>> movement{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int                    n, m;

void BFS(void)
{
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    x1++;
    y1++;
    x2++;
    y2++;
    dequeBFS.clear();
    memset(dist, -1, sizeof(dist));
    dequeBFS.emplace_front(x1, y1);
    dist[x1][y1] = 0;
    while (!dequeBFS.empty()) {
        PII cur = dequeBFS.front();
        dequeBFS.pop_front();
        for (PII iter : movement) {
            PII adj(cur.first + iter.first, cur.second + iter.second);
            if (adj.first >= 1 && adj.first <= n && adj.second >= 1 && adj.second <= m
                && dist[adj.first][adj.second] == -1) {
                if (input[adj.first][adj.second] == input[cur.first][cur.second]) {
                    dequeBFS.emplace_front(adj.first, adj.second);
                    dist[adj.first][adj.second] = dist[cur.first][cur.second];
                } else {
                    dequeBFS.emplace_back(adj.first, adj.second);
                    dist[adj.first][adj.second] = dist[cur.first][cur.second] + 1;
                }
            }
        }
    }
    cout << dist[x2][y2] << '\n';
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    while (true) {
        cin >> n >> m;
        if (n == 0 && m == 0) {
            return 0;
        }
        for (int row = 1; row <= n; row++) {
            for (int col = 1; col <= m; col++) {
                cin >> input[row][col];
            }
        }
        BFS();
    }

    return 0;
}