#include <bits/stdc++.h>
using namespace std;
int dp[1000001], inf = 1000000000;

int gcd(int a, int b)
{
    return b > 0 ? gcd(b, a % b) : a;
}

struct qry {
    int x;
    int y;
    int k;
    int id;

    friend bool operator<(qry a, qry b)
    {
        return a.k < b.k;
    }
} qx[10000];

int ans[10000];

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int q, g, i, j, t;
    for (i = 1; i <= 1000000; i++)
        dp[i] = inf;
    dp[1] = 0;
    cin >> q;
    for (i = 0; i < q; i++) {
        cin >> qx[i].x >> qx[i].y >> qx[i].k;
        qx[i].id = i;
        g        = gcd(qx[i].x, qx[i].y);
        qx[i].x /= g;
        qx[i].y /= g;
    }
    sort(qx, qx + q);
    j = 1;
    for (i = 0; i < q; i++) {
        for (; j <= qx[i].k; j++) {
            for (t = 1; j * t <= 1000000; t++)  // 起点
                dp[j * t] = min(dp[j * t], dp[t] + 1);
        }
        if (dp[qx[i].x] == inf || dp[qx[i].y] == inf)
            ans[qx[i].id] = -1;
        else
            ans[qx[i].id] = dp[qx[i].x] + dp[qx[i].y];
    }
    for (i = 0; i < q; i++)
        cout << ans[i] << '\n';
    return 0;
}