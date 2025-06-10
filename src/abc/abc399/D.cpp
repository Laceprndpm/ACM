#include <compare>
#include <map>
#include <utility>
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
    map<pair<int, int>, int> mp;
    vector<int>              arr(n * 2 + 4);
    for (int i = 1; i <= 2 * n; i++) {
        cin >> arr[i];
    }
    i64 ans = 0;
    i64 a, b;

    pair<i64, i64> lastp = {0, 0};
    for (int i = 1; i < 2 * n; i++) {
        a                      = arr[i];
        b                      = arr[i + 1];
        pair<i64, i64> curpair = {min(a, b), max(a, b)};
        if (curpair == lastp) {
            lastp = {0, 0};
            continue;
        }
        lastp = curpair;
        if (a == arr[i - 1] || arr[i + 2] == b || a == b) {
            continue;
        }
        if (mp.count(curpair) == 0) {
            mp[curpair] = 1;
        } else {
            ans++;
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