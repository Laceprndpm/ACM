#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<ll> a(n), b(m);
        for (int i = 0; i < n; i++)
            cin >> a[i];
        for (int i = 0; i < m; i++)
            cin >> b[i];
        vector<int> pref(n + 1, 0);
        int         j = 0;
        for (int i = 1; i <= n; i++) {
            if (j < m && a[i - 1] >= b[j]) {
                j++;
            }
            pref[i] = j;
        }
        if (pref[n] == m) {
            cout << 0 << "\n";
            continue;
        }
        vector<int> suff(n + 2, 0);
        int         back_j = m - 1, matchedBack = 0;
        for (int i = n; i >= 1; i--) {
            if (back_j >= 0 && a[i - 1] >= b[back_j]) {
                back_j--;
                matchedBack++;
            }
            suff[i] = matchedBack;
        }
        suff[n + 1]  = 0;
        const ll INF = (ll)4e18;
        ll       ans = INF;
        for (int i = 0; i <= n; i++) {
            int x = pref[i];
            int y = suff[i + 1];
            if (x + y >= m - 1) {
                if (x < m) {
                    ans = min(ans, b[x]);
                }
            }
        }
        if (ans == INF) ans = -1;
        cout << ans << "\n";
    }
    return 0;
}
