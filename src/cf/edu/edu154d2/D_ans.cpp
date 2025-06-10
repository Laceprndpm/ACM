/**
 *    author:  tourist
 *    created: 31.08.2023 10:35:08
 **/
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv)
{
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    cin >> tt;
    while (tt--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        int ans = 0;
        for (int i = 0; i < n - 1; i++) {
            ans += (a[i] >= a[i + 1]);
        }
        int cur = ans;
        for (int i = 0; i < n - 1; i++) {
            cur -= (a[i] >= a[i + 1]);
            if (i > 0) {
                cur += (a[i] >= a[i - 1]);
            }
            ans = min(ans, cur + 1);
        }
        cout << ans << '\n';
    }
    return 0;
}
