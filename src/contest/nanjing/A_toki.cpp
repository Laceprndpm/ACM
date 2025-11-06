#include <bits/stdc++.h>
using namespace std;
using i64      = long long;
const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
int       n, m;

bool check(int x, int y)
{  // 是否越界
    return (x >= 1 && x <= n && y >= 1 && y <= m);
}

void Tokisaki()
{
    cin >> n >> m;
    vector<vector<char>> g(n + 1, vector<char>(m + 1));  // 存图
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) cin >> g[i][j];
    }
    vector<pair<int, int>>    path;  // 存连通块
    map<pair<int, int>, bool> vis;   // 当前点是否被访问
    // 找最大连通块
    function<void(pair<int, int>)> bfs = [&](pair<int, int> st) -> void {
        path.clear();  // 先清空上一个连通块
        path.push_back(st);
        vis[st] = 1;
        queue<pair<int, int>> q;
        q.push(st);
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            for (int i = 0; i < 4; i++) {
                int new_x = x + dx[i], new_y = y + dy[i];
                if (g[new_x][new_y] == 'O') continue;  // 当前位置是洞
                if (!check(new_x, new_y)) continue;    // 越界
                if (vis[{new_x, new_y}]) continue;     // 已经访问
                vis[{new_x, new_y}] = 1;
                q.push({new_x, new_y});
                path.push_back({new_x, new_y});
            }
        }
    };
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (g[i][j] == '.' && vis[{i, j}] == 0) {
                bfs({i, j});  // 宽搜找到连通块，存在path中
                bool finded = 0;
                // 尝试以每个点为起点看能不能把path走完，如走完就说明还有一个一模一样连通块
                for (int ii = 1; ii <= n && !finded; ii++) {
                    for (int jj = 1; jj <= m && !finded; jj++) {
                        if (ii == i && jj == j) continue;   // 起点不能相同
                        if (g[ii][jj] == 'O') continue;     // 洞显然不能作为起点
                        int  addx = ii - i, addy = jj - j;  // 求出偏移量
                        bool flag = 1;
                        for (auto pa : path) {
                            int pa_x = pa.first + addx;
                            int pa_y = pa.second + addy;  // 求出对应要走的路径
                            if (!check(pa_x, pa_y)) {     // 越界
                                flag = 0;
                                break;
                            }
                            if (g[pa_x][pa_y] == 'O') {  // 走进坑了
                                flag = 0;
                                break;
                            }
                        }
                        if (flag) finded = 1;  // 如果全部走完了，说明找到一个一样的图
                    }
                }
                if (finded) continue;
                ans += (int)path.size();  // 如果没找到，说明这个联通块的袋鼠可以干掉其他所有连通块，更新答案
            }
        }
    }
    cout << ans << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) Tokisaki();
    return 0;
}