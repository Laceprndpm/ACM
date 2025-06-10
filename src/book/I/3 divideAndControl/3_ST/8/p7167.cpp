#include <bits/stdc++.h>
using namespace std;
using LL  = long long;
using PII = pair<int, int>;

constexpr int MAXN = 1e5 + 5;
// 从i节点水槽溢出1<<j次后到达的节点
int f[MAXN][32];
// 从i节点水槽溢出1<<j次后花费的水
int g[MAXN][32];
int iNext[MAXN];
int diInput[MAXN], ciInput[MAXN];
int m, q;

int quary(int r, int v)
{
    if (r == 0 || v <= ciInput[r]) {
        return r;
    }
    int leftJ = 0, rightJ = 31;
    while (leftJ < rightJ) {
        int mid = (rightJ - leftJ - 1) / 2 + leftJ + 1;

        if (g[r][mid] < v) {
            leftJ = mid;
        } else {
            rightJ = mid - 1;
        }
    }
    return quary(f[r][leftJ], v - g[r][leftJ]);
}

void init()
{
    for (int i = 1; i <= m; i++) {
        g[i][0] = ciInput[i];
        f[i][0] = iNext[i];
    }
    for (int i = m; i >= 1; i--) {
        for (int j = 1; j <= 31; ++j) {
            f[i][j] = f[f[i][j - 1]][j - 1];
            g[i][j] = g[i][j - 1] + g[f[i][j - 1]][j - 1];
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> m >> q;
    for (int i = 1; i <= m; i++) {
        cin >> diInput[i] >> ciInput[i];
    }
    stack<int> monoStack;
    for (int i = m; i >= 1; i--) {
        while (!monoStack.empty() && diInput[monoStack.top()] <= diInput[i]) {
            monoStack.pop();
        }
        iNext[i] = monoStack.empty() ? 0 : monoStack.top();
        monoStack.push(i);
    }
    init();
    for (int i = 1; i <= q; i++) {
        int r, v;
        cin >> r >> v;
        cout << quary(r, v) << '\n';
    }
    return 0;
}