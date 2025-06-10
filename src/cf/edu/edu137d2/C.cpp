#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int i   = 0;
    i64 ans = 0;
    for (; i < n; i++) {
        if (i + 1 < n && s[i] == '0' && s[i + 1] == '1') {
            int j    = i + 1;
            int minE = arr[i];
            i64 sumE = arr[i];
            while (s[j] == '1') {
                sumE += arr[j];
                minE = min(minE, arr[j]);
                j++;
            }
            ans += sumE - minE;
            i = j - 1;
            continue;
        }
        if (s[i] == '1') {
            ans += arr[i];
        }
    }
    cout << ans << '\n';
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