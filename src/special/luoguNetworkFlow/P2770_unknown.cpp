#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
#define inf 0x7fffffff / 2
#define eps 1e-6
#define N   100010
using namespace std;
typedef long long          ll;
typedef unsigned long long ull;

inline ll read()
{
    char ch = getchar();
    ll   s = 0, w = 1;
    while (ch < '0' || ch > '9') {
        if (ch == '-') w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        s  = s * 10 + ch - '0';
        ch = getchar();
    }
    return s * w;
}

int              n, m;
map<string, int> ma;

struct edge {
    int next, to, fl, v;
} e[N << 1];

int        head[N], cnt = 1;
int        dist[N], pre[N], vis[N], minn[N];
queue<int> Q;
int        s, t, val, flag[N], check;
string     ss[N];

inline void add_edge(int from, int to, int fl, int v)
{
    e[++cnt].to = to;
    e[cnt].next = head[from];
    e[cnt].fl   = fl;
    e[cnt].v    = v;
    head[from]  = cnt;
}

void update(int x, int flow)
{
    e[pre[x]].fl -= flow;
    e[pre[x] ^ 1].fl += flow;
    if (e[pre[x] ^ 1].to) update(e[pre[x] ^ 1].to, flow);
}

inline int spfa()
{
    memset(vis, 0, sizeof(vis));
    while (!Q.empty()) Q.pop();
    for (int i = 1; i <= t; i++) dist[i] = -inf;
    minn[s] = inf;
    dist[s] = 0;
    Q.push(s);
    vis[s] = 1;
    while (!Q.empty()) {
        int x = Q.front();
        Q.pop();
        vis[x] = 0;
        for (int i = head[x]; i; i = e[i].next) {
            if (dist[e[i].to] < dist[x] + e[i].v && e[i].fl) {
                dist[e[i].to] = dist[x] + e[i].v;
                pre[e[i].to]  = i;
                minn[e[i].to] = min(minn[x], e[i].fl);
                if (!vis[e[i].to]) {
                    vis[e[i].to] = 1;
                    Q.push(e[i].to);
                }
            }
        }
    }
    if (dist[t] == -inf) return -inf;
    update(t, minn[t]);
    val += minn[t];
    return minn[t] * dist[t];
}

inline int EK()
{
    int sum = 0;
    while (1) {
        int x = spfa();
        if (x == -inf) return sum;
        sum += x;
    }
}  // 最大费用最大流

void dfs1(int x)
{
    cout << ss[x] << endl;  // 第一遍dfs正序输出
    vis[x] = 1;             // 不让第二次dfs再找到这个点
    for (int i = head[x]; i; i = e[i].next) {
        if (e[i].to > n && e[i].to <= 2 * n && e[i].fl == 0) {
            dfs1(e[i].to - n);
            break;
        }  // 第一次dfs只找一条路径，找到就break
    }
}

void dfs2(int x)
{
    vis[x] = 1;
    for (int i = head[x]; i; i = e[i].next) {
        if (e[i].to > n && e[i].to <= 2 * n && e[i].fl == 0 && !vis[e[i].to - n]) {
            dfs2(e[i].to - n);
        }  // 不走第一次路径走过的点
    }
    cout << ss[x] << endl;  // 第二次dfs倒序输出
}  // vis[n]在第一次dfs已经设为1，不会输出第二次

int main()
{
    n = read(), m = read();
    t = n * 2 + 1;
    for (int i = 1; i <= n; i++) {
        cin >> ss[i];
        ma[ss[i]] = i;
    }
    for (int i = 1; i <= m; i++) {
        string s1, s2;
        cin >> s1 >> s2;
        int x = ma[s1], y = ma[s2];
        if (x > y) swap(x, y);            // 让西边的点向东边建边
        if (x == 1 && y == n) check = 1;  // 如果有直接1-n的路径
        add_edge(x, y + n, 1, 0);
        add_edge(y + n, x, 0, 0);
    }
    add_edge(s, n + 1, inf, 0);
    add_edge(n + 1, s, 0, 0);
    add_edge(n, t, inf, 0);
    add_edge(t, n, 0, 0);
    for (int i = 1; i <= n; i++) {
        if (i != 1 && i != n)
            add_edge(i + n, i, 1, 1), add_edge(i, i + n, 0, -1);
        else
            add_edge(i + n, i, 2, 1), add_edge(i, i + n, 0, -1);
    }
    // 对于我的代码,1-n是Bi,n+1-2*n是Ai
    int maxflow = EK();
    if (val == 2)
        printf("%d\n", maxflow - 2);  // 1和n被重复计算，应该减去
    else if (val == 1 && check) {
        printf("%d\n", 2);
        cout << ss[1] << endl << ss[n] << endl << ss[1] << endl;
        return 0;
    }  // 如果有1-n直接的路径即使只有1条也是满足条件的
    else {
        printf("No Solution!\n");
        return 0;
    }
    memset(vis, 0, sizeof(vis));
    dfs1(1);
    dfs2(1);  // 输出城市
    return 0;
}
