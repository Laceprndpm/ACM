#include <algorithm>
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
    vector<int> a(n);
    for (int& i : a) {
        cin >> i;
    }
    int cnt0P = count(a.begin(), a.begin() + 2, 0);
    int cnt0S = count(a.begin() + 2, a.begin() + n, 0);
    if (cnt0P + cnt0S == 0) {
        cout << 1 << '\n';
        cout << 1 << ' ' << n << '\n';
        return;
    }
    if (cnt0P == 0) {
        cout << 2 << '\n';
        cout << 3 << ' ' << n << '\n';
        cout << "1 3\n";
        return;
    }
    if (cnt0S == 0) {
        cout << "2\n";
        cout << "1 2\n";
        cout << 1 << ' ' << n - 1 << '\n';
        return;
    }
    cout << 3 << '\n';
    cout << "1 2" << '\n';
    cout << "2 " << n - 1 << '\n';
    cout << "1 2\n";
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
    // n>=4
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}