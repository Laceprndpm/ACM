#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
using Graph       = vector<vector<int>>;
constexpr int INF = INT32_MAX;

int check(int x, const string& target)
{
    string subs = "FBFFBFFB";
    int    l    = target.length();
    for (int i = 0; i < l; i++) {
        int idx1 = (i + x) % 8;
        if (subs[idx1] != target[i]) {
            return false;
        }
    }
    return true;
}

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    for (int i = 0; i < 8; i++) {
        if (check(i, s)) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
    return;
}

//  F B F F B  F  F B
//  3 5 6 9 10 12 15

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