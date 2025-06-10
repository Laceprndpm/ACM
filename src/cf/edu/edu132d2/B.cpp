#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
#define int i64

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    vector<int> r(n + 1);
    vector<int> l(n + 1);
    for (int i = 2; i <= n; i++) {
        l[i] = l[i - 1] + max(arr[i] - arr[i - 1], 0ll);
    }
    for (int i = n - 1; i >= 1; i--) {
        r[i] = r[i + 1] + max(arr[i] - arr[i + 1], 0ll);
    }
    while (m--) {
        int a, b;
        cin >> a >> b;
        if (a > b) {
            cout << l[a] - l[b];
        } else {
            cout << -r[b] + r[a];
        }
        cout << '\n';
    }
    return 0;
}