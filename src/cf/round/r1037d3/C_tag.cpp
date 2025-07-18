#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int       n, k, a[maxn], mx = -1e9;

void solve()
{
    cin >> n >> k;
    mx = -1e9;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        mx = max(mx, a[i]);
    }
    int waterpos = 1, mypos = a[k] + 1, now;
    sort(a + 1, a + n + 1);
    for (int i = n; i >= 1; i--) {
        if (a[i] == mypos - 1) {
            now = i;
            break;
        }
    }
    while (1) {
        if (mypos == mx + 1) {
            cout << "YES\n";
            return;
        } else if (mypos <= waterpos) {
            cout << "NO\n";
            return;
        }
        int len = mypos - waterpos, nxt = -1;
        for (int i = n; i >= now + 1; i--) {
            if (a[i] - a[now] <= len) {
                nxt = i;
                break;
            }
        }
        if (nxt == -1) {
            cout << "NO\n";
            return;
        }
        waterpos += a[nxt] - a[now];
        mypos = a[nxt] + 1;
        now   = nxt;
    }
}

int main()
{
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}