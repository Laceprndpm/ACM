#include <bits/stdc++.h>
using namespace std;
int         n, m;
int         ans[2002002];
vector<int> g[2002002], h[2002002];
int         d[2002002], c[2002002], q;
int         a[2002002], b[2001001];
int         tr[2002002];
int         to[2002002];

int lowbit(int x)
{
    return x & (-x);
}

void push(int x, int y)
{
    for (; x <= 2 * n; x += lowbit(x))
        tr[x] += y;
}

int get(int x)
{
    int sum = 0;
    for (; x; x -= lowbit(x))
        sum += tr[x];
    return sum;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
        cin >> a[i] >> b[i], to[a[i]] = b[i], to[b[i]] = a[i];
    cin >> q;
    for (int i = 1; i <= q; i++) {
        cin >> c[i] >> d[i];
        if (c[i] > d[i]) swap(c[i], d[i]);
        g[c[i]].push_back(i);
        h[d[i]].push_back(i);
    }
    for (int i = 1; i <= 2 * n; i++) {
        if (to[i] != 0) {
            if (to[i] > i)
                push(to[i], 1);
            else
                push(i, -1);
        }
        for (auto j : g[i])
            ans[j] += get(d[j]);
    }
    memset(tr, 0, sizeof(tr));
    for (int i = 2 * n; i >= 1; i--) {
        if (to[i] != 0) {
            if (to[i] < i)
                push(2 * n + 1 - to[i], 1);
            else
                push(2 * n + 1 - i, -1);
        }
        for (auto j : h[i])
            ans[j] += get(2 * n + 1 - c[j]);
    }
    for (int i = 1; i <= q; i++)
        cout << ans[i] << "\n";
}