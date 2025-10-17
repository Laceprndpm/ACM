#include <iostream>
#include <vector>

using namespace std;

using i64 = long long;

constexpr int MAXN = 2000;

void solve()
{
    int n;
    cin >> n;
    vector<int>         arr(n + 1);
    vector<vector<int>> prefix(n + 1, vector<int>(MAXN + 1, 0));
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        prefix[i][arr[i]]++;
    }
    for (int i = 1; i <= MAXN; i++) {
        for (int j = 1; j <= n; j++) {
            prefix[j][i] += prefix[j - 1][i];
        }
    }
    for (int i = 1; i <= MAXN; i++) {
        for (int j = 1; j <= n; j++) {
            prefix[j][i] += prefix[j][i - 1];
        }
    }
    i64 ans  = 0;
    int ansl = 1, ansr = 1;
    for (int l = 1; l <= n; l++) {
        for (int r = l + 1; r <= n; r++) {
            i64 substract = prefix[r][arr[l] - 1] - prefix[l][arr[l] - 1];
            i64 add       = (prefix[r][MAXN] - prefix[l][MAXN]) - (prefix[r][arr[l]] - prefix[l][arr[l]]);
            // ans = max(ans, substract-add);
            if (ans < substract - add) {
                ansl = l, ansr = r;
                ans = substract - add;
            }
        }
    }
    cout << ansl << ' ' << ansr << '\n';
}

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
