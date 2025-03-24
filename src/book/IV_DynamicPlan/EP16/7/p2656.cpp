#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

signed main(int argc, char** argv)
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
    vector<int>    u(m + 1), v(m + 1), num(m + 1);
    vector<double> recovery(m + 1);
    for (int i = 1; i <= m; i++) {
        cin >> u[i] >> v[i] >> num[i] >> recovery[i];
    }
    
    return 0;
}