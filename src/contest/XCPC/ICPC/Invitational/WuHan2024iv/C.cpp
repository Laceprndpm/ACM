#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<i64> frr(n * 2);
    vector<i64> ansarr(n * 2);
    i64         T = n * 2 - 1;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    for (int i = 1; i <= n; i++) {
        if (i != n) {
            int f = (arr[i] / T) * 2;
            if (arr[i] % T <= (n - i) * 2 + 1)
                f += 1;
            else
                f += 2;
            frr[i] = f;
        } else {
            frr[i] = (arr[i] + T - 1) / T * 2;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j * frr[i] < 2 * n; j++) {
            ansarr[j * frr[i]]++;
        }
    }
    cout << "ans:\n";
    for (int i = 0; i < n; i++) {
        cout << ansarr[i * 2] + ansarr[i * 2 + 1] << ' ';
    }
    cout << '\n';
    return;
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}