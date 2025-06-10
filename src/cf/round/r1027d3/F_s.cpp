#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;
#define int long long
const int INF = 1e18;
#define F(i, l, r) for (int i = l; i <= r; i++)
#define R(i, l, r) for (int i = r; i >= l; i--)
#define pii        pair<int, int>
const int mod = 998244353;
// const int mod = 1e9+7;
const int   M = 1e7 + 5;
int         a[N], b[N], c[N], d[N], dp[N];
int         dx[4] = {1, 0, -1, 0};
int         dy[4] = {0, 1, 0, -1};
int         n, m, k, ans;
bool        temp;
string      s;
vector<int> v[N];

struct node {
    int x, y;
} jie[N];

void solve()
{
    int x, y;
    cin >> x >> y >> k;
    int gc = __gcd(x, y);
    x /= gc, y /= gc;
    int ans = 0;
    if (x > 1) {
        int op = 0;
        for (int i = 1; i * i <= x; i++) {
            if (x % i == 0) {
                a[++op] = i;
                if (x / i != i) a[++op] = x / i;
            }
        }
        sort(a + 1, a + 1 + op);
        F(i, 1, op) dp[i] = INF;
        F(i, 1, op)
        {
            if (a[i] <= k) {
                dp[i] = 1;
                continue;
            }
            F(j, 1, i - 1)
            {
                if (a[i] % a[j] == 0 && a[i] / a[j] <= k) dp[i] = min(dp[i], dp[j] + 1);
            }
        }
        ans += dp[op];
    }
    x = y;
    if (x > 1) {
        int op = 0;
        for (int i = 1; i * i <= x; i++) {
            if (x % i == 0) {
                a[++op] = i;
                if (x / i != i) a[++op] = x / i;
            }
        }
        sort(a + 1, a + 1 + op);
        F(i, 1, op) dp[i] = INF;
        F(i, 1, op)
        {
            if (a[i] <= k) {
                dp[i] = 1;
                continue;
            }
            F(j, 1, i - 1)
            {
                if (a[i] % a[j] == 0 && a[i] / a[j] <= k) dp[i] = min(dp[i], dp[j] + 1);
            }
        }
        ans += dp[op];
    }
    if (ans >= INF) ans = -1;
    cout << ans << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);  // cin.tie(nullptr);
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}