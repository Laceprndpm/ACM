#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (n); i++)
using namespace std;

int inf = 1000000010;

int main()
{
    int n;
    cin >> n;
    vector<vector<char>> c(n, vector<char>(n));
    rep(i, n) rep(j, n) cin >> c[i][j];
    vector<vector<int>>   a(n, vector<int>(n, inf));
    queue<pair<int, int>> que;
    rep(i, n)
    {
        que.push({i, i});
        a[i][i] = 0;
    }
    rep(i, n) rep(j, n)
    {
        if (i == j or c[i][j] == '-') continue;
        que.push({i, j});
        a[i][j] = 1;
    }
    while (!que.empty()) {
        auto q = que.front();
        que.pop();
        int i = q.first, j = q.second;
        rep(k, n) rep(l, n)
        {
            if (c[k][i] != '-' && c[j][l] != '-' && c[k][i] == c[j][l] && a[k][l] == inf) {
                a[k][l] = a[i][j] + 2;
                que.push({k, l});
            }
        }
    }
    rep(i, n)
    {
        rep(j, n)
        {
            cout << (a[i][j] == inf ? -1 : a[i][j]) << " \n"[j == n - 1];
        }
    }
}
