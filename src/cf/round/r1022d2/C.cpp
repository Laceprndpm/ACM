#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    vector<i64> weight(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> weight[i];
    }
    auto cmp = [&](int u, int v) -> bool {
        if (weight[u] == weight[v]) {
            return u > v;
        } else {
            return weight[u] < weight[v];
        }
    };
    priority_queue<i64, vector<i64>, decltype(cmp)> pq(cmp);
    for (int i = 1; i <= n; i++) {
        pq.push(i);
    }
    i64          ans = 0;
    vector<bool> finishfront(n + 1, false);
    while (!pq.empty()) {
        i64 cur = pq.top();
        pq.pop();
        if (cur - 1 >= 1 && (weight[cur - 1] > weight[cur] || (finishfront[cur - 1]))) {
            finishfront[cur] = true;
            continue;
        }
        if (cur + 1 <= n && weight[cur] <= weight[cur + 1]) {
            continue;
        }
        ans++;
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