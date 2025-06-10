#include <algorithm>
#include <cstdint>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

i64 qpow(i64 n, i64 q)
{
    if (q == 0) {
        return 1;
    }
    i64 ans = 1;
    while (q > 0) {
        if (q & 1) {
            ans *= n;
        }
        n *= n;
        q >>= 1;
    }
    return ans;
}

void solve()
{
    i64 n, k;
    cin >> n >> k;
    vector<i64> ai(n);
    for (i64& i : ai) {
        cin >> i;
    }
    sort(ai.begin(), ai.end(), less<>());
    i64 ans = 0;
    k++;
    for (int i = 0; i < ai.size(); i++) {
        i64 limit = INT64_MAX;
        if (i != ai.size() - 1) limit = qpow(10, ai[i + 1] - ai[i]) - 1;
        i64 curneed = min(k, limit);
        k -= curneed;
        ans += curneed * qpow(10, ai[i]);
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