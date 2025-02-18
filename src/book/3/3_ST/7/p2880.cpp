#include <bits/stdc++.h>
using namespace std;
using LL  = long long;
using PII = pair<int, int>;

constexpr int MAXN = 5e4 + 5;
int           n, q;

int stMAX[MAXN][18];
int stMIN[MAXN][18];
int hiInput[MAXN];

void init()
{
    for (int i = 1; i <= n; ++i) {
        stMAX[i][0] = hiInput[i];
    }
    for (int j = 1; (1 << j) <= n; ++j) {
        for (int i = 1; i <= n - (1 << j) + 1; ++i) {
            stMAX[i][j] = max(stMAX[i][j - 1], stMAX[i + (1 << (j - 1))][j - 1]);
        }
    }
    for (int i = 1; i <= n; ++i) {
        stMIN[i][0] = hiInput[i];
    }
    for (int j = 1; (1 << j) <= n; ++j) {
        for (int i = 1; i <= n - (1 << j) + 1; ++i) {
            stMIN[i][j] = min(stMIN[i][j - 1], stMIN[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int rmqMAX(int l, int r)
{
    int lengthQ = r - l + 1;
    int ans     = INT32_MIN;
    int cur     = l;
    int j       = 0;
    while (lengthQ > 0) {
        if (lengthQ & 1) {
            ans = max(ans, stMAX[cur][j]);
            cur += (1 << j);
        }
        lengthQ >>= 1;
        ++j;
    }
    return ans;
}

int rmqMIN(int l, int r)
{
    int lengthQ = r - l + 1;
    int ans     = INT32_MAX;
    int cur     = l;
    int j       = 0;
    while (lengthQ > 0) {
        if (lengthQ & 1) {
            ans = min(ans, stMIN[cur][j]);
            cur += (1 << j);
        }
        lengthQ >>= 1;
        ++j;
    }
    return ans;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        cin >> hiInput[i];
    }
    init();
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << rmqMAX(l, r) - rmqMIN(l, r) << '\n';
    }
    return 0;
}

