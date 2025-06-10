#include <bits/stdc++.h>
using namespace std;
using LL           = long long;
using PII          = pair<int, int>;
constexpr int MAXN = 1e5 + 5;

int m, q;
int iNext[MAXN];
int diInput[MAXN], ciInput[MAXN];
int stmap[MAXN][32];
// 在i处,使用了j档次的跳跃后消耗的水
int stcost[MAXN][32];

struct idx2val {
    unordered_map<int, int> idx2value;

    int operator[](int x)
    {
        return idx2value[x];
    }

    idx2val()
    {
        for (int i = 0; i <= 31; i++) {
            idx2value[1 << i] = i;
        }
    }

} idx2val;

inline int lowbit(int x)

{
    return x & (-x);
}

int get_highest(int x)
{
    int cur;
    while (x > 0) {
        cur = lowbit(x);
        x -= cur;
    }
    return cur;
}

// 在r处，v体积水，将到return处
int quaryplace(int r, int v)
{
    if (r == 0) {
        return 0;
    }
    if (v <= ciInput[r]) {
        return r;
    }
    int j         = idx2val[get_highest(v)];
    int nextPlace = stmap[r][j];
    return quaryplace(nextPlace, v - stcost[r][j]);
}

void init(int x)  // 初始化x处
{
    for (int j = 0; j <= 31; j++) {
        stmap[x][j] = quaryplace(x, 1 << j);
    }

    for (int j = 1; j <= 31; j++) {
        stcost[x][j] = stcost[x][j - 1] + stcost[stmap[x][j - 1]][];
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
        while (!monoStack.empty() && monoStack.top() <= diInput[i]) {
            monoStack.pop();
        }
        monoStack.push(i);
        iNext[i] = monoStack.empty() ? 0 : monoStack.top();
    }

    return 0;
}