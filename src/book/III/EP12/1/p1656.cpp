#include <bits/stdc++.h>
using namespace std;
int maps[151][151];  // 邻接矩阵，简单易懂

struct Edge {
    int x, y;
} E[5001];  // 这是存答案的，用邻接表存，应该不用解释

int dfn[151], low[151], n, m, id, cnt, father[151];

/*这些数组的含义：
       dfn:
       {
       下标：点编号
       内存的值：深度优先搜索时第几个遍历
       }
       low:
       {
       下标：点编号
       内存的值：这个点能通过它的子孙到达的dfn值最小的点的dfn
       }
       f:
       {
       下标：点标号
       内存的值：它遍历的上一个点
       }
       变量的含义：
       n:结点个数
       m:边个数
       id:用于dfn标记
       cnt:用于邻接表存图
*/

bool cmp(struct Edge a, struct Edge b)
{
    if (a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}  // 因题目要求，边要排序，要做这道题的人应该都知道cmp

void addEdge(int x, int y)
{
    E[++cnt].x = x;
    E[cnt].y   = y;
}  // addedge函数，存入邻接表

void tarjan(int root)
{
    int c     = 0, adj;
    dfn[root] = low[root] = ++id;
    for (int i = 1; i <= n; i++) {
        if (!maps[root][i]) continue;  // 首先要有边
        adj = i;                       // 处理对象
        if (dfn[adj] && adj != father[root])
            low[root] = min(low[root], dfn[adj]);          // 如果是它爸爸，割边就没有用了，好好理解
        if (!dfn[adj]) {                                   // 如果找到祖先还有什么用呢
            father[adj] = root;                            // 不是祖先就认爸爸
            tarjan(adj);                                   // dfs过程
            low[root] = min(low[root], low[adj]);          // 回溯时带着爸爸更新low
            if (low[adj] > dfn[root]) addEdge(root, adj);  // 是割边，就加入吧
        }
    }
}  // tarjan部分，证明在下面

int main()
{
    int x, y;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> x >> y;
        maps[x][y] = maps[y][x] = 1;  // 存边
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) tarjan(i);  // tarjan
    }
    sort(E + 1, E + cnt + 1, cmp);  // sort大法好
    for (int i = 1; i <= cnt; i++) {
        cout << min(E[i].x, E[i].y) << ' ' << max(E[i].x, E[i].y) << endl;  // 输出
    }
    return 0;  // 程序结束了，证明开始了
}