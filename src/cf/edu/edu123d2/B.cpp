#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

bool check(auto a, auto b)
{
    while (a + 2 != b) {
        if (*a + *(a + 1) == *(a + 2)) {
            return false;
        }
        a++;
    }
    return true;
}

void solve()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    if (n == 3) {
        cout << "3 2 1\n";
        cout << "1 3 2\n";
        cout << "3 1 2\n";
        return;
    }
    iota(arr.rbegin(), arr.rend(), 1);
    for (int i = 0; i < n; i++) {
        for (int j = i; j < i + n; j++) {
            cout << arr[j % n] << ' ';
        }
        cout << '\n';
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