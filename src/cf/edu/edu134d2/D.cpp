#include <cstdint>
#include <map>
#include <utility>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

// 0 1 0 1
//
bool check(vector<int> &a, vector<int> &b, int tryEach, int n)
{
    map<int, int> cnt;
    for (int i = 1; i <= n; i++) {
        cnt[a[i] & tryEach]++;
    }
    for (int i = 1; i <= n; i++) {
        cnt[((~b[i]) & INT32_MAX) & tryEach]--;
    }
    for (pair<int, int> i : cnt) {
        if (i.second != 0) {
            return false;
        }
    }
    return true;
}

void solve()
{
    int n;
    int tryEach = 0;
    cin >> n;
    vector<int> a(n + 1);
    vector<int> b(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    for (int i = 29; i >= 0; i--) {
        tryEach |= (1 << i);
        if (!check(a, b, tryEach, n)) {
            tryEach &= ~(1 << i);
        }
    }
    cout << tryEach << '\n';
}

signed main(int argc, char **argv)
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