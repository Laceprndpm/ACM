#include <algorithm>
#include <functional>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n, m;
    cin >> n;
    vector<int> ai(n);
    for (int& i : ai) {
        cin >> i;
    }
    cin >> m;
    vector<int> bi(m);
    for (int& i : bi) {
        cin >> i;
    }
    sort(ai.begin(), ai.end(), greater<int>());
    sort(bi.begin(), bi.end(), greater<int>());
    if (ai[0] == bi[0]) {
        cout << "Alice" << '\n' << "Bob" << '\n';
    } else if (ai[0] > bi[0]) {
        cout << "Alice" << '\n' << "Alice" << '\n';
    } else {
        cout << "Bob" << '\n' << "Bob" << '\n';
    }
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