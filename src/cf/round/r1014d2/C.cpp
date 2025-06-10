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
    vector<int> arr(n);
    int         cnt1 = 0;
    i64         sumA = 0;
    for (int& i : arr) {
        cin >> i;
        sumA += i;
        if (i % 2) {
            cnt1++;
        }
    }
    if (cnt1 == n || cnt1 == 0) {
        cout << *max_element(arr.begin(), arr.end()) << '\n';
        return;
    }
    cout << sumA - cnt1 + 1 << '\n';
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