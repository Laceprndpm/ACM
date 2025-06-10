#include <bits/stdc++.h>
#define int     long long
#define in      inline
#define ri      register
#define _123hh2 0
using namespace std;

in int read()
{
    int  x = 0, f = 1;
    char ch = getchar();
    while (ch > '9' || ch < '0') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x  = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

in void write(int x)
{
    if (x < 0) {
        x = -x;
        putchar('-');
    }
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

const int maxn = 1e6 + 5;
const int mod  = 1e9 + 7;
string    awa[maxn];
int       n, m, fa[maxn], zt[maxn];

int find(int x)
{
    return x == fa[x] ? fa[x] : fa[x] = find(fa[x]);
}

void join(int x, int y)
{
    fa[find(x)] = fa[find(y)];
}

vector<pair<int, int>> qwq;
map<int, bool>         q;

in int fstpow(int n, int m)
{
    if (!m) return 1;
    int ans = 1, base = n % mod;
    while (m) {
        if (m & 1) ans *= base, ans %= mod;
        base *= base, base %= mod, m >>= 1;
    }
    return ans;
}

bool check(pair<int, int> it)
{
    int u = it.first, v = it.second;
    if (find(u) == find(v)) {
        if (zt[u] == zt[v]) return 1;
        return 0;
    } else {
        if (zt[u] != zt[v]) {
            join(u, v);
            return 0;
        }
        int now = find(u);
        for (int i = 1; i <= n; i++) {
            if (find(fa[i]) == now) zt[i] ^= 1;
        }
        join(u, v);
    }
    return 0;
}

void change(int x)
{
    int to = find(x);
    for (int i = 1; i <= n; i++)
        if (find(i) == to) zt[i] = 0;
}

void deal()
{
    for (int i = 1; i <= n; i++)
        fa[i] = i, zt[i] = -1;
    qwq.clear(), q.clear();
    for (int i = 0; i < m / 2; i++) {
        int f1 = 0, f2 = 0, k1 = 0, k2 = 0;
        for (int j = 1; j <= n; j++) {
            if (awa[j][i] == '1') {
                if (!f1)
                    f1 = j, k1 = i;
                else {
                    if (!f2)
                        f2 = j, k2 = i;
                    else {
                        cout << 0 << endl;
                        return;
                    }
                }
            }
            if (awa[j][m - i - 1] == '1') {
                if (!f1)
                    f1 = j, k1 = m - i - 1;
                else {
                    if (!f2)
                        f2 = j, k2 = m - i - 1;
                    else {
                        cout << 0 << endl;
                        return;
                    }
                }
            }
        }
        if (!f1 && !f2)
            continue;
        else if (f1 && !f2)
            continue;
        else if (f1 && f2) {
            if (k1 != k2) {
                join(f1, f2);
                change(f1);
            } else
                qwq.push_back(make_pair(f1, f2));
        }
    }
    if (m & 1) {
        int cnt = 0;
        for (int j = 1; j <= n; j++)
            if (awa[j][m / 2] == '1') cnt++;
        if (cnt >= 2) {
            cout << 0 << endl;
            return;
        }
    }
    for (auto it : qwq)
        if (check(it)) {
            cout << 0 << endl;
            return;
        }
    for (int i = 1; i <= n; i++) {
        q[find(fa[i])] = 1;
    }
    cout << fstpow(2, q.size()) << endl;
}

signed main()
{
    cin.tie(NULL);
    cout.tie(NULL);
    int t = read();
    while (t-- > 0) {
        n = read(), m = read();
        for (int i = 1; i <= n; i++)
            cin >> awa[i];
        deal();
    }
    return _123hh2;
}